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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : TaxTypeRule.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : May 18, 2000
// ^CLASS    : TaxTypeRule
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include "stdafx.h"
#include "taxtyperule.hpp"
#include "redcodebytaxtype.hpp"
#include "redcodebytaxtypelist.hpp"
#include "taxjurislimitlist.hpp"
#include <ifastdataimpl\dse_dstc0087_req.hpp>
#include <ifastdataimpl\dse_dstc0087_vw.hpp>
#include <ifastdataimpl\dse_dstc0087_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0138_vwrepeat_record.hpp>

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DepositType;
   extern CLASS_IMPORT const BFTextFieldId RedCode;
   extern CLASS_IMPORT const BFTextFieldId DepositTypeList;
   extern CLASS_IMPORT const BFTextFieldId RedCodeList;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,              State Flags,   Group Flags 
   { ifds::TaxType,          BFCBO::NONE, 0 },  
   { ifds::TaxTypeDesc,      BFCBO::NONE, 0 },  
   { ifds::PlanType,         BFCBO::NONE, 0 },  
   { ifds::PlanTypeDesc,     BFCBO::NONE, 0 },  
   { ifds::AccountTypes,     BFCBO::NONE, 0 },  
   { ifds::SelfDirected,     BFCBO::NONE, 0 },  
   { ifds::TransferType,     BFCBO::NONE, 0 },  
   { ifds::LockedIn,         BFCBO::NONE, 0 },  
   { ifds::TaxByJuris,       BFCBO::NONE, 0 },  
   { ifds::FedJurisAllowed,  BFCBO::NONE, 0 },  
   { ifds::Certificate,      BFCBO::NONE, 0 },  
   { ifds::NomTaxRcpt,       BFCBO::NONE, 0 },  
   { ifds::Unseizable,       BFCBO::NONE, 0 },  
   { ifds::AvailNonRes,      BFCBO::NONE, 0 },  
   { ifds::ReinDistOnly,     BFCBO::NONE, 0 },  
   { ifds::MinimumApplies,   BFCBO::NONE, 0 },  
   { ifds::MaximumApplies,   BFCBO::NONE, 0 },  
   { ifds::GICallowed,       BFCBO::NONE, 0 },  
   { ifds::PACallowed,       BFCBO::NONE, 0 },  
   { ifds::SWPallowed,       BFCBO::NONE, 0 },  
   { ifds::AdminFeeDefn,     BFCBO::NONE, 0 },  
   { ifds::MailList1,        BFCBO::NONE, 0 },  
   { ifds::MailList2,        BFCBO::NONE, 0 },  
   { ifds::MailList3,        BFCBO::NONE, 0 },  
   { ifds::MailList4,        BFCBO::NONE, 0 },  
   { ifds::MailList5,        BFCBO::NONE, 0 },  
   { ifds::MailList6,        BFCBO::NONE, 0 },  
   { ifds::MailList7,        BFCBO::NONE, 0 },  
   { ifds::MailList8,        BFCBO::NONE, 0 },  
   { ifds::MailList9,        BFCBO::NONE, 0 },  
   { ifds::MailList10,       BFCBO::NONE, 0 },  
   { ifds::MailList11,       BFCBO::NONE, 0 },  
   { ifds::MailList12,       BFCBO::NONE, 0 },  
   { ifds::TaxCashDist1,     BFCBO::NONE, 0 },  
   { ifds::TaxCashDist2,     BFCBO::NONE, 0 },  
   { ifds::TaxCashDist3,     BFCBO::NONE, 0 },  
   { ifds::TaxEarlyClose1,   BFCBO::NONE, 0 },  
   { ifds::TaxEarlyClose2,   BFCBO::NONE, 0 },  
   { ifds::TaxEarlyClose3,   BFCBO::NONE, 0 },  
   { ifds::TaxFullRdmp1,     BFCBO::NONE, 0 },  
   { ifds::TaxFullRdmp2,     BFCBO::NONE, 0 },  
   { ifds::TaxFullRdmp3,     BFCBO::NONE, 0 },  
   { ifds::TaxNotional1,     BFCBO::NONE, 0 },  
   { ifds::TaxNotional2,     BFCBO::NONE, 0 },  
   { ifds::TaxNotional3,     BFCBO::NONE, 0 },  
   { ifds::TaxPartRdmp1,     BFCBO::NONE, 0 },  
   { ifds::TaxPartRdmp2,     BFCBO::NONE, 0 },  
   { ifds::TaxPartRdmp3,     BFCBO::NONE, 0 },  
   { ifds::TaxPurchase1,     BFCBO::NONE, 0 },  
   { ifds::TaxPurchase2,     BFCBO::NONE, 0 },  
   { ifds::TaxPurchase3,     BFCBO::NONE, 0 },  
   { ifds::TaxReinvDist1,    BFCBO::NONE, 0 },  
   { ifds::TaxReinvDist2,    BFCBO::NONE, 0 },  
   { ifds::TaxReinvDist3,    BFCBO::NONE, 0 },  
   { ifds::TaxSwitches1,     BFCBO::NONE, 0 },  
   { ifds::TaxSwitches2,     BFCBO::NONE, 0 },  
   { ifds::TaxSwitches3,     BFCBO::NONE, 0 },  
   { ifds::TaxTransfers1,    BFCBO::NONE, 0 },  
   { ifds::TaxTransfers2,    BFCBO::NONE, 0 },  
   { ifds::TaxTransfers3,    BFCBO::NONE, 0 },  
   { ifds::ClientEquiv,      BFCBO::NONE, 0 },  
   { ifds::DepositTypeList,  BFCBO::NONE, 0 },  
   { ifds::RedCodeList,      BFCBO::NONE, 0 },  
   //{ ifds::CriticalAge1,     BFCBO::NONE, 0 },  
   //{ ifds::CriticalAge2,     BFCBO::NONE, 0 },  
   //{ ifds::CriticalAge3,     BFCBO::NONE, 0 },  
   //{ ifds::BailOutAge1,      BFCBO::NONE, 0 },  
   //{ ifds::BailOutAge2,      BFCBO::NONE, 0 },  
   //{ ifds::BailOutAge3,      BFCBO::NONE, 0 },  
   //{ ifds::LegalAgeCalcType, BFCBO::NONE, 0 },  
   //{ ifds::LegalMaxAge,      BFCBO::NONE, 0 },  
   { ifds::RedCode,          BFCBO::NONE, 0 }, 
   { ifds::DepositType,      BFCBO::NONE, 0 }, 
   { ifds::ChkAgeOfMajority, BFCBO::NONE, 0 }, 
};

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "TaxTypeRule" );
   const I_CHAR * const DEPOSIT_CODE_TYPE       = I_( "D" );
   const I_CHAR * const REDEMPTION_CODE_TYPE    = I_( "R" );
   const I_CHAR * const COMMA                   = I_( "," );
}

