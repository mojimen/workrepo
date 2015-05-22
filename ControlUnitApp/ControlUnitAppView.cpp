
// ControlUnitAppView.cpp : CControlUnitAppView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "ControlUnitApp.h"
#endif

#include "ControlUnitAppDoc.h"
#include "ControlUnitAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CControlUnitAppView

IMPLEMENT_DYNCREATE(CControlUnitAppView, CFormView)

BEGIN_MESSAGE_MAP(CControlUnitAppView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CControlUnitAppView �R���X�g���N�V����/�f�X�g���N�V����

CControlUnitAppView::CControlUnitAppView()
	: CFormView(CControlUnitAppView::IDD)
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

}

CControlUnitAppView::~CControlUnitAppView()
{
}

void CControlUnitAppView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CControlUnitAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CFormView::PreCreateWindow(cs);
}

void CControlUnitAppView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

void CControlUnitAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CControlUnitAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CControlUnitAppView �f�f

#ifdef _DEBUG
void CControlUnitAppView::AssertValid() const
{
	CFormView::AssertValid();
}

void CControlUnitAppView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CControlUnitAppDoc* CControlUnitAppView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CControlUnitAppDoc)));
	return (CControlUnitAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CControlUnitAppView ���b�Z�[�W �n���h���[
