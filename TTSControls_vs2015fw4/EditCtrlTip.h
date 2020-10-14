/*|*\
|*|  File:      EditCtrlTip.h
|*|  By:        wjf  20191021
|*|Prompt暗淡的 注意:这是“调光编辑控件”的实现。
\*|*/
#if !defined(AFX_DIMEDITCTRL_H__CF8D88FB_6945_11D4_8AC4_00C04F6092F9__INCLUDED_)
#define AFX_DIMEDITCTRL_H__CF8D88FB_6945_11D4_8AC4_00C04F6092F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// EditCtrlTip.h : header file
//  This Specifies The Length Of The Prompt Text Buffer...

static  const   int     DIM_TEXT_LEN = 128;                // Prompt Text Buffer Length

/////////////////////////////////////////////////////////////////////////////
// CEditCtrlTip window

class CEditCtrlTip : public CEdit
{
	// Construction
public:
	/**/
	CEditCtrlTip();                                 // Constructor

	// Attributes
public:

	// Operations
public:

	void    SetShowDimControl(bool bShow);                // Show Or Hide The Prompt Control
	void    SetDimText(LPCTSTR cpText);                   // Set The Prompt Text
	void    SetDimColor(COLORREF crDColor);               // Set The Prompt Color
	void    SetDimOffset(char cRedOS, char cGreenOS,
		char cBlueOS);                                     // Set The Prompt Color Offset

// Overrides
// ClassWizard generated virtual function overrides
//{{AFX_VIRTUAL(CEditCtrlTip)
public:
	//virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CEditCtrlTip();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditCtrlTip)
	afx_msg void OnChange();
	afx_msg void OnSetfocus();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnKillfocus();
	//}}AFX_MSG
	//  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

	void        DrawDimText(void);                        // Draw The Prompt Text

	COLORREF    m_crDimTextColor;                           // "Hard" Prompt Text Color
	TCHAR       m_caDimText[DIM_TEXT_LEN + 1];            // Prompt Text Buffer
	bool        m_bShowDimText;                             // Are We Showing The Prompt Text?
	bool        m_bUseDimOffset;                            // Are We Using The Offset Colors (Not Hard Color)?
	char        m_cRedOS;                                   // Red Color Prompt Offset
	char        m_cGreenOS;                                 // Green Color Prompt Offset
	char        m_cBlueOS;                                  // Blue Color Prompt Offset
	int         m_iDimTextLen;                              // Length Of Prompt Text
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIMEDITCTRL_H__CF8D88FB_6945_11D4_8AC4_00C04F6092F9__INCLUDED_)
