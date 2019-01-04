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
//    Copyright 2002 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : FeeParamSysList.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : Jan. 11, 2002
//
// ^CLASS    : FeeParamSysList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0230_req.hpp>
#include <ifastdataimpl\dse_dstc0230_vw.hpp>

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"
#include "feeparamBaselist.hpp"
#include "feeparamsyslist.hpp"
#include "FeeParamSys.hpp"
#include "FeeParamConfigList.hpp"



namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM_SYSTEM_LIST;
}


namespace  
{
   const I_CHAR * const CLASSNAME    = I_( "FeeParamSysList" );  
   const I_CHAR * const IDI_CODE     = I_("CODE");  
   const I_CHAR * const DEFAULT_DATE = I_( "01010001" );
   const I_CHAR * const YES			 = I_( "Y" );
   const I_CHAR * const NO			 = I_( "N" );

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//*********************************************************************************
FeeParamSysList::FeeParamSysList( BFAbstractCBO &parent )
: FeeParamBaseList( parent )
, requestData230( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
FeeParamSysList::~FeeParamSysList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   delete requestData230;
}

//*********************************************************************************
SEVERITY FeeParamSysList::init( const BFDataGroupId& idDataGroup, bool bDefault,
                  const DString& feeCode,              
                  const DString& dstrTrack,
                  const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
// receive data from back end
	DString mgmtCoIdOut;
	DString dstrSearchType;
   DString dstrBrokerCode;
   DString dstrCommGroupCode;
   DString dstrFundCode;
   DString dstrClassCode;
   DString dstrFeeCode;
   DString dstrShGroup;
   DString dstrBranchCode;
   DString dstrSalesRepCode;
   DString dstrFeeModelCode;
   DString dstrAsofDate;

	bDefault_ = bDefault;
	requestData230 = new BFData(ifds::DSTC0230_REQ);  
   if( bDefault_ )
   {
  	      requestData230->setElementValue( ifds::SysFeeSearchType, NULL_STRING );   
 	      requestData230->setElementValue( ifds::FeeCode, feeCode );   
   }
   else
   {  
	      getParent()->getField(ifds::SysFeeSearchType,dstrSearchType,idDataGroup,false);
	      getParent()->getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup,false);
	      getParent()->getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
	      getParent()->getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);
	      getParent()->getField(ifds::CommGroup,dstrCommGroupCode,idDataGroup,false);
         if(I_("NA") == dstrCommGroupCode)
            dstrCommGroupCode = I_("");
	      getParent()->getField(ifds::FeeCode,dstrFeeCode,idDataGroup,false);
	      getParent()->getField(ifds::ShGroup,dstrShGroup,idDataGroup,false);
	      getParent()->getField(ifds::BranchCode,dstrBranchCode,idDataGroup,false);
	      getParent()->getField(ifds::SlsrepCode,dstrSalesRepCode,idDataGroup,false);
	      getParent()->getField(ifds::FeeModelCode,dstrFeeModelCode,idDataGroup,false);
         
