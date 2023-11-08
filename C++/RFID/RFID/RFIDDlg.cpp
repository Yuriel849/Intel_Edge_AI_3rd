
// RFIDDlg.cpp: 구현 파일
//
#include "is_d2xx.h"
#include "pch.h"
#include "framework.h"
#include "RFID.h"
#include "RFIDDlg.h"
#include "afxdialogex.h"

#include <codecvt>
#include <iostream> 
#include <locale> 
#include <string> 
#include <windows.h>

#include "DataSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRFIDDlg 대화 상자



CRFIDDlg::CRFIDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RFID_DIALOG, pParent)
	, m_strRfid(_T(""))
	, m_strEntryDate(_T(""))
	, m_strDateTime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CRFIDDlg::~CRFIDDlg()
{
	OnDisconnect();
}

void CRFIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strRfid);
	DDX_Control(pDX, IDC_PIC, m_picControl);
	DDX_Text(pDX, IDC_EDIT2, m_strDateTime);
}

BEGIN_MESSAGE_MAP(CRFIDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CRFIDDlg::OnConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CRFIDDlg::OnDisconnect)
	ON_BN_CLICKED(IDC_BUTTON3, &CRFIDDlg::OnReadOnce)
	ON_BN_CLICKED(IDC_BUTTON4, &CRFIDDlg::OnReadContinue)
	ON_BN_CLICKED(IDC_BUTTON5, &CRFIDDlg::OnQuery)
	ON_BN_CLICKED(IDC_BUTTON6, &CRFIDDlg::OnDelete)
END_MESSAGE_MAP()


// CRFIDDlg 메시지 처리기

BOOL CRFIDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRFIDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRFIDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRFIDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// "RFID연결" 버튼 클릭 시
void CRFIDDlg::OnConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//열린 포트번호 찾기
	if (is_GetDeviceNumber(&usbnumber) == IS_OK)
	{
		printf("FTDI USB To Serial 연결된 개수 : %d\n", usbnumber);
		if (is_GetSerialNumber(0, readSerialNumber) == IS_OK)
		{
			if (memcmp(changeSerialNumber, readSerialNumber, sizeof(changeSerialNumber) != 0))
			{
				if (is_SetSerialNumber(0, changeSerialNumber) == IS_OK)
				{
					printf(" USB To Serial Number 를 변경 하였습니다.\n");
					printf(" FTDI SerialNumber :  %s \n", changeSerialNumber);
				}
			}
			else
				printf(" FTDI SerialNumber :  %s \n", changeSerialNumber);
		}
	}

	//열린 포트번호로 연결
	unsigned long portNumber;
	if (is_GetCOMPort_NoConnect(0, &portNumber) == IS_OK)
	{
		printf("COM Port : %d\n", portNumber);
	}
	if (is_OpenSerialNumber(&ftHandle, readSerialNumber, 115200) != IS_OK)
	{
		printf("USB To Serial과 통신 연결 실패\n");
		//return -1;
	}
	else {
		printf("Serial포트 %d와 통신 연결성공!! \n", portNumber);
	}
	Sleep(100);
	flag_r = 0;
}

// "RFID해제" 버튼 클릭 시
void CRFIDDlg::OnDisconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// 무선파워를 끊어요.
	is_RfOff(ftHandle);
	//USB 포트를 Close
	if (is_Close(ftHandle) == IS_OK)
	{
		printf("연결을 닫습니다. ");
	}
}

