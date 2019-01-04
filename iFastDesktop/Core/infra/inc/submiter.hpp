#ifndef SUBMITER_HPP
#define SUBMITER_HPP

#  pragma message( "including "__FILE__ )

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/**@pkg DICBOCORE */

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#define  DSTRING_HPP
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
#define COMMONPORT_H
#endif


//forward declares
class Data;

// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif

class CBOBASE_LINKAGE Submiter
{


public:
   Submiter();
   virtual ~Submiter();

   bool submitData( const DString& strData, Data& returnData, const DString& strDataId = I_("") );

private:
   Submiter( const Submiter &copy );
   Submiter& operator=( const Submiter &copy );

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
// $Log:   Y:/VCS/iFastAWD/inc/submiter.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:52   kovacsro
//Initial revision.
// 
//    Rev 1.7   28 Nov 2001 12:42:12   dt14177
// fixed linkage define
// 
//    Rev 1.6   28 Nov 2000 10:46:48   dt14177
// cleanup
#endif