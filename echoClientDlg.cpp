
// echoClientDlg.cpp : ���� ����
#include "stdafx.h"
#include "echoClient.h"
#include "echoClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PORT 9999

// CechoClientDlg ��ȭ ����
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


// CechoClientDlg �޽��� ó����
BOOL CechoClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ClientSocket.SetWnd(this->m_hWnd);
	m_ClientSocket.Create();
	if(m_ClientSocket.Connect(_T("127.0.0.1"), PORT) == FALSE) 
	{
		AfxMessageBox(_T("ERROR : Failed to connect Server"));
		PostQuitMessage(0);
		return FALSE;
	}

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CechoClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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
    m_edit_send.GetWindowText(str); // �ؽ�Ʈ ��������

    if (!str.IsEmpty())
	{
        if (m_ClientSocket.SendMessageToServer(str))
            m_list_msg.AddString(str); // ����Ʈ �ڽ��� �޽��� �߰�
		else
            AfxMessageBox(_T("������ �޽��� ���� ����"));
    }
    m_edit_send.SetWindowText(_T("")); // �Է� �ʵ� �ʱ�ȭ
}

afx_msg LRESULT CechoClientDlg::OnClientRecv(WPARAM wParam, LPARAM lParam)
{
    CString str = (LPCTSTR)lParam;
    m_list_msg.AddString(str); // �����κ��� ���� �޽����� ����Ʈ �ڽ�(IDC_LIST_MSG)�� �߰�
	
	// ������ ������ �ٽ� ������
	CString response = _T("Response to server: ") + str;
    m_ClientSocket.SendMessageToServer(response);

    return 0;
}