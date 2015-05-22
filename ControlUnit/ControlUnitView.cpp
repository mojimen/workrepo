
// ControlUnitView.cpp : CControlUnitView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "ControlUnit.h"
#endif

#include "ControlUnitDoc.h"
#include "ControlUnitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CControlUnitView

IMPLEMENT_DYNCREATE(CControlUnitView, CView)

BEGIN_MESSAGE_MAP(CControlUnitView, CView)
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CControlUnitView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CControlUnitView �R���X�g���N�V����/�f�X�g���N�V����

CControlUnitView::CControlUnitView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

}

CControlUnitView::~CControlUnitView()
{
}

BOOL CControlUnitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

// CControlUnitView �`��

void CControlUnitView::OnDraw(CDC* /*pDC*/)
{
	CControlUnitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
}


// CControlUnitView ���


void CControlUnitView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CControlUnitView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ����̈������
	return DoPreparePrinting(pInfo);
}

void CControlUnitView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CControlUnitView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}

void CControlUnitView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CControlUnitView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CControlUnitView �f�f

#ifdef _DEBUG
void CControlUnitView::AssertValid() const
{
	CView::AssertValid();
}

void CControlUnitView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CControlUnitDoc* CControlUnitView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CControlUnitDoc)));
	return (CControlUnitDoc*)m_pDocument;
}
#endif //_DEBUG


// CControlUnitView ���b�Z�[�W �n���h���[
