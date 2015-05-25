
// ControlUnitAppProtoView.cpp : CControlUnitAppProtoView クラスの実装
//
// 移動判定の本格対応、クリップ隣接時の境界線、トランジション、ツールチップ、リップル／デュアル、デバイスコンテキスト作成を少なく、移動幅が大きい時のアニメーション、ウィンドウ全体描画

//#include "math.h"


#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "ControlUnitAppProto.h"
#endif

#include "ControlUnitAppProtoDoc.h"
#include "ControlUnitAppProtoView.h"
#include "ClipDataTest.h"
#include "TestDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PROTOTYPEMODE


// CControlUnitAppProtoView

IMPLEMENT_DYNCREATE(CControlUnitAppProtoView, CView)

BEGIN_MESSAGE_MAP(CControlUnitAppProtoView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()

// CControlUnitAppProtoView コンストラクション/デストラクション

CControlUnitAppProtoView::CControlUnitAppProtoView()
{
	// TODO: 構築コードをここに追加します。

	// TODO: とりあえずはここにおいておくが、別途Initとかに持っていく
	m_clClipData1 = new ClipDataTest();
	m_clClipData2 = new ClipDataTest();
	m_clClipData1->m_iTimelineInPoint = 101;
	m_clClipData1->SetDuration(10);
	m_clClipData2->m_iTimelineInPoint = 600;
	m_clClipData2->SetDuration(100);

	m_fLButtonClicking = FALSE;
	m_fMoving = FALSE;
	m_fSingleInTriming = FALSE;
	m_fSingleOutTriming = FALSE;
	m_fScrubing = FALSE;
	m_fDragShuttling = FALSE;

	m_rcPreviewPanelRect.bottom = m_rcPreviewPanelRect.top + kPreviewPanelDefaltHeight;
	//m_rcTimelineEditPanelRect.bottom = m_rcTimelineEditPanelRect.top + kTimelineEditDefaltHeight;

	m_iLeftFrameNumber = 0;
	m_iRightFrameNumber = 0;
	m_iTimelineCursorFramePosition = 0;
	m_iOperatingFrameCount = 0;
	m_iOperatingClipFrameCount = 0;

	m_iSelectedDisplayScaleNumber = 8;
	ChangeDisplayScale();


}

CControlUnitAppProtoView::~CControlUnitAppProtoView()
{
}

BOOL CControlUnitAppProtoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);

}

// CControlUnitAppProtoView 描画

void CControlUnitAppProtoView::OnDraw(CDC* /*pDC*/)
{
	CControlUnitAppProtoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}

// 右ボタンアップ
void CControlUnitAppProtoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	if (m_rcTimelineControlPanelRect.PtInRect(point))
	{
		++m_iSelectedDisplayScaleNumber;
		if (ChangeDisplayScale())
		{
			Invalidate();
		}
	}
	else
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}
}

void CControlUnitAppProtoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CControlUnitAppProtoView 診断

#ifdef _DEBUG
void CControlUnitAppProtoView::AssertValid() const
{
	CView::AssertValid();
}

void CControlUnitAppProtoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CControlUnitAppProtoDoc* CControlUnitAppProtoView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CControlUnitAppProtoDoc)));
	return (CControlUnitAppProtoDoc*)m_pDocument;
}
#endif //_DEBUG


// CControlUnitAppProtoView メッセージ ハンドラー

