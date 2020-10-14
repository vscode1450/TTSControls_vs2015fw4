// ComboBoxCtrlEx.cpp : ʵ���ļ�

#include "stdafx.h"
#include "resource.h"
#include "ComboBoxCtrlEx.h"

//��Խ��ļ��if (size() <= _Pos)ֻ���� Debug ģʽ�½��У������ǿ���ͨ��
//#define _HAS_ITERATOR_DEBUGGING 0
//���ε�������ġ�
//���� Release ģʽ�£���������������ּ�⡣
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
	m_bgBrush->CreateSolidBrush(RGB(141, 178, 227));//��ˢ����

	m_bgPen.CreatePen(PS_SOLID, 1, RGB(160, 31, 208));//������ɫ
	m_font.CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("����"));
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


// CComboBoxCtrlEx ��Ϣ�������

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
	/*����lpDrawItemStruct�����itemID����ȡ����AddString��ID��
	ͨ�����ID��, ���ǿ��Ի�ȡ������ItemList�Ľṹ.�Ӷ�������Ӧ�Ķ���.*/

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

		//���µ�ǰ����
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
//��DrawItem �¼��л�����֮ǰָ������Ĵ�С������
void CComboBoxCtrlEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 30;
	lpMeasureItemStruct->itemWidth = 400;
}


//(��ʼ������)������ؼ��ϣ�����ؼ�����ʾ
void CComboBoxCtrlEx::InitControl(void)
{
	//������  ��������AddString(_T("Google��ҳ"));  ��AddString,��ô���ݾͼӲ���
	ItemList* pItem0 = new ItemList;
	pItem0->clrLeft = RGB(0, 132, 114);
	pItem0->clrRight = RGB(0, 255, 125);
	pItem0->hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	pItem0->strTitle = _T("����ʦ ʢ�����");
	pItem0->strUrl = _T("http://www.qq.com");
	AddString(_T("�ȸ��������")); //��AddString, ��ô���ݾͼӲ���ȥ
	pItem0->iItem = 1;
	//����vector��push_back("aa")������vector��������ݣ��÷������Զ������ڴ棬����vector��size�Ϳ��������ӣ�����Խ�硣
	////push��push_back��STL�г����ķ��������������ݽṹ�����Ԫ�ء�
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

	//һ��Ҫ����һ��
	//GetDlgItem(IDC_STATIC)->SetWindowText("your string");
	//GetDlgItem(IDC_STATIC)->GetParent()->RedrawWindow();
		//InvalidateRect(rc);
	// TODO: �ڴ���ӿؼ�֪ͨ����������


}

//�߿����ͨ������OnNCPaintʵ��.  DrawContent��OnNcPaint�еĻ��Ʋ���Ҫ��ͬ��������Ŀ�ĸ߶Ȳ�ͬ
void CComboBoxCtrlEx::OnNcPaint(CDC* pDC)
{
	HICON hIcon;//��ǰͼ����

	//���ƿͻ���
	CDC dMemDC;
	dMemDC.CreateCompatibleDC(pDC);
	dMemDC.SetMapMode(pDC->GetMapMode());

	//������
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

	//����һ��ͼ��
	rcLeft.right = rcLeft.left + 16;
	rcLeft.left += 1;
	rcLeft.top += 4;
	::DrawIconEx(dMemDC.m_hDC, rcLeft.left, rcLeft.top, pItem->hIcon, 16, 16, NULL, NULL, DI_NORMAL);

	//���ڶ����ı�
	rcMid.left = rcLeft.right + 10;
	rcMid.right = rc.right - 110;
	CFont* pOldFont = dMemDC.SelectObject(&m_font);
	dMemDC.SetTextColor(pItem->clrLeft);
	dMemDC.DrawText(pItem->strUrl, &rcMid, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

	//���������ı�  //�滭����
	rcRight.left = rcMid.right;
	dMemDC.SetTextColor(pItem->clrRight);
	dMemDC.DrawText(pItem->strTitle, &rcRight, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
	dMemDC.SelectObject(pOldFont);

	CRect rcEnd(rc);
	rcEnd.left = rc.right - 22;
	//rcEnd.top += 3;

	//DrawFrameControl ���ƵĽ�������Ǽ�ͷ
	if (m_bDown)
	{
		dMemDC.DrawFrameControl(&rcEnd, DFC_SCROLL, DFCS_SCROLLDOWN | DFCS_FLAT | DFCS_MONO | DFCS_PUSHED);
	}
	else
	{
		dMemDC.DrawFrameControl(&rcEnd, DFC_SCROLL, DFCS_SCROLLDOWN | DFCS_FLAT | DFCS_MONO);
	}
	//�ú���BitBlt�Ӻ�̨�豸�����а����߿�����SRCCOPY��������ΧΪ��200��100��195��100���ĵ�ǰ�豸�����У������������β���ϵ�ǰ�����ݵ㣬���ѭ����
	pDC->BitBlt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, &dMemDC,rc.left, rc.top, SRCCOPY);

	//�ָ�
	dMemDC.SelectObject(pOldBmp);
	pOldBmp->DeleteObject();
	dMemDC.DeleteDC();
}
void CComboBoxCtrlEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	OnNcPaint(&dc);
}

