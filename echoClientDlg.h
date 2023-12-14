
// echoClientDlg.h : 헤더 파일
#pragma once
#include "afxwin.h"
#include "ClientSocket.h"

#define WM_CLIENT_RECV WM_USER+1

// CechoClientDlg 대화 상자
class CechoClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CechoClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ECHOCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CClientSocket m_ClientSocket;

public:
	CListBox m_list_msg;									// IDC_LIST_MSG
	CEdit m_edit_send;										// IDC_EDIT_SEND
	afx_msg void OnBnClickedBtnSend();						// IDC_BTN_SEND

protected:
	afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam);
};
