#pragma once

#include <vector>
using std::vector;

//控件属性必须为四个条件缺一不可Owner Drawer : Variable,Has Strings : False;Type:Drop List;Sort:False;要选择他,就得要响应CompareItem消息
// CComboBoxCtrlEx.h  控件属性必须为Owner Drawer : Variable,Has Strings : False;Type:Drop List;Sort:False;四个条件缺一不可
//Owner Draw属性:这个属性有三个选项:No(不响应DrawItem),
//Fixed(固定属性的列表高度和宽度), 响应DrawItem(不响应MeasureItem)
//Variable(改变列表的高度和宽度).响应MeasureItem(当然也响应DrawItem).
//Type属性:Simple(简单的, 也就是相当于CEdit)、
//Dropdown(相当于前面说的三个控件)和
//DropList(可以理解成是只读的CEdit + CButton + CListBox)

//数据的传递结构   结构体保存从主界面传给控件的数据的.
// 关联的CImageList
typedef struct  tagITEMLIST
{
	HICON hIcon;		//图标
	CString strUrl;		//Url地址
	CString strTitle;	//标题(Url官网名称)
	COLORREF clrLeft;	//左边文本的颜色
	COLORREF clrRight;	//右边文本的颜色
	UINT     iItem;		//ID 号
}ItemList, * PItemList;


class CComboBoxCtrlEx : public CComboBox
{
	DECLARE_DYNAMIC(CComboBoxCtrlEx)

public:
	CComboBoxCtrlEx();
	virtual ~CComboBoxCtrlEx();
	//vector方便扩充数据
	vector<ItemList*>	m_vecItemList;
	typedef vector<ItemList*>::iterator IterItem;
public:
	//member function
	//wjf(初始化数据)到这个控件上 否则
	//PItemList pItem = m_vecItemList[itemID];  将一个无效参数传递给了将无效参数视为严重错误的函数”。
	void InitControl(void);

	//virtual function 消息的处理.(主要是OnPaint和DrawItem) 打一个断点怎样触发这两个消息
	virtual void    MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	//wjf 单击了按钮显示下拉的时候, 它才进DrawItem
	virtual void	DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//command function
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//鼠标离开消息
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	//wjf当需要刷新非下拉区域时进入OnPaint.
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchange();

	DECLARE_MESSAGE_MAP()
private:
	void	UpdateRect(void);
	//wjf 初始化时进入
	void    OnNcPaint(CDC* pDC);
	void    DrawContent(UINT iState, CRect rcClient, CDC* pDC, int itemID);

	BOOL	m_bOver;
	CBrush* m_pBrsh;
	CPen	m_bgPen;
	CBrush* m_bgBrush;
	BOOL	m_bDown;
	CFont	m_font;

	int		m_selItem;	    //select item flags
	BOOL	m_bFous;	    //over fous
	int		m_preSelItem;	//pre select item flags

};


