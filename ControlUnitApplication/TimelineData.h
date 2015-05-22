#pragma once

// TimelineData �h�L�������g

class TimelineData : public CDocument
{
	DECLARE_DYNCREATE(TimelineData)

public:
	TimelineData();
	virtual ~TimelineData();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // �h�L�������g I/O �ɑ΂��ăI�[�o�[���C�h����܂����B
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};
