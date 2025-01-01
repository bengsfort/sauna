#pragma once

namespace sauna_graphics
{

enum class DrawableType
{
	Default,
	Drawable2D,
	Drawable3D,
};

class Drawable
{
public:
	DrawableType type = DrawableType::Default;

	virtual ~Drawable() {}
	virtual void draw() = 0;
};

}; // namespace sauna_graphics
