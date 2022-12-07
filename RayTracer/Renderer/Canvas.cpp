#include "Canvas.h"
#include "Renderer.h"

Canvas::Canvas(int width, int height, const Renderer& renderer) :
	m_width { width },
	m_height { height }
{
	m_texture = SDL_CreateTexture(renderer.m_renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		width, height);

	m_buffer.resize(width* height);
}

Canvas::~Canvas()
{
	if (m_texture) SDL_DestroyTexture(m_texture);
}

void Canvas::Update()
{
	SDL_UpdateTexture(m_texture, nullptr, m_buffer.data(), m_width * sizeof(rgba_t));
}

void Canvas::Draw(const Renderer& renderer)
{
	SDL_RenderCopy(renderer.m_renderer, m_texture, nullptr, nullptr);
}

void Canvas::Clear(const color4& color)
{
	rgba_t rgba =ColorToRGBA(color);
	std::fill(m_buffer.begin(), m_buffer.end(), rgba);
}

void Canvas::DrawPoint(const glm::ivec2& point, const color4& color)
{
	if (point.x < 0 || point.x >= m_width || point.y < 0 || point.y >= m_height) return;
	m_buffer[point.x + (point.y * m_width)] = ColorToRGBA(color);
}
