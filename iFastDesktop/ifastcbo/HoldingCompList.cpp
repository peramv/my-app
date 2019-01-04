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
// ^FILE   : HoldingCompList.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : HoldingCompList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0448_req.hpp>
#include <ifastdataimpl\dse_dstc0448_vw.hpp>

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"

#include "holdingcomp.hpp"
#include "holdingcomplist.hpp"
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest HOLDING_COMPANY;
}

namespace  
{
   const I_CHAR * const CLASSNAME      = I_( "HoldingCompList" );  
   const I_CHAR * const IDI_CODE       = I_("CODE");  
   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );

}

namespace CND
{  // Conditions used
   extern const long ERR_FEE_MODEL_ALREADY_IN_USE;
   extern const long ERR_FEE_MODEL_CODE_IN_USE; //can not delete
   extern CLASS_IMPORT const long ERR_HOLDING_COMPANY_CODE_IS_ALREADY_DELETED;
}

namespace ifds
{
//   extern CLASS_IMPORT const BFTextFieldId AutoGenHoldingCompCode;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//*********************************************************************************
HoldingCompList::HoldingCompList( BFAbstractCBO &parent, const DString& dstrHoldingCompCode, const DString& dstrHoldingCompName, 
                                             const DString& dstrAll, const DString& dstrEffDate)
: MFCanBFCbo( parent ), 
m_intNewKey( 1 ), 
m_intKey( 1024 ),
m_HoldingCompCode(dstrHoldingCompCode),
m_HoldingCompName(dstrHoldingCompName),
m_SearchAll(dstrAll),
m_AsofDate(dstrEffDate),
m_RequestData448(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();   
}

//*********************************************************************************
HoldingCompList::~HoldingCompList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if(m_RequestData448)
      delete m_RequestData448;
}

