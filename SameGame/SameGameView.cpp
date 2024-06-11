
// SameGameView.cpp : implementation of the CSameGameView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"
#include "SameGameView.h"
#include "COptionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSameGameView

IMPLEMENT_DYNCREATE(CSameGameView, CView)

BEGIN_MESSAGE_MAP(CSameGameView, CView)
//	ON_WM_MBUTTONDOWN()
ON_WM_LBUTTONDOWN()
ON_COMMAND(ID_DIFFICULTY_3COLORS, &CSameGameView::OnDifficulty3colors)
ON_UPDATE_COMMAND_UI(ID_DIFFICULTY_3COLORS, &CSameGameView::OnUpdateDifficulty3colors)
ON_COMMAND(ID_DIFFICULTY_4COLORS, &CSameGameView::OnDifficulty4colors)
ON_UPDATE_COMMAND_UI(ID_DIFFICULTY_4COLORS, &CSameGameView::OnUpdateDifficulty4colors)
ON_COMMAND(ID_DIFFICULTY_5COLORS, &CSameGameView::OnDifficulty5colors)
ON_UPDATE_COMMAND_UI(ID_DIFFICULTY_5COLORS, &CSameGameView::OnUpdateDifficulty5colors)
ON_COMMAND(ID_DIFFICULTY_6COLORS, &CSameGameView::OnDifficulty6colors)
ON_UPDATE_COMMAND_UI(ID_DIFFICULTY_6COLORS, &CSameGameView::OnUpdateDifficulty6colors)
ON_COMMAND(ID_DIFFICULTY_7COLORS, &CSameGameView::OnDifficulty7colors)
ON_UPDATE_COMMAND_UI(ID_DIFFICULTY_7COLORS, &CSameGameView::OnUpdateDifficulty7colors)
ON_COMMAND(ID_SETTINGS_NUMBEROFBLOCKS, &CSameGameView::OnSettingsNumberofblocks)
ON_COMMAND(ID_SETTINGS_SIZEOFBLOCKS, &CSameGameView::OnSettingsSizeofblocks)
ON_COMMAND(ID_EDIT_UNDO, &CSameGameView::OnEditUndo)
ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CSameGameView::OnUpdateEditUndo)
ON_COMMAND(ID_EDIT_REDO, &CSameGameView::OnEditRedo)
ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CSameGameView::OnUpdateEditRedo)
END_MESSAGE_MAP()

// CSameGameView construction/destruction

CSameGameView::CSameGameView() noexcept
{
	// TODO: add construction code here

}

CSameGameView::~CSameGameView()
{
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSameGameView drawing

void CSameGameView::OnDraw(CDC* pDC)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	int nDCSave = pDC->SaveDC();

	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);

	pDC->FillSolidRect(&rcClient, clr);

	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);

	for (int row = 0; row < pDoc->GetRows(); row++) {
		for (int col = 0; col < pDoc->GetColumns(); col++) {
			clr = pDoc->GetBoardSpace(row, col);

			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();

			pDC->FillSolidRect(&rcBlock, clr);

			pDC->Rectangle(&rcBlock);
		}
	}
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}


// CSameGameView diagnostics

#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameDoc* CSameGameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif //_DEBUG

void CSameGameView::OnInitialUpdate() {
	CView::OnInitialUpdate();

	ResizeWindow();
}

void CSameGameView::ResizeWindow() {
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rcClient, rcWindow;
	GetClientRect(rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();

	rcWindow.right = rcWindow.left + pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top + pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;

	GetParentFrame()->MoveWindow(&rcWindow);
}


// CSameGameView message handlers

void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point) {
	CSameGameDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();

	int count = pDoc->DeleteBlocks(row, col);

	if (count > 0) {
		Invalidate();
		UpdateWindow();

		if (pDoc->IsGameOver()) {
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("No more moves left\nBlocks remaining: %d"), remaining);

			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

void CSameGameView::setColorsCount(int numColors) {
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->SetNumColors(numColors);

	Invalidate();
	UpdateWindow();
}

void CSameGameView::setColorsCheckmark(int numColors, CCmdUI *pCmdUI) {
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pCmdUI->SetCheck(pDoc->GetNumColors() == numColors);
}

void CSameGameView::OnDifficulty3colors()
{
	setColorsCount(3);
}


void CSameGameView::OnUpdateDifficulty3colors(CCmdUI* pCmdUI)
{
	setColorsCheckmark(3, pCmdUI);
}


void CSameGameView::OnDifficulty4colors()
{
	setColorsCount(4);
}


void CSameGameView::OnUpdateDifficulty4colors(CCmdUI* pCmdUI)
{
	setColorsCheckmark(4, pCmdUI);
}


void CSameGameView::OnDifficulty5colors()
{
	setColorsCount(5);
}


void CSameGameView::OnUpdateDifficulty5colors(CCmdUI* pCmdUI)
{
	setColorsCheckmark(5, pCmdUI);
}


void CSameGameView::OnDifficulty6colors()
{
	setColorsCount(6);
}


void CSameGameView::OnUpdateDifficulty6colors(CCmdUI* pCmdUI)
{
	setColorsCheckmark(6, pCmdUI);
}


void CSameGameView::OnDifficulty7colors()
{
	setColorsCount(7);
}


void CSameGameView::OnUpdateDifficulty7colors(CCmdUI* pCmdUI)
{
	setColorsCheckmark(7, pCmdUI);
}


void CSameGameView::OnSettingsNumberofblocks()
{
	// TODO: Add your command handler code here
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	COptionDialog dlg(true, this);

	dlg.m_nValue1 = pDoc->GetRows();
	dlg.m_nValue2 = pDoc->GetColumns();

	if (dlg.DoModal() == IDOK)
	{
		pDoc->DeleteBoard();

		pDoc->SetRows(dlg.m_nValue1);
		pDoc->SetColumns(dlg.m_nValue2);

		pDoc->SetupBoard();

		ResizeWindow();
	}
}


void CSameGameView::OnSettingsSizeofblocks()
{
	// TODO: Add your command handler code here
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	COptionDialog dlg(false, this);

	dlg.m_nValue1 = pDoc->GetWidth();
	dlg.m_nValue2 = pDoc->GetHeight();

	if (dlg.DoModal() == IDOK)
	{
		pDoc->DeleteBoard();

		pDoc->SetWidth(dlg.m_nValue1);
		pDoc->SetHeight(dlg.m_nValue2);

		pDoc->SetupBoard();

		ResizeWindow();
	}
}


void CSameGameView::OnEditUndo()
{
	// TODO: Add your command handler code here
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UndoLast();

	Invalidate();
	UpdateWindow();
}


void CSameGameView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pCmdUI->Enable(pDoc->CanUndo());
}


void CSameGameView::OnEditRedo()
{
	// TODO: Add your command handler code here
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->RedoLast();

	Invalidate();
	UpdateWindow();
}


void CSameGameView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pCmdUI->Enable(pDoc->CanRedo());
}
