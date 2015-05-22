
// ProtoType4K8KApplicationDoc.h : CProtoType4K8KApplicationDoc クラスのインターフェイス
//


#pragma once


class CProtoType4K8KApplicationDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CProtoType4K8KApplicationDoc();
	DECLARE_DYNCREATE(CProtoType4K8KApplicationDoc)

// 属性
public:

// 操作
public:

// オーバーライド
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 実装
public:
	virtual ~CProtoType4K8KApplicationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 検索ハンドラーの検索コンテンツを設定するヘルパー関数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
