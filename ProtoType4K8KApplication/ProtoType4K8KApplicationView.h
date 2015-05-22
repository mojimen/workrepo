
// ProtoType4K8KApplicationView.h : CProtoType4K8KApplicationView クラスのインターフェイス
//

#pragma once


class CProtoType4K8KApplicationView : public CView
{
protected: // シリアル化からのみ作成します。
	CProtoType4K8KApplicationView();
	DECLARE_DYNCREATE(CProtoType4K8KApplicationView)

// 属性
public:
	CProtoType4K8KApplicationDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
public:
	virtual ~CProtoType4K8KApplicationView();
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

#ifndef _DEBUG  // ProtoType4K8KApplicationView.cpp のデバッグ バージョン
inline CProtoType4K8KApplicationDoc* CProtoType4K8KApplicationView::GetDocument() const
   { return reinterpret_cast<CProtoType4K8KApplicationDoc*>(m_pDocument); }
#endif

