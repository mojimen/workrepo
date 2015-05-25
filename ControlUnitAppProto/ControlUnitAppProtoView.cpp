
// ControlUnitAppProtoView.cpp : CControlUnitAppProtoView �N���X�̎���
//
// �ړ�����̖{�i�Ή��A�N���b�v�אڎ��̋��E���A�g�����W�V�����A�c�[���`�b�v�A���b�v���^�f���A���A�f�o�C�X�R���e�L�X�g�쐬�����Ȃ��A�ړ������傫�����̃A�j���[�V�����A�E�B���h�E�S�̕`��

//#include "math.h"


#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "ControlUnitAppProto.h"
#endif

#include "ControlUnitAppProtoDoc.h"
#include "ControlUnitAppProtoView.h"
#include "ClipDataTest.h"
#include "TestDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PROTOTYPEMODE


// CControlUnitAppProtoView

IMPLEMENT_DYNCREATE(CControlUnitAppProtoView, CView)

BEGIN_MESSAGE_MAP(CControlUnitAppProtoView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()

// CControlUnitAppProtoView �R���X�g���N�V����/�f�X�g���N�V����

CControlUnitAppProtoView::CControlUnitAppProtoView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

	// TODO: �Ƃ肠�����͂����ɂ����Ă������A�ʓrInit�Ƃ��Ɏ����Ă���
	m_clClipData1 = new ClipDataTest();
	m_clClipData2 = new ClipDataTest();
	m_clClipData1->m_iTimelineInPoint = 101;
	m_clClipData1->SetDuration(10);
	m_clClipData2->m_iTimelineInPoint = 600;
	m_clClipData2->SetDuration(100);

	m_fLButtonClicking = FALSE;
	m_fMoving = FALSE;
	m_fSingleInTriming = FALSE;
	m_fSingleOutTriming = FALSE;
	m_fScrubing = FALSE;
	m_fDragShuttling = FALSE;

	m_rcPreviewPanelRect.bottom = m_rcPreviewPanelRect.top + kPreviewPanelDefaltHeight;
	//m_rcTimelineEditPanelRect.bottom = m_rcTimelineEditPanelRect.top + kTimelineEditDefaltHeight;

	m_iLeftFrameNumber = 0;
	m_iRightFrameNumber = 0;
	m_iTimelineCursorFramePosition = 0;
	m_iOperatingFrameCount = 0;
	m_iOperatingClipFrameCount = 0;

	m_iSelectedDisplayScaleNumber = 8;
	ChangeDisplayScale();


}

CControlUnitAppProtoView::~CControlUnitAppProtoView()
{
}

BOOL CControlUnitAppProtoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);

}

// CControlUnitAppProtoView �`��

void CControlUnitAppProtoView::OnDraw(CDC* /*pDC*/)
{
	CControlUnitAppProtoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
}

// �E�{�^���A�b�v
void CControlUnitAppProtoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	if (m_rcTimelineControlPanelRect.PtInRect(point))
	{
		++m_iSelectedDisplayScaleNumber;
		if (ChangeDisplayScale())
		{
			Invalidate();
		}
	}
	else
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}
}

void CControlUnitAppProtoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CControlUnitAppProtoView �f�f

#ifdef _DEBUG
void CControlUnitAppProtoView::AssertValid() const
{
	CView::AssertValid();
}

void CControlUnitAppProtoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CControlUnitAppProtoDoc* CControlUnitAppProtoView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CControlUnitAppProtoDoc)));
	return (CControlUnitAppProtoDoc*)m_pDocument;
}
#endif //_DEBUG


// CControlUnitAppProtoView ���b�Z�[�W �n���h���[

