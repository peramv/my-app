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
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundGroupSubList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 01/09/02
//
// ^CLASS    : FundGroupSubList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include <bfutil\bfguard.hpp>
#include "fundgroupsublist.hpp"
#include "fundgroupsub.hpp"
#include <ifastdataimpl\dse_dstc0229_req.hpp>
#include <ifastdataimpl\dse_dstc0229_vw.hpp>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME                    = I_( "FundGroupSubList" );
  
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_COMM_GROUP_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundType;

}

namespace  CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_INVALID_FUND_GROUP_TYPE;
}
//******************************************************************************
FundGroupSubList::FundGroupSubList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
m_strFundType(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   //setVersionable( false );
}

//******************************************************************************
FundGroupSubList::~FundGroupSubList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FundGroupSubList::init( const DString& strFundType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString dstrFundType(strFundType);
   if( dstrFundType.strip().empty() )
      return(GETCURRENTHIGHESTSEVERITY());

   m_strFundType = dstrFundType;

   BFGuard cs( _csFundGroupSubList );

   BFObjIter iter( *this, BF::HOST, 0, BFObjIter::ITERTYPE::NON_DELETED );
   BFAbstractCBO *pBFCBO;
   DString str;
   while( !iter.end() )
   {
      pBFCBO = iter.getObject();
      pBFCBO->getField( ifds::FundType, str, BF::HOST, false );
      if( str.strip() == dstrFundType )//view has been already called for this fund type
         return(GETCURRENTHIGHESTSEVERITY());
      ++iter;
   }

   BFData requestData(ifds::DSTC0229_REQ);
   DString mgmtCoIdOut, strNextKey = NULL_STRING;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::GroupType,  dstrFundType  );
   requestData.setElementValue( ifds::Track, I_("N") );
   requestData.setElementValue( ifds::Activity, NULL_STRING );
   requestData.setElementValue( ifds::NextKey,  strNextKey );

   if( ReceiveData( DSTC_REQUEST::FUND_COMM_GROUP_LIST, requestData, ifds::DSTC0229_VW, DSTCRequestor( getSecurity(), true, true ) ) > WARNING )
   {
      int count = CONDITIONCOUNT();
      Condition   *c = NULL;
      for( int i = 0; i < count; i++ )
      {
         c = GETCONDITION( i );
         int condCode = c->getCode();
         if( condCode == CND::ERR_DATA_NOT_FOUND || condCode == CND::ERR_INVALID_FUND_GROUP_TYPE)
         {
            CLEARCONDITION( i )
            BFObjectKey objKey;
            BFCBO* pBFCBO = getNewListItem(objKey);
            break;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FundGroupSubList::doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   FundGroupSub* pFundGroupSub = new FundGroupSub( *this );
   pFundGroupSub->setField(ifds::FundType, m_strFundType, BF::HOST, false);
   pFundGroupSub->setField(ifds::FundGroup, NULL_STRING, BF::HOST, false);
   pBase = pFundGroupSub;

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY FundGroupSubList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   FundGroupSub* pFundGroupSub = new FundGroupSub( *this );
   pFundGroupSub->setField(ifds::FundType, m_strFundType, BF::HOST, false);
   pFundGroupSub->init(data);
   pObjOut = pFundGroupSub;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
DString FundGroupSubList::getFundGroupSubList( const DString& strFundType )
{
   init( strFundType );
   return(buildSubList(strFundType));

}
//******************************************************************************

DString FundGroupSubList::buildSubList( const DString& strFundType )
{
   DString dstrFundType(strFundType), strSubstList(NULL_STRING);

   if( !dstrFundType.strip().empty() )
   {
      BFGuard cs( _csFundGroupSubList );

      BFObjIter iter( *this, BF::HOST, 0, BFObjIter::ITERTYPE::NON_DELETED );
      BFAbstractCBO *pBFCBO;
      DString strType, strGroupCode, strGroupDescr;
      while( !iter.end() )
      {
         pBFCBO = iter.getObject();
         pBFCBO->getField( ifds::FundType, strType, BF::HOST, false );
         if( strType.strip() == dstrFundType )//a match has been found
         {
            pBFCBO->getField( ifds::FundGroup, strGroupCode, BF::HOST, false );
            if( !strGroupCode.strip().empty() )
            {
               strSubstList += strGroupCode.strip();
               strSubstList += I_( "=" );
               pBFCBO->getField( ifds::GroupName, strGroupDescr, BF::HOST, false );
               if (strGroupDescr.strip().empty())
                  strSubstList += strGroupCode.strip();//use code if description is empty
               else
                  strSubstList += strGroupDescr.strip();
               strSubstList += I_( ";" );
            }
         }
         ++iter;
      }
   }
   
   return(strSubstList);
}

//******************************************************************************

bool FundGroupSubList::doesFundGroupExist( const DString &_dstrFundGroup )
{
   bool bExist = false;
	BFObjIter iter( *this, BF::HOST, true, BFObjIter::ITERTYPE::NON_DELETED );
   BFAbstractCBO *pBFCBO;
   iter.begin();      
   DString dstrFundGroup, dstrFundGroup_( _dstrFundGroup );

   while( !iter.end() )
   {
      pBFCBO = iter.getObject();
      pBFCBO->getField( ifds::FundGroup, dstrFundGroup, BF::HOST, false );
      if( dstrFundGroup.upperCase() == dstrFundGroup_.upperCase() )
      {
         bExist = true;
         break;
      }
      ++iter;
   }

   return( bExist );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundGroupSubList.cpp-arc  $
// 
//    Rev 1.6   Nov 24 2004 10:18:30   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.5   Nov 18 2004 13:28:08   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.4   Nov 14 2004 14:42:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Sep 21 2004 16:00:32   HERNANDO
// PET1094 FN06 - Absatzmeldung Files enhancement.
// 
//    Rev 1.2   Sep 21 2004 13:29:48   HERNANDO
// PET1094 FN06 - Absatzmeldung Files enhancement.  Added doesFundGroupExist.
// 
//    Rev 1.1   Mar 21 2003 18:11:20   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.0   Jan 12 2003 19:03:32   KOVACSRO
// Initial revision.
// 
 * 
 *
*/