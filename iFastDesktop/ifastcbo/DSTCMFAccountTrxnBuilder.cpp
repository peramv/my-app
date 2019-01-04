//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : DSTCMFAccountTrxnBuilder.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October 1999
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCMFAccountTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "mfaccount.hpp"
#include "mgmtco.hpp"

#include "ifasthosttransactioncontainer.hpp"
#include <ifastdataimpl\dse_dstc0076_req.hpp>
#include <ifastdataimpl\dse_dstc0076_vw.hpp>

#include "dstcacbtrxnbuilder.hpp"
#include "dstcaccountcommitmenttrxnbuilder.hpp"
#include "dstcaccountentitytrxnbuilder.hpp"
#include "dstcaccountreviewtrxnbuilder.hpp"
#include "dstcacctcategorytrxnbuilder.hpp"
#include "dstcacctsplitcommtrxnbuilder.hpp"
#include "dstcaspensionplantrxnbuilder.hpp"
#include "dstccontracttrxnbuilder.hpp"
#include "dstcregdocumentlisttrxnbuilder.hpp"
#include "dstcamsacctlvltrxnbuilder.hpp"
#include "dstcdistributionstrxnbuilder.hpp"
#include "dstcesoptrxnbuilder.hpp"
#include "dstcmfaccounttrxnbuilder.hpp"
#include "dstcrrifinfotrxnbuilder.hpp"
#include "dstcsystematicstrxnbuilder.hpp"
#include "dstcfeeparamtrxnbuilder.hpp"
#include "dstcpensioninfotrxnbuilder.hpp"
#include "dstcacctmailingoverridetrxnbuilder.hpp"
#include "dstcbeneficiaryallocationtrxnbuilder.hpp"
#include "dstcmatsweepinstrtrxnbuilder.hpp"
#include "dstcdemographicstrxnbuilder.hpp"
#include "dstcdirecttradingtrxnbuilder.hpp"
#include "dstcacctsettlementinstrtrxnbuilder.hpp"
#include "dstctaxexemptauthtrxnbuilder.hpp"
#include "dstcuserdefmattrxnbuilder.hpp"
#include "acctcutofftimestrxnbuilder.hpp"
#include "dstcacctsettlementruletrxnbuilder.hpp"
#include "dstctransactionupdatetrxnbuilder.hpp"
#include "dstcinvestorauthorizationtrxnbuilder.hpp"
#include "dstcresptransfertrxnbuilder.hpp"
#include "dstcacctguaranteeguardopttrxnbuilder.hpp"
#include "dstcmatsweepinstrtrxnbuilder.hpp"
#include "dstccontractmatinstrtrxnbuilder.hpp"
#include "DSTCAcctRegDetailsTrxnBuilder.hpp"
#include "DSTCEntityRegDetailsTrxnBuilder.hpp"
#include "DSTCEntityRegJurisDetailsTrxnBuilder.hpp"
#include "DSTCRegPlanTransfTrxnBuilder.hpp"
#include "DSTCAcctRoundingRuleTrxnBuilder.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MFACCOUNT_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCMFAccountTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId AcctNumCtrl;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const SHRNUM;
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
void DSTCMFAccountTrxnBuilder::buildTrxnKey( DString& strKey, MFAccount* mfAccount )
{
   DString accountNum, shrNum;

   //get the shareholder number off the account
   mfAccount->getField( ifds::ShrNum, shrNum, BF::HOST, true );
   shrNum.stripLeading( '0' );
   shrNum.strip();
   //get the account number off the account
   mfAccount->getField( ifds::AccountNum, accountNum, BF::HOST, true );
   accountNum.stripLeading( '0' );
   accountNum.strip();
   //build the key
   addIDITagValue( strKey, TRXNTAG::SHRTAG, shrNum );
   addIDITagValue( strKey, TRXNTAG::ACCTTAG, accountNum );
}

