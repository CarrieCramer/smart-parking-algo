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
	, m_LocY(_T(""))
	, m_WeightScale(0)
{

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
	DDX_Control(pDX, IDC_ET_WEIGHTEDIT, m_WeightSeen);
	DDX_Text(pDX, IDC_EDIT1, m_WeightScale);
}


BEGIN_MESSAGE_MAP(Cadd_Driver, CDialogEx)
END_MESSAGE_MAP()


// Cadd_Driver message handlers
