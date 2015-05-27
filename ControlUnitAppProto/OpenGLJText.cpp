/*!	@file
	@brief	COGLJText�N���X����
	@author	Nobuki HIRAMINE
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
#include "stdafx.h"
#include "OpenGLJText.h"

#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//! ������o�b�t�@�[�̃T�C�Y
const unsigned int BUFFERSIZE = 4096;

/*!	@brief	�R���X�g���N�^
	@return	�Ȃ�
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
OpenGLJText::OpenGLJText(const TCHAR* pszFontName,	//!< [in] �t�H���g��
						float fFontSize,			//!< [in] �t�H���g�T�C�Y
						EORIGINALPOS eOriginPos )	//!< [in] ��_�ʒu
	:	m_fFontSize(fFontSize),
		m_eOriginPos(eOriginPos),
		m_hFont(NULL),
		m_uiDisplayListIndex(0),
		m_pszString(NULL)
{
	if( NULL == pszFontName
	 || 0== _tcscmp( _T(""), pszFontName ) )
	{
		_tcsncpy_s( m_szFontName, LF_FACESIZE, _T("�l�r �S�V�b�N"), _TRUNCATE );
	}
	else
	{
		_tcsncpy_s( m_szFontName, LF_FACESIZE, pszFontName, _TRUNCATE );
	}
}

/*!	@brief	�f�X�g���N�^
	@return	�Ȃ�
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
OpenGLJText::~OpenGLJText()
{
	DeleteDisplayList();
	if( m_pszString )
	{
		free( m_pszString );	// �`�敶����̍폜
	}
	if( m_hFont )
	{
		DeleteObject( m_hFont );	// �t�H���g�I�u�W�F�N�g�̊J��
	}
}

/*!	@brief	�����t���f�[�^�̏�������
	@return	�Ȃ�
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
void OpenGLJText::Format(const TCHAR* format,	//!< [in] �����w�蕶����
						... )
{
	va_list  valist;
	TCHAR buff[BUFFERSIZE];

	va_start(valist, format );
	_vsntprintf_s( buff, BUFFERSIZE, _TRUNCATE, format , valist );
	va_end(valist);

	if( NULL != m_pszString
	 && 0 == _tcscmp( buff, m_pszString ) )
	{	// ������͕ς���ĂȂ�
		return;
	}

	// ������͕ς����
	if( NULL != m_pszString )
	{
		free( m_pszString );
	}
	m_pszString = _tcsdup( buff );
	DeleteDisplayList();
}

/*!	@brief	�t�H���g�I�u�W�F�N�g�̍쐬
	@return	�Ȃ�
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
HFONT OpenGLJText::CreateJFont(HDC hDC,					//!< [in] �f�o�C�X�R���e�L�X�g
					const TCHAR* pszFontName,	//!< [in] �t�H���g��
					float fFontSize )			//!< [in] �t�H���g�T�C�Y
{
	if( NULL == pszFontName )
	{
		return NULL;
	}
	HFONT hFont = NULL;
	LOGFONT logfont;
	FillMemory( &logfont, sizeof(LOGFONT), 0 );
	logfont.lfHeight	= -MulDiv( (int)fFontSize, GetDeviceCaps( hDC, LOGPIXELSY ), 72 );	// �����̍���
	logfont.lfCharSet	= SHIFTJIS_CHARSET;	// �L�����N�^�Z�b�g�i���{��L�����N�^�Z�b�g�j
	logfont.lfWeight	= FW_NORMAL;		// �����i�W���̑����j
	_tcsncpy_s( logfont.lfFaceName, LF_FACESIZE, pszFontName, _TRUNCATE );
	hFont = CreateFontIndirect( &logfont );
	assert( hFont );
	return hFont;
}

/*!	@brief	BITMAP�̏�����
	@return	�Ȃ�
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
void OpenGLJText::InitBitmap(BITMAP *pBitmap,	//!< [in/out] ����������r�b�g�}�b�v
					LONG lWidth,		//!< [in] �r�b�g�}�b�v�̕� 
					LONG lHeight )		//!< [in] �r�b�g�}�b�v�̍���
{
	if( NULL == pBitmap )
	{
		return;
	}
	FillMemory( pBitmap, sizeof(*pBitmap), 0 );
	pBitmap->bmWidth		= lWidth;
	pBitmap->bmHeight		= lHeight;
	pBitmap->bmWidthBytes	= ((lWidth + 7) / 8 + 1) & (~1);
	pBitmap->bmPlanes		= 1;
	pBitmap->bmBitsPixel	= 1;
	pBitmap->bmBits			= malloc( pBitmap->bmWidthBytes * lHeight );
}

/*!	@brief	BITMAP�̌㏈��
	@return	�Ȃ�
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
void OpenGLJText::UninitBitmap(BITMAP *pBitmap)
{
	if( NULL == pBitmap )
	{
		return;
	}
	if( pBitmap->bmBits )
	{
		free( pBitmap->bmBits );
	}
}

/*!	@brief	�����r�b�g��̍쐬
	@return	�쐬���ꂽ�r�b�g�}�b�v�̃|�C���^
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
GLubyte* OpenGLJText::CreateMonoBits(HDC hDC,			//!< [in] �f�o�C�X�R���e�L�X�g
							HBITMAP hBitmap,	//!< [in] �r�b�g�}�b�v�n���h��
							SIZE& rsizeBitmap )	//!< [out] �r�b�g�}�b�v�̑傫��
{
	// �C���v�b�g�̃`�F�b�N
	if( NULL == hDC
	 || NULL == hBitmap )
	{
		return NULL;
	}

	// �r�b�g�}�b�v�̏��̎擾
	BITMAP bitmap;
	GetObject( hBitmap, sizeof(bitmap), &bitmap );
	rsizeBitmap.cx = ( (bitmap.bmWidth+31) & (~31) );	// 32�̔{���ɂ���i���R�͒������j
	rsizeBitmap.cy = bitmap.bmHeight;

	// �r�b�g��̗̈�̊m��
	// 1�s�N�Z��������1bit�̗̈���m�ۂ���B
	// 1byte��8bits�ł���Acy * cx �̌��ʂ�8�Ŋ���K�v������B
	// cx�͏�̌v�Z�̌��ʂł���8�̔{���ł��邱�Ƃ��ۏ؂���Ă���̂ŁAcx��8�Ŋ���B
	int uiBitsSize = rsizeBitmap.cy * (rsizeBitmap.cx / 8);
	GLubyte* pubMonoBits = (GLubyte*)malloc( uiBitsSize );
	FillMemory( pubMonoBits, uiBitsSize, 0 );

	// �r�b�g�}�b�v���r�b�g��ɃR�s�[
	struct
	{
		BITMAPINFOHEADER    bmiHeader;
		RGBQUAD             bmiColors[2];	// �p���b�g�i�F�̐�(��2^biBitCount)����RGBQUAD��p�ӂ���K�v������j
	} monobitmapinfo;
	BITMAPINFO* pBitmapinfo = (BITMAPINFO*)&monobitmapinfo;

	pBitmapinfo->bmiHeader.biSize			= sizeof(pBitmapinfo->bmiHeader);
	pBitmapinfo->bmiHeader.biWidth			= bitmap.bmWidth;
	pBitmapinfo->bmiHeader.biHeight			= bitmap.bmHeight;
	pBitmapinfo->bmiHeader.biPlanes			= 1;
	pBitmapinfo->bmiHeader.biBitCount		= 1;	// 1�s�N�Z��������̃r�b�g���i1�s�N�Z���������1�r�b�g���Q�F�r�b�g�}�b�v�j
	pBitmapinfo->bmiHeader.biCompression	= BI_RGB;
	pBitmapinfo->bmiHeader.biSizeImage		= uiBitsSize;
	pBitmapinfo->bmiHeader.biXPelsPerMeter	= 1;
	pBitmapinfo->bmiHeader.biYPelsPerMeter	= 1;
	pBitmapinfo->bmiHeader.biClrUsed		= 0;
	pBitmapinfo->bmiHeader.biClrImportant	= 0;

	GetDIBits( hDC, hBitmap, 0, bitmap.bmHeight, pubMonoBits, pBitmapinfo, DIB_RGB_COLORS );

	return pubMonoBits;
}

/*!	@brief	�����񔒍��r�b�g��̍쐬
	@return	�쐬���ꂽ�r�b�g�}�b�v�̃|�C���^
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
GLubyte* OpenGLJText::CreateStringMonoBits(HDC hDC,				//!< [in] �f�o�C�X�R���e�L�X�g
								HFONT hFont,			//!< [in] �t�H���g�n���h��
								const TCHAR* pszString,	//!< [in] ������
								SIZE& rsizeBitmap )		//!< [out] �r�b�g�}�b�v�̑傫��
{
	// �A�E�g�v�b�g�̐錾�A������
	GLubyte    *pubStringMonoBits = NULL;

	// �C���v�b�g�̃`�F�b�N
	if( NULL == hDC
	 || NULL == hFont
	 || NULL == pszString )
	{
		assert( !"CreateStringMonoBits" );
		return NULL;
	}

	// ������̕�����
	unsigned int uiStringLength = (unsigned int)_tcslen(pszString);

	HFONT   hFont_old = (HFONT)SelectObject(hDC, hFont);

	// �e�L�X�g�̕��ƍ������v�Z���܂��B
	SIZE sizeText;
	GetTextExtentPoint32( hDC, pszString, uiStringLength, &sizeText );

	//�w�肳�ꂽ���A�����A�F�`�������r�b�g�}�b�v�̍쐬
	BITMAP	bitmap;
	InitBitmap( &bitmap, sizeText.cx, sizeText.cy );	// BITMAP�̏�����
	HBITMAP hBitmap = CreateBitmapIndirect( &bitmap );
	assert( hBitmap );
	UninitBitmap( &bitmap );	// BITMAP�̌㏈��

	if( hBitmap )
	{
		// �w�肳�ꂽ�f�o�C�X�ƌ݊����̂��郁�����f�o�C�X�R���e�L�X�g�̍쐬
		HDC hMemDC = CreateCompatibleDC( hDC );
		assert( hMemDC );
		if( hMemDC )
		{
			// MemDC�̃r�b�g�}�b�v�A�t�H���g�A�e�L�X�g�F�A�w�i�F�A�w�i���[�h�̎w��
			HBITMAP hBitmap_memdc_old = (HBITMAP)SelectObject( hMemDC, hBitmap );
			HFONT hFont_memdc_old = (HFONT)SelectObject( hMemDC, hFont );
			SetTextColor( hMemDC, RGB(255,255,255) );
			SetBkColor( hMemDC, RGB(0,0,0) );
			SetBkMode( hMemDC, OPAQUE );

			// MemDC��Ƀe�L�X�g���o��
			TextOut( hMemDC, 0, 0, pszString, uiStringLength );

#ifdef	_DEBUG
#if 0
			if( OpenClipboard(NULL) )
			{
				EmptyClipboard();
				SetClipboardData( CF_BITMAP, hBitmap );
				CloseClipboard();
			}
#endif
#endif

			// MonoBits�f�[�^�̍쐬�A�\�z
			pubStringMonoBits = CreateMonoBits( hMemDC, hBitmap, rsizeBitmap );

			SelectObject( hMemDC, hFont_memdc_old );
			SelectObject( hMemDC, hBitmap_memdc_old );

			DeleteDC( hMemDC );
		}
		DeleteObject( hBitmap );
	}
	SelectObject( hDC, hFont_old );

	return pubStringMonoBits;
}

/*!	@brief	���s���܂ޕ���������s�ŕ������A���s���܂܂Ȃ�������̔z��ɕϊ�
	@return	�Ȃ�
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
bool OpenGLJText::Split(const TCHAR* pszString_source,	//!< [in] �������镶����
			TCHAR*& rpszString_dest,		//!< [out] �������镶�����\n,\r��\0�ɒu���������������
			unsigned int& ruiCountLine,		//!< [out] �s��
			TCHAR**& rapszLineString )		//!< [out] ��s������̐擪������̃A�h���X�̔z��
{
	if( NULL == pszString_source )
	{
		return false;
	}

	rpszString_dest = _tcsdup( pszString_source );

	// �s�������߂�B
	ruiCountLine = 0;
	TCHAR* pszString_work = rpszString_dest;
	while( 1 )
	{
		TCHAR* pszString_strchr = _tcschr( pszString_work, _T('\n') );
		if( NULL == pszString_strchr )
		{	// �����u\n�v�͂Ȃ�
			++ruiCountLine;
			break;
		}
		else
		{
			++ruiCountLine;
			pszString_work = &(pszString_strchr[1]);	// ���[�N������̊J�n�������A�������u\n�v�̎��̕����ɂ���B
			if( _T('\0') == pszString_work[0] )
			{	// ������I��
				break;
			}
		}
	}
	assert( ruiCountLine );

	// ��s������̐擪������̃A�h���X�̔z��̗̈�̊m��
	rapszLineString = (TCHAR**)malloc( ruiCountLine * sizeof(char*) );
	assert( rapszLineString );

	// ������̉�́i�s�����́j
	unsigned int uiIndexLine = 0;
	pszString_work = rpszString_dest;
	while( 1 )
	{
		TCHAR* pszString_strchr = _tcschr( pszString_work, _T('\n') );
		if( NULL == pszString_strchr )
		{	// �����u\n�v�͂Ȃ�
			rapszLineString[uiIndexLine] = pszString_work;
			++uiIndexLine;
			break;
		}
		else
		{
			pszString_strchr[0] = _T('\0');	// �������u\n�v���u\0�v�ɒu���B
			if( _T('\r') == pszString_work[_tcslen(pszString_work)-1] )
			{	// \r\n�Ή�
				pszString_work[_tcslen(pszString_work)-1] = _T('\0');
			}
			rapszLineString[uiIndexLine] = pszString_work;
			++uiIndexLine;
			pszString_work = &(pszString_strchr[1]);	// ���[�N������̊J�n�������A�������u\n�v�̎��̕����ɂ���B
			if( _T('\0') == pszString_work[0] )
			{	// ������I��
				break;
			}
		}
	}
	assert( uiIndexLine == ruiCountLine );

	return true;
}

/*!	@brief	�`��
	@return	�Ȃ�
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
void OpenGLJText::Render()
{
	if( 0 != m_uiDisplayListIndex )
	{	// �f�B�X�v���C���X�g���ς݂Ȃ�΁A�f�B�X�v���C���X�g�Ăяo���ďI���B
		glCallList( m_uiDisplayListIndex );
		return;
	}

	if( NULL == m_pszString )
	{	// �`�敶����Ȃ�
		return;
	}

	// �f�o�C�X�R���e�L�X�g�̎擾
	HDC hDC = wglGetCurrentDC();
	assert( hDC );

	// �t�H���g�I�u�W�F�N�g�̍쐬
	if( NULL == m_hFont )
	{
		m_hFont = CreateJFont( hDC, m_szFontName, m_fFontSize );
		assert( m_hFont );
	}

	// ����������s�ŕ���
	TCHAR* pszString_split = NULL;
	unsigned int uiCountLine = 0;
	TCHAR** apszLineString = NULL;	// ��s������̐擪������̃A�h���X�̔z��
	if( !Split( m_pszString,
				pszString_split,
				uiCountLine,
				apszLineString ) )
	{	// ���s
		return;
	}
	assert( pszString_split );
	assert( uiCountLine );
	assert( apszLineString );

	// �f�B�X�v���C���X�g���ƕ`��
	m_uiDisplayListIndex = glGenLists( 1 );
	glNewList( m_uiDisplayListIndex, GL_COMPILE_AND_EXECUTE );
		for( unsigned int uiIndexLine = 0; uiIndexLine < uiCountLine; ++uiIndexLine )
		{
			if( 0 == _tcscmp( _T(""), apszLineString[uiIndexLine] ) )
			{	// ��s
				continue;	// �R���e�B�j���[����Ƌ�s���ł���B
			}
			// �����񔒍��r�b�g��̍쐬
			SIZE sizeBitmap;
			GLubyte* pubBits = CreateStringMonoBits( hDC, m_hFont, apszLineString[uiIndexLine], sizeBitmap );
			if( NULL == pubBits )
			{	// �r�b�g�}�b�v�쐬���s�����Ƃ��́A��s�ɂ���B
				assert( !"CreateStringMonoBits()" );
				continue;	// �R���e�B�j���[����Ƌ�s���ł���B
			}
			GLfloat	xmove = 0.0;
			GLfloat	ymove = 0.0;
			switch( m_eOriginPos )
			{
				case OP_LEFTTOP:	// �����񌴓_���A����Ƃ���ꍇ
					ymove = (GLfloat)( (int)(uiIndexLine + 1) * sizeBitmap.cy );
					break;
				case OP_RIGHTTOP:	// �����񌴓_���A�E��Ƃ���ꍇ
					xmove = (GLfloat)sizeBitmap.cx;
					ymove = (GLfloat)( (int)(uiIndexLine + 1) * sizeBitmap.cy );
					break;
				case OP_LEFTBOTTOM:	// �����񌴓_���A�����Ƃ���ꍇ
					ymove = (GLfloat)( (int)(uiIndexLine + 1 - uiCountLine) * sizeBitmap.cy );
					break;
				case OP_RIGHTBOTTOM:// �����񌴓_���A�E���Ƃ���ꍇ
					xmove = (GLfloat)sizeBitmap.cx;
					ymove = (GLfloat)( (int)(uiIndexLine + 1 - uiCountLine) * sizeBitmap.cy );
					break;
				default:
					assert( !"���Ή�" );
					ymove = (GLfloat)( (uiIndexLine + 1)*sizeBitmap.cy );
					break;
			}
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
			glBitmap(	sizeBitmap.cx,	// width
						sizeBitmap.cy,	// height
						xmove,		// �r�b�g�}�b�v���_���ǂ��ɂ��邩�i�r�b�g�}�b�v�̍�����B���́A�w���͉E�����A�x���͏�����j
						ymove,		// �r�b�g�}�b�v���_���ǂ��ɂ��邩�i�r�b�g�}�b�v�̍�����B���́A�w���͉E�����A�x���͏�����j
						0.0,
						0.0,
						pubBits );
			free( pubBits );
		}
	glEndList();

	free( apszLineString );
	free( pszString_split );
}

/*!	@brief	�f�B�X�v���C���X�g�̍폜
	@return	�Ȃ�
	@date	2009/09/21 : �V�K�쐬
	@note	�Ȃ�*/
void OpenGLJText::DeleteDisplayList()
{
	if( m_uiDisplayListIndex )
	{
		glDeleteLists( m_uiDisplayListIndex, 1 );
		m_uiDisplayListIndex = 0;
	}
}

// OpenGLJText.cpp : �����t�@�C��
//

