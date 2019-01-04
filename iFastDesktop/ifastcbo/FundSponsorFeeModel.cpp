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
//    Copyright 2002 by International Financial
//
//
//******************************************************************************
//
// ^FILE   : FundSponsorFeeModel.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : FundSponsorFeeModel
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0307_vw.hpp>
#include <ifastdataimpl\dse_dstc0307_req.hpp>
#include <ifastdataimpl\dse_dstc0305_vw.hpp>
#include <ifastdataimpl\dse_dstc0305_req.hpp>

#include "fundsponsorfeemodel.hpp"
#include "fundsponsorfeemodellist.hpp"
#include "fundsponsorslist.hpp"
#include "fundsponsorfeelist.hpp"
#include "fundsponsorfee.hpp"
#include "feemodellist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "FeeModelList.hpp"


namespace  
{
   const I_CHAR * const CLASSNAME      = I_( "FundSponsorFeeModel" );
   const I_CHAR * const DISCOUNTMODEL  = I_("1");
   const I_CHAR * const BUYATNAV       = I_("2");
   const I_CHAR * const BONIMAX        = I_("3");
   const I_CHAR * const IDI_CODE       = I_("CODE");
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFTextFieldId SystematicCrossField1;
   extern CLASS_IMPORT const BFTextFieldId FndSpFeeModelID;
   extern CLASS_IMPORT const BFTextFieldId FundGroupDesc;
}

namespace CND
{  // Conditions used
   extern const long ERR_EFF_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_FEEMODEL_CODE_NOT_SETUP;
   extern const long ERR_FEEMODEL_CODE_NOT_ACTIVE;
   extern const long ERR_CONDITION_RATE_NOT_SETUP;
}

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags    

   { ifds::Currency,                BFCBO::NONE,                  0 }, 
   { ifds::FeeModelCode,		      BFCBO::REQUIRED,	            0 }, 
   { ifds::FeeModelDesc,		      BFCBO::CALCULATED_FIELD,	   0 },
   { ifds::EffectiveDate,		      BFCBO::NONE,	               0 },
   { ifds::StopDate,		            BFCBO::NONE,	               0 },
   { ifds::FundGroup,               BFCBO::REQUIRED,	            0 },
   { ifds::FundGroupDesc,           BFCBO::CALCULATED_FIELD,	   0 },
   { ifds::FeeModelOption,          BFCBO::REQUIRED,	            0 },   
   { ifds::FndSpFeeModelID,         BFCBO::NONE,	               0 },   
   { ifds::SystematicCrossField1,   BFCBO::IMMEDIATE_VALIDATION,  0 }, 
   { ifds::CompoundDate,            BFCBO::NONE,	               0 },

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

