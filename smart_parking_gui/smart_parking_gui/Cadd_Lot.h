#pragma once
#include "../../Lot.h"
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
private:
	int IDvalue;
	CString m_EchoLotID;
public:
	double m_BaseCost;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();	
};
