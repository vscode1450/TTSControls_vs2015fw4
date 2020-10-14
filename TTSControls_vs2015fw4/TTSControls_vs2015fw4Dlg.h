
// TTSControls_vs2015fw4Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "MyButton.h"


// CTTSControls_vs2015fw4Dlg 对话框
class CTTSControls_vs2015fw4Dlg : public CDialogEx
{
// 构造
public:
	CTTSControls_vs2015fw4Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TTSCONTROLS_VS2015FW4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBoxCtrlEx m_comboBox;
	CComboBoxCtrlEx1 m_comboBox1;
	CImageList  m_imglist1;
	CEditCtrlTip m_EditCtrlTip;
	CListBoxCtrlEx m_ListBoxCtrlEx;
	CEditCtrlImage m_EditCtrlImage;
	CEditCtrlImage m_EditCtrlImagRight;
	CListReport m_CListCtrlex;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton8();
	CMyButton m_CMyButton;
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	int m_Row;
	afx_msg void OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton9();

	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton12();
};
