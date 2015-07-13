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
	, m_EchoPolicyDesc(_T("1"))
	, m_EchoLotID(_T("This lot will have ID: 0."))
{
	this->IDvalue = inputID;
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
	DDX_Control(pDX, IDC_SLIDER1, m_HSliderPolicy);
	DDX_Text(pDX, IDC_SLIDER1, pricingPolicy);
	DDX_Text(pDX, IDC_ET_BASECOST, m_BaseCost);
	DDX_Text(pDX, IDC_POLICY_DESC, m_EchoPolicyDesc);
	DDX_Text(pDX, IDC_LOT_ID_CHECK, m_EchoLotID);
}


BEGIN_MESSAGE_MAP(Cadd_Lot, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &Cadd_Lot::OnBnClickedOk)
END_MESSAGE_MAP()


// Cadd_Lot message handlers


void Cadd_Lot::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == (CScrollBar *) &m_HSliderPolicy) {
		pricingPolicy = m_HSliderPolicy.GetPos();
		switch (pricingPolicy) {
		case 1:
			m_EchoPolicyDesc.Format(_T("2\n"));
			break;
		case 2:
			m_EchoPolicyDesc.Format(_T("3\n"));
			break;
		case 3:
			m_EchoPolicyDesc.Format(_T("4\n"));
			break;
		case 4:
			m_EchoPolicyDesc.Format(_T("5\n"));
			break;
		case 5:
			m_EchoPolicyDesc.Format(_T("6\n"));
			break;
		default: // case 0 and all else
			m_EchoPolicyDesc.Format(_T("1-\nConstant"));
			break;
		}
		UpdateData(FALSE);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL Cadd_Lot::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_HSliderPolicy.SetRange(0, 6, TRUE);
	m_HSliderPolicy.SetPos(0);
	m_EchoLotID.Format(_T("This lot will have ID: %d."), IDvalue);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void Cadd_Lot::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