// 左ボタンダウン
void CControlUnitAppProtoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	// タイムラインデータエリア内判定
	if(m_rcTimelineDataRect.PtInRect(point))
	{
		// クリップ判定
		if (IsPointInAnyClipRect(point))
		{
			m_fLButtonClicking = TRUE;
			SetCapture(); // マウスをキャプチャー( OnLButtonUp()で解放)
			m_poMousePointerLocation = point;	// 移動量計算のため、初期座標を保存
			m_clMovingClipData->SetOperatingRect(static_cast<CRect>(m_clMovingClipData));
			m_rcBorderRect.CopyRect(static_cast<CRect>(m_clMovingClipData));
			m_iOperatingClipFrameCount = 0;
			Invalidate();
		}
		// タイムラインカーソル判定
		else if (m_rcTimelineCursorHitArea.PtInRect(point))
		{
			m_fLButtonClicking = TRUE;
			m_fDragShuttling = TRUE;
			SetCapture(); // マウスをキャプチャー( OnLButtonUp()で解放)
			m_poMousePointerLocation = point;	// 移動量計算のため、初期座標を保存
			m_iOperatingFrameCount = 0;
			m_fSuttleSpeed = 0;
			Invalidate();
		}
	}
	else
	{
		// タイムラインカーソル判定
		if (m_rcTimelineCursorHitArea.PtInRect(point))
		{
			m_fLButtonClicking = TRUE;
			m_fDragShuttling = TRUE;
			SetCapture(); // マウスをキャプチャー( OnLButtonUp()で解放)
			m_poMousePointerLocation = point;	// 移動量計算のため、初期座標を保存
			m_iOperatingFrameCount = 0;
			m_fSuttleSpeed = 0;
			Invalidate();
		}
		// シークバー内判定
		else if (IsPointInSeekBar(point))
		{
			m_fLButtonClicking = TRUE;
			m_fScrubing = TRUE;
			SetCapture(); // マウスをキャプチャー( OnLButtonUp()で解放)
			m_poMousePointerLocation = point;	// 移動量計算のため、初期座標を保存
			m_iOperatingFrameCount = 0;

			//TODO: デバッグ用なので後で削除
#ifdef PROTOTYPEMODE
			int iFrame = ChangeDisplayPointToTimelineFramePosition(point);
			CDC* pDC = GetDC();
			CRect rcViewRect;
			GetClientRect(&rcViewRect);
			CString strFrameNumber;
			strFrameNumber.Format(_T("SEEKBAR CLICK FRAME %d"), iFrame);
			pDC->TextOutW(300, 5, strFrameNumber);
			strFrameNumber.Format(_T("SEEKBAR CLICK POINT %d"), point.x);
			pDC->TextOutW(300, 40, strFrameNumber);
			pDC->DeleteDC();
#endif
		}
		// タイムラインコントロールパネル内判定
		else if (m_rcTimelineControlPanelRect.PtInRect(point))
		{
			--m_iSelectedDisplayScaleNumber;
			if (ChangeDisplayScale())
			{
				Invalidate();
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

// 左ボタンアップ
void CControlUnitAppProtoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	m_fLButtonClicking = FALSE; // フラグを下げる
	ReleaseCapture(); // マウスを解放します。

	if (m_fMoving)
	{
		m_clMovingClipData->m_iTimelineInPoint += m_iOperatingClipFrameCount;
		m_clMovingClipData->CopyRect(m_clMovingClipData->GetOperatingRect());
	}
	else if (m_fSingleInTriming)
	{
		m_clMovingClipData->m_iTimelineInPoint += m_iOperatingClipFrameCount;
		int iClipDuration = m_clMovingClipData->GetDuration();
		// In側に伸びる（マイナス方向への移動）は長さを加算
		m_clMovingClipData->SetDuration(iClipDuration - m_iOperatingClipFrameCount);
		m_clMovingClipData->CopyRect(m_clMovingClipData->GetOperatingRect());
	}
	else if (m_fSingleOutTriming)
	{
		int iClipDuration = m_clMovingClipData->GetDuration();
		m_clMovingClipData->SetDuration(iClipDuration + m_iOperatingClipFrameCount);
		m_clMovingClipData->CopyRect(m_clMovingClipData->GetOperatingRect());
	}
	else if (m_fScrubing)
	{
		if ((point.x == m_poMousePointerLocation.x) && (point.y == m_poMousePointerLocation.y))
		{
			int iFrame = ChangeDisplayPointToTimelineFramePosition(point);
			// できれば実現
			//DrawAnimation(iFrame - m_iTimelineCursorFramePosition);
			m_iTimelineCursorFramePosition = iFrame;
		}
		else
		{
			m_iTimelineCursorFramePosition += m_iOperatingFrameCount;
		}
	}

	m_rcBorderRect.SetRectEmpty();
	m_iOperatingFrameCount = 0;
	m_iOperatingClipFrameCount = 0;

	Invalidate(); // 再描画します。

	m_clMovingClipData = nullptr;
	m_clStaticClipData = nullptr;
	m_fMoving = FALSE;
	m_fSingleInTriming = FALSE;
	m_fSingleOutTriming = FALSE;
	m_fScrubing = FALSE;
	m_fDragShuttling = FALSE;


	CView::OnLButtonUp(nFlags, point);
}

// ドラッグ操作
void CControlUnitAppProtoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	if (m_fLButtonClicking) 
	{
		CSize szMoveSize(point - m_poMousePointerLocation);
		if (m_fMoving)
		{
			m_iOperatingClipFrameCount = ChangeOperatingDistanceToTimelineFrames(szMoveSize, m_clMovingClipData->m_iTimelineInPoint);
			CalcClipRectDisplayPoint(m_rcBorderRect, m_clMovingClipData, m_iOperatingClipFrameCount);
			CheckMove(point);
			Invalidate();
		}
		else if (m_fSingleInTriming || m_fSingleOutTriming)
		{
			m_clMovingClipData->SetOperatingRect(static_cast<CRect>(m_clMovingClipData)); // 伸縮分のイメージ座標
			if (m_fSingleInTriming)
			{					
				m_iOperatingClipFrameCount = ChangeOperatingDistanceToTimelineFrames(szMoveSize, m_clMovingClipData->m_iTimelineInPoint);
				CheckInTrim();
				CalcClipRectDisplayPoint(*(m_clMovingClipData->GetOperatingRect()), m_clMovingClipData, 0, m_iOperatingClipFrameCount);
			}
			else
			{
				m_iOperatingClipFrameCount = ChangeOperatingDistanceToTimelineFrames(szMoveSize,
					(m_clMovingClipData->m_iTimelineInPoint + m_clMovingClipData->GetDuration()));
				CheckOutTrim();
				CalcClipRectDisplayPoint(*(m_clMovingClipData->GetOperatingRect()), m_clMovingClipData, 0, 0, m_iOperatingClipFrameCount);
			}
			Invalidate();
		}
		else if (m_fScrubing)
		{
			szMoveSize.cx *= -1;
			m_iOperatingFrameCount = ChangeOperatingDistanceToTimelineFrames(szMoveSize, m_iTimelineCursorFramePosition);
			// 最小範囲チェック
			// TODO: 最大範囲チェックは？
			if ((m_iTimelineCursorFramePosition + m_iOperatingFrameCount) < 0)
			{
				m_iOperatingFrameCount = -1 * m_iTimelineCursorFramePosition;
			}
			Invalidate();
		}
		else if (m_fDragShuttling)
		{
			// マウス位置から倍速速度を取得
			m_fSuttleSpeed = SetShuttleSpeed(point, szMoveSize);
			Invalidate();
		}
	}

	CView::OnMouseMove(nFlags, point);
}


void CControlUnitAppProtoView::OnPaint()
{
	CPaintDC dcViewDc(this); // device context for painting
	// TODO: ここにメッセージ ハンドラー コードを追加します。
	// 描画メッセージで CView::OnPaint() を呼び出さないでください。

	// Viewエリアの表示情報を取得
	CRect rcViewRect;
	GetClientRect(&rcViewRect);

	// View内の表示位置確認
	SetPanelRect();

	//--------- ここからダブルバッファ用コード
	// 仮想デバイスコンテキストを作成
	CDC dcMemDc;
	dcMemDc.CreateCompatibleDC(&dcViewDc);
	CBitmap bmOffScreenBitmap;
	bmOffScreenBitmap.CreateCompatibleBitmap(&dcViewDc, rcViewRect.Width(), rcViewRect.Height());
	CBitmap* bmOldOffScreenBitmap = dcMemDc.SelectObject(&bmOffScreenBitmap);
	//---------- ここまで

	//背景描画
	CBrush brBaseBrush(TIMELINEBASECOLOR_BRUSH);
	dcMemDc.FillRect(&rcViewRect, &brBaseBrush);

	// 枠描画
	CPen brPenBrush(PS_SOLID, 1, LIGHTGRAYCOLOR_BRUSH);
	CPen* oldpen = dcMemDc.SelectObject(&brPenBrush);
	dcMemDc.Rectangle(m_rcPreviewPanelRect);
	dcMemDc.Rectangle(m_rcTimelineControlPanelRect);
	dcMemDc.Rectangle(m_rcTrackHeaderRect);
	dcMemDc.Rectangle(m_rcTimelineDataRect);
	dcMemDc.SelectObject(oldpen);

	// コントロールパネル描画
	DrawTimelineControlPanel(dcMemDc);

	// シークバー描画
	DrawSeekBar(dcMemDc);

	// 静止クリップ描画
	CBrush brClipBrush(CLIPCOLOR_BRUSH);
	CalcClipRectDisplayPoint(static_cast<CRect&>(*m_clClipData1), m_clClipData1);
	dcMemDc.FillRect(static_cast<CRect*>(m_clClipData1), &brClipBrush);
	CalcClipRectDisplayPoint(static_cast<CRect&>(*m_clClipData2), m_clClipData2);
	dcMemDc.FillRect(static_cast<CRect*>(m_clClipData2), &brClipBrush);

	// 操作イメージ描画
	if ((m_fSingleInTriming || m_fSingleOutTriming || m_fMoving) && (!(m_clMovingClipData->GetOperatingRect()->IsRectEmpty())))
	{
		DrawOperatingClip(&dcViewDc, rcViewRect, dcMemDc);
	}

	// タイムラインカーソル／シャトル操作補助線描画
	DrawTimelineCursor(&dcViewDc, rcViewRect, dcMemDc);

	//--------- ここからダブルバッファ用コード
	// 描画
	BitBlt(dcViewDc.GetSafeHdc(), 0, 0, rcViewRect.Width(), rcViewRect.Height(), dcMemDc.GetSafeHdc(), 0, 0, SRCCOPY);
	// 仮想デバイスコンテキストビットマップの初期化・破棄
	dcMemDc.SelectObject(bmOffScreenBitmap);
	bmOldOffScreenBitmap->DeleteObject();
	bmOffScreenBitmap.DeleteObject();
	dcMemDc.DeleteDC();
	// ---------- ここまで
	brBaseBrush.DeleteObject();
	brPenBrush.DeleteObject();
	brClipBrush.DeleteObject();

}

// タイムラインコントロールパネルの描画を行う
void CControlUnitAppProtoView::DrawTimelineControlPanel(CDC& dcMemDc)
{
	// 背景塗りつぶし
	CBrush brControlPanelBaseBrush(TIMELINECONTROLPANELBACKGROUNDCOLOR_BRUSH);
	dcMemDc.FillRect(m_rcTimelineControlPanelRect, &brControlPanelBaseBrush);
	brControlPanelBaseBrush.DeleteObject();

#ifdef PROTOTYPEMODE
	CString strText;
	int iOldBkMode;
	iOldBkMode = dcMemDc.SetBkMode(TRANSPARENT);
	COLORREF crOldTextColor = dcMemDc.SetTextColor(SEEKBARTIMECODETEXTCOLOR_BRUSH);
	strText.Format(_T("%d"), m_iFramePerBase);
	dcMemDc.TextOut(m_rcTimelineControlPanelRect.left + 5, m_rcTimelineControlPanelRect.bottom - 20, strText);
	dcMemDc.SetBkMode(iOldBkMode);
	dcMemDc.SetTextColor(crOldTextColor);
#endif
}

// シークバーの描画を行う
void CControlUnitAppProtoView::DrawSeekBar(CDC& dcMemDc)
{
	// 背景塗りつぶし
	CBrush brSeekBarBaseBrush(SEEKBARBACKGROUNDCOLOR_BRUSH);
	dcMemDc.FillRect(m_rcSeekBarRect, &brSeekBarBaseBrush);

	CPen brSeekBarBigScalePen(PS_SOLID, kSeekBarMiddleScaleThikness, SEEKBARBIGSCALECOLOR_BRUSH);
	CPen brSeekBarMiddleScalePen(PS_SOLID, kSeekBarMiddleScaleThikness, SEEKBARMIDDLESCALECOLOR_BRUSH);
	CPen brSeekBarSmallScalePen(PS_SOLID, kSeekBarSmallScaleThikness, SEEKBARSMALLSCALECOLOR_BRUSH);
	CPen brSeekBarBigScaleLinePen(PS_SOLID, kSeekBarMiddleScaleThikness, SEEKBARBIGSCALELINECOLOR_BRUSH);
	CPen brSeekBarMiddleScaleLinePen(PS_SOLID, kSeekBarMiddleScaleThikness, SEEKBARMIDDLESCALELINECOLOR_BRUSH);
	CPen brSeekBarSmallScaleLinePen(PS_SOLID, kSeekBarSmallScaleThikness, SEEKBARSMALLSCALELINECOLOR_BRUSH);
	CPen* oldpen = dcMemDc.SelectObject(&brSeekBarMiddleScalePen);

	POINT pScaleLine;
	pScaleLine.x = m_iTimelineCursorPoint;
	pScaleLine.y = m_rcSeekBarRect.top;
	int iDrawFrame = m_iTimelineCursorFramePosition + m_iOperatingFrameCount;

	// カーソルから右側の目盛り描画
	while (pScaleLine.x < m_rcSeekBarRect.right)
	{
		if (iDrawFrame == m_iTimelineCursorFramePosition)
		{
			//TODO: デバッグ
			CString strText;
			strText.Format(_T("CURSOR SEEKBAR  %d"), m_iRightFrameNumber + pScaleLine.x);
			dcMemDc.TextOutW(5, 85, strText);
		}
		// 大目盛り
		if ((iDrawFrame % (kSeekBarBigScaleInterval * m_iFramePerBase)) == 0)
		{
			if (iDrawFrame >= 0)
			{
				DrawBigScale(dcMemDc, iDrawFrame, brSeekBarBigScalePen, brSeekBarBigScaleLinePen, pScaleLine);
			}
		}
		// 中目盛り
		else if ((iDrawFrame % m_iFramePerBase) == 0)
		{
			if (iDrawFrame >= 0)
			{
				DrawMiddleScale(dcMemDc, iDrawFrame, brSeekBarMiddleScalePen, brSeekBarMiddleScaleLinePen, pScaleLine);
			}
		}
		// 小目盛り
		else if ((iDrawFrame % m_iFramePerScale) == 0)
		{
			if (iDrawFrame >= 0)
			{
				DrawSmallScale(dcMemDc, iDrawFrame, brSeekBarSmallScaleLinePen, brSeekBarSmallScaleLinePen, pScaleLine);
			}
		}
		if (m_fFramePerPoint < 1)
		{
			pScaleLine.x += m_fPointPerFrame;
		}
		else
		{
			if ((iDrawFrame % static_cast<int>(m_fFramePerPoint)) == 0)
			{
				++pScaleLine.x;
			}
		}
		++iDrawFrame;
	}
	// カーソルから左側の目盛り描画
	pScaleLine.x = m_iTimelineCursorPoint;
	pScaleLine.y = m_rcSeekBarRect.top;
	iDrawFrame = m_iTimelineCursorFramePosition + m_iOperatingFrameCount;
	while ((pScaleLine.x > m_rcSeekBarRect.left) && (iDrawFrame >= 0))
	{
		// 大目盛り
		if ((iDrawFrame % (kSeekBarBigScaleInterval * m_iFramePerBase)) == 0)
		{
			DrawBigScale(dcMemDc, iDrawFrame, brSeekBarBigScalePen, brSeekBarBigScaleLinePen, pScaleLine);
		}
		// 中目盛り
		else if ((iDrawFrame % m_iFramePerBase) == 0)
		{
			DrawMiddleScale(dcMemDc, iDrawFrame, brSeekBarMiddleScalePen, brSeekBarMiddleScaleLinePen, pScaleLine);
		}
		// 小目盛り
		else if ((iDrawFrame % m_iFramePerScale) == 0)
		{
			DrawSmallScale(dcMemDc, iDrawFrame, brSeekBarSmallScaleLinePen, brSeekBarSmallScaleLinePen, pScaleLine);
		}
		if (m_fFramePerPoint < 1)
		{
			pScaleLine.x -= m_fPointPerFrame;
		}
		else
		{
			if ((iDrawFrame % static_cast<int>(m_fFramePerPoint)) == 0)
			{
				--pScaleLine.x;
			}
		}
		--iDrawFrame;
	}
	dcMemDc.SelectObject(oldpen);

#ifdef PROTOTYPEMODE
	CString strFrameNumber;
	strFrameNumber.Format(_T("%d"), m_iTimelineCursorFramePosition + m_iOperatingFrameCount);
	dcMemDc.TextOutW(5, 5, strFrameNumber);
	strFrameNumber.Format(_T("%d"), m_iLeftFrameNumber + m_iOperatingFrameCount);
	dcMemDc.TextOutW(5, 40, strFrameNumber);
	strFrameNumber.Format(_T("%d"), m_iRightFrameNumber + m_iOperatingFrameCount);
	dcMemDc.TextOutW(5, 65, strFrameNumber);
#endif

	brSeekBarBaseBrush.DeleteObject();
	brSeekBarBigScalePen.DeleteObject();
	brSeekBarMiddleScalePen.DeleteObject();
	brSeekBarSmallScalePen.DeleteObject();
	brSeekBarBigScaleLinePen.DeleteObject();
	brSeekBarMiddleScaleLinePen.DeleteObject();
	brSeekBarSmallScaleLinePen.DeleteObject();

}

// 大目盛り描画
void CControlUnitAppProtoView::DrawBigScale(CDC& dcMemDc, const int iDrawFrame,  const CPen& brScalePen, const CPen& brLinePen, POINT& pScaleLine)
{
	CString strFrameNumber;
#ifdef PROTOTYPEMODE
	int iOldBkMode;
#endif

	// TODO: 製品はタイムコードを表示
	iOldBkMode = dcMemDc.SetBkMode(TRANSPARENT);
	COLORREF crOldTextColor = dcMemDc.SetTextColor(SEEKBARTIMECODETEXTCOLOR_BRUSH);
	strFrameNumber.Format(_T("%d"), iDrawFrame);
	dcMemDc.TextOut(pScaleLine.x + 2, m_rcSeekBarRect.top + 2, strFrameNumber);
	dcMemDc.SetBkMode(iOldBkMode);
	dcMemDc.SetTextColor(crOldTextColor);

	dcMemDc.SelectObject(brScalePen);
	pScaleLine.y = m_rcSeekBarRect.top + kSeekBarBigScaleMargin;
	dcMemDc.MoveTo(pScaleLine);
	pScaleLine.y = m_rcSeekBarRect.bottom;
	dcMemDc.LineTo(pScaleLine);
	dcMemDc.SelectObject(brLinePen);
	pScaleLine.y = m_rcTimelineDataRect.bottom;
	dcMemDc.LineTo(pScaleLine);

	return;
}

// 中目盛り描画
void CControlUnitAppProtoView::DrawMiddleScale(CDC& dcMemDc, const int iDrawFrame, const CPen& brScalePen, const CPen& brLinePen, POINT& pScaleLine)
{
	CString strFrameNumber;
#ifdef PROTOTYPEMODE
	int iOldBkMode;
#endif

	// TODO: デバッグ用表示なのでとる事
#ifdef PROTOTYPEMODE
	iOldBkMode = dcMemDc.SetBkMode(TRANSPARENT);
	COLORREF crOldTextColor = dcMemDc.SetTextColor(SEEKBARTIMECODETEXTCOLOR_BRUSH);
	strFrameNumber.Format(_T("%d"), (iDrawFrame % (kSeekBarBigScaleInterval * m_iSeekBarScaleCountPerBase)));
	dcMemDc.TextOut(pScaleLine.x + 2, m_rcSeekBarRect.top + 6, strFrameNumber);
	dcMemDc.SetBkMode(iOldBkMode);
	dcMemDc.SetTextColor(crOldTextColor);
#endif
	dcMemDc.SelectObject(brScalePen);
	pScaleLine.y = m_rcSeekBarRect.top + kSeekBarMiddleScaleMargin;
	dcMemDc.MoveTo(pScaleLine);
	pScaleLine.y = m_rcSeekBarRect.bottom;
	dcMemDc.LineTo(pScaleLine);
#ifdef PROTOTYPEMODE
	dcMemDc.SelectObject(brLinePen);
	pScaleLine.y = m_rcTimelineDataRect.bottom;
	dcMemDc.LineTo(pScaleLine);
#endif

	return;
}

// 小目盛り描画
void CControlUnitAppProtoView::DrawSmallScale(CDC& dcMemDc, const int iDrawFrame, const CPen& brScalePen, const CPen& brLinePen, POINT& pScaleLine)
{
	CString strFrameNumber;

	dcMemDc.SelectObject(brScalePen);
	pScaleLine.y = m_rcSeekBarRect.top + kSeekBarSmallScaleMargin;
	dcMemDc.MoveTo(pScaleLine);
	pScaleLine.y = m_rcSeekBarRect.bottom;
	dcMemDc.LineTo(pScaleLine);
#ifdef PROTOTYPEMODE
	dcMemDc.SelectObject(brLinePen);
	pScaleLine.y = m_rcTimelineDataRect.bottom;
	dcMemDc.LineTo(pScaleLine);
#endif

	return;
}


// 操作中クリップの描画を行う
BOOL CControlUnitAppProtoView::DrawOperatingClip(const CDC* dcViewDc, const CRect& rcViewRect, CDC& dcMemDc)
{
	if (dcViewDc == nullptr)
	{
		return FALSE;
	}

	//操作イメージ用デバイスコンテキスト作成
	// 仮想デバイスコンテキストを作成
	CDC dcMovingMemDc;
	dcMovingMemDc.CreateCompatibleDC(const_cast<CDC*>(dcViewDc));
	CBitmap bmMovingScreenBitmap;
	bmMovingScreenBitmap.CreateCompatibleBitmap(const_cast<CDC*>(dcViewDc), rcViewRect.Width(), rcViewRect.Height());
	CBitmap* bmOldMovingScreenBitmap = dcMovingMemDc.SelectObject(&bmMovingScreenBitmap);
	// 透過ブレンド用データ
	BLENDFUNCTION blAlphaBlend;
	blAlphaBlend.BlendOp = AC_SRC_OVER;
	blAlphaBlend.BlendFlags = 0;
	blAlphaBlend.SourceConstantAlpha = kMovingClipAlpha;
	blAlphaBlend.AlphaFormat = 0;

	// 元のクリップの色を変える
	CBrush brMovingClipBrush(LIGHTGRAYCOLOR_BRUSH);
	CalcClipRectDisplayPoint(static_cast<CRect&>(*m_clMovingClipData), m_clMovingClipData);
	dcMemDc.FillRect(static_cast<CRect*>(m_clMovingClipData), &brMovingClipBrush);
	brMovingClipBrush.DeleteObject();

	CBrush brClipBrush(CLIPCOLOR_BRUSH);

	if (m_fSingleInTriming || m_fSingleOutTriming)
	{
		CRect rcMovingRect = m_clMovingClipData->GetOperatingRect();
		//CBrush brClipTrimBrush(ACCENTCOLOR_BRUSH);
		dcMovingMemDc.FillRect(rcMovingRect, &brClipBrush);
		//brClipTrimBrush.DeleteObject();
		dcMemDc.AlphaBlend(rcMovingRect.left, rcMovingRect.top, rcMovingRect.Width(), rcMovingRect.Height(),
			&dcMovingMemDc, rcMovingRect.left, rcMovingRect.top, rcMovingRect.Width(), rcMovingRect.Height(),
			blAlphaBlend);

#ifdef PROTOTYPEMODE
		//TODO: デバッグ
		CString strText;
		int iPoint;
		int iDuration;
		if (m_fSingleInTriming)
		{
			iPoint = m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount;
		}
		else
		{
			iPoint = m_clMovingClipData->m_iTimelineInPoint;
		}
		strText.Format(_T("TrimingClipInPoint  %d"), iPoint);
		dcMemDc.TextOutW(300, 5, strText);
		strText.Format(_T("TrimingClipLeftPoint  %d"), rcMovingRect.left);
		dcMemDc.TextOutW(300, 25, strText);
		if (m_fSingleInTriming)
		{
			iPoint = m_clMovingClipData->m_iTimelineInPoint + m_clMovingClipData->GetDuration() - 1;
			iDuration = m_clMovingClipData->GetDuration() - m_iOperatingClipFrameCount;
		}
		else
		{
			iPoint = m_clMovingClipData->m_iTimelineInPoint + m_clMovingClipData->GetDuration() - 1 + m_iOperatingClipFrameCount;
			iDuration = m_clMovingClipData->GetDuration() + m_iOperatingClipFrameCount;
		}
		strText.Format(_T("TrimingClipOutPoint  %d"), iPoint);
		dcMemDc.TextOutW(300, 45, strText);
		strText.Format(_T("TrimingClipRightPoint  %d"), rcMovingRect.right);
		dcMemDc.TextOutW(300, 65, strText);
		strText.Format(_T("TrimingClipDuration  %d"), iDuration);
		dcMemDc.TextOutW(300, 85, strText);
#endif

	}
	else
	{
		// ドロップ位置用
		CRect rcMovingRect = m_clMovingClipData->GetOperatingRect();
		//CBrush brClipMoveBrush(ACCENTCOLOR_BRUSH);
		dcMovingMemDc.FillRect(&rcMovingRect, &brClipBrush);
		//brClipMoveBrush.DeleteObject();
		dcMemDc.AlphaBlend(rcMovingRect.left, rcMovingRect.top, rcMovingRect.Width(), rcMovingRect.Height(),
			&dcMovingMemDc, rcMovingRect.left, rcMovingRect.top, rcMovingRect.Width(), rcMovingRect.Height(),
			blAlphaBlend);

#ifdef PROTOTYPEMODE
		//TODO: デバッグ
		CString strText;
		strText.Format(_T("MovingClipInPoint  %d"), m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount);
		dcMemDc.TextOutW(300, 5, strText);
		strText.Format(_T("MovingClipLeftPoint  %d"), rcMovingRect.left);
		dcMemDc.TextOutW(300, 25, strText);
		strText.Format(_T("MovingClipRightPoint  %d"), rcMovingRect.right);
		dcMemDc.TextOutW(300, 45, strText);
		strText.Format(_T("BorderClipLeftPoint  %d"), m_rcBorderRect.left);
		dcMemDc.TextOutW(300, 65, strText);
		strText.Format(_T("BorderClipRightPoint  %d"), m_rcBorderRect.right);
		dcMemDc.TextOutW(300, 85, strText);
#endif

		// マウス位置追随用
		if (!(m_rcBorderRect.EqualRect(rcMovingRect)))
		{
			CBrush brClipOverlapBrush(CLIPOVERLAPPINGCOLOR_BRUSH);
			dcMovingMemDc.FillRect(&m_rcBorderRect, &brClipOverlapBrush);
			blAlphaBlend.SourceConstantAlpha = kMovingClipOverlappingAlpha;
			dcMemDc.AlphaBlend(m_rcBorderRect.left, m_rcBorderRect.top, m_rcBorderRect.Width(), m_rcBorderRect.Height(),
				&dcMovingMemDc, m_rcBorderRect.left, m_rcBorderRect.top, m_rcBorderRect.Width(), m_rcBorderRect.Height(),
				blAlphaBlend);
			strText.Format(_T("ClipBorderLeftPoint  %d"), m_rcBorderRect.left);
			dcMemDc.TextOutW(300, 45, strText);
		}
	}
	// 仮想デバイスコンテキストビットマップの初期化・破棄
	dcMovingMemDc.SelectObject(bmMovingScreenBitmap);
	bmOldMovingScreenBitmap->DeleteObject();
	bmMovingScreenBitmap.DeleteObject();
	dcMovingMemDc.DeleteDC();
	// ---------- ここまで
	brClipBrush.DeleteObject();

	return TRUE;
}

// タイムラインカーソルの描画を行う
BOOL CControlUnitAppProtoView::DrawTimelineCursor(const CDC* dcViewDc, const CRect& rcViewRect, CDC& dcMemDc)
{
	if (dcViewDc == nullptr)
	{
		return FALSE;
	}

	//透過用デバイスコンテキスト作成
	// 仮想デバイスコンテキストを作成
	CDC dcMovingMemDc;
	dcMovingMemDc.CreateCompatibleDC(const_cast<CDC*>(dcViewDc));
	CBitmap bmMovingScreenBitmap;
	bmMovingScreenBitmap.CreateCompatibleBitmap(const_cast<CDC*>(dcViewDc), rcViewRect.Width(), rcViewRect.Height());
	CBitmap* bmOldMovingScreenBitmap = dcMovingMemDc.SelectObject(&bmMovingScreenBitmap);
	// 透過ブレンド用データ
	BLENDFUNCTION blAlphaBlend;
	blAlphaBlend.BlendOp = AC_SRC_OVER;
	blAlphaBlend.BlendFlags = 0;
	blAlphaBlend.SourceConstantAlpha = kTimelineCursorAlpha;
	blAlphaBlend.AlphaFormat = 0;

	// 描画座標を計算
	CRect rcTimelineCursorRect;
	rcTimelineCursorRect.left = m_iTimelineCursorPoint;
	rcTimelineCursorRect.right = rcTimelineCursorRect.left + kTimelineCursorThickness - 1;
	rcTimelineCursorRect.top = m_rcSeekBarRect.top;
	rcTimelineCursorRect.bottom = m_rcTimelineDataRect.bottom;

	// ラインを描画
	CBrush brTimelineCursorBrush(TIMELINECURSORCOLOR_BRUSH);
	dcMovingMemDc.FillRect(rcTimelineCursorRect, &brTimelineCursorBrush);
	brTimelineCursorBrush.DeleteObject();
	dcMemDc.AlphaBlend(rcTimelineCursorRect.left, rcTimelineCursorRect.top, rcTimelineCursorRect.Width(), rcTimelineCursorRect.Height(),
		&dcMovingMemDc, rcTimelineCursorRect.left, rcTimelineCursorRect.top, rcTimelineCursorRect.Width(), rcTimelineCursorRect.Height(),
		blAlphaBlend);

	//TODO: デバッグ
	CString strText;
	strText.Format(_T("CURSOR LINE  %d"), m_iRightFrameNumber + rcTimelineCursorRect.left);
	dcMemDc.TextOutW(5, 105, strText);

	if (m_fDragShuttling)
	{
		blAlphaBlend.SourceConstantAlpha = kTimelineCursorDragGuideLineAlpha;
		
		//TODO: 位置は検討が必要
		CString strText;
		int iOldBkMode = dcMemDc.SetBkMode(TRANSPARENT);
		COLORREF crOldTextColor = dcMemDc.SetTextColor(SEEKBARTIMECODETEXTCOLOR_BRUSH);
		strText.Format(_T("×  %d"), m_fSuttleSpeed);
		dcMemDc.TextOutW(90, m_rcTimelineControlPanelRect.bottom - 20, strText);
		dcMemDc.SetBkMode(iOldBkMode);
		dcMemDc.SetTextColor(crOldTextColor);

		//補助線の描画
		CRect rcShuttleLineRect;
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragOneSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragTowSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragFourSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragEightSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragSixteenSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragThirtyTwoSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragSixtyFourSpeed);

	}

	// 仮想デバイスコンテキストビットマップの初期化・破棄
	dcMovingMemDc.SelectObject(bmMovingScreenBitmap);
	bmOldMovingScreenBitmap->DeleteObject();
	bmMovingScreenBitmap.DeleteObject();
	dcMovingMemDc.DeleteDC();
	// ---------- ここまで
	brTimelineCursorBrush.DeleteObject();

	return TRUE;
}

