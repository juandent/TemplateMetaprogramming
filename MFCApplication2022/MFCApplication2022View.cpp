
// MFCApplication2022View.cpp : implementation of the CMFCApplication2022View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication2022.h"
#endif

#include "MFCApplication2022Doc.h"
#include "MFCApplication2022View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2022View

IMPLEMENT_DYNCREATE(CMFCApplication2022View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication2022View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication2022View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplication2022View construction/destruction

CMFCApplication2022View::CMFCApplication2022View() noexcept
{
	// TODO: add construction code here

}

CMFCApplication2022View::~CMFCApplication2022View()
{
}

BOOL CMFCApplication2022View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplication2022View drawing

void CMFCApplication2022View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication2022Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCApplication2022View printing


void CMFCApplication2022View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication2022View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplication2022View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplication2022View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCApplication2022View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication2022View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication2022View diagnostics

#ifdef _DEBUG
void CMFCApplication2022View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication2022View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication2022Doc* CMFCApplication2022View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2022Doc)));
	return (CMFCApplication2022Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication2022View message handlers
