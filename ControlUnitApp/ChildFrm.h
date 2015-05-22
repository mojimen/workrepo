
// ChildFrm.h : CChildFrame クラスのインターフェイス
//

#pragma once
class CControlUnitAppView;

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 属性
protected:
	CSplitterWndEx m_wndSplitter;
public:

// 操作
public:

// オーバーライド
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 実装
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CControlUnitAppView* GetRightPane();
// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
};
