// ListBoxCtrlEx.cpp : 实现文件

#include "stdafx.h"
#include "resource.h"
#include "TTSControls_vs2015fw4.h"
#include "ListBoxCtrlEx.h"


// CListBoxCtrlEx

IMPLEMENT_DYNAMIC(CListBoxCtrlEx, CListBox)

CListBoxCtrlEx::CListBoxCtrlEx()
{

}

CListBoxCtrlEx::~CListBoxCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListBoxCtrlEx, CListBox)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CListBoxCtrlEx 消息处理程序



void CListBoxCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (GetCount() == 0)
	{
		return;
	}
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	List_AppendData* pData = (List_AppendData*)GetItemDataPtr(lpDrawItemStruct->itemID);

	//获取列表数据
	CString str;
	GetText(lpDrawItemStruct->itemID, str);
	if (lpDrawItemStruct->itemAction | ODA_SELECT && lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		CBrush t_brush1;
		t_brush1.CreateSolidBrush(RGB(229, 239, 244));
		dc.FillRect(&lpDrawItemStruct->rcItem, &t_brush1);

	}
	else
	{
		CBrush t_brush1;
		t_brush1.CreateSolidBrush(RGB(255, 255, 255));
		dc.FillRect(&lpDrawItemStruct->rcItem, &t_brush1);
	}
	//画图标
	HICON t_hIcon;
	t_hIcon = LoadIcon(AfxGetInstanceHandle(), pData->hIcon);
	DrawIcon(dc.m_hDC, 10, lpDrawItemStruct->rcItem.top + 15, t_hIcon);
	//第一排字体
	HFONT t_hFont = CreateFont(12, 0, 0, 0, 600, 0, 0, 0, 1, 2, 1, 0, FF_MODERN, _T("宋体"));
	dc.SelectObject(t_hFont);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(46, 134, 208));
	dc.TextOut(60, lpDrawItemStruct->rcItem.top + 18, str, str.GetLength());
	//第二排字体
	HFONT t_hFont1 = CreateFont(12, 0, 0, 0, 400, 0, 0, 0, 1, 2, 1, 0, FF_MODERN, _T("宋体"));
	dc.SelectObject(t_hFont1);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(142, 142, 142));
	str = pData->strAppend;
	dc.TextOut(60, lpDrawItemStruct->rcItem.top + 37, str, str.GetLength());
	//底部边线
	CPen t_pen(PS_SOLID, 1, RGB(211, 218, 223));
	dc.SelectObject(t_pen);
	dc.MoveTo(0, lpDrawItemStruct->rcItem.bottom - 1);
	dc.LineTo(lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom - 1);



	dc.Detach(); //分离
}

void CListBoxCtrlEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{

	// TODO:  添加您的代码以确定指定项的大小
	lpMeasureItemStruct->itemHeight = 63;
}
void CListBoxCtrlEx::InsertStr(CString str, int iIndex, CString strAppend, LPTSTR icon)
{
	List_AppendData* pData = new List_AppendData;
	pData->hIcon = icon;
	pData->strAppend = strAppend;
	int i = SetItemDataPtr(InsertString(iIndex, str), pData);
}
void CListBoxCtrlEx::OnDestroy()
{
	CListBox::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	int iCount = GetCount();
	for (int i = 0; i < iCount; i++)
	{
		List_AppendData* pData = (List_AppendData*)GetItemDataPtr(i);
		delete pData;
		pData = NULL;
	}
}

BOOL CListBoxCtrlEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CListBox::OnEraseBkgnd(pDC);
}

void CListBoxCtrlEx::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListBox::OnMouseMove(nFlags, point);
}


//void CListBoxCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
//{
//	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
//	pDC->SetBkMode(TRANSPARENT);
//	RECT& rcItem = lpDrawItemStruct->rcItem;
//
//	CString cstrItemText;
//	CListBox::GetText(lpDrawItemStruct->itemID, cstrItemText);
//
//	LBDataXI* pData = (LBDataXI*)CListBox::GetItemDataPtr(lpDrawItemStruct->itemID);
//	if (NULL == pData)
//	{
//		return;
//	}
//
//	// 是否处于选中状态
//	BOOL bIsSelected = (lpDrawItemStruct->itemAction | ODA_SELECT)
//		&& (lpDrawItemStruct->itemState & ODS_SELECTED);
//
//	// 是否处于焦点状态
//	BOOL bIsFocused = (lpDrawItemStruct->itemAction | ODA_FOCUS)
//		&& (lpDrawItemStruct->itemState & ODS_FOCUS);
//
//	// 绘制背景
//	if (bIsSelected)
//	{
//		COLORREF oldColor = pDC->GetBkColor();
//		pDC->FillSolidRect(&rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
//		pDC->SetBkColor(oldColor);
//	}
//	else
//	{
//		pDC->FillSolidRect(&rcItem, pDC->GetBkColor());
//	}
//
//	// 绘制ICON
//	CRect rcIcon(rcItem.left, rcItem.top, rcItem.left, rcItem.top);
//	if (m_pImageList)
//	{
//		HICON hIcon = m_pImageList->ExtractIcon(pData->iImageIndex);
//		if (hIcon)
//		{
//			rcIcon.right = rcItem.left + m_imageSize.cx + 2 * LBXI_CX_BORDER;
//			rcIcon.bottom = rcItem.top + m_imageSize.cy + 2 * LBXI_CY_BORDER;
//
//			CPoint pos(rcIcon.left + LBXI_CX_BORDER, rcIcon.top + LBXI_CY_BORDER);
//			pDC->DrawState(pos, m_imageSize, hIcon, DSS_NORMAL, (CBrush*)NULL);
//			::DestroyIcon(hIcon);
//		}
//	}
//
//	// 绘制Text
//	if (bIsSelected)
//	{
//		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
//	}
//	else
//	{
//		pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
//	}
//	CRect rcText(rcItem);
//	rcText.left = rcIcon.right;
//	rcText.top = rcIcon.top;
//	pDC->DrawText(cstrItemText, rcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_WORDBREAK);
//}
//
//void CListBoxCtrlEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
//{
//	CDC* pDC = GetDC();
//	LPCTSTR lpszText = (LPCTSTR)lpMeasureItemStruct->itemData;
//	CSize szText = pDC->GetTextExtent(lpszText);
//	ReleaseDC(pDC);
//
//	lpMeasureItemStruct->itemHeight =
//		szText.cy > m_imageSize.cy + 2 * LBXI_CY_BORDER ? szText.cy : m_imageSize.cy + 2 * LBXI_CY_BORDER;
//}
//
