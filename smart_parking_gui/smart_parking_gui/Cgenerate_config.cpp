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
	, m_RandCapacIn(FALSE)
	, m_Capac(0)
{
	engine = default_random_engine(random_device{}());
	pricingPolicy = 1;
	m_Capac = 0;
	maxSlideValue = 100;
	scrolling = false;
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
	DDX_Check(pDX, IDC_CHECKLOTCAPS, m_RandCapacIn);
	DDX_Control(pDX, IDC_LOTCAPACITY, LotCapacityBox);
	DDX_Text(pDX, IDC_LOTCAPACITY, m_Capac);
	DDX_Control(pDX, IDC_CHECKLOTCAPS, m_RLCCheckbox);
	DDX_Control(pDX, IDC_SLIDE_UTILRATE, m_SlideUtilRate);
	DDX_Control(pDX, IDC_SLIDE_OCCURATE, m_SlideOccuRate);
	DDX_Control(pDX, IDC_UTILRATE, UtilRead);
	DDX_Control(pDX, IDC_OCCURATE, OccuRead);
}


BEGIN_MESSAGE_MAP(Cgenerate_config, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cgenerate_config::OnBnClickedOk)
	ON_BN_CLICKED(IDC_B_BROWSE, &Cgenerate_config::OnBnClickedBBrowse)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECKLOTCAPS, &Cgenerate_config::OnBnClickedChecklotcaps)
	ON_EN_CHANGE(IDC_UTILRATE, &Cgenerate_config::OnEnChangeUtilrate)
	ON_EN_CHANGE(IDC_OCCURATE, &Cgenerate_config::OnEnChangeOccurate)
END_MESSAGE_MAP()


// Cgenerate_config message handlers

void Cgenerate_config::OnBnClickedOk()
{
	// Run generate_config files
	UpdateData(TRUE);
	ofstream config;
	if (newConfigFileName.IsEmpty()) {
		config.open("config.txt");
	}
	else {
		config.open(newConfigFileName);
	}

	// Write information to config
	writeIterations(m_ItNumber, config);
	writeGridSize(m_GridSize, config);
	writeDestCount(m_DestCount, config);
	writeDestLocs(m_GridSize, m_DestCount, config, engine);
	std::list<double> destProbs = writeDestProbs(m_RandDestProbs, m_DestCount, config, engine);
	vector<double> avgDurations = writeDestAvgDurs(m_DestCount, config, engine);
	writeLotCount(m_LotCount, config);
	writeLotLocs(m_GridSize, m_LotCount, config, engine);
	int totalCapacity = writeLotCapacities(m_RandCapacIn, m_Capac, m_AvgDemand, m_LotCount, config, engine);
	writeLotTypes(m_LotCount, pricingPolicy, config, engine);
	writePricePolicy(pricingPolicy, config);
	writeLotPrices(pricingPolicy, m_LotPrice, m_LotCount, config, engine);
	writeOccupationRate(m_occuRate, config);
	writeAvgDemand(m_AvgDemand, config);
	std::list<std::list<double> > arrivals = generateArrivals(m_ItNumber, m_SimuHours, m_AvgDemand, config, engine);
	std::list<int> numDrivers = writeNumDrivers(arrivals, config);
	writeDriverArrivals(arrivals, config);
	writeDriverLocs(m_GridSize, numDrivers, config, engine);
	std::list<std::list<int> > dests = writeDriverDests(destProbs, numDrivers, config, engine);
	writeDriverDurs(m_AvgDemand, m_utilRate, totalCapacity, numDrivers, config, engine);
	writeDriverMaxWalkDists(m_GridSize, numDrivers, config, engine);
	writeDriverMaxPrices(numDrivers, config, engine);
	writeDriverImportWeights(numDrivers, config, engine);
	
	config.close();

	CDialogEx::OnOK();
}


void Cgenerate_config::OnBnClickedBBrowse()
{
	TCHAR szFilters[] = _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");

	// Create a Save dialog
	CFileDialog fileDlg(FALSE, _T("txt"), _T("config.txt"),
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
	scrolling = true;
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
		case 7:
			policyDesc.Format(_T("Competitive Pricing Game\r\n"));
		default:
			pricingPolicy = 1;
			policyDesc.Format(_T("Equal Static Pricing\r\nAll lots are given the same static prices."));
			GetDlgItem(IDC_LOTPRICE)->EnableWindow(TRUE);
			break;
		}
		m_EchoDescription.SetWindowText(policyDesc);
	}
	else  {
		int value;
		if (pScrollBar == (CScrollBar *)&m_SlideUtilRate) {
			value = m_SlideUtilRate.GetPos();
		}
		else if (pScrollBar == (CScrollBar *)&m_SlideOccuRate){
			value = m_SlideOccuRate.GetPos();
		}
		double scrollValue = (double)value / (double)maxSlideValue;
		CString echoScroll;
		echoScroll.Format(_T("%.2f"), scrollValue);
		if (pScrollBar == (CScrollBar *)&m_SlideUtilRate) {
			UtilRead.SetWindowText(echoScroll);
		}
		else {
			OccuRead.SetWindowText(echoScroll);
		}
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	scrolling = false;
}


BOOL Cgenerate_config::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	m_SliderPolicy.SetRange(1, 7, TRUE); // range from policies 1 to 7
	m_SlideUtilRate.SetRange(0, maxSlideValue, TRUE);
	m_SlideOccuRate.SetRange(0, maxSlideValue, TRUE);
	m_EchoDescription.SetWindowText(_T("Equal Static Pricing\r\nAll lots are given the same static prices."));
	LotCapacityBox.EnableWindow(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void Cgenerate_config::OnBnClickedChecklotcaps()
{
	// TODO: Add your control notification handler code here
	if (m_RLCCheckbox.GetCheck() == TRUE) {
		GetDlgItem(IDC_LOTCAPACITY)->EnableWindow(FALSE); // disable lot capacity
		m_Capac = 0;
	}
	else {
		GetDlgItem(IDC_LOTCAPACITY)->EnableWindow(TRUE);
	}
}


void Cgenerate_config::OnEnChangeUtilrate()
{
	// TODO:  Add your control notification handler code here
	if (scrolling == false){
		CString readValue;
		UtilRead.GetWindowText(readValue);
		m_utilRate = _wtof(readValue);
		if (m_utilRate >= 0 && m_utilRate <= 1) {
			m_SlideUtilRate.SetPos(m_utilRate*maxSlideValue);
		}
	}
}


void Cgenerate_config::OnEnChangeOccurate()
{
	// TODO:  Add your control notification handler code here
	if (scrolling == false) {
		CString readValue;
		OccuRead.GetWindowText(readValue);
		m_occuRate = _wtof(readValue);
		if (m_occuRate >= 0 && m_occuRate <= 1) {
			m_SlideOccuRate.SetPos(m_occuRate*maxSlideValue);
		}
	}
}
