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
// ^FILE   : FeeModelList.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : FeeModelList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0305_req.hpp>
#include <ifastdataimpl\dse_dstc0305_vw.hpp>
#include <ifastdataimpl\dse_dstc0305_vwrepeat_record.hpp>

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"

#include "feemodel.hpp"
#include "feemodellist.hpp"
#include "feemodelcopytogroup.hpp"
#include "feemodelcopytogrouplist.hpp"

#include <bfcbo\bfconstobjiter.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_MODEL;
}

namespace  
{
   const I_CHAR * const CLASSNAME      = I_( "FeeModelList" );  
   const I_CHAR * const IDI_CODE       = I_("CODE");  
   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
   const I_CHAR * const FEE_MODEL_TYPE_ADVISOR_FEE = I_("DF");
}

namespace CND
{  // Conditions used
   extern const long ERR_FEE_MODEL_ALREADY_IN_USE;
   extern const long ERR_FEE_MODEL_CODE_IN_USE; //can not delete
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AutoGenFeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId FeeModelSrc;
   extern CLASS_IMPORT const BFTextFieldId GroupDest;
   extern CLASS_IMPORT const BFTextFieldId AcctGrpType;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//*********************************************************************************
FeeModelList::FeeModelList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_intNewKey( 1 )
, m_intKey( 512 )
, m_bRetrieveAll(false)
, m_bAllFeeModels(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();   
}

//*********************************************************************************
FeeModelList::~FeeModelList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY FeeModelList::init( const BFDataGroupId& idDataGroup,
	                          const DString& dstrTrack,
                             const DString& dstrPageName, 
                             const DString& dstrHoldingCompCode,
                             const DString& dstrHoldingCompName,
                             const DString& dstrFeeModelCode,
                             const DString& dstrFeeModelDesc,
                             const DString& dstrSearchAll,
                             const DString& dstrAsofDate,
                             bool  bRetrieveAll)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   m_bRetrieveAll  = bRetrieveAll;
   // receive data from back end
   DString mgmtCoIdOut;
   requestData305 = new BFData(ifds::DSTC0305_REQ);  

   requestData305->setElementValue( ifds::HoldingCompCode,  dstrHoldingCompCode);
   requestData305->setElementValue( ifds::HoldingCompName,  dstrHoldingCompName);
   requestData305->setElementValue( ifds::FeeModelCode,     dstrFeeModelCode);
   requestData305->setElementValue( ifds::FeeModelDesc,     dstrFeeModelDesc);
   requestData305->setElementValue( ifds::SearchAll,        dstrSearchAll);
   requestData305->setElementValue( ifds::AsofDate,         dstrAsofDate);

   requestData305->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData305->setElementValue( ifds::Track, dstrTrack );
   requestData305->setElementValue( ifds::Activity, dstrPageName );
   requestData305->setElementValue( ifds::NextKey,     NULL_STRING );

