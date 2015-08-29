#pragma once
#include "Animation.h"
#include "Camera.h"
class StaticAnimationContainer
{
	std::vector<StaticAnimation*>animations;
	Camera& camera;
	ID2D1Bitmap* image = nullptr;
public:
	StaticAnimationContainer(Camera& cam);
	
	virtual ~StaticAnimationContainer()
	{
		std::for_each(animations.begin(), animations.end(), delete_ptr<StaticAnimation>);
	}
	virtual void Remove(UINT& index);
	void SetImage(ID2D1Bitmap* img) { image = img; }
	void Add(StaticAnimation::StaticAnimationDesc& desc);
	void Update(float& dt);
	void Rasterize();
};

