//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : ProdPortfolioInfoList.cpp
// ^AUTHOR : 
// ^DATE   : Aug, 2011
//
// ^CLASS    : ProdPortfolioInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0418_vw.hpp>
#include <ifastdataimpl\dse_dstc0418_req.hpp>
#include <ifastdataimpl\dse_dstc0418_vwrepeat_record.hpp>

#include "ProdPortfolioInfo.hpp"
#include "ProdPortfolioInfoList.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PROD_PORTFOLIO_INFO_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "ProdPortfolioInfoList" );
}

namespace ifds
{
}

namespace CND
{
}

//******************************************************************************
ProdPortfolioInfoList::ProdPortfolioInfoList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
, requestData418(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( 0,
                       NULL,
                       0,
                       NULL );

   setObjectAsList( );
}

//******************************************************************************
ProdPortfolioInfoList::~ProdPortfolioInfoList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if ( requestData418 != NULL )
   {
      delete requestData418;
      requestData418 = NULL;
   }
}

//********************************************************************************
SEVERITY ProdPortfolioInfoList::init(const DString& dstrShGroup, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   DString mgmtCoIdOut;
   requestData418 = new BFData(ifds::DSTC0418_REQ);

   requestData418->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData418->setElementValue (ifds::ShGroup, dstrShGroup);

   BFData* responseData = new BFData (ifds::DSTC0418_VW);
   ReceiveData( DSTC_REQUEST::PROD_PORTFOLIO_INFO_INQUIRY,
                *requestData418, 
                *responseData, 
                DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ProdPortfolioInfoList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new ProdPortfolioInfo( *this );
   ((ProdPortfolioInfo*) pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ProdPortfolioInfoList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::PROD_PORTFOLIO_INFO_INQUIRY, 
                  *requestData418, 
                  ifds::DSTC0418_VW, 
                  DSTCRequestor( getSecurity(), false ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ProdPortfolioInfoList::getSubstitutionList(DString& dstrSubstitutionList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSubstitutionList" ) );

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString strTempSubList = I_("");
   while( !iter.end() )
   {
      ProdPortfolioInfo* pObj = dynamic_cast<ProdPortfolioInfo*>(iter.getObject());
      if(pObj)
      {
         DString strPortfolioName, strProdPortfolioUUID;
         pObj->getField(ifds::PortfolioName, strPortfolioName, idDataGroup, false);
         pObj->getField(ifds::ProdPortfolioUUID, strProdPortfolioUUID, idDataGroup, false);
         strTempSubList += strProdPortfolioUUID;
         strTempSubList += I_("=");
         strTempSubList += strPortfolioName;
         strTempSubList += I_(";");
      }
      ++iter; 
   }

   dstrSubstitutionList = strTempSubList;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ProdPortfolioInfoList::getPortfolioUUIDbyPortfolioCode (DString& _portfolioCode, 
                                                                 DString*& _prodPortfolioUUID,
                                                                 const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSubstitutionList" ) );

   *_prodPortfolioUUID = NULL_STRING;
   
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   
   while (!iter.end())
   {
      ProdPortfolioInfo* pObj = dynamic_cast<ProdPortfolioInfo*>(iter.getObject());
      if (pObj)
      {
         DString portfolioCode;
         
         pObj->getField(ifds::PortfolioCode, portfolioCode, idDataGroup, false);
         if (portfolioCode == _portfolioCode)
         {
            pObj->getField (ifds::ProdPortfolioUUID, *_prodPortfolioUUID, idDataGroup, false);
            break;
         }
      }
      ++iter; 
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ProdPortfolioInfoList::getPortfolioCodebyPortfolioUUID (DString& _portfolioUUID, 
                                                                 DString*& _prodPortfolioCode,
                                                                 const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSubstitutionList" ) );

   *_prodPortfolioCode = NULL_STRING;

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

   while (!iter.end())
   {
      ProdPortfolioInfo* pObj = dynamic_cast<ProdPortfolioInfo*>(iter.getObject());
      if (pObj)
      {
         DString portfolioUUID;

         pObj->getField(ifds::ProdPortfolioUUID, portfolioUUID, idDataGroup, false);
         if (portfolioUUID == _portfolioUUID)
         {
            pObj->getField (ifds::PortfolioCode, *_prodPortfolioCode, idDataGroup, false);
            break;
         }
      }
      ++iter; 
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ProdPortfolioInfoList::hasPortfolioSegFunds (const DString& _prodPortfolioUUID,
                                                  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "hasPortfolioSegFunds" ) );

   bool bHasPortfolioSegFunds = false;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   
   while (!iter.end())
   {
      ProdPortfolioInfo* pObj = dynamic_cast<ProdPortfolioInfo*>(iter.getObject());
      if (pObj)
      {
         DString prodPortfolioUUID;
         
         pObj->getField (ifds::ProdPortfolioUUID, prodPortfolioUUID, idDataGroup, false);
         if (_prodPortfolioUUID == prodPortfolioUUID)
         {
            DString segFundIncl;
            
            pObj->getField (ifds::SegFundIncl, segFundIncl, idDataGroup, false);
            bHasPortfolioSegFunds = segFundIncl == I_("Y");
            break;
         }
      }
      ++iter; 
   }
   return bHasPortfolioSegFunds;
}

//******************************************************************************
bool ProdPortfolioInfoList::isCommitmentApplicable ( const DString& _prodPortfolioUUID,
                                                     const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isCommitmentApplicable" ) );

   bool bIsCommitmentApplicable = false;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   
   while (!iter.end())
   {
      ProdPortfolioInfo* pObj = dynamic_cast<ProdPortfolioInfo*>(iter.getObject());
      if (pObj)
      {
         DString prodPortfolioUUID;
         
         pObj->getField (ifds::ProdPortfolioUUID, prodPortfolioUUID, idDataGroup, false);
         if (_prodPortfolioUUID == prodPortfolioUUID)
         {
            DString commitApplicable;
            
            pObj->getField (ifds::CommitApplicable, commitApplicable, idDataGroup, false);
            bIsCommitmentApplicable = commitApplicable == I_("Y");
            break;
         }
      }
      ++iter; 
   }
   return bIsCommitmentApplicable;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ProdPortfolioInfoList.cpp-arc  $
// 
//    Rev 1.6   Feb 24 2012 16:06:56   popescu
// NASU - Added commitment.
// 
//    Rev 1.5   Jan 21 2012 09:01:42   dchatcha
// IN# 2799812 - Contract Screen issues.
// 
//    Rev 1.4   Dec 19 2011 23:32:40   popescu
// P0186484 - FN 05 - work on Contract Information Screen
// 
//    Rev 1.3   Sep 30 2011 10:07:38   popescu
// P0186477 FN01 - GIA Enhancements
// 
//    Rev 1.2   Sep 16 2011 17:56:42   dchatcha
// P0186477 FN01 - GIA Enhancements, Create substitution list
// 
//    Rev 1.1   Aug 30 2011 14:46:40   dchatcha
// P0186477 FN01 - GIA Enhancements, put 'ShGroup' as query parameter.
// 
//    Rev 1.0   Aug 25 2011 17:09:00   dchatcha
// Initial revision.
// 

