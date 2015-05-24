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
