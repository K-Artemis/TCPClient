
// echoClientDlg.cpp : 구현 파일
#include "stdafx.h"
#include "echoClient.h"
#include "echoClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PORT 9999

// CechoClientDlg 대화 상자
CechoClientDlg::CechoClientDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CechoClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CechoClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);
	DDX_Control(pDX, IDC_EDIT_SEND, m_edit_send);
}

BEGIN_MESSAGE_MAP(CechoClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CechoClientDlg::OnBnClickedBtnSend)
	ON_MESSAGE(WM_CLIENT_RECV, &CechoClientDlg::OnClientRecv)
END_MESSAGE_MAP()


// CechoClientDlg 메시지 처리기
BOOL CechoClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ClientSocket.SetWnd(this->m_hWnd);
	m_ClientSocket.Create();
	if(m_ClientSocket.Connect(_T("127.0.0.1"), PORT) == FALSE) 
	{
		AfxMessageBox(_T("ERROR : Failed to connect Server"));
		PostQuitMessage(0);
		return FALSE;
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CechoClientDlg::OnPaint()
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

HCURSOR CechoClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CechoClientDlg::OnBnClickedBtnSend()
{
    CString str;
    m_edit_send.GetWindowText(str); // 텍스트 가져오기

    if (!str.IsEmpty())
	{
        if (m_ClientSocket.SendMessageToServer(str))
            m_list_msg.AddString(str); // 리스트 박스에 메시지 추가
		else
            AfxMessageBox(_T("서버로 메시지 전송 실패"));
    }
    m_edit_send.SetWindowText(_T("")); // 입력 필드 초기화
}

afx_msg LRESULT CechoClientDlg::OnClientRecv(WPARAM wParam, LPARAM lParam)
{
    CString str = (LPCTSTR)lParam;
    m_list_msg.AddString(str); // 서버로부터 받은 메시지를 리스트 박스(IDC_LIST_MSG)에 추가
	
	// 응답을 서버로 다시 보내기
	CString response = _T("Response to server: ") + str;
    m_ClientSocket.SendMessageToServer(response);

    return 0;
}