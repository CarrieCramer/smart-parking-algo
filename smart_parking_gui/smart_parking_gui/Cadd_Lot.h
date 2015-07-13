#pragma once
#include "Lot.h"
#include "afxcmn.h"

// Cadd_Lot dialog

class Cadd_Lot : public CDialogEx
{
	DECLARE_DYNAMIC(Cadd_Lot)

public:
	Cadd_Lot(int, CWnd* pParent = NULL);   // standard constructor
	virtual ~Cadd_Lot();

// Dialog Data
	enum { IDD = IDD_LOT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_LocationX;
	double m_LocationY;
	int m_ParkSpaceCount;
	int pricingPolicy;
private:
	// currently 6 pricing policies
	CSliderCtrl m_HSliderPolicy;
	CString m_EchoPolicyDesc;
	int IDvalue;
public:
	double m_BaseCost;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
private:
	CString m_EchoLotID;
};
