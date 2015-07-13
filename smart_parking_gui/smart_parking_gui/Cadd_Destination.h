#pragma once
#include "Destination.h"

// Cadd_Destination dialog

class Cadd_Destination : public CDialogEx
{
	DECLARE_DYNAMIC(Cadd_Destination)

public:
	Cadd_Destination(int destID, CWnd* pParent = NULL);   // standard constructor
	virtual ~Cadd_Destination();

// Dialog Data
	enum { IDD = IDD_DESTINATION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int destID;
	CWnd * mainDialog;
	CString m_EchoDestId;
public:
	afx_msg void OnBnClickedOk();
	double m_LocationX;
	double m_LocationY;
};
