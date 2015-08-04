// Cgenerate_config.cpp : implementation file
//

#include "stdafx.h"
#include "smart_parking_gui.h"
#include "Cgenerate_config.h"
#include "afxdialogex.h"


// Cgenerate_config dialog

IMPLEMENT_DYNAMIC(Cgenerate_config, CDialogEx)

Cgenerate_config::Cgenerate_config(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cgenerate_config::IDD, pParent)
	, m_ItNumber(5)
	, m_GridSize(100)
	, m_SimuHours(1)
	, m_AvgDemand(0)
	, m_LotCount(0)
	, m_DestCount(0)
	, m_utilRate(0)
	, m_occuRate(0)
	, m_LotPrice(0)
	, m_RandDestProbs(FALSE)
{
	engine = default_random_engine(random_device{}());
	pricingPolicy = 1;
}

Cgenerate_config::~Cgenerate_config()
{
}

void Cgenerate_config::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ITERCOUNT, m_ItNumber);
	DDV_MinMaxInt(pDX, m_ItNumber, 1, 100);
	DDX_Text(pDX, IDC_GRIDSIZE, m_GridSize);
	DDX_Text(pDX, IDC_SIMUHOUR, m_SimuHours);
	DDX_Text(pDX, IDC_AVGDEMAND, m_AvgDemand);
	DDX_Text(pDX, IDC_LOTCOUNT, m_LotCount);
	DDX_Text(pDX, IDC_DESTCOUNT, m_DestCount);
	DDX_Text(pDX, IDC_UTILRATE, m_utilRate);
	DDX_Text(pDX, IDC_OCCURATE, m_occuRate);
	DDX_Control(pDX, IDC_POLICY_SLIDER, m_SliderPolicy);
	DDX_Text(pDX, IDC_LOTPRICE, m_LotPrice);
	DDX_Control(pDX, IDC_FILETITLE, FileTitleBox);
	DDV_MinMaxDouble(pDX, m_utilRate, 0, 1);
	DDV_MinMaxDouble(pDX, m_occuRate, 0, 1);
	DDX_Control(pDX, IDC_POLICYDESCRIPTION, m_EchoDescription);
	DDX_Check(pDX, IDC_CHECKDESTPROBS, m_RandDestProbs);
}


BEGIN_MESSAGE_MAP(Cgenerate_config, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cgenerate_config::OnBnClickedOk)
	ON_BN_CLICKED(IDC_B_BROWSE, &Cgenerate_config::OnBnClickedBBrowse)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Cgenerate_config message handlers



void Cgenerate_config::OnBnClickedOk()
{
	
	CDialogEx::OnOK();
	// Run generate_config files
}


void Cgenerate_config::OnBnClickedBBrowse()
{
	TCHAR szFilters[] = _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");

	// Create a Save dialog
	CFileDialog fileDlg(FALSE, _T("txt"), _T("*.txt"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();
		FileTitleBox.SetWindowText(pathName);
	}
}


void Cgenerate_config::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// Describe the current pricing policy
	if (pScrollBar == (CScrollBar *)&m_SliderPolicy) {
		pricingPolicy = m_SliderPolicy.GetPos();
		CString policyDesc;
		switch (pricingPolicy) {
		case 1:
			policyDesc.Format(_T("Equal Static Pricing\r\nAll lots are given the same static prices."));
			GetDlgItem(IDC_LOTPRICE)->EnableWindow(TRUE);
			break;
		case 2:
			policyDesc.Format(_T("Random Static Pricing\r\nAll lots are given random yet static prices."));
			GetDlgItem(IDC_LOTPRICE)->EnableWindow(FALSE);
			break;
		case 3:
			policyDesc.Format(_T("Proportional Dynamic Pricing\r\n"));
			GetDlgItem(IDC_LOTPRICE)->EnableWindow(TRUE);
			break;
		case 4:
			policyDesc.Format(_T("LA Express Park Dynamic Pricing\r\nDemand-based algorithm used to change the price of each lot"));
			GetDlgItem(IDC_LOTPRICE)->EnableWindow(TRUE);
			break;
		case 5:
			policyDesc.Format(_T("Proportional-Derivative Dynamic Pricing\r\nPrice based on changes in the lot reservation rate"));
			GetDlgItem(IDC_LOTPRICE)->EnableWindow(TRUE);
			break;
		case 6:
			policyDesc.Format(_T("Uber Dynamic Pricing\r\n"));
			GetDlgItem(IDC_LOTPRICE)->EnableWindow(TRUE);
			break;
		default:
			pricingPolicy = 1;
			policyDesc.Format(_T("Equal Static Pricing\r\nAll lots are given the same static prices."));
			GetDlgItem(IDC_LOTPRICE)->EnableWindow(TRUE);
			break;
		}
		m_EchoDescription.SetWindowText(policyDesc);
		UpdateData(FALSE);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL Cgenerate_config::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_SliderPolicy.SetRange(1, 7, TRUE); // range from policies 1 to 7
	m_EchoDescription.SetWindowText(_T("Equal Static Pricing\r\nAll lots are given the same static prices."));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
