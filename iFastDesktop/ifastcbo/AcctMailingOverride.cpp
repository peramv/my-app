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
// ^FILE   : AcctMailingOverride.cpp
// ^AUTHOR : 
// ^DATE   : 09/10/2002
//
// ^CLASS    : AcctMailingOverride
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//****************************************************3**************************
#include "stdafx.h"
#include "AcctMailingOverride.hpp"
#include "FundCommGroupList.hpp"
#include "mgmtco.hpp"
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
#include "TranslationTable.hpp"
#include "addresslist.hpp"
#include "accountentityxref.hpp"
#include "DefaultMailOptionList.hpp"
#include "DocumentType.hpp"
#include "taxtyperule.hpp"


namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId OPDeliveryOption;
   extern CLASS_IMPORT const BFTextFieldId OPDeliveryMethods;
   extern CLASS_IMPORT const BFTextFieldId Email;	
   extern CLASS_IMPORT const BFTextFieldId HomeFax;	
   extern CLASS_IMPORT const BFTextFieldId BusinessFax;	
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;	
   extern CLASS_IMPORT const BFTextFieldId OnHold;
   extern CLASS_IMPORT const BFTextFieldId TxnConfAddr;
   extern CLASS_IMPORT const BFTextFieldId StmtAddr;
   extern CLASS_IMPORT const BFTextFieldId MailingOption;
   extern CLASS_IMPORT const BFTextFieldId MailConsent;
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit1;
   extern CLASS_IMPORT const BFTextFieldId Authorization;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId TaxType;


}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,             State Flags,  Group Flags
   { ifds::DocumentType,			BFCBO::REQUIRED,                 0 }, 
   { ifds::EntityAddrCode,			BFCBO::NONE,	                  0 }, 
   { ifds::Suppress,				   BFCBO::REQUIRED,                 0 }, 
   //{ ifds::DeliveryOption,			BFCBO::REQUIRED,              0 }, 
   { ifds::EntityType,				BFCBO::NONE,                     0 }, 
   { ifds::EntityTypeSeq,			BFCBO::NONE,                     0 }, 
   { ifds::Consent,				   BFCBO::NONE,                     0 }, 
   { ifds::FundGroup,				BFCBO::NONE,                     0 }, 
   { ifds::LEmail,				   BFCBO::NONE,                     0 }, 
   { ifds::Fax,				      BFCBO::NONE,                     0 }, 
   { ifds::Mail,				      BFCBO::NONE,                     0 }, 
   { ifds::CD,					      BFCBO::NONE,                     0 }, 
   { ifds::EPost,					   BFCBO::NONE,                     0 }, 
   { ifds::AuthCode,			      BFCBO::REQUIRED,                 0 },
   { ifds::Authorization,			BFCBO::NONE,                     0 },  
   { ifds::OnHold,				   BFCBO::NONE,                     0 }, 
   { ifds::MailingOption,			BFCBO::IMMEDIATE_VALIDATION,     0 }, 
   { ifds::MailConsent,			   BFCBO::IMMEDIATE_VALIDATION,     0 }, 
   { ifds::FieldCrossEdit1,	   BFCBO::NONE,                     0 }, 

};

namespace  
{
	const I_CHAR * const CLASSNAME = I_( "AcctMailingOverride" );  
	const I_CHAR * const NO =   I_( "N" );  
	const I_CHAR * const YES =   I_( "Y" );  
   const I_CHAR * const IDI_CODE = I_( "CODE" );
}

