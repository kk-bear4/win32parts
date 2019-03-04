// win32parts2.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "win32parts2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一のアプリケーション オブジェクトです。

CWinApp theApp;

using namespace std;

#include <locale.h>
#include <stdio.h>
#include "LCSV.h"
#define	SAMPLECSV	_T("..\\testdata\\sample.csv")

bool	test_LCSV()
{
	int			i, j;
	LStrArray	sa;
	LCSV		csv;

	if( ! csv.Load( SAMPLECSV )){
		_ftprintf( stderr, _T("ERROR in LCSV::Load()\n") );
		return false;
	}
	_tprintf( _T("↓＊＊＊＊ %s ＊＊＊＊＊\n"), SAMPLECSV );
	for(i=0;i<csv.GetCount();i++){
		sa = csv.GetSA(i);
		for(j=0;j<sa.GetCount();j++){
			_tprintf( _T("%s[%s]"), (j==0)? _T(""):_T(", "), sa.GetStr(j) );
		}
		_tprintf( _T("\n") );
	}
	_tprintf( _T("↑＊＊＊＊ %s ＊＊＊＊＊\n"), SAMPLECSV );
	return true;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	_tsetlocale( LC_ALL, _T("Japanese"));

	if (hModule != NULL)
	{
		// MFC を初期化して、エラーの場合は結果を印刷します。
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 必要に応じてエラー コードを変更してください。
			_tprintf(_T("致命的なエラー: MFC の初期化ができませんでした。\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: アプリケーションの動作を記述するコードをここに挿入してください。
			test_LCSV();
			getchar();
		}
	}
	else
	{
		// TODO: 必要に応じてエラー コードを変更してください。
		_tprintf(_T("致命的なエラー: GetModuleHandle が失敗しました\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
