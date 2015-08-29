
#include "Animation.h"

StaticAnimation::StaticAnimation(StaticAnimationDesc& desc)
	:
	Desc(desc),
	timer( desc.life_span / (float)desc.frames)
{
	createClipRects();
}
// destroy when returning false
bool StaticAnimation::Update(float& dt)
{
	fElapsedtime += dt;
	if (timer.Update(dt))
		Desc.index < clipRect.size() - 1 ? Desc.index++ : Desc.index = clipRect.size() - 1;
	
	return fElapsedtime < Desc.life_span;
}
void StaticAnimation::createClipRects()
{
	float2 pos = Desc.clip_startpos;
	for (UINT c = 0; c < Desc.frames; c++)
	{
		D2D1_RECT_F r = D2D1::RectF(pos.x, pos.y, pos.x + Desc.clipWidth, pos.y + Desc.clipHeight);
		clipRect.push_back(r);
		pos.x += Desc.clipWidth;
	}
}
///////////////////////////////////////////////////////////
StaticAnimation::Drawable::Drawable(StaticAnimation& p)
	:
	parent(p)
{

}
void StaticAnimation::Drawable::Rasterize(GrafixD2& gfx)
{
	matWorld = matRot * matTrans;
	gfx.DrawSprite(
		matWorld,
		parent.Desc.drawPos,
		parent.Desc.bmp,
		parent.Desc.bp,
		parent.Desc.transparency,
		parent.Desc.interpMode,
		&parent.clipRect[parent.Desc.index]
		);
}
void StaticAnimation::Drawable::Translate(const float2& pos)
{
	matTrans = Mat3x2Math::Translate(pos);
}
void StaticAnimation::Drawable::Transform(D2D1::Matrix3x2F mat)
{
	matTrans = mat * matTrans;
}