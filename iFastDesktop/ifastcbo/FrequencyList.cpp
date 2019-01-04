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
//    Copyright 2007 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : FrequencyList.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : June 2007
//
// ^CLASS    : FrequencyList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "Frequency.hpp"
#include "Frequencylist.hpp"

#include <ifastdataimpl\dse_dstc0382_req.hpp>                 // Frequency Inquiry
#include <ifastdataimpl\dse_dstc0382_vw.hpp>                  // Frequency Inquiry
#include <ifastdataimpl\dse_dstc0382_vwrepeat_record.hpp>     // Frequency Inquiry 


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FREQUENCY_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("FrequencyList");
}

//******************************************************************************
FrequencyList::FrequencyList(BFAbstractCBO &parent)
: MFCanBFCbo(parent),
_pRequestData(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
FrequencyList::~FrequencyList(void)
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}

//******************************************************************************
SEVERITY FrequencyList::init( const DString& dstrTrack,             // I_( "N" )
							         const DString &dstrPageName )         // NULL_STRING );			
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
    	
   _pRequestData = new BFData (ifds::DSTC0382_REQ);

   DString mgmtCoIdOut;
   
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue (ifds::Track,     dstrTrack );
   _pRequestData->setElementValue (ifds::Activity,  dstrPageName );
  
   ReceiveData( DSTC_REQUEST::FREQUENCY_LIST, 
    				 *_pRequestData, 
	  			    ifds::DSTC0382_VW, 
                DSTCRequestor (getSecurity(), 
				    false ) );

   while ( doMoreRecordsExist() )
	   getMore();

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FrequencyList::init( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("FrequencyList"));

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FrequencyList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   Frequency *pFrequency = new Frequency (*this);

   if (pFrequency->init( data ) <= WARNING)
   {
      pObjOut = pFrequency;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FrequencyList::getStrKey( DString &dstrKey, const BFData *data )
{
   if( data ) 
   {    
      DString dstrSchedSetupFreqID;
      dstrSchedSetupFreqID = data->getElementValue( ifds::SchedSetupFreqID );
                  
      buildKey( dstrKey, 
				    dstrSchedSetupFreqID );
      
   }
   else
   {
      BFCBO::getStrKey( dstrKey, NULL);
   }
}

//******************************************************************************
void FrequencyList::buildKey( DString &dstrKey, 
							         const DString &dstrSchedSetupFreqID )
{
   DString dstrLocalSchedSetupFreqID( dstrSchedSetupFreqID ); 
   dstrKey = I_("SchedSetupFreqID=") + dstrLocalSchedSetupFreqID.stripAll();
}


//******************************************************************************
SEVERITY FrequencyList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));

   if (doMoreRecordsExist())
   {      
      ReceiveData( DSTC_REQUEST::FREQUENCY_LIST, 
			          *_pRequestData, 
				       ifds::DSTC0382_VW, 
				       DSTCRequestor(getSecurity(), 
				       false ) );    
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY FrequencyList::getFrequency( const DString &dstrSchedSetupFreqID,
									           const BFDataGroupId &idDataGroup,
									           Frequency *&pFrequency )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFrequency"));

	pFrequency = NULL;

	DString dstrKey;	
	buildKey( dstrKey, 
			    dstrSchedSetupFreqID );

	pFrequency = dynamic_cast<Frequency*>( getObject( dstrKey, idDataGroup ) );
	
	return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY FrequencyList::getFrequencySubstitutionSet( DString &dstrFrequencySubstitutionSet,
												                 const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFrequencySubstitutionSet"));

   BFObjIter FrequencyListIter( *this, 
 				                    idDataGroup, 
       							     true, 
							           BFObjIter::ITERTYPE::NON_DELETED );
         
   FrequencyListIter.begin();  
   while( !FrequencyListIter.end() )
	{
	   DString dstrSchedSetupFreqID, dstrSchedFreqDesc;
	   FrequencyListIter.getObject()->getField( ifds::SchedSetupFreqID, dstrSchedSetupFreqID,     idDataGroup );
	   FrequencyListIter.getObject()->getField( ifds::SchedFreqDesc,    dstrSchedFreqDesc, idDataGroup );

	   dstrFrequencySubstitutionSet += dstrSchedSetupFreqID + I_("=") + dstrSchedFreqDesc + I_(";");				
		      
		++FrequencyListIter;         
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FrequencyList.cpp-arc  $
// 
//    Rev 1.1   Jun 22 2007 14:21:04   porteanm
// PET 2360 FN02 - AMS - work in progress.
// 
//    Rev 1.0   Jun 20 2007 11:40:24   porteanm
// Initial revision.
// 
// 

