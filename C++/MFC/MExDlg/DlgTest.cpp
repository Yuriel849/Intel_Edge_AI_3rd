// DlgTest.cpp: 구현 파일
//

#include "pch.h"
#include "MExDlg.h"
#include "afxdialogex.h"
#include "DlgTest.h"


// CDlgTest 대화 상자

IMPLEMENT_DYNAMIC(CDlgTest, CDialog)

CDlgTest::CDlgTest(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIGTEST, pParent)
	, m_bCheckButton(FALSE)
{

}

CDlgTest::~CDlgTest()
{
}

void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_bCheckButton);
}


BEGIN_MESSAGE_MAP(CDlgTest, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CDlgTest::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgTest::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgTest::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgTest::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgTest 메시지 처리기


void CDlgTest::OnBnClickedRadio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Radio button 1 press"));
}


void CDlgTest::OnBnClickedRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Radio button 2 press"));
}


void CDlgTest::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString message;
	message.Format(_T("Check button press value : %d"), m_bCheckButton);
	AfxMessageBox(message);
}


void CDlgTest::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Button 1 press"));
}
