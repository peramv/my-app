//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : FamilyCodeList.cpp
// ^AUTHOR : 
// ^DATE   : Oct, 2011
//
// ^CLASS    : FamilyCodeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0235_vw.hpp>
#include <ifastdataimpl\dse_dstc0235_req.hpp>
#include <ifastdataimpl\dse_dstc0235_vwrepeat_record.hpp>

#include "FamilyCode.hpp"
#include "FamilyCodeList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FAMILY_MASTER;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "FamilyCodeList" );
}

namespace ifds
{
}

namespace CND
{
}

//******************************************************************************
FamilyCodeList::FamilyCodeList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
, requestData235(NULL)
, _bRefresh(true)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( 0,
                       NULL,
                       0,
                       NULL );

   setObjectAsList( );
}

//******************************************************************************
FamilyCodeList::~FamilyCodeList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if ( requestData235 != NULL )
   {
      delete requestData235;
      requestData235 = NULL;
   }
}

//********************************************************************************
SEVERITY FamilyCodeList::init(const DString& dstrFamilyCode,
                              const DString& dstrFamilyName,
                              const DString& dstrExactMatch,
                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;
   requestData235 = new BFData(ifds::DSTC0235_REQ);

   requestData235->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData235->setElementValue( ifds::FamilyCode, dstrFamilyCode );
   requestData235->setElementValue( ifds::FamilyName, dstrFamilyName );
   requestData235->setElementValue( ifds::ExactMatch, dstrExactMatch );
   requestData235->setElementValue( ifds::Track, I_( "N" ) );
   requestData235->setElementValue( ifds::Activity, NULL_STRING );

   BFData* responseData = new BFData (ifds::DSTC0235_VW);
   ReceiveData( DSTC_REQUEST::FAMILY_MASTER,
                *requestData235, 
                *responseData, 
                DSTCRequestor (getSecurity(), true));
   _bRefresh = false;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FamilyCodeList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new FamilyCode( *this );
   ((FamilyCode*) pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FamilyCodeList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::FAMILY_MASTER, 
                  *requestData235, 
                  ifds::DSTC0235_VW, 
                  DSTCRequestor( getSecurity(), false ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool FamilyCodeList::isFamilyCodeExisted(const DString& dstrLookForCode, const BFDataGroupId& idDataGroup)
{
   bool bReturn = false;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      FamilyCode* pObj = dynamic_cast<FamilyCode*>(iter.getObject());
      if(pObj)
      {
         DString strFamilyCode;
         pObj->getField(ifds::FamilyCode, strFamilyCode, idDataGroup, false);
         strFamilyCode.strip();
         
         if(dstrLookForCode == strFamilyCode)
         {
            bReturn = true;
            break;
         }
      }
      ++iter; 
   }

   return bReturn;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FamilyCodeList.cpp-arc  $
// 
//    Rev 1.1   Nov 17 2011 19:12:46   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.0   Nov 08 2011 11:47:00   dchatcha
// Initial revision.
// 