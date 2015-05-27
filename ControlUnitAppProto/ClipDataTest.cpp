// ClipDataTest.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ControlUnitAppProto.h"
#include "ClipDataTest.h"


// ClipDataTest

ClipDataTest::ClipDataTest()
{
}

ClipDataTest::~ClipDataTest()
{
}


// ClipDataTest メンバー関数
BOOL ClipDataTest::InitializeClipId(UUID& uiClipId)
{
	if (RPC_S_OK == UuidCreate(&m_uiClipId))
	{
		uiClipId = m_uiClipId;
		CreateClipInOutPoint();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void ClipDataTest::CreateClipInOutPoint()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> In(1, 99999999);
	std::uniform_int_distribution<int> Dur(1, 99999);

	m_iInPoint = In(mt);
	m_iDuration = Dur(mt);
	m_iOutPoint = m_iInPoint + m_iDuration - 1;

	return;
}

void ClipDataTest::GetOperatingVert(float(&fVert)[4][3])
{
	for (int i = 0; i < 4; ++i)
	{
		fVert[i][0] = m_fOperatingVert[i][0];
		fVert[i][1] = m_fOperatingVert[i][1];
		fVert[i][2] = m_fOperatingVert[i][2];
	}
	return;
}

void ClipDataTest::SetOperatingVert(const float fLeft, const float fTop, const float fRight, const float fBottom)
{

	m_fOperatingVert[0][0] = fLeft;
	m_fOperatingVert[0][1] = fTop;
	m_fOperatingVert[0][2] = 0.0f;
	m_fOperatingVert[1][0] = fRight;
	m_fOperatingVert[1][1] = fTop;
	m_fOperatingVert[1][2] = 0.0f;
	m_fOperatingVert[2][0] = fRight;
	m_fOperatingVert[2][1] = fBottom;
	m_fOperatingVert[2][2] = 0.0f;
	m_fOperatingVert[3][0] = fLeft;
	m_fOperatingVert[3][1] = fBottom;
	m_fOperatingVert[3][2] = 0.0f;

	return;
}

void ClipDataTest::SetOperatingVert(const int iHeight)
{

	m_fOperatingVert[0][0] = m_rcOperatingRect.left;
	m_fOperatingVert[0][1] = iHeight - m_rcOperatingRect.top;
	m_fOperatingVert[0][2] = 0.0f;
	m_fOperatingVert[1][0] = m_rcOperatingRect.right;
	m_fOperatingVert[1][1] = iHeight - m_rcOperatingRect.top;
	m_fOperatingVert[1][2] = 0.0f;
	m_fOperatingVert[2][0] = m_rcOperatingRect.right;
	m_fOperatingVert[2][1] = iHeight - m_rcOperatingRect.bottom;
	m_fOperatingVert[2][2] = 0.0f;
	m_fOperatingVert[3][0] = m_rcOperatingRect.left;
	m_fOperatingVert[3][1] = iHeight - m_rcOperatingRect.bottom;
	m_fOperatingVert[3][2] = 0.0f;

	return;
}