// シャトル操作時のガイドラインを表示する
void CControlUnitAppProtoView::DrawShuttleGuideLine(CDC& dcMemDc, CDC& dcMovingMemDc, BLENDFUNCTION& blAlphaBlend, CRect& rcLineRect, float fGuideAreaWidth)
{
	int iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * fGuideAreaWidth));

	rcLineRect.left = m_iTimelineCursorPoint + iGuideAreaWidth - kTimelineCursorDragGuideLineThickness;
	rcLineRect.right = rcLineRect.left + kTimelineCursorDragGuideLineThickness;
	rcLineRect.top = m_rcTimelineDataRect.top;
	rcLineRect.bottom = m_rcTimelineDataRect.bottom;

	// ラインを描画
	CBrush brShuttleGuidLineBrush(TIMELINECURSORDRAGGUIDELINECOLOR_BRUSH);
	dcMovingMemDc.FillRect(rcLineRect, &brShuttleGuidLineBrush);
	dcMemDc.AlphaBlend(rcLineRect.left, rcLineRect.top, rcLineRect.Width(), rcLineRect.Height(),
		&dcMovingMemDc, rcLineRect.left, rcLineRect.top, rcLineRect.Width(), rcLineRect.Height(),
		blAlphaBlend);

	rcLineRect.left = m_iTimelineCursorPoint - iGuideAreaWidth;
	rcLineRect.right = rcLineRect.left + kTimelineCursorDragGuideLineThickness;

	// ラインを描画
	dcMovingMemDc.FillRect(rcLineRect, &brShuttleGuidLineBrush);
	brShuttleGuidLineBrush.DeleteObject();
	dcMemDc.AlphaBlend(rcLineRect.left, rcLineRect.top, rcLineRect.Width(), rcLineRect.Height(),
		&dcMovingMemDc, rcLineRect.left, rcLineRect.top, rcLineRect.Width(), rcLineRect.Height(),
		blAlphaBlend);
}


