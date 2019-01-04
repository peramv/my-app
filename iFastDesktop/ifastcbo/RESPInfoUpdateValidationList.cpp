//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : RESPInfoUpdateValidationList.cpp
// ^AUTHOR : 
// ^DATE   : Oct, 2010
//
// ^CLASS    : RESPInfoUpdateValidationList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0415_req.hpp>
#include <ifastdataimpl\dse_dstc0415_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0415_vw.hpp>
#include <ifastdataimpl\dse_dstc0415_vwrepeat_record.hpp>

#include "RESPInfoUpdateValidationList.hpp"
#include "RESPInfoUpdateValidation.hpp"
#include "AccountEntityXref.hpp"
#include "AccountEntityXrefObject.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESP_INFO_UPDATE_VALIDATION_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "RESPInfoUpdateValidationList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId DofBirth;
}

namespace CND
{
}

//******************************************************************************
RESPInfoUpdateValidationList::RESPInfoUpdateValidationList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList( );
}

//******************************************************************************
RESPInfoUpdateValidationList::~RESPInfoUpdateValidationList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************
SEVERITY RESPInfoUpdateValidationList::initNew(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew") );


   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY RESPInfoUpdateValidationList::init(const DString& strAccountNum,
                                            const DString& strTransId,
                                            const DString& strNewTaxJuris,
                                            const DString& strNewSibling,
                                            const DString& strValidateType,
                                            const DString& strBenefIdList,
                                            const BFDataGroupId& idDataGroup,
                                            const DString& strTrack,
                                            const DString& strPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;
   BFData requestData (ifds::DSTC0415_REQ);

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, strTrack);
   requestData.setElementValue (ifds::Activity, strPageName);
   requestData.setElementValue (ifds::AccountNum, strAccountNum);
   requestData.setElementValue (ifds::TransId, strTransId);
   requestData.setElementValue (ifds::NewTaxJuris, strNewTaxJuris);
   requestData.setElementValue (ifds::NewSibling, strNewSibling);
   requestData.setElementValue (ifds::ValidateType, strValidateType);
 
   // separate Benef Id List
   if(strBenefIdList == NULL_STRING) 
      requestData.setElementValue (ifds::RepeatCount, I_("0"));   // default

   else
   {
      // benef id pass from the trade screen.
      // create repeat request record
      BFData repeat(ifds::DSTC0415_REQRepeat_Record);
      DString strBenefId, tmpBenefIdList;
      tmpBenefIdList = strBenefIdList;
      DString::size_type pos = 0;
      do
      {
         EXTRACT_VALUE(tmpBenefIdList, strBenefId)         
         repeat.setElementValue(ifds::RESPBenefId, strBenefId);
         // To avoid the benef id = 0 in case of financial.
         strBenefId.stripLeading('0');
         if( !strBenefId.empty() )
         {
            AccountEntityXref *pAccountEntityXref (NULL);

            // get Entity
            if ( getWorkSession().getAccountEntityXref( idDataGroup, pAccountEntityXref )  <= WARNING)
            {
               BFObjIter iterAccountEntityXrefOut (*pAccountEntityXref, 
                                                   idDataGroup, 
                                                   true, 
                                                   BFObjIter::ITERTYPE::NON_DELETED);

               DString searchKey;

               AccountEntityXref::buildPartialKeyForEntityId (searchKey, strBenefId);

               iterAccountEntityXrefOut.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey);

               if (!iterAccountEntityXrefOut.end())
               {
                  AccountEntityXrefObject *pObj =
                        dynamic_cast<AccountEntityXrefObject*>(iterAccountEntityXrefOut.getObject());

                  if ( pObj )
                  {
                     DString dstrNewDofBirth;
                     pObj->getField(ifds::DofBirth, dstrNewDofBirth, idDataGroup, false);
                     repeat.setElementValue(ifds::NewDofBirth, dstrNewDofBirth);            
                  }
               }
            }
         }
         
         requestData.addRepeat(repeat);
         // cut string from list
         CHOP_STRING (tmpBenefIdList)
      }
      while (tmpBenefIdList != NULL_STRING);   

      DString dstRepeats = DString::asString( requestData.getRepeatCount() );
      requestData.setElementValue(ifds::RepeatCount, dstRepeats);         
   }

   ReceiveData(DSTC_REQUEST::RESP_INFO_UPDATE_VALIDATION_INQUIRY, requestData, 
               ifds::DSTC0415_VW, DSTCRequestor(getSecurity(), false, false));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPInfoUpdateValidationList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new RESPInfoUpdateValidation( *this );
   ((RESPInfoUpdateValidation*) pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPInfoUpdateValidationList::doCreateNewObject (BFCBO *& pBase, 
                                                          DString &strKey, 
                                                          const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RESPInfoUpdateValidationList::displayAllRESPError(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "displayAllRESPError" ) );

   BFObjIter iter (*this, idDataGroup, false);
   iter.begin();

   RESPInfoUpdateValidation *pRESPInfoUpdateValidation = NULL;

   while(!iter.end())
   {
      pRESPInfoUpdateValidation = dynamic_cast< RESPInfoUpdateValidation* >(iter.getObject());   
      pRESPInfoUpdateValidation->displayRESPError(idDataGroup);
      ++iter;
   }
   //delete pRESPInfoUpdateValidation;
   pRESPInfoUpdateValidation = NULL;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPInfoUpdateValidationList.cpp-arc  $
// 
//    Rev 1.2   Feb 04 2011 05:24:30   kitticha
// IN2409562 - Incorrect warning message when bene age > 18.
// 
//    Rev 1.1   Nov 23 2010 09:04:00   kitticha
// PET165541_FN03_QESI_Phase3_Non_Finance - revise.
// 
//    Rev 1.0   Oct 29 2010 03:57:54   kitticha
// Initial revision.
// 
//
