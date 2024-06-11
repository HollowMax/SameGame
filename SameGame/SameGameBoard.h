#ifndef SAME_GAME_BOARD
#define SAME_GAME_BOARD

class CSameGameBoard {
public:
	CSameGameBoard(void);

	CSameGameBoard(const CSameGameBoard& board);

	~CSameGameBoard(void);

	void SetupBoard(void);

	COLORREF GetBoardSpace(int row, int col);


	int GetWidth(void) const { return m_nWidth; }
	int GetHeight(void) const { return m_nHeight; }
	int GetColumns(void) const { return m_nColumns; }
	int GetRows(void) const { return m_nRows; }

	void SetWidth(int nWidth) { m_nWidth = (nWidth >= 3) ? nWidth : 3; }
	void SetHeight(int nHeight) { m_nHeight = (nHeight >= 3) ? nHeight : 3; }
	void SetColumns(int nColumns) { m_nColumns = (nColumns >= 5) ? nColumns : 5; }
	void SetRows(int nRows) { m_nRows = (nRows >= 5) ? nRows : 5; }

	int GetRemainingCount(void) const { return m_nRemaining; };

	int GetNumColors(void) { return m_nColors; }

	void SetNumColors(int nColors) {
		m_nColors = (nColors >= 3 && nColors <= 7) ? nColors : m_nColors;
	}

	void DeleteBoard(void);
	
	bool IsGameOver(void) const;

	int DeleteBlocks(int row, int col);

private: 
	void CreateBoard(void);

	enum Direction {
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	int DeleteNeighborBlocks(int row, int col, int color, Direction direction);
	void CompactBoard(void);

	int** m_arrBoard;

	COLORREF m_arrColors[8];

	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
	int m_nRemaining;
	int m_nColors;
};

#endif
