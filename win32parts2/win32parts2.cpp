// win32parts2.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "win32parts2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �B��̃A�v���P�[�V���� �I�u�W�F�N�g�ł��B

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
	_tprintf( _T("���������� %s ����������\n"), SAMPLECSV );
	for(i=0;i<csv.GetCount();i++){
		sa = csv.GetSA(i);
		for(j=0;j<sa.GetCount();j++){
			_tprintf( _T("%s[%s]"), (j==0)? _T(""):_T(", "), sa.GetStr(j) );
		}
		_tprintf( _T("\n") );
	}
	_tprintf( _T("���������� %s ����������\n"), SAMPLECSV );
	return true;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	_tsetlocale( LC_ALL, _T("Japanese"));

	if (hModule != NULL)
	{
		// MFC �����������āA�G���[�̏ꍇ�͌��ʂ�������܂��B
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: �K�v�ɉ����ăG���[ �R�[�h��ύX���Ă��������B
			_tprintf(_T("�v���I�ȃG���[: MFC �̏��������ł��܂���ł����B\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �A�v���P�[�V�����̓�����L�q����R�[�h�������ɑ}�����Ă��������B
			test_LCSV();
			getchar();
		}
	}
	else
	{
		// TODO: �K�v�ɉ����ăG���[ �R�[�h��ύX���Ă��������B
		_tprintf(_T("�v���I�ȃG���[: GetModuleHandle �����s���܂���\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
