
// MFCApplication6Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMFCApplication6Dlg dialog
class CMFCApplication6Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication6Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCAPPLICATION6_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit op1;
	CEdit op2;
	CEdit op3;
	int and;
	int or;
	int xor;
	CButton shift;
	CComboBox shiftype;
	CButton compute;
	CListBox list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	int radiobuttons;
};
