
// NFCReaderDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "NFCReader.h"
#include "NFCReaderDlg.h"
#include "afxdialogex.h"

//#include <windows.h>
#include <winscard.h>
//#include <stdio.h>
//#include <tchar.h>
//#include <assert.h>

#pragma comment (lib, "winscard.lib")

#define SAMPLE_TITLE		_T("GET DATA (UID)")
#define PCSC_RECV_BUFF_LEN	(262)

SCARD_IO_REQUEST *CardProtocol2PCI(DWORD dwProtocol)
{
	if (dwProtocol == SCARD_PROTOCOL_T0) {
		return (SCARD_IO_REQUEST *)SCARD_PCI_T0;
	} else if (dwProtocol == SCARD_PROTOCOL_T1) {
		return (SCARD_IO_REQUEST *)SCARD_PCI_T1;
	} else if (dwProtocol == SCARD_PROTOCOL_RAW) {
		return (SCARD_IO_REQUEST *)SCARD_PCI_RAW;
	} else if (dwProtocol == SCARD_PROTOCOL_UNDEFINED) {
		//assert(false);
		return NULL;
	}

	return (SCARD_IO_REQUEST *)SCARD_PCI_T1;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNFCReaderDlg �_�C�A���O




CNFCReaderDlg::CNFCReaderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNFCReaderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNFCReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNFCReaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_READ, &CNFCReaderDlg::OnBnClickedBtnRead)
END_MESSAGE_MAP()


// CNFCReaderDlg ���b�Z�[�W �n���h���[

BOOL CNFCReaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CNFCReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CNFCReaderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CNFCReaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNFCReaderDlg::OnBnClickedBtnRead()
{
	CEdit *ed=(CEdit*)GetDlgItem(IDC_ED_IDM);
	ed->SetWindowTextW(_T(""));

	SCARDCONTEXT	hContext = 0;
	LONG lResult = ::SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hContext);
	CString str;

	if (lResult != SCARD_S_SUCCESS) {
		if (lResult == SCARD_E_NO_SERVICE) {
			//_ftprintf_s(stdout, _T("Smart Card Servise is not Started.\n"));
			AfxMessageBox(_T("Smart Card Servise is not Started.\n"));
		} else {
			//_ftprintf_s(stdout, _T("SCardEstablishContext Error.\nErrorCode %08X\n"), lResult);
			AfxMessageBox(_T("SCardEstablishContext Error.\nErrorCode[]\n"));
		}
		//return EXIT_FAILURE;
		return;
	}

	LPTSTR	lpszReaderName = NULL;
	DWORD	dwAutoAllocate = SCARD_AUTOALLOCATE;
	TCHAR	*pszExpectedReaderName = _T("Sony FeliCa Port/PaSoRi 3.0");

	lResult = ::SCardListReaders(hContext, NULL, (LPTSTR)&lpszReaderName, &dwAutoAllocate);
//	str.Format(_T("code=%d"), lResult);
//	AfxMessageBox(str);
	if (lResult != SCARD_S_SUCCESS) {
		if (lResult == SCARD_E_NO_READERS_AVAILABLE)  {
			//_ftprintf_s(stdout, _T("Reader/Writer is not Found.\n"));
			str.Format(_T("Reader/Writer is not Found.\n"));
		} else {
			//_ftprintf_s(stdout, _T("Reader/Writer is not Found.\n"));_T("SCardListReaders Error.\nErrorCode %08X\n"), lResult);
			str.Format(_T("SCardListReaders Error.\nErrorCode %08X\n"), lResult);
		}
		AfxMessageBox(str);
		::SCardReleaseContext(hContext);
		//return EXIT_FAILURE;
		return;
	}
	if (_tcsncmp(pszExpectedReaderName, lpszReaderName, _tcslen(pszExpectedReaderName)) != 0) {
		//_ftprintf_s(stdout, _T("Reader/Writer is not Found.\n"));
		str.Format( _T("Reader/Writer is not Found.\n"));
		::SCardFreeMemory(hContext, lpszReaderName);
		::SCardReleaseContext(hContext);
		//return EXIT_FAILURE;		
		return;
	}

	// ****   Connect to NFC Carad   *******
	SCARDHANDLE	hCard = NULL;
	DWORD		dwActiveProtocol = 0;
	lResult = ::SCardConnect(hContext, lpszReaderName, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwActiveProtocol);
	if (lResult != SCARD_S_SUCCESS) {
		if (lResult == SCARD_W_REMOVED_CARD) {
			//_ftprintf_s(stdout, _T("Card is not Found.\n"));
			str.Format(_T("Card is not Found.\n"));
		} else {
			//_ftprintf_s(stdout, _T("SCardConnect Error.\nErrorCode %08X\n"), lResult);
			str.Format(_T("SCardConnect Error.\nErrorCode %08X\n"), lResult);
		}
		AfxMessageBox(str);
		::SCardFreeMemory(hContext, lpszReaderName);
		::SCardReleaseContext(hContext);
		//return EXIT_FAILURE;		
		return;
	}

	//  ******  IDm�ǂݍ���    *********
	BYTE	bSendCommand[] = {0xFF, 0xCA, 0x00, 0x00, 0x00};
	BYTE	bRecvBuf[PCSC_RECV_BUFF_LEN] = {0x00};
	DWORD	dwResponseSize = sizeof(bRecvBuf);
	lResult = ::SCardTransmit(hCard, CardProtocol2PCI(dwActiveProtocol), bSendCommand, sizeof(bSendCommand), NULL, bRecvBuf, &dwResponseSize);
	if (lResult != SCARD_S_SUCCESS) {
		//_ftprintf_s(stdout, _T("SCardTransmit Error.\nErrorCode %08X\n"), lResult);
		str.Format(_T("SCardTransmit Error.\nErrorCode %08X\n"), lResult);
		AfxMessageBox(str);
		::SCardDisconnect(hCard, SCARD_LEAVE_CARD);	
		::SCardFreeMemory(hContext, lpszReaderName);
		::SCardReleaseContext(hContext);
		//return EXIT_FAILURE;
		return;
	}
	CString tmp;
	str.Format(_T(""));
	for (UINT uiRespIdx = 0; uiRespIdx < dwResponseSize; uiRespIdx ++) {
		//_ftprintf_s(stdout, _T("%02X"), bRecvBuf[uiRespIdx]);
		tmp.Format(_T("%02X"), bRecvBuf[uiRespIdx]);
		str += tmp;
		//str.SetAt(uiRespIdx, str.GetString());
		/*if ((uiRespIdx + 1) >= dwResponseSize) {
			_ftprintf_s(stdout, _T("\n"));
		} else {
			_ftprintf_s(stdout, _T(" "));
		}*/
	}
	//AfxMessageBox(str);
	ed->SetWindowText(str);

	::SCardDisconnect(hCard, SCARD_LEAVE_CARD);	
	::SCardFreeMemory(hContext, lpszReaderName);
	::SCardReleaseContext(hContext);



}
