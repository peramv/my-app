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
// ^FILE   : Awd23LookupResult.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 6 Jan 1998
//
// ----------------------------------------------------------
//
// ^CLASS    : Awd23LookupResult
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define DIAWD23_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#include "stdafx.h"

#ifndef AWD23LOOKUPRESULT_HPP
   #include "awd23lookupresult.hpp"
#endif

//******************************************************************************
//              Public Methods
//******************************************************************************

Awd23LookupResult::Awd23LookupResult( AWDOBJ &obj )
{
   switch ( obj.awdobjkey.recordcd )
   {
      case 'C':
      case 'T':
         m_unit = DStringA( obj.awddata.awdwrkobj.unitcd, 10 );
         m_wrkt = DStringA( obj.awddata.awdwrkobj.wrktype, 10 );
         m_stat = DStringA( obj.awddata.awdwrkobj.statcd, 10 );
         m_queu = DStringA( obj.awddata.awdwrkobj.queuecd, 8 );
         break;

      case 'O':
         m_unit = DStringA( obj.awddata.awdsrcobj.unitcd, 10 );
         m_objt = DStringA( obj.awddata.awdsrcobj.objtype, 10 );
         break;
   }

   m_crda = DStringA( obj.awdobjkey.crdattim, 26 );
   m_reco = DStringA( 1, obj.awdobjkey.recordcd );
   m_crno = DStringA( obj.awdobjkey.crnode, 2 );
}

Awd23LookupResult::~Awd23LookupResult()
{
}

//******************************************************************************
//              Protected Methods
//******************************************************************************



//******************************************************************************
//              Private Methods
//******************************************************************************


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
// $Log:   Y:/VCS/iFastAWD/diawd23/awd23lookupresult.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:16:34   kovacsro
// Initial revision.
// 
//    Rev 1.2   Jun 10 1999 15:56:22   DMUM
// Bux Fix
//
//    Rev 1.1   Apr 09 1999 13:50:40   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.2.0   Mar 31 1999 13:20:56   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0.1.0   Feb 19 1999 07:48:52   DMUM
// Added lookupSource()
//
//    Rev 1.0   Jan 20 1999 09:10:26   DMUM
//
//
//

