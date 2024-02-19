#pragma once

#include "shader.h"
#include "texture2d.h"

class SpriteRenderer
{
public:
    SpriteRenderer(const Shader& shader);
    ~SpriteRenderer();
    SpriteRenderer(const SpriteRenderer& other) = delete;
    SpriteRenderer& operator=(const SpriteRenderer& other) = delete;

public:
    void DrawSprite(const Texture2D& texture, glm::vec2 position,
                    glm::vec2 size = glm::vec2{10.0f, 10.0f}, float rotate = 0.0f,
                    glm::vec3 color = glm::vec3{1.0f});

private:
    void InitRenderData();

private:
    Shader shader_;
    uint32_t quad_vao_;
};