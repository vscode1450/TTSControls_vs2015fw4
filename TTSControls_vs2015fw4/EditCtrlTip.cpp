/*
|*|  File:      CEditCtrlTip.cpp
*/

#include "stdafx.h"
#include "resource.h"
#include "TTSControls_vs2015fw4.h"
#include "EditCtrlTip.h"


#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditCtrlTip

CEditCtrlTip::CEditCtrlTip() :
	m_bShowDimText(true),                                       // Set The Prompt Flag
	//  m_cRedOS( -0x40 ),                                      // Set The Default Prompt Offset Colors
	//  m_cGreenOS( -0x40 ),                                    // Set The Default Prompt Offset Colors
	//  m_cBlueOS( -0x40 ),                                     // Set The Default Prompt Offset Colors
	//  m_bUseDimOffset( true ),                                // Use The Offset Colors
	m_iDimTextLen(0),                                     // No Prompt Text Set Yet
	m_crDimTextColor(RGB(0x00, 0x00, 0x00))              // No "Hard" Prompt Text Color
{
	m_caDimText[0] = _T('\0');                          // Terminate The Buffer
	SetDimOffset(-0x40, -0x40, -0x40);                    // Set The Prompt Offset

	return;                                                 // Done!
}


CEditCtrlTip::~CEditCtrlTip()
{
	return;                                                 // Done!
}


BEGIN_MESSAGE_MAP(CEditCtrlTip, CEdit)
	//{{AFX_MSG_MAP(CEditCtrlTip)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnSetfocus)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SETTINGCHANGE()
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillfocus)
	//}}AFX_MSG_MAP
	//  ON_WM_LBUTTONDOWN()
	//  ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditCtrlTip message handlers

void    CEditCtrlTip::PreSubclassWindow()
{
	CEdit::PreSubclassWindow();                             // Do Default...

	SetShowDimControl(true);                                // Default To Show The Prompt Control

	return;                                                 // 
}


void    CEditCtrlTip::SetDimText(LPCTSTR cpDimText)
{
	if (cpDimText)                                         // If Prompt Text Specified
	{
		_tcsncpy(m_caDimText, cpDimText, DIM_TEXT_LEN);   // Copy Over The Text
		m_caDimText[DIM_TEXT_LEN] = _T('\0');           // Enforce Termination (I Am Paranoid, I Know!)
		m_iDimTextLen = _tcslen(m_caDimText);             // Store Length Of The Prompt Text
	}
	else                                                    // If No Prompt Text
	{
		m_caDimText[0] = _T('\0');                      // Just Terminate The Buffer (No Text)
		m_iDimTextLen = 0;                                  // No Prompt Text
	}
	if (m_bShowDimText)                                    // If Showing Any Prompt Text
	{
		DrawDimText();                                      // Draw The Prompt Text
	}
	return;                                                 // Done!
}


void CEditCtrlTip::SetShowDimControl(bool bShow)
{
	m_bShowDimText = bShow;                                 // Set The Prompt Flag
	if (bShow)                                             // If Showing Any Prompt Text
	{
		DrawDimText();                                      // Draw The Prompt Text
	}
	return;                                                 // Done!
}

//复合控件中只读
//BOOL    CEditCtrlTip::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
//	DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,
//	CCreateContext* pContext)
//{
//	BOOL    bCreated = CWnd::Create(lpszClassName,
//		lpszWindowName, dwStyle, rect,
//		pParentWnd, nID, pContext);                        // Try To Create Ourselves...
//
//	if (bCreated)                                          // If We Got Created
//	{
//		SetShowDimControl(true);                          // Show The Prompt Control
//	}
//	return(bCreated);                                     // Return Creation Status
//}


void CEditCtrlTip::OnChange()
{
	int iLen = GetWindowTextLength();                     // Get Control's Text Length

	if (!iLen)                                             // If No Text
	{
		SetShowDimControl(true);                          // Show The Prompt Text
	}
	else                                                    // If Text Now In The Control
	{
		SetShowDimControl(false);                         // Disable The Prompt Text
	}
	return;                                                 // Done!
}


void CEditCtrlTip::OnSetfocus()
{
	if (m_bShowDimText)                                    // If Showing Any Prompt Text
	{
		DrawDimText();                                      // Draw The Prompt Text
	}
	return;                                                 // Done!
}


