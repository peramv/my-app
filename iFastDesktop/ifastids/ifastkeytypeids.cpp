#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

//defines the key tpes, retured by view#74 which will stop a persistent transaction
namespace KEYTYPES
{
   extern CLASS_EXPORT I_CHAR * const ENTITYID = I_( "EntityId" );
   extern CLASS_EXPORT I_CHAR * const SHRNUM = I_( "ShrNum" );
   extern CLASS_EXPORT I_CHAR * const ACCOUNTNUM = I_( "AccountNum" );
   extern CLASS_EXPORT I_CHAR * const REPORT_NAME = I_( "ReportName" );
   extern CLASS_EXPORT I_CHAR * const SPONSORMODELID = I_( "SponsorModelID" );
}
