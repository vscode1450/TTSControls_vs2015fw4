#pragma once
#include "afxwin.h"
class CMyButton :
	public CButton
{
public:
	CMyButton();
	~CMyButton();

private:
	int          m_Style;     //��ť��״��0-������1-��ǰ��2-���£�3-������
	BOOL         b_InRect;            //�������־
	CString      m_strText;           //��ť����
	COLORREF     m_ForeColor;         //�ı���ɫ
	COLORREF     m_BackColor;         //����ɫ
	COLORREF     m_LockForeColor;     //������ť��������ɫ
	CRect        m_ButRect;           //��ť�ߴ�
	CFont*       p_Font;              //����

	void   DrawButton(CDC *pDC);      //�������İ�ť

									  // �ӿں���
public:
	void SetText(CString str);
	void SetForeColor(COLORREF color);       //�����ı���ɫ
	void SetBkColor(COLORREF color);         //���ñ�����ɫ
	void SetTextFont(int FontHight, LPCTSTR FontName);    //�������� 
	
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


