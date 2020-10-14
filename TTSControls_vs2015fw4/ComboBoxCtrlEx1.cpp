/**********************************************************
迭代器删除要注意处理  iter = abooklist.erase(iter);
 ComboBoxCtrlEx1.cpp : implementation file
 Written by Wang
 Version:

使用说明使用方法:
CComboBoxCtrlEx1 m_combo1;
CImageList  m_imglist1;
m_imglist1.Create(32, 32, ILC_COLOR32 | ILC_MASK, 2, 1);
m_imglist1.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
m_imglist1.Add(AfxGetApp()->LoadIcon(IDI_ICON2));

m_combo1.SetImageList(&m_imglist1);
m_combo1.AddString("123", 0);
m_combo1.AddString("456", 1);
m_combo1.SetCurSel(1);

注意事项:
Owner Draw — Variable (改变列表的高度和宽度)
Has Strings — True

1、Type属性:DropList(可以理解成是只读的CEdit+CButton+CListBox) 对于DropList，在MeasureItem中确定了EditCtrl的高度，对于DropDown和Simple则采用默认的高度。
2、SetItemHeight，第一项传-1表明设置的是EditCtrl的高度
3、DrawItem中，if (lpDrawItemStruct->itemID == -1){return;}

**********************************************************/

#include "stdafx.h"
#include "resource.h"
#include "ComboBoxCtrlEx1.h"

#define	CBXI_CX_BORDER   2
#define	CBXI_CY_BORDER   2

// CComboBoxCtrlEx1

IMPLEMENT_DYNAMIC(CComboBoxCtrlEx1, CComboBox)
BEGIN_MESSAGE_MAP(CComboBoxCtrlEx1, CComboBox)
END_MESSAGE_MAP()

// CComboBoxCtrlEx1 message handlers
CComboBoxCtrlEx1::CComboBoxCtrlEx1()
{
	m_pImageList = NULL;
	m_imageSize.cx = 0;
	m_imageSize.cy = 0;
	m_nEditHeight = 0;
	m_iIsDropList = -1;
}

CComboBoxCtrlEx1::~CComboBoxCtrlEx1()
{
}

//---------------------------------------------------------
// 函数: SetImageList
// 功能: 设置关联的ImageList
// 参数: 
//       pImageList --- ImageList的指针
// 返回: 无
//---------------------------------------------------------
void CComboBoxCtrlEx1::SetImageList(CImageList* pImageList)
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
CImageList* CComboBoxCtrlEx1::GetImageList() const
{
	return m_pImageList;
}