//******************************************************************************
SEVERITY DSTCMFAccountTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                      BFAbstractCBO* pObj, 
                                                      HostTransactionContainer* pTrCont, 
                                                      BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
    SEVERITY severity = SEVERE_ERROR;
    MFAccount* mfAccount = dynamic_cast<MFAccount*>(pObj);

    //check if the account itself is updated,
    //do not ask the children (call hasTransactionUpdates with false)
    if( mfAccount != NULL && (objActivity == OBJ_ACTIVITY_ADDED || mfAccount->hasTransactionUpdates( false )) )
    {

        BFData *request = new BFData( ifds::DSTC0076_REQ );
        BFData *response = new BFData( ifds::DSTC0076_VW );
        //fill in the request update, only the part for which the MFAccount is responsible
        mfAccount->getData( *request, BF::HOST );

        DString strAccountNumManual;
        workSession.getOption( ifds::AcctNumCtrl, strAccountNumManual, BF::HOST  );
        if( strAccountNumManual.strip().upperCase() == I_("M") )
            strAccountNumManual = I_("Y");
        else
            strAccountNumManual = I_("N");

        DString strTrack,strAvtivity;
        mfAccount->getTrackActivity(strTrack,strAvtivity);          
        request->setElementValue( ifds::Track, strTrack, false, false );
        request->setElementValue( ifds::Activity, strAvtivity, false, false );

        //mfAccount->getData( *request, BF::HOST );

        //set the RunMode field to the AccountUpdate trxn
        DSTCWorkSession::setRunMode( request, objActivity );

        DString mgmtCoId;
        workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
        request->setElementValue( ifds::CompanyId, mgmtCoId );

        request->setElementValue( ifds::AccountNumManual, strAccountNumManual, false, false );

        DString strKey;

        //get the string key for the account
        DSTCMFAccountTrxnBuilder::buildTrxnKey( strKey, mfAccount );
        //check first if this is a new account or updated
        TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_ACCOUNT : UPDATE_ACCOUNT;

        DString keyTypes;
        DString accountNum, shrNum;

        mfAccount->getField( ifds::ShrNum, shrNum, BF::HOST, true );
        shrNum.strip();
        //get the account number off the account
        mfAccount->getField( ifds::AccountNum, accountNum, BF::HOST, true );
        accountNum.strip();
        //build the key
        shrNum.stripLeading( '0' );
        shrNum.strip();
        accountNum.stripLeading( '0' );
        accountNum.strip();
        addIDITagValue( keyTypes, KEYTYPES::SHRNUM, shrNum );
        addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, accountNum );


        JData *jdata = new JData( DSTC_REQUEST::MFACCOUNT_UPDATE, request, response );
        pTrCont->addTransaction( strKey, jdata, objActivity, trxnType, keyTypes );
    }
    //call the transaction builders of the objects that are contained by the account

    //for the systematic list
    DSTCSystematicsTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );
    //for the account distribution list
    DSTCDistributionsTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );

    if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
    {
        //for the RRIF/LIF/LRIF list
        DSTCRRIFInfoTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );
        DSTCContractTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );
        DSTCUserDefMatTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );
        DSTCAcctSplitCommTrxnBuilder::buildTransactions ( workSession, mfAccount, pTrCont );
        DSTCPensionInfoTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );
        DSTCDirectTradingTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );
    }

    if( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
    {
        DSTCESoPTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );
    }

    //call the transaction builders of the objects that are contained by the shareholder
    //build demographics transactions 
    DSTCDemographicsTrxnBuilder::buildTransactions(workSession, mfAccount, pTrCont, objActivity);

    DSTCAccountCommitmentTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont, objActivity );

    DSTCAsPensionPlanTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );

    //FeeParamList
    DSTCFeeParamTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );

    // for Account Review List
    DSTCAccountReviewTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );

    DSTCAcctCategoryTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );
    DSTCAcctMailingOverrideTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );

    // Settlement Location at Account Level
    DSTCAcctSettlementInstrTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont, objActivity );
    DSTCTaxExemptAuthTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );

    // Account Cut Off Times
    AcctCutOffTimesTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );

    // AMS Acct level
    DSTCAMSAcctLvlTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont, objActivity );

    // Account level settlement rule
    DSTCAcctSettlementRuleTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont, objActivity );

   // Regulatory Documents:
   DSTCRegDocumentListTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont, objActivity );

   // Transactions update
   DSTCTransactionUpdateTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont, objActivity );

   // Investor authorization update
   DSTCInvestorAuthorizationTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont, objActivity );

   // RESP Beneficiary update
   DSTCBeneficiaryAllocationTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont, objActivity );

   // RESP Transfer update
   DSTCRESPTransferTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont, objActivity );

   // Account guarantee guard option
   DSTCAcctGuaranteeGuardOptTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont, objActivity );

   //maturity instructions...
   DSTCMatSweepInstrTrxnBuilder::buildTransactions (workSession, mfAccount, pTrCont, objActivity) ;

   //Contract maturity instructions..
   DSTCContractMatInstrTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont );

   //Update for ACB plug
   DSTCACBTrxnBuilder::buildTransactions (workSession, mfAccount, pTrCont, objActivity);

   //AcctRegDetails update
   DSTCAcctRegDetailsTrxnBuilder::buildTransactions (workSession, mfAccount, pTrCont, objActivity);

   //EntityRegDetails update
   DSTCEntityRegDetailsTrxnBuilder::buildTransactions (workSession, mfAccount, pTrCont, objActivity);

   //EntityRegJurisDetails update
   DSTCEntityRegJurisDetailsTrxnBuilder::buildTransactions (workSession, mfAccount, pTrCont, objActivity);

   DSTCRegPlanTransfTrxnBuilder::buildTransactions (workSession, mfAccount, pTrCont, objActivity);

   // Account Rounding Rule update
   DSTCAcctRoundingRuleTrxnBuilder::buildTransactions( workSession, mfAccount, pTrCont, objActivity );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCMFAccountTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.50   Feb 22 2012 17:00:58   if991250
 * Account Commitment
 * 
 *    Rev 1.49   Feb 21 2012 15:44:16   wp040100
 * P0186484 FN05 - Contract Maturity Instruction Changes
 * 
 *    Rev 1.48   Dec 14 2011 16:55:50   popescu
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.47   Oct 29 2010 02:28:36   kitticha
 * PET173756 FN02 - Don’t Bust the Rules.
 * 
 *    Rev 1.46   Apr 23 2010 16:07:24   jankovii
 * PET0165541 FN01 QESI RESP Trading
 * 
 *    Rev 1.45   Mar 29 2010 10:51:40   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.44   29 Jun 2009 16:08:48   popescu
 * PET 156681 - FN 14 - Investor Authorization
 * 
 *    Rev 1.43   May 22 2009 10:30:42   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.42   Mar 02 2009 09:57:38   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.41   07 Aug 2008 15:28:52   kovacsro
 * PET 59888 - AML Enhancement. - call view 390 after 81
 * 
 *    Rev 1.40   Jul 25 2008 14:55:34   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.39   Mar 11 2008 20:07:52   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.38   Jun 27 2007 14:39:24   porteanm
 * PET 2360 FN02 - AMS Acct level support.
 * 
 *    Rev 1.37   Jul 06 2005 11:59:50   hernando
 * PET1250 FN01 - Added AcctCutOffTimeTrxnBuilder call.
 * 
 *    Rev 1.36   Mar 20 2005 15:04:38   hernando
 * PET1024 FN02 - Added call to DSTCUserDefMatListTrxnBuilder.
 * 
 *    Rev 1.35   Dec 10 2004 19:22:16   vadeanum
 * PET1117_FN21: settlement instructions.
 * 
 *    Rev 1.34   Nov 14 2004 14:32:52   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.33   Oct 13 2004 13:51:48   VADEANUM
 * PET 1117 FN21 - Replaced SettleLoc with SettlementInstr...
 * 
 *    Rev 1.32   Sep 20 2004 10:27:50   ZHANGCEL
 * PET1094-FN8 -- Admin Fee enhancement
 * 
 *    Rev 1.31   Nov 24 2003 18:20:18   HERNANDO
 * PET859 FN1 - Added call to Settlement Location at Account Level builder.
 * 
 *    Rev 1.30   Oct 16 2003 12:21:28   FENGYONG
 * PET809 FN08 Direct Trading enhancement
 * 
 *    Rev 1.29   Jul 11 2003 16:03:34   FENGYONG
 * move demographic from shareholder to MFAccount
 * 
 *    Rev 1.28   Apr 02 2003 11:32:12   FENGYONG
 * Add acctmailingoverride transaction builder
 * 
 *    Rev 1.27   Mar 21 2003 18:05:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.26   Jan 25 2003 17:02:52   KOVACSRO
 * Added account category builder.
 * 
 *    Rev 1.25   Oct 09 2002 23:54:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.24   Aug 29 2002 12:55:32   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.23   Jun 11 2002 21:32:12   HSUCHIN
 * added pension juris
 * 
 *    Rev 1.22   31 May 2002 13:52:40   HERNANDO
 * Added AccountReviewTrxnBuilder call.
 * 
 *    Rev 1.21   22 May 2002 18:27:56   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.20   25 Feb 2002 20:13:50   PURDYECH
 * BFData Implementation Quick Fixes
 * 
 *    Rev 1.19   Feb 22 2002 13:28:58   YINGBAOL
 * add Fee update Transaction
 * 
 *    Rev 1.18   13 Dec 2001 17:16:50   KOVACSRO
 * Moved the TaxType check into MFAccount (in some cases getField(TaxType...)  was calling view 4)
 * 
 *    Rev 1.17   Sep 19 2001 15:27:20   JANKAREN
 * Changed logic for As Pension to be based on taxtype
 * 
 *    Rev 1.16   19 Sep 2001 14:56:08   KOVACSRO
 * Added ESOP.
 * 
 *    Rev 1.15   30 Aug 2001 16:35:24   HSUCHIN
 * added acct split comm builder
 * 
 *    Rev 1.14   Aug 23 2001 12:51:34   JANKAREN
 * Added call to DSTCAsPensionPlanTrxnBuilder
 * 
 *    Rev 1.13   Jul 19 2001 18:24:42   OLTEANCR
 *  setElementValue for AccountNumManual
 * 
 *    Rev 1.12   23 May 2001 14:39:30   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.11   03 May 2001 14:06:18   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.10   Mar 29 2001 15:58:24   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.9   Feb 12 2001 14:56:56   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.8   09 Feb 2001 15:01:30   SMITHDAV
 * Removed commented code; Removed unneeded includes; Some fixes.
 * 
 *    Rev 1.7   Jan 31 2001 16:10:58   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.6   Jan 16 2001 13:53:36   OLTEANCR
 * 
 *    Rev 1.5   Dec 17 2000 20:23:10   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.4   Sep 29 2000 13:27:10   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.3   May 12 2000 17:40:26   ZHANGCEL
 * Added call to DSTCContractTrxnBuilder
 * 
 *    Rev 1.2   May 11 2000 13:32:50   HUANGSHA
 * Added Market Flag for building RRIF/LIF transaction
 * 
 *    Rev 1.1   May 05 2000 17:03:56   PETOLESC
 * Added call to DSTCRRIFInfoTrxnBuilder.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:56   SMITHDAV
 * Initial revision.
// 
//    Rev 1.18   Feb 03 2000 10:52:00   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.17   Feb 02 2000 10:33:58   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.16   Jan 07 2000 14:18:12   POPESCUS
// fixes
// 
//    Rev 1.15   Dec 30 1999 14:44:04   POPESCUS
// added initialization method for fields that are not in the inquiry mode
// 
//    Rev 1.14   Dec 24 1999 10:31:04   VASILEAD
// Fixed NASU flow
// 
//    Rev 1.13   Dec 12 1999 17:55:44   POPESCUS
// Delete the XchgData object and minor fixes
// 
*/