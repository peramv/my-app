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
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : ShrAllocType.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : ShrAllocType
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : former shareholder level allocation
//
//******************************************************************************
#include "stdafx.h"
#include "defacctalloclist.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "shralloctype.hpp"
#include "shralloctypelist.hpp"
#include <ifastdataimpl\dse_dstc0058_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME                 = I_( "ShrAllocType" );
   const I_CHAR * const DEFAULTACCOUNTALLOCATIONS = I_( "DefAcctAllocList" );
   const I_CHAR * const ONE_HUNDRED               = I_( "100.0000" );
   const I_CHAR * const SHR_LEVEL                 = I_( "1" );
}

namespace CND
{  // Conditions used
   extern const long ERR_RO_EFF_DATE;
   extern const long WARN_RO_EFF_DATE;
   extern const long ERR_RB_EFFECTIVEDATE;
}

namespace IFASTERR
{
	extern CLASS_IMPORT I_CHAR * const RO_EFF_DATE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId rxTransTypeJapanese;
   extern CLASS_IMPORT const BFDecimalFieldId Level;
   extern CLASS_IMPORT const BFTextFieldId rxTransType;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId TaxTransTypes;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				  State Flags,					Group Flags
   { ifds::TransType,       BFCBO::REQUIRED, 0 }, 
   { ifds::EffectiveDate,   BFCBO::REQUIRED, 0 }, 
   { ifds::DistribDetlVer,  BFCBO::NONE,     0 }, 
   { ifds::DistribDetlRid,  BFCBO::NONE,     0 }, 
   { ifds::Level,           BFCBO::NONE,     0 }, 
   { ifds::AllocPercentage, BFCBO::NONE,     0 }, 
   { ifds::AccountNum,      BFCBO::NONE,     0 }, 
       //cross edits
   { ifds::TaxTransTypes, BFCBO::IMMEDIATE_VALIDATION, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                  State Flags,      Group Flags 
   { I_( "DefAcctAllocList" ),        BFCBO::NONE,     0},

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );


//******************************************************************************
ShrAllocType::ShrAllocType( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_allowRBROEffectiveDateChange( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo );

   addCrossEdit(ifds::TaxTransTypes, ifds::TransType);
   addCrossEdit(ifds::TaxTransTypes, ifds::EffectiveDate);
}

//******************************************************************************
ShrAllocType::~ShrAllocType( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY ShrAllocType::initNew( const BFDataGroupId& idDataGroup,
                                const DString& dstrTrack,
                                const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void ShrAllocType::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString dstrEffectiveDate;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrEffectiveDate, idDataGroup, false);
   setFieldNoValidate( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false, false, true );
   setFieldNoValidate( ifds::AllocPercentage, ONE_HUNDRED, idDataGroup, false, false, true );
   setFieldNoValidate(ifds::Level, SHR_LEVEL, idDataGroup, false);

   loadSubstitutions( idDataGroup );
}
//******************************************************************************

SEVERITY ShrAllocType::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );


   attachDataObject( const_cast< BFData & >( data ), false, true ); 
   //setFieldReadOnly(DBR::EffectiveDate, BF::HOST, true);
   setFieldReadOnly(ifds::TransType, BF::HOST, true);
   //have to create the account allocation list
   DefAcctAllocList* pDefAcctAllocList = new DefAcctAllocList(*this);
   if( pDefAcctAllocList->initExisting() <= WARNING )
      setObject(pDefAcctAllocList, DEFAULTACCOUNTALLOCATIONS);
   else
      delete pDefAcctAllocList;

   loadSubstitutions( BF::HOST );
   clearUpdatedFlags( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

MFCanBFCbo* ShrAllocType::getTopLevelCBO()
{
   return( dynamic_cast<MFCanBFCbo*>(getParent()->getParent()) );
}
//******************************************************************************

SEVERITY ShrAllocType::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if( idField == ifds::TransType || idField == ifds::EffectiveDate )
   {
      DefAcctAllocList *pAcctAllocList = NULL;
      getAccountAllocationList(pAcctAllocList, idDataGroup, false); 
      if( pAcctAllocList )
      {
         DString strValue;
         getField(idField, strValue, idDataGroup, false);
         pAcctAllocList->setField(idField, strValue, idDataGroup, false);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY ShrAllocType::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::TaxTransTypes )
     validateTransTypeEffDate( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ShrAllocType::loadSubstitutions( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadSubstitutions" ) );

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN )
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::rxTransTypeJapanese );
   else  // for Canada and any other market
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::rxTransType);

   return(GETCURRENTHIGHESTSEVERITY());

}
//******************************************************************************

