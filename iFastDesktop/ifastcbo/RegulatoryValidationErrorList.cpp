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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RegulatoryValidationErrorList.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Sep 2015
//
// ^CLASS    : RegulatoryValidationErrorList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RegulatoryValidationErrorList.hpp"
#include <ifastdataimpl\dse_dstc0469_req.hpp>
#include <ifastdataimpl\dse_dstc0469_vw.hpp>
#include <ifastdataimpl\dse_dstc0469_vwrepeat_record.hpp>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_warn_includes.h>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REGULATORY_VALIDATIONS;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RegulatoryValidationErrorList" );
}

namespace CND
{ 
   CIFast_IFast_ifastcbo_err_acct_not_SIF   ERR_ACCOUNT_NOT_SIF_ELIGABLE;
   CIFast_IFast_ifastcbo_warn_acct_not_SIF  WARN_ACCOUNT_NOT_SIF_ELIGABLE;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_NOT_SIF_ELIGABLE;   //= 1706
   extern CLASS_IMPORT I_CHAR * const SUPRESSION_CODE_EMPTY;      //= 1703;
}

namespace REGULATION
{
  extern CLASS_EXPORT const I_CHAR * const SIF = I_("SIF");
}

typedef struct 
{
   public:  const I_CHAR * dstrErrNum; 
            const I_CHAR * dstrRegualarion;
            const CConditionObject* errConditionObj; 
            const CConditionObject* warnConditionObj; 

}REGULATORY_ERROR;

const REGULATORY_ERROR classRegulatoryErrorList[] = 
{
  //PASS in Null if condition object is not avliable..Eg :if only error pass warning as null.

  //{ REJERROR CODE                            , REGULATION                   ,  &errConditionObj                            ,  &warnConditionObj                         }

    { IFASTERR::ACCOUNT_NOT_SIF_ELIGABLE        , REGULATION::SIF              ,  &CND::ERR_ACCOUNT_NOT_SIF_ELIGABLE          ,  &CND::WARN_ACCOUNT_NOT_SIF_ELIGABLE      },
};

static const int iRegulatoryErrorFields= sizeof( classRegulatoryErrorList ) / sizeof( REGULATORY_ERROR );

//******************************************************************************
RegulatoryValidationErrorList::RegulatoryValidationErrorList(BFAbstractCBO &parent)
: MFCanBFCbo( parent ),
m_requestData(ifds::DSTC0469_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   setVersionable( false );
}

//******************************************************************************
RegulatoryValidationErrorList::~RegulatoryValidationErrorList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY RegulatoryValidationErrorList::init ( const DString& dstrAccountNum,  
                                               const DString& dstrFund,        
                                               const DString& dstrDate,         
                                               const DString& dstrTransType,  
                                               const DString& dstrRegulation,  /*=     NULL_STRING */
                                               const DString& dstrTrack,       /*=I_("N")*/
                                               const DString& dstrPageName     /*=NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData *receivedData = new BFData (ifds::DSTC0469_VW);
   DString mgmtCoIdOut;
   
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );

   m_requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   m_requestData.setElementValue( ifds::Fund, dstrFund );
   m_requestData.setElementValue( ifds::Date, dstrDate );
   m_requestData.setElementValue( ifds::RegulatoryStandard, dstrRegulation );
   m_requestData.setElementValue( ifds::TransType, dstrTransType );

   ReceiveData ( DSTC_REQUEST::REGULATORY_VALIDATIONS, 
                 m_requestData, 
                 *receivedData, 
                 DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RegulatoryValidationErrorList::getStrKey (DString &strKey, const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      strKey = data->getElementValue (ifds::ErrNum);
      strKey.strip();
   }
   else
   {
      BFCBO::getStrKey (strKey, NULL);
   }

}

//******************************************************************************
SEVERITY RegulatoryValidationErrorList::doRegulatoryValidations( const DString& dstrAccountNum,                                                                  
                                                                 const DString& dstrFund,                                                                 
                                                                 const DString& dstrDate, 
                                                                 const BFDataGroupId& idDataGroup,                                                                     
                                                                 const DString& dstrTransType,   
                                                                 const DString& dstrRegulation   /*=     NULL_STRING */
                                                                )
{
  
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doRegulatoryValidations" ) );

  init ( dstrAccountNum, dstrFund, dstrDate, dstrTransType, dstrRegulation ); 

  if( WARNING >= displayRegulatoryValidationErrors(idDataGroup, I_("E"), dstrRegulation)) //display all validation errors first
      displayRegulatoryValidationErrors(idDataGroup, I_("W"), dstrRegulation );    //if no errors display warning...

  return GETCURRENTHIGHESTSEVERITY();
  
}

//******************************************************************************
SEVERITY RegulatoryValidationErrorList::displayRegulatoryValidationErrors ( const BFDataGroupId& idDataGroup, const DString& dstrEWI, 
                                                                            const DString& dstrRegulation  /*=     NULL_STRING */ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "displayRegulatoryValidationErrors" ) );

   BFObjIter iter (*this, BF::HOST);
   int count = 0; 
   iter.begin();
   bool bDisplayAllRegulationRelatedError = dstrRegulation.empty() ? true : false;
   DString dstrCurrEWI;

   if(bDisplayAllRegulationRelatedError) //display all errors retured by the validation view
   {
      for( int i = 0; i< iRegulatoryErrorFields; i++ )
      {
         if (iter.positionByKey (classRegulatoryErrorList[i].dstrErrNum))
         {
             iter.getObject()->getField (ifds::EWI, dstrCurrEWI, idDataGroup); 
             if(dstrEWI == dstrCurrEWI)
               {
                  CConditionObject *ptrConditionObject = NULL;
                  ptrConditionObject = (dstrEWI == I_("E")) ? const_cast <CConditionObject*> (classRegulatoryErrorList[i].errConditionObj)
                                                            : const_cast <CConditionObject*> (classRegulatoryErrorList[i].warnConditionObj) ;
                  if(ptrConditionObject)
                     ADDCONDITIONFROMOBJECT(*ptrConditionObject);
               }
         }//positionByKey
      }//for     
   }//if
   else
   {
      for( int i = 0; i< iRegulatoryErrorFields; i++ )
      {
         if(dstrRegulation == classRegulatoryErrorList[i].dstrRegualarion)
          {
             if (iter.positionByKey (classRegulatoryErrorList[i].dstrErrNum))
             {
                 iter.getObject()->getField (ifds::EWI, dstrCurrEWI, idDataGroup); 
                 if(dstrEWI == dstrCurrEWI)
                  {
                        CConditionObject *ptrConditionObject = NULL;
                        ptrConditionObject = (dstrEWI == I_("E")) ? const_cast <CConditionObject*> (classRegulatoryErrorList[i].errConditionObj)
                                                                  : const_cast <CConditionObject*> (classRegulatoryErrorList[i].warnConditionObj) ;
                        if(ptrConditionObject)
                            ADDCONDITIONFROMOBJECT(*ptrConditionObject);
                  }   
              }//positionByKey
         }//dstrRegulation
      }//for
   }//else
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RegulatoryValidationErrorList.cpp-arc  $
//    Rev 1.0  Sep 14 2015 
// Initial revision.
*/


