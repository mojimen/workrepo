#pragma once
#include "afxwin.h"

// TimelineEditView �t�H�[�� �r���[

class TimelineEditView : public CFormView
{
	DECLARE_DYNCREATE(TimelineEditView)

protected:
	TimelineEditView();           // ���I�����Ŏg�p����� protected �R���X�g���N�^�[
	virtual ~TimelineEditView();

public:
	enum { IDD = IDD_TIMELINEEDITVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

	// �R���X�^���g�l
#define ACCENTCOLOR_BRUSH RGB(51,153,255)
#define ACCENTCOLOR_BRUSH2 RGB(51,102,255)
#define ACCENTCOLOR_BRUSH3 RGB(51,204,255)
#define ACCENTCOLOR_BRUSH4 RGB(51,255,255)
#define BLACKCOLOR_BRUSH RGB(0,0,0)
#define WHITECOLOR_BRUSH RGB(255,255,255)
#define DARKGRAYCOLOR_BRUSH RGB(102,102,102)
#define GRAYCOLOR_BRUSH RGB(153,153,153)
#define LIGHTGRAYCOLOR_BRUSH RGB(204,204,204)

#define CLIPCOLOR_BRUSH ACCENTCOLOR_BRUSH
#define BASECOLOR_BRUSH WHITECOLOR_BRUSH

private:
	const int kTrackMinHeight = 10;
	const int kTrackMaxHeight = 1000;
	const int kDisplayBaseWidth = 100;
	const int kTimelineDataDisplayBorderThikness = 5;
	const LONG kkTimelineDataDisplayMarginLeft = -10;
	const LONG kkTimelineDataDisplayMarginRight = -10;
	const LONG kkTimelineDataDisplayMarginTop = -10;
	const LONG kkTimelineDataDisplayMarginBottom = -10;

	//�\�����
private:
	int m_iScale;
	CRect m_rcTimelineDisplayRect;


	// �}�`�h���b�O�p�̃����o
private:
	CRect m_rcRect	// �ړ��Ώۂ̐}�`
		, m_rcRectV	// �ړ����̃C���[�W�i�`��j
		, m_rcRectH // �ړ����̃C���[�W�i�����j
		, *m_pRectH;
	CPoint m_poMousePointerLocation; // �}�E�X�{�^���������ꂽ�Ƃ��̈ʒu
	CSize m_szRectFrameSize; // �ړ����̎l�p�`�́A�g�̑��� (�������̕��ƁA�c�����̕�)
	BOOL m_fLButtonClicking; // �}�E�X�{�^����������Ă��邩�ǂ������L�^

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();

private:
	CStatic m_xcPictureControl;
	BOOL m_fDrawn;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


