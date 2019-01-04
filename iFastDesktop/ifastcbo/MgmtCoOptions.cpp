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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : MgmtCoOptions.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : 10/14/1999
//
// ^CLASS    : MgmtCoOptions
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "version_App.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_req.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_req.hpp>
#include <ifastdataimpl\dse_dstc0263_vw.hpp>
#include <ifastdataimpl\dse_dstc0263_req.hpp>
#include <ifastdataimpl\dse_dstc0344_vw.hpp>
#include <ifastdataimpl\dse_dstc0344_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MGMT_CO_OPTIONS;
   extern CLASS_IMPORT const DSTCRequest MGMT_CO_OPTIONS_NEXT;
   extern CLASS_IMPORT const DSTCRequest MGMT_CO_OPTIONS_AMS_RESTRICTION;
   extern CLASS_IMPORT const DSTCRequest TRADE_CONTROL_OPTION;
}

namespace
{
   const I_CHAR * const CLASSNAME   = I_( "MgmtCoOptions" );
}

namespace CND
{  // Conditions used
   extern const long IFASTCBO_ERR_VERSION_MISMATCH;
   extern const long IFASTCBO_WARN_VERSION_MISMATCH;
}
//******************************************************************************
MgmtCoOptions::MgmtCoOptions( BFAbstractCBO &parent ) : MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setVersionable( false );
}

//******************************************************************************
MgmtCoOptions::~MgmtCoOptions()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY MgmtCoOptions::init( const DString& dstrTrack,const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData083 (ifds::DSTC0083_REQ),
      queryData149 (ifds::DSTC0149_REQ),
      queryData263 (ifds::DSTC0263_REQ);

   DString mgmtCoIdOut;
   queryData149.setElementValue (ifds::CompanyId,  getMgmtCoId (mgmtCoIdOut));
   queryData149.setElementValue (ifds::Track, dstrTrack);
   queryData149.setElementValue (ifds::Activity, dstrPageName);
   SEVERITY vew149ret = ReceiveData ( DSTC_REQUEST::MGMT_CO_OPTIONS_NEXT, 
                 queryData149, 
                 ifds::DSTC0149_VW, 
                 DSTCRequestor (getSecurity())
               );
   if(vew149ret  > WARNING)
      return GETCURRENTHIGHESTSEVERITY(); 

   DString dstrAppVersion = ifds::getAppVersion();
//   dstrAppVersion = I_("16.3.0.0"); // QA
//   dstrAppVersion = I_("16.3.6"); // UAT
   if(i_strncmp(dstrAppVersion.c_str(), I_("Dev"), 3))// && i_strcmp(dstrAppVersion.c_str(), I_("Dev")))
   {
      ifds::IfdsVersionInfo ifdsAppVersion(dstrAppVersion);

      DString dstrVersionLabel;
      getField(ifds::VersionLabel, dstrVersionLabel, BF::HOST);

      ifds::IfdsVersionInfo ifdsVersionInfoLabel(dstrVersionLabel);
                  
      if(i_strcmp(ifdsVersionInfoLabel.versionMajor.c_str(), ifdsAppVersion.versionMajor.c_str()))
      {
         DString idiStr;
         addIDITagValue(idiStr, I_("DSK_VER"), dstrAppVersion);
         addIDITagValue(idiStr, I_("DB_VER"), dstrVersionLabel);

         ADDCONDITIONFROMFILEIDI (CND::IFASTCBO_ERR_VERSION_MISMATCH, idiStr);
         return GETCURRENTHIGHESTSEVERITY(); 
      }
      else if( i_strcmp(ifdsVersionInfoLabel.versionMinor.c_str(), ifdsAppVersion.versionMinor.c_str()) )
      {
         DString idiStr;
         addIDITagValue(idiStr, I_("DSK_VER"), dstrAppVersion);
         addIDITagValue(idiStr, I_("DB_VER"), dstrVersionLabel);

         ADDCONDITIONFROMFILEIDI (CND::IFASTCBO_WARN_VERSION_MISMATCH, idiStr);
      }
   }


//call view 83
   queryData083.setElementValue (ifds::CompanyId,mgmtCoIdOut);
   queryData083.setElementValue (ifds::Track, dstrTrack );
   queryData083.setElementValue (ifds::Activity, dstrPageName);
   AsyncReceiveData ( DSTC_REQUEST::MGMT_CO_OPTIONS, 
                      queryData083, 
                      ifds::DSTC0083_VW, 
                      DSTCRequestor (getSecurity())
                    );
//call view 263
   queryData263.setElementValue (ifds::CompanyId, mgmtCoIdOut);
   queryData263.setElementValue (ifds::Track, dstrTrack);
   queryData263.setElementValue (ifds::Activity, dstrPageName);
   AsyncReceiveData ( DSTC_REQUEST::MGMT_CO_OPTIONS_AMS_RESTRICTION, 
                      queryData263, 
                      ifds::DSTC0263_VW, 
                      DSTCRequestor( getSecurity())
                    );

// view 344
   BFData queryData0344 (ifds::DSTC0344_REQ);
   queryData0344.setElementValue (ifds::CompanyId, mgmtCoIdOut);
   queryData0344.setElementValue (ifds::Track, dstrTrack);
   queryData0344.setElementValue (ifds::Activity, dstrPageName);
   AsyncReceiveData ( DSTC_REQUEST::TRADE_CONTROL_OPTION, 
                      queryData0344, 
                      ifds::DSTC0344_VW, 
                      DSTCRequestor( getSecurity())
                    );
   return GETCURRENTHIGHESTSEVERITY(); 
}

