#pragma once

// ComboBoxCtrlEx1.h
class CComboBoxCtrlEx1 : public CComboBox
{
	DECLARE_DYNAMIC(CComboBoxCtrlEx1)

public:
	CComboBoxCtrlEx1();
	virtual ~CComboBoxCtrlEx1();

	//�ṩ�Ľӿ�
	//---------------------------------------------------------
	    // ����: SetImageList
		// ����: ���ù�����ImageList
		// ����:  pImageList --- ImageList��ָ��
		// ����: ��
	//---------------------------------------------------------
	void SetImageList(CImageList* pImageList);
	//---------------------------------------------------------
    // ����: GetImageList
    // ����: ��ȡ����ImageList��ָ��
    // ����: ��
    // ����: ����ImageList��ָ��,��û�й���ImageList����NULL
    //---------------------------------------------------------
	CImageList* GetImageList() const;

	//---------------------------------------------------------
    // ����: GetItemImage
    // ����: ��ȡ���ͼƬ����
    // ����: 
    //       nIndex  --- ������(��0Ϊ���)
    // ����:
    //       ��0Ϊ��ʼ��ͼƬ�������
    //       �����ڴ���,��nIndex������Χ,����-1
    //       ����û�й���ͼƬ,����-1
   //---------------------------------------------------------
	int GetItemImage(int nIndex);

	//---------------------------------------------------------
    // ����: SetItemImage
    // ����: �������ͼƬ����
    // ����: 
    //       nIndex      --- ������(��0Ϊ���)
    //       nImageIndex --- ͼƬ����(��0Ϊ���)
    //       bRepaint    --- �Ƿ��ػ�
    // ����:
    //       �ɹ�����0,ʧ�ܷ���-1
    //---------------------------------------------------------

	int SetItemImage(int nIndex, int nImageIndex, BOOL bRepaint = TRUE);


	//---------------------------------------------------------
    // ����: AddString
   // ����: �����
   // ����: lpszString  --- �ַ���ָ��
   //        nImageIndex --- ͼƬ����(��0Ϊ���)
   // ����: �����������ֵ
   //        ʧ���򷵻�LB_ERR��LB_ERRSPACE
   //---------------------------------------------------------

	int AddString(LPCTSTR lpszString, int nImageIndex = -1);
	int DeleteString(UINT nIndex);
	//---------------------------------------------------------
	// ����: InsertString
	// ����: ��ָ��λ�ò�����
	// ����: 
	//       nIndex      --- ָ��λ��
	//       lpszString  --- �ַ���ָ��
	//       nImageIndex --- ͼƬ����(��0Ϊ���)
	// ����: 
	//       ����������ֵ
	//       ʧ���򷵻�LB_ERR��LB_ERRSPACE
	//---------------------------------------------------------

	int InsertString(int nIndex, LPCTSTR lpszString, int nImageIndex);
	void ResetContent();

	DWORD_PTR GetItemData(int nIndex) const;
	//---------------------------------------------------------
    // ����: SetItemData
    // ����: ���������������
    // ����:
    //       nIndex     --- ����
    //       dwItemData --- ���������� 
    // ����:
    //       �ɹ�����LB_OKAY, ʧ�ܷ���LB_ERR
    //---------------------------------------------------------

	int SetItemData(int nIndex, DWORD_PTR dwItemData);
	void* GetItemDataPtr(int nIndex) const;
	int SetItemDataPtr(int nIndex, void* pData);


protected:
	//��ӦDrawItem(����ӦMeasureItem)����ӦMeasureItem(��ȻҲ��ӦDrawItem).
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	DECLARE_MESSAGE_MAP()

private:
	// ������CImageList
	CImageList* m_pImageList;
	CSize      m_imageSize;

	// EditCtrl�ĸ߶�
	unsigned int  m_nEditHeight;

	// �Ƿ���DropList:ֻ��DropList����EditCtrl�ĸ߶�,��DropDown��Simple�����Ĭ�ϸ߶�
	// -1(����,δ���), 1(Yes), 0(No)
	int m_iIsDropList;

	struct CBDataXI
	{
		// ͼ�����,���Ϊ-1,���ʾ��ͼ��
		int iImageIndex;
		// �������ݵ�ָ�� 
		LPVOID pData;
		CBDataXI()
		{
			iImageIndex = -1;
			pData = NULL;
		}
	};

	void DeleteItemData(int nIndex);
};


