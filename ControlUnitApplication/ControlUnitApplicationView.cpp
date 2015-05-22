
// ControlUnitApplicationView.cpp : CControlUnitApplicationView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "ControlUnitApplication.h"
#endif

#include "ControlUnitApplicationDoc.h"
#include "ControlUnitApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define CLIP_COLOR RGB(128,128,128)

// CControlUnitApplicationView

IMPLEMENT_DYNCREATE(CControlUnitApplicationView, CView)

BEGIN_MESSAGE_MAP(CControlUnitApplicationView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CControlUnitApplicationView �R���X�g���N�V����/�f�X�g���N�V����

CControlUnitApplicationView::CControlUnitApplicationView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

	// TODO: �Ƃ肠�����͂����ɂ����Ă������A�ʓrInit�Ƃ��Ɏ����Ă���
	m_rcRect.SetRect(10, 10, 50, 50); // �e�X�g�p�}�`
	m_szRectFrameSize.cx = 5;
	m_szRectFrameSize.cy = 5; // �ړ����̎l�p�`�̘g���B
	m_fLButtonClicking = FALSE;

}

CControlUnitApplicationView::~CControlUnitApplicationView()
{
}

BOOL CControlUnitApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

// CControlUnitApplicationView �`��

void CControlUnitApplicationView::OnDraw(CDC* pDC)
{
	CControlUnitApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B


	CBrush BR;
	BR.CreateSolidBrush(CLIP_COLOR);
	pDC->FillRect(&m_rcRect, &BR);

}

void CControlUnitApplicationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CControlUnitApplicationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CControlUnitApplicationView �f�f

#ifdef _DEBUG
void CControlUnitApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CControlUnitApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CControlUnitApplicationDoc* CControlUnitApplicationView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CControlUnitApplicationDoc)));
	return (CControlUnitApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CControlUnitApplicationView ���b�Z�[�W �n���h���[


void CControlUnitApplicationView::OnLButtonDown(UINT nFlags, CPoint point)
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
void CControlUnitApplicationView::OnMouseMove(UINT nFlags, CPoint point)
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


void CControlUnitApplicationView::OnLButtonUp(UINT nFlags, CPoint point)
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
