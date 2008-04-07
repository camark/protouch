

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Wed Apr 02 15:43:13 2008
 */
/* Compiler settings for .\MenuExtFirst.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __MenuExtFirst_h__
#define __MenuExtFirst_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIGMenuEx_FWD_DEFINED__
#define __IIGMenuEx_FWD_DEFINED__
typedef interface IIGMenuEx IIGMenuEx;
#endif 	/* __IIGMenuEx_FWD_DEFINED__ */


#ifndef __IGMenuEx_FWD_DEFINED__
#define __IGMenuEx_FWD_DEFINED__

#ifdef __cplusplus
typedef class IGMenuEx IGMenuEx;
#else
typedef struct IGMenuEx IGMenuEx;
#endif /* __cplusplus */

#endif 	/* __IGMenuEx_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IIGMenuEx_INTERFACE_DEFINED__
#define __IIGMenuEx_INTERFACE_DEFINED__

/* interface IIGMenuEx */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IIGMenuEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E1A3E657-D0C0-4C7C-B492-A44ABB329874")
    IIGMenuEx : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IIGMenuExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIGMenuEx * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIGMenuEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIGMenuEx * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIGMenuEx * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIGMenuEx * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIGMenuEx * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIGMenuEx * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IIGMenuExVtbl;

    interface IIGMenuEx
    {
        CONST_VTBL struct IIGMenuExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIGMenuEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIGMenuEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIGMenuEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIGMenuEx_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIGMenuEx_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIGMenuEx_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIGMenuEx_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIGMenuEx_INTERFACE_DEFINED__ */



#ifndef __MenuExtFirstLib_LIBRARY_DEFINED__
#define __MenuExtFirstLib_LIBRARY_DEFINED__

/* library MenuExtFirstLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MenuExtFirstLib;

EXTERN_C const CLSID CLSID_IGMenuEx;

#ifdef __cplusplus

class DECLSPEC_UUID("2CE4C7E6-0984-4389-A44D-CEBBD740F814")
IGMenuEx;
#endif
#endif /* __MenuExtFirstLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


