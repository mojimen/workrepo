
// ProtoType4K8KApplication.h : ProtoType4K8KApplication �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��


// CProtoType4K8KApplicationApp:
// ���̃N���X�̎����ɂ��ẮAProtoType4K8KApplication.cpp ���Q�Ƃ��Ă��������B
//

class CProtoType4K8KApplicationApp : public CWinAppEx
{
public:
	CProtoType4K8KApplicationApp();


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CProtoType4K8KApplicationApp theApp;
