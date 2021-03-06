#pragma once
#include "LStrArray.h"

class LCSV
{
public:
	LCSV(void);
	LCSV(const LCSV& obj);
	~LCSV(void);

	LCSV&	operator = ( const LCSV& obj );

	 CArray <LStrArray, LStrArray&>	m_SA;
	 LStrArray			m_SANone;

	 void		RemoveAll();
	 int		GetCount();
	 LStrArray	GetSA( int idx ) const;
	 void		DelSA( int idx );
	 void		InsSA( int idx, LStrArray sa );
	 void		UpSA( int idx );
	 void		DownSA( int idx );
	 int		FindSA( LPCTSTR str, int col=0, bool fNoCase=true );

	 int	AddLine( CString line );
	 bool	Load( LPCTSTR path, LPCTSTR encode=_T("UTF-8") );
	 bool	Save( LPCTSTR path, LPCTSTR encode=_T("UTF-8") );

	 void	DebugView();
};

                                                                                                                                                                                                                                                                                                                                                                                                                                           