namespace CND
{  // Conditions used

}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
TaxTypeRule::TaxTypeRule( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
m_pTaxJurisLimitList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
TaxTypeRule::~TaxTypeRule()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( m_pTaxJurisLimitList )
   {
      delete m_pTaxJurisLimitList;
      m_pTaxJurisLimitList = NULL;
   }
}

//******************************************************************************
SEVERITY TaxTypeRule::init( const BFData &viewData )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   attachDataObject( const_cast<BFData&>( viewData ), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool TaxTypeRule::validTransfer ( const DString& dstrTaxTypeIn, const BFDataGroupId& idDataGroup )
{
   DString dstrTaxTypeList, strTaxType;
   bool TaxTypeOkay;

   getField( ifds::TransferType, dstrTaxTypeList, idDataGroup );
   dstrTaxTypeList = COMMA + dstrTaxTypeList + COMMA;

   strTaxType = COMMA + dstrTaxTypeIn + COMMA;

   TaxTypeOkay = (dstrTaxTypeList.find(strTaxType) != DString::npos);

   return(TaxTypeOkay);
}

//******************************************************************************
void TaxTypeRule::getDepTypeList ( RedCodeByTaxTypeList *&pDepTypeList, const BFDataGroupId& idDataGroup )
{
//CP20040219   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDepTypeList") );
 
   pDepTypeList = NULL;

   RedCodeByTaxTypeList* pWorkingDepTypeList = NULL;
   pWorkingDepTypeList = dynamic_cast< RedCodeByTaxTypeList * >( BFCBO::getObject( I_( "DepCodeByTaxTypeList" ), idDataGroup ) );

   if( !pWorkingDepTypeList )
   {
      DString dstrTaxType, dstrCodeType (DEPOSIT_CODE_TYPE);

      pWorkingDepTypeList = new RedCodeByTaxTypeList( *this );
      getField( ifds::TaxType, dstrTaxType, idDataGroup );
      dstrTaxType.strip().upperCase();

      if( pWorkingDepTypeList->init( dstrTaxType, dstrCodeType) >= SEVERE_ERROR )
      {
         delete pWorkingDepTypeList;
         pWorkingDepTypeList = NULL;
      }
      else
      {
         setObject( pWorkingDepTypeList, I_( "DepCodeByTaxTypeList" ), OBJ_ACTIVITY_NONE, idDataGroup );  
      }
   }
   pDepTypeList = pWorkingDepTypeList;
}

//******************************************************************************
void TaxTypeRule::getRedCodeList ( RedCodeByTaxTypeList *&pRedCodeList, const BFDataGroupId& idDataGroup )
{
//CP20040219   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRedCodeList") );
//CP20050927   BFGuard g( csRedCodeList_ );

   pRedCodeList = NULL;

   RedCodeByTaxTypeList* pLocalRedCodeList = NULL;
   pLocalRedCodeList = dynamic_cast< RedCodeByTaxTypeList * >( BFCBO::getObject( I_( "RedCodeByTaxTypeList" ), idDataGroup ) );

   if( !pLocalRedCodeList )
   {
      DString dstrTaxType, dstrCodeType (REDEMPTION_CODE_TYPE);

      pLocalRedCodeList = new RedCodeByTaxTypeList( *this );
      getField( ifds::TaxType, dstrTaxType, idDataGroup );
      dstrTaxType.strip().upperCase();

      if( pLocalRedCodeList->init( dstrTaxType, dstrCodeType ) >= SEVERE_ERROR )
      {
         delete pLocalRedCodeList;
         pLocalRedCodeList = NULL;
      }
      else
      {
         setObject( pLocalRedCodeList, I_( "RedCodeByTaxTypeList" ), OBJ_ACTIVITY_NONE, idDataGroup );  
      }
   }
   pRedCodeList = pLocalRedCodeList;
}


//******************************************************************************
bool TaxTypeRule::validAcctType ( const DString& accountType, const BFDataGroupId& idDataGroup )
{
   DString dstrAcctTypeList, strAcctType;
   bool AcctTypeOkay;

   getField( ifds::AccountTypes, dstrAcctTypeList, idDataGroup );
   dstrAcctTypeList = COMMA + dstrAcctTypeList + COMMA;

   strAcctType = COMMA + accountType + COMMA;

   AcctTypeOkay = (dstrAcctTypeList.find(strAcctType) != DString::npos);

   return(AcctTypeOkay);
}

//******************************************************************************
bool TaxTypeRule::validAcctDesignation ( const DString& dstrAcctDesignation, const BFDataGroupId& idDataGroup )
{
   DString dstrAcctDesignationList, strAcctDesignation;
   bool AcctDesignationOkay;

   getField( ifds::AcctDesignation, dstrAcctDesignationList, idDataGroup );
   dstrAcctDesignationList = COMMA + dstrAcctDesignationList + COMMA;

   strAcctDesignation = COMMA + dstrAcctDesignation + COMMA;

   AcctDesignationOkay = (dstrAcctDesignationList.find(strAcctDesignation) != DString::npos);

   return(AcctDesignationOkay);
}
//******************************************************************************

bool TaxTypeRule::isValidDepCode(const DString& dstrDepCode )
{
   DString strDepCodeList;
   getField(ifds::DepositTypeList, strDepCodeList, BF::HOST, false);
   return(DSTCommonFunctions::codeInList(dstrDepCode, strDepCodeList, true));
}
//******************************************************************************

bool TaxTypeRule::isValidRedCode(const DString& dstrRedCode )
{
   DString strRedCodeList;
   getField(ifds::RedCodeList, strRedCodeList, BF::HOST, false);
   return(DSTCommonFunctions::codeInList(dstrRedCode, strRedCodeList, true));

}

//******************************************************************************

bool TaxTypeRule::doesTaxJurisdictionLimitationListExist(const BFDataGroupId& idDataGroup)
{
   if( NULL != m_pTaxJurisLimitList ) {
      return( true );
   }

   DString dstrTaxType, dstrTaxTypeSched;
   TaxJurisLimitList* pTaxJurisLimitList = new TaxJurisLimitList( *this );
   getField( ifds::TaxType, dstrTaxType, idDataGroup );
   dstrTaxType.strip().upperCase();
   getField( ifds::TaxTypeSchedule, dstrTaxTypeSched, idDataGroup );

   if( pTaxJurisLimitList->init( dstrTaxType, dstrTaxTypeSched ) >= SEVERE_ERROR )
   {
      delete pTaxJurisLimitList;
      pTaxJurisLimitList = NULL;
   }

   // Possible Deadlock if retrieval is done from within a BFGuard due
   // to synchronization object in BFNotification - CP20050927
   BFGuard g( csTaxJurisLimitList_ );

   if( NULL != m_pTaxJurisLimitList ) {
      return( true );
   }
   m_pTaxJurisLimitList = pTaxJurisLimitList;

   return( NULL != m_pTaxJurisLimitList ); // No warning with != NULL
}

//******************************************************************************

bool TaxTypeRule::isValidAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup ) 
{
   if( doesTaxJurisdictionLimitationListExist(idDataGroup) )
   {
      if( m_pTaxJurisLimitList )
      {
         return(m_pTaxJurisLimitList->isValidAge( dstrAge, dstrJurisdiction, idDataGroup ));
      }
   }

   return(false);
}

