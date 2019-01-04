//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : SettleLocationAcctLvlList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "SettleLocationAcctLvlList.hpp"
#include "SettleLocationAcctLvl.hpp"
#include "SettleLocationSysLvlList.hpp"
#include "SettleLocationSysLvl.hpp"
#include <dataimpl\dse_dstc0269_vw.hpp>
#include <dataimpl\dse_dstc0269_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SETTLE_LOCATION_ACCT_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "SettleLocationAcctLvlList" );
}

namespace CND
{
   extern const long ERR_MISSING_DEFAULT;
   extern const long ERR_MULTIPLE_DEFAULT;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Active;
}

//******************************************************************************

SettleLocationAcctLvlList::SettleLocationAcctLvlList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), 
m_requestData( ifds::DSTC0269_REQ ), 
m_dstrSettleLocationCodeSubstitution( NULL_STRING ),
m_dstrInitialSettleLocationCode( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );

   // Determine Substitution String for Settle Location Code
   // Initialize substitution for Settle Location Code

   SettleLocationSysLvlList *pSettleLocationSysLvlList = NULL;
   getWorkSession().getSettlementLocationSysLvlList( pSettleLocationSysLvlList, BF::HOST, true );
   while( pSettleLocationSysLvlList && pSettleLocationSysLvlList->doMoreRecordsExist() )
   {
      pSettleLocationSysLvlList->getMore();
   }
   if( pSettleLocationSysLvlList )
   {
      DString dstrSettleLocationCode, dstrSettleLocationDesc, dstrActive;
      BFObjIter bfObjIter( *pSettleLocationSysLvlList, BF::HOST, BFObjIter::ITERTYPE::NON_DELETED );
      while( !bfObjIter.end() )
      {
         bfObjIter.getObject()->getField( ifds::SettleLocationCode, dstrSettleLocationCode, BF::HOST, false );
         bfObjIter.getObject()->getField( ifds::SettleLocationDesc, dstrSettleLocationDesc, BF::HOST, false );
         bfObjIter.getObject()->getField( ifds::Active, dstrActive, BF::HOST, false );
         dstrSettleLocationCode.stripLeading().stripTrailing();
         dstrSettleLocationDesc.stripLeading().stripTrailing();
         dstrActive.stripAll().upperCase();
         if( dstrActive == I_("Y") )
         {
            if( m_dstrInitialSettleLocationCode.empty() )
            {
               m_dstrInitialSettleLocationCode = dstrSettleLocationCode;
            }
            m_dstrSettleLocationCodeSubstitution += dstrSettleLocationCode + I_("=") + dstrSettleLocationDesc + I_(";");
         }
         ++bfObjIter;
      }
   }
}

//******************************************************************************

SettleLocationAcctLvlList::~SettleLocationAcctLvlList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY SettleLocationAcctLvlList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY SettleLocationAcctLvlList::init(const DString& dstrAccountNum,
                                         const DString& dstrTrack,
                                         const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   m_requestData.setElementValue( ifds::NextKey, NULL_STRING );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );
   m_requestData.setElementValue( ifds::AccountNum, dstrAccountNum );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   ReceiveData(DSTC_REQUEST::SETTLE_LOCATION_ACCT_INQUIRY, m_requestData, ifds::DSTC0269_VW, DSTCRequestor(getSecurity(), false, false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY SettleLocationAcctLvlList::reInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************

SEVERITY SettleLocationAcctLvlList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut =  new SettleLocationAcctLvl( *this );
   ((SettleLocationAcctLvl*) pObjOut)->init( data, m_dstrSettleLocationCodeSubstitution );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************

SEVERITY SettleLocationAcctLvlList::doCreateNewObject( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   pObjOut =  new SettleLocationAcctLvl( *this );
   ((SettleLocationAcctLvl*) pObjOut)->initNew( idDataGroup, m_dstrSettleLocationCodeSubstitution, m_dstrInitialSettleLocationCode );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************

SEVERITY SettleLocationAcctLvlList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   // Check to ensure that one list item is marked default if a list exists.
	short nFound = 0;
   DString dstrDefault;

   // Check list
   bool bList = false;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() && nFound < 2)
   {
      if( !iter.isDummy() )
      {
         bList = true;
         iter.getObject()->getField( ifds::Default, dstrDefault, idDataGroup, false );
         dstrDefault.stripAll().upperCase();
         if( dstrDefault == I_("Y") ) 
         {
            ++nFound;
         }
      }
      ++iter;
   }
   if( bList )
   {
      if( nFound == 0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_DEFAULT );
      }
      else if( nFound > 1 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_DEFAULT ); // This is backup.  Should be caught earlier.
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************

void  SettleLocationAcctLvlList::getStrKey( DString &strKey, const BFData *data  )
{
   BFCBO::getStrKey( strKey, NULL );
}

//**********************************************************************************

bool SettleLocationAcctLvlList::isDuplicateSettlementLocation( DString &dstrSettleLocationCode, 
                                      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isDuplicateSettlementLocation") );

	short nFound = 0;
   DString dstrSettleLocationCodeTmp;

   // Check current list
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() && nFound < 2)
   {
      iter.getObject()->getField( ifds::SettleLocationCode, dstrSettleLocationCodeTmp, idDataGroup, false );
      dstrSettleLocationCodeTmp.stripAll().upperCase();
      if( dstrSettleLocationCodeTmp == dstrSettleLocationCode ) 
      {
         ++nFound;
      }
      ++iter;
   }

   return( nFound > 1 );
}

//**********************************************************************************

bool SettleLocationAcctLvlList::isDuplicateDefault( DString &dstrDefault, 
                                      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isDuplicateDefault") );

   short nFound = 0;

   if( dstrDefault == I_("Y") )
   {
      DString dstrDefaultTmp;

      // Check current list
      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() && nFound < 2)
      {
         iter.getObject()->getField( ifds::Default, dstrDefaultTmp, idDataGroup, false );
         dstrDefaultTmp.stripAll().upperCase();
         if( dstrDefaultTmp == dstrDefault ) 
         {
            ++nFound;
         }
         ++iter;
      }
   }

   return( nFound > 1 );
}

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettleLocationAcctLvlList.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:53:50   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Nov 27 2003 18:11:36   HERNANDO
// Changed checking in doValidateAll.
// 
//    Rev 1.1   Nov 24 2003 18:12:10   HERNANDO
// Next revision.
// 
//    Rev 1.0   Nov 20 2003 11:08:42   HERNANDO
// Initial revision.
