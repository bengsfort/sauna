#pragma once

#include "raylib.h"

namespace sauna_graphics
{

const int DEFAULT_WINDOW_WIDTH = 1200;
const int DEFAULT_WINDOW_HEIGHT = 800;

class GraphicSystem
{
public:
	GraphicSystem();
	GraphicSystem(int winWidth, int winHeight);
	~GraphicSystem();

	inline void setWindowSize(int width, int height)
	{
		m_windowWidth = width;
		m_windowHeight = height;
		SetWindowSize(m_windowWidth, m_windowHeight);
	};

	inline Vector2 getWindowSize()
	{
		return {(float)m_windowWidth, (float)m_windowHeight};
	}

	void init(const char* windowTitle);
	void draw();
	void shutdown();

public:
	Color clearColor = BLACK;

protected:
	// TODO: Grab from stored settings when we have a settings system
	int m_windowHeight = DEFAULT_WINDOW_HEIGHT;
	int m_windowWidth = DEFAULT_WINDOW_WIDTH;

	// TODO: Array of Drawables (Or do we have the scene cache drawables, and have the API be "draw scene"?)
};

}; // namespace sauna_graphics

