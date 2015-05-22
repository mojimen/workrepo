// TimelineData.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ControlUnitApplication.h"
#include "TimelineData.h"


// TimelineData

IMPLEMENT_DYNCREATE(TimelineData, CDocument)

TimelineData::TimelineData()
{
}

BOOL TimelineData::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

TimelineData::~TimelineData()
{
}


BEGIN_MESSAGE_MAP(TimelineData, CDocument)
END_MESSAGE_MAP()


// TimelineData 診断

#ifdef _DEBUG
void TimelineData::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void TimelineData::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// TimelineData シリアル化

void TimelineData::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 格納するコードをここに追加してください。
	}
	else
	{
		// TODO: 読み込むコードをここに追加してください。
	}
}
#endif


// TimelineData コマンド
