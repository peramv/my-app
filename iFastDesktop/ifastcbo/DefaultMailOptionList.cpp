
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
//    Copyright 2005 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : DefaultMailOptionList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Semptember. 1, 2005
//
// ^CLASS    : DefaultMailOptionList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0352_req.hpp>
#include <ifastdataimpl\dse_dstc0352_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"
#include "DefaultMailOptionList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DEFAULT_MAILOPTION_LIST;   
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "DefaultMailOptionList" );  
   const I_CHAR * const YES = I_( "Y" );  
   const I_CHAR * const NO = I_( "N" );  
}


//*********************************************************************************
DefaultMailOptionList::DefaultMailOptionList(BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   setVersionable( false );

}

//*********************************************************************************
DefaultMailOptionList::~DefaultMailOptionList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//**********************************************************************************

SEVERITY DefaultMailOptionList::init(  )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   BFData _requestData(ifds::DSTC0352_REQ);

   _requestData.setElementValue( ifds::All, NO );

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::Track, I_("N") );
   _requestData.setElementValue( ifds::Activity, NULL_STRING );

   ReceiveData(DSTC_REQUEST::DEFAULT_MAILOPTION_LIST, _requestData, ifds::DSTC0352_VW, 
               DSTCRequestor( getSecurity() ) );
   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************************************
SEVERITY DefaultMailOptionList::init( const DString& fundGroup   )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   BFData _requestData(ifds::DSTC0352_REQ);

   _requestData.setElementValue( ifds::All, NO );
   _requestData.setElementValue( ifds::FundGroup, fundGroup );

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::Track, I_("N") );
   _requestData.setElementValue( ifds::Activity,  NULL_STRING );

   ReceiveData(DSTC_REQUEST::DEFAULT_MAILOPTION_LIST, _requestData, ifds::DSTC0352_VW, 
               DSTCRequestor( getSecurity() ) );
   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************************************