//******************************************************************************

bool TaxTypeRule::getAgeCalcBasedOn(int& ageCalcBasedOn, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup ) 
{
   if( doesTaxJurisdictionLimitationListExist(idDataGroup) )
   {
      if( m_pTaxJurisLimitList )
      {
         return(m_pTaxJurisLimitList->getAgeCalcBasedOn( ageCalcBasedOn, dstrJurisdiction, idDataGroup ));
      }
   }

   return(false);
}

//******************************************************************************

bool TaxTypeRule::isValidMinimumAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup ) 
{
   if( doesTaxJurisdictionLimitationListExist(idDataGroup) )
   {
      if( m_pTaxJurisLimitList )
      {
         return(m_pTaxJurisLimitList->isValidMinimumAge( dstrAge, dstrJurisdiction, idDataGroup ));
      }
   }

   return(false);
}

//******************************************************************************

bool TaxTypeRule::isValidMaximumAge( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup ) 
{
   if( doesTaxJurisdictionLimitationListExist(idDataGroup) )
   {
      if( m_pTaxJurisLimitList )
      {
         return(m_pTaxJurisLimitList->isValidMaximumAge( dstrAge, dstrJurisdiction, idDataGroup ));
      }
   }

   return(false);
}

//******************************************************************************

bool TaxTypeRule::isValidPensionJurisdiction( const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup ) 
{
   if( doesTaxJurisdictionLimitationListExist(idDataGroup) )
   {
      if( m_pTaxJurisLimitList )
      {
         return(m_pTaxJurisLimitList->isValidPensionJurisdiction( dstrJurisdiction, idDataGroup ));
      }
   }

   return(false);
}

