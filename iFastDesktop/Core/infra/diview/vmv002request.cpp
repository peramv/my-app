/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2001 by DST Systems, Inc.
 */

#define DIVIEW_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef VMV002REQUEST_HPP
   #include "vmv002request.hpp"
#endif



static const int PB00250_REQUEST_HEADER_LEN = 23;
static const int PB00250_REQUEST_VIEW_NAME_LEN = 8;
static const int PB00250_REQUEST_VIEW_NAME_INDEX = 4;
static const int PB00250_REQUEST_OPERATOR_LEN = 8;
static const int PB00250_REQUEST_OPERATOR_INDEX = 12;


VMV002Request::VMV002Request( const char *viewName,
                              const char *operatorId,
                              const char *password,
                              const char *newPassword,
                              const char *securityType,
                              const char *sessionKey,
                              const char *sourceSystemId,
                              const char *locationId,
                              const char *targetRoutingId,
                              const char *traceFlag,
                              const char *clientData,
                              const char *dataVersion )
{
   m_requestHeaderFixedArea.recordType = 'V';
   strncpy( m_requestHeaderFixedArea.version, "002", 3 );
   strncpy( m_requestHeaderFixedArea.encryption, "00", 2 );
   strncpy( m_requestHeaderFixedArea.compression, "00", 2 );
   strncpy( m_requestHeaderFixedArea.nameSpace, "00", 2 );
   m_tagMap[ I_("AAAA") ] = viewName;
   m_tagMap[ I_("AAAB") ] = operatorId;
   m_tagMap[ I_("AAAC") ] = securityType;
   m_tagMap[ I_("AAAD") ] = password;
   m_tagMap[ I_("AAAQ") ] = newPassword;
   m_tagMap[ I_("AAAE") ] = sessionKey;
   m_tagMap[ I_("AAAF") ] = sourceSystemId;

   if ( 0 == locationId ||
        0 == locationId[ 0 ] )
   {
       m_tagMap[ I_("AAAG") ] = getMACAddress();
   }
   else
   {
      m_tagMap[ I_("AAAG") ] = locationId;
   }

   m_tagMap[ I_("AAAH") ] = targetRoutingId;
   m_tagMap[ I_("AAAI") ] = traceFlag;
   m_tagMap[ I_("AAAJ") ] = clientData;
   m_tagMap[ I_("AAAK") ] = dataVersion;
}


VMV002Request::VMV002Request( const unsigned char *pb00250Request,
                              unsigned long ulRequestLength,
                              const char *password,
                              const char *sourceSystemId,
                              const char *newPassword,
                              const char *securityType,
                              const char *sessionKey,
                              const char *locationId,
                              const char *targetRoutingId,
                              const char *traceFlag,
                              const char *clientData,
                              const char *dataVersion )
{
   m_requestHeaderFixedArea.recordType = 'V';
   strncpy( m_requestHeaderFixedArea.version, "002", 3 );
   strncpy( m_requestHeaderFixedArea.encryption, "00", 2 );
   strncpy( m_requestHeaderFixedArea.compression, "00", 2 );
   strncpy( m_requestHeaderFixedArea.nameSpace, "00", 2 );
   m_tagMap[ I_("AAAC") ] = securityType;
   m_tagMap[ I_("AAAD") ] = password;
   m_tagMap[ I_("AAAQ") ] = newPassword;
   m_tagMap[ I_("AAAE") ] = sessionKey;
   m_tagMap[ I_("AAAF") ] = sourceSystemId;

   if ( 0 == locationId ||
        0 == locationId[ 0 ] )
   {
       m_tagMap[ I_("AAAG") ] = getMACAddress();
   }
   else
   {
      m_tagMap[ I_("AAAG") ] = locationId;
   }

   m_tagMap[ I_("AAAH") ] = targetRoutingId;
   m_tagMap[ I_("AAAI") ] = traceFlag;
   m_tagMap[ I_("AAAJ") ] = clientData;
   m_tagMap[ I_("AAAK") ] = dataVersion;

   // Check pb00250Request min length
   if ( PB00250_REQUEST_HEADER_LEN > ulRequestLength )
   {
      // DTWK throw an error!
   }

   // Pull viewName from pb00250
   char szViewName[ PB00250_REQUEST_VIEW_NAME_LEN + 1 ];
   memcpy( szViewName, pb00250Request + PB00250_REQUEST_VIEW_NAME_INDEX,
           PB00250_REQUEST_VIEW_NAME_LEN );
   szViewName[ PB00250_REQUEST_VIEW_NAME_LEN ] = 0;
   m_tagMap[ I_( "AAAA" ) ] = szViewName;

   // Check to see if there's actual data after the header
   if ( ulRequestLength > PB00250_REQUEST_HEADER_LEN )
   {
      // We have to do this because it may no
      m_tagMap[ I_( "AAAL" ) ].append(
                ( ( const char * )pb00250Request ) + PB00250_REQUEST_HEADER_LEN,
                ulRequestLength - PB00250_REQUEST_HEADER_LEN );
   }

   // Pull operatorId from pb00250
   if ( !strncmp( "SIGNON", szViewName, 6 ) )
   {
      // If we are doing a signon view, then the operator Id will not be in
      // the pb00250 header, but in the data block!
      char szOperatorId[ PB00250_REQUEST_OPERATOR_LEN + 1 ];
      memcpy( szOperatorId, pb00250Request + PB00250_REQUEST_HEADER_LEN,
              PB00250_REQUEST_OPERATOR_LEN );
      szOperatorId[ PB00250_REQUEST_OPERATOR_LEN ] = 0;
      m_tagMap[ I_( "AAAB" ) ] = szOperatorId;
   }
   else
   {
      char szOperatorId[ PB00250_REQUEST_OPERATOR_LEN + 1 ];
      memcpy( szOperatorId, pb00250Request + PB00250_REQUEST_OPERATOR_INDEX,
              PB00250_REQUEST_OPERATOR_LEN );
      szOperatorId[ PB00250_REQUEST_OPERATOR_LEN ] = 0;
      m_tagMap[ I_( "AAAB" ) ] = szOperatorId;
   }
}


