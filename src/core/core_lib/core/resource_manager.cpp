#include <assert.h>

#include "core_lib/core/resource_manager.h"
#include "core_lib/core/logger.h"
#include "core_lib/chrono/measure.h"

using namespace sauna_core;

static std::string k_AppDirectoryPath;

ResourceManager& ResourceManager::Get()
{
    assert(g_resourceManager != nullptr);
    return *g_resourceManager;
};

void ResourceManager::Init()
{
    k_AppDirectoryPath = ResourceManager::GetResourceBasePath();

    assert(g_resourceManager == nullptr);
    g_resourceManager = new ResourceManager();
};

void ResourceManager::Shutdown()
{
    g_resourceManager->clearQueue();
    g_resourceManager->unloadAllResources();
    delete g_resourceManager;
    g_resourceManager = nullptr;
};

ResourceManager::ResourceManager()
{
    Logger::LogInfo("App directory: {}", k_AppDirectoryPath);

    // Setup space reservations
    m_resourceIdLookup.reserve(20);
    m_resourceMap.reserve(20);

    m_queue.reserve(20);
    m_scopedResources.reserve(3);
    m_models.reserve(10);
    m_textures.reserve(10);
    m_images.reserve(10);
    m_fonts.reserve(5);
}

ResourceManager::~ResourceManager()
{
    if (hasActiveResource_())
    {
        // warning! Shutdown needs to occur
        unloadAllResources();
    }

    // Unload all resources
    unloadAllResources();

    // Flush queues and maps
    m_diagnostics.flush();
    m_resourceIdLookup.clear();
    m_resourceMap.clear();
    m_queue.clear();
    m_scopedResources.clear();
    m_models.clear();
    m_fonts.clear();
    m_textures.clear();
    m_images.clear();
}

bool ResourceManager::hasActiveResource_()
{
    return m_models.size() > 0 || m_fonts.size() > 0 || m_textures.size() > 0 || m_images.size() > 0;
}

// Queuing 

void ResourceManager::queueResource(const Resource& resource)
{
    assert(resource.name.length() > 0 && resource.path.length() > 0);
    if (m_resourceIdLookup.contains(resource.name)) {
        Logger::LogWarn("Resource {} already loaded -- skipping", resource.name);
        return;
    }

    Logger::LogInfo("Queuing resource: {}", resource.name);
    m_queue.emplace_back(resource);
    m_diagnostics.addQueuedResource();
}

void ResourceManager::queueResources(std::initializer_list<const Resource> resources)
{
    for (auto& resource : resources) {
        queueResource(resource);
    }
}

void ResourceManager::clearQueue()
{
    m_diagnostics.removeQueuedResource(m_queue.size());
    m_queue.clear();
}

// Resource Lifecycle

// TODO: INVESTIGATE THIS FOR COPIES AND ALLOCATIONS!!
void ResourceManager::loadResource_(Resource& resource)
{
    assert(resource.name.length() > 0 && resource.path.length() > 0);
    if (m_resourceIdLookup.contains(resource.name)) {
        return;
    }

    // Load given resource
    auto loadFailed = false;
    long long resourceSize = -1;
    const int resourceId = ++m_idCounter;
    assert(!m_resourceMap.contains(resourceId));

    sauna_chrono::Measure loadTimer;
    std::string resourcePath = k_AppDirectoryPath + resource.path;
    
    Logger::LogInfo("Resource {} assigned ID {}, loading...", resource.name, resourceId);
    switch (resource.type)
    {
    case ResourceType::Model:
        assert(!m_models.contains(resourceId));
        auto model = LoadModel(resourcePath.c_str());
        m_models.insert({ resourceId, model });
        resourceSize = sizeof(model);
        // TODO: FAILED CHECK (CHECK RAYLIB SOURCE FOR THIS LOAD FN)
        break;

    case ResourceType::Font:
        assert(!m_fonts.contains(resourceId));
        auto font = LoadFont(resourcePath.c_str());
        m_fonts.insert({ resourceId, font });
        resourceSize = sizeof(font);
        // TODO: FAILED CHECK (CHECK RAYLIB SOURCE FOR THIS LOAD FN)
        break;

    case ResourceType::Image:
        assert(!m_images.contains(resourceId));
        auto image = LoadImage(resourcePath.c_str());
        m_images.insert({ resourceId, image });
        resourceSize = sizeof(image);
        // TODO: FAILED CHECK (CHECK RAYLIB SOURCE FOR THIS LOAD FN)
        break;

    case ResourceType::Texture2D:
        assert(!m_textures.contains(resourceId));
        auto texture = LoadTexture(resourcePath.c_str());
        m_textures.insert({ resourceId, texture });
        resourceSize = sizeof(texture);
        // TODO: FAILED CHECK (CHECK RAYLIB SOURCE FOR THIS LOAD FN)
        break;

    default:
        Logger::LogError("Invalid resource type for resource provided");
        return;
    }

    // Cache resource info
    if (!m_scopedResources.contains(resource.scope)) {
        m_scopedResources.emplace(resource.scope, 20);
    }

    m_scopedResources[resource.scope].emplace_back(resourceId);
    m_resourceIdLookup.emplace(resource.name, resourceId);
    m_resourceMap.emplace(resourceId, resource);
    Logger::LogInfo("Resource {} loaded.", resource.name, resourceId);

    if (loadFailed) {
        m_diagnostics.addFailedResource();
        return;
    }

    loadTimer.done();
    m_diagnostics.addLoadedResource(resource.scope, loadTimer.getDurationMilliseconds(), resourceSize);
}

