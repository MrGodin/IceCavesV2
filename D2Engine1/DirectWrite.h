#pragma once

#ifndef DWRITE_H_INCLUDED
#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")
#endif

class DirectWrite
{
public:
	DirectWrite();
	~DirectWrite();

	// Creates a format for all text you want to write in this style and font
	// The returned text format interface can get and set line spacing and 
	// paragraph alignment as well as word wrapping.
	IDWriteTextFormat *CreateFormat(LPWSTR FontName, float FontSize,
		DWRITE_FONT_WEIGHT FontWeight = DWRITE_FONT_WEIGHT_REGULAR, 
		DWRITE_FONT_STYLE FontStyle = DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH FontStretch = DWRITE_FONT_STRETCH_NORMAL,
		LPWSTR FontLocale = L"en-us");
private:
	IDWriteFactory *pFactory;
};

