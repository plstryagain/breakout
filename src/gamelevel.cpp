#include "gamelevel.h"
#include "resourcemanager.h"

#include <locale>
#include <stdint.h>
#include <string>
#include <fstream>
#include <sstream>

GameLevel::GameLevel()
{

}

GameLevel::~GameLevel()
{

}

void GameLevel::Load(const std::filesystem::path& file_path, uint32_t level_width, uint32_t level_height)
{
    bricks_.clear();
    uint32_t tile_code = 0;
    std::string line;
    std::ifstream fstream{file_path};
    std::vector<std::vector<TileCode>> tile_data;
    if (fstream) {
        while (std::getline(fstream, line)) {
            std::istringstream sstream{line};
            std::vector<TileCode> row;
            while (sstream >> tile_code) {
                row.push_back(static_cast<TileCode>(tile_code));
            }
            tile_data.push_back(std::move(row));
        }
        if (tile_data.size() > 0) {
            Init(tile_data, level_width, level_height);
        }
    }
}
void GameLevel::Draw(SpriteRenderer& renderer)
{
    for (auto& tile : bricks_) {
        if (!tile.IsDestroyed()) {
            tile.Draw(renderer);
        }
    }
}

bool GameLevel::IsCompleted()
{
    for (const auto& tile : bricks_) {
        if (!tile.IsDestroyed() && !tile.IsSolid()) {
            return false;
        }
    }
    return true;
}

void GameLevel::Init(const std::vector<std::vector<TileCode>>& tile_data, uint32_t level_width, uint32_t level_height)
{
    uint32_t height = static_cast<uint32_t>(tile_data.size());
    uint32_t width = static_cast<uint32_t>(tile_data.at(0).size());
    float unit_height = level_height / static_cast<float>(height);
    float unit_width = level_width / static_cast<float>(width);

    for (uint32_t y = 0; y < height; ++y) {
        for (uint32_t x = 0; x < width; ++x) {
            glm::vec2 pos{unit_width * x, unit_height * y};
            glm::vec2 size{unit_width, unit_height};
            bool is_solid = false;
            glm::vec3 color{1.0f};
            std::string texture_name = "brick";
            switch (tile_data[y][x]) {
            case TileCode::SOLID_BRICK:
                color = glm::vec3{0.8f, 0.8f, 0.7f};
                texture_name = "solid_brick";
                is_solid = true;
                break;
            case TileCode::BLUE_BRICK:
                color = glm::vec3{0.2f, 0.6f, 1.0f};
                break;
            case TileCode::GREEN_BRICK:
                color =  glm::vec3{0.0f, 0.7f, 0.0f};
                break;
            case TileCode::LIGHT_GREEN_BRICK:
                color = glm::vec3{0.8f, 0.8f, 0.4f};
                break;
            case TileCode::RED_BRICK:
                color = glm::vec3{1.0f, 0.5f, 0.0f};
                break;
            case TileCode::NO_BRICK:
                continue;
            }
            bricks_.emplace_back(pos, size, ResourceManager::getInstance().GetTexture2D(texture_name), color, glm::vec2{0.0f, 0.0f}, is_solid);
        }
    }
}