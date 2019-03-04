#pragma once
class LStrArray
{
public:
	LStrArray(void);
	LStrArray(const LStrArray& obj);
	~LStrArray(void);

	LStrArray&	operator = ( const LStrArray& obj );

	 CArray <CString>	m_Str;
	 CString			m_StrNone;

	 void		RemoveAll();
	 int		GetCount();
	 CString	GetStr( int idx ) const;
	 int		GetInt( int idx );
	 double		GetDouble( int idx );

	 int	AddLine( CString line );
	 void	Chop( CString& line );
	 CString	GetLine() const;

	 void	DebugView();
};

