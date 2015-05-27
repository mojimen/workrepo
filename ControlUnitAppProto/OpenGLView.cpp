// OpenGLView.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ControlUnitAppProto.h"
#include "OpenGLView.h"

#include "locale.h"
#include "mbstring.h"


// OpenGLView

IMPLEMENT_DYNCREATE(OpenGLView, CView)

OpenGLView::OpenGLView()
{

}

OpenGLView::~OpenGLView()
{
}

BEGIN_MESSAGE_MAP(OpenGLView, CView)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// OpenGLView �`��

void OpenGLView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �`��R�[�h�������ɒǉ����Ă��������B


}


// OpenGLView �f�f

#ifdef _DEBUG
void OpenGLView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void OpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// OpenGLView ���b�Z�[�W �n���h���[
BOOL OpenGLView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		1,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (pixelformat == 0) {
		return FALSE;
	}

	if (::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE) {
		return FALSE;
	}

	return TRUE;
}


BOOL OpenGLView::InitGLContext()
{
	m_pDC = new CClientDC(this);

	if (m_pDC == NULL) {
		return FALSE;
	}
	if (!SetupPixelFormat()) return FALSE;
	if ((m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc())) == 0) {
		return FALSE;
	}
	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE) {
		return FALSE;
	}
	::glEnable(GL_BLEND);
	::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	::glEnableClientState(GL_VERTEX_ARRAY);

	return TRUE;
}


void OpenGLView::PreSubclassWindow()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊��N���X���Ăяo���Ă��������B

	LONG  style = GetWindowLong(this->m_hWnd, GWL_STYLE);
	style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	SetWindowLong(this->m_hWnd, GWL_STYLE, style);

	InitGLContext();

	CView::PreSubclassWindow();
}


void OpenGLView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B

	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B

	if (::wglMakeCurrent(NULL, NULL) == FALSE) {
		//	�K�v�ɉ����ăG���[�n���h�����O
	}

	if (::wglDeleteContext(m_hRC) == FALSE) {
		//	�K�v�ɉ����ăG���[�n���h�����O
	}

	if (m_hRC)
	{
		delete m_hRC;
	}
	if (m_pDC)
	{
		delete m_pDC;
	}
}


BOOL OpenGLView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	return TRUE;

	//return CView::OnEraseBkgnd(pDC);
}

void OpenGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B

	if (m_hRC != NULL) {
		CRect rcViewRect;
		GetClientRect(&rcViewRect);
		GLint width = rcViewRect.Width();
		GLint height = rcViewRect.Height();

		// OpenGL �̏����ݒ�
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, static_cast<GLdouble>(cx), 0.0, static_cast<GLdouble>(cy), -1.0, 1.0);
		//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);

		glGetIntegerv(GL_VIEWPORT, m_iViewport);
		glGetDoublev(GL_PROJECTION_MATRIX, m_dProjection);
		glGetDoublev(GL_MODELVIEW_MATRIX, m_dModelview);


	}

}

int OpenGLView::DrawTextOnGL(PCTSTR pszStr, HDC hDC, HFONT& hfFont, GLfloat gfRed, GLfloat gfGreen, GLfloat gfBlue, GLfloat gfAlpha,
	GLfloat gfPosX, GLfloat gfPosY, GLfloat gfPosZ, GLfloat gfMoveX)
{
	unsigned int textLength;	//�����Ŏ󂯎�����e�L�X�g�̒���
	WCHAR * unicodeText;		//text��UNICODE�ɕϊ�������������i�[����
	GLuint listbaseIdx;		//�f�B�X�v���C���X�g�̍ŏ��̃C���f�b�N�X

	CStringA strA(pszStr);
	char* text = new char[(strA.GetLength() * sizeof(TCHAR)) + 1];
	strcpy_s(text, (strA.GetLength() * sizeof(TCHAR)), strA);

	//���{��̕�����Ƃ��Ĉ����悤�ݒ�
	setlocale(LC_CTYPE, "jpn");

	//text�̕��������擾
	textLength = (unsigned int)_mbstrlen(text);
	if (textLength == -1)
		return -1;

	//text�̕��������̃��C�h������̗̈���쐬
	unicodeText = (WCHAR *)calloc(textLength + 1, sizeof(WCHAR));
	if (unicodeText == NULL)
	{
		return -2;
	}

	//�擾�����W���C���gID��UNICODE�ɕϊ�����
	if (MultiByteToWideChar(CP_ACP, 0, text, -1, unicodeText, (sizeof(WCHAR) * textLength) + 1) == 0)
		return -3;

	HFONT hfOldFont = static_cast<HFONT>(SelectObject(hDC, hfFont));

	//���������̃f�B�X�v���C���X�g���m�ۂ��A�f�B�X�v���C���X�g�̍ŏ��̃C���f�b�N�X���擾
	listbaseIdx = glGenLists(textLength);

	for (unsigned int textCnt = 0; textCnt < textLength; ++textCnt)
	{
		if (wglUseFontBitmapsW(hDC, unicodeText[textCnt], 1, listbaseIdx + textCnt) == FALSE)
		{
			//MessageBox(hwnd, "wglUseFontBitmaps() Error!!", "wgl Error", MB_OK);
		}
	}

	//�����F�̎w��
	glColor3f(gfRed, gfGreen, gfBlue);

	//1�����`�悵���當������bit���炷��
	glBitmap(0, 0, 0, 0, gfMoveX/*x move*/, 0/*y move*/, NULL);

	//������`�悷��ʒu�����߂�
	glRasterPos3f(gfPosX, gfPosY, gfPosZ);

	//�f�B�X�v���C���X�g�����s����
	for (unsigned int textCnt = 0; textCnt < textLength; textCnt++)
	{
		glCallList(listbaseIdx + (GLuint)textCnt);
	}

	SelectObject(hDC, hfOldFont);
	DeleteObject(hfOldFont);

	return 1;
}

