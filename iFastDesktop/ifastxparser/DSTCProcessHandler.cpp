/*******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 *
*******************************************************************************/

#include "stdafx.h"
#define IFASTXPARSER_DLL

#include "dstcprocesshandler.hpp"
#include <bfproc\abstractprocess.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\InterProcessData.hpp>

using namespace xp;

namespace
{
   const I_CHAR * const CLASSNAME = I_( "NASUChildProcessHandler" );

   const I_CHAR * const TRACK = I_("ETRACK");
   const I_CHAR * const ACTIVITY = I_("ACTIVITY");  
   const I_CHAR * const YES_TRACK = I_("Y");    
   const I_CHAR * const NO_TRACK = I_("N");    
}

namespace ELEMENT_NAME
{
   extern const I_CHAR * BATCH;

   extern const I_CHAR * NASU;
   extern const I_CHAR * PURCHASE;
   extern const I_CHAR * REDEMPTION;
   extern const I_CHAR * EXCHANGE;
};

//******************************************************************************
DSTCProcessHandler::ETrackMap DSTCProcessHandler::eTrackMap_;

//******************************************************************************
DSTCProcessHandler::DSTCProcessHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes ) :
ProcessHandler( parentHandler, elementName, attributes )
{
}

bool DSTCProcessHandler::requiresWorkSession() // const
{
   const DString &name = getName();
   if ( name == I_("Shutdown") || name == I_("MgmtCoRefresh") ) 
   {
      return false;
   }
   else
   {
      return true;
   }
}


//******************************************************************************
void DSTCProcessHandler::setProcessParms( AbstractProcess *process )
{
   setProcessTrackParms( process );
}

//******************************************************************************
void DSTCProcessHandler::setProcessTrackParms( AbstractProcess *process )
{

   InterProcessData& ipd = process->getGIContainer()->getInterProcessData();

   // top level processes only
   if( getParent()->getName() == ELEMENT_NAME::BATCH )
   {
      ETrackMap::iterator iter = eTrackMap_.find( getName() );

      if( iter != eTrackMap_.end() )
      {
         ipd.setParameter( TRACK, YES_TRACK );
         ipd.setParameter( ACTIVITY, (*iter).second );
         return;
      }
   }

   ipd.setParameter( TRACK, NO_TRACK );
   ipd.setParameter( ACTIVITY, NULL_STRING );

}

//******************************************************************************
DSTCProcessHandler::ETrackMap::ETrackMap()
{
//   addItem( I_("AccountDistributionProcess"), I_("APIDISTRIBUITION") );
   addItem( ELEMENT_NAME::PURCHASE,           I_("APITRADE") );
   addItem( ELEMENT_NAME::REDEMPTION,         I_("APITRADE") );
   addItem( ELEMENT_NAME::EXCHANGE,           I_("APITRADE") );
   addItem( ELEMENT_NAME::NASU,               I_("APINASU") );
   addItem( I_("AccountDetailsProcess"),      I_("APIACCTDETAIL") );

//   addItem( I_("MgmtCoRefresh"),              I_("APIMGMTCOREFRESH") );
//   addItem( I_("AvailabilityProcess"),        I_("APIAVAILABILITY") );
}

//******************************************************************************
void DSTCProcessHandler::ETrackMap::addItem( const DString &processName, const DString &trackActivity )
{
   assert( insert( value_type( processName, trackActivity ) ).second );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/DSTCProcessHandler.cpp-arc  $
// 
//    Rev 1.7   Nov 17 2004 15:01:08   PURDYECH
// PET910 - .NET Conversion
// 
//    Rev 1.6   Nov 16 2004 11:14:28   PURDYECH
// PET910 - .NET Conversion
// 
//    Rev 1.5   May 27 2004 16:29:52   SMITHDAV
// Changes to InterProcessData to move "global data" to the session level.
// 
//    Rev 1.4   May 10 2004 19:28:54   SMITHDAV
// Add requiresWorksession() override.
// 
//    Rev 1.2   Oct 09 2002 23:56:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.1   Jul 04 2002 15:23:22   SMITHDAV
// NASU support and minor interface changes.
// 
//    Rev 1.0   Jun 18 2002 09:50:18   SMITHDAV
// Initial revision.
 * 
 */
