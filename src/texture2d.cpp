#include "texture2d.h"

#include <glad/glad.h>

Texture2D::Texture2D(bool alpha)
    : width_(0), height_(0), internal_format_(GL_RGB), image_format_(GL_RGB), wrap_s_(GL_REPEAT),
        wrap_t_(GL_REPEAT), filter_max_(GL_LINEAR), filter_min_(GL_LINEAR)
{
    if (alpha) {
        internal_format_ = GL_RGBA;
        image_format_ = GL_RGBA;
    }
    glGenTextures(1, &id_);
}

Texture2D::~Texture2D()
{

}

void Texture2D::Generate(uint32_t width, uint32_t height, const std::vector<unsigned char>& data)
{
    Generate(width, height, data.data());
}

void Texture2D::Generate(uint32_t width, uint32_t height, const unsigned char* data)
{
    width_ = width;
    height_ = height;

    glBindTexture(GL_TEXTURE_2D, id_);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format_, width_, height_, 0, image_format_, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min_);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture2D::Clear()
{
    if (id_ != 0) {
        glDeleteTextures(1, &id_);
        id_ = 0;
    }
}