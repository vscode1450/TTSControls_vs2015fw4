#pragma once
//wjf ʹ�÷���:  Owner Draw �� Variable  Has Strings �� True
//CImageList m_imglist1;
//m_listbox1.SetImageList(&m_imglist1);
//�Ի�Ҳ������DrawItem��MeasureItem��ʵ�֡�
// CListBoxCtrlEx 
class CListBoxCtrlEx : public CListBox
{
	DECLARE_DYNAMIC(CListBoxCtrlEx)

public:
	CListBoxCtrlEx();
	virtual ~CListBoxCtrlEx();

protected:
	DECLARE_MESSAGE_MAP()
public:

	// ÿ��Ĺ�������
	typedef struct _ListBox_Data
	{
		CString strAppend;	//�ڶ��Ÿ�������
		LPTSTR	hIcon;		//ͼ��
		_ListBox_Data()
		{
			strAppend = _T("");
			hIcon = NULL;
		}
	} List_AppendData;
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	void InsertStr(CString str, int iIndex, CString strAppend, LPTSTR icon);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


