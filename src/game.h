#pragma once

#include "spriterenderer.h"
#include "gamelevel.h"

#include <stdint.h>
#include <memory>
#include <vector>

enum class GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    Game(uint32_t width, uint32_t height);
    ~Game();

public:
    void Init();
    void ProcessInput(float delta_time);
    void Update(float delta_time);
    void Render();
    void SetKey(int32_t key, bool value);

private:
    uint32_t width_;
    uint32_t height_;
    GameState state_;
    bool keys_[1024];
    std::unique_ptr<SpriteRenderer> sprite_renderer_;
    std::vector<GameLevel> levels_;
    uint32_t level_;
    std::unique_ptr<GameObject> player_;
};