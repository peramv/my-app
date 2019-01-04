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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TransactionExternalLinksList.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : August, 2004
//
// ^CLASS    : TransactionExternalLinksList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "TransactionExternalLinkslist.hpp"

#include <ifastdataimpl\dse_dstc0314_req.hpp>
#include <ifastdataimpl\dse_dstc0314_vw.hpp>     
#include <ifastdataimpl\dse_dstc0314_vw.hpp>     

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSACTION_EXTERNAL_LINKS_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("TransactionExternalLinksList");
}

namespace CND
{  // Conditions used   
	extern const long ERR_DUPLICATE_RECORD;	
}

//******************************************************************************
TransactionExternalLinksList::TransactionExternalLinksList(BFAbstractCBO &parent)
: MFCanBFCbo(parent),
_pRequestData(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
TransactionExternalLinksList::~TransactionExternalLinksList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}

//******************************************************************************
SEVERITY TransactionExternalLinksList::init( const DString &dstrTransNum,
														   const DString &dstrTransId,
														   const BFDataGroupId &idDataGroup, // BF::HOST
														   const DString& dstrTrack,         // I_("N"), 
														   const DString &dstrPageName )     // NULL_STRING )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
    	
   _pRequestData = new BFData (ifds::DSTC0314_REQ);

   DString mgmtCoIdOut;

   _pRequestData->setElementValue (ifds::TransNum,  dstrTransNum );
   _pRequestData->setElementValue (ifds::TransId,   dstrTransId );   
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue (ifds::Track,     dstrTrack );
   _pRequestData->setElementValue (ifds::Activity,  dstrPageName );

	ReceiveData( DSTC_REQUEST::TRANSACTION_EXTERNAL_LINKS_LIST, 
		          *_pRequestData, 
					 ifds::DSTC0314_VW, 
					 DSTCRequestor( getSecurity() ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TransactionExternalLinksList::getStrKey( DString &dstrKey, const BFData *data )
{
   if( data ) 
   {
      DString dstrExternalIdType, dstrExternalId;		
		data->getElementValue(ifds::ExternalIdType, dstrExternalIdType );
		data->getElementValue(ifds::ExternalId,     dstrExternalId );		
      		   
      buildKey( dstrKey, 
					 dstrExternalIdType, 
					 dstrExternalId );
   }
   else
   {
      BFCBO::getStrKey( dstrKey, NULL);
   }
}

//creates a unique key for the list
//******************************************************************************
void TransactionExternalLinksList::buildKey( DString &dstrKey, 
													     const DString &dstrExternalIdType, 
													     const DString &dstrExternalId )
{
   DString dstrLocalExternalIdType (dstrExternalIdType),
           dstrLocalExternalId( dstrExternalId );
   	
	dstrKey = I_("ExternalIdType=") + dstrLocalExternalIdType.stripAll().upperCase() +
			    I_(";ExternalId=")    + dstrLocalExternalId.stripAll().upperCase();
}

//********************************************************************
SEVERITY TransactionExternalLinksList::getTransactionExternalLink( const DString &dstrExternalIdType,
						                                                 const DString &dstrExternalId, 
												                               const BFDataGroupId &idDataGroup,
												                               BFAbstractCBO *&pTransactionExternalLink )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTransactionExternalLink"));

	pTransactionExternalLink = NULL;

	DString dstrKey;
	buildKey( dstrKey, dstrExternalIdType, dstrExternalId );

	pTransactionExternalLink = dynamic_cast<BFAbstractCBO*>( getObject( dstrKey, idDataGroup ) );
	
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionExternalLinksList.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:58:18   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Sep 07 2004 15:31:48   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.0   Aug 30 2004 14:15:52   VADEANUM
// Initial revision.
//
