// RectOpenGL.cpp : ŽÀ‘•ƒtƒ@ƒCƒ‹
//

#include "stdafx.h"
#include "ControlUnitAppProto.h"
#include "RectOpenGL.h"


// RectOpenGL

RectOpenGL::RectOpenGL()
{
}

RectOpenGL::~RectOpenGL()
{
}


void RectOpenGL::GetVert(float (&fVert)[4][3])
{
	for (int i = 0; i < 4; ++i)
	{
		fVert[i][0] = m_fVert[i][0];
		fVert[i][1] = m_fVert[i][1];
		fVert[i][2] = m_fVert[i][2];
	}
	return;
}

void RectOpenGL::GetBorderVert(float(&fVert)[4][3])
{
	for (int i = 0; i < 4; ++i)
	{
		fVert[i][0] = m_fVert[i][0];
		fVert[i][1] = m_fVert[i][1];
		fVert[i][2] = m_fVert[i][2];
	}
	fVert[0][0] += 1;
	fVert[2][1] += 1;
	fVert[3][0] += 1;
	fVert[3][1] += 1;
	return;
}

void RectOpenGL::GetLeftBorderVert(float(&fVert)[2][3])
{
	fVert[0][0] = m_fVert[0][0] + 1;
	fVert[0][1] = m_fVert[0][1];
	fVert[0][2] = m_fVert[0][2];
	fVert[1][0] = m_fVert[3][0] + 1;
	fVert[1][1] = m_fVert[3][1] + 1;
	fVert[1][2] = m_fVert[3][2];
}

void RectOpenGL::GetTopBorderVert(float(&fVert)[2][3])
{
	fVert[0][0] = m_fVert[0][0] + 1;
	fVert[0][1] = m_fVert[0][1];
	fVert[0][2] = m_fVert[0][2];
	fVert[1][0] = m_fVert[1][0];
	fVert[1][1] = m_fVert[1][1];
	fVert[1][2] = m_fVert[1][2];
}

void RectOpenGL::GetRightBorderVert(float(&fVert)[2][3])
{
	fVert[0][0] = m_fVert[1][0];
	fVert[0][1] = m_fVert[1][1];
	fVert[0][2] = m_fVert[1][2];
	fVert[1][0] = m_fVert[2][0];
	fVert[1][1] = m_fVert[2][1] + 1;
	fVert[1][2] = m_fVert[2][2];
}

void RectOpenGL::GetBottomBorderVert(float(&fVert)[2][3])
{
	fVert[0][0] = m_fVert[2][0];
	fVert[0][1] = m_fVert[2][1] + 1;
	fVert[0][2] = m_fVert[2][2];
	fVert[1][0] = m_fVert[3][0] + 1;
	fVert[1][1] = m_fVert[3][1] + 1;
	fVert[1][2] = m_fVert[3][2];
}

void RectOpenGL::GetLeftBorderColor(float(&fVert)[2][4])
{
	fVert[0][0] = m_fBorderColor[0][0];
	fVert[0][1] = m_fBorderColor[0][1];
	fVert[0][2] = m_fBorderColor[0][2];
	fVert[0][3] = m_fBorderColor[0][3];
	fVert[1][0] = m_fBorderColor[3][0];
	fVert[1][1] = m_fBorderColor[3][1];
	fVert[1][2] = m_fBorderColor[3][2];
	fVert[1][3] = m_fBorderColor[3][3];
}

void RectOpenGL::GetTopBorderColor(float(&fVert)[2][4])
{
	fVert[0][0] = m_fBorderColor[0][0];
	fVert[0][1] = m_fBorderColor[0][1];
	fVert[0][2] = m_fBorderColor[0][2];
	fVert[0][3] = m_fBorderColor[0][3];
	fVert[1][0] = m_fBorderColor[1][0];
	fVert[1][1] = m_fBorderColor[1][1];
	fVert[1][2] = m_fBorderColor[1][2];
	fVert[1][3] = m_fBorderColor[1][3];
}

void RectOpenGL::GetRightBorderColor(float(&fVert)[2][4])
{
	fVert[0][0] = m_fBorderColor[1][0];
	fVert[0][1] = m_fBorderColor[1][1];
	fVert[0][2] = m_fBorderColor[1][2];
	fVert[0][3] = m_fBorderColor[1][3];
	fVert[1][0] = m_fBorderColor[2][0];
	fVert[1][1] = m_fBorderColor[2][1];
	fVert[1][2] = m_fBorderColor[2][2];
	fVert[1][3] = m_fBorderColor[2][3];
}

