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

#ifndef VMV002RESPONSE_HPP
   #include "vmv002response.hpp"
#endif


#define PB00251_SIZE 27

VMV002Response::VMV002Response( unsigned char *buffer )
 : m_dataBuffer( NULL ), m_fixedPointer( NULL ), m_repeatPointer( NULL ),
   m_dataLength( 0 ), m_fixedLength( 0 ), m_repeatLength( 0 ), m_numRepeats( 0 )
{
   unsigned char *buffPtr = buffer;
   long buffLen;
   char *tempBuffer;
   DStringA tempString;
   unsigned long valueLength, lengthLength;
   long bytesLeft;
   char tagBuffer[ 5 ], lenBuffer[ 10 ];
   try
   {
      m_responseHeaderFixedArea.recordType = buffPtr[0];
      buffPtr += 1;
      memcpy( m_responseHeaderFixedArea.version, buffPtr, 3 );
      buffPtr += 3;
      memcpy( m_responseHeaderFixedArea.packetLength, buffPtr, 8 );
      buffPtr += 8;
      sscanf( m_responseHeaderFixedArea.packetLength, "%8d", &buffLen );
      memcpy( m_responseHeaderFixedArea.encryption, buffPtr, 2 );
      buffPtr += 2;
      memcpy( m_responseHeaderFixedArea.compression, buffPtr, 2 );
      buffPtr += 2;
      memcpy( m_responseHeaderFixedArea.nameSpace, buffPtr, 2 );
      buffPtr += 2;
      memcpy( m_responseHeaderFixedArea.returnCode, buffPtr, 4 );
      buffPtr += 4;

      bytesLeft = buffLen - 22;
      memset( tagBuffer, 0, 5 );

      while ( bytesLeft > 0 )
      {
         if ( bytesLeft > 4 )
         {
            memcpy( tagBuffer, buffPtr, 4 );
            buffPtr += 4;
            bytesLeft -= 4;
            memcpy( lenBuffer, buffPtr, 2 );
            buffPtr += 2;
            bytesLeft -= 2;
            if ( lenBuffer[0] == '+' )
            {
               lengthLength = lenBuffer[1] - '0';
               memcpy( lenBuffer, buffPtr, lengthLength );
               buffPtr += lengthLength;
               bytesLeft -= lengthLength;
            }
            sscanf( lenBuffer, "%d", &valueLength );
            if ( !strcmp( tagBuffer, "AAAL" )) // is this the data itself?
            {
               m_dataBuffer = new unsigned char[ valueLength ];
               memcpy( m_dataBuffer, buffPtr, valueLength );
               buffPtr += valueLength;
               bytesLeft -= valueLength;
               m_dataLength = valueLength;
            }
            else
            {
               tempBuffer = new char[ valueLength + 1 ];
               memset( tempBuffer, 0, valueLength + 1 );
               memcpy( tempBuffer, buffPtr, valueLength );
               buffPtr += valueLength;
               bytesLeft -= valueLength;
               tempString = tempBuffer;
               delete [] tempBuffer;
               m_tagMap[ tagBuffer ] = tempString;
            }
         }
      }
   }
   catch(...)
   {
   }
   TagMapType::iterator iter;
   iter = m_tagMap.find( "AAAN" );
   if ( iter != m_tagMap.end() )
   {
      sscanf( (*iter).second.c_str(), "%ld", &m_fixedLength );
   }
   iter = m_tagMap.find( "AAAO" );
   if ( iter != m_tagMap.end() )
   {
      sscanf( (*iter).second.c_str(), "%ld", &m_repeatRecordLength );
   }
   iter = m_tagMap.find( "AAAP" );
   if ( iter != m_tagMap.end() )
   {
      sscanf( (*iter).second.c_str(), "%ld", &m_numRepeats );
   }
   m_repeatLength = m_numRepeats * m_repeatRecordLength;
   if ( m_repeatLength == 0 )
   {
      m_repeatPointer = NULL;
   }
   else
   {
      m_repeatPointer = m_dataBuffer + m_fixedLength;
   }
   if ( m_fixedLength == 0 )
   {
      m_fixedPointer = NULL;
   }
   else
   {
      m_fixedPointer = m_dataBuffer;
   }
}

VMV002Response::~VMV002Response()
{
   delete [] m_dataBuffer;
}

DStringA VMV002Response::getTransactionId()
{
   TagMapType::iterator iter = m_tagMap.find( "AAAA" );
   if (  iter != m_tagMap.end() )
   {
      return (*iter).second;
   }
   return "";
}

DStringA VMV002Response::getOperatorId()
{
   TagMapType::iterator iter = m_tagMap.find( "AAAB" );
   if (  iter != m_tagMap.end() )
   {
      return (*iter).second;
   }
   return "";
}

DStringA VMV002Response::getSessionKey()
{
   TagMapType::iterator iter = m_tagMap.find( "AAAE" );
   if (  iter != m_tagMap.end() )
   {
      return (*iter).second;
   }
   return "";
}

DStringA VMV002Response::getTraceFlag()
{
   TagMapType::iterator iter = m_tagMap.find( "AAAI" );
   if (  iter != m_tagMap.end() )
   {
      return (*iter).second;
   }
   return "";
}

DStringA VMV002Response::getReturnCodeLocation()
{
   TagMapType::iterator iter = m_tagMap.find( "AAAM" );
   if (  iter != m_tagMap.end() )
   {
      return (*iter).second;
   }
   return "";
}

unsigned long VMV002Response::getNonRepeatLength()
{
   return m_fixedLength;
}