//DrawContent ���п�ܣ����ڿ�����������Ҫ���¡�
void CComboBoxCtrlEx::DrawContent(UINT iState, CRect rcClient, CDC* pDC, int itemID)
{
	//����
	//wjfʸ������ m_vecItemListwΪ��ʱ����  wjf m_vecItemListwΪ��ʱ����
	//m_vecItemList��0��ʼ itemID��1 
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
	//pItem�޷���ȡ�¾䱨��	if (pItem->strTitle.IsEmpty()) 

	CPen	m_penLeft;
	CPen	m_penRight;
	CRect rcLeft, rcMid, rcRight;
	rcLeft = rcMid = rcRight = rcClient;
	pDC->SetBkMode(TRANSPARENT);

	if (iState & ODS_SELECTED)
	{
		//��ʱ����ѡ������
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

	//����һ��ͼ��
	rcLeft.right = rcLeft.left + 16;
	rcLeft.left += 1;
	rcLeft.top += 4;
	::DrawIconEx(pDC->m_hDC, rcLeft.left, rcLeft.top, pItem->hIcon, 16, 16, NULL, NULL, DI_NORMAL);

	//���ڶ����ı�
	rcMid.left = rcLeft.right + 10;
	rcMid.right = rcClient.right - 110;
	CFont* pOldFont = pDC->SelectObject(&m_font);
	pDC->SetTextColor(pItem->clrLeft);
	pDC->DrawText(pItem->strUrl, &rcMid, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

	//���������ı�
	rcRight.left = rcMid.right + 8;
	pDC->SetTextColor(pItem->clrRight);
	pDC->DrawText(pItem->strTitle, &rcRight, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
	pDC->SelectObject(pOldFont);

	CRect rcEnd(rcClient);
	rcEnd.left = rcEnd.right - 22;
	//rcEnd.top += 3; //��������ƫ��

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

//�ú�����һ��Ӧ�ó�����ĺ������������͸����ڵ���Ϣ��WNDPROC���Ͷ�����һ��ָ��ûص�������ָ�롣
//hwnd��ָ�򴰿ڵľ����WindowProc������Լ��Ĵ��ڶ���Ĵ��ڴ����� DefWindowProc��windowsƽ̨�ṩ��Ĭ�ϴ��ڴ�����
//д��ͷ�ļ� virtual LRESULT WindowProc(UINT nMessage, WPARAM wParam, LPARAM lParam)switch(nMessage){case WM_MOUSEMOVE:
LRESULT CComboBoxCtrlEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	//ComboBox�µ�EditBox��ListBox������ComboBox���ڷ���WM_CTLCOLOR��Ϣ
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
