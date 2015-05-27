#pragma once
#include <list>
#include <map>
#include <rpc.h>

#pragma comment(lib ,"rpcrt4.lib")

#include "RectOpenGL.h"

// Debug
#include <random>


// ClipDataTest コマンド ターゲット

struct FilterInfo
{
	int iOutPoint;
	int iDuration;
	UUID uiFilterId;
};


class ClipDataTest : public RectOpenGL
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

	// ForView
	CRect m_rcOperatingRect;
	//double m_dMovingWorldLeft;
	//double m_dMovingWorldRight;
	//double m_dMovingWorldTop;
	//double m_dMovingWorldBottom;
	float m_fOperatingVert[4][3];


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
	void SetOperatingRect(const CRect& rcRect) { m_rcOperatingRect.CopyRect(rcRect); }
	void CopyOperatingRectToOriginalRect(void) { CopyRect(m_rcOperatingRect); m_rcOperatingRect.SetRectEmpty(); }
	//void SetMovingWorldLeft(double dLeft) { m_dMovingWorldLeft = dLeft; }
	//void SetMovingWorldRight(double dRight) { m_dMovingWorldRight = dRight; }
	//void SetMovingWorldTop(double dTop) { m_dMovingWorldTop = dTop; }
	//void SetMovingWorldBottom(double dBottom) { m_dMovingWorldBottom = dBottom; }
	//void SetMovingWorldPoint(const double dLeft, const double dRight, const double dTop, const double dBottom);
	void SetOperatingVert(const float fLeft, const float fTop, const float fRight, const float fBottom);
	void SetOperatingVert(const int iHeight);

	void InitializeOperatingRect(void) { m_rcOperatingRect.SetRectEmpty(); }

	ClipDataInfoTag GetTag(void) { return m_eClipDataInfoTag; }
	UUID GetClipId(void) { return m_uiClipId; }
	ClipKind GetClipKind(void) { return m_eClipKind; }
	UUID GetFileId(void) { return m_uiFileId; }
	int GetInPoint(void) { return m_iInPoint; }
	int GetOutPoint(void) { return m_iOutPoint; }
	int GetDuration(void) { return m_iDuration; }
	int GetInOffset(void) { return m_iInOffset; }
	CRect* GetOperatingRect(void) { return &m_rcOperatingRect; }
	//double GetMovingWorldLeft(void) { return m_dMovingWorldLeft; }
	//double GetMovingWorldRight(void) { return m_dMovingWorldRight; }
	//double GetMovingWorldTop(void) { return m_dMovingWorldTop; }
	//double GetMovingWorldBottom(void) { return m_dMovingWorldBottom; }
	//void GetMovingWorldPoint(double& dLeft, double& dRight, double& dTop, double& dBottom);
	float(*GetOperatingVert(void))[3] { return m_fOperatingVert; }
	void GetOperatingVert(float(&fVert)[4][3]);




};