void    CEditCtrlTip::OnPaint()
{
	Default();                                              // Do Default Control Drawing

	if (m_bShowDimText)                                    // If Showing Any Prompt Text
	{
		DrawDimText();                                      // Draw The Prompt Text
	}
	return;                                                 // Done!
}


void CEditCtrlTip::DrawDimText(void)
{
	if (!m_iDimTextLen)                                    // If No Prompt Text
	{
		return;                                             // Stop Here
	}
	CClientDC   dcDraw(this);
	CRect       rRect;
	int         iState = dcDraw.SaveDC();                   // Save The DC State

	GetClientRect(&rRect);                                // Get Drawing Area
	rRect.OffsetRect(1, 1);                               // Add Sanity Space

	dcDraw.SelectObject((*GetFont()));                    // Use The Control's Current Font
	dcDraw.SetTextColor(m_crDimTextColor);                // Set The Text Color
	dcDraw.SetBkColor(GetSysColor(COLOR_WINDOW));         // Set The Bk Color
	dcDraw.DrawText(m_caDimText, m_iDimTextLen, &rRect,
		(DT_CENTER | DT_VCENTER));                       // Draw The Prompt Text

	dcDraw.RestoreDC(iState);                             // Restore The DC State

	return;                                                 // Done!
}


BOOL CEditCtrlTip::OnEraseBkgnd(CDC* pDC)
{
	BOOL    bStatus = CEdit::OnEraseBkgnd(pDC);
	if ((bStatus) && (m_bShowDimText))                 // If All Good, And Showing Any Prompt Text
	{
		DrawDimText();                                      // Draw The Prompt Text
	}
	return(bStatus);                                      // Return Erase Status
}

/*
void CEditCtrlTip::OnLButtonDown(UINT nFlags, CPoint point)
{
	TRACE( _T( "Click...\n" ) );
	CEdit::OnLButtonDown(nFlags, point);
}

void CEditCtrlTip::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	TRACE( _T( "DClick...\n" ) );
	CEdit::OnLButtonDblClk(nFlags, point);
}
*/

void CEditCtrlTip::SetDimOffset(char cRedOS, char cGreenOS, char cBlueOS)
{
	COLORREF    crWindow = GetSysColor(COLOR_WINDOW);
	BYTE        btRedOS = (GetRValue(crWindow) + cRedOS);
	BYTE        btGreenOS = (GetGValue(crWindow) + cGreenOS);
	BYTE        btBlueOS = (GetBValue(crWindow) + cBlueOS);

	m_bUseDimOffset = true;                                 // Set The Flag
	m_cRedOS = cRedOS;                                      // Store Red Offset
	m_cGreenOS = cGreenOS;                                  // Store Green Offset
	m_cBlueOS = cBlueOS;                                    // Store Blue Offset
	m_crDimTextColor = RGB((BYTE)btRedOS, (BYTE)btGreenOS,
		(BYTE)btBlueOS);                               // Build The New Prompt Color
	return;                                                 // Done!
}


void CEditCtrlTip::SetDimColor(COLORREF crColor)
{
	m_bUseDimOffset = false;                                // Unset The Flag
	m_crDimTextColor = crColor;                             // Set The New Prompt Color
	m_cRedOS = m_cGreenOS = m_cBlueOS = 0;                  // No Offset

	return;                                                 // Done!
}


void CEditCtrlTip::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CEdit::OnSettingChange(uFlags, lpszSection);

	if (m_bUseDimOffset)                                   // If Using An Offset For The Prompt Color
	{
		COLORREF    crWindow = GetSysColor(COLOR_WINDOW);

		m_crDimTextColor = RGB(GetRValue(crWindow) +
			m_cRedOS, GetGValue(crWindow) +
			m_cGreenOS, GetBValue(crWindow) +
			m_cBlueOS);                                        // Rebuild The Prompt Color
	}
	return;                                                 // Done!
}

void CEditCtrlTip::OnKillfocus()
{
	int iLen = GetWindowTextLength();                   // Get Control's Text Length
	if (!iLen)                                             // If No Text
	{
		SetShowDimControl(true);                          // Show The Prompt Text
	}
	else                                                    // If Text Now In The Control
	{
		SetShowDimControl(false);                         // Disable The Prompt Text
	}
	return;
}