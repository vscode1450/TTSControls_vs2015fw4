#include "stdafx.h"
#include "resource.h"
#include "EditCtrlImage.h"


IMPLEMENT_DYNAMIC(CEditCtrlImage, CStatic)


CEditCtrlImage::CEditCtrlImage()
{
	m_bTracking = m_bHover = FALSE;
	m_normal_in_color = RGB(141, 178, 227);//画刷恬蓝
	m_normal_out_color = RGB(160, 31, 208);//画笔紫色
	m_text_color = RGB(0, 0, 0);//黑色
	m_left_icon = NULL;
	m_right_icon = NULL;
}

CEditCtrlImage::~CEditCtrlImage()
{
}

BEGIN_MESSAGE_MAP(CEditCtrlImage, CStatic)
	ON_WM_NCPAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//ON_WM_ERASEBKGND()当你操作滚动栏或者是在非当前dlg中的操作
	//（比如dlg是某个子窗口，当你拖动外部窗口、页面缩放时）时，
	/*你的自绘dlg此时可能不是你想要的效果，可能没有重绘。
	解决方法是ON_WM_NCPAINT中再次调用你的自绘函数DrawMyDlg（）；
	*/
END_MESSAGE_MAP()
void CEditCtrlImage::Init(BOOL leftright,HICON left_icon, HICON right_icon, int radian, int padding) {
	//m_left_icon = ImageFromResource(AfxGetResourceHandle(), left_icon, L"PNG");
	//m_right_icon = ImageFromResource(AfxGetResourceHandle(), right_icon, L"PNG");
	//m_left_icon = AfxGetApp()->LoadIcon(IDI_ICON6);
	//m_right_icon = AfxGetApp()->LoadIcon(IDI_ICON7);
	m_leftright = leftright;
	m_left_icon = left_icon;
	m_right_icon = left_icon;
	m_radian = radian;
	m_padding = padding;
}

void CEditCtrlImage::PreSubclassWindow()
{
	DWORD dwStyle = GetStyle();
	SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_OWNERDRAW | SS_NOTIFY);
	CStatic::PreSubclassWindow();
}

void CEditCtrlImage::OnNcPaint()
{
	CStatic::OnNcPaint();
}
void CEditCtrlImage::OnPaint()
{
	CStatic::OnPaint();
}
//内色外色文本颜色
void CEditCtrlImage::setNormalColor(COLORREF inColor, COLORREF outColor, COLORREF textColor) {
    m_normal_in_color = inColor;
	m_normal_out_color = outColor;
	m_text_color = textColor;
}

void CEditCtrlImage::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	/*ICONINFO iconInfo;
	::GetIconInfo(m_left_icon, &iconInfo);
	BITMAP bm;
	::GetObject(iconInfo.hbmColor, sizeof(BITMAP), &bitmap);
	m_byIconW = (byte)bitmap.bmWidth; //int* cx = bm.bmWidth;
	m_byIconH = (byte)bitmap.bmHeight;

	//删除
	::DeleteObject(iconInfo.hbmColor);
	::DeleteObject(iconInfo.hbmMask);
	 */

	CRect rc;
	rc = lpDrawItemStruct->rcItem;

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	DrawBorder(&dc, rc);
	//消减少 通过朝CRect的中心移动边以缩小CRect。
	rc.DeflateRect(m_padding, m_padding);
	
	//rc是edit的区域
	if (m_leftright) {
		/*	rc.left += m_left_icon->GetWidth();*/
		rc.left += 16;
	}
	else//右边的图
	{
		/*rc.right -= m_right_icon->GetWidth();*/
     	rc.right -= 16;
	}
	
	if (m_edit.GetSafeHwnd()) {
		m_edit.ShowWindow(SW_SHOW);
	}
	else {
		//CEdit m_edit;
		m_edit.Create(WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL, rc, this, 1);
	
		//m_edit.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL, rc, this, 1, NULL);
		//m_edit.CreateEx(NULL, NULL, WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL, NULL, NULL,WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL, rc, this, 101, NULL);

	/*	m_edit.Create(L"", L"",WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL, rc, this, 1, 0);*/
		m_edit.SetFont(GetFont());

		m_edit.SetShowDimControl(FALSE);
		m_edit.SetWindowText(_T(""));
		m_edit.SetDimText(_T("卫星分辨率8--15cm 普通0.5m"));
		m_edit.SetDimColor(RGB(0xC1, 0xCD, 0xC1));
		m_edit.SetDimOffset(-0x40, -0x40, -0x40);
		m_edit.SetShowDimControl(TRUE);

	}

	ReleaseDC(&dc);
}

