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
//    Copyright 2002 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : FundSponsorFundSponsorFeeModelList.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : FundSponsorFeeModelList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0307_req.hpp>
#include <ifastdataimpl\dse_dstc0307_vw.hpp>

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"

#include "fundsponsorfeemodel.hpp"
#include "fundsponsorfeemodellist.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUNDSPONSOR_FEE_MODEL;
}


namespace  
{
   const I_CHAR * const CLASSNAME    = I_( "FundSponsorFeeModelList" );  
}

namespace CND
{
   extern const long ERR_DUPLICATE_RECORD;
   extern const long ERR_DELETE_FUNDSPONSOR_FEE_MODEL;
   extern CLASS_IMPORT const long ERR_FNDSPONSOR_FEEMODEL_DOES_NOT_EXIST;
}

//******************************************************************************
void FundSponsorFeeModelList::buildKey ( DString &dstrKey, 
                                         const DString &feeModelCode, 
                                         const DString &fundSponsor)
{
   DString _feeModelCode (feeModelCode),
      _fundSponsor (fundSponsor);

   dstrKey = 
      I_("FeeModelCode=") + _feeModelCode.strip ().upperCase() + 
      I_(";FundSponsor=") + _fundSponsor.strip ().upperCase();
}

//*********************************************************************************
FundSponsorFeeModelList::FundSponsorFeeModelList( BFAbstractCBO &parent )
: MFCanBFCbo (parent),
_pRequestData307 (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
FundSponsorFeeModelList::~FundSponsorFeeModelList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY FundSponsorFeeModelList::init ( const BFDataGroupId &idDataGroup, 
                                         const DString &dstrTrack, 
                                         const DString &dstrPageName,
                                         const DString &feeModelCode, 
                                         const DString &fundSponsorCode,
                                         bool allResults /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
//it is possible due to the way this list is used by the account fund sponsor fee model screen
//that several rquests for data are made, although data has already been retrieved.
//the boolean will guard this.
   bool bDoNotMakeTheViewCallASecondTime = 
      allResults && 
      !feeModelCode.empty () && 
      fundSponsorCode.empty() && 
      !_feeModelCodes.insert (feeModelCode).second; //already exists in the set ?

   if (!bDoNotMakeTheViewCallASecondTime)
   {
      DString mgmtCoIdOut;
   	
      _pRequestData307 = new BFData (ifds::DSTC0307_REQ);  
	   _pRequestData307->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	   _pRequestData307->setElementValue (ifds::Track, dstrTrack);
	   _pRequestData307->setElementValue (ifds::Activity, dstrPageName);
	   _pRequestData307->setElementValue (ifds::NextKey, NULL_STRING);
	   _pRequestData307->setElementValue (ifds::FeeModelCode, feeModelCode);
	   _pRequestData307->setElementValue (ifds::FundGroup, fundSponsorCode);

   // receive data from back end
	   if (ReceiveData ( DSTC_REQUEST::FUNDSPONSOR_FEE_MODEL, 
                        *_pRequestData307, 
                        ifds::DSTC0307_VW, 
                        DSTCRequestor ( getSecurity(), 
                                       //do not always, retrieve all results - Incident# 352435
                                       allResults)) > WARNING)
      {
        //if view error, erase the fee model code
         _feeModelCodes.erase (feeModelCode);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY FundSponsorFeeModelList::initNew (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY FundSponsorFeeModelList::getFundSponsorFeeModel ( const DString &feeModelCode,
                                                           const DString &fundSponsorCode,
                                                           FundSponsorFeeModel *&pFundSponsorFeeModel, 
                              	                          const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getFundSponsorFeeModel" ));
   pFundSponsorFeeModel = NULL;
   BFObjIter iter ( *this, 
                     idDataGroup, 
                     false, 
                     BFObjIter::ITERTYPE::NON_DELETED);
   DString strKey;
   
   buildKey (strKey, feeModelCode, fundSponsorCode);
   if (iter.positionByKey (strKey))
   {
      pFundSponsorFeeModel = dynamic_cast <FundSponsorFeeModel*> (iter.getObject());
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY FundSponsorFeeModelList::getFundSponsorFeeModel ( const DString &feeModelCode,
                                                           FundSponsorFeeModel *&pFundSponsorFeeModel, 
                              	                          const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getFundSponsorFeeModel" ));
   pFundSponsorFeeModel = NULL;
   BFObjIter iter ( *this, 
                     idDataGroup, 
                     false, 
                     BFObjIter::ITERTYPE::NON_DELETED);
	iter.begin();   
    while( !iter.end() )
    {
		DString dstrTemp, dstrFeeModel( feeModelCode );
	    iter.getObject()->getField ( ifds::FeeModelCode, dstrTemp, idDataGroup );
		if( dstrTemp.strip().upperCase() == dstrFeeModel.strip().upperCase() )
		{
			pFundSponsorFeeModel = dynamic_cast <FundSponsorFeeModel*> (iter.getObject());
			break;
		}
	    ++iter;
    }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY FundSponsorFeeModelList::doCreateObject (const BFData &data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new FundSponsorFeeModel ((BFAbstractCBO&)(*this));
   ((FundSponsorFeeModel*)pObjOut)->init (data);
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY FundSponsorFeeModelList::doCreateNewObject ( BFCBO *&pBase, 
                                                      DString &strKey, 
                                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   FundSponsorFeeModel *pFundSponsorFeeModel = new FundSponsorFeeModel ((BFAbstractCBO&)(*this));
   pFundSponsorFeeModel->initNew (idDataGroup);
   pBase = pFundSponsorFeeModel;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundSponsorFeeModelList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));
   
   assert (_pRequestData307);
   if (doMoreRecordsExist())
   {
      ReceiveData ( DSTC_REQUEST::FUNDSPONSOR_FEE_MODEL,
                    *_pRequestData307, 
                    ifds::DSTC0307_VW, 
                    DSTCRequestor (getSecurity(), false));
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY FundSponsorFeeModelList::checkDuplicate ( const FundSponsorFeeModel *pFundSponsorFeeModelToCheck, 
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("checkDuplicate"));
   DString fundGroup, 
      feeModelCode;

//get the values for fund sponsor / fee model code, to check against
   pFundSponsorFeeModelToCheck->getField (ifds::FundGroup, fundGroup, idDataGroup);
   pFundSponsorFeeModelToCheck->getField (ifds::FeeModelCode, feeModelCode, idDataGroup);
   fundGroup.strip ().upperCase();
   feeModelCode.strip ().upperCase();
   
   bool hasDuplicate = false;

//check first whether in the list (in memory) we have a duplicate
//this catches the newly added items, as well 
   BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end())
   {
      FundSponsorFeeModel *pFundSponsorFeeModel =  
            dynamic_cast <FundSponsorFeeModel*>(iter.getObject());

      if (pFundSponsorFeeModel != pFundSponsorFeeModelToCheck)
      {
         DString fundGroup_, 
            feeModelCode_;

         pFundSponsorFeeModel-> getField (ifds::FundGroup, fundGroup_, idDataGroup);
         pFundSponsorFeeModel-> getField (ifds::FeeModelCode, feeModelCode_, idDataGroup);
         fundGroup_.strip ().upperCase();
         feeModelCode_.strip ().upperCase();
         if ( feeModelCode == feeModelCode_ && 
              fundGroup == fundGroup_)
         {
            hasDuplicate = true;
            break;
         }
      }
      ++iter;
   }
//if no duplicates in memory, check the back-end
   if (!hasDuplicate)
   {
      FundSponsorFeeModelList fundSponsorFeeModelList ((BFAbstractCBO&)(*this));

      if ( fundSponsorFeeModelList.init ( idDataGroup, 
												      I_("N"), 
												      NULL_STRING,
												      feeModelCode, 
												      fundGroup) <= WARNING)
      {
	      FundSponsorFeeModel *pFundSponsorFeeModel = NULL;

	      if ( fundSponsorFeeModelList.getFundSponsorFeeModel ( feeModelCode,
																			      fundGroup,
																			      pFundSponsorFeeModel,
																			      idDataGroup) <= WARNING &&
			     pFundSponsorFeeModel)
	      {
            hasDuplicate = true; //database has a similar record
		  }
      }
      else //clear the condition, no duplicates
      {
	         int count = CONDITIONCOUNT();
	         Condition *c = NULL;
	      
            for (int i = 0; i < count; i++)
	         {
		         c = GETCONDITION( i );
		         int condCode = c->getCode();
		         //do not want to promote this condition
		         if (condCode == CND::ERR_FNDSPONSOR_FEEMODEL_DOES_NOT_EXIST) 
		         {
			         CLEARCONDITION (i);			         
			         break;
		         }
	         }
      }
      
      if (hasDuplicate && GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
//if we found a duplicate in database, this might have been already deleted in the memory
//check the memory again for possible deleted duplicates
         BFObjIter iter (*this, idDataGroup);

         while (!iter.end())
         {
            if (iter.getKey().getActivity() == OBJ_ACTIVITY_DELETED)
            {
               FundSponsorFeeModel *pFundSponsorFeeModel =  
                     dynamic_cast <FundSponsorFeeModel*> (iter.getObject());
               DString deletedFundGroup, 
                  deletedFeeModelCode;

               pFundSponsorFeeModel-> getField (ifds::FundGroup, deletedFundGroup, idDataGroup);
               pFundSponsorFeeModel-> getField (ifds::FeeModelCode, deletedFeeModelCode, idDataGroup);
               deletedFundGroup.strip ().upperCase();
               deletedFeeModelCode.strip ().upperCase();
               if ( fundGroup == deletedFundGroup && 
                    feeModelCode == deletedFeeModelCode)
               {
                  hasDuplicate = false;
                  break;
               }
            }
            ++iter;
         }
      }
   }
   if (hasDuplicate)
   {
      ADDCONDITIONFROMFILE (CND::ERR_DUPLICATE_RECORD);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FundSponsorFeeModelList::getStrKey (DString &strKey, const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data) 
   {
      DString feeModelCode = data->getElementValue (ifds::FeeModelCode);
      DString fundSponsorCode = data->getElementValue (ifds::FundGroup);

      buildKey ( strKey, 
                 feeModelCode, 
                 fundSponsorCode);
   }
   else
   {
      BFCBO::getStrKey (strKey, NULL);
   }
}

//************************************************************************************
bool FundSponsorFeeModelList::canDeleteObject ( const DString &strKey, 
                                                const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canDeleteObject" ) );

// logic: if it is new, or if it is just created today, delete is allowed 
   DString strProcessDate,
      strCurBusDate;
   BFAbstractCBO *pObj = getObject(strKey, idDataGroup);
   assert (pObj);
   getWorkSession().getDateInHostFormat (strCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);  
   pObj->getField(ifds::ProcessDate,strProcessDate,idDataGroup,false);  
   if ( pObj->isNew() || 
        DSTCommonFunctions::CompareDates (strCurBusDate,strProcessDate) == DSTCommonFunctions::EQUAL)
   {
      return true;
   }
   ADDCONDITIONFROMFILE (CND::ERR_DELETE_FUNDSPONSOR_FEE_MODEL);
   return false;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundSponsorFeeModelList.cpp-arc  $
// 
//    Rev 1.14   Jul 20 2005 13:36:16   Fengyong
// Incident #352435 - fix duplicate checking problem.
// 
//    Rev 1.13   Jul 19 2005 15:49:30   Fengyong
// Incident 352435 - add new function fix crash problem.
// 
//    Rev 1.12   Jul 18 2005 12:36:42   popescu
// Incident 352435 - fixed the call to buildKey, params were reversed
// 
//    Rev 1.11   Jul 13 2005 17:38:44   popescu
// Incident 352435 - improved performance on the fund sponsor fee model screen - get rid of the wacky keys
// 
//    Rev 1.10   Dec 11 2004 11:47:26   popescu
// PET 1117/56 more fixes, pending trade mods
// 
//    Rev 1.9   Dec 10 2004 20:19:36   winnie
// PET 1117 FN06 : set FeeModelCode and FundSponsor to the request when making view call
// 
//    Rev 1.8   Nov 14 2004 14:43:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.7   Nov 02 2004 11:01:44   FENGYONG
// PTS10035274 - Validation between ModelOption and FeeCode
// 
//    Rev 1.6   Sep 15 2004 15:45:04   FENGYONG
// duplicate not case sensitive
// 
//    Rev 1.5   Sep 15 2004 12:21:28   FENGYONG
// ReceiveAll
// 
//    Rev 1.4   Sep 14 2004 16:43:26   FENGYONG
// fix overlap validation
// 
//    Rev 1.3   Sep 02 2004 12:31:02   FENGYONG
// Add Conditions for PET1117 FN5
// 
//    Rev 1.2   Aug 31 2004 17:30:44   FENGYONG
// change Field names
// 
//    Rev 1.1   Aug 10 2004 11:24:40   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.0   Aug 09 2004 10:06:24   FENGYONG
// Initial Revision
// 
// 
*/
