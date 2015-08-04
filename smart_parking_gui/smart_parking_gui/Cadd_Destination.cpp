// Cadd_Destination.cpp : implementation file
//

#include "stdafx.h"
#include "smart_parking_gui.h"
#include "Cadd_Destination.h"
#include "afxdialogex.h"
#include "Destination.h"


// Cadd_Destination dialog

IMPLEMENT_DYNAMIC(Cadd_Destination, CDialogEx)

Cadd_Destination::Cadd_Destination(int destID, CWnd* pParent /*=NULL*/)
	: CDialogEx(Cadd_Destination::IDD, pParent)
	, m_LocationX(0)
	, m_LocationY(0)
	, m_EchoDestId(_T("This destination will have ID: 0."))
{
	this->destID = destID;
	m_EchoDestId.Format(_T("This destination will have ID: %d."), destID); // Changes number to new ID
}

Cadd_Destination::~Cadd_Destination()
{
}

void Cadd_Destination::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_E_LOCX, m_LocationX);
	DDX_Text(pDX, IDC_E_LOCY, m_LocationY);
	DDX_Text(pDX, IDC_DEST_ID, m_EchoDestId);
}


BEGIN_MESSAGE_MAP(Cadd_Destination, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cadd_Destination::OnBnClickedOk)
END_MESSAGE_MAP()


// Cadd_Destination message handlers


void Cadd_Destination::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
