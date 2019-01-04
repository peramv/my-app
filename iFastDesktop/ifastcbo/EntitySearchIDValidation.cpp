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
// Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : EntitySearchIDValidation.cpp
// ^AUTHOR : 
// ^DATE   : Dec, 2010
//
// ^CLASS    : EntitySearchIDValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "EntitySearchIDValidation.hpp"

#include <ifastdataimpl\dse_dstc0417_req.hpp>
#include <ifastdataimpl\dse_dstc0417_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "EntitySearchIDValidation" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const YES                     = I_( "Y" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
}

namespace CND
{  // Conditions used
}

namespace IFASTERR
{
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITY_SEARCHID_VALIDATION_INQUIRY;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,      Group Flags
   {ifds::IsValid,            BFCBO::NONE,           0},
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************************
EntitySearchIDValidation::EntitySearchIDValidation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, pRequestData_(NULL)
, pResponseData_(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL);
}

//******************************************************************************************
EntitySearchIDValidation::~EntitySearchIDValidation()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if ( pRequestData_ != NULL )
   {
      delete pRequestData_;
      pRequestData_ = NULL;
   }
}

//******************************************************************************************
SEVERITY EntitySearchIDValidation::init(const DString& dstrWhereUse,
                                        const DString& dstrRelationShip,
                                        const DString& dstrSrchIdType,
                                        const DString& dstrBicCodeValue,
                                        const DString& dstrEntityId,
                                        const DString& strTrack,
                                        const DString& strPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;

   if ( pRequestData_ != NULL )
   {
      delete pRequestData_;
      pRequestData_ = NULL;
   }

   if ( pResponseData_ != NULL )
   {
      delete pResponseData_;
      pResponseData_ = NULL;
   }

   pRequestData_  = new BFData(ifds::DSTC0417_REQ);
   pResponseData_ = new BFData(ifds::DSTC0417_VW);

   pRequestData_->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   pRequestData_->setElementValue (ifds::WhereUse, dstrWhereUse);
   pRequestData_->setElementValue (ifds::RelationShip, dstrRelationShip);
   pRequestData_->setElementValue (ifds::SrchIdType, dstrSrchIdType);
   pRequestData_->setElementValue (ifds::SrchIdValue, dstrBicCodeValue);
   pRequestData_->setElementValue (ifds::EntityId, dstrEntityId);
   pRequestData_->setElementValue (ifds::Track, strTrack);
   pRequestData_->setElementValue (ifds::Activity, strPageName);

   ReceiveData(DSTC_REQUEST::ENTITY_SEARCHID_VALIDATION_INQUIRY, *pRequestData_, 
      *pResponseData_, DSTCRequestor(getSecurity(), false, false));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/EntitySearchIDValidation.cpp-arc  $
// 
//    Rev 1.0   Dec 27 2010 02:10:26   dchatcha
// Initial revision.
// 