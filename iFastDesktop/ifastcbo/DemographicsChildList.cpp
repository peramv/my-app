//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2014 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : DemographicsChildList.cpp
// ^AUTHOR : 
// ^DATE   : Oct, 2014
//
// ^CLASS    : DemographicsChildList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "demographicschildlist.hpp"

#include "demographics.hpp"
#include "DemographicsChild.hpp"

#include <ifastdataimpl\dse_dstc0465_req.hpp>
#include <ifastdataimpl\dse_dstc0465_vw.hpp>
#include <ifastdataimpl\dse_dstc0465_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "DemographicsChildList" );
   const I_CHAR * const SOURCE_OF_PAYMENT       = I_( "SOP" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
}

namespace CND
{  // Conditions used
}

namespace IFASTERR
{
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DEMOGRAPHICS_CHILD_LIST_INQUIRY;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,                 State Flags,               Group Flags 

   { ifds::AccountNum,           BFCBO::CALCULATED_FIELD,      0 },
   { ifds::EntityId,             BFCBO::CALCULATED_FIELD,      0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
DemographicsChildList::DemographicsChildList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_("Contructor") );
   
   registerMemberData( NUM_FIELDS, 
                      (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, 
                       NULL );

   setObjectAsList();
}

//******************************************************************************************
DemographicsChildList::~DemographicsChildList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY DemographicsChildList::init(const DString &accountNum, 
                                     const DString &entityId)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData (ifds::DSTC0465_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::AccountNum, accountNum); 
   requestData.setElementValue (ifds::EntityId, entityId); 

   requestData.setElementValue (ifds::Track, I_("N"));
   requestData.setElementValue (ifds::Activity, NULL_STRING);

   setFieldNoValidate (ifds::AccountNum, accountNum,BF::HOST,false,true,false,false);
   setFieldNoValidate (ifds::EntityId, entityId,BF::HOST,false,true,false,false);

   ReceiveData ( DSTC_REQUEST::DEMOGRAPHICS_CHILD_LIST_INQUIRY, 
                 requestData, 
                 ifds::DSTC0465_VW, 
                 DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DemographicsChildList::init ( const DString &accountNum, 
                                       const DString &entityId,
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   setFieldNoValidate (ifds::AccountNum, accountNum,idDataGroup,false,true,false,false);
   setFieldNoValidate (ifds::EntityId, entityId,idDataGroup,false,true,false,false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DemographicsChildList::doCreateObject( const BFData& data, BFCBO*& pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   DemographicsChild* pDemographicsChild = new DemographicsChild( *this );

   pDemographicsChild->init (data);
   pObjOut = pDemographicsChild;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DemographicsChildList::doCreateNewObject( BFCBO*& pBase, 
                                                   DString& strKey, 
                                                   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   DemographicsChild* pDemographicsChild = new DemographicsChild( *this );

   pDemographicsChild->initNew (idDataGroup);
   pBase = pDemographicsChild;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DemographicsChildList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DemographicsChildList::doValidateField( const BFFieldId& idField,
                                                 const DString& strValue,
                                                 const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DemographicsChildList::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DemographicsChildList::addNewKYCAttribRecord( const DString& code,
                                                       const DString& strValue,
                                                       const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addNewKYCAttribRecord" ) );

   DemographicsChild *pDemographicsChild = NULL;

   DString strObjKey = I_("KYCAttribType=");
   strObjKey += SOURCE_OF_PAYMENT;
   strObjKey += I_(";KYCAttribCode=");
   strObjKey += code;
   BFObjectKey objKey (strObjKey, idDataGroup);
   pDemographicsChild = dynamic_cast <DemographicsChild*> (getNewListItem (objKey));

   if (pDemographicsChild)
   {
      pDemographicsChild->setField (ifds::KYCAttribType, SOURCE_OF_PAYMENT, idDataGroup, false);
      pDemographicsChild->setField (ifds::KYCAttribCode, code, idDataGroup, false);
      pDemographicsChild->setField (ifds::KYCAttribStat, strValue, idDataGroup, false);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DemographicsChildList.cpp-arc  $
// 

