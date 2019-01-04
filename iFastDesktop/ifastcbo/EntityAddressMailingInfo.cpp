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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : EntityAddressMailingInfo.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 09/10/2002
//
// ^CLASS    : EntityAddress
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "EntityAddressMailingInfo.hpp"
#include <ifastdataimpl\dse_dstc0214_vw.hpp>
#include <ifastdataimpl\dse_dstc0214_req.hpp>
#include <ifastdataimpl\dse_dstc0216_req.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include "DocumentTypeList.hpp"
#include "mgmtco.hpp"
#include "entity.hpp"
#include "shareholder.hpp"
#include "accountmailinginfo.hpp"
#include "accountmailinglist.hpp"
#include "mfaccount.hpp"
#include "AcctMailingOverride.hpp"
#include "addressentitylist.hpp"



namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId OPDeliveryOption;
	extern CLASS_IMPORT const BFTextFieldId OPDeliveryMethods;
   extern CLASS_IMPORT const BFTextFieldId Email;	
   extern CLASS_IMPORT const BFTextFieldId HomeFax;	
   extern CLASS_IMPORT const BFTextFieldId BusinessFax;	
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId AuthCode;	
   
}
namespace  
{
	const I_CHAR * const CLASSNAME = I_( "EntityAddressMailingInfo" );  
	const I_CHAR * const YES =   I_( "Y" );
	const I_CHAR * const NO =   I_( "N" );
   const I_CHAR * const IDI_CODE = I_( "CODE" );
 }

namespace CND
{
   extern const long ERR_NO_EMAIL_ADDRESS_FOR_ENTITY;
   extern const long ERR_NO_FAX_AVAILABLE_FOR_ENTITY;
   extern const long WARNING_DOCUMENT_TYPE_IS_ONHOLD;
   extern const long ERR_ADDRESS_CODE_NOT_SETUP;
   extern const long ERR_ADDRESS_CODE_REQUIRED;
}


//*************************************************************************************************
EntityAddressMailingInfo::EntityAddressMailingInfo( BFAbstractCBO &parent )
   : AcctMailingOverride( parent ) 
   {
      TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   }
//*************************************************************************************************
EntityAddressMailingInfo::~EntityAddressMailingInfo()
   {
      TRACE_DESTRUCTOR( CLASSNAME );
   }     

//---------------------------------------------------------------------  
SEVERITY EntityAddressMailingInfo::doValidateField( const BFFieldId& idField,
                                            const DString& strValue,
                                            const BFDataGroupId& idDataGroup )

   {
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

		if( idField == ifds::Suppress )
		{
			validateHold(idField,idDataGroup );
		}
				
	   AcctMailingOverride::doValidateField(idField, strValue, idDataGroup);		
	
		return GETCURRENTHIGHESTSEVERITY();

   }
