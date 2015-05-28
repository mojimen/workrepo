#pragma once

#include <list>
#include <map>
#include <rpc.h>
#pragma comment(lib ,"rpcrt4.lib")

#include "RectOpenGL.h"

class ClipDataTest;

// TrackDataTest �R�}���h �^�[�Q�b�g

typedef std::map<int, ClipDataTest*> ClipDataInfoMap;	//InPoint,ClipId 
//typedef std::map<int, UUID> ClipDataInfoMap;	//InPoint,ClipId 

class TrackDataTest : public RectOpenGL
{
public:
	TrackDataTest();
	virtual ~TrackDataTest();

	enum TrackDataInfoTag{ TRACKDATAINFO };
	enum TrackKind {
		VIDEO,
		AUDIO,
		TITLE,
		INFO,
		MASTER_VIDEO,
		MASTER_AUDIO
	};

private:
	TrackDataInfoTag m_eTrackDataInfoTag;
	UUID m_uiTrackId;
	TrackKind m_eTrackKind;
	CString m_strTrackName;
	UUID m_uiInputChannel;
	UUID m_uiOutputChannel;
	ClipDataInfoMap m_mpClipDataInfoMap;

	// �Đ����Q�ƍ���
	BOOL m_fSolo;
	BOOL m_fAudioRecordable;
	BOOL m_fMuted;
	BOOL m_fLevelPointRecordable;
	// �ҏW���Q�ƍ���
	BOOL m_fLocked;
	BOOL m_fGapless;
	// ��ʕ\���Q�ƍ���
	BOOL m_fDisplayOverlay;
	BOOL m_fDisplayLevelPoint;
	int m_iHeight;


public:
	BOOL InitializeClipId(UUID& uiClipId);

	int GetHeight(void) { return m_iHeight; }
	PCTSTR GetTrackName(void) { return static_cast<PCTSTR>(m_strTrackName); }
	// TODO: �܂��̓N���b�v���d�Ȃ�Ȃ��O��
	ClipDataTest* GetClip(int iFrame, int& iInPoint);

	void SetTrackName(PCTSTR pszTrackName) { m_strTrackName = static_cast<CString>(pszTrackName); }
	void SetHeight(int iHeight) { m_iHeight = iHeight; }
	void AddClip(const int iInPoint, ClipDataTest* pClipData);
	void DeleteClip(const int iInPoint);
	void ChangeClip(const int iOldInPoint, const int iNewInPoint, ClipDataTest* pClipData);
	ClipDataTest* CheckMove(ClipDataTest* pCheckClipData, const int iInPoint, const int iOutPoint);

};