void ResourceManager::loadQueuedResources()
{
    if (m_queue.size() == 0) {
        Logger::LogWarn("Attempting to load zero resources!"); // TODO: Remove
        return;
    }

    if (m_loadActive) {
        Logger::LogWarn("Attempting to load while already loading!"); // TODO: Remove
        return;
    }

    // TODO: Background thread.
    // TODO: Emit events?
    m_loadActive = true;
    m_cancelLoadFlag = false;
    m_loadProgress = 0.0f;
    int numLoaded = 0;
    size_t total = m_queue.size();

    for (auto& resource : m_queue) {
        if (m_cancelLoadFlag) {
            m_loadActive = false;
            m_loadProgress = 0.0f;
            m_cancelLoadFlag = false;
            m_diagnostics.addCancelledResource(total - numLoaded);
            return;
        }

        loadResource_(resource);
        numLoaded++;
        m_loadProgress = static_cast<float>(numLoaded) / total;
    }

    m_loadActive = false;
    m_cancelLoadFlag = false;
    m_loadProgress = 1.0f;
    m_queue.clear();
}

void ResourceManager::cancelCurrentLoad()
{
    Logger::LogInfo("Attempting to cancel current resource load");
    m_cancelLoadFlag = true;
}

void ResourceManager::unloadResourceById_(int id)
{
    // TODO: New thread.
    // TODO: emit events?

    if (!m_resourceMap.contains(id)) {
        Logger::LogInfo("Could not find resource to unload with id {}", id);
        return;
    }

    long long resourceSize = -1;
    auto& resource = m_resourceMap[id];

    switch (resource.type) {
    case ResourceType::Model:
        assert(m_models.contains(id));
        resourceSize = sizeof(m_models[id]);
        UnloadModel(m_models[id]);
        m_models.erase(id);
        break;

    case ResourceType::Font:
        assert(m_fonts.contains(id));
        resourceSize = sizeof(m_fonts[id]);
        UnloadFont(m_fonts[id]);
        m_fonts.erase(id);
        break;

    case ResourceType::Texture2D:
        assert(m_textures.contains(id));
        resourceSize = sizeof(m_textures[id]);
        UnloadTexture(m_textures[id]);
        m_textures.erase(id);
        break;

    case ResourceType::Image:
        assert(m_images.contains(id));
        resourceSize = sizeof(m_images[id]);
        UnloadImage(m_images[id]);
        m_images.erase(id);
        break;

    default:
        Logger::LogError("Invalid resource type for unloading resource provided");
        return;
    }

    if (m_scopedResources.contains(resource.scope)) {
        auto& list = m_scopedResources[resource.scope];
        std::erase(list, id);
    }

    m_resourceMap.erase(id);
    m_resourceIdLookup.erase(resource.name);

    if (resourceSize > -1) {
        m_diagnostics.addUnloadedResource(resourceSize);
    }
}

void ResourceManager::unloadResource(std::string name)
{
    // TODO: New thread.
    // TODO: Emit events?

    if (!m_resourceIdLookup.contains(name)) {
        Logger::LogInfo("Could not find resource to unload with name {}",  name);
        return;
    }

    auto id = m_resourceIdLookup[name];
    unloadResourceById_(id);
}

void ResourceManager::unloadAllResources()
{
    // TODO: New thread
    // TODO: Emit events?

    // NOTE: This is explicitly implemented to fully unload EVERYTHING.
    // It could be implemented to iterate through all ids and use those,
    // but then there is a possibility of missing something that may have
    // failed to unload fully; ie. there is still a model but the associated
    // ID has already been cleaned up.
    m_resourceIdLookup.clear();
    m_resourceMap.clear();
    m_scopedResources.clear();

    for (auto& pair : m_models) {
        UnloadModel(pair.second);
    }
    m_models.clear();

    for (auto& pair : m_fonts) {
        UnloadFont(pair.second);
    }
    m_fonts.clear();

    for (auto& pair : m_images) {
        UnloadImage(pair.second);
    }
    m_images.clear();

    for (auto& pair : m_textures) {
        UnloadTexture(pair.second);
    }
    m_textures.clear();
}

void ResourceManager::unloadScope(std::string scope)
{
    assert(m_scopedResources.contains(scope));
    assert(m_scopedResources[scope].size() > 0);

    for (int resourceId : m_scopedResources[scope]) {
        unloadResourceById_(resourceId);
    }

    m_scopedResources[scope].clear();
    m_scopedResources.erase(scope);
    
    // TODO: DIAGNOSTICS
}

// Getters

Model& ResourceManager::getModel(std::string name)
{
    // TODO: return "missing" model if none found
    assert(m_resourceIdLookup.contains(name));
    int id = m_resourceIdLookup[name];

    assert(m_models.contains(id));
    return m_models[id];
}

Font& ResourceManager::getFont(std::string name)
{
    // TODO: return "missing" font if none found
    assert(m_resourceIdLookup.contains(name));
    int id = m_resourceIdLookup[name];

    assert(m_fonts.contains(id));
    return m_fonts[id];
}

Image& ResourceManager::getImage(std::string name)
{
    // TODO: return "missing" image if none found
    assert(m_resourceIdLookup.contains(name));
    int id = m_resourceIdLookup[name];

    assert(m_images.contains(id));
    return m_images[id];
}

Texture2D& ResourceManager::getTexture(std::string name)
{
    // TODO: return "missing" texture if none found
    assert(m_resourceIdLookup.contains(name));
    int id = m_resourceIdLookup[name];

    assert(m_textures.contains(id));
    return m_textures[id];
}
