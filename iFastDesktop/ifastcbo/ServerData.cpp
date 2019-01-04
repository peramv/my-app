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
//    Copyright 1999 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : ServerData.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : Oct 2, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ServerData
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "serverdata.hpp"

FieldMap UpdTrakShr_FieldMap[]=
{
//	I_("SHRNUM"),                       I_("ShrNum"),
   I_("ACCTDESIGNATION"),              I_("AcctDesignation"),
   I_("GROUPCODE"),                    I_("GroupCode"),
   I_("RESPROVCODE"),                  I_("ResProvCode"),
   I_("TAXJURISCODE"),                 I_("TaxJurisCode"),
   //I_("INSTCODE"),                     I_("InstCode"),
   //I_("TRANSITNO"),						  I_("TransitNo"),
   //I_("BANKACCTNUM"),						  I_("BankAcctNum"),
   //I_("ADDITIONALINFO"),					  I_("AdditionalInfo"),
   NULL
};

FieldMap UpdTrakAct_FieldMap[]=
{
   //I_("SHRNUM"),								I_("ShrNum"),
   //I_("ACCOUNTNUM"),							I_("AccountNum"),
   //I_("ADDITIONALINFO"),					  I_("Repeating3"),
   I_("ALTACCOUNT"),             I_("AltAccount"),
   I_("BENOWNER"),             I_("BeneficialOwner"),
   I_("BRANCHCODE"),             I_("BranchCode"),
   I_("BRANCHNAME"),             I_("BranchName"),
   I_("BROKERCODE"),             I_("BrokerCode"),
   I_("BROKERNAME"),             I_("BrokerName"),
   I_("CURRENCY"),             I_("Currency"),
   I_("EMPLOYEE"),             I_("Employee"),
   I_("INTRUSTFOR"),             I_("InTrustFor"),
   //I_("ITFDETAILS"),						  I_("Repeating13"),
   I_("MARKETMAIL"),             I_("MarketMail"),
   I_("SALESREPCODE"),           I_("Slsrep"),
   I_("SALESREPNAME"),           I_("SlsrepName"),
   I_("STOPPUR"),                I_("StopPurchase"),
   I_("STOPRED"),                I_("StopRed"),
   I_("STOPXFERIN"),             I_("StopXferIn"),
   I_("STOPXFEROUT"),            I_("StopXferOut"),
   I_("SUPCONF"),                I_("SupConf"),
   I_("UNSEIZABLE"),             I_("Unseizable"),
   I_("TAXTYPE"),                I_("TaxType"),
   I_("ACCTTYPE"),             I_("AcctType"),
   //I_("STATUS"),								I_("AcctStatus"),
   I_("MANAGEMENTSTYLE"),              I_("ManagementStyle"),
   I_("DISCRETIONARY"),              I_("Discretionary"),
   NULL
};

FieldMap UpdTrakEnt_FieldMap[]=
{
   //I_("ACCOUNTNUM"),							I_("AccountNum"),
   //I_("ENTITYID"),							I_("EntityId"),
   I_("AUTHORIZEDTOTRADE"),        I_("AuthorizedToTrade"),
   I_("BUSEXT"),               I_("BusinessExt"),
   I_("BUSFAX"),               I_("BusinessFax"),
   I_("BUSPHONE"),             I_("BusinessPhone"),
   I_("DOFBIRTH"),             I_("DofBirth"),
   I_("EMAIL"),                I_("Email"),
   I_("ENTITYTYPE"),             I_("EntityType"),
   I_("FIRSTNAME"),              I_("FirstName"),
   I_("GENDER"),               I_("Gender"),
   I_("HOMEFAX"),                I_("HomeFax"),
   I_("HOMEPHONE"),              I_("HomePhone"),
   I_("LANG"),                 I_("LanguageCode"),
   I_("LASTNAME"),             I_("LastName"),
   I_("SALUTATION"),             I_("Salutation"),
   I_("SIN"),                  I_("SIN"),
   I_("BENIRREVOCABLE"),         I_("Irrevocable"),
   I_("BENPERCENTAGE"),            I_("BenPercentage"),
   I_("BENRELATECODE"),            I_("RelateCode"),
   I_("JOINTDISPCODE"),            I_("DepositionCode"),
   I_("JOINTTYPE"),              I_("JointType"),
   //I_("ADDITIONALINFO"),					  I_("Repeating23"),
   NULL
};

