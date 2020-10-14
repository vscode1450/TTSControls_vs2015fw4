//----------------------------------------------------------------------------
//模块:位图选择器 描述:类CBitmapPickerCombo的声明
//@基本公共| CComboBox 从中选择位图的组合框 public | CComboBox 
// 1。在项目中包括CBitmapPickerCombo.cpp和CBitmapPickerCombo.h
// 2。在资源编辑器中创建一个常规组合框，其中至少包含//以下样式:下拉列表、所有者原始变量、有字符串
// 3。在VC的类向导中为组合框创建一个控件成员变量
// 4。在对话框中用CBitmapPickerCombo替换CComboBox。h文件
// 5。在对话框中使用添加位图或插入位图成员函数向组合框添加位图(和字符串)
//----------------------------------------------------------------------------

#if !defined(AFX_CBITMAPPICKERCOMBO_H__8AAE34F7_7B02_11D3_A615_0060085FE616__INCLUDED_)
#define AFX_CBITMAPPICKERCOMBO_H__8AAE34F7_7B02_11D3_A615_0060085FE616__INCLUDED_

#include "BitmapKeyed.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000 


class CBitmapPickerCombo : public CComboBox
{
  // @access Public Member Functions and Variables
public:

  // @cmember
  // constructor
  CBitmapPickerCombo();

  // @cmember,mfunc
  // destructor
  virtual ~CBitmapPickerCombo() {}

  // @cmember
  // adds bitmap (and string) item to combobox
  int AddBitmap(const CBitmapKeyed *bitmap, const char *string = NULL);

  // @cmember
  // adds bitmap (and string) item to combobox at specified index
  int InsertBitmap(int nIndex, const CBitmapKeyed *bitmap, const char *string = NULL);

  // @access Protected Member Functions and Variables
protected:

  // @cmember
  // Called by MFC when visual aspect of combo box changes 
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

  // @cmember
  // Called by MFC when combo box is created
  virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);

  // @cmember,mfunc
  // strings cannot be added
  virtual int AddString(LPCTSTR lpszString) { return -1; }

  // @cmember,mfunc
  // strings cannot be added
  virtual int InsertString(int nIndex, LPCTSTR lpszString) { return -1; }

  // @cmember,mfunc
  // strings cannot be deleted
  //virtual int DeleteString(int nIndex) { return -1; }

#ifdef _DEBUG
  // @cmember,mfunc
  // for assertion only
  virtual void PreSubclassWindow();
#endif

// @access Private Member Functions and Variables
private:

  int m_nItemWidth, m_nItemHeight; // @cmember size of items

  // @cmember
  // draws bitmap (and string) in item
  void OutputBitmap(LPDRAWITEMSTRUCT lpDIS, bool selected);

  // @cmember
  // sets overall item size
  void SetSize(int width, int height);

  /*void DrawDimText(void);

  DECLARE_MESSAGE_MAP();

  afx_msg BOOL OnEraseBkgnd(CDC* pDC);*/
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBITMAPPICKERCOMBO_H__8AAE34F7_7B02_11D3_A615_0060085FE616__INCLUDED_)
