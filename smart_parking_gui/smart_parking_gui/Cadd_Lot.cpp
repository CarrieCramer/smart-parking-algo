// Cadd_Lot.cpp : implementation file
//

#include "stdafx.h"
#include "smart_parking_gui.h"
#include "Cadd_Lot.h"
#include "afxdialogex.h"


// Cadd_Lot dialog

IMPLEMENT_DYNAMIC(Cadd_Lot, CDialogEx)

Cadd_Lot::Cadd_Lot(int inputID, CWnd* pParent /*=NULL*/)
	: CDialogEx(Cadd_Lot::IDD, pParent)
	, m_LocationX(0)
	, m_LocationY(0)
	, m_ParkSpaceCount(0)
	, m_BaseCost(0)
	, m_EchoLotID(_T("This lot will have ID: 0."), inputID)
{
	this->IDvalue = inputID;
	m_EchoLotID.Format(_T("This lot will have ID: %d."), inputID);
}

Cadd_Lot::~Cadd_Lot()
{
}

void Cadd_Lot::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_LocationX);
	DDX_Text(pDX, IDC_EDIT2, m_LocationY);
	DDX_Text(pDX, IDC_ET_PARKSPACENO, m_ParkSpaceCount);
	DDX_Text(pDX, IDC_ET_BASECOST, m_BaseCost);
}


BEGIN_MESSAGE_MAP(Cadd_Lot, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &Cadd_Lot::OnBnClickedOk)
END_MESSAGE_MAP()


// Cadd_Lot message handlers

BOOL Cadd_Lot::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void Cadd_Lot::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDialogEx::OnOK();
}

