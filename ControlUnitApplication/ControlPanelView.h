#pragma once



// ControlPanelView �t�H�[�� �r���[

class ControlPanelView : public CFormView
{
	DECLARE_DYNCREATE(ControlPanelView)

protected:
	ControlPanelView();           // ���I�����Ŏg�p����� protected �R���X�g���N�^�[
	virtual ~ControlPanelView();

public:
	enum { IDD = IDD_CONTROLPANELVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};