void CControlUnitAppProtoView::DrawAnimation(const int iFrame)
{
	if (m_iTimelineCursorFramePosition > iFrame)
	{
		for (m_iTimelineCursorFramePosition; m_iTimelineCursorFramePosition >= iFrame; --m_iTimelineCursorFramePosition)
		{
			Invalidate();;
		}
	}
	else
	{
		for (m_iTimelineCursorFramePosition; m_iTimelineCursorFramePosition <= iFrame; ++m_iTimelineCursorFramePosition)
		{
			Invalidate();
			Sleep(100);
		}
	}
}


BOOL CControlUnitAppProtoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}

// Viewのサイズから各表示パネルの座標を計算して設定する。
void CControlUnitAppProtoView::SetPanelRect(void)
{
	CRect rcViewRect;
	GetClientRect(&rcViewRect);

	float fViewHeight = static_cast<float>(rcViewRect.Height());
	long lViewHeight = static_cast<long>(floor((fViewHeight - static_cast<float>(m_rcSeekBarRect.Height())) / 2));

	// TODO: いずれはメンバ変数に！
	int iTimelineEditHeaderDefaltHeight = kTimelineEditHeaderDefaltHeight;
	int iTimelineControlPanelDefaultWidth = kTimelineControlPanelDefaultWidth;


	m_rcPreviewPanelRect.left = rcViewRect.left;
	m_rcPreviewPanelRect.top = rcViewRect.top;
	m_rcPreviewPanelRect.right = rcViewRect.right;
	m_rcPreviewPanelRect.bottom = rcViewRect.top + lViewHeight;

	m_rcTimelineEditPanelRect.left = rcViewRect.left;
	m_rcTimelineEditPanelRect.top = m_rcPreviewPanelRect.bottom + kSplitterHeight;
	m_rcTimelineEditPanelRect.right = rcViewRect.right;
	m_rcTimelineEditPanelRect.bottom = rcViewRect.bottom;

	// タイムラインヘッダーエリアの配置
	m_rcTimelineEditHeaderRect.CopyRect(m_rcTimelineEditPanelRect);
	m_rcTimelineEditHeaderRect.bottom = m_rcTimelineEditHeaderRect.top + iTimelineEditHeaderDefaltHeight;

	// タイムラインコントロールエリアの配置
	m_rcTimelineControlPanelRect.CopyRect(m_rcTimelineEditHeaderRect);
	m_rcTimelineControlPanelRect.right = m_rcTimelineControlPanelRect.left + iTimelineControlPanelDefaultWidth;

	// シークバーエリアの配置
	m_rcSeekBarRect.CopyRect(m_rcTimelineEditHeaderRect);
	m_rcSeekBarRect.left = m_rcTimelineControlPanelRect.right + kSplitterWidth;

	// トラックヘッダの配置
	m_rcTrackHeaderRect.CopyRect(m_rcTimelineEditPanelRect);
	m_rcTrackHeaderRect.top = m_rcTimelineEditHeaderRect.bottom + kSplitterHeight;
	m_rcTrackHeaderRect.right = m_rcTimelineControlPanelRect.right;

	// タイムラインデータエリアの配置
	m_rcTimelineDataRect.CopyRect(m_rcTimelineEditPanelRect);
	m_rcTimelineDataRect.left = m_rcSeekBarRect.left;
	m_rcTimelineDataRect.top = m_rcTrackHeaderRect.top;

	// タイムラインカーソルヒット領域の配置
	m_rcTimelineCursorHitArea.CopyRect(m_rcTimelineEditPanelRect);
	m_rcTimelineCursorHitArea.top = m_rcSeekBarRect.top;
	m_rcTimelineCursorHitArea.left = m_iTimelineCursorPoint - kTimelineCursorDragArea;
	m_rcTimelineCursorHitArea.right = m_iTimelineCursorPoint + kTimelineCursorDragArea;

	// 表示可能フレーム範囲の計算
	int iDisplayFrameCount = static_cast<int>(floor(m_rcSeekBarRect.Width() / m_fPointPerFrame));
	m_iTimelineCursorPoint = static_cast<int>(floor(m_rcSeekBarRect.Width() / 2)) + m_rcSeekBarRect.left;
	m_iLeftFrameNumber = m_iTimelineCursorFramePosition - static_cast<int>(floor((iDisplayFrameCount / 2)));
	m_iRightFrameNumber = m_iTimelineCursorFramePosition + static_cast<int>(ceil((iDisplayFrameCount / 2))) + 1;

	return;
}

