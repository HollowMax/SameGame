
// SameGameDoc.h : interface of the CSameGameDoc class
//


#pragma once

#include "SameGameBoard.h"


class CSameGameDoc : public CDocument
{
protected: // create from serialization only
	CSameGameDoc() noexcept;
	DECLARE_DYNCREATE(CSameGameDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSameGameDoc();

	COLORREF GetBoardSpace(int row, int col) {
		return m_board.GetBoardSpace(row, col);
	}
	void SetupBoard(void) { m_board.SetupBoard(); }
	int GetWidth(void) { return m_board.GetWidth(); }
	int GetHeight(void) { return m_board.GetHeight(); }
	int GetRows(void) { return m_board.GetRows(); }
	int GetColumns(void) { return m_board.GetColumns(); }
	void DeleteBoard(void) { m_board.DeleteBoard(); }
	
	bool IsGameOver() { return m_board.IsGameOver(); }
	int DeleteBlocks(int row, int col) { return m_board.DeleteBlocks(row, col); }
	int GetRemainingCount() { return m_board.GetRemainingCount(); }

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CSameGameBoard m_board;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
