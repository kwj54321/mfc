
// MFCApplication1View.cpp: CMFCApplication1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CScrollView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_DOT, &CMFCApplication1View::OnDrawDot)
	ON_COMMAND(ID_DRAW_LINE, &CMFCApplication1View::OnDrawLine)
	ON_COMMAND(ID_DRAW_RECT, &CMFCApplication1View::OnDrawRect)
	ON_COMMAND(ID_DRAW_CIRCLE, &CMFCApplication1View::OnDrawCircle)
	ON_COMMAND(ID_ERASER, &CMFCApplication1View::OnEraser)
	ON_COMMAND(ID_COLOR_FOREGROUND, &CMFCApplication1View::OnColorForeground)
	ON_UPDATE_COMMAND_UI(ID_DRAW_DOT, &CMFCApplication1View::OnUpdateDrawDot)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CMFCApplication1View::OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, &CMFCApplication1View::OnUpdateDrawRect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CMFCApplication1View::OnUpdateDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_ERASER, &CMFCApplication1View::OnUpdateEraser)
END_MESSAGE_MAP()

// CMFCApplication1View 생성/소멸

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_colorFore = RGB(0, 0, 0);
}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCApplication1View 그리기

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CDC MemDC;
	CBitmap* pOldBitmap;
	BITMAP bit;

	m_cbitmap.GetBitmap(&bit);
	MemDC.CreateCompatibleDC(pDC);
	pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);

	pDC->BitBlt(0, 0, bit.bmWidth, bit.bmHeight, &MemDC, 0, 0, SRCCOPY);
	
	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
}

void CMFCApplication1View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 1920;
	sizeTotal.cy = 1080;
	SetScrollSizes(MM_TEXT, sizeTotal);

	if (m_cbitmap.m_hObject) m_cbitmap.DeleteObject();
	
	CDC* pDC = GetDC();
	m_cbitmap.CreateCompatibleBitmap(pDC, sizeTotal.cx, sizeTotal.cy);

	CDC MemDC;
	CBitmap* pOldBitmap;
	BITMAP bit;

	m_cbitmap.GetBitmap(&bit);
	MemDC.CreateCompatibleDC(pDC);
	pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);
	MemDC.PatBlt(0, 0, bit.bmWidth, bit.bmHeight, WHITENESS);

	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
	ReleaseDC(pDC);

	m_nDraw = 1;
	m_bClick = FALSE;
	m_ptClick.SetPoint(0, 0);
	
}


// CMFCApplication1View 인쇄

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCApplication1View 진단

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 메시지 처리기


void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_nDraw == 1)
	{
		CDC MemDC;
		CBitmap* pOldBitmap;
		BITMAP bit;

		CDC* pDC = GetDC();

		m_cbitmap.GetBitmap(&bit);
		MemDC.CreateCompatibleDC(pDC);
		pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);


		int x = GetScrollPos(SB_HORZ);
		int y = GetScrollPos(SB_VERT);

		CPoint ptNew(point.x + x, point.y + y);

		MemDC.SetPixel(ptNew, m_colorFore);

		MemDC.SelectObject(pOldBitmap);
		MemDC.DeleteDC();

		Invalidate(FALSE);
		ReleaseDC(pDC);
	}
	else if (m_nDraw == 2)
	{
		int x = GetScrollPos(SB_HORZ);
		int y = GetScrollPos(SB_VERT);

		m_bClick = TRUE;
		m_ptClick.SetPoint(point.x + x, point.y + y);
		m_ptMove.SetPoint(point.x + x, point.y + y);
	}
	else if (m_nDraw == 3)
	{
		int x = GetScrollPos(SB_HORZ);
		int y = GetScrollPos(SB_VERT);

		m_bClick = TRUE;
		m_ptClick.SetPoint(point.x + x, point.y + y);
		m_ptMove.SetPoint(point.x + x, point.y + y);
	}
	else if (m_nDraw == 4)
	{
		int x = GetScrollPos(SB_HORZ);
		int y = GetScrollPos(SB_VERT);

		m_bClick = TRUE;
		m_ptClick.SetPoint(point.x + x, point.y + y);
		m_ptMove.SetPoint(point.x + x, point.y + y);
	}
	else if (m_nDraw == 0)
	{
		CDC MemDC;
		CBitmap* pOldBitmap;
		BITMAP bit;
		CPen   pen;
		CBrush brush;

		CDC* pDC = GetDC();

		pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		brush.CreateSolidBrush(RGB(255, 255, 255));

		m_cbitmap.GetBitmap(&bit);
		MemDC.CreateCompatibleDC(pDC);
		pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);

		CPen* oldPen = MemDC.SelectObject(&pen);
		CBrush* oldBrush = MemDC.SelectObject(&brush);

		int x = GetScrollPos(SB_HORZ);
		int y = GetScrollPos(SB_VERT);

		CPoint ptNew(point.x + x, point.y + y);

		MemDC.Ellipse(ptNew.x - 10, ptNew.y - 10, ptNew.x + 10, ptNew.y + 10);

		MemDC.SelectObject(oldPen);
		MemDC.SelectObject(oldBrush);
		MemDC.SelectObject(pOldBitmap);
		MemDC.DeleteDC();
		pen.DeleteObject();
		brush.DeleteObject();

		Invalidate(FALSE);
		ReleaseDC(pDC);
	
	}
	
	CScrollView::OnLButtonDown(nFlags, point);
}


