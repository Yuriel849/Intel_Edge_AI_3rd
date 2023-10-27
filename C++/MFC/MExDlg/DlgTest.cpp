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
	, m_strEdit(_T("Hello world! ...from constructor"))
{

}

CDlgTest::~CDlgTest()
{
}

void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_bCheckButton);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit);
}


BEGIN_MESSAGE_MAP(CDlgTest, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CDlgTest::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgTest::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgTest::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgTest::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CDlgTest::OnEnChangeEdit1)
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


void CDlgTest::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL CDlgTest::OnInitDialog()
{
	// TODO: 여기에 구현 코드 추가.
	CDialog::OnInitDialog();
	m_strEdit = _T("HELLO WORLD! ...from OnInitDialog()");
	UpdateData(FALSE);

	return true;
}
