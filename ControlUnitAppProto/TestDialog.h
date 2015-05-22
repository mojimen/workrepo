#pragma once


// TestDialog ダイアログ

class TestDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TestDialog)

public:
	TestDialog(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~TestDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bCompositEnable; //Aero合成有効無効
	MARGINS m_margins; 	//マージン
	VOID ChangeFrame(); //エアロフレームの設定&再設定

public:
	afx_msg void OnCompositionChanged();
};
