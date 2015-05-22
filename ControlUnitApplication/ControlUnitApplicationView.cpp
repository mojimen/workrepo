
// ControlUnitApplicationView.cpp : CControlUnitApplicationView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "ControlUnitApplication.h"
#endif

#include "ControlUnitApplicationDoc.h"
#include "ControlUnitApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define CLIP_COLOR RGB(128,128,128)

// CControlUnitApplicationView

IMPLEMENT_DYNCREATE(CControlUnitApplicationView, CView)

BEGIN_MESSAGE_MAP(CControlUnitApplicationView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CControlUnitApplicationView コンストラクション/デストラクション

CControlUnitApplicationView::CControlUnitApplicationView()
{
	// TODO: 構築コードをここに追加します。

	// TODO: とりあえずはここにおいておくが、別途Initとかに持っていく
	m_rcRect.SetRect(10, 10, 50, 50); // テスト用図形
	m_szRectFrameSize.cx = 5;
	m_szRectFrameSize.cy = 5; // 移動時の四角形の枠幅。
	m_fLButtonClicking = FALSE;

}

CControlUnitApplicationView::~CControlUnitApplicationView()
{
}

BOOL CControlUnitApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CControlUnitApplicationView 描画

void CControlUnitApplicationView::OnDraw(CDC* pDC)
{
	CControlUnitApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。


	CBrush BR;
	BR.CreateSolidBrush(CLIP_COLOR);
	pDC->FillRect(&m_rcRect, &BR);

}

void CControlUnitApplicationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CControlUnitApplicationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CControlUnitApplicationView 診断

#ifdef _DEBUG
void CControlUnitApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CControlUnitApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CControlUnitApplicationDoc* CControlUnitApplicationView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CControlUnitApplicationDoc)));
	return (CControlUnitApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CControlUnitApplicationView メッセージ ハンドラー


void CControlUnitApplicationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	m_fLButtonClicking = TRUE;
	SetCapture(); // マウスをキャプチャー( OnLButtonUp()で解放)
	m_poMousePointerLocation = point;	// 移動量計算のため、初期座標を保存
	m_pRectH = NULL;

	CView::OnLButtonDown(nFlags, point);
}

//移動中の状態を表すために、DrawDragRect() で、枠 rcRectV を表示
//rcRectV を m_rcRectH にコピーし、少し移動する毎に rcRectV を表示し m_rcRectH を消す
void CControlUnitApplicationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	if (m_fLButtonClicking == 1)
	{
		CDC* pDC = GetDC();
		CSize szMoveSize(point - m_poMousePointerLocation);
		m_rcRectV = m_rcRect + szMoveSize; // rcRectV を、マウス位置のイメージ座標とする
		pDC->DrawDragRect(&m_rcRectV, m_szRectFrameSize, m_pRectH, m_szRectFrameSize);
		m_rcRectH = m_rcRectV;
		m_pRectH = &m_rcRectH;
		ReleaseDC(pDC);
	}

	CView::OnMouseMove(nFlags, point);
}


void CControlUnitApplicationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	m_fLButtonClicking = FALSE; // フラグを下げる
	ReleaseCapture(); // マウスを解放します。
	CSize szMoveSize(point - m_poMousePointerLocation); // マウスのボタンが最初に押された位置からの偏移
	m_rcRect += szMoveSize; // 四角形を、ボタンが離された位置に移動
	RedrawWindow(); // 再描画します。
	// OnMouseMove() で表示した内容(移動中の四角形)は、消されます。


	CView::OnLButtonUp(nFlags, point);
}
