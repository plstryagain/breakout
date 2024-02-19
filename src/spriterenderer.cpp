#include "spriterenderer.h"
#include "glm/ext/matrix_transform.hpp"

#include <glad/glad.h>

SpriteRenderer::SpriteRenderer(const Shader& shader)
    : shader_(shader)
{
    InitRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &quad_vao_);
}

void SpriteRenderer::DrawSprite(const Texture2D& texture, glm::vec2 position,
                                glm::vec2 size, float rotate, glm::vec3 color)
{
    shader_.Use();
    glm::mat4 model = glm::mat4{1.0f};
    model = glm::translate(model, glm::vec3{position, 0.0f});

    model = glm::translate(model, glm::vec3{0.5f * size.x, 0.5f * size.y, 0.0f});
    model = glm::rotate(model, glm::radians(rotate), glm::vec3{0.0f, 0.0f, 1.0f});
    model = glm::translate(model, glm::vec3{-0.5f * size.x, -0.5f * size.y, 0.0f});

    model = glm::scale(model, glm::vec3{size, 1.0f});

    shader_.SetMatrix4f("model", model);
    shader_.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(quad_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::InitRenderData()
{
    uint32_t vbo;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &quad_vao_);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quad_vao_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}