//
//  Bryce Booth


//  Auckland
//  New Zealand
//

//
//  File Name :   D10Text.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Framework\DirectX 10\D10Renderer.h"


// This Include
#include "D10Text.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10Text constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10Text::CD10Text()
: m_tColour(0.0f, 0.0f, 0.0f, 1.0f)
, m_uiFontSize(20)
, m_pD10Text(0)
, m_wcpText(0)
{
	ZeroMemory(&m_tContainer, sizeof(RECT));
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* CD10Text deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD10Text::~CD10Text()
{
	Deinitialise();
}





bool
CD10Text::Initialise(CD10Renderer& _rD10Renderer, const TDesc& _ktrDexription)
{
	bool bReturn = false;

	

	D3DX10_FONT_DESC tD10TextDesc;
	CompileFontDesc(_ktrDexription, tD10TextDesc);


	bReturn = _rD10Renderer.CreateFontIndirect(tD10TextDesc, m_pD10Text);


	return (bReturn);
}





bool
CD10Text::Draw()
{
	bool bReturn = false;


	HRESULT hResult = m_pD10Text->DrawText(0, m_wcpText, -1, &m_tContainer, DT_NOCLIP, m_tColour);


	if (FAILED(hResult))
	{
		// Failed to draw text
		bReturn = false;
		assert(false);
	}


	return (bReturn);
}





void
CD10Text::SetText(const char* _kcpText)
{
	FW_DELETE(m_wcpText);


	uint uiStringLength = strlen(_kcpText) + 1;
	
	
	m_wcpText = new wchar_t[uiStringLength];


	for (uint uiChar = 0; uiChar < uiStringLength; ++ uiChar)
	{
		m_wcpText[uiChar] = _kcpText[uiChar];
	}
}





/********************************
            Protected
*********************************/





bool
CD10Text::CompileFontDesc(const TDesc& _ktrDexription, D3DX10_FONT_DESC& _trFontDesc) const
{
	_trFontDesc.Height          = _ktrDexription.uiSize;
    _trFontDesc.Width           = 0;
	_trFontDesc.Weight          = _ktrDexription.uiWeight;
    _trFontDesc.MipLevels       = 1;
	_trFontDesc.Italic          = _ktrDexription.bItalic;
    _trFontDesc.CharSet         = DEFAULT_CHARSET;
    _trFontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
    _trFontDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;


	switch (_ktrDexription.eQuality)
	{
	case QUALITY_LOW:
		break;

	case QUALITY_HIGH:
		break;

	default:
		// Invalid quality
		assert(false);
		break;
	}


    wcscpy_s(_trFontDesc.FaceName, L"Times New Roman");


	return (true);
}






/********************************
            Private
*********************************/





void
CD10Text::Deinitialise()
{
	FW_RELEASE(m_pD10Text);
	FW_DELETE(m_wcpText);
}