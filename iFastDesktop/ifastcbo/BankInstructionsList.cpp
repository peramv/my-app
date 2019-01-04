//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//*****************************************************************************
//
// ^FILE   : BankInstructionsList.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 2/9/01
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : bankinstructionslist
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"

#include "bankinstructions.hpp"
#include "bankinstructionslist.hpp"
#include "dstcommonfunction.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0052_req.hpp>
#include <ifastdataimpl\dse_dstc0052_vw.hpp>
#include "Shareholder.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BANK_INSTRUCTION;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME                        = I_("BankInstructionsList");
   const I_CHAR * EFT_REDEMPTION_BANK_CODE               = I_( "07" );
   const I_CHAR * ALTERNATIVE_EFT_REDEMPTION_BANK_CODE   = I_( "36" );
   const I_CHAR * const YES                              = I_ ("Y");

}

namespace ifds
{
   //the type of the bank
   extern CLASS_IMPORT const BFTextFieldId BankInstrType;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId SwitchBanks;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT;
}

namespace BANKENTITY
{
   extern CLASS_EXPORT I_CHAR * const CLIENT = I_("01");
   extern CLASS_EXPORT I_CHAR * const BROKER = I_("02");
   extern CLASS_EXPORT I_CHAR * const BRANCH = I_("03");
   extern CLASS_EXPORT I_CHAR * const SALESREP = I_("04");
   extern CLASS_EXPORT I_CHAR * const FUND_GROUP = I_("05");
   extern CLASS_EXPORT I_CHAR * const FUND_CLASS = I_("07");
   extern CLASS_EXPORT I_CHAR * const SHAREHOLDER = I_("10");
   extern CLASS_EXPORT I_CHAR * const FUND = I_("11");
   extern CLASS_EXPORT I_CHAR * const FUND_SPONSOR = I_("12");
   extern CLASS_EXPORT I_CHAR * const REG_AGENT = I_("13");
   extern CLASS_EXPORT I_CHAR * const ACCOUNT = I_("14");
}

namespace CND
{  // Conditions used
   extern const long ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_ACCTUSE_ALREADY_EXIST;
   extern const long WARN_BANK_INSTRUCTIONS_OVERLAP;
   extern const long ERR_BANK_INSTRUCTIONS_OVERLAP;
   extern const long ERR_DUPLICATE_EFT_REDEMPTION_CURRENCY;
   extern const long WARN_SWITCH_EFT_TO_ALTERNATIVEEFT;
   extern const long WARN_EFT_RED_CURRENCY_MISSING;
   extern const long WARN_DUPLICATE_EFT_REDEMPTION_CURRENCY;
   extern const long ERR_DUPLICATE_EFT_PURCHASE_CURRENCY;
   extern const long WARN_DUPLICATE_EFT_PURCHASE_CURRENCY;
   extern const long WARN_EFT_PUR_CURRENCY_MISSING;
   extern const long WARN_SWITCH_EFT_PUR_TO_ALTERNATIVE_EFT_PUR;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const DUPLICATE_BANK_WITH_SAME_USAGE_AND_CURRENCY;
}

