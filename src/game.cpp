#include "game.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "resourcemanager.h"

Game::Game(uint32_t width, uint32_t height)
    : width_{width}, height_{height}, state_{GameState::GAME_ACTIVE}, keys_{}
{

}

Game::~Game()
{

}

void Game::Init()
{
    Shader& sprite_shader = ResourceManager::getInstance().LoadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", "", "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width_), static_cast<float>(height_), 0.0f, -1.0f, 1.0f);
    sprite_shader.Use().SetInteger("image", 0);
    sprite_shader.Use().SetMatrix4f("projection", projection);
    sprite_renderer_ = std::make_unique<SpriteRenderer>(ResourceManager::getInstance().GetShader("sprite"));
    ResourceManager::getInstance().LoadTexture2d("assets/textures/awesomeface.png", true, "face");
}

void Game::ProcessInput(float delta_time)
{

}

void Game::Update(float delta_time)
{

}

void Game::Render()
{
    sprite_renderer_->DrawSprite(ResourceManager::getInstance().GetTexture2D("face"),
                                glm::vec2{200.0f, 200.0f}, glm::vec2{300.0f, 400.0f}, 45.0f,
                                glm::vec3{0.0f, 1.0f, 0.0f});
}

void Game::SetKey(int32_t key, bool value)
{
    keys_[key] = value;
}