namespace CND
{
   extern const long ERR_NO_EMAIL_ADDRESS_FOR_ENTITY;
   extern const long ERR_NO_FAX_AVAILABLE_FOR_ENTITY;
   extern const long WARNING_DOCUMENT_TYPE_IS_ONHOLD;
   extern const long ERR_NO_MAIL_TO_SUPPRESS;
   extern const long ERR_NO_FAX_AVAILABLE;
   extern const long ERR_NO_EMAIL_ADDRESS;  
   extern const long ERR_ADDRESS_CODE_NOT_EFFECTIVE;  
   extern const long WARN_ADDRESS_CODE_NOT_EFFECTIVE;   
   extern const long ERR_ADDRESS_CODE_NOT_SETUP;
   extern const long ERR_ADDRESS_CODE_REQUIRED;
   extern const long ERR_MAIL_CONSENT_CANNT_BOTH_YES_OR_NO;
   extern const long ERR_NO_HOLD_FOR_RETURN_MAIL;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

//*************************************************************************************************
AcctMailingOverride::AcctMailingOverride( BFAbstractCBO &parent )
   : MFCanBFCbo( parent ) 
   {
      TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

      registerMemberData( NUM_FIELDS,
                          (const CLASS_FIELD_INFO *)&classFieldInfo,
                          0, NULL );

	  addCrossEdit(ifds::MailingOption, ifds::Suppress);
//	  addCrossEdit(ifds::MailingOption, ifds::Consent);
	  addCrossEdit(ifds::MailingOption, ifds::Mail );
	  addCrossEdit(ifds::MailingOption, ifds::CD );
	  addCrossEdit(ifds::MailingOption, ifds::Email );
	  addCrossEdit(ifds::MailingOption, ifds::Fax );
	  addCrossEdit(ifds::MailingOption, ifds::EPost );
	  addCrossEdit(ifds::MailConsent, ifds::Mail);
	  addCrossEdit(ifds::MailConsent, ifds::Consent);
	  addCrossEdit(ifds::FieldCrossEdit1, ifds::AuthCode);
	  addCrossEdit(ifds::FieldCrossEdit1, ifds::OnHold);

   }
//*************************************************************************************************
AcctMailingOverride::~AcctMailingOverride()
   {
      TRACE_DESTRUCTOR( CLASSNAME );
   }     

//---------------------------------------------------------------------  
SEVERITY AcctMailingOverride::doValidateField( const BFFieldId& idField,
                                            const DString& strValue,
                                            const BFDataGroupId& idDataGroup )

{
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

		 if (idField == ifds::LEmail )
		{
			validateEmail( strValue, idDataGroup );
		}
		else if (idField == ifds::Fax )
		{
			validateFax(strValue,idDataGroup );
		
		}
		else if ( idField == ifds::Mail || idField == ifds::CD || idField == ifds::EntityAddrCode )
		{
		    validateAddrMail( strValue, idDataGroup );
		
		}
		else if( idField == ifds::MailingOption )
		{
			DString suppress, consent;
			getField( ifds::Suppress, suppress, idDataGroup, false );
			getField( ifds::Consent, consent, idDataGroup, false );

			if( suppress == YES /*|| consent == YES*/ ) 
			{
				DString mail, cd, email, fax,epost;
				getField( ifds::Mail, mail, idDataGroup, false );
				getField( ifds::CD, cd, idDataGroup, false );
				getField( ifds::LEmail, email, idDataGroup, false );
				getField( ifds::Fax, fax, idDataGroup, false );
				getField( ifds::EPost, epost, idDataGroup, false );
            mail.strip().upperCase();
            cd.strip().upperCase();
            email.strip().upperCase();
            fax.strip().upperCase();
            epost.strip().upperCase();
				if(mail == NO && cd == NO && email == NO && fax == NO && epost == NO  )
				{
					DString docCode,docDes;
					getField(ifds::DocumentType,docCode,idDataGroup,false);
					getField(ifds::DocumentType,docDes,idDataGroup,true);
					docCode.strip();docDes.strip();
					DString idiStr;
					addIDITagValue( idiStr, I_("DOCTYPE"), docDes );
					
					ADDCONDITIONFROMFILEIDI( CND::ERR_NO_MAIL_TO_SUPPRESS, idiStr.c_str() );
				}
			}
		}
		//if( idField == ifds::Mail || idField == ifds::Consent )
		else if( idField == ifds::MailConsent )
		{
			DString mail, consent;
			getField( ifds::Mail, mail, idDataGroup, false );
			getField( ifds::Consent, consent, idDataGroup, false );
			if((mail == YES && consent == YES) || (mail == NO && consent == NO))
			{
				DString docCode,docDes;
				getField(ifds::DocumentType,docCode,idDataGroup,false);
				getField(ifds::DocumentType,docDes,idDataGroup,true);
				docCode.strip();docDes.strip();
				DString idiStr;
				addIDITagValue( idiStr, I_("DOCTYPE"), docDes );
				ADDCONDITIONFROMFILEIDI( CND::ERR_MAIL_CONSENT_CANNT_BOTH_YES_OR_NO, idiStr.c_str() );
			}
		}
		else if( idField == ifds::OnHold)
		{
		}
      else if( idField == ifds::FieldCrossEdit1 )  
      {
         validateAuthHold(  idDataGroup );
      }
		return GETCURRENTHIGHESTSEVERITY();

}
//*******************************************************************************************
SEVERITY AcctMailingOverride::doValidateAll(const BFDataGroupId &idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
	DString dstrAccountNum;
	getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	dstrAccountNum.strip ().stripLeading ('0');
	MFAccount *pMFAccount = NULL;
	if (!isNew()&& isUpdatedForDataGroup (idDataGroup)&& 
		getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
	{
		bool bDisplyWarnSICAV ,bDisplyWarnOEIC;
		pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
		if(bDisplyWarnSICAV)
			ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
		if(bDisplyWarnOEIC)
			ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC); 
	}

	return GETCURRENTHIGHESTSEVERITY();	
}



//*************************************************************************************************
void AcctMailingOverride::setMailingFieldsReadonly(const BFDataGroupId& idDataGroup)
{
	DString dstrDeliveryMethod,dstrDeliveryOption;
	getWorkSession().getOption2( ifds::OPDeliveryOption, dstrDeliveryOption, BF::HOST, false);
	getWorkSession().getOption2( ifds::OPDeliveryMethods, dstrDeliveryMethod, BF::HOST, false);
	dstrDeliveryMethod.strip();
	dstrDeliveryOption.strip();
	bool bSuppressReadonly = dstrDeliveryOption == NO;

	DocumentTypeList* pDocumentTypeList = NULL;
	getMgmtCo().getDocumentTypeList( pDocumentTypeList ); 

	bool bFindDocMail = false;
	bool bFindDocFax = false;
	bool bFindDocEmail = false;
	bool bFindDocCD = false;
   bool bFindEpost = false;
	DString dstrDocType;
	getField(ifds::DocumentType,dstrDocType,idDataGroup,false);
   if(pDocumentTypeList)
	{		
		DString dstrSubstList;
		pDocumentTypeList->getDeliverySubstitute(dstrDocType,dstrSubstList,dstrDeliveryMethod);
      bFindDocMail = (dstrSubstList.find(DELIVER_OPTION::MAIL ) != DString::npos );
      bFindDocEmail = (dstrSubstList.find(DELIVER_OPTION::EMAIL) != DString::npos );
      bFindDocFax = (dstrSubstList.find(DELIVER_OPTION::FAX ) != DString::npos );
      bFindDocCD = (dstrSubstList.find(DELIVER_OPTION::CD ) != DString::npos );
      bFindEpost = (dstrSubstList.find(DELIVER_OPTION::EPOST ) != DString::npos );
	}

	bool bUpdate = (dstrDeliveryOption == YES  && bFindDocMail );
	setFieldReadOnly( ifds::Mail, idDataGroup, !bUpdate );
	bUpdate = (dstrDeliveryOption == YES  && bFindDocFax );
	setFieldReadOnly( ifds::Fax, idDataGroup, !bUpdate );
	bUpdate = (dstrDeliveryOption == YES  && bFindDocCD );
	setFieldReadOnly( ifds::CD, idDataGroup, !bUpdate );
	bUpdate = (dstrDeliveryOption == YES  && bFindDocEmail );
	setFieldReadOnly( ifds::LEmail, idDataGroup, !bUpdate );	
	bUpdate = (dstrDeliveryOption == YES  && bFindEpost );
	setFieldReadOnly( ifds::EPost, idDataGroup, !bUpdate );
// suppress
//
   if( dstrDocType != DocType::CONFIRMATION  && dstrDocType != DocType::STATEMENT 
          && dstrDocType != DocType::ADDITIONAL_CONFIRM && dstrDocType != DocType::ADDITIONAL_STATEMENT
          && dstrDocType != DocType::CONTRACT_NOTES )
   {
      bSuppressReadonly = true;
   }
   setFieldReadOnly( ifds::Suppress, idDataGroup, bSuppressReadonly );



}
//*****************************************************************************************
SEVERITY AcctMailingOverride::validateHold(const BFFieldId& idField,const BFDataGroupId& idDataGroup )
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

//**********************************************************************************************
SEVERITY AcctMailingOverride::validateFax(const DString dstrValue,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFax" ) );

	DString email(dstrValue);
	email.strip().upperCase();
	Entity*  pEntity = NULL;

	getWorkSession().getEntity( idDataGroup, _entityID, pEntity );  
   if(pEntity &&  email == YES )
	{
	  DString dstrBusFax,dstrHomFax;
	  pEntity->getField(ifds::HomeFax,dstrHomFax,idDataGroup,false);
	  pEntity->getField(ifds::BusinessFax,dstrBusFax,idDataGroup,false);
	  dstrHomFax.stripAll();
	  dstrBusFax.stripAll();
	  if( dstrBusFax == NULL_STRING  && dstrHomFax == NULL_STRING )	
	  {
		 ADDCONDITIONFROMFILE( CND::ERR_NO_FAX_AVAILABLE );		  
	  }
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************************
SEVERITY AcctMailingOverride::validateEmail(const DString dstrValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEmail" ) );
	DString email(dstrValue);
	email.strip().upperCase();
	Entity*  pEntity = NULL;

	getWorkSession().getEntity( idDataGroup, _entityID, pEntity );  
   if(pEntity &&  email == YES )
	{
	  DString dstrEmail;
	  pEntity->getField(ifds::Email,dstrEmail,idDataGroup,false);
	  dstrEmail.stripAll();
	  if( dstrEmail == NULL_STRING ){
		ADDCONDITIONFROMFILE( CND::ERR_NO_EMAIL_ADDRESS );	
	  }	
	}
   return GETCURRENTHIGHESTSEVERITY();

}
//************************************************************************************************
// this mothed should be overrided for entity mailing


SEVERITY AcctMailingOverride::validateAddrMail(const DString dstrValue,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMail" ) );
   DString mail,cd;
	DString dstrAddrCode;


	getField(ifds::Mail,mail,idDataGroup,false);
	getField(ifds::CD,cd,idDataGroup,false);
   cd.strip().upperCase();
   mail.strip().upperCase();

	getField(ifds::EntityAddrCode,dstrAddrCode,idDataGroup,false);
	dstrAddrCode.stripAll();
	if(mail == YES ||  cd == YES )
	{
		if( dstrAddrCode == NULL_STRING )
		{
			ADDCONDITIONFROMFILE( CND::ERR_ADDRESS_CODE_REQUIRED );			
		}
	   else
		{
			DString dstrShrNum;
			getParent()->getParent()->getField(ifds::ShrNum,dstrShrNum,idDataGroup,false);
			dstrShrNum.strip();
			Shareholder* pShareholder;

			if( getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder ) <= WARNING )
			{
				AddressList* pAddressList = NULL;

				if( pShareholder->getAddressList( pAddressList, idDataGroup ) <= WARNING )
				{
					if( pAddressList )
					{
						DString strTemp;
						bool bValid = false;

						if( pAddressList->IsValidateAddressCode( dstrAddrCode, idDataGroup, bValid ) )
						{
							if( !bValid )
							{
								addIDITagValue( strTemp, IDI_CODE, dstrAddrCode.asInteger() );
								ADDCONDITIONFROMFILEIDI( CND::WARN_ADDRESS_CODE_NOT_EFFECTIVE, strTemp );
							}
						}
						else
						{
							addIDITagValue( strTemp, IDI_CODE, dstrAddrCode.asInteger() );
							ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_CODE_NOT_SETUP, strTemp);
						}										
					}
				}
			}		
		}	
	}
   return GETCURRENTHIGHESTSEVERITY();

}


//-----------------------------------------------------------------------------------------
SEVERITY AcctMailingOverride::init( const BFData& InstData )
   {
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(int,BFData&)" ) );

		DString locDump;
		InstData.getAllValues( locDump, true, true );
		attachDataObject(const_cast<BFData&>(InstData), false, true );  //true

		setupSubstituteList(BF::HOST );
		DString dstrValue;	

		setFieldNoValidate(ifds::EntityType,I_("01"),BF::HOST,false);
		setFieldNoValidate(ifds::EntityTypeSeq,I_("1"),BF::HOST,false);

		//for existing record, the key field should be readonly
		setFieldReadOnly( ifds::FundGroup, BF::HOST, true );
		setFieldReadOnly( ifds::DocumentType, BF::HOST, true );
      setupAuthorizationList(BF::HOST );
		setMailingFieldsReadonly(BF::HOST );
      return GETCURRENTHIGHESTSEVERITY();
   }
//----------------------------------------------------------------------------------
//called by create new object
SEVERITY AcctMailingOverride::init( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(long)" ) );
   setupSubstituteList(idDataGroup );
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
void AcctMailingOverride::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
	DString dstrValue;	
	
	setFieldNoValidate(ifds::EntityType,I_("01"),idDataGroup,false);	
	setFieldNoValidate(ifds::EntityTypeSeq,I_("1"),idDataGroup,false);

	setFieldNoValidate(ifds::Suppress,NO,idDataGroup,false);
	setFieldNoValidate(ifds::Consent,NO,idDataGroup,false);
	setFieldNoValidate(ifds::LEmail,NO,idDataGroup,false);
	setFieldNoValidate(ifds::CD,NO,idDataGroup,false);
	setFieldNoValidate(ifds::Fax,NO,idDataGroup,false);
	setFieldNoValidate(ifds::OnHold,NO,idDataGroup,false);
	setFieldNoValidate(ifds::Mail,YES,idDataGroup,false);
	setFieldNoValidate(ifds::EPost,NO,idDataGroup,false);
	setFieldNoValidate(ifds::DocumentType,NULL_STRING,idDataGroup,false);
	setFieldNoValidate(ifds::AuthCode,I_("D"),idDataGroup,false);
	
//	setFieldNoValidate(ifds::DeliveryOption,I_("01"),idDataGroup,false);
}

//********************************************************************************************************
void AcctMailingOverride::setupSubstituteList(const BFDataGroupId& idDataGroup )
{
	TranslationTable* pTranslationTable = NULL;
	DString dstrGroupCode = I_("OM");
	DString docTypeSubList;
	getMgmtCo().getTranslationTable(dstrGroupCode, pTranslationTable);
	if( pTranslationTable )
	{
	   pTranslationTable->getSubstitutionList(docTypeSubList);
		setFieldAllSubstituteValues( ifds::DocumentType, idDataGroup, docTypeSubList );
	
	}
	FundCommGroupList* pFundCommGroupList = NULL;
	if(getMgmtCo().getFundCommGroupList(I_("Mail"), pFundCommGroupList ) <= WARNING )	//group type should be "FndGrp", need change back when view data fix applied
	{
		DString dstrSubList;
		pFundCommGroupList->getCommGroupSubstitute(dstrSubList);
		setFieldAllSubstituteValues( ifds::FundGroup,idDataGroup, dstrSubList );	
	}

	DString dstrAcctNum;	
	getParent()->getParent()->getField(ifds::AccountNum, dstrAcctNum, idDataGroup, false);
	
	AccountEntityXref *_pAccountEntityXref;

	if ( getWorkSession().getAccountEntityXref( idDataGroup, _pAccountEntityXref ) <= WARNING )
	{
	 if ( _pAccountEntityXref->PopulateAccountOwner( idDataGroup, NULL_STRING, dstrAcctNum, NULL_STRING, NULL_STRING ) <= WARNING )
	 {
		BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
		DString searchKey;
		AccountEntityXref::buildPartialKeyForRetrievingEntity( searchKey, dstrAcctNum, I_( "01" ), I_( "1" ) );

		if ( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
		{
			 DString dstrEntityId;
			 iterAccountEntityXrefOut.getObject()->getField( ifds::EntityId, dstrEntityId, idDataGroup, false );      
			 dstrEntityId.strip();
			 setEntityId(dstrEntityId);

		}
	 }
	}
}
//*******************************************************************************************************
//*******************************************************************************************************
SEVERITY AcctMailingOverride::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );	
	if( idField == ifds::DocumentType )
	{
		doDocTypeRelateChange(idDataGroup);
	}
	else if(idField == ifds::EntityAddrCode  )
	{
		setFieldUpdated( ifds::Mail, idDataGroup,true );
		setValidFlag( ifds::Mail, idDataGroup,false );	
	}
    else if(idField == ifds::Mail  )
	{
		setFieldUpdated( ifds::EntityAddrCode, idDataGroup,true );
		setValidFlag( ifds::EntityAddrCode, idDataGroup,false );	
	}
    else if ( idField == ifds::FundGroup )
    {
        setDefaultHoldFlag( idDataGroup );
    }
    else if ( idField ==  ifds::AuthCode )
    {
      authorizRelatedChanges( idField,idDataGroup );
    }
    else if( idField == ifds::OnHold )
    {
      if ( !bfutil::isServerContext() )
      {
         holdRelatedChanges( idField, idDataGroup );
      }
    }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************************
SEVERITY AcctMailingOverride::doDocTypeRelateChange( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doDocTypeRelateChange" ) );
   setMailingFieldsReadonly( idDataGroup );
   Shareholder*	_pShareholder = NULL;
   MFAccount* pMfAccount = NULL;
   DString dstrAccountNum,strKey;
   getParent()->getParent()->getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );
   if(getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMfAccount ) >WARNING ) 
	   return NO_CONDITION;

	DString dstrDocType, dstrAddrCode;
	getField(ifds::DocumentType,dstrDocType,idDataGroup,false);

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
               if(dstrDocType == DocType::CONFIRMATION )
					{
						pAccountMailing->getField(ifds::TxnConfAddr, dstrAddrCode, idDataGroup, false);
						setField(ifds::EntityAddrCode, dstrAddrCode.strip(), idDataGroup, false);
					}
					if(dstrDocType == DocType::STATEMENT )
					{
						pAccountMailing->getField(ifds::StmtAddr, dstrAddrCode, idDataGroup, false);
						setField(ifds::EntityAddrCode, dstrAddrCode.strip(), idDataGroup, false);
					}
				}		  
		  }
      }		
   }

   setupAuthorizationList(  idDataGroup );
   //set hold flag accordingly
   setDefaultHoldFlag( idDataGroup );


   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************************
