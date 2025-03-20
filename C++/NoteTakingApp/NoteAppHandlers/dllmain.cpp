// dllmain.cpp : Implementation of DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "NoteAppHandlers_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CNoteAppHandlersModule _AtlModule;

class CNoteAppHandlersApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CNoteAppHandlersApp, CWinApp)
END_MESSAGE_MAP()

CNoteAppHandlersApp theApp;

BOOL CNoteAppHandlersApp::InitInstance()
{
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, nullptr))
		return FALSE;
	return CWinApp::InitInstance();
}

int CNoteAppHandlersApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
