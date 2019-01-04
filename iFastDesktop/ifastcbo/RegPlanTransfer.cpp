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
//    Copyright 1999-2016 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : RegPlanTransfer.cpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ^CLASS  : RegPlanTransfer
// ^PARENT : 
//
// ^CLASS DESCRIPTION :
//  ements a map from the STL to hold fully instantiated CBOBase objects
//  that are created from Data objects stored in the inherited ListBase class
//
//******************************************************************************

#include "stdafx.h"
#include "RegPlanTransfer.hpp"
#include "fundmasterlist.hpp"
#include "funddetaillist.hpp"

#include "regplantransferalloclist.hpp"
#include "translationtablebyasyncreading.hpp"
#include "mgmtco.hpp"


#include <ifastdataimpl\dse_dstc0472_vw.hpp>
#include <ifastdataimpl\dse_dstc0472_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0472_req.hpp>
#include <ifastdataimpl\dse_dstc0474_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0474_req.hpp>


namespace IFASTERR
{
   //   extern CLASS_IMPORT I_CHAR * const NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP;
}

namespace
{
   // Trace literals
   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
   const I_CHAR * const OTHER          = I_( "OTHER" );
   const I_CHAR * const CLASSNAME = I_( "RegPlanTransfer" );

   const I_CHAR * const REGTRANSFER_STATUS_OPEN = I_("1");
   const I_CHAR * const AMOUNTTYPEALLOC_PERCENT = I_("P");
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const INVALID_INSTITUTION_CODE;
}

namespace CORFAX
{
   extern CLASS_IMPORT const DSTCHost HOST;
   const char *const CFX_TRANS      = "CFXTRAN";
}
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SWP_TAX_OVERRIDE;
}
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DEPOSIT;
   extern CLASS_IMPORT const DSTCRequest TRANS_NUM;
   extern CLASS_IMPORT const DSTCRequest ACTIVE_BATCH;
   extern CLASS_IMPORT const DSTCRequest MEXT_PROC_DATE;
}

namespace AMT_TYPE
{
}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_FUND_NOT_EFFECTIVE;
   extern const long ERR_FUND_CLASS_NOT_EFFECTIVE;
   extern const long ERR_INVALID_INSTITUTION_CODE;
   extern const long WARN_INVALID_INSTITUTION_CODE;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RESTART_PAC_ON_CAPPED_FUND;
   extern CLASS_IMPORT I_CHAR * const SWP_TAX_OVERRIDE;
}

namespace TRADETYPE 
{
   extern CLASS_IMPORT I_CHAR * const PAC;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId CPIRate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId IndexType;
   extern CLASS_IMPORT const BFTextFieldId AmountType1;
}

namespace PLATFORM
{
   const I_CHAR * const DESKTOP = I_("01"); 
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   //  Field DD Id,                    State Flags,            Group Flags 
   { ifds::RunMode         ,           BFCBO::NONE,                  0 },
   { ifds::RegTransferMstrUUID,         BFCBO::NONE,                 0 },
   { ifds::RegTransferStatus,           BFCBO::NONE,                 0 },
   { ifds::AccountNum,                  BFCBO::NONE,                 0 },
   { ifds::ExternalInstitution,         BFCBO::REQUIRED,             0 },
   { ifds::ExternalInstitutionName,     BFCBO::NONE,                 0 },
   { ifds::ExternalInstitutionAcct,     BFCBO::NONE,                 0 },
   { ifds::ExpectedAmt,                 BFCBO::NONE,                 0 },
   { ifds::ActualAmount,                BFCBO::NONE,                 0 },
   { ifds::AmountTypeAlloc,             BFCBO::NONE,                 0 },
   { ifds::InitiationDate,              BFCBO::NONE,                 0 },
   { ifds::ClosedDate,                  BFCBO::NONE,                 0 },
   { ifds::Version,                     BFCBO::NONE,                 0 },
   { ifds::ModDate,                     BFCBO::NONE,                 0 },
   { ifds::ModUser,                     BFCBO::NONE,                 0 },
   { ifds::ProcessDate,                 BFCBO::NONE,                 0 },
   { ifds::Username,                    BFCBO::NONE,                 0 },

};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//************************************************************************
RegPlanTransfer::RegPlanTransfer( BFAbstractCBO &parent ) : 
   MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,(const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);


}

