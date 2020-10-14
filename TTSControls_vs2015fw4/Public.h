#pragma once  
//对于透明图片的处理可以用CImage类和GDI+需要加载库，用CImage类头文件#include "atlimage.h"就可以了
//GDI + 主要使用Image类 CImage则是微软 MFC-自绘控件（CButton篇）
//#include "stdafx.h" 

////加载透明图片
//CImage Image;
//Image.Load("./img/HandOk.png");
//if (Image.IsNull())
//{
//	MessageBox(0, "加载HandOk.png失败", 0, 0);
//	return;
//}

//#include "d:\GDIPlus\includes\gdiplus.h"   ////请修改为你的头文件路径
//using namespace Gdiplus;
//#pragma comment(lib, "d:\\GDIPlus\\lib\\gdiplus.lib") 

#include "stdafx.h"
#include <atlimage.h>  
#include "gdiplus.h"  
#pragma comment(lib, "gdiplus.lib") 

using namespace Gdiplus;
//按钮的状态  
enum
{
	CTRL_NOFOCUS = 0x01,            //普通  
	CTRL_FOCUS,                     //mousemove  
	CTRL_SELECTED,                  //buttondown  
	CTRL_DISABLE,                   //无效  
};

//图片形式  
enum
{
	BTN_IMG_1 = 1,                  //  
	BTN_IMG_3 = 3,                  //3分图（1个图片内有3小图，下同）  
	BTN_IMG_4 = 4,                  //4分图  
};

//按钮类型  
enum
{
	BTN_TYPE_NORMAL = 0x10,         //普通BTN  
	BTN_TYPE_MENU,                  //菜单类型的BTN  
	BTN_TYPE_STATIC,                //静态类型的BTN  
};

//图片在程序运行时需要更换则通常使用第一个函数Load(LPCTSTR pszFileName)载入图片
//是从资源中取得图片信息，每一个参数是包含有待载入图片的模块实例句柄，第二个参数是资源的ID或名称。
//const char*
//HRESULT Load(LPCTSTR pszFileName) throw();
//HRESULT Load(IStream* pStream) throw();
//void LoadFromResource(HINSTANCE hInstance, LPCTSTR pszResourceName) throw();
//void LoadFromResource(HINSTANCE hInstance, UINT nIDResource) throw();

//从资源里面加载位图  
bool LoadImageFromResourse(CImage* pImg, UINT nImgID, LPCTSTR lpImgType);
bool LoadPicture(CImage& bmp, UINT nImgID, LPCTSTR lpImgType = _T("PNG"));
