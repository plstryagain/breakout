#pragma once

#include "shader.h"
#include "texture2d.h"

#include <map>
#include <string>
#include <filesystem>

class ResourceManager
{
public:
    static ResourceManager& getInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    ~ResourceManager();
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager& operator=(const ResourceManager& other) = delete;

private:
    ResourceManager();

public:
    Shader LoadShader(const std::filesystem::path& vshader_file_path, const std::filesystem::path& fshader_file_path, 
                        const std::filesystem::path& gshader_file_path, const std::string& name);
    Shader GetShader(const std::string& name);
    Texture2D LoadTexture2d(const std::filesystem::path& file_path, bool alpha, const std::string& name);
    Texture2D GetTexture2D(const std::string& name);
    void Clear();

private:
    Shader LoadShaderFromFile(const std::filesystem::path& vshader_file_path, const std::filesystem::path& fshader_file_path, 
                        const std::filesystem::path& gshader_file_path);
    Texture2D LoadTexture2DFromFile(const std::filesystem::path& file_path, bool alpha);

private:
    std::map<std::string, Shader> shaders_;
    std::map<std::string, Texture2D> textures2d_;
};