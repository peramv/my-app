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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DateEdit.cpp
// ^AUTHOR : Steve Tarver
// ^DATE   : 5/22/98
//
// ----------------------------------------------------------
//
// ^CLASS    : CDateEdit
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"

#include "DateEdit.h"


#ifndef STRINGFUNCTIONS_HPP
   #include <StringFunctions.hpp>
#endif
namespace CND
{
}


#ifdef _DEBUG
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CDateEdit, CEdit)
//{{AFX_MSG_MAP(CDateEdit)
ON_WM_KILLFOCUS()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

const I_CHAR *dateFormats[] =
{
   I_( "" ),               // e_INVALID
   I_( "MMdd" ),           // e_MMDD
   I_( "MM/dd" ),          // e_MM_DD
   I_( "MMddyyyy" ),       // e_MMDDYYYY
   I_( "MM/dd/yyyy" )      // e_MM_DD_YYYY
};


//******************************************************************************
//  Public methods
//******************************************************************************

CDateEdit::CDateEdit()
: m_format( e_MM_DD_YYYY )
{
}

//******************************************************************************

CDateEdit::~CDateEdit()
{
}

//******************************************************************************

// Constructs a CString on the stack and puts our formatted text into it. Note
// that if the text is invalid, we return an empty string.
CString CDateEdit::Format()
{
   CString temp;

   if( ::IsWindow( m_hWnd ) )
   {
      GetWindowText( temp );
      if( !temp.IsEmpty() )
      {
         Format( temp );
      }
   }
   return(temp);
}

//******************************************************************************

CString &CDateEdit::Format(
                          CString &text
                          )
{
   return(Format( text, m_format ));
}

//******************************************************************************

// Applies our format to a date and returns a ref to the text. This is
// necessary because COleDateTime will use the User's default date format
// and we always want this to be a four digit year.
// An empty format will produce an empty string for output.
CString &CDateEdit::Format(
                          CString &text,
                          DisplayFormatType format)
{
   ASSERT( !text.IsEmpty() );
   ASSERT( format );

   if( !text.IsEmpty() )
   {
      if( !ParseString( text, format ) )  // This also formats our string
      {
         text.Empty();
      }
   }
   return(text);
}

//******************************************************************************

bool CDateEdit::Format(
                      COleDateTime &date,        // Should be parsed and valid
                      CString &text,             // Should have already been through ParseString
                      DisplayFormatType format)
{
   // We should not get this far if either of the following is false
   ASSERT( COleDateTime::valid == date.GetStatus() );

   bool result = false;

   if( COleDateTime::valid == date.GetStatus() )
   {
      SYSTEMTIME st;
      memset( &st, 0, sizeof( st ) );

      st.wYear = date.GetYear();
      st.wMonth = date.GetMonth();
      st.wDay = date.GetDay();

      I_CHAR buf[32] = I_( "" );
      result = ::GetDateFormat( LOCALE_SYSTEM_DEFAULT, 
                                0, 
                                &st,
                                GetFormatString( format ), 
                                buf, 
                                sizeof( buf ) ) != FALSE;
      text = buf;
   }
   else
   {
      text.Empty();
   }
   return(!!result);  // Cheap way to turn number into BOOL
}

//******************************************************************************

// A little safer access to our format strings - prevents us from walking
// off the end of the array if passed a bogus enum.
const I_CHAR *CDateEdit::GetFormatString(
                                        DisplayFormatType formatEnum
                                        )
{
   const I_CHAR *format = dateFormats[ e_INVALID ];

   switch( formatEnum )
   {
      case e_MMDD:
      case e_MM_DD:
      case e_MMDDYYYY:
      case e_MM_DD_YYYY:
         format = dateFormats[ formatEnum ];
         break;

      default:
         ASSERT( 0 );   // Invalid enum value
   }
   return(format);
}

//******************************************************************************

// Returns our value using our format. We return an empty string if it is
// invalid so you should also check that the control is not empty. This
// scheme is cheaper than providing an IsValid().
CString &CDateEdit::GetText(
                           CString &text
                           )
{
   return(GetText( text, m_format ));
}

//******************************************************************************

DString &CDateEdit::GetText(
                           DString &text
                           )
{
   CString temp;
   GetText( temp, m_format );
   text = temp.operator LPCTSTR();
   return(text);
}

//******************************************************************************

// Returns our value using provided format. We return an empty string if it is
// invalid so you should also check that the control is not empty. This
// scheme is cheaper than providing an IsValid().
CString &CDateEdit::GetText(
                           CString &text,
                           DisplayFormatType useThisFormat
                           )
{
   // Ensure they didn't give us a bogus enum.
   ASSERT( int( useThisFormat ) >= 0 && int( useThisFormat ) <= 3 );

   GetWindowText( text );

   if( !ParseString( text, useThisFormat ) )
   {
      text.Empty();
   }
   return(text);
}


///////////////////////////////////////////////////////////////////////////////
DString &CDateEdit::GetText(
                           DString &text,
                           DisplayFormatType useThisFormat)
{
   CString temp;
   GetText( temp, useThisFormat );
   text = temp.operator LPCTSTR();
   return(text);
}

