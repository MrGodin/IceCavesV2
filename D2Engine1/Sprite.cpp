#include "Sprite.h"
#include "UtilsD2.h"
#include "StateCores.h"

//Sprite::Sprite()
//	:
//CollidableObject(),
//animation(Desc.animateDesc)
//{
//	
//}


Sprite::~Sprite()
{
	
}

void Sprite::SetProperties(float DpiX, float DpiY, D2D1_PIXEL_FORMAT PixFormat)
{
	Desc.animateDesc.bp.dpiX = DpiX;
	Desc.animateDesc.bp.dpiY = DpiY;
	Desc.animateDesc.bp.pixelFormat = PixFormat;
	
	
}

void Sprite::SetInterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE InterpMode)
{
	Desc.animateDesc.interpMode = InterpMode;
}

/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
Sprite::Collide::Collide(Sprite& p)
	:
	parent(p)
{

};
bool Sprite::Collide::SphericalCollision(CollidableObject& obj)
{
	if (obj.GetAABB().OverLaps(parent.GetAABB()))
	{
		if (Collision::HandleSphericalObjectCollision(parent, obj))
		{
			
			return true;
		};
	}
	return false;

}
void Sprite::Collide::MapCollision()
{
	Collision::HandleMapCollision(parent);
	Collision::DoSupport(parent);
}