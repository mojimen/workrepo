/*!	@file
	@brief	COGLJText�N���X�w�b�_
	@author	Nobuki HIRAMINE
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
#pragma once

#include <gl\gl.h>

/*!	@brief	OpenGL�œ��{��e�L�X�g��`�悷�邽�߂̃N���X
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
class OpenGLJText : public CObject
{
public:
	//! ��_�ʒu
	enum EORIGINALPOS
	{
		OP_LEFTTOP = 0,	//!< ����
		OP_RIGHTTOP,	//!< �E��
		OP_LEFTBOTTOM,	//!< ����
		OP_RIGHTBOTTOM,	//!< �E��
	};
// �R���X�g���N�^�A�f�X�g���N�^
public:
	OpenGLJText(const TCHAR* pszFontName, float fFontSize, EORIGINALPOS eOriginPos = OP_LEFTBOTTOM);
	virtual	~OpenGLJText();

// �����o�ϐ�
public:
protected:
private:
	TCHAR			m_szFontName[LF_FACESIZE];	//!< �t�H���g���iLOGFONT��lfFaceName�̎d�l�ɂ��A������̒����̓k�������܂߂�LF_FACESIZE(=32)�j
	float			m_fFontSize;				//!< �t�H���g�T�C�Y
	EORIGINALPOS	m_eOriginPos;				//!< ��_�ʒu
	HFONT			m_hFont;					//!< �t�H���g�n���h��
	GLuint			m_uiDisplayListIndex;		//!< �f�B�X�v���C���X�g�C���f�b�N�X
	TCHAR*			m_pszString;				//!< �`�敶����
// �����o�֐�
public:
	//�������A�N�Z�T������
	float	GetFontSize() const { return m_fFontSize; }	//!< �t�H���g�T�C�Y�̎擾
	void	SetFontSize( float fFontSize )
						{	if( m_fFontSize == fFontSize ){ return; }
							DeleteDisplayList();
							if( m_hFont ){ DeleteObject( m_hFont ); m_hFont = NULL; }
							m_fFontSize = fFontSize; }	//!< �t�H���g�T�C�Y�̐ݒ�
	const TCHAR*	GetFontName() const { return m_szFontName; }	//!< �t�H���g���̎擾
	void	SetFontName( const TCHAR* pszFontName )
						{	if( NULL != pszFontName && 0 == _tcscmp( m_szFontName, pszFontName ) ){ return; }
							DeleteDisplayList();
							if( m_hFont ){ DeleteObject( m_hFont ); m_hFont = NULL; }
							if( NULL == pszFontName
							 || 0 == _tcscmp( _T(""), pszFontName ) )
							{
								_tcsncpy_s( m_szFontName, LF_FACESIZE, _T("�l�r �S�V�b�N"), _TRUNCATE );
							}
							else
							{
								_tcsncpy_s( m_szFontName, LF_FACESIZE, pszFontName, _TRUNCATE );
							} }	//!< �t�H���g���̐ݒ�
	EORIGINALPOS	GetOriginPos() const { return m_eOriginPos; }	//!< ��_�ʒu�̎擾
	void	SetOriginPos( const EORIGINALPOS eOriginPos ){ m_eOriginPos = eOriginPos; }	//!< ��_�ʒu�̐ݒ�
	//�������A�N�Z�T������
public:
	HFONT CreateJFont(HDC hDC, const TCHAR* pszFontName, float fFontSize);
	void InitBitmap(BITMAP *pBitmap, LONG lWidth, LONG lHeight);
	void UninitBitmap(BITMAP *pBitmap);
	GLubyte* CreateMonoBits(HDC hDC, HBITMAP hBitmap, SIZE& rsizeBitmap);
	GLubyte* CreateStringMonoBits(HDC hDC, HFONT hFont, const TCHAR* pszString, SIZE& rsizeBitmap);
	void Format(const TCHAR* fmt, ...);
	bool Split(const TCHAR* pszString_source, TCHAR*& rpszString_dest, unsigned int& ruiCountLine, TCHAR**& rapszLineString);
	void Render();
protected:
private:
	void DeleteDisplayList();
};


