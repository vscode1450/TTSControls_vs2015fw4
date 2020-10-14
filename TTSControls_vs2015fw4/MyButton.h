#pragma once
#include "afxwin.h"
class CMyButton :
	public CButton
{
public:
	CMyButton();
	~CMyButton();

private:
	int          m_Style;     //按钮形状（0-正常，1-当前，2-按下，3-锁定）
	BOOL         b_InRect;            //鼠标进入标志
	CString      m_strText;           //按钮文字
	COLORREF     m_ForeColor;         //文本颜色
	COLORREF     m_BackColor;         //背景色
	COLORREF     m_LockForeColor;     //锁定按钮的文字颜色
	CRect        m_ButRect;           //按钮尺寸
	CFont*       p_Font;              //字体

	void   DrawButton(CDC *pDC);      //画正常的按钮

									  // 接口函数
public:
	void SetText(CString str);
	void SetForeColor(COLORREF color);       //设置文本颜色
	void SetBkColor(COLORREF color);         //设置背景颜色
	void SetTextFont(int FontHight, LPCTSTR FontName);    //设置字体 
	
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


