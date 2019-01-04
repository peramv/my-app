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
// ^FILE   : DSTOleDateTime.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : 07/21/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : DSTOleDateTime
//
// ^MEMBER VARIABLES :
//
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"
#include "dstoledatetime.h"
#include <configmanager.hpp>
#include <bfdata\bfdatafieldproperties.hpp>
#include <bfutil\clientlocalecontext.hpp>
#include <assert.h>

namespace CND
{
}
#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DSTDateTimeCtrl

void DSTOleDateTime::DSTHostFormat( CString &strOut, DString Type )
{
   strOut.Empty();

   //  look in the registry for the date format mask
   DString dstrMask( GetConfigValueAsString( I_( "LocaleFormats" ), I_( "HostMasks" ), Type ) );

   // Default
   if( dstrMask.length() == 0 )
   {
      if( Type == I_("T") )
      {
         dstrMask = I_("HH:mm");
      }
   }

   if( dstrMask.length() )
   {
      CString strOleDateTimeMask( dstrMask.c_str() );

      if( Type == I_("D") )
      {
         strOleDateTimeMask.Replace( _T( "dd" ), _T( "%d" ) );
         strOleDateTimeMask.Replace( _T( "MM" ), _T( "%m" ) );
         strOleDateTimeMask.Replace( _T( "yyyy" ), _T( "%Y" ) );
      }
      else if( Type == I_("T") )
      {
         strOleDateTimeMask.Replace( _T( "HH" ), _T( "%H" ) );
         strOleDateTimeMask.Replace( _T( "mm" ), _T( "%M" ) );
         strOleDateTimeMask.Replace( _T( "SS" ), _T( "%S" ) );
      }

      strOut = Format( strOleDateTimeMask );
   }
}


void DSTOleDateTime::DSTDisplayFormat( CString &strOut, const BFDataFieldProperties* pProps ) const
{
   strOut.Empty();
   DString dstrMask;
   if( NULL != pProps && NULL != pProps->getMask(ClientLocaleContext::get()) )
   {
      dstrMask = pProps->getMask(ClientLocaleContext::get())->getMask();
   }

   if( dstrMask.length() )
   {
      CString strOleDateTimeMask( dstrMask.c_str() );

      strOleDateTimeMask.Replace( _T( "dd" ), _T( "%d" ) );
      strOleDateTimeMask.Replace( _T( "MM" ), _T( "%m" ) );
      strOleDateTimeMask.Replace( _T( "yyyy" ), _T( "%Y" ) );
      //strOleDateTimeMask.Replace( _T( "/" ), _T( "\'/\'" ) );
      //strOleDateTimeMask.Replace( _T( "yyyy" ), _T( "yyy" ) );

      strOut = Format( strOleDateTimeMask );
   }
}

void DSTOleDateTime::getDisplayFormat( DString& dateFormat )
{ 
   //  look in the registry for the date format mask
   DString dstrConfiguration( I_( "DisplayMasks" ) );
   DString dstrType( I_( "-D" ) );
   const DString &lcv = ClientLocaleContext::get().getLocale();
   DString dstrKey( lcv );
   dstrKey.append( dstrType );

   dateFormat = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );

   if( dateFormat == NULL_STRING ) dateFormat = I_("dd/MM/yyyy");

   _dateFormat = dateFormat;
}

// this function is used in stingery control
// input: formatted date in registry format, output: formatted to machine locale. 
void DSTOleDateTime::DSTDisplayFormat( const DString& formattedDate, CString &strOut )
{
   if( formattedDate == NULL_STRING ) return;

   DString tmp;
   if( _dateFormat == NULL_STRING )
      getDisplayFormat( _dateFormat );

   _dateFormat.upperCase();

   int nYear, nMonth, nDay;
   int pos = _dateFormat.find( I_( "MM" ) );
   if( pos != DString::npos )
   {
      tmp.assign( formattedDate, pos, 2);
      nMonth = convertToULong( tmp );
   }

   pos = _dateFormat.find( I_( "DD" ) );
   if( pos != DString::npos )
   {
      tmp.assign( formattedDate, pos, 2);
      nDay = convertToULong( tmp );
   }

   pos = _dateFormat.find( I_( "YYYY" ) );
   if( pos != DString::npos )
   {
      tmp.assign( formattedDate, pos, 4);
      nYear = convertToULong( tmp );
   }

   SetDate( nYear, nMonth, nDay );
   strOut = Format();
}
//***********************************************************************
void DSTOleDateTime::DSTFormatWithHostFormat( const DString& hostDate, CString &strOut )
{
   if( hostDate == NULL_STRING ) return;

   DString tmp;
   DString dstrMask( GetConfigValueAsString( I_( "LocaleFormats" ), 
                                             I_( "HostMasks" ), I_( "D" ) ) );

   dstrMask.upperCase();
   int nYear, nMonth, nDay;
   int pos = dstrMask.find( I_( "MM" ) );
   if( pos != DString::npos )
   {
      tmp.assign( hostDate, pos, 2);
      nMonth = convertToULong( tmp );
   }

   pos = dstrMask.find( I_( "DD" ) );
   if( pos != DString::npos )
   {
      tmp.assign( hostDate, pos, 2);
      nDay = convertToULong( tmp );
   }

   pos = dstrMask.find( I_( "YYYY" ) );
   if( pos != DString::npos )
   {
      tmp.assign( hostDate, pos, 4);
      nYear = convertToULong( tmp );
   }

   SetDate( nYear, nMonth, nDay );
   strOut = Format();
}