
// ChildFrm.cpp : CChildFrame �N���X�̎���
//

#include "stdafx.h"
#include "ControlUnitAppProto.h"

#include "ChildFrm.h"

#include "ControlUnitAppProtoDoc.h"
#include "ControlUnitAppProtoView.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CChildFrame �R���X�g���N�V����/�f�X�g���N�V����

CChildFrame::CChildFrame()
{
	// TODO: �����o�[�������R�[�h�������ɒǉ����Ă��������B
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs ��ύX���āAWindow �N���X�܂��̓X�^�C����ύX���܂��B
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

// CChildFrame �f�f

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ���b�Z�[�W �n���h���[

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	////���I�ȕ����̗�
	//return m_wndSplitter.Create(this, 2, 2, CSize(10, 10), pContext);

	if (!m_wndSplitter.CreateStatic(this,
		2, 1,                 // TODO: �s�Ɨ�̐��𒲐����Ă��������B
		WS_CHILD | WS_VISIBLE)
		) return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(TestView), CSize(1000, 400), pContext)) return FALSE;
	if (!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CControlUnitAppProtoView), CSize(128, 64), pContext)) return FALSE;

	return TRUE;
}

BOOL CChildFrame::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	//return TRUE;

	return CMDIChildWndEx::OnEraseBkgnd(pDC);
}
