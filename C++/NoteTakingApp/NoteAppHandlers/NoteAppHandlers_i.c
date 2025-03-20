

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Mon Jan 18 22:14:07 2038
 */
/* Compiler settings for NoteAppHandlers.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IPreview,0x1a3788eb,0x6594,0x470c,0xbb,0x79,0x5b,0xaa,0x0b,0x11,0xe6,0xaa);


MIDL_DEFINE_GUID(IID, IID_IThumbnail,0xe6eb073c,0x7463,0x4130,0x89,0xe0,0xa8,0xeb,0x20,0x2b,0x4c,0x78);


MIDL_DEFINE_GUID(IID, IID_ISearch,0xa7b03ff8,0xb62b,0x4172,0x8d,0x05,0xfe,0x08,0x61,0xe6,0x2b,0x0e);


MIDL_DEFINE_GUID(IID, LIBID_NoteAppHandlersLib,0x17d9eb88,0xfc02,0x4c34,0xac,0xbf,0xb5,0x4a,0x76,0xbc,0x47,0x2a);


MIDL_DEFINE_GUID(CLSID, CLSID_Preview,0x94be135b,0xa5f7,0x4cf5,0x9e,0x4c,0x75,0xe6,0x95,0x0e,0xcb,0xd8);


MIDL_DEFINE_GUID(CLSID, CLSID_Thumbnail,0xcffed064,0x5af5,0x4eee,0x93,0x2f,0x65,0xfb,0xf6,0x4e,0x86,0x67);


MIDL_DEFINE_GUID(CLSID, CLSID_Search,0x592d14a1,0xbd55,0x42f9,0xa5,0x00,0x8e,0x5f,0x80,0xe8,0x14,0x74);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



