
// ControlUnitApplicationView.h : CControlUnitApplicationView �N���X�̃C���^�[�t�F�C�X
//

#pragma once


class CControlUnitApplicationView : public CView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CControlUnitApplicationView();
	DECLARE_DYNCREATE(CControlUnitApplicationView)

// ����
public:
	CControlUnitApplicationDoc* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����
public:
	virtual ~CControlUnitApplicationView();
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

// �}�`�h���b�O�p�̃����o
private:
	CRect m_rcRect	// �ړ��Ώۂ̐}�`
		, m_rcRectV	// �ړ����̃C���[�W�i�`��j
		, m_rcRectH // �ړ����̃C���[�W�i�����j
		, *m_pRectH;
	CPoint m_poMousePointerLocation; // �}�E�X�{�^���������ꂽ�Ƃ��̈ʒu
	CSize m_szRectFrameSize; // �ړ����̎l�p�`�́A�g�̑��� (�������̕��ƁA�c�����̕�)
	BOOL m_fLButtonClicking; // �}�E�X�{�^����������Ă��邩�ǂ������L�^

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ControlUnitApplicationView.cpp �̃f�o�b�O �o�[�W����
inline CControlUnitApplicationDoc* CControlUnitApplicationView::GetDocument() const
   { return reinterpret_cast<CControlUnitApplicationDoc*>(m_pDocument); }
#endif

