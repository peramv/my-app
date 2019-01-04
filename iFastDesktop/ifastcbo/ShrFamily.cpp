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
// ^FILE   : ShrFamily.cpp
// ^AUTHOR : Claudio Sanchez
// ^DATE   : Jan. 09/2003
//
// ^CLASS    : ShrFamily
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "familycodelist.hpp"
#include "familycode.hpp"
#include "shrfamily.hpp"
#include "shrfamilylist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "shareholder.hpp"
#include <ifastdataimpl\dse_dstc0233_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0233_vw.hpp>

#include <ifastdataimpl\dse_dstc0235_req.hpp>
#include <ifastdataimpl\dse_dstc0235_vw.hpp>
#include <ifastdataimpl\dse_dstc0235_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FAMILY_MASTER;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "SrhFamily" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ExactMatch;
   extern CLASS_IMPORT const BFDecimalFieldId ShrFamilyRid;

   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

namespace SHAREHOLDER_TYPE
{
   extern CLASS_EXPORT const I_CHAR * const DSC                  = I_( "DSC" );
   extern CLASS_EXPORT const I_CHAR * const MFR_HOUSEHOLDING     = I_( "HH" );
}

namespace CND
{  // Conditions used
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,              State Flags,             Group Flags 
   { ifds::FamilyCode,           BFCBO::NONE,                  0 }, 
   { ifds::FamilyName,           BFCBO::NONE,                  0 }, 
   { ifds::FamilyType,           BFCBO::NONE,                  0 }, 
   { ifds::Role,                 BFCBO::NONE,                  0 }, 
   { ifds::ShrFamilyRid,         BFCBO::NONE,                  0 }, 
   
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
ShrFamily::ShrFamily( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
ShrFamily::~ShrFamily()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY ShrFamily::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   familyCodeRelatedChanges(BF::HOST);

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY ShrFamily::initNew( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   setObjectNew();

   Shareholder* pShareholder = dynamic_cast<Shareholder*>(getParent()->getParent());

   if(pShareholder)
   {
      DString strShrNum;
      pShareholder->getField(ifds::ShrNum, strShrNum,idDataGroup,false);
      setFieldNoValidate(ifds::FamilyCode, strShrNum,idDataGroup,false,true,true,false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ShrFamily::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   SEVERITY  sevRtn = NO_CONDITION;  

   if( idField == ifds::FamilyCode )
   {
      familyCodeRelatedChanges(idDataGroup);
   }
   else if ( idField == ifds::FamilyType )
   {
      familyTypeRelatedChanges(idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY ShrFamily::getFamilyName( const DString& dstrFamilyCode, 
                                   DString &dstrFamilyName, 
                                   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFamilyName" ) );
   
   DString mgmtCoIdOut;

   BFData requestData(ifds::DSTC0235_REQ);
   BFData response   (ifds::DSTC0235_VW);

   // Initialize parameter to a default value
   dstrFamilyName = NULL_STRING;

   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::FamilyCode, dstrFamilyCode );
   requestData.setElementValue( ifds::ExactMatch, I_("Y") );
   requestData.setElementValue( ifds::Track, I_( "N" ) );
   requestData.setElementValue( ifds::Activity, NULL_STRING );

   SEVERITY sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::FAMILY_MASTER,
                                                            requestData, 
                                                            response, 
                                                            DSTCRequestor( getSecurity(), true ) );
   // Find a family name for given family code
   if ( sevRtn <= WARNING ) 
   {
      if(response.getRepeatCount())
      {
         const BFData& repeatData = response.getRepeat(0);
         dstrFamilyName = repeatData.getElementValue ( ifds::FamilyName );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY()); 
}

//******************************************************************************
SEVERITY ShrFamily::doValidateField( const BFFieldId& idField, 
                                     const DString& strValue, 
                                     const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFamily::familyCodeRelatedChanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "familyCodeRelatedChanges" ) );

   DString dstrFamilyCode, 
      dstrFamilyName,
      dstrFamilyType;

   getField( ifds::FamilyCode, dstrFamilyCode, idDataGroup, false );
   getField( ifds::FamilyType, dstrFamilyType, idDataGroup, false );
   dstrFamilyType.strip().upperCase();

   // look for existing ones
   FamilyCodeList familyCodeList (*this);
   if (familyCodeList.init (dstrFamilyCode, NULL, I_("Y"), idDataGroup) <= WARNING)
   {
      BFObjIter iter (familyCodeList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

      if (!iter.end())
      {
         FamilyCode *pFamilyCode = dynamic_cast <FamilyCode*> (iter.getObject());
         if (pFamilyCode)
         {
            DString strDefaultFamilyName;

            pFamilyCode->getField (ifds::FamilyName, strDefaultFamilyName, idDataGroup, false);
            setFieldNoValidate (ifds::FamilyName, strDefaultFamilyName, idDataGroup, true, true, true, false);
         }
         else
         {
            setFieldNoValidate ( ifds::FamilyName, NULL_STRING, idDataGroup, true, true, true, false );
         }
      }
      else
      {
         setFieldNoValidate ( ifds::FamilyName, NULL_STRING, idDataGroup, true, true, true, false );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFamily::familyTypeRelatedChanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "familyTypeRelatedChanges" ) );
   

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ShrFamily::needsCacheRefresh (const BFDataGroupId& idDataGroup)
{
   bool bRefresh = false;
   bRefresh = isFieldUpdated (ifds::FamilyCode,   idDataGroup) || 
              isFieldUpdated (ifds::FamilyName,   idDataGroup);
   return bRefresh; 
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFamily.cpp-arc  $
// 
//    Rev 1.16   Mar 22 2012 00:01:26   popescu
// Incident 2889121 - shareholder family screen freeze
// 
//    Rev 1.15   Mar 20 2012 18:36:22   popescu
// Incident 2889121 - shareholder family screen freeze
// 
//    Rev 1.14   Dec 09 2011 11:43:52   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.13   Nov 21 2011 12:09:52   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.12   Nov 17 2011 19:13:46   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.11   Nov 16 2011 19:17:56   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.10   Nov 15 2011 18:44:36   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.9   Nov 14 2011 20:14:40   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.8   Nov 08 2011 12:06:18   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.7   Nov 14 2004 14:55:34   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Mar 21 2003 18:24:54   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Jan 24 2003 12:18:32   sanchez
// Modified getFamilyName().  Don't loop, just get const BFData& repeatData = response.getRepeat(0);
// 
//    Rev 1.4   Jan 22 2003 16:25:40   WINNIE
// fix getting the family from the view
// 
//    Rev 1.3   Jan 21 2003 19:11:34   WINNIE
// add family code validation and display family name if exists
// 
//    Rev 1.2   Jan 14 2003 17:40:04   sanchez
// added  Revision Control Entries
 */