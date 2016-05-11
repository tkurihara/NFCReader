
// NFCReader.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CNFCReaderApp:
// このクラスの実装については、NFCReader.cpp を参照してください。
//

class CNFCReaderApp : public CWinApp
{
public:
	CNFCReaderApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CNFCReaderApp theApp;