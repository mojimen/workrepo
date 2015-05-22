#pragma once



// ControlPanelView フォーム ビュー

class ControlPanelView : public CFormView
{
	DECLARE_DYNCREATE(ControlPanelView)

protected:
	ControlPanelView();           // 動的生成で使用される protected コンストラクター
	virtual ~ControlPanelView();

public:
	enum { IDD = IDD_CONTROLPANELVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};


