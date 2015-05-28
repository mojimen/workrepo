// TrackDataTest.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ControlUnitAppProto.h"
#include "TrackDataTest.h"
#include "ClipDataTest.h"


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

ClipDataTest* TrackDataTest::GetClip(int iFrame, int& iInPoint)
{
	if (m_mpClipDataInfoMap.size() == 0)
	{
		return nullptr;
	}
	ClipDataInfoMap::iterator itr = m_mpClipDataInfoMap.upper_bound(iFrame);
	if (itr == m_mpClipDataInfoMap.begin())
	{
		return nullptr;
	}
	--itr;
	ClipDataTest* pClipData = (*itr).second;
	if (((*itr).first <= iFrame) && (iFrame <= ((*itr).first + pClipData->GetDuration() - 1)))
	{
		iInPoint = (*itr).first;
		return pClipData;
	}
	else
	{
		return nullptr;
	}

}




void TrackDataTest::AddClip(const int iInPoint, ClipDataTest* pClipData)
{
	m_mpClipDataInfoMap[iInPoint] = pClipData;
}

void TrackDataTest::DeleteClip(const int iInPoint)
{
	m_mpClipDataInfoMap.erase(iInPoint);
}

void TrackDataTest::ChangeClip(const int iOldInPoint, const int iNewInPoint, ClipDataTest* pClipData)
{
	DeleteClip(iOldInPoint);
	AddClip(iNewInPoint, pClipData);
}


// TODO: これはコントローラーにあるべき
ClipDataTest* TrackDataTest::CheckMove(ClipDataTest* pCheckClipData, const int iInPoint, const int iOutPoint)
{
	ClipDataTest* pClipData;
	int iPoint;
	pClipData = GetClip(iInPoint, iPoint);
	if ((pClipData != nullptr) && (pClipData != pCheckClipData))
	{
		return pClipData;
	}
	pClipData = GetClip(iOutPoint, iPoint);
	if ((pClipData != nullptr) && (pClipData != pCheckClipData))
	{
		return pClipData;
	}
	// 移動中のクリップに含まれるクリップがないかをチェック
	ClipDataInfoMap::iterator itr = m_mpClipDataInfoMap.upper_bound(iInPoint);
	if (itr == m_mpClipDataInfoMap.end())
	{
		return nullptr;
	}
	if (iOutPoint < (*itr).first)
	{
		return nullptr;
	}
	else
	{
		return (*itr).second;
	}

}