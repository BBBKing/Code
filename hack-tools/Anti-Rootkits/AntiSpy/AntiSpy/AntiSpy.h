
// AntiSpy.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAntiSpyApp:
// �йش����ʵ�֣������ AntiSpy.cpp
//

class CAntiSpyApp : public CWinApp
{
public:
	CAntiSpyApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAntiSpyApp theApp;