BOOL OpenGLView::CreateDrawFont(int iHeight, int iAngle, PCTSTR pszFace, HFONT& hfFont)
{
	hfFont = CreateFont(iHeight, 0, iAngle, 0, FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN, pszFace);
	if (hfFont == NULL)
	{
		return FALSE;
	}
	return TRUE;
}

void OpenGLView::ChangeScreenPointToOpenGLPoint(const int iPointX, const int iPointY, int iWindowHeight, double& dPointX, double& dPointY)
{
	float z;
	double objZ;
	glReadPixels(iPointX, iWindowHeight - iPointY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject(iPointX, iWindowHeight - iPointY, z, m_dModelview, m_dProjection, m_iViewport, &dPointX, &dPointY, &objZ);
}


void OpenGLView::ChangeScreenRectToOpenGLPoint(const CRect& rcScreenRect, int iWindowHeight, double& dLeft, double& dRight, double& dTop, double& dBottom)
{
	//dLeft = static_cast<double>(rcScreenRect.left);
	//dRight = static_cast<double>(rcScreenRect.right);
	//dTop = static_cast<double>(iWindowHeight - rcScreenRect.top);
	//dBottom = static_cast<double>(iWindowHeight - rcScreenRect.bottom);

	float z;
	double objZ;
	glReadPixels(rcScreenRect.left, iWindowHeight - rcScreenRect.top, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject(rcScreenRect.left, iWindowHeight - rcScreenRect.top, z, m_dModelview, m_dProjection, m_iViewport, &dLeft, &dTop, &objZ);
	glReadPixels(rcScreenRect.right, iWindowHeight - rcScreenRect.bottom, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject(rcScreenRect.right, iWindowHeight - rcScreenRect.bottom, z, m_dModelview, m_dProjection, m_iViewport, &dRight, &dBottom, &objZ);

}

void OpenGLView::DrawRect(const double& dLeft, const double& dRight, const double& dTop, const double& dBottom, const float& fLineWidth, 
	const float& fRed, const float& fGreen, const float& fBlue, const float& fAlpha, GLenum glMode /* = GL_LINE_LOOP */)
{
	glLineWidth(fLineWidth);
	glColor4f(fRed, fGreen, fBlue, fAlpha);
	glBegin(glMode);
	glVertex2d(dLeft, dTop);
	glVertex2d(dRight, dTop);
	glVertex2d(dRight, dBottom);
	glVertex2d(dLeft, dBottom);
	glEnd();
}

void OpenGLView::DrawRect(const float& fLineWidth, const float& fRed, const float& fGreen, const float& fBlue, const float& fAlpha, GLenum glMode /* = GL_LINE_LOOP */)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glLineWidth(fLineWidth);
	glColor4f(fRed, fGreen, fBlue, fAlpha);
	glVertexPointer(3, GL_FLOAT, 0, m_fRectVert);
	glDrawArrays(glMode, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void OpenGLView::DrawRect(const float& fLineWidth, GLenum glMode /* = GL_LINE_LOOP */)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glLineWidth(fLineWidth);
	glVertexPointer(3, GL_FLOAT, 0, m_fRectVert);
	glColorPointer(4, GL_FLOAT, 0, m_fRectColor);
	glDrawArrays(glMode, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}


void OpenGLView::DrawLine(const int& iWindowHeight, const int& iFromX, const int& iFromY, const int& iToX, const int& iToY, const float& fLineWidth,
	const float& fRed, const float& fGreen, const float& fBlue, const float& fAlpha)
{
	float z;
	double objZ, dFromX, dFromY, dToX, dToY;
	glReadPixels(iFromX, iWindowHeight - iFromY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject(iFromX, iWindowHeight - iFromY, z, m_dModelview, m_dProjection, m_iViewport, &dFromX, &dFromY, &objZ);
	glReadPixels(iToX, iWindowHeight - iToY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject(iToX, iWindowHeight - iToY, z, m_dModelview, m_dProjection, m_iViewport, &dToX, &dToY, &objZ);
	glLineWidth(fLineWidth);
	glBegin(GL_LINES);
	glColor4f(fRed, fGreen, fBlue, fAlpha);
	glVertex2d(dFromX, dFromY);
	glVertex2d(dToX, dToY);
	glEnd();
}

void OpenGLView::DrawLine(const float& fLineWidth)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glLineWidth(fLineWidth);
	glVertexPointer(3, GL_FLOAT, 0, m_fLineVert);
	glColorPointer(4, GL_FLOAT, 0, m_fLineColor);
	glDrawArrays(GL_LINES, 0, 2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
