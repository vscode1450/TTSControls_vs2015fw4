//修改CButton类按钮背景颜色和文字颜色，自绘方法对按钮进行重新绘制。通过定义一个以CButton为基类的新按钮类来实现。
#include "stdafx.h"
#include "MyButton.h"


CMyButton::CMyButton()
{
	m_Style = 0;                //按钮形状风格
	b_InRect = false;           //鼠标进入标志
	m_strText = _T("");         //按钮文字（使用默认文字）
	m_ForeColor = RGB(255, 255 ,255);             //文字颜色（白色）
	m_BackColor = RGB(40, 116, 228);          //背景色（蓝色）
	m_LockForeColor = GetSysColor(COLOR_GRAYTEXT);     //锁定按钮的文字颜色
	p_Font = NULL;                        //字体指针
}


CMyButton::~CMyButton()
{
	if (p_Font)   delete p_Font;         //删除字体
}



BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void CMyButton::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	//就是为按钮设置属性为“自绘”式，这样，用户在添加按钮后，就不需设置“Owner draw”属性了。
	ModifyStyle(0, BS_OWNERDRAW);         //设置按钮属性为自画式
	CButton::PreSubclassWindow();
}

//按钮的绘制工作就在DrawItem进行，它的作用相当于对话框中的OnPaint()函数和视图中的OnDraw()函数。
void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	m_ButRect = lpDrawItemStruct->rcItem;     //获取按钮尺寸

	if (m_strText.IsEmpty())
		GetWindowText(m_strText);           //获取按钮文本

	int nSavedDC = pDC->SaveDC();
	VERIFY(pDC);
	DrawButton(pDC);                 //绘制按钮
	pDC->RestoreDC(nSavedDC);

}

//变量 m_Style 表当前按钮状态，它的取值为：0 - 正常，1 - 当前，2 - 按下，3 - 锁定。
//不同状态下按钮的边框颜色和文字颜色有所不同。m_Style 的值在鼠标响应函数中进行修改。
//绘制工作主要利用CDC类的绘图函数完成，主要注意在 m_Style 不同取值下表现出来的差别。

void CMyButton::DrawButton(CDC *pDC)
{
	//调整状态
	if (m_Style == 3) m_Style = 0;
	if (GetStyle() & WS_DISABLED)
		m_Style = 3;     //禁止状态
						 //根据状态调整边框颜色和文字颜色
	COLORREF bColor, fColor;     //bColor为边框颜色，fColor为文字颜色
	switch (m_Style)
	{
	case 0: bColor = RGB(192, 192, 192); fColor = m_ForeColor; break;   //正常按钮
	case 1: bColor = RGB(255, 255, 255); fColor = m_ForeColor; break;   //鼠标进入时按钮
	case 2: bColor = RGB(192, 192, 192); fColor = m_ForeColor; break;   //按下的按钮
	case 3: bColor = m_BackColor; fColor = m_LockForeColor; break;    //锁定的按钮
	}
	//绘制按钮背景
	CBrush Brush;
	Brush.CreateSolidBrush(m_BackColor);     //建立背景刷
	pDC->SelectObject(&Brush);// 选入设备环境
	CPen Pen;
	Pen.CreatePen(PS_SOLID, 1, bColor);
	pDC->SelectObject(&Pen);
	pDC->RoundRect(&m_ButRect, CPoint(5, 5));    //画圆角矩形
												 //绘制按钮按下时的边框
	if (m_Style != 2)
	{
		CRect Rect;
		Rect.SetRect(m_ButRect.left + 2, m_ButRect.top + 1, m_ButRect.right, m_ButRect.bottom);
		pDC->DrawEdge(&Rect, BDR_RAISEDINNER, BF_RECT);     //画边框
	}
	//绘制按钮文字
	pDC->SetTextColor(fColor);         //画文字
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(m_strText, &m_ButRect, DT_SINGLELINE | DT_CENTER
		| DT_VCENTER | DT_END_ELLIPSIS);
	//绘制拥有焦点按钮的虚线框
	if (GetFocus() == this)
	{
		CRect Rect;
		Rect.SetRect(m_ButRect.left + 2, m_ButRect.top + 1, m_ButRect.right - 2, m_ButRect.bottom - 1);
		pDC->DrawFocusRect(&Rect);     //画拥有焦点的虚线框
	}
}

//用于判定当前鼠标指针是否在按钮上。b_InRect是个标志，为true表示鼠标指针进入了按钮区域，此时要捕获鼠标，让鼠标命令传送给按钮。当鼠标指针离开按钮时，要清除b_InRect标志，并且释放捕获的鼠标，让其它窗口可以接收鼠标命令。
//Invalidate()函数用于更新按钮，它会自动调用DrawItem()函数重新绘制按钮。
//设置条件的目的是仅在鼠标指针进入按钮和离开按钮时更新按钮，这样可以防止鼠标在按钮上移动时发生闪烁。

void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!b_InRect || GetCapture() != this)     //鼠标进入按钮
	{
		b_InRect = true;     //设置进入标志
		SetCapture();        //捕获鼠标
		m_Style = 1;         //设置按钮状态
		Invalidate();        //重绘按钮
	}
	else
	{
		if (!m_ButRect.PtInRect(point))     //鼠标离开按钮
		{
			b_InRect = false;    //清除进入标志
			ReleaseCapture();    //释放捕获的鼠标
			m_Style = 0;         //设置按钮状态
			Invalidate();        //重绘按钮
		}
	}

	CButton::OnMouseMove(nFlags, point);
}

//单击鼠标左键时的消息函数。这里只是重新绘制按钮，具体的单击响应应该在拥有按钮的对话框或视图中进行。
void CMyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Style = 2;
	Invalidate();         //重绘按钮
	CButton::OnLButtonDown(nFlags, point);
}

//单击鼠标左键后弹起时的消息函数。这里也只是重绘按钮，这样能使按钮在按下和弹起时有所不同，使按钮看上去有动态效果。
void CMyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Style = 1;
	Invalidate();         //重绘按钮
	CButton::OnLButtonUp(nFlags, point);
}

//设置按钮文本
void CMyButton::SetText(CString str)
{
	m_strText = _T(str);
	SetWindowText(str);

}

//设置文本颜色
void CMyButton::SetForeColor(COLORREF color)
{
	m_ForeColor = color;
	Invalidate();
}

//设置背景颜色
void CMyButton::SetBkColor(COLORREF color)
{
	m_BackColor = color;
	Invalidate();
}

//设置字体(字体高度、字体名)
void CMyButton::SetTextFont(int FontHight, LPCTSTR FontName)
{
	if (p_Font)  delete p_Font;     //删除旧字体
	p_Font = new CFont;  //生成字体对象
	p_Font->CreatePointFont(FontHight, FontName);     //创建新字体
	SetFont(p_Font);                 //设置字体
}