FundSponsorFeeModel::FundSponsorFeeModel (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   
   addCrossEdit(ifds::CompoundDate, ifds::EffectiveDate);
   addCrossEdit(ifds::CompoundDate, ifds::StopDate);
//to check the duplicates
   addCrossEdit (ifds::SystematicCrossField1, ifds::FeeModelCode);
   addCrossEdit (ifds::SystematicCrossField1, ifds::FundGroup);
}
//******************************************************************************************
FundSponsorFeeModel::~FundSponsorFeeModel()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//************************************************************************************
SEVERITY FundSponsorFeeModel::initNew( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   setFieldReadOnly (ifds::FeeModelCode, idDataGroup, false);
   setFieldReadOnly (ifds::FundGroup, idDataGroup, false);   
  	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY FundSponsorFeeModel::init (const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init(BFData&)"));  
   
   attachDataObject (const_cast<BFData&>(data), false);  

   setFieldReadOnly (ifds::FeeModelCode,BF::HOST,true);
   setFieldReadOnly (ifds::FundGroup,BF::HOST,true);
   setSubstitutionList (BF::HOST);
      
   DString dstrFeeModelCode, 
      dstrFeeModelDesc, 
      dstrFundGroup, 
      dstrFundGroupDesc;
      
   dstrFeeModelCode = data.getElementValue( ifds::FeeModelCode );
   dstrFundGroup = data.getElementValue( ifds::FundGroup );
   dstrFundGroup.stripAll().upperCase();

   FeeModelList* pFeeModelList;
   if (getFeeModelInfo (pFeeModelList, dstrFeeModelCode, BF::HOST) <= WARNING &&
        pFeeModelList)
   {
      pFeeModelList->getDescByFeeModelCode (BF::HOST, dstrFeeModelCode, dstrFeeModelDesc);
      setFieldNoValidate (ifds::FeeModelDesc, dstrFeeModelDesc, BF::HOST, false);
	}	
	if (!dstrFundGroup.empty())
	{
		FundSponsorsList* pFundSponsorsList = NULL;
		if ( getMgmtCo ().getFundSponsorsList (pFundSponsorsList) <= WARNING &&
			  pFundSponsorsList)
		{
			BFAbstractCBO *pFundSponsor = NULL;
			if ( pFundSponsorsList->getFundSponsor (dstrFundGroup, pFundSponsor) <= WARNING &&
				  pFundSponsor)
			{				
				pFundSponsor->getField  (ifds::FundGroupDesc, dstrFundGroupDesc, BF::HOST, false);
				setFieldNoValidate (ifds::FundGroupDesc, dstrFundGroupDesc, BF::HOST, false);	
			}                		
		}
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FundSponsorFeeModel::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString stopDate, dstrCurrBusDate;
   
   setFieldRequired (ifds::FeeModelCode, idDataGroup, true);
   setFieldRequired (ifds::FundGroup, idDataGroup, true);   
   setFieldRequired (ifds::EffectiveDate, idDataGroup, true);   
   setFieldRequired (ifds::StopDate, idDataGroup, true);
   setFieldRequired (ifds::FeeModelOption, idDataGroup, true);

   getWorkSession().getDateInHostFormat (stopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false);
   getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false);
   setSubstitutionList (idDataGroup);
}

//***********************************************************************************
SEVERITY FundSponsorFeeModel::doValidateField ( const BFFieldId &idField,
                                                const DString &strValue,
                                                const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

	if (idField == ifds::CompoundDate)
   {
		validateEffectiveStopDate (idDataGroup);
   }
   if (idField == ifds::SystematicCrossField1)
   {
      FundSponsorFeeModelList *pFundSponsorFeeModelList = 
            dynamic_cast <FundSponsorFeeModelList*> (getParent());
      if (pFundSponsorFeeModelList)
      {
         pFundSponsorFeeModelList->checkDuplicate (this, idDataGroup);
      }
   }
   if (idField == ifds::FeeModelCode)
   {
      validateModelCode (idDataGroup, strValue);
   }
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY FundSponsorFeeModel::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if (idField == ifds::FeeModelCode)
	{
      DString dstrFeeModelCode, 
         dstrFeeModelDesc;
      
      getField (ifds::FeeModelCode, dstrFeeModelCode, idDataGroup, false);

      FeeModelList* pFeeModelList = NULL;

      if (getFeeModelInfo (pFeeModelList, dstrFeeModelCode, idDataGroup) <= WARNING && 
           pFeeModelList)
      {
         pFeeModelList->getDescByFeeModelCode (idDataGroup,dstrFeeModelCode,dstrFeeModelDesc);
         setFieldNoValidate (ifds::FeeModelDesc, dstrFeeModelDesc, idDataGroup, false);	
	   }

      FundSponsorFeeList *pFundSponsorFeeList = NULL;

      if ( getFundSponsorFeeList (pFundSponsorFeeList, idDataGroup) <= WARNING && 
           pFundSponsorFeeList)
      {  
         pFundSponsorFeeList->setFieldForAllRecords (ifds::FeeModelCode, dstrFeeModelCode, idDataGroup);
      }
   } 
   else if (idField == ifds::FeeModelOption)
   {
      DString dstrFeeModelOption;
   
      getField (ifds::FeeModelOption,dstrFeeModelOption,idDataGroup,false);

      FundSponsorFeeList *pFundSponsorFeeList = NULL;
      if ( getFundSponsorFeeList (pFundSponsorFeeList, idDataGroup) <= WARNING  &&
           pFundSponsorFeeList)
      {
         if (dstrFeeModelOption == BUYATNAV || dstrFeeModelOption == BONIMAX)
         {
            pFundSponsorFeeList->setStopDateForAllRecords (idDataGroup);
         }         
         pFundSponsorFeeList->setFieldValidflag (ifds::FeeCode, idDataGroup, false);
/*         else
         {
            DString defaultStopDate;
            getWorkSession().getDateInHostFormat (defaultStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
            pFundSponsorFeeList->setStopDateForAllRecords(ifds::StopDate, defaultStopDate, idDataGroup);
         }
*/
      }
   }
   else if (idField == ifds::FundGroup)
   {
      DString dstrFundGroup, dstrFundGroupDesc;
      getField(ifds::FundGroup,dstrFundGroup,idDataGroup,false);
      
      FundSponsorFeeList *pFundSponsorFeeList = NULL;
      if ( getFundSponsorFeeList(pFundSponsorFeeList, idDataGroup) <= WARNING &&
           pFundSponsorFeeList)
      {         
         pFundSponsorFeeList->setFieldForAllRecords(ifds::FundGroup, dstrFundGroup, idDataGroup);            
      }
      if (!dstrFundGroup.empty())
	   {
         dstrFundGroup.stripAll().upperCase();

         FundSponsorsList* pFundSponsorsList = NULL;
		   if ( getMgmtCo ().getFundSponsorsList (pFundSponsorsList) <= WARNING &&
			     pFundSponsorsList)
		   {
			   BFAbstractCBO *pFundSponsor = NULL;
			   
            if (pFundSponsorsList->getFundSponsor (dstrFundGroup, pFundSponsor) <= WARNING &&
				    pFundSponsor)
			   {				
				   pFundSponsor->getField (ifds::FundGroupDesc, dstrFundGroupDesc, idDataGroup, false);
				   setFieldNoValidate (ifds::FundGroupDesc, dstrFundGroupDesc, idDataGroup, false);	
			   }                		
		   }
	   }
   }
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY FundSponsorFeeModel::validateEffectiveStopDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   DString dstrEffectDate,
      dstrStopDate;

   getField (ifds::EffectiveDate, dstrEffectDate, idDataGroup, false);
   getField (ifds::StopDate, dstrStopDate, idDataGroup, false);

   if (DSTCommonFunctions::CompareDates (dstrStopDate, dstrEffectDate) == DSTCommonFunctions::FIRST_EARLIER)
   {
      ADDCONDITIONFROMFILE (CND::ERR_EFF_DATE_LATE_THAN_STOP_DATE);
   }            
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
void FundSponsorFeeModel::setFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly) 
{
	setFieldReadOnly (ifds::FeeModelCode, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::FundGroup, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::FeeModelDesc, idDataGroup, true);	
}

//*****************************************************************************************
void FundSponsorFeeModel::setSubstitutionList (const BFDataGroupId &idDataGroup)
{
//Call View148 to build FundSponsor List and link to FundSponsorCode
   FundSponsorsList *pFundSponsorsList;
   if (getMgmtCo().getFundSponsorsList (pFundSponsorsList) <= WARNING && pFundSponsorsList)
   {
      DString dstrSubList;
   
      pFundSponsorsList->getFundSponsorCodeSubstList (dstrSubList);
      setFieldAllSubstituteValues (ifds::FundGroup, idDataGroup, dstrSubList);
   }   
}

//*****************************************************************************************
void FundSponsorFeeModel::validateModelCode ( const BFDataGroupId &idDataGroup, 
                                              const DString &dstrModelCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateModelCode" ) );

   FeeModelList * pFeeModelList = NULL;
   if (getFeeModelInfo (pFeeModelList, dstrModelCode, idDataGroup) <= WARNING &&
        pFeeModelList)
   {
      DString dstrEffectiveDate;
      
      getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
      
      int ret = pFeeModelList->isValidFeeModelCode (idDataGroup, dstrModelCode, dstrEffectiveDate);

      if (ret == 1)
      {
         DString dstrTemp;

         addIDITagValue (dstrTemp, I_("FEEMODELCODE"), dstrModelCode);
         ADDCONDITIONFROMFILEIDI (CND::ERR_FEEMODEL_CODE_NOT_SETUP, dstrTemp);
      }
      else if (ret == 2)
      {
         DString dstrTemp;

         addIDITagValue (dstrTemp, I_("FEEMODELCODE"), dstrModelCode);
         addIDITagValue (dstrTemp, I_("DATE"), dstrEffectiveDate);
         ADDCONDITIONFROMFILEIDI (CND::ERR_FEEMODEL_CODE_NOT_ACTIVE, dstrTemp);	
      }
   }
}

//*****************************************************************************************
SEVERITY FundSponsorFeeModel::getFundSponsorFeeList( FundSponsorFeeList *&pFundSponsorFeeList, 
													              const BFDataGroupId& idDataGroup,
													              bool inquireDatabase /*= true */)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundClassHoldingsList" ) );

   DString dstrFeeModelCode, 
      dstrFundGroup;
   
   getField (ifds::FundGroup, dstrFundGroup, idDataGroup, false);
   getField (ifds::FeeModelCode, dstrFeeModelCode, idDataGroup, false);

   pFundSponsorFeeList = dynamic_cast <FundSponsorFeeList*> (BFCBO::getObject (I_("FundSponsorFeeList"), idDataGroup));
   
   BFDataGroupId tDataGroup = idDataGroup;
   
   if (!pFundSponsorFeeList)
   {
      if (isNew())
      {
	      pFundSponsorFeeList = new FundSponsorFeeList (*this);
	      pFundSponsorFeeList->InitNew (tDataGroup);
      }	
      if (inquireDatabase && dstrFeeModelCode != NULL_STRING)
      {
	      pFundSponsorFeeList = new FundSponsorFeeList (*this);
	      pFundSponsorFeeList->init (dstrFeeModelCode, dstrFundGroup, idDataGroup);
	      tDataGroup = BF::HOST;
      }
      if (pFundSponsorFeeList)
      {
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
         {
			   setObject ( pFundSponsorFeeList, 
                        I_("FundSponsorFeeList"), 
				            OBJ_ACTIVITY_NONE, 
                        tDataGroup); 
         }
         else
		   {
			   delete pFundSponsorFeeList;
            pFundSponsorFeeList = NULL;
         }
      }
   }	 
   return GETCURRENTHIGHESTSEVERITY();
}


