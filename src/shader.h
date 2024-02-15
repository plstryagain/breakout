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

public:
    Shader& Use();
    void Compile(std::string_view vertex_source, std::string_view fragment_source, std::string_view geometry_source = std::string_view{});
    void SetFloat(std::string_view name, float value, bool use_shader = false);
    void SetInteger(std::string_view name, int32_t value, bool use_shader = false);
    void SetVector2f(std::string_view name, float x, float y, bool use_shader = false);
    void SetVector2f(std::string_view name, const  glm::vec2& value, bool use_shader = false);
    void SetVector3f(std::string_view name, float x, float y, float z, bool use_shader = false);
    void SetVector3f(std::string_view name, const glm::vec3& value, bool use_shader = false);
    void SetVector4f(std::string_view name, float x, float y, float z, float w, bool use_shader = false);
    void SetVector4f(std::string_view name, const glm::vec4& value, bool use_shader = false);
    void SetMatrix4f(std::string_view name, const glm::mat4& value, bool use_shader = false);

private:
    int32_t GetUniformLocation(std::string_view name);
    void CheckCompilerErrors(uint32_t object, std::string_view type);

private:
    uint32_t id_;
    std::unordered_map<std::string_view, int32_t> location_cache_;
};