FieldMap UpdTrakAdd_FieldMap[]=
{
   //I_("SHRNUM"),								I_("ShrNum"),
   I_("ADDRCODE"),             I_("AddrCode"),
   I_("ADDRLINE1"),              I_("AddrLine1"),
   I_("ADDRLINE2"),              I_("AddrLine2"),
   I_("ADDRLINE3"),              I_("AddrLine3"),
   I_("ADDRLINE4"),              I_("AddrLine4"),
   I_("COUNTRYCODE"),            I_("CountryCode"),
   I_("POSTALCODE"),             I_("PostalCode"),
   //I_("EXCEPTIONMAIL"),						I_("Repeating9"),
   //I_("EXCEPTIONDETAILS"),					I_("Repeating10"),
   //I_("MAILINGINSTRUCTIONS"),				I_("Repeating11"),
   NULL
};

FieldMap UpdTrakTxn_FieldMap[]=
{
   I_("ACCOUNTNUM"),             I_("AccountNum"),
   I_("TRANSID"),                I_("TransId"),
   //I_("ADDITIONALINFO"),					I_("Repeating3"),
   I_("AMOUNT"),               I_("Amount"),
   I_("AMOUNTTYPE"),             I_("AmtType"),
   //I_("CHEQUEADDR"),							I_("Repeating6"),
   I_("CLASSFROMCODE"),            I_("FromClass"),
   //I_("CLASSFROMNAME"),						I_("Repeating8"),
   I_("CLASSTOCODE"),            I_("ToClass"),
   //I_("CLASSTONAME"),						I_("Repeating10"),
   I_("EXCHRATE"),             I_("ExchRate"),
   I_("ACQUISITIONFEE"),          I_("AcqFeeDefault"),
   I_("FEE"),                 I_("Fee"),
   I_("FEETYPE"),                I_("AcqFeeType"),
   I_("FLATPERCENT"),            I_("FlatPercent"),
   I_("FUNDFROMCODE"),           I_("FromFund"),
   //I_("FUNDFROMNAME"),						I_("Repeating15"),
   I_("FUNDTOCODE"),             I_("ToFund"),
   //I_("FUNDTONAME"),							I_("Repeating17"),
   I_("PAYTYPE"),                I_("TradesPayType"),
   I_("SETTLECURRENCY"),         I_("SettleCurrency"),
   //I_("SETTLEINFUNDCURR"),					I_("Repeating20"),
   I_("TRANSTYPE"),              I_("TradesTransType"),
   /*I_("DIVTOSAMEFUND"),						I_("Repeating22"),
   I_("DIVTOFUNDLIST"),						I_("Repeating23"),      
   I_("DIVTOCLASSLIST"),					I_("Repeating24"),
   I_("DIVTOPERCENTLIST"),					I_("Repeating25"),*/
   I_("REMARKS1"),              I_("Remarks1"),
   NULL
};

FieldMap UpdTrakDis_FieldMap[]=
{
   I_("ACCOUNTNUM"),             I_("AccountNum"),
   I_("FUNDCODE"),             I_("FundCode"),
   I_("CLASSCODE"),                I_("ClassCode"),
   I_("FUNDTOCODE"),               I_("FundToCode"),
   I_("CURRENCY"),               I_("Currency"),
   I_("TRANSTYPE"),                I_("TransType"),
   I_("DISTRIBUTIONPAYTYPE"),         I_("DistributionPayType"),
   I_("ALLOCPERCENT"),            I_("AllocPercent"),
/*	I_("TRANSID"),								I_("TransId"),
  //I_("ADDITIONALINFO"),					I_("Repeating3"),
  I_("AMOUNT"),								I_("Amount"),
  I_("AMOUNTTYPE"),							I_("AmtType"),
  //I_("CHEQUEADDR"),							I_("Repeating6"),
  I_("CLASSFROMCODE"),						I_("FromClass"),
  //I_("CLASSFROMNAME"),						I_("Repeating8"),
  I_("CLASSTOCODE"),						I_("FromCode"),
  //I_("CLASSTONAME"),						I_("Repeating10"),
  I_("EXCHRATE"),							I_("ExchRate"),
   I_("ACQUISITIONFEE"),					I_("AcqFeeDefault"),
   I_("FEE"),									I_("AcqFee"),
   I_("FEETYPE"),							   I_("AcqFeeType"),
  I_("FLATPERCENT"),						I_("FlatPercent"),
  I_("FUNDFROMCODE"),						I_("FromFund"),
  //I_("FUNDFROMNAME"),						I_("Repeating15"),
  I_("FUNDTOCODE"),							I_("ToFund"),
  //I_("FUNDTONAME"),							I_("Repeating17"),
  I_("PAYTYPE"),								I_("DepositType"),
  I_("SETTLECURRENCY"),					I_("SettleCurrency"),
  //I_("SETTLEINFUNDCURR"),					I_("Repeating20"),
  I_("TRANSTYPE"),							I_("TradesPayType"),*/
   /*I_("DIVTOSAMEFUND"),						I_("Repeating22"),
   I_("DIVTOFUNDLIST"),						I_("Repeating23"),
   I_("DIVTOCLASSLIST"),					I_("Repeating24"),
   I_("DIVTOPERCENTLIST"),					I_("Repeating25"),*/
   NULL
};

