#pragma once
#include "Camera.h"
#include "../Math/Ray.h"
#include "../Objects/Object.h"
#include "../Objects/Scene.h"
#include "Canvas.h"
#include <SDL.h>
class Renderer
{
public:
	Renderer() = default;
	void Render(Canvas& canvas, Scene& scene, Camera& camera);

	bool Initialize();
	void Shutdown();

	bool CreateWindow(int width, int height);

	void CopyCanvas(const Canvas& canvas);
	void Present();

	friend class Canvas;
	
private:
	color3 GetBackgroundFromRay(const Ray& ray);

private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
};