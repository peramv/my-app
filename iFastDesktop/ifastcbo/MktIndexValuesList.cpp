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
// ^FILE   : MktIndexValuesList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "MktIndexValuesList.hpp"
#include "MktIndexValues.hpp"
#include "MktIndexMasterList.hpp"
#include "MktIndexMaster.hpp"
#include <ifastdataimpl\dse_dstc0247_vw.hpp>
#include <ifastdataimpl\dse_dstc0247_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MKT_INDEX_VALUES_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "MktIndexValuesList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId IndexName;
   extern CLASS_IMPORT const BFTextFieldId SearchIndexType;
   extern CLASS_IMPORT const BFTextFieldId InputDataType;
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                     State Flags,      Group Flags 
	{ ifds::SearchIndexType,      BFCBO::REQUIRED,         0},
    { ifds::FromDate,		      BFCBO::NONE,             0},
	{ ifds::IndexCode,            BFCBO::REQUIRED,         0 },  
};
static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//******************************************************************************

MktIndexValuesList::MktIndexValuesList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), 
m_requestData( ifds::DSTC0247_REQ ), 
m_dstrIndexCodeSubstitution( NULL_STRING ),
m_dstrInitialIndexCode( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   // Determine Substitution String for Index Code
   // Initialize substitution for Index Code
   MktIndexMasterList *pMktIndexMasterList = NULL;
   getWorkSession().getMktIndexMasterList(pMktIndexMasterList, BF::HOST, true );
   if( pMktIndexMasterList )
   {
      DString dstrIndexCode, dstrIndexName;
      BFObjIter bfObjIter( *pMktIndexMasterList, BF::HOST, BFObjIter::ITERTYPE::NON_DELETED );
      while( !bfObjIter.end() )
      {
         bfObjIter.getObject()->getField( ifds::IndexCode, dstrIndexCode, BF::HOST, false );
         bfObjIter.getObject()->getField( ifds::IndexName, dstrIndexName, BF::HOST, false );
         dstrIndexCode.stripLeading().stripTrailing();
         dstrIndexName.stripLeading().stripTrailing();
         if( m_dstrInitialIndexCode.empty() )
         {
            m_dstrInitialIndexCode = dstrIndexCode;
         }
         m_dstrIndexCodeSubstitution += dstrIndexCode + I_("=") + dstrIndexName + I_(";");
         ++bfObjIter;
      }
   }
   DString strSub = I_("ALL=ALL;") + m_dstrIndexCodeSubstitution;
   setFieldAllSubstituteValues( ifds::SearchIndexType, BF::HOST, strSub );
   setFieldNoValidate (ifds::SearchIndexType, I_("ALL"), BF::HOST, false, true, true);
}

//******************************************************************************

MktIndexValuesList::~MktIndexValuesList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MktIndexValuesList::init(const BFDataGroupId& idDataGroup,
                               const DString& dstrTrack,
                               const DString& dstrPageName,
                               const DString& dstrSearchType,
							   const DString& dstrIndexCode,
                               const DString& dstrFromDate,
                               const DString& dstrToDate)