//*****************************************************************************************
SEVERITY EntityAddressMailingInfo::validateHold(const BFFieldId& idField,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateHold" ) );

   Shareholder*	_pShareholder = NULL;
	MFAccount* pMfAccount = NULL;
   DString dstrAccountNum,strKey;
   getParent()->getParent()->getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );
	if(getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMfAccount ) >WARNING ) return NO_CONDITION;

	DString dstrShareholderNum;
   pMfAccount->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );

   SEVERITY sevRtn = getWorkSession().getShareholder( idDataGroup, dstrShareholderNum, _pShareholder );

   if( sevRtn <= WARNING )
   {
		AccountMailingList*	_pAccountMailingList = NULL;
      sevRtn = _pShareholder->getAccountMailingList( _pAccountMailingList, idDataGroup );
      if( sevRtn <= WARNING )
      {	
		  DString strKey;
  		  _pAccountMailingList->buildKey( strKey, dstrAccountNum );
		  BFObjIter iter(*_pAccountMailingList,idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );	
		  if(iter.positionByKey( strKey ) )
		  {
				AccountMailingInfo* pAccountMailing = dynamic_cast<AccountMailingInfo* >(iter.getObject() );
				if(pAccountMailing)
				{
					DString docCode,docDes;
					getField(ifds::DocumentType,docCode,idDataGroup,false);
					getField(ifds::DocumentType,docDes,idDataGroup,true);
					docCode.strip();docDes.strip();
					if(pAccountMailing->isDocumentTypeOnHold(docCode,idDataGroup) )
					{
						DString idiStr;
						addIDITagValue( idiStr, I_("DOCTYPE"), docDes );
						ADDCONDITIONFROMFILEIDI( CND::WARNING_DOCUMENT_TYPE_IS_ONHOLD, idiStr.c_str() );  						
					
					}				
				}		  
		  }
      }		
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//-----------------------------------------------------------------------------------------
SEVERITY EntityAddressMailingInfo::init( const BFData& InstData )
   {
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(int,BFData&)" ) );

      DString locDump;
      InstData.getAllValues( locDump, true, true );
      attachDataObject(const_cast<BFData&>(InstData), false, true );  //true
		setupSubstituteList(BF::HOST );
		DString dstrValue;	
		getParent()->getParent()->getField(ifds::EntityType,dstrValue,BF::HOST,false);
		setFieldNoValidate(ifds::EntityType,dstrValue,BF::HOST,false);
		getParent()->getParent()->getField(ifds::EntityTypeSeq,dstrValue,BF::HOST,false);
      setFieldNoValidate(ifds::EntityTypeSeq,dstrValue,BF::HOST,false);
	   DString dstrEntityId;
      getParent()->getParent()->getField(ifds::EntityId,dstrEntityId,BF::HOST);
      dstrEntityId.strip();
	   setEntityId(dstrEntityId);
      setMailingFieldsReadonly( BF::HOST );
      setupAuthorizationList(BF::HOST );

      return GETCURRENTHIGHESTSEVERITY();
   }
//----------------------------------------------------------------------------------
//called by create new object
SEVERITY EntityAddressMailingInfo::init( const BFDataGroupId& idDataGroup )
   {
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(long)" ) );

      return GETCURRENTHIGHESTSEVERITY();
   }

//***********************************************************************************
void EntityAddressMailingInfo::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
	DString dstrValue;	
	getParent()->getParent()->getField(ifds::EntityType,dstrValue,idDataGroup,false);
	setFieldNoValidate(ifds::EntityType,dstrValue,idDataGroup,false);
	getParent()->getParent()->getField(ifds::EntityTypeSeq,dstrValue,idDataGroup,false);
	setFieldNoValidate(ifds::EntityTypeSeq,dstrValue,idDataGroup,false);
	DString dstrEntityId;
   getParent()->getParent()->getField(ifds::EntityId,dstrEntityId,idDataGroup);
	setEntityId(dstrEntityId);
	setFieldNoValidate(ifds::Suppress,NO,idDataGroup,false);
	setFieldNoValidate(ifds::Consent,NO,idDataGroup,false);
	setFieldNoValidate(ifds::LEmail,NO,idDataGroup,false);
	setFieldNoValidate(ifds::CD,NO,idDataGroup,false);
	setFieldNoValidate(ifds::Fax,NO,idDataGroup,false);
	setFieldNoValidate(ifds::Mail,YES,idDataGroup,false);
	setFieldNoValidate(ifds::EPost,NO,idDataGroup,false);
	setFieldNoValidate(ifds::DocumentType,NULL_STRING,idDataGroup,false);
   setFieldNoValidate(ifds::AuthCode,I_("D"),idDataGroup,false);
   setupSubstituteList(idDataGroup );

}

