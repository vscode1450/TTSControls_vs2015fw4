// ListReport.cpp : implementation file
//

#include "../..//stdafx.h"
#include "ListReport.h"

#include "..\CSVLineParser\CSVLineparser.h"
#include "ListItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int intDefaultSpace = 15;


using namespace ListReportDefinition;
/////////////////////////////////////////////////////////////////////////////
// CListReport

CListReport::CListReport(int intStyle) : m_intStyle(intStyle)
{
}

CListReport::~CListReport()
{
}


BEGIN_MESSAGE_MAP(CListReport, CListCtrl)
	//{{AFX_MSG_MAP(CListReport)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	////wjf
	//ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	//ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListReport message handlers


void CListReport::PreSubclassWindow() 
{
	CListCtrl::PreSubclassWindow();
	////wjf
	//GetToolTips()->Activate(FALSE);

	return;
}

CListItem * CListReport::FindSelectedItem(CPoint point, int &intRow, int &intColumn)
{
	LVHITTESTINFO hitTestInfo;
	int intColumnCount, intSelectedColumn = -1, intItemType = ItemTypeText;
	CRect rcItem;
	CCSVLineParser csv;
	CListItem *pItem = NULL;

	intRow = -1, intColumn = -1;

	LV_COLUMN lvc;
	::ZeroMemory(&lvc, sizeof(lvc));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;

	hitTestInfo.pt = point;
	if (HitTest(&hitTestInfo) >= 0 && hitTestInfo.iItem >= 0)
	{
		intRow = hitTestInfo.iItem;
		for (intColumnCount=0; GetColumn(intColumnCount, &lvc); intColumnCount++)
		{
			GetSubItemRect(hitTestInfo.iItem, intColumnCount,LVIR_BOUNDS, rcItem);
			if (intColumnCount == 0)
				rcItem.right = GetColumnWidth(0);

			if (rcItem.PtInRect(point))
			{
				intSelectedColumn = intColumnCount;
				break;
			}
		}
		if (intSelectedColumn >= 0
				&& m_vecProperty.size() >= hitTestInfo.iItem 
				&& m_vecProperty[hitTestInfo.iItem].size() >= intSelectedColumn)
		{
			intColumn = intSelectedColumn;

			csv.SetFullString(m_vecProperty[hitTestInfo.iItem][intSelectedColumn]);
			if (csv.size())
				intItemType = atoi(csv.GetAt(0).c_str());


			switch(intItemType)
			{
			case ItemTypeText:
				pItem = new CListItemText(csv.GetFullString());
				break;
			case ItemTypeCheckBox:
				pItem = new CListItemCheckBox(csv.GetFullString());
				break;
			default:
				pItem = NULL;
				break;
			}
		}
	}
	return pItem;
}

void CListReport::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int intRow, intColumn;
	CWnd* pWnd;

	// record clicked point
	m_point = point;
	CListItem *pItem = FindSelectedItem(point, intRow, intColumn);//取得与序号关联的数据

	if (pItem && intRow >= 0 && intColumn >= 0)
		pItem->DbClickItem(this, intRow, intColumn);
	delete pItem;
	CListCtrl::OnLButtonDblClk(nFlags, point);

	// notify parent with user messages
	if (pWnd = GetParent())
		pWnd->PostMessage(WM_LISTREPORT_LBUTTONDBLCLK);
}

void CListReport::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int intRow, intColumn;
	CWnd* pWnd;

	// record clicked point
	m_point = point;
	CListItem *pItem = FindSelectedItem(point, intRow, intColumn);

	if (pItem && intRow >= 0 && intColumn >= 0)
		pItem->ClickItem(this, intRow, intColumn);
	delete pItem;
	CListCtrl::OnLButtonDown(nFlags, point);

	// notify parent with user messages
	if (pWnd = GetParent())
		pWnd->PostMessage(WM_LISTREPORT_LBUTTONDOWN);
}