// Currently, the valid SearchTypes are "ALL", "INDEXCODE", "DEFF"
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   m_requestData.setElementValue( ifds::NextKey, NULL_STRING );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );
   m_requestData.setElementValue( ifds::SearchType, dstrSearchType );
    m_requestData.setElementValue( ifds::IndexCode, dstrIndexCode );
   m_requestData.setElementValue( ifds::FromDate, dstrFromDate );
   m_requestData.setElementValue( ifds::ToDate, dstrToDate );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   ReceiveData(DSTC_REQUEST::MKT_INDEX_VALUES_LIST, m_requestData, ifds::DSTC0247_VW, DSTCRequestor(getSecurity(), false, false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MktIndexValuesList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      ReceiveData(DSTC_REQUEST::MKT_INDEX_VALUES_LIST, m_requestData, ifds::DSTC0247_VW, DSTCRequestor(getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MktIndexValuesList::reInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************

SEVERITY MktIndexValuesList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut =  new MktIndexValues( *this );
   ((MktIndexValues*) pObjOut)->init( data, m_dstrIndexCodeSubstitution );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************

SEVERITY MktIndexValuesList::doCreateNewObject( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   pObjOut =  new MktIndexValues( *this );
   ((MktIndexValues*) pObjOut)->initNew( idDataGroup, m_dstrIndexCodeSubstitution, m_dstrInitialIndexCode );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************

SEVERITY MktIndexValuesList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************

void  MktIndexValuesList::getStrKey( DString &strKey, const BFData *data  )
{
   BFCBO::getStrKey( strKey, NULL );
}

//**********************************************************************************

bool MktIndexValuesList::isDuplicate( DString &dstrIndexCode, 
                                      DString &dstrEffectiveDate,
                                      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isDuplicate") );

	short nFound = 0;
   DString dstrIndexCodeTmp, dstrEffectiveDateTmp, dstrStatusTmp;

   // Check current list
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() && nFound < 2)
   {
      iter.getObject()->getField( ifds::IndexCode, dstrIndexCodeTmp, idDataGroup, false );
      iter.getObject()->getField( ifds::EffectiveDate, dstrEffectiveDateTmp, idDataGroup, false );
      iter.getObject()->getField( ifds::GoodBad, dstrStatusTmp, idDataGroup, false );

      dstrIndexCodeTmp.strip().upperCase();
      dstrEffectiveDateTmp.strip().upperCase();
      dstrStatusTmp.strip().upperCase();

      if( dstrStatusTmp == I_("Y") && 
          dstrIndexCodeTmp == dstrIndexCode && 
          dstrEffectiveDateTmp == dstrEffectiveDate )
      {
         ++nFound;
      }
      ++iter;
   }

   if( nFound > 1 )
      return true;

   // Check Back-End
	BFData requestData( ifds::DSTC0247_REQ );

   requestData.setElementValue( ifds::NextKey, NULL_STRING );
   requestData.setElementValue( ifds::Track, I_("N") );
   requestData.setElementValue( ifds::Activity, NULL_STRING );
   requestData.setElementValue( ifds::SearchType, I_("INDEXCODE") );
   requestData.setElementValue( ifds::IndexCode, dstrIndexCode );
   requestData.setElementValue( ifds::FromDate, dstrEffectiveDate );
   requestData.setElementValue( ifds::ToDate, dstrEffectiveDate );

   SEVERITY sevRtn = SEVERE_ERROR;
	DSTCRequestor requestor( getSecurity(), true, true );
	BFData receivedData(ifds::DSTC0247_VW);
	bool bExist = false;

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   ReceiveData(DSTC_REQUEST::MKT_INDEX_VALUES_LIST, requestData, ifds::DSTC0247_VW, DSTCRequestor(getSecurity(), false, false) );

   if( BFDataBroker::getInstance( )->receive( DSTC_REQUEST::MKT_INDEX_VALUES_LIST, 
		requestData, receivedData, requestor ) <= WARNING )
	{
		bExist = true;
	}
	CLEARCONDITIONS();

	return bExist;
}
//******************************************************************************************************************************
DString MktIndexValuesList::getInputDataType(DString indexCode,const BFDataGroupId& idDataGroup,bool bIndexName /*FALSE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getInputDataType" ) );

   DString dstrIndexCode,dstrInputDataType;
   MktIndexMasterList *pMktIndexMasterList = NULL;
   getWorkSession().getMktIndexMasterList(pMktIndexMasterList, BF::HOST, true );
   if( pMktIndexMasterList )
   {
	   DString dstrIndexName;
	   BFObjIter bfObjIter( *pMktIndexMasterList, BF::HOST, BFObjIter::ITERTYPE::NON_DELETED );
	   while( !bfObjIter.end() )
	   {
		   bfObjIter.getObject()->getField( ifds::IndexCode, dstrIndexCode, BF::HOST, false );
		   bfObjIter.getObject()->getField( ifds::IndexName, dstrIndexName, BF::HOST, false );
		   dstrIndexCode.stripLeading().stripTrailing();
		   
		   if( bIndexName )
		   {
			   if( dstrIndexName == indexCode )
			   {
				   bfObjIter.getObject()->getField( ifds::InputDataType, dstrInputDataType, BF::HOST, false ); 
				   break;
			   }
		   }
		   else 
		   {
			   if( dstrIndexCode == indexCode )
			   {
				   bfObjIter.getObject()->getField( ifds::InputDataType, dstrInputDataType, BF::HOST, false );
				   break;
			   }
		   }		  
		   ++bfObjIter;
	   }
   }
   return dstrInputDataType;
}
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexValuesList.cpp-arc  $
// 
//    Rev 1.8   Jan 16 2012 17:23:40   wp040027
// P0188394_Performance Fees
// 
//    Rev 1.7   Jan 16 2012 14:34:32   wp040027
// P0188394_Performance Fees - Benchmark Upload
// 
//    Rev 1.6   Nov 14 2004 14:50:40   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   May 16 2003 17:33:44   HERNANDO
// Initialize IndexCode.
// 
//    Rev 1.4   Mar 21 2003 18:19:38   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Feb 06 2003 14:43:52   HERNANDO
// Add back-end duplicate check.
// 
//    Rev 1.2   Feb 06 2003 10:40:56   HERNANDO
// Revised.
// 
//    Rev 1.1   Jan 29 2003 18:35:04   HERNANDO
// Revised.
// 
//    Rev 1.0   Jan 29 2003 11:39:34   HERNANDO
// Initial Revision
//
