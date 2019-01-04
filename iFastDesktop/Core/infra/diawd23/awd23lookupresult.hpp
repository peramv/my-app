#ifndef AWD23LOOKUPRESULT_HPP
#define AWD23LOOKUPRESULT_HPP

#pragma message( "including "__FILE__ )

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DIAWD23 */    

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif
#ifndef AWDLOOKUPRESULT_HPP
   #include "awdlookupresult.hpp"
#endif

#ifndef AWDSTRCT_H
   #include "awdstrct.h"
#endif

#undef DIAWD23_LINKAGE
#ifdef DIAWD23_DLL
   #define DIAWD23_LINKAGE CLASS_EXPORT
#else
   #define DIAWD23_LINKAGE CLASS_IMPORT
#endif

class DIAWD23_LINKAGE Awd23LookupResult : public AwdLookupResult
{
   public:
      Awd23LookupResult( AWDOBJ &obj );
      virtual ~Awd23LookupResult();
};



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
// $Log:   Y:/VCS/iFastAWD/diawd23/awd23lookupresult.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:16:34   kovacsro
//Initial revision.
// 
//    Rev 1.2   05 Dec 2000 14:18:56   dt14177
// cleanup
// 
//    Rev 1.1   Apr 09 1999 13:50:42   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.1.0   Mar 31 1999 13:20:58   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0   Jan 20 1999 09:10:28   DMUM
//
//
//

#endif // AWD23LOOKUPRESULT_HPP

