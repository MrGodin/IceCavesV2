#pragma once
#include "Texture.h"
using namespace std;
#include "UtilsD2.h"


class Images
{
private:
	std::vector<Texture*>textures;
	ID2D1HwndRenderTarget *m_pRT = nullptr;
	void Flush(){ std::for_each(textures.begin(), textures.end(), delete_ptr<Texture>); }
	
public:
	Images(ID2D1HwndRenderTarget *pRt)
		:
		m_pRT(pRt)
	{

	}
	~Images()
	{
		Flush();
	}
	void AddTexture(const std::wstring &Basename,UINT clipSize)
	{
		textures.push_back(new Texture(m_pRT, Basename,clipSize));
	}
	Texture* GetTextureObj(UINT index)
	{
		assert(index < textures.size());
		return textures[index];
	}
	Texture* GetLast() { return textures[textures.size() -1]; }
	UINT Count() { return textures.size(); }
	ID2D1Bitmap* GetTexture(UINT index)
	{
		Assert(index < textures.size());
		return textures[index]->GetBmp();
	}
	void OnLostDevice()
	{
		Flush();
	}
};