
// ControlUnitAppProtoView.cpp : CControlUnitAppProtoView クラスの実装
//

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
END_MESSAGE_MAP()

// CControlUnitAppProtoView コンストラクション/デストラクション

CControlUnitAppProtoView::CControlUnitAppProtoView()
{
	// TODO: 構築コードをここに追加します。

	// TODO: とりあえずはここにおいておくが、別途Initとかに持っていく
	m_clClipData1 = new ClipDataTest();
	m_clClipData2 = new ClipDataTest();
	m_clClipData1->m_iTimelineInPoint = 101;
	m_clClipData1->SetDuration(50);
	m_clClipData2->m_iTimelineInPoint = 600;
	m_clClipData2->SetDuration(100);

	//CRect rcWorkRect;
	//rcWorkRect.SetRect(10, 0, 200, 100);
	//m_clClipData1->SetCurrentRect(&rcWorkRect);
	//rcWorkRect.SetRect(500, 0, 800, 100);
	//m_clClipData2->SetCurrentRect(&rcWorkRect);
	m_fLButtonClicking = FALSE;
	m_fMoving = FALSE;
	m_fInTriming = FALSE;
	m_fOutTriming = FALSE;
	m_fScrubing = FALSE;
	m_rcPreviewPanelRect.bottom = m_rcPreviewPanelRect.top + kPreviewPanelDefaltHeight;
	m_rcControlPanelRect.bottom = m_rcControlPanelRect.top + kControlPanelDefaltHeight;
	m_rcTimelineEditPanelRect.bottom = m_rcTimelineEditPanelRect.top + kTimelineEditDefaltHeight;

	m_iLeftFrameNumber = 0;
	m_iRightFrameNumber = 0;
	m_iTimelineCursorFrameNumber = 0;
	m_iScrubingFrameCount = 0;

	m_iFramePerBase = 60;
	m_fPointPerFrame = static_cast<float>(kSeekBarScaleBaseWidth) / static_cast<float>(m_iFramePerBase);
	if (m_iFramePerBase < kSeekBarSmallScaleCount)
	{
		m_iSeekBarSmallScaleCount = m_iFramePerBase;
	} 
	else
	{
		m_iSeekBarSmallScaleCount = kSeekBarSmallScaleCount;
	}
	m_iSmallScaleLength = kSeekBarScaleBaseWidth / m_iSeekBarSmallScaleCount;

	//TestDialog td = new TestDialog();
	//td.DoModal();


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

void CControlUnitAppProtoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
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


void CControlUnitAppProtoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	if (IsPointInAnyClipRect(point))
	{
		m_fLButtonClicking = TRUE;
		SetCapture(); // マウスをキャプチャー( OnLButtonUp()で解放)
		m_poMousePointerLocation = point;	// 移動量計算のため、初期座標を保存
		m_rcMovingRect.CopyRect(m_rcClipDisplayRect);
		m_rcBorderRect.CopyRect(m_rcClipDisplayRect);
	}
	else
	{
		m_clMovingClipData = NULL;
		m_clStaticClipData = NULL;
		if (IsPointInSeekBar(point))
		{
			m_fLButtonClicking = TRUE;
			SetCapture(); // マウスをキャプチャー( OnLButtonUp()で解放)
			m_poMousePointerLocation = point;	// 移動量計算のため、初期座標を保存
			m_iScrubingFrameCount = 0;
		}
	}

	CView::OnLButtonDown(nFlags, point);
}


void CControlUnitAppProtoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	m_fLButtonClicking = FALSE; // フラグを下げる
	ReleaseCapture(); // マウスを解放します。

	CSize szMoveSize(point - m_poMousePointerLocation); // マウスのボタンが最初に押された位置からの偏移
	CRect rcWorkRect;

	if (m_fMoving)
	{
		long lMoveDistance = m_rcMovingRect.left - m_rcClipDisplayRect.left;
		m_rcClipDisplayRect.MoveToX(m_rcClipDisplayRect.left + lMoveDistance);
		m_clMovingClipData->SetDisplayRect(m_rcClipDisplayRect);
		m_rcClipRect.MoveToX(m_rcClipRect.left + lMoveDistance);
		m_clMovingClipData->SetCurrentRect(m_rcClipRect);
	} 
	else if (m_fInTriming)
	{
		m_rcClipRect.left = m_rcClipRect.left + (m_rcMovingRect.left - m_rcClipDisplayRect.left);
		m_clMovingClipData->SetCurrentRect(m_rcClipRect);
		m_rcClipDisplayRect.left = m_rcMovingRect.left;
		m_clMovingClipData->SetDisplayRect(m_rcClipDisplayRect);
	}
	else if (m_fOutTriming)
	{
		m_rcClipRect.right = m_rcClipRect.right + (m_rcMovingRect.right - m_rcClipDisplayRect.right);
		m_clMovingClipData->SetCurrentRect(m_rcClipRect);
		m_rcClipDisplayRect.right = m_rcMovingRect.right;
		m_clMovingClipData->SetDisplayRect(m_rcClipDisplayRect);
	}
	else if (m_fScrubing)
	{
		m_iTimelineCursorFrameNumber += m_iScrubingFrameCount;
	}

	m_rcClipRect.SetRectEmpty();
	m_rcClipDisplayRect.SetRectEmpty();
	m_rcMovingRect.SetRectEmpty();
	m_rcBorderRect.SetRectEmpty();
	m_iScrubingFrameCount = 0;

	Invalidate(); // 再描画します。

	m_fMoving = FALSE;
	m_fInTriming = FALSE;
	m_fOutTriming = FALSE;
	m_fScrubing = FALSE;


	CView::OnLButtonUp(nFlags, point);
}


void CControlUnitAppProtoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	if (m_fLButtonClicking) 
	{
		if (m_fMoving)
		{
			CDC* pDC = GetDC();
			CSize szMoveSize(point - m_poMousePointerLocation);
			// フレーム単位の移動幅に変換して、それをin点に足してrectを出す
			int iMoveFrame = szMoveSize.cx / m_fPointPerFrame;
			CalcClipRectDisplayPoint(m_rcClipDisplayRect, m_clMovingClipData, iMoveFrame);
			//m_rcMovingRect.CopyRect(m_rcClipDisplayRect); //  ドロップ位置のイメージ座標
			//m_rcMovingRect.MoveToX(m_rcMovingRect.left + szMoveSize.cx);
			//m_rcBorderRect.CopyRect(m_rcClipDisplayRect); //  マウス位置のイメージ座標
			//m_rcBorderRect.MoveToX(m_rcBorderRect.left + szMoveSize.cx);
			CheckMove(point);
			Invalidate();
			ReleaseDC(pDC);
		}
		else if (m_fInTriming || m_fOutTriming)
		{
			CSize szMoveSize(point - m_poMousePointerLocation);
			m_rcMovingRect.CopyRect(m_rcClipDisplayRect); // 伸縮分のイメージ座標
			if (m_fInTriming)
			{
				m_rcMovingRect.left += szMoveSize.cx;
				CheckInTrim();
			}
			else
			{
				m_rcMovingRect.right += szMoveSize.cx;
				CheckOutTrim();
			}
			Invalidate();
		}
		else if (m_fScrubing)
		{
			CSize szMoveSize(point - m_poMousePointerLocation);
			m_iScrubingFrameCount = static_cast<int>(floor(szMoveSize.cx / m_fPointPerFrame));
			if ((m_iTimelineCursorFrameNumber + m_iScrubingFrameCount) < 0)
			{
				m_iScrubingFrameCount = -1 * m_iTimelineCursorFrameNumber;
			}
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
	CBrush brBaseBrush(BASECOLOR_BRUSH);
	dcMemDc.FillRect(&rcViewRect, &brBaseBrush);

	// 枠描画
	CPen brPenBrush(PS_SOLID, kTimelineDataDisplayBorderThikness, LIGHTGRAYCOLOR_BRUSH);
	CPen* oldpen = dcMemDc.SelectObject(&brPenBrush);
	dcMemDc.Rectangle(m_rcPreviewPanelRect);
	dcMemDc.SelectObject(oldpen);

	// シークバー描画
	DrawSeekBar(dcMemDc);

	// 静止クリップ描画
	CBrush brClipBrush(CLIPCOLOR_BRUSH);
	CRect crClipRect;
	CalcClipRectDisplayPoint(crClipRect, m_clClipData1);
	dcMemDc.FillRect(&crClipRect, &brClipBrush);
	CalcClipRectDisplayPoint(crClipRect, m_clClipData2);
	dcMemDc.FillRect(&crClipRect, &brClipBrush);

	// 操作イメージ描画
	if ((m_fInTriming || m_fOutTriming || m_fMoving) && (!(m_rcMovingRect.IsRectEmpty())))
	{
		DrawOperatingClip(&dcViewDc, rcViewRect, dcMemDc);
	}

	// タイムラインカーソル描画
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


BOOL CControlUnitAppProtoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}

// Viewのサイズから各表示パネルの座標を計算して設定する。
void CControlUnitAppProtoView::SetPanelRect(void)
{
	CRect rcViewRect, rcControlPanelRect, rcPreviewPanelRect, rcTimelineEditPanelRect;
	GetClientRect(&rcViewRect);

	rcControlPanelRect.CopyRect(m_rcControlPanelRect);
	rcPreviewPanelRect.CopyRect(m_rcPreviewPanelRect);
	rcTimelineEditPanelRect.CopyRect(m_rcTimelineEditPanelRect);

	float fViewHeight = static_cast<float>(rcViewRect.Height());
	long lViewHeight = static_cast<long>(floor((fViewHeight - static_cast<float>(m_rcControlPanelRect.Height())) / 2));

	m_rcPreviewPanelRect.left = rcViewRect.left;
	m_rcPreviewPanelRect.top = rcViewRect.top;
	m_rcPreviewPanelRect.right = rcViewRect.right;
	m_rcPreviewPanelRect.bottom = rcViewRect.top + lViewHeight;

	int iControlPanelHeight = rcControlPanelRect.Height();
	m_rcControlPanelRect.left = rcViewRect.left;
	m_rcControlPanelRect.top = m_rcPreviewPanelRect.bottom + kSplitterHeight;
	m_rcControlPanelRect.right = rcViewRect.right;
	m_rcControlPanelRect.bottom = m_rcControlPanelRect.top + iControlPanelHeight;
	
	int iDisplayFrameCount = static_cast<int>(floor(m_rcControlPanelRect.Width() / m_fPointPerFrame));
	m_iLeftFrameNumber = m_iTimelineCursorFrameNumber - static_cast<int>(floor((iDisplayFrameCount / 2)));
	m_iRightFrameNumber = m_iTimelineCursorFrameNumber + static_cast<int>(ceil((iDisplayFrameCount / 2)));

	m_rcTimelineEditPanelRect.left = rcViewRect.left;
	m_rcTimelineEditPanelRect.top = m_rcControlPanelRect.bottom + kSplitterHeight;
	m_rcTimelineEditPanelRect.right = rcViewRect.right;
	m_rcTimelineEditPanelRect.bottom = rcViewRect.bottom;

	return;
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
	CRect rcClipRect1, rcClipRect2, rcHitTestRect;
	// Clip1Hit判定
	CalcClipRectDisplayPoint(rcClipRect1, m_clClipData1);
	CalcClipRectDisplayPoint(rcClipRect2, m_clClipData2);
	if (IsPointInClipRect(point, rcClipRect1, rcHitTestRect))
	{
			m_clMovingClipData = m_clClipData1;
			m_clStaticClipData = m_clClipData2;
	}
	// Clip2Hit判定
	else if (IsPointInClipRect(point, rcClipRect2, rcHitTestRect))
	{
				m_clMovingClipData = m_clClipData2;
				m_clStaticClipData = m_clClipData1;
	}
	return (m_fMoving || m_fInTriming || m_fOutTriming);
}

BOOL CControlUnitAppProtoView::IsPointInClipRect(const CPoint& point, const CRect& rcClipRect, CRect& rcHitTestRect)
{
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
		m_rcClipDisplayRect.CopyRect(rcClipRect);
	}
	return (m_fMoving || m_fInTriming || m_fOutTriming);
}

