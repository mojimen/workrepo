
// LeftView.cpp : CLeftView �N���X�̎���
//

#include "stdafx.h"
#include "ControlUnitApp.h"

#include "ControlUnitAppDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
END_MESSAGE_MAP()


// CLeftView �R���X�g���N�V����/�f�X�g���N�V����

CLeftView::CLeftView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs ��ύX���āAWindow �N���X�܂��̓X�^�C����ύX���܂��B

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO:  GetTreeCtrl() �����o�[�֐��̌Ăяo�����Ƃ����Ē��ڂ��̃��X�g �R���g���[����
	//  �A�N�Z�X���邱�Ƃɂ���� TreeView ���A�C�e���ŌŒ�ł��܂��B
}


// CLeftView �f�f

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CControlUnitAppDoc* CLeftView::GetDocument() // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CControlUnitAppDoc)));
	return (CControlUnitAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView ���b�Z�[�W �n���h���[