//************************************************************************
RegPlanTransfer::~RegPlanTransfer()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//************************************************************************
SEVERITY RegPlanTransfer::init( const BFDataGroupId& idDataGroup, const BFData &viewData)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject(const_cast<BFData&>(viewData), false, true);

   setFieldSubstituteValues( ifds::AmountTypeAlloc, idDataGroup, ifds::AmountType1);

   DString dstrExternalInstitution;     
   dstrExternalInstitution = viewData.getElementValue(ifds::ExternalInstitution);

   if(dstrExternalInstitution.length() > 0  && OTHER != dstrExternalInstitution.stripAll())
      setFieldReadOnly(ifds::ExternalInstitutionName, idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY();
}


//*********************************************************************************
void RegPlanTransfer::init2( const BFDataGroupId& idDataGroup, RegPlanTransferList *pList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

}

//************************************************************
SEVERITY RegPlanTransfer::initNew( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   setFieldSubstituteValues( ifds::AmountTypeAlloc, idDataGroup, ifds::AmountType1);
   RegPlanTransferAllocList*  _pRegPlanTransferAllocList = new RegPlanTransferAllocList( *this );

   _pRegPlanTransferAllocList->initNew( idDataGroup);

   setObject( _pRegPlanTransferAllocList, I_( "RegPlanTransferAllocList" ), OBJ_ACTIVITY_NONE, BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}


//**********************************************************
void RegPlanTransfer::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
      CLASSNAME, 
      I_("doInitWithDefaultValues"));
   DString currBusDate;
   getWorkSession ().getOption ( ifds::CurrBusDate, currBusDate, idDataGroup, false);
   setFieldNoValidate ( ifds::InitiationDate, currBusDate, idDataGroup, false);

   setFieldNoValidate ( ifds::RegTransferStatus, REGTRANSFER_STATUS_OPEN, idDataGroup, false);
   setFieldNoValidate ( ifds::AmountTypeAlloc,   AMOUNTTYPEALLOC_PERCENT, idDataGroup, false);
}



//*******************************************************************************
SEVERITY RegPlanTransfer::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if (idField == ifds::ExternalInstitution)
   {
      validateExternalInst(strValue, idDataGroup);

   }

   return(GETCURRENTHIGHESTSEVERITY());
}


