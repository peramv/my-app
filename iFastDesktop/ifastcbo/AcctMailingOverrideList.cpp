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
// ^FILE   : AcctMailingOverrideList.cpp
// ^AUTHOR : 
// ^DATE   : Semptember. 10, 2002
//
// ^CLASS    : AcctMailingOverrideList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0214_req.hpp>
#include <ifastdataimpl\dse_dstc0214_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"
#include "AcctMailingOverrideList.hpp"
#include "AcctMailingOverride.hpp"
#include "DefaultMailOptionList.hpp"
#include "FundCommGroupList.hpp"
#include "TranslationTable.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITY_ADDRESS_MAILING;   
   extern CLASS_IMPORT const DSTCRequest ENTITY_MAIL_DELIVER_OPTION;
}

namespace  
{
	const I_CHAR * const CLASSNAME = I_( "AcctMailingOverrideList" );  
	
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId MiscCode;
}
namespace CND
{  // Conditions used
      extern const long ERR_DUPLICATED_ENTITY_MAIL;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//*********************************************************************************
AcctMailingOverrideList::AcctMailingOverrideList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
AcctMailingOverrideList::~AcctMailingOverrideList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//**********************************************************************************
SEVERITY AcctMailingOverrideList::initNew( const DString& accountNum,
									   const BFDataGroupId& idDataGroup,
													const DString& entityType,
													const DString& seqNumber )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );


   return(GETCURRENTHIGHESTSEVERITY());
}
//*********************************************************************************
SEVERITY AcctMailingOverrideList::init( const DString& dstrAccountNum, 
													  const BFDataGroupId& idDataGroup,
													  const DString& dstrEntityType,
													  const DString& dstrEntityTypeSeq,													  
													  const DString& dstrRequestType,													  
													  const DString& dstrTrack,
													  const DString& dstrPageName  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   
   BFData _requestData(ifds::DSTC0214_REQ);
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
	_requestData.setElementValue( ifds::EntityType, dstrEntityType );
	_requestData.setElementValue( ifds::EntityTypeSeq, dstrEntityTypeSeq );
	_requestData.setElementValue( ifds::RequestType, dstrRequestType );
   ReceiveData(DSTC_REQUEST::ENTITY_ADDRESS_MAILING, _requestData, ifds::DSTC0214_VW, DSTCRequestor( getSecurity(), false) );
 	return GETCURRENTHIGHESTSEVERITY();
}
//********************************************************************************
SEVERITY AcctMailingOverrideList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
	pObjOut =  new AcctMailingOverride( *this );
	((AcctMailingOverride* )pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY AcctMailingOverrideList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   AcctMailingOverride* pAcctMailingOverride = new AcctMailingOverride( *this );
	pAcctMailingOverride->init( idDataGroup  );
	pBase = pAcctMailingOverride;
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY AcctMailingOverrideList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
//document type and FundGroup should be unique
// yingbao as of Dec. 2, 2004
	BFObjIter iter1( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
	BFObjIter iter2( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
	while( !iter1.end() )
	{
		DString docType1,docType2,fundGroup1, fundGroup2,docDes;
		BFAbstractCBO* pBase1 = iter1.getObject();
      if( pBase1 )
      {
		   pBase1->getField(ifds::DocumentType,docType1,idDataGroup,false);
		   pBase1->getField(ifds::DocumentType,docDes,idDataGroup,true);
		   pBase1->getField(ifds::FundGroup,fundGroup1,idDataGroup,false);
		   docType1.strip();
         fundGroup1.strip();
	      iter2.positionByKey( iter1.getStringKey() ); 
		   ++iter2;
		   while(!iter2.end() )
			   {
				   BFAbstractCBO* pBase2 = iter2.getObject();
               if ( pBase2 )
               {
				      pBase2->getField(ifds::DocumentType,docType2,idDataGroup,false);
				      pBase2->getField(ifds::FundGroup,fundGroup2,idDataGroup,false);
				      docType2.strip();
				      fundGroup2.strip();
				      if(docType1 == docType2  &&  fundGroup1 == fundGroup2 )
				      {
					      DString idiStr;
					      addIDITagValue( idiStr, I_("DOCTYPE"), docDes );
					      ADDCONDITIONFROMFILEIDI( CND::ERR_DUPLICATED_ENTITY_MAIL, idiStr.c_str() );  							
				      }
               }
			     ++iter2;
			   }
      }
	 ++iter1;
	}
   return GETCURRENTHIGHESTSEVERITY();
}
//**************************************************************************************************
// 
// notice: this is a special requirement from base side, please do not use the method anywhare else!
//

SEVERITY AcctMailingOverrideList::createAllPossibleRecordsInNasu( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createAllPossibleRecordsInNasu" ) );
	FundCommGroupList* pFundCommGroupList = NULL;
   SEVERITY sev = getMgmtCo().getFundCommGroupList(I_("Mail"), pFundCommGroupList );
	if( sev <= WARNING  && pFundCommGroupList )
	{
	      TranslationTable* pTranslationTable = NULL;      	
	      sev = getMgmtCo().getTranslationTable(I_("OM"), pTranslationTable);
	      if(  sev <= WARNING && pTranslationTable )
	      {
	         BFObjIter iterFundGroup( *pFundCommGroupList, idDataGroup  );
            while ( !iterFundGroup.end() )
            {
               DString fundGroup;
               iterFundGroup.getObject()->getField(ifds::FundGroup,fundGroup,BF::HOST,false);
               fundGroup.strip();
            	BFObjIter iterDocList( *pTranslationTable, idDataGroup  );
               while ( !iterDocList.end() )
               {
                  DString docType;
                  iterDocList.getObject()->getField(ifds::MiscCode,docType,BF::HOST,false);
                  docType.strip();
                  if( docType != NULL_STRING && fundGroup != NULL_STRING )
                  {
                     DefaultMailOptionList* pDefaultMailOptionList = NULL;
                     sev = getMgmtCo().getDefaultMailOptionList( pDefaultMailOptionList );
                     if( sev <= WARNING && pDefaultMailOptionList )
                     {
                        if( pDefaultMailOptionList->isObjectExit(fundGroup, docType ) )
                        {     
                           DString strKey;
                           BFObjectKey objKey( strKey, idDataGroup );
                           AcctMailingOverride* pAcctMlOverride = 
                              dynamic_cast<AcctMailingOverride* >( getNewListItem( objKey ) );
                           if( pAcctMlOverride )
                           {

                              pAcctMlOverride->setObjectAsUpdated( docType,fundGroup,idDataGroup );
                           }
                        }                     
                     }
                  }
                  ++iterDocList;   
               }        
              ++iterFundGroup;   
            }
         }
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
void AcctMailingOverrideList::getStrKey(DString &strKey, const BFData *data)  
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

	if (data)
   {
      DString dstrFundGroup = 
         data->getElementValue (ifds::FundGroup);
      DString dstrDocumentType = 
         data->getElementValue (ifds::DocumentType);

      dstrFundGroup.strip();
      dstrDocumentType.strip();
      strKey = dstrFundGroup + I_(" ") + dstrDocumentType;
   }
   else
   {
      BFCBO::getStrKey (strKey , NULL);
   }
}


//******************************************************************************
void AcctMailingOverrideList::buildKey ( const DString &dstrFundGroup,
                                       const DString &dstrDocumentType,
                                       DString &strKey)
{
   DString _FundGroup (dstrFundGroup), _DocumentType (dstrDocumentType);

	_FundGroup.strip().stripLeading ('0');
   _DocumentType.strip().stripLeading ('0');
   strKey = _FundGroup + I_(" ") + _DocumentType;
}

/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctMailingOverrideList.cpp-arc  $
// 
//    Rev 1.7   Oct 24 2005 17:22:38   ZHANGCEL
// PET1332 FN09A -- Add getStrKey 
// 
//    Rev 1.6   Sep 29 2005 10:49:26   yingbaol
// PET1277-FN09: Investment Fund Continuous Disclosure
// 
//    Rev 1.5   Sep 21 2005 16:45:06   yingbaol
// PEt1277,FN09: Investment Fund Continuous Disclosure
// 
//    Rev 1.4   Dec 03 2004 17:18:16   yingbaol
// PET1137,FN01: fix business rules.
// 
//    Rev 1.3   Sep 18 2003 15:44:26   FENGYONG
// modify parameter sequence, add default value for parameters
// 
//    Rev 1.2   Apr 04 2003 16:35:40   FENGYONG
// Add getstrkey
// 
//    Rev 1.1   Apr 01 2003 16:42:30   FENGYONG
// use different CBO for view #214 
// 
//    Rev 1.0   Mar 31 2003 15:51:54   FENGYONG
// Initial Revision
//
*/