void RectOpenGL::GetBottomBorderColor(float(&fVert)[2][4])
{
	fVert[0][0] = m_fBorderColor[2][0];
	fVert[0][1] = m_fBorderColor[2][1];
	fVert[0][2] = m_fBorderColor[2][2];
	fVert[0][3] = m_fBorderColor[2][3];
	fVert[1][0] = m_fBorderColor[3][0];
	fVert[1][1] = m_fBorderColor[3][1];
	fVert[1][2] = m_fBorderColor[3][2];
	fVert[1][3] = m_fBorderColor[3][3];
}


void RectOpenGL::GetColor(float(&fColor)[4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		fColor[i][0] = m_fColor[i][0];
		fColor[i][1] = m_fColor[i][1];
		fColor[i][2] = m_fColor[i][2];
		fColor[i][3] = m_fColor[i][3];
	}
	return;
}

void RectOpenGL::GetBorderColor(float(&fColor)[4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		fColor[i][0] = m_fBorderColor[i][0];
		fColor[i][1] = m_fBorderColor[i][1];
		fColor[i][2] = m_fBorderColor[i][2];
		fColor[i][3] = m_fBorderColor[i][3];
	}
	return;
}

void RectOpenGL::SetVert(const float fLeft, const float fTop, const float fRight, const float fBottom)
{

	m_fVert[0][0] = fLeft;
	m_fVert[0][1] = fTop;
	m_fVert[0][2] = 0.0f;
	m_fVert[1][0] = fRight;
	m_fVert[1][1] = fTop;
	m_fVert[1][2] = 0.0f;
	m_fVert[2][0] = fRight;
	m_fVert[2][1] = fBottom;
	m_fVert[2][2] = 0.0f;
	m_fVert[3][0] = fLeft;
	m_fVert[3][1] = fBottom;
	m_fVert[3][2] = 0.0f;

	return;
}

void RectOpenGL::SetVert(const int iHeight)
{

	m_fVert[0][0] = left;
	m_fVert[0][1] = iHeight - top;
	m_fVert[0][2] = 0.0f;
	m_fVert[1][0] = right;
	m_fVert[1][1] = iHeight - top;
	m_fVert[1][2] = 0.0f;
	m_fVert[2][0] = right;
	m_fVert[2][1] = iHeight - bottom;
	m_fVert[2][2] = 0.0f;
	m_fVert[3][0] = left;
	m_fVert[3][1] = iHeight - bottom;
	m_fVert[3][2] = 0.0f;

	return;
}

void RectOpenGL::SetColor(const float fR1, const float fG1, const float fB1, const float fA1,
	const float fR2, const float fG2, const float fB2, const float fA2,
	const float fR3, const float fG3, const float fB3, const float fA3,
	const float fR4, const float fG4, const float fB4, const float fA4)
{

	m_fColor[0][0] = fR1;
	m_fColor[0][1] = fG1;
	m_fColor[0][2] = fB1;
	m_fColor[0][3] = fA1;
	m_fColor[1][0] = fR2;
	m_fColor[1][1] = fG2;
	m_fColor[1][2] = fB2;
	m_fColor[1][3] = fA2;
	m_fColor[2][0] = fR3;
	m_fColor[2][1] = fG3;
	m_fColor[2][2] = fB3;
	m_fColor[2][3] = fA3;
	m_fColor[3][0] = fR4;
	m_fColor[3][1] = fG4;
	m_fColor[3][2] = fB4;
	m_fColor[3][3] = fA4;

	return;
}

void RectOpenGL::SetBorderColor(const float fR1, const float fG1, const float fB1, const float fA1,
	const float fR2, const float fG2, const float fB2, const float fA2,
	const float fR3, const float fG3, const float fB3, const float fA3,
	const float fR4, const float fG4, const float fB4, const float fA4)
{

	m_fBorderColor[0][0] = fR1;
	m_fBorderColor[0][1] = fG1;
	m_fBorderColor[0][2] = fB1;
	m_fBorderColor[0][3] = fA1;
	m_fBorderColor[1][0] = fR2;
	m_fBorderColor[1][1] = fG2;
	m_fBorderColor[1][2] = fB2;
	m_fBorderColor[1][3] = fA2;
	m_fBorderColor[2][0] = fR3;
	m_fBorderColor[2][1] = fG3;
	m_fBorderColor[2][2] = fB3;
	m_fBorderColor[2][3] = fA3;
	m_fBorderColor[3][0] = fR4;
	m_fBorderColor[3][1] = fG4;
	m_fBorderColor[3][2] = fB4;
	m_fBorderColor[3][3] = fA4;

	return;
}
