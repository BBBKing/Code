// ProcessWndChangDataDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AntiSpy.h"
#include "ProcessWndChangDataDlg.h"
#include "afxdialogex.h"


// CProcessWndChangDataDlg �Ի���

IMPLEMENT_DYNAMIC(CProcessWndChangDataDlg, CDialog)

CProcessWndChangDataDlg::CProcessWndChangDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessWndChangDataDlg::IDD, pParent)
	, m_Edit(_T(""))
{

}

CProcessWndChangDataDlg::~CProcessWndChangDataDlg()
{
}

void CProcessWndChangDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DATA, m_Edit);
}


BEGIN_MESSAGE_MAP(CProcessWndChangDataDlg, CDialog)
END_MESSAGE_MAP()


// CProcessWndChangDataDlg ��Ϣ�������
