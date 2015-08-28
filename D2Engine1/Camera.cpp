
#include "Camera.h"
#include "TileMap.h"

Camera::Camera(RenderTarget& next, float width, float height)
	:
	next(next),
	pos({ 0,0 }),
	center({ width / 2.0f,height / 2.0f }),
	screen_width(width),
	screen_height(height)
{

}
void Camera::Rasterize(Drawable& obj)
{
	obj.Transform(Mat3x2Math::Translate(-pos));
	next.Rasterize(obj);
};

float2 Camera::GetPos() { return pos; }
void Camera::ConfineToRect(RectF& b) { Box = b; };
void Camera::Resize(float& w, float& h)
{
	screen_width = w;
	screen_height = h;
	center = Vec2F(w / 2, h / 2);
	TileMap::SetDrawIndex(pos, w, h);
};

void Camera::UpdatePosition(float2 in_pos)
{
	pos = in_pos - center;
	pos.x = __max(pos.x, Box.left);
	pos.y = __max(pos.y, Box.top);
	pos.x = __min(pos.x, Box.right - screen_width);
	pos.y = __min(pos.y, Box.bottom - screen_height);
	TileMap::SetDrawIndex(pos, screen_width, screen_height);
}