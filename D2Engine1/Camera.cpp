
#include "Camera.h"
#include "TileMap.h"
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