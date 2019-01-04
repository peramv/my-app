//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : SettlementTotal.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
//********************************************************************************
#include "stdafx.h"

#include "SettlementTotal.hpp"
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include "dstcommonfunction.hpp"
#include <ifastdataimpl\dse_dstc0200_vw.hpp>
#include <ifastdataimpl\dse_dstc0206_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SHAREHOLDER;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "SettlementTotal" );
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_SHAREHOLDER_NUMBER_EXISTS;
   extern const long ERR_SHAREHOLDER_NUM_CANNOT_BE_LEFT_EMPTY;
   extern const long ERR_EFFECTIVE_DATE_BACKWARD;
   extern const long ERR_SHAREHOLDER_NUMBER_CANNOT_START_WITH_ZERO;
   extern const long ERR_SHAREHOLDER_NUMBER_EMPTY;
   extern const long ERR_RESIDENCE_PROVINCE_EMPTY;
   extern const long ERR_TAX_JURIS_EMPTY;
   extern const long ERR_INVALID_SHAREHOLDER_NUM;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId PurchaseTotalSettle;
   extern CLASS_IMPORT const BFDecimalFieldId RedemptionTotalSettle;
   extern CLASS_IMPORT const BFDecimalFieldId NetTotalSettle;
   extern CLASS_IMPORT const BFDecimalFieldId CountTotalSettel;
   extern CLASS_IMPORT const BFTextFieldId GNSettle;
   extern CLASS_IMPORT const BFTextFieldId Settled;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,			Group Flags 
   { ifds::RedemptionTotalSettle, BFCBO::NONE, 0 }, 
   { ifds::PurchaseTotalSettle,   BFCBO::NONE, 0 }, 
   { ifds::NetTotalSettle,        BFCBO::NONE, 0 }, 
   { ifds::CountTotalSettel,      BFCBO::NONE, 0 }
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );



const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "" ),    BFCBO::NONE,     0},

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************

