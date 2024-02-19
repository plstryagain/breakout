#include "resourcemanager.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <stb_image.h>

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
    Clear();
}

Shader& ResourceManager::LoadShader(const std::filesystem::path& vshader_file_path, const std::filesystem::path& fshader_file_path, 
                    const std::filesystem::path& gshader_file_path, const std::string& name)
{
    shaders_[name] = LoadShaderFromFile(vshader_file_path, fshader_file_path, gshader_file_path);
    return shaders_[name];
}

Shader& ResourceManager::GetShader(const std::string& name)
{
    return shaders_[name];
}

Texture2D& ResourceManager::LoadTexture2d(const std::filesystem::path& file_path, bool alpha, const std::string& name)
{
    textures2d_[name] = LoadTexture2DFromFile(file_path, alpha);
    return textures2d_[name];
}

Texture2D& ResourceManager::GetTexture2D(const std::string& name)
{
    return textures2d_[name];
}

void ResourceManager::Clear()
{
    for (auto& shader : shaders_) {
        shader.second.Clear();
    }
    for (auto& texture : textures2d_) {
        texture.second.Clear();
    }
}

Shader ResourceManager::LoadShaderFromFile(const std::filesystem::path& vshader_file_path, const std::filesystem::path& fshader_file_path, 
                                            const std::filesystem::path& gshader_file_path)
{
    auto read_file = [](const std::filesystem::path& file_path) -> std::string {
        if (file_path.empty()) {
            return std::string{};
        }
        std::ifstream shader_file;
        std::stringstream shader_stream;
        shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            shader_file.open(file_path);
            shader_stream << shader_file.rdbuf();
            shader_file.close();
        } catch (std::ifstream::failure& e) {
            std::string str_error = "ERROR::SHADER::FAILED_TO_READ_FILE: " + file_path.u8string() + e.what();
            std::cout << str_error << std::endl;
            throw std::runtime_error(str_error);
        }
        return shader_stream.str();
    };
    std::string vshader_source = read_file(vshader_file_path);
    std::string fshader_source = read_file(fshader_file_path);
    std::string gshader_source = read_file(gshader_file_path);

    Shader shader;
    shader.Compile(vshader_source, fshader_source, gshader_source);
    return shader;
}

Texture2D ResourceManager::LoadTexture2DFromFile(const std::filesystem::path& file_path, bool alpha)
{
    Texture2D texture{alpha};
    int32_t width = 0;
    int32_t height = 0;
    int32_t nr_channels = 0;
    auto data = stbi_load(file_path.u8string().data(), &width, &height, &nr_channels, 0);
    texture.Generate(width, height, data);
    stbi_image_free(data);
    return texture;
}