// ���{�^���_�E��
void CControlUnitAppProtoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	// �^�C�����C���f�[�^�G���A������
	if(m_rcTimelineDataRect.PtInRect(point))
	{
		// �N���b�v����
		if (IsPointInAnyClipRect(point))
		{
			m_fLButtonClicking = TRUE;
			SetCapture(); // �}�E�X���L���v�`���[( OnLButtonUp()�ŉ��)
			m_poMousePointerLocation = point;	// �ړ��ʌv�Z�̂��߁A�������W��ۑ�
			m_clMovingClipData->SetOperatingRect(static_cast<CRect>(m_clMovingClipData));
			m_rcBorderRect.CopyRect(static_cast<CRect>(m_clMovingClipData));
			m_iOperatingClipFrameCount = 0;
			Invalidate();
		}
		// �^�C�����C���J�[�\������
		else if (m_rcTimelineCursorHitArea.PtInRect(point))
		{
			m_fLButtonClicking = TRUE;
			m_fDragShuttling = TRUE;
			SetCapture(); // �}�E�X���L���v�`���[( OnLButtonUp()�ŉ��)
			m_poMousePointerLocation = point;	// �ړ��ʌv�Z�̂��߁A�������W��ۑ�
			m_iOperatingFrameCount = 0;
			m_fSuttleSpeed = 0;
			Invalidate();
		}
	}
	else
	{
		// �^�C�����C���J�[�\������
		if (m_rcTimelineCursorHitArea.PtInRect(point))
		{
			m_fLButtonClicking = TRUE;
			m_fDragShuttling = TRUE;
			SetCapture(); // �}�E�X���L���v�`���[( OnLButtonUp()�ŉ��)
			m_poMousePointerLocation = point;	// �ړ��ʌv�Z�̂��߁A�������W��ۑ�
			m_iOperatingFrameCount = 0;
			m_fSuttleSpeed = 0;
			Invalidate();
		}
		// �V�[�N�o�[������
		else if (IsPointInSeekBar(point))
		{
			m_fLButtonClicking = TRUE;
			m_fScrubing = TRUE;
			SetCapture(); // �}�E�X���L���v�`���[( OnLButtonUp()�ŉ��)
			m_poMousePointerLocation = point;	// �ړ��ʌv�Z�̂��߁A�������W��ۑ�
			m_iOperatingFrameCount = 0;

			//TODO: �f�o�b�O�p�Ȃ̂Ō�ō폜
#ifdef PROTOTYPEMODE
			int iFrame = ChangeDisplayPointToTimelineFramePosition(point);
			CDC* pDC = GetDC();
			CRect rcViewRect;
			GetClientRect(&rcViewRect);
			CString strFrameNumber;
			strFrameNumber.Format(_T("SEEKBAR CLICK FRAME %d"), iFrame);
			pDC->TextOutW(300, 5, strFrameNumber);
			strFrameNumber.Format(_T("SEEKBAR CLICK POINT %d"), point.x);
			pDC->TextOutW(300, 40, strFrameNumber);
			pDC->DeleteDC();
#endif
		}
		// �^�C�����C���R���g���[���p�l��������
		else if (m_rcTimelineControlPanelRect.PtInRect(point))
		{
			--m_iSelectedDisplayScaleNumber;
			if (ChangeDisplayScale())
			{
				Invalidate();
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

// ���{�^���A�b�v
void CControlUnitAppProtoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	m_fLButtonClicking = FALSE; // �t���O��������
	ReleaseCapture(); // �}�E�X��������܂��B

	if (m_fMoving)
	{
		m_clMovingClipData->m_iTimelineInPoint += m_iOperatingClipFrameCount;
		m_clMovingClipData->CopyRect(m_clMovingClipData->GetOperatingRect());
	}
	else if (m_fSingleInTriming)
	{
		m_clMovingClipData->m_iTimelineInPoint += m_iOperatingClipFrameCount;
		int iClipDuration = m_clMovingClipData->GetDuration();
		// In���ɐL�т�i�}�C�i�X�����ւ̈ړ��j�͒��������Z
		m_clMovingClipData->SetDuration(iClipDuration - m_iOperatingClipFrameCount);
		m_clMovingClipData->CopyRect(m_clMovingClipData->GetOperatingRect());
	}
	else if (m_fSingleOutTriming)
	{
		int iClipDuration = m_clMovingClipData->GetDuration();
		m_clMovingClipData->SetDuration(iClipDuration + m_iOperatingClipFrameCount);
		m_clMovingClipData->CopyRect(m_clMovingClipData->GetOperatingRect());
	}
	else if (m_fScrubing)
	{
		if ((point.x == m_poMousePointerLocation.x) && (point.y == m_poMousePointerLocation.y))
		{
			int iFrame = ChangeDisplayPointToTimelineFramePosition(point);
			// �ł���Ύ���
			//DrawAnimation(iFrame - m_iTimelineCursorFramePosition);
			m_iTimelineCursorFramePosition = iFrame;
		}
		else
		{
			m_iTimelineCursorFramePosition += m_iOperatingFrameCount;
		}
	}

	m_rcBorderRect.SetRectEmpty();
	m_iOperatingFrameCount = 0;
	m_iOperatingClipFrameCount = 0;

	Invalidate(); // �ĕ`�悵�܂��B

	m_clMovingClipData = nullptr;
	m_clStaticClipData = nullptr;
	m_fMoving = FALSE;
	m_fSingleInTriming = FALSE;
	m_fSingleOutTriming = FALSE;
	m_fScrubing = FALSE;
	m_fDragShuttling = FALSE;


	CView::OnLButtonUp(nFlags, point);
}

// �h���b�O����
void CControlUnitAppProtoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	if (m_fLButtonClicking) 
	{
		CSize szMoveSize(point - m_poMousePointerLocation);
		if (m_fMoving)
		{
			m_iOperatingClipFrameCount = ChangeOperatingDistanceToTimelineFrames(szMoveSize, m_clMovingClipData->m_iTimelineInPoint);
			CalcClipRectDisplayPoint(m_rcBorderRect, m_clMovingClipData, m_iOperatingClipFrameCount);
			CheckMove(point);
			Invalidate();
		}
		else if (m_fSingleInTriming || m_fSingleOutTriming)
		{
			m_clMovingClipData->SetOperatingRect(static_cast<CRect>(m_clMovingClipData)); // �L�k���̃C���[�W���W
			if (m_fSingleInTriming)
			{					
				m_iOperatingClipFrameCount = ChangeOperatingDistanceToTimelineFrames(szMoveSize, m_clMovingClipData->m_iTimelineInPoint);
				CheckInTrim();
				CalcClipRectDisplayPoint(*(m_clMovingClipData->GetOperatingRect()), m_clMovingClipData, 0, m_iOperatingClipFrameCount);
			}
			else
			{
				m_iOperatingClipFrameCount = ChangeOperatingDistanceToTimelineFrames(szMoveSize,
					(m_clMovingClipData->m_iTimelineInPoint + m_clMovingClipData->GetDuration()));
				CheckOutTrim();
				CalcClipRectDisplayPoint(*(m_clMovingClipData->GetOperatingRect()), m_clMovingClipData, 0, 0, m_iOperatingClipFrameCount);
			}
			Invalidate();
		}
		else if (m_fScrubing)
		{
			szMoveSize.cx *= -1;
			m_iOperatingFrameCount = ChangeOperatingDistanceToTimelineFrames(szMoveSize, m_iTimelineCursorFramePosition);
			// �ŏ��͈̓`�F�b�N
			// TODO: �ő�͈̓`�F�b�N�́H
			if ((m_iTimelineCursorFramePosition + m_iOperatingFrameCount) < 0)
			{
				m_iOperatingFrameCount = -1 * m_iTimelineCursorFramePosition;
			}
			Invalidate();
		}
		else if (m_fDragShuttling)
		{
			// �}�E�X�ʒu����{�����x���擾
			m_fSuttleSpeed = SetShuttleSpeed(point, szMoveSize);
			Invalidate();
		}
	}

	CView::OnMouseMove(nFlags, point);
}


void CControlUnitAppProtoView::OnPaint()
{
	CPaintDC dcViewDc(this); // device context for painting
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����܂��B
	// �`�惁�b�Z�[�W�� CView::OnPaint() ���Ăяo���Ȃ��ł��������B

	// View�G���A�̕\�������擾
	CRect rcViewRect;
	GetClientRect(&rcViewRect);

	// View���̕\���ʒu�m�F
	SetPanelRect();

	//--------- ��������_�u���o�b�t�@�p�R�[�h
	// ���z�f�o�C�X�R���e�L�X�g���쐬
	CDC dcMemDc;
	dcMemDc.CreateCompatibleDC(&dcViewDc);
	CBitmap bmOffScreenBitmap;
	bmOffScreenBitmap.CreateCompatibleBitmap(&dcViewDc, rcViewRect.Width(), rcViewRect.Height());
	CBitmap* bmOldOffScreenBitmap = dcMemDc.SelectObject(&bmOffScreenBitmap);
	//---------- �����܂�

	//�w�i�`��
	CBrush brBaseBrush(TIMELINEBASECOLOR_BRUSH);
	dcMemDc.FillRect(&rcViewRect, &brBaseBrush);

	// �g�`��
	CPen brPenBrush(PS_SOLID, 1, LIGHTGRAYCOLOR_BRUSH);
	CPen* oldpen = dcMemDc.SelectObject(&brPenBrush);
	dcMemDc.Rectangle(m_rcPreviewPanelRect);
	dcMemDc.Rectangle(m_rcTimelineControlPanelRect);
	dcMemDc.Rectangle(m_rcTrackHeaderRect);
	dcMemDc.Rectangle(m_rcTimelineDataRect);
	dcMemDc.SelectObject(oldpen);

	// �R���g���[���p�l���`��
	DrawTimelineControlPanel(dcMemDc);

	// �V�[�N�o�[�`��
	DrawSeekBar(dcMemDc);

	// �Î~�N���b�v�`��
	CBrush brClipBrush(CLIPCOLOR_BRUSH);
	CalcClipRectDisplayPoint(static_cast<CRect&>(*m_clClipData1), m_clClipData1);
	dcMemDc.FillRect(static_cast<CRect*>(m_clClipData1), &brClipBrush);
	CalcClipRectDisplayPoint(static_cast<CRect&>(*m_clClipData2), m_clClipData2);
	dcMemDc.FillRect(static_cast<CRect*>(m_clClipData2), &brClipBrush);

	// ����C���[�W�`��
	if ((m_fSingleInTriming || m_fSingleOutTriming || m_fMoving) && (!(m_clMovingClipData->GetOperatingRect()->IsRectEmpty())))
	{
		DrawOperatingClip(&dcViewDc, rcViewRect, dcMemDc);
	}

	// �^�C�����C���J�[�\���^�V���g������⏕���`��
	DrawTimelineCursor(&dcViewDc, rcViewRect, dcMemDc);

	//--------- ��������_�u���o�b�t�@�p�R�[�h
	// �`��
	BitBlt(dcViewDc.GetSafeHdc(), 0, 0, rcViewRect.Width(), rcViewRect.Height(), dcMemDc.GetSafeHdc(), 0, 0, SRCCOPY);
	// ���z�f�o�C�X�R���e�L�X�g�r�b�g�}�b�v�̏������E�j��
	dcMemDc.SelectObject(bmOffScreenBitmap);
	bmOldOffScreenBitmap->DeleteObject();
	bmOffScreenBitmap.DeleteObject();
	dcMemDc.DeleteDC();
	// ---------- �����܂�
	brBaseBrush.DeleteObject();
	brPenBrush.DeleteObject();
	brClipBrush.DeleteObject();

}

// �^�C�����C���R���g���[���p�l���̕`����s��
void CControlUnitAppProtoView::DrawTimelineControlPanel(CDC& dcMemDc)
{
	// �w�i�h��Ԃ�
	CBrush brControlPanelBaseBrush(TIMELINECONTROLPANELBACKGROUNDCOLOR_BRUSH);
	dcMemDc.FillRect(m_rcTimelineControlPanelRect, &brControlPanelBaseBrush);
	brControlPanelBaseBrush.DeleteObject();

#ifdef PROTOTYPEMODE
	CString strText;
	int iOldBkMode;
	iOldBkMode = dcMemDc.SetBkMode(TRANSPARENT);
	COLORREF crOldTextColor = dcMemDc.SetTextColor(SEEKBARTIMECODETEXTCOLOR_BRUSH);
	strText.Format(_T("%d"), m_iFramePerBase);
	dcMemDc.TextOut(m_rcTimelineControlPanelRect.left + 5, m_rcTimelineControlPanelRect.bottom - 20, strText);
	dcMemDc.SetBkMode(iOldBkMode);
	dcMemDc.SetTextColor(crOldTextColor);
#endif
}

// �V�[�N�o�[�̕`����s��
void CControlUnitAppProtoView::DrawSeekBar(CDC& dcMemDc)
{
	// �w�i�h��Ԃ�
	CBrush brSeekBarBaseBrush(SEEKBARBACKGROUNDCOLOR_BRUSH);
	dcMemDc.FillRect(m_rcSeekBarRect, &brSeekBarBaseBrush);

	CPen brSeekBarBigScalePen(PS_SOLID, kSeekBarMiddleScaleThikness, SEEKBARBIGSCALECOLOR_BRUSH);
	CPen brSeekBarMiddleScalePen(PS_SOLID, kSeekBarMiddleScaleThikness, SEEKBARMIDDLESCALECOLOR_BRUSH);
	CPen brSeekBarSmallScalePen(PS_SOLID, kSeekBarSmallScaleThikness, SEEKBARSMALLSCALECOLOR_BRUSH);
	CPen brSeekBarBigScaleLinePen(PS_SOLID, kSeekBarMiddleScaleThikness, SEEKBARBIGSCALELINECOLOR_BRUSH);
	CPen brSeekBarMiddleScaleLinePen(PS_SOLID, kSeekBarMiddleScaleThikness, SEEKBARMIDDLESCALELINECOLOR_BRUSH);
	CPen brSeekBarSmallScaleLinePen(PS_SOLID, kSeekBarSmallScaleThikness, SEEKBARSMALLSCALELINECOLOR_BRUSH);
	CPen* oldpen = dcMemDc.SelectObject(&brSeekBarMiddleScalePen);

	POINT pScaleLine;
	pScaleLine.x = m_iTimelineCursorPoint;
	pScaleLine.y = m_rcSeekBarRect.top;
	int iDrawFrame = m_iTimelineCursorFramePosition + m_iOperatingFrameCount;

	// �J�[�\������E���̖ڐ���`��
	while (pScaleLine.x < m_rcSeekBarRect.right)
	{
		if (iDrawFrame == m_iTimelineCursorFramePosition)
		{
			//TODO: �f�o�b�O
			CString strText;
			strText.Format(_T("CURSOR SEEKBAR  %d"), m_iRightFrameNumber + pScaleLine.x);
			dcMemDc.TextOutW(5, 85, strText);
		}
		// ��ڐ���
		if ((iDrawFrame % (kSeekBarBigScaleInterval * m_iFramePerBase)) == 0)
		{
			if (iDrawFrame >= 0)
			{
				DrawBigScale(dcMemDc, iDrawFrame, brSeekBarBigScalePen, brSeekBarBigScaleLinePen, pScaleLine);
			}
		}
		// ���ڐ���
		else if ((iDrawFrame % m_iFramePerBase) == 0)
		{
			if (iDrawFrame >= 0)
			{
				DrawMiddleScale(dcMemDc, iDrawFrame, brSeekBarMiddleScalePen, brSeekBarMiddleScaleLinePen, pScaleLine);
			}
		}
		// ���ڐ���
		else if ((iDrawFrame % m_iFramePerScale) == 0)
		{
			if (iDrawFrame >= 0)
			{
				DrawSmallScale(dcMemDc, iDrawFrame, brSeekBarSmallScaleLinePen, brSeekBarSmallScaleLinePen, pScaleLine);
			}
		}
		if (m_fFramePerPoint < 1)
		{
			pScaleLine.x += m_fPointPerFrame;
		}
		else
		{
			if ((iDrawFrame % static_cast<int>(m_fFramePerPoint)) == 0)
			{
				++pScaleLine.x;
			}
		}
		++iDrawFrame;
	}
	// �J�[�\�����獶���̖ڐ���`��
	pScaleLine.x = m_iTimelineCursorPoint;
	pScaleLine.y = m_rcSeekBarRect.top;
	iDrawFrame = m_iTimelineCursorFramePosition + m_iOperatingFrameCount;
	while ((pScaleLine.x > m_rcSeekBarRect.left) && (iDrawFrame >= 0))
	{
		// ��ڐ���
		if ((iDrawFrame % (kSeekBarBigScaleInterval * m_iFramePerBase)) == 0)
		{
			DrawBigScale(dcMemDc, iDrawFrame, brSeekBarBigScalePen, brSeekBarBigScaleLinePen, pScaleLine);
		}
		// ���ڐ���
		else if ((iDrawFrame % m_iFramePerBase) == 0)
		{
			DrawMiddleScale(dcMemDc, iDrawFrame, brSeekBarMiddleScalePen, brSeekBarMiddleScaleLinePen, pScaleLine);
		}
		// ���ڐ���
		else if ((iDrawFrame % m_iFramePerScale) == 0)
		{
			DrawSmallScale(dcMemDc, iDrawFrame, brSeekBarSmallScaleLinePen, brSeekBarSmallScaleLinePen, pScaleLine);
		}
		if (m_fFramePerPoint < 1)
		{
			pScaleLine.x -= m_fPointPerFrame;
		}
		else
		{
			if ((iDrawFrame % static_cast<int>(m_fFramePerPoint)) == 0)
			{
				--pScaleLine.x;
			}
		}
		--iDrawFrame;
	}
	dcMemDc.SelectObject(oldpen);

#ifdef PROTOTYPEMODE
	CString strFrameNumber;
	strFrameNumber.Format(_T("%d"), m_iTimelineCursorFramePosition + m_iOperatingFrameCount);
	dcMemDc.TextOutW(5, 5, strFrameNumber);
	strFrameNumber.Format(_T("%d"), m_iLeftFrameNumber + m_iOperatingFrameCount);
	dcMemDc.TextOutW(5, 40, strFrameNumber);
	strFrameNumber.Format(_T("%d"), m_iRightFrameNumber + m_iOperatingFrameCount);
	dcMemDc.TextOutW(5, 65, strFrameNumber);
#endif

	brSeekBarBaseBrush.DeleteObject();
	brSeekBarBigScalePen.DeleteObject();
	brSeekBarMiddleScalePen.DeleteObject();
	brSeekBarSmallScalePen.DeleteObject();
	brSeekBarBigScaleLinePen.DeleteObject();
	brSeekBarMiddleScaleLinePen.DeleteObject();
	brSeekBarSmallScaleLinePen.DeleteObject();

}

// ��ڐ���`��
void CControlUnitAppProtoView::DrawBigScale(CDC& dcMemDc, const int iDrawFrame,  const CPen& brScalePen, const CPen& brLinePen, POINT& pScaleLine)
{
	CString strFrameNumber;
#ifdef PROTOTYPEMODE
	int iOldBkMode;
#endif

	// TODO: ���i�̓^�C���R�[�h��\��
	iOldBkMode = dcMemDc.SetBkMode(TRANSPARENT);
	COLORREF crOldTextColor = dcMemDc.SetTextColor(SEEKBARTIMECODETEXTCOLOR_BRUSH);
	strFrameNumber.Format(_T("%d"), iDrawFrame);
	dcMemDc.TextOut(pScaleLine.x + 2, m_rcSeekBarRect.top + 2, strFrameNumber);
	dcMemDc.SetBkMode(iOldBkMode);
	dcMemDc.SetTextColor(crOldTextColor);

	dcMemDc.SelectObject(brScalePen);
	pScaleLine.y = m_rcSeekBarRect.top + kSeekBarBigScaleMargin;
	dcMemDc.MoveTo(pScaleLine);
	pScaleLine.y = m_rcSeekBarRect.bottom;
	dcMemDc.LineTo(pScaleLine);
	dcMemDc.SelectObject(brLinePen);
	pScaleLine.y = m_rcTimelineDataRect.bottom;
	dcMemDc.LineTo(pScaleLine);

	return;
}

// ���ڐ���`��
void CControlUnitAppProtoView::DrawMiddleScale(CDC& dcMemDc, const int iDrawFrame, const CPen& brScalePen, const CPen& brLinePen, POINT& pScaleLine)
{
	CString strFrameNumber;
#ifdef PROTOTYPEMODE
	int iOldBkMode;
#endif

	// TODO: �f�o�b�O�p�\���Ȃ̂łƂ鎖
#ifdef PROTOTYPEMODE
	iOldBkMode = dcMemDc.SetBkMode(TRANSPARENT);
	COLORREF crOldTextColor = dcMemDc.SetTextColor(SEEKBARTIMECODETEXTCOLOR_BRUSH);
	strFrameNumber.Format(_T("%d"), (iDrawFrame % (kSeekBarBigScaleInterval * m_iSeekBarScaleCountPerBase)));
	dcMemDc.TextOut(pScaleLine.x + 2, m_rcSeekBarRect.top + 6, strFrameNumber);
	dcMemDc.SetBkMode(iOldBkMode);
	dcMemDc.SetTextColor(crOldTextColor);
#endif
	dcMemDc.SelectObject(brScalePen);
	pScaleLine.y = m_rcSeekBarRect.top + kSeekBarMiddleScaleMargin;
	dcMemDc.MoveTo(pScaleLine);
	pScaleLine.y = m_rcSeekBarRect.bottom;
	dcMemDc.LineTo(pScaleLine);
#ifdef PROTOTYPEMODE
	dcMemDc.SelectObject(brLinePen);
	pScaleLine.y = m_rcTimelineDataRect.bottom;
	dcMemDc.LineTo(pScaleLine);
#endif

	return;
}

// ���ڐ���`��
void CControlUnitAppProtoView::DrawSmallScale(CDC& dcMemDc, const int iDrawFrame, const CPen& brScalePen, const CPen& brLinePen, POINT& pScaleLine)
{
	CString strFrameNumber;

	dcMemDc.SelectObject(brScalePen);
	pScaleLine.y = m_rcSeekBarRect.top + kSeekBarSmallScaleMargin;
	dcMemDc.MoveTo(pScaleLine);
	pScaleLine.y = m_rcSeekBarRect.bottom;
	dcMemDc.LineTo(pScaleLine);
#ifdef PROTOTYPEMODE
	dcMemDc.SelectObject(brLinePen);
	pScaleLine.y = m_rcTimelineDataRect.bottom;
	dcMemDc.LineTo(pScaleLine);
#endif

	return;
}


// ���쒆�N���b�v�̕`����s��
BOOL CControlUnitAppProtoView::DrawOperatingClip(const CDC* dcViewDc, const CRect& rcViewRect, CDC& dcMemDc)
{
	if (dcViewDc == nullptr)
	{
		return FALSE;
	}

	//����C���[�W�p�f�o�C�X�R���e�L�X�g�쐬
	// ���z�f�o�C�X�R���e�L�X�g���쐬
	CDC dcMovingMemDc;
	dcMovingMemDc.CreateCompatibleDC(const_cast<CDC*>(dcViewDc));
	CBitmap bmMovingScreenBitmap;
	bmMovingScreenBitmap.CreateCompatibleBitmap(const_cast<CDC*>(dcViewDc), rcViewRect.Width(), rcViewRect.Height());
	CBitmap* bmOldMovingScreenBitmap = dcMovingMemDc.SelectObject(&bmMovingScreenBitmap);
	// ���߃u�����h�p�f�[�^
	BLENDFUNCTION blAlphaBlend;
	blAlphaBlend.BlendOp = AC_SRC_OVER;
	blAlphaBlend.BlendFlags = 0;
	blAlphaBlend.SourceConstantAlpha = kMovingClipAlpha;
	blAlphaBlend.AlphaFormat = 0;

	// ���̃N���b�v�̐F��ς���
	CBrush brMovingClipBrush(LIGHTGRAYCOLOR_BRUSH);
	CalcClipRectDisplayPoint(static_cast<CRect&>(*m_clMovingClipData), m_clMovingClipData);
	dcMemDc.FillRect(static_cast<CRect*>(m_clMovingClipData), &brMovingClipBrush);
	brMovingClipBrush.DeleteObject();

	CBrush brClipBrush(CLIPCOLOR_BRUSH);

	if (m_fSingleInTriming || m_fSingleOutTriming)
	{
		CRect rcMovingRect = m_clMovingClipData->GetOperatingRect();
		//CBrush brClipTrimBrush(ACCENTCOLOR_BRUSH);
		dcMovingMemDc.FillRect(rcMovingRect, &brClipBrush);
		//brClipTrimBrush.DeleteObject();
		dcMemDc.AlphaBlend(rcMovingRect.left, rcMovingRect.top, rcMovingRect.Width(), rcMovingRect.Height(),
			&dcMovingMemDc, rcMovingRect.left, rcMovingRect.top, rcMovingRect.Width(), rcMovingRect.Height(),
			blAlphaBlend);

#ifdef PROTOTYPEMODE
		//TODO: �f�o�b�O
		CString strText;
		int iPoint;
		int iDuration;
		if (m_fSingleInTriming)
		{
			iPoint = m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount;
		}
		else
		{
			iPoint = m_clMovingClipData->m_iTimelineInPoint;
		}
		strText.Format(_T("TrimingClipInPoint  %d"), iPoint);
		dcMemDc.TextOutW(300, 5, strText);
		strText.Format(_T("TrimingClipLeftPoint  %d"), rcMovingRect.left);
		dcMemDc.TextOutW(300, 25, strText);
		if (m_fSingleInTriming)
		{
			iPoint = m_clMovingClipData->m_iTimelineInPoint + m_clMovingClipData->GetDuration() - 1;
			iDuration = m_clMovingClipData->GetDuration() - m_iOperatingClipFrameCount;
		}
		else
		{
			iPoint = m_clMovingClipData->m_iTimelineInPoint + m_clMovingClipData->GetDuration() - 1 + m_iOperatingClipFrameCount;
			iDuration = m_clMovingClipData->GetDuration() + m_iOperatingClipFrameCount;
		}
		strText.Format(_T("TrimingClipOutPoint  %d"), iPoint);
		dcMemDc.TextOutW(300, 45, strText);
		strText.Format(_T("TrimingClipRightPoint  %d"), rcMovingRect.right);
		dcMemDc.TextOutW(300, 65, strText);
		strText.Format(_T("TrimingClipDuration  %d"), iDuration);
		dcMemDc.TextOutW(300, 85, strText);
#endif

	}
	else
	{
		// �h���b�v�ʒu�p
		CRect rcMovingRect = m_clMovingClipData->GetOperatingRect();
		//CBrush brClipMoveBrush(ACCENTCOLOR_BRUSH);
		dcMovingMemDc.FillRect(&rcMovingRect, &brClipBrush);
		//brClipMoveBrush.DeleteObject();
		dcMemDc.AlphaBlend(rcMovingRect.left, rcMovingRect.top, rcMovingRect.Width(), rcMovingRect.Height(),
			&dcMovingMemDc, rcMovingRect.left, rcMovingRect.top, rcMovingRect.Width(), rcMovingRect.Height(),
			blAlphaBlend);

#ifdef PROTOTYPEMODE
		//TODO: �f�o�b�O
		CString strText;
		strText.Format(_T("MovingClipInPoint  %d"), m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount);
		dcMemDc.TextOutW(300, 5, strText);
		strText.Format(_T("MovingClipLeftPoint  %d"), rcMovingRect.left);
		dcMemDc.TextOutW(300, 25, strText);
		strText.Format(_T("MovingClipRightPoint  %d"), rcMovingRect.right);
		dcMemDc.TextOutW(300, 45, strText);
		strText.Format(_T("BorderClipLeftPoint  %d"), m_rcBorderRect.left);
		dcMemDc.TextOutW(300, 65, strText);
		strText.Format(_T("BorderClipRightPoint  %d"), m_rcBorderRect.right);
		dcMemDc.TextOutW(300, 85, strText);
#endif

		// �}�E�X�ʒu�ǐ��p
		if (!(m_rcBorderRect.EqualRect(rcMovingRect)))
		{
			CBrush brClipOverlapBrush(CLIPOVERLAPPINGCOLOR_BRUSH);
			dcMovingMemDc.FillRect(&m_rcBorderRect, &brClipOverlapBrush);
			blAlphaBlend.SourceConstantAlpha = kMovingClipOverlappingAlpha;
			dcMemDc.AlphaBlend(m_rcBorderRect.left, m_rcBorderRect.top, m_rcBorderRect.Width(), m_rcBorderRect.Height(),
				&dcMovingMemDc, m_rcBorderRect.left, m_rcBorderRect.top, m_rcBorderRect.Width(), m_rcBorderRect.Height(),
				blAlphaBlend);
			strText.Format(_T("ClipBorderLeftPoint  %d"), m_rcBorderRect.left);
			dcMemDc.TextOutW(300, 45, strText);
		}
	}
	// ���z�f�o�C�X�R���e�L�X�g�r�b�g�}�b�v�̏������E�j��
	dcMovingMemDc.SelectObject(bmMovingScreenBitmap);
	bmOldMovingScreenBitmap->DeleteObject();
	bmMovingScreenBitmap.DeleteObject();
	dcMovingMemDc.DeleteDC();
	// ---------- �����܂�
	brClipBrush.DeleteObject();

	return TRUE;
}

// �^�C�����C���J�[�\���̕`����s��
BOOL CControlUnitAppProtoView::DrawTimelineCursor(const CDC* dcViewDc, const CRect& rcViewRect, CDC& dcMemDc)
{
	if (dcViewDc == nullptr)
	{
		return FALSE;
	}

	//���ߗp�f�o�C�X�R���e�L�X�g�쐬
	// ���z�f�o�C�X�R���e�L�X�g���쐬
	CDC dcMovingMemDc;
	dcMovingMemDc.CreateCompatibleDC(const_cast<CDC*>(dcViewDc));
	CBitmap bmMovingScreenBitmap;
	bmMovingScreenBitmap.CreateCompatibleBitmap(const_cast<CDC*>(dcViewDc), rcViewRect.Width(), rcViewRect.Height());
	CBitmap* bmOldMovingScreenBitmap = dcMovingMemDc.SelectObject(&bmMovingScreenBitmap);
	// ���߃u�����h�p�f�[�^
	BLENDFUNCTION blAlphaBlend;
	blAlphaBlend.BlendOp = AC_SRC_OVER;
	blAlphaBlend.BlendFlags = 0;
	blAlphaBlend.SourceConstantAlpha = kTimelineCursorAlpha;
	blAlphaBlend.AlphaFormat = 0;

	// �`����W���v�Z
	CRect rcTimelineCursorRect;
	rcTimelineCursorRect.left = m_iTimelineCursorPoint;
	rcTimelineCursorRect.right = rcTimelineCursorRect.left + kTimelineCursorThickness - 1;
	rcTimelineCursorRect.top = m_rcSeekBarRect.top;
	rcTimelineCursorRect.bottom = m_rcTimelineDataRect.bottom;

	// ���C����`��
	CBrush brTimelineCursorBrush(TIMELINECURSORCOLOR_BRUSH);
	dcMovingMemDc.FillRect(rcTimelineCursorRect, &brTimelineCursorBrush);
	brTimelineCursorBrush.DeleteObject();
	dcMemDc.AlphaBlend(rcTimelineCursorRect.left, rcTimelineCursorRect.top, rcTimelineCursorRect.Width(), rcTimelineCursorRect.Height(),
		&dcMovingMemDc, rcTimelineCursorRect.left, rcTimelineCursorRect.top, rcTimelineCursorRect.Width(), rcTimelineCursorRect.Height(),
		blAlphaBlend);

	//TODO: �f�o�b�O
	CString strText;
	strText.Format(_T("CURSOR LINE  %d"), m_iRightFrameNumber + rcTimelineCursorRect.left);
	dcMemDc.TextOutW(5, 105, strText);

	if (m_fDragShuttling)
	{
		blAlphaBlend.SourceConstantAlpha = kTimelineCursorDragGuideLineAlpha;
		
		//TODO: �ʒu�͌������K�v
		CString strText;
		int iOldBkMode = dcMemDc.SetBkMode(TRANSPARENT);
		COLORREF crOldTextColor = dcMemDc.SetTextColor(SEEKBARTIMECODETEXTCOLOR_BRUSH);
		strText.Format(_T("�~  %d"), m_fSuttleSpeed);
		dcMemDc.TextOutW(90, m_rcTimelineControlPanelRect.bottom - 20, strText);
		dcMemDc.SetBkMode(iOldBkMode);
		dcMemDc.SetTextColor(crOldTextColor);

		//�⏕���̕`��
		CRect rcShuttleLineRect;
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragOneSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragTowSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragFourSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragEightSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragSixteenSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragThirtyTwoSpeed);
		DrawShuttleGuideLine(dcMemDc, dcMovingMemDc, blAlphaBlend, rcShuttleLineRect, kTimelineCursorDragSixtyFourSpeed);

	}

	// ���z�f�o�C�X�R���e�L�X�g�r�b�g�}�b�v�̏������E�j��
	dcMovingMemDc.SelectObject(bmMovingScreenBitmap);
	bmOldMovingScreenBitmap->DeleteObject();
	bmMovingScreenBitmap.DeleteObject();
	dcMovingMemDc.DeleteDC();
	// ---------- �����܂�
	brTimelineCursorBrush.DeleteObject();

	return TRUE;
}

// �V���g�����쎞�̃K�C�h���C����\������
void CControlUnitAppProtoView::DrawShuttleGuideLine(CDC& dcMemDc, CDC& dcMovingMemDc, BLENDFUNCTION& blAlphaBlend, CRect& rcLineRect, float fGuideAreaWidth)
{
	int iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * fGuideAreaWidth));

	rcLineRect.left = m_iTimelineCursorPoint + iGuideAreaWidth - kTimelineCursorDragGuideLineThickness;
	rcLineRect.right = rcLineRect.left + kTimelineCursorDragGuideLineThickness;
	rcLineRect.top = m_rcTimelineDataRect.top;
	rcLineRect.bottom = m_rcTimelineDataRect.bottom;

	// ���C����`��
	CBrush brShuttleGuidLineBrush(TIMELINECURSORDRAGGUIDELINECOLOR_BRUSH);
	dcMovingMemDc.FillRect(rcLineRect, &brShuttleGuidLineBrush);
	dcMemDc.AlphaBlend(rcLineRect.left, rcLineRect.top, rcLineRect.Width(), rcLineRect.Height(),
		&dcMovingMemDc, rcLineRect.left, rcLineRect.top, rcLineRect.Width(), rcLineRect.Height(),
		blAlphaBlend);

	rcLineRect.left = m_iTimelineCursorPoint - iGuideAreaWidth;
	rcLineRect.right = rcLineRect.left + kTimelineCursorDragGuideLineThickness;

	// ���C����`��
	dcMovingMemDc.FillRect(rcLineRect, &brShuttleGuidLineBrush);
	brShuttleGuidLineBrush.DeleteObject();
	dcMemDc.AlphaBlend(rcLineRect.left, rcLineRect.top, rcLineRect.Width(), rcLineRect.Height(),
		&dcMovingMemDc, rcLineRect.left, rcLineRect.top, rcLineRect.Width(), rcLineRect.Height(),
		blAlphaBlend);
}


