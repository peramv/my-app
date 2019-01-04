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
// ^FILE   : RecipientTypeList.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : Nov 2000
//
// ^CLASS    : RecipientTypeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : The recipient type list
//
//******************************************************************************
#include "stdafx.h"
#include "recipienttypelist.hpp"
#include <ifastdataimpl\dse_dstc0146_req.hpp>
#include <ifastdataimpl\dse_dstc0146_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RECIPIENT_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RecipientTypeList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TaxJuris;
}

//****************************************************************************************
RecipientTypeList::RecipientTypeList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList ();
   setVersionable (false);
}

//****************************************************************************************
RecipientTypeList::~RecipientTypeList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************************
SEVERITY RecipientTypeList::init (const DString& dstrTrack,
                                  const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData (ifds::DSTC0146_REQ);   

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);

   ReceiveData (DSTC_REQUEST::RECIPIENT_LIST, queryData, ifds::DSTC0146_VW, DSTCRequestor(getSecurity()));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY RecipientTypeList::getRecipientType( const DString& taxType, 
                                              const DString& acctType, 
                                              const DString& taxJuris,
                                              DString& recipientType, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRecipientType" ));
   
   bool bReturn = false;
   DString _taxType, 
      _acctType,
      _taxJuris;
   
   BFObjIter Iter (*this, BF::HOST);
   
   for( Iter.begin(); !Iter.end(); ++Iter )
   {
      Iter.getObject()->getField (ifds::TaxType,  _taxType, idDataGroup);
      Iter.getObject()->getField (ifds::AcctType, _acctType, idDataGroup);
      Iter.getObject()->getField (ifds::TaxJuris, _taxJuris, idDataGroup);
      if( _taxType  == taxType   && 
          _acctType == acctType/*&&
          _taxJuris == taxJuris*/)
      {
         Iter.getObject()->getField (ifds::RecipientType, recipientType, idDataGroup);
         break;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RecipientTypeList.cpp-arc  $
// 
//    Rev 1.14   08 Dec 2008 12:34:58   popescu
// Incident 1507900
// Recipient Code Changes in Base and Desktop
// 
//    Rev 1.13   Dec 10 2004 14:53:36   hernando
// PET1117 - Recovered version feature.
// 
//    Rev 1.12   Nov 24 2004 10:18:46   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.11   Nov 18 2004 13:28:22   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.10   Nov 14 2004 14:51:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Mar 21 2003 18:20:38   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Oct 09 2002 23:54:50   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.7   Aug 29 2002 12:56:26   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   22 May 2002 18:29:40   PURDYECH
// BFData Implementation
// 
//    Rev 1.5   03 May 2001 14:06:58   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.4   Jan 18 2001 16:05:42   YINGBAOL
// add eTracker
// 
//    Rev 1.3   Dec 17 2000 20:24:14   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.2   Dec 15 2000 13:53:16   HERNANDO
// Prevent warning message change.
// 
//    Rev 1.1   Nov 24 2000 17:15:04   ZHANGCEL
// Added function getRecipientTypeMsg()
// 
//    Rev 1.0   Nov 22 2000 12:08:02   ZHANGCEL
// Initial revision.
// 
//
 * 
*/