#pragma once
//wjf 使用方法:  Owner Draw — Variable  Has Strings — True
//CImageList m_imglist1;
//m_listbox1.SetImageList(&m_imglist1);
//自绘也就是在DrawItem及MeasureItem中实现。
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

	// 每项的关联数据
	typedef struct _ListBox_Data
	{
		CString strAppend;	//第二排附加数据
		LPTSTR	hIcon;		//图标
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


