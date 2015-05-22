
// ProtoType4K8KApplication.h : ProtoType4K8KApplication アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル


// CProtoType4K8KApplicationApp:
// このクラスの実装については、ProtoType4K8KApplication.cpp を参照してください。
//

class CProtoType4K8KApplicationApp : public CWinAppEx
{
public:
	CProtoType4K8KApplicationApp();


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

extern CProtoType4K8KApplicationApp theApp;
