#include "StaticAnimationContainer.h"

StaticAnimationContainer::StaticAnimationContainer(Camera& cam)
	:
	camera(cam)
{

}
StaticAnimation* StaticAnimationContainer::Add(StaticAnimation::AnimationDesc& desc)
{
	desc.bmp = image;
	animations.push_back(new StaticAnimation(desc));
	return animations[animations.size() - 1];
}
void StaticAnimationContainer::Remove(UINT& index)
{
	size_t size = animations.size();
	auto ptr1 = animations.begin() + index;
	std::for_each(ptr1, ptr1 + 1, delete_ptr<StaticAnimation>);
	animations.erase(ptr1);
	animations.resize(size - 1);
}
void StaticAnimationContainer::Update(float& dt)
{
	for (UINT c = 0; c < animations.size(); c++)
	{
		if(!animations[c]->Update(dt))
			Remove(c);
	}
}
void StaticAnimationContainer::Rasterize()
{
	for (UINT c = 0; c < animations.size(); c++)
	{
		camera.Rasterize(animations[c]->GetDrawable());
	}
}