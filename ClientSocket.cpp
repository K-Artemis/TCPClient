// ClientSocket.cpp : 구현 파일입니다.
#include "stdafx.h"
#include "echoClient.h"
#include "ClientSocket.h"

// CClientSocket
CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}

// CClientSocket 멤버 함수
void CClientSocket::SetWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

void CClientSocket::OnReceive(int nErrorCode)
{
    TCHAR szBuffer[1024];
    ZeroMemory(szBuffer, sizeof(szBuffer));

    int nReceived = Receive(szBuffer, sizeof(szBuffer) - 1);
    if(nReceived > 0) 
    {
        szBuffer[nReceived] = _T('\0');
        SendMessage(m_hWnd, WM_CLIENT_RECV, 0,(LPARAM)szBuffer);
    }
    CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR:Disconnected from server!"));
	PostQuitMessage(0);
}

BOOL CClientSocket::SendMessageToServer(const CString& message)
{
    int len = message.GetLength() * sizeof(TCHAR);
    int sent = Send((LPCTSTR)message, len);
    if (sent == SOCKET_ERROR)
        return FALSE;
    return TRUE;
}