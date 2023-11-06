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
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	DDX_Control(pDX, IDC_SLIDER1, m_Slidectrl);
	DDX_Control(pDX, IDC_SLIDER2, m_Slidectrl1);
	DDX_Control(pDX, IDC_SLIDER3, m_Slidectrl2);
	DDX_Control(pDX, IDC_PIC, m_picControl);
}


BEGIN_MESSAGE_MAP(CDlgTest, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CDlgTest::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgTest::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgTest::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgTest::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CDlgTest::OnEnChangeEdit1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDlgTest::OnLbnSelchangeList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgTest::OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CDlgTest::OnNMCustomdrawSlider1)
	ON_EN_CHANGE(IDC_EDIT2, &CDlgTest::OnEnChangeEdit2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CDlgTest::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CDlgTest::OnNMCustomdrawSlider3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgTest::OnBnClickedButton2)
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

	CString data;
	for (int i = 1; i < 11; i++)
	{
		data.Format(_T("List data%d"), i);
		m_ListBox.AddString(data);
		data.Format(_T("Combo data%d"), i);
		m_ComboBox.AddString(data);
	}

	m_Slidectrl.SetRange(2000, 2300, TRUE);
	m_Slidectrl.SetPos(2023);

	m_Slidectrl1.SetRange(1, 12, TRUE);
	m_Slidectrl1.SetPos(1);

	m_Slidectrl2.SetRange(1, 31, TRUE);
	m_Slidectrl2.SetPos(1);

	return true;
}


void CDlgTest::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int num = m_ListBox.GetCurSel(); // Search the current position
	CString data;
	m_ListBox.GetText(num, data); // Get character at select position
	AfxMessageBox(data); // Output message box
}


void CDlgTest::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int num = m_ComboBox.GetCurSel(); // Search the current position
	CString data;
	m_ComboBox.GetLBText(num, data); // Get character at select position
	AfxMessageBox(data); // Output message box
}


void CDlgTest::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int position;
	position = m_Slidectrl.GetPos();
	SetDlgItemInt(IDC_EDIT2, position);

	*pResult = 0;
}


void CDlgTest::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgTest::OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int position;
	position = m_Slidectrl1.GetPos();
	SetDlgItemInt(IDC_EDIT3, position);

	*pResult = 0;
}


void CDlgTest::OnNMCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int position;
	position = m_Slidectrl2.GetPos();
	SetDlgItemInt(IDC_EDIT4, position);

	*pResult = 0;
}


void CDlgTest::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_picControl.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_picControl.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	CImage image;//불러오고 싶은 이미지를 로드할 CImage 
	image.Load(_T("./res/GitBashIcon.png"));//이미지 로드

	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
	ReleaseDC(dc);//DC 해제
}
