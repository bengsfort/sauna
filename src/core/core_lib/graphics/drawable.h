#pragma once

namespace sauna_graphics
{

enum class DrawableType
{
	UI,
	Drawable2D,
	Drawable3D,
};

class Drawable
{
public:
	DrawableType drawType = DrawableType::UI;

	virtual ~Drawable() {}
	virtual void draw() = 0;
};

}; // namespace sauna_graphics
