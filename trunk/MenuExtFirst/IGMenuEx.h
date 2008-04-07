// IGMenuEx.h : Declaration of the CIGMenuEx

#pragma once
#include "resource.h"       // main symbols

#include "MenuExtFirst.h"
#include "CMagicTouchDlg.h"
#include <shlobj.h>
#include <comdef.h>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

#define IDM_MAGICTOUCH WM_USER+1001


// CIGMenuEx


class ATL_NO_VTABLE CIGMenuEx :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIGMenuEx, &CLSID_IGMenuEx>,
	public IDispatchImpl<IIGMenuEx, &IID_IIGMenuEx, &LIBID_MenuExtFirstLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellExtInit,
	public IContextMenu
{
public:
	CIGMenuEx()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_IGMENUEX)


	BEGIN_COM_MAP(CIGMenuEx)
		COM_INTERFACE_ENTRY(IIGMenuEx)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IShellExtInit)
		COM_INTERFACE_ENTRY(IContextMenu)
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	//IShellExtInit interface
	HRESULT STDMETHODCALLTYPE Initialize( 
		/* [in] */ LPCITEMIDLIST pidlFolder,
		/* [in] */ IDataObject *pdtobj,
		/* [in] */ HKEY hkeyProgID)
	{
		FORMATETC fmt = { CF_HDROP,NULL,DVASPECT_CONTENT,-1,TYMED_HGLOBAL };
		STGMEDIUM stg = { TYMED_HGLOBAL };

		if (FAILED(pdtobj->GetData(&fmt,&stg)))
		{
			return E_INVALIDARG;
		}

		HDROP hDrop=(HDROP)GlobalLock(stg.hGlobal);

		if(NULL == hDrop)
		{
			ReleaseStgMedium(&stg);
			return E_INVALIDARG;
		}

		UINT uNumFiles=::DragQueryFile(hDrop,
			static_cast<UINT>(-1),
			NULL,
			0);

		if(0==uNumFiles)
		{
			GlobalUnlock(stg.hGlobal);
			ReleaseStgMedium(&stg);
			return E_INVALIDARG;
		}

		HRESULT hr=S_OK;
		
		TCHAR m_FileName[MAX_PATH+1];
		for (UINT i=0;i<uNumFiles;i++)
		{
			if(0==DragQueryFile(hDrop,i,m_FileName,MAX_PATH))
				continue;

			m_Files.push_back(m_FileName);

		}
		return hr;
	}

	//IContextMenu interface
	STDMETHOD(QueryContextMenu)(THIS_
		HMENU hmenu,
		UINT indexMenu,
		UINT idCmdFirst,
		UINT idCmdLast,
		UINT uFlags)
	{
		if(uFlags & CMF_DEFAULTONLY)
			return MAKE_HRESULT(SEVERITY_SUCCESS,FACILITY_NULL,0);

		//::InsertMenu(hmenu,indexMenu,MF_STRING|MF_BYPOSITION,idCmdFirst+1,_T("MagicTouch"));

		HMENU hPopMenu=::CreatePopupMenu();
		int id=1;
		if(hPopMenu)
		{
			AppendMenu(hPopMenu,MF_STRING,idCmdFirst+id++,_T("Use Current DateTime"));
			AppendMenu(hPopMenu,MF_STRING,idCmdFirst+id++,_T("Use Recent Settings"));
			AppendMenu(hPopMenu,MF_STRING,idCmdFirst+id++,_T("Magic Touch ..."));

			InsertMenu(hmenu,idCmdFirst++,MF_BYPOSITION |MF_POPUP,(UINT_PTR)hPopMenu,_T("Magic Touch"));

			DestroyMenu(hPopMenu);

			return MAKE_HRESULT(SEVERITY_SUCCESS,FACILITY_NULL,4);
		}

		return MAKE_HRESULT(SEVERITY_SUCCESS,FACILITY_NULL,0);
	}

	STDMETHOD(InvokeCommand)(THIS_
		LPCMINVOKECOMMANDINFO lpici)
	{
		HRESULT hr=S_OK;

		int iCmd=LOWORD(lpici->lpVerb);

		switch(iCmd)
		{
		case 1:			
			for (StringList::const_iterator it=m_Files.begin();it!=m_Files.end();it++)
			{
				if(SetFileTimeToCurrentFile(it->c_str())==FALSE)
					::MessageBox(lpici->hwnd,_T("Change Time Error"),it->c_str(),MB_OK);
			}
			::MessageBox(lpici->hwnd,_T("Message Test Success!"),_T("Notice"),MB_OK);
			break;
		case 2:
			MessageBox(lpici->hwnd,_T("Use Recent Settings"),_T("Message"),MB_OK);
			break;
		case 3:			
			ShowTouchDialog(&m_Files,lpici);	
			break;
		default:
			break;
		}		
		return hr;
	}

	void ShowTouchDialog(const StringList* files,const LPCMINVOKECOMMANDINFO ici)
	{
		CCMagicTouchDlg dlg(files,ici);
		dlg.DoModal();		
	}

	STDMETHOD(GetCommandString)(THIS_
		UINT_PTR    idCmd,
		UINT        uType,
		UINT      * pwReserved,
		LPSTR       pszName,
		UINT        cchMax) 
	{
		USES_CONVERSION;

		if(0!=idCmd)
			return E_INVALIDARG;

		if ( uType & GCS_HELPTEXT )
		{
			LPCTSTR szText = _T("This is the simple shell extension's help");

			if ( uType & GCS_UNICODE )
			{
				// We need to cast pszName to a Unicode string, and then use the

				// Unicode string copy API.

				lstrcpynW ( (LPWSTR) pszName, T2CW(szText), cchMax );
			}
			else
			{
				// Use the ANSI string copy API to return the help string.

				lstrcpynA ( pszName, T2CA(szText), cchMax );
			}

			return S_OK;
		}

		return E_INVALIDARG;
	}
	
public:
	//Change File Time
	BOOL SetFileTimeToCurrentFile(const LPCTSTR fileName)
	{
		HANDLE hFile;

		hFile=CreateFile(fileName,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_DELETE,
			NULL,OPEN_EXISTING,
			0,
			NULL);

		if(NULL== hFile)
			return FALSE;

		FILETIME ftWriteTime;
		SYSTEMTIME st;

		GetSystemTime(&st);
		SystemTimeToFileTime(&st,&ftWriteTime);

		 BOOL result=SetFileTime(hFile,(LPFILETIME)NULL,(LPFILETIME)NULL,&ftWriteTime);

		 CloseHandle(hFile);

		 return result;
	}
private:
	StringList m_Files;
};

OBJECT_ENTRY_AUTO(__uuidof(IGMenuEx), CIGMenuEx)
