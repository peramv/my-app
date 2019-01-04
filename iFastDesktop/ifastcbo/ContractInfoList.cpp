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
// ^FILE   : ContractInfoList.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/01/2000
//
// ^CLASS    : ContractInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "contractinfo.hpp"
#include "contractinfolist.hpp"
#include "mastercontractlist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcworksession.hpp"
#include <ifastdataimpl\dse_dstc0133_vw.hpp>
#include <ifastdataimpl\dse_dstc0133_req.hpp>
#include <ifastdataimpl\dse_dstc0105_vw.hpp>
#include <ifastdataimpl\dse_dstc0105_req.hpp>

#include "entity.hpp"
#include "accountentityxref.hpp"

#include <bfutil\bfdate.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CONTRACTINFO_LIST;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "ContractInfoList" );
}

namespace TRID
{
   extern const I_CHAR* CONTRACTINFO;

}

namespace CND
{ // Conditions used
   extern const long ERR_PROVINCE_IS_REQUIRED;
   extern const long ERR_EFF_STOP_DATE_RANGE_OVERLAP;
   extern const long ERR_EFFECTIVE_DATE_MUST_LATE;
   extern const long ERR_CONTRACT_MUST_BE_CREATED;
   extern const long ERR_LINKED_CONTRACT_DIFFERENT;
   extern const long ERR_ADD_LINKED_CONTRACT;
     //extern const long ERR_NO_DATE_OF_BIRTH;
  // extern const long ERR_OLDEST_LEGAL_DATE_CANNOT_BE_IN_THE_PAST;
}
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_MULTI_CONTRACT;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId PorfolioIsRequried;  
}

//******************************************************************************
// Constructors
//******************************************************************************

ContractInfoList::ContractInfoList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ) 
, pMgmtCoOptions(NULL)
, pTaxTypeRuleList(NULL)
, pMasterContractList(NULL)
, pMFAccount(NULL)
, pAccountHoldingList(NULL)
, pRequestData105(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );

   dstrAcctNum  = NULL_STRING;
}

//******************************************************************************

ContractInfoList::~ContractInfoList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if ( pRequestData105 != NULL )
   {
      delete pRequestData105;
      pRequestData105 = NULL;
   }
}

