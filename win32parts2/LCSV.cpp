#include "StdAfx.h"
#include "LCSV.h"


LCSV::LCSV(void)
{
	m_SANone.RemoveAll();
}

LCSV::LCSV(const LCSV& obj)
{
	if( &obj != this ){
		m_SA.Copy( obj.m_SA );
		m_SANone = obj.m_SANone;
	}
}

LCSV::~LCSV(void)
{
}

LCSV&	LCSV::operator = ( const LCSV& obj )
{
	if( &obj != this ){
		m_SA.Copy( obj.m_SA );
		m_SANone = obj.m_SANone;
	}
	return *this;
}

void	LCSV::RemoveAll()
{
	m_SA.RemoveAll();
}
int		LCSV::GetCount()
{
	return m_SA.GetCount();
}
LStrArray	LCSV::GetSA( int idx ) const
{
	if( (idx < 0) || (idx >= m_SA.GetCount())){
		return m_SANone;
	}
	return m_SA.GetAt( idx );
}

int	LCSV::AddLine( CString line )
{
	int			cnt;
	LStrArray	sa;

	cnt = sa.AddLine( line );
	if( cnt > 0 ){
		m_SA.Add( sa );
	}
	return cnt;
}

void	LCSV::DelSA( int idx )
{
	if( idx < m_SA.GetCount() && idx >= 0 ){
		m_SA.RemoveAt( idx );
	}
}
void	LCSV::InsSA( int idx, LStrArray sa )
{
	if( idx < 0 ){
		return;
	}
	if( idx < m_SA.GetCount() ){
		m_SA.InsertAt( idx, sa );
	}else{
		m_SA.Add( sa );
	}
}
void	LCSV::UpSA( int idx )
{
	if( idx <= 0 ){
		return;
	}
	if( idx < m_SA.GetCount() ){
		LStrArray	sa;
		sa = m_SA.GetAt( idx );
		m_SA.RemoveAt( idx );
		m_SA.InsertAt( idx-1, sa );
	}
}
void	LCSV::DownSA( int idx )
{
	if( idx < 0 || (idx >= (m_SA.GetCount()-1)) ){
		return;
	}
	LStrArray	sa;
	sa = m_SA.GetAt( idx );
	m_SA.RemoveAt( idx );
	m_SA.InsertAt( idx+1, sa );
}

int		LCSV::FindSA( LPCTSTR str, int col, bool fNoCase)
{
	CString		st;
	LStrArray	sa;
	int		i, idx = -1;

	for(i=0;i<m_SA.GetCount();i++){
		sa = m_SA.GetAt(i);
		if( col < sa.GetCount() ){
			st = sa.GetStr(col);
			if( fNoCase ){
				if( st.CompareNoCase( str ) == 0 ){
					idx = i;
					break;
				}
			}else{
				if( st.Compare( str ) == 0 ){
					idx = i;
					break;
				}
			}
		}
	}
	return idx;
}

bool	LCSV::Load( LPCTSTR path, LPCTSTR encode )
{
	CString		ln, opt;
	FILE		*fp;
	char		tbuf[ 2048 ];
	int			ef = 0;

	if( encode != NULL ){
		opt.Format(_T("r,ccs=%s"), encode );

		if( _tfopen_s( &fp, path, opt ) ){
			return false;
		}
		CStdioFile sf( fp );
		RemoveAll();
		while( sf.ReadString( ln ) ){
			AddLine( ln );
		}
		return true;
	}

	if( _tfopen_s( &fp, path, _T("rt") ) ){
		return false;
	}
	RemoveAll();
	while( ! ef ){	
		fgets( tbuf, sizeof(tbuf), fp );
		ef = feof( fp );
		if( ! ef ){
			ln = tbuf;
			AddLine( ln );
		}
	}
	fclose( fp );
	return true;
}

bool	LCSV::Save( LPCTSTR path, LPCTSTR encode )
{
	CString		ln, opt;
	int			i;
	FILE		*fp;

	if( encode == NULL ){
		opt = _T("wt");
	}else{
		opt.Format(_T("w,ccs=%s"), encode );
	}
	if( _tfopen_s( &fp, path, opt ) ){
		return false;
	}
	if( encode == NULL ){
		CStringA	lnA;
		for(i=0;i<GetCount();i++){
			ln = GetSA( i ).GetLine();
			lnA = ln; // UNICODE -> ANSI
			lnA += "\n";
			fwrite( lnA, 1, lnA.GetLength(), fp );
		}
		fclose( fp );

	}else{
		CStdioFile sf( fp );
		for(i=0;i<GetCount();i++){
			ln = GetSA( i ).GetLine();
			ln += _T("\n");
			sf.WriteString( ln );
		}
		sf.Close();
	}
	return true;
}
void	LCSV::DebugView()
{
	int	i;

	TRACE(_T("*** %d ***\n"), GetCount() );
	for(i=0;i<GetCount();i++){
		GetSA( i ).DebugView();
	}
}