	      requestData230->setElementValue( ifds::BrokerCode, dstrBrokerCode );
	      requestData230->setElementValue( ifds::FundCode, dstrFundCode );
	      requestData230->setElementValue( ifds::ClassCode, dstrClassCode );
	      requestData230->setElementValue( ifds::CommGroup, dstrCommGroupCode );
	      requestData230->setElementValue( ifds::FeeCode, dstrFeeCode );
	      requestData230->setElementValue( ifds::ShGroup, dstrShGroup );
	      requestData230->setElementValue( ifds::SysFeeSearchType, dstrSearchType );
 	      requestData230->setElementValue( ifds::BranchCode, dstrBranchCode );
	      requestData230->setElementValue( ifds::SlsrepCode, dstrSalesRepCode );
	      requestData230->setElementValue( ifds::FeeModelCode, dstrFeeModelCode);
         
   }
	getParent()->getField(ifds::AsofDate,dstrAsofDate,idDataGroup,false);
   requestData230->setElementValue( ifds::AsofDate, dstrAsofDate );
   requestData230->setElementValue( ifds::DefaultFeeCode, bDefault?YES:NO );
   requestData230->setElementValue( ifds::DefaultFeeCode, bDefault?YES:NO );
	requestData230->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	requestData230->setElementValue( ifds::Track, dstrTrack );
	requestData230->setElementValue( ifds::Activity, dstrPageName );
	requestData230->setElementValue( ifds::NextKey,     NULL_STRING );
	BFData* responseData = new BFData(ifds::DSTC0230_VW);
	ReceiveData(DSTC_REQUEST::FEE_PARAM_SYSTEM_LIST, *requestData230, *responseData, 
      DSTCRequestor( getSecurity(),bDefault_,false ) );


   return(GETCURRENTHIGHESTSEVERITY());
}
//********************************************************************************
SEVERITY FeeParamSysList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );


   pObjOut =  new FeeParamSys( *this );
   ((FeeParamSys* )pObjOut )->Init(data,bDefault_);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FeeParamSysList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   FeeParamSys* pFeeParamSys = new FeeParamSys( *this );
   pFeeParamSys->InitNew( idDataGroup  );
   pBase = pFeeParamSys;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FeeParamSysList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
	   BFData* responseData = new BFData(ifds::DSTC0230_VW);
	   ReceiveData(DSTC_REQUEST::FEE_PARAM_SYSTEM_LIST, *requestData230, *responseData, DSTCRequestor( getSecurity(),false,false ) );
    }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//get default value using effective date 01/01/0001, feecode, fund, fundgroup
SEVERITY FeeParamSysList::getDefaultFeeParamRecord
												(
													 FeeParamSys *&pFeeParamSys, 
													 const DString strFeeCode, 
													 const DString strFundCode, 
													 const DString strClassCode, 
													 const DString strFundGroup, 
													 const BFDataGroupId& idDataGroup,
                                        const bool bCompFundGroup,
                                        bool  bCompFundClass
												)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDefaultFeeParamRecord" ) );

   DString dstrEffectiveDate, dstrStopDate;
   DString dstrFeeCodeComp, dstrFundCodeComp, dstrClassCodeComp, dstrFundGroupComp;

   pFeeParamSys = NULL;

   BFObjIter iter(*this, BF::HOST, false , BFObjIter::ITERTYPE::NON_DELETED );
   while ( !iter.end() ) 
   {
      iter.getObject()->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
      iter.getObject()->getField( ifds::StopDate, dstrStopDate, idDataGroup, false );
      iter.getObject()->getField( ifds::FeeCode, dstrFeeCodeComp, idDataGroup, false );
      iter.getObject()->getField( ifds::FundCode, dstrFundCodeComp, idDataGroup, false );
      iter.getObject()->getField( ifds::ClassCode, dstrClassCodeComp, idDataGroup, false );
      iter.getObject()->getField( ifds::CommGroup, dstrFundGroupComp, idDataGroup, false );

      dstrEffectiveDate.strip();
      dstrStopDate.strip();
      dstrFeeCodeComp.strip();
      dstrFundCodeComp.strip();
      dstrClassCodeComp.strip();
      dstrFundGroupComp.strip();


      // find the corresponding record by matching the effectivedate = "01/01/0001" and stopdate = "01/01/0001"
     if (	 DSTCommonFunctions::CompareDates(dstrEffectiveDate, DEFAULT_DATE ) == DSTCommonFunctions::EQUAL  
		  && DSTCommonFunctions::CompareDates(dstrStopDate, DEFAULT_DATE ) == DSTCommonFunctions::EQUAL 
        && dstrFeeCodeComp == strFeeCode )
     {
         if( bCompFundGroup && dstrFundGroupComp != strFundGroup )
         {
            ++iter;
            continue;
         }

        if( bCompFundClass && ( strFundCode != NULL_STRING || strClassCode != NULL_STRING ) )
         {
            if( dstrFundCodeComp != strFundCode || dstrClassCodeComp != strClassCode )
            {
               ++iter;
               continue;
            }
         }
        
        // default value for FeeModel
        
         pFeeParamSys = dynamic_cast<FeeParamSys*>( iter.getObject() );  
         break;
        
                
     }
      ++iter;
   }

   CLEARCONDITIONSFRAMECURRENT(); 
   return NO_CONDITION;
}

