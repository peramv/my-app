#ifndef VMV002RESPONSEHEADER_HPP
#define VMV002RESPONSEHEADER_HPP

#include <map>
#include "dstringa.hpp"

#  pragma message( "including "__FILE__ )

typedef struct _fixedResponseHeader
{
   char recordType;
   char version[ 3 ];
   char packetLength[ 8 ];
   char encryption[ 2 ];
   char compression[ 2 ];
   char nameSpace[ 2 ];
   char returnCode[ 4 ];
} FixedResponseHeader;

#undef DIVIEW_LINKAGE
#ifdef DIVIEW_DLL
   #define DIVIEW_LINKAGE CLASS_EXPORT
#else
   #define DIVIEW_LINKAGE CLASS_IMPORT
#endif

class DIVIEW_LINKAGE VMV002Response
{
public:
   VMV002Response( unsigned char *buffer );
   virtual ~VMV002Response();

DStringA dumpTags();

   virtual void setRecordType( char recType );
   virtual void setVersion( const DStringA &version );
   virtual void setPacketLength( unsigned long packetLength );
   virtual void setEncryption( const DStringA &encryption );
   virtual void setCompression( const DStringA &compression );
   virtual void setNameSpace( const DStringA &nameSpace );

   virtual char getRecordType();
   virtual DStringA getVersion();
   virtual DStringA getPacketLength();
   virtual unsigned long getPacketLength( unsigned long &packetLength );
   virtual DStringA getEncryption();
   virtual DStringA getCompression();
   virtual DStringA getNameSpace();
   virtual DStringA getReturnCode();

   virtual DStringA getTransactionId();
   virtual DStringA getOperatorId();
   virtual DStringA getSessionKey();
   virtual DStringA getTraceFlag();
   virtual DStringA getReturnCodeLocation();
   virtual unsigned long getNonRepeatLength();
   virtual unsigned long getRepeatRecordLength();
   virtual unsigned long getNumRepeats();
   virtual DStringA getClientData();
   virtual DStringA getDataVersion();
   virtual void getData( void *buffer, unsigned long buffLen );
   virtual void getFixedData( void *buffer, unsigned long buffLen );
   virtual void getRepeatData( void *buffer, unsigned long buffLen );
   virtual unsigned long getDataLength();
   virtual unsigned long getRepeatLength();

   unsigned long getPB00251( unsigned char * );

private:
   FixedResponseHeader m_responseHeaderFixedArea;
   typedef std::map< DStringA, DStringA, std::less< DStringA > > TagMapType;
   TagMapType m_tagMap;
   unsigned char *m_dataBuffer, *m_fixedPointer, *m_repeatPointer;
   unsigned long m_dataLength, m_fixedLength, m_repeatLength;
   unsigned long m_numRepeats, m_repeatRecordLength;

   VMV002Response( const VMV002Response &copy );
   VMV002Response &operator=( const VMV002Response );
};


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

#endif
