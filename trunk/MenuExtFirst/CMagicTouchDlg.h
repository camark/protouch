// CMagicTouchDlg.h : Declaration of the CCMagicTouchDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>


// CCMagicTouchDlg

class CCMagicTouchDlg : 
	public CDialogImpl<CCMagicTouchDlg>
{
public:
	CCMagicTouchDlg(const StringList* fileList,const CMINVOKECOMMANDINFO* pCmdInfo)
		:m_FileList(fileList),lpici(pCmdInfo)
	{
	}

	~CCMagicTouchDlg()
	{
	}

	enum { IDD = IDD_CMAGICTOUCHDLG };

BEGIN_MSG_MAP(CCMagicTouchDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	COMMAND_HANDLER(IDC_APPLYCHANGE,BN_CLICKED,OnClickedApply)
	COMMAND_HANDLER(IDC_CHKTIME,BN_CLICKED,OnClickedChkTime)
	COMMAND_HANDLER(IDC_CHKDATE,BN_CLICKED,OnClickedChkDate)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//CDialogImpl<CCMagicTouchDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		
		//Set Time and Date Checkbox to Checked
		SendDlgItemMessage(IDC_CHKTIME,BM_SETCHECK,BST_CHECKED,0);
		SendDlgItemMessage(IDC_CHKDATE,BM_SETCHECK,BST_CHECKED,0);

		SendDlgItemMessage(IDC_CHKMODIFY,BM_SETCHECK,BST_CHECKED,0);

		//DateTime_SetFormat(GetDlgItem(IDC_DTTIME),L"h:m:s tt");
		CenterWindow(lpici->hwnd);
		ShowWindow(SW_SHOW);
		bHandled = TRUE;
		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedChkTime(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		BOOL bChecked=IsDlgButtonChecked(IDC_CHKTIME);
		::EnableWindow(GetDlgItem(IDC_DTTIME),bChecked);

		return 0;
	}

	LRESULT OnClickedChkDate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		BOOL bChecked=IsDlgButtonChecked(IDC_CHKDATE);
		::EnableWindow(GetDlgItem(IDC_DTDATE),bChecked);
		return 0;
	}

	LRESULT OnClickedApply(WORD wNotifyCode,WORD wID,HWND hWndCtl,BOOL& bHandled)
	{
		BOOL b_ModifyTime=IsDlgButtonChecked(IDC_CHKTIME);
		BOOL b_ModifyDate=IsDlgButtonChecked(IDC_CHKDATE);

		BOOL b_ModifyCreateTime=IsDlgButtonChecked(IDC_CHKCREATE);
		BOOL b_ModifyModifyTime=IsDlgButtonChecked(IDC_CHKMODIFY);
		BOOL b_ModifyAccessTime=IsDlgButtonChecked(IDC_CHKACCESS);

		SYSTEMTIME ftCreate,ftAccess,ftModify;

		for (StringList::const_iterator it=m_FileList->begin();it!=m_FileList->end();it++)
		{
			if(b_ModifyTime && b_ModifyDate)
			{
				SYSTEMTIME st=GetSelectedTime(it->c_str());
				SetFileTimeByParam(it->c_str(),st,st,st,b_ModifyCreateTime,b_ModifyAccessTime,b_ModifyModifyTime);
			}
			else if(b_ModifyTime){
				if(GetFileTimex(it->c_str(),ftCreate,ftModify,ftAccess))
				{
					WORD wHour,wMinute,wSecond,wMillec;
					DecodeSystemTimeTime(&GetTimeofDtTime(),&wHour,&wMinute,&wSecond,&wMillec);
					if(b_ModifyCreateTime)
					{					
						ModifyTime(&ftCreate,wHour,wMinute,wSecond,wMillec);
					}

					if(b_ModifyModifyTime)
						ModifyTime(&ftModify,wHour,wMinute,wSecond,wMillec);

					if(b_ModifyAccessTime)
						ModifyTime(&ftAccess,wHour,wMinute,wSecond,wMillec);

					SetFileTimeByParam(it->c_str(),
						ftCreate,
						ftModify,
						ftAccess,
						b_ModifyCreateTime,
						b_ModifyAccessTime,
						b_ModifyModifyTime);
				}
			}else if(b_ModifyDate){
				if(GetFileTimex(it->c_str(),ftCreate,ftModify,ftAccess))
				{
					WORD wYear,wMonth,wDay,wDayOfWeek;

					DecodeSystemTimeDate(&GetTimeofDtDate(),&wYear,&wMonth,&wDay,&wDayOfWeek);
					
					if(b_ModifyCreateTime)
						ModifyDate(&ftCreate,wYear,wMonth,wDay,wDayOfWeek);

					if(b_ModifyModifyTime)
						ModifyDate(&ftModify,wYear,wMonth,wDay,wDayOfWeek);

					if(b_ModifyAccessTime)
						ModifyDate(&ftAccess,wYear,wMonth,wDay,wDayOfWeek);
					
					SetFileTimeByParam(it->c_str(),
						ftCreate,
						ftModify,
						ftAccess,
						b_ModifyCreateTime,
						b_ModifyAccessTime,
						b_ModifyModifyTime);

				}
			}else{
				MessageBox(L"You shuold choose Modify day or Time,or Modify All",L"Warning",MB_OK | MB_ICONERROR);
			}
			
		}
		return 0;
	}

	BOOL ModifyTime(LPSYSTEMTIME lpst,WORD hour,WORD Minute,WORD Second,WORD Millec)
	{
		lpst->wHour=hour;
		lpst->wMinute=Minute;
		lpst->wSecond=Second;
		lpst->wMilliseconds=Millec;

		return TRUE;
	}

	BOOL ModifyDate(LPSYSTEMTIME lpst,WORD year,WORD month,WORD day,WORD dayOfWeek)
	{
		lpst->wYear=year;
		lpst->wMonth=month;
		lpst->wDay=day;
		lpst->wDayOfWeek=dayOfWeek;

		return TRUE;
	}

	

	SYSTEMTIME GetTimeofDtTime()
	{
		SYSTEMTIME st;
		
		DateTime_GetSystemtime(GetDlgItem(IDC_DTTIME),&st);
		
		return st;
	}

	SYSTEMTIME GetTimeofDtDate()
	{
		SYSTEMTIME st;
		
		DateTime_GetSystemtime(GetDlgItem(IDC_DTDATE),&st);

		return st;
	}
	
	SYSTEMTIME GetSelectedTime(LPCTSTR fileName)
	{
		SYSTEMTIME st_Time,st_Date,st_All;
		
		/*GetSystemTime(&st_All);*/
		//ZeroMemory(&st_All,sizeof(SYSTEMTIME),0);
		st_Time=GetTimeofDtTime();
		st_Date=GetTimeofDtDate();

		st_All.wDay=st_Date.wDay;
		st_All.wMonth=st_Date.wMonth;
		st_All.wYear=st_Date.wYear;
		st_All.wDayOfWeek=st_Date.wDayOfWeek;

		//
		st_All.wHour=st_Time.wHour;
		st_All.wSecond=st_Time.wSecond;
		st_All.wMinute=st_Time.wMinute;
		st_All.wMilliseconds=st_Time.wMilliseconds;
				

		return st_All;
	}

	VOID GetModifyDate(SYSTEMTIME& st)
	{
		BOOL b_ModifyDate=IsDlgButtonChecked(IDC_CHKDATE);
		if(b_ModifyDate)
		{
			SYSTEMTIME st_Date;

			st_Date=GetTimeofDtDate();
			WORD year,month,day,dayofweek;

			DecodeSystemTimeDate(&st_Date,&year,&month,&day,&dayofweek);

			st.wYear=year;
			st.wMonth=month;
			st.wDay=day;
			st.wDayOfWeek=dayofweek;
		}		
	}

	VOID GetModifyTime(SYSTEMTIME& st)
	{
		BOOL b_ModifyTime=IsDlgButtonChecked(IDC_CHKTIME);
		if(b_ModifyTime){
			SYSTEMTIME st_Time;
			WORD hour,minute,second,millsec;

			DecodeSystemTimeTime(&st_Time,&hour,&minute,&second,&millsec);

			st.wHour=hour;
			st.wMinute=minute;
			st.wSecond=second;
			st.wMilliseconds=millsec;
		}
	}

	void DecodeSystemTimeDate(const LPSYSTEMTIME lpSt,LPWORD year,LPWORD month,LPWORD day,LPWORD dayofWeek)
	{
		*year=lpSt->wYear;
		*month=lpSt->wMonth;
		*day=lpSt->wDay;
		*dayofWeek=lpSt->wDayOfWeek;
	}

	void DecodeSystemTimeTime(const LPSYSTEMTIME lpst,LPWORD hour,LPWORD minute,LPWORD second,LPWORD millsec)
	{
		*hour=lpst->wHour;
		*minute=lpst->wMinute;
		*second=lpst->wSecond;
		*millsec=lpst->wMilliseconds;
	}

	BOOL SetFileTimeByParam(LPCTSTR fileName,SYSTEMTIME stCreate,SYSTEMTIME stModify,SYSTEMTIME stAccess,BOOL setCreated,BOOL setAccessed,BOOL setWrited)
	{
		HANDLE hFile;

		hFile=CreateFile(fileName,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_DELETE,
			NULL,OPEN_EXISTING,
			0,
			NULL);

		if(INVALID_HANDLE_VALUE== hFile)
			return FALSE;

		FILETIME ftWriteTime,ftCreateTime,ftAccessTime;
		
		//FileTimeToLocalFileTime(&ftWriteTime,&ftLocalWriteTime);
		if(setWrited)
			ConvertSystemTimeToFileTime(&stModify,&ftWriteTime);

		if(setAccessed)
			ConvertSystemTimeToFileTime(&stAccess,&ftAccessTime);

		if(setCreated)
			ConvertSystemTimeToFileTime(&stCreate,&ftCreateTime);

		BOOL result=SetFileTime(hFile,
			setCreated ? &ftCreateTime:(LPFILETIME)NULL,
			setAccessed ? &ftAccessTime:(LPFILETIME)NULL,
			setWrited ? &ftWriteTime:(LPFILETIME)NULL
			);

		CloseHandle(hFile);

		return result;
	}

	VOID ConvertSystemTimeToFileTime(LPSYSTEMTIME st,LPFILETIME stResult)
	{
		FILETIME stLocal;

		SystemTimeToFileTime(st,&stLocal);
		LocalFileTimeToFileTime(&stLocal,stResult);
	}

	VOID ConvertFileTimeToSystemTime(LPFILETIME ft,LPSYSTEMTIME st)
	{
		FILETIME ftLocal;
		FileTimeToLocalFileTime(ft,&ftLocal);
		FileTimeToSystemTime(&ftLocal,st);
	}

	BOOL GetFileTimex(LPCTSTR fileName,SYSTEMTIME &ftCreateTime,SYSTEMTIME &ftModifyTime,SYSTEMTIME &ftAccessTime)
	{
		HANDLE hFile;

		hFile=CreateFile(fileName,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

		if(NULL==hFile)
			return FALSE;

		FILETIME ftCreate,ftAccess,ftModify;
		if(FALSE==::GetFileTime(hFile,&ftCreate,&ftAccess,&ftModify))
		{
			CloseHandle(hFile);
			return FALSE;
		}

		//FileTimeToSystemTime(&ftCreate,&ftCreateTime);
		ConvertFileTimeToSystemTime(&ftCreate,&ftCreateTime);
		//FileTimeToSystemTime(&ftAccess,&ftAccessTime);
		ConvertFileTimeToSystemTime(&ftAccess,&ftAccessTime);
		//FileTimeToSystemTime(&ftModify,&ftModifyTime);
		ConvertFileTimeToSystemTime(&ftModify,&ftModifyTime);

		CloseHandle(hFile);

		return TRUE;
	}
private:
	const StringList* m_FileList;
	const CMINVOKECOMMANDINFO *lpici;
};


