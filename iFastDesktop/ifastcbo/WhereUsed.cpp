//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : WhereUsed.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : WhereUsed
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "whereused.hpp"
#include "whereusedlist.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "fundsponsorslist.hpp"
#include "entity.hpp"
#include "entityidslist.hpp"
#include <ifastdataimpl\dse_dstc0061_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME                     = I_( "WhereUsed" );   
   // Where Use Type (WhereUsed)
   const I_CHAR * const FUNDBROKER                    = I_( "01" );
   const I_CHAR * const ACCOUNT                       = I_( "02" );
   const I_CHAR * const CLIENT                        = I_( "03" );
   const I_CHAR * const FUND                          = I_( "04" );
   const I_CHAR * const FUNDSPONSOR                   = I_( "05" );
   const I_CHAR * const HOLDINGCMP                    = I_( "06" );
   const I_CHAR * const COUNTRY                       = I_( "11" );
   const I_CHAR * const EXTERNAL_PRODUCT_PROVIDER     = I_( "12" );
   const I_CHAR * const LEGAL_ENTITY                  = I_( "15" );

   // Relationship (EntityType)
   const I_CHAR * const PRIMARY_CONTACT               = I_( "02" );
   const I_CHAR * const PAYING_AGENT                  = I_( "04" );
   const I_CHAR * const NETWORK_SENDER                = I_( "06" );
   //const I_CHAR * const GOVT_STATIC_DATA            = I_( "08" );

   // TA Automated Fund Transfer
   const I_CHAR * const FUND_CUSTODIAN                = I_( "12" );
   const I_CHAR * const FUND_ACCOUNTANT               = I_( "13" );
   const I_CHAR * const REG_AGENT                     = I_( "14"); 
}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_FUND;
   extern const long ERR_WHERE_USE_TYPE_ACCOUNT_INVALID;
   extern const long ERR_WHERE_USE_TYPE_FUND_BROKER_INVALID;
   extern const long ERR_WHERE_USE_TYPE_FUND_INVALID;
   extern const long ERR_DATE_NUST_BEFORE_CURRBUSDATE;
   extern const long ERR_EFF_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
   extern const long ERR_INVALID_GROUP_CODE;
   extern const long ERR_INVALID_FS_RELATIONSHIP;
   extern const long ERR_RELATIONSHIP_IDVALUE_NOT_CONSISTENT;
   extern const long ERR_FIELD_IS_BLANK;
   extern const long ERR_USER_DOES_NOT_HAVE_PERMISSION_TO_ADD_EPP;
   extern const long ERR_REG_AGENT_TAX_TYPE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId EntityWhereUseRelationship;
   extern CLASS_IMPORT const BFTextFieldId GoodBad;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFTextFieldId WhereUsedXEdit;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId CountryCode;
   extern CLASS_IMPORT const BFTextFieldId IdType;
   extern CLASS_IMPORT const BFTextFieldId IdValue;
   extern CLASS_IMPORT const BFTextFieldId WhereUseTaxType;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const EXTERNAL_PROVIDER_UPDATE;
}

namespace IDS
{
   extern const I_CHAR * const FUND_ACCOUNTANT;
   extern const I_CHAR * const FUND_CUSTODIAN;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   // Field DD Id,                     State Flags,                 Group Flags 
   { ifds::WhereUse,                   BFCBO::NONE,                 0 },
   { ifds::EntityType,                 BFCBO::NONE,                 0 },
   { ifds::EntityWhereUseRelationship, BFCBO::NONE,                 0 },
   { ifds::WhereUseCode,               BFCBO::NONE,                 0 },
   { ifds::EntityId,                   BFCBO::NONE,                 0 },
   { ifds::WhereUsedXEdit,             BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::StopDate,                   BFCBO::NONE,                 0 },
   { ifds::EffectiveDate,              BFCBO::NONE,                 0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//****************************************************************************
// Constructor
//****************************************************************************
WhereUsed::WhereUsed( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );

   addCrossEdit(ifds::WhereUsedXEdit, ifds::WhereUse );
   addCrossEdit(ifds::WhereUsedXEdit, ifds::WhereUseCode );
   addCrossEdit(ifds::WhereUsedXEdit, ifds::EntityType );
   addCrossEdit(ifds::WhereUsedXEdit, ifds::EffectiveDate );
   addCrossEdit(ifds::WhereUsedXEdit, ifds::StopDate );
}

//****************************************************************************
// Destructor
//****************************************************************************
WhereUsed::~WhereUsed()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
//Initializes the CBO
//@param const BFData& InstData - Data object to attach to WhereUsedList.
//@returns SEVERITY
//****************************************************************************
SEVERITY WhereUsed::init( const DString& entityId, const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( const BFData& InstData )" ) );
   attachDataObject( const_cast<BFData&>(InstData), false, true );
   setFieldNoValidate (ifds::EntityId, entityId, BF::HOST, true); 
   CommInit(&InstData,BF::HOST);
   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************************************
void  WhereUsed::CommInit(const BFData* pData,const BFDataGroupId& idDataGroup)
{
   DString whereUsed, dstrRelationship;
   bool  bWhereUseKeyMandatroy = false;
   bool  bDatesMandatory = false;
   bool  bEffDatesMandatory = false;
   bool  bFundSponsorMandatoryFields = false;

   Entity* pEntity = dynamic_cast<Entity* >( getParent()->getParent() );

   if( pData )
   {
      pData->getElementValue(ifds::WhereUse, whereUsed);
   }
   else 
   {
      getField(ifds::WhereUse,whereUsed,idDataGroup);   
   }

   whereUsed.strip();

   if ( whereUsed == FUNDBROKER)
   {
      setFieldSubstituteValues( ifds::EntityType, BF::HOST, ifds::EntityWhereUseRelationship);
      setFieldReadOnly( ifds::WhereUseCode, idDataGroup, true );
   }
   else if( whereUsed == CLIENT )
   {
      DString subSet;

      BFProperties *pProp = getFieldProperties (ifds::EntityWhereUseRelationship, idDataGroup);
      assert (pProp);
      if (pProp)
      {
         pProp->getAllSubstituteValues (subSet);
         int iPos = subSet.find_first_of(I_(";"));
         subSet = subSet.right(subSet.length() - iPos  - 1);
         setFieldAllSubstituteValues( ifds::EntityType, idDataGroup, subSet ); 
      }   

      if (!isNew ())
      {
         pData->getElementValue(ifds::EntityType, dstrRelationship);
         dstrRelationship.strip();
         bDatesMandatory = dstrRelationship == PAYING_AGENT ? true : false;
      }

      setFieldReadOnly( ifds::WhereUseCode, idDataGroup, true );
   }
   else if( whereUsed == FUND )
   {
      pData->getElementValue(ifds::EntityType, dstrRelationship);
      dstrRelationship.strip();

      bool bReadOnly = dstrRelationship == PAYING_AGENT ? false : true;
      bWhereUseKeyMandatroy = !bReadOnly;
      bDatesMandatory = bWhereUseKeyMandatroy;

      setFieldSubstituteValues( ifds::EntityType, BF::HOST, ifds::EntityWhereUseRelationship);
      setFieldReadOnly( ifds::WhereUseCode, idDataGroup, bReadOnly );
   }
   else if( whereUsed == FUNDSPONSOR )
   {
      pData->getElementValue(ifds::EntityType, dstrRelationship);
      dstrRelationship.strip();

      bool bReadOnly = false;
      bWhereUseKeyMandatroy = false;
      bDatesMandatory = false;

      setFieldSubstituteValues( ifds::EntityType, BF::HOST, ifds::EntityWhereUseRelationship);
      setFieldReadOnly( ifds::WhereUseCode, idDataGroup, bReadOnly );
   }
   else if (whereUsed == HOLDINGCMP)
   {
      bool bReadOnly = false;
      bWhereUseKeyMandatroy = false;
      bDatesMandatory = false;

      setFieldSubstituteValues( ifds::EntityType, BF::HOST, ifds::EntityWhereUseRelationship);
      setFieldReadOnly( ifds::WhereUseCode, idDataGroup, bReadOnly ); 
   }
   else if ( whereUsed == EXTERNAL_PRODUCT_PROVIDER)
   {
      setFieldSubstituteValues( ifds::EntityType, BF::HOST, ifds::EntityWhereUseRelationship);
      setFieldReadOnly( ifds::WhereUseCode, idDataGroup, true );
   }
   else if ( whereUsed == COUNTRY )
   {
      setFieldSubstituteValues( ifds::WhereUseCode, BF::HOST, ifds::CountryCode );
      //setFieldSubstituteValues( ifds::EntityType, BF::HOST, ifds::EntityWhereUseRelationship);
      setFieldReadOnly ( ifds::WhereUseCode, BF::HOST, false );
      setFieldReadOnly ( ifds::EntityType, BF::HOST, true ); 
   }
   else if( whereUsed == REG_AGENT )
   {
	   bWhereUseKeyMandatroy = true;
	   setFieldSubstituteValues( ifds::EntityType, idDataGroup, ifds::WhereUseTaxType);
	   setFieldReadOnly( ifds::WhereUseCode, idDataGroup, false );
	   setFieldRequired(ifds::WhereUseCode,idDataGroup,bWhereUseKeyMandatroy);
	   setFieldValid (ifds::WhereUseCode, idDataGroup,!bWhereUseKeyMandatroy); 
   }
   else if( whereUsed == LEGAL_ENTITY )
   {
      bWhereUseKeyMandatroy = true;
      bEffDatesMandatory = true;
      setFieldReadOnly( ifds::WhereUseCode, idDataGroup, false );
      setFieldSubstituteValues( ifds::EntityType, idDataGroup, ifds::EntityWhereUseRelationship );
      setFieldSubstituteValues( ifds::WhereUseCode, idDataGroup, ifds::NullFieldId );
   }
   else
   {
      setFieldReadOnly ( ifds::EntityType, BF::HOST, false ); 
      setFieldSubstituteValues( ifds::EntityType, BF::HOST, ifds::EntityType );
      setFieldSubstituteValues( ifds::WhereUseCode, BF::HOST, ifds::NullFieldId );
   }

   setFieldRequired (ifds::WhereUseCode, idDataGroup, bWhereUseKeyMandatroy);
   setFieldRequired (ifds::EffectiveDate, idDataGroup, bDatesMandatory || bEffDatesMandatory);
   setFieldRequired (ifds::StopDate, idDataGroup, bDatesMandatory);

   if(pEntity) 
      pEntity->setFundSponsorMandatoryFields (idDataGroup);

   setAllFieldsReadOnlyforAccountRelated( BF::HOST );
}

//*****************************************************************************
SEVERITY WhereUsed::initNew(const DString &entityId, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );
   setFieldNoValidate (ifds::EntityId, entityId, idDataGroup, true); 
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
void WhereUsed::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   if( Entity::bUsedByEntityAlone )
   {
      setFieldNoValidate (ifds::WhereUse, I_("03"), idDataGroup, true); // Where use set to client for new Where use
      setFieldRequired(ifds::EntityType, idDataGroup, true);
      setValidFlag(ifds::EntityType, idDataGroup, false);
   }

   DString dstrStopDate,  dstrCurrBusDate;

   getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
   getWorkSession().getDateInHostFormat(dstrStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);

   setFieldNoValidate( ifds::EffectiveDate, dstrCurrBusDate, idDataGroup );
   setFieldNoValidate( ifds::StopDate, dstrStopDate, idDataGroup, false, true, true );   

   CommInit(NULL,idDataGroup);
}

//********************************************************************************
void WhereUsed::setAllFieldsReadOnlyforAccountRelated( const BFDataGroupId& idDataGroup )
{
   DString dstrRelationship, dstrWhereUse;
   bool bWhereUseCodeReadOnly = false;
   bool bDatesReadOnly =  false;
   bool bEffDatesReadOnly = true;
   bool bReadOnly = false;
   DString status; 
   Entity* pEntity = dynamic_cast<Entity* >( getParent()->getParent() );

   if(pEntity )
   {
      pEntity->getField(ifds::GoodBad, status,BF::HOST,false );
      status.strip().upperCase();
      bReadOnly |=  status == I_("N");
   }

   if (bReadOnly)
   {
      bWhereUseCodeReadOnly = true;
      bDatesReadOnly =  true;
   }
   else
   {
      getField(ifds::EntityType,dstrRelationship,idDataGroup );
      getField(ifds::WhereUse,dstrWhereUse,idDataGroup );

      dstrRelationship.strip ();
      dstrWhereUse.strip ();

      bReadOnly = dstrWhereUse == FUNDBROKER || dstrWhereUse == ACCOUNT ? true : false;

      if (dstrWhereUse == FUND)
         bWhereUseCodeReadOnly = dstrRelationship == PAYING_AGENT ? false : true;
      else if (dstrWhereUse == FUNDSPONSOR)
         bWhereUseCodeReadOnly = false;
      else if (dstrWhereUse == COUNTRY )
         //bWhereUseCodeReadOnly = dstrRelationship == GOVT_STATIC_DATA ? false : true;
         bWhereUseCodeReadOnly = true;

      if((dstrWhereUse == FUND || dstrWhereUse == CLIENT) && dstrRelationship == PAYING_AGENT)
      {
         bDatesReadOnly = false;
      }
      else if (dstrWhereUse == LEGAL_ENTITY)
      {
         bEffDatesReadOnly = false;
      }
      else
      {
         bDatesReadOnly = true;
      }
      
   }

   setFieldReadOnly( ifds::StopDate, idDataGroup, bDatesReadOnly );
   setFieldReadOnly( ifds::EffectiveDate, idDataGroup, bDatesReadOnly && bEffDatesReadOnly);
   setFieldReadOnly( ifds::WhereUseCode, idDataGroup, bWhereUseCodeReadOnly );
   setFieldReadOnly( ifds::WhereUse, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::EntityType, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::EntityWhereUseRelationship, idDataGroup, bReadOnly );
}

//******************************************************************************
SEVERITY WhereUsed::doValidateField ( const BFFieldId& idField,  
                                      const DString& strValue, 
                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if ( ifds::WhereUse == idField )
   {
      if (strValue == ACCOUNT)
      {
         ADDCONDITIONFROMFILE ( CND::ERR_WHERE_USE_TYPE_ACCOUNT_INVALID );
      }
      else if (strValue == FUNDBROKER)
      {
         ADDCONDITIONFROMFILE( CND::ERR_WHERE_USE_TYPE_FUND_BROKER_INVALID );
      }
      else if (strValue == FUND)
      {
         DString dstrRelationship;

         getField(ifds::EntityType,dstrRelationship,idDataGroup );

         if (dstrRelationship == NETWORK_SENDER)
            ADDCONDITIONFROMFILE( CND::ERR_WHERE_USE_TYPE_FUND_INVALID );
      }
      else if (strValue == FUNDSPONSOR)
      {
         WhereUsedList *pWhereUsedList = dynamic_cast<WhereUsedList*>( getParent( ) );      

         if (pWhereUsedList)
         {
            pWhereUsedList->validateFundSponsor (idDataGroup);
         }
      }
      else if (strValue == EXTERNAL_PRODUCT_PROVIDER)
      {
         if (!getWorkSession().hasUpdatePermission (UAF::EXTERNAL_PROVIDER_UPDATE))
         {
            ADDCONDITIONFROMFILE (CND::ERR_USER_DOES_NOT_HAVE_PERMISSION_TO_ADD_EPP);
         }
      }
   }
   else if (idField == ifds::EntityType)
   {
      DString dstrWhereUse;
      getField (ifds::WhereUse, dstrWhereUse,idDataGroup );

      if (dstrWhereUse != CLIENT && strValue == NETWORK_SENDER )
      {
         ADDCONDITIONFROMFILE( CND::ERR_WHERE_USE_TYPE_FUND_INVALID );
      }
      else if (dstrWhereUse == FUNDSPONSOR )
      {
         if ( strValue != PRIMARY_CONTACT && 
              strValue != FUND_ACCOUNTANT &&
              strValue != FUND_CUSTODIAN )
         {
            ADDCONDITIONFROMFILE (CND:: ERR_INVALID_FS_RELATIONSHIP);
         }
      }
      else if (dstrWhereUse == REG_AGENT)
      {
         if (strValue == NULL_STRING)
         {
            ADDCONDITIONFROMFILE(CND::ERR_REG_AGENT_TAX_TYPE);
         }
      }

      if (strValue == NETWORK_SENDER)
      {
         Entity* entity = dynamic_cast<Entity* >( getParent()->getParent() );

         entity->validateBICCode (idDataGroup);
      }
   }
   else if (idField == ifds::EffectiveDate)
   {
      DString dstrEffectiveDate, 
         dstrStopDate,
         dstrCurrBussinesDate;

      getField(ifds::EffectiveDate,dstrEffectiveDate,idDataGroup );
      getField(ifds::StopDate,dstrStopDate,idDataGroup );
      getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBussinesDate, idDataGroup, false);

      if (DSTCommonFunctions::CompareDates (dstrEffectiveDate, dstrStopDate) == DSTCommonFunctions::FIRST_EARLIER)
      {
         if (!isNew ())
         {
            if( DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrCurrBussinesDate) == DSTCommonFunctions::SECOND_EARLIER)
            {
               ADDCONDITIONFROMFILE(CND::ERR_DATE_NUST_BEFORE_CURRBUSDATE);
            }
         }
      }
      else
      {
         ADDCONDITIONFROMFILE(CND::ERR_EFF_DATE_LATE_THAN_STOP_DATE);
      }
   }
   else if (idField == ifds::StopDate)
   {
      DString dstrEffectiveDate, 
         dstrStopDate;

      getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
      getField (ifds::StopDate, dstrStopDate, idDataGroup );

      if (DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrStopDate )  == DSTCommonFunctions::SECOND_EARLIER)
      {
         ADDCONDITIONFROMFILE(CND::ERR_STOP_DATE_LESS_THAN_DEFF);
      }
   }
   else if (idField == ifds::WhereUsedXEdit)
   {
      // Duplicate check
      if (isUpdatedForDataGroup (idDataGroup, true))
      {
         WhereUsedList *pWhereUsedList = dynamic_cast<WhereUsedList*>( getParent( ) );      

         if (pWhereUsedList)
         {
            pWhereUsedList->checkDuplicate( this, idDataGroup );
         }
      }
   }
   else if (idField == ifds::WhereUseCode)
   {
      DString dstrRelationship, 
              dstrWhereUse;

      getField (ifds::WhereUse, dstrWhereUse,idDataGroup );
      getField (ifds::EntityType, dstrRelationship, idDataGroup);

      if (dstrRelationship == PAYING_AGENT && dstrWhereUse == FUND)
      {
         FundMasterList* pFundMasterList;
         getMgmtCo().getFundMasterList (pFundMasterList);
         if (pFundMasterList && !strValue.empty())
         {
            if (!pFundMasterList->IsFundExist (strValue, idDataGroup))
            {
               ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND);
            }
         }
      }
      else if ( dstrWhereUse == FUNDSPONSOR)
      {
         if ( dstrRelationship == PRIMARY_CONTACT || 
              dstrRelationship == FUND_ACCOUNTANT ||
              dstrRelationship == FUND_CUSTODIAN )
         {
            FundSponsorsList *pFundSponsorsList;
            if (getMgmtCo().getFundSponsorsList (pFundSponsorsList) <= WARNING && pFundSponsorsList)
            {
               BFAbstractCBO *pFundSponsor = NULL;

               pFundSponsorsList->getFundSponsor (strValue, pFundSponsor);

               if (pFundSponsor == NULL)
                  ADDCONDITIONFROMFILE (CND::ERR_INVALID_GROUP_CODE);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY WhereUsed::doApplyRelatedChanges( const BFFieldId &idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   Entity* pEntity = dynamic_cast<Entity* >( getParent()->getParent() );
   if(pEntity )
   {
      DString status;
      pEntity->getField(ifds::GoodBad, status,BF::HOST,false );
      status.strip().upperCase();
      if (status == I_("N"))
      {
         setAllFieldsReadOnlyforAccountRelated (idDataGroup);
         return GETCURRENTHIGHESTSEVERITY();
      }
   }

   if (idField == ifds::EntityType || idField == ifds::WhereUse)
   {
      DString dstrRelationship, dstrWhereUse;

      getField (ifds::WhereUse, dstrWhereUse, idDataGroup);

      bool bEffDatesReadOnly = true;

      if ( dstrWhereUse == FUNDBROKER     ||
           dstrWhereUse == CLIENT         ||
           dstrWhereUse == FUND           ||
           dstrWhereUse == FUNDSPONSOR    ||
           dstrWhereUse == HOLDINGCMP     ||
           dstrWhereUse == LEGAL_ENTITY   ||
           dstrWhereUse == EXTERNAL_PRODUCT_PROVIDER)
      {
         setFieldSubstituteValues( ifds::EntityType, idDataGroup, ifds::EntityWhereUseRelationship);
      }
      else if( dstrWhereUse == REG_AGENT)
      {      
         setFieldSubstituteValues( ifds::EntityType, idDataGroup, ifds::WhereUseTaxType);	  				
      }
      else
      {
         setFieldSubstituteValues( ifds::EntityType, BF::HOST, ifds::EntityType );
      }

      getField (ifds::EntityType, dstrRelationship, idDataGroup);

      bool bWhereUseCodeReadOnly = true;

      if (dstrWhereUse == FUND)
      {
         bWhereUseCodeReadOnly = dstrRelationship == PAYING_AGENT ? false : true;
      }
      else if (dstrWhereUse == FUNDSPONSOR)
      {
         if ( dstrRelationship == PRIMARY_CONTACT || 
              dstrRelationship == FUND_ACCOUNTANT ||
              dstrRelationship == FUND_CUSTODIAN )
         {
            bWhereUseCodeReadOnly = false;
         }
         else
         {
            bWhereUseCodeReadOnly = true;
         }
      }
      else if (dstrWhereUse == HOLDINGCMP)
      {
         bWhereUseCodeReadOnly = false;
      }
      else if (dstrWhereUse == EXTERNAL_PRODUCT_PROVIDER)
      {
         bWhereUseCodeReadOnly = true;
      }
      else if (dstrWhereUse == COUNTRY)
      {
         //bWhereUseCodeReadOnly = dstrRelationship == GOVT_STATIC_DATA ? false : true;
         //setFieldSubstituteValues( ifds::EntityType, idDataGroup, ifds::EntityWhereUseRelationship);
         bWhereUseCodeReadOnly = true;
      }
      else if (dstrWhereUse == REG_AGENT)
      {
         bWhereUseCodeReadOnly = false;
         setFieldReadOnly (ifds::EntityType, idDataGroup, false ); 
         setFieldRequired (ifds::EntityType, idDataGroup, true );
         if(isNew()) 
            setFieldNoValidate (ifds::EntityType, NULL_STRING, BF::HOST, true);		
      }
      else if (dstrWhereUse == LEGAL_ENTITY)
      {
         bWhereUseCodeReadOnly = false;
         bEffDatesReadOnly = false;
      }

      bool bDatesReadOnly = true;
      
      if((dstrWhereUse == FUND || dstrWhereUse == CLIENT) && dstrRelationship == PAYING_AGENT)
      {
         bDatesReadOnly = false;
         bEffDatesReadOnly = false;
      }

      setFieldReadOnly (ifds::WhereUseCode, idDataGroup, bWhereUseCodeReadOnly); 
      setFieldRequired (ifds::WhereUseCode, idDataGroup, !bWhereUseCodeReadOnly);
      setFieldValid (ifds::WhereUseCode, idDataGroup, bWhereUseCodeReadOnly); 
      setFieldReadOnly (ifds::EffectiveDate, idDataGroup, bDatesReadOnly && bEffDatesReadOnly); 
      setFieldReadOnly (ifds::StopDate, idDataGroup, bDatesReadOnly ); 

      if(pEntity) 
         pEntity->setFundSponsorMandatoryFields (idDataGroup);

      if ( dstrRelationship != PAYING_AGENT || dstrWhereUse != FUND  || dstrWhereUse != FUNDSPONSOR ||  dstrWhereUse != REG_AGENT)
      {
         if ( dstrWhereUse == COUNTRY )
         {
            setFieldSubstituteValues ( ifds::WhereUseCode, idDataGroup, ifds::CountryCode );
            //setFieldSubstituteValues( ifds::EntityType, idDataGroup, ifds::EntityWhereUseRelationship);
            setFieldReadOnly (ifds::WhereUseCode, idDataGroup, false ); 
            setFieldRequired (ifds::WhereUseCode, idDataGroup, true );
            setFieldReadOnly (ifds::EntityType, idDataGroup, true ); 
            setFieldRequired (ifds::EntityType, idDataGroup, false );
         }
         else
         {
            setFieldSubstituteValues ( ifds::WhereUseCode, idDataGroup, ifds::NullFieldId );
            setFieldReadOnly (ifds::EntityType, idDataGroup, false ); 
            setFieldRequired (ifds::EntityType, idDataGroup, true );
         }

         if (isNew())
         {
            setFieldNoValidate( ifds::WhereUseCode, I_( "" ), idDataGroup, false, false, true, true );
         }
         else
         { 
            DString dstrBefRelationship, dstrBefWhereUse;

            getFieldBeforeImage( ifds::EntityType, dstrBefRelationship );
            getFieldBeforeImage( ifds::WhereUse,   dstrBefWhereUse );

            DString dstrBefWhereUseCode;

            if ( ( dstrBefRelationship != PAYING_AGENT && dstrBefWhereUse != FUND ) &&
               ( dstrBefWhereUse != CLIENT ) && dstrBefWhereUse != FUNDSPONSOR)
            {
               getFieldBeforeImage (ifds::WhereUseCode, dstrBefWhereUseCode);
            }
            setFieldNoValidate (ifds::WhereUseCode, dstrBefWhereUseCode, idDataGroup, false, false, true, true);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY WhereUsed::doValidateAll ( const BFDataGroupId& idDataGroup, 
                                    long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doValidateAll"));	

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/WhereUsed.cpp-arc  $ */
// 
//    Rev 1.34   May 16 2012 20:02:28   wp040039
// PETP0187485-CPF-Agent bank and CPFB 
// INCIDENT#  2933935 - System allows to save RA code as Blank value  after delete the existing code
// 
//    Rev 1.33   Mar 29 2012 21:11:56   wp040039
// PETP0187485.FN01- CPF - Agent bank and CPFB 
// Adding Registration Agent as new WhereUse type with relationship OA,SA and SRS
// 
//    Rev 1.32   May 12 2010 11:59:06   popescu
// RESP/QESI - adding extra security to the EPP where used type
// 
//    Rev 1.31   Apr 23 2010 14:04:18   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.30   Apr 07 2010 09:38:24   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.29   Oct 01 2009 11:31:42   dchatcha
// P0163546 FN01 TA Automate Fund Transfer, Code review.
// 
//    Rev 1.28   Sep 28 2009 07:51:40   dchatcha
// P0163546 FN01 TA Automate Fund Transfer.
// 
//    Rev 1.27   Nov 06 2008 06:43:48   daechach
// PET5517 FN71 Unclaimed Property Phase 2 - Fix infinite loop when change where use type.
// 
//    Rev 1.26   Nov 06 2008 02:10:28   daechach
// PET5517 FN71 Unclaimed Property Phase 2
// 