//******************************************************************************

// Returns whether the current value is different than the initial value.
bool CDateEdit::IsModified()
{
   CString  text;
   bool result = false;

   GetWindowText( text );
   if( ParseString( text ) )
   {
      result = ( m_initialValue == text );
   }
   return(result);
}

//******************************************************************************

// Update our control text with our formatted value when ever we lose focus
void CDateEdit::OnKillFocus(
                           CWnd *focusedWnd
                           )
{
   CEdit::OnKillFocus( focusedWnd );

   if( GetModify() )
   {
      SetWindowText( Format() );
      SetModify( FALSE );
   }
}

//******************************************************************************

// Parses the given string and returns it in the given format. Originally,
// this was to change the string into our internal format. The formatter
// requires a string in a known form. This special version is to prevent
// the string from being formatted into our internal format and then again
// into the desired format.
//
// The special case of an empty string should be handled by callers. Empty
// is considered a valid value but we can't format it.
//
bool CDateEdit::ParseString(
                           CString &text,
                           DisplayFormatType format      // Should have already been validated
                           )
{
   ASSERT( GetFormatString( format ) );

   bool result = false;

   if( !text.IsEmpty() )
   {
      COleDateTime date;

      // NOTE: This should be the common case.
      if( date.ParseDateTime( text, VAR_DATEVALUEONLY ) )
      {
         // Can't use a Format() that calls ParseString()
         Format( date, text, format );   // If we can parse, we can format
         result = TRUE;
      }

      // If COleDateTime couldn't figure it out, we will make some
      // assumptions and see if we can make sense of the supplied text.
      // Note that we duplicate the ParseDateTime() code to make the common
      // case fast.
      else
      {
         DString str( text.operator LPCTSTR() );

         if( isAllDigits( str ) )
         {
            // We will assume they left out all slashes and used either m d or m d y
            // They must provide leading zeroes or we can't tell 1/21 from 12/1
            const DString slash( I_( "/" ) );
            switch( str.length() )
            {
               case 8:     // MM DD YYYY
               case 6:     // MM DD YY
                  str.insert( 4, slash );    // Note intentional fall through

               case 4:     // MM DD
                  str.insert( 2, slash );
            }

            // Now let COleDateTime have another go at it..
            if( date.ParseDateTime( str.c_str(), VAR_DATEVALUEONLY ) )
            {
               // Can't use a Format() that calls ParseString()
               Format( date, text, format );   // If we can parse, we can format
               result = true;
            }
         }
      }
   }
   return(result);
}

//******************************************************************************

// This version of ParseString converts the text into our default internal
// format. Use the other version of ParseString() if the desired outcome is
// a different format to avoid two trips through the formatter.
bool CDateEdit::ParseString(
                           CString &text
                           )
{
   return(ParseString( text, e_MM_DD_YYYY ));
}

//******************************************************************************

bool CDateEdit::SetFormat(
                         DisplayFormatType newFormat)
{
   bool result = true;

   switch( newFormat )
   {
      case e_MMDD:
      case e_MM_DD:
      case e_MMDDYYYY:
      case e_MM_DD_YYYY:
         m_format = newFormat;
         if( ::IsWindow( m_hWnd ) )
         {
            SetWindowText( Format() );
         }
         break;

      default:
         ASSERT( 0 );   // Invalid enum value
         result = false;
   }
   return(result);
}

//******************************************************************************

bool CDateEdit::SetInitialValue(
                               const I_CHAR *text
                               )
{
   // If we can parse the string, we will store it in our internal format
   // MM/DD/YYYY
   CString  temp( text );
   bool result = true;

   if( text )
   {
      result = ParseString( temp );

      if( result )
      {
         m_initialValue = temp;
         SetWindowText( Format( temp ) ); // Don't re-format the initial value
      }
   }
   return(result);
}

//******************************************************************************

bool CDateEdit::SetText(
                       const I_CHAR *text
                       )
{
   return(SetText( CString( text ) ));  // Don't the ctor.
}

//******************************************************************************

bool CDateEdit::SetText(
                       const DString &text
                       )
{
   return(SetText( text.c_str() ));
}

//******************************************************************************

bool CDateEdit::SetText(
                       const CString &text
                       )
{
   bool result = false;

   if( ::IsWindow( m_hWnd ) ) // Can't set the text unless we have a window
   {
      // We need to modify the string so make a copy. The copy should be
      // cheap since MFC shares strings.
      CString temp( text );
      temp.TrimRight();       // Clear off extraneous white space
      if( !temp.IsEmpty() )
      {
         if( ParseString( temp, m_format ) )
         {
            SetWindowText( temp );
            result = true;
         }
      }
      else
      {
         SetWindowText( NULL );
         result = true;
      }
   }
   return(result);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/DateEdit.cpp-arc  $
 * 
 *    Rev 1.3   Oct 09 2002 17:42:38   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   Sep 10 2002 14:34:28   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.1   Feb 25 2002 18:58:06   PURDYECH
 * Removed annoying compiler warnings.
 * 
 *    Rev 1.0   Feb 15 2000 11:01:38   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:04:54   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