// タイムラインデータ表示倍率の変更
BOOL CControlUnitAppProtoView::ChangeDisplayScale(void)
{
	int kDisplayScaleArray[13] = { 1, 2, 3, 6, 10, 30, 60, 300, 600, 1800, 3600, 18000, 36000 };
	int iArrayCount = sizeof kDisplayScaleArray / sizeof kDisplayScaleArray[0];

	if (m_iSelectedDisplayScaleNumber < 0)
	{
		m_iSelectedDisplayScaleNumber = 0;
		return FALSE;
	}
	else if (m_iSelectedDisplayScaleNumber > iArrayCount - 1)
	{
		m_iSelectedDisplayScaleNumber = iArrayCount - 1;
		return FALSE;
	}

	m_iFramePerBase = kDisplayScaleArray[m_iSelectedDisplayScaleNumber];

	m_fPointPerFrame = static_cast<float>(kSeekBarScaleBaseWidth) / static_cast<float>(m_iFramePerBase);

	if (m_iFramePerBase < kSeekBarScaleMaxCountPerBase)
	{
		m_iSeekBarScaleCountPerBase = m_iFramePerBase;
	}
	else
	{
		m_iSeekBarScaleCountPerBase = kSeekBarScaleMaxCountPerBase;
	}

	m_iSmallScaleLength = kSeekBarScaleBaseWidth / m_iSeekBarScaleCountPerBase;

	if (m_fPointPerFrame < 1)
	{
		m_iPointPerOperation = 1;
	}
	else
	{
		m_iPointPerOperation = static_cast<int>(floor(m_fPointPerFrame));
		if ((m_fPointPerFrame - m_iPointPerOperation) != 0)
		{
			return FALSE;
		}
	}

	m_fFramePerPoint = static_cast<float>(m_iFramePerBase) / static_cast<float>(kSeekBarScaleBaseWidth);

	float fFramePerScale = static_cast<float>(m_iFramePerBase) / static_cast<float>(m_iSeekBarScaleCountPerBase);
	if ((fFramePerScale - static_cast<int>(floor(fFramePerScale))) == 0)
	{
		m_iFramePerScale = m_iFramePerBase / m_iSeekBarScaleCountPerBase;
	}
	else
	{
		m_iFramePerScale = static_cast<int>(floor(fFramePerScale));
		return FALSE;
	}
	return TRUE;
}




int CControlUnitAppProtoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: ここに特定な作成コードを追加してください。

	return 0;
}


// クリック箇所の判定
BOOL CControlUnitAppProtoView::IsPointInAnyClipRect(const CPoint& point)
{
	m_fMoving = FALSE;
	if (IsPointInClipRect(point, static_cast<CRect&>(*m_clClipData1)))
	{
		CalcClipRectDisplayPoint(static_cast<CRect>(m_clClipData1), m_clClipData1);
		m_clMovingClipData = m_clClipData1;
		m_clStaticClipData = m_clClipData2;
	}
	// Clip2Hit判定
	else if (IsPointInClipRect(point, static_cast<CRect&>(*m_clClipData2)))
	{
		CalcClipRectDisplayPoint(static_cast<CRect>(m_clClipData2), m_clClipData2);
		m_clMovingClipData = m_clClipData2;
		m_clStaticClipData = m_clClipData1;
	}
	return (m_fMoving || m_fSingleInTriming || m_fSingleOutTriming);
}

BOOL CControlUnitAppProtoView::IsPointInClipRect(const CPoint& point, const CRect& rcClipRect)
{
	CRect rcHitTestRect;
	rcHitTestRect.CopyRect(rcClipRect);
	// クリップ長が規定値より短い場合は規定値幅で判定する
	if (rcClipRect.Width() < kClipHitCheckMinWidth)
	{
		int iAdditionalLength = static_cast<int>(floor((kClipHitCheckMinWidth - rcHitTestRect.Width()) / 2));
		rcHitTestRect.left -= iAdditionalLength;
		rcHitTestRect.right += iAdditionalLength;
	}
	// 入力のClipRect内にポインタが存在するか？
	if (rcHitTestRect.PtInRect(point))
	{
		// Trim判定で漏れたらMove
		m_fMoving = !(IsPointInTrimRange(point, &rcClipRect));
	}
	return (m_fMoving || m_fSingleInTriming || m_fSingleOutTriming);
}

