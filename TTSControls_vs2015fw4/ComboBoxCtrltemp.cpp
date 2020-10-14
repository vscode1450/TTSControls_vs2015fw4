
#include "Public.h"   //头文件和cpp文件都要引用的，否则Image* err
#include <atlimage.h>  

#include "pch.h"
#include "framework.h"
#include "resource.h"

#include "TTSControls_vs2015fw4.h"
#include "ComboBoxCtrltemp.h"



IMPLEMENT_DYNAMIC(ComboBoxCtrltemp, CComboBox)

BEGIN_MESSAGE_MAP(ComboBoxCtrltemp, CComboBox)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnCbnSelchange)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
ComboBoxCtrltemp::ComboBoxCtrltemp()
{
	m_bOver = FALSE;
	m_bArtFont = FALSE;
	m_pBrsh = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	m_bgPen.CreatePen(PS_SOLID, 1, RGB(160, 31, 208));
	m_font.CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("宋体"));
	m_bDown = FALSE;
	m_selItem = 666666666;
	m_preSelItem = 666666666;
	m_bFous = FALSE;
	m_endIcon = NULL;
	m_crFrame = DEF_FRAME_COLOR;
	m_crBgTitle = DEF_BG_COLOR;
	m_crBgSelected = DEF_SELECT_COLOR;
	m_crBgNoSelected = DEF_BG_COLOR;
	m_crArtFont = DEF_FRAME_COLOR;
	m_norImg = NULL;
	m_clickImg = NULL;
}

ComboBoxCtrltemp::~ComboBoxCtrltemp()
{
	if (m_bgPen.m_hObject != NULL)
		m_bgPen.DeleteObject();
	if (m_pBrsh->m_hObject != NULL)
		m_pBrsh->DeleteObject();
	if (m_font.m_hObject != NULL)
		m_font.DeleteObject();
	for (auto* e : m_vecItemList)
	{
		if (e != NULL) {
			delete e;
		}
	}
}
void ComboBoxCtrltemp::AddNewString(CString leftText, UINT icon, COLORREF leftColor)
{
	ItemList* pItem = new ItemList;
	pItem->clrLeft = leftColor;
	pItem->hIcon = icon ? AfxGetApp()->LoadIcon(icon) : NULL;
	pItem->strUrl = leftText;
	pItem->iItem = AddString(leftText);
	m_vecItemList.push_back(pItem);
}
void ComboBoxCtrltemp::SetEndIcon(UINT endIcon) {
	m_endIcon = endIcon;
}
void ComboBoxCtrltemp::SetRightButton(UINT norImg, UINT clickImg) {
	m_norImg = ImageFromResource(AfxGetInstanceHandle(), norImg, _T("PNG"));
	m_clickImg = ImageFromResource(AfxGetInstanceHandle(), clickImg, _T("PNG"));
	if (!m_norImg || !m_clickImg) {
		m_norImg = m_clickImg = NULL;
	}
}
Image* ComboBoxCtrltemp::ImageFromResource(HINSTANCE hInstance, UINT uImgID, LPCTSTR lpType)
{
	HRSRC hResInfo = ::FindResource(hInstance, MAKEINTRESOURCE(uImgID), lpType);
	if (hResInfo == NULL)
		return NULL; //fail  
	DWORD dwSize;
	dwSize = SizeofResource(hInstance, hResInfo); //get resource size(bytes)   
	HGLOBAL hResData;
	hResData = ::LoadResource(hInstance, hResInfo);
	if (hResData == NULL)
		return NULL; //fail  
	HGLOBAL hMem;
	hMem = ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
	if (hMem == NULL) {
		::FreeResource(hResData);
		return NULL;
	}
	LPVOID lpResData, lpMem;
	lpResData = ::LockResource(hResData);
	lpMem = ::GlobalLock(hMem);
	::CopyMemory(lpMem, lpResData, dwSize); //copy memory  
	::GlobalUnlock(hMem);
	::FreeResource(hResData); //free memory  

	IStream* pStream;
	HRESULT hr;
	hr = ::CreateStreamOnHGlobal(hMem, TRUE, &pStream);//create stream object  
	Image* pImage = NULL;
	if (SUCCEEDED(hr)) {
		pImage = Image::FromStream(pStream);//get GDI+ pointer  
		pStream->Release();
	}
	::GlobalFree(hMem);
	return pImage;
}