SEVERITY FeeParamSysList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   FeeParamBaseList::doValidateAll(idDataGroup, lValidateGroup);
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

   while( !iter.end() )
   {
        dynamic_cast<FeeParamSys*>(iter.getObject() )->clearUpdateFlags( idDataGroup );

        ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
// the method is created for tuning purpose
// What we found is that in Dynamic environment to retrieve default value is very slow
// view will be changed to using index and feecode to retrieve default fee parameter
// it will be called in mgmtCo object
// Incident 240192
//

SEVERITY FeeParamSysList::initForDefault( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initForDefault" ) );
   FeeParamConfigList *pFeeParamConfigList = NULL;
   DString feeCode;
   if ( getMgmtCo().getFeeParamConfigList (pFeeParamConfigList) <= WARNING &&
         pFeeParamConfigList)
   {
      DString feeCodeList;
      if( pFeeParamConfigList->getAllFeeCodeInTheList( feeCodeList ) )
      {
         int iPos =  feeCodeList.find_first_of(I_(";") );
         while( iPos != DString::npos )
         {
		      iPos =  feeCodeList.find_first_of(I_(";") );
		      if( iPos == DString::npos ) break;
		      feeCode = feeCodeList.left(iPos);
		      feeCodeList = feeCodeList.right(feeCodeList.length() - iPos  - 1);
            feeCode.strip();
            if( feeCode != NULL_STRING )
            {
               init(	idDataGroup, true, feeCode );           
            }                      
         }	     
      }
   }
   // we don't want it to return error
   CLEARCONDITIONSFRAMECURRENT(); 
   return NO_CONDITION;
}

SEVERITY FeeParamSysList::copyItem(const DString &strKey, const BFDataGroupId& idDataGroup, DString &newKey)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initForDefault" ) );
   FeeParamSys* pOldFeeParamSys = dynamic_cast<FeeParamSys*>( getObject(strKey, idDataGroup));
      
   BFObjectKey objKey( newKey, idDataGroup );
   FeeParamSys* pFeeParamSysClone = dynamic_cast<FeeParamSys*>(getNewListItem(objKey));
   pOldFeeParamSys->copyData(pFeeParamSysClone, idDataGroup);

   newKey = objKey.getStringKey();
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParamSysList.cpp-arc  $
// 
//    Rev 1.19   Apr 20 2005 13:54:38   yingbaol
// Incident240192: put version 1.16 back, incindent 265632 in R60 and 240192 in R61.
// 
//    Rev 1.16   Apr 14 2005 08:58:24   yingbaol
// Incident 265632 Change set default fee logic for FundSponsorFee
// 
//    Rev 1.15   Mar 21 2005 10:19:40   yingbaol
// Incident240192: Speed up getDefault fee parameter
// 
//    Rev 1.14   Dec 20 2004 15:50:12   yingbaol
// PTS10036888:fix default value for FeeModel
// 
//    Rev 1.13   Nov 14 2004 14:40:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.12   Sep 10 2004 15:51:42   FENGYONG
// PET1117 FN5 - Client Fee
// 
//    Rev 1.11   Jul 02 2003 13:33:08   YINGBAOL
// PTS10019127,sync.verison 1.8.1.0
// 
//    Rev 1.10   Jun 26 2003 10:21:04   linmay
// added doValidateAll()
// 
//    Rev 1.9   Jun 20 2003 16:31:38   linmay
// PTS#10014935
// 
//    Rev 1.8   May 02 2003 14:56:28   linmay
// modified init()
// 
//    Rev 1.7   Mar 21 2003 18:09:40   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Jan 31 2003 10:28:50   linmay
// modified init()
// 
//    Rev 1.5   Jan 17 2003 14:08:10   YINGBAOL
// change Init method
// 
//    Rev 1.4   Jan 15 2003 16:19:28   linmay
// added getMore() 
// 
//    Rev 1.3   Jan 15 2003 11:57:56   linmay
// added Log Comment
// 
*/
