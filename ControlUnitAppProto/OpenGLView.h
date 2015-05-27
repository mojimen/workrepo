#pragma once

//	OpenGL�̃w�b�_���C���N���[�h
#include <GL/gl.h>
#include <GL/glu.h>

#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")

// OpenGLView �r���[

class OpenGLView : public CView
{
	DECLARE_DYNCREATE(OpenGLView)

protected:
	OpenGLView();           // ���I�����Ŏg�p����� protected �R���X�g���N�^�[
	virtual ~OpenGLView();

public:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h����܂��B
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

protected:
	HGLRC m_hRC;
	CDC* m_pDC;
	int m_iViewport[4];
	double m_dProjection[16];
	double m_dModelview[16];
	float m_fLineVert[2][3];	// ���`�掞���W�̒��_�z��
	float m_fLineColor[2][4];	// ���`�掞�F�̒��_�z��
	float m_fRectVert[4][3];	// �l�p�`�`�掞���W�̒��_�z��
	float m_fRectColor[4][4];	// �l�p�`�`�掞���W�̒��_�z��

	int DrawTextOnGL(PCTSTR pszStr, HDC hDC, HFONT& hfFont, GLfloat gfRed, GLfloat gfGreen, GLfloat gfBlue, GLfloat gfAlpha,
		GLfloat gfPosX, GLfloat gfPosY, GLfloat gfPosZ, GLfloat gfMoveX);
	BOOL CreateDrawFont(int iHeight, int iAngle, PCTSTR pszFace, HFONT& hfFont);
	void ChangeScreenPointToOpenGLPoint(const int iPointX, const int iPointY, int iWindowHeight, double& dPointX, double& dPointY);
	void ChangeScreenRectToOpenGLPoint(const CRect& rcScreenRect, int iWindowHeight, double& dLeft, double& dRight, double& dTop, double& dBottom);
	void DrawRect(const double& dLeft, const double& dRight, const double& dTop, const double& dBottom, const float& fLineWidth, 
		const float& fRed, const float& fGreen, const float& fBlue, const float& fAlpha, GLenum glMode = GL_LINE_LOOP);
	void DrawRect(const float& fLineWidth, const float& fRed, const float& fGreen, const float& fBlue, const float& fAlpha, GLenum glMode = GL_LINE_LOOP);
	void DrawRect(const float& fLineWidth, GLenum glMode = GL_LINE_LOOP);
	void DrawLine(const int& iWindowHeight, const int& dFromX, const int& dFromY, const int& dToX, const int& dToY, const float& fLineWidth,
		const float& fRed, const float& fGreen, const float& fBlue, const float& fAlpha);
	void DrawLine(const float& fLineWidth);

	virtual BOOL SetupPixelFormat();
	virtual BOOL InitGLContext();
	virtual void PreSubclassWindow();

public:
	virtual afx_msg void OnDestroy();
	virtual afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual afx_msg void OnSize(UINT nType, int cx, int cy);

};


