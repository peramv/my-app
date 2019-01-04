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
// ^FILE   : InternWire.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/08/2000
//
// ^CLASS    : InternWire
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "InternWire.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0210_req.hpp>
#include <ifastdataimpl\dse_dstc0210_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INTERNATIONAL_WIRE;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "InternWire" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId GroupCode;
   extern CLASS_IMPORT const BFTextFieldId DepAllowed;
}

//****************************************************************************
InternWire::InternWire( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
m_strFund(NULL_STRING),
m_strClass(NULL_STRING),
m_strSettleCurr(NULL_STRING),
m_strCountryCode(NULL_STRING),
m_bInternationalWire(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//****************************************************************************
InternWire::~InternWire()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************
SEVERITY InternWire::init( const DString& strFundCode, 
                           const DString& strClassCode,
                           const DString& strSettleCurrency, 
                           const DString& strCountryCode,
                           const DString& dstrTrack,
                           const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   assert(0);//~IntWireStuff~
   return(NO_CONDITION);//~IntWireStuff~

   if( strFundCode==m_strFund && strClassCode==m_strClass && 
       strSettleCurrency==m_strSettleCurr && strCountryCode==m_strCountryCode )
   {
      return(NO_SEVERITY);
   }

   //make the view call
   BFData requestData( ifds::DSTC0210_REQ );
   BFData receivedData( ifds::DSTC0210_VW );

   DString mgmtCoIdOut;

   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::FundCode, strFundCode );
   requestData.setElementValue( ifds::ClassCode, strClassCode );
   requestData.setElementValue( ifds::SettleCurrency, strSettleCurrency );
   requestData.setElementValue( ifds::CountryCode, strCountryCode );

   if( BFDataBroker::getInstance( )->receive( DSTC_REQUEST::INTERNATIONAL_WIRE, requestData, 
                                              receivedData, DSTCRequestor( getSecurity(), true, true ) ) <= WARNING )
   {
      m_strFund=strFundCode;
      m_strClass=strClassCode;
      m_strSettleCurr=strSettleCurrency;
      m_strCountryCode=strCountryCode;
      DString strIntWire;
      receivedData.getElementValue( ifds::InternationalWire, strIntWire );
      m_bInternationalWire = strIntWire.strip() == YES;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

bool InternWire::isInternationalWire()
{
   return(m_bInternationalWire);
}



//****************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InternWire.cpp-arc  $
// 
//    Rev 1.5   Nov 14 2004 14:48:38   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   Mar 21 2003 18:17:00   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Oct 09 2002 23:54:42   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Sep 09 2002 12:15:30   KOVACSRO
// Sync-up PTS 10009768 : removed corr bank edit check 
// 
//    Rev 1.1   Aug 29 2002 12:56:04   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.0   Jun 07 2002 17:57:16   KOVACSRO
// Initial revision.

*/