void CControlUnitAppProtoView::DrawAnimation(const int iFrame)
{
	if (m_iTimelineCursorFramePosition > iFrame)
	{
		for (m_iTimelineCursorFramePosition; m_iTimelineCursorFramePosition >= iFrame; --m_iTimelineCursorFramePosition)
		{
			Invalidate();;
		}
	}
	else
	{
		for (m_iTimelineCursorFramePosition; m_iTimelineCursorFramePosition <= iFrame; ++m_iTimelineCursorFramePosition)
		{
			Invalidate();
			Sleep(100);
		}
	}
}


BOOL CControlUnitAppProtoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}

// View�̃T�C�Y����e�\���p�l���̍��W���v�Z���Đݒ肷��B
void CControlUnitAppProtoView::SetPanelRect(void)
{
	CRect rcViewRect;
	GetClientRect(&rcViewRect);

	float fViewHeight = static_cast<float>(rcViewRect.Height());
	long lViewHeight = static_cast<long>(floor((fViewHeight - static_cast<float>(m_rcSeekBarRect.Height())) / 2));

	// TODO: ������̓����o�ϐ��ɁI
	int iTimelineEditHeaderDefaltHeight = kTimelineEditHeaderDefaltHeight;
	int iTimelineControlPanelDefaultWidth = kTimelineControlPanelDefaultWidth;


	m_rcPreviewPanelRect.left = rcViewRect.left;
	m_rcPreviewPanelRect.top = rcViewRect.top;
	m_rcPreviewPanelRect.right = rcViewRect.right;
	m_rcPreviewPanelRect.bottom = rcViewRect.top + lViewHeight;

	m_rcTimelineEditPanelRect.left = rcViewRect.left;
	m_rcTimelineEditPanelRect.top = m_rcPreviewPanelRect.bottom + kSplitterHeight;
	m_rcTimelineEditPanelRect.right = rcViewRect.right;
	m_rcTimelineEditPanelRect.bottom = rcViewRect.bottom;

	// �^�C�����C���w�b�_�[�G���A�̔z�u
	m_rcTimelineEditHeaderRect.CopyRect(m_rcTimelineEditPanelRect);
	m_rcTimelineEditHeaderRect.bottom = m_rcTimelineEditHeaderRect.top + iTimelineEditHeaderDefaltHeight;

	// �^�C�����C���R���g���[���G���A�̔z�u
	m_rcTimelineControlPanelRect.CopyRect(m_rcTimelineEditHeaderRect);
	m_rcTimelineControlPanelRect.right = m_rcTimelineControlPanelRect.left + iTimelineControlPanelDefaultWidth;

	// �V�[�N�o�[�G���A�̔z�u
	m_rcSeekBarRect.CopyRect(m_rcTimelineEditHeaderRect);
	m_rcSeekBarRect.left = m_rcTimelineControlPanelRect.right + kSplitterWidth;

	// �g���b�N�w�b�_�̔z�u
	m_rcTrackHeaderRect.CopyRect(m_rcTimelineEditPanelRect);
	m_rcTrackHeaderRect.top = m_rcTimelineEditHeaderRect.bottom + kSplitterHeight;
	m_rcTrackHeaderRect.right = m_rcTimelineControlPanelRect.right;

	// �^�C�����C���f�[�^�G���A�̔z�u
	m_rcTimelineDataRect.CopyRect(m_rcTimelineEditPanelRect);
	m_rcTimelineDataRect.left = m_rcSeekBarRect.left;
	m_rcTimelineDataRect.top = m_rcTrackHeaderRect.top;

	// �^�C�����C���J�[�\���q�b�g�̈�̔z�u
	m_rcTimelineCursorHitArea.CopyRect(m_rcTimelineEditPanelRect);
	m_rcTimelineCursorHitArea.top = m_rcSeekBarRect.top;
	m_rcTimelineCursorHitArea.left = m_iTimelineCursorPoint - kTimelineCursorDragArea;
	m_rcTimelineCursorHitArea.right = m_iTimelineCursorPoint + kTimelineCursorDragArea;

	// �\���\�t���[���͈͂̌v�Z
	int iDisplayFrameCount = static_cast<int>(floor(m_rcSeekBarRect.Width() / m_fPointPerFrame));
	m_iTimelineCursorPoint = static_cast<int>(floor(m_rcSeekBarRect.Width() / 2)) + m_rcSeekBarRect.left;
	m_iLeftFrameNumber = m_iTimelineCursorFramePosition - static_cast<int>(floor((iDisplayFrameCount / 2)));
	m_iRightFrameNumber = m_iTimelineCursorFramePosition + static_cast<int>(ceil((iDisplayFrameCount / 2))) + 1;

	return;
}