//******************************************************************************
// Method to return the value of the idField requested based on the jurisdiction
// passed in from the TaxJurisLimitList CBO.
// @param   const BFFieldId& idField - Field Id request
//          const DString& dstrJurisdiction - Jurisdiction used.
//          const BFDataGroupId& idDataGroup - datagroup id.
// @return  DString - value of field Id based on the Jurisdiction.
//******************************************************************************
DString TaxTypeRule::getJurisLimitField( const BFFieldId& idField, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup, bool blFormatted ) 
{
   if( doesTaxJurisdictionLimitationListExist(idDataGroup) )
   {
      if( m_pTaxJurisLimitList )
      {
         return(m_pTaxJurisLimitList->getJurisLimitField( idField, dstrJurisdiction, idDataGroup, blFormatted ));
      }
   }
   return(NULL_STRING);
}

//******************************************************************************
// This method returns a bool indicating whether the age (dstrAge) passed in
// is a valid Minimum withdraw age.  The age (dstrAge) has to be greater than
// the minimum withdraw age store in the TaxJurisLimitList CBO based on the 
// Jurisdiction.
// @param   const DString& dstrAge - Age to check.
//          const DString& dstrJurisdiction - Jurisdiction to check in
//          const idDataGroup - datagroup id.
// @return bool - true if dstrAge is greater than min withdraw age for the jurisdiction.
//                false otherwise.
//******************************************************************************
bool TaxTypeRule::isValidMinimumAgeForWithdrawl( const DString& dstrAge, const DString& dstrJurisdiction, const BFDataGroupId& idDataGroup )
{
   if( doesTaxJurisdictionLimitationListExist(idDataGroup) )
   {
      if( m_pTaxJurisLimitList )
      {
         return(m_pTaxJurisLimitList->isValidMinimumAgeForWithdrawl( dstrAge, dstrJurisdiction, idDataGroup ));
      }
   }
   return(false);
}

