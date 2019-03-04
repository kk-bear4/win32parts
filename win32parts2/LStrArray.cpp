#include "StdAfx.h"
#include "LStrArray.h"


LStrArray::LStrArray(void)
{
	m_StrNone = _T("");
}
LStrArray::LStrArray(const LStrArray& obj)
{
	if( &obj != this ){
		m_Str.Copy( obj.m_Str );
		m_StrNone = obj.m_StrNone;
	}
}
LStrArray::~LStrArray(void)
{
}

LStrArray&	LStrArray::operator = ( const LStrArray& obj )
{
	if( &obj != this ){
		m_Str.Copy( obj.m_Str );
		m_StrNone = obj.m_StrNone;
	}
	return *this;
}

void	LStrArray::RemoveAll()
{
	m_Str.RemoveAll();
}

int	LStrArray::GetCount()
{
	return m_Str.GetCount();
}

CString	LStrArray::GetStr( int idx ) const
{
	if( (idx < 0) || (idx >= m_Str.GetCount())){
		return m_StrNone;
	}
	return m_Str.GetAt( idx );
}

int		LStrArray::GetInt( int idx )
{
	CString	st = GetStr( idx );
	return _tstoi( st );
}
double	LStrArray::GetDouble( int idx )
{
	CString	st = GetStr( idx );
	return _tstof( st );
}

void	LStrArray::Chop( CString& line )
{
	int			i, idx, mlen;
	CString	ln = line;
	TCHAR	rmlist[ 3 ] = { _T('\n'), _T('\r'), _T('\0') };

	i=0;
	do{
		mlen = ln.GetLength();
		idx = ln.Find( rmlist[i] );
		if( idx != -1 ){
			ln = ln.Left( idx );
		}
	}while( rmlist[i++] != _T('\0') );
	
	mlen = ln.GetLength();
	line = ln;
}

int	LStrArray::AddLine( CString line )
 {
	int		i=0, idx, cnt = 0;
	CString	ln = line;
	CString	wd;
	bool	fNext = false;

	RemoveAll();
	Chop( ln );

	while( (! ln.IsEmpty()) || fNext ){
		idx = ln.Find( _T(',') );
		wd = _T("");
		if( idx != -1 ){
			if( idx > 0 ){
				wd = ln.Left( idx );
			}
			m_Str.Add( wd.Trim() );
			++cnt;

			ln = ln.Mid( idx+1, ln.GetLength() );
			fNext = true;

		}else{
			if( fNext ){
				m_Str.Add( ln.Trim() );
				++cnt;
			}
			ln = _T("");
			fNext = false;
		}
	}
	return cnt;
 }

CString	LStrArray::GetLine() const
{
	CString		ln = _T("");
	int			i;

	for(i=0;i<m_Str.GetCount();i++){
		if(i!=0){
			ln += _T(",");
		}
		ln += GetStr( i );
	}
	return ln;
}

 void	LStrArray::DebugView()
 {
	int	i;

	TRACE(_T("%d"), GetCount() );
	for(i=0;i<GetCount();i++){
		TRACE(_T(" [%s]"), GetStr( i ));
	}
	TRACE(_T("\n"));
 }
