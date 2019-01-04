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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : FeeInfo.cpp
// ^AUTHOR : 
// ^DATE   : 29/08/2000
//
// ^CLASS    : FeeInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feeinfo.hpp"
#include <ifastdataimpl\dse_dstc0107_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEEINFOINQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "FeeInfo" );
   const I_CHAR * const YES = I_( "Y" );
}


//****************************************************************************
FeeInfo::FeeInfo( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
}

//****************************************************************************
FeeInfo::~FeeInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
SEVERITY FeeInfo::init( const BFData &viewData )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   attachDataObject( const_cast<BFData&>( viewData ), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
void FeeInfo::getField( const BFFieldId& idField, DString& strFieldValue, 
                        const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{
   BFCBO::getField(idField, strFieldValue, idDataGroup, formattedReturn );

   if( formattedReturn )
   {
      if( idField == ifds::AcqRate )
      {
         DString dstrAcqFeeType;
         BFCBO::getField(ifds::AcqFeeType, dstrAcqFeeType, idDataGroup, false);
         if( dstrAcqFeeType == I_("0") )      //Flat
         {
         }
         else if( strFieldValue.strip().stripAll(I_CHAR(',')).isDecimal() )
         {
            double fieldvalue = atof(strFieldValue.asA().c_str());
            strFieldValue = DSTCommonFunctions::doubleToDString(ifds::AcqRate, fieldvalue);
         }
      }
   }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeInfo.cpp-arc  $
// 
//    Rev 1.9   Nov 14 2004 14:39:58   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Mar 21 2003 18:08:52   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:54:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 12:55:48   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   22 May 2002 18:28:36   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   Oct 29 2001 16:08:00   ZHANGCEL
// Added the History Log 
 *
 * 
 */