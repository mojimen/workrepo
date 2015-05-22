
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
	// ��{�J���[
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

	// �ŗL�J���[
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
	const int kSplitterWidth = 5;					// �X�v���b�^�̕�
	const int kSplitterHeight = 5;					// �X�v���b�^�̕�
	const int kMovingClipAlpha = 128;				// �ړ����N���b�v�̃A���t�@�l
	const int kMovingClipOverlappingAlpha = 32;		// �ړ����N���b�v�̃A���t�@�l�i�z�u�s�\���j
	const double kTrimAreaRate = 0.2;				// �g�����G���A�Ƃ��Ďg�p����䗦
	const int kClipHitCheckMinWidth = 10;			// �N���b�v�����蔻��̍ŏ��ۏؕ��i������N���b�v���Z���ꍇ�Ɏg�p���镝�j
	const int kTrimHitCheckMinWidth = 5;			// �g�����`�F�b�N�Ŏg�p����ŏ����i������g�����`�F�b�N�͈͂��Z���ꍇ�Ɏg�p���镝�j
	const int kTrimHitCheckMaxWidth = 30;			// �g�����`�F�b�N�Ŏg�p����ő啝�i������g�����`�F�b�N�͈͂������ꍇ�Ɏg�p���镝�j
	const int kPreviewPanelDefaltHeight = 300;		// ���g�p�ɂȂ�
	const int kPreviewPanelMinHeight = 100;			// ���g�p�ɂȂ�

	const int kTimelineEditDefaltHeight = 300;		// �^�C�����C���f�[�^�\���p�l���̏�������
	const int kTimelineEditPanelMinHeight = 100;	// �^�C�����C���f�[�^�\���p�l���̍ŏ�����
	const int kTimelineEditHeaderDefaltHeight = 30;	// �^�C�����C���f�[�^�\���p�l���w�b�_�[�s�̏�������
	const int kTimelineControlPanelDefaultWidth = 200;	// �^�C�����C���f�[�^�\���p�l�����o���̏�����

	const int kTrackDefaultHeight = 100;			// �g���b�N�̏��������iTODO: �g���b�N�}�l�[�W���[�Ɉړ����ׂ��j
	const int kTrackMinHeight = 10;					// �g���b�N�̍ŏ�����
	const int kTrackMaxHeight = 1000;				// �g���b�N�̍ő卂��

	const int kSeekBarScaleBaseWidth = 60;			// �V�[�N�o�[�̂P�P�ʓ�����̕�
	const int kSeekBarBigScaleThikness = 1;			// �V�[�N�o�[��ڐ���̑���
	const int kSeekBarMiddleScaleThikness = 1;		// �V�[�N�o�[���ڐ���̑���
	const int kSeekBarSmallScaleThikness = 1;		// �V�[�N�o�[���ڐ���̑���
	const int kSeekBarBigScaleMargin = 10;			// �V�[�N�o�[��ڐ���̃}�[�W���i��̂݁j
	const int kSeekBarMiddleScaleMargin = 20;		// �V�[�N�o�[���ڐ���̃}�[�W���i��̂݁j
	const int kSeekBarSmallScaleMargin = 25;		// �V�[�N�o�[���ڐ���̃}�[�W���i��̂݁j
	const int kSeekBarBigScaleInterval = 10;		// �V�[�N�o�[��ڐ����`�悷��Ԋu
	const int kSeekBarScaleMaxCountPerBase = 10;	// �P�P�ʂ��ƂɃV�[�N�o�[�ڐ����`�悷��ő吔
	int kDisplayScaleArray[13];// = { 1, 2, 3, 6, 10, 30, 60, 300, 600, 1800, 3600, 18000, 36000 };

	const int kTimelineCursorAlpha = 204;					// �^�C�����C���J�[�\���̃A���t�@�l
	const int kTimelineCursorThickness = 2;					// �^�C�����C���J�[�\���̑���
	const int kTimelineCursorDragArea = 5;					// �^�C�����C���J�[�\���h���b�O���̃q�b�g�̈�i���E�ɂ��̒l���v���X���Ĕ���j
	const int kTimelineCursorDragGuideLineThickness = 1;	// �^�C�����C���J�[�\���h���b�O���̃K�C�h���C���̑���
	const int kTimelineCursorDragGuideLineAlpha = 128;		// �^�C�����C���J�[�\���h���b�O���̃K�C�h���C���̃A���t�@�l
	const float kTimelineCursorDragOneSpeed = 0.1;			// �^�C�����C���J�[�\���h���b�O���́~�P�{�ړ��͈�
	const float kTimelineCursorDragTowSpeed = 0.2;			// �^�C�����C���J�[�\���h���b�O���́~�Q�{�ړ��͈�
	const float kTimelineCursorDragFourSpeed = 0.28;		// �^�C�����C���J�[�\���h���b�O���́~�S�{�ړ��͈�
	const float kTimelineCursorDragEightSpeed = 0.36;		// �^�C�����C���J�[�\���h���b�O���́~�W�{�ړ��͈�
	const float kTimelineCursorDragSixteenSpeed = 0.42;		// �^�C�����C���J�[�\���h���b�O���́~�P�U�{�ړ��͈�
	const float kTimelineCursorDragThirtyTwoSpeed = 0.47;	// �^�C�����C���J�[�\���h���b�O���́~�R�Q�{�ړ��͈�
	const float kTimelineCursorDragSixtyFourSpeed = 0.5;	// �^�C�����C���J�[�\���h���b�O���́~�U�S�{�ړ��͈�


	//�\�����
