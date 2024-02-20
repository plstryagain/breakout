#pragma once

#include "gameobject.h"
#include "spriterenderer.h"

#include <filesystem>
#include <vector>

enum class TileCode : uint32_t
{
    NO_BRICK = 0,
    SOLID_BRICK,
    BLUE_BRICK,
    GREEN_BRICK,
    LIGHT_GREEN_BRICK,
    RED_BRICK
};

class GameLevel
{
public:
    GameLevel();
    ~GameLevel();

public:
    void Load(const std::filesystem::path& file_path, uint32_t level_width, uint32_t level_height);
    void Draw(SpriteRenderer& renderer);
    bool IsCompleted();

private:
    void Init(const std::vector<std::vector<TileCode>>& tile_data, uint32_t level_width, uint32_t level_height);

private:
    std::vector<GameObject> bricks_;
};