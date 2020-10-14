// ComboBoxCtrlEx.cpp : 实现文件

#include "stdafx.h"
#include "resource.h"
#include "ComboBoxCtrlEx.h"

//对越界的检测if (size() <= _Pos)只会在 Debug 模式下进行，而且是可以通过
//#define _HAS_ITERATOR_DEBUGGING 0
//屏蔽掉这个检测的。
//而在 Release 模式下，根本不会进行这种检测。
//#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#define _HAS_ITERATOR_DEBUGGING 0
#define _SCL_SECURE_NO_WARNINGS

// CComboBoxCtrlEx
IMPLEMENT_DYNAMIC(CComboBoxCtrlEx, CComboBox)
BEGIN_MESSAGE_MAP(CComboBoxCtrlEx, CComboBox)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnCbnSelchange)
END_MESSAGE_MAP()

CComboBoxCtrlEx::CComboBoxCtrlEx()
{
	m_bOver = FALSE;
	m_pBrsh = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	m_bgBrush = new CBrush;
	m_bgBrush->CreateSolidBrush(RGB(141, 178, 227));//画刷恬蓝

	m_bgPen.CreatePen(PS_SOLID, 1, RGB(160, 31, 208));//画笔紫色
	m_font.CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("宋体"));
	m_bDown = FALSE;
	m_selItem = 666666666;
	m_preSelItem = 666666666;
	m_bFous = FALSE;
}

CComboBoxCtrlEx::~CComboBoxCtrlEx()
{
	if (m_bgPen.m_hObject != NULL)
	{
		m_bgPen.DeleteObject();
	}
	if (m_pBrsh->m_hObject != NULL)
	{
		m_pBrsh->DeleteObject();
	}
	if (m_bgBrush != NULL)
	{
		delete m_bgBrush;
	}
	if (m_bgBrush->m_hObject == NULL)
	{
		m_bgBrush->DeleteObject();
	}
	if (m_font.m_hObject != NULL)
	{
		m_font.DeleteObject();
	}

	for (IterItem iter = m_vecItemList.begin(); iter != m_vecItemList.end(); iter++)
	{
		if (*iter != NULL)
		{
			delete* iter;
		}
	}

	//for (auto* e : m_vecItemList)
	//{
	//	if (e != NULL) {
	//		delete e;
	//	}
	//}

}


// CComboBoxCtrlEx 消息处理程序

BOOL CComboBoxCtrlEx::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CComboBoxCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (lpDrawItemStruct->CtlType != ODT_COMBOBOX)
	{
		return;
	}
	if (GetCount() == 0)
	{
		return;
	}
	/*利用lpDrawItemStruct里面的itemID来获取其用AddString的ID号
	通过这个ID号, 我们可以获取到整个ItemList的结构.从而绘制相应的东西.*/

	UINT itemID = lpDrawItemStruct->itemID;
	CRect rcClient = lpDrawItemStruct->rcItem;
	UINT  iState = lpDrawItemStruct->itemState;

	CBitmap MemBit;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	DrawContent(iState, rcClient, pDC, itemID);

}

void CComboBoxCtrlEx::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bOver == FALSE)
	{
		m_bOver = TRUE;

		//更新当前区域
		UpdateRect();

		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = 0;
		tme.hwndTrack = m_hWnd;

		_TrackMouseEvent(&tme);
	}
	CComboBox::OnMouseMove(nFlags, point);
}
LRESULT CComboBoxCtrlEx::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if (m_bOver)
	{
		m_bOver = FALSE;
	}
	UpdateRect();

	return 1;
}

void CComboBoxCtrlEx::UpdateRect(void)
{
	CRect rcClient;
	GetWindowRect(&rcClient);
	rcClient.DeflateRect(-2, -2);
	GetParent()->ScreenToClient(&rcClient);
	GetParent()->InvalidateRect(&rcClient, FALSE);

	return;
}
//在DrawItem 事件中绘制项之前指定该项的大小。测量
void CComboBoxCtrlEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 30;
	lpMeasureItemStruct->itemWidth = 400;
}