void CListReport::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
//	struct ITEM_CHECK
//	{
//		int item;                 //第几行
//		int flag;                 //falg 0是空，1是被选中，-1是变灰
//	};
//
// vector<ITEM_CHECK>      m_itemVector;    //保存所有item状态 
////重写InsertItem，每插入一个m_itemVector添加一个。
// int CListCtrlCl::InsertItem(int nItem, LPCTSTR lpszItem)
// m_itemVector.push_back(m_itemCheck);
////自绘的DrawItem函数
//	void CListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDIS)
//	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
//	if (m_itemVector.at(nItem).flag == 0)
//	{
//		pDC->DrawFrameControl(&rt, DFC_BUTTON, DFCS_BUTTONCHECK);
//
//	}
//	else if (m_itemVector.at(nItem).flag == 1)
//	{
//		pDC->DrawFrameControl(&rt, DFC_BUTTON, DFCS_CHECKED);
//	}
//	else
//	{
//		pDC->DrawFrameControl(&rt, DFC_BUTTON, DFCS_INACTIVE);
//	}
//}
//很简单就是用了CDC::DrawFrameControl画出CheckBox的三种不同状态。
	//单击选中通过修改m_itemVector的item状态，来改变绘制的不同状态。
	//void CListCtrlEx : OnLButtonDown(UINT nFlags, CPoint point)

	//GetItemRect(0, tempRect, LVIR_BOUNDS);
	//itemHeight = tempRect.Height();
	//m_Header.GetItemRect(0, headerRect);
	//iItem = (height - headerRect.Height()) / itemHeight;    //减去表头的高度,得到点击的是第几个item
	//GetSubItemRect(iItem, 0, LVIR_LABEL, tempRect);

	//	if (tempRect.PtInRect(point))
	//	{
	//		ITEM_CHECK& itemCheck = m_itemVector.at(iItem);
	//		if (itemCheck.flag == 1)
	//		{
	//			itemCheck.flag = 0;
	//		}
	//		else if (itemCheck.flag == 0)
	//		{
	//			itemCheck.flag = 1;
	//		}
	//		InvalidateRect(tempRect, 0);

	//OnLButtonDown(nFlags, point); //调用单击OnLButtonDown

	CDC dc;
	CRect rcItem, rcCell;
	COLORREF rgbBkgnd=RGB(255,0,0);
	bool bSelected;

	int intColumnCount, intItemType = ItemTypeText;
	CCSVLineParser csv;
	CListItem *pItem;

	dc.Attach(lpDIS->hDC);

	TCHAR  lpBuffer[256];
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_PARAM ;
	lvi.iItem = lpDIS->itemID ; 	
	lvi.iSubItem = 0;
	lvi.pszText = lpBuffer ;
	lvi.cchTextMax = sizeof(lpBuffer);

	LV_COLUMN lvc;
	::ZeroMemory(&lvc, sizeof(lvc));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;


	for (intColumnCount=0; GetColumn(intColumnCount, &lvc); intColumnCount++)
	{
		GetSubItemRect(lpDIS->itemID, intColumnCount,LVIR_BOUNDS, rcCell);
		if (intColumnCount == 0)
		{
			rcItem = rcCell;
			rcCell.right = GetColumnWidth(0);
		}

		if (m_intStyle & intCellSelect)
			bSelected = (rcCell.PtInRect(m_point) == TRUE);
		else
			bSelected = (rcItem.PtInRect(m_point) == TRUE);

		//wjf  COLOR_GRAYTEXT  rgbBkgnd = RGB(255,0,0);
		if (bSelected)
			rgbBkgnd = ::GetSysColor(COLOR_HIGHLIGHT);
		else
			rgbBkgnd = ::GetSysColor(COLOR_WINDOW);
		
		//rgbBkgnd = ::GetSysColor(COLOR_WINDOW);
		CBrush br(rgbBkgnd);
		dc.FillRect(rcCell, &br);

		if( lpDIS->itemID < 0)
			break;

		if (m_vecProperty.size() < lpDIS->itemID 
				|| m_vecProperty[lpDIS->itemID].size() < intColumnCount)
			break;

		csv.SetFullString(m_vecProperty[lpDIS->itemID][intColumnCount]);
		if (csv.size())
			intItemType = atoi(csv.GetAt(0).c_str());

		switch(intItemType)
		{
		case ItemTypeText:
			pItem = new CListItemText(csv.GetFullString());
			break;
		case ItemTypeCheckBox:
			pItem = new CListItemCheckBox(csv.GetFullString());
			break;
		default:
			pItem = NULL;
			break;
		}

		if (pItem)
		{
			lvi.iSubItem = intColumnCount;
			VERIFY(GetItem(&lvi));
			pItem->DrawRect(dc, rcCell, lpBuffer, bSelected);
		}
		delete pItem;
	}
	dc.Detach();  //分离
}

