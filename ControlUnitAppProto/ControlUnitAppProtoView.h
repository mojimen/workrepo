
// ControlUnitAppProtoView.h : CControlUnitAppProtoView �N���X�̃C���^�[�t�F�C�X
//

#pragma once

class ClipDataTest;

class CControlUnitAppProtoView : public CView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CControlUnitAppProtoView();
	DECLARE_DYNCREATE(CControlUnitAppProtoView)

// ����
public:
	CControlUnitAppProtoDoc* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����
public:
	virtual ~CControlUnitAppProtoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	// �R���X�^���g�l
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

#define CLIPCOLOR_BRUSH ACCENTCOLOR_BRUSH
#define BASECOLOR_BRUSH WHITECOLOR_BRUSH
#define SEEKBARBACKGROUNDCOLOR_BRUSH ACCENTCOLOR_BRUSH2
#define SEEKBARSCALECOLOR_BRUSH LIGHTGRAYCOLOR_BRUSH
#define TIMELINECURSORCOLOR_BRUSH RGB(255,0,255)


private:
	const int kSplitterHeight = 5;
	const int kMovingClipAlpha = 128;
	const int kMovingClipCautionAlpha = 32;
	const int kClipHitCheckMinWidth = 10;
	const int kTrimHitCheckMinWidth = 5;
	const int kTrimHitCheckMaxWidth = 30;
	const int kControlPanelDefaltHeight = 30;
	const int kControlPanelMinHeight = 10;
	const int kPreviewPanelDefaltHeight = 300;
	const int kPreviewPanelMinHeight = 100;
	const int kTimelineEditDefaltHeight = 300;
	const int kTimelineEditPanelMinHeight = 100;
	const int kTrackDefaultHeight = 100;
	const int kTrackMinHeight = 10;
	const int kTrackMaxHeight = 1000;
	const int kSeekBarScaleBaseWidth = 60;
	const int kSeekBarBigScaleThikness = 1;
	const int kSeekBarMiddleScaleThikness = 1;
	const int kSeekBarSmallScaleThikness = 1;
	const int kSeekBarBigScaleMargin = 10;
	const int kSeekBarMiddleScaleMargin = 20;
	const int kSeekBarSmallScaleMargin = 25;
	const int kSeekBarMainLineInterval = 10;
	const int kSeekBarSmallScaleCount = 10;
	const int kSeekBarScrollWait = 10;
	const int kTimelineCursorAlpha = 204;
	const int kTimelineDataDisplayBorderThikness = 3;
	const LONG kkTimelineDataDisplayMarginLeft = 0;
	const LONG kkTimelineDataDisplayMarginRight = 0;
	const LONG kkTimelineDataDisplayMarginTop = 0;
	const LONG kkTimelineDataDisplayMarginBottom = 0;

	const double kClipLengthRate = 0.2;

	//�\�����
private:
	int m_iScale;
	CRect m_rcControlPanelRect;
	CRect m_rcPreviewPanelRect;
	CRect m_rcTimelineEditPanelRect;

	int m_iLeftFrameNumber;
	int m_iRightFrameNumber;
	int m_iScrubingFrameCount;
	int m_iTimelineCursorFrameNumber;
	float m_fPointPerFrame;
	int m_iFramePerBase;
	int m_iSeekBarSmallScaleCount;
	int m_iSmallScaleLength;

	void SetPanelRect(void);
	BOOL CalcClipRectDisplayPoint(CRect& crClipRect, ClipDataTest* clClipData, int iMoveFrame = 0);

	// ���z�N���b�v
	ClipDataTest* m_clClipData1;
	ClipDataTest* m_clClipData2;
	ClipDataTest* m_clMovingClipData;
	ClipDataTest* m_clStaticClipData;

	// �}�`�h���b�O�p
private:
	CRect m_rcClipRect			// �ړ��Ώۂ̐}�`�i���΍��W�Ǘ��j
		, m_rcClipDisplayRect	// �ړ��Ώۂ̐}�`�i��΍��W�Ǘ��j
		, m_rcMovingRect		// �ړ����̃C���[�W�i�h���b�v�ӏ��j
		, m_rcBorderRect;		// �ړ����̃C���[�W�i�ړ��g�j
	CPoint m_poMousePointerLocation; // �}�E�X�{�^���������ꂽ�Ƃ��̈ʒu
	CSize m_szRectFrameSize; // �ړ����̎l�p�`�́A�g�̑��� (�������̕��ƁA�c�����̕�)
	BOOL m_fLButtonClicking; // �}�E�X�{�^����������Ă��邩�ǂ������L�^
	BOOL m_fMoving;
	BOOL m_fInTriming;
	BOOL m_fOutTriming;
	BOOL m_fScrubing;

	BOOL IsPointInAnyClipRect(const CPoint& point);
	BOOL IsPointInClipRect(const CPoint& point, const CRect& rcClipRect, CRect& rcHitTestRect);
	BOOL IsPointInTrimRange(const CPoint& point, const CRect& rcClipRect);
	BOOL CheckInTrim(void);
	BOOL CheckOutTrim(void);
	BOOL CheckMove(CPoint& point);

	BOOL IsPointInSeekBar(const CPoint& point);
	void DrawSeekBar(CDC& dcMemDc);
	BOOL DrawOperatingClip(const CDC* dcViewDc, const CRect& rcViewRect, CDC& dcMemDc);
	BOOL DrawTimelineCursor(const CDC* dcViewDc, const CRect& rcViewRect, CDC& dcMemDc);


public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // ControlUnitAppProtoView.cpp �̃f�o�b�O �o�[�W����
inline CControlUnitAppProtoDoc* CControlUnitAppProtoView::GetDocument() const
   { return reinterpret_cast<CControlUnitAppProtoDoc*>(m_pDocument); }
#endif

