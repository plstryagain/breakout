#include "game.h"

#include "resourcemanager.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <GLFW/glfw3.h>
#include <memory>

inline constexpr glm::vec2 PLAYER_SIZE{100.0f, 20.0f};
inline constexpr float PLAYER_VELOCITY{500.0f};

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
    ResourceManager::getInstance().LoadTexture2d("assets/textures/background.jpg", false, "background");
    ResourceManager::getInstance().LoadTexture2d("assets/textures/brick.png", false, "brick");
    ResourceManager::getInstance().LoadTexture2d("assets/textures/solid_brick.png", false, "solid_brick");
    ResourceManager::getInstance().LoadTexture2d("assets/textures/paddle.png", true, "paddle");

    std::vector<std::string> level_assets = {
        "assets/levels/1.txt",
        "assets/levels/2.txt",
        "assets/levels/3.txt",
        "assets/levels/4.txt",
    };
    for (size_t i = 0; i < level_assets.size(); ++i) {
        levels_.emplace_back();
        levels_.at(i).Load(level_assets.at(i), width_, height_ / 2);
    }
    level_ = 0;
    glm::vec2 player_pos{width_ / 2.0f - PLAYER_SIZE.x / 2.0f, height_ - PLAYER_SIZE.y};
    player_ = std::make_unique<GameObject>(player_pos, PLAYER_SIZE, ResourceManager::getInstance().GetTexture2D("paddle"));
}

void Game::ProcessInput(float delta_time)
{

}

void Game::Update(float delta_time)
{
    if (state_ == GameState::GAME_ACTIVE) {
        float velocity = PLAYER_VELOCITY * delta_time;
        if (keys_[GLFW_KEY_A]) {
            if (player_->GetPosistion().x >= 0.0f) {
                player_->ChangePosisiton(-1 * velocity, 0.0f);
            }
        }
        if (keys_[GLFW_KEY_D]) {
            if (player_->GetPosistion().x <= width_ - player_->GetSize().x) {
                player_->ChangePosisiton(velocity, 0.0f);
            }
        }
    }
}

void Game::Render()
{
    if (state_ == GameState::GAME_ACTIVE) {
        sprite_renderer_->DrawSprite(ResourceManager::getInstance().GetTexture2D("background"),
                                    glm::vec2{0.0f, 0.0f}, glm::vec2{width_, height_}, 0.0f);
        levels_.at(level_).Draw(*sprite_renderer_.get());
        player_->Draw(*sprite_renderer_.get());
    }
}

void Game::SetKey(int32_t key, bool value)
{
    keys_[key] = value;
}