//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//*****************************************************************************
//
//    ^FILE   : BankInstructions4Trxn.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : October 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : BankInstructions4Trxn
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "bankinstructions4trxn.hpp"
#include <ifastdataimpl\dse_dstc0055_vw.hpp>

namespace 
{
   const I_CHAR * CLASSNAME = I_( "BankInstructions4Trxn" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId BankAcctCurrency;
   extern CLASS_IMPORT const BFTextFieldId BankAcctName;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const DIVIDEND;
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
}

namespace AcctUseCode
{
   extern const I_CHAR * const EFT;
   extern const I_CHAR * const DIRECT_TRADING;
   extern const I_CHAR * const EFT_REDEMPTION;
   extern const I_CHAR * const EFT_DIVIDEND;
   extern const I_CHAR * const COMM_CLEAR;
   extern const I_CHAR * const DIRECT_DEPOSIT;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,             State Flags,      Group Flags
   { ifds::EffectiveDate,     BFCBO::NONE,           0 },
}
;

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
BankInstructions4Trxn::BankInstructions4Trxn (BFAbstractCBO &parent, 
   const DString &transType, const DString &payType) : BankInstructions(parent),
_transType (transType),
_payType (payType)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
}

//******************************************************************************
BankInstructions4Trxn::~BankInstructions4Trxn()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY BankInstructions4Trxn::preInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("preInit"));
   //call super
   BankInstructions::preInit (idDataGroup);

   setFieldNoValidate (ifds::TransType, _transType, 
      idDataGroup, false, true, true);
   if (DSTCommonFunctions::codeInList (_transType, TRADETYPE::PURCHASE_LIKE))
   {
      if (_payType == I_("D"))
      {
         setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::DIRECT_TRADING, 
            idDataGroup, false, true, true);
      }
      else
      {
         setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::EFT, 
            idDataGroup, false, true, true);
      }
   }
   else if (DSTCommonFunctions::codeInList (_transType, TRADETYPE::REDEMPTION_LIKE))
   {
      if (_transType == TRADETYPE::ADMIN_FEE || 
          _transType == TRADETYPE::MGMT_FEE)
      {
         setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::COMM_CLEAR, 
            idDataGroup, false, true, true);
      }
      else
      {
         if (_payType == I_("D"))
         {
            setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::DIRECT_TRADING, 
               idDataGroup, false, true, true);
         }
         else if (_payType == I_("D1"))
         {
            setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::DIRECT_DEPOSIT, 
               idDataGroup, false, true, true);
         }
         else
         {
            setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::EFT_REDEMPTION, 
               idDataGroup, false, true, true);
         }
      }
   }
   else if (_transType == TRADETYPE::DIVIDEND)
   {
      setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::EFT_DIVIDEND, 
         idDataGroup, false, true, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructions4Trxn::init (const BFData &data, 
   const DString &dstrBankType)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   BankInstructions::init (data, dstrBankType);
   postInit (BF::HOST);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructions4Trxn::postInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("postInit"));
   //calls the base
   BankInstructions::postInit (idDataGroup);
   //set the bank account name as read only
   setFieldReadOnly (ifds::AcctUseCode, idDataGroup, true);
   setFieldReadOnly (ifds::BankIdType, idDataGroup, true);
   setFieldReadOnly (ifds::BankIdValue, idDataGroup, true);
   setFieldReadOnly (ifds::TransitNo, idDataGroup, true);
   setFieldReadOnly (ifds::BankAcctNum, idDataGroup, true);
   setFieldReadOnly (ifds::BankAcctName, idDataGroup, true);
   setFieldReadOnly (ifds::BankAcctCurrency, idDataGroup, true);
   setFieldReadOnly (ifds::FFC, idDataGroup, true);
   setFieldReadOnly (ifds::PayReason1, idDataGroup, true);
   setFieldReadOnly (ifds::PayReason2, idDataGroup, true);
   setFieldReadOnly (ifds::BankAcctType, idDataGroup, true);
   setFieldReadOnly (ifds::StopDate, idDataGroup, true);
   setFieldReadOnly (ifds::EffectiveDate, idDataGroup, true);
   setFieldReadOnly (ifds::ACHProcessor, idDataGroup, true);
//correspondent banking
   setFieldReadOnly (ifds::TransitNoCB, idDataGroup, true);
   setFieldReadOnly (ifds::BankIdValueCB, idDataGroup, true);
   setFieldReadOnly (ifds::BankIdTypeCB, idDataGroup, true);
   setFieldReadOnly (ifds::InstNameCB, idDataGroup, true);
   setFieldReadOnly (ifds::BankCountryCB, idDataGroup, true);
   setFieldReadOnly (ifds::BankPostalCB, idDataGroup, true);
   setFieldReadOnly (ifds::BankContactCB, idDataGroup, true);
   setFieldReadOnly (ifds::BankAddrCB1, idDataGroup, true);
   setFieldReadOnly (ifds::BankAddrCB2, idDataGroup, true);
   setFieldReadOnly (ifds::BankAddrCB3, idDataGroup, true);
   setFieldReadOnly (ifds::BankAddrCB4, idDataGroup, true);
   setFieldReadOnly (ifds::BankAddrCB5, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructions4Trxn.cpp-arc  $
// 
//    Rev 1.9   Jan 27 2010 17:06:18   popescu
// Incident 1991646 - made sure that the account usage code on redemption banking is properly set for in species redemptions.
// 
//    Rev 1.8   Jul 16 2009 19:13:32   dchatcha
// PET156681 FN14 H36 Investor Authorization, Integration issues.
// 
//    Rev 1.7   Nov 14 2004 14:28:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Sep 08 2004 18:07:14   ZHANGCEL
// PET1094-FN8 -- AdminFee related changes
// 
//    Rev 1.5   Jul 22 2004 09:56:32   popescu
// PTS 10027951, acct usage of the banking infor for a CASH ID transaction is displayed as 'EFT Dividend'
// 
//    Rev 1.4   Feb 13 2004 18:04:28   popescu
// PTS 10027188, copy the value of the file processor field into trading screen, and trade banking screen, when modifying a pending trade; removed the substitution list of the BankInstrType, since the combo is being loaded anyhow in the dialog. This field is not  updatable. Assign the correct transaction type to the bankinstructions4trxn object and set all the fields to read only in postInit
// 
//    Rev 1.3   Dec 29 2003 18:35:36   popescu
// PTS 10025597, cleared the TransitNum if the bank id type changes and the bank id type doesn't support transits
// 
//    Rev 1.2   Nov 10 2003 14:52:10   popescu
// Revised the names of the suppporting objects based on Desktop's naming standards
// 
//    Rev 1.1   Oct 30 2003 17:27:02   FENGYONG
// Add paytype as a parameter
// 
//    Rev 1.0   Oct 19 2003 19:08:26   popescu
// Initial revision.
// 
 */