void ComboBoxCtrltemp::SetComboColor(COLORREF crFrame, COLORREF crBgTitle, COLORREF crBgSelected, COLORREF crBgNoSelected)
{
	m_crFrame = crFrame;
	m_crBgTitle = crBgTitle;
	m_crBgSelected = crBgSelected;
	m_crBgNoSelected = crBgNoSelected;
}
void ComboBoxCtrltemp::SetFontType(int fontSize, CString fontType, BOOL bArtFont, COLORREF crArtFont) {
	m_font.Detach();
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = fontSize;
	_tcsncpy_s(lf.lfFaceName, LF_FACESIZE, fontType, fontType.GetLength());
	VERIFY(m_font.CreateFontIndirect(&lf));
	m_bArtFont = bArtFont;
	m_crArtFont = crArtFont;
}

void ComboBoxCtrltemp::InitControl(void)
{
	//王建峰 
	//
	AddNewString(_T("对弈"), IDI_ICON1);
	AddNewString(_T("无应"), IDI_ICON2);
	AddNewString(_T("攻守"), IDI_ICON3);
	SetFontType(10, _T("宋体"), TRUE, RGB(0, 150, 255));
	SetRightButton(IDB_PNG1, IDB_PNG1);
	//SetCurSel(0);

}

void ComboBoxCtrltemp::OnNcPaint(CDC* pDC)
{
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
	CBrush bgBs(m_crBgNoSelected);
	CBrush* pOldBrsh = dMemDC.SelectObject(&bgBs);
	dMemDC.Rectangle(&rc);
	dMemDC.SelectObject(pOldPen);
	dMemDC.SelectObject(&pOldBrsh);

	if ((GetCurSel() > 4) || (GetCurSel() < 0))
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
	if (pItem->hIcon != NULL) {
		rcLeft.left = 5;
		rcLeft.right = rcLeft.left + 16;
		rcLeft.top += 4;
		::DrawIconEx(dMemDC.m_hDC, rcLeft.left, rcLeft.top, pItem->hIcon, 16, 16, NULL, NULL, DI_NORMAL);
	}
	else {
		rcLeft.right = 0;
	}
	//画第二段文本
	rcMid.left = rcLeft.right + 5;
	CFont* pOldFont = dMemDC.SelectObject(&m_font);
	DrawTextString(&dMemDC, pItem->strUrl, pItem->clrLeft, m_crArtFont, &rcMid);
	dMemDC.SelectObject(pOldFont);

	CRect rcEnd(rc);
	rcEnd.left = rc.right - 22;
	if (m_norImg == NULL) {
		if (m_bDown)
		{
			dMemDC.DrawFrameControl(&rcEnd, DFC_SCROLL, DFCS_SCROLLDOWN | DFCS_FLAT | DFCS_MONO | DFCS_PUSHED);
		}
		else
		{
			dMemDC.DrawFrameControl(&rcEnd, DFC_SCROLL, DFCS_SCROLLDOWN | DFCS_FLAT | DFCS_MONO);
		}
	}
	else {
		Graphics graphics(dMemDC.m_hDC);
		if (m_bDown) {
			graphics.DrawImage(m_norImg, rcEnd.left, rcEnd.top + 1, 22, 22);
		}
		else {
			graphics.DrawImage(m_clickImg, rcEnd.left, rcEnd.top + 1, 22, 22);
		}
		graphics.ReleaseHDC(dMemDC.m_hDC);
	}


	pDC->BitBlt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, &dMemDC,
		rc.left, rc.top, SRCCOPY);

	//恢复
	dMemDC.SelectObject(pOldBmp);
	pOldBmp->DeleteObject();
	dMemDC.DeleteDC();
}
void ComboBoxCtrltemp::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	OnNcPaint(&dc);
}
void ComboBoxCtrltemp::DrawContent(UINT iState, CRect rcClient, CDC* pDC, int itemID)
{
	PItemList pItem = m_vecItemList[itemID];

	CPen	m_penLeft;
	CPen	m_penRight;
	CRect rcLeft, rcMid;
	rcLeft = rcMid = rcClient;
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
		CBrush bgBs(m_crBgSelected);
		CBrush* pOldBrush = pDC->SelectObject(&bgBs);
		pDC->RoundRect(&rcClient, CPoint(5, 5));
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
		bgPen.DeleteObject();
	}
	else {
		CBrush bgBs(m_crBgNoSelected);
		pDC->FillRect(&rcClient, &bgBs);
	}
	//画第一段图标
	if (pItem->hIcon != NULL) {
		rcLeft.left = 5;
		rcLeft.right = rcLeft.left + 16;
		rcLeft.top += 4;
		::DrawIconEx(pDC->m_hDC, rcLeft.left, rcLeft.top, pItem->hIcon, 16, 16, NULL, NULL, DI_NORMAL);
	}
	else {
		rcLeft.right = 0;
	}

	//画第二段文本
	rcMid.left = rcLeft.right + 5;
	if (m_endIcon != NULL)
		rcMid.right -= 22;
	pDC->SetTextColor(pItem->clrLeft);
	CFont* pOldFont = pDC->SelectObject(&m_font);
	DrawTextString(pDC, pItem->strUrl, pItem->clrLeft, m_crArtFont, &rcMid);
	pDC->SelectObject(pOldFont);

	CRect rcEnd(rcClient);
	rcEnd.left = rcEnd.right - 18;
	rcEnd.top += 3;
	if (itemID == m_selItem && m_endIcon != NULL)
		DrawIconEx(pDC->m_hDC, rcEnd.left, rcEnd.top, AfxGetApp()->LoadIcon(m_endIcon), 16, 16, NULL, NULL, DI_NORMAL);
}
//鼠标移动消息
void ComboBoxCtrltemp::OnMouseMove(UINT nFlags, CPoint point)
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

