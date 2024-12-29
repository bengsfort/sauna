#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "raylib.h"

#include "core_lib/core/logger.h"

namespace sauna_core
{

enum class ResourceType
{
    Model,
    Font,
    Texture2D,
    Image,
    Unknown
};

typedef struct Resource
{
    std::string name;
    std::string path;
    ResourceType type;
    // The scope of this resource. If not specified, it will be global.
    // Scope defines the 'bucket' that this resource will be loaded with.
    // Scopes can be used to load and unload resources in groups.
    std::string scope;
} Resource;

class ResourceManager
{
public:
    static ResourceManager& Get();
    static void Init();
    static void Shutdown();

    ResourceManager(const ResourceManager&) = delete; // Prevent copying
    ResourceManager& operator=(const ResourceManager&) = delete; // Prevent copy assignment

    // TODO: Not sure if this needs to be & or not
    void queueResource(const Resource& Resource);
    // TODO: Maybe change the type here? Spread args?
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