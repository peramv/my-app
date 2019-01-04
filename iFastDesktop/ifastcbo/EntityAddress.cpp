//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : EntityAddress.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 10/06/99
//
// ^CLASS    : EntityAddress
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "entityaddress.hpp"
#include "mfaccount.hpp"
#include "addressentitylist.hpp"
#include "mgmtco.hpp"
#include "provincelist.hpp"

#include <ifastdataimpl\dse_dstc0071_vw.hpp>    // Entity Adddress Response
#include <ifastdataimpl\dse_dstc0083_vw.hpp>    // System Configuration

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME                  = I_( "EntityAddress" );
   const I_CHAR * const ACCOUNT_OWNNER             = I_( "01" );
   const I_CHAR * const FIRST_SEQ_ACCT_OWNNER      = I_( "1" );
   const I_CHAR * const YES                        = I_( "Y" );
}
 
namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFNumericFieldId SeqNumber;
	extern CLASS_IMPORT const BFTextFieldId EntityType;
    extern CLASS_IMPORT const BFTextFieldId RetMailUpdt;
}

namespace CND
{   
	// Conditions used   
	extern const long ERR_DUPLICATE_RECORD;		
	extern const long ERR_ENTITY_ADDRESS_ID_INVALID;
	extern const long ERR_COUNTRY_IS_BLANK;
	extern const long WARN_RET_MAIL_CHANGED;	
	extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
    extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //Field DD Id,             State Flags, Group Flags
   { ifds::Username,          BFCBO::NONE, 0 }, 
   { ifds::ProcessDate,       BFCBO::NONE, 0 }, 
   { ifds::ModUser,           BFCBO::NONE, 0 }, 
   { ifds::ModDate,           BFCBO::NONE, 0 }, 
   { ifds::EntityAddrVer,     BFCBO::NONE, 0 }, 
   { ifds::EntityAddrRid,     BFCBO::NONE, 0 }, 
   { ifds::EntityAddrXrefVer, BFCBO::NONE, 0 }, 
   { ifds::EntityAddrXrefRid, BFCBO::NONE, 0 }, 
   { ifds::AddrCode,          BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::AddrDesc,          BFCBO::NONE, 0 }, 
   { ifds::AddrLine1,         BFCBO::NONE, 0 }, 
   { ifds::AddrLine2,         BFCBO::NONE, 0 }, 
   { ifds::AddrLine3,         BFCBO::NONE, 0 }, 
   { ifds::City,              BFCBO::NONE, 0 }, 
   { ifds::AddrId,            BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::PostalCode,        BFCBO::NONE, 0 }, 
   { ifds::Country,           BFCBO::NONE, 0 }, 
   { ifds::HoldMail,          BFCBO::NONE, 0 }, 
   { ifds::CountryName,       BFCBO::NONE, 0 }, 
   { ifds::Province,          BFCBO::NONE, 0 }, 
   { ifds::ProvinceName,      BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate,     BFCBO::NONE, 0 },    
   { ifds::RetMailFlag,       BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::RetMailDate,       BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::RetMailReasonCode, BFCBO::NONE, 0 }, 
   { ifds::UnclmComment,      BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//********************************************************************************
EntityAddress::EntityAddress( BFAbstractCBO &parent )
: MFCanBFCbo( parent ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL );   
}

//********************************************************************************
EntityAddress::~EntityAddress()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//********************************************************************************
SEVERITY EntityAddress::init( const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(int,BFData&)" ) );
   
   attachDataObject(const_cast<BFData&>(InstData), false, true );  

   commonInit( BF::HOST );
   applyCountryCodeRelatedChanges( BF::HOST );		

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY EntityAddress::init( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(int,long)" ) );

   commonInit( idDataGroup );
      
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY EntityAddress::commonInit( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "commonInit" ) );

	setFieldAllSubstituteValues( ifds::AddrCode, idDataGroup, NULL_STRING );		

	// The key should be read only for existing records
	setFieldReadOnly( ifds::EffectiveDate, idDataGroup, idDataGroup == BF::HOST );
	setFieldReadOnly( ifds::AddrCode,      idDataGroup, idDataGroup == BF::HOST );
	setFieldReadOnly( ifds::AddrId,        idDataGroup, idDataGroup == BF::HOST );
	
    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void EntityAddress::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
	DString dstrCurrentBusinessDate;
	getWorkSession ().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false );

	setFieldNoValidate( ifds::EffectiveDate, dstrCurrentBusinessDate, idDataGroup, false, true, true, false);

