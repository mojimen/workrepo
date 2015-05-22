// TestDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ControlUnitAppProto.h"
#include "TestDialog.h"
#include "afxdialogex.h"
#include "dwmapi.h"
#pragma comment(lib ,"dwmapi.lib")

// TestDialog �_�C�A���O

IMPLEMENT_DYNAMIC(TestDialog, CDialogEx)

TestDialog::TestDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(TestDialog::IDD, pParent)
{
	m_bCompositEnable = TRUE;
	DwmIsCompositionEnabled(&m_bCompositEnable);//�}�[�W���ݒ�
	m_margins = { 100, 100, 100, 100 };
	ChangeFrame();

}

TestDialog::~TestDialog()
{
}

void TestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TestDialog, CDialogEx)
	ON_WM_DWMCOMPOSITIONCHANGED()
END_MESSAGE_MAP()


// TestDialog ���b�Z�[�W �n���h���[

VOID TestDialog::ChangeFrame(void)
{
	if (m_bCompositEnable){
		HRESULT hr = DwmExtendFrameIntoClientArea(this->m_hWnd, &m_margins);
		if (SUCCEEDED(hr)){
		}
		else{
			//Error
		}
	}
	Invalidate();
}

void TestDialog::OnCompositionChanged()
{
	// ���̋@�\�ɂ� Windows Vista �ȍ~�̃o�[�W�������K�v�ł��B
	// �V���{�� _WIN32_WINNT �� >= 0x0600 �ɂ���K�v������܂��B
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	DwmIsCompositionEnabled(&m_bCompositEnable);
	ChangeFrame();
	//CDialogEx::OnCompositionChanged();
}