void CEditCtrlImage::DrawBorder(CDC* dc, CRect& rc) 
{
	CPen inpen(PS_SOLID, 1, m_normal_in_color);
	CPen outpen(PS_SOLID, 1, m_normal_out_color);
	
	CPen* oldPen = dc->SelectObject(&inpen);
	dc->RoundRect(rc, CPoint(m_radian, m_radian));
	
	//DeFlateRect紧  充Inflate
	rc.InflateRect(-1, -1);//-1
	
	dc->SelectObject(&outpen);
	dc->RoundRect(rc, CPoint(m_radian, m_radian));
	dc->SelectObject(oldPen);

	oldPen->Detach();  //分离
	oldPen = NULL;


	//if (m_left_icon) {
	//	graph.DrawImage(m_left_icon, 0, 0, 0, 0, m_left_icon->GetWidth(), m_left_icon->GetHeight(), UnitPixel);
	//}
	//if (m_right_icon) {
	//	graph.DrawImage(m_right_icon, rc.Width() - m_right_icon->GetWidth(), 0, 0, 0, m_right_icon->GetWidth(), m_right_icon->GetHeight(), UnitPixel);
	//}
	//graph.ReleaseHDC(dc->GetSafeHdc());


	if (m_leftright) {
		::DrawIconEx(dc->m_hDC, rc.left+1, rc.top+1, m_left_icon, 16, 16, NULL, NULL, DI_NORMAL);
	}

	if (m_right_icon) {
		::DrawIconEx(dc->m_hDC, rc.Width()-16, rc.top+1, m_right_icon, 16, 16, NULL, NULL, DI_NORMAL);
	}
}

BOOL CEditCtrlImage::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


HBRUSH CEditCtrlImage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CStatic::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何特性  pDC->SetTextColor(RGB(0,69,214)); 
	pDC->SetTextColor(m_text_color);     //设置字体颜色
	//pDC->SetBkMode(TRANSPARENT);      //设置背景透明
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
	//HBRUSH B = CreateSolidBrush(RGB(125, 125, 255));
	//return (HBRUSH)B;
}


//GDI + Image类调图
//Image* CPngEdit::ImageFromResource(HINSTANCE hInstance, UINT uImgID, LPCTSTR lpType)
//{
//	HRSRC hResInfo = ::FindResource(hInstance, MAKEINTRESOURCE(uImgID), lpType);
//	if (hResInfo == NULL)
//		return NULL; //fail  
//	DWORD dwSize;
//	dwSize = SizeofResource(hInstance, hResInfo); //get resource size(bytes)   
//	HGLOBAL hResData;
//	hResData = ::LoadResource(hInstance, hResInfo);
//	if (hResData == NULL)
//		return NULL; //fail  
//	HGLOBAL hMem;
//	hMem = ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
//	if (hMem == NULL) {
//		::FreeResource(hResData);
//		return NULL;
//	}
//	LPVOID lpResData, lpMem;
//	lpResData = ::LockResource(hResData);
//	lpMem = ::GlobalLock(hMem);
//	::CopyMemory(lpMem, lpResData, dwSize); //copy memory  
//	::GlobalUnlock(hMem);
//	::FreeResource(hResData); //free memory  
//
//	IStream* pStream;
//	HRESULT hr;
//	hr = ::CreateStreamOnHGlobal(hMem, TRUE, &pStream);//create stream object  
//	Image* pImage = NULL;
//	if (SUCCEEDED(hr)) {
//		pImage = Image::FromStream(pStream);//get GDI+ pointer  
//		pStream->Release();
//	}
//	::GlobalFree(hMem);
//	return pImage;

//rcLeft = rcMid = rcRight = rc;
//dMemDC.SetBkMode(TRANSPARENT);
//
////画左边图标16*16
//rcLeft.right = rcLeft.left;
//rcLeft.right = rcLeft.left + 16; //Image* m_left_icon.GetWidth()
//rcLeft.left -= 16
//rcLeft.left += pItem->m_padding;
//rcLeft.top += 4;
//::DrawIconEx(dMemDC.m_hDC, rcLeft.left, rcLeft.top, pItem->left_hIcon, 16, 16, NULL, NULL, DI_NORMAL);
//



