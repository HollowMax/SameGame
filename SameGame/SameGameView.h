
// SameGameView.h : interface of the CSameGameView class
//

#pragma once


class CSameGameView : public CView
{
protected: // create from serialization only
	CSameGameView() noexcept;
	DECLARE_DYNCREATE(CSameGameView)

// Attributes
public:
	CSameGameDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	void ResizeWindow();

	virtual ~CSameGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void setColorsCount(int numColors);
	void setColorsCheckmark(int numColors, CCmdUI* pCmdUI);

	virtual void OnInitialUpdate();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDifficulty3colors();
	afx_msg void OnUpdateDifficulty3colors(CCmdUI* pCmdUI);
	afx_msg void OnDifficulty4colors();
	afx_msg void OnUpdateDifficulty4colors(CCmdUI* pCmdUI);
	afx_msg void OnDifficulty5colors();
	afx_msg void OnUpdateDifficulty5colors(CCmdUI* pCmdUI);
	afx_msg void OnDifficulty6colors();
	afx_msg void OnUpdateDifficulty6colors(CCmdUI* pCmdUI);
	afx_msg void OnDifficulty7colors();
	afx_msg void OnUpdateDifficulty7colors(CCmdUI* pCmdUI);
	afx_msg void OnSettingsNumberofblocks();
	afx_msg void OnSettingsSizeofblocks();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // debug version in SameGameView.cpp
inline CSameGameDoc* CSameGameView::GetDocument() const
   { return reinterpret_cast<CSameGameDoc*>(m_pDocument); }
#endif