//*********************************************************************************
SEVERITY HoldingCompList::init (const BFDataGroupId& idDataGroup, 
                                const DString& dstrTrack,
                                const DString& dstrPageName,
                                bool ignoreFoundDeletedError)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   // receive data from back end
   DString mgmtCoIdOut;
   m_RequestData448 = new BFData(ifds::DSTC0448_REQ);  
   m_RequestData448->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   m_RequestData448->setElementValue( ifds::Track, dstrTrack );
   m_RequestData448->setElementValue( ifds::Activity, dstrPageName );
   m_RequestData448->setElementValue( ifds::NextKey,  NULL_STRING );
   m_RequestData448->setElementValue( ifds::Activity, dstrPageName );

   m_RequestData448->setElementValue( ifds::HoldingCompCode, m_HoldingCompCode);
   m_RequestData448->setElementValue( ifds::HoldingCompName, m_HoldingCompName );
   m_RequestData448->setElementValue( ifds::AsofDate, m_AsofDate);
   m_RequestData448->setElementValue( ifds::SearchAll, m_SearchAll );

   DSTCRequestor requestor( getSecurity(), false, false );
   if(ignoreFoundDeletedError)
   {
      requestor.filterHostCondition(CND::ERR_HOLDING_COMPANY_CODE_IS_ALREADY_DELETED);
   }

   BFData* responseData = new BFData(ifds::DSTC0448_VW);
   ReceiveData(DSTC_REQUEST::HOLDING_COMPANY, *m_RequestData448, *responseData, requestor );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY HoldingCompList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new HoldingComp( *this );
   ((HoldingComp* )pObjOut )->Init(data);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY HoldingCompList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   HoldingComp* pHoldingComp = new HoldingComp( *this );
   pHoldingComp->InitNew( idDataGroup  );
   pBase = pHoldingComp;

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY HoldingCompList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   //BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY HoldingCompList::getHoldingComp ( const DString &HoldingCompCode, 
                                     HoldingComp *&pHoldingComp, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getHoldingComp"));

   pHoldingComp = NULL;
   DString dstrHoldingCompCode(HoldingCompCode);
   dstrHoldingCompCode.upperCase();

   BFObjIter iter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end())
   {
      DString HoldingCompCode_;
      HoldingComp* plHoldingComp = dynamic_cast <HoldingComp*> (iter.getObject());
      if(plHoldingComp)
      {
         plHoldingComp->getField(ifds::WhereUseKey, HoldingCompCode_, idDataGroup, false);
         if (HoldingCompCode_.upperCase() == dstrHoldingCompCode) 
         {
            pHoldingComp = plHoldingComp;
            break;
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY HoldingCompList::validateOverlapping( BFCBO *pCBO, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );   

   DString dstrHoldingCompCode,
      dstrHoldingCompType,
      dstrAutoGenHoldingCompCode;

   HoldingComp* pChkObj = dynamic_cast<HoldingComp*> ( pCBO );

   //getWorkSession ().getOption (ifds::AutoGenHoldingCompCode, dstrAutoGenHoldingCompCode, BF::HOST, false);
   dstrAutoGenHoldingCompCode.strip().upperCase();

   if(pChkObj)
   {
      dstrHoldingCompCode.strip().upperCase();
      dstrHoldingCompType.strip().upperCase();

      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
      while( !iter.end() )
      {
         DString dstrHoldingCompCode1,
            dstrHoldingCompType1;

         dstrHoldingCompCode1.strip().upperCase();
         dstrHoldingCompType1.strip().upperCase();

         if ( pChkObj != iter.getObject()) 
         {
            bool bSameFeeCode = dstrHoldingCompCode == dstrHoldingCompCode1;
            bool bSameFeeType = dstrHoldingCompType == dstrHoldingCompType1;
            bool bRaiseCondition = false;

            if (dstrAutoGenHoldingCompCode != I_("Y"))
            {
               if( bSameFeeCode )
               {
                  bRaiseCondition = true;
               }
            }
            else
            {
               if (!pChkObj->isNew() && bSameFeeCode)
               {
                  bRaiseCondition = true;
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
bool HoldingCompList::canDeleteObject( const DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canDeleteObject" ) );   

   DString dstrCodeInUse = NO;
   BFAbstractCBO* pObj = getObject(strKey, idDataGroup);
   assert( pObj );

//   pObj->getField(ifds::CodeIsInUse,dstrCodeInUse,idDataGroup,false);
   if( pObj->isNew() || dstrCodeInUse != YES )
   {
      return true;
   }

   ADDCONDITIONFROMFILE( CND::ERR_FEE_MODEL_CODE_IN_USE );

   return false;
}

//******************************************************************************
void HoldingCompList::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   strKey = asString(m_intKey);

   m_intKey++;
}

//******************************************************************************
void HoldingCompList::getStrKeyForNewItem(DString & strKey)
{
   strKey = asString(m_intNewKey);
   m_intNewKey++;
}

//******************************************************************************
int HoldingCompList::isValidHoldingCompCode( const BFDataGroupId& idDataGroup, const DString& dstrHoldingCompCode, const DString& dstrDate)
{
   //DString dstrEffectiveDate, dstrCode, inputCode = dstrHoldingCompCode;
   //bool found = false;

   //BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   //while( !iter.end() )
   //{
   //   HoldingComp * pHoldingComp = dynamic_cast< HoldingComp*> (iter.getObject() );
   //   if( pHoldingComp != NULL )
   //   {
   //      if(dstrCode.strip().upperCase() == inputCode.strip().upperCase() )
   //      {
   //         found = true;
   //         pHoldingComp->getField( ifds::EffectiveDate, dstrEffectiveDate, BF::HOST );
   //         if( DSTCommonFunctions::CompareDates( dstrDate, dstrEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER )
   //            return 2;
   //      }
   //   }
   //   ++iter;
   //}

   //if( !found ) return 1;
   //

   //check exist, 1 for not exist
   //check effectivedate, 2 for not effective

   return 0; //0 for others
}

//******************************************************************************
void HoldingCompList::getDescByHoldingCompCode( const BFDataGroupId& idDataGroup, const DString& dstrHoldingCompCode, DString& dstrDesc)
{
   //dstrDesc = NULL_STRING;
   //BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   //DString dstrCode = NULL_STRING, inputcode = dstrHoldingCompCode;

   //while( !iter.end() )
   //{
   //   HoldingComp * pHoldingComp = dynamic_cast< HoldingComp*> (iter.getObject() );
   //   if( pHoldingComp != NULL )
   //   {
   //      pHoldingComp->getField( ifds::HoldingCompCode, dstrCode, BF::HOST );
   //      if(dstrCode.strip().upperCase() == inputcode.strip().upperCase() )
   //      {
   //         pHoldingComp->getField( ifds::HoldingCompDesc, dstrDesc, BF::HOST );
   //         break;
   //      }
   //   }
   //   ++iter;
   //}

   return;
}

SEVERITY HoldingCompList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
	   BFData* responseData = new BFData(ifds::DSTC0448_VW);
      ReceiveData(DSTC_REQUEST::HOLDING_COMPANY, *m_RequestData448, *responseData, DSTCRequestor( getSecurity(),false,false ) );
    }

   return(GETCURRENTHIGHESTSEVERITY());
}