//(初始化数据)到这个控件上，否则控件不显示
void CComboBoxCtrlEx::InitControl(void)
{
	//王建峰  插入数据AddString(_T("Google首页"));  不AddString,那么数据就加不进
	ItemList* pItem0 = new ItemList;
	pItem0->clrLeft = RGB(0, 132, 114);
	pItem0->clrRight = RGB(0, 255, 125);
	pItem0->hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	pItem0->strTitle = _T("张老师 盛唐软件");
	pItem0->strUrl = _T("http://www.qq.com");
	AddString(_T("先付款后消费")); //不AddString, 那么数据就加不进去
	pItem0->iItem = 1;
	//调用vector的push_back("aa")方法向vector中添加数据，该方法会自动申请内存，这样vector的size就可以逐步增加，不会越界。
	////push与push_back是STL中常见的方法，都是向数据结构中添加元素。
	m_vecItemList.push_back(pItem0);//push_back


	
    //Editstruct* pItem0 = new Editstruct;
	//pItem0->inclr = RGB(0, 132, 114);
	//pItem0->outclr = RGB(0, 255, 125);
	//pItem0->textclr = RGB(141, 178, 227);
	//pItem0->left_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	//pItem0->right_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	//pItem0->m_radian = 5;
	//pItem0->m_padding = 2;
	//m_EditCtrlImage.m_vecEditstruct.push_back(pItem0);
	////wjf

	//一定要加这一句
	//GetDlgItem(IDC_STATIC)->SetWindowText("your string");
	//GetDlgItem(IDC_STATIC)->GetParent()->RedrawWindow();
		//InvalidateRect(rc);
	// TODO: 在此添加控件通知处理程序代码


}

//边框可以通过重载OnNCPaint实现.  DrawContent和OnNcPaint中的绘制参数要相同，否则项目的高度不同
void CComboBoxCtrlEx::OnNcPaint(CDC* pDC)
{
	HICON hIcon;//当前图标句柄

	//绘制客户区
	CDC dMemDC;
	dMemDC.CreateCompatibleDC(pDC);
	dMemDC.SetMapMode(pDC->GetMapMode());

	//画动作
	CBitmap mNewBmp;
	CRect rc;
	GetClientRect(&rc);

	mNewBmp.CreateCompatibleBitmap(pDC, rc.right - rc.left, rc.bottom - rc.top);
	CBitmap* pOldBmp = dMemDC.SelectObject(&mNewBmp);

	CPen* pOldPen = dMemDC.SelectObject(&m_bgPen);
	CBrush* pOldBrsh = dMemDC.SelectObject(m_bgBrush);
	dMemDC.Rectangle(&rc);
	dMemDC.SelectObject(pOldPen);
	dMemDC.SelectObject(&pOldBrsh);

	//wjf
	//if ((GetCurSel() > 4) || (GetCurSel() < 0))
	//{
	//	return;
	//}

	if (m_vecItemList.empty())
	{
		return;
	}

	PItemList pItem = m_vecItemList[GetCurSel()];

	CPen	m_penLeft;
	CPen	m_penRight;
	CRect rcLeft, rcMid, rcRight;
	rcLeft = rcMid = rcRight = rc;
	dMemDC.SetBkMode(TRANSPARENT);

	//画第一段图标
	rcLeft.right = rcLeft.left + 16;
	rcLeft.left += 1;
	rcLeft.top += 4;
	::DrawIconEx(dMemDC.m_hDC, rcLeft.left, rcLeft.top, pItem->hIcon, 16, 16, NULL, NULL, DI_NORMAL);

	//画第二段文本
	rcMid.left = rcLeft.right + 10;
	rcMid.right = rc.right - 110;
	CFont* pOldFont = dMemDC.SelectObject(&m_font);
	dMemDC.SetTextColor(pItem->clrLeft);
	dMemDC.DrawText(pItem->strUrl, &rcMid, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

	//画第三段文本  //绘画字体
	rcRight.left = rcMid.right;
	dMemDC.SetTextColor(pItem->clrRight);
	dMemDC.DrawText(pItem->strTitle, &rcRight, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
	dMemDC.SelectObject(pOldFont);

	CRect rcEnd(rc);
	rcEnd.left = rc.right - 22;
	//rcEnd.top += 3;

	//DrawFrameControl 绘制的结果，仅是箭头
	if (m_bDown)
	{
		dMemDC.DrawFrameControl(&rcEnd, DFC_SCROLL, DFCS_SCROLLDOWN | DFCS_FLAT | DFCS_MONO | DFCS_PUSHED);
	}
	else
	{
		dMemDC.DrawFrameControl(&rcEnd, DFC_SCROLL, DFCS_SCROLLDOWN | DFCS_FLAT | DFCS_MONO);
	}
	//用函数BitBlt从后台设备环境中把曲线拷贝到SRCCOPY矩形区范围为（200，100，195，100）的当前设备环境中，最后再在曲线尾画上当前的数据点，如此循环。
	pDC->BitBlt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, &dMemDC,rc.left, rc.top, SRCCOPY);

	//恢复
	dMemDC.SelectObject(pOldBmp);
	pOldBmp->DeleteObject();
	dMemDC.DeleteDC();
}
void CComboBoxCtrlEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	OnNcPaint(&dc);
}

