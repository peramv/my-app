///******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2007, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : AMSAcctLvlList.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : June 19, 2007
//
// ^CLASS    : AMSAcctLvl
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include "AMSAcctLvlList.hpp"

#include "AMSAcctLvl.hpp"
#include "AMSAcctLvlList.hpp"
#include "amsmstrlist.hpp"
#include "errmsgruleslist.hpp"
#include "mfaccount.hpp"
#include "mfaccountholdinglist.hpp"
#include "mgmtco.hpp"
#include "shareholder.hpp"

#include <ifastdataimpl\dse_dstc0004_vw.hpp>   // MFAccount
#include <ifastdataimpl\dse_dstc0020_vw.hpp>   // MFAccountHolding
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0380_req.hpp>  // AMS Account Inquiry
#include <ifastdataimpl\dse_dstc0380_vw.hpp>   // AMS Account Inquiry


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_ACCT_LEVEL_LIST;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "AmsLmtOverrideList" );
}


namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;

}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   /*
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   */
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   {ifds::AccountNum,    BFCBO::NONE,  0}, 
   {ifds::ShrNum,        BFCBO::NONE,  0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
AMSAcctLvlList::AMSAcctLvlList( BFAbstractCBO &parent ) :
 MFCanBFCbo( parent )
,_requestData(ifds::DSTC0380_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
   registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
}


//******************************************************************************
AMSAcctLvlList::~AMSAcctLvlList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY AMSAcctLvlList::init( const DString& dstrShrNum, 
                               const DString& dstrAccountNum, 
                               const DString& dstrTrack,
                               const DString& dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   setField( ifds::AccountNum, dstrAccountNum, BF::HOST, false);
   setField (ifds::ShrNum, dstrShrNum, BF::HOST, false);

   BFData *receivedData = new BFData(ifds::DSTC0380_VW);

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId,  getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::Track,      dstrTrack );
   _requestData.setElementValue( ifds::Activity,   dstrPageName );   
   _requestData.setElementValue( ifds::AccountNum, dstrAccountNum );   
//   _requestData.setElementValue( ifds::AMSType,    dstrAMSType );   
	
   ReceiveData( DSTC_REQUEST::AMS_ACCT_LEVEL_LIST, 
                _requestData, *receivedData, 
                DSTCRequestor( getSecurity(), 
                false, 
                false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSAcctLvlList::initNew ( const DString& dstrShrNum, 
                                   const DString& dstrAccountNum)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   setField (ifds::AccountNum, dstrAccountNum, BF::HOST, false);
   setField (ifds::ShrNum, dstrShrNum, BF::HOST, false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AMSAcctLvlList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   AMSAcctLvl * pAMSAcctLvl = new AMSAcctLvl( *this );
   pAMSAcctLvl->init( data );
   pObjOut = pAMSAcctLvl;

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
SEVERITY AMSAcctLvlList::doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   AMSAcctLvl *pAMSAcctLvl = new AMSAcctLvl (*this);
   if( pAMSAcctLvl->initNew( idDataGroup) <= WARNING )
   {
      pBase = pAMSAcctLvl;		
   }   

   return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************************
SEVERITY AMSAcctLvlList::doValidateAll ( const BFDataGroupId& idDataGroup, 
                                         long lValidateGroup)
{ 
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll" ));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AMSAcctLvlList.cpp-arc  $
// 
//    Rev 1.5   14 Sep 2007 10:59:24   popescu
// Incident 1003183 (GAP2360/02) - fixed AMS allocations
// 
//    Rev 1.4   Aug 30 2007 10:18:00   smithdav
// Add AccountNum parameter to the initNew of the AMSAcctLvlList.
// 
//    Rev 1.3   Jul 18 2007 09:35:36   smithdav
// PET2360 FN02
// 
//    Rev 1.2   Jul 11 2007 16:21:38   smithdav
// PET 2360 FN02 - AMS - Interim changes
// 
//    Rev 1.1   Jun 22 2007 14:18:42   porteanm
// PET 2360 FN02 - AMS - work in progress.
// 
//    Rev 1.0   Jun 20 2007 11:42:56   porteanm
// Initial revision.
// 
*/
