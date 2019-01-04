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
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

//name of the params used at transfering the search criteria to the business process
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0023_req.hpp>
#include <ifastdataimpl\dse_dstc0023_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0063_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FI_FUND_DETAIL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FI_FUND_INFO_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FI_FUND_MASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FI_PROC_GEN_LIST;
   extern IFASTBP_LINKAGE const BFContainerId UNIT_FACTORS_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundInfoHeading;
   extern CLASS_IMPORT const BFTextFieldId UnitFactorHeading;
   extern CLASS_IMPORT const BFTextFieldId UnitFactor;
   extern CLASS_IMPORT const BFDecimalFieldId FactorRate;
}

#define FUND_CODE_VALUE			    I_( "FundCodeValue" )
#define CLASS_CODE_VALUE	     	 I_( "ClassCodeValue" )
#define FROM_DATE_VALUE			    I_( "FromDateValue" )
#define TO_DATE_VALUE			    I_( "ToDateValue" )
#define PREV_DATE_PRESSED_VALUE   I_( "PrevDatePressedValue" )
#define NEXT_DATE_PRESSED_VALUE   I_( "NextDatePressedValue" )
#define NEXT_KEY_VALUE            I_( "NextKeyValue" )


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundInfoProcessIncludes.h-arc  $
 * 
 *    Rev 1.8   Sep 17 2004 13:38:58   popescu
 * PET1117 FN22 - revert fund factors dialog display to old logic
 * 
 *    Rev 1.7   Sep 09 2004 11:37:00   HERNANDO
 * PET1117 FN22 - WKN & ISIN Enhancement.
 * 
 *    Rev 1.6   Mar 21 2003 17:40:32   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:53:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   22 May 2002 18:20:56   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:17:08   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Mar 13 2000 17:27:44   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.1   Feb 15 2000 18:56:30   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:10   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.4   Aug 09 1999 17:11:06   BUZILA
 * fixed list IDs
 * 
 *    Rev 1.3   Aug 05 1999 14:16:42   DT24433
 * gave PROC_GEN_LIST non-zero ID
 * 
 *    Rev 1.2   Jul 15 1999 16:39:28   BUZILA
 * Fixing Mgmt Detail
 * 
 *    Rev 1.1   Jul 08 1999 10:03:44   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
