#pragma once
#include "../Math/Color.h"
#include <SDL.h>
#include <vector>

class Renderer;

class Canvas
{
public:
    Canvas(int width, int height, const Renderer& renderer);
    ~Canvas();

    void Update();
    void Draw(const Renderer& renderer);

    void Clear(const color4& color);
    void DrawPoint(const glm::ivec2& point, const color4& color);

    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }

    friend class Renderer;

private:
    SDL_Texture* m_texture{ nullptr };
    std::vector<rgba_t> m_buffer;

    int m_width = 0;
    int m_height = 0;
};