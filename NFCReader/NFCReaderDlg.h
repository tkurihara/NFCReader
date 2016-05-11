
// NFCReaderDlg.h : ヘッダー ファイル
//

#pragma once


// CNFCReaderDlg ダイアログ
class CNFCReaderDlg : public CDialogEx
{
// コンストラクション
public:
	CNFCReaderDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_NFCREADER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRead();
	afx_msg void OnBnClickedBtnReadblock();
};
