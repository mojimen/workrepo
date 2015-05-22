
// CtrlUnitView.cpp : CCtrlUnitView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "CtrlUnit.h"
#endif

#include "CtrlUnitDoc.h"
#include "CtrlUnitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCtrlUnitView

IMPLEMENT_DYNCREATE(CCtrlUnitView, CFormView)

BEGIN_MESSAGE_MAP(CCtrlUnitView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CCtrlUnitView コンストラクション/デストラクション

CCtrlUnitView::CCtrlUnitView()
	: CFormView(CCtrlUnitView::IDD)
{
	// TODO: 構築コードをここに追加します。


	// TODO: とりあえずはここにおいておくが、別途Initとかに持っていく
	m_rcRect.SetRect(10, 10, 50, 50); // テスト用図形
	m_szRectFrameSize.cx = 5;
	m_szRectFrameSize.cy = 5; // 移動時の四角形の枠幅。
	m_fLButtonClicking = FALSE;

}

CCtrlUnitView::~CCtrlUnitView()
{
}

void CCtrlUnitView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_xcTimelineDataArea);
}

BOOL CCtrlUnitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CFormView::PreCreateWindow(cs);
}

void CCtrlUnitView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

void CCtrlUnitView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCtrlUnitView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCtrlUnitView 診断

#ifdef _DEBUG
void CCtrlUnitView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCtrlUnitView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCtrlUnitDoc* CCtrlUnitView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCtrlUnitDoc)));
	return (CCtrlUnitDoc*)m_pDocument;
}
#endif //_DEBUG


// CCtrlUnitView メッセージ ハンドラー


void CCtrlUnitView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	m_fLButtonClicking = TRUE;
	SetCapture(); // マウスをキャプチャー( OnLButtonUp()で解放)
	m_poMousePointerLocation = point;	// 移動量計算のため、初期座標を保存
	m_pRectH = NULL;

	CFormView::OnLButtonDown(nFlags, point);
}


void CCtrlUnitView::OnLButtonUp(UINT nFlags, CPoint point)
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

	CFormView::OnLButtonUp(nFlags, point);
}


void CCtrlUnitView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	m_fLButtonClicking = FALSE; // フラグを下げる
	ReleaseCapture(); // マウスを解放します。
	CSize szMoveSize(point - m_poMousePointerLocation); // マウスのボタンが最初に押された位置からの偏移
	m_rcRect += szMoveSize; // 四角形を、ボタンが離された位置に移動
	RedrawWindow(); // 再描画します。

	CFormView::OnMouseMove(nFlags, point);
}


void CCtrlUnitView::OnPaint()
{
	CPaintDC dcViewDc(this); // device context for painting
	// TODO: ここにメッセージ ハンドラー コードを追加します。
	// 描画メッセージで CFormView::OnPaint() を呼び出さないでください。

	// Viewエリアの表示情報を取得
	CRect rcViewRect;
	GetClientRect(&rcViewRect);

	m_rcTimelineDisplayRect.CopyRect(rcViewRect);
	m_rcTimelineDisplayRect.InflateRect(kkTimelineDataDisplayMarginLeft, kkTimelineDataDisplayMarginTop, kkTimelineDataDisplayMarginRight, kkTimelineDataDisplayMarginBottom);

	//--------- ここからダブルバッファ用コード
	// 仮想デバイスコンテキストを作成
	CDC dcMemDc;
	dcMemDc.CreateCompatibleDC(&dcViewDc);
	CBitmap bmOffScreenBitmap;
	bmOffScreenBitmap.CreateCompatibleBitmap(&dcViewDc, rcViewRect.Width(), rcViewRect.Height());
	CBitmap* bmOldOffScreenBitmap = dcMemDc.SelectObject(&bmOffScreenBitmap);
	//---------- ここまで

	//背景描画
	CBrush brBaseBrush(BASECOLOR_BRUSH);
	dcMemDc.FillRect(&rcViewRect, &brBaseBrush);

	// 枠描画
	CPen brPenBrush(PS_SOLID, kTimelineDataDisplayBorderThikness, DARKGRAYCOLOR_BRUSH);
	CPen* oldpen = dcMemDc.SelectObject(&brPenBrush);
	dcMemDc.Rectangle(m_rcTimelineDisplayRect);
	dcMemDc.SelectObject(oldpen);

	CBrush brClipBrush(CLIPCOLOR_BRUSH);
	dcMemDc.FillRect(&m_rcRect, &brClipBrush);


	//--------- ここからダブルバッファ用コード
	// 描画
	BitBlt(dcViewDc.GetSafeHdc(), 0, 0, rcViewRect.Width(), rcViewRect.Height(), dcMemDc.GetSafeHdc(), 0, 0, SRCCOPY);
	//仮想デバイスコンテキストビットマップの初期化・破棄
	dcMemDc.SelectObject(bmOffScreenBitmap);
	bmOldOffScreenBitmap->DeleteObject();
	bmOffScreenBitmap.DeleteObject();
	dcMemDc.DeleteDC();
	//---------- ここまで
	brBaseBrush.DeleteObject();
	brPenBrush.DeleteObject();
	brClipBrush.DeleteObject();

}
