#pragma once


// CListBoxXI

class CListBoxXI : public CListBox
{
	DECLARE_DYNAMIC(CListBoxXI)

public:
	CListBoxXI();
	virtual ~CListBoxXI();

	void SetImageList(CImageList* pImageList);
	CImageList* GetImageList() const;
	int GetItemImage(int nIndex);
	int SetItemImage(int nIndex, int nImageIndex, BOOL bRepaint = TRUE);

	int AddString(LPCTSTR lpszString, int nImageIndex = -1);
	int DeleteString(UINT nIndex);
	int InsertString(int nIndex, LPCTSTR lpszString, int nImageIndex);
	void ResetContent();

	DWORD_PTR GetItemData(int nIndex) const;
	int SetItemData(int nIndex, DWORD_PTR dwItemData);
	void* GetItemDataPtr(int nIndex) const;
	int SetItemDataPtr(int nIndex, void* pData);

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	DECLARE_MESSAGE_MAP()

private:
	// ������CImageList
	CImageList *m_pImageList;
	CSize      m_imageSize;

	// ÿ��Ĺ�������
	struct LBDataXI
	{
		// ͼ�����,���Ϊ-1,���ʾ��ͼ��
		int iImageIndex;

		// �������ݵ�ָ��
		LPVOID pData;

		LBDataXI()
		{
			iImageIndex = -1;
			pData = NULL;
		}
	};

	// ɾ����������
	void DeleteItemData(int nIndex);
};


