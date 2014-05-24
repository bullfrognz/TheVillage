//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name   :   D10Text.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __D10Text_H__
#define __D10Text_H__


// Library Includes
#include <D3DX10.h>


// Local Includes
#include "Framework\Text.h"


// Types


// Constants


// Prototypes
class CD10Renderer;


class CD10Text : public IText
{

	// Member Functions
public:


			 CD10Text();
	virtual ~CD10Text();


	bool Initialise(CD10Renderer& _rD10Renderer, const TDesc& _ktrDexription);


	virtual bool Draw();


	virtual void SetText(const char* _kcpText);


	// Inline Functions
	virtual inline void SetSize(uint _uiSize);
	virtual inline void SetColour(float _fRed, float _fGreen, float _fBlue);
	virtual inline void SetTransparency(float _fLevel);
	virtual inline void SetPosition(int _iX, int _iY);
	virtual inline void SetPositionX(int _iX);
	virtual inline void SetPositionY(int _iY);


protected:


	bool CompileFontDesc(const TDesc& _ktrDexription, D3DX10_FONT_DESC& _trFontDesc) const;


private:


	void Deinitialise();


	CD10Text(const CD10Text& _krD10Text);
	CD10Text& operator = (const CD10Text& _krD10Text);


	// Member Variables
protected:


private:


	D3DXCOLOR m_tColour;
	RECT m_tContainer;


	uint m_uiFontSize;


	ID3DX10Font* m_pD10Text;
	wchar_t* m_wcpText;


};


#include "D10Text.inl"


#endif //__D10Text_H__