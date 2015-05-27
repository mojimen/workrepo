
// ChildFrm.cpp : CChildFrame クラスの実装
//

#include "stdafx.h"
#include "ControlUnitAppProto.h"

#include "ChildFrm.h"

#include "ControlUnitAppProtoDoc.h"
#include "ControlUnitAppProtoView.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CChildFrame コンストラクション/デストラクション

CChildFrame::CChildFrame()
{
	// TODO: メンバー初期化コードをここに追加してください。
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs を変更して、Window クラスまたはスタイルを変更します。
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

// CChildFrame 診断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame メッセージ ハンドラー

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	////動的な分割の例
	//return m_wndSplitter.Create(this, 2, 2, CSize(10, 10), pContext);

	if (!m_wndSplitter.CreateStatic(this,
		2, 1,                 // TODO: 行と列の数を調整してください。
		WS_CHILD | WS_VISIBLE)
		) return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(TestView), CSize(1000, 400), pContext)) return FALSE;
	if (!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CControlUnitAppProtoView), CSize(128, 64), pContext)) return FALSE;

	return TRUE;
}

BOOL CChildFrame::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	//return TRUE;

	return CMDIChildWndEx::OnEraseBkgnd(pDC);
}
