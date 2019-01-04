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
// ^FILE   : ProtectedFundList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/2003
//
// ^CLASS    : ProtectedFundList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "ProtectedFundList.hpp"
#include "ProtectedFund.hpp"
#include <ifastdataimpl\dse_dstc0237_req.hpp>
#include <ifastdataimpl\dse_dstc0237_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PROTECTED_FUND_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_( "ProtectedFundList" );
   const I_CHAR *  FUNDCODE   = I_( "FundCode" );
   const I_CHAR *  CLASSCODE  = I_( "ClassCode" );
}



//******************************************************************************
ProtectedFundList::ProtectedFundList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
ProtectedFundList::~ProtectedFundList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY ProtectedFundList::init(const BFDataGroupId& idDataGroup/*=BF::HOST*/, 
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0237_REQ);
   DString mgmtCoIdOut;

   queryData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
   queryData.setElementValue(ifds::Track, dstrTrack);
   queryData.setElementValue(ifds::Activity, dstrPageName);

   ReceiveData(DSTC_REQUEST::PROTECTED_FUND_LIST, queryData, 
      ifds::DSTC0237_VW, DSTCRequestor(getSecurity()));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ProtectedFundList::doCreateNewObject(BFCBO *&pBase, DString &strKey, 
   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new ProtectedFund( *this );
   ((ProtectedFund* )pBase)->init( idDataGroup );    

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY ProtectedFundList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   ProtectedFund * pProtectedFund = new ProtectedFund( *this );
   pProtectedFund->init( data );
   pObjOut = pProtectedFund;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//used when refreshing a function
SEVERITY ProtectedFundList::reInit()
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );

   return init();
}

//*************************************************************
void ProtectedFundList::getStrKey( DString &strKey, const BFData *data )
{
   if (data) 
   {
      DString dstrFundCode  = data->getElementValue( ifds::FundCode );
      DString dstrClassCode = data->getElementValue( ifds::ClassCode );
      buildKey(strKey, dstrFundCode, dstrClassCode);
   }
   else
   {
      BFCBO::getStrKey(strKey, NULL);
   }
}

//*************************************************************
bool ProtectedFundList::isProtectedFund (const DString& dstrFundCode, 
   const DString& dstrClassCode, const BFDataGroupId& idDataGroup )
{
   DString dstrKey;
   DString dstrFund (dstrFundCode), dstrClass(dstrClassCode);

   buildKey(dstrKey, dstrFund, dstrClass);
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   iter.setKeyFilter(dstrKey);
   return !iter.end();
}

//*************************************************************
void ProtectedFundList::buildKey( DString& dstrKey, DString &dstrFundCode, DString &dstrClassCode )
{
   dstrKey = dstrFundCode.strip() + I_( " " ) + dstrClassCode.strip();
   dstrKey.strip().upperCase() ;   
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ProtectedFundList.cpp-arc  $
// 
//    Rev 1.10   Nov 14 2004 14:51:14   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   May 27 2003 18:29:48   popescu
// due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
// 
//    Rev 1.8   Mar 21 2003 18:20:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Feb 06 2003 10:34:48   WINNIE
// change isProtectedFund input parameters to const since call methods have fund and class as constant.
// 
//    Rev 1.6   Feb 05 2003 15:56:30   HSUCHIN
// added get string key and new method to check if fund/class passed in is a protected fund
// 
//    Rev 1.5   Feb 03 2003 11:54:12   popescu
// Changes to support the KeyString field of view 249
// 
//    Rev 1.4   Jan 26 2003 15:51:00   popescu
// Added the Revsion Control entry section
 */