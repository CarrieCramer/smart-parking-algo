// Cadd_Driver.cpp : implementation file
//

#include "stdafx.h"
#include "smart_parking_gui.h"
#include "Cadd_Driver.h"
#include "afxdialogex.h"


// Cadd_Driver dialog

IMPLEMENT_DYNAMIC(Cadd_Driver, CDialogEx)

Cadd_Driver::Cadd_Driver(int inputID, CWnd* pParent /*=NULL*/)
	: CDialogEx(Cadd_Driver::IDD, pParent)
	, m_DestID(0)
	, m_LocX(0)
	, m_LocY(0)
	, m_WeightScale(0)
	, m_ArrivalTime(0)
	, m_TimeAtPark(0)
	, m_MaxDist(0)
	, m_MaxLotCharge(0)
	, m_Iteration(0)
	, m_EchoID(_T("This driver will have ID: 0."))
{
	this->maxSlideValue = 100;
	scrolling = false;
	m_EchoID.Format(_T("This driver will have ID: %d."), inputID);
}

Cadd_Driver::~Cadd_Driver()
{
}

void Cadd_Driver::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_E_DESTID, m_DestID);
	DDX_Text(pDX, IDC_E_LOCX, m_LocX);
	DDX_Text(pDX, IDC_E_LOCY, m_LocY);
	DDX_Control(pDX, IDC_SLIDER1, m_HSliderWeight);
	DDX_Text(pDX, IDC_ET_WEIGHTEDIT, m_WeightScale);
	DDX_Text(pDX, IDC_ET_ARRIVAL, m_ArrivalTime);
	DDX_Text(pDX, IDC_ET_PARKTIME, m_TimeAtPark);
	DDX_Text(pDX, IDC_ET_MAXDIST, m_MaxDist);
	DDX_Text(pDX, IDC_ET_MAXCHARGE, m_MaxLotCharge);
	DDX_Text(pDX, IDC_ET_ITER, m_Iteration);
	DDX_Control(pDX, IDC_ET_WEIGHTEDIT, ScaleRead);
	DDX_Text(pDX, IDC_DRIVERIDTEXT, m_EchoID);
}

BOOL Cadd_Driver::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_HSliderWeight.SetRange(0, maxSlideValue, TRUE);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(Cadd_Driver, CDialogEx)
	ON_EN_CHANGE(IDC_ET_WEIGHTEDIT, &Cadd_Driver::OnEnChangeEtWeightedit)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Cadd_Driver message handlers


void Cadd_Driver::OnEnChangeEtWeightedit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// Check if what's entered is a number between 0 and 1
	// and set it as the value
	if (scrolling == false) { // check if not scrolling
		CString readValue;
		ScaleRead.GetWindowText(readValue);
		m_WeightScale = _wtof(readValue);
		if (m_WeightScale >= 0 && m_WeightScale <= 1) {
			m_HSliderWeight.SetPos(m_WeightScale*maxSlideValue);
		}
	}
}


void Cadd_Driver::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == (CScrollBar *)&m_HSliderWeight) {
		scrolling = true;
		int value = m_HSliderWeight.GetPos();
		double scrollValue = value / (double) maxSlideValue;
		CString echoScroll;
		echoScroll.Format(_T("%f"), scrollValue);
		ScaleRead.SetWindowText(echoScroll);
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
		scrolling = false;
	}
}
