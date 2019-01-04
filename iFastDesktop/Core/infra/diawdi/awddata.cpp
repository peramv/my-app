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
// ^FILE   : AwdData.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 1 Apr 97
//
// ----------------------------------------------------------
//
// ^CLASS    : AwdData
//
// ^MEMBER VARIABLES :
//
//    string_map  m_data  - Holds the lob data
//    AwdKey     *m_pKey  - Handle to the AWD object in the AWD server database
//    string      m_unit  - Business area
//    string      m_wrkt  - Work type
//    string      m_stat  - Status
//
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define DIAWDI_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef AWDDATA_HPP
   #include "awddata.hpp"
#endif
#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif
#ifndef DIAWDCND_H
   #include "diawdcnd.h"
#endif

namespace AwdDataConsts
{
   const DString strUNIT     = I_("UNIT");
   const DString strWRKT     = I_("WRKT");
   const DString strSTAT     = I_("STAT");
   const DString strOBJT     = I_("OBJT");

   const int  SEQ_LEN    = 3;
   const int  SEQ_POS    = 4;
   const int  NAME_POS   = 3;
   const int  NAME_LEN   = 4;
   const int  SIZE_POZ   = 7;
}

using namespace AwdDataConsts;

//******************************************************************************
//              Public Methods
//******************************************************************************

AwdData::AwdData()
   : m_empty( I_("") ),
     m_beginTime( I_("") ),
     m_endTime( I_("") ),
     m_pKey( NULL )
{
}

AwdData::AwdData( const DString &unit,
                  const DString &wrkt,
                  const DString &stat )
   : m_empty( I_("") ),
     m_beginTime( I_("") ),
     m_endTime( I_("") ),
     m_pKey( NULL )
{
   setLobData( strUNIT, unit );
   setLobData( strWRKT, wrkt );
   setLobData( strSTAT, stat );
}

AwdData::AwdData( const AwdData &copy )
   : m_empty( I_("") ),
     m_beginTime( I_("") ),
     m_endTime( I_("") ),
     m_pKey( NULL )
{
   this->operator =( copy );
}

AwdData::~AwdData()
{
   if ( m_pKey )
   {
      // Delete the key if we have one
      delete m_pKey;
   }
}

void AwdData::setLobData( const DString &name,
                          const DString &value,
                          const int seq )
{
   DString seqname;

   // Mangle the sequence number and name into seqname
   AwdData::LobData::setSeqName( seqname, seq, name );

   // See if the key is alread there
   string_map_iterator iter = m_data.find( seqname );

   if ( iter == m_data.end() )
   {
      // Not there, insert the new pair
      m_data.insert( string_map_type( seqname, value ) );
   }
   else
   {
      // Found, override th old value
      (*iter).second = value;
   }
}

void AwdData::setLobData( const LobData &lobData )
{
   // See if the data is alread there
   string_map_iterator iter = m_data.find( lobData.m_lobData.first );

   if ( iter == m_data.end() )
   {
      // Not there, insert it
      m_data.insert( lobData.m_lobData );
   }
   else
   {
      // Found, overrider the value
      ( *iter ).second = lobData.m_lobData.second;
   }
}

void AwdData::setUnit( const DString &unit )
{
   setLobData( strUNIT, unit );
}

void AwdData::setWrkt( const DString &wrkt )
{
   setLobData( strWRKT, wrkt );
}

void AwdData::setStat( const DString &stat )
{
   setLobData( strSTAT, stat );
}

void AwdData::setObjt( const DString &objt )
{
   setLobData( strOBJT, objt );
}

const DString &AwdData::getLobValue( const DString &name, const int seq ) const
{
   DString seqname;

   // mangle the sequence number and name into seqname
   AwdData::LobData::setSeqName( seqname, seq, name );

   // Find the key
   string_map_const_iterator iter = m_data.find( seqname );

   if ( iter != m_data.end() )
   {
      // Found, return the value
      return ( *iter ).second;
   }

   // not found, return an empty string
   return m_empty;
}

const DString &AwdData::getUnit() const
{
   return getLobValue( strUNIT );
}

const DString &AwdData::getWrkt() const
{
   return getLobValue( strWRKT );
}

const DString &AwdData::getStat() const
{
   return getLobValue( strSTAT );
}

const DString &AwdData::getObjt() const
{
   return getLobValue( strOBJT );
}

SEVERITY AwdData::setBeginTime( const DString &dateTime )
{
   TRACE_METHOD( I_("AwdData"), I_("setBeginTime( const DString & )") )

   return validateAndCopyDateTime( dateTime, m_beginTime );
}

SEVERITY AwdData::setEndTime( const DString &dateTime )
{
   TRACE_METHOD( I_("AwdData"), I_("setEndTime( const DString & )") )

   return validateAndCopyDateTime( dateTime, m_endTime );
}