// クリック箇所がクリップ内のトリム操作エリア内かを判定
BOOL CControlUnitAppProtoView::IsPointInTrimRange(const CPoint& point, const CRect& rcClipRect)
{

	m_fSingleInTriming = FALSE;
	m_fSingleOutTriming = FALSE;

	CRect rcTrimRect;

	// In側判定
	rcTrimRect.CopyRect(rcClipRect);
	// クリップ幅が規定値未満の場合はTrim決めうち
	if (rcTrimRect.Width() < kClipHitCheckMinWidth)
	{
		//TODO: In側映像がない場合（ClipIn点=0）OutTrimにふる
		m_fSingleInTriming = TRUE;
	}
	else
	{
		rcTrimRect.right = rcTrimRect.left + static_cast<long>(floor(rcTrimRect.Width() * kTrimAreaRate));
		if (rcTrimRect.Width() < kTrimHitCheckMinWidth)
		{
			rcTrimRect.right = rcTrimRect.left + kTrimHitCheckMinWidth;
		}		
		else if (rcTrimRect.Width() > kTrimHitCheckMaxWidth)
		{
			rcTrimRect.right = rcTrimRect.left + kTrimHitCheckMaxWidth;
		}
		m_fSingleInTriming = rcTrimRect.PtInRect(point);
	}

	if (!(m_fSingleInTriming || m_fSingleOutTriming))
	{
		// Out側判定
		rcTrimRect.CopyRect(rcClipRect);
		rcTrimRect.left = rcTrimRect.right - static_cast<long>(floor(rcTrimRect.Width() * kTrimAreaRate));
		if (rcTrimRect.Width() < kTrimHitCheckMinWidth)
		{
			rcTrimRect.left = rcTrimRect.right - kTrimHitCheckMinWidth;
		}
		else if (rcTrimRect.Width() > kTrimHitCheckMaxWidth)
		{
			rcTrimRect.left = rcTrimRect.right - kTrimHitCheckMaxWidth;
		}
		m_fSingleOutTriming = rcTrimRect.PtInRect(point);
	}

	return (m_fSingleInTriming || m_fSingleOutTriming);
}

// 操作がIn側トリム可能な範囲内かを判定して位置を調整する
BOOL CControlUnitAppProtoView::CheckInTrim(void)
{
	int iDuration = m_clMovingClipData->GetDuration();
	// 範囲チェック
	if (iDuration - m_iOperatingClipFrameCount < 1)
	{
		m_iOperatingClipFrameCount = iDuration - 1;
		return FALSE;
	}

	// 重なりチェック
	// TODO: In点の場所にクリップがあるかをサーチする。
	int iOutPoint = m_clStaticClipData->m_iTimelineInPoint + m_clStaticClipData->GetDuration() - 1;
	if ((m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount <= iOutPoint) && (m_clMovingClipData->m_iTimelineInPoint >= m_clStaticClipData->m_iTimelineInPoint))
	{
		m_iOperatingClipFrameCount = iOutPoint - m_clMovingClipData->m_iTimelineInPoint + 1;
		return FALSE;
	}

	// 範囲チェック（重なりチェックより後にやらないと0を超えてドラッグされた場合に0に設定されてしまう）
	if (m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount < 0)
	{
		m_iOperatingClipFrameCount = m_clMovingClipData->m_iTimelineInPoint * -1;
		return FALSE;
	}

	return TRUE;
}

// 操作がOut側トリム可能な範囲内かを判定して位置を調整する
BOOL CControlUnitAppProtoView::CheckOutTrim(void)
{
	// 範囲チェック
	int iDuration = m_clMovingClipData->GetDuration();
	// 範囲チェック
	if (iDuration + m_iOperatingClipFrameCount < 1)
	{
		m_iOperatingClipFrameCount = (iDuration * -1) + 1;
		return FALSE;
	}

	// 重なりチェック
	// TODO: Out点の場所にクリップがあるかをサーチする。
	int iOutPoint = m_clMovingClipData->m_iTimelineInPoint + iDuration - 1 + m_iOperatingClipFrameCount;
	if ((iOutPoint >= m_clStaticClipData->m_iTimelineInPoint) && (m_clMovingClipData->m_iTimelineInPoint <= m_clStaticClipData->m_iTimelineInPoint))
	{
		m_iOperatingClipFrameCount = m_clStaticClipData->m_iTimelineInPoint - (m_clMovingClipData->m_iTimelineInPoint + iDuration);
		return FALSE;
	}

	return TRUE;
}

// 操作がMove可能な範囲内かを判定して位置を調整する
BOOL CControlUnitAppProtoView::CheckMove(CPoint& point)
{
	// 範囲チェック
	if (m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount < 0)
	{
		m_iOperatingClipFrameCount = m_clMovingClipData->m_iTimelineInPoint * -1;
		return FALSE;
	}

	// 重なりチェック
	// TODO: 重なった先の再判定が必要（再帰処理にするか）
	CRect rcStaticClip = m_clStaticClipData->GetDisplayRect();
	int iMovingClipInFrame = m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount;
	int iMovingClipOutFrame = m_clMovingClipData->m_iTimelineInPoint + m_clMovingClipData->GetDuration() - 1 + m_iOperatingClipFrameCount;
	int iStaticClipInFrame = m_clStaticClipData->m_iTimelineInPoint;
	int iStaticClipOutFrame = m_clStaticClipData->m_iTimelineInPoint + m_clStaticClipData->GetDuration()  - 1;
	if (((iStaticClipInFrame <= iMovingClipInFrame) && (iMovingClipInFrame <= iStaticClipOutFrame)) ||
		((iStaticClipInFrame <= iMovingClipOutFrame) && (iMovingClipOutFrame <= iStaticClipOutFrame)) ||
		((iMovingClipInFrame <= iStaticClipInFrame) && (iStaticClipInFrame <= iMovingClipOutFrame)) ||
		((iMovingClipInFrame <= iStaticClipOutFrame) && (iStaticClipOutFrame <= iMovingClipOutFrame)))
	{
		int iStaticClipCenterFrame = iStaticClipInFrame + static_cast<int>(floor(m_clStaticClipData->GetDuration() / 2));
		int iDropInPoint = 0;
		if (iMovingClipInFrame <= iStaticClipCenterFrame)
		{
			iDropInPoint = iStaticClipInFrame - m_clMovingClipData->GetDuration();
		}
		else
		{
			iDropInPoint = iStaticClipOutFrame + 1;
		}
		m_iOperatingClipFrameCount = iDropInPoint - m_clMovingClipData->m_iTimelineInPoint;
		CalcClipRect(*(m_clMovingClipData->GetOperatingRect()), iDropInPoint, m_clMovingClipData->GetDuration());
		return FALSE;

	}
	
	CalcClipRectDisplayPoint(*(m_clMovingClipData->GetOperatingRect()), m_clMovingClipData, m_iOperatingClipFrameCount);
	return TRUE;
}