//******************************************************************************
SEVERITY ContractInfoList::init( const BFDataGroupId& idDataGroup, 
                                 const DString& AccountNumber, 
                                 bool bViewCall, 
                                 const DString& dstrTrack,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );   

   dstrAcctNum = AccountNumber;
   // Get info for doValidateField() and SetDefault()
   getInfoForVldandDft( idDataGroup);
   if( bViewCall )
   {
      //BFData queryData(ifds::DSTC0105_REQ);
      pRequestData105 = new BFData(ifds::DSTC0105_REQ);
      //BFData *receivedData = new BFData(ifds::DSTC0105_VW);
      DString mgmtCoIdOut;
      pRequestData105->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      pRequestData105->setElementValue( ifds::AccountNum, AccountNumber ); 
      pRequestData105->setElementValue( ifds::Track, dstrTrack );
      pRequestData105->setElementValue( ifds::Activity, dstrPageName );
      ReceiveData( DSTC_REQUEST::CONTRACTINFO_LIST, 
                   *pRequestData105, 
                   ifds::DSTC0105_VW, 
                   DSTCRequestor(getSecurity()) );
   }

   bool _bMultiContract = getWorkSession().hasReadPermission( UAF::SEG_FUND_MULTI_CONTRACT );
   if( _bMultiContract )
   {
      DString dstrContractType;

      BFObjIter iterContracts( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
      iterContracts.begin();

      ContractInfo* pContractInfo = NULL;
      while(!iterContracts.end())
      {
         pContractInfo = (ContractInfo*)iterContracts.getObject();
         
         pContractInfo->getField(ifds::ContractType, dstrContractType, BF::HOST);
         dstrContractType.strip().upperCase();

         DString dstrIssueDate;
         pContractInfo->getField(ifds::IssueDate, dstrIssueDate, BF::HOST);
         dstrIssueDate.strip();
         if(dstrIssueDate == I_("") || dstrIssueDate == I_("12319999"))
         {
            BFAbstractCBO* pMasterContract = NULL;
            pContractInfo->getMasterContract(pMasterContract, BF::HOST);
            if(pMasterContract)
            {
               DString dstrLinkedContract;
               pMasterContract->getField(ifds::LinkedContract, dstrLinkedContract, BF::HOST);
               dstrLinkedContract.strip();
               if(dstrLinkedContract != I_(""))
               {
                  ContractInfo* pLinkedContract = NULL;
                  if(getContractByType(pLinkedContract, dstrLinkedContract, BF::HOST) <= WARNING &&
                     pLinkedContract)
                  {
                     DString dstrLinkedIssueDate;
                     pLinkedContract->getField(ifds::IssueDate, dstrLinkedIssueDate, BF::HOST);
                     dstrLinkedIssueDate.strip();
                     if(dstrLinkedIssueDate != I_("") && dstrLinkedIssueDate != I_("12319999"))
                     {
                        pContractInfo->updateContractMatBasedOnSubst(BF::HOST, true);
                     }
                  };
               }
            }

         }
         ++iterContracts;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


SEVERITY ContractInfoList::getContractByType(ContractInfo*& pContractInfo, const DString& dstrContractType, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getContractByType" ) );

   BFObjIter iterContracts( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   iterContracts.begin();

   while(!iterContracts.end())
   {
      ContractInfo* pLocalContractInfo = (ContractInfo*)iterContracts.getObject();
      DString dstrContractTypeValue;
      pLocalContractInfo->getField(ifds::ContractType, dstrContractTypeValue, idDataGroup);
      dstrContractTypeValue.strip().upperCase();

      if(dstrContractType == dstrContractTypeValue)
      {
         pContractInfo = pLocalContractInfo;
         break;
      }
      ++iterContracts;
   }

   return(GETCURRENTHIGHESTSEVERITY());
};

//******************************************************************************
SEVERITY ContractInfoList::doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   ContractInfo *pContractinfo = new ContractInfo ( *this );

   pBase = pContractinfo;
   pContractinfo->init2( this, idDataGroup);
   pContractinfo->initStatusSubst( idDataGroup ); 

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfoList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   ContractInfo *pContractinfo = new ContractInfo ( *this );
   pObjOut = pContractinfo;

   pContractinfo->init( data );
   pContractinfo->init2( this, BF::HOST );
   pContractinfo->SetFieldProperties( BF::HOST, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void ContractInfoList::AddCopy(DString &orgKey, DString &destKey, const BFDataGroupId& idDataGroup)
{
   ContractInfo *pOrgContractInfo = NULL, *pDestContractInfo = NULL;

   for( BFObjIter Iter( *this, idDataGroup ); !Iter.end(); ++Iter )
   {
      if( Iter.getStringKey() == orgKey )
      {
         pOrgContractInfo = dynamic_cast< ContractInfo * >( Iter.getObject( ) );
      }
      else if( Iter.getStringKey() == destKey )
      {
         pDestContractInfo = dynamic_cast< ContractInfo * >( Iter.getObject( ) );
      }
   }

   assert ( pOrgContractInfo && pDestContractInfo );

   pDestContractInfo->ModelOffer(pOrgContractInfo, idDataGroup);

}

//******************************************************************************
void ContractInfoList::getInfoForVldandDft( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getInfoForVldandDft" ) );

   if( pMgmtCoOptions ) return;
   try
   {
      getWorkSession().getMFAccount( idDataGroup, dstrAcctNum, pMFAccount );
      getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
      getMgmtCo().getTaxTypeRuleList( pTaxTypeRuleList );
      getMasterContractList( pMasterContractList, idDataGroup );
      //getMgmtCo().getMasterContractList( pMasterContractList );
      pMFAccount->getAccountHoldingList( pAccountHoldingList, idDataGroup, true ); // chencking
   }
   catch( ConditionException &ce )
   {
      pMgmtCoOptions = NULL;
      SETCONDITIONFROMEXCEPTION( ce );
   }
}
//********************************************************************************************
SEVERITY ContractInfoList::ValidateTwinContracts( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateTwinContracts" ) );
   bool _bMultiContract = getWorkSession().hasReadPermission( UAF::SEG_FUND_MULTI_CONTRACT );
   if( _bMultiContract )
   {
      DString dstrContractFromType;

      BFObjIter iterContractsFrom( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
      iterContractsFrom.begin();

      ContractInfo* pContractInfoFrom = NULL;
	  //couldn't check the current object for duplicate
      while(!iterContractsFrom.end())
      {
         pContractInfoFrom = (ContractInfo*)iterContractsFrom.getObject();
         
         pContractInfoFrom->getField(ifds::ContractType, dstrContractFromType, idDataGroup);
         dstrContractFromType.strip().upperCase();
         BFAbstractCBO* pMasterContract = NULL;
         pContractInfoFrom->getMasterContract(pMasterContract, idDataGroup);
         if(pMasterContract != NULL)
         {
            DString dstrLinkedContract;
            pMasterContract->getField(ifds::LinkedContract, dstrLinkedContract, idDataGroup, false);

            if(dstrLinkedContract.stripAll().upperCase() != NULL_STRING)
            {
               bool bFoundTwin = false;
               bool bFoundIdenticalTwin = false;
               BFObjIter iterContractsTo( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
               iterContractsTo.begin();

               ContractInfo* pContractInfoTo = NULL;
               while(!iterContractsTo.end())
               {
                  pContractInfoTo = (ContractInfo*)iterContractsTo.getObject();
                  if(pContractInfoTo != pContractInfoFrom)
                  {
                     DString dstrContractToType;
                     pContractInfoTo->getField(ifds::ContractType, dstrContractToType, idDataGroup);
                     if(dstrContractToType.stripAll().upperCase() == dstrLinkedContract)// && dstrContractFromType < dstrContractToType)
                     {
                        bFoundTwin = true;
                        if(pContractInfoFrom->CompareTwinContracts(pContractInfoTo, idDataGroup))
                        {
                           bFoundIdenticalTwin = true;
                        }
                        
                     }
                  }
                  ++iterContractsTo;
               }
               if(!bFoundTwin)
               {
                  ADDCONDITIONFROMFILE(CND::ERR_ADD_LINKED_CONTRACT);
               }
               else if(!bFoundIdenticalTwin)
               {
                  ADDCONDITIONFROMFILE(CND::ERR_LINKED_CONTRACT_DIFFERENT);
               }
            }
         }   

         ++iterContractsFrom;
      } 
   }
	
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfoList:: doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   DString dstrStartDate, dstrEndDate, dstrStartDate1, dstrEndDate1, dstrContractType, dstrContractType1, dstrProvinceCanada;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFAbstractCBO *pBFCBO;
   BFAbstractCBO *pBFCBO1;

   while( !iter.end() )
   {
      pBFCBO = iter.getObject();
      if( !iter.isDummy()  && pBFCBO )
      {
         pBFCBO->getField(ifds::EffectiveDate, dstrStartDate, idDataGroup);
         pBFCBO->getField(ifds::StopDate, dstrEndDate, idDataGroup);
         pBFCBO->getField(ifds::ContractType, dstrContractType, idDataGroup );

// This check is not absolutely necessary since the CBO already validated the date range
// but let's be safe and do it again.
         if( DSTCommonFunctions::CompareDates( dstrStartDate, dstrEndDate ) 
             == DSTCommonFunctions::FIRST_EARLIER )
         {
            // position to the next item
            iter1.positionByKey( iter.getStringKey() );
            if( !iter1.end() )++iter1;

            while( !iter1.end() )
            {
               pBFCBO1 = iter1.getObject();
               pBFCBO1->getField ( ifds::ContractType, dstrContractType1, idDataGroup );
               if( !iter1.isDummy()  && pBFCBO1 && dstrContractType == dstrContractType1 )
               {
                  pBFCBO1->getField(ifds::EffectiveDate, dstrStartDate1, idDataGroup);
                  pBFCBO1->getField(ifds::StopDate, dstrEndDate1, idDataGroup);

                  if( DSTCommonFunctions::CompareDates( dstrStartDate1, dstrEndDate1 ) // check only when date are valid
                      == DSTCommonFunctions::FIRST_EARLIER )
                  {
                     if( DSTCommonFunctions::CompareDates( dstrStartDate1, dstrEndDate ) 
                         == DSTCommonFunctions::FIRST_EARLIER  &&
                         DSTCommonFunctions::CompareDates( dstrStartDate, dstrEndDate1 ) 
                         == DSTCommonFunctions::FIRST_EARLIER )
                     {
                        ADDCONDITIONFROMFILE( CND::ERR_EFFECTIVE_DATE_MUST_LATE );
                        return(GETCURRENTHIGHESTSEVERITY());
                     }
                  }
               }
               ++iter1;
            }
         }
      }
      ++iter;
   }

   /*DString dstrDateOfBirth = NULL_STRING;
   getDofBirth( idDataGroup, dstrDateOfBirth );
   ValidateOldestLegalDate( dstrDateOfBirth, idDataGroup );*/

   ValidateTwinContracts(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfoList::validateDateRanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateDateRanges" ) );

   BFObjIter                iter( *this, idDataGroup, false,BFObjIter::ITERTYPE::NON_DELETED);
   BFObjIter                iter2( *this, idDataGroup, false,BFObjIter::ITERTYPE::NON_DELETED);
   DString                  strAC1EffectDate;
   DString                  strAC1StopDate;
   DString                  strAC2EffectDate;
   DString                  strAC2StopDate;

   while( !iter.end() )
   {
      iter.getObject()->getField(ifds::EffectiveDate,strAC1EffectDate,idDataGroup);
      iter.getObject()->getField(ifds::StopDate,strAC1StopDate,idDataGroup);
      //position iter2 on the next list item
      iter2.positionByKey( iter.getStringKey() ); 
      ++iter2;

      while( !iter2.end() )
      {
         if( ! iter2.isDummy() )
         {
            iter2.getObject()->getField(ifds::EffectiveDate,strAC2EffectDate,idDataGroup);
            iter2.getObject()->getField(ifds::StopDate,strAC2StopDate,idDataGroup);

            if( DSTCommonFunctions::dateRangesOverlap( strAC1EffectDate, strAC1StopDate,
                                                       strAC2EffectDate, strAC2StopDate ) )
            {
               DString strTemp;
               ADDCONDITIONFROMFILEIDI( CND::ERR_EFF_STOP_DATE_RANGE_OVERLAP, strTemp);
               return(GETCURRENTHIGHESTSEVERITY());
            }
         }
         ++iter2;
      }

      ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool ContractInfoList::setMultiContrPerm( bool bMultiContract )
{
   bMultiContract = getWorkSession().hasReadPermission( UAF::SEG_FUND_MULTI_CONTRACT );
   return(bMultiContract);
}

//******************************************************************************
SEVERITY ContractInfoList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::CONTRACTINFO_LIST, 
                  *pRequestData105, 
                  ifds::DSTC0105_VW, 
                  DSTCRequestor( getSecurity(), false ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfoList::getMasterContractList(MasterContractList*& _pMasterContractList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterContractList" ) );
   
   DString dstrPorfolioIsRequried;
   getWorkSession().getOption( ifds::PorfolioIsRequried, dstrPorfolioIsRequried, idDataGroup, false );      
   dstrPorfolioIsRequried.strip().upperCase();

   if( dstrPorfolioIsRequried == I_("Y") )
   {
      DString dstrAcctNum;

      ContractInfoList* pContractInfoList = static_cast<ContractInfoList*>(this);
      if ( NULL != pContractInfoList )
      {
         dstrAcctNum  = pContractInfoList->getAcctNum();
      }
      
      getWorkSession().getMFAccount( idDataGroup, dstrAcctNum, pMFAccount );
      if ( NULL != pMFAccount )
      {
         pMFAccount->getMasterContractListByPortfolio(_pMasterContractList,idDataGroup);
      }   
   }
   else
   {
      getMgmtCo().getMasterContractList( _pMasterContractList );
   }   
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ContractInfoList.cpp-arc  $
 * 
 *    Rev 1.49   Apr 18 2012 15:35:08   if991250
 * IN 2900126 - change error message when the linked contract is missing
 * 
 *    Rev 1.48   Apr 10 2012 17:24:52   if991250
 * IN 2900207 Contract Information - changed linked contracts error message
 * 
 *    Rev 1.47   Apr 10 2012 16:20:46   if991250
 * IN 2900207 Contract Information
 * 
 *    Rev 1.46   Jan 27 2012 19:27:24   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.45   Jan 21 2012 09:24:40   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.44   Dec 27 2011 00:47:08   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.43   May 30 2006 18:00:50   ZHANGCEL
 * PET2102 FN01 -- Legal age related changes
 * 
 *    Rev 1.42   May 25 2006 17:49:04   ZHANGCEL
 * PET 2102 FN01 -- Legal age related changes with new view367
 * 
 *    Rev 1.41   Nov 14 2004 14:29:58   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.40   Mar 21 2003 18:02:00   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.39   Jan 03 2003 14:52:14   FENGYONG
 * populate entity before use it.
 * 
 *    Rev 1.38   Oct 09 2002 23:54:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.37   Aug 29 2002 12:55:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.36   Jul 17 2002 14:46:14   HSUCHIN
 * getDofBirth had a bug where it could not find an entity due to the sequence number not resetting.  Refer to comment in code for full detail description of fix.
 * 
 *    Rev 1.35   Jul 16 2002 11:45:14   HSUCHIN
 * no change - removed old commented out code
 * 
 *    Rev 1.34   Jul 16 2002 11:43:38   HSUCHIN
 * no change - beautified source
 * 
 *    Rev 1.33   May 28 2002 12:18:38   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.32   22 May 2002 18:26:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.31   May 06 2002 11:53:24   YINGBAOL
 * Fix ValidateOldestLegalDate
 * 
 *    Rev 1.30   Feb 25 2002 18:55:12   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.29   Nov 20 2001 15:23:06   ZHANGCEL
 * reverse changeing haspermission
 * 
 *    Rev 1.28   Nov 20 2001 14:59:20   ZHANGCEL
 * Change Permission for release 44
 * 
 *    Rev 1.27   Nov 15 2001 10:06:28   ZHANGCEL
 * Milestone check in
 * 
 *    Rev 1.26   Nov 14 2001 11:46:56   ZHANGCEL
 * Many changes for Multiple Contracts
 * 
 *    Rev 1.25   Nov 07 2001 14:35:52   ZHANGCEL
 * Many changes for multiple Contracts
 * 
 *    Rev 1.23   18 Oct 2001 13:58:56   HSUCHIN
 * Changed the validation to allow duplicate contracts and checks for unique date ranges
 * 
 *    Rev 1.22   05 Aug 2001 11:36:18   YINGZ
 * fix delete bug
 * 
 *    Rev 1.21   Jul 16 2001 19:13:32   OLTEANCR
 * added setMultiContractPerm(..)
 * 
 *    Rev 1.20   Jun 26 2001 12:55:02   PURDYECH
 * Infrastructure Release 1.9 Integration.
 * 
 *    Rev 1.19   14 May 2001 09:34:22   YINGZ
 * code sync up
 * 
 *    Rev 1.17.1.0   10 May 2001 11:45:58   HSUCHIN
 * Sync up with SSB
 * 
 *    Rev 1.17   Jan 18 2001 16:04:32   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.16   Jan 17 2001 12:08:32   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.15   Dec 17 2000 20:22:50   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.14   Dec 04 2000 13:37:00   ZHANGCEL
 * Added logic for EffectiveDate validation, Added "const" for variables in the namespace
 * 
 *    Rev 1.13   Nov 01 2000 11:10:46   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.12   Oct 19 2000 17:20:12   KOVACSRO
 * Bug fixed.
 * 
 *    Rev 1.11   Oct 13 2000 15:17:12   KOVACSRO
 * Modified init() not to call always the view.
 * 
 *    Rev 1.10   Oct 02 2000 12:06:40   ZHANGCEL
 * Added a condition for Province validation
 * 
 *    Rev 1.9   Sep 21 2000 14:42:26   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.8   Jul 28 2000 16:42:26   ZHANGCEL
 * Removed date overlap validation ( no longer needed )
 * 
 *    Rev 1.7   Jul 26 2000 11:07:54   ZHANGCEL
 * Added code for validateing date overlap problem
 * 
 *    Rev 1.6   Jul 07 2000 10:25:44   ZHANGCEL
 * Deal with the leap year problem
 * 
 *    Rev 1.5   May 12 2000 17:47:44   ZHANGCEL
 * Deal with DofBirth checking problem
 * 
 *    Rev 1.4   Apr 20 2000 16:36:18   ZHANGCEL
 * Milestone check in
 * 
 *    Rev 1.3   Apr 14 2000 09:45:50   ZHANGCEL
 * Added functions for validation
 * 
 *    Rev 1.2   Apr 11 2000 11:50:56   ZHANGCEL
 * Set default value
 * 
 *    Rev 1.1   Mar 07 2000 10:26:32   HSUCHIN
 * changed to use new infra
 * 
 *    Rev 1.2   Feb 24 2000 15:15:22   VASILEAD
 * Fixes for release
 * 
 *    Rev 1.1   Feb 22 2000 17:47:20   ZHANGCEL
 * Chech in for release
 * 
 *    Rev 1.0   Feb 03 2000 13:28:54   ZHANGCEL
 * Initial revision.
 * 
 *
 */