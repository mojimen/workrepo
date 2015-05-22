
// ControlUnitAppView.h : CControlUnitAppView クラスのインターフェイス
//

#pragma once

#include "resource.h"


class CControlUnitAppView : public CFormView
{
protected: // シリアル化からのみ作成します。
	CControlUnitAppView();
	DECLARE_DYNCREATE(CControlUnitAppView)

public:
	enum{ IDD = IDD_CONTROLUNITAPP_FORM };

// 属性
public:
	CControlUnitAppDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void OnInitialUpdate(); // 構築後に初めて呼び出されます。

// 実装
public:
	virtual ~CControlUnitAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ControlUnitAppView.cpp のデバッグ バージョン
inline CControlUnitAppDoc* CControlUnitAppView::GetDocument() const
   { return reinterpret_cast<CControlUnitAppDoc*>(m_pDocument); }
#endif