// クリック箇所がクリップ内のトリム操作エリア内かを判定
BOOL CControlUnitAppProtoView::IsPointInTrimRange(const CPoint& point, const CRect& rcClipRect)
{

	m_fInTriming = FALSE;
	m_fOutTriming = FALSE;

	CRect rcTrimRect;

	// In側判定
	rcTrimRect.CopyRect(rcClipRect);
	// クリップ幅が規定値未満の場合はTrim決めうち
	if (rcTrimRect.Width() < kClipHitCheckMinWidth)
	{
		//TODO: In側映像がない場合（ClipIn点=0）OutTrimにふる
		m_fInTriming = TRUE;
	}
	else
	{
		rcTrimRect.right = rcTrimRect.left + static_cast<long>(floor(rcTrimRect.Width() * kClipLengthRate));
		if (rcTrimRect.Width() < kTrimHitCheckMinWidth)
		{
			rcTrimRect.right = rcTrimRect.left + kTrimHitCheckMinWidth;
		}		
		else if (rcTrimRect.Width() > kTrimHitCheckMaxWidth)
		{
			rcTrimRect.right = rcTrimRect.left + kTrimHitCheckMaxWidth;
		}
		m_fInTriming = rcTrimRect.PtInRect(point);
	}

	if (!(m_fInTriming || m_fOutTriming))
	{
		// Out側判定
		rcTrimRect.CopyRect(rcClipRect);
		rcTrimRect.left = rcTrimRect.right - static_cast<long>(floor(rcTrimRect.Width() * kClipLengthRate));
		if (rcTrimRect.Width() < kTrimHitCheckMinWidth)
		{
			rcTrimRect.left = rcTrimRect.right - kTrimHitCheckMinWidth;
		}
		else if (rcTrimRect.Width() > kTrimHitCheckMaxWidth)
		{
			rcTrimRect.left = rcTrimRect.right - kTrimHitCheckMaxWidth;
		}
		m_fOutTriming = rcTrimRect.PtInRect(point);
	}

	return (m_fInTriming || m_fOutTriming);
}

// 操作がIn側トリム可能な範囲内かを判定して位置を調整する
BOOL CControlUnitAppProtoView::CheckInTrim(void)
{
	// 範囲チェック
	if (m_rcMovingRect.Width() < 1)
	{
		m_rcMovingRect.left = m_rcMovingRect.right - 1;
		return FALSE;
	}

	// 重なりチェック
	CRect rcWorkRect;
	rcWorkRect.CopyRect(m_clStaticClipData->GetDisplayRect());
	if ((rcWorkRect.left < m_rcClipDisplayRect.left) && (rcWorkRect.right >= m_rcMovingRect.left))
	{
		m_rcMovingRect.left = rcWorkRect.right + 1;
		return FALSE;
	}

	// 範囲チェック
	if (m_rcMovingRect.left < m_rcTimelineEditPanelRect.left)
	{
		m_rcMovingRect.left = m_rcTimelineEditPanelRect.left;
		return FALSE;
	}

	return TRUE;
}

// 操作がOut側トリム可能な範囲内かを判定して位置を調整する
BOOL CControlUnitAppProtoView::CheckOutTrim(void)
{
	// 範囲チェック
	if (m_rcMovingRect.Width() < 1)
	{
		m_rcMovingRect.right = m_rcMovingRect.left + 1;
		return FALSE;
	}

	// 重なりチェック
	CRect rcWorkRect;
	rcWorkRect.CopyRect(m_clStaticClipData->GetDisplayRect());
	if ((m_rcClipDisplayRect.right < rcWorkRect.right) && (m_rcMovingRect.right >= rcWorkRect.left))
	{
		m_rcMovingRect.right = rcWorkRect.left - 1;
		return FALSE;
	}

	// 範囲チェック
	if (m_rcMovingRect.right > m_rcTimelineEditPanelRect.right)
	{
		m_rcMovingRect.right = m_rcTimelineEditPanelRect.right;
		return FALSE;
	}

	return TRUE;
}

