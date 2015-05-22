// TestDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ControlUnitAppProto.h"
#include "TestDialog.h"
#include "afxdialogex.h"
#include "dwmapi.h"
#pragma comment(lib ,"dwmapi.lib")

// TestDialog ダイアログ

IMPLEMENT_DYNAMIC(TestDialog, CDialogEx)

TestDialog::TestDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(TestDialog::IDD, pParent)
{
	m_bCompositEnable = TRUE;
	DwmIsCompositionEnabled(&m_bCompositEnable);//マージン設定
	m_margins = { 100, 100, 100, 100 };
	ChangeFrame();

}

TestDialog::~TestDialog()
{
}

void TestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TestDialog, CDialogEx)
	ON_WM_DWMCOMPOSITIONCHANGED()
END_MESSAGE_MAP()


// TestDialog メッセージ ハンドラー

VOID TestDialog::ChangeFrame(void)
{
	if (m_bCompositEnable){
		HRESULT hr = DwmExtendFrameIntoClientArea(this->m_hWnd, &m_margins);
		if (SUCCEEDED(hr)){
		}
		else{
			//Error
		}
	}
	Invalidate();
}

void TestDialog::OnCompositionChanged()
{
	// この機能には Windows Vista 以降のバージョンが必要です。
	// シンボル _WIN32_WINNT は >= 0x0600 にする必要があります。
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	DwmIsCompositionEnabled(&m_bCompositEnable);
	ChangeFrame();
	//CDialogEx::OnCompositionChanged();
}
