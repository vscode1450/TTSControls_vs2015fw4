#pragma once
//GDI +
#include "Public.h"
#include <vector>
#include <atlimage.h>

using std::vector;

//重复定义
//typedef struct  tagITEMLIST
//{
//	//HICON		hIcon;		//图标
//	//CString		strUrl;		//Url地址
//	//COLORREF	clrLeft;	//左边文本的颜色
//	//UINT		iItem;		//ID 号
//	HICON hIcon;		//图标
//	CString strUrl;		//Url地址
//	CString strTitle;	//标题(Url官网名称)
//	COLORREF clrLeft;	//左边文本的颜色
//	COLORREF clrRight;	//右边文本的颜色
//	UINT     iItem;		//ID 号
//}ItemList, *PItemList;

#define DEF_FRAME_COLOR					RGB(40,138,228)
#define DEF_TEXT_COLOR					RGB(0,0,0)
#define DEF_BG_COLOR					RGB(210,210,210)
#define DEF_SELECT_COLOR				RGB(250,250,250)

//组合框类
class ComboBoxCtrltemp : public CComboBox
{
public:
	//构造函数
	ComboBoxCtrltemp();
	//析构函数
	virtual ~ComboBoxCtrltemp();

public:
	// 添加元素
	void AddNewString(CString leftText, UINT icon = NULL, COLORREF leftColor = DEF_TEXT_COLOR);
	// 设置尾部图标
	void SetEndIcon(UINT endIcon);
	// 设置颜色
	void SetComboColor(COLORREF crFrame = DEF_FRAME_COLOR, COLORREF crBgTitle = DEF_BG_COLOR, COLORREF crBgSelected = DEF_SELECT_COLOR, COLORREF crBgNoSelected = DEF_BG_COLOR);
	//设置字体大小及类型
	void SetFontType(int fontSize, CString fontType, BOOL bArtFont = FALSE, COLORREF crArtFont = DEF_FRAME_COLOR);
	//设置右侧点击按钮的图标
	void SetRightButton(UINT norImg, UINT clickImg);

protected:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchange();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(ComboBoxCtrltemp)
private:
	void	UpdateRect(void);
	void	OnNcPaint(CDC* pDC);
	void	DrawContent(UINT iState, CRect rcClient, CDC* pDC, int itemID);
	Image* ImageFromResource(HINSTANCE hInstance, UINT uImgID, LPCTSTR lpType); // GDI+ 否则报错  #include "gdiplus.h" #pragma comment( lib, "gdiplus.lib" )  
	//CImage* ImageFromResource(HINSTANCE hInstance, UINT uImgID, LPCTSTR lpType);
	void    DrawTextString(CDC* pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, LPRECT lpRect);
	void    DrawTextString(CDC* pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos);
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//member function
	void InitControl(void);

protected:
	BOOL				m_bOver;
	CBrush* m_pBrsh;
	CPen				m_bgPen;
	BOOL				m_bDown;
	CFont				m_font;
	int					m_selItem;	//select item flags
	BOOL				m_bFous;	//over fous
	int					m_preSelItem;	//pre select item flags
	UINT				m_endIcon;
	COLORREF			m_crFrame;
	COLORREF			m_crBgTitle;
	COLORREF			m_crBgSelected;
	COLORREF			m_crBgNoSelected;
	vector<ItemList*>	m_vecItemList;
	BOOL				m_bArtFont;
	COLORREF			m_crArtFont;
	Image* m_norImg;
	Image* m_clickImg;
	//CImage* m_norImg;
	//CImage* m_clickImg;

};