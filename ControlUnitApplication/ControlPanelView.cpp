// ControlPanelView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ControlUnitApplication.h"
#include "ControlPanelView.h"


// ControlPanelView

IMPLEMENT_DYNCREATE(ControlPanelView, CFormView)

ControlPanelView::ControlPanelView()
	: CFormView(ControlPanelView::IDD)
{

}

ControlPanelView::~ControlPanelView()
{
}

void ControlPanelView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ControlPanelView, CFormView)
END_MESSAGE_MAP()


// ControlPanelView 診断

#ifdef _DEBUG
void ControlPanelView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ControlPanelView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ControlPanelView メッセージ ハンドラー
