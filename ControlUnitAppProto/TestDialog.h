#pragma once


// TestDialog �_�C�A���O

class TestDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TestDialog)

public:
	TestDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~TestDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bCompositEnable; //Aero�����L������
	MARGINS m_margins; 	//�}�[�W��
	VOID ChangeFrame(); //�G�A���t���[���̐ݒ�&�Đݒ�

public:
	afx_msg void OnCompositionChanged();
};
