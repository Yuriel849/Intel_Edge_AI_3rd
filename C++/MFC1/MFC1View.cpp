
// MFC1View.cpp: CMFC1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC1.h"
#endif

#include "MFC1Doc.h"
#include "MFC1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC1View

IMPLEMENT_DYNCREATE(CMFC1View, CView)

BEGIN_MESSAGE_MAP(CMFC1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFC1View 생성/소멸

CMFC1View::CMFC1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFC1View::~CMFC1View()
{
}

BOOL CMFC1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC1View 그리기

void CMFC1View::OnDraw(CDC* pDC)
{
	CMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	// 글꼴 설정 변경
	CFont cFont, * oldFont;
	//폰트를 만든다.
	cFont.CreateFont(24, 8,//v,h size
		0, 0,//angle
		FW_DONTCARE,//bold
		TRUE,//italic
		FALSE,//under line
		FALSE,//STRIKEOUT pulg
		DEFAULT_CHARSET,//CHAR SET
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH, _T("Consolas"));
	//oldFont backup
	oldFont = pDC->SelectObject(&cFont);
	

	CString test = _T("Hello MFC SDI GDI interface test.");
	pDC->TextOut(0, 0, test);

	//char temp[80];
	//sprintf_s(temp, "안녕하세요 MFC 테스트입니다.");
	////pDC->TextOut(0, 0, temp, strlen(temp)); // 구버전 O.K. 현재X
	//pDC->TextOut(0, 0, (LPCWSTR)temp, strlen(temp)); // 실행은 되나 글자는 깨짐... 문제를 우회하기 위해 CString으로 모든 문자열을 처리하도록
	//// CString 클래스는 MFC에서 자동으로 지원, 사용 가능; 따로 헤더파일 불러올 필요도 없음
	//// MFC에서 새롭게 만든 전용 클래스는 모두 "Class"라는 의미에서 대문자 'C'를 앞에 붙인다


	test.Format(_T("HORZRES(가로크기)=%d"),
		pDC->GetDeviceCaps(HORZRES));
	pDC->TextOut(0, 20, test);
	test.Format(_T("VERTRES(새로크기)=%d"),
		pDC->GetDeviceCaps(VERTRES));
	pDC->TextOut(0, 40, test);

	test = _T("DrawText Example");
	// set box area
	CRect rect = CRect(0, 60, 400, 100);
	// call DrawText function
	pDC->DrawText(test, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	test = _T("ExtTextOut Example");
	pDC->SetTextColor(RGB(0, 0, 255)); //foreground color is blue
	pDC->SetBkColor(RGB(255, 255, 0)); // background color is yellow
	pDC->ExtTextOut(0, 120, ETO_CLIPPED | ETO_OPAQUE, CRect(0, 120, 400, 200), test, NULL);

	// 탭 크기 배열
	int tabstop[4] = { 8,16,24,32 };
	test = _T("TabbedTextOut\t를\t이용한\t출력");
	//TabbedTextOut함수 사용
	pDC->TabbedTextOut(0, 100, test, 4, tabstop, 0);
	test = _T("ExtTextOut를 이용한 출력");
	//문자 출력색을 청색으로
	pDC->SetTextColor(RGB(0, 0, 255));
	//배경색을 노랑색으로
	pDC->SetBkColor(RGB(255, 255, 0));
	//ExtTextOut함수사용
	pDC->ExtTextOut(0, 120, ETO_CLIPPED | ETO_OPAQUE, CRect(0, 120, 400, 200),
		test, NULL);
	//oldFont를 다시 설정한다.
	pDC->SelectObject(oldFont); // restore oldFont
	//delete current font
	cFont.DeleteObject();

}


// CMFC1View 인쇄

BOOL CMFC1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC1View 진단

#ifdef _DEBUG
void CMFC1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC1Doc* CMFC1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC1Doc)));
	return (CMFC1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC1View 메시지 처리기