unsigned long VMV002Response::getRepeatRecordLength()
{
   return m_repeatRecordLength;
}

unsigned long VMV002Response::getNumRepeats()
{
   return m_numRepeats;
}

unsigned long VMV002Response::getRepeatLength()
{
   return m_repeatLength;
}

DStringA VMV002Response::getClientData()
{
   TagMapType::iterator iter = m_tagMap.find( "AAAJ" );
   if (  iter != m_tagMap.end() )
   {
      return (*iter).second;
   }
   return "";
}

DStringA VMV002Response::getDataVersion()
{
   TagMapType::iterator iter = m_tagMap.find( "AAAK" );
   if (  iter != m_tagMap.end() )
   {
      return (*iter).second;
   }
   return "";
}

unsigned long VMV002Response::getDataLength()
{
   return m_dataLength;
}

void VMV002Response::getData( void *buffer, unsigned long buffLen )
{
   if ( buffLen > m_dataLength )
   {
      memcpy( buffer, m_dataBuffer, m_dataLength );
   }
   else
   {
      memcpy( buffer, m_dataBuffer, buffLen );
   }
}

void VMV002Response::getFixedData( void *buffer, unsigned long buffLen )
{
   if ( m_fixedPointer )
   {
      if ( buffLen > m_fixedLength )
      {
         memcpy( buffer, m_fixedPointer, m_fixedLength );
      }
      else
      {
         memcpy( buffer, m_fixedPointer, buffLen );
      }
   }
}

void VMV002Response::getRepeatData( void *buffer, unsigned long buffLen )
{
   if ( m_repeatPointer )
   {
      if ( buffLen > m_repeatLength )
      {
         memcpy( buffer, m_repeatPointer, m_repeatLength );
      }
      else
      {
         memcpy( buffer, m_repeatPointer, buffLen );
      }
   }
}

void VMV002Response::setRecordType( char recType )
{
   m_responseHeaderFixedArea.recordType = recType;
}

void VMV002Response::setVersion( const DStringA &version )
{
   strncpy( m_responseHeaderFixedArea.version, version.c_str(), 3 );
}

void VMV002Response::setPacketLength( unsigned long packetLength )
{
   char tempPacketLen[ 9 ];
   sprintf( tempPacketLen, "%ld", packetLength );
   strncpy( m_responseHeaderFixedArea.packetLength, tempPacketLen, 8 );
}

void VMV002Response::setEncryption( const DStringA &encryption )
{
   strncpy( m_responseHeaderFixedArea.encryption, encryption.c_str(), 2 );
}

void VMV002Response::setCompression( const DStringA &compression )
{
   strncpy( m_responseHeaderFixedArea.compression, compression.c_str(), 2 );
}

void VMV002Response::setNameSpace( const DStringA &nameSpace )
{
   strncpy( m_responseHeaderFixedArea.nameSpace, nameSpace.c_str(), 2 );
}

char VMV002Response::getRecordType()
{
   return m_responseHeaderFixedArea.recordType;
}

DStringA VMV002Response::getVersion()
{
   return DStringA( m_responseHeaderFixedArea.version, 3 );;
}

DStringA VMV002Response::getPacketLength()
{
   return DStringA( m_responseHeaderFixedArea.packetLength, 8 );;
}

unsigned long VMV002Response::getPacketLength( unsigned long &packetLength )
{
   sscanf( m_responseHeaderFixedArea.packetLength, "%ld", &packetLength );
   return packetLength;
}

DStringA VMV002Response::getEncryption()
{
   return DStringA( m_responseHeaderFixedArea.encryption, 2 );;
}

DStringA VMV002Response::getCompression()
{
   return DStringA( m_responseHeaderFixedArea.compression, 2 );;
}

DStringA VMV002Response::getNameSpace()
{
   return DStringA( m_responseHeaderFixedArea.nameSpace, 2 );;
}

DStringA VMV002Response::getReturnCode()
{
   DStringA retVal( m_responseHeaderFixedArea.returnCode, 4 );
   retVal.stripLeading( '0' );
   return retVal;
}

DStringA VMV002Response::dumpTags()
{
   DStringA returnValue;
   for ( TagMapType::iterator iter = m_tagMap.begin();
         iter != m_tagMap.end(); ++iter )
   {
      returnValue += (*iter).first;
      returnValue += "=";
      returnValue += (*iter).second;
      returnValue += ";";
   }
   return returnValue;
}


unsigned long VMV002Response::getPB00251( unsigned char *pBuffer )
{
   sprintf( ( char * )( pBuffer ),
            "%05.5lu%05.5lu%03.3lu%-8.8s%03.3u%03.3s",
            getNonRepeatLength(),
            getRepeatRecordLength(),
            getNumRepeats(),
            getOperatorId().c_str(),
            getReturnCode().asInteger(),
            "0" ); // Requestor_Data_Length_Cnt_Out?

   getData( pBuffer + PB00251_SIZE, m_dataLength );
   return PB00251_SIZE + m_dataLength;
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
// $Log:   Y:/VCS/iFastAWD/diview/vmv002response.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:24:16   kovacsro
// Initial revision.
//
//   Rev 1.3   Aug 31 2001 16:44:16   DT11159
//Freed m_dataBuffer in destructor (was a leak).
//Removed memcpy in getFixedData and getRepeatData.  These
//calls to memcpy would cause an access violation if executed.
//
//
//   Rev 1.2   May 21 2001 13:33:56   DT21858
//Added include of srcprag
//

