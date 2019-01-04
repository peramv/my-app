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

#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0005_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0049_vw.hpp>
#include <ifastdataimpl\dse_dstcconf_vw.hpp>
#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId CONFIRMATION;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT;
   extern IFASTBP_LINKAGE const BFContainerId REMARKS_LIST;
}
namespace CONFPROC
{
   const BFFieldId CHOICE_FIELD (100);
   const BFFieldId CREATING_SHAREHOLDER (101);
   const BFFieldId REMARKS_AVAILABLE (102);
   const BFFieldId FROM_REMARKS (103);
   const BFFieldId SHOW_UPDATE_ALL_CIF (104);
   const BFFieldId HostShareholderNum (105, I_("HostShareholderNum"));
   const BFFieldId HostAccountNum (106, I_("HostAccountNum"));
   const BFFieldId HostEntityId (107, I_("HostEntityId"));
   extern IFASTBP_LINKAGE const DString REFRESH;
   extern IFASTBP_LINKAGE const DString GETWORK;
   extern IFASTBP_LINKAGE const DString END;
   extern IFASTBP_LINKAGE const DString NEWSEARCH;
   extern IFASTBP_LINKAGE const DString CHOICE;
   extern IFASTBP_LINKAGE const DString TRADE;
   const I_CHAR * const PARM_AWDEVENT = I_( "AwdEvent" );
   const I_CHAR * const PARM_CALLED_FROM = I_( "CalledFrom" );
   const I_CHAR * const CREATING_ACCOUNT = I_( "CreatingAccount" );  
   const I_CHAR * const ENABLE_REBOOK = I_( "EnableRebook" );  
   const I_CHAR * const COMMIT_PARENT_DATA_GROUPS = I_("CommitParentDataGroups");
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId LastActiveEntityId;
   extern CLASS_IMPORT const BFTextFieldId CSSStopSINMatch;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ConfirmationProcessIncludes.h-arc  $
 * 
 *    Rev 1.20   01 Aug 2007 09:45:34   popescu
 * GAP 6 - CIF - also added UpdateAllCIF for vew 85
 * 
 *    Rev 1.19   17 Jul 2007 15:18:52   popescu
 * GAP 6 CIF - AIM
 * 
 *    Rev 1.18   Jul 08 2005 09:37:36   Yingbaol
 * PET1235,FN01:cancellation rebook
 * 
 *    Rev 1.17   Jun 20 2005 18:40:16   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.16   Jun 16 2005 10:56:40   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.15   Apr 12 2005 10:27:14   porteanm
 * PET1190 FN14 - Wire order redemption against unsettled units.
 * 
 *    Rev 1.14   Nov 14 2004 14:22:06   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.13   May 27 2004 17:19:14   HERNANDO
 * PET1017 FN01- Remarks-Confirmation change.   Allow Confirmation to view the Added Remark and allow copying it to the AWD object.
 * 
 *    Rev 1.12   Mar 21 2003 17:38:14   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Mar 09 2003 15:55:34   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.10   Oct 09 2002 23:53:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:52:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:21:26   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   19 Mar 2002 13:15:28   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.6   Jul 10 2001 15:59:46   OLTEANCR
 * unchanged
 * 
 *    Rev 1.5   Jan 03 2001 10:48:22   ZHANGCEL
 * Define a new parameter CREATING_ACCOUNT
 * 
 *    Rev 1.4   Oct 11 2000 14:16:46   KOVACSRO
 * Added parameter 'CalledFrom'.
 * 
 *    Rev 1.3   Sep 18 2000 17:55:42   HERNANDO
 * Added Parameter; passes AWD Event from process to dialog
 * 
 *    Rev 1.2   Aug 25 2000 10:42:36   YINGBAOL
 * popup trde screen after confirmation
 * 
 *    Rev 1.1   Feb 15 2000 18:56:20   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Jan 23 2000 18:27:48   POPESCUS
 * disable remarks when no global account num and shareholder num exist
 * 
 *    Rev 1.9   Jan 21 2000 15:47:12   POPESCUS
 * added a new param
 * 
 *    Rev 1.8   Jan 21 2000 14:35:16   HSUCHIN
 * minor chage to use get global
 * 
 *    Rev 1.7   Jan 19 2000 09:36:24   HSUCHIN
 * Check in for Mihai
 * 
 *    Rev 1.6   Jan 18 2000 11:29:54   POPESCUS
 * fixed some of the settings of the global values (account & shareholder)
 * 
 *    Rev 1.5   Jan 16 2000 16:58:08   POPESCUS
 * prepared for refresh and cleaned up the code
 * 
 *    Rev 1.4   07 Jan 2000 14:09:34   HSUCHIN
 * latest infra changes and remark updates
 * 
 *    Rev 1.3   Nov 22 1999 15:24:34   HSUCHIN
 * redesigned and OG usage.
 * 
 *    Rev 1.2   Jul 27 1999 16:03:36   BUZILA
 * Increment M2
 * 
 *    Rev 1.1   Jul 08 1999 10:03:40   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

