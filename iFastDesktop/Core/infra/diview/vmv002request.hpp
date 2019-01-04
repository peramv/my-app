#ifndef VMV002REQUEST_HPP
#define VMV002REQUEST_HPP

#include <map>
#include "dstringa.hpp"

#  pragma message( "including "__FILE__ )

typedef struct _fixedRequestHeader
{
   char recordType;
   char version[ 3 ];
   char packetLength[ 8 ];
   char encryption[ 2 ];
   char compression[ 2 ];
   char nameSpace[ 2 ];
} FixedRequestHeader;

#undef DIVIEW_LINKAGE
#ifdef DIVIEW_DLL
   #define DIVIEW_LINKAGE CLASS_EXPORT
#else
   #define DIVIEW_LINKAGE CLASS_IMPORT
#endif

class DIVIEW_LINKAGE VMV002Request
{
public:
   VMV002Request( const char *viewName, const char *operatorId,
                  const char *password, const char *newPassword = "",
                  const char *securityType = "S", const char *sessionKey = "",
                  const char *sourceSystemId = "",
                  const char *locationId = "",
                  const char *targetRoutingId = "", const char *traceFlag = "N",
                  const char *clientData = "",
                  const char *dataVersion = "001" );
   VMV002Request( const unsigned char *pb00250Request,
                  unsigned long ulRequestLength,
                  const char *password, const char *sourceSystemId = "",
                  const char *newPassword = "",
                  const char *securityType = "S", const char *sessionKey = "",
                  const char *locationId = "",
                  const char *targetRoutingId = "", const char *traceFlag = "N",
                  const char *clientData = "",
                  const char *dataVersion = "001" );
   virtual ~VMV002Request();

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

   void setTaggedValue( char *tag, char *value );
   virtual DStringA getHeader( unsigned long dataLength );
   virtual DStringA getHeader();

   static const char * getMACAddress();

private:

   FixedRequestHeader m_requestHeaderFixedArea;
   typedef std::map< DStringA, DStringA, std::less< DStringA > > TagMapType;
   TagMapType m_tagMap;

   VMV002Request( const VMV002Request &copy );
   VMV002Request &operator=( const VMV002Request );
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