//******************************************************************************
bool TaxTypeRule::isCarryForwardUnusedMaxApplic( const DString& dstrJurisdiction, 
				  						         const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isCarryForwardUnusedMaxApplic" ) );

	bool bIsCarryForwardUnusedMaxApplic = false;

	if ( m_pTaxJurisLimitList )
		bIsCarryForwardUnusedMaxApplic = m_pTaxJurisLimitList->isCarryForwardUnusedMaxApplic( dstrJurisdiction, 
													                                         idDataGroup );

	return bIsCarryForwardUnusedMaxApplic;
}

//******************************************************************************
bool TaxTypeRule::canUseSpousesAge( const DString& dstrJurisdiction, 
				  						         const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canUseSpousesAge" ) );

	bool bUseSpousesAge = true;

	if ( m_pTaxJurisLimitList )
		bUseSpousesAge = m_pTaxJurisLimitList->canUseSpousesAge( dstrJurisdiction, idDataGroup );

	return bUseSpousesAge;
}

//******************************************************************************

SEVERITY TaxTypeRule::isTaxTypeSchedule01Exist( bool &bApplicable, const DString& dstrPensionJuris, 
	                                            const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canUseSpousesAge" ) );

   bApplicable = false;
   DString strPensionJuris(dstrPensionJuris);
   if( !strPensionJuris.strip().empty() )
   {
	   DString strTaxTypeSchedule = getJurisLimitField( ifds::TaxTypeSchedule, strPensionJuris, idDataGroup );
	   if( strTaxTypeSchedule.strip() == I_( "01" ) )
	   {
		   bApplicable = true;
	   }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool TaxTypeRule::getCheckEligibleAge(const BFDataGroupId& idDataGroup)
{
	bool bChkAge = false;
    DString dstrCheckEligibleAge;

    getField(ifds::ChkAgeOfMajority, dstrCheckEligibleAge, idDataGroup);

    return dstrCheckEligibleAge.stripAll().upperCase() == I_("Y");
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxTypeRule.cpp-arc  $
// 
//    Rev 1.39   Feb 20 2009 14:35:02   jankovii
// IN  1557042 - Accountholder less than 55 but no warning on Desktop and a/c created
// 
//    Rev 1.38   Nov 28 2008 13:46:44   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.37   06 Oct 2008 13:20:04   kovacsro
// PET142007  FN01 TFSA
// 
//    Rev 1.36   12 Sep 2008 15:41:16   kovacsro
// PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
// 
//    Rev 1.35   01 May 2008 13:57:54   kovacsro
// PET2255 FN47 - New Ontario LIF - finalized
// 
//    Rev 1.34   15 Apr 2008 12:10:12   kovacsro
// PET2255 FN47 - New Ontario LIF
// 
//    Rev 1.33   Jan 23 2008 11:55:00   hsuchin
// Incident# 1105490 - default to allow data entry for spousal date of birth for RRIFs
// 
//    Rev 1.32   Aug 10 2007 17:07:14   smithdav
// PET2360 FN76,91
// 
//    Rev 1.31   Sep 14 2006 17:35:32   ZHANGCEL
// PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt.
// 
//    Rev 1.30   Sep 07 2006 16:53:44   porteanm
// PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt. 
// 
//    Rev 1.29   May 25 2006 17:49:56   ZHANGCEL
// PET 2102 FN01 -- Legal age related changes with new view367
// 
//    Rev 1.28   Sep 29 2005 10:26:46   purdyech
// PTS406322 - Synchronization objects around lazy init were causing deadlock in BPServer.  Object retrieval is now done at management company level and sync objects have been removed.
// 
//    Rev 1.27   Nov 14 2004 14:57:08   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.26   Feb 19 2004 14:14:56   PURDYECH
// Fixed some multithreading issues.
// 
//    Rev 1.25   Mar 21 2003 18:26:16   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.24   Oct 09 2002 23:55:06   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.23   Aug 29 2002 12:56:48   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.22   Jul 09 2002 10:23:08   HSUCHIN
// added getJurisLimitField and isValidMinimumAgeForWithdrawl to get Field values from TaxJurisLimitList based on jurisdiction and check for valid min age for withdrawl based on jurisdiction.
// 
//    Rev 1.21   08 Jun 2002 18:21:36   HERNANDO
// Added functions to validate Tax Jurisdiction and Age.
// 
//    Rev 1.20   22 May 2002 18:30:00   PURDYECH
// BFData Implementation
// 
//    Rev 1.19   25 Feb 2002 11:58:36   KOVACSRO
// Implemented isValidDepCode and isValidRedCode  methods.
// 
//    Rev 1.18   11 May 2001 10:34:40   HSUCHIN
// Sync up with SSB (1.16.1.0)
// 
//    Rev 1.17   03 May 2001 14:07:10   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.16   Feb 19 2001 15:25:00   ZHANGCEL
// Changed the parameter name in validTransfer().
// 
//    Rev 1.15   Dec 18 2000 15:23:38   DINACORN
// Fix the problem for DepositType Substitution List
// 
//    Rev 1.14   Dec 17 2000 20:24:38   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.13   Dec 12 2000 15:29:38   DINACORN
// Fix the problem for DepositType - values 01, 02, …, 09 replaced with 1, 2, …, 9
// 
//    Rev 1.12   Dec 07 2000 18:01:36   DINACORN
// Temporary CheckIn
// 
//    Rev 1.11   Nov 30 2000 10:59:30   WINNIE
// new method to validate against acct designation
// 
//    Rev 1.10   Nov 21 2000 10:20:52   HUANGSHA
// put back the subst code + desc
// 
//    Rev 1.9   Nov 17 2000 13:28:44   WINNIE
// restore methods
// 
//    Rev 1.8   Nov 16 2000 10:48:20   DINACORN
// Create the substitution lists for RedCode and DepositType which get the description from DataDictionary, not from view
// 
//    Rev 1.7   Nov 02 2000 14:11:40   VASILEAD
// Added workSeesionId parameter for Mgmtco based CBOs
// 
//    Rev 1.6   Oct 27 2000 17:58:22   HUANGSHA
// temporarily changed getAllowedCode() to get the Tax rule desc as the substitution desc
// 
//    Rev 1.5   Oct 18 2000 15:34:14   DINACORN
// Added getAcctTypeSubstList and getAccountTypeDescription methods
// 
//    Rev 1.4   Aug 08 2000 14:21:02   WINNIE
// Add business rule to validate account type based on the tax type of the account
// 
//    Rev 1.3   May 29 2000 14:46:32   BUZILA
// pDepositTypeList and pRedemptionCodeList taken out 
// 
//    Rev 1.2   May 25 2000 15:35:26   WINNIE
// add getsessionId
// 
//    Rev 1.1   May 24 2000 16:50:38   WINNIE
// Add method to get valid redemption code and deposit type
// 
//    Rev 1.0   May 18 2000 16:43:10   WINNIE
// Initial revision.
*/