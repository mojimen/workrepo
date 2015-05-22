
// ControlUnitApplicationView.h : CControlUnitApplicationView クラスのインターフェイス
//

#pragma once


class CControlUnitApplicationView : public CView
{
protected: // シリアル化からのみ作成します。
	CControlUnitApplicationView();
	DECLARE_DYNCREATE(CControlUnitApplicationView)

// 属性
public:
	CControlUnitApplicationDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CControlUnitApplicationView();
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
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ControlUnitApplicationView.cpp のデバッグ バージョン
inline CControlUnitApplicationDoc* CControlUnitApplicationView::GetDocument() const
   { return reinterpret_cast<CControlUnitApplicationDoc*>(m_pDocument); }
#endif