AwdData &AwdData::operator =( const AwdData &copy )
{
   if ( this != &copy )
   {
      this->m_beginTime = copy.m_beginTime;
      this->m_endTime   = copy.m_endTime;
      this->m_data      = copy.m_data;

      if ( m_pKey )
      {
         delete m_pKey;
         m_pKey = NULL;
      }

      if ( copy.m_pKey )
      {
         this->m_pKey = copy.m_pKey->makeCopy();
      }
   }

   return *this;
}

void AwdData::setKey( AwdKey *awdKey )
{
   // No memory leak here!
   if ( m_pKey )
   {
      // If we already have a key, delete the old one
      delete m_pKey;
   }

   m_pKey = awdKey;
}

const AwdKey *AwdData::getKey() const
{
   return m_pKey;
}

const AwdData::LobIterator AwdData::begin()
{
   return AwdData::LobIterator( m_data.begin(), m_data.end() );
}

const AwdData::LobIterator AwdData::end()
{
   return AwdData::LobIterator( m_data.end(), m_data.end() );
}

unsigned short AwdData::lobCount() const
{
   return m_data.size();
}

//******************************************************************************
//              Private methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : AwdData::validateAndCopyDateTime
//
// ^DESCRIPTION : validates the date time and copies it
//
// ^PARAMETERS  :
//   ^^ const string &source -
//   ^^ string &copy -
//
// ^RETURNS     : SEVERITY -
//
// ^THROWS      : none
//
//******************************************************************************
SEVERITY AwdData::validateAndCopyDateTime( const DString &source, DString &copy )
{
   MAKEFRAMEAUTOPROMOTE( DIAWDI_CONDITION, I_("AwdData::validateAndCopyDateTime()" ))

   bool isValid = true;
   DString working( source );

   int len = source.length();

   isValid = ( DATETIME_LEN == len );

   // Only continue to validate if the source is valid
   if ( isValid )
   {

      stripAll( working, '-' );
      stripAll( working, '.' );

      isValid = isAllDigits( working );
   }

   //
   //  CCYY-MM-DD-HH.MM.SS.TTTTTT
   //  01234567890123456789012345
   //

   // Only continue to validate if the source is valid
   if ( isValid )
   {
      working = source.substr( 5, 2 );
      int month = asInteger( working );

      isValid = ( ( 13 > month ) && ( 0 < month ) );
   }

   // Only continue to validate if the source is valid
   if ( isValid )
   {
      working = source.substr( 8, 2 );
      int day = asInteger( working );

      isValid = ( ( 32 > day ) && ( 0 < day ) );
   }

   // Only continue to validate if the source is valid
   if ( isValid )
   {
      working = source.substr( 11, 2 );
      int hour = asInteger( working );

      isValid = ( ( 25 > hour ) && ( 0 <= hour ) );
   }

   // Only continue to validate if the source is valid
   if ( isValid )
   {
      working = source.substr( 14, 2 );
      int minute = asInteger( working );

      isValid = ( ( 61 > minute ) && ( 0 <= minute ) );
   }

   // Only continue to validate if the source is valid
   if ( isValid )
   {
      working = source.substr( 5, 2 );
      int second = asInteger( working );

      isValid = ( ( 61 > second ) && ( 0 <= second ) );
   }

   if ( isValid )
   {
      copy = source;
   }
   else
   {
      ADDCONDITIONFROMFILE( DIAWDI_INVALID_DATE_TIME_PASSED );
   }

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//
// CLASS:   LobData
//
// ^MEMBER VARIABLES :
//
//    string_map_type m_lobData - a pair, seqname and value
//
//******************************************************************************

AwdData::LobData::LobData( const DString &name,
                           const DString &value,
                           const int seq )
{
   DString seqname;

   // Mangle the sequence number and name into seqname
   setSeqName( seqname, seq, name );

   (DString &)m_lobData.first = seqname;
   m_lobData.second = value;
}

AwdData::LobData::LobData( const AwdData::LobData &copy )
{
   this->operator =( copy );
}

AwdData::LobData::LobData( const string_map_type &data )
   : m_lobData( data )
{
}

AwdData::LobData::~LobData()
{
}

const DString AwdData::LobData::getName() const
{
   // Extract the name
   const DString &name = m_lobData.first;
   DString strSize = name.substr( SIZE_POZ, 1 );
   int size = strSize.asInteger();

   return name.substr( 0, size );
}

const DString &AwdData::LobData::getValue() const
{
   return m_lobData.second;
}

const int AwdData::LobData::getSeqNo() const
{
   // Extract the value
   int seq = ::asInteger( m_lobData.first.substr( SEQ_POS, SEQ_LEN ) );

   return seq;
}

const DString AwdData::LobData::getSeqNoAsString() const
{
   return m_lobData.first.substr( SEQ_POS, SEQ_LEN );
}

AwdData::LobData &AwdData::
LobData::operator =( const AwdData::LobData &copy )
{
   if ( this != &copy )
   {
      (DString &)this->m_lobData.first = copy.m_lobData.first;
      m_lobData.second = copy.m_lobData.second;
   }

   return *this;
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : AwdData::LobData::setSeqName
//
// ^DESCRIPTION : This method combines the sequence number and name into
//                one object called seqname.
//
// ^PARAMETERS  :
//   ^^ string &seqname    - String containing both sequence number and name
//   ^^ const int seq      - Sequence number
//   ^^ const string &name - Dataset Name
//
// ^RETURNS     : void
//
// ^THROWS      : none
//
//******************************************************************************
void AwdData::LobData::setSeqName( DString &seqname,
                                   const int seq,
                                   const DString &name )
{
   seqname = name;

   int size = name.size();

   if ( NAME_LEN < size )
   {
      size = NAME_LEN;
      seqname = name.substr( 0, size );
   }
   else if ( NAME_LEN > size )
   {
      seqname.padRight( NAME_LEN );
   }

   DString strSeq;
   strSeq.appendInt( seq );
   strSeq.padLeft( SEQ_LEN, '0' );

   I_CHAR buffer[3];
   i_itot( size, buffer, 10 );

   seqname += strSeq;
   seqname += buffer;
}

//******************************************************************************
//
// CLASS:   LobIterator
//
// ^MEMBER VARIABLES :
//
//******************************************************************************

AwdData::LobIterator::LobIterator()
{
}

AwdData::LobIterator::LobIterator( const AwdData::LobIterator &copy )
{
   this->operator =( copy );
}

AwdData::LobIterator::~LobIterator()
{
}

AwdData::LobData AwdData::LobIterator::operator *() const
{
   return AwdData::LobData( *m_dataPtr );
}

AwdData::LobIterator &AwdData::LobIterator::operator ++()
{
   // Check for end
   if ( ! ( m_dataPtr == m_endPtr ) )
   {
      // Increment the iterator
      ++m_dataPtr;
   }

   return *this;
}

AwdData::LobIterator &AwdData::
LobIterator::operator =( const AwdData::LobIterator &copy )
{
   if ( this != &copy )
   {
      this->m_dataPtr = copy.m_dataPtr;
      this->m_endPtr  = copy.m_endPtr;
   }

   return *this;
}

bool AwdData::LobIterator::operator ==( const LobIterator &copy ) const
{
   return this->m_dataPtr == copy.m_dataPtr;
}

bool AwdData::LobIterator::operator !=( const LobIterator &copy ) const
{
   return ! operator ==( copy );
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : AwdData::LobIterator::LobIterator
//
// ^DESCRIPTION : Provate constructor called by the class AwdData
//
// ^PARAMETERS  :
//   ^^ const string_map_iterator &dataPtr -
//   ^^ const string_map_iterator &endPtr -
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
//******************************************************************************
AwdData::LobIterator::LobIterator( const string_map_iterator &dataPtr,
                                   const string_map_iterator &endPtr )
   : m_dataPtr( dataPtr ), m_endPtr( endPtr )
{
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/diawdi/awddata.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:18:14   kovacsro
// Initial revision.
// 
//    Rev 1.8   Feb 08 2002 07:52:02   DT21858
// Fix bug with AwdData to work with datanames that are
// less than four characters.
//
//    Rev 1.7   Aug 26 1999 12:58:38   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of a source.
//
//    Rev 1.5   Apr 09 1999 13:48:58   DMUM
// Sync up with 1.6.x
//
//    Rev 1.2.1.0   Mar 31 1999 13:19:18   DMUM
//
//
//    Rev 1.0.1.0   Dec 30 1998 16:12:50   DMUM
// Fixes - for Kemper & for 3.4
//
//    Rev 1.0   29 Jul 1998 20:28:56   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.13   Jul 23 1998 08:35:48   dmum
// Fixed potential bug
//
//    Rev 1.12   Mar 17 1998 10:44:14   dmum
// Fixed problem in validating DateTime
//
//    Rev 1.11   Mar 16 1998 15:41:48   dmum
// Added begin and end Time methods
//
//    Rev 1.10   Dec 30 1997 11:18:58   dmum
// Changed the get methods to be const
//
//    Rev 1.9   Dec 16 1997 11:25:44   dmum
// New Methods
//
//    Rev 1.8   10 Nov 1997 15:23:02   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.7   02 Sep 1997 15:07:12   dmum
// Added new method getSeqNoAsString()
//
//    Rev 1.6   27 Jun 1997 14:36:20   dmum
// Further documentation
//
//    Rev 1.5   27 Jun 1997 07:26:46   dmum
// Added documentaion
//
//    Rev 1.4   13 Jun 1997 14:50:48   dmum
// Added unit wrkt and stat into the Lob collection
//
//    Rev 1.3   May 22 1997 10:04:32   dmum
// Now uses commontemplates.h
//
//    Rev 1.2   Apr 28 1997 11:10:34   dmum
// Added support for sequence number
//
//
//    Rev 1.1   Apr 25 1997 11:20:52   dmum
// Second Iteration
//
//    Rev 1.0   Apr 18 1997 09:18:38   dmum
//
//
//


