
// CtrlUnitView.h : CCtrlUnitView クラスのインターフェイス
//

#pragma once

#include "resource.h"
#include "afxwin.h"


class CCtrlUnitView : public CFormView
{
protected: // シリアル化からのみ作成します。
	CCtrlUnitView();
	DECLARE_DYNCREATE(CCtrlUnitView)

public:
	enum{ IDD = IDD_CTRLUNIT_FORM };

// 属性
public:
	CCtrlUnitDoc* GetDocument() const;

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
	virtual ~CCtrlUnitView();
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
public:
	CListBox m_xcTimelineDataArea;


	// コンスタント値
#define ACCENTCOLOR_BRUSH RGB(51,153,255)
#define ACCENTCOLOR_BRUSH2 RGB(51,102,255)
#define ACCENTCOLOR_BRUSH3 RGB(51,204,255)
#define ACCENTCOLOR_BRUSH4 RGB(51,255,255)
#define BLACKCOLOR_BRUSH RGB(0,0,0)
#define WHITECOLOR_BRUSH RGB(255,255,255)
#define DARKGRAYCOLOR_BRUSH RGB(102,102,102)
#define GRAYCOLOR_BRUSH RGB(153,153,153)
#define LIGHTGRAYCOLOR_BRUSH RGB(204,204,204)

#define CLIPCOLOR_BRUSH ACCENTCOLOR_BRUSH
#define BASECOLOR_BRUSH WHITECOLOR_BRUSH

private:
	const int kTrackMinHeight = 10;
	const int kTrackMaxHeight = 1000;
	const int kDisplayBaseWidth = 100;
	const int kTimelineDataDisplayBorderThikness = 5;
	const LONG kkTimelineDataDisplayMarginLeft = -10;
	const LONG kkTimelineDataDisplayMarginRight = -10;
	const LONG kkTimelineDataDisplayMarginTop = -10;
	const LONG kkTimelineDataDisplayMarginBottom = -10;

	//表示情報
private:
	int m_iScale;
	CRect m_rcTimelineDisplayRect;


	// 図形ドラッグ用のメンバ
private:
	CRect m_rcRect	// 移動対象の図形
		, m_rcRectV	// 移動中のイメージ（描画）
		, m_rcRectH // 移動中のイメージ（消去）
		, *m_pRectH;
	CPoint m_poMousePointerLocation; // マウスボタンが押されたときの位置
	CSize m_szRectFrameSize; // 移動中の四角形の、枠の太さ (横方向の幅と、縦方向の幅)
	BOOL m_fLButtonClicking; // マウスボタンが押されているかどうかを記録


public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // CtrlUnitView.cpp のデバッグ バージョン
inline CCtrlUnitDoc* CCtrlUnitView::GetDocument() const
   { return reinterpret_cast<CCtrlUnitDoc*>(m_pDocument); }
#endif