VMV002Request::~VMV002Request()
{
}

void VMV002Request::setTaggedValue( char *tag, char *value )
{
   m_tagMap[ tag ] = value;
}

void VMV002Request::setRecordType( char recType )
{
   m_requestHeaderFixedArea.recordType = recType;
}

void VMV002Request::setVersion( const DStringA &version )
{
   strncpy( m_requestHeaderFixedArea.version, version.c_str(), 3 );
}

void VMV002Request::setPacketLength( unsigned long packetLength )
{
   char tempPacketLen[ 9 ];
   sprintf( tempPacketLen, "%.8ld", packetLength );
   strncpy( m_requestHeaderFixedArea.packetLength, tempPacketLen, 8 );
}

void VMV002Request::setEncryption( const DStringA &encryption )
{
   strncpy( m_requestHeaderFixedArea.encryption, encryption.c_str(), 2 );
}

void VMV002Request::setCompression( const DStringA &compression )
{
   strncpy( m_requestHeaderFixedArea.compression, compression.c_str(), 2 );
}

void VMV002Request::setNameSpace( const DStringA &nameSpace )
{
   strncpy( m_requestHeaderFixedArea.nameSpace, nameSpace.c_str(), 2 );
}

char VMV002Request::getRecordType()
{
   return m_requestHeaderFixedArea.recordType;
}

DStringA VMV002Request::getVersion()
{
   return m_requestHeaderFixedArea.version;
}

DStringA VMV002Request::getPacketLength()
{
   return m_requestHeaderFixedArea.packetLength;
}

unsigned long VMV002Request::getPacketLength( unsigned long &packetLength )
{
   sscanf( m_requestHeaderFixedArea.packetLength, "%ld", &packetLength );
   return packetLength;
}

DStringA VMV002Request::getEncryption()
{
   return m_requestHeaderFixedArea.encryption;
}

DStringA VMV002Request::getCompression()
{
   return m_requestHeaderFixedArea.compression;
}

DStringA VMV002Request::getNameSpace()
{
   return m_requestHeaderFixedArea.nameSpace;
}

DStringA VMV002Request::getHeader( unsigned long dataLength )
{
   char headerBuffer[19], lenBuffer[10];
   char *buffPtr = headerBuffer;
   int buffLen;
   DStringA header, tagHeader, tagValue;
   TagMapType::iterator iter;
   iter = m_tagMap.find( "AAAC" );
   if ( iter != m_tagMap.end() )
   {
      tagValue = (*iter).second;
   }
   else
   {
      tagValue = "S";
   }
   if ( tagValue == "S" )
   {
      iter = m_tagMap.find( "AAAE" );
      if ( iter == m_tagMap.end() )
      {
         m_tagMap["AAAE"] = "                ";
      }
      else if ( (*iter).second == "" )
      {
         m_tagMap["AAAE"] = "                ";
      }
   }
   for ( iter = m_tagMap.begin(); iter != m_tagMap.end();
         ++iter )
   {
      if ( strcmp( (*iter).second.c_str(), "" ))
      {
         tagHeader += (*iter).first;
         memset( lenBuffer, 0, 10 );
         buffLen = strlen( (*iter).second.c_str() );
         if ( buffLen > 99 )
         {
            sprintf( lenBuffer, "%d", buffLen );
            char plusLenBuffer[3];
            plusLenBuffer[0] = '+';
            plusLenBuffer[1] = '0' + strlen( lenBuffer );
            plusLenBuffer[2] = '\0';
            tagHeader += plusLenBuffer;
            tagHeader += lenBuffer;
         }
         else
         {
            sprintf( lenBuffer, "%.2d", buffLen );
            tagHeader += lenBuffer;
         }
         tagHeader += (*iter).second;
      }
   }
   memset( headerBuffer, 0, 19 );
   setPacketLength( dataLength + strlen( tagHeader.c_str() ) + 18 );
   memcpy( buffPtr, &m_requestHeaderFixedArea.recordType, 1 );
   buffPtr += 1;
   memcpy( buffPtr, m_requestHeaderFixedArea.version, 3 );
   buffPtr += 3;
   memcpy( buffPtr, m_requestHeaderFixedArea.packetLength, 8 );
   buffPtr += 8;
   memcpy( buffPtr, m_requestHeaderFixedArea.encryption, 2 );
   buffPtr += 2;
   memcpy( buffPtr, m_requestHeaderFixedArea.compression, 2 );
   buffPtr += 2;
   memcpy( buffPtr, m_requestHeaderFixedArea.nameSpace, 2 );
   header = headerBuffer;
   header += tagHeader;
   return header;
}

DStringA VMV002Request::getHeader()
{
   return getHeader( 0 );
}

//************************************************************************
//              Revision Control Entries
//************************************************************************
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
// $Log:   Y:/VCS/iFastAWD/diview/vmv002request.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:24:14   kovacsro
// Initial revision.
//
//   Rev 1.2   May 21 2001 13:33:50   DT21858
//Added include of srcprag
//