// operations
BOOL CListReport::AddColumn(LPCTSTR strItem,int nItem, int intColumnWidth, int nSubItem, int nMask,int nFmt)
{
	LV_COLUMN lvc;
	lvc.mask = nMask;
	lvc.fmt = nFmt;
	lvc.pszText = (LPTSTR) strItem;
	
	if (intColumnWidth > 0)
		lvc.cx = intColumnWidth;
	else
		lvc.cx = GetStringWidth(lvc.pszText) + intDefaultSpace;
	
	if(nMask & LVCF_SUBITEM)
	{
		if(nSubItem != -1)
			lvc.iSubItem = nSubItem;
		else
			lvc.iSubItem = nItem;
	}
	return InsertColumn(nItem,&lvc);
}

BOOL CListReport::AddItem(int nItem, int nSubItem, LPCTSTR strItem, string sProperty)
{
	LV_ITEM lvItem;
	lvItem.mask = (LVIF_TEXT | LVIF_PARAM);
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR) strItem;
	lvItem.lParam = 0;

	// record property of the sub item.
	if (nItem > m_vecProperty.size() || (nSubItem && nSubItem > m_vecProperty[nItem].size()) )
		return false;
	else if (nItem == m_vecProperty.size())
	{
		vecPropertyItem prop;
		prop.push_back(sProperty);
		m_vecProperty.push_back(prop);
	}
	else if (nSubItem == m_vecProperty[nItem].size())
		m_vecProperty[nItem].push_back(sProperty);
	else
		m_vecProperty[nItem][nSubItem] = sProperty;


	if(nSubItem == 0)
	{
		return InsertItem(&lvItem);
	}
	else
	{
		lvItem.mask &= ~(LVIF_PARAM);
		return SetItem(&lvItem);
	}
}

// helper function, get displayed actual text
LPCTSTR CListReport::MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset)
{
	static const _TCHAR szThreeDots[] = _T("...");

	int nStringLen = lstrlen(lpszLong);

	if(nStringLen == 0 ||
		(pDC->GetTextExtent(lpszLong, nStringLen).cx + nOffset) <= nColumnLen)
	{
		return(lpszLong);
	}

	static _TCHAR szShort[MAX_PATH];

	lstrcpy(szShort,lpszLong);
	int nAddLen = pDC->GetTextExtent(szThreeDots,sizeof(szThreeDots)).cx;

	for(int i = nStringLen-1; i > 0; i--)
	{
		szShort[i] = 0;
		if((pDC->GetTextExtent(szShort, i).cx + nOffset + nAddLen)
			<= nColumnLen)
		{
			break;
		}
	}

	lstrcat(szShort, szThreeDots);
	return(szShort);
}

BOOL CListReport::DeleteItem( int nItem )
{
	int intItemCount;

	if (!CListCtrl::DeleteItem(nItem))
		return FALSE;

	if (nItem < 0 || nItem >= (int)m_vecProperty.size())
		return TRUE;

	for (intItemCount = nItem; intItemCount < (int)m_vecProperty.size()-1; intItemCount++)
		swap(m_vecProperty[intItemCount], m_vecProperty[intItemCount+1]);

	m_vecProperty.pop_back();
	return TRUE;
}

