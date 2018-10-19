// zkbhShow.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "zkbhShow.h"
#include "mainFrame.h"
CComModule _Module;


void InitResource()
{
	// ��Դ����
#ifdef _DEBUG
	CPaintManagerUI::SetResourceType(UILIB_FILE);
#else
	CPaintManagerUI::SetResourceType(UILIB_ZIPRESOURCE);
#endif
	// ��Դ·��
	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
	// ������Դ
	switch(CPaintManagerUI::GetResourceType())
	{
	case UILIB_FILE:
		{
			strResourcePath += _T("skin\\");
			CPaintManagerUI::SetResourcePath(strResourcePath.GetData());

			break;
		}
	case UILIB_RESOURCE:
		{
			strResourcePath += _T("skin\\");
			CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
			// ������Դ������
			CResourceManager::GetInstance()->LoadResource(_T("IDR_RES"), _T("xml"));
			break;
		}
	case UILIB_ZIP:
		{
			strResourcePath += _T("skin\\");
			CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
			// ����
			CPaintManagerUI::SetResourceZip(_T("pwRes.zip"), true, _T("duilib_ultimate"));
			break;
		}
	case UILIB_ZIPRESOURCE:
		{
			strResourcePath += _T("skin\\");
			CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
			HRSRC hResource = ::FindResource(CPaintManagerUI::GetResourceDll(), _T("IDR_ZIPRES"), _T("ZIPRES"));
			if( hResource != NULL ) {
				DWORD dwSize = 0;
				HGLOBAL hGlobal = ::LoadResource(CPaintManagerUI::GetResourceDll(), hResource);
				if( hGlobal != NULL ) {
					dwSize = ::SizeofResource(CPaintManagerUI::GetResourceDll(), hResource);
					if( dwSize > 0 ) {
						CPaintManagerUI::SetResourceZip((LPBYTE)::LockResource(hGlobal), dwSize);
					}
				}
				::FreeResource(hResource);
			}
		}
		break;
	}

	// ע��ؼ�
	//REGIST_DUICONTROL(CCircleProgressUI);
	//REGIST_DUICONTROL(CMyComboUI);
	//REGIST_DUICONTROL(CChartViewUI);
	//REGIST_DUICONTROL(CWndUI);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	TCHAR strAppName[] = _T("x-pwshow");
	HANDLE hMutex = NULL;
	//�����������
	hMutex = CreateMutex(NULL, FALSE, strAppName);

	if (hMutex != NULL)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			MessageBox(NULL, TEXT("����һ������������"), TEXT("��Ϣ"), MB_OK | MB_ICONINFORMATION);	//�رջ�������˳�����

			CloseHandle(hMutex);
			return (-1);
		} 
	}
	else
	{
		MessageBox(NULL, TEXT("�޷������������"), TEXT("��Ϣ"), MB_OK | MB_ICONINFORMATION);
	}


	CPaintManagerUI::SetInstance(hInstance);
	// ��ʼ����Դ
	InitResource();
	HINSTANCE hInstRich = ::LoadLibrary(_T("Riched20.dll"));

	::CoInitialize(NULL);
	::OleInitialize(NULL);

	_Module.Init( 0, hInstance );


	HRESULT Hr = ::CoInitialize(NULL);

	if( FAILED(Hr) ) return 0;

	MainFrame* pFrame = new MainFrame();

	if( pFrame == NULL ) return 0;

	pFrame->Create(NULL, _T("�пƲ���չ����ʾ"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE| WS_EX_APPWINDOW, 0, 0, 0, 0);

	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();
	CPaintManagerUI::Term();

	_Module.Term();

	::OleUninitialize();
	::CoUninitialize();

	::FreeLibrary(hInstRich);

	CloseHandle(hMutex);
	return 0;	
}