// 操作がMove可能な範囲内かを判定して位置を調整する
BOOL CControlUnitAppProtoView::CheckMove(CPoint& point)
{
	// 範囲チェック
	if (m_rcMovingRect.left < m_rcTimelineEditPanelRect.left)
	{
		m_rcMovingRect.MoveToX(m_rcTimelineEditPanelRect.left);
		return FALSE;
	}
	if (m_rcMovingRect.right > m_rcTimelineEditPanelRect.right)
	{
		m_rcMovingRect.MoveToX(m_rcTimelineEditPanelRect.right - m_rcMovingRect.Width());
		return FALSE;
	}

	// 重なりチェック
	// TODO: 重なった先の再判定が必要（再帰処理にするか）
	CRect rcStaticClip = m_clStaticClipData->GetDisplayRect();
	if (((m_rcMovingRect.left <= rcStaticClip.left) && (rcStaticClip.left <= m_rcMovingRect.right)) ||
		((m_rcMovingRect.left <= rcStaticClip.right) && (rcStaticClip.right <= m_rcMovingRect.right))||
		((rcStaticClip.left <= m_rcMovingRect.left) && (m_rcMovingRect.right <= rcStaticClip.right)) ||
		((m_rcMovingRect.left <= rcStaticClip.left) && (rcStaticClip.right <= m_rcMovingRect.right)))
	{
		long lSplitPoint = rcStaticClip.right - static_cast<long>(floor(rcStaticClip.Width() / 2));
		//if (point.x < lSplitPoint)
		if (m_rcMovingRect.left < lSplitPoint)
		{
			long lCorrectionWidth = m_rcMovingRect.right - rcStaticClip.left + 1;
			m_rcMovingRect.left -= lCorrectionWidth;
			m_rcMovingRect.right -= lCorrectionWidth;
			return FALSE;
		}
		else
		{
			long lCorrectionWidth = rcStaticClip.right - m_rcMovingRect.left + 1;
			m_rcMovingRect.left += lCorrectionWidth;
			m_rcMovingRect.right += lCorrectionWidth;
			return FALSE;
		}

	}
	
	return TRUE;
}

// シークバーの描画を行う
void CControlUnitAppProtoView::DrawSeekBar(CDC& dcMemDc)
{
	// 背景塗りつぶし
	CBrush brSeekBarBrush(SEEKBARBACKGROUNDCOLOR_BRUSH);
	dcMemDc.FillRect(m_rcControlPanelRect, &brSeekBarBrush);

	// 目盛り描画
	CPen brSeekBarBigScalePen(PS_SOLID, kSeekBarBigScaleThikness, SEEKBARSCALECOLOR_BRUSH);
	CPen brSeekBarMiddelScalePen(PS_SOLID, kSeekBarMiddleScaleThikness, SEEKBARSCALECOLOR_BRUSH);
	CPen brSeekBarSmallScalePen(PS_SOLID, kSeekBarSmallScaleThikness, SEEKBARSCALECOLOR_BRUSH);
	CPen* oldpen = dcMemDc.SelectObject(&brSeekBarMiddelScalePen);
	POINT pScaleLine;
	pScaleLine.x = m_rcControlPanelRect.left;
	pScaleLine.y = m_rcControlPanelRect.top;
	int i = m_iLeftFrameNumber + m_iScrubingFrameCount, j = 0, iOldBkMode, iFramePerSmallScale = m_iFramePerBase / m_iSeekBarSmallScaleCount;
	CString strFrameNumber;
	COLORREF crOldColor;
	while (pScaleLine.x < m_rcControlPanelRect.right)
	{
		while ((i % iFramePerSmallScale) != 0)
		{
			++i;
			pScaleLine.x += m_fPointPerFrame;
		}
		if (i >= 0)
		{
			if ((i % (kSeekBarMainLineInterval * m_iSeekBarSmallScaleCount * iFramePerSmallScale)) == 0)
			{
				// TODO: 製品はタイムコードを表示
				iOldBkMode = dcMemDc.SetBkMode(TRANSPARENT);
				crOldColor = dcMemDc.SetTextColor(SEEKBARSCALECOLOR_BRUSH);
				strFrameNumber.Format(_T("%d"), i);
				dcMemDc.TextOut(pScaleLine.x + 2, m_rcControlPanelRect.top + 2, strFrameNumber);
				dcMemDc.SetBkMode(iOldBkMode);
				dcMemDc.SetTextColor(crOldColor);

				dcMemDc.SelectObject(&brSeekBarBigScalePen);
				pScaleLine.y = m_rcControlPanelRect.top + kSeekBarBigScaleMargin;
				dcMemDc.MoveTo(pScaleLine);
				pScaleLine.y = m_rcTimelineEditPanelRect.bottom;
				dcMemDc.LineTo(pScaleLine);
				pScaleLine.x += m_iSmallScaleLength;
				i += iFramePerSmallScale;
			}
			else if ((i % (m_iSeekBarSmallScaleCount * iFramePerSmallScale)) == 0)
			{
				// TODO: デバッグ用表示なのでとる事
				iOldBkMode = dcMemDc.SetBkMode(TRANSPARENT);
				crOldColor = dcMemDc.SetTextColor(SEEKBARSCALECOLOR_BRUSH);
				strFrameNumber.Format(_T("%d"), (i % (kSeekBarMainLineInterval * m_iSeekBarSmallScaleCount)));
				dcMemDc.TextOut(pScaleLine.x + 2, m_rcControlPanelRect.top + 6, strFrameNumber);
				dcMemDc.SelectObject(&brSeekBarMiddelScalePen);
				pScaleLine.y = m_rcControlPanelRect.top + kSeekBarMiddleScaleMargin;
				dcMemDc.MoveTo(pScaleLine);
				pScaleLine.y = m_rcControlPanelRect.bottom;
				dcMemDc.LineTo(pScaleLine);
				pScaleLine.x += m_iSmallScaleLength;
				i += iFramePerSmallScale;
			}
			else
			{
				j = 0;
				while (j < (m_iSeekBarSmallScaleCount - 1) && ((i % (m_iSeekBarSmallScaleCount * iFramePerSmallScale)) != 0))
				{
					dcMemDc.SelectObject(&brSeekBarSmallScalePen);
					pScaleLine.y = m_rcControlPanelRect.top + kSeekBarSmallScaleMargin;
					dcMemDc.MoveTo(pScaleLine);
					pScaleLine.y = m_rcControlPanelRect.bottom;
					dcMemDc.LineTo(pScaleLine);
					pScaleLine.x += m_iSmallScaleLength;
					++j;
					i += iFramePerSmallScale;
				}
			}
		}
		else
		{
			pScaleLine.x += m_iSmallScaleLength;
			i += iFramePerSmallScale;
		}
	}
	dcMemDc.SelectObject(oldpen);
	strFrameNumber.Format(_T("%d"), m_iTimelineCursorFrameNumber);
	dcMemDc.TextOutW(5, 5, strFrameNumber);
	strFrameNumber.Format(_T("%d"), m_iLeftFrameNumber);
	dcMemDc.TextOutW(5, 40, strFrameNumber);
	strFrameNumber.Format(_T("%d"), m_iRightFrameNumber);
	dcMemDc.TextOutW(5, 65, strFrameNumber);

	brSeekBarBrush.DeleteObject();
	brSeekBarBigScalePen.DeleteObject();
	brSeekBarMiddelScalePen.DeleteObject();
	brSeekBarSmallScalePen.DeleteObject();

}