TableData _UpdTableData[]=
{
   I_("TRAKSHR"),I_("Shr"), UpdTrakShr_FieldMap,
   I_("TRAKACT"),I_("Act"), UpdTrakAct_FieldMap,
   I_("TRAKENT"),I_("Ent"), UpdTrakEnt_FieldMap,
   I_("TRAKADD"),I_("Add"), UpdTrakAdd_FieldMap,
   I_("TRAKTXN"),I_("Txn"), UpdTrakTxn_FieldMap,
   I_("TRAKDIS"),I_("Dis"), UpdTrakDis_FieldMap
};

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ServerData" );
}

ServerData::ServerData( BFAbstractCBO &parent )
: VerificationConf( parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   pVerificationStringProcessor = NULL;
}

//*****************************************************************************
ServerData::~ServerData()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( pVerificationStringProcessor )
      delete pVerificationStringProcessor;
}

//*****************************************************************************
SEVERITY ServerData::init( DString& param )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   if( param != NULL_STRING )
   {
      pVerificationStringProcessor = new VerificationStringProcessor;
      int NumItem = sizeof(_UpdTableData)/sizeof(_UpdTableData[0]);
      pVerificationStringProcessor->init( param, _UpdTableData, NumItem );

      pVerificationStringProcessor->ProcessUpdates();
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
void ServerData::getShareholderData( BFData **data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getShareholderData") );

   pVerificationStringProcessor->getShareholderData( data );
}   

//*****************************************************************************
void ServerData::getAccountData( BFData **data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAccountData") );

   pVerificationStringProcessor->getAccountData( data );
}   

bool ServerData::getEntityData( BFData **data, long type )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntityData") );

   return(pVerificationStringProcessor->getEntityData( data, type ));
}   

//*****************************************************************************
bool ServerData::getAddressData( BFData **data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAddressData") );

   return(pVerificationStringProcessor->getAddressData( data ));
}   

//*****************************************************************************
void ServerData::getTradesData( BFData **data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTradesData") );

   pVerificationStringProcessor->getTradesData( data );
}   

//*****************************************************************************
void ServerData::getAccDistributionData( BFData **data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAccDistributionData") );

   pVerificationStringProcessor->getAccDistributionData( data );
}   

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ServerData.cpp-arc  $
 // 
 //    Rev 1.16   Nov 14 2004 14:53:46   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.15   Oct 09 2002 23:54:58   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.14   Aug 29 2002 12:56:36   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.13   22 May 2002 18:29:50   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.12   03 May 2001 14:07:06   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.11   Apr 02 2001 10:47:46   FENGYONG
 // Add remarks1
 // 
 //    Rev 1.10   Mar 29 2001 12:27:32   FENGYONG
 // add managementstyle and discretionary
 // 
 //    Rev 1.9   Dec 17 2000 20:24:28   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.8   Dec 11 2000 11:55:34   VASILEAD
 // changed AcqFee to Fee
 // 
 //    Rev 1.7   Dec 04 2000 13:23:36   VASILEAD
 // Fixed the FundTo parameter
 // 
 //    Rev 1.6   Nov 10 2000 15:39:16   VASILEAD
 // Chaged fields for TXN buffer
 // 
 //    Rev 1.5   Nov 01 2000 10:36:10   VASILEAD
 // Added Purchase service
 // 
 //    Rev 1.4   Oct 27 2000 16:11:04   VASILEAD
 // Added Purchase service
 // 
 //    Rev 1.3   Oct 20 2000 11:14:02   VASILEAD
 // Fixed NASU process
 // 
 //    Rev 1.2   Oct 16 2000 16:27:18   VASILEAD
 // Added Shareholder and Account in NASU
 // 
 //    Rev 1.1   Oct 11 2000 11:55:48   VASILEAD
 // Added server updates support
 // 
 //    Rev 1.0   Oct 03 2000 11:20:22   VASILEAD
 // Initial revision.
 // 
 // 
*/