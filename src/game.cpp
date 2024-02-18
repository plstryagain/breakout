#include "game.h"

Game::Game(uint32_t width, uint32_t height)
    : width_{width}, height_{height}, state_{GameState::GAME_ACTIVE}, keys_{}
{

}

Game::~Game()
{

}

void Game::Init()
{

}

void Game::ProcessInput(float delta_time)
{

}

void Game::Update(float delta_time)
{

}

void Game::Render()
{

}

void Game::SetKey(int32_t key, bool value)
{
    keys_[key] = value;
}