DString  DefaultMailOptionList::getDefaultHoldFlag(const DString& docType, 
                                                   const DString& fundGroup  )
{
   DString holdFlag(NO);
   DString group(fundGroup);
   group.strip();
   bool bFindGroup = false;
   if( group != NULL_STRING )
   {
      DefaultMailOptionList* pDefaultMailOptionList = NULL;
      if ( getDefaultMailOptionListByFundGroup( group,
                                 pDefaultMailOptionList  ) <= WARNING )
      {
         BFObjIter iter( *pDefaultMailOptionList, BF::HOST, true, 
                        BFObjIter::ITERTYPE::NON_DELETED );
      
         while ( !iter.end()  )
         {
            DString itDocType;
            iter.getObject()->getField(ifds::DocumentType,itDocType,BF::HOST,false);
            if(  docType == itDocType.strip() )
            {
               bFindGroup = true;
               iter.getObject()->getField(ifds::HoldMail,holdFlag,BF::HOST,false);
               holdFlag.strip().upperCase();  
               break;
            }      
            ++iter;
         }         
      }
   }
   if( bFindGroup )
   {
      return holdFlag;
   }
//can not find default mail option for the group
//then try to look for document typpe without group.

   DefaultMailOptionList* pDefaultMailOptionList = NULL;
   if( getDefaultMailOptionListForDocType( pDefaultMailOptionList ) <= WARNING  && pDefaultMailOptionList )
   {
      BFObjIter iter( *pDefaultMailOptionList, BF::HOST, true, 
                     BFObjIter::ITERTYPE::NON_DELETED );      
      while ( !iter.end()  )
      {
         DString itDocType;
         iter.getObject()->getField(ifds::DocumentType,itDocType,BF::HOST,false);
         if(  docType == itDocType.strip() )
         {
            iter.getObject()->getField(ifds::HoldMail,holdFlag,BF::HOST,false);
            holdFlag.strip().upperCase();  
            break;
         }      
         ++iter;
      }   
   }
   return holdFlag;
}
//******************************************************************************
// DefaultMailOption  at fund Group level
//
SEVERITY  DefaultMailOptionList::getDefaultMailOptionListByFundGroup( 
                                    const DString& fundGroup,
                                    DefaultMailOptionList*& pDefaultMailOptionList  )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDefaultMailOptionListByFundGroup" ) );
   DString strKey = I_("DefaultOption")+ fundGroup;
	pDefaultMailOptionList = dynamic_cast<DefaultMailOptionList*>(getObject( strKey, BF::HOST ) );
    
	if (!pDefaultMailOptionList )
    {
      // if does not exist, create a new one
      pDefaultMailOptionList = new DefaultMailOptionList((BFAbstractCBO&)(*this));

      if ( pDefaultMailOptionList->init( fundGroup ) <= WARNING )
      {
         setObject( pDefaultMailOptionList, strKey, OBJ_ACTIVITY_NONE, BF::HOST ); 		
      }
      else
      {
         delete pDefaultMailOptionList;
         pDefaultMailOptionList = NULL;
      }
	}
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// DefaultMailOption 
//
SEVERITY  DefaultMailOptionList::getDefaultMailOptionListForDocType( 
                                    DefaultMailOptionList*& pDefaultMailOptionList  )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDefaultMailOptionListForDocType" ) );
   DString strKey = I_("DefaultOptionDoc");
	pDefaultMailOptionList = dynamic_cast<DefaultMailOptionList*>(getObject( strKey, BF::HOST ) );
    
	if (!pDefaultMailOptionList )
    {
      // if does not exist, create a new one
      pDefaultMailOptionList = new DefaultMailOptionList((BFAbstractCBO&)(*this));
      if ( pDefaultMailOptionList->init( ) <= WARNING )
      {
         setObject( pDefaultMailOptionList, strKey, OBJ_ACTIVITY_NONE, BF::HOST ); 		
      }
      else
      {
         delete pDefaultMailOptionList;
         pDefaultMailOptionList = NULL;
      }
	}
   return(GETCURRENTHIGHESTSEVERITY());
}
//**************************************************************************
bool DefaultMailOptionList::isObjectExit(const DString& fundGroup, const DString& docType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isObjectExit" ) );

   bool bRet = false;
   DefaultMailOptionList* pDefaultMailOptionList = NULL;
   SEVERITY sev = getDefaultMailOptionListByFundGroup( fundGroup,pDefaultMailOptionList  );
   if( sev <= WARNING && pDefaultMailOptionList )
   {
      BFObjIter iter( *pDefaultMailOptionList, BF::HOST, true, 
                     BFObjIter::ITERTYPE::NON_DELETED );      
      while ( !iter.end()  )
      {
         DString itDocType;
         iter.getObject()->getField(ifds::DocumentType,itDocType,BF::HOST,false);
         if(  docType == itDocType.strip() )
         {
            bRet = true;
            break;
         }
         ++iter;
      }
   }
   return bRet;
}

//******************************************************************************
SEVERITY DefaultMailOptionList::getDefaultDeliveryOptionFlags(DString& defOption, 
                                                              const DString& docType,
                                                              const DString& fundGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDefaultDeliveryOptionFlags" ) );

   DefaultMailOptionList* pDefaultMailOptionList = NULL;
   SEVERITY sev = getDefaultMailOptionListByFundGroup( fundGroup,pDefaultMailOptionList  );
   if( sev <= WARNING && pDefaultMailOptionList )
   {
      BFObjIter iter( *pDefaultMailOptionList, BF::HOST, true, 
                       BFObjIter::ITERTYPE::NON_DELETED );

      DString strDeliveryOptionDefault;
      while ( !iter.end()  )
      {
         DString itDocType;
         iter.getObject()->getField(ifds::DocumentType,itDocType,BF::HOST,false);
         if( docType == itDocType.strip() )
         {
            iter.getObject()->getField(ifds::DeliveryOptionDefault,strDeliveryOptionDefault,BF::HOST,true);
            strDeliveryOptionDefault.strip().upperCase();
            
            defOption = strDeliveryOptionDefault;
            break;
         }
         ++iter;
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultMailOptionList.cpp-arc  $
// 
//    Rev 1.1   Sep 29 2005 10:49:30   yingbaol
// PET1277-FN09: Investment Fund Continuous Disclosure
// 
//    Rev 1.0   Sep 21 2005 16:49:04   yingbaol
// Initial revision.
 * 



 */




