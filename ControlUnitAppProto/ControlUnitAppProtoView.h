
// ControlUnitAppProtoView.h : CControlUnitAppProtoView クラスのインターフェイス
//

#pragma once

class ClipDataTest;

class CControlUnitAppProtoView : public CView
{
protected: // シリアル化からのみ作成します。
	CControlUnitAppProtoView();
	DECLARE_DYNCREATE(CControlUnitAppProtoView)

// 属性
public:
	CControlUnitAppProtoDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CControlUnitAppProtoView();
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

	// コンスタント値
	// 基本カラー
#define ACCENTCOLOR_BRUSH RGB(51,153,255)
#define ACCENTCOLOR_BRUSH2 RGB(51,102,255)
#define ACCENTCOLOR_BRUSH3 RGB(51,204,255)
#define ACCENTCOLOR_BRUSH4 RGB(51,255,255)
#define CAUTIONCOLOR_BRUSH RGB(255,0,0)

#define BLACKCOLOR_BRUSH RGB(0,0,0)
#define WHITECOLOR_BRUSH RGB(255,255,255)
#define DARKGRAYCOLOR_BRUSH RGB(102,102,102)
#define GRAYCOLOR_BRUSH RGB(153,153,153)
#define LIGHTGRAYCOLOR_BRUSH RGB(204,204,204)

	// 固有カラー
#define CLIPCOLOR_BRUSH ACCENTCOLOR_BRUSH
#define CLIPOVERLAPPINGCOLOR_BRUSH CAUTIONCOLOR_BRUSH
#define BASECOLOR_BRUSH WHITECOLOR_BRUSH

#define TIMELINECONTROLPANELBACKGROUNDCOLOR_BRUSH ACCENTCOLOR_BRUSH2
#define SEEKBARBACKGROUNDCOLOR_BRUSH ACCENTCOLOR_BRUSH2
#define SEEKBARBIGSCALECOLOR_BRUSH LIGHTGRAYCOLOR_BRUSH
#define SEEKBARMIDDLESCALECOLOR_BRUSH RGB(255,204,204)
#define SEEKBARSMALLSCALECOLOR_BRUSH RGB(255,255,204)
#define SEEKBARTIMECODETEXTCOLOR_BRUSH LIGHTGRAYCOLOR_BRUSH
#define SEEKBARBIGSCALELINECOLOR_BRUSH SEEKBARBIGSCALECOLOR_BRUSH
#define SEEKBARMIDDLESCALELINECOLOR_BRUSH SEEKBARMIDDLESCALECOLOR_BRUSH
#define SEEKBARSMALLSCALELINECOLOR_BRUSH SEEKBARSMALLSCALECOLOR_BRUSH
#define TIMELINECURSORCOLOR_BRUSH RGB(255,0,255)
#define TIMELINECURSORDRAGGUIDELINECOLOR_BRUSH ACCENTCOLOR_BRUSH


private:
	const int kSplitterWidth = 5;					// スプリッタの幅
	const int kSplitterHeight = 5;					// スプリッタの幅
	const int kMovingClipAlpha = 128;				// 移動中クリップのアルファ値
	const int kMovingClipOverlappingAlpha = 32;		// 移動中クリップのアルファ値（配置不能時）
	const double kTrimAreaRate = 0.2;				// トリムエリアとして使用する比率
	const int kClipHitCheckMinWidth = 10;			// クリップ当たり判定の最小保証幅（これよりクリップが短い場合に使用する幅）
	const int kTrimHitCheckMinWidth = 5;			// トリムチェックで使用する最小幅（これよりトリムチェック範囲が短い場合に使用する幅）
	const int kTrimHitCheckMaxWidth = 30;			// トリムチェックで使用する最大幅（これよりトリムチェック範囲が長い場合に使用する幅）
	const int kPreviewPanelDefaltHeight = 300;		// 未使用になる
	const int kPreviewPanelMinHeight = 100;			// 未使用になる

	const int kTimelineEditDefaltHeight = 300;		// タイムラインデータ表示パネルの初期高さ
	const int kTimelineEditPanelMinHeight = 100;	// タイムラインデータ表示パネルの最小高さ
	const int kTimelineEditHeaderDefaltHeight = 30;	// タイムラインデータ表示パネルヘッダー行の初期高さ
	const int kTimelineControlPanelDefaultWidth = 200;	// タイムラインデータ表示パネル見出しの初期幅

