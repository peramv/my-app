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
// ^FILE   : Remarks.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : 11/09/99
//
// ^CLASS    : Remarks
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "remarks.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0005_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "Remarks" );
   const I_CHAR * const REDIRECT = I_("02");
   const I_CHAR * const GENERAL = I_("00");
}

namespace UAF
{
    extern CLASS_IMPORT I_CHAR * const REMARK_ALERT;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::TransNote,      BFCBO::NONE, 0 }, 
   { ifds::Remark1,        BFCBO::NONE, 0 }, 
   { ifds::Remark2,        BFCBO::NONE, 0 }, 
   { ifds::Remark3,        BFCBO::NONE, 0 }, 
   { ifds::Remark4,        BFCBO::NONE, 0 }, 
   { ifds::Remark5,        BFCBO::NONE, 0 }, 
   { ifds::Remark6,        BFCBO::NONE, 0 }, 
   { ifds::Remark7,        BFCBO::NONE, 0 }, 
   { ifds::Remark8,        BFCBO::NONE, 0 }, 
   { ifds::Remark9,        BFCBO::NONE, 0 }, 
   { ifds::Remark10,       BFCBO::NONE, 0 }, 
   { ifds::Active,         BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate,  BFCBO::NONE, 0 }, 
   { ifds::ProcessDate,    BFCBO::NONE, 0 }, 
   { ifds::Username,       BFCBO::NONE, 0 }, 
   { ifds::ModDate,        BFCBO::NONE, 0 }, 
   { ifds::ModUser,        BFCBO::NONE, 0 }, 
   { ifds::RemarksDetlRid, BFCBO::NONE, 0 }, 
   { ifds::RemarksDetlVer, BFCBO::NONE, 0 }, 
   { ifds::RemarkType,		BFCBO::NONE, 0 }, 
   { ifds::RemarkAlert,		BFCBO::NONE, 0 }, 
   { ifds::AccountNum,		BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
Remarks::Remarks( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
Remarks::~Remarks()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY Remarks::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );
   setFieldReadOnly (ifds::AccountNum, BF::HOST, true);

   DString strRemarkType = 
      data.getElementValue (ifds::RemarkType);
   
   strRemarkType.stripAll();
   if(strRemarkType == REDIRECT)
   {
	   //apply these rules later
	   //setFieldReadOnly( ifds::RemarkType, BF::HOST, true );
	   //setFieldReadOnly( ifds::Active, BF::HOST, true );
   }

   DString dstrRemarkAlert;
   getField(ifds::RemarkAlert, dstrRemarkAlert, BF::HOST);

   if (!getWorkSession().hasUpdatePermission(UAF::REMARK_ALERT))
   {
       setFieldReadOnly(ifds::RemarkAlert, BF::HOST, true);

       if (dstrRemarkAlert.upperCase() == Y)
           setAllFieldsReadOnly(BF::HOST);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
//generally used for new objects
SEVERITY Remarks::init (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void Remarks::doInitWithDefaultValues (
      const BFDataGroupId &idDataGroup)
{
   DString currDate;

   getWorkSession().getMgmtCoOptions()->getField (ifds::CurrBusDate, 
      currDate, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, currDate, idDataGroup, 
      false, true, true);
   setFieldNoValidate (ifds::RemarkType, GENERAL, idDataGroup, 
      false, true, true);

   setFieldNoValidate(ifds::RemarkAlert, N, idDataGroup, false, false, true, true);
   setFieldReadOnly(ifds::RemarkAlert, idDataGroup, !getWorkSession().hasUpdatePermission(UAF::REMARK_ALERT));
}

//****************************************************************************
bool Remarks::isRemarkInfoField(const BFFieldId &idField)
{
    return idField == ifds::Remark1 ||
           idField == ifds::Remark2 ||
           idField == ifds::Remark3 ||
           idField == ifds::Remark4 ||
           idField == ifds::Remark5 ||
           idField == ifds::Remark6 ||
           idField == ifds::Remark7 ||
           idField == ifds::Remark8 ||
           idField == ifds::Remark9 ||
           idField == ifds::Remark10;
}

//****************************************************************************
SEVERITY Remarks::setField (
   const BFFieldId &idField, 
   const DString &dstrValue,
   const BFDataGroupId &idDataGroup, 
   bool bFormatted, 
   bool bSideEffect, 
   bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );

   if (!dstrValue.empty() || isRemarkInfoField(idField))
   {
		bool blSetField = true;

		if ( ifds::AccountNum == idField )
		{			
			if ( isNew() )
			{			
				DString dstrRemark1, dstrRemark2, dstrRemark3, dstrRemark4, dstrRemark5,
					     dstrRemark6, dstrRemark7, dstrRemark8, dstrRemark9, dstrRemark10;

				getField( ifds::Remark1,  dstrRemark1,  idDataGroup, false );
				getField( ifds::Remark2,  dstrRemark2,  idDataGroup, false );
				getField( ifds::Remark3,  dstrRemark3,  idDataGroup, false );
				getField( ifds::Remark4,  dstrRemark4,  idDataGroup, false );
				getField( ifds::Remark5,  dstrRemark5,  idDataGroup, false );
				getField( ifds::Remark6,  dstrRemark6,  idDataGroup, false );
				getField( ifds::Remark7,  dstrRemark7,  idDataGroup, false );
				getField( ifds::Remark8,  dstrRemark8,  idDataGroup, false );
				getField( ifds::Remark9,  dstrRemark9,  idDataGroup, false );
				getField( ifds::Remark10, dstrRemark10, idDataGroup, false );	


				if ( dstrRemark1.strip().empty() && 
					  dstrRemark2.strip().empty() && 
					  dstrRemark3.strip().empty() && 
					  dstrRemark4.strip().empty() && 
					  dstrRemark5.strip().empty() && 
					  dstrRemark6.strip().empty() && 
					  dstrRemark7.strip().empty() && 
					  dstrRemark8.strip().empty() && 
					  dstrRemark9.strip().empty() && 
					  dstrRemark10.strip().empty() )
				{
					blSetField = false;				
				}
								
			} // end if isNew()

			if ( !isNew() && !hasUpdatedFields( BF::HOST ) && !hasUpdatedFields( idDataGroup ) )
			{			
				blSetField = false;	
			}			
		}

		if ( blSetField )
			BFCBO::setField (idField, dstrValue, idDataGroup, bFormatted, bSideEffect);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY Remarks::doApplyRelatedChanges (
   const BFFieldId &idField, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (idField == ifds::RemarkType)
   {
      DString strRemarkType;
	   
      getField( ifds::RemarkType, strRemarkType, idDataGroup, false );
	   if (strRemarkType == REDIRECT)
	   {
		   //Apply these rules later
		   //setFieldReadOnly( ifds::RemarkType, idDataGroup, true );
		   //setFieldReadOnly( ifds::Active, idDataGroup, true );
	   }
	   else
	   {
		   //setFieldReadOnly( ifds::RemarkType, idDataGroup, false );
		   //setFieldReadOnly( ifds::Active, idDataGroup, false );
	   }
   }
	
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
void Remarks::setAllFieldsReadOnly(const BFDataGroupId& idDataGroup)
{
   const CLASS_FIELD_INFO* pClassFieldInfo = (const CLASS_FIELD_INFO *)&classFieldInfo;
   
   for( int i = 0; i < NUM_FIELDS; i++, pClassFieldInfo++ )
   {
      setFieldReadOnly(pClassFieldInfo->m_fieldId, idDataGroup, true);
   }      
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Remarks.cpp-arc  $
 * 
 *    Rev 1.17   Nov 14 2004 14:51:50   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.16   Mar 26 2004 12:51:36   VADEANUM
 * PTS 10028335 - Inconsistent AccountNum behaviour.
 * 
 *    Rev 1.15   Feb 23 2004 10:41:28   popescu
 * PTS 10027283, moved the initialization of the effective date and remark type to the 'doInitWithDefaultValues' method, from init of new objects method. Also removed setting the update flag of the account field in init for new objects method, which makes the object always dirty.
 * 
 *    Rev 1.14   Oct 03 2003 09:59:04   VADEANUM
 * PTS 10022399 - Wrong Account # assigned to Remark - replaced RefAccount with AccountNum in order to have the fieldid picked up in DSTCWorkSession::commit() after including the field in the transaction key.
 * 
 *    Rev 1.13   Aug 14 2003 10:05:48   FENGYONG
 * default general for remark type
 * 
 *    Rev 1.12   Aug 11 2003 11:04:00   FENGYONG
 * Set default DefAccount updateflag on for new remarks.
 * 
 *    Rev 1.11   Jul 30 2003 11:26:06   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.10   Jul 17 2003 10:43:48   FENGYONG
 * Add fields
 * 
 *    Rev 1.9   Mar 21 2003 18:21:14   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:54:52   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:56:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   Jul 12 2002 15:50:10   HERNANDO
 * Added setField to compensate for unformatting an empty field, remarks1.
 * 
 *    Rev 1.5   22 May 2002 18:29:42   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   03 May 2001 14:07:00   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.3   Feb 19 2001 13:21:12   DINACORN
 * Add Revision Control Entries
 *
 */