//DrawContent 呼叫框架，其在控制项的外观需要更新。
void CComboBoxCtrlEx::DrawContent(UINT iState, CRect rcClient, CDC* pDC, int itemID)
{
	//空行
	//wjf矢量容器 m_vecItemListw为空时报错！  wjf m_vecItemListw为空时报错！
	//m_vecItemList从0开始 itemID大1 
	if (m_vecItemList.size()  == itemID)
	{
		return;
	}

	if (GetCurSel() < 0)
	{
		return;
	}

	PItemList pItem = m_vecItemList[itemID];

	if (NULL == pItem)
	{
		return;
	}
	//pItem无法读取下句报错	if (pItem->strTitle.IsEmpty()) 

	CPen	m_penLeft;
	CPen	m_penRight;
	CRect rcLeft, rcMid, rcRight;
	rcLeft = rcMid = rcRight = rcClient;
	pDC->SetBkMode(TRANSPARENT);

	if (iState & ODS_SELECTED)
	{
		//及时更新选择区域
		UpdateRect();
	}

	if (itemID == m_selItem)
	{
		CPen bgPen;
		bgPen.CreatePen(PS_SOLID, 1, RGB(141, 178, 227));
		CPen* pOldPen = pDC->SelectObject(&bgPen);
		CBrush* pOldBrush = pDC->SelectObject(m_pBrsh);
		pDC->RoundRect(&rcClient, CPoint(5, 5));
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
		bgPen.DeleteObject();
	}

	//画第一段图标
	rcLeft.right = rcLeft.left + 16;
	rcLeft.left += 1;
	rcLeft.top += 4;
	::DrawIconEx(pDC->m_hDC, rcLeft.left, rcLeft.top, pItem->hIcon, 16, 16, NULL, NULL, DI_NORMAL);

	//画第二段文本
	rcMid.left = rcLeft.right + 10;
	rcMid.right = rcClient.right - 110;
	CFont* pOldFont = pDC->SelectObject(&m_font);
	pDC->SetTextColor(pItem->clrLeft);
	pDC->DrawText(pItem->strUrl, &rcMid, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

	//画第三段文本
	rcRight.left = rcMid.right + 8;
	pDC->SetTextColor(pItem->clrRight);
	pDC->DrawText(pItem->strTitle, &rcRight, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
	pDC->SelectObject(pOldFont);

	CRect rcEnd(rcClient);
	rcEnd.left = rcEnd.right - 22;
	//rcEnd.top += 3; //否则三角偏下

	if (itemID == m_selItem)
	{
		if (m_bFous)
		{
			DrawIconEx(pDC->m_hDC, rcEnd.left, rcEnd.top, AfxGetApp()->LoadIcon(IDI_ICON6), 16, 16, NULL, NULL, DI_NORMAL);
		}
		else
		{
			DrawIconEx(pDC->m_hDC, rcEnd.left, rcEnd.top, AfxGetApp()->LoadIcon(IDI_ICON7), 16, 16, NULL, NULL, DI_NORMAL);
		}

	}
}

void CComboBoxCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDown = TRUE;
	UpdateRect();
	CComboBox::OnLButtonDown(nFlags, point);
}

void CComboBoxCtrlEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDown = FALSE;
	UpdateRect();
	CComboBox::OnLButtonUp(nFlags, point);
}

void CComboBoxCtrlEx::OnCbnSelchange()
{
	//UpdateRect();
}

//该函数是一个应用程序定义的函数。它处理发送给窗口的消息。WNDPROC类型定义了一个指向该回调函数的指针。
//hwnd：指向窗口的句柄。WindowProc是你给自己的窗口定义的窗口处理函数 DefWindowProc是windows平台提供的默认窗口处理函数
//写在头文件 virtual LRESULT WindowProc(UINT nMessage, WPARAM wParam, LPARAM lParam)switch(nMessage){case WM_MOUSEMOVE:
LRESULT CComboBoxCtrlEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	//ComboBox下的EditBox和ListBox均会向ComboBox窗口发送WM_CTLCOLOR消息
	if (WM_CTLCOLORLISTBOX == message)
	{
		HWND hListBox = (HWND)lParam;

		CListBox* pListBox = (CListBox*)FromHandle(hListBox);
		ASSERT(pListBox);
		int nCount = pListBox->GetCount();

		if (CB_ERR != nCount)
		{
			CPoint pt;
			GetCursorPos(&pt);
			pListBox->ScreenToClient(&pt);

			CRect rc;
			for (int i = 0; i < nCount; i++)
			{
				pListBox->GetItemRect(i, &rc);
				if (rc.PtInRect(pt))
				{
					m_preSelItem = m_selItem;

					m_selItem = i;
					if (m_selItem != m_preSelItem)
					{
						CRect preRc;
						CRect rcFous(rc);
						rcFous.left = rcFous.right - 18;

						pListBox->GetItemRect(m_preSelItem, &preRc);
						pListBox->InvalidateRect(&preRc);

						if (rcFous.PtInRect(pt))
						{
							m_bFous = TRUE;
							pListBox->InvalidateRect(&rc);
						}
						else
						{
							m_bFous = FALSE;
							pListBox->InvalidateRect(&rc);
						}

					}

					break;
				}
			}
		}

	}
	return CComboBox::WindowProc(message, wParam, lParam);
}
