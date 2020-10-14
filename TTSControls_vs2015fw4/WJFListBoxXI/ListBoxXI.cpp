/**********************************************************
 ListBoxXI.cpp : implementation file
 Written by WangYao (wangyao1052@163.com)
 Version: V1.0 2014-06-07

 //CListBoxXI m_listbox1;
 //CImageList m_imglist1;
 //DDX_Control(pDX, IDC_LIST1, m_listbox1);
 m_imglist1.Create(32, 32, ILC_COLOR32 | ILC_MASK, 2, 1);
 m_imglist1.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
 m_imglist1.Add(AfxGetApp()->LoadIcon(IDI_ICON2));

 m_listbox1.SetImageList(&m_imglist1);
 m_listbox1.AddString("456", 1);
 m_listbox1.AddString("123", 0);
 m_listbox1.AddString("hello kitty", 0);

**********************************************************/

#include "stdafx.h"
#include "ListBoxXI.h"

#define	LBXI_CX_BORDER   2
#define	LBXI_CY_BORDER   2

// CListBoxXI

IMPLEMENT_DYNAMIC(CListBoxXI, CListBox)

CListBoxXI::CListBoxXI()
{
	m_pImageList = NULL;
	m_imageSize.cx = 0;
	m_imageSize.cy = 0;
}

CListBoxXI::~CListBoxXI()
{
}

//---------------------------------------------------------
// 函数: SetImageList
// 功能: 设置关联的ImageList
// 参数: 
//       pImageList --- ImageList的指针
// 返回: 无
//---------------------------------------------------------
void CListBoxXI::SetImageList(CImageList* pImageList)
{
	m_pImageList = pImageList;
	if (m_pImageList)
	{
		int cx;
		int cy;
		ImageList_GetIconSize(*m_pImageList, &cx, &cy);
		m_imageSize.cx = cx;
		m_imageSize.cy = cy;
	}
	else
	{
		m_imageSize.cx = 0;
		m_imageSize.cy = 0;
	}

	Invalidate();
}

//---------------------------------------------------------
// 函数: GetImageList
// 功能: 获取关联ImageList的指针
// 参数: 无
// 返回: 关联ImageList的指针,若没有关联ImageList返回NULL
//---------------------------------------------------------
CImageList* CListBoxXI::GetImageList() const
{
	return m_pImageList;
}

//---------------------------------------------------------
// 函数: GetItemImage
// 功能: 获取项的图片索引
// 参数: 
//       nIndex  --- 项索引(以0为起点)
// 返回:
//       以0为起始的图片索引序号
//       若存在错误,如nIndex超出范围,返回-1
//       若项没有关联图片,返回-1
//---------------------------------------------------------
int CListBoxXI::GetItemImage(int nIndex)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return -1;
	}

	return pLBData->iImageIndex;
}

//---------------------------------------------------------
// 函数: SetItemImage
// 功能: 设置项的图片索引
// 参数: 
//       nIndex      --- 项索引(以0为起点)
//       nImageIndex --- 图片索引(以0为起点)
//       bRepaint    --- 是否重绘
// 返回:
//       成功返回0,失败返回-1
//---------------------------------------------------------
int CListBoxXI::SetItemImage(int nIndex, int nImageIndex, BOOL bRepaint)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return -1;
	}
	pLBData->iImageIndex = nImageIndex;

	if (bRepaint)
	{
		Invalidate();
	}

	return 0;
}

//---------------------------------------------------------
// 函数: AddString
// 功能: 添加项
// 参数: lpszString  --- 字符串指针
//        nImageIndex --- 图片索引(以0为起点)
// 返回: 新增项的索引值
//        失败则返回LB_ERR或LB_ERRSPACE
//---------------------------------------------------------
int CListBoxXI::AddString(LPCTSTR lpszString, int nImageIndex)
{
	int nIndex = CListBox::AddString(lpszString);

	if (nIndex != LB_ERR && nIndex != LB_ERRSPACE)
	{
		LBDataXI *pData = new LBDataXI();
		pData->iImageIndex = nImageIndex;
		pData->pData = NULL;
		CListBox::SetItemData(nIndex, (DWORD_PTR)pData);
	}

	return nIndex;
}

//---------------------------------------------------------
// 函数: InsertString
// 功能: 在指定位置插入项
// 参数: 
//       nIndex      --- 指定位置
//       lpszString  --- 字符串指针
//       nImageIndex --- 图片索引(以0为起点)
// 返回: 
//       插入项索引值
//       失败则返回LB_ERR或LB_ERRSPACE
//---------------------------------------------------------
int CListBoxXI::InsertString(int nIndex, LPCTSTR lpszString, int nImageIndex)
{
	int nRet = CListBox::InsertString(nIndex, lpszString);
	if (nRet != LB_ERR && nRet != LB_ERRSPACE)
	{
		LBDataXI *pData = new LBDataXI();
		pData->iImageIndex = nImageIndex;
		pData->pData = NULL;
		CListBox::SetItemData(nIndex, (DWORD_PTR)pData);
	}

	return nRet;
}

//---------------------------------------------------------
// 函数: DeleteString
// 功能: 删除项
// 参数: 
//       nIndex  --- 索引
// 返回: 
//       成功则返回当前还剩的项数
//       失败则返回LB_ERR
//---------------------------------------------------------
int CListBoxXI::DeleteString(UINT nIndex)
{
	DeleteItemData(nIndex);

	return CListBox::DeleteString(nIndex);
}

