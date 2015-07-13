#pragma once
#include "Driver.h"
#include "afxcmn.h"
#include "afxwin.h"

// Cadd_Driver dialog

class Cadd_Driver : public CDialogEx
{
	DECLARE_DYNAMIC(Cadd_Driver)

public:
	Cadd_Driver(int, CWnd* pParent = NULL);   // standard constructor
	virtual ~Cadd_Driver();

// Dialog Data
	enum { IDD = IDD_DRIVER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_DestID;
	double m_LocX;
	CString m_LocY;
private:
	CSliderCtrl m_HSliderWeight;
	CEdit m_WeightSeen;
public:
	// should be changeable by the slider later
	double m_WeightScale;
};