//******************************************************************************
void MgmtCoOptions::getField( const BFFieldId& idField, DString &dstrFieldValue, 
                              const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{
   // This is just a quick solution to enforce the banking format for all Canadian clients as 
   // this is the standard banking format in Canada. None of the Canadian client has generic control
   // set up to enforce to format. Base system on hard code format based on the banking layout
   // feature. This solution minimize changes required for each individual CBO to cope with Canadian
   // and internation clients.   W. Shiu Oct 12, 2000
   if( idField == ifds::BankingFormat ||
       idField == ifds::InstCodeMax ||
       idField == ifds::TransitNoMax || 
       idField == ifds::BankAcctNumMax )
   {
      if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
      {
         if (idField == ifds::BankingFormat)
         {
            dstrFieldValue = I_( "Y" );
         }
         if (idField == ifds::InstCodeMax)
         {
            dstrFieldValue = I_( "3" );
         }
         if (idField == ifds::TransitNoMax)
         {
            dstrFieldValue = I_( "5" );
         }
         if (idField == ifds::BankAcctNumMax)
         {
            dstrFieldValue = I_( "12" );
         }
      }
      else BFCBO::getField( idField, dstrFieldValue, idDataGroup, formattedReturn );
   }
   else
   {
      BFCBO::getField( idField, dstrFieldValue, idDataGroup, formattedReturn );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MgmtCoOptions.cpp-arc  $
 * 
 *    Rev 1.26   May 18 2005 09:03:14   yingbaol
 * PET1203,FN01 Commission-Class A enhancement
 * 
 *    Rev 1.25   Dec 10 2004 14:53:12   hernando
 * PET1117 - Recovered version feature.
 * 
 *    Rev 1.24   Nov 27 2004 19:44:54   popescu
 * PET 1117/56, removed two validation methods from MgmtCoOptions. Either we have all of them here or none. Moved the methods to the CBO's that require 'em.
 * 
 *    Rev 1.23   Nov 24 2004 10:18:42   yingbaol
 * PET1117:temperary take out version features
 * 
 *    Rev 1.22   Nov 18 2004 13:28:20   YINGBAOL
 * PET1117: Perfermance Tunning
 * 
 *    Rev 1.21   Nov 14 2004 14:50:14   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.20   Jul 30 2003 14:17:52   linmay
 * added view 263
 * 
 *    Rev 1.19   May 30 2003 11:22:04   popescu
 * fixed logging issue with views 83 an 149
 * 
 *    Rev 1.18   Mar 21 2003 18:18:48   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Oct 09 2002 23:54:46   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.16   Aug 29 2002 12:56:20   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.15   22 May 2002 18:29:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.14   07 May 2001 13:19:02   SMITHDAV
 * Session sync-up.
 * 
 *    Rev 1.13   Apr 05 2001 11:43:50   HUANGSHA
 * bug fix for getting vw149
 * 
 *    Rev 1.12   Mar 30 2001 11:05:00   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.11   Mar 09 2001 11:37:14   OLTEANCR
 * added ResponseData(..) for view DSTC0149_VW
 * 
 *    Rev 1.10   09 Feb 2001 14:56:16   SMITHDAV
 * Do Async Requests...
 * 
 *    Rev 1.9   Jan 18 2001 16:05:40   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.8   Dec 17 2000 20:24:10   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.7   Dec 06 2000 13:59:44   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.6   Dec 01 2000 10:56:30   DINACORN
 * "Yes" replaced with "Y"
 * 
 *    Rev 1.5   Nov 06 2000 16:18:30   OLTEANCR
 * added  'closeAcctRedCode'  function
 * 
 *    Rev 1.4   Nov 01 2000 15:30:40   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.3   Oct 17 2000 14:07:08   WINNIE
 * Enforce banking format for Canadian Clients
 * 
 *    Rev 1.2   Aug 23 2000 12:10:46   DINACORN
 * used Dstring::npos for compare at find() function
 * 
 *    Rev 1.1   Aug 17 2000 12:24:42   DINACORN
 * Added method validateIfTaxTypeCanTradeInCurrency( )
 * 
 *    Rev 1.0   Feb 15 2000 11:00:04   SMITHDAV
 * Initial revision.
// 
//    Rev 1.3   Dec 12 1999 16:25:52   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
//    Rev 1.2   Dec 09 1999 10:43:40   POPESCUS
// Fixed some memory leaks
*/