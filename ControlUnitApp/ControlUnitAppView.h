
// ControlUnitAppView.h : CControlUnitAppView �N���X�̃C���^�[�t�F�C�X
//

#pragma once

#include "resource.h"


class CControlUnitAppView : public CFormView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CControlUnitAppView();
	DECLARE_DYNCREATE(CControlUnitAppView)

public:
	enum{ IDD = IDD_CONTROLUNITAPP_FORM };

// ����
public:
	CControlUnitAppDoc* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void OnInitialUpdate(); // �\�z��ɏ��߂ČĂяo����܂��B

// ����
public:
	virtual ~CControlUnitAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ControlUnitAppView.cpp �̃f�o�b�O �o�[�W����
inline CControlUnitAppDoc* CControlUnitAppView::GetDocument() const
   { return reinterpret_cast<CControlUnitAppDoc*>(m_pDocument); }
#endif