	const int kTrackDefaultHeight = 100;			// トラックの初期高さ（TODO: トラックマネージャーに移動すべき）
	const int kTrackMinHeight = 10;					// トラックの最小高さ
	const int kTrackMaxHeight = 1000;				// トラックの最大高さ

	const int kSeekBarScaleBaseWidth = 60;			// シークバーの１単位当たりの幅
	const int kSeekBarBigScaleThikness = 1;			// シークバー大目盛りの太さ
	const int kSeekBarMiddleScaleThikness = 1;		// シークバー中目盛りの太さ
	const int kSeekBarSmallScaleThikness = 1;		// シークバー小目盛りの太さ
	const int kSeekBarBigScaleMargin = 10;			// シークバー大目盛りのマージン（上のみ）
	const int kSeekBarMiddleScaleMargin = 20;		// シークバー中目盛りのマージン（上のみ）
	const int kSeekBarSmallScaleMargin = 25;		// シークバー小目盛りのマージン（上のみ）
	const int kSeekBarBigScaleInterval = 10;		// シークバー大目盛りを描画する間隔
	const int kSeekBarScaleMaxCountPerBase = 10;	// １単位ごとにシークバー目盛りを描画する最大数
	int kDisplayScaleArray[13];// = { 1, 2, 3, 6, 10, 30, 60, 300, 600, 1800, 3600, 18000, 36000 };

	const int kTimelineCursorAlpha = 204;					// タイムラインカーソルのアルファ値
	const int kTimelineCursorThickness = 2;					// タイムラインカーソルの太さ
	const int kTimelineCursorDragArea = 5;					// タイムラインカーソルドラッグ時のヒット領域（左右にこの値をプラスして判定）
	const int kTimelineCursorDragGuideLineThickness = 1;	// タイムラインカーソルドラッグ時のガイドラインの太さ
	const int kTimelineCursorDragGuideLineAlpha = 128;		// タイムラインカーソルドラッグ時のガイドラインのアルファ値
	const float kTimelineCursorDragOneSpeed = 0.1;			// タイムラインカーソルドラッグ時の×１倍移動範囲
	const float kTimelineCursorDragTowSpeed = 0.2;			// タイムラインカーソルドラッグ時の×２倍移動範囲
	const float kTimelineCursorDragFourSpeed = 0.28;		// タイムラインカーソルドラッグ時の×４倍移動範囲
	const float kTimelineCursorDragEightSpeed = 0.36;		// タイムラインカーソルドラッグ時の×８倍移動範囲
	const float kTimelineCursorDragSixteenSpeed = 0.42;		// タイムラインカーソルドラッグ時の×１６倍移動範囲
	const float kTimelineCursorDragThirtyTwoSpeed = 0.47;	// タイムラインカーソルドラッグ時の×３２倍移動範囲
	const float kTimelineCursorDragSixtyFourSpeed = 0.5;	// タイムラインカーソルドラッグ時の×６４倍移動範囲


	//表示情報
private:
	CRect m_rcPreviewPanelRect;
	CRect m_rcTimelineEditPanelRect;
	CRect m_rcTimelineEditHeaderRect;
	CRect m_rcTimelineControlPanelRect;
	CRect m_rcSeekBarRect;
	CRect m_rcTrackHeaderRect;
	CRect m_rcTimelineDataRect;
	CRect m_rcTimelineCursorHitArea;

	int m_iTimelineCursorFramePosition;	// タイムラインカーソル位置のフレーム番号
	int m_iLeftFrameNumber;				// タイムラインデータ表示範囲の先頭フレーム
	int m_iRightFrameNumber;			// タイムラインデータ表示範囲の最終フレーム
	int m_iOperatingFrameCount;			// 操作中の移動フレーム数
	int m_iOperatingClipFrameCount;		// 操作中クリップの移動／伸縮フレーム数
	int m_fSuttleSpeed;					// シャトル操作中の移動スピード（倍）
	int m_iFramePerBase;				// １単位あたりに表示するフレーム数
	int m_iSelectedDisplayScaleNumber;	// 選択中の表示倍率番号
	int m_iFramePerScale;				// １目盛りあたりに表示するフレーム数
	float m_fFramePerPoint;				// １ポイントあたりのフレーム数
	float m_fPointPerFrame;				// １フレームあたりのポイント数
	int m_iPointPerOperation;			// １操作で移動するポイント長
	int m_iSeekBarScaleCountPerBase;	// １単位当たりに表示する目盛り数
	int m_iSmallScaleLength;			// １目盛りの長さ
	int m_iTimelineCursorPoint;			// タイムラインカーソルの描画位置

