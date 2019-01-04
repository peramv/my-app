/*
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : BankTransaction.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 03/30/01
//
// ^CLASS    : BankTransaction
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "banktransaction.hpp"
#include "banktransactionlist.hpp"
#include "dstcommonfunction.hpp"
#include <dataimpl\dse_dstc0055_vw.hpp>

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId PayMethod;
   extern CLASS_IMPORT const BFTextFieldId BankInstrType;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;

}
//******************************************************************************

const BFFieldId readOnlyFields[]=
{
   ifds::PayMethod,
   ifds::BankIdType,    
   ifds::BankIdValue,      
   ifds::InstName,         
   ifds::TransitNo,     
   ifds::BankAcctType,  
   ifds::SwiftCode,  
   ifds::RefNumber,  
   ifds::ACHProcessor,  
   ifds::BankPostal, 
   ifds::BankPostalCB,  
   ifds::BankAcctNum,   
   ifds::BankAcctCurrency, 
   ifds::BankCountry,   
   ifds::BankCountryCB, 
   ifds::BankContact,   
   ifds::BankContactCB, 
   ifds::BankAcctName,  
   ifds::BankIdTypeCB,  
   ifds::BankIdValueCB, 
   ifds::TransitNoCB,      
   ifds::InstNameCB,    
   ifds::FFC,           
   ifds::PayReason1,    
   ifds::PayReason2,    
   ifds::BankAddrCB1,      
   ifds::BankAddrCB2,      
   ifds::BankAddrCB3,      
   ifds::BankAddrCB4,      
   ifds::BankAddrCB5,      
   ifds::BankAddr1,     
   ifds::BankAddr2,     
   ifds::BankAddr3,     
   ifds::BankAddr4,     
   ifds::BankAddr5,     
   ifds::EffectiveDate, 
   ifds::StopDate,         
};
static const int numReadOnlyFields = sizeof( readOnlyFields ) / sizeof( BFFieldId );

//******************************************************************************


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { BFCBO::CLASS_FIELD_INFO( ifds::InstName,         BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::SwiftCode,        BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::RefNumber,        BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::TransitNo,        BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAcctNum,      BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAcctName,     BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAcctType,     BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAcctCurrency, BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::PayReason1,       BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::PayReason2,       BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::CorrespBankId,    BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankIdType,       BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankIdTypeCB,     BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankIdValueCB,    BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::FFC,              BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::FFC1,             BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::ACHProcessor,     BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankContactCB,    BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankCountryCB,    BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankPostalCB,     BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAddrCB1,      BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAddrCB2,      BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAddrCB3,      BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAddrCB4,      BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAddrCB5,      BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAddr1,        BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAddr2,        BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAddr3,        BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAddr4,        BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankAddr5,        BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankContact,      BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankCountry,      BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankPostal,       BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::TransitNoCB,      BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::InstNameCB,       BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::PACSWPId,         BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::DistribDetlRid,   BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankIdValue,      BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::BankId,           BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::EffectiveDate,    BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::StopDate,         BFCBO::NONE, 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::PayMethod,        BFCBO::NONE, 0 )}, 

	
};


static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//******************************************************************************

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME            = I_( "BankTransaction" );

}


//******************************************************************************

BankTransaction::BankTransaction( BFAbstractCBO &parent ) :
BankInstructions ( parent ),
m_strTradeDate(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);
}

//******************************************************************************

BankTransaction::~BankTransaction()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//******************************************************************************
SEVERITY BankTransaction::doValidateField( const BFFieldId& idField,
                                           const DString& strValue,
                                           const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY BankTransaction::init( const BFData& data, const DString& strTradeDate, const DString& strBankType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   setFieldNoValidate(ifds::BankInstrType, strBankType, BF::HOST, false);

   setAcctUseSubstList(BF::HOST);
   setFieldNoValidate(ifds::AcctUseCode, strBankType, BF::HOST, false);

   attachDataObject(const_cast<BFData&>(data), false, true );
   setFieldNoValidate( ifds::EffectiveDate, strTradeDate, BF::HOST, true, true, true );
   //because PayMethod is not in view 55, for now we'll set it to WIRE
   setFieldNoValidate( ifds::PayMethod, I_("WIRE"), BF::HOST, false, true, true );
   setStopDate9999( BF::HOST );  

   m_strTradeDate = strTradeDate;
   setFieldsReadOnly(readOnlyFields, numReadOnlyFields);
   clearUpdatedFlags( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void BankTransaction::initNew( const DString& strTradeDate, const DString& strBankType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew") );

   setFieldNoValidate(ifds::BankInstrType, strBankType, idDataGroup, false);

   setAcctUseSubstList(idDataGroup);
   setFieldNoValidate(ifds::AcctUseCode, strBankType, idDataGroup, false);

   m_strTradeDate = strTradeDate;
   setFieldNoValidate( ifds::EffectiveDate, strTradeDate, idDataGroup, true, true, true );
   clearUpdatedFlags( idDataGroup );

   setFieldsReadOnly(readOnlyFields, numReadOnlyFields, idDataGroup);
   setStopDate9999( idDataGroup );  
}

//******************************************************************************
void BankTransaction::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   setFieldNoValidate( ifds::EffectiveDate, m_strTradeDate, idDataGroup, true, true, true );
   setStopDate9999( idDataGroup );  

}

//******************************************************************************
SEVERITY BankTransaction::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) )

   return(GETCURRENTHIGHESTSEVERITY());
}
/******************************************************************************
void BankTransaction::init2( const DString& strDate )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init2") );
   
   setFieldsAsReadOnly( BF::HOST );
   setDefaultValues( BF::HOST, strDate );

   SEVERITY sevRtn = SEVERE_ERROR;
  
}*/

/**************************************************************************
void BankTransaction::setDefaultValues( const BFDataGroupId& idDataGroup, 
                                        const DString& dstrDate )
{

   setFieldNoValidate( ifds::EffectiveDate, dstrDate, idDataGroup, false, true, true );
   DString strStopDate;

   getWorkSession().getDateInHostFormat(strStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);

   setFieldNoValidate( ifds::StopDate, strStopDate, idDataGroup, false  );

}*/
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankTransaction.cpp-arc  $
// 
//    Rev 1.18   Nov 14 2004 14:29:08   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.17   Oct 19 2003 16:44:04   popescu
// CIBC, PET809, FN 13 banking work
// 
//    Rev 1.16   Jul 29 2003 13:47:10   YINGBAOL
// PTS10020130---Wrong field ID between base class and derived class. 
// 
//    Rev 1.15   Jun 18 2003 17:45:06   popescu
// RRIF Banking Enhancement , business rules, bug fixes 
// 
//    Rev 1.14   May 22 2003 14:12:00   popescu
// Replaced name 'BankInstr' with 'BankInstructions'; 
// simplified child lists getters for the Shareholder object
// 
//    Rev 1.13   Mar 21 2003 18:00:42   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.12   Oct 09 2002 23:54:06   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.11   Aug 30 2002 18:58:58   SMITHDAV
// More FieldId fixes.
// 
//    Rev 1.10   Aug 29 2002 12:55:08   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.9   Jul 19 2002 11:48:52   KOVACSRO
// setting stop date to 9999.
// 
//    Rev 1.8   Jul 11 2002 13:41:08   KOVACSRO
// doApplyRelatedChanges should do nothing for transaction bank.
// 
//    Rev 1.7   Jul 05 2002 11:55:44   KOVACSRO
// Dynamically loading AcctUse subst. list.
// 
//    Rev 1.6   Jun 28 2002 11:51:00   KOVACSRO
// Actually the EffectiveDate comes formatted (shouldn't matter anymore...)
// 
//    Rev 1.5   Jun 17 2002 17:28:30   KOVACSRO
// payment method not in view.
// 
//    Rev 1.4   Jun 16 2002 17:03:24   KOVACSRO
// fit in the new bank design.
// 
//    Rev 1.3   22 May 2002 18:26:30   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   09 May 2001 15:00:48   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.0.1.1   Apr 09 2001 15:14:06   YINGBAOL
// pass trade date
// 
//    Rev 1.0.1.0   Apr 06 2001 14:27:34   YINGBAOL
// change signature of init
// 
//    Rev 1.0   Apr 02 2001 16:53:30   YINGBAOL
// Initial revision.

// 
 * 
*/

