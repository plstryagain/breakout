#pragma once

#include <stdint.h>
#include <string>
#include <string_view>
#include <unordered_map>

#include <glm/glm.hpp>

class Shader
{
public:
    Shader();
    ~Shader();
    Shader(const Shader& other) = default;
    Shader& operator=(const Shader& other) = default;

public:
    Shader& Use();
    void Clear();
    void Compile(std::string_view vertex_source, std::string_view fragment_source, std::string_view geometry_source = std::string_view{});
    void SetFloat(const std::string& name, float value, bool use_shader = false);
    void SetInteger(const std::string& name, int32_t value, bool use_shader = false);
    void SetVector2f(const std::string& name, float x, float y, bool use_shader = false);
    void SetVector2f(const std::string& name, const  glm::vec2& value, bool use_shader = false);
    void SetVector3f(const std::string& name, float x, float y, float z, bool use_shader = false);
    void SetVector3f(const std::string& name, const glm::vec3& value, bool use_shader = false);
    void SetVector4f(const std::string& name, float x, float y, float z, float w, bool use_shader = false);
    void SetVector4f(const std::string& name, const glm::vec4& value, bool use_shader = false);
    void SetMatrix4f(const std::string& name, const glm::mat4& value, bool use_shader = false);

private:
    int32_t GetUniformLocation(const std::string& name);
    void CheckCompilerErrors(uint32_t object, std::string_view type);

private:
    uint32_t id_;
    std::unordered_map<std::string, int32_t> location_cache_;
};