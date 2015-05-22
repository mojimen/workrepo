// TimelineEditView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ControlUnitApplication.h"
#include "TimelineEditView.h"


// TimelineEditView

IMPLEMENT_DYNCREATE(TimelineEditView, CFormView)

TimelineEditView::TimelineEditView()
	: CFormView(TimelineEditView::IDD)
{
	m_fDrawn = FALSE;
	// TODO: とりあえずはここにおいておくが、別途Initとかに持っていく
	m_rcRect.SetRect(10, 10, 50, 50); // テスト用図形
	m_szRectFrameSize.cx = 5;
	m_szRectFrameSize.cy = 5; // 移動時の四角形の枠幅。
	m_fLButtonClicking = FALSE;
}

TimelineEditView::~TimelineEditView()
{
}

void TimelineEditView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_PICTURE, m_xcPictureControl);
}

BEGIN_MESSAGE_MAP(TimelineEditView, CFormView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// TimelineEditView 診断

#ifdef _DEBUG
void TimelineEditView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void TimelineEditView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// TimelineEditView メッセージ ハンドラー


void TimelineEditView::OnLButtonDown(UINT nFlags, CPoint point)
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
void TimelineEditView::OnMouseMove(UINT nFlags, CPoint point)
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

void TimelineEditView::OnLButtonUp(UINT nFlags, CPoint point)
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

HBRUSH TimelineEditView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: ここで DC の属性を変更してください。

	// TODO: 既定値を使用したくない場合は別のブラシを返します。

	 //ダイアログの色変更
	if (nCtlColor == CTLCOLOR_DLG)
	{
		if (*pWnd == *this)
		{
			// 背景色
			hbr = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		}
	}
	return hbr;
}


void TimelineEditView::OnPaint()
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




	//CFormView::OnPaint();
}


BOOL TimelineEditView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	return TRUE;
	//return CFormView::OnEraseBkgnd(pDC);
}