//********************************************************************************************************
void EntityAddressMailingInfo::setupSubstituteList(const BFDataGroupId& idDataGroup )
{
	DocumentTypeList* pDocumentTypeList = NULL;
   getMgmtCo().getDocumentTypeList( pDocumentTypeList ); 
	DString docTypeSubList;
	if(pDocumentTypeList)
	{
		pDocumentTypeList->getDocumentTypeSubstitute(docTypeSubList,true);
		setFieldAllSubstituteValues( ifds::DocumentType, idDataGroup, docTypeSubList );	
/*		if(idDataGroup == BF::HOST )
		{
			DString docType,delSubList,dstrDeliveryMethod;
			getWorkSession().getOption2( ifds::OPDeliveryMethods, dstrDeliveryMethod, idDataGroup, false);

			getField(ifds::DocumentType,docType,idDataGroup,false);
			docType.strip();
			pDocumentTypeList->getDeliverySubstitute(docType,delSubList,dstrDeliveryMethod);			
			setFieldAllSubstituteValues( ifds::DeliveryOption, idDataGroup, delSubList );					
		}	
*/
	}
	
}
//*******************************************************************************************************
//override base method 
//
//
SEVERITY EntityAddressMailingInfo::validateAddrMail(const DString dstrValue,const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAddrMail" ) );	
   Entity* pEntity = NULL;
	DString mail(dstrValue);
	mail.strip().upperCase();
	DString dstrAddrCode;
	getField(ifds::EntityAddrCode,dstrAddrCode,idDataGroup,false);
	dstrAddrCode.stripAll();
	if(mail == YES )
	{
		if( dstrAddrCode == NULL_STRING )
		{
			ADDCONDITIONFROMFILE( CND::ERR_ADDRESS_CODE_REQUIRED );			
		}
	}
	SEVERITY sev = getWorkSession().getEntity ( idDataGroup, getEntityId(),pEntity );
   if( pEntity && sev <= WARNING )
	{
		AddressEntityList* pAddressEntityList = NULL;
	   sev = pEntity->getAddressEntityList (pAddressEntityList,idDataGroup); 
      if( sev <= WARNING && pAddressEntityList )
		{
			if( pAddressEntityList->doesAddressCodeExist(dstrAddrCode,idDataGroup ) == false )
			{
				DString strTemp;
				addIDITagValue( strTemp, IDI_CODE, dstrAddrCode.asInteger() );
				ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_CODE_NOT_SETUP, strTemp);
			}		
		}
	}
   return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************************************
SEVERITY EntityAddressMailingInfo::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );	
   AcctMailingOverride::doApplyRelatedChanges( idField, idDataGroup );
   return GETCURRENTHIGHESTSEVERITY();
}
//
// override base logic
SEVERITY EntityAddressMailingInfo::doDocTypeRelateChange( const BFDataGroupId& idDataGroup )
{
   setMailingFieldsReadonly( idDataGroup );

   setupAuthorizationList(  idDataGroup );
   //set hold flag accordingly
   setDefaultHoldFlag( idDataGroup );

   return NO_CONDITION;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityAddressMailingInfo.cpp-arc  $
// 
//    Rev 1.13   Sep 21 2005 16:46:16   yingbaol
// PET1277,FN09 Investment Fund Continious Disclosure
// 
//    Rev 1.12   Jan 20 2005 15:15:42   yingbaol
// PTS10038113: set mailing option as read only for exisitng record.
// 
//    Rev 1.11   Dec 02 2004 11:36:56   yingbaol
// PET1137,FN01: Add Epost functionality.
// 
//    Rev 1.10   Nov 14 2004 14:36:34   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Nov 10 2004 09:41:40   YINGBAOL
// PET1137 FN01: add validation for mail etc...
// 
// 
//    Rev 1.8   Mar 21 2003 18:08:02   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 30 2002 10:10:46   YINGBAOL
// Sync. up from old PVCS database
// 
//    Rev 1.8   Oct 21 2002 11:19:38   YINGBAOL
// more business rules added
// 
//    Rev 1.7   Oct 11 2002 11:38:54   YINGBAOL
// change AddrCode to EntityAddrCode
// 
// 
//    Rev 1.6   Oct 10 2002 12:50:34   HUANGSHA
// added consent
//  		
//    Rev 1.5   Oct 08 2002 11:46:50   YINGBAOL
// change getDocument 
// 
//    Rev 1.4   Sep 26 2002 09:55:12   YINGBAOL
// tune
// 
//    Rev 1.3   Sep 24 2002 10:49:24   YINGBAOL
// add business logic
// 
//    Rev 1.2   Sep 20 2002 15:00:26   YINGBAOL
// add doInitWithdefaultValue
// 
//    Rev 1.1   Sep 17 2002 13:40:48   YINGBAOL
// change fields name
// 
//    Rev 1.0   Sep 10 2002 14:03:26   YINGBAOL
// Initial revision.
 
*/