SEVERITY RegPlanTransfer::validateExternalInst(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateExternalInst" ) );

   MiscInfoExternalInstitutionList *pMiscInfoExternalInstitutionList = nullptr;
   if(getMgmtCo().getMiscInfoExternalInstitutionList(pMiscInfoExternalInstitutionList) <= WARNING && pMiscInfoExternalInstitutionList != NULL)
   {
      DString lookupValue(strValue);
      lookupValue.stripAll().upperCase();

      if(!pMiscInfoExternalInstitutionList->codeExists(lookupValue))
      {
         getErrMsg(IFASTERR::INVALID_INSTITUTION_CODE, CND::ERR_INVALID_INSTITUTION_CODE, CND::WARN_INVALID_INSTITUTION_CODE, idDataGroup );
      };
   }


   return(GETCURRENTHIGHESTSEVERITY());
}
//************************************************************************************************
SEVERITY RegPlanTransfer::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if (idField == ifds::ExternalInstitution)
   {
      DString dstrExternalInstitution;
      getField (ifds::ExternalInstitution, dstrExternalInstitution, idDataGroup, false);
      dstrExternalInstitution.stripAll().upperCase();

      MiscInfoExternalInstitutionList *pMiscInfoExternalInstitutionList = nullptr;
      if(getMgmtCo().getMiscInfoExternalInstitutionList(pMiscInfoExternalInstitutionList) <= WARNING && pMiscInfoExternalInstitutionList != NULL)
      {
         DString strDescription;
         bool isOther = false;
         if(isOther)
            strDescription = I_("");
         if(pMiscInfoExternalInstitutionList->getDescription(dstrExternalInstitution, strDescription, isOther))
         {
            setFieldReadOnly(ifds::ExternalInstitutionName, idDataGroup, !isOther);
            setField(ifds::ExternalInstitutionName, strDescription, idDataGroup, false, true);
         }
      }
   }
   else if(idField == ifds::RegTransferStatus)
   {
      DString dstrStatus;
      getField (idField, dstrStatus, idDataGroup, false);
      if(I_("2") == dstrStatus || I_("3") == dstrStatus) //Closed, Cancelled
      {
         DString dstrCurrentBusinessDate;
         getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false);
         setFieldNoValidate(ifds::ClosedDate, dstrCurrentBusinessDate, idDataGroup, false, true, true);
      }
      else if(I_("1") == dstrStatus) //Open
      {
         //DString dstrCurrentBusinessDate;
         //getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup);
         setFieldNoValidate(ifds::ClosedDate, I_(""), idDataGroup, false, true, true);
      }
   }
   else if(idField == ifds::AmountTypeAlloc)
   {
      applyAmountTypeAllocChange(idDataGroup);
   }
   else if(idField == ifds::ExpectedAmt)
   {
      //DString expectedAmount;
      //getField(idField, expectedAmount, idDataGroup, false);
      //BigDecimal totalAmount(expectedAmount);
      //RegPlanTransferAllocList *pRegPlanTransferAllocList = NULL;
      //if(getRegPlanTransferAllocList(idDataGroup,  pRegPlanTransferAllocList ) <= WARNING && pRegPlanTransferAllocList != NULL)
      //{
      //   pRegPlanTransferAllocList->updateTotalAmount(idDataGroup, totalAmount);
      //}
      //
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

void RegPlanTransfer::applyAmountTypeAllocChange( const BFDataGroupId& idDataGroup)
{
   DString dstrAmountTypeAlloc;
   getField(ifds::AmountTypeAlloc, dstrAmountTypeAlloc, idDataGroup);
   RegPlanTransferAllocList *pRegPlanTransferAllocList = NULL;
   if(getRegPlanTransferAllocList(idDataGroup,  pRegPlanTransferAllocList ) <= WARNING && pRegPlanTransferAllocList != NULL)
   {
      pRegPlanTransferAllocList->setPercentTypeAlloc(idDataGroup, I_("P") == dstrAmountTypeAlloc.strip().upperCase());
   }

}


//*****************************************************
SEVERITY RegPlanTransfer::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY RegPlanTransfer::validateFundCode( const DString& dstrfundCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );
   FundMasterList* _pFundMasterList = NULL;
   MgmtCo &mgmtCo = getMgmtCo();

   mgmtCo.getFundMasterList(_pFundMasterList);

   if( _pFundMasterList != NULL && !dstrfundCode.empty() )
   {
      if( _pFundMasterList->IsFundExist( dstrfundCode, idDataGroup ) == false )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      }
      else  //if fund does exists
      {
         DString dstrEffectiveDate, dstrclassCode;
         getField( ifds::InitiationDate, dstrEffectiveDate, idDataGroup, false );
         //getField( ifds::ClassCode, dstrclassCode, idDataGroup, false );
         if( _pFundMasterList->IsFundValidAtDate ( dstrfundCode, dstrEffectiveDate, idDataGroup) == false )
         {
            DString idiStr, FundCodeCopy( dstrfundCode );
            addIDITagValue( idiStr, I_( "FUNDNAME" ),  FundCodeCopy.strip() );
            ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_NOT_EFFECTIVE, idiStr );
         }

      }
   }
   return(GETCURRENTHIGHESTSEVERITY());  
}

SEVERITY RegPlanTransfer::validateClassCode( const DString& dstrfundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClassCode" ) );
   FundDetailList*  _pFundDetailList = NULL;
   MgmtCo &mgmtCo = getMgmtCo();

   mgmtCo.getFundDetailList(_pFundDetailList);

   if( _pFundDetailList != NULL && (!dstrfundCode.empty() || !dstrClassCode.empty()) )
   {
      FundDetail *pFundDetail = NULL;
      if( _pFundDetailList->getFundDetail( dstrfundCode, dstrClassCode, idDataGroup, pFundDetail ) == false )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      }
      else
      {
         DString dstrEffectiveDate;
         getField( ifds::InitiationDate, dstrEffectiveDate, idDataGroup, false );

         //If FundCode is not effective then don't need to validate classcode
         SEVERITY sev = NO_CONDITION;
         sev = validateFundCode( dstrfundCode, idDataGroup );
         if(sev <= WARNING)
         {
            if( _pFundDetailList->IsFundValidAtDate ( dstrfundCode, dstrClassCode, dstrEffectiveDate, idDataGroup) == false )
            {
               DString idiStr, FundCodeCopy( dstrfundCode ), ClassCodeCopy( dstrClassCode );
               addIDITagValue( idiStr, I_( "FUNDNAME" ),  FundCodeCopy.strip() );
               addIDITagValue( idiStr, I_( "CLASSNAME" ), ClassCodeCopy.strip() );
               ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_EFFECTIVE, idiStr );
            }
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());  
}