// �^�C�����C���f�[�^�\���{���̕ύX
BOOL CControlUnitAppProtoView::ChangeDisplayScale(void)
{
	int kDisplayScaleArray[13] = { 1, 2, 3, 6, 10, 30, 60, 300, 600, 1800, 3600, 18000, 36000 };
	int iArrayCount = sizeof kDisplayScaleArray / sizeof kDisplayScaleArray[0];

	if (m_iSelectedDisplayScaleNumber < 0)
	{
		m_iSelectedDisplayScaleNumber = 0;
		return FALSE;
	}
	else if (m_iSelectedDisplayScaleNumber > iArrayCount - 1)
	{
		m_iSelectedDisplayScaleNumber = iArrayCount - 1;
		return FALSE;
	}

	m_iFramePerBase = kDisplayScaleArray[m_iSelectedDisplayScaleNumber];

	m_fPointPerFrame = static_cast<float>(kSeekBarScaleBaseWidth) / static_cast<float>(m_iFramePerBase);

	if (m_iFramePerBase < kSeekBarScaleMaxCountPerBase)
	{
		m_iSeekBarScaleCountPerBase = m_iFramePerBase;
	}
	else
	{
		m_iSeekBarScaleCountPerBase = kSeekBarScaleMaxCountPerBase;
	}

	m_iSmallScaleLength = kSeekBarScaleBaseWidth / m_iSeekBarScaleCountPerBase;

	if (m_fPointPerFrame < 1)
	{
		m_iPointPerOperation = 1;
	}
	else
	{
		m_iPointPerOperation = static_cast<int>(floor(m_fPointPerFrame));
		if ((m_fPointPerFrame - m_iPointPerOperation) != 0)
		{
			return FALSE;
		}
	}

	m_fFramePerPoint = static_cast<float>(m_iFramePerBase) / static_cast<float>(kSeekBarScaleBaseWidth);

	float fFramePerScale = static_cast<float>(m_iFramePerBase) / static_cast<float>(m_iSeekBarScaleCountPerBase);
	if ((fFramePerScale - static_cast<int>(floor(fFramePerScale))) == 0)
	{
		m_iFramePerScale = m_iFramePerBase / m_iSeekBarScaleCountPerBase;
	}
	else
	{
		m_iFramePerScale = static_cast<int>(floor(fFramePerScale));
		return FALSE;
	}
	return TRUE;
}




int CControlUnitAppProtoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: �����ɓ���ȍ쐬�R�[�h��ǉ����Ă��������B

	return 0;
}


// �N���b�N�ӏ��̔���
BOOL CControlUnitAppProtoView::IsPointInAnyClipRect(const CPoint& point)
{
	m_fMoving = FALSE;
	if (IsPointInClipRect(point, static_cast<CRect&>(*m_clClipData1)))
	{
		CalcClipRectDisplayPoint(static_cast<CRect>(m_clClipData1), m_clClipData1);
		m_clMovingClipData = m_clClipData1;
		m_clStaticClipData = m_clClipData2;
	}
	// Clip2Hit����
	else if (IsPointInClipRect(point, static_cast<CRect&>(*m_clClipData2)))
	{
		CalcClipRectDisplayPoint(static_cast<CRect>(m_clClipData2), m_clClipData2);
		m_clMovingClipData = m_clClipData2;
		m_clStaticClipData = m_clClipData1;
	}
	return (m_fMoving || m_fSingleInTriming || m_fSingleOutTriming);
}

BOOL CControlUnitAppProtoView::IsPointInClipRect(const CPoint& point, const CRect& rcClipRect)
{
	CRect rcHitTestRect;
	rcHitTestRect.CopyRect(rcClipRect);
	// �N���b�v�����K��l���Z���ꍇ�͋K��l���Ŕ��肷��
	if (rcClipRect.Width() < kClipHitCheckMinWidth)
	{
		int iAdditionalLength = static_cast<int>(floor((kClipHitCheckMinWidth - rcHitTestRect.Width()) / 2));
		rcHitTestRect.left -= iAdditionalLength;
		rcHitTestRect.right += iAdditionalLength;
	}
	// ���͂�ClipRect���Ƀ|�C���^�����݂��邩�H
	if (rcHitTestRect.PtInRect(point))
	{
		// Trim����ŘR�ꂽ��Move
		m_fMoving = !(IsPointInTrimRange(point, &rcClipRect));
	}
	return (m_fMoving || m_fSingleInTriming || m_fSingleOutTriming);
}

