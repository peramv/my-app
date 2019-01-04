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
// ^FILE   : ShrFundBrokerList.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : June, 2004
//
// ^CLASS    : ShrFundBrokerList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "ShrFundBroker.hpp"
#include "ShrFundBrokerlist.hpp"
#include "dstcommonfunction.hpp"

#include <ifastdataimpl\dse_dstc0069_vw.hpp>      // Shareholder
#include <ifastdataimpl\dse_dstc0327_req.hpp>   // Shareholder Fund Broker Inquiry
#include <ifastdataimpl\dse_dstc0327_vw.hpp>    // Shareholder Fund Broker Inquiry


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SHR_FUND_BROKER;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("ShrFundBrokerList");
}

namespace CND
{  // Conditions used   
	extern const long ERR_DUPLICATE_RECORD;	
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,        State Flags, Group Flags 
   { ifds::ShrNum, BFCBO::NONE, 0 },    
};
static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
ShrFundBrokerList::ShrFundBrokerList(BFAbstractCBO &parent)
: MFCanBFCbo(parent),
_pRequestData(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                      NULL);
}

//******************************************************************************
ShrFundBrokerList::~ShrFundBrokerList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}

//******************************************************************************
SEVERITY ShrFundBrokerList::initNew( const DString& dstrShrNum, 
												  const BFDataGroupId& idDataGroup ) // = BF::HOST 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

	setFieldNoValidate (ifds::ShrNum, dstrShrNum, idDataGroup, false );
   
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ShrFundBrokerList::init( const DString &dstrShareholderNum,
                                  const DString &dstrFund,   
											 const DString &dstrFundBroker, 
											 const DString &dstrDuplicateCheck,    // I_( "N" )
											 const BFDataGroupId &idDataGroup,     // BF::HOST 
											 const DString& dstrTrack,             // I_( "N" )
											 const DString &dstrPageName )         // NULL_STRING );			
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString dstrLocalFund( dstrFund ),
		     dstrLocalFundBroker( dstrFundBroker );

	dstrLocalFund.stripAll().upperCase();
	dstrLocalFundBroker.stripAll();   
	   
	setFieldNoValidate (ifds::ShrNum, dstrShareholderNum,  idDataGroup, false );
    	
   _pRequestData = new BFData (ifds::DSTC0327_REQ);

   DString mgmtCoIdOut;

   _pRequestData->setElementValue (ifds::ShrNum, dstrShareholderNum );
   _pRequestData->setElementValue (ifds::FundCode,       dstrLocalFund );   
	_pRequestData->setElementValue (ifds::FundBroker,     dstrLocalFundBroker );   
   _pRequestData->setElementValue (ifds::DuplicateCheck, dstrDuplicateCheck );
   _pRequestData->setElementValue (ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue (ifds::Track,          dstrTrack );
   _pRequestData->setElementValue (ifds::Activity,       dstrPageName );
  
	ReceiveData( DSTC_REQUEST::SHR_FUND_BROKER, 
				    *_pRequestData, 
					 ifds::DSTC0327_VW, 
                DSTCRequestor (getSecurity(), false));


   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundBrokerList::doCreateNewObject( BFCBO *&pBase, 
																		   DString &dstrKey, 
																		   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));
   	
	ShrFundBroker *pShrFundBroker = new ShrFundBroker (*this);
   if( pShrFundBroker->init( idDataGroup) <= WARNING )
   {
      pBase = pShrFundBroker;		
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY ShrFundBrokerList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   ShrFundBroker *pShrFundBroker = new ShrFundBroker (*this);

   if (pShrFundBroker->init( data ) <= WARNING)
   {
      pObjOut = pShrFundBroker;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ShrFundBrokerList::getStrKey( DString &dstrKey, const BFData *data )
{
   if( data ) 
   {
      DString dstrShareholderNum;
		if ( NULL != _pRequestData )
			_pRequestData->getElementValue (ifds::ShrNum, dstrShareholderNum );
      
		DString dstrFund       = data->getElementValue( ifds::FundCode );
		DString dstrFundBroker = data->getElementValue( ifds::FundBroker );
      
      buildKey( dstrKey, 
					 dstrShareholderNum, 
					 dstrFund,
					 dstrFundBroker );
   }
   else
   {
      BFCBO::getStrKey( dstrKey, NULL);
   }
}

//******************************************************************************
void ShrFundBrokerList::buildKey( DString &dstrKey, 
											 const DString &dstrShareholderNum, 
											 const DString &dstrFund,
											 const DString &dstrFundBroker )
{
   DString dstrLocalShareholderNum (dstrShareholderNum),
           dstrLocalFund( dstrFund ),
	        dstrLocalFundBroker( dstrFundBroker );   
   	
	dstrKey = I_("ShareholderNum=") + dstrLocalShareholderNum.stripAll().upperCase() +
			    I_(";Fund=")          + dstrLocalFund.stripAll().upperCase() +
				 I_(";FundBroker=")    + dstrLocalFundBroker.stripAll().upperCase();
}


//******************************************************************************
SEVERITY ShrFundBrokerList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));

   if (doMoreRecordsExist())
   {
      ReceiveData( DSTC_REQUEST::SHR_FUND_BROKER, 
						 *_pRequestData, 
						 ifds::DSTC0327_VW, 
						 DSTCRequestor(getSecurity(), false));
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY ShrFundBrokerList::checkDuplicate( const ShrFundBroker *pShrFundBrokerToCheck, 
																		const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );   	
	
   DString dstrShareholderNum, dstrFundCodeToCheck, dstrFundBrokerToCheck;
   getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
   pShrFundBrokerToCheck->getField( ifds::FundCode,       dstrFundCodeToCheck,       idDataGroup );
   pShrFundBrokerToCheck->getField( ifds::FundBroker,     dstrFundBrokerToCheck,     idDataGroup );
   dstrFundCodeToCheck.strip().upperCase();
   dstrFundBrokerToCheck.strip().upperCase();

   bool bHasDuplicate = false;

   //check first whether in the list (in memory) we have a duplicate
   //this catches the newly added items, as well 
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();
   while (!iter.end())
   {
      ShrFundBroker *pCurrentShrFundBroker = dynamic_cast<ShrFundBroker*>(iter.getObject());
      // Don't check against itself
      if ( pCurrentShrFundBroker != pShrFundBrokerToCheck )
      {
         DString dstrCurrentFund, dstrCurrentFundBroker;

         pCurrentShrFundBroker->getField(ifds::FundCode,   dstrCurrentFund, idDataGroup);
         pCurrentShrFundBroker->getField(ifds::FundBroker, dstrCurrentFundBroker, idDataGroup);
         dstrCurrentFund.stripAll().upperCase();
         dstrCurrentFundBroker.stripAll().upperCase();

         if ( dstrCurrentFund       == dstrFundCodeToCheck &&
              dstrCurrentFundBroker == dstrFundBrokerToCheck )
         {
           bHasDuplicate = true;
            break;
         }
      }
      ++iter;
   }

   //finally, if no duplicates in memory, check the back-end
   // but only if not new SHareholder
   if ( !bHasDuplicate &&
	    !getParent()->isNew() )
   {      	  
      ShrFundBrokerList ShrFundBrokerList((BFAbstractCBO&)(*this));

      //check duplicate, 
      if ( ShrFundBrokerList.init( dstrShareholderNum,
                                   dstrFundCodeToCheck, 
                                   dstrFundBrokerToCheck, 
                                   I_("Y"), 
                                   idDataGroup ) <= WARNING )
      {
         //we should get an exact match, so the DuplicateExist flag of the single section is set to Y or N
         DString dstrDuplicateExist;

         ShrFundBrokerList.getField (ifds::DuplicateExist, dstrDuplicateExist, idDataGroup, false);
         bHasDuplicate = dstrDuplicateExist == I_("Y");
         
         //but if we found a duplicate, this might have been already deleted in the memory
         if ( bHasDuplicate )
         { 
            //check the memory again for possible deleted duplicates
            BFObjIter iterInMemory(*this, idDataGroup);
            iterInMemory.begin();
            while ( !iterInMemory.end() )
            {
               if (iterInMemory.getKey().getActivity() == OBJ_ACTIVITY_DELETED )
               {
                  ShrFundBroker *pDeletedShrFundBroker = dynamic_cast<ShrFundBroker*>(iterInMemory.getObject());
                  DString dstrDeletedFundCode, 
                          dstrDeletedFundBroker;
                          
                  pDeletedShrFundBroker->getField(ifds::FundCode,   dstrDeletedFundCode,   idDataGroup );
                  pDeletedShrFundBroker->getField(ifds::FundBroker, dstrDeletedFundBroker, idDataGroup );
                  dstrDeletedFundCode.stripAll().upperCase();
                  dstrDeletedFundBroker.stripAll().upperCase();

                  if ( dstrFundCodeToCheck   == dstrDeletedFundCode && 
                       dstrFundBrokerToCheck == dstrDeletedFundBroker )
                       
                  {
                     bHasDuplicate = false;
                     break;
                  }
               }
               ++iterInMemory;
            }
         }
      }
   }

   if ( bHasDuplicate )
   {
      ADDCONDITIONFROMFILE(CND::ERR_DUPLICATE_RECORD);
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY ShrFundBrokerList::getShrFundBroker( const DString &dstrFund,																			  
															 const DString &dstrFundBroker,
															 const BFDataGroupId &idDataGroup,
															 ShrFundBroker *&pShrFundBroker )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getShrFundBroker"));

	pShrFundBroker = NULL;

	DString dstrKey;
	DString dstrShareholderNum;
	getParent()->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
	buildKey( dstrKey, dstrShareholderNum, dstrFund, dstrFundBroker );

	pShrFundBroker = dynamic_cast<ShrFundBroker*>( getObject( dstrKey, idDataGroup ) );
	
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFundBrokerList.cpp-arc  $
// 
//    Rev 1.4   Apr 27 2005 14:04:28   porteanm
// Incident 283312 - Changed field name from ShareholderNum to ShrNum for 327 req, 328 req in order to support NASU flow.
// 
//    Rev 1.3   Nov 28 2004 14:05:18   vadeanum
// PET1117 FN08 - Shareholder Fund Broker support.
// 
//    Rev 1.2   Nov 14 2004 16:32:14   purdyech
// Sync 1.0.1.0
// 
//    Rev 1.1   Nov 11 2004 16:39:46   vadeanum
// PET1117 FN08 - Shareholder Fund Broker support - work in progress
// 
//    Rev 1.0   Nov 04 2004 17:25:10   VADEANUM
// Initial revision.
//