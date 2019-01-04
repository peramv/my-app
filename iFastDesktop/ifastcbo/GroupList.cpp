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
// ^FILE   : GroupList.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 10/1/1999
//
// ^CLASS    : GroupList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "grouplist.hpp"
#include "group.hpp"
#include <ifastdataimpl\dse_dstc0088_req.hpp>
#include <ifastdataimpl\dse_dstc0088_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest GROUP;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "GroupList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctGroup;
}

//******************************************************************************
GroupList::GroupList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setVersionable( false );
   setObjectAsList();
}

//******************************************************************************
GroupList::~GroupList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY GroupList::init( const DString& dstrGropCode /*=NULL_STRING*/,
                          const DString& dstrTrack,
                          const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0088_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );
   queryData.setElementValue( ifds::GroupCode, dstrGropCode ); 
   ReceiveData (DSTC_REQUEST::GROUP, queryData, ifds::DSTC0088_VW, DSTCRequestor (getSecurity()));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY GroupList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut = new Group( *this );
   ( ( Group* ) ( pObjOut ) )->init( data);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void GroupList::getStrKey( DString &strKey, const BFData *data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString strGroupCode = data->getElementValue( I_( "rxGroupCode" ) );
      strKey = strGroupCode.strip().upperCase();
   }
   else
   {
      BFCBO::getStrKey( strKey , NULL );
   }

}

//******************************************************************************
void GroupList::getGroupSubstList( DString &strList, bool bMakeUppercase)
{        
   DString     strGroupCode = NULL_STRING;
   BFAbstractCBO *pCurrEntry  = NULL;
   BFSubst     lBFSubst;
   bool        bAddBlankCode = false;

   BFObjIter   iter( *this, BF::HOST );

   strList = NULL_STRING;

   if( iter.end() )
      bAddBlankCode = true;

   while( !iter.end() )
   {
      pCurrEntry = iter.getObject();
      if( pCurrEntry != NULL )
      {
         pCurrEntry->getField( ifds::rxGroupCode, strGroupCode, BF::HOST );
         if( bMakeUppercase )
            strGroupCode.upperCase();
         lBFSubst.addSubst( strGroupCode, strGroupCode );
      }
      ++iter;      
   }

   if( bAddBlankCode )
      lBFSubst.addSubst( BLANK_STRING, BLANK_STRING );

   lBFSubst.getList( strList );

}


//******************************************************************************
void GroupList::buildKey( const DString& strGroup, DString &strKey )
{
   strKey = strGroup;
   strKey.strip().upperCase();
}

//******************************************************************************
SEVERITY GroupList::getField( const DString& strGroupCode, const BFFieldId& idField, DString& strValue, 
                              const BFDataGroupId& idDataGroup, bool formattedReturn ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getField" ));
   SEVERITY sevRtn = NO_CONDITION;   

   DString strGroup,strKey;
   BFObjIter iter(*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

   buildKey( strGroupCode, strKey );

   if( iter.positionByKey(strKey) )
   {
      iter.getObject()->getField( idField, strValue, idDataGroup, formattedReturn );  
   }
   else sevRtn = SEVERE_ERROR;

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GroupList.cpp-arc  $
 * 
 *    Rev 1.20   Jun 29 2011 14:39:08   wutipong
 * IN#2556973 Unable to change shareholder group
 * 
 *    Rev 1.19   Dec 10 2004 14:51:16   hernando
 * PET1117 - Recovered version feature.
 * 
 *    Rev 1.18   Dec 02 2004 14:28:36   Fengyong
 * PET972
 * 
 *    Rev 1.17   Nov 14 2004 14:43:40   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.16   Nov 04 2004 17:37:56   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.15   Aug 30 2004 14:53:10   YINGBAOL
 * PTS10032768: speed up list  for non updateable CBO.
 * 
 *    Rev 1.14   Mar 21 2003 18:12:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Oct 09 2002 23:54:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Aug 29 2002 12:56:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.11   22 May 2002 18:28:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.10   Feb 25 2002 18:55:46   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.9   Nov 29 2001 16:27:16   ZHANGCEL
 * Overrite the function doCreateObject()
 * 
 *    Rev 1.8   03 May 2001 14:06:38   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.7   Jan 18 2001 16:05:12   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.6   Dec 17 2000 20:23:46   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.5   Dec 06 2000 11:40:08   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.4   Nov 02 2000 10:28:14   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.3   Sep 01 2000 15:25:44   HUANGSHA
 * added pClientLocale in setField(...)
 * 
 *    Rev 1.2   Aug 25 2000 09:34:48   WINNIE
 * Add new method to for getting field value in the pass in group code
 * 
 *    Rev 1.1   Aug 16 2000 10:39:54   DINACORN
 * Added method getGroupList()
 * 
 *    Rev 1.0   Feb 15 2000 11:00:00   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Jan 20 2000 10:43:56   POPESCUS
// set the object as a list
// 
//    Rev 1.4   Dec 24 1999 17:10:12   PRAGERYA
// For internal release
// 
//    Rev 1.3   Dec 12 1999 16:25:26   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
*/