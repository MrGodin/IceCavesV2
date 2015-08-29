
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
	viewFrame.left   = pos.x;
	viewFrame.top    = pos.y;
	viewFrame.right  = viewFrame.left + screen_width;
	viewFrame.bottom = viewFrame.top + screen_height;
}
void Camera::Rasterize(Drawable& obj)
{
	
	obj.Transform(Mat3x2Math::Translate(-pos));
	next.Rasterize(obj);
};

float2 Camera::GetPos() { return pos; }
void Camera::ConfineToMap(RectF& map_frame) { mapFrame = map_frame; };
bool Camera::PointInViewFrame(float2 pt,const float2& offset)
{
	return pt.x > viewFrame.left + -offset.x && pt.x < viewFrame.right + offset.x &&
		   pt.y > viewFrame.top  + -offset.y && pt.y < viewFrame.bottom + offset.y;
}
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
	pos.x = __max(pos.x, mapFrame.left);
	pos.y = __max(pos.y, mapFrame.top);
	pos.x = __min(pos.x, mapFrame.right - screen_width);
	pos.y = __min(pos.y, mapFrame.bottom - screen_height);
	TileMap::SetDrawIndex(pos, screen_width, screen_height);
	viewFrame.left = pos.x;
	viewFrame.top = pos.y;
	viewFrame.right = viewFrame.left + screen_width;
	viewFrame.bottom = viewFrame.top + screen_height;
}