// "등록" 버튼 클릭 시
void CRFIDDlg::OnReadContinue()
{
	DataSource ds;

	CString temp, temp1 = _T("");

	if (is_WriteReadCommand(ftHandle, CM1_ISO15693, CM2_ISO15693_ACTIVE + BUZZER_ON,
		writeLength, wirteData, &readLength, readData) == IS_OK)
	{
		int i;
		printf("UID : ");
		for (i = 0; i < readLength; i++)
		{
			// print to console
			printf("%02x ", readData[i]);

			// save to print to dialog
			temp.Format(_T("%02x "), readData[i]);
			temp1 += temp;
		}
		printf("\n");

		// Create a converter object to convert between wide strings and UTF-8 encoded strings 
		wstring_convert<codecvt_utf8_utf16<wchar_t> > converter;
		// Convert the LPCWSTR to a wstring and then to an std::string 
		string uid = converter.to_bytes(wstring(temp1));
		if (!ds.exists(uid)) // 등록되지 않은 사용자라면
		{
			UpdateData(TRUE);
			string src = "./res/user_" + uid + ".png";
			ds.addUser(uid, src);
		}
	}
}

// "출입" 버튼 클릭 시
void CRFIDDlg::OnReadOnce()
{
	DataSource ds;

	CString temp, temp1=_T("");
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//ISO15693모드로 읽기( 싱글모드 읽기 )
	if (is_WriteReadCommand(ftHandle, CM1_ISO15693, CM2_ISO15693_ACTIVE + BUZZER_ON,
			writeLength, wirteData, &readLength, readData) == IS_OK)
	{
		int i;
		printf("ISO 15693 UID : ");
		for (i = 0; i < readLength; i++)
		{
			// print to console
			printf("%02x ", readData[i]);

			// save to print to dialog
			temp.Format(_T("%02x "), readData[i]);
			temp1 += temp;
		}
		// print to text box "m_strRfid" in dialog
		m_strRfid = temp1;
		UpdateData(FALSE);
		
		printf("\n");

		// Create a converter object to convert between wide strings and UTF-8 encoded strings 
		wstring_convert<codecvt_utf8_utf16<wchar_t> > converter;
		// Convert the LPCWSTR to a wstring and then to an std::string 
		string uid = converter.to_bytes(wstring(temp1));

		if (ds.exists(uid) && ds.isActive(uid)) // 등록된 사용자라면
		{
			ds.setEntry(uid);
			string src = ds.findImg(uid);

			// Convert std::string 'src' to wchar_t* (alternative to _T())
			wstring wsrc;
			for (int i = 0; i < src.length(); ++i)
				wsrc += wchar_t(src[i]);
			const wchar_t* wtsrc = wsrc.c_str();

			// Display image
			CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
			m_picControl.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
			CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
			dc = m_picControl.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
			CImage image;//불러오고 싶은 이미지를 로드할 CImage 
			image.Load(wtsrc);//이미지 로드

			image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);//이미지를 픽쳐 컨트롤 크기로 조정
			ReleaseDC(dc);//DC 해제
		}
	}
}

// "삭제" 버튼 클릭 시
void CRFIDDlg::OnDelete()
{
	DataSource ds;

	CString temp, temp1 = _T("");
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//ISO15693모드로 읽기( 싱글모드 읽기 )
	if (is_WriteReadCommand(ftHandle, CM1_ISO15693, CM2_ISO15693_ACTIVE + BUZZER_ON,
		writeLength, wirteData, &readLength, readData) == IS_OK)
	{
		int i;
		printf("ISO 15693 UID : ");
		for (i = 0; i < readLength; i++)
		{
			// print to console
			printf("%02x ", readData[i]);

			// save to print to dialog
			temp.Format(_T("%02x "), readData[i]);
			temp1 += temp;
		}
		// print to text box "m_strRfid" in dialog
		m_strRfid = temp1;
		UpdateData(FALSE);

		printf("\n");

		// Create a converter object to convert between wide strings and UTF-8 encoded strings 
		wstring_convert<codecvt_utf8_utf16<wchar_t> > converter;
		// Convert the LPCWSTR to a wstring and then to an std::string 
		string uid = converter.to_bytes(wstring(temp1));

		if (ds.exists(uid)) // 등록된 사용자라면
		{
			ds.deactivate(uid);
			m_strRfid = CString(_T("This card is no longer active"));
		}
	}
}


void CRFIDDlg::OnQuery()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::cout << "Queried" << std::endl;
}