SEVERITY ShrAllocType::getAccountAllocationList(DefAcctAllocList *&pAcctAllocList, const BFDataGroupId& idDataGroup, bool bCreate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountAllocationList" ) );

   pAcctAllocList = dynamic_cast<DefAcctAllocList * >(
                                                     getObject( DEFAULTACCOUNTALLOCATIONS, idDataGroup ));

   if( !pAcctAllocList && bCreate )
   {
      pAcctAllocList = new DefAcctAllocList(*this);
      if( pAcctAllocList->initNew(idDataGroup) <= WARNING )
         setObject(pAcctAllocList, DEFAULTACCOUNTALLOCATIONS, OBJ_ACTIVITY_NONE, idDataGroup);
      else
      {
         delete pAcctAllocList;
         pAcctAllocList = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool ShrAllocType::hasDefaultAllocations(const DString& strAccNum, const BFDataGroupId& idDataGroup)
{
   DString strAccNumIn(strAccNum);
   if( strAccNumIn.strip().stripLeading('0').empty() )
      return false;
   
   DefAcctAllocList *pDefAcctAllocList = NULL;
   if( getAccountAllocationList(pDefAcctAllocList, idDataGroup)<=WARNING )
   {
      BFObjIter iter(*pDefAcctAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
      while( !iter.end() )
      {
         BFAbstractCBO* pDefAcctAlloc = iter.getObject();
         assert(pDefAcctAlloc);
         DString strAccountNum;
         pDefAcctAlloc->getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
         if( strAccNumIn == strAccountNum.strip().stripLeading('0') )
            return true;
         ++iter;
      }
   }
   
   return false;
}

//******************************************************************************

void ShrAllocType::clearAllocations(const BFDataGroupId& idDataGroup)
{
   DefAcctAllocList *pAcctAllocList = NULL;
   if( getAccountAllocationList(pAcctAllocList, idDataGroup, false) <= WARNING )
   {
      if( pAcctAllocList )
      {
         pAcctAllocList->clearAllocations( idDataGroup );
      }
   }

}

//******************************************************************************

SEVERITY ShrAllocType::validateTransTypeEffDate( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTransTypeEffDate" ) );

   if( _allowRBROEffectiveDateChange )
   {
	   return(GETCURRENTHIGHESTSEVERITY());
   }

   DString dstrTransType, dstrEffectiveDate, dstrOldEffectiveDate;
   getField( ifds::TransType, dstrTransType, idDataGroup );
   dstrTransType.strip().upperCase();

   getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
   dstrEffectiveDate.strip();

   if( dstrTransType == I_( "RB" ) || dstrTransType == I_( "RO" ) )
   {
	   getFieldBeforeImage( ifds::EffectiveDate, dstrOldEffectiveDate, false );
	   dstrOldEffectiveDate.strip();
	   
	   if( dstrTransType == I_( "RO" ) )
	   {
	     //only applies for existing records; user can modify EffectiveDate for new records
		 if ( !dstrOldEffectiveDate.empty() &&
			  DSTCommonFunctions::CompareDates( dstrOldEffectiveDate, dstrEffectiveDate ) != DSTCommonFunctions::EQUAL )
		 {
           getErrMsg (IFASTERR::RO_EFF_DATE,
								CND::ERR_RO_EFF_DATE, 
								CND::WARN_RO_EFF_DATE, 
								idDataGroup);
		 }
	   }
	   else//RB
	   {
		 //Oct. 19 applies both for Existing and new records 
		 //Nov. 5, 2007 - No, it only applies for existing records!
         if ( !dstrOldEffectiveDate.empty() &&
			  DSTCommonFunctions::CompareDates( dstrOldEffectiveDate, dstrEffectiveDate ) != DSTCommonFunctions::EQUAL )
		 {
		   ADDCONDITIONFROMFILE( CND::ERR_RB_EFFECTIVEDATE );
		 }
	   }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void ShrAllocType::allowRBROEffectiveDateChange( bool blAllow )
{
	_allowRBROEffectiveDateChange = blAllow;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrAllocType.cpp-arc  $
// 
//    Rev 1.9   05 Nov 2007 14:50:24   kovacsro
// IN#1038318 - requirements have changed: RB effective date check only applies for existing records (so new RB records can be added into the system, via Allocations process)
// 
//    Rev 1.8   19 Oct 2007 16:18:26   kovacsro
// IN#1038318 - added rej erros / hard edit to prevent users from entering future dated Stop dates on AMS and modifying Effective Date for RB/RO default allocations on Allocation screen
// 
//    Rev 1.7   Nov 14 2004 14:55:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Mar 21 2003 18:24:44   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Dec 04 2002 17:34:34   HERNANDO
// Added clearAllocations.
// 
//    Rev 1.4   Nov 18 2002 13:37:54   KOVACSRO
// Added  hasDefaultAllocations.
// 
//    Rev 1.3   Oct 09 2002 23:55:02   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Aug 29 2002 12:56:40   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.1   22 May 2002 18:29:52   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   22 Apr 2002 13:00:04   KOVACSRO
// Initial revision.
 * 
 * 
 */