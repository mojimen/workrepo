
// CtrlUnitView.cpp : CCtrlUnitView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
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

// CCtrlUnitView �R���X�g���N�V����/�f�X�g���N�V����

CCtrlUnitView::CCtrlUnitView()
	: CFormView(CCtrlUnitView::IDD)
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B


	// TODO: �Ƃ肠�����͂����ɂ����Ă������A�ʓrInit�Ƃ��Ɏ����Ă���
	m_rcRect.SetRect(10, 10, 50, 50); // �e�X�g�p�}�`
	m_szRectFrameSize.cx = 5;
	m_szRectFrameSize.cy = 5; // �ړ����̎l�p�`�̘g���B
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
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

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


// CCtrlUnitView �f�f

#ifdef _DEBUG
void CCtrlUnitView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCtrlUnitView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCtrlUnitDoc* CCtrlUnitView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCtrlUnitDoc)));
	return (CCtrlUnitDoc*)m_pDocument;
}
#endif //_DEBUG


// CCtrlUnitView ���b�Z�[�W �n���h���[


void CCtrlUnitView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	m_fLButtonClicking = TRUE;
	SetCapture(); // �}�E�X���L���v�`���[( OnLButtonUp()�ŉ��)
	m_poMousePointerLocation = point;	// �ړ��ʌv�Z�̂��߁A�������W��ۑ�
	m_pRectH = NULL;

	CFormView::OnLButtonDown(nFlags, point);
}


void CCtrlUnitView::OnLButtonUp(UINT nFlags, CPoint point)
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

	CFormView::OnLButtonUp(nFlags, point);
}


void CCtrlUnitView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	m_fLButtonClicking = FALSE; // �t���O��������
	ReleaseCapture(); // �}�E�X��������܂��B
	CSize szMoveSize(point - m_poMousePointerLocation); // �}�E�X�̃{�^�����ŏ��ɉ����ꂽ�ʒu����̕Έ�
	m_rcRect += szMoveSize; // �l�p�`���A�{�^���������ꂽ�ʒu�Ɉړ�
	RedrawWindow(); // �ĕ`�悵�܂��B

	CFormView::OnMouseMove(nFlags, point);
}


void CCtrlUnitView::OnPaint()
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

}
