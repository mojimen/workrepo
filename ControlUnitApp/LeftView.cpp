
// LeftView.cpp : CLeftView クラスの実装
//

#include "stdafx.h"
#include "ControlUnitApp.h"

#include "ControlUnitAppDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
END_MESSAGE_MAP()


// CLeftView コンストラクション/デストラクション

CLeftView::CLeftView()
{
	// TODO: 構築コードをここに追加します。
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs を変更して、Window クラスまたはスタイルを変更します。

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO:  GetTreeCtrl() メンバー関数の呼び出しをとおして直接そのリスト コントロールに
	//  アクセスすることによって TreeView をアイテムで固定できます。
}


// CLeftView 診断

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CControlUnitAppDoc* CLeftView::GetDocument() // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CControlUnitAppDoc)));
	return (CControlUnitAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView メッセージ ハンドラー