	setFieldRequired (ifds::EffectiveDate, idDataGroup, true );
	setFieldRequired (ifds::AddrCode,      idDataGroup, true );
	// Address Id could be blank (and the view will assign the ID) or
	// could be an existing ID
	//setFieldRequired (ifds::AddrId,        idDataGroup, true );
	setFieldRequired (ifds::Country,       idDataGroup, true );
}

//********************************************************************************
SEVERITY EntityAddress::doValidateField( const BFFieldId& idField,
                                         const DString& strValue,
                                         const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if ( idField == ifds::AddrCode )
   {
	   DString dstrAddrCodeSubst = strValue + I_( "=" ) + strValue + I_( ";" ); 
	   setFieldAllSubstituteValues( ifds::AddrCode, idDataGroup, dstrAddrCodeSubst );	

	   AddressEntityList *pAddressEntityList = dynamic_cast<AddressEntityList*>( getParent( ) );      
	   if ( NULL != pAddressEntityList && hasNonHostUpdates( ) )
	   {
			// we'll have one unique record for each address code. 	
			if ( pAddressEntityList->isDuplicateEntityAddress( this, idDataGroup ) )
						ADDCONDITIONFROMFILE( CND::ERR_DUPLICATE_RECORD );			    
	   }
   }      
   if( idField == ifds::AddrId )
   {
	   _dstrAddrLine1 = I_( "" );
	   _dstrAddrLine2 = I_( "" );
	   _dstrAddrLine3 = I_( "" );
	   _dstrCity      = I_( "" ); 
	   _dstrPostal    = I_( "" ); 
	   _dstrHoldMail  = I_( "" ); 
	   _dstrCountry   = I_( "" ); 
	   _dstrProvince  = I_( "" ); 	   

	   // Make sure is an existing Address
	   // Entity Address ID can be 0 or a valid existing Address ID.
	   if ( isNew() && strValue != I_( "0" ) && !strValue.empty() )
	   {
		   AddressEntityList *pAddressEntityList = new AddressEntityList (*this);   
		   if ( pAddressEntityList->initSearch( I_( "AddrID" ), 
				                                I_( "" ), 
						      	  			    I_( "" ), 
												strValue, 
												I_( "" ), 
												I_( "" ),
												I_( "N" ),
												NULL_STRING,
												false ) > WARNING )
			{
				ADDCONDITIONFROMFILE( CND::ERR_ENTITY_ADDRESS_ID_INVALID );
			}			
		   else
		   {				
			    bool bHasRecords = false;
				BFObjIter iter( *pAddressEntityList, idDataGroup );
				while( !iter.end() )
				{
					bHasRecords = true;
					EntityAddress *pEntityAddress = dynamic_cast <EntityAddress*>( iter.getObject());
					if( pEntityAddress )
					{
						pEntityAddress->getField( ifds::AddrLine1,  _dstrAddrLine1, idDataGroup );
						pEntityAddress->getField( ifds::AddrLine2,  _dstrAddrLine2, idDataGroup );
						pEntityAddress->getField( ifds::AddrLine3,  _dstrAddrLine3, idDataGroup );
						pEntityAddress->getField( ifds::City,       _dstrCity,      idDataGroup );
						pEntityAddress->getField( ifds::PostalCode, _dstrPostal,    idDataGroup );
						pEntityAddress->getField( ifds::HoldMail,   _dstrHoldMail,  idDataGroup );
						pEntityAddress->getField( ifds::Country,    _dstrCountry,   idDataGroup );
						pEntityAddress->getField( ifds::Province,   _dstrProvince,  idDataGroup );												
													
						break;						
					}
					++iter;
				}

				if ( !bHasRecords )
					ADDCONDITIONFROMFILE( CND::ERR_ENTITY_ADDRESS_ID_INVALID );
		   }
	   }
   }
   else if ( idField == ifds::Province )
   {
		DString dstrCountry;
		getField( ifds::Country, dstrCountry, idDataGroup );

		if (dstrCountry == NULL_STRING)
		{
			ADDCONDITIONFROMFILE( CND::ERR_COUNTRY_IS_BLANK);
		}
		else
		{
			DString dstrProvinceListSubstSet;
			ProvinceList *pProvinceList = NULL;
			if ( getMgmtCo().getProvinceList( dstrCountry, pProvinceList ) <= WARNING && 
				NULL != pProvinceList )
			{		
				pProvinceList->getProvinceSubstitutionSet( dstrProvinceListSubstSet, BF::HOST );
			}
		
			if ( dstrProvinceListSubstSet.empty() )
			{
				DString dstrProvinceSubst = strValue + I_( "=" ) + strValue + I_( ";" ); 
				setFieldAllSubstituteValues( ifds::Province, idDataGroup, dstrProvinceSubst );				
			}
		}
   }
   else if( idField == ifds::HoldMail )
   {
      DString oldRetMail;
      DString retMail( strValue );
      retMail.strip().upperCase();
      getField( ifds::HoldMail,oldRetMail,BF::HOST,false);
      oldRetMail.strip().upperCase();
      if( oldRetMail != retMail )
      {
         ADDCONDITIONFROMFILE (CND::WARN_RET_MAIL_CHANGED);               
      }    
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************
SEVERITY EntityAddress::doValidateAll(const BFDataGroupId &idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

	DString dstrAccountNum;
	getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	dstrAccountNum.strip ().stripLeading ('0');
	MFAccount *pMFAccount = NULL;
	if (!isNew() && isUpdatedForDataGroup (idDataGroup)
		&& getWorkSession().getMFAccount (idDataGroup, dstrAccountNum,
		pMFAccount) <= WARNING && pMFAccount)
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


//******************************************************************************
SEVERITY EntityAddress::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if( idField == ifds::AddrId )
   {
		// populate Address, City, Postal Code, Country based on Address Id
		DString dstrAddressId;
		getField( ifds::AddrId, dstrAddressId, idDataGroup );
		if ( isNew() && dstrAddressId != I_( "0" ) )
		{
			setFieldNoValidate( ifds::AddrLine1,  _dstrAddrLine1, idDataGroup );
			setFieldNoValidate( ifds::AddrLine2,  _dstrAddrLine2, idDataGroup );
			setFieldNoValidate( ifds::AddrLine3,  _dstrAddrLine3, idDataGroup );
			setFieldNoValidate( ifds::City,       _dstrCity,      idDataGroup );
			setFieldNoValidate( ifds::PostalCode, _dstrPostal,    idDataGroup );
			setFieldNoValidate( ifds::HoldMail,   _dstrHoldMail,  idDataGroup );			
			setFieldNoValidate( ifds::Country,    _dstrCountry,   idDataGroup );
			applyCountryCodeRelatedChanges( idDataGroup );
			setFieldNoValidate( ifds::Province,   _dstrProvince,  idDataGroup );			
		}
   }
   if( idField == ifds::Country )
   {
	   setFieldNoValidate( ifds::Province, I_( "" ), idDataGroup );
	   applyCountryCodeRelatedChanges( idDataGroup );		
   }
   else if (idField == ifds::RetMailFlag)
   {
      DString retMailFlag;
	  /* Copy logic concept from Address.cpp */
      getField(ifds::RetMailFlag, retMailFlag, idDataGroup, false);
      retMailFlag.stripAll().upperCase();
      DString strOldRetMailFlag;
      getFieldBeforeImage (ifds::RetMailFlag, strOldRetMailFlag);

      if (retMailFlag == I_("N"))
      {
         setFieldNoValidate (ifds::RetMailDate, NULL_STRING, idDataGroup);
         setFieldReadOnly (ifds::RetMailDate, idDataGroup, true);
         setFieldRequired (ifds::RetMailDate, idDataGroup, false);
         setFieldNoValidate (ifds::RetMailReasonCode, I_(""), idDataGroup, false, false, true, true);		 
         setFieldNoValidate (ifds::UnclmComment,  I_(""),idDataGroup, false, false, true, true);
	  }
	  else
	  {

		 DString dstrCurrentBusinessDate;
		 getWorkSession ().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false );
		 setFieldNoValidate (ifds::RetMailDate, dstrCurrentBusinessDate, idDataGroup, false, false, true, true);

		 // Yes
         setFieldReadOnly (ifds::RetMailDate, idDataGroup, false);
         setFieldRequired (ifds::RetMailDate, idDataGroup, true);
         setFieldNoValidate (ifds::RetMailReasonCode, I_("UN"), idDataGroup, false, false, true, true);		 
	  
	  }

      DString dstrRetMailUpdt;
      getWorkSession().getOption(ifds::RetMailUpdt, dstrRetMailUpdt, BF::HOST, false);

      if (dstrRetMailUpdt == YES)
      {
          updateMailingInfoByRetmailForAddrCode(retMailFlag, idDataGroup);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY EntityAddress::applyCountryCodeRelatedChanges( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "applyCountryCodeRelatedChanges" ) );

	// populate Province List based on Country Code
	DString dstrCountry;
	getField( ifds::Country, dstrCountry, idDataGroup );

	DString dstrProvinceListSubstSet;
	if ( !dstrCountry.strip().empty() )
	{		
		ProvinceList *pProvinceList = NULL;
		if ( getMgmtCo().getProvinceList( dstrCountry, pProvinceList ) <= WARNING && 
			NULL != pProvinceList )
		{		
			pProvinceList->getProvinceSubstitutionSet( dstrProvinceListSubstSet, BF::HOST );		
		}
	}

	setFieldAllSubstituteValues (ifds::Province, idDataGroup, dstrProvinceListSubstSet );

	return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY EntityAddress::getFormattedAddress(DString& dstrAddress, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFormattedAddress"));

   DString dstrAddrField;
   getField(ifds::AddrLine1, dstrAddrField, idDataGroup);  
   dstrAddress = dstrAddrField.strip();

   getField(ifds::AddrLine2, dstrAddrField, idDataGroup);  
   dstrAddrField.strip();
   if(dstrAddrField.strip() != I_(""))
      dstrAddress += (I_("\r\n") + dstrAddrField);

   getField(ifds::AddrLine3, dstrAddrField, idDataGroup);  
   dstrAddrField.strip();
   if(dstrAddrField.strip() != I_(""))
      dstrAddress += (I_("\r\n") + dstrAddrField);

   getField(ifds::City, dstrAddrField, idDataGroup);  
   dstrAddrField.strip();
   if(dstrAddrField.strip() != I_(""))
      dstrAddress += (I_("\r\n") + dstrAddrField);

   DString dstrProvince;
   DString dstrPostalCode;
   DString dstrCountry;

   getField(ifds::Province,   dstrProvince,   idDataGroup);  
   getField(ifds::PostalCode, dstrPostalCode, idDataGroup);  
   getField(ifds::Country,    dstrCountry,    idDataGroup);  

   dstrAddrField = dstrProvince + I_(" ") + dstrPostalCode + I_(" ") + dstrCountry;
   if(dstrAddrField.strip() != I_(""))
      dstrAddress += (I_("\r\n") + dstrAddrField);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool EntityAddress::isFirstShareholder(const BFDataGroupId& idDataGroup)
{
	DString dstrSeqNumber, dstrEntityType;

	getParent()->getField(ifds::EntityType, dstrEntityType, idDataGroup);
	getParent()->getField(ifds::SeqNumber, dstrSeqNumber, idDataGroup);
	
	return (dstrEntityType == ACCOUNT_OWNNER && dstrSeqNumber == FIRST_SEQ_ACCT_OWNNER);
}


//******************************************************************************
SEVERITY EntityAddress::updateMailingInfoByRetmailForAddrCode(const DString &dstrHoldFlag, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("updateMailingInfoByRetmailForAddrCode"));

	if (!isFirstShareholder(idDataGroup))
	{
		setFieldNoValidate(ifds::HoldMail, dstrHoldFlag, idDataGroup, false, false, true, true);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityAddress.cpp-arc  $
 * 
 *    Rev 1.22   Oct 10 2007 14:44:06   jankovii
 * IN 837879 - Canadian Resident with Foreign Address - Country Code 0015.
 * 
 *    Rev 1.21   Sep 21 2005 16:46:04   yingbaol
 * PET1277,FN09 Investment Fund Continious Disclosure
 * 
 *    Rev 1.20   May 30 2005 15:40:10   porteanm
 * Incident 252121 - Call province list if country code is not empty.
 * 
 *    Rev 1.19   Mar 15 2005 11:21:12   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.18   Mar 15 2005 11:05:14   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
 * 
 *    Rev 1.17   Mar 14 2005 16:30:04   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.16   Mar 10 2005 16:38:28   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.15   Mar 08 2005 17:08:32   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.14   Mar 08 2005 14:32:24   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.13   Mar 02 2005 16:43:14   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
 * 
 *    Rev 1.12   Nov 14 2004 14:36:32   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.11   Mar 21 2003 18:07:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:54:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:55:44   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   Jul 09 2002 11:47:48   YINGBAOL
 * override getfield
 * 
 *    Rev 1.7   22 May 2002 18:28:30   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   03 May 2001 14:06:24   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Mar 29 2001 15:58:50   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.4   Feb 12 2001 14:59:50   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.3   Dec 17 2000 20:23:16   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.2   Sep 23 2000 11:02:12   YINGBAOL
 * set EntityAddress readonly
 * 
 *    Rev 1.1   Feb 15 2000 18:57:44   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:58   SMITHDAV
 * Initial revision.
// 
//    Rev 1.6   Feb 03 2000 10:51:04   BUZILA
// INIT_TO_DEFAULT flag took out
// 
//    Rev 1.5   Jan 21 2000 16:44:34   YINGBAOL
// change the way access other list
// 
//    Rev 1.4   Dec 13 1999 10:43:00   YINGBAOL
// 
//    Rev 1.3   Dec 10 1999 11:50:44   YINGBAOL
// added validation
*/



