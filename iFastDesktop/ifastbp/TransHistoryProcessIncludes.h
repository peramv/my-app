#pragma once
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
// ^FILE   : TransactionHistoryProcessinclude.h
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/04/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0017_vw.hpp>
#include <ifastdataimpl\dse_dstc0017_req.hpp>
#include <ifastdataimpl\dse_dstc0022_vw.hpp>
#include <ifastdataimpl\dse_dstc0022_req.hpp>
#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0053_req.hpp>
#include <ifastdataimpl\dse_dstc0054_vw.hpp>
#include <ifastdataimpl\dse_dstc0054_req.hpp>
#include <ifastdataimpl\dse_dstc0063_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0049_vw.hpp>
#include <ifastdataimpl\dse_dstc0298_vw.hpp>
#include <ifastdataimpl\dse_dstc0330_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0344_vw.hpp>

#include <bfproc/bfcontainerid.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ALLOCATION;
   extern IFASTBP_LINKAGE const BFContainerId DEDUCTION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_DETAIL_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_LIST;
   extern IFASTBP_LINKAGE const BFContainerId FUND_MASTER_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
   extern IFASTBP_LINKAGE const BFContainerId PENDING_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANS_LIST;
	extern IFASTBP_LINKAGE const BFContainerId TRANSACTION_EXTERNAL_LINKS_LIST;	
   extern IFASTBP_LINKAGE const BFContainerId TRANS_FEE_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRANS_DECIMALS;
   extern IFASTBP_LINKAGE const BFContainerId TRADE_AUTHRIZATION;
   extern IFASTBP_LINKAGE const BFContainerId TRANSACTION_UPDATE;
}
const BFFieldId AMOUNT_UNITS(112);
const BFFieldId AMOUNT_DOLLARS(113);
const BFFieldId FUND_CODE(114);
const BFFieldId CLASS_CODE(115);
const BFFieldId FUND_CLASS_KEY(116);
const BFFieldId USER_ID(117);
const BFFieldId DSC_REDEMP_ACCESS(118);
const BFFieldId IsChargeTransFee(119, I_("IsChargeTransFee"));
const BFFieldId CallPendigTradeDetails(120, I_("CallPendigTradesDetails"));
const BFFieldId IS_FUND_BEL( 121 ); // Used in Pending.  Will return Yes/No depending if fund is BEL.
const BFFieldId HAS_RIGHT_TO_CANCEL_FUND_LIMIT_RULE( 122 ); 
const BFFieldId AMT_INV_APPL(10136, I_("AMT_INV_APPL"));

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransHistoryProcessIncludes.h-arc  $
 * 
 *    Rev 1.20   May 22 2009 10:21:28   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.19   May 12 2009 15:04:12   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.18   Mar 02 2009 09:56:38   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.17   May 18 2005 09:05:38   yingbaol
 * PET1203,FN01 Commission Class A enhancement
 * 
 *    Rev 1.16   Mar 04 2005 17:07:48   Fengyong
 * PET1190 FN04 - TransCancel Tempery check in for other coder
 * 
 *    Rev 1.15   Mar 03 2005 14:33:14   aguilaam
 * PET1171_FN01: display view 330 details on Transaction Detail screen (history) EUSDSavings - others
 * 
 *    Rev 1.14   Jan 20 2005 15:58:12   hernando
 * PTS10037884 - Change the Back End Load display 
 * 
 *    Rev 1.13   Dec 21 2004 18:11:34   popescu
 * PET 1117/56, fixed call to pending trades details view 54 when dialog is launched.
 * 
 *    Rev 1.12   Dec 09 2004 12:37:38   popescu
 * PET 1117/56, more fees work /pending trade
 * 
 *    Rev 1.11   Dec 07 2004 21:20:14   popescu
 * PET 1117/06, pending trades/fees fixes, add-ons
 * 
 *    Rev 1.10   Aug 30 2004 16:35:32   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.9   Mar 21 2003 17:49:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:53:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:54:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   22 May 2002 18:18:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:19:06   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   26 Feb 2002 16:52:00   HSUCHIN
 * added dsc redemption
 * 
 *    Rev 1.3   Jun 11 2001 16:57:16   ZHANGCEL
 * Added a new const int:  USER_ID.
 * 
 *    Rev 1.2   Aug 08 2000 10:46:02   VADEANUM
 * Title Bar Standards
 * 
 *    Rev 1.1   Feb 15 2000 18:57:04   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:26   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.4   Sep 27 1999 13:56:02   YINGZ
 * add dosetfield
 * 
 *    Rev 1.3   Jul 30 1999 14:04:30   YINGZ
 * grey pending when there is no pending
 * 
 *    Rev 1.2   Jul 22 1999 14:59:28   YINGZ
 * process amount and units in pending
 * 
 *    Rev 1.1   Jul 08 1999 10:04:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

