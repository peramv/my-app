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
//    Copyright 1999 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE     : UserDefMat.cpp
// ^CLASS    : UserDefMat
//
//******************************************************************************
#include "stdafx.h"

#include "contractinfo.hpp"
#include "contractinfoList.hpp"
#include "mastercontractlist.hpp"
#include "MFAccount.hpp"
#include "mgmtco.hpp"
#include "UserDefMat.hpp"
#include "UserDefMatList.hpp"
#include "SeqFundValidation.hpp"
#include "accountentityxref.hpp"
#include "entity.hpp"

#include <ifastdataimpl\dse_dstc0004_vw.hpp>                  // Account
#include <ifastdataimpl\dse_dstc0133_vwrepeat_record.hpp>     // Master Contract List
#include <ifastdataimpl\dse_dstc0354_vw.hpp>                  // Contract List
#include <ifastdataimpl\dse_dstc0340_vwrepeat_record.hpp>     // 

namespace
{
   const I_CHAR * const CLASSNAME = I_( "UserDefMat" );
   const I_CHAR * const CMD_BASED_ON_USERDEFINED               = I_( "04" );   
}

namespace CND
{
   extern const long ERR_CMD_LATER_THAN_LEGAL_MATURITY_DATE;
   extern const long WARN_CMD_LATER_THAN_LEGAL_MATURITY_DATE;
   extern const long ERR_DMD_LATER_THAN_LEGAL_MATURITY_DATE;
   extern const long WARN_DMD_LATER_THAN_LEGAL_MATURITY_DATE;
   extern const long WARN_USER_DEF_MAT_LESS;
   extern const long ERR_USER_DEF_MAT_LESS;
   extern const long ERR_GUAR_TRANS_EVENTS_EXIST;
   extern const long ERR_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK;
   extern const long WARN_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK;
   extern const long ERR_USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE;
   extern const long WARN_USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE; 
   extern const long ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE;
   extern const long WARN_USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE;
   extern const long ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM;
   extern const long WARN_USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM;

}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId LegalMaturityDate;
   extern CLASS_IMPORT const BFDateFieldId FirstEffective;
   extern CLASS_IMPORT const BFTextFieldId PorfolioIsRequried;
   extern CLASS_IMPORT const BFTextFieldId ContractMaturDateCrossEdit;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFNumericFieldId SeqNumber;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFDateFieldId DofBirth;
   extern CLASS_IMPORT const BFTextFieldId ContractMatBasedOn;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const DMD_LATER_THAN_LEGAL_MATURITY_DATE;
   extern CLASS_IMPORT I_CHAR * const CMD_LATER_THAN_LEGAL_MATURITY_DATE;
   extern CLASS_IMPORT I_CHAR * const USER_DEF_MAT_LESS;
   extern CLASS_IMPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE;
   extern CLASS_IMPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE;
   extern CLASS_IMPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM;
   extern CLASS_IMPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK;      
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//    Field DD Id,               State Flags,         Group Flags 
   { ifds::ContractMaturityDate, BFCBO::REQUIRED,           0 }, 
   { ifds::EffectiveDate,        BFCBO::NONE,               0 }, 
   { ifds::StopDate,             BFCBO::NONE,               0 }, 
   { ifds::OrigEventType,        BFCBO::NONE,               0 }, 
   { ifds::RecId,                BFCBO::NONE,               0 }, 
   { ifds::AccountNum,           BFCBO::NONE,               0 }, 
   { ifds::ContractType,         BFCBO::NONE,               0 }, 
   { ifds::ProcessDate,          BFCBO::NONE,               0 }, 
   { ifds::Username,             BFCBO::NONE,               0 }, 
   { ifds::ModDate,              BFCBO::NONE,               0 }, 
   { ifds::ModUser,              BFCBO::NONE,               0 },
   { ifds::ContractMaturDateCrossEdit, BFCBO::IMMEDIATE_VALIDATION,   0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
UserDefMat::UserDefMat( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   addCrossEdit(ifds::ContractMaturDateCrossEdit, ifds::ContractMaturityDate);   
   addCrossEdit(ifds::ContractMaturDateCrossEdit, ifds::ContractType);
}

//****************************************************************************
UserDefMat::~UserDefMat()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY UserDefMat::init( const BFData& data, const DString &ContractType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(const BFData&)" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   // Effective Date, Stop Date, and Original Event Type is not updateable.
   setFieldReadOnly( ifds::EffectiveDate, BF::HOST, true );
   setFieldReadOnly( ifds::StopDate, BF::HOST, true );
   setFieldReadOnly( ifds::OrigEventType, BF::HOST, true );

   // Contract Type
   setFieldNoValidate( ifds::ContractType, ContractType, BF::HOST, false );
   setFieldRequired( ifds::ContractMaturityDate, BF::HOST, true);
   setFieldUpdated( ifds::ContractMaturityDate, BF::HOST, true);

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY UserDefMat::init( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(idDataGroup)" ) );

   // Effective Date, Stop Date, and Original Event Type is not updateable.
   setFieldReadOnly( ifds::EffectiveDate, idDataGroup, true );
   setFieldReadOnly( ifds::StopDate, idDataGroup, true );
   setFieldReadOnly( ifds::OrigEventType, idDataGroup, true );
   setFieldRequired( ifds::ContractMaturityDate, idDataGroup, true);
   setFieldUpdated( ifds::ContractMaturityDate, idDataGroup, true);

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY UserDefMat::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::ContractMaturityDate )
   {
      ValidateMaturityDate( strValue, idDataGroup );
   }
   else if ( idField == ifds::ContractMaturDateCrossEdit)
   {
      DString strMaturityDate;
      getField(ifds::ContractMaturityDate, strMaturityDate, idDataGroup, false );
      strMaturityDate.strip();

      ValidateMaturityDate( strMaturityDate, idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
void UserDefMat::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   // Initialize dates
   DString FirstEffective, AccountNum, ContractType;
   MFAccount *pMFAccount = NULL;
   getParent()->getField( ifds::AccountNum, AccountNum, idDataGroup, false );
   getWorkSession().getMFAccount( idDataGroup, AccountNum, pMFAccount );
   if ( pMFAccount )
   {
      pMFAccount->getField (ifds::FirstEffective, FirstEffective, idDataGroup );
      setFieldNoValidate( ifds::EffectiveDate, FirstEffective, idDataGroup, false );
   }
   setFieldNoValidate( ifds::StopDate, I_("12319999"), idDataGroup, false );

   // Contract Type
   getParent()->getField( ifds::ContractType, ContractType, idDataGroup, false );
   setFieldNoValidate( ifds::ContractType, ContractType, idDataGroup, false );

   setFieldValid (ifds::ContractMaturDateCrossEdit, idDataGroup, false);   
   setFieldValid(ifds::ContractMaturityDate, idDataGroup, false);
}

//****************************************************************************
SEVERITY UserDefMat::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   // There is only 1 userdefmatlist for all contracts for an account -> it shouldn't, but this is for now
   // so if user def mat maturity date for 1 contract is updated, then the others need to be updated with the same value
   // Needs refactoring in the future to fully support multiple contracts! View 340 (add ContractType in the request), DSTSUserDefMatTrxnBuilder 9remove the break statement,etc...
   if ( ifds::ContractMaturityDate == idField )
   {
      //not needed, each contract type has its own user def mat list
      
      //DString dstrMaturityDate;
      //getField( ifds::ContractMaturityDate, dstrMaturityDate, idDataGroup );

      //DString dstrAccountNum;
      //getParent()->getField( ifds::AccountNum, dstrAccountNum, idDataGroup, false );
      //MFAccount *pMFAccount = NULL;
      //getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount );
      //ContractInfoList *pContractInfoList = NULL;
      //if ( NULL != pMFAccount &&
      //   pMFAccount->getContractInfoList( pContractInfoList, idDataGroup ) <= WARNING &&
      //   NULL != pContractInfoList )
      //{
      //   BFObjIter iterContractList( *pContractInfoList, idDataGroup );
      //   iterContractList.begin();
      //   while( !iterContractList.end() )
      //   {
      //      ContractInfo *pContractInfo = dynamic_cast< ContractInfo* >( iterContractList.getObject() );
      //      DString dstrContractType;
      //      if ( NULL != pContractInfo )
      //         pContractInfo->getField( ifds::ContractType, dstrContractType, idDataGroup );

      //      UserDefMatList* pUserDefMatList = NULL;
      //      if ( pMFAccount->getUserDefMatList( pUserDefMatList, idDataGroup, false, I_( "" ), dstrContractType ) <= WARNING &&
      //           NULL != pUserDefMatList )
      //      {
      //         BFObjIter iterUserDefMatList( *pUserDefMatList, idDataGroup );
      //         iterUserDefMatList.begin();

      //         while( !iterUserDefMatList.end() )
      //         {
      //            UserDefMat *pUserDefMat = dynamic_cast< UserDefMat* >( iterUserDefMatList.getObject() );

      //            if ( pUserDefMat != this )
      //            {
      //               pUserDefMat->setFieldNoValidate( ifds::ContractMaturityDate, 
      //                                                dstrMaturityDate, 
      //                                                idDataGroup,
      //                                                true, 
      //                                                true,
      //                                                true,
      //                                                false );
      //            }

      //            ++iterUserDefMatList;
      //         }
      //      }

      //      ++iterContractList;
      //   }
      //}
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY UserDefMat::ValidateMaturityDate( const DString& strValue, const BFDataGroupId& idDataGroup )
{
   // Two rules - 

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateMaturityDate" ) );
   
   DString strValidatingCMD(strValue),
      str12319999;
   getWorkSession().getDateInHostFormat (str12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   
   if(strValidatingCMD.empty() || strValidatingCMD == str12319999 )
   {
      getErrMsg( IFASTERR::USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK, 
                 CND::ERR_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK, 
                 CND::WARN_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK, 
                 idDataGroup );

      return GETCURRENTHIGHESTSEVERITY();
   }

   DString ContractMaturityDate; 
   DString dstrContractType;     // Current object
   DString AccountNum;           // from parent, UserDefList
   DString dstrGroupCode;        
   DString FirstEffective;       // Account level
   DString dstrMinTerm;          // from MasterContractList
   DString dstrCMDBasedON;
   
   getField( ifds::ContractMaturityDate, ContractMaturityDate, idDataGroup, false );
   getField( ifds::ContractType, dstrContractType, idDataGroup, false );	
   getField( ifds::ContractMatBasedOn, dstrCMDBasedON, idDataGroup, false);

   getParent()->getField( ifds::AccountNum, AccountNum, idDataGroup, false );
   MFAccount            *pMFAccount = NULL;  
   MasterContractList   *pMasterContractList = NULL;
   SEVERITY             sevRtn = SEVERE_ERROR;

   getWorkSession().getMFAccount( idDataGroup, AccountNum, pMFAccount );
   //sevRtn = getWorkSession().getMgmtCo().getMasterContractList(pMasterContractList);
   sevRtn = getMasterContractList(pMasterContractList, idDataGroup);

   // Check Legal Maturity Date
   // If Acct is !New, Maturity Date cannot be greater than Account Level Contr. Leg Mat Date, Err.   
   if( pMFAccount && !pMFAccount->isNew() )
   {
      DString LegalMaturityDate;
      getParent()->getField( ifds::LegalMaturityDate, LegalMaturityDate, idDataGroup, false );
      if( !LegalMaturityDate.empty() )
      {
         if( DSTCommonFunctions::CompareDates( LegalMaturityDate, ContractMaturityDate ) == DSTCommonFunctions::FIRST_EARLIER )
         {
//IN 2938847 - validate user def maturity date - begin
            getErrMsg( IFASTERR::USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE, 
               CND::ERR_USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE, 
               CND::WARN_USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE, 
               idDataGroup );
//IN 2938847 - validate user def maturity date - end

            DString GroupCode;
            DString ContMatDateBasedOn, MatDateBasedOn;
            pMFAccount->getField( ifds::AcctGroup, GroupCode, idDataGroup, false );

            if (pMasterContractList != NULL)
            {
               pMasterContractList->getFieldByGroupAndContractType( GroupCode, dstrContractType, ifds::ContMatDateBasedOn, ContMatDateBasedOn, idDataGroup, false);
               pMasterContractList->getFieldByGroupAndContractType( GroupCode, dstrContractType, ifds::MatDateBasedOn, MatDateBasedOn, idDataGroup, false);
            }

            if (MatDateBasedOn == I_("01"))
            {
               getErrMsg (IFASTERR::DMD_LATER_THAN_LEGAL_MATURITY_DATE, 
                          CND::ERR_DMD_LATER_THAN_LEGAL_MATURITY_DATE, 
                          CND::WARN_DMD_LATER_THAN_LEGAL_MATURITY_DATE, 
                          idDataGroup); 
            }
            else if (ContMatDateBasedOn == I_("02"))
            {
               getErrMsg (IFASTERR::CMD_LATER_THAN_LEGAL_MATURITY_DATE, 
                          CND::ERR_CMD_LATER_THAN_LEGAL_MATURITY_DATE, 
                          CND::WARN_CMD_LATER_THAN_LEGAL_MATURITY_DATE, 
                          idDataGroup); 
            }
         }
      }
   }

   if ( NULL != pMFAccount )
   {
      pMFAccount->getField( ifds::AcctGroup, dstrGroupCode, idDataGroup, false );	  
      pMFAccount->getField (ifds::FirstEffective, FirstEffective, idDataGroup );
   }

   BFCBO* pContractMasterObj = NULL;
   if ( sevRtn <= WARNING && NULL != pMasterContractList )
   {
      BFObjIter iterMst( *pMasterContractList, idDataGroup );
      iterMst.begin();

      bool bDefaultVer = true;

      DString dstrPorfolioIsRequried,
         dstrDefaultVer;
      getWorkSession().getOption( ifds::PorfolioIsRequried, dstrPorfolioIsRequried, idDataGroup, false );
      dstrPorfolioIsRequried.strip().upperCase();

      while( !iterMst.end() )
      {
         DString dstrCurrentGroupCode, dstrCurrentContractType;
         iterMst.getObject( )->getField( ifds::GroupCode,    dstrCurrentGroupCode,    idDataGroup, false );
         iterMst.getObject( )->getField( ifds::ContractType, dstrCurrentContractType, idDataGroup, false );

         if( dstrPorfolioIsRequried == I_("Y") )
         {
            iterMst.getObject( )->getField( ifds::DefaultVer, dstrDefaultVer, idDataGroup, false );
            dstrDefaultVer.strip().upperCase();

            bDefaultVer = dstrDefaultVer == I_("Y");
         }

         if( dstrCurrentGroupCode.stripAll().stripLeading('0')    == dstrGroupCode.stripAll().stripLeading('0') &&
             dstrCurrentContractType.stripAll().stripLeading('0') == dstrContractType.stripAll().stripLeading('0') && 
             bDefaultVer )
         {
            pContractMasterObj = dynamic_cast<BFCBO*>(iterMst.getObject());
            break;
         }
         else
            ++iterMst;
      }
   }
   
   DString dstrContractTypeId;
   DString dstrEffectiveDate;      
   DString dstrContractMatBasedOn;
   ContractInfo *pContractInfo = NULL;
   
   if ( NULL != pMFAccount )
   {
      getContractInfo(pContractInfo, pMFAccount, idDataGroup);
      if(pContractInfo != NULL)
      {
         pContractInfo->getField( ifds::ContractMatBasedOn, dstrContractMatBasedOn, idDataGroup, false);
         pContractInfo->getField( ifds::ContractTypeId,     dstrContractTypeId, idDataGroup, false );
         pContractInfo->getField( ifds::EffectiveDate,      dstrEffectiveDate,  idDataGroup, false );
      }

   }

   if(dstrContractMatBasedOn == CMD_BASED_ON_USERDEFINED)
   {
      if(pContractMasterObj)
      {
         // If Maturity Date < Master Contract Term (in years) from first account effective date, Warning.
         pContractMasterObj->getField( ifds::MinTerm, dstrMinTerm, idDataGroup, false );
         int iMinTerm = dstrMinTerm.asInteger();
         if ( iMinTerm == 0 )
            iMinTerm = 10;
         BFDate dateFirstEffective( FirstEffective, BFDate::DF_DDATE_DEPRECATED );

         int iDayOfMonth = dateFirstEffective.getDay();
         int iMonth = dateFirstEffective.getMonth();
         int iMod = iMinTerm % 4;
         BFDate* pDateFirstEffectivePlusTen = NULL;
         if( iDayOfMonth == 29 && iMonth == 2 && iMod != 0 )
         {
            BFDate dateFirstEffectivePlusTen( 1, 3, dateFirstEffective.getYear() + iMinTerm );//Feb29 into Mar. 1
            pDateFirstEffectivePlusTen = &dateFirstEffectivePlusTen;
         }
         else
         {
            BFDate dateFirstEffectivePlusTen( dateFirstEffective.getDay(), dateFirstEffective.getMonth(), dateFirstEffective.getYear() + iMinTerm );
            pDateFirstEffectivePlusTen = &dateFirstEffectivePlusTen;
         }
         
         BFDate dateContractMaturityDate( ContractMaturityDate, BFDate::DF_DDATE_DEPRECATED );

         if( dateContractMaturityDate - *pDateFirstEffectivePlusTen < 0 )
         {
            DString idiDStr;  
            addIDITagValue( idiDStr, I_("TERM"), iMinTerm == 0 ? I_("10") : dstrMinTerm );
            // As per SEGMDTV1.P
            // User-defined maturity date is less than %TERM% years from account effective date.	  
            getErrMsg( IFASTERR::USER_DEF_MAT_LESS, 
                     CND::ERR_USER_DEF_MAT_LESS, 
                     CND::WARN_USER_DEF_MAT_LESS, 
                     idDataGroup,
                     idiDStr ); 
         }
      }

      if ( NULL != pMFAccount )
      {
         //ContractInfoList *pContractInfoList = NULL;
         //if ( pMFAccount->getContractInfoList( pContractInfoList, idDataGroup ) <= WARNING &&
         //     NULL != pContractInfoList )
         //{
         //   BFObjIter iterContractList( *pContractInfoList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
         //   iterContractList.begin();
         //   while( !iterContractList.end() )
         //   {
         //      ContractInfo *pCurrentContractInfo = dynamic_cast< ContractInfo* >( iterContractList.getObject() );

         //      DString dstrCurrentContractType;
         //      if ( NULL != pCurrentContractInfo // && !pCurrentContractInfo->isNewContract( idDataGroup ) 
         //         )
         //      {
         //         pCurrentContractInfo->getField( ifds::ContractType, dstrCurrentContractType, idDataGroup );
         //         pCurrentContractInfo->getField( ifds::ContractMatBasedOn, dstrContractMatBasedOn, idDataGroup, false);
         //      }
         //      if ( dstrContractType == dstrCurrentContractType )
         //      {
         //         pCurrentContractInfo->getField( ifds::ContractTypeId, dstrContractTypeId, idDataGroup, false );
         //         pCurrentContractInfo->getField( ifds::EffectiveDate,  dstrEffectiveDate,  idDataGroup, false );
         //         break;
         //      }
         //      ++iterContractList;
         //   }
         //}

         if ( !dstrContractTypeId.stripAll().empty() && 
            !dstrEffectiveDate.stripAll().empty() )
         {
            SeqFundValidation *pSeqFundValidation = new SeqFundValidation ( *this );
            if( pSeqFundValidation->init354( AccountNum, 
                                             dstrContractType, 
                                             dstrEffectiveDate,
                                             dstrContractTypeId ) <= WARNING &&
                                             NULL != pSeqFundValidation )
            {
               DString dstrAllowUDMUpdate;
               pSeqFundValidation->getField( ifds::AllowUDMUpdate, dstrAllowUDMUpdate, idDataGroup );
               dstrAllowUDMUpdate.stripAll().upperCase();
               if ( I_( "N" ) == dstrAllowUDMUpdate )
               {
                  // Add/Modify/Delete not allowed since transactions/events exist.
                  ADDCONDITIONFROMFILE( CND::ERR_GUAR_TRANS_EVENTS_EXIST );
               }

               delete pSeqFundValidation;
               pSeqFundValidation = NULL;
            }
         }

         if(pContractMasterObj && !dstrEffectiveDate.stripAll().empty())
         {
            DString dstrDofBirth;
            bool ret = getDofBirth( idDataGroup, dstrDofBirth);
            DString dstrMinTerm;
            DString dstrMinAge;
            DString dstrMaxAge;

            getMasterMinTermAndMinMaxAge( dstrMinTerm, dstrMinAge, dstrMaxAge, idDataGroup );

            int intMinTerm  = dstrMinTerm.asInteger();

            DString dstrTaxType;
            pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
            dstrTaxType.strip().upperCase();
            if(dstrTaxType != I_("9") && dstrTaxType != I_("M"))//no RESP
            {
               int intMaxAge  = dstrMaxAge.asInteger();
               int intMinAge  = dstrMinAge.asInteger();

               BFDate bfdDOB(dstrDofBirth, BFDate::DATE_FORMAT::DF_HOST);
               BFDate bfdMinCMD = bfdDOB;
               bfdMinCMD.addYears(intMinAge);

               BFDate bfdMaxCMD = bfdDOB;
               bfdMaxCMD.addYears(intMaxAge);

               BFDate bfdCMD(ContractMaturityDate, BFDate::DATE_FORMAT::DF_HOST);
               
               if(bfdCMD < bfdMinCMD || bfdCMD > bfdMaxCMD)
               {
                  getErrMsg( IFASTERR::USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE, 
                     CND::ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE, 
                     CND::WARN_USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE, 
                     idDataGroup );
               }
            }

            BFDate bfdMinCMD(dstrEffectiveDate, BFDate::DATE_FORMAT::DF_HOST);
            bfdMinCMD.addYears(intMinTerm);

            BFDate bfdCMD(ContractMaturityDate, BFDate::DATE_FORMAT::DF_HOST);
            if(bfdCMD < bfdMinCMD)
            {
               getErrMsg( IFASTERR::USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM, 
                  CND::ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM, 
                  CND::WARN_USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM, 
                  idDataGroup );
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY UserDefMat::getContractInfo(ContractInfo*& pContractInfo, MFAccount* pMFAccount, const BFDataGroupId& idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getContractInfo"));

   DString dstrContractType;
   getField( ifds::ContractType, dstrContractType, idDataGroup, false );	

//   DString dstrContractTypeId, dstrEffectiveDate;      
   pContractInfo = NULL;
   if ( NULL != pMFAccount )
   {
      ContractInfoList *pContractInfoList = NULL;
      if ( pMFAccount->getContractInfoList( pContractInfoList, idDataGroup ) <= WARNING &&
           NULL != pContractInfoList )
      {
         BFObjIter iterContractList( *pContractInfoList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
         iterContractList.begin();
         while( !iterContractList.end() )
         {
            ContractInfo *pCurrentContractInfo = dynamic_cast< ContractInfo* >( iterContractList.getObject() );

            DString dstrCurrentContractType;
            if ( NULL != pCurrentContractInfo)
               pCurrentContractInfo->getField( ifds::ContractType, dstrCurrentContractType, idDataGroup );
            
            if ( dstrContractType == dstrCurrentContractType )
            {
               pContractInfo = pCurrentContractInfo;
               break;
            }
            ++iterContractList;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

bool UserDefMat::getDofBirth( const BFDataGroupId& idDataGroup, DString &dstrDofBirth )
{
   DString strAccountNum;
   DString dstrAcctType;
   DString dstrTaxType;
   DString dstrEntityType;
   DString dstrSeqNumber;
   DString dstrEntityId; 

   bool bRtn = false;

   SEVERITY sevRtn = SEVERE_ERROR;
   getParent()->getField( ifds::AccountNum, strAccountNum, idDataGroup, false );

   MFAccount* _pMFAccount = NULL;
   
   getWorkSession().getMFAccount( idDataGroup, strAccountNum, _pMFAccount );

   _pMFAccount->getField( ifds::AccountNum, strAccountNum, idDataGroup );  
   _pMFAccount->getField( ifds::AcctType, dstrAcctType, idDataGroup, false );
   _pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );

   AccountEntityXref *pAccountEntityXref;
   sevRtn = getWorkSession().getAccountEntityXref( BF::HOST, pAccountEntityXref );
   sevRtn = pAccountEntityXref->PopulateEntitiesList(  idDataGroup, strAccountNum );
   if( sevRtn >= WARNING || !pAccountEntityXref )
      return(false);

   BFObjIter iterAcctEntXRef( *pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   DString searchKey;
   pAccountEntityXref->buildPartialKeyForAccount( searchKey, strAccountNum );

   //  For the non-registered tax type ( TaxType_4 == "0" ), the annuitant entity type ( EntityType_50 = "05" )
   //  with the smallest sequence number, this entity must have valid DOfBirth_51 and use it for BaiMaturityDate
   //  and LegalMaturityDate calculations
   if( getWorkSession().isNonRegLike( dstrTaxType.stripAll() ) )
   {  // non-registered account
      for( iterAcctEntXRef.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ); !iterAcctEntXRef.end(); ++iterAcctEntXRef )
      {
         iterAcctEntXRef.getObject( )->getField(ifds::EntityType, dstrEntityType, idDataGroup, false );
         iterAcctEntXRef.getObject( )->getField(ifds::SeqNumber, dstrSeqNumber, idDataGroup, false );
         // EntityType = "05" means an annuitant entity. The program should check annuitant's DofBirth.
         // We want the first Entity with EntityType = 05 by looking at the Entity sequence number.
         // The sequence number does not always start with one.
         // Since Entities are indexed by AccountNum, EntityType, EntitySequence, EntityId
         // The first object in the iteration that matches entity type 05 should be 
         // the entity with the smallest sequence number.
         if( dstrEntityType.stripAll() ==  I_("05") )
         {
            // get annuitant's entityId
            iterAcctEntXRef.getObject( )->getField(ifds::EntityId, dstrEntityId, idDataGroup, false );
            break;
         }
      }
   }
   else
   {   // registered account
      for( iterAcctEntXRef.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ); !iterAcctEntXRef.end(); ++iterAcctEntXRef )
      {
         iterAcctEntXRef.getObject( )->getField(ifds::EntityType, dstrEntityType, idDataGroup, false );
         iterAcctEntXRef.getObject( )->getField(ifds::SeqNumber, dstrSeqNumber, idDataGroup, false );
         // EntityType = "01" means Owner . The program should get owner's DofBirth
         // Refer to above comment, same concept.
         if( dstrEntityType.stripAll() ==  I_("01") )
         {
            // get owner's entityId
            iterAcctEntXRef.getObject( )->getField(ifds::EntityId, dstrEntityId, idDataGroup, false );
            break;
         }
      }
   }

   if( dstrEntityId != NULL_STRING )
   {
      Entity *pEntity;
      sevRtn = getWorkSession().getEntity(  idDataGroup, dstrEntityId, pEntity );
      if( sevRtn <= WARNING && pEntity )
      {
         pEntity->getField( ifds::DofBirth, dstrDofBirth, idDataGroup, false );
         if( dstrDofBirth != NULL_STRING )
            bRtn = true;
         else
            bRtn = false;

      }
   }
   return(bRtn);  
}
//******************************************************************************
SEVERITY UserDefMat::getMasterContractList(MasterContractList*& _pMasterContractList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterContractList" ) );
   
   DString dstrPorfolioIsRequried;
   getWorkSession().getOption( ifds::PorfolioIsRequried, dstrPorfolioIsRequried, idDataGroup, false );
   dstrPorfolioIsRequried.strip().upperCase();

   if( dstrPorfolioIsRequried == I_("Y") )
   {
      MFAccount *pMFAccount = NULL;
      DString dstrAcctNum;

      getParent()->getField( ifds::AccountNum, dstrAcctNum, idDataGroup, false );
      getWorkSession().getMFAccount( idDataGroup, dstrAcctNum, pMFAccount );
      if ( NULL != pMFAccount )
      {
         pMFAccount->getMasterContractListByPortfolio(_pMasterContractList,idDataGroup);
      }
   }
   else
   {
      getMgmtCo().getMasterContractList( _pMasterContractList );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY UserDefMat::getMasterMinTermAndMinMaxAge( DString& dstrMinTerm, DString& dstrMinAge, 
                                                    DString& dstrMaxAge, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterMinTermAndMinMaxAge" ) );

   BFAbstractCBO* pMasterContract = NULL;
   getMasterContract(pMasterContract, idDataGroup);
   if(pMasterContract)
   {
      pMasterContract->getField(ifds::MinAge,  dstrMinAge,  idDataGroup );
      pMasterContract->getField(ifds::MaxAge,  dstrMaxAge,  idDataGroup );
      pMasterContract->getField(ifds::MinTerm, dstrMinTerm, idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY UserDefMat::getMasterContract(BFAbstractCBO*& _pMasterContract, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterContract" ) );

   _pMasterContract = NULL;

   MasterContractList* _pMasterContractList = NULL;
   getMasterContractList(_pMasterContractList, idDataGroup);

   DString dstrAcctGroup;
   DString dstrContractType;

   getField( ifds::ContractType, dstrContractType, idDataGroup );

   MFAccount* _pMFAccount = NULL;
   
   DString strAccountNum;
   getParent()->getField( ifds::AccountNum, strAccountNum, idDataGroup, false );
   getWorkSession().getMFAccount( idDataGroup, strAccountNum, _pMFAccount );
   _pMFAccount->getField(ifds::AcctGroup, dstrAcctGroup, idDataGroup);
   dstrAcctGroup.strip().upperCase();

   if (_pMasterContractList)
   {
      BFObjIter iterMasterContract( *_pMasterContractList, idDataGroup);
      iterMasterContract.begin();
      BFAbstractCBO* pMasterContract = NULL;

      while( !iterMasterContract.end() )
      {
         DString dstrMstrCntrTypeId;
         DString dstrMstrType;
         DString dstrMstrDefaultVer;
         DString dstrMstrCntrGroup;
            
         pMasterContract = iterMasterContract.getObject();
         pMasterContract->getField(ifds::ContractTypeId, dstrMstrCntrTypeId,  idDataGroup, false); 
         pMasterContract->getField(ifds::ContractType,   dstrMstrType,        idDataGroup, false);
         pMasterContract->getField(ifds::DefaultVer,     dstrMstrDefaultVer,  idDataGroup, false);
         pMasterContract->getField(ifds::GroupCode,      dstrMstrCntrGroup,   idDataGroup, false); 

         dstrMstrCntrTypeId.strip().upperCase();
         dstrMstrType.strip().upperCase();
         dstrMstrDefaultVer.strip().upperCase();
         dstrMstrCntrGroup.strip().upperCase();

         if( dstrContractType == dstrMstrType && dstrMstrDefaultVer == I_("Y") && dstrMstrCntrGroup == dstrAcctGroup)
         {
            _pMasterContract = pMasterContract;
            break;
         }
         ++iterMasterContract;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/UserDefMat.cpp-arc  $
// 
//    Rev 1.23   Jun 18 2012 17:34:42   if991250
// IN2937065: new CMD Based on: User Defined Mat - Transfer
// 
//    Rev 1.22   May 29 2012 14:14:36   if991250
// User defined validation
// 
//    Rev 1.21   May 25 2012 19:13:00   if991250
// IN#2938847 Contract Information - User defined Maturity Date validation
// 
//    Rev 1.20   Feb 10 2012 18:07:10   dchatcha
// IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
// 
//    Rev 1.19   Feb 08 2012 21:26:38   dchatcha
// IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
// 
//    Rev 1.18   Feb 03 2012 18:59:18   dchatcha
// IN# 2799812 - Contract Screen Issues.
// 
//    Rev 1.17   Jan 30 2012 11:20:56   dchatcha
// IN# 2799812 - Contract Screen Issues.
// 
//    Rev 1.16   13 Mar 2008 16:07:58   kovacsro
// IN#1201922 - it was crashing on Feb. 29
// 
//    Rev 1.15   Sep 12 2006 14:30:18   porteanm
// Incident 642056 - UDM validation only for existing records.
// 
//    Rev 1.14   Jul 25 2006 19:32:18   porteanm
// Incident 642056 - UDM validation. Layout change for 354 request and fixed response.
// 
//    Rev 1.13   Jun 06 2006 17:25:14   porteanm
// PET 2102 FN01 - Support for error 444. Added ERR_USER_DEF_MAT_LESS,     ERR_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK, WARN_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK.
// 
//    Rev 1.12   May 02 2006 14:25:46   jankovii
// PET 2102 Manulife Flex - User Defined Maturity Dates.
// 
//    Rev 1.11   Dec 13 2005 16:24:06   porteanm
// Incident 492179 - User Def mat Date not saved.
// 
//    Rev 1.10   Nov 03 2005 15:38:20   porteanm
// Incident 442910 - Changed validateMaturityDate based on the real Contract Term from ContractMaster.
// 
//    Rev 1.9   Sep 23 2005 18:26:44   ZHANGCEL
// PET1244 FN01 -- Seg Func Evolution enhancement
// 
//    Rev 1.8   Jun 22 2005 13:11:46   popescu
// Incident #339563 - fixed NASU flow crash on the UserDefMat screen
// 
//    Rev 1.7   May 15 2005 16:41:40   hernando
// Inc 305633 - Added ContractType in init call.
// 
//    Rev 1.6   May 08 2005 18:17:24   hernando
// Inc 305974 - Changed 10-yr comparison.
// 
//    Rev 1.5   May 08 2005 17:17:28   hernando
// Inc 305537 - Checks if MFAccount isn't new before checking legal date.
// 
//    Rev 1.4   Apr 18 2005 17:18:16   hernando
// PET1024 FN02 - Changed DataGroup to Host for values stored in User Def Mat List.
// 
//    Rev 1.3   Apr 18 2005 13:52:24   hernando
// PET1024 FN02 - Changed location to retrieve Account Num.
// 
//    Rev 1.2   Apr 14 2005 10:07:48   hernando
// PET1024 FN02 - Added Contract Type support.
// 
//    Rev 1.1   Mar 20 2005 17:50:36   hernando
// PET1024 FN02 - Added doInitWithDefaultValues.
// 
//    Rev 1.0   Mar 20 2005 17:12:08   hernando
// Initial revision.
