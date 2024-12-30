#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "raylib.h"

#include "core_lib/core/logger.h"

namespace sauna_core
{

static const int k_LoadTimeBufferSize = 30;

enum class ResourceType
{
    Model,
    Font,
    Texture2D,
    Image,
    Unknown
};

// Definition of a resource that can be loaded and managed by the ResourceManager.
// Once registered with the ResourceManager, the resources can be loaded, unloaded,
// and accessed using the name provided with the initial Resource definition.
//
// Additionally, resources can be scoped which allows for grouping a batch of
// resources together to be loaded or unloaded together. This can be used to
// for example load all resources for a specific scene, and then unload them once
// the scene is no longer active (while maintaining other resources that are not
// included within that scope).
struct Resource
{
    std::string name;
    std::string path;
    ResourceType type;
    // The scope of this resource. If not specified, it will be global.
    // Scope defines the 'bucket' that this resource will be loaded with.
    // Scopes can be used to load and unload resources in groups.
    std::string scope;
};

// Container for resource loading diagnostics.
// Maintains a count of resources loaded, unloaded, queued, failed, and cancelled.
struct ResourceDiagnostics
{
    int totalResourcesLoaded = 0;
    int totalResourcesUnloaded = 0;
    int totalResourcesQueued = 0;
    int totalResourcesFailed = 0;
    int totalResourcesCancelled = 0;

    int numActiveResources = 0;
    int maxActiveResources = 0;
    int numScopes = 0;
    int maxScopes = 0;

    double lastLoadTime = 0.0;
    double longestLoadTime = 0.0;
    double shortestLoadTime = 0.0;
    double averageLoadTime = 0.0;

    long long activeResourceSize = 0;
    long long maxLoadedResourceSize = 0;
    long long minLoadedResourceSize = 0;
};

class ResourceDiagnosticReporter
{
public:
    inline void addLoadedResource(std::string scope, double loadTime, long long size)
    {
        // Handle first-resource special case.
        if (m_diagnostics.totalResourcesLoaded == 0 && m_diagnostics.minLoadedResourceSize == 0) {
            m_diagnostics.minLoadedResourceSize = size;
        }

        // Normal flow.
        m_diagnostics.totalResourcesLoaded += 1;
        m_diagnostics.numActiveResources += 1;
        m_diagnostics.totalResourcesQueued -= 1;

        if (m_diagnostics.numActiveResources > m_diagnostics.maxActiveResources) {
            m_diagnostics.maxActiveResources = m_diagnostics.numActiveResources;
        }

        // TODO: Add scope to vector IF is not already in

        if (m_loadTimeCount < k_LoadTimeBufferSize)
            m_loadTimeCount++;

        m_loadTimes[m_loadTimeCursor] = loadTime;
        m_loadTimeCursor = (m_loadTimeCursor + 1) % k_LoadTimeBufferSize;
        
        double sum = 0.0;
        for (int i = 0; i < m_loadTimeCount; i++)
            sum += m_loadTimes[i];

        if (m_loadTimeCount > 0)
            m_diagnostics.averageLoadTime = sum / m_loadTimeCount;

        if (size > m_diagnostics.maxLoadedResourceSize)
            m_diagnostics.maxLoadedResourceSize = size;

        if (size < m_diagnostics.minLoadedResourceSize)
            m_diagnostics.minLoadedResourceSize = size;

        m_diagnostics.activeResourceSize += size;
    }

    inline void addUnloadedResource(long long size)
    {
        m_diagnostics.totalResourcesUnloaded += 1;
        m_diagnostics.numActiveResources -= 1;
        m_diagnostics.activeResourceSize -= size;
        
        // TODO: Scopes
    }

    inline void addCancelledResource(int amount = 1)
    {
        m_diagnostics.totalResourcesCancelled += amount;
        m_diagnostics.totalResourcesQueued -= amount;
    }

    inline void addFailedResource()
    {
        m_diagnostics.totalResourcesFailed += 1;
        m_diagnostics.totalResourcesQueued -= 1;

    }

    inline void addQueuedResource()
    {
        m_diagnostics.totalResourcesQueued += 1;
    }

    inline void removeQueuedResource(int amount = 1)
    {
        m_diagnostics.totalResourcesQueued -= amount;
    }

    inline void flush()
    {
        m_diagnostics = { 0 };
        m_loadTimeCursor = 0;
        m_loadTimeCount = 0;
        m_activeScopes.clear();
        for (int i = 0; i < k_LoadTimeBufferSize; i++) {
            m_loadTimes[i] = 0;
        }
    }

    inline ResourceDiagnostics &getDiagnostics()
    {
        return m_diagnostics;
    }

private:
    ResourceDiagnostics m_diagnostics = { 0 };
    double m_loadTimes[k_LoadTimeBufferSize];
    int m_loadTimeCursor = 0;
    int m_loadTimeCount = 0;
    std::vector<std::string> m_activeScopes = {};
};

class ResourceManager
{
public:
    static ResourceManager& Get();
    static void Init();
    static void Shutdown();

    ResourceManager(const ResourceManager&) = delete; // Prevent copying
    ResourceManager& operator=(const ResourceManager&) = delete; // Prevent copy assignment

    inline ResourceDiagnostics &getDiagnostics()
    {
        return m_diagnostics.getDiagnostics();
    }

    void queueResource(const Resource& Resource);
    void queueResources(std::initializer_list<const Resource> resources);
    void clearQueue();
    void loadQueuedResources();
    void cancelCurrentLoad();

    void unloadAllResources();
    void unloadScope(std::string scope);
    void unloadResource(std::string name);

    Model& getModel(std::string name);
    Font& getFont(std::string name);
    Texture2D& getTexture(std::string name);
    Image& getImage(std::string name);

private:
    ResourceManager();
    ~ResourceManager();

    bool hasActiveResource_();
    void loadResource_(Resource& resource);
    void unloadResourceById_(int id);

    static inline const std::string GetResourceBasePath()
    {
        const char *raw = GetApplicationDirectory();
        std::string base = std::string(raw);
        assert(base.length() > 0);

        // Normalize slashes
        for (char& c : base) {
            if (c == '\\') {
                c = '/';
            }
        }

        return base + "resources/";
    }

private:
    int m_idCounter = -1;
    bool m_loadActive = false;
    bool m_cancelLoadFlag = false;
    float m_loadProgress = 0.0f;
    ResourceDiagnosticReporter m_diagnostics;

    std::vector<Resource> m_queue{};
    std::unordered_map<std::string, int> m_resourceIdLookup;
    std::unordered_map<int, Resource> m_resourceMap;

    std::unordered_map<std::string, std::vector<int>> m_scopedResources;
    std::unordered_map<int, Model> m_models;
    std::unordered_map<int, Font> m_fonts;
    std::unordered_map<int, Texture2D> m_textures;
    std::unordered_map<int, Image> m_images;
};

inline ResourceManager* g_resourceManager = nullptr;

}; // namespace sauna_core