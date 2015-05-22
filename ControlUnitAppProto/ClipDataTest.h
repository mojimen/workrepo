#pragma once
#include <list>
#include <map>
#include <random>
#include <rpc.h>
#pragma comment(lib ,"rpcrt4.lib")

// ClipDataTest コマンド ターゲット

struct FilterInfo
{
	int iOutPoint;
	int iDuration;
	UUID uiFilterId;
};


class ClipDataTest : public CObject
{

public:
	ClipDataTest();
	virtual ~ClipDataTest();


	enum ClipDataInfoTag{ CLIPDATAINFO };
	enum ClipKind {
		VIDEO,
		AUDIO,
		TITLE,
		MASTER_VIDEO,
		MASTER_AUDIO
	};

private:
	ClipDataInfoTag m_eClipDataInfoTag;
	UUID m_uiClipId;
	ClipKind m_eClipKind;
	UUID m_uiFileId;
	int m_iInPoint;
	int m_iOutPoint;
	int m_iDuration;
	int m_iInOffset;
	UUID m_uiMetaInfoId;
	std::list<UUID> m_uiVideoLevelPointList;
	std::list<UUID> m_uiAudioLevelPointList;
	std::list<UUID> m_uiVALinkList;
	BOOL m_fLocked;
	std::map < int, FilterInfo > m_FilterMap;	//InPoint, FilterInfo 

	// For Prototype
	CRect m_rcDisplayRect;
	CRect m_rcCurrentRect;

public:
	int m_iTimelineInPoint; // プロト設計中のワーク項目


	void CreateClipInOutPoint(void);


public:

	BOOL InitializeClipId(UUID& uiClipId);

	void SetTag(ClipDataInfoTag eTag) { m_eClipDataInfoTag = eTag; }
	void SetClipId(UUID uiClipId) { m_uiClipId = uiClipId; }
	void SetClipKind(ClipKind eClipKind) { m_eClipKind = eClipKind; }
	void SetFileId(UUID uiFileId) { m_uiFileId = uiFileId; }
	void SetInPoint(int iInPoint) { m_iInPoint = iInPoint; }
	void SetOutPoint(int iOutPoint) { m_iOutPoint = iOutPoint; }
	void SetDuration(int iDuration) { m_iDuration = iDuration; }
	void SetInOffset(int iInOffset) { m_iInOffset = iInOffset; }

	ClipDataInfoTag GetTag(void) { return m_eClipDataInfoTag; }
	UUID GetClipId(void) { return m_uiClipId; }
	ClipKind GetClipKind(void) { return m_eClipKind; }
	UUID GetFileId(void) { return m_uiFileId; }
	int GetInPoint(void) { return m_iInPoint; }
	int GetOutPoint(void) { return m_iOutPoint; }
	int GetDuration(void) { return m_iDuration; }
	int GetInOffset(void) { return m_iInOffset; }

	// For Prototype
	void SetCurrentRect(const CRect& rcRect) { m_rcCurrentRect.CopyRect(rcRect); }
	CRect GetCurrentRect(void) { return m_rcCurrentRect; }
	void SetDisplayRect(const CRect& rcRect) { m_rcDisplayRect.CopyRect(rcRect); }
	CRect GetDisplayRect(void) { return m_rcDisplayRect; }


};