SEVERITY RegPlanTransfer::getRegPlanTransferAllocList(const BFDataGroupId& idDataGroup,  RegPlanTransferAllocList *&pRegPlanTransferAllocList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRegPlanTransferAllocList" ) );

   RegPlanTransferAllocList *_pRegPlanTransferAllocList = dynamic_cast< RegPlanTransferAllocList* >( BFCBO::getObject( I_( "RegPlanTransferAllocList" ), idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !_pRegPlanTransferAllocList)
   {

      _pRegPlanTransferAllocList = new RegPlanTransferAllocList( *this );
      DString dstrRegTransferMstrUUID;
      getField(ifds::RegTransferMstrUUID, dstrRegTransferMstrUUID, idDataGroup);

      _pRegPlanTransferAllocList->init( idDataGroup, dstrRegTransferMstrUUID);

      setObject( _pRegPlanTransferAllocList, I_( "RegPlanTransferAllocList" ), OBJ_ACTIVITY_NONE, BF::HOST );

      DString dstrAmountTypeAlloc;
      getField(ifds::AmountTypeAlloc, dstrAmountTypeAlloc, idDataGroup);
      _pRegPlanTransferAllocList->setPercentTypeAlloc(idDataGroup, I_("P") == dstrAmountTypeAlloc.strip().upperCase());
   }

   pRegPlanTransferAllocList = _pRegPlanTransferAllocList;

   return(GETCURRENTHIGHESTSEVERITY());
}

void RegPlanTransfer::ModelOffer(RegPlanTransfer *Model, const BFDataGroupId& idDataGroup)
{
   BFData data_DSTC0472(ifds::DSTC0472_VWRepeat_Record);


   BFDataFieldIter dIter(data_DSTC0472);

   DString str;
   //setObjectAsNew(Model->isNewObject());

   //DString dstrPayType;
   //Model->getField(ifds::PayType, dstrPayType, idDataGroup, false);
   //setField(ifds::PayType, dstrPayType, idDataGroup, false);
   
   for( ;dIter; ++dIter )
   {
      const BFFieldId& idField = dIter().getId();
      if(idField != ifds::RegTransferMstrUUID &&
         idField != ifds::OutstandingDays)
      {
         Model->getField( idField, str, idDataGroup, false );
         setFieldNoValidate(idField, str, idDataGroup, false, true, false, false );
      }
   };

   setFieldSubstituteValues( ifds::AmountTypeAlloc, idDataGroup, ifds::AmountType1);

   // to do, need view to send back pre bus day
   getWorkSession().getDateInHostFormat(str, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);
   setField(ifds::InitiationDate, str, idDataGroup, false);

   getWorkSession().getDateInHostFormat(str, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setField(ifds::ClosedDate, str, idDataGroup, false);

   setField(ifds::RegTransferStatus, I_("1"), idDataGroup, false);

   //clear 
   clearUpdatedFlags( idDataGroup );
   setAllFieldsValid( idDataGroup );

   RegPlanTransferAllocList* pRegPlanTransferAllocList;
   RegPlanTransferAllocList* pModelRegPlanTransferAllocList;

   Model->getRegPlanTransferAllocList(idDataGroup, pModelRegPlanTransferAllocList);

   if( pModelRegPlanTransferAllocList )
   {
      getRegPlanTransferAllocList(idDataGroup, pRegPlanTransferAllocList);
      pRegPlanTransferAllocList->ModelOffer(pModelRegPlanTransferAllocList, idDataGroup);
   }

}

