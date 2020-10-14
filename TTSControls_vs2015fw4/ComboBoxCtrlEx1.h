#pragma once

// ComboBoxCtrlEx1.h
class CComboBoxCtrlEx1 : public CComboBox
{
	DECLARE_DYNAMIC(CComboBoxCtrlEx1)

public:
	CComboBoxCtrlEx1();
	virtual ~CComboBoxCtrlEx1();

	//提供的接口
	//---------------------------------------------------------
	    // 函数: SetImageList
		// 功能: 设置关联的ImageList
		// 参数:  pImageList --- ImageList的指针
		// 返回: 无
	//---------------------------------------------------------
	void SetImageList(CImageList* pImageList);
	//---------------------------------------------------------
    // 函数: GetImageList
    // 功能: 获取关联ImageList的指针
    // 参数: 无
    // 返回: 关联ImageList的指针,若没有关联ImageList返回NULL
    //---------------------------------------------------------
	CImageList* GetImageList() const;

	//---------------------------------------------------------
    // 函数: GetItemImage
    // 功能: 获取项的图片索引
    // 参数: 
    //       nIndex  --- 项索引(以0为起点)
    // 返回:
    //       以0为起始的图片索引序号
    //       若存在错误,如nIndex超出范围,返回-1
    //       若项没有关联图片,返回-1
   //---------------------------------------------------------
	int GetItemImage(int nIndex);

	//---------------------------------------------------------
    // 函数: SetItemImage
    // 功能: 设置项的图片索引
    // 参数: 
    //       nIndex      --- 项索引(以0为起点)
    //       nImageIndex --- 图片索引(以0为起点)
    //       bRepaint    --- 是否重绘
    // 返回:
    //       成功返回0,失败返回-1
    //---------------------------------------------------------

	int SetItemImage(int nIndex, int nImageIndex, BOOL bRepaint = TRUE);


	//---------------------------------------------------------
    // 函数: AddString
   // 功能: 添加项
   // 参数: lpszString  --- 字符串指针
   //        nImageIndex --- 图片索引(以0为起点)
   // 返回: 新增项的索引值
   //        失败则返回LB_ERR或LB_ERRSPACE
   //---------------------------------------------------------

	int AddString(LPCTSTR lpszString, int nImageIndex = -1);
	int DeleteString(UINT nIndex);
	//---------------------------------------------------------
	// 函数: InsertString
	// 功能: 在指定位置插入项
	// 参数: 
	//       nIndex      --- 指定位置
	//       lpszString  --- 字符串指针
	//       nImageIndex --- 图片索引(以0为起点)
	// 返回: 
	//       插入项索引值
	//       失败则返回LB_ERR或LB_ERRSPACE
	//---------------------------------------------------------

	int InsertString(int nIndex, LPCTSTR lpszString, int nImageIndex);
	void ResetContent();

	DWORD_PTR GetItemData(int nIndex) const;
	//---------------------------------------------------------
    // 函数: SetItemData
    // 功能: 设置项关联的数据
    // 参数:
    //       nIndex     --- 索引
    //       dwItemData --- 关联的数据 
    // 返回:
    //       成功返回LB_OKAY, 失败返回LB_ERR
    //---------------------------------------------------------

	int SetItemData(int nIndex, DWORD_PTR dwItemData);
	void* GetItemDataPtr(int nIndex) const;
	int SetItemDataPtr(int nIndex, void* pData);


protected:
	//响应DrawItem(不响应MeasureItem)、响应MeasureItem(当然也响应DrawItem).
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	DECLARE_MESSAGE_MAP()

private:
	// 关联的CImageList
	CImageList* m_pImageList;
	CSize      m_imageSize;

	// EditCtrl的高度
	unsigned int  m_nEditHeight;

	// 是否是DropList:只对DropList设置EditCtrl的高度,对DropDown和Simple则采用默认高度
	// -1(待定,未检测), 1(Yes), 0(No)
	int m_iIsDropList;

	struct CBDataXI
	{
		// 图像序号,如果为-1,则表示无图像
		int iImageIndex;
		// 关联数据的指针 
		LPVOID pData;
		CBDataXI()
		{
			iImageIndex = -1;
			pData = NULL;
		}
	};

	void DeleteItemData(int nIndex);
};


