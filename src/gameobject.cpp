#include "gameobject.h"

GameObject::GameObject()
    : position_{0.0f, 0.0f}, size_{1.0f, 1.0f}, velocity_{0.0f},
        color_{1.0f}, rotation_{0.0f}, sprite_{}, is_solid_{false}, destroyed_{}
{

}

GameObject::GameObject(const glm::vec2& pos, const glm::vec2& size, const Texture2D& sprite, const glm::vec3& color, const glm::vec2& velocity, bool is_solid)
    : position_{pos}, size_{size}, velocity_{velocity},
        color_{color}, rotation_{0.0f}, sprite_{sprite}, is_solid_{is_solid}, destroyed_{}
{

}

GameObject::~GameObject()
{

}

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(sprite_, position_, size_, rotation_, color_);
}

bool GameObject::IsDestroyed() const
{
    return destroyed_;
}

bool GameObject::IsSolid() const
{
    return is_solid_;
}

glm::vec2 GameObject::GetPosistion() const
{
    return position_;
}

void GameObject::ChangePosisiton(float add_x, float add_y)
{
    position_.x += add_x;
    position_.y += add_y;
}

glm::vec2 GameObject::GetSize() const
{
    return size_;
}