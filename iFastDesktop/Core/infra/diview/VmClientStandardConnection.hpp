#pragma message( "including "__FILE__ )

#ifndef VMCLIENTSTANDARDCONNECTION_HPP
#define VMCLIENTSTANDARDCONNECTION_HPP

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2001 by DST Systems, Inc.
 */

#ifndef PLATFORM_H
   #include "platform.h"
#endif
#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif
#ifndef VMCLIENTCONNECTION_HPP
   #include "vmclientconnection.hpp"
#endif

extern "C"
{
#include <vm.h>
#include <vmdll.h>
#include <vmdst.h>
}

/**
 * View Manager Standard Connection class
 */
class DIVIEW_LINKAGE VmClientStandardConnection : public VmClientConnection
{
public:
   /**
    * Constructor
    *
    * @param hostId          The name of target host.  The default host
    *                        configured in View Manager will be used if this
    *                        hostId is an empty string.
    * @param connectionName  The name of the connection to View Manager client.
    */
   VmClientStandardConnection( const DString & hostId,
                               const DString & connectionName  );
   virtual ~VmClientStandardConnection( );

   /**
    * Used to send a request to the host.
    *
    * @param requestName  name of the request.
    *
    * @param request      data to send.
    *
    * @param timeout      maximum number of seconds to wait for a response.  If
    *                     this value is zero, or > 0xFFFF, the maximum wait will
    *                     be INFINITE.
    */
   virtual void send( const DString & viewName,
                      const DString & request,
                      unsigned long timeout );

protected:
   virtual void connect( );
   virtual void disconnect( );

private:
   VMCON _vmConnection;
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
// $Log:   Y:/VCS/iFastAWD/diview/VmClientStandardConnection.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:24:12   kovacsro
//Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:27:46   DT11159
// 
//
//

#endif