//---------------------------------------------------------
// 函数: GetItemImage
// 功能: 获取项的图片索引 // 图像序号,如果为-1,则表示无图像
// 参数: 
//       nIndex  --- 项索引(以0为起点)
// 返回:
//       以0为起始的图片序号
//       若存在错误,如nIndex超出范围,返回-1
//       若组合框项没有关联图片则返回-1
//---------------------------------------------------------
int CComboBoxCtrlEx1::GetItemImage(int nIndex)
{
	CBDataXI* pCBData = (CBDataXI*)CComboBox::GetItemData(nIndex);
	if (pCBData == (CBDataXI*)CB_ERR || pCBData == NULL)
	{
		return -1;
	}

	return pCBData->iImageIndex;
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
int CComboBoxCtrlEx1::SetItemImage(int nIndex, int nImageIndex, BOOL bRepaint)
{
	CBDataXI* pCBData = (CBDataXI*)CComboBox::GetItemData(nIndex);
	if (pCBData == (CBDataXI*)CB_ERR || pCBData == NULL)
	{
		return -1;
	}
	pCBData->iImageIndex = nImageIndex;

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
//        失败则返回CB_ERR或CB_ERRSPACE
//---------------------------------------------------------
int CComboBoxCtrlEx1::AddString(LPCTSTR lpszString, int nImageIndex)
{
	int nIndex = CComboBox::AddString(lpszString);
	if (nIndex != CB_ERR && nIndex != CB_ERRSPACE)
	{
		CBDataXI* pData = new CBDataXI();
		pData->iImageIndex = nImageIndex;
		pData->pData = NULL;
		CComboBox::SetItemData(nIndex, (DWORD_PTR)pData);
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
//       失败则返回CB_ERR或CB_ERRSPACE
//---------------------------------------------------------
int CComboBoxCtrlEx1::InsertString(int nIndex, LPCTSTR lpszString, int nImageIndex)
{
	int nRet = CComboBox::InsertString(nIndex, lpszString);
	if (nRet != CB_ERR && nRet != CB_ERRSPACE)
	{
		CBDataXI* pData = new CBDataXI();
		pData->iImageIndex = nImageIndex;
		pData->pData = NULL;
		CComboBox::SetItemData(nIndex, (DWORD_PTR)pData);
	}

	return nRet;
}

//---------------------------------------------------------
// 函数: DeleteString
// 功能: 删除项 // 删除关联数据
// 参数: 
//       nIndex  --- 索引
// 返回: 
//       成功则返回当前还剩的项数
//       失败则返回CB_ERR
//---------------------------------------------------------
int CComboBoxCtrlEx1::DeleteString(UINT nIndex)
{
	DeleteItemData(nIndex);

	return CComboBox::DeleteString(nIndex);
}

//---------------------------------------------------------
// 函数: ResetContent
// 功能: 清空内容
//---------------------------------------------------------
void CComboBoxCtrlEx1::ResetContent()
{
	int nCnt = CComboBox::GetCount();
	for (int i = 0; i < nCnt; ++i)
	{
		DeleteItemData(i);
	}

	CComboBox::ResetContent();
}

//---------------------------------------------------------
// 函数: GetItemData
// 功能: 获取项关联的数据
// 参数:
//       nIndex --- 索引
// 返回:
//       关联的数据,失败则返回CB_ERR
//---------------------------------------------------------
DWORD_PTR CComboBoxCtrlEx1::GetItemData(int nIndex) const
{
	CBDataXI* pCBData = (CBDataXI*)CComboBox::GetItemData(nIndex);
	if (pCBData == (CBDataXI*)CB_ERR || pCBData == NULL)
	{
		return CB_ERR;
	}

	return (DWORD_PTR)pCBData->pData;
}

void CComboBoxCtrlEx1::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC* pDC = GetDC();
	LPCTSTR lpszText = (LPCTSTR)lpMeasureItemStruct->itemData;
	CSize szText = pDC->GetTextExtent(lpszText);
	ReleaseDC(pDC);

	lpMeasureItemStruct->itemHeight =
		szText.cy > m_imageSize.cy + 2 * CBXI_CY_BORDER ? szText.cy : m_imageSize.cy + 2 * CBXI_CY_BORDER;

	// 检测是否是DropList
	if (-1 == m_iIsDropList)
	{
		DWORD dwStyle = GetStyle();
		if (DWORD(CBS_DROPDOWNLIST & dwStyle) == (DWORD)CBS_DROPDOWNLIST)
		{
			m_iIsDropList = 1;
		}
		else
		{
			m_iIsDropList = 0;
		}
	}

	// 设置EditCtrl的高度
	if (m_iIsDropList == 1 && lpMeasureItemStruct->itemHeight > m_nEditHeight)
	{
		m_nEditHeight = lpMeasureItemStruct->itemHeight;
		SetItemHeight(-1, m_nEditHeight);
	}
}
//---------------------------------------------------------
// 函数: SetItemData
// 功能: 设置项关联的数据
// 参数:
//       nIndex     --- 索引
//       dwItemData --- 关联的数据 
// 返回:
//       成功返回CB_OKAY, 失败返回CB_ERR
//---------------------------------------------------------
int CComboBoxCtrlEx1::SetItemData(int nIndex, DWORD_PTR dwItemData)
{
	CBDataXI* pCBData = (CBDataXI*)CComboBox::GetItemData(nIndex);
	if (pCBData == (CBDataXI*)CB_ERR || pCBData == NULL)
	{
		return CB_ERR;
	}

	pCBData->pData = (LPVOID)dwItemData;
	return CB_OKAY;
}

//---------------------------------------------------------
// 函数: GetItemDataPtr
// 功能: 获取项关联的数据
// 参数:
//       nIndex --- 索引
// 返回:
//       关联的数据,失败则返回CB_ERR
//---------------------------------------------------------
void* CComboBoxCtrlEx1::GetItemDataPtr(int nIndex) const
{
	CBDataXI* pCBData = (CBDataXI*)CComboBox::GetItemDataPtr(nIndex);
	if (pCBData == (CBDataXI*)CB_ERR || pCBData == NULL)
	{
		return (void*)CB_ERR;
	}

	return pCBData->pData;
}
//---------------------------------------------------------
// 函数: SetItemDataPtr
// 功能: 设置项关联的数据
// 参数:
//       nIndex --- 索引
//       pData  --- 关联的数据
// 返回:
//       成功返回CB_OKAY, 失败则返回CB_ERR
//---------------------------------------------------------
int CComboBoxCtrlEx1::SetItemDataPtr(int nIndex, void* pData)
{
	CBDataXI* pCBData = (CBDataXI*)CComboBox::GetItemDataPtr(nIndex);
	if (pCBData == (CBDataXI*)CB_ERR || pCBData == NULL)
	{
		return CB_ERR;
	}

	pCBData->pData = pData;
	return CB_OKAY;
}

void CComboBoxCtrlEx1::DeleteItemData(int nIndex)
{
	CBDataXI* pCBData = (CBDataXI*)CComboBox::GetItemData(nIndex);
	if (pCBData != (CBDataXI*)CB_ERR)
	{
		delete pCBData;
		CComboBox::SetItemData(nIndex, (DWORD_PTR)NULL);
	}
}

void CComboBoxCtrlEx1::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (lpDrawItemStruct->itemID == -1)
	{
		return;
	}

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	pDC->SetBkMode(TRANSPARENT);
	RECT& rcItem = lpDrawItemStruct->rcItem;

	CString cstrItemText;
	CComboBox::GetLBText(lpDrawItemStruct->itemID, cstrItemText);

	CBDataXI* pData = (CBDataXI*)CComboBox::GetItemDataPtr(lpDrawItemStruct->itemID);
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
			rcIcon.right = rcItem.left + m_imageSize.cx + 2 * CBXI_CX_BORDER;
			rcIcon.bottom = rcItem.top + m_imageSize.cy + 2 * CBXI_CY_BORDER;

			CPoint pos(rcIcon.left + CBXI_CX_BORDER, rcIcon.top + CBXI_CY_BORDER);
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
