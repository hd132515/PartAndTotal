
// TeilUndAlles.h : TeilUndAlles ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CTeilUndAllesApp:
// �� Ŭ������ ������ ���ؼ��� TeilUndAlles.cpp�� �����Ͻʽÿ�.
//

class CTeilUndAllesApp : public CWinAppEx
{
public:
	CTeilUndAllesApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTeilUndAllesApp theApp;
