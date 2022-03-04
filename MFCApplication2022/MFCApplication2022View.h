
// MFCApplication2022View.h : interface of the CMFCApplication2022View class
//

#pragma once


class CMFCApplication2022View : public CView
{
protected: // create from serialization only
	CMFCApplication2022View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication2022View)

// Attributes
public:
	CMFCApplication2022Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCApplication2022View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCApplication2022View.cpp
inline CMFCApplication2022Doc* CMFCApplication2022View::GetDocument() const
   { return reinterpret_cast<CMFCApplication2022Doc*>(m_pDocument); }
#endif

