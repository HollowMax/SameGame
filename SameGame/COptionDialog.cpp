// COptionDialog.cpp : implementation file
//

#include "pch.h"
#include "SameGame.h"
#include "afxdialogex.h"
#include "COptionDialog.h"


// COptionDialog dialog

IMPLEMENT_DYNAMIC(COptionDialog, CDialog)

COptionDialog::COptionDialog(bool bRowColumn, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_OPTIONS, pParent)
	, m_nValue1(0)
	, m_nValue2(0)
	, m_bRowColumnDialog(bRowColumn)
{

}

COptionDialog::~COptionDialog()
{
}

void COptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT1, m_ctrlStaticText1);
	DDX_Control(pDX, IDC_STATIC_TEXT2, m_ctrlStaticText2);
	DDX_Text(pDX, IDC_EDIT1, m_nValue1);
	DDX_Text(pDX, IDC_EDIT2, m_nValue2);
}


BEGIN_MESSAGE_MAP(COptionDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &COptionDialog::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// COptionDialog message handlers


BOOL COptionDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	if (m_bRowColumnDialog) {
		SetWindowText(_T("Update Block Count"));

		m_ctrlStaticText1.SetWindowText(_T("Rows"));
		m_ctrlStaticText2.SetWindowText(_T("Columns"));
	}
	else {
		SetWindowText(_T("Update Block Size"));

		m_ctrlStaticText1.SetWindowText(_T("Block Width"));
		m_ctrlStaticText2.SetWindowText(_T("Block Height"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void COptionDialog::OnBnClickedButtonReset()
{
	// TODO: Add your control notification handler code here
		m_nValue1 = m_nValue2 = m_bRowColumnDialog ? 15 : 35;

		UpdateData(false);
}
