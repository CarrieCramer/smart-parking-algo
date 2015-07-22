
// smart_parking_guiDlg.h : header file
//

#pragma once

#include "Grid.h"
#include "afxcmn.h"
#include <sstream>
class Grid;
// Csmart_parking_guiDlg dialog
class Csmart_parking_guiDlg : public CDialogEx
{
// Construction
public:
	Csmart_parking_guiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SMART_PARKING_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	Grid * world; // the world of the system
public:
	afx_msg void OnBnClickedBOpenConfig();
	afx_msg void OnBnClickedBSaveconfig();
	afx_msg void OnBnClickedBNextevent();
	int updateMs; // set update time
	void addDestination(Destination *);
	void addLot(Lot *);
	void addDriver(Driver *, int); // requires iteration
private:
	CString m_EchoSize;
	CString m_EchoTime;
	CString m_EchoStatus;
	double m_TimeDisplay;
	double m_GridSize;
	CString m_IterationEcho;
	CWnd * gridDrawSurface;
	CDC * gridDraw;
	CBrush * gridBrush;
	CPen * gridPen;
	CEdit* pEdit;
	bool destDrawn;
	bool lotDrawn;
	UINT_PTR m_nSimTimer; // timer used for autorun simulation
	std::string fileOpen; // name of the currently open file
	std::ostringstream oss; // used to display events
	void DrawGrid(); // draws the entire grid
	void displayText(); // displays text on status screen
public:
	afx_msg void OnBnClickedBNewdest();
	afx_msg void OnBnClickedBNewlot();
	afx_msg void OnBnClickedBNewdriver();
	afx_msg void OnBnClickedBSimend();
	afx_msg void OnBnClickedBShowstatus();
	CSliderCtrl m_VSliderIteration;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBSimpause();
	int m_RadioTextDisplay;
	afx_msg void OnBnClickedRadio();
};
