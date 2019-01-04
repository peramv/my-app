//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial
//
//*****************************************************************************
//
// ^FILE   : PrinterList.cpp
// ^AUTHOR : 
// ^DATE   : Nov 25, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : PrinterList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "printerlist.hpp"
#include <ifastdataimpl\dse_dstc0222_req.hpp>
#include <ifastdataimpl\dse_dstc0222_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PRINTER_LIST;   
}

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "PrinterList" );
}

//******************************************************************************
// Constructor
// @param   BFBase - pointer to the parent BFBase
//******************************************************************************
PrinterList::PrinterList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_pRequestData ( 0 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
// Destructor
//******************************************************************************
PrinterList::~PrinterList()
{
   if ( _pRequestData )
      delete _pRequestData;
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Makes view call 222 to obtain a list of printers.
// @param   const DString& dstTrack - 
//          const DString& dstrPageName - 
//******************************************************************************
SEVERITY PrinterList::init( const DString& dstrCompanyId,
                            const DString& dstrTrack,
                            const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );   
   DString mgmtCoIdOut;
   _pRequestData = new BFData(ifds::DSTC0222_REQ);
   _pRequestData->setElementValue( ifds::CompanyId, dstrCompanyId );
   _pRequestData->setElementValue( ifds::Track, dstrTrack );
   _pRequestData->setElementValue( ifds::Activity, dstrPageName );
   ReceiveData(DSTC_REQUEST::PRINTER_LIST, *_pRequestData, ifds::DSTC0222_VW, DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// getMore retrieves more data.
// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//                    SEVERE_ERROR if the accural type is not defined to be
//                    INTEREST_ACCRUAL/MF_ACCRUAL/MF_REBATE_ACCRUAL
//******************************************************************************
SEVERITY PrinterList::getMore( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );    
   ReceiveData(DSTC_REQUEST::PRINTER_LIST, *_pRequestData, ifds::DSTC0222_VW, DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PrinterList.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:51:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Mar 21 2003 18:20:14   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Dec 08 2002 22:04:46   HSUCHIN
// added companyid to init
// 
//    Rev 1.0   Nov 27 2002 11:39:02   HSUCHIN
// Initial Revision
*/