void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_nDraw == 2)
	{
		CDC MemDC;
		CBitmap* pOldBitmap;
		BITMAP bit;

		CDC* pDC = GetDC();

		m_cbitmap.GetBitmap(&bit);
		MemDC.CreateCompatibleDC(pDC);
		pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);

		CPen pen(PS_SOLID, 1, m_colorFore);
		CPen* poldPen = MemDC.SelectObject(&pen);

		
		int x = GetScrollPos(SB_HORZ);
		int y = GetScrollPos(SB_VERT);

		CPoint ptNew(point.x + x, point.y + y);

		MemDC.MoveTo(m_ptClick);
		MemDC.LineTo(ptNew);

		MemDC.SelectObject(poldPen);
		pen.DeleteObject();
		
		MemDC.SelectObject(pOldBitmap);
		MemDC.DeleteDC();

		Invalidate(FALSE);
		ReleaseDC(pDC);

	}
	else if (m_nDraw == 3)
	{
		CDC MemDC;
		CBitmap* pOldBitmap;
		BITMAP bit;

		CDC* pDC = GetDC();

		m_cbitmap.GetBitmap(&bit);
		MemDC.CreateCompatibleDC(pDC);
		pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);

		CPen pen(PS_SOLID, 1, m_colorFore);
		CPen* poldPen = MemDC.SelectObject(&pen);

		int x = GetScrollPos(SB_HORZ);
		int y = GetScrollPos(SB_VERT);

		CPoint ptNew(point.x + x, point.y + y);

		MemDC.Rectangle(m_ptClick.x, m_ptClick.y, ptNew.x, ptNew.y);

		MemDC.SelectObject(poldPen);
		pen.DeleteObject();
		
		MemDC.SelectObject(pOldBitmap);
		MemDC.DeleteDC();

		Invalidate(FALSE);
		ReleaseDC(pDC);
	}
	else if (m_nDraw == 4)
	{
		CDC MemDC;
		CBitmap* pOldBitmap;
		BITMAP bit;

		CDC* pDC = GetDC();

		m_cbitmap.GetBitmap(&bit);
		MemDC.CreateCompatibleDC(pDC);
		pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);

		CPen pen(PS_SOLID, 1, m_colorFore);
		CPen* poldPen = MemDC.SelectObject(&pen);

		int x = GetScrollPos(SB_HORZ);
		int y = GetScrollPos(SB_VERT);

		CPoint ptNew(point.x + x, point.y + y);

		MemDC.Ellipse(m_ptClick.x, m_ptClick.y, ptNew.x, ptNew.y);

		MemDC.SelectObject(poldPen);
		pen.DeleteObject();
		
		MemDC.SelectObject(pOldBitmap);
		MemDC.DeleteDC();

		Invalidate(FALSE);
		ReleaseDC(pDC);
	}
	
	CScrollView::OnLButtonUp(nFlags, point);
}