SEVERITY AcctMailingOverride::setDefaultHoldFlag( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultHoldFlag" ) );

   DString fundGroup,docType,hold(NO),authorize ;
   getField(ifds::DocumentType,docType,idDataGroup,false );
   getField(ifds::FundGroup,fundGroup,idDataGroup,false );
   getField(ifds::AuthCode,authorize,idDataGroup,false );
   authorize.strip().upperCase();
   fundGroup.strip();
   docType.strip();
   if( docType != NULL_STRING && ( authorize == I_("D") ||authorize == NULL_STRING )  )
   {
	   DefaultMailOptionList* pDefaultMailOptionList = NULL;
      if( getMgmtCo().getDefaultMailOptionList( pDefaultMailOptionList ) <= WARNING )
      {
         hold = pDefaultMailOptionList->getDefaultHoldFlag(docType,fundGroup ); 
      }
   }
   setFieldNoValidate( ifds::OnHold, hold,idDataGroup,false,
                           true,true,false);             


   return GETCURRENTHIGHESTSEVERITY();
}
//*********************************************************************************
void AcctMailingOverride::setupAuthorizationList(  const BFDataGroupId& idDataGroup )
{
   //PET 1277,FN09
   //set AuthCode substitution list accordingly
   DString substList1,substList2;
   BFProperties *pProperties = getFieldProperties (ifds::Authorization, idDataGroup);
   if( pProperties )
   {
      pProperties->getAllSubstituteValues (substList1);
   }
   substList2 = substList1;
   substList1 = removeItemFromSubtList( substList1,I_("A") );
   //substList2 = removeItemFromSubtList( substList2,I_("P") );
   DString dstrDocType;
   getField(ifds::DocumentType,dstrDocType,idDataGroup,false);

   if( dstrDocType == DocType::ANNUAL_MRFP || dstrDocType == DocType::ANNUAL_REPORT ||
      dstrDocType == DocType::SEMI_ANNUAL_MRFP || dstrDocType == DocType::SEMI_ANNUAL_REPORT)
   {
      setFieldAllSubstituteValues(  ifds::AuthCode, 
                                    idDataGroup, 
                                    substList2 );                                    
   }
   else 
   {
      setFieldAllSubstituteValues( ifds::AuthCode, 
                                    idDataGroup, 
                                    substList1 );                                    
   }
}
//******************************************************************************
SEVERITY AcctMailingOverride::holdRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "holdRelatedChanges" ) );	
   setFieldNoValidate( ifds::AuthCode,NULL_STRING,idDataGroup,false,false,true,false);               
   return GETCURRENTHIGHESTSEVERITY();
}
//********************************************************************************
SEVERITY AcctMailingOverride::authorizRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "authorizRelatedChanges" ) );	
   DString authorize;
   getField(ifds::AuthCode,authorize,idDataGroup,false );
   authorize.strip().upperCase();
   if( authorize == I_("D") ) // default
   {
      setDefaultHoldFlag( idDataGroup );
   }
   else if( authorize == I_("R") ) // return mail
   {
      setFieldNoValidate( ifds::OnHold, YES,idDataGroup,false,
                           true,true,false);                
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//**********************************************************************************
SEVERITY AcctMailingOverride:: validateAuthHold( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAuthHold" ) );	
   DString authorize, hold;
   getField( ifds::AuthCode,authorize,idDataGroup,false );
   getField( ifds::OnHold,hold,idDataGroup,false );
   authorize.strip();
   hold.strip().upperCase();
   if( authorize == I_("R") && hold == NO  )
   {

		DString docDes;
		getField(ifds::DocumentType,docDes,idDataGroup,true);
		docDes.strip();
		DString idiStr;
		addIDITagValue( idiStr, I_("TYPE"), docDes );
	   ADDCONDITIONFROMFILEIDI( CND::ERR_NO_HOLD_FOR_RETURN_MAIL, idiStr.c_str() );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
inline void  AcctMailingOverride::setEntityId(const DString& entityID )
	{
		_entityID = entityID;
	}
//********************************************************************************
inline DString& AcctMailingOverride::getEntityId()
	{
		return _entityID;
	}

//******************************************************************************
void  AcctMailingOverride ::setObjectAsUpdated(const DString& docType, 
                                               const DString& fundGroup,  
                                               const BFDataGroupId& idDataGroup )
{
   DString defaultAddrCode = I_("01");
   setUpdatedFlag(ifds::DocumentType,idDataGroup,true);
	setFieldNoValidate(ifds::DocumentType,docType,idDataGroup,false);
	setFieldNoValidate(ifds::FundGroup,fundGroup,idDataGroup,false);

   MFAccount* pAcct = dynamic_cast<MFAccount* >(getParent()->getParent() );
   if( pAcct )
   {
      DString designation,taxType;
      pAcct->getField( ifds::AcctDesignation, designation,idDataGroup,false);
      designation.strip();
      pAcct->getField( ifds::TaxType, taxType,idDataGroup,false);
      taxType.strip();
      if( designation == I_("2") || designation == I_("3") )
      {
         if( docType == DocType::DIVIDEND_CONFIRM || docType == DocType::CONFIRMATION ||
            docType == DocType::STATEMENT || docType == DocType::LETTERS || 
            docType == DocType::BENEFICIAL_OWNER || docType == DocType::ANNUAL_MRFP ||
            docType == DocType::ANNUAL_REPORT ||docType == DocType::SEMI_ANNUAL_MRFP ||
            docType == DocType::SEMI_ANNUAL_REPORT || docType == DocType::PROSPECTUSES ||
            docType == DocType::NON_FINANCIAL_CONFIRM )
         {
               defaultAddrCode = I_("02");     
         }
         if( getWorkSession().isNonRegLike( taxType ) && docType == DocType::TAX_RECEIPT )
         {
               defaultAddrCode = I_("02");       
         }
      }
   }
   setFieldNoValidate(ifds::EntityAddrCode,defaultAddrCode,idDataGroup,false );

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctMailingOverride.cpp-arc  $
// 
//    Rev 1.21   06 Oct 2008 13:16:40   kovacsro
// PET142007  FN01 TFSA
// 
//    Rev 1.20   12 Sep 2008 15:40:48   kovacsro
// PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
// 
//    Rev 1.19   Apr 26 2006 12:22:00   porteanm
// Incident 605455 - Replaced error with warning  WARN_ADDRESS_CODE_NOT_EFFECTIVE.
// 
//    Rev 1.18   Oct 06 2005 11:17:42   yingbaol
// PEt1277,FN09:change default address code logic after demo
// 
//    Rev 1.17   Sep 29 2005 17:03:44   yingbaol
// PET1277,FN09: validate hold authorization at the end.
// 
//    Rev 1.16   Sep 29 2005 10:49:06   yingbaol
// PET1277-FN09: Investment Fund Continuous Disclosure
// 
//    Rev 1.15   Sep 21 2005 16:45:00   yingbaol
// PEt1277,FN09: Investment Fund Continuous Disclosure
// 
//    Rev 1.14   Mar 21 2005 09:59:08   yingbaol
// Incident252121: fix Suppress and Consent issue
// 
//    Rev 1.13   Dec 03 2004 17:18:06   yingbaol
// PET1137,FN01: fix business rules.
// 
//    Rev 1.12   Dec 02 2004 11:36:52   yingbaol
// PET1137,FN01: Add Epost functionality.
// 
//    Rev 1.11   Nov 14 2004 14:25:08   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Oct 26 2004 11:24:22   YINGBAOL
// PEt1137 FN01: add validation for CD,Mail,Email and Fax
// 
//    Rev 1.9   Oct 14 2003 15:31:54   HERNANDO
// Replaced DocumentTypeOverrideList with TranslationTable.
// 
//    Rev 1.8   Apr 21 2003 09:42:18   YINGBAOL
// populate document type by using view 254
// 
//    Rev 1.7   Apr 12 2003 15:05:00   YINGBAOL
// EntityAddrCode should be updateable
// 
//    Rev 1.6   Apr 11 2003 10:09:30   FENGYONG
// Add two crossedit field
// 
//    Rev 1.5   Apr 04 2003 16:36:36   FENGYONG
// Add validation
// 
//    Rev 1.4   Apr 03 2003 17:54:22   FENGYONG
// changeback Group type FndGrp
// 
//    Rev 1.3   Apr 03 2003 15:21:52   FENGYONG
// Maining override will always use default 01 for entity type and 1 for entity type seqence.
// 
//    Rev 1.2   Apr 02 2003 13:21:12   FENGYONG
// set default value and fundgroup type tempory set to COMM
// before data fix on testting slot
// 
//    Rev 1.1   Apr 01 2003 17:33:22   FENGYONG
// existing record have key fields read only
// 
//    Rev 1.0   Apr 01 2003 16:29:56   FENGYONG
// Initial revision.
// 
 
*/