//---------------------------------------------------------
// 函数: ResetContent
// 功能: 清空内容
//---------------------------------------------------------
void CListBoxXI::ResetContent()
{
	int nCnt = CListBox::GetCount();
	for (int i = 0; i < nCnt; ++i)
	{
		DeleteItemData(i);
	}

	CListBox::ResetContent();
}

//---------------------------------------------------------
// 函数: GetItemData
// 功能: 获取项关联的数据
// 参数:
//       nIndex --- 索引
// 返回:
//       关联的数据,失败则返回LB_ERR
//---------------------------------------------------------
DWORD_PTR CListBoxXI::GetItemData(int nIndex) const
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return LB_ERR;
	}

	return (DWORD_PTR)pLBData->pData;
}

//---------------------------------------------------------
// 函数: SetItemData
// 功能: 设置项关联的数据
// 参数:
//       nIndex     --- 索引
//       dwItemData --- 关联的数据 
// 返回:
//       成功返回LB_OKAY, 失败返回LB_ERR
//---------------------------------------------------------
int CListBoxXI::SetItemData(int nIndex, DWORD_PTR dwItemData)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return LB_ERR;
	}

	pLBData->pData = (LPVOID)dwItemData;
	return LB_OKAY;
}

//---------------------------------------------------------
// 函数: GetItemDataPtr
// 功能: 获取项关联的数据
// 参数:
//       nIndex --- 索引
// 返回:
//       关联的数据,失败则返回LB_ERR
//---------------------------------------------------------
void* CListBoxXI::GetItemDataPtr(int nIndex) const
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemDataPtr(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return (void*)LB_ERR;
	}

	return pLBData->pData;
}

//---------------------------------------------------------
// 函数: SetItemDataPtr
// 功能: 设置项关联的数据
// 参数:
//       nIndex --- 索引
//       pData  --- 关联的数据
// 返回:
//       成功返回LB_OKAY, 失败则返回LB_ERR
//---------------------------------------------------------
int CListBoxXI::SetItemDataPtr(int nIndex, void* pData)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemDataPtr(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return LB_ERR;
	}

	pLBData->pData = pData;
	return LB_OKAY;
}

void CListBoxXI::DeleteItemData(int nIndex)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData != (LBDataXI*)LB_ERR)
	{
		delete pLBData;
		CListBox::SetItemData(nIndex, (DWORD_PTR)NULL);
	}
}

void CListBoxXI::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	pDC->SetBkMode(TRANSPARENT);
	RECT& rcItem = lpDrawItemStruct->rcItem;

	CString cstrItemText;
	CListBox::GetText(lpDrawItemStruct->itemID, cstrItemText);

	LBDataXI* pData = (LBDataXI*)CListBox::GetItemDataPtr(lpDrawItemStruct->itemID);
	if (NULL == pData)
	{
		return;
	}

	// 是否处于选中状态
	BOOL bIsSelected = (lpDrawItemStruct->itemAction | ODA_SELECT) 
		&& (lpDrawItemStruct->itemState & ODS_SELECTED);

	// 是否处于焦点状态
	BOOL bIsFocused = (lpDrawItemStruct->itemAction | ODA_FOCUS) 
		&& (lpDrawItemStruct->itemState & ODS_FOCUS);

	// 绘制背景
	if (bIsSelected)
	{
		COLORREF oldColor = pDC->GetBkColor();
		pDC->FillSolidRect(&rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
		pDC->SetBkColor(oldColor);
	}
	else
	{
		pDC->FillSolidRect(&rcItem, pDC->GetBkColor());
	}

	// 绘制ICON
	CRect rcIcon(rcItem.left, rcItem.top, rcItem.left, rcItem.top);
	if (m_pImageList)
	{
		HICON hIcon = m_pImageList->ExtractIcon(pData->iImageIndex);
		if (hIcon)
		{
			rcIcon.right = rcItem.left + m_imageSize.cx + 2 * LBXI_CX_BORDER;
			rcIcon.bottom = rcItem.top + m_imageSize.cy + 2 * LBXI_CY_BORDER;

			CPoint pos(rcIcon.left + LBXI_CX_BORDER, rcIcon.top + LBXI_CY_BORDER);
			pDC->DrawState(pos, m_imageSize, hIcon, DSS_NORMAL, (CBrush*)NULL);
			::DestroyIcon(hIcon);
		}
	}

	// 绘制Text
	if (bIsSelected)
	{
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	}
	CRect rcText(rcItem);
	rcText.left = rcIcon.right;
	rcText.top = rcIcon.top;
	pDC->DrawText(cstrItemText, rcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_WORDBREAK);
}

void CListBoxXI::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC *pDC = GetDC();
	LPCTSTR lpszText = (LPCTSTR)lpMeasureItemStruct->itemData;
	CSize szText = pDC->GetTextExtent(lpszText);
	ReleaseDC(pDC);

	lpMeasureItemStruct->itemHeight = 
		szText.cy > m_imageSize.cy + 2 * LBXI_CY_BORDER ? szText.cy :  m_imageSize.cy + 2 * LBXI_CY_BORDER;
}

BEGIN_MESSAGE_MAP(CListBoxXI, CListBox)
END_MESSAGE_MAP()

// CListBoxXI message handlers


