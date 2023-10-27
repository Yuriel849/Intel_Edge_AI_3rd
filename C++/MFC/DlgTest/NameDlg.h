#pragma once
#include "afxdialogex.h"


// CNameDlg 대화 상자

class CNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNameDlg)

public:
	CNameDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNameDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CString m_strName;
	int m_nAge;
	afx_msg void OnBnClickedCheck1();
	BOOL m_bLicense;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio8();
//	int m_njob;
	int m_nFloor;
	int m_nJob;
};