   BFData* responseData = new BFData(ifds::DSTC0305_VW);
   ReceiveData(DSTC_REQUEST::FEE_MODEL, *requestData305, *responseData, DSTCRequestor( getSecurity(), 
                           m_bRetrieveAll, false));

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeModelList::init (const DString &dstrFeeModelCode, 
                             const BFDataGroupId& idDataGroup, 
                             const DString& dstrTrack,
                             const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   // receive data from back end
   DString mgmtCoIdOut;
   requestData305 = new BFData(ifds::DSTC0305_REQ);  

   requestData305->setElementValue( ifds::SearchAll, I_("Y"));
   requestData305->setElementValue( ifds::AsofDate, I_("12319999"));

   requestData305->setElementValue( ifds::FeeModelCode, dstrFeeModelCode );
   requestData305->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData305->setElementValue( ifds::Track, dstrTrack );
   requestData305->setElementValue( ifds::Activity, dstrPageName );
   requestData305->setElementValue( ifds::NextKey,     NULL_STRING );

   BFData* responseData = new BFData(ifds::DSTC0305_VW);
   ReceiveData(DSTC_REQUEST::FEE_MODEL, *requestData305, *responseData, DSTCRequestor( getSecurity(),true,false ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY FeeModelList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new FeeModel( *this );
   ((FeeModel* )pObjOut )->Init(data);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeModelList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   FeeModel* pFeeModel = new FeeModel( *this );
   pFeeModel->InitNew( idDataGroup  );
   pBase = pFeeModel;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FeeModelList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      BFData* responseData = new BFData(ifds::DSTC0305_VW);
      ReceiveData(DSTC_REQUEST::FEE_MODEL, *requestData305, *responseData, DSTCRequestor( getSecurity(), 
         m_bRetrieveAll,false ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FeeModelList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   //BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY FeeModelList::getFeeModel ( const DString &feeModelCode, 
                                     FeeModel *&pFeeModel, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFeeModel"));

   pFeeModel = NULL;
   BFObjIter iter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   DString lFeeModelCode = feeModelCode;
   lFeeModelCode.upperCase();
   
   if(!lFeeModelCode.stripAll().empty())
   {
      while (!iter.end())
      {
         DString feeModelCode_;

         iter.getObject()->getField (ifds::FeeModelCode, feeModelCode_, idDataGroup, false);
         if (feeModelCode_.upperCase() == lFeeModelCode) 
         {
            pFeeModel = dynamic_cast <FeeModel*> (iter.getObject());
            break;
         }
         ++iter;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FeeModelList::initForCloneToGroupModel() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initForCloneToGroupModel" ) );

   setObjectNew();

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FeeModelList::validateOverlapping( BFCBO *pCBO, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );   

   DString dstrFeeModelCode,
      dstrFeeModelType,
      dstrAutoGenFeeModelCode;

   FeeModel* pChkObj = dynamic_cast<FeeModel*> ( pCBO );

   getWorkSession ().getOption (ifds::AutoGenFeeModelCode, dstrAutoGenFeeModelCode, BF::HOST, false);
   dstrAutoGenFeeModelCode.strip().upperCase();

   if(pChkObj)
   {
      pChkObj->getField(ifds::FeeModelCode, dstrFeeModelCode, idDataGroup,false );
      pChkObj->getField(ifds::FeeModelType, dstrFeeModelType, idDataGroup,false );
      dstrFeeModelCode.strip().upperCase();
      dstrFeeModelType.strip().upperCase();

      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
      while( !iter.end() )
      {
         DString dstrFeeModelCode1,
            dstrFeeModelType1;

         iter.getObject()->getField( ifds::FeeModelCode,dstrFeeModelCode1,idDataGroup,false );
         iter.getObject()->getField( ifds::FeeModelType,dstrFeeModelType1,idDataGroup,false );
         dstrFeeModelCode1.strip().upperCase();
         dstrFeeModelType1.strip().upperCase();

         if ( pChkObj != iter.getObject()) 
         {
            bool bSameFeeCode = dstrFeeModelCode == dstrFeeModelCode1;
            bool bSameFeeType = dstrFeeModelType == dstrFeeModelType1;
            bool bRaiseCondition = false;

            if (dstrAutoGenFeeModelCode != I_("Y"))
            {
               if( bSameFeeCode )
               {
                  if (dstrFeeModelType != FEE_MODEL_TYPE_ADVISOR_FEE)
                  {
                     bRaiseCondition = true;
                  }
               }
            }
            else
            {
               if (!pChkObj->isNew() && bSameFeeCode)
               {
                  if (dstrFeeModelType != FEE_MODEL_TYPE_ADVISOR_FEE)
                  {
                     bRaiseCondition = true;
                  }
               }
            }

            if (bRaiseCondition)
            {
               ADDCONDITIONFROMFILE(CND::ERR_FEE_MODEL_ALREADY_IN_USE);
            }
         }
         ++iter;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool FeeModelList::canDeleteObject( const DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canDeleteObject" ) );   

   DString dstrCodeInUse = NO;
   BFAbstractCBO* pObj = getObject(strKey, idDataGroup);
   assert( pObj );

   pObj->getField(ifds::CodeIsInUse,dstrCodeInUse,idDataGroup,false);
   if( pObj->isNew() || dstrCodeInUse != YES )
   {
      return true;
   }

   ADDCONDITIONFROMFILE( CND::ERR_FEE_MODEL_CODE_IN_USE );

   return false;
}

//******************************************************************************
void FeeModelList::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   strKey = asString(m_intKey);

   m_intKey++;
}

//******************************************************************************
void FeeModelList::getStrKeyForNewItem(DString & strKey)
{
   strKey = asString(m_intNewKey);
   m_intNewKey++;
}

//******************************************************************************
int FeeModelList::isValidFeeModelCode( const BFDataGroupId& idDataGroup, const DString& dstrFeeModelCode, const DString& dstrDate)
{
   DString dstrEffectiveDate, dstrCode, inputCode = dstrFeeModelCode;
   bool found = false;

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end() )
   {
      FeeModel * pFeeModel = dynamic_cast< FeeModel*> (iter.getObject() );
      if( pFeeModel != NULL )
      {
         pFeeModel->getField( ifds::FeeModelCode, dstrCode, BF::HOST );
         if(dstrCode.strip().upperCase() == inputCode.strip().upperCase() )
         {
            found = true;
            pFeeModel->getField( ifds::EffectiveDate, dstrEffectiveDate, BF::HOST );
            if( DSTCommonFunctions::CompareDates( dstrDate, dstrEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER )
               return 2;
         }
      }
      ++iter;
   }

   if( !found ) return 1;
   

   //check exist, 1 for not exist
   //check effectivedate, 2 for not effective

   return 0; //0 for others
}

//******************************************************************************
void FeeModelList::getDescByFeeModelCode( const BFDataGroupId& idDataGroup, const DString& dstrFeeModelCode, DString& dstrDesc)
{
   dstrDesc = NULL_STRING;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   DString dstrCode = NULL_STRING, inputcode = dstrFeeModelCode;

   if(!inputcode.stripAll().empty())
   {
      while( !iter.end() )
      {
         FeeModel * pFeeModel = dynamic_cast< FeeModel*> (iter.getObject() );
         if( pFeeModel != NULL )
         {
            pFeeModel->getField( ifds::FeeModelCode, dstrCode, BF::HOST );
            if(dstrCode.strip().upperCase() == inputcode.strip().upperCase() )
            {
               pFeeModel->getField( ifds::FeeModelDesc, dstrDesc, BF::HOST );
               break;
            }
         }
         ++iter;
      }
   }
   return;
}

//******************************************************************************
void FeeModelList::setFromHoldingCompany(const DString& dstrHoldingCompCode, const BFDataGroupId& idDataGroup )
{
   m_dstrFromHoldingComp = dstrHoldingCompCode;

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

   while( !iter.end() )
   {
      FeeModel * pFeeModel = dynamic_cast< FeeModel*> (iter.getObject() );
      if( pFeeModel != NULL )
      {
         pFeeModel->setFromHoldingCompany(dstrHoldingCompCode, idDataGroup);
      }
      ++iter;
   }

};

//******************************************************************************
SEVERITY FeeModelList::copyFeeModelToNewGroup(FeeModelCopyToGroupList* pCopyable,
                                              FeeModelList* pSrcModelList,
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "copyFeeModelToNewGroup" ) );

   BFObjIter iterCopyable( *pCopyable, idDataGroup);

   iterCopyable.begin();

   while(!iterCopyable.end())
   {
      DString srcFeeModel,dstGroupModel;

      iterCopyable.getObject()->getField(ifds::FeeModelSrc,srcFeeModel,idDataGroup,false);
      iterCopyable.getObject()->getField(ifds::GroupDest,dstGroupModel,idDataGroup,false);

      srcFeeModel.strip().upperCase();
      dstGroupModel.strip().upperCase();

      BFObjIter iterFeeModel( *pSrcModelList, idDataGroup);
      iterFeeModel.begin();

      while(!iterFeeModel.end())
      {
         DString feeModelRecId, feeModelCode, feeModelDesc;
         iterFeeModel.getObject()->getField(ifds::FeeModelRecid, feeModelRecId, idDataGroup,false);
         iterFeeModel.getObject()->getField(ifds::FeeModelCode, feeModelCode, idDataGroup,false);
         iterFeeModel.getObject()->getField(ifds::FeeModelDesc, feeModelDesc, idDataGroup,false);

         if (feeModelRecId.strip() == srcFeeModel.strip() && !dstGroupModel.empty())
         {
            BFData* pClonedFeeMode = new BFData(ifds::DSTC0305_VWRepeat_Record);
            SEVERITY sevLevel = 
               dynamic_cast<BFCBO*>(iterFeeModel.getObject())->getData(*pClonedFeeMode,idDataGroup);

            if (sevLevel <= WARNING) {
               pClonedFeeMode->setElementValue (ifds::FeeModelRecid, NULL_STRING);
               pClonedFeeMode->setElementValue (ifds::ProcessDate, NULL_STRING);
               pClonedFeeMode->setElementValue (ifds::Username, NULL_STRING);
               pClonedFeeMode->setElementValue (ifds::ModDate, NULL_STRING);
               pClonedFeeMode->setElementValue (ifds::ModUser, NULL_STRING);
               pClonedFeeMode->setElementValue (ifds::FeeModelCode, feeModelCode);
               pClonedFeeMode->setElementValue (ifds::FeeModelDesc, feeModelDesc);

               FeeModel *pFeeModel = nullptr;

               BFObjectKey objKey (dstGroupModel, idDataGroup);
               pFeeModel = dynamic_cast <FeeModel*> (getNewListItem (objKey));

               if(pFeeModel) {
                  pFeeModel->InitNew (*pClonedFeeMode, idDataGroup);

                  pFeeModel->setField(ifds::AcctGrpType, dstGroupModel,idDataGroup,false);
                  pFeeModel->setFieldUpdated(ifds::AcctGrpType, idDataGroup, true);
               }
            }
            else {
               delete pClonedFeeMode;
               pClonedFeeMode = nullptr;
            }
         }

         ++iterFeeModel;
      }

      ++iterCopyable;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeModelList.cpp-arc  $
// 
//    Rev 1.13   Jan 11 2011 10:37:34   jankovii
// IN 2350361 - iFast performance issue
// 
//    Rev 1.12   Jul 13 2005 17:38:18   popescu
// Incident 352435 - improved performance on the fund sponsor fee model screen - get rid of the wacky keys
// 
//    Rev 1.11   Nov 14 2004 14:40:06   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Sep 21 2004 16:58:16   FENGYONG
// case insensitive
// 
//    Rev 1.9   Sep 20 2004 16:24:48   YINGBAOL
// PET1117:FN5 fieldname does not match with view, canDelete function does not work.....
// 
//    Rev 1.8   Sep 20 2004 15:34:42   FENGYONG
// change host to idGroup
// 
//    Rev 1.7   Sep 20 2004 15:16:48   YINGBAOL
// PET1117 FN5 retrieve all records from back end
// 
//    Rev 1.6   Sep 15 2004 15:44:44   FENGYONG
// duplicate not case sensitive
// 
//    Rev 1.5   Sep 15 2004 12:21:04   FENGYONG
// ReceiveAll
// 
//    Rev 1.4   Sep 09 2004 10:58:48   FENGYONG
// small fix for PET 1117
// 
//    Rev 1.3   Sep 07 2004 11:01:30   FENGYONG
// uncomment code after view is ready - PET1117 FN5
// 
//    Rev 1.2   Sep 02 2004 12:30:40   FENGYONG
// Add Conditions for PET1117 FN5
// 
//    Rev 1.1   Aug 10 2004 11:24:02   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.0   Aug 09 2004 10:06:16   FENGYONG
// Initial Revision
// 
// 
*/