// 操作中クリップの描画を行う
BOOL CControlUnitAppProtoView::DrawOperatingClip(const CDC* dcViewDc, const CRect& rcViewRect, CDC& dcMemDc)
{
	if (dcViewDc == NULL)
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
	CRect crClipRect;
	CalcClipRectDisplayPoint(crClipRect, m_clMovingClipData);
	dcMemDc.FillRect(&crClipRect, &brMovingClipBrush);
	brMovingClipBrush.DeleteObject();

	CBrush brClipBrush(CLIPCOLOR_BRUSH);

	if (m_fInTriming || m_fOutTriming)
	{
		//CBrush brClipTrimBrush(ACCENTCOLOR_BRUSH);
		dcMovingMemDc.FillRect(&m_rcMovingRect, &brClipBrush);
		//brClipTrimBrush.DeleteObject();
		dcMemDc.AlphaBlend(m_rcMovingRect.left, m_rcMovingRect.top, m_rcMovingRect.Width(), m_rcMovingRect.Height(),
			&dcMovingMemDc, m_rcMovingRect.left, m_rcMovingRect.top, m_rcMovingRect.Width(), m_rcMovingRect.Height(),
			blAlphaBlend);
	}
	else
	{
		// ドロップ位置用
		//CBrush brClipMoveBrush(ACCENTCOLOR_BRUSH);
		dcMovingMemDc.FillRect(&m_rcMovingRect, &brClipBrush);
		//brClipMoveBrush.DeleteObject();
		dcMemDc.AlphaBlend(m_rcMovingRect.left, m_rcMovingRect.top, m_rcMovingRect.Width(), m_rcMovingRect.Height(),
			&dcMovingMemDc, m_rcMovingRect.left, m_rcMovingRect.top, m_rcMovingRect.Width(), m_rcMovingRect.Height(),
			blAlphaBlend);

		// マウス位置追随用
		if (!(m_rcBorderRect.EqualRect(m_rcMovingRect)))
		{
			CBrush brClipOverlapBrush(CAUTIONCOLOR_BRUSH);
			dcMovingMemDc.FillRect(&m_rcBorderRect, &brClipOverlapBrush);
			blAlphaBlend.SourceConstantAlpha = kMovingClipCautionAlpha;
			dcMemDc.AlphaBlend(m_rcBorderRect.left, m_rcBorderRect.top, m_rcBorderRect.Width(), m_rcBorderRect.Height(),
				&dcMovingMemDc, m_rcBorderRect.left, m_rcBorderRect.top, m_rcBorderRect.Width(), m_rcBorderRect.Height(),
				blAlphaBlend);
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
	if (dcViewDc == NULL)
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
	rcTimelineCursorRect.left = m_rcControlPanelRect.left + (m_iTimelineCursorFrameNumber - m_iLeftFrameNumber) * m_fPointPerFrame;
	rcTimelineCursorRect.right = rcTimelineCursorRect.left + 1;
	rcTimelineCursorRect.top = m_rcControlPanelRect.top;
	rcTimelineCursorRect.bottom = m_rcTimelineEditPanelRect.bottom;

	// ラインを描画
	CBrush brTimelineCursorBrush(TIMELINECURSORCOLOR_BRUSH);
	dcMovingMemDc.FillRect(rcTimelineCursorRect, &brTimelineCursorBrush);
	brTimelineCursorBrush.DeleteObject();
	dcMemDc.AlphaBlend(rcTimelineCursorRect.left, rcTimelineCursorRect.top, rcTimelineCursorRect.Width(), rcTimelineCursorRect.Height(),
		&dcMovingMemDc, rcTimelineCursorRect.left, rcTimelineCursorRect.top, rcTimelineCursorRect.Width(), rcTimelineCursorRect.Height(),
		blAlphaBlend);

	// 仮想デバイスコンテキストビットマップの初期化・破棄
	dcMovingMemDc.SelectObject(bmMovingScreenBitmap);
	bmOldMovingScreenBitmap->DeleteObject();
	bmMovingScreenBitmap.DeleteObject();
	dcMovingMemDc.DeleteDC();
	// ---------- ここまで
	brTimelineCursorBrush.DeleteObject();

	return TRUE;
}

// クリック位置がシークバー内かを判定する
BOOL CControlUnitAppProtoView::IsPointInSeekBar(const CPoint& point)
{
	if (!(m_rcControlPanelRect.PtInRect(point)))
	{
		return FALSE;
	}
	m_fScrubing = TRUE;
	return TRUE;
}

// クリップ位置計算
BOOL CControlUnitAppProtoView::CalcClipRectDisplayPoint(CRect& crClipRect, ClipDataTest* clClipData, int iMoveFrame /* = 0 */) 
{
	int iClipDuration = clClipData->GetDuration();
	crClipRect.top = m_rcTimelineEditPanelRect.top;
	crClipRect.bottom = crClipRect.top + kTrackDefaultHeight;
	int iLeftScrubingFrameCount = m_iLeftFrameNumber + m_iScrubingFrameCount;
	int iRightScrubingFrameCount = m_iRightFrameNumber + m_iScrubingFrameCount;

	if (clClipData->m_iTimelineInPoint + iMoveFrame > iRightScrubingFrameCount)
	{
		crClipRect.SetRectEmpty();
		return FALSE;
	}
	if ((clClipData->m_iTimelineInPoint + iMoveFrame + iClipDuration) < iLeftScrubingFrameCount)
	{
		crClipRect.SetRectEmpty();
		return FALSE;
	}
	int iDisplayInPoint = clClipData->m_iTimelineInPoint + iMoveFrame - iLeftScrubingFrameCount;
	int iDisplayOutPoint = clClipData->m_iTimelineInPoint + iMoveFrame + iClipDuration;
	if (iDisplayInPoint < 0)
	{
		iDisplayInPoint = 0;
	}
	if (iDisplayOutPoint > iRightScrubingFrameCount)
	{
		iDisplayOutPoint = iRightScrubingFrameCount;
	}
	iDisplayOutPoint -= iLeftScrubingFrameCount;
	crClipRect.left = iDisplayInPoint * m_fPointPerFrame;
	crClipRect.right = iDisplayOutPoint * m_fPointPerFrame;
	if (crClipRect.right > m_rcTimelineEditPanelRect.right)
	{
		crClipRect.right = m_rcTimelineEditPanelRect.right;
	}

}