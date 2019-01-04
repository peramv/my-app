#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//    AUTHOR : Mihai Virgil Buzila
//    DATE   : 16/04/99
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

#include <ifastdataimpl\dse_dstc0021_req.hpp>
#include <ifastdataimpl\dse_dstc0021_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0063_req.hpp>
#include <ifastdataimpl\dse_dstc0063_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//name of the params used at transfering the search criteria to the business process

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId CHEQUE_DETAILS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId CHEQUE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_DETAIL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_MASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId REMITTANCE_CHEQUE;
}
namespace CHQPROC  //stands for cheque process
{
   const I_CHAR * const TRANS_ID_VALUE = I_( "TransId" );
   const I_CHAR * const ACCOUNT_NUM_VALUE = I_( "AccountNum" );
   const I_CHAR * const IN_CHEQ_NUM_VALUE = I_( "InCheqNum" );
   const I_CHAR * const BROKER_VALUE = I_( "Broker" );
   const I_CHAR * const STATUS_VALUE = I_( "Status" );
   const I_CHAR * const IGNOREDNF = I_( "IgnoreDataNotFound" );
   const I_CHAR * const IGNOREUNKNACC = I_( "IgnoreUnknownAccount" );
   const BFFieldId SHAREHOLDER_NUMBER(500);
   const BFFieldId PRIMARY_ACCOUNT_OWNER(600);
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId NumEntry;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId ChequeAddr;
   extern CLASS_IMPORT const BFTextFieldId ChequesListHeadingSet;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ChequeProcessIncludes.h-arc  $
 * 
 *    Rev 1.12   08 Jan 2009 14:30:12   kovacsro
 * IN#1521695 - GL #1541 - Users received an internal problem error msg from Desktop
 * 
 *    Rev 1.11   Sep 08 2008 16:09:00   jankovii
 * PET 5517 FN71 - Stale Cheque.
 * 
 *    Rev 1.10   May 13 2004 21:06:10   popescu
 * PET 985, FN 01, LSIF Trade entry
 * 
 *    Rev 1.9   Mar 21 2003 17:37:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:53:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:52:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   22 May 2002 18:21:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:15:24   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   Jun 19 2000 14:43:20   HUANGSHA
 * add doGetField(...) for getting ShrNum and EntityName
 * 
 *    Rev 1.3   Jun 09 2000 11:47:28   BUZILA
 * cheque fix
 * 
 *    Rev 1.2   Mar 08 2000 18:20:14   HSUCHIN
 * C2 changes added, but still needs to be converted to use new infra
 * 
 *    Rev 1.1   Feb 15 2000 18:56:18   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.4   Dec 05 1999 18:58:40   VASILEAD
 * Friday night changes( don't be so hard on us )
 * 
 *    Rev 1.3   Aug 26 1999 16:10:40   PRAGERYA
 * Implementing Search for Shareholder and Account Info
 * 
 *    Rev 1.2   Jul 20 1999 13:38:08   POPESCUS
 * Added param to ignore data not found
 * 
 *    Rev 1.1   Jul 08 1999 10:03:34   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

