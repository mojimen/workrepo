
// ChildFrm.h : CChildFrame �N���X�̃C���^�[�t�F�C�X
//

#pragma once

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// ����
public:

// ����
public:

// �I�[�o�[���C�h
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// ����
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()

protected:
	CSplitterWnd m_wndSplitter;

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
