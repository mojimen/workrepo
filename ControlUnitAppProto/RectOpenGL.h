#pragma once

// RectOpenGL コマンド ターゲット

class RectOpenGL : public CRect
{
protected:
	// OpenGL上での座標
	float m_fVert[4][3];
	float m_fColor[4][4];
	float m_fBorderColor[4][4];

public:
	RectOpenGL();
	virtual ~RectOpenGL();

	float (*GetVert(void))[3] { return m_fVert; }
	float (*GetColor(void))[4] { return m_fColor; }
	float (*GetBorderColor(void))[4] { return m_fBorderColor; }
	void GetVert(float(&fVert)[4][3]);
	void GetBorderVert(float(&fVert)[4][3]);
	void GetLeftBorderVert(float(&fVert)[2][3]);
	void GetTopBorderVert(float(&fVert)[2][3]);
	void GetRightBorderVert(float(&fVert)[2][3]);
	void GetBottomBorderVert(float(&fVert)[2][3]);
	void GetColor(float(&fcolor)[4][4]);
	void GetBorderColor(float(&fcolor)[4][4]);
	void GetLeftBorderColor(float(&fVert)[2][4]);
	void GetTopBorderColor(float(&fVert)[2][4]);
	void GetRightBorderColor(float(&fVert)[2][4]);
	void GetBottomBorderColor(float(&fVert)[2][4]);

	void SetVert(const float fLeft, const float fTop, const float fRight, const float fBottom);
	void SetVert(const int iHeight);
	void SetColor(const float fR1, const float fG1, const float fB1, const float fA1,
		const float fR2, const float fG2, const float fB2, const float fA2, 
		const float fR3, const float fG3, const float fB3, const float fA3, 
		const float fR4, const float fG4, const float fB4, const float fA4);
	void SetBorderColor(const float fR1, const float fG1, const float fB1, const float fA1,
		const float fR2, const float fG2, const float fB2, const float fA2,
		const float fR3, const float fG3, const float fB3, const float fA3,
		const float fR4, const float fG4, const float fB4, const float fA4);

};


