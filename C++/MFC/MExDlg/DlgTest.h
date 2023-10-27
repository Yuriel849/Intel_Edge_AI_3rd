#pragma once
#include "afxdialogex.h"


// CDlgTest 대화 상자

class CDlgTest : public CDialog
{
	DECLARE_DYNAMIC(CDlgTest)

public:
	CDlgTest(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgTest();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIGTEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	BOOL m_bCheckButton;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMThemeChangedScrollbar1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnNMThemeChangedScrollbar2(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_strEdit;
	BOOL OnInitDialog();
};
