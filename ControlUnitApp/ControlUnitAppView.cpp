
// ControlUnitAppView.cpp : CControlUnitAppView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "ControlUnitApp.h"
#endif

#include "ControlUnitAppDoc.h"
#include "ControlUnitAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CControlUnitAppView

IMPLEMENT_DYNCREATE(CControlUnitAppView, CFormView)

BEGIN_MESSAGE_MAP(CControlUnitAppView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CControlUnitAppView コンストラクション/デストラクション

CControlUnitAppView::CControlUnitAppView()
	: CFormView(CControlUnitAppView::IDD)
{
	// TODO: 構築コードをここに追加します。

}

CControlUnitAppView::~CControlUnitAppView()
{
}

void CControlUnitAppView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CControlUnitAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CFormView::PreCreateWindow(cs);
}

void CControlUnitAppView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

void CControlUnitAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CControlUnitAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CControlUnitAppView 診断

#ifdef _DEBUG
void CControlUnitAppView::AssertValid() const
{
	CFormView::AssertValid();
}

void CControlUnitAppView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CControlUnitAppDoc* CControlUnitAppView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CControlUnitAppDoc)));
	return (CControlUnitAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CControlUnitAppView メッセージ ハンドラー
