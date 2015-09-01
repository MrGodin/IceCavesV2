
#include "Animation.h"

StaticAnimation::StaticAnimation(AnimationDesc& desc)
	:
	Desc(desc),
	timer( desc.life_span / (float)desc.frames)
{
	createClipRects();
	
	
}
//====================================================================
void StaticAnimation::SetStartEndFrame(UINT start, UINT end, float lifespan)
{
	assert(start >= 0);
	assert(end < Desc.frames);
	Desc.index = Desc.startFrame = start;
	Desc.endFrame = end;
	UINT newFrameCount = end - start;
	Desc.life_span = lifespan;
	timer.Set(Desc.life_span / (float)newFrameCount);
	fElapsedtime = 0.0f;
}
//==========================================================================
// destroy when returning false
bool StaticAnimation::Update(float& dt)
{
	fElapsedtime += dt;
	if (Desc.do_animate)
	{
		if (timer.Update(dt))
		{
			if (!Desc.keep_alive)
				Desc.index < Desc.endFrame  ? Desc.index++ : Desc.index = Desc.endFrame ;
			else
				Desc.index < Desc.endFrame ? Desc.index++ : Desc.index = Desc.startFrame;
		}
		if (!Desc.keep_alive)
			return fElapsedtime < Desc.life_span;
	}
	return true;
}
//======================================================================
void StaticAnimation::createClipRects()
{
	float2 pos = Desc.clip_startpos;
	pos.x += (float)Desc.clipOffsetW;
	pos.y += (float)Desc.clipOffsetH;
	float w = pos.x + Desc.clipWidth - (float)Desc.clipOffsetW;
	float h = pos.y + Desc.clipHeight - (float)Desc.clipOffsetH;

	for (UINT c = 0; c < Desc.frames; c++)
	{
		D2D1_RECT_F r = D2D1::RectF(pos.x , pos.y, w, h);
		clipRect.push_back(r);
		pos.x += Desc.clipWidth;
		w = pos.x + Desc.clipWidth - (float)Desc.clipOffsetW;
	}
}
//==========================================================================
///////////////////////////////////////////////////////////
StaticAnimation::Drawable::Drawable(StaticAnimation& p)
	:
	parent(p)
{
	matRot = Mat3x2Math::Rotate(parent.Desc.angle, parent.Desc.center);
}
void StaticAnimation::Drawable::Rasterize(GrafixD2& gfx)
{
	
	matWorld = matRot * matTrans;
	matWorld = matViewPort * matWorld;
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

/////////////////////////////////////////////////////

MoveableAnimation::MoveableAnimation(AnimationDesc& desc)
	:
	StaticAnimation(desc)
{

}
bool MoveableAnimation::Update(float& dt)
{
	fElapsedtime += dt;
	if (Desc.do_animate)
	{
		if (timer.Update(dt))
		{
			if (!Desc.keep_alive)
				Desc.index < Desc.endFrame ? Desc.index++ : Desc.index = Desc.endFrame;
			else
				Desc.index < Desc.endFrame ? Desc.index++ : Desc.index = Desc.startFrame;
		}
		if (!Desc.keep_alive)
			return fElapsedtime < Desc.life_span;
	}
	return true;
}

void MoveableAnimation::SetPos(float2& pos)
{
	Desc.drawPos = D2D1::RectF(pos.x, pos.y, pos.x + Desc.drawWidth + Desc.clipOffsetW, pos.y + Desc.drawHeight + Desc.clipOffsetH);
	Desc.center = float2(pos.x + Desc.drawWidth / 2, pos.y + Desc.drawHeight / 2);
	Desc.pos = pos;
};