BOOL CListReport::DeleteAllItems()
{
	if (!CListCtrl::DeleteAllItems())
		return FALSE;
	m_vecProperty.clear();
	return TRUE;
}
////wjf
//// CListReport 消息处理程序
//int CListReport::OnToolHitTest(CPoint point, TOOLINFO* pTI) const {
//	//See if the point falls onto a list item
//	//UINT nFlags = 0;
//	LVHITTESTINFO lvhitTestInfo;
//	lvhitTestInfo.pt = point;
//	int nItem = ListView_SubItemHitTest(
//		this->m_hWnd,
//		&lvhitTestInfo);
//	int nSubItem = lvhitTestInfo.iSubItem;
//	UINT nFlags = lvhitTestInfo.flags;
//	//nFlags is 0 if the SubItemHitTest fails
//	//Therefore, 0 & <anything> will equal false
//	if (nFlags & LVHT_ONITEMLABEL) {
//		//If it did fall on a list item,and it was also hit one of the
//		//item specific sub-areas we wish to show tool tips for
//		//Get the client (area occupied by this control
//		//如果它确实落在列表项上，//它也被击中了
//		//我们希望显示工具提示的项目特定子区域
//		//获取客户端(该控件占用的区域
//
//		RECT rcClient;
//		GetClientRect(&rcClient);
//		//Fill in the TOOLINFO structure
//		pTI->hwnd = m_hWnd;
//		pTI->uId = (UINT)(nItem * 100 + nSubItem);
//		pTI->lpszText = LPSTR_TEXTCALLBACK;
//		pTI->rect = rcClient;
//		return pTI->uId; 
//		//By returning a unique value per listItem,we ensure that when the mouse moves over another list item,
//		//the tooltip will change
//	}  //通过为每个列表项返回唯一的值，//我们确保当鼠标移动到另一个列表项上时,工具提示将会更改
//	else {
//		//Otherwise, we aren't interested, so let the message propagate
//		return -1;
//	}
//}
//
//BOOL CListReport::OnToolTipText(UINT id, NMHDR* pNMHDR, LRESULT* pResult) {
//	//VC6.0则用下面这句
//	//_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
//	//VC2003则用这句
//	AFX_MODULE_THREAD_STATE* pThreadState = AfxGetModuleThreadState();
//	CToolTipCtrl* pToolTip = pThreadState->m_pToolTip;
//	pToolTip->SetMaxTipWidth(500);
//
//	//Handle both ANSI and UNICODE versions of the message
//	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
//	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
//
//	if ((pNMHDR->idFrom == (UINT)m_hWnd) &&
//		(((pNMHDR->code == TTN_NEEDTEXTA) && (pTTTA->uFlags & TTF_IDISHWND)) ||
//		((pNMHDR->code == TTN_NEEDTEXTW) && (pTTTW->uFlags & TTF_IDISHWND)))) {
//		return FALSE;
//	}
//	*pResult = 0;
//	//Get the mouse position
//	const MSG* pMessage;
//	pMessage = GetCurrentMessage();
//	ASSERT(pMessage);
//	CPoint pt;
//	pt = pMessage->pt; //Get the point from the message
//	ScreenToClient(&pt);
//
//	LVHITTESTINFO lvhitTestInfo;
//	lvhitTestInfo.pt = pt;
//	int nItem = SubItemHitTest(&lvhitTestInfo);
//	int nSubItem = lvhitTestInfo.iSubItem;
//	UINT nFlags = lvhitTestInfo.flags;
//
//	if (nFlags & LVHT_ONITEMLABEL) {
//		//在这里设置提示信息显示的内容
//	/*	添加提示信息的时候只需要在OnToolTipText函数中if(nFlags & LVHT_ONITEMLABEL)代码块中设置你要显示的值给m_strToolTipText就可以了。这个时候你就可以为不同的单元格显示不同的提示信息，而且提示信息可以为任意多行，提示信息可以使用“\n”分行。
//			这个时候你就可以为不同的单元格显示不同的提示信息，而且提示信息可以为任意多行，提示信息可以使用“\n”分行。
//	*/	
//		m_strToolTipText = GetItemText(nItem, nSubItem) + _T("\nTEST");
//		pTTTA->lpszText = (LPSTR)(LPCSTR)m_strToolTipText;
//		pTTTW->lpszText = (LPWSTR)(LPCTSTR)m_strToolTipText;
//
//		//{{下面为提供提示信息的另外一种方法
//		//   CString strTipText;//提示信息内容
//		//#ifndef _UNICODE
//		//   if (pNMHDR->code == TTN_NEEDTEXTA)
//		//    lstrcpyn(pTTTA->szText, strTipText, 80);
//		//   else
//		//    _mbstowcsz(pTTTW->szText, strTipText, 80);
//		//#else
//		//   if (pNMHDR->code == TTN_NEEDTEXTA)
//		//    _wcstombsz(pTTTA->szText, strTipText, 80);
//		//   else
//		//    lstrcpyn(pTTTW->szText, strTipText, 80);
//		//#endif
//		//}}另外一种提示方法结束
//
//		return FALSE;
//	}
//	return FALSE;
//}