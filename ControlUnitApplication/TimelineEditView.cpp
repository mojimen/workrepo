// TimelineEditView.cpp : �����t�@�C��
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
	// TODO: �Ƃ肠�����͂����ɂ����Ă������A�ʓrInit�Ƃ��Ɏ����Ă���
	m_rcRect.SetRect(10, 10, 50, 50); // �e�X�g�p�}�`
	m_szRectFrameSize.cx = 5;
	m_szRectFrameSize.cy = 5; // �ړ����̎l�p�`�̘g���B
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


// TimelineEditView �f�f

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


// TimelineEditView ���b�Z�[�W �n���h���[


void TimelineEditView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	m_fLButtonClicking = TRUE;
	SetCapture(); // �}�E�X���L���v�`���[( OnLButtonUp()�ŉ��)
	m_poMousePointerLocation = point;	// �ړ��ʌv�Z�̂��߁A�������W��ۑ�
	m_pRectH = NULL;

	CView::OnLButtonDown(nFlags, point);
}

//�ړ����̏�Ԃ�\�����߂ɁADrawDragRect() �ŁA�g rcRectV ��\��
//rcRectV �� m_rcRectH �ɃR�s�[���A�����ړ����閈�� rcRectV ��\���� m_rcRectH ������
void TimelineEditView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	if (m_fLButtonClicking == 1)
	{
		CDC* pDC = GetDC();
		CSize szMoveSize(point - m_poMousePointerLocation);
		m_rcRectV = m_rcRect + szMoveSize; // rcRectV ���A�}�E�X�ʒu�̃C���[�W���W�Ƃ���
		pDC->DrawDragRect(&m_rcRectV, m_szRectFrameSize, m_pRectH, m_szRectFrameSize);
		m_rcRectH = m_rcRectV;
		m_pRectH = &m_rcRectH;
		ReleaseDC(pDC);
	}

	CView::OnMouseMove(nFlags, point);
}

void TimelineEditView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	m_fLButtonClicking = FALSE; // �t���O��������
	ReleaseCapture(); // �}�E�X��������܂��B
	CSize szMoveSize(point - m_poMousePointerLocation); // �}�E�X�̃{�^�����ŏ��ɉ����ꂽ�ʒu����̕Έ�
	m_rcRect += szMoveSize; // �l�p�`���A�{�^���������ꂽ�ʒu�Ɉړ�
	RedrawWindow(); // �ĕ`�悵�܂��B
	// OnMouseMove() �ŕ\���������e(�ړ����̎l�p�`)�́A������܂��B


	CView::OnLButtonUp(nFlags, point);
}

HBRUSH TimelineEditView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: ������ DC �̑�����ύX���Ă��������B

	// TODO: ����l���g�p�������Ȃ��ꍇ�͕ʂ̃u���V��Ԃ��܂��B

	 //�_�C�A���O�̐F�ύX
	if (nCtlColor == CTLCOLOR_DLG)
	{
		if (*pWnd == *this)
		{
			// �w�i�F
			hbr = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		}
	}
	return hbr;
}


void TimelineEditView::OnPaint()
{
	CPaintDC dcViewDc(this); // device context for painting
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
	// �`�惁�b�Z�[�W�� CFormView::OnPaint() ���Ăяo���Ȃ��ł��������B

	// View�G���A�̕\�������擾
	CRect rcViewRect;
	GetClientRect(&rcViewRect);

	m_rcTimelineDisplayRect.CopyRect(rcViewRect);
	m_rcTimelineDisplayRect.InflateRect(kkTimelineDataDisplayMarginLeft, kkTimelineDataDisplayMarginTop, kkTimelineDataDisplayMarginRight, kkTimelineDataDisplayMarginBottom);

	//--------- ��������_�u���o�b�t�@�p�R�[�h
	// ���z�f�o�C�X�R���e�L�X�g���쐬
	CDC dcMemDc;
	dcMemDc.CreateCompatibleDC(&dcViewDc);
	CBitmap bmOffScreenBitmap;
	bmOffScreenBitmap.CreateCompatibleBitmap(&dcViewDc, rcViewRect.Width(), rcViewRect.Height());
	CBitmap* bmOldOffScreenBitmap = dcMemDc.SelectObject(&bmOffScreenBitmap);
	//---------- �����܂�

	//�w�i�`��
	CBrush brBaseBrush(BASECOLOR_BRUSH);
	dcMemDc.FillRect(&rcViewRect, &brBaseBrush);

	// �g�`��
	CPen brPenBrush(PS_SOLID, kTimelineDataDisplayBorderThikness, DARKGRAYCOLOR_BRUSH);
	CPen* oldpen = dcMemDc.SelectObject(&brPenBrush);
	dcMemDc.Rectangle(m_rcTimelineDisplayRect);
	dcMemDc.SelectObject(oldpen);

	CBrush brClipBrush(CLIPCOLOR_BRUSH);
	dcMemDc.FillRect(&m_rcRect, &brClipBrush);


	//--------- ��������_�u���o�b�t�@�p�R�[�h
	// �`��
	BitBlt(dcViewDc.GetSafeHdc(), 0, 0, rcViewRect.Width(), rcViewRect.Height(), dcMemDc.GetSafeHdc(), 0, 0, SRCCOPY);
	//���z�f�o�C�X�R���e�L�X�g�r�b�g�}�b�v�̏������E�j��
	dcMemDc.SelectObject(bmOffScreenBitmap);
	bmOldOffScreenBitmap->DeleteObject();
	bmOffScreenBitmap.DeleteObject();
	dcMemDc.DeleteDC();
	//---------- �����܂�
	brBaseBrush.DeleteObject();
	brPenBrush.DeleteObject();
	brClipBrush.DeleteObject();




	//CFormView::OnPaint();
}


BOOL TimelineEditView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	return TRUE;
	//return CFormView::OnEraseBkgnd(pDC);
}