namespace AcctUseCode
{
   extern const I_CHAR * const EFT_PURCHASE;
   extern const I_CHAR * const ALT_EFT_PURCHASE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,           State Flags,                 Group Flags
   { ifds::BankInstrType,   BFCBO::CALCULATED_FIELD,           0 }, 
   { ifds::AccountNum,      BFCBO::CALCULATED_FIELD,           0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
BankInstructionsList::BankInstructionsList ( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
   setObjectAsList();
}

//******************************************************************************
BankInstructionsList::~BankInstructionsList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************
SEVERITY BankInstructionsList::initNew ( const DString &bankInstrType,
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("initNew"));

   setFieldNoValidate ( ifds::BankInstrType, bankInstrType, idDataGroup, false, 
                        true, 
                        true);

   BFObjectKey objKey (NULL_STRING, idDataGroup);

   if (bankInstrType != BANKTYPE::SHAREHOLDER ||
       BANKTYPE::ACCOUNT != bankInstrType)
   {
      getNewListItem (objKey);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructionsList::init ( const DString &bankInstrType, 
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init"));

   setFieldNoValidate ( ifds::BankInstrType, bankInstrType, idDataGroup, false, 
                        true, 
                        true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructionsList::init ( BFData &requestData, 
                                      const DString &bankInstrType, 
                                      const DString &dstrTrack, 
                                      const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString mgmtCoIdOut;

   setFieldNoValidate ( ifds::BankInstrType, bankInstrType, BF::HOST, false, 
                        true, 
                        true);
   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName);
   //call the back-end
   ReceiveData ( DSTC_REQUEST::BANK_INSTRUCTION, 
                 requestData, 
                 ifds::DSTC0052_VW, 
                 DSTCRequestor (getSecurity(), true)); 
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY BankInstructionsList::doCreateObject (const BFData &data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));
   
   BankInstructions *pBankInstructions = new BankInstructions(*this);
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, BF::HOST, false);
   pBankInstructions->init (data, bankInstrType);
   pObjOut = pBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY BankInstructionsList::doCreateNewObject ( BFCBO* &pBase, 
                                                   DString &strKey, 
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doCreateNewObject"));

   BankInstructions *pBankInstructions = new BankInstructions(*this);
   DString bankInstrType;

   getField (ifds::BankInstrType, bankInstrType, idDataGroup, false);
   if(bankInstrType ==  BANKTYPE::ACCOUNT || bankInstrType ==  BANKTYPE::SHAREHOLDER )
   {
     DString dstrCurSel = NULL_STRING;
     Shareholder* pShareHolder = NULL;
     pShareHolder = dynamic_cast <Shareholder*>(getParent ());
     if(pShareHolder)
     {
       pShareHolder->getCurrentBankingSel(dstrCurSel); 
       bankInstrType = BANKTYPE::ACCOUNT  == dstrCurSel ? BANKTYPE::ACCOUNT : BANKTYPE::SHAREHOLDER ;
     }
   }
   pBankInstructions->initNew (bankInstrType, idDataGroup);
   pBase = pBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY BankInstructionsList::doValidateAll ( const BFDataGroupId &idDataGroup, 
                                               long lValidateGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "doValidateAll" ));

   validateCurrencyAccountUseCode(idDataGroup);
   doesDefaultEFTRedemptionExist (idDataGroup);
   doesDefaultEFTPurchaseExist (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void BankInstructionsList::validateCurrencyAccountUseCode (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateCurrencyAccountUseCode" ) );

   DString AcctUseCode, BankAcctCurrency, EffectiveDate, StopDate, bankInstrType, dstrBankingEntity,dstrAccountNum;
   DString AcctUseCode1, BankAcctCurrency1, EffectiveDate1, StopDate1, bankInstrType1, dstrBankingEntity1, dstrAccountNum1;

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFAbstractCBO *pBFBase;
   BFAbstractCBO *pBFBase1;

   while( !iter.end() )
   {
      pBFBase = iter.getObject();
      if( !iter.isDummy()  && pBFBase)
      {
         pBFBase->getField(ifds::EffectiveDate, EffectiveDate, idDataGroup);
         pBFBase->getField(ifds::StopDate, StopDate, idDataGroup);

         if( DSTCommonFunctions::CompareDates( EffectiveDate, StopDate ) // check only when date are valid
             == DSTCommonFunctions::FIRST_EARLIER )
         {
            pBFBase->getField(ifds::AcctUseCode, AcctUseCode, idDataGroup);
            pBFBase->getField(ifds::BankAcctCurrency, BankAcctCurrency, idDataGroup);
            pBFBase->getField (ifds::BankInstrType, bankInstrType, idDataGroup);
            pBFBase->getField (ifds::rxBankingEntity, dstrBankingEntity, idDataGroup);
            pBFBase->getField (ifds::rxAcctNum, dstrAccountNum, idDataGroup);
            // position to the next item
            iter1.positionByKey( iter.getStringKey() );
            if( !iter1.end() )++iter1;

            while( !iter1.end() )
            {
               pBFBase1 = iter1.getObject();
               if( !iter1.isDummy()  && pBFBase1 && pBFBase != pBFBase1 )
               {
                  pBFBase1->getField(ifds::EffectiveDate, EffectiveDate1, idDataGroup);
                  pBFBase1->getField(ifds::StopDate, StopDate1, idDataGroup);

                  if( DSTCommonFunctions::CompareDates( EffectiveDate1, StopDate1 ) // check only when date are valid
                      == DSTCommonFunctions::FIRST_EARLIER )
                  {
                     pBFBase1->getField (ifds::AcctUseCode, AcctUseCode1, idDataGroup );
                     pBFBase1->getField (ifds::BankAcctCurrency, BankAcctCurrency1, idDataGroup);
                     pBFBase1->getField (ifds::BankInstrType, bankInstrType1, idDataGroup);
                     pBFBase->getField (ifds::rxBankingEntity, dstrBankingEntity1, idDataGroup);
                     pBFBase->getField (ifds::rxAcctNum, dstrAccountNum1, idDataGroup);

                     if (AcctUseCode1 == AcctUseCode && BankAcctCurrency1 == BankAcctCurrency &&
                         dstrBankingEntity1 == dstrBankingEntity && dstrAccountNum1 == dstrAccountNum &&
//dates DO NOT overlap if (E-effective date; S-stop date)
//E < S < E1 < S1 , or
//E1 < S1 < E < S
                          !( DSTCommonFunctions::CompareDates (StopDate, EffectiveDate1) ==
                                 DSTCommonFunctions::FIRST_EARLIER ||
                             DSTCommonFunctions::CompareDates (StopDate1, EffectiveDate) ==
                                 DSTCommonFunctions::FIRST_EARLIER))
//allow multiple active bank accounts that overlap, but raise a warning...
                     {
                        DString idiStr, 
                           currencyDescr, 
                           acctUsageCodeDescr;
                        
                        pBFBase1->getField (ifds::BankAcctCurrency, currencyDescr, idDataGroup, true);
                        pBFBase1->getField (ifds::AcctUseCode, acctUsageCodeDescr, idDataGroup, true);
                        addIDITagValue (idiStr, I_("accusage"), acctUsageCodeDescr);
                        addIDITagValue (idiStr, I_("cur"), currencyDescr);
                        if ( bankInstrType == bankInstrType1 && ( bankInstrType.upperCase() == I_("FUNDSPONSOR") ||
																  bankInstrType.upperCase() == I_("REGISTRATION AGENT")))
                        {
                           ADDCONDITIONFROMFILEIDI (CND::ERR_BANK_INSTRUCTIONS_OVERLAP, idiStr);
                        }
                        else
                        {
                           ADDCONDITIONFROMFILEIDI (CND::WARN_BANK_INSTRUCTIONS_OVERLAP, idiStr);
                        }
                        return;
                     }
                  }
               }
               ++iter1;
            }
         }
      }
      ++iter;
   }
}

//********************************************************************************
SEVERITY BankInstructionsList::switchToAlternativeEFTRedemption (const BankInstructions *pBankInstructionsToCheck, const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "switchToAlternativeEFTRedemption" ));

   DString dstrAcctUseCodeToCheck, dstrAcctUseCode;
   DString dstrCurrencyToCheck, dstrCurrency;

   pBankInstructionsToCheck->getField( ifds::AcctUseCode, dstrAcctUseCodeToCheck, idDataGroup );
   pBankInstructionsToCheck->getField( ifds::BankAcctCurrency, dstrCurrencyToCheck, idDataGroup );

   dstrAcctUseCodeToCheck.strip ();
   dstrCurrencyToCheck.strip ();

   if (dstrAcctUseCodeToCheck.empty () ||
      dstrAcctUseCodeToCheck != EFT_REDEMPTION_BANK_CODE ||
      dstrCurrencyToCheck.empty ())
      return GETCURRENTHIGHESTSEVERITY();

   //check first whether in the list (in memory) we have a duplicate
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      BankInstructions *pBankInstructions = dynamic_cast<BankInstructions*>(iter.getObject());
      // Don't check against itself
      if ( pBankInstructions != pBankInstructionsToCheck )
      {
         pBankInstructions->getField( ifds::AcctUseCode, dstrAcctUseCode, idDataGroup );
         pBankInstructions->getField( ifds::BankAcctCurrency, dstrCurrency, idDataGroup );		
         dstrAcctUseCode.strip ();
         dstrCurrency.strip ();

         if ( dstrAcctUseCode == EFT_REDEMPTION_BANK_CODE &&
            dstrCurrencyToCheck == dstrCurrency)
         {
            pBankInstructions->setField (ifds::AcctUseCode, ALTERNATIVE_EFT_REDEMPTION_BANK_CODE, idDataGroup, true, false, false);	
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY BankInstructionsList::switchToAlternativeEFTPurchase (const BankInstructions *pBankInstructionsToCheck, const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "switchToAlternativeEFTPurchase" ));

   DString dstrAcctUseCodeToCheck, dstrAcctUseCode;
   DString dstrCurrencyToCheck, dstrCurrency;

   pBankInstructionsToCheck->getField( ifds::AcctUseCode, dstrAcctUseCodeToCheck, idDataGroup );
   pBankInstructionsToCheck->getField( ifds::BankAcctCurrency, dstrCurrencyToCheck, idDataGroup );

   dstrAcctUseCodeToCheck.strip ();
   dstrCurrencyToCheck.strip ();

   if (dstrAcctUseCodeToCheck.empty () ||
      dstrAcctUseCodeToCheck != AcctUseCode::EFT_PURCHASE ||
      dstrCurrencyToCheck.empty ())
      return GETCURRENTHIGHESTSEVERITY();

   //check first whether in the list (in memory) we have a duplicate
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      BankInstructions *pBankInstructions = dynamic_cast<BankInstructions*>(iter.getObject());
      // Don't check against itself
      if ( pBankInstructions != pBankInstructionsToCheck )
      {
         pBankInstructions->getField( ifds::AcctUseCode, dstrAcctUseCode, idDataGroup );
         pBankInstructions->getField( ifds::BankAcctCurrency, dstrCurrency, idDataGroup );		
         dstrAcctUseCode.strip ();
         dstrCurrency.strip ();

         if ( dstrAcctUseCode == AcctUseCode::EFT_PURCHASE &&
            dstrCurrencyToCheck == dstrCurrency)
         {
            pBankInstructions->setField (ifds::AcctUseCode, AcctUseCode::ALT_EFT_PURCHASE, idDataGroup, true, false, false);	
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY BankInstructionsList::displayEFTWarning (const BankInstructions *pBankInstructionsToCheck, const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "displayEFTWarning" ));
   DString dstrAcctUseCodeToCheck, dstrAcctUseCode;
   DString dstrCurrencyToCheck, dstrCurrency;

   DString dstrSwitchBanks;

   getWorkSession ().getOption ( ifds::SwitchBanks, dstrSwitchBanks, idDataGroup, false);

   if (dstrSwitchBanks != YES)
      return GETCURRENTHIGHESTSEVERITY();

   pBankInstructionsToCheck->getField( ifds::AcctUseCode, dstrAcctUseCodeToCheck, idDataGroup );
   pBankInstructionsToCheck->getField( ifds::BankAcctCurrency, dstrCurrencyToCheck, idDataGroup );

   dstrAcctUseCodeToCheck.strip ();
   dstrCurrencyToCheck.strip ();

   if (dstrAcctUseCodeToCheck.empty () ||
      ( dstrAcctUseCodeToCheck != EFT_REDEMPTION_BANK_CODE &&
        dstrAcctUseCodeToCheck != AcctUseCode::EFT_PURCHASE ) ||
      dstrCurrencyToCheck.empty ())
   {
      return GETCURRENTHIGHESTSEVERITY();
   }

   //check first whether in the list (in memory) we have a duplicate
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      BankInstructions *pBankInstructions = dynamic_cast<BankInstructions*>(iter.getObject());
      // Don't check against itself
      if ( pBankInstructions != pBankInstructionsToCheck )
      {
         pBankInstructions->getField( ifds::AcctUseCode, dstrAcctUseCode, idDataGroup );
         pBankInstructions->getField( ifds::BankAcctCurrency, dstrCurrency, idDataGroup );		
         dstrAcctUseCode.strip ();
         dstrCurrency.strip ();

         if( dstrCurrencyToCheck == dstrCurrency )
         {
            if ( dstrAcctUseCode == EFT_REDEMPTION_BANK_CODE &&
                 dstrAcctUseCodeToCheck == EFT_REDEMPTION_BANK_CODE )
            {
               ADDCONDITIONFROMFILE (CND::WARN_SWITCH_EFT_TO_ALTERNATIVEEFT);
            }
            else if ( dstrAcctUseCode == AcctUseCode::EFT_PURCHASE &&
                      dstrAcctUseCodeToCheck == AcctUseCode::EFT_PURCHASE )
            {
               ADDCONDITIONFROMFILE (CND::WARN_SWITCH_EFT_PUR_TO_ALTERNATIVE_EFT_PUR);
            }
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY BankInstructionsList::validateEFTRedemptionBanking (const BankInstructions *pBankInstructionsToCheck, const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAcctUseCode" ));

   DString dstrSwitchBanks;

   getWorkSession ().getOption ( ifds::SwitchBanks, dstrSwitchBanks, idDataGroup, false);

   if (dstrSwitchBanks == YES)
      return GETCURRENTHIGHESTSEVERITY();

   DString dstrAcctUseCodeToCheck, dstrAcctUseCode;
   DString dstrCurrencyToCheck, dstrCurrency;
   DString dstrStopDateToCheck, dstrStopDate, dstrEffectiveDateToCheck, dstrEffectiveDate;

   pBankInstructionsToCheck->getField( ifds::AcctUseCode, dstrAcctUseCodeToCheck, idDataGroup );
   pBankInstructionsToCheck->getField( ifds::BankAcctCurrency, dstrCurrencyToCheck, idDataGroup );
   pBankInstructionsToCheck->getField( ifds::EffectiveDate, dstrEffectiveDateToCheck, idDataGroup );
   pBankInstructionsToCheck->getField( ifds::StopDate, dstrStopDateToCheck, idDataGroup );

   dstrAcctUseCodeToCheck.strip ();
   dstrCurrencyToCheck.strip ();

   if (dstrAcctUseCodeToCheck.empty () ||
      dstrAcctUseCodeToCheck != EFT_REDEMPTION_BANK_CODE ||
      dstrCurrencyToCheck.empty ())
      return GETCURRENTHIGHESTSEVERITY();

   //check first whether in the list (in memory) we have a duplicate
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      BankInstructions *pBankInstructions = dynamic_cast<BankInstructions*>(iter.getObject());
      // Don't check against itself
      if ( pBankInstructions != pBankInstructionsToCheck )
      {
         pBankInstructions->getField( ifds::AcctUseCode, dstrAcctUseCode, idDataGroup );
         pBankInstructions->getField( ifds::BankAcctCurrency, dstrCurrency, idDataGroup );
         pBankInstructions->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
         pBankInstructions->getField( ifds::StopDate, dstrStopDate, idDataGroup );

         dstrAcctUseCode.strip ();

         if ( dstrAcctUseCode  == dstrAcctUseCodeToCheck && 
            dstrAcctUseCode == EFT_REDEMPTION_BANK_CODE &&
            dstrCurrencyToCheck == dstrCurrency)
         {
            // check dates:
            if( DSTCommonFunctions::dateRangesOverlap (dstrEffectiveDateToCheck, dstrStopDateToCheck,
               dstrEffectiveDate, dstrStopDate))
            {
               getErrMsg ( I_("979"),
                           CND::ERR_DUPLICATE_EFT_REDEMPTION_CURRENCY, 
                           CND::WARN_DUPLICATE_EFT_REDEMPTION_CURRENCY, 
                           idDataGroup);

            }
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY BankInstructionsList::validateEFTPurchaseBanking (const BankInstructions *pBankInstructionsToCheck, const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEFTPurchaseBanking" ));


   DString dstrSwitchBanks;

   getWorkSession ().getOption ( ifds::SwitchBanks, dstrSwitchBanks, idDataGroup, false);

   if (dstrSwitchBanks == YES)
      return GETCURRENTHIGHESTSEVERITY();

   DString dstrAcctUseCodeToCheck, dstrAcctUseCode;
   DString dstrCurrencyToCheck, dstrCurrency;
   DString dstrStopDateToCheck, dstrStopDate, dstrEffectiveDateToCheck, dstrEffectiveDate;

   pBankInstructionsToCheck->getField( ifds::AcctUseCode, dstrAcctUseCodeToCheck, idDataGroup );
   pBankInstructionsToCheck->getField( ifds::BankAcctCurrency, dstrCurrencyToCheck, idDataGroup );
   pBankInstructionsToCheck->getField( ifds::EffectiveDate, dstrEffectiveDateToCheck, idDataGroup );
   pBankInstructionsToCheck->getField( ifds::StopDate, dstrStopDateToCheck, idDataGroup );

   dstrAcctUseCodeToCheck.strip ();
   dstrCurrencyToCheck.strip ();

   if (dstrAcctUseCodeToCheck.empty () ||
      dstrAcctUseCodeToCheck != AcctUseCode::EFT_PURCHASE ||
      dstrCurrencyToCheck.empty ())
      return GETCURRENTHIGHESTSEVERITY();

   //check first whether in the list (in memory) we have a duplicate
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      BankInstructions *pBankInstructions = dynamic_cast<BankInstructions*>(iter.getObject());
      // Don't check against itself
      if ( pBankInstructions != pBankInstructionsToCheck )
      {
         pBankInstructions->getField( ifds::AcctUseCode, dstrAcctUseCode, idDataGroup );
         pBankInstructions->getField( ifds::BankAcctCurrency, dstrCurrency, idDataGroup );
         pBankInstructions->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
         pBankInstructions->getField( ifds::StopDate, dstrStopDate, idDataGroup );

         dstrAcctUseCode.strip ();

         if ( dstrAcctUseCode  == dstrAcctUseCodeToCheck && 
            dstrAcctUseCode == AcctUseCode::EFT_PURCHASE &&
            dstrCurrencyToCheck == dstrCurrency)
         {
            // check dates:
            if( DSTCommonFunctions::dateRangesOverlap (dstrEffectiveDateToCheck, dstrStopDateToCheck,
               dstrEffectiveDate, dstrStopDate))
            {
               getErrMsg ( IFASTERR::DUPLICATE_BANK_WITH_SAME_USAGE_AND_CURRENCY,
                           CND::ERR_DUPLICATE_EFT_PURCHASE_CURRENCY, 
                           CND::WARN_DUPLICATE_EFT_PURCHASE_CURRENCY, 
                           idDataGroup);
            }
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY BankInstructionsList::doesDefaultEFTRedemptionExist (const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doesDefaultEFTRedemptionExist" ));

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   bool bFound = false;
   bool bAlternative = false;

   DString dstrCurrencyDescr, dstrAcctUseDescr;
   DString dstrAcctUseCode, dstrAcctUseCode1;
   DString dstrCurrency, dstrCurrency1;

   while (!iter.end())
   {
      BankInstructions *pBankInstructions = dynamic_cast<BankInstructions*>(iter.getObject());

      if (pBankInstructions)
      {
         pBankInstructions->getField( ifds::AcctUseCode, dstrAcctUseCode, idDataGroup );
         pBankInstructions->getField( ifds::BankAcctCurrency, dstrCurrency, idDataGroup );

         if ( dstrAcctUseCode == ALTERNATIVE_EFT_REDEMPTION_BANK_CODE)
         {
            bAlternative = true;
         }
         else
         {
            ++iter;
            continue;
         }

         BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
         iter1.begin();

         while (!iter1.end())
         {
            BankInstructions *pBankInstructions1 = dynamic_cast<BankInstructions*>(iter1.getObject());

            if (pBankInstructions == pBankInstructions1)

            {
               if (dstrCurrencyDescr.empty ())
                  dstrCurrencyDescr = dstrCurrency ;
               else
               {
                  int pos = dstrCurrencyDescr.find (dstrCurrency);
                  if (pos == -1)       
                     dstrCurrencyDescr = dstrCurrencyDescr + I_(",") + dstrCurrency ;
               }

               ++iter1;
               continue;
            }

            pBankInstructions1->getField( ifds::AcctUseCode, dstrAcctUseCode1, idDataGroup );
            pBankInstructions1->getField( ifds::BankAcctCurrency, dstrCurrency1, idDataGroup );

            if (dstrAcctUseCode1 == EFT_REDEMPTION_BANK_CODE &&
               dstrCurrency == dstrCurrency1)
            {
               bFound = true;
            }
            else
            {
               if (dstrCurrencyDescr.empty ())
                  dstrCurrencyDescr = dstrCurrency ;
               else
               {
                  int pos = dstrCurrencyDescr.find (dstrCurrency);
                  if (pos == -1)       
                     dstrCurrencyDescr = dstrCurrencyDescr + I_(",") + dstrCurrency ;
               }
            }
            ++iter1;
         }
      }

      ++iter;
   }

   if (!bFound && bAlternative)
   {
      DString idiStr;

      addIDITagValue (idiStr, I_("cur"), dstrCurrencyDescr);

      ADDCONDITIONFROMFILEIDI (CND::WARN_EFT_RED_CURRENCY_MISSING, idiStr);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY BankInstructionsList::doesDefaultEFTPurchaseExist (const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doesDefaultEFTRedemptionExist" ));

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   bool bFound = false;
   bool bAlternative = false;

   DString dstrCurrencyDescr, dstrAcctUseDescr;
   DString dstrAcctUseCode, dstrAcctUseCode1;
   DString dstrCurrency, dstrCurrency1;

   while (!iter.end())
   {
      BankInstructions *pBankInstructions = dynamic_cast<BankInstructions*>(iter.getObject());

      if (pBankInstructions)
      {
         pBankInstructions->getField( ifds::AcctUseCode, dstrAcctUseCode, idDataGroup );
         pBankInstructions->getField( ifds::BankAcctCurrency, dstrCurrency, idDataGroup );

         if ( dstrAcctUseCode == AcctUseCode::ALT_EFT_PURCHASE )
         {
            bAlternative = true;
         }
         else
         {
            ++iter;
            continue;
         }

         BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
         iter1.begin();

         while (!iter1.end())
         {
            BankInstructions *pBankInstructions1 = dynamic_cast<BankInstructions*>(iter1.getObject());

            if (pBankInstructions == pBankInstructions1)

            {
               if (dstrCurrencyDescr.empty ())
                  dstrCurrencyDescr = dstrCurrency ;
               else
               {
                  int pos = dstrCurrencyDescr.find (dstrCurrency);
                  if (pos == -1)       
                     dstrCurrencyDescr = dstrCurrencyDescr + I_(",") + dstrCurrency ;
               }

               ++iter1;
               continue;
            }

            pBankInstructions1->getField( ifds::AcctUseCode, dstrAcctUseCode1, idDataGroup );
            pBankInstructions1->getField( ifds::BankAcctCurrency, dstrCurrency1, idDataGroup );

            if (dstrAcctUseCode1 == AcctUseCode::EFT_PURCHASE &&
               dstrCurrency == dstrCurrency1)
            {
               bFound = true;
            }
            else
            {
               if (dstrCurrencyDescr.empty ())
                  dstrCurrencyDescr = dstrCurrency ;
               else
               {
                  int pos = dstrCurrencyDescr.find (dstrCurrency);
                  if (pos == -1)       
                     dstrCurrencyDescr = dstrCurrencyDescr + I_(",") + dstrCurrency ;
               }
            }

            ++iter1;
         }
      }

      ++iter;
   }

   if (!bFound && bAlternative)
   {
      DString idiStr;
      addIDITagValue (idiStr, I_("CUR"), dstrCurrencyDescr);
      ADDCONDITIONFROMFILEIDI (CND::WARN_EFT_PUR_CURRENCY_MISSING, idiStr);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructionsList.cpp-arc  $
 * 
 *    Rev 1.38   Apr 04 2012 23:12:24   wp040039
 * PETP0187485-Registartion Agent  Banking
 * 
 *    Rev 1.37   Jan 31 2011 22:22:24   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.36   Jan 31 2011 18:10:32   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.35   Feb 20 2008 09:50:32   jankovii
 * PET 2385 FN06 Bank Details upload.
 * 
 *    Rev 1.34   Nov 01 2006 11:21:42   ZHANGCEL
 * PET2217 FN26 -- Add logic to raise an error message when a duplicate bank exists
 * 
 *    Rev 1.33   Oct 18 2006 15:53:30   popescu
 * PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
 * 
 *    Rev 1.32   Sep 10 2006 17:58:36   popescu
 * STP 2192/12
 * 
 *    Rev 1.31   Jul 31 2006 15:32:50   ZHANGCEL
 * PET2192 FN11 -- MgmtCo Banking related changes
 * 
 *    Rev 1.30   Apr 10 2005 16:08:54   popescu
 * Incident# 261420, allow multiple active bank accounts; raise warning at transaction level if shareholder has more then one active bank account
 * 
 *    Rev 1.29   Nov 14 2004 14:28:20   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.28   Nov 04 2004 17:37:18   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.27   Sep 21 2004 13:31:48   HERNANDO
 * PET1094 FN06 - Absatzmeldung Files enhancement.  Added constant FUND_GROUP.
 * 
 *    Rev 1.26   Oct 19 2003 16:43:44   popescu
 * CIBC, PET809, FN 13 banking work
 * 
 *    Rev 1.25   Aug 25 2003 11:51:12   popescu
 * The default bank acct name would not show up if in NASU flow. Fixed that.
 * 
 *    Rev 1.24   Jun 10 2003 11:49:06   popescu
 * the bank entity type is 07 for the fund/class search
 * 
 *    Rev 1.23   Jun 09 2003 17:39:54   popescu
 * Added support for fund and class search, still stopped at the Gui level, because it shouldn't be functional yet; do not know the id for the bank entity when seraching for bank using fund and class
 * 
 *    Rev 1.22   May 31 2003 11:54:48   popescu
 * RRIF bank work
 * 
 *    Rev 1.21   May 27 2003 18:29:18   popescu
 * due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
 * 
 *    Rev 1.20   May 27 2003 13:14:04   popescu
 * RRIF Banking work
 * 
 *    Rev 1.19   May 23 2003 10:04:14   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.18   May 22 2003 14:11:58   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
// 
//    Rev 1.19   Mar 21 2003 18:00:16   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.18   Oct 09 2002 23:54:04   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.17   Sep 09 2002 12:15:10   KOVACSRO
// Sync-up PTS 10009768 : removed corr bank edit check 
// 
//    Rev 1.16   Aug 29 2002 12:55:06   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.15   Jul 08 2002 15:21:04   KOVACSRO
// fix for Default usage.
// 
//    Rev 1.14   Jul 05 2002 11:54:52   KOVACSRO
// Dynamically loading AcctUse subst. list.
// 
//    Rev 1.13   Jun 28 2002 11:50:16   KOVACSRO
// Added resetIntWire().
// 
//    Rev 1.12   Jun 12 2002 17:42:34   KOVACSRO
// usage fixes.
// 
//    Rev 1.11   Jun 07 2002 17:49:36   KOVACSRO
// International Wire modifications.
//
//    Rev 1.10   03 Jun 2002 15:20:40   KOVACSRO
// check in for Chin
// 
//    Rev 1.9   24 May 2002 15:42:52   KOVACSRO
// Fund and Client bank.
// 
//    Rev 1.8   22 May 2002 18:26:28   PURDYECH
// BFData Implementation
// 
//    Rev 1.7   Feb 25 2002 18:55:12   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.6   Jul 04 2001 11:26:00   ZHANGCEL
// Sync up with 1.2.1.4
// 
//    Rev 1.5   May 16 2001 13:37:16   WINNIE
// sync up with 1.2.1.3 : fix initialization of BankInstructions
// 
//    Rev 1.4   09 May 2001 14:36:12   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.2.1.2   26 Apr 2001 10:33:42   BUZILAMI
// fix
// 
//    Rev 1.2.1.1   Apr 19 2001 16:25:34   WINNIE
// initialization of substitution list
// 
//    Rev 1.2.1.0   Apr 16 2001 10:33:02   WINNIE
// Remove old validation for bank; copy new fields for bank between BankInstructions and the CBO;
// 
//    Rev 1.2   30 Mar 2001 17:09:26   BUZILAMI
// Systematic bank changes
// 
//    Rev 1.1   07 Mar 2001 15:42:16   BUZILAMI
// Broker, Branch, SlsRep Bank Instructions changes
// 
//    Rev 1.0   Feb 21 2001 16:02:34   BUZILAMI
// Initial revision.
// 
 * 
*/