// クリック位置がシークバー内かを判定する
BOOL CControlUnitAppProtoView::IsPointInSeekBar(const CPoint& point)
{
	if (!(m_rcSeekBarRect.PtInRect(point)))
	{
		return FALSE;
	}
	return TRUE;
}

// クリップ位置計算
BOOL CControlUnitAppProtoView::CalcClipRectDisplayPoint(CRect& rcClipRect, const ClipDataTest* clClipData, const int& iMoveFrames /* = 0 */, 
	const int& iIntrimFrames /* = 0 */, const int& iOuttrimFrames/* = 0 */)
{
	
	if (CalcClipRect(rcClipRect, const_cast<ClipDataTest*>(clClipData)->m_iTimelineInPoint, const_cast<ClipDataTest*>(clClipData)->GetDuration(), 
		iMoveFrames, iIntrimFrames, iOuttrimFrames))
	{
		if (rcClipRect.left < m_rcTimelineDataRect.left)
		{
			rcClipRect.left = m_rcTimelineDataRect.left;
		}
		if (rcClipRect.right > m_rcTimelineDataRect.right)
		{
			rcClipRect.right = m_rcTimelineDataRect.right;
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

// クリップ位置計算（はみ出し補正なし）
BOOL CControlUnitAppProtoView::CalcClipRect(CRect& rcClipRect, const int& iInPoint, const int& iDuration, const int& iMoveFrames /* = 0 */,
	const int& iIntrimFrames /* = 0 */, const int& iOuttrimFrames/* = 0 */)
{
	rcClipRect.top = m_rcTimelineDataRect.top;
	rcClipRect.bottom = rcClipRect.top + kTrackDefaultHeight;
	int iLeftScrubingFrameCount = m_iLeftFrameNumber + m_iOperatingFrameCount;
	int iRightScrubingFrameCount = m_iRightFrameNumber + m_iOperatingFrameCount;

	if (iInPoint + iMoveFrames + iIntrimFrames > iRightScrubingFrameCount)
	{
		rcClipRect.SetRectEmpty();
		return FALSE;
	}
	if ((iInPoint + iDuration + iMoveFrames + iOuttrimFrames) < iLeftScrubingFrameCount)
	{
		rcClipRect.SetRectEmpty();
		return FALSE;
	}
	int iDisplayInPoint = iInPoint + iMoveFrames + iIntrimFrames;
	int iDisplayOutPoint = iInPoint + iDuration + iMoveFrames + iOuttrimFrames;

	rcClipRect.left = ChangeTimelineFramePositionToDisplayPoint(iDisplayInPoint);
	rcClipRect.right = ChangeTimelineFramePositionToDisplayPoint(iDisplayOutPoint);

	return TRUE;
}
// フレーム位置を画面上の座標に変換する
int CControlUnitAppProtoView::ChangeTimelineFramePositionToDisplayPoint(const int iFrame)
{
	int iXPoint;
	int iFrameCountFromTimelineCursor = iFrame - m_iTimelineCursorFramePosition - m_iOperatingFrameCount;

	// １ポイントあたりのフレーム数が１未満の場合（１フレームが複数ポイントに跨る）
	if (m_fFramePerPoint < 1)
	{
		// タイムラインカーソルからの相対座標を求める
		iXPoint = iFrameCountFromTimelineCursor * m_fPointPerFrame;
	}
	else
	{
		// タイムラインカーソルからの相対座標を求める
		iXPoint = static_cast<int>(ceil(iFrameCountFromTimelineCursor / m_fFramePerPoint));
	}
	return (iXPoint + m_iTimelineCursorPoint);
}

// クリック位置をフレーム位置に変換する
int CControlUnitAppProtoView::ChangeDisplayPointToTimelineFramePosition(const CPoint& point)
{
	int iFrame;
	int iHorizontalLengthFromTimelineCursor = point.x - m_iTimelineCursorPoint;

	// １フレームあたりのポイント数が１未満の場合
	if (m_fPointPerFrame < 1)
	{
		// タイムラインカーソルからのフレーム数を求める
		iFrame = iHorizontalLengthFromTimelineCursor * m_fFramePerPoint + m_iTimelineCursorFramePosition;
	}
	else
	{
		// タイムラインカーソルからの相対座標を求める
		iFrame = static_cast<int>(ceil(iHorizontalLengthFromTimelineCursor / m_fPointPerFrame)) + m_iTimelineCursorFramePosition;
	}
	if (iFrame < 0)
	{
		return 0;
	}
	else
	{
		return iFrame;
	}
}

// 操作量を操作フレーム数に変換する
int CControlUnitAppProtoView::ChangeOperatingDistanceToTimelineFrames(const CSize& szMoveSize, const int iStratFrame /* = 0 */)
{

	int iFrames = 0;
	if (szMoveSize.cx == 0)
	{
		return iFrames;
	}

	// １ポイントあたりのフレーム数が１未満の場合（１フレームが複数ポイントに跨る）
	if (m_fFramePerPoint < 1)
	{
		// 移動フレーム数は実際の移動長×１ポイントあたりのフレーム数（必要な幅を動かさないとフレームは動かない）
		iFrames = static_cast<int>(floor(szMoveSize.cx * m_fFramePerPoint));
	}
	else
	{
		// 表示に切りの良いフレーム位置でない場合は調整する
		int iSurPlus = iStratFrame % static_cast<int>(m_fFramePerPoint);
		if (iSurPlus == 0)
		{
			// 移動フレーム数は実際の移動長×１ポイントあたりのフレーム数（１ポイントで複数フレーム動く）
			iFrames = szMoveSize.cx * m_fFramePerPoint;
		}
		else
		{
			// （移動フレーム数は実際の移動長－１）×１ポイントあたりのフレーム数（最初の１ポイントは端数処理に使う）
			if(szMoveSize.cx < 0)
			{
				iFrames = ((szMoveSize.cx + 1) * m_fFramePerPoint) - iSurPlus;
			} 
			else 
			{
				iFrames = ((szMoveSize.cx - 1) * m_fFramePerPoint) + (static_cast<int>(m_fFramePerPoint) - iSurPlus);
			}
		}
	}
	return iFrames;
}


// シャトル操作中の速度判定
float CControlUnitAppProtoView::SetShuttleSpeed(const CPoint& point, CSize& szMoveSize)
{
	if (point.x > (m_iTimelineCursorPoint + kTimelineCursorDragArea))
	{
		return SetShuttleSpeedByMoveLength(szMoveSize.cx);
	}
	else if (point.x < (m_iTimelineCursorPoint - kTimelineCursorDragArea))
	{
		int iMoveLength = szMoveSize.cx * -1;
		return SetShuttleSpeedByMoveLength(iMoveLength) * -1;
	}
	return 0.0;
}

// シャトル操作中の速度判定（マウス移動距離から倍率を返却）
float CControlUnitAppProtoView::SetShuttleSpeedByMoveLength(int iMoveLength)
{
	// TODO: そもそも無段階にすべきか？
	// TODO: 配列なりに変更して効率よく処理したい！
	int iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragOneSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 1.0;
	}
	iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragTowSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 2.0;
	}
	iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragFourSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 4.0;
	}
	iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragEightSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 8.0;
	}
	iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragSixteenSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 16.0;
	}
	iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragThirtyTwoSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 32.0;
	}
	return 64.0;
}



// 左ダブルクリック
void CControlUnitAppProtoView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。


	CView::OnLButtonDblClk(nFlags, point);
}

// 右ダブルクリック
void CControlUnitAppProtoView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	CView::OnRButtonDblClk(nFlags, point);
}
