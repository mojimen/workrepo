
// ControlUnitAppProto.h : ControlUnitAppProto アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CControlUnitAppProtoApp:
// このクラスの実装については、ControlUnitAppProto.cpp を参照してください。
//

class CControlUnitAppProtoApp : public CWinAppEx
{
public:
	CControlUnitAppProtoApp();


// オーバーライド
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 実装
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CControlUnitAppProtoApp theApp;
