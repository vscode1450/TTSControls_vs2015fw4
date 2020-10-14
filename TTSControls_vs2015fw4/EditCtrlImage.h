

#pragma once
//#include "Public.h"
//#include <atlimage.h>  
//virtual function ��Ϣ�Ĵ���.(��Ҫ��OnPaint��DrawItem) ��һ���ϵ�����������������Ϣ
//�����˰�ť, ��ʾ������ʱ��, ���Ž�DrawItem
//
#include "EditCtrlTip.h"
////////////////////////////////////////////////////////////////////////
#define TRANS_BACK RGB(255,0,0)
#define DEFAULT_COLOR RGB(40,138,228)

///////////////////////////////////////////////////////////////////////
class CEditCtrlImage :
	public CStatic
{
public:
	CEditCtrlImage();
	~CEditCtrlImage();

public:
	// ��ʼ��,��������ͼ�꣬ ���ͼ�꣬�Ҳ�ͼ�꣬Բ�ǣ��ھ� 
	void Init(BOOL leftright, HICON left_icon, HICON right_icon, int radian = 0, int padding = 0);
	// �����ڿ����������ɫ
	void setNormalColor(COLORREF inColor, COLORREF outColor, COLORREF textColor = RGB(0, 0, 0));
public:
	BOOL    m_bTracking;
	BOOL    m_bHover;

	//GDI + ��Ҫʹ��Image��
	//Image* m_left_icon;  
	//Image* m_right_icon;

	HICON   m_left_icon;
	HICON   m_right_icon;
	int		m_radian = 3;
	int		m_padding = 2;
	BOOL    m_leftright = true;

	COLORREF m_normal_in_color;
	COLORREF m_normal_out_color;
	COLORREF m_default_color = RGB(255, 0, 0); //red
	COLORREF m_trans_back_color = RGB(40, 138, 228);//��ɫ
	COLORREF m_text_color = RGB(0, 0, 0);//��ɫ
	//CEdit m_edit;
	CEditCtrlTip m_edit;

protected:
	//WM_NCPAINT�����ڿͻ�������Ĳ��֣��細�ڱ��������˵����ȣ���Ҫ�ػ�ʱ��ϵͳ����򷢳�����Ϣ��
	//WM_PAINTӦ�ó���ͨ���������Ϣʵ���ڴ����ϵĻ��ƹ�����
	//WM_ERASEBKGND��Ϣ���ػ�����

	void OnNcPaint();
	void OnPaint();
	//DEClARE_DYNCREATE / IMPLEMENT_DYNCREATE��Ϊ�ˡ���̬����"���ʵ��������ĺꡣnew���������������󣬵����Ƕ�̬�ġ�
	//DECLARE_DYNAMIC(CEditCtrlImage)

	DECLARE_DYNAMIC(CEditCtrlImage)
	DECLARE_MESSAGE_MAP()
	//PreSubclassWindow����CWnd::SubclassWindow�е��õģ���Ŀ������������ڶ�̬���໯�ؼ��򴰿�֮ǰ��һЩ��������Ҫ�Ķ���
	virtual void PreSubclassWindow();
	//�����ػ���
	//MFC CStatic�ؼ���DrawItem���Ի�
    //ȷ����Ϣӳ���в����У�ON_WM_PAINT��Ҳ����ֱ����OnPaint�л��ƣ���ON_WM_DRAWITEM ��Ϣ������DrawItem�������ᱻ����
    //ע���ڶ�������DrawItem����OnDrawItem��OnDrawItem��ON_WM_DRAWITEM��Ϣ�Ĵ��������Ǵ����ӿؼ����͹������Ի���Ϣ��

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void DrawBorder(CDC* dc, CRect& rc);
	//GDI + Image���ͼ ��CImage�࣬��ͷ�ļ�#include "atlimage.h"�Ϳ�����
	//Image* ImageFromResource(HINSTANCE hInstance, UINT uImgID, LPCTSTR lpType);
};

