
// ControlUnitView.cpp : CControlUnitView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "ControlUnit.h"
#endif

#include "ControlUnitDoc.h"
#include "ControlUnitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CControlUnitView

IMPLEMENT_DYNCREATE(CControlUnitView, CView)

BEGIN_MESSAGE_MAP(CControlUnitView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CControlUnitView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CControlUnitView コンストラクション/デストラクション

CControlUnitView::CControlUnitView()
{
	// TODO: 構築コードをここに追加します。

}

CControlUnitView::~CControlUnitView()
{
}

BOOL CControlUnitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CControlUnitView 描画

void CControlUnitView::OnDraw(CDC* /*pDC*/)
{
	CControlUnitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


// CControlUnitView 印刷


void CControlUnitView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CControlUnitView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CControlUnitView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CControlUnitView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

void CControlUnitView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CControlUnitView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CControlUnitView 診断

#ifdef _DEBUG
void CControlUnitView::AssertValid() const
{
	CView::AssertValid();
}

void CControlUnitView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CControlUnitDoc* CControlUnitView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CControlUnitDoc)));
	return (CControlUnitDoc*)m_pDocument;
}
#endif //_DEBUG


// CControlUnitView メッセージ ハンドラー
