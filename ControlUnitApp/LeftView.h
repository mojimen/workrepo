
// LeftView.h : CLeftView �N���X�̃C���^�[�t�F�C�X
//


#pragma once

class CControlUnitAppDoc;

class CLeftView : public CTreeView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// ����
public:
	CControlUnitAppDoc* GetDocument();

// ����
public:

// �I�[�o�[���C�h
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // �\�z��ɏ��߂ČĂяo����܂��B

// ����
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // LeftView.cpp �̃f�o�b�O �o�[�W����
inline CControlUnitAppDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CControlUnitAppDoc*>(m_pDocument); }
#endif

