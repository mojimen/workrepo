// TimelineData.cpp : �����t�@�C��
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


// TimelineData �f�f

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
// TimelineData �V���A����

void TimelineData::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �i�[����R�[�h�������ɒǉ����Ă��������B
	}
	else
	{
		// TODO: �ǂݍ��ރR�[�h�������ɒǉ����Ă��������B
	}
}
#endif


// TimelineData �R�}���h