	void SetPanelRect(void);
	BOOL CalcClipRectDisplayPoint(CRect& crClipRect, ClipDataTest* clClipData, int iMoveFrame = 0, int iIntrimFrames = 0, int iOuttrimFrames = 0);
	BOOL ChangeDisplayScale(void);
	int ChangeTimelineFramePositionToDisplayPoint(const int iFrame);
	int ChangeDisplayPointToTimelineFramePosition(const CPoint& point);
	int ChangeOperatingDistanceToTimelineFrames(const CSize& szMoveSize, const int iStratFrame = 0);

	// 仮想クリップ
	ClipDataTest* m_clClipData1;
	ClipDataTest* m_clClipData2;
	ClipDataTest* m_clMovingClipData;
	ClipDataTest* m_clStaticClipData;

	// 図形ドラッグ用
private:
	CRect m_rcClipRect			// 移動対象の図形（相対座標管理）
		, m_rcClipDisplayRect	// 移動対象の図形（絶対座標管理）
		, m_rcMovingRect		// 移動中のイメージ（ドロップ箇所）
		, m_rcBorderRect;		// 移動中のイメージ（移動枠）
	CPoint m_poMousePointerLocation; // マウスボタンが押されたときの位置
	BOOL m_fLButtonClicking;	// マウスボタンが押されているかどうかを記録
	BOOL m_fMoving;				// Move操作中
	BOOL m_fInTriming;			// In側SingleTrim操作中
	BOOL m_fOutTriming;			// Out側SingleTrim操作中
	BOOL m_fScrubing;			// Scrub操作中
	BOOL m_fShuttling;			// Shuttle操作中

	BOOL IsPointInAnyClipRect(const CPoint& point);
	BOOL IsPointInClipRect(const CPoint& point, const CRect& rcClipRect, CRect& rcHitTestRect);
	BOOL IsPointInTrimRange(const CPoint& point, const CRect& rcClipRect);
	BOOL CheckInTrim(void);
	BOOL CheckOutTrim(void);
	BOOL CheckMove(CPoint& point);

	BOOL IsPointInSeekBar(const CPoint& point);
	float SetShuttleSpeed(const CPoint& point, CSize& szMoveSize);
	float SetShuttleSpeedByMoveLength(int iMoveLength);

	// 描画
	void DrawTimelineControlPanel(CDC& dcMemDc);
	void DrawSeekBar(CDC& dcMemDc);
	void DrawBigScale(CDC& dcMemDc, const int iDrawFrame, const CPen& brScalePen, const CPen& brLinePen, POINT& pScaleLine);
	void DrawMiddleScale(CDC& dcMemDc, const int iDrawFrame, const CPen& brScalePen, const CPen& brLinePen, POINT& pScaleLine);
	void DrawSmallScale(CDC& dcMemDc, const int iDrawFrame, const CPen& brScalePen, const CPen& brLinePen, POINT& pScaleLine);
	BOOL DrawOperatingClip(const CDC* dcViewDc, const CRect& rcViewRect, CDC& dcMemDc);
	BOOL DrawTimelineCursor(const CDC* dcViewDc, const CRect& rcViewRect, CDC& dcMemDc);
	void DrawShuttleGuideLine(CDC& dcMemDc, CDC& dcMovingMemDc, BLENDFUNCTION& blAlphaBlend, CRect& rcShuttleLineRect, float fGuideAreaWidth);
	void DrawAnimation(const int iFrame);

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ControlUnitAppProtoView.cpp のデバッグ バージョン
inline CControlUnitAppProtoDoc* CControlUnitAppProtoView::GetDocument() const
   { return reinterpret_cast<CControlUnitAppProtoDoc*>(m_pDocument); }
#endif

