#pragma once

#include "texture2d.h"
#include "spriterenderer.h"

class GameObject
{
public:
    GameObject();
    GameObject(const glm::vec2& pos, const glm::vec2& size, const Texture2D& sprite, const glm::vec3& color = glm::vec3{1.0f},
                const  glm::vec2& velocity = glm::vec2{0.0f, 0.0f}, bool is_solid = false);
    virtual ~GameObject();

public:
    virtual void Draw(SpriteRenderer& renderer);
    bool IsDestroyed() const;
    bool IsSolid() const;

private:
    float rotation_;
    bool is_solid_;
    bool destroyed_;
    Texture2D sprite_;
    glm::vec2 position_;
    glm::vec2 size_;
    glm::vec2 velocity_;
    glm::vec3 color_;
};