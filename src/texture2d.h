#pragma once

#include <stdint.h>
#include <vector>

class Texture2D
{
public:
    Texture2D(bool alpha = false);
    ~Texture2D();
    Texture2D(const Texture2D& other) = default;
    Texture2D& operator=(const Texture2D& other) = default;

public:
    void Generate(uint32_t width, uint32_t height, const std::vector<unsigned char>& data);
    void Generate(uint32_t width, uint32_t height, const unsigned char* data);
    void Bind() const;
    void Clear();

private:
    uint32_t id_;
    uint32_t width_;
    uint32_t height_;
    uint32_t internal_format_;
    uint32_t image_format_;
    uint32_t wrap_s_;
    uint32_t wrap_t_;
    uint32_t filter_min_;
    uint32_t filter_max_;
};