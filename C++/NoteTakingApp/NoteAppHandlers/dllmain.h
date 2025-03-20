// dllmain.h : Declaration of module class.

class CNoteAppHandlersModule : public ATL::CAtlDllModuleT<CNoteAppHandlersModule>
{
public :
	DECLARE_LIBID(LIBID_NoteAppHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_NOTEAPPHANDLERS, "{97ac1a26-002f-4710-8332-ca846941489a}")
};

extern class CNoteAppHandlersModule _AtlModule;
