// TrackDataTest.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ControlUnitAppProto.h"
#include "TrackDataTest.h"


// TrackDataTest

TrackDataTest::TrackDataTest()
{
}

TrackDataTest::~TrackDataTest()
{
}


// TrackDataTest メンバー関数

BOOL TrackDataTest::InitializeClipId(UUID& uiClipId)
{
	if (RPC_S_OK == UuidCreate(&m_uiTrackId))
	{
		uiClipId = m_uiTrackId;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
