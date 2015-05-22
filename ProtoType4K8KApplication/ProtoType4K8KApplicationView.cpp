
// ProtoType4K8KApplicationView.cpp : CProtoType4K8KApplicationView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "ProtoType4K8KApplication.h"
#endif

#include "ProtoType4K8KApplicationDoc.h"
#include "ProtoType4K8KApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProtoType4K8KApplicationView

IMPLEMENT_DYNCREATE(CProtoType4K8KApplicationView, CView)

BEGIN_MESSAGE_MAP(CProtoType4K8KApplicationView, CView)
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CProtoType4K8KApplicationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CProtoType4K8KApplicationView �R���X�g���N�V����/�f�X�g���N�V����

CProtoType4K8KApplicationView::CProtoType4K8KApplicationView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

}

CProtoType4K8KApplicationView::~CProtoType4K8KApplicationView()
{
}

BOOL CProtoType4K8KApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

// CProtoType4K8KApplicationView �`��

void CProtoType4K8KApplicationView::OnDraw(CDC* /*pDC*/)
{
	CProtoType4K8KApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
}


// CProtoType4K8KApplicationView ���


void CProtoType4K8KApplicationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CProtoType4K8KApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ����̈������
	return DoPreparePrinting(pInfo);
}

void CProtoType4K8KApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CProtoType4K8KApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}

void CProtoType4K8KApplicationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CProtoType4K8KApplicationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CProtoType4K8KApplicationView �f�f

#ifdef _DEBUG
void CProtoType4K8KApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CProtoType4K8KApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProtoType4K8KApplicationDoc* CProtoType4K8KApplicationView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProtoType4K8KApplicationDoc)));
	return (CProtoType4K8KApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CProtoType4K8KApplicationView ���b�Z�[�W �n���h���[
