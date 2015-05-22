
// ProtoType4K8KApplicationView.cpp : CProtoType4K8KApplicationView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "ProtoType4K8KApplication.h"
#endif

#include "ProtoType4K8KApplicationDoc.h"
#include "ProtoType4K8KApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProtoType4K8KApplicationView

IMPLEMENT_DYNCREATE(CProtoType4K8KApplicationView, CView)

BEGIN_MESSAGE_MAP(CProtoType4K8KApplicationView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CProtoType4K8KApplicationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CProtoType4K8KApplicationView コンストラクション/デストラクション

CProtoType4K8KApplicationView::CProtoType4K8KApplicationView()
{
	// TODO: 構築コードをここに追加します。

}

CProtoType4K8KApplicationView::~CProtoType4K8KApplicationView()
{
}

BOOL CProtoType4K8KApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CProtoType4K8KApplicationView 描画

void CProtoType4K8KApplicationView::OnDraw(CDC* /*pDC*/)
{
	CProtoType4K8KApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


// CProtoType4K8KApplicationView 印刷


void CProtoType4K8KApplicationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CProtoType4K8KApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CProtoType4K8KApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CProtoType4K8KApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

void CProtoType4K8KApplicationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CProtoType4K8KApplicationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CProtoType4K8KApplicationView 診断

#ifdef _DEBUG
void CProtoType4K8KApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CProtoType4K8KApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProtoType4K8KApplicationDoc* CProtoType4K8KApplicationView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProtoType4K8KApplicationDoc)));
	return (CProtoType4K8KApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CProtoType4K8KApplicationView メッセージ ハンドラー
