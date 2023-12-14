
// echoClientDlg.h : ��� ����
#pragma once
#include "afxwin.h"
#include "ClientSocket.h"

#define WM_CLIENT_RECV WM_USER+1

// CechoClientDlg ��ȭ ����
class CechoClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CechoClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ECHOCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
