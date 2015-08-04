#pragma once

#include "../../generate_config/generate_config.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <random> // random_engine
// Cgenerate_config dialog

class Cgenerate_config : public CDialogEx
{
	DECLARE_DYNAMIC(Cgenerate_config)

public:
	Cgenerate_config(CWnd* pParent = NULL);   // standard constructor
	virtual ~Cgenerate_config();

// Dialog Data
	enum { IDD = IDD_GENERATEFILE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	default_random_engine engine;
	DECLARE_MESSAGE_MAP()
public:
	// Contains between 0 and 100 iterations
	int m_ItNumber;
	double m_GridSize;
	int m_SimuHours;
	int m_AvgDemand;
	int m_LotCount;
	int m_DestCount;
	int pricingPolicy;
	double m_utilRate;
	double m_occuRate;
	CString newConfigFileName;
private:
	CSliderCtrl m_SliderPolicy;
	CEdit m_EchoDescription;
public:
	double m_LotPrice;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBBrowse();
	CEdit FileTitleBox;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	
	virtual BOOL OnInitDialog();
	BOOL m_RandDestProbs;
};
