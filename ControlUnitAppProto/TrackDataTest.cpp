// TrackDataTest.cpp : �����t�@�C��
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


// TrackDataTest �����o�[�֐�

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