SettlementTotal::SettlementTotal( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************

SettlementTotal::~SettlementTotal()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************
SEVERITY SettlementTotal::init(const BFData&   data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
   setDefaultValue(BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}
//*************************************************************************************
void SettlementTotal::setDefaultValue(const BFDataGroupId& idDataGroup )
{
   setFieldNoValidate(ifds::RedemptionTotalSettle,I_("0.00"),idDataGroup,true); 
   setFieldNoValidate(ifds::PurchaseTotalSettle,I_("0.00"),idDataGroup,true);   
   setFieldNoValidate(ifds::NetTotalSettle,I_("0.00"),idDataGroup,true);  
   setFieldNoValidate(ifds::CountTotalSettel,I_("0"),idDataGroup,true);   
}

//*************************************************************************************

SEVERITY SettlementTotal::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY SettlementTotal::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges" ) );


   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
//when user chage SettleAll, the following function is called
// public
SEVERITY SettlementTotal::setAllTotal( const MFCanBFCbo* pCbo, bool bSettleAll,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAllTotal" ) );

   DString dstrValue = I_("0");
   const BFFieldId fieldOrg[] = {ifds::PurchaseTotal,ifds::EligibleRedempTotal,ifds::EligibleNetTotal,ifds::CountTotal, ifds::NullFieldId};
   const BFFieldId fieldDes[] = {ifds::PurchaseTotalSettle,ifds::RedemptionTotalSettle,
      ifds::NetTotalSettle,ifds::CountTotalSettel, ifds::NullFieldId};

   int i = 0;
   while( fieldDes[i] != ifds::NullFieldId )
   {
      if( bSettleAll )
      {
         getField(fieldOrg[i],dstrValue,idDataGroup,true);
      }
      setFieldNoValidate(fieldDes[i],dstrValue,idDataGroup,true);  
      i++;
   }
   
   if(!bSettleAll) return GETCURRENTHIGHESTSEVERITY();

   DString dstrCurrency;
   getField(ifds::Currency, dstrCurrency, idDataGroup);
   for(BFObjIter iter(*const_cast<MFCanBFCbo*>(pCbo),idDataGroup, false,BFObjIter::NON_DELETED);
	   !iter.end();
	   ++iter)
   {
	   DString iterSettleCurrency, iterGNSettle, iterOrigGNSettle;
	   iter.getObject()->getField(ifds::SettleCurrency, iterSettleCurrency, idDataGroup);
	   if(iterSettleCurrency != dstrCurrency) continue;

	   iter.getObject()->getField(ifds::GNSettle, iterGNSettle, idDataGroup);
	   iter.getObject()->getFieldBeforeImage(ifds::GNSettle, iterOrigGNSettle);
	   iterOrigGNSettle.stripAll();

	   if(iterGNSettle == iterOrigGNSettle) continue;

	   DString iterTransType;
	   iter.getObject()->getField(ifds::TransType, iterTransType, idDataGroup);	   
	   if(iterTransType != I_("ED") && iterTransType != I_("PW")) continue;
	   
	   auto fieldSettleTotal = iterTransType == I_("ED")? 
		   ifds::PurchaseTotalSettle :
		   ifds::RedemptionTotalSettle;

		DString dstrSettleTotal, iterNetAmount;
		getField(fieldSettleTotal, dstrSettleTotal, idDataGroup);
		iter.getObject()->getField(ifds::NetAmt, iterNetAmount, idDataGroup);
		
		DString iterCommission;
		iter.getObject()->getField(ifds::Commission, iterCommission, idDataGroup);

		BigDecimal settleTotal(dstrSettleTotal);
		BigDecimal netAmount(iterNetAmount);
		BigDecimal commission(iterCommission);
		BigDecimal grossAmount = netAmount + commission;

		if(iterGNSettle == I_("G"))
			settleTotal = (settleTotal - netAmount) + grossAmount;
		else
			settleTotal = (settleTotal - grossAmount) + netAmount;

		setFieldNoValidate(fieldSettleTotal, settleTotal.asDString(), idDataGroup);
   }
   

   return(GETCURRENTHIGHESTSEVERITY());
}
//*********************************************************************************
//the following function handle Settle and Gross or Net 
// public
SEVERITY SettlementTotal::CalculateTotal(const MFCanBFCbo* pCbo ,const BFFieldId& idField,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("CalculateTotal" ) );
   DString dstrGrossNet,dstrSettle,dstrTransType;
   pCbo->getField(ifds::TransType,  dstrTransType,idDataGroup,false );
   dstrTransType.strip();
   pCbo->getField(ifds::GNSettle,   dstrGrossNet,idDataGroup,false );
   dstrGrossNet.strip();

   BFFieldId adjustField = ifds::RedemptionTotalSettle;
   if( dstrTransType == I_("ED") ) // Purchase
   {
      adjustField = ifds::PurchaseTotalSettle;   
   }

   bool bGNChange = false;
   if( idField == ifds::GNSettle ) bGNChange = true;
   changeSettleTotal(pCbo,adjustField,idDataGroup,bGNChange );
   //change Net
   changeNetValue(idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// private
//
void SettlementTotal::changeSettleTotal(const MFCanBFCbo* pCbo,const BFFieldId& idField, const BFDataGroupId& idDataGroup,bool bGNChange )
{
   DString dstrOrgValue,dstrValue,dstrSettle;
   pCbo->getField(ifds::Settled, dstrSettle,idDataGroup,false );
   dstrSettle.strip(); 
   getField(idField,dstrOrgValue,idDataGroup );
  
   if( bGNChange )
   { //chage Gross Net; 
	   BigDecimal dOrg( dstrOrgValue );
	   
	   DString dstrGrossAmt, dstrNetAmt;
	   pCbo->getField(ifds::GrossAmt, dstrGrossAmt, idDataGroup);
	   pCbo->getField(ifds::NetAmt, dstrNetAmt, idDataGroup);

	   DString dstrGN;
	   pCbo->getField(ifds::GNSettle, dstrGN, idDataGroup,false );
	   dstrGN.strip();

	   BigDecimal grossAmt(dstrGrossAmt);
	   BigDecimal netAmt(dstrNetAmt);
	   BigDecimal dValue;

      if( dstrGN == I_("G") ) //from Net to G 
         dValue = (dOrg - netAmt) + grossAmt;
      else if( dstrGN == I_("N") )
         dValue = (dOrg - grossAmt) + netAmt;

	  setFieldNoValidate(idField,dValue.asDString(),idDataGroup );
   }
   else // adjust amount  //change settle
   {
	   double dValue = 0.00;
	   double dOrg = DSTCommonFunctions::convertToDouble(dstrOrgValue);

      if( dstrSettle == I_("Y") )
         dValue = dOrg + getAdjustAmount( pCbo,idDataGroup );
      else
         dValue = dOrg - getAdjustAmount( pCbo,idDataGroup );

      adjustCountSettle(dstrSettle == I_("Y"),idDataGroup);
	  dstrValue = DSTCommonFunctions::doubleToDString(  idField,dValue );
	  setFieldNoValidate(idField,dstrValue,idDataGroup );
   }
   
}
//******************************************************************************
//private
void  SettlementTotal::adjustCountSettle(bool bSettle,const BFDataGroupId& idDataGroup )
{
   DString dstrCount;
   getField( ifds::CountTotalSettel,dstrCount,idDataGroup );
   int iCount = dstrCount.asInteger();
   if( bSettle )
      iCount++;
   else
      iCount--;
   dstrCount = DString::asString( iCount );
   setFieldNoValidate( ifds::CountTotalSettel,dstrCount,idDataGroup );
}

//*****************************************************************************
// the function change the NetTotalSettle
// private
void  SettlementTotal::changeNetValue(const BFDataGroupId& idDataGroup )
{
   DString dstrPurChase,dstrRedemption,dstrNet;
   getField(ifds::PurchaseTotalSettle,dstrPurChase,idDataGroup );
   getField(ifds::RedemptionTotalSettle,dstrRedemption,idDataGroup );
   double dPurchase = DSTCommonFunctions::convertToDouble( dstrPurChase );
   double dRedemption = DSTCommonFunctions::convertToDouble( dstrRedemption );
   double dNet = dPurchase + dRedemption;
   dstrNet = DSTCommonFunctions::doubleToDString( ifds::NetTotalSettle,dNet );
   setFieldNoValidate(ifds::NetTotalSettle,dstrNet,idDataGroup);
}
//*****************************************************************************
//
double SettlementTotal::getAdjustAmount(const MFCanBFCbo* pCbo, const BFDataGroupId& idDataGroup)
{
   DString dstrGrossNet, dstrGrossAmount,dstrTransType;
   pCbo->getField(ifds::TransType,  dstrTransType,idDataGroup,false );
   dstrTransType.strip();
   BFFieldId idGrossAmt = ifds::NullFieldId;
   if( dstrTransType == I_("ED") )
      idGrossAmt = ifds::GrossAmt;
   else if( dstrTransType == I_("PW") ||  dstrTransType == I_("AF") )
      idGrossAmt = ifds::NetAmt;

   pCbo->getField(idGrossAmt,dstrGrossAmount,idDataGroup,false);
   dstrGrossAmount.strip();
   double dGrossAmt = DSTCommonFunctions::convertToDouble( dstrGrossAmount );
   double dAdj;
   pCbo->getField(ifds::GNSettle,dstrGrossNet,idDataGroup,false);
   dstrGrossNet.strip();
   if( I_("G") == dstrGrossNet )
   {
      dAdj = dGrossAmt; 
   }
   else
   {

      dAdj = dGrossAmt - getCommission(pCbo,idDataGroup);
   }
   return(dAdj);
}

//******************************************************************************
double SettlementTotal::getCommission(const MFCanBFCbo* pCbo, const BFDataGroupId& idDataGroup)
{
   DString dstrCommision1,dstrCommision2;
   pCbo->getField(ifds::CommSettleCurr,dstrCommision1, idDataGroup);
   pCbo->getField(ifds::Comm2SettleCurr,dstrCommision2,   idDataGroup);

   double dCom1 = DSTCommonFunctions::convertToDouble( dstrCommision1 );
   double dCom2 = DSTCommonFunctions::convertToDouble( dstrCommision2 );
   double dCom = dCom1 + dCom2;
   return(dCom);
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTotal.cpp-arc  $
// 
//    Rev 1.14   Nov 14 2004 14:54:08   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.13   Sep 08 2004 18:14:00   ZHANGCEL
// PET1094-FN8 -- AdminFee related changes
// 
//    Rev 1.12   Aug 13 2004 13:57:26   YINGBAOL
// PET1027:StopSettlementRedemption
// 
//    Rev 1.11   Oct 01 2003 09:30:56   YINGBAOL
// change settlement Total calculation
// 
//    Rev 1.10   Sep 10 2003 16:05:40   YINGBAOL
// use CommSettleCurr to calculte SettleAmount
// 
//    Rev 1.9   Mar 21 2003 18:23:58   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Oct 09 2002 23:54:58   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.7   Aug 29 2002 12:56:38   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   Aug 13 2002 12:52:48   YINGBAOL
// change calculation for settle total
// 
//    Rev 1.5   Aug 06 2002 15:03:08   HERNANDO
// PTS 10009268 - Clean up.  Removed ERR_DATE_FUNCTIONS from Namespace.
// 
//    Rev 1.4   Jun 13 2002 17:15:14   YINGBAOL
// set default value for calculate fields
// 
//    Rev 1.3   Jun 11 2002 11:42:38   YINGBAOL
// more business rules added
// 
//    Rev 1.2   Jun 06 2002 16:08:24   YINGBAOL
// save work
//



//

