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
// ����: SetImageList
// ����: ���ù�����ImageList
// ����: 
//       pImageList --- ImageList��ָ��
// ����: ��
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
// ����: GetImageList
// ����: ��ȡ����ImageList��ָ��
// ����: ��
// ����: ����ImageList��ָ��,��û�й���ImageList����NULL
//---------------------------------------------------------
CImageList* CListBoxXI::GetImageList() const
{
	return m_pImageList;
}

//---------------------------------------------------------
// ����: GetItemImage
// ����: ��ȡ���ͼƬ����
// ����: 
//       nIndex  --- ������(��0Ϊ���)
// ����:
//       ��0Ϊ��ʼ��ͼƬ�������
//       �����ڴ���,��nIndex������Χ,����-1
//       ����û�й���ͼƬ,����-1
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
// ����: SetItemImage
// ����: �������ͼƬ����
// ����: 
//       nIndex      --- ������(��0Ϊ���)
//       nImageIndex --- ͼƬ����(��0Ϊ���)
//       bRepaint    --- �Ƿ��ػ�
// ����:
//       �ɹ�����0,ʧ�ܷ���-1
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
// ����: AddString
// ����: �����
// ����: lpszString  --- �ַ���ָ��
//        nImageIndex --- ͼƬ����(��0Ϊ���)
// ����: �����������ֵ
//        ʧ���򷵻�LB_ERR��LB_ERRSPACE
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
// ����: InsertString
// ����: ��ָ��λ�ò�����
// ����: 
//       nIndex      --- ָ��λ��
//       lpszString  --- �ַ���ָ��
//       nImageIndex --- ͼƬ����(��0Ϊ���)
// ����: 
//       ����������ֵ
//       ʧ���򷵻�LB_ERR��LB_ERRSPACE
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
// ����: DeleteString
// ����: ɾ����
// ����: 
//       nIndex  --- ����
// ����: 
//       �ɹ��򷵻ص�ǰ��ʣ������
//       ʧ���򷵻�LB_ERR
//---------------------------------------------------------
int CListBoxXI::DeleteString(UINT nIndex)
{
	DeleteItemData(nIndex);

	return CListBox::DeleteString(nIndex);
}

//---------------------------------------------------------
// ����: ResetContent
// ����: �������
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
// ����: GetItemData
// ����: ��ȡ�����������
// ����:
//       nIndex --- ����
// ����:
//       ����������,ʧ���򷵻�LB_ERR
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
// ����: SetItemData
// ����: ���������������
// ����:
//       nIndex     --- ����
//       dwItemData --- ���������� 
// ����:
//       �ɹ�����LB_OKAY, ʧ�ܷ���LB_ERR
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
// ����: GetItemDataPtr
// ����: ��ȡ�����������
// ����:
//       nIndex --- ����
// ����:
//       ����������,ʧ���򷵻�LB_ERR
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
// ����: SetItemDataPtr
// ����: ���������������
// ����:
//       nIndex --- ����
//       pData  --- ����������
// ����:
//       �ɹ�����LB_OKAY, ʧ���򷵻�LB_ERR
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
			rcIcon.right = rcItem.left + m_imageSize.cx + 2 * LBXI_CX_BORDER;
			rcIcon.bottom = rcItem.top + m_imageSize.cy + 2 * LBXI_CY_BORDER;

			CPoint pos(rcIcon.left + LBXI_CX_BORDER, rcIcon.top + LBXI_CY_BORDER);
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


