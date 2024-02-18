#include "shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdint.h>
#include <iostream>

Shader::Shader()
    : id_(0)
{

}

Shader::~Shader()
{
    Clear();
}

Shader& Shader::Use()
{
    glUseProgram(id_);
    return *this;
}

void Shader::Clear()
{
    if (id_ != 0) {
        glDeleteProgram(id_);
        id_ = 0;
    }
}

void Shader::Compile(std::string_view vertex_source, std::string_view fragment_source, std::string_view geometry_source)
{
    auto compile_shader = [=](uint32_t shader_type, std::string_view shader_type_str, std::string_view source) -> uint32_t {
        uint32_t shader = glCreateShader(shader_type);
        const char* source_ptr = source.data();
        glShaderSource(shader, 1, &source_ptr, nullptr);
        glCompileShader(shader);
        CheckCompilerErrors(shader, shader_type_str);
        return shader;
    };
    uint32_t vertex_shader = compile_shader(GL_VERTEX_SHADER, "VERTEX", vertex_source);
    uint32_t fragment_shader = compile_shader(GL_FRAGMENT_SHADER, "FRAGMENT", fragment_source);
    uint32_t geometry_shader = 0;
    if (!geometry_source.empty()) {
        geometry_shader = compile_shader(GL_GEOMETRY_SHADER, "GEOMETRY", geometry_source);
    }
    id_ = glCreateProgram();
    glAttachShader(id_, vertex_shader);
    glAttachShader(id_, fragment_shader);
    if (!geometry_source.empty()) {
        glAttachShader(id_, geometry_shader);
    }
    glLinkProgram(id_);
    CheckCompilerErrors(id_, "PROGRAM");
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    if (!geometry_source.empty()) {
        glDeleteShader(geometry_shader);
    }
}

void Shader::SetFloat(const std::string& name, float value, bool use_shader)
{
    if (use_shader) {
        Use();
    }
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetInteger(const std::string& name, int32_t value, bool use_shader)
{
    if (use_shader) {
        Use();
    }
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetVector2f(const std::string& name, float x, float y, bool use_shader)
{
    if (use_shader) {
        Use();
    }
    glUniform2f(GetUniformLocation(name), x, y);
}

void Shader::SetVector2f(const std::string& name, const  glm::vec2& value, bool use_shader)
{
    if (use_shader) {
        Use();
    }
    glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetVector3f(const std::string& name, float x, float y, float z, bool use_shader)
{
    if (use_shader) {
        Use();
    }
    glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetVector3f(const std::string& name, const glm::vec3& value, bool use_shader)
{
    if (use_shader) {
        Use();
    }
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const std::string& name, float x, float y, float z, float w, bool use_shader)
{
    if (use_shader) {
        Use();
    }
    glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetVector4f(const std::string& name, const glm::vec4& value, bool use_shader)
{
    if (use_shader) {
        Use();
    }
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4f(const std::string& name, const glm::mat4& value, bool use_shader)
{
    if (use_shader) {
        Use();
    }
    glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(value));
}

int32_t Shader::GetUniformLocation(const std::string& name)
{
    auto it = location_cache_.find(name);
    if (it != location_cache_.end()) {
        return it->second;
    }
    int32_t location = glGetUniformLocation(id_, name.data());
    location_cache_[name] = location;
    return location;
}

void Shader::CheckCompilerErrors(uint32_t object, std::string_view type)
{
    int32_t success = 0;
    char info_log[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, nullptr, info_log);
            std::string error = std::string{"| ERROR::SHADER: Compile-time error: Type: "} + std::string{type} + std::string{"\n"} + std::string{info_log};
            throw std::runtime_error(error);
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, nullptr, info_log);
            std::string error = std::string{"| ERROR::SHADER: Link-time error: Type: "} + std::string{type} + std::string{"\n"} + std::string{info_log};
            throw std::runtime_error(error);
        }
    }
}