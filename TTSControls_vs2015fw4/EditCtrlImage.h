

#pragma once
//#include "Public.h"
//#include <atlimage.h>  
//virtual function 消息的处理.(主要是OnPaint和DrawItem) 打一个断点怎样触发这两个消息
//单击了按钮, 显示下拉的时候, 它才进DrawItem
//
#include "EditCtrlTip.h"
////////////////////////////////////////////////////////////////////////
#define TRANS_BACK RGB(255,0,0)
#define DEFAULT_COLOR RGB(40,138,228)

///////////////////////////////////////////////////////////////////////
class CEditCtrlImage :
	public CStatic
{
public:
	CEditCtrlImage();
	~CEditCtrlImage();

public:
	// 初始化,设置左右图标， 左侧图标，右侧图标，圆角，内距 
	void Init(BOOL leftright, HICON left_icon, HICON right_icon, int radian = 0, int padding = 0);
	// 设置内框、外框、字体颜色
	void setNormalColor(COLORREF inColor, COLORREF outColor, COLORREF textColor = RGB(0, 0, 0));
public:
	BOOL    m_bTracking;
	BOOL    m_bHover;

	//GDI + 主要使用Image类
	//Image* m_left_icon;  
	//Image* m_right_icon;

	HICON   m_left_icon;
	HICON   m_right_icon;
	int		m_radian = 3;
	int		m_padding = 2;
	BOOL    m_leftright = true;

	COLORREF m_normal_in_color;
	COLORREF m_normal_out_color;
	COLORREF m_default_color = RGB(255, 0, 0); //red
	COLORREF m_trans_back_color = RGB(40, 138, 228);//蓝色
	COLORREF m_text_color = RGB(0, 0, 0);//黑色
	//CEdit m_edit;
	CEditCtrlTip m_edit;

protected:
	//WM_NCPAINT当窗口客户区以外的部分（如窗口标题栏、菜单栏等）需要重画时，系统向程序发出该消息。
	//WM_PAINT应用程序通过处理该消息实现在窗口上的绘制工作。
	//WM_ERASEBKGND消息来重画背景

	void OnNcPaint();
	void OnPaint();
	//DEClARE_DYNCREATE / IMPLEMENT_DYNCREATE是为了“动态创建"类的实例而定义的宏。new可以用来创建对象，但不是动态的。
	//DECLARE_DYNAMIC(CEditCtrlImage)

	DECLARE_DYNAMIC(CEditCtrlImage)
	DECLARE_MESSAGE_MAP()
	//PreSubclassWindow是在CWnd::SubclassWindow中调用的，其目的是允许程序在动态子类化控件或窗口之前做一些其它所需要的动作
	virtual void PreSubclassWindow();
	//完成相关绘制
	//MFC CStatic控件在DrawItem中自绘
    //确保消息映射中不能有：ON_WM_PAINT（也可以直接在OnPaint中绘制）、ON_WM_DRAWITEM 消息，否则DrawItem函数不会被调用
    //注：第二步的是DrawItem而非OnDrawItem。OnDrawItem是ON_WM_DRAWITEM消息的处理函数，是处理子控件发送过来的自绘消息的

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void DrawBorder(CDC* dc, CRect& rc);
	//GDI + Image类调图 用CImage类，加头文件#include "atlimage.h"就可以了
	//Image* ImageFromResource(HINSTANCE hInstance, UINT uImgID, LPCTSTR lpType);
};