private:
	CRect m_rcPreviewPanelRect;
	CRect m_rcTimelineEditPanelRect;
	CRect m_rcTimelineEditHeaderRect;
	CRect m_rcTimelineControlPanelRect;
	CRect m_rcSeekBarRect;
	CRect m_rcTrackHeaderRect;
	CRect m_rcTimelineDataRect;
	CRect m_rcTimelineCursorHitArea;

	int m_iTimelineCursorFramePosition;	// �^�C�����C���J�[�\���ʒu�̃t���[���ԍ�
	int m_iLeftFrameNumber;				// �^�C�����C���f�[�^�\���͈͂̐擪�t���[��
	int m_iRightFrameNumber;			// �^�C�����C���f�[�^�\���͈͂̍ŏI�t���[��
	int m_iOperatingFrameCount;			// ���쒆�̈ړ��t���[����
	int m_iOperatingClipFrameCount;		// ���쒆�N���b�v�̈ړ��^�L�k�t���[����
	int m_fSuttleSpeed;					// �V���g�����쒆�̈ړ��X�s�[�h�i�{�j
	int m_iFramePerBase;				// �P�P�ʂ�����ɕ\������t���[����
	int m_iSelectedDisplayScaleNumber;	// �I�𒆂̕\���{���ԍ�
	int m_iFramePerScale;				// �P�ڐ��肠����ɕ\������t���[����
	float m_fFramePerPoint;				// �P�|�C���g������̃t���[����
	float m_fPointPerFrame;				// �P�t���[��������̃|�C���g��
	int m_iPointPerOperation;			// �P����ňړ�����|�C���g��
	int m_iSeekBarScaleCountPerBase;	// �P�P�ʓ�����ɕ\������ڐ��萔
	int m_iSmallScaleLength;			// �P�ڐ���̒���
	int m_iTimelineCursorPoint;			// �^�C�����C���J�[�\���̕`��ʒu

	void SetPanelRect(void);
	BOOL CalcClipRectDisplayPoint(CRect& crClipRect, ClipDataTest* clClipData, int iMoveFrame = 0, int iIntrimFrames = 0, int iOuttrimFrames = 0);
	BOOL ChangeDisplayScale(void);
	int ChangeTimelineFramePositionToDisplayPoint(const int iFrame);
	int ChangeDisplayPointToTimelineFramePosition(const CPoint& point);
	int ChangeOperatingDistanceToTimelineFrames(const CSize& szMoveSize, const int iStratFrame = 0);

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
	BOOL m_fLButtonClicking;	// �}�E�X�{�^����������Ă��邩�ǂ������L�^
	BOOL m_fMoving;				// Move���쒆
	BOOL m_fInTriming;			// In��SingleTrim���쒆
	BOOL m_fOutTriming;			// Out��SingleTrim���쒆
	BOOL m_fScrubing;			// Scrub���쒆
	BOOL m_fShuttling;			// Shuttle���쒆

	BOOL IsPointInAnyClipRect(const CPoint& point);
	BOOL IsPointInClipRect(const CPoint& point, const CRect& rcClipRect, CRect& rcHitTestRect);
	BOOL IsPointInTrimRange(const CPoint& point, const CRect& rcClipRect);
	BOOL CheckInTrim(void);
	BOOL CheckOutTrim(void);
	BOOL CheckMove(CPoint& point);

	BOOL IsPointInSeekBar(const CPoint& point);
	float SetShuttleSpeed(const CPoint& point, CSize& szMoveSize);
	float SetShuttleSpeedByMoveLength(int iMoveLength);

	// �`��
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

#ifndef _DEBUG  // ControlUnitAppProtoView.cpp �̃f�o�b�O �o�[�W����
inline CControlUnitAppProtoDoc* CControlUnitAppProtoView::GetDocument() const
   { return reinterpret_cast<CControlUnitAppProtoDoc*>(m_pDocument); }
#endif

