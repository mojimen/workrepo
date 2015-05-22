#pragma once

// TimelineData ドキュメント

class TimelineData : public CDocument
{
	DECLARE_DYNCREATE(TimelineData)

public:
	TimelineData();
	virtual ~TimelineData();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // ドキュメント I/O に対してオーバーライドされました。
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