//*********************************************************************************
SEVERITY FundSponsorFeeModel::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   DString dstrModelOption, 
      dstrFeeCode, 
      dstrDEFF, 
      dstrStopDate, 
      dstrCurrBusDate;
   
   getField(ifds::FeeModelOption,dstrModelOption,idDataGroup,false);
   if (dstrModelOption == DISCOUNTMODEL)
   {
      FundSponsorFeeList * pFundSponsorFeeList = NULL;
      if ( getFundSponsorFeeList (pFundSponsorFeeList, idDataGroup) <= WARNING && 
           pFundSponsorFeeList)
      {
         bool havediscountfee = false;
         BFObjIter iter( *pFundSponsorFeeList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

         while (!iter.end())
         {
            if (!iter.isDummy()) 
            {
               iter.getObject()->getField (ifds::FeeCode, dstrFeeCode, idDataGroup);
               iter.getObject()->getField (ifds::EffectiveDate, dstrDEFF, idDataGroup);
               iter.getObject()->getField (ifds::StopDate, dstrStopDate, idDataGroup);
               getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
               if (dstrFeeCode == I_("110") || dstrFeeCode == I_("111")) 	
               {
	               if (DSTCommonFunctions::IsDateBetween (dstrDEFF, dstrStopDate, dstrCurrBusDate))
	               {
		               havediscountfee = true;
		               break;
	               }
               }
            }
            ++iter;
         }
         if (!havediscountfee) 
         {
            ADDCONDITIONFROMFILE (CND::ERR_CONDITION_RATE_NOT_SETUP);
         }
      }
   }  
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY FundSponsorFeeModel::getFeeModelInfo (FeeModelList *&pFeeModelList, 
											   const DString &dstrFeeModelCode,
											   const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeModelInfo" ) );

	DString strKey = I_("FeeModelList") + dstrFeeModelCode;
	strKey.stripAll();

	pFeeModelList = dynamic_cast <FeeModelList*> (BFCBO::getObject (strKey, idDataGroup));
   
	if (!pFeeModelList)
	{
      
		pFeeModelList = new FeeModelList (*this);
		pFeeModelList->init (dstrFeeModelCode, idDataGroup); 
	  
		if (pFeeModelList)
		{
			if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
			{
				setObject (pFeeModelList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
			}
			else
			{
			   delete pFeeModelList;
				pFeeModelList = NULL;
			}
		}
	}	 
	
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundSponsorFeeModel.cpp-arc  $
// 
//    Rev 1.20   Jan 11 2011 10:40:22   jankovii
// IN 2350361 - iFast performance issue
// 
//    Rev 1.19   Jul 13 2005 17:38:36   popescu
// Incident 352435 - improved performance on the fund sponsor fee model screen - get rid of the wacky keys
// 
//    Rev 1.18   Jan 31 2005 12:22:44   winnie
// Correction for data comparion for condition rate edit check. The original logic issue error if the condition rate has effective date of the current business date which is a default value.
// 
//    Rev 1.17   Dec 16 2004 10:13:58   Fengyong
// PET1117 FN5 - condition rate must be setup for discount fee model.
// 
//    Rev 1.16   Nov 29 2004 16:14:14   Fengyong
// PET1117 FN56 - 3rd_party fund trade processing
// 
//    Rev 1.15   Nov 14 2004 14:43:08   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.14   Nov 02 2004 11:01:40   FENGYONG
// PTS10035274 - Validation between ModelOption and FeeCode
// 
//    Rev 1.13   Oct 21 2004 17:50:02   FENGYONG
// PTS10034976 - Error message of Fee ModelCode not active
// 
//    Rev 1.12   Oct 21 2004 17:23:46   YINGBAOL
// PTS10034903: change logic for stamp current business date to stop date.
// 
//    Rev 1.11   Sep 29 2004 09:34:00   FENGYONG
// PET1117FN5 - change after Ess walk through
// 
//    Rev 1.10   Sep 21 2004 16:59:42   FENGYONG
// case insensitive
// 
//    Rev 1.9   Sep 20 2004 15:36:34   FENGYONG
// Add validate field FeeModelCode
// 
//    Rev 1.8   Sep 15 2004 12:21:26   FENGYONG
// ReceiveAll
// 
//    Rev 1.7   Sep 14 2004 16:42:42   FENGYONG
// Add crossedits
// 
//    Rev 1.6   Sep 10 2004 15:52:02   FENGYONG
// PET1117 FN5 - Client Fee
// 
//    Rev 1.5   Sep 08 2004 17:16:04   FENGYONG
// PET1117 FN5 - Client Fee
// 
//    Rev 1.4   Sep 02 2004 12:31:00   FENGYONG
// Add Conditions for PET1117 FN5
// 
//    Rev 1.3   Aug 31 2004 17:29:58   FENGYONG
// change Field names
// 
//    Rev 1.2   Aug 13 2004 17:09:16   YINGBAOL
// PET1117: change  getFundSponsorFeeList
// 
//    Rev 1.1   Aug 10 2004 11:24:38   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.0   Aug 09 2004 10:06:20   FENGYONG
// Initial Revision
// 
// 
*/
