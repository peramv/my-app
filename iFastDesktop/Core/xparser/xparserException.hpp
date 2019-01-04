#pragma once


// Import/Export resolution
#undef XPARSER_LINKAGE
#ifdef XPARSER_DLL
   #define XPARSER_LINKAGE CLASS_EXPORT
#else
   #define XPARSER_LINKAGE CLASS_IMPORT
#endif

//Forward declaration
class XPARSER_LINKAGE XparserException : public std::exception
{
protected:
   long      _errorCode;
   DString   _errorMessage;
   DString   _errortype;
public:
   XparserException();
   XparserException( long errorCode, DString& errorMessage, DString& locale=DString( NULL_STRING ) ) :
   _errorCode( errorCode ), _errorMessage( errorMessage )
   { _locale = locale;}
   XparserException( I_CHAR* format, ... );
   //to be overide by derived classes
   virtual void getOutMessage( DString &strOut );
   virtual long geterrorcode() { return(_errorCode);};
   virtual void geterrormessage(DString& errormessage) { errormessage = _errorMessage;};
private:
   DString _locale;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/xparser/xparserException.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 17:43:28   PURDYECH
//New PVCS Database
//
//   Rev 1.1   02 Apr 2002 12:57:36   SMITHDAV
//Change the way XML processing is handled.
//
//   Rev 1.0   Aug 28 2001 10:38:16   FENGYONG
//Initial revision.
 * 
 * 
 */