//鼠标离开消息
LRESULT ComboBoxCtrltemp::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	if (m_bOver)
	{
		m_bOver = FALSE;
	}
	UpdateRect();

	return 1;
}

void ComboBoxCtrltemp::UpdateRect(void)
{
	CRect rcClient;
	GetWindowRect(&rcClient);
	rcClient.DeflateRect(-2, -2);
	GetParent()->ScreenToClient(&rcClient);
	GetParent()->InvalidateRect(&rcClient, FALSE);
	return;
}

//绘画背景
BOOL ComboBoxCtrltemp::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void ComboBoxCtrltemp::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDown = TRUE;
	UpdateRect();
	CComboBox::OnLButtonDown(nFlags, point);
}

void ComboBoxCtrltemp::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDown = FALSE;
	UpdateRect();
	CComboBox::OnLButtonUp(nFlags, point);
}
void ComboBoxCtrltemp::OnCbnSelchange()
{
	UpdateRect();
}

void ComboBoxCtrltemp::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (lpDrawItemStruct->CtlType != ODT_COMBOBOX)
	{
		return;
	}
	UINT itemID = lpDrawItemStruct->itemID;
	CRect rcClient = lpDrawItemStruct->rcItem;
	UINT  iState = lpDrawItemStruct->itemState;

	CBitmap MemBit;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	DrawContent(iState, rcClient, pDC, itemID);
}

void ComboBoxCtrltemp::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 30;
	lpMeasureItemStruct->itemWidth = 400;
}
LRESULT ComboBoxCtrltemp::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
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
//艺术字体
void ComboBoxCtrltemp::DrawTextString(CDC* pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, LPRECT lpRect)
{
	//变量定义
	int nStringLength = lstrlen(pszString);
	int nXExcursion[8] = { 1,1,1,0,-1,-1,-1,0 };
	int nYExcursion[8] = { -1,0,1,1,1,0,-1,-1 };
	//绘画边框
	pDC->SetTextColor(crFrame);
	CRect rcDraw;
	for (int i = 0; i < sizeof(nXExcursion) / sizeof(nXExcursion[0]); ++i)
	{
		rcDraw.CopyRect(lpRect);
		rcDraw.OffsetRect(nXExcursion[i], nYExcursion[i]);
		pDC->DrawText(pszString, nStringLength, &rcDraw, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_END_ELLIPSIS);
	}
	//绘画字体
	rcDraw.CopyRect(lpRect);
	pDC->SetTextColor(crText);
	pDC->DrawText(pszString, nStringLength, &rcDraw, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_END_ELLIPSIS);
	return;
}

//艺术字体
void ComboBoxCtrltemp::DrawTextString(CDC* pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos)
{
	//变量定义
	int nStringLength = lstrlen(pszString);
	int nXExcursion[8] = { 1,1,1,0,-1,-1,-1,0 };
	int nYExcursion[8] = { -1,0,1,1,1,0,-1,-1 };
	//绘画边框
	pDC->SetTextColor(crFrame);
	for (int i = 0; i < sizeof(nXExcursion) / sizeof(nXExcursion[0]); i++)
	{
		pDC->TextOut(nXPos + nXExcursion[i], nYPos + nYExcursion[i], pszString, nStringLength);
	}

	//绘画字体
	pDC->SetTextColor(crText);
	pDC->TextOut(nXPos, nYPos, pszString, nStringLength);
	return;
}
