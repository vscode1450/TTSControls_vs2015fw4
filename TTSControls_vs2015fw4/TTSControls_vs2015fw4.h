
// TTSControls_vs2015fw4.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTTSControls_vs2015fw4App: 
// �йش����ʵ�֣������ TTSControls_vs2015fw4.cpp
//

class CTTSControls_vs2015fw4App : public CWinApp
{
public:
	CTTSControls_vs2015fw4App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTTSControls_vs2015fw4App theApp;