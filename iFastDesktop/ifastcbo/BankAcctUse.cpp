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
// ^FILE   : BankAcctUse.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 07/03/02
//
// ^CLASS    : BankAcctUse
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "BankAcctUse.hpp"


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME   = I_( "BankAcctUse" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId BankingEntity;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::BankingEntity, BFCBO::NONE, 0 }, 
   { ifds::AcctUseCode,   BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

BankAcctUse::BankAcctUse( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);
}

//******************************************************************************
BankAcctUse::~BankAcctUse()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     
//******************************************************************************

void BankAcctUse::init(const BFData& data)
{
   attachDataObject(const_cast<BFData&>(data), false, true);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankAcctUse.cpp-arc  $
// 
//    Rev 1.5   Dec 14 2004 15:00:38   popescu
// Fix crash on Desktop/exit
// 
//    Rev 1.4   Dec 07 2004 01:37:30   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.3   Nov 14 2004 14:27:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Oct 09 2002 23:54:02   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.1   Aug 29 2002 12:55:04   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.0   Jul 05 2002 12:02:50   KOVACSRO
// Initial revision.
// 

*/
