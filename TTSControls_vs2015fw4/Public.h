#pragma once  
//����͸��ͼƬ�Ĵ��������CImage���GDI+��Ҫ���ؿ⣬��CImage��ͷ�ļ�#include "atlimage.h"�Ϳ�����
//GDI + ��Ҫʹ��Image�� CImage����΢�� MFC-�Ի�ؼ���CButtonƪ��
//#include "stdafx.h" 

////����͸��ͼƬ
//CImage Image;
//Image.Load("./img/HandOk.png");
//if (Image.IsNull())
//{
//	MessageBox(0, "����HandOk.pngʧ��", 0, 0);
//	return;
//}

//#include "d:\GDIPlus\includes\gdiplus.h"   ////���޸�Ϊ���ͷ�ļ�·��
//using namespace Gdiplus;
//#pragma comment(lib, "d:\\GDIPlus\\lib\\gdiplus.lib") 

#include "stdafx.h"
#include <atlimage.h>  
#include "gdiplus.h"  
#pragma comment(lib, "gdiplus.lib") 

using namespace Gdiplus;
//��ť��״̬  
enum
{
	CTRL_NOFOCUS = 0x01,            //��ͨ  
	CTRL_FOCUS,                     //mousemove  
	CTRL_SELECTED,                  //buttondown  
	CTRL_DISABLE,                   //��Ч  
};

//ͼƬ��ʽ  
enum
{
	BTN_IMG_1 = 1,                  //  
	BTN_IMG_3 = 3,                  //3��ͼ��1��ͼƬ����3Сͼ����ͬ��  
	BTN_IMG_4 = 4,                  //4��ͼ  
};

//��ť����  
enum
{
	BTN_TYPE_NORMAL = 0x10,         //��ͨBTN  
	BTN_TYPE_MENU,                  //�˵����͵�BTN  
	BTN_TYPE_STATIC,                //��̬���͵�BTN  
};

//ͼƬ�ڳ�������ʱ��Ҫ������ͨ��ʹ�õ�һ������Load(LPCTSTR pszFileName)����ͼƬ
//�Ǵ���Դ��ȡ��ͼƬ��Ϣ��ÿһ�������ǰ����д�����ͼƬ��ģ��ʵ��������ڶ�����������Դ��ID�����ơ�
//const char*
//HRESULT Load(LPCTSTR pszFileName) throw();
//HRESULT Load(IStream* pStream) throw();
//void LoadFromResource(HINSTANCE hInstance, LPCTSTR pszResourceName) throw();
//void LoadFromResource(HINSTANCE hInstance, UINT nIDResource) throw();

//����Դ�������λͼ  
bool LoadImageFromResourse(CImage* pImg, UINT nImgID, LPCTSTR lpImgType);
bool LoadPicture(CImage& bmp, UINT nImgID, LPCTSTR lpImgType = _T("PNG"));
