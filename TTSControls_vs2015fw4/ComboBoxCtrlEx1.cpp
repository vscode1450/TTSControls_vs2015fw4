/**********************************************************
������ɾ��Ҫע�⴦��  iter = abooklist.erase(iter);
 ComboBoxCtrlEx1.cpp : implementation file
 Written by Wang
 Version:

ʹ��˵��ʹ�÷���:
CComboBoxCtrlEx1 m_combo1;
CImageList  m_imglist1;
m_imglist1.Create(32, 32, ILC_COLOR32 | ILC_MASK, 2, 1);
m_imglist1.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
m_imglist1.Add(AfxGetApp()->LoadIcon(IDI_ICON2));

m_combo1.SetImageList(&m_imglist1);
m_combo1.AddString("123", 0);
m_combo1.AddString("456", 1);
m_combo1.SetCurSel(1);

ע������:
Owner Draw �� Variable (�ı��б�ĸ߶ȺͿ��)
Has Strings �� True

1��Type����:DropList(����������ֻ����CEdit+CButton+CListBox) ����DropList����MeasureItem��ȷ����EditCtrl�ĸ߶ȣ�����DropDown��Simple�����Ĭ�ϵĸ߶ȡ�
2��SetItemHeight����һ�-1�������õ���EditCtrl�ĸ߶�
3��DrawItem�У�if (lpDrawItemStruct->itemID == -1){return;}

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
// ����: SetImageList
// ����: ���ù�����ImageList
// ����: 
//       pImageList --- ImageList��ָ��
// ����: ��
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
// ����: GetImageList
// ����: ��ȡ����ImageList��ָ��
// ����: ��
// ����: ����ImageList��ָ��,��û�й���ImageList����NULL
//---------------------------------------------------------
CImageList* CComboBoxCtrlEx1::GetImageList() const
{
	return m_pImageList;
}

//---------------------------------------------------------
// ����: GetItemImage
// ����: ��ȡ���ͼƬ���� // ͼ�����,���Ϊ-1,���ʾ��ͼ��
// ����: 
//       nIndex  --- ������(��0Ϊ���)
// ����:
//       ��0Ϊ��ʼ��ͼƬ���
//       �����ڴ���,��nIndex������Χ,����-1
//       ����Ͽ���û�й���ͼƬ�򷵻�-1
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
// ����: SetItemImage
// ����: �������ͼƬ����
// ����: 
//       nIndex      --- ������(��0Ϊ���)
//       nImageIndex --- ͼƬ����(��0Ϊ���)
//       bRepaint    --- �Ƿ��ػ�
// ����:
//       �ɹ�����0,ʧ�ܷ���-1
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
// ����: AddString
// ����: �����
// ����: lpszString  --- �ַ���ָ��
//        nImageIndex --- ͼƬ����(��0Ϊ���)
// ����: �����������ֵ
//        ʧ���򷵻�CB_ERR��CB_ERRSPACE
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
// ����: InsertString
// ����: ��ָ��λ�ò�����
// ����: 
//       nIndex      --- ָ��λ��
//       lpszString  --- �ַ���ָ��
//       nImageIndex --- ͼƬ����(��0Ϊ���)
// ����: 
//       ����������ֵ
//       ʧ���򷵻�CB_ERR��CB_ERRSPACE
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
// ����: DeleteString
// ����: ɾ���� // ɾ����������
// ����: 
//       nIndex  --- ����
// ����: 
//       �ɹ��򷵻ص�ǰ��ʣ������
//       ʧ���򷵻�CB_ERR
//---------------------------------------------------------
int CComboBoxCtrlEx1::DeleteString(UINT nIndex)
{
	DeleteItemData(nIndex);

	return CComboBox::DeleteString(nIndex);
}

//---------------------------------------------------------
// ����: ResetContent
// ����: �������
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
// ����: GetItemData
// ����: ��ȡ�����������
// ����:
//       nIndex --- ����
// ����:
//       ����������,ʧ���򷵻�CB_ERR
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

	// ����Ƿ���DropList
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

	// ����EditCtrl�ĸ߶�
	if (m_iIsDropList == 1 && lpMeasureItemStruct->itemHeight > m_nEditHeight)
	{
		m_nEditHeight = lpMeasureItemStruct->itemHeight;
		SetItemHeight(-1, m_nEditHeight);
	}
}
//---------------------------------------------------------
// ����: SetItemData
// ����: ���������������
// ����:
//       nIndex     --- ����
//       dwItemData --- ���������� 
// ����:
//       �ɹ�����CB_OKAY, ʧ�ܷ���CB_ERR
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
// ����: GetItemDataPtr
// ����: ��ȡ�����������
// ����:
//       nIndex --- ����
// ����:
//       ����������,ʧ���򷵻�CB_ERR
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
// ����: SetItemDataPtr
// ����: ���������������
// ����:
//       nIndex --- ����
//       pData  --- ����������
// ����:
//       �ɹ�����CB_OKAY, ʧ���򷵻�CB_ERR
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

	// �Ƿ���ѡ��״̬
	BOOL bIsSelected = (lpDrawItemStruct->itemAction | ODA_SELECT)
		&& (lpDrawItemStruct->itemState & ODS_SELECTED);

	// �Ƿ��ڽ���״̬
	BOOL bIsFocused = (lpDrawItemStruct->itemAction | ODA_FOCUS)
		&& (lpDrawItemStruct->itemState & ODS_FOCUS);

	// ���Ʊ���
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

	// ����ICON
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

	// ����Text
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
