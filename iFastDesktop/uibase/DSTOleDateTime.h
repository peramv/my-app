#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DSTCOleDateTime.h
// ^AUTHOR : Yakov Prager
// ^DATE   : 07/20/99
//
// ^CLASS    : DSTOleDateTime
// ^SUBCLASS : COleDateTime
//
// ^CLASS DESCRIPTION : Wraps COleDateTime class
//
//
//
// ^METHOD : process()
//
// ^DESCRIPTION : Get the intial stuff. Gets parms from call global.
//                
//
// ^PARAMETERS  :
//    ^^STRINGVECTOR *display - Values to add to list, comes from
//                                CallDataPtr()->_psvParm1
//    ^^string title            - Title of dialog, comes from
//                                CallDataPtr()->_sParm1
//
// ^RETURNS     :
//    ^^ int - Index into string vector of item selected or -1
//             CallDataPtr->iParm1
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

class BFDataFieldProperties;
class DString;

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE DSTOleDateTime : public COleDateTime
{
public:
   DSTOleDateTime() : COleDateTime() {}
   DSTOleDateTime( const COleDateTime& dateSrc ) : COleDateTime( dateSrc ) {}
   DSTOleDateTime( const VARIANT& varSrc ) : COleDateTime( varSrc ) {}
   DSTOleDateTime( DATE dtSrc ) : COleDateTime( dtSrc ) {}
   DSTOleDateTime( time_t timeSrc ) : COleDateTime( timeSrc ) {}
   DSTOleDateTime( const SYSTEMTIME& systimeSrc ) 
   : COleDateTime( systimeSrc ) {}
   DSTOleDateTime( const FILETIME& filetimeSrc ) 
   : COleDateTime( filetimeSrc ) {}
   DSTOleDateTime( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec ) 
   : COleDateTime( nYear, nMonth, nDay, nHour, nMin, nSec ) {}
   DSTOleDateTime( WORD wDosDate, WORD wDosTime ) 
   : COleDateTime( wDosDate, wDosTime ) {}

   void getDisplayFormat( DString& dateFormat ); 
   void DSTDisplayFormat( const DString& formattedDate, CString &strOut ); 

   void DSTHostFormat( CString &strOut, DString Type = I_("D") );
   void DSTDisplayFormat( CString &strOut, const BFDataFieldProperties* pProps ) const;
   void DSTFormatWithHostFormat( const DString& hostDate, CString &strOut );


private:
   DString _dateFormat;
};

