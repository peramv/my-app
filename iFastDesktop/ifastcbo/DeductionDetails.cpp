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
//    Copyright 1999 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DeductionDetails.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/20/99
//
// ^CLASS    : DeductionDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "deductiondetails.hpp"
#include <ifastdataimpl\dse_currency_vw.hpp>
#include <ifastdataimpl\dse_dstc0022_vw.hpp>

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_( "DeductionDetails" );
}

//******************************************************************************
DeductionDetails::DeductionDetails( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_AlreadyGotDetails (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************
DeductionDetails::~DeductionDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}     

//******************************************************************************
void DeductionDetails::init( BFData &data, DString& currency )
{
   _currency=currency;
   attachDataObject( data, false, true);
}

//******************************************************************************
void DeductionDetails::getField( const BFFieldId& idField, 
                                 DString& strFieldValue,
                                 const BFDataGroupId& idDataGroup, 
                                 bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn);
   if( idField == ifds::DeductAmt &&
       formattedReturn )
   {
      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( _currency, strFieldValue, strFieldValue );
   }
	else if ( idField == ifds::FeeRate )	
	{
		DString dstrFeeRate( strFieldValue.stripAll() );
		double dblFeeRate = DSTCommonFunctions::convertToDouble ( dstrFeeRate );
		if ( dblFeeRate == 0.00 )
		{
			strFieldValue = I_( "N/A" );
		}					
	}	
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DeductionDetails.cpp-arc  $
 * 
 *    Rev 1.11   Nov 14 2004 14:30:20   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.10   Feb 23 2004 10:28:34   VADEANUM
 * PET 859 FN23 - ADL - Fee Rate formatting.
 * 
 *    Rev 1.9   Mar 21 2003 18:02:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:54:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:55:14   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   22 May 2002 18:26:44   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   03 May 2001 14:06:08   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   Feb 16 2001 14:04:48   DINACORN
 * Add Revision Control Entries
 * 
 */
