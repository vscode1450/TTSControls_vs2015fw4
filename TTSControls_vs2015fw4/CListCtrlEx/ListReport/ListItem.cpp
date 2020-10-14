// ListItem.cpp: implementation of the CListItem class.
//��������item״̬ 
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
	//rect.top/bottom/left/right�ֱ��¼������Ϣ,rect.height/width�ֱ��¼����
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

	//����   �����Ͻǿ�ʼ��+һ������ߣ��߶�Ϊ�ߵĿ�ȣ���ɵ�б��
	if (atoi(sText.c_str()))
	{
		//draw the check mark  XHeaderCtrl.cpp 
		//wjf �Ժ�ƫ������
		int x = chkboxrect.left + 13;//9
		ASSERT(x < chkboxrect.right);
		int y = chkboxrect.top + 4;//3 y����Խ�󣬴�ֱ����ͼ��Խ�� + 9ͼ����+4//һ��ԭ��������Ļ���Ͻǵ�λ�á�
		//���������Ͻ�+9=���Ͻ�
		int i;
		//x- y+ �����½�
		for (i = 0; i <6; i++)
		{
			//һ��ԭ��������Ļ���Ͻǵ�λ�á�
			//x��X���λ�ã�ˮƽ����
			//y��Y���λ�ã���ֱ����
			
			dc.MoveTo(x, y);    //���ʶ�λ �ı䵱ǰ���λ��
			//ˮƽ���䴹ֱ�������ӻ���=б�� +3Ϊ�ߵĿ��
			dc.LineTo(x, y+2);  //��һ���ɵ�ǰ�㵽����ָ�������   //��(x, y)��(x, y+3)���ϻ�һ��ֱ��.

		//����Ϊ�������Ͻǿ�ʼ->�����½�  ���ұ߳� 
			x--; //ˮƽ�������
			y++; //��ֱ��������
		}
	/*	x- y-�����Ͻ�*/
		for (i = 0; i <4; i++)
		{
			dc.MoveTo(x, y); //���ʶ�λ  �ı䵱ǰ���λ��
			//ˮƽ���䴹ֱ�������ӻ���=б�� +3Ϊ�ߵĿ��
			dc.LineTo(x, y+2);  //��(x, y)��(x, y+3)���ϻ�һ��ֱ��.
			//����Ϊ���ӵײ���ʼ->�����Ͻ� ����߶� 
			x--;
			y--;
		}
	}
}

////����������С���ǣ�wjf ʵ�ĵ�����С���ǣ�
//int w = 7;
//int h = 4;
//int x = nWindth - w - 7;
//int y = (nHeight - h) / 2;
//for (int i = 0; i<h; i++) { //iΪ0-3
//	MoveToEx(hDC, x, y, NULL);
//	//y���䣬x�ڱ䣬��ˮƽ�����ɵ��̻���
//	LineTo(hDC, x + w, y);
//	//����Ϊ�������½�
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
