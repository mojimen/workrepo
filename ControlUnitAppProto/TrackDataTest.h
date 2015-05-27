#pragma once

#include <list>
#include <map>
#include <rpc.h>
#pragma comment(lib ,"rpcrt4.lib")

#include "RectOpenGL.h"

// TrackDataTest コマンド ターゲット

typedef std::map<int, UUID> ClipDataInfoMap;	//InPoint,ClipId 

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
	TrackKind m_eClipKind;
	CString m_strTrackName;
	UUID m_uiInputChannel;
	UUID m_uiOutputChannel;
	ClipDataInfoMap m_ClipDataInfoMap;

	// 再生時参照項目
	BOOL m_fSolo;
	BOOL m_fAudioRecordable;
	BOOL m_fMuted;
	BOOL m_fLevelPointRecordable;
	// 編集時参照項目
	BOOL m_fLocked;
	BOOL m_fGapless;
	// 画面表示参照項目
	BOOL m_fDisplayOverlay;
	BOOL m_fDisplayLevelPoint;
	int m_iHeight;


public:
	BOOL InitializeClipId(UUID& uiClipId);

	int GetHeight(void) { return m_iHeight; }
	PCTSTR GetTrackName(void) { return static_cast<PCTSTR>(m_strTrackName); }

	void SetTrackName(PCTSTR pszTrackName) { m_strTrackName = static_cast<CString>(pszTrackName); }
	void SetHeight(int iHeight) { m_iHeight = iHeight; }

};