// �N���b�N�ӏ����N���b�v���̃g��������G���A�����𔻒�
BOOL CControlUnitAppProtoView::IsPointInTrimRange(const CPoint& point, const CRect& rcClipRect)
{

	m_fSingleInTriming = FALSE;
	m_fSingleOutTriming = FALSE;

	CRect rcTrimRect;

	// In������
	rcTrimRect.CopyRect(rcClipRect);
	// �N���b�v�����K��l�����̏ꍇ��Trim���߂���
	if (rcTrimRect.Width() < kClipHitCheckMinWidth)
	{
		//TODO: In���f�����Ȃ��ꍇ�iClipIn�_=0�jOutTrim�ɂӂ�
		m_fSingleInTriming = TRUE;
	}
	else
	{
		rcTrimRect.right = rcTrimRect.left + static_cast<long>(floor(rcTrimRect.Width() * kTrimAreaRate));
		if (rcTrimRect.Width() < kTrimHitCheckMinWidth)
		{
			rcTrimRect.right = rcTrimRect.left + kTrimHitCheckMinWidth;
		}		
		else if (rcTrimRect.Width() > kTrimHitCheckMaxWidth)
		{
			rcTrimRect.right = rcTrimRect.left + kTrimHitCheckMaxWidth;
		}
		m_fSingleInTriming = rcTrimRect.PtInRect(point);
	}

	if (!(m_fSingleInTriming || m_fSingleOutTriming))
	{
		// Out������
		rcTrimRect.CopyRect(rcClipRect);
		rcTrimRect.left = rcTrimRect.right - static_cast<long>(floor(rcTrimRect.Width() * kTrimAreaRate));
		if (rcTrimRect.Width() < kTrimHitCheckMinWidth)
		{
			rcTrimRect.left = rcTrimRect.right - kTrimHitCheckMinWidth;
		}
		else if (rcTrimRect.Width() > kTrimHitCheckMaxWidth)
		{
			rcTrimRect.left = rcTrimRect.right - kTrimHitCheckMaxWidth;
		}
		m_fSingleOutTriming = rcTrimRect.PtInRect(point);
	}

	return (m_fSingleInTriming || m_fSingleOutTriming);
}

// ���삪In���g�����\�Ȕ͈͓����𔻒肵�Ĉʒu�𒲐�����
BOOL CControlUnitAppProtoView::CheckInTrim(void)
{
	int iDuration = m_clMovingClipData->GetDuration();
	// �͈̓`�F�b�N
	if (iDuration - m_iOperatingClipFrameCount < 1)
	{
		m_iOperatingClipFrameCount = iDuration - 1;
		return FALSE;
	}

	// �d�Ȃ�`�F�b�N
	// TODO: In�_�̏ꏊ�ɃN���b�v�����邩���T�[�`����B
	int iOutPoint = m_clStaticClipData->m_iTimelineInPoint + m_clStaticClipData->GetDuration() - 1;
	if ((m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount <= iOutPoint) && (m_clMovingClipData->m_iTimelineInPoint >= m_clStaticClipData->m_iTimelineInPoint))
	{
		m_iOperatingClipFrameCount = iOutPoint - m_clMovingClipData->m_iTimelineInPoint + 1;
		return FALSE;
	}

	// �͈̓`�F�b�N�i�d�Ȃ�`�F�b�N����ɂ��Ȃ���0�𒴂��ăh���b�O���ꂽ�ꍇ��0�ɐݒ肳��Ă��܂��j
	if (m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount < 0)
	{
		m_iOperatingClipFrameCount = m_clMovingClipData->m_iTimelineInPoint * -1;
		return FALSE;
	}

	return TRUE;
}

// ���삪Out���g�����\�Ȕ͈͓����𔻒肵�Ĉʒu�𒲐�����
BOOL CControlUnitAppProtoView::CheckOutTrim(void)
{
	// �͈̓`�F�b�N
	int iDuration = m_clMovingClipData->GetDuration();
	// �͈̓`�F�b�N
	if (iDuration + m_iOperatingClipFrameCount < 1)
	{
		m_iOperatingClipFrameCount = (iDuration * -1) + 1;
		return FALSE;
	}

	// �d�Ȃ�`�F�b�N
	// TODO: Out�_�̏ꏊ�ɃN���b�v�����邩���T�[�`����B
	int iOutPoint = m_clMovingClipData->m_iTimelineInPoint + iDuration - 1 + m_iOperatingClipFrameCount;
	if ((iOutPoint >= m_clStaticClipData->m_iTimelineInPoint) && (m_clMovingClipData->m_iTimelineInPoint <= m_clStaticClipData->m_iTimelineInPoint))
	{
		m_iOperatingClipFrameCount = m_clStaticClipData->m_iTimelineInPoint - (m_clMovingClipData->m_iTimelineInPoint + iDuration);
		return FALSE;
	}

	return TRUE;
}

// ���삪Move�\�Ȕ͈͓����𔻒肵�Ĉʒu�𒲐�����
BOOL CControlUnitAppProtoView::CheckMove(CPoint& point)
{
	// �͈̓`�F�b�N
	if (m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount < 0)
	{
		m_iOperatingClipFrameCount = m_clMovingClipData->m_iTimelineInPoint * -1;
		return FALSE;
	}

	// �d�Ȃ�`�F�b�N
	// TODO: �d�Ȃ�����̍Ĕ��肪�K�v�i�ċA�����ɂ��邩�j
	CRect rcStaticClip = m_clStaticClipData->GetDisplayRect();
	int iMovingClipInFrame = m_clMovingClipData->m_iTimelineInPoint + m_iOperatingClipFrameCount;
	int iMovingClipOutFrame = m_clMovingClipData->m_iTimelineInPoint + m_clMovingClipData->GetDuration() - 1 + m_iOperatingClipFrameCount;
	int iStaticClipInFrame = m_clStaticClipData->m_iTimelineInPoint;
	int iStaticClipOutFrame = m_clStaticClipData->m_iTimelineInPoint + m_clStaticClipData->GetDuration()  - 1;
	if (((iStaticClipInFrame <= iMovingClipInFrame) && (iMovingClipInFrame <= iStaticClipOutFrame)) ||
		((iStaticClipInFrame <= iMovingClipOutFrame) && (iMovingClipOutFrame <= iStaticClipOutFrame)) ||
		((iMovingClipInFrame <= iStaticClipInFrame) && (iStaticClipInFrame <= iMovingClipOutFrame)) ||
		((iMovingClipInFrame <= iStaticClipOutFrame) && (iStaticClipOutFrame <= iMovingClipOutFrame)))
	{
		int iStaticClipCenterFrame = iStaticClipInFrame + static_cast<int>(floor(m_clStaticClipData->GetDuration() / 2));
		int iDropInPoint = 0;
		if (iMovingClipInFrame <= iStaticClipCenterFrame)
		{
			iDropInPoint = iStaticClipInFrame - m_clMovingClipData->GetDuration();
		}
		else
		{
			iDropInPoint = iStaticClipOutFrame + 1;
		}
		m_iOperatingClipFrameCount = iDropInPoint - m_clMovingClipData->m_iTimelineInPoint;
		CalcClipRect(*(m_clMovingClipData->GetOperatingRect()), iDropInPoint, m_clMovingClipData->GetDuration());
		return FALSE;

	}
	
	CalcClipRectDisplayPoint(*(m_clMovingClipData->GetOperatingRect()), m_clMovingClipData, m_iOperatingClipFrameCount);
	return TRUE;
}

// �N���b�N�ʒu���V�[�N�o�[�����𔻒肷��
BOOL CControlUnitAppProtoView::IsPointInSeekBar(const CPoint& point)
{
	if (!(m_rcSeekBarRect.PtInRect(point)))
	{
		return FALSE;
	}
	return TRUE;
}

// �N���b�v�ʒu�v�Z
BOOL CControlUnitAppProtoView::CalcClipRectDisplayPoint(CRect& rcClipRect, const ClipDataTest* clClipData, const int& iMoveFrames /* = 0 */, 
	const int& iIntrimFrames /* = 0 */, const int& iOuttrimFrames/* = 0 */)
{
	
	if (CalcClipRect(rcClipRect, const_cast<ClipDataTest*>(clClipData)->m_iTimelineInPoint, const_cast<ClipDataTest*>(clClipData)->GetDuration(), 
		iMoveFrames, iIntrimFrames, iOuttrimFrames))
	{
		if (rcClipRect.left < m_rcTimelineDataRect.left)
		{
			rcClipRect.left = m_rcTimelineDataRect.left;
		}
		if (rcClipRect.right > m_rcTimelineDataRect.right)
		{
			rcClipRect.right = m_rcTimelineDataRect.right;
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

// �N���b�v�ʒu�v�Z�i�͂ݏo���␳�Ȃ��j
BOOL CControlUnitAppProtoView::CalcClipRect(CRect& rcClipRect, const int& iInPoint, const int& iDuration, const int& iMoveFrames /* = 0 */,
	const int& iIntrimFrames /* = 0 */, const int& iOuttrimFrames/* = 0 */)
{
	rcClipRect.top = m_rcTimelineDataRect.top;
	rcClipRect.bottom = rcClipRect.top + kTrackDefaultHeight;
	int iLeftScrubingFrameCount = m_iLeftFrameNumber + m_iOperatingFrameCount;
	int iRightScrubingFrameCount = m_iRightFrameNumber + m_iOperatingFrameCount;

	if (iInPoint + iMoveFrames + iIntrimFrames > iRightScrubingFrameCount)
	{
		rcClipRect.SetRectEmpty();
		return FALSE;
	}
	if ((iInPoint + iDuration + iMoveFrames + iOuttrimFrames) < iLeftScrubingFrameCount)
	{
		rcClipRect.SetRectEmpty();
		return FALSE;
	}
	int iDisplayInPoint = iInPoint + iMoveFrames + iIntrimFrames;
	int iDisplayOutPoint = iInPoint + iDuration + iMoveFrames + iOuttrimFrames;

	rcClipRect.left = ChangeTimelineFramePositionToDisplayPoint(iDisplayInPoint);
	rcClipRect.right = ChangeTimelineFramePositionToDisplayPoint(iDisplayOutPoint);

	return TRUE;
}
// �t���[���ʒu����ʏ�̍��W�ɕϊ�����
int CControlUnitAppProtoView::ChangeTimelineFramePositionToDisplayPoint(const int iFrame)
{
	int iXPoint;
	int iFrameCountFromTimelineCursor = iFrame - m_iTimelineCursorFramePosition - m_iOperatingFrameCount;

	// �P�|�C���g������̃t���[�������P�����̏ꍇ�i�P�t���[���������|�C���g�Ɍׂ�j
	if (m_fFramePerPoint < 1)
	{
		// �^�C�����C���J�[�\������̑��΍��W�����߂�
		iXPoint = iFrameCountFromTimelineCursor * m_fPointPerFrame;
	}
	else
	{
		// �^�C�����C���J�[�\������̑��΍��W�����߂�
		iXPoint = static_cast<int>(ceil(iFrameCountFromTimelineCursor / m_fFramePerPoint));
	}
	return (iXPoint + m_iTimelineCursorPoint);
}

// �N���b�N�ʒu���t���[���ʒu�ɕϊ�����
int CControlUnitAppProtoView::ChangeDisplayPointToTimelineFramePosition(const CPoint& point)
{
	int iFrame;
	int iHorizontalLengthFromTimelineCursor = point.x - m_iTimelineCursorPoint;

	// �P�t���[��������̃|�C���g�����P�����̏ꍇ
	if (m_fPointPerFrame < 1)
	{
		// �^�C�����C���J�[�\������̃t���[���������߂�
		iFrame = iHorizontalLengthFromTimelineCursor * m_fFramePerPoint + m_iTimelineCursorFramePosition;
	}
	else
	{
		// �^�C�����C���J�[�\������̑��΍��W�����߂�
		iFrame = static_cast<int>(ceil(iHorizontalLengthFromTimelineCursor / m_fPointPerFrame)) + m_iTimelineCursorFramePosition;
	}
	if (iFrame < 0)
	{
		return 0;
	}
	else
	{
		return iFrame;
	}
}

// ����ʂ𑀍�t���[�����ɕϊ�����
int CControlUnitAppProtoView::ChangeOperatingDistanceToTimelineFrames(const CSize& szMoveSize, const int iStratFrame /* = 0 */)
{

	int iFrames = 0;
	if (szMoveSize.cx == 0)
	{
		return iFrames;
	}

	// �P�|�C���g������̃t���[�������P�����̏ꍇ�i�P�t���[���������|�C���g�Ɍׂ�j
	if (m_fFramePerPoint < 1)
	{
		// �ړ��t���[�����͎��ۂ̈ړ����~�P�|�C���g������̃t���[�����i�K�v�ȕ��𓮂����Ȃ��ƃt���[���͓����Ȃ��j
		iFrames = static_cast<int>(floor(szMoveSize.cx * m_fFramePerPoint));
	}
	else
	{
		// �\���ɐ؂�̗ǂ��t���[���ʒu�łȂ��ꍇ�͒�������
		int iSurPlus = iStratFrame % static_cast<int>(m_fFramePerPoint);
		if (iSurPlus == 0)
		{
			// �ړ��t���[�����͎��ۂ̈ړ����~�P�|�C���g������̃t���[�����i�P�|�C���g�ŕ����t���[�������j
			iFrames = szMoveSize.cx * m_fFramePerPoint;
		}
		else
		{
			// �i�ړ��t���[�����͎��ۂ̈ړ����|�P�j�~�P�|�C���g������̃t���[�����i�ŏ��̂P�|�C���g�͒[�������Ɏg���j
			if(szMoveSize.cx < 0)
			{
				iFrames = ((szMoveSize.cx + 1) * m_fFramePerPoint) - iSurPlus;
			} 
			else 
			{
				iFrames = ((szMoveSize.cx - 1) * m_fFramePerPoint) + (static_cast<int>(m_fFramePerPoint) - iSurPlus);
			}
		}
	}
	return iFrames;
}


// �V���g�����쒆�̑��x����
float CControlUnitAppProtoView::SetShuttleSpeed(const CPoint& point, CSize& szMoveSize)
{
	if (point.x > (m_iTimelineCursorPoint + kTimelineCursorDragArea))
	{
		return SetShuttleSpeedByMoveLength(szMoveSize.cx);
	}
	else if (point.x < (m_iTimelineCursorPoint - kTimelineCursorDragArea))
	{
		int iMoveLength = szMoveSize.cx * -1;
		return SetShuttleSpeedByMoveLength(iMoveLength) * -1;
	}
	return 0.0;
}

// �V���g�����쒆�̑��x����i�}�E�X�ړ���������{����ԋp�j
float CControlUnitAppProtoView::SetShuttleSpeedByMoveLength(int iMoveLength)
{
	// TODO: �����������i�K�ɂ��ׂ����H
	// TODO: �z��Ȃ�ɕύX���Č����悭�����������I
	int iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragOneSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 1.0;
	}
	iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragTowSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 2.0;
	}
	iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragFourSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 4.0;
	}
	iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragEightSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 8.0;
	}
	iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragSixteenSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 16.0;
	}
	iGuideAreaWidth = static_cast<int>(floor(m_rcTimelineDataRect.Width() * kTimelineCursorDragThirtyTwoSpeed));
	if (iMoveLength <= iGuideAreaWidth)
	{
		return 32.0;
	}
	return 64.0;
}



// ���_�u���N���b�N
void CControlUnitAppProtoView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B


	CView::OnLButtonDblClk(nFlags, point);
}

// �E�_�u���N���b�N
void CControlUnitAppProtoView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	CView::OnRButtonDblClk(nFlags, point);
}
