// ListItem.cpp: implementation of the CListItem class.
//保存所有item状态 
//////////////////////////////////////////////////////////////////////


#include "../..//stdafx.h"
#include <sstream>

#include "ListItem.h"
#include "..\CSVLineParser\CSVLineparser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// begin class CListItemText
//////////////////////////////////////////////////////////////////////
CListItemText::CListItemText(string sProperty)
	: CListItem(sProperty)
	, m_bBold(false)
	, m_colorText(::GetSysColor(COLOR_WINDOWTEXT))

{
	CCSVLineParser csv(sProperty);

	if ((int)csv.size() == 3)
	{
		m_bBold = (csv.GetAt(1) != "0");
		m_colorText = atoi(csv.GetAt(2).c_str());
	}
}

string CListItemText::GenerateProperty(bool bBold, COLORREF color)
{
	CCSVLineParser csv;
	stringstream ss;

	ss << ItemTypeText;
	csv.SetAt(0, ss.str()); // item type first
	csv.SetAt(1, bBold ? string("1") : string("0"));
	ss.str("");
	ss << color;
	csv.SetAt(2, ss.str());

	return csv.GetFullString();
}

void CListItemText::DrawRect(CDC &dc, CRect rcItem, string sText, bool bSelected)
{
	COLORREF rgbBkgnd = ::GetSysColor(bSelected ? COLOR_HIGHLIGHT : COLOR_WINDOW)
		, rgbText = m_colorText; 
	CFont *pOldFont = NULL;
	CFont fontObj;
	if (m_bBold)
	{
		fontObj.CreateFont(
			rcItem.bottom-rcItem.top,  // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_BOLD,		           // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial");
		pOldFont = dc.SelectObject(&fontObj);
	}

	dc.SetBkColor(rgbBkgnd);
	dc.SetTextColor(rgbText);
	LPCSTR pszText = CListReport::MakeShortString(&dc, sText.c_str(), rcItem.right-rcItem.left, 2*intBorder);
	dc.TextOut(rcItem.left + intBorder, rcItem.top + intBorder, pszText);

	if (m_bBold)
	{
		dc.SelectObject(pOldFont);
		fontObj.DeleteObject();
	}
}

//////////////////////////////////////////////////////////////////////
// end of class CListItemText
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// begin class CListItemCheckBox
//////////////////////////////////////////////////////////////////////
CListItemCheckBox::CListItemCheckBox(string sProperty)
	: CListItem(sProperty)
{
}

string CListItemCheckBox::GenerateProperty()
{
	CCSVLineParser csv;
	stringstream ss;

	ss << ItemTypeCheckBox;
	csv.SetAt(0, ss.str()); // item type first
	return csv.GetFullString();
}

void CListItemCheckBox::DrawRect(CDC &dc, CRect rcItem, string sText, bool bSelected)
{
	//rect.top/bottom/left/right分别记录坐标信息,rect.height/width分别记录长宽
	CRect chkboxrect;
	chkboxrect = rcItem;
	chkboxrect.bottom -= 1;
	chkboxrect.left += 9;		// line up checkbox with header checkbox
	chkboxrect.right = chkboxrect.left + chkboxrect.Height();	// width = height

	// center the checkbox
	chkboxrect.left = rcItem.left + rcItem.Width()/2 - chkboxrect.Height()/2 - 1;
	chkboxrect.right = chkboxrect.left + chkboxrect.Height();

	// draw border
	dc.DrawEdge(&chkboxrect, EDGE_SUNKEN, BF_RECT);

	//画勾   从右上角开始画+一组短竖线（高度为线的宽度）组成的斜线
	if (atoi(sText.c_str()))
	{
		//draw the check mark  XHeaderCtrl.cpp 
		//wjf 对号偏左下了
		int x = chkboxrect.left + 13;//9
		ASSERT(x < chkboxrect.right);
		int y = chkboxrect.top + 4;//3 y坐标越大，垂直方向图形越低 + 9图低于+4//一般原点是在屏幕左上角的位置。
		//坐标在左上角+9=右上角
		int i;
		//x- y+ 向左下角
		for (i = 0; i <6; i++)
		{
			//一般原点是在屏幕左上角的位置。
			//x是X轴的位置，水平方向，
			//y是Y轴的位置，垂直方向。
			
			dc.MoveTo(x, y);    //画笔定位 改变当前点的位置
			//水平不变垂直方向增加划线=斜线 +3为线的宽度
			dc.LineTo(x, y+2);  //画一条由当前点到参数指定点的线   //从(x, y)到(x, y+3)向上画一条直线.

		//方向为：从右上角开始->向左下角  勾右边长 
			x--; //水平方向减少
			y++; //垂直方向增加
		}
	/*	x- y-向左上角*/
		for (i = 0; i <4; i++)
		{
			dc.MoveTo(x, y); //画笔定位  改变当前点的位置
			//水平不变垂直方向增加划线=斜线 +3为线的宽度
			dc.LineTo(x, y+2);  //从(x, y)到(x, y+3)向上画一条直线.
			//方向为：从底部开始->向左上角 勾左边短 
			x--;
			y--;
		}
	}
}

////画出下拉的小三角（wjf 实心的向下小三角）
//int w = 7;
//int h = 4;
//int x = nWindth - w - 7;
//int y = (nHeight - h) / 2;
//for (int i = 0; i<h; i++) { //i为0-3
//	MoveToEx(hDC, x, y, NULL);
//	//y不变，x在变，即水平方向由到短划线
//	LineTo(hDC, x + w, y);
//	//方向为：向右下角
//	x++;
//	y++;
//	w = w - 2;

void CListItemCheckBox::ClickItem(CListReport *pParent, int intRow, int intColumn)
{
	ASSERT(pParent);
	if (intRow < 0 && intColumn < 0)
		return;

	bool bCheck = pParent->GetItemText(intRow, intColumn) == "1";
	pParent->SetItemText(intRow, intColumn, bCheck ? "0":"1");
}
//////////////////////////////////////////////////////////////////////
// end of class CListItemCheckBox
//////////////////////////////////////////////////////////////////////