void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_nDraw == 1)
	{
		if (nFlags & MK_LBUTTON)
		{
			CDC MemDC;
			CBitmap* pOldBitmap;
			BITMAP bit;

			CDC* pDC = GetDC();

			m_cbitmap.GetBitmap(&bit);
			MemDC.CreateCompatibleDC(pDC);
			pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);

			int x = GetScrollPos(SB_HORZ);
			int y = GetScrollPos(SB_VERT);

			CPoint ptNew(point.x + x, point.y + y);

			MemDC.SetPixel(ptNew, m_colorFore);

			MemDC.SelectObject(pOldBitmap);
			MemDC.DeleteDC();

			Invalidate(FALSE);
			ReleaseDC(pDC);
		}
	}
	else if (m_nDraw == 2)
	{
		if (nFlags & MK_LBUTTON && m_bClick)
		{
			CDC MemDC;
			CBitmap* pOldBitmap;
			BITMAP bit;

			CDC* pDC = GetDC();

			m_cbitmap.GetBitmap(&bit);
			MemDC.CreateCompatibleDC(pDC);
			pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);

			CPen pen(PS_SOLID, 1, m_colorFore);
			CPen* poldPen = MemDC.SelectObject(&pen);

			
			int x = GetScrollPos(SB_HORZ);
			int y = GetScrollPos(SB_VERT);

			CPoint ptNew(point.x + x, point.y + y);

			MemDC.SetROP2(R2_NOTXORPEN);
			MemDC.MoveTo(m_ptClick);
			MemDC.LineTo(m_ptMove);

			m_ptMove = ptNew;
			
			MemDC.MoveTo(m_ptClick);
			MemDC.LineTo(m_ptMove);

			MemDC.SelectObject(poldPen);
			pen.DeleteObject();
			
			MemDC.SelectObject(pOldBitmap);
			MemDC.DeleteDC();

			Invalidate(FALSE);
			ReleaseDC(pDC);
		}
	}
	else if (m_nDraw == 3)
	{
		if (nFlags & MK_LBUTTON && m_bClick)
		{
			CDC MemDC;
			CBitmap* pOldBitmap;
			BITMAP bit;

			CDC* pDC = GetDC();

			m_cbitmap.GetBitmap(&bit);
			MemDC.CreateCompatibleDC(pDC);
			pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);

			CPen pen(PS_SOLID, 1, m_colorFore);
			CPen* poldPen = MemDC.SelectObject(&pen);

			
			int x = GetScrollPos(SB_HORZ);
			int y = GetScrollPos(SB_VERT);

			CPoint ptNew(point.x + x, point.y + y);

			MemDC.SetROP2(R2_NOTXORPEN);
			MemDC.Rectangle(m_ptClick.x, m_ptClick.y, m_ptMove.x, m_ptMove.y);

			m_ptMove = ptNew;

			MemDC.Rectangle(m_ptClick.x, m_ptClick.y, m_ptMove.x, m_ptMove.y);

			MemDC.SelectObject(poldPen);
			pen.DeleteObject();
			
			MemDC.SelectObject(pOldBitmap);
			MemDC.DeleteDC();

			Invalidate(FALSE);
			ReleaseDC(pDC);
		}
	}
	else if (m_nDraw == 4)
	{
		if (nFlags & MK_LBUTTON && m_bClick)
		{
			CDC MemDC;
			CBitmap* pOldBitmap;
			BITMAP bit;

			CDC* pDC = GetDC();

			m_cbitmap.GetBitmap(&bit);
			MemDC.CreateCompatibleDC(pDC);
			pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);

			CPen pen(PS_SOLID, 1, m_colorFore);
			CPen* poldPen = MemDC.SelectObject(&pen);

			
			int x = GetScrollPos(SB_HORZ);
			int y = GetScrollPos(SB_VERT);

			CPoint ptNew(point.x + x, point.y + y);

			MemDC.SetROP2(R2_NOTXORPEN);
			MemDC.Ellipse(m_ptClick.x, m_ptClick.y, m_ptMove.x, m_ptMove.y);

			m_ptMove = ptNew;

			MemDC.Ellipse(m_ptClick.x, m_ptClick.y, m_ptMove.x, m_ptMove.y);

			MemDC.SelectObject(poldPen);
			pen.DeleteObject();
			
			MemDC.SelectObject(pOldBitmap);
			MemDC.DeleteDC();

			Invalidate(FALSE);
			ReleaseDC(pDC);
		}
	}
	else if (m_nDraw == 0)
	{
		if (nFlags & MK_LBUTTON)
		{
			CDC MemDC;
			CBitmap* pOldBitmap;
			BITMAP bit;
			CPen   pen;
			CBrush brush;

			
			CDC* pDC = GetDC();


			pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
			brush.CreateSolidBrush(RGB(255, 255, 255));

			 
			
			m_cbitmap.GetBitmap(&bit);
			MemDC.CreateCompatibleDC(pDC);
			pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_cbitmap);

			CPen* oldPen = MemDC.SelectObject(&pen);
			CBrush* oldBrush = MemDC.SelectObject(&brush);
			
			int x = GetScrollPos(SB_HORZ);
			int y = GetScrollPos(SB_VERT);

			CPoint ptNew(point.x + x, point.y + y);

			MemDC.Ellipse(ptNew.x - 10, ptNew.y - 10, ptNew.x + 10, ptNew.y + 10);

			MemDC.SelectObject(oldPen);
			MemDC.SelectObject(oldBrush);
			MemDC.SelectObject(pOldBitmap);
			MemDC.DeleteDC();
			pen.DeleteObject();
			brush.DeleteObject();
			
			Invalidate(FALSE);
			ReleaseDC(pDC);
		}
	}
	
	CScrollView::OnMouseMove(nFlags, point);
}


void CMFCApplication1View::OnDrawDot()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDraw = 1;
}


void CMFCApplication1View::OnDrawLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDraw = 2;
}


void CMFCApplication1View::OnDrawRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDraw = 3;
}


void CMFCApplication1View::OnDrawCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDraw = 4;
}


void CMFCApplication1View::OnEraser()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDraw = 0;
}


void CMFCApplication1View::OnColorForeground()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlg(RGB(0, 0, 0));

	dlg.DoModal();

	m_colorFore = dlg.GetColor();
	
}


void CMFCApplication1View::OnUpdateDrawDot(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDraw == 1);
}


void CMFCApplication1View::OnUpdateDrawLine(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDraw == 2);
}


void CMFCApplication1View::OnUpdateDrawRect(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDraw == 3);
}


void CMFCApplication1View::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDraw == 4);
}


void CMFCApplication1View::OnUpdateEraser(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDraw == 0);
}
