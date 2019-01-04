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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : ProvinceList.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : February 2004
//
// ^CLASS    : ProvinceList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "Province.hpp"
#include "Provincelist.hpp"

#include <ifastdataimpl\dse_dstc0252_req.hpp>                 // Province Inquiry
#include <ifastdataimpl\dse_dstc0252_vw.hpp>                  // Province Inquiry
#include <ifastdataimpl\dse_dstc0252_vwrepeat_record.hpp>     // Province Inquiry> 


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PROVINCE_LIST_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("ProvinceList");
}

//******************************************************************************
ProvinceList::ProvinceList(BFAbstractCBO &parent)
: MFCanBFCbo(parent),
_pRequestData(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
ProvinceList::~ProvinceList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}


//******************************************************************************
SEVERITY ProvinceList::init( const DString &dstrCountryCode,  
							 const BFDataGroupId &idDataGroup,     // BF::HOST 
							 const DString& dstrTrack,             // I_( "N" )
							 const DString &dstrPageName )         // NULL_STRING );			
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
    	
   _pRequestData = new BFData (ifds::DSTC0252_REQ);

   DString mgmtCoIdOut;

   _pRequestData->setElementValue (ifds::Country,   dstrCountryCode );
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue (ifds::Track,     dstrTrack );
   _pRequestData->setElementValue (ifds::Activity,  dstrPageName );
  
   ReceiveData( DSTC_REQUEST::PROVINCE_LIST_INQUIRY, 
				 *_pRequestData, 
				 ifds::DSTC0252_VW, 
                 DSTCRequestor (getSecurity(), 
				 false ) );

   while ( doMoreRecordsExist() )
	   getMore();
  
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ProvinceList::init( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ProvinceList"));

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ProvinceList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   Province *pProvince = new Province (*this);

   if (pProvince->init( data ) <= WARNING)
   {
      pObjOut = pProvince;
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY ProvinceList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));

   if (doMoreRecordsExist())
   {
      ReceiveData( DSTC_REQUEST::PROVINCE_LIST_INQUIRY, 
			       *_pRequestData, 
				   ifds::DSTC0252_VW, 
				   DSTCRequestor(getSecurity(), 
				   false ) );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY ProvinceList::getProvinceSubstitutionSet( DString &dstrProvinceSubstitutionSet,
												   const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getProvinceSubstitutionSet"));


   BFObjIter provinceListIter( *this, 
				               idDataGroup, 
							   true, 
							   BFObjIter::ITERTYPE::NON_DELETED );
         
   provinceListIter.begin();  
   while( !provinceListIter.end() )
	{
	   DString dstrProvince, dstrProvinceName;
	   provinceListIter.getObject()->getField( ifds::Province,     dstrProvince,     idDataGroup );
	   provinceListIter.getObject()->getField( ifds::ProvinceName, dstrProvinceName, idDataGroup );

	   dstrProvinceSubstitutionSet += dstrProvince + I_("=") + dstrProvinceName + I_(";");				
		      
		++provinceListIter;         
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ProvinceList.cpp-arc  $
// 
//    Rev 1.4   06 Nov 2007 13:46:44   kovacsro
// IN#1057338 - province CanadaUS substitution set read from view 252 now, rather than the DD
// 
//    Rev 1.3   Mar 15 2005 10:45:12   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.2   Mar 14 2005 16:16:04   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.1   Mar 02 2005 16:41:48   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.0   Feb 22 2005 14:30:44   porteanm
// Initial revision.
// 

