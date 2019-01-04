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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : CertificateList.cpp
// ^AUTHOR : Brian Hicks
// ^DATE   : June 11, 1999
//
// ^CLASS    : CertificateList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "certificatelist.hpp"
#include "dstcommonfunction.hpp"
#include <ifastdataimpl\dse_dstc0018_req.hpp>
#include <ifastdataimpl\dse_dstc0018_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CERTIFICATE;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "CertificateList" );
}

/*******************************************************************************************************/
CertificateList::CertificateList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

/*******************************************************************************************************/
CertificateList::~CertificateList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

/*******************************************************************************************************/
SEVERITY CertificateList::init( DString& AcctNum,
                                DString& Fund, 
                                DString& CertNum, 
                                DString& XrefNum, 
                                bool bIgnoreDataNotFound, 
                                bool bIgnoreAccNumberIsInvalid, 
                                const DString& dstrTrack,
                                const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   BFData requestData(ifds::DSTC0018_REQ);
   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::InAcctNum, AcctNum ); 
   requestData.setElementValue( ifds::InFund, Fund );
   requestData.setElementValue( ifds::InCertNum, CertNum );
   requestData.setElementValue( ifds::InXrefNum, XrefNum );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
   ReceiveData(DSTC_REQUEST::CERTIFICATE, requestData, ifds::DSTC0018_VW, DSTCRequestor( getSecurity(), true, !bIgnoreDataNotFound ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool CertificateList::certIssueUnitsExist( const DString& dstrFund, 
                                           const DString& dstrClass, 
                                           double &dIssueUnits, 
                                           const BFDataGroupId& idDataGroup)
{
   bool bIssueUnitsExist ( false );
   BFObjIter iterCertList( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iterCertList.end() )
   {
      DString certFundCode, certClassCode, dstrIssueUnits;
      iterCertList.getObject()->getField ( ifds::rxFundCode, certFundCode, idDataGroup, false );
      iterCertList.getObject()->getField ( ifds::rxClassCode, certClassCode, idDataGroup, false );
      if( certFundCode == dstrFund && certClassCode == dstrClass )
      {
         iterCertList.getObject()->getField ( ifds::IssuedUnits, dstrIssueUnits, idDataGroup );
         dIssueUnits = DSTCommonFunctions::convertToDouble( dstrIssueUnits );
         if( dIssueUnits > 0 )
         {
            bIssueUnitsExist = true;
            break;
         }
      }
      ++iterCertList;
   }
   return(bIssueUnitsExist);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CertificateList.cpp-arc  $
 * 
 *    Rev 1.14   Nov 14 2004 14:29:32   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.13   Mar 21 2003 18:01:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:54:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 12:55:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   Jul 15 2002 13:57:22   HERNANDO
 * Ignore DataNotFound cases to allow displaying an empty dialog.
 * 
 *    Rev 1.9   22 May 2002 18:26:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   05 Aug 2001 13:22:16   HSUCHIN
 * clean up, bug fix to certIssueUnitsExist and init to return Data Not Found as a Error
 * 
 *    Rev 1.7   03 May 2001 14:06:04   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   Jan 18 2001 16:04:12   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.5   Dec 17 2000 20:22:42   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.4   Dec 06 2000 10:40:32   OLTEANCR
 * changed ReceiveData
 * 
 *    Rev 1.3   Nov 24 2000 12:09:18   WINNIE
 * new method for issue units checking
 * 
 *    Rev 1.2   Nov 02 2000 13:22:48   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.1   Oct 13 2000 13:46:38   ZHANGCEL
 * Debug fixed
 * 
 *    Rev 1.0   Feb 15 2000 10:59:50   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Jan 05 2000 20:10:38   BUZILA
 * adding list flag
 * 
 *    Rev 1.9   Dec 12 1999 16:25:12   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/