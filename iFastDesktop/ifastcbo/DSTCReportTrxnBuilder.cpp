//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : DSTCReportTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : Nov 18, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : DSTCReportTrxnBuilder
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcreporttrxnbuilder.hpp"
#include "ifastcommonreportcriteria.hpp"
#include "ifastreportcriterialist.hpp"
#include <ifastcbo\mgmtco.hpp>
#include <ifastdataimpl\dse_dstc0220_req.hpp>
#include <ifastdataimpl\dse_dstc0220_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0220_vw.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <AMSHypoAllocList.hpp>
#include <AMSHypoAlloc.hpp>

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCReportTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace ifds
{  
	extern CLASS_IMPORT const BFTextFieldId		FundCode;
   extern CLASS_IMPORT const BFTextFieldId		ClassCode;
   extern CLASS_IMPORT const BFDecimalFieldId 	AllocPercentage;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const REPORT_NAME;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REPORT_UPDATE;
}

const BFFieldId fieldsInCommonCriteria[]=
{
   ifds::ReportMode,
   ifds::RunOnDate,
   ifds::RunOnTime,
   ifds::ReportName,
   ifds::PrinterName,
   ifds::ScheduleJob,
   ifds::ReportType,   
};

static const int numFieldsInCommonCriteria = sizeof( fieldsInCommonCriteria ) / sizeof( BFFieldId );

//******************************************************************************
void DSTCReportTrxnBuilder::buildTrxnKey( DString& strKey, ifastCommonReportCriteria* pifastCommonReportCriteria )
{
   DString dstrReportName;
   pifastCommonReportCriteria->getField( ifds::ReportName, dstrReportName, BF::HOST, true );
   //build the key    
   addIDITagValue( strKey, TRXNTAG::REPORTIDTAG, dstrReportName );   
}

//******************************************************************************
SEVERITY DSTCReportTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                 BFAbstractCBO* pObj,
                                                 HostTransactionContainer* pTrCont,
                                                 BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   ifastCommonReportCriteria* pifastCommonReportCriteria = dynamic_cast<ifastCommonReportCriteria*>(pObj);
   if( pifastCommonReportCriteria != NULL ) {
      ifastReportCriteriaList* pifastReportCriteriaList = pifastCommonReportCriteria->getCriteriaList( );      
      BFData* request = new BFData( ifds::DSTC0220_REQ );
      BFData* response = new BFData( ifds::DSTC0220_VW );
      DString mgmtCoId, dstrTrack, dstrActivity, dstr;
      workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
      request->setElementValue( ifds::CompanyId, mgmtCoId );      
      pifastCommonReportCriteria->getTrackActivity( dstrTrack,dstrActivity );
      request->setElementValue( ifds::Track, dstrTrack, false, false );
      request->setElementValue( ifds::Activity, dstrActivity, false, false );  
      
      //populate fixed section.
      for ( int i = 0; i <= numFieldsInCommonCriteria; i++ ) {
         pifastCommonReportCriteria->getField ( fieldsInCommonCriteria[i], dstr, BF::HOST );
         request->setElementValue( fieldsInCommonCriteria[i], dstr, false, false );
      }    

      //populate repeat section.
	  DString dstrCriteriaType,dstrReportName,dstrLevelRebal,dstrAMSCode,dstrAccountNum;
      int count = 0;
      BFFieldId fieldId;
      pifastCommonReportCriteria->getField ( ifds::ReportName, dstrReportName, BF::HOST );
	  bool bIsAMSHypocalRebal = (dstrReportName == I_("IFAST.AMSHYPOCALCREBAL") ? true : false);

	  BFObjIter iter ( *pifastReportCriteriaList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );   

	  BFData dataRepeat(ifds::DSTC0220_REQRepeat_Record);          

	  for(iter.begin();!iter.end();iter++){
         BFAbstractCBO* pBFAbstractCBO = iter.getObject();
         pBFAbstractCBO->getField ( ifds::CriteriaType, dstr, BF::HOST );
         dataRepeat.setElementValue( ifds::CriteriaType, dstr, false, false );
		 dstrCriteriaType = dstr;

		 if (dstrCriteriaType == I_("GlobalLevelRebal") || dstrCriteriaType == I_("AccountLevelRebal"))
		 {
			dstrLevelRebal = dstrCriteriaType;
			continue;
		 }
		 else if (dstrCriteriaType == NULL_STRING)
			continue;

         fieldId = BFFieldId::getId ( dstr );
/*         const BFDataFieldProperties* pProps = BFDataFieldProperties::get ( fieldId );
         if ( pProps->getType() == BFDataFieldProperties::Type::date ) {
            pBFAbstractCBO->getField ( fieldId, dstr, BF::HOST, true );
         } else {*/
            pBFAbstractCBO->getField ( fieldId, dstr, BF::HOST );
//         }
		 if (bIsAMSHypocalRebal)
		 {
			if (dstrCriteriaType == I_("AMSCode"))
			{
				dstrAMSCode = dstr;
				continue;
			}
			else if (dstrCriteriaType == I_("AccountNum"))
			{
				dstrAccountNum = dstr;
				continue;
			}
		 }
         dataRepeat.setElementValue( ifds::CriteriaValue, dstr, false, false );
         pBFAbstractCBO->getField ( ifds::IncludeExclude, dstr, BF::HOST );
         dataRepeat.setElementValue( ifds::IncludeExclude, dstr, false, false );
         pBFAbstractCBO->getField ( ifds::RecordType, dstr, BF::HOST );
		 if ((dstrCriteriaType == I_("PendingWithAMSFund") || dstrCriteriaType == I_( "UnsettleWithAMSFund" )) 
			 && dstr == I_("R") )
		 {
				dstr = I_("F"); // It must be "F", other wise VEWREBALN99.P expected recordType for "PendingWithAMSFund" is "F"
		 }
		 else if ( dstrCriteriaType == I_("AMSCode" ) && dstr == I_("F") )
		 {
			dstr = I_("R"); // CriteriaType "AMSCode" must be initial with "F" to prevent unexpected delete on screen.
		 }
         dataRepeat.setElementValue( ifds::RecordType, dstr, false, false );
         request->addRepeat( dataRepeat );	
         ++count;
      }

	  // If Report is Hypocal with allocation
	  DString dstrFund, dstrClass, dstrPrcnt;
	  AMSHypoAllocList* pAMSHypoAllocList;
	  dataRepeat.setElementValue ( ifds::CriteriaType, I_("HypocalRebal"), false, false );
	  dataRepeat.setElementValue ( ifds::CriteriaValue, (bIsAMSHypocalRebal ? I_("Y") : I_("N")), false, false );
	  dataRepeat.setElementValue ( ifds::IncludeExclude, I_("Y"), false, false );
	  dataRepeat.setElementValue ( ifds::RecordType, I_("R"), false, false );
	  request->addRepeat( dataRepeat );	
	  ++count;
	  if(bIsAMSHypocalRebal)
	  {
		  pAMSHypoAllocList = pifastReportCriteriaList->getAMSHypoAllocList(BF::HOST);
		  for(BFObjIter iter(*pAMSHypoAllocList, BF::HOST); !iter.end(); ++iter)
		  {
			  DString dstr;

			  iter.getObject()->getField(ifds::FundCode, dstr, BF::HOST);
			  if(dstrFund.empty() || dstrFund == "")
				dstrFund = dstr;
			  else 
				dstrFund = dstrFund + I_("|") + dstr;

			  dstr = NULL_STRING;
			  iter.getObject()->getField(ifds::ClassCode, dstr, BF::HOST);
			  if(dstrClass.empty() || dstrClass == "")
				dstrClass = dstr;
			  else 
				dstrClass = dstrClass + I_("|") + dstr;

			  dstr = NULL_STRING;
			  iter.getObject()->getField(ifds::AllocPercentage, dstr, BF::HOST, true);
			  if(dstrPrcnt.empty() || dstrPrcnt == "")
				dstrPrcnt = dstr;
			  else 
				dstrPrcnt = dstrPrcnt + I_("|") + dstr;
		  }
	  
		dataRepeat.setElementValue ( ifds::CriteriaType, I_("AllocFund"), false, false );
		dataRepeat.setElementValue ( ifds::CriteriaValue, dstrFund, false, false );
		dataRepeat.setElementValue ( ifds::IncludeExclude, I_("Y"), false, false );
		dataRepeat.setElementValue ( ifds::RecordType, I_("R"), false, false );
		request->addRepeat( dataRepeat );	
		++count;

		dataRepeat.setElementValue ( ifds::CriteriaType, I_("AllocClass"), false, false );
		dataRepeat.setElementValue ( ifds::CriteriaValue, dstrClass, false, false );
		dataRepeat.setElementValue ( ifds::IncludeExclude, I_("Y"), false, false );
		dataRepeat.setElementValue ( ifds::RecordType, I_("R"), false, false );
		request->addRepeat( dataRepeat );	
		++count;

		dataRepeat.setElementValue ( ifds::CriteriaType, I_("AllocPrcnt"), false, false );
		dataRepeat.setElementValue ( ifds::CriteriaValue, dstrPrcnt, false, false );
		dataRepeat.setElementValue ( ifds::IncludeExclude, I_("Y"), false, false );
		dataRepeat.setElementValue ( ifds::RecordType, I_("R"), false, false );
		request->addRepeat( dataRepeat );	
		++count;

		DString dstrCriteriaType, dstrCriteriaValue;
		if (dstrLevelRebal == I_("GlobalLevelRebal"))
		{
			dstrCriteriaType = I_("AMSCode");
			dstrCriteriaValue = dstrAMSCode;
		}
		else
		{
			dstrCriteriaType = I_("AccountNum");
			dstrCriteriaValue = dstrAccountNum;
		}

		dataRepeat.setElementValue ( ifds::CriteriaType, dstrCriteriaType, false, false );
		dataRepeat.setElementValue ( ifds::CriteriaValue, dstrCriteriaValue, false, false );
		dataRepeat.setElementValue ( ifds::IncludeExclude, I_("Y"), false, false );
		dataRepeat.setElementValue ( ifds::RecordType, I_("R"), false, false );
		request->addRepeat( dataRepeat );	
		++count;
	  }
      request->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );

      DString dstrKeyTypes, strKey;
      addIDITagValue( dstrKeyTypes, KEYTYPES::REPORT_NAME, dstrReportName );
      buildTrxnKey( strKey, pifastCommonReportCriteria );
      TRXN_TYPE trxnType = NEW_ACCOUNT;
      JData *jdata = new JData( DSTC_REQUEST::REPORT_UPDATE, request, response );
      pTrCont->addTransaction( strKey, jdata, objActivity, NOT_PERSISTENT, dstrKeyTypes );
   }   
   return(GETCURRENTHIGHESTSEVERITY());   
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCReportTrxnBuilder.cpp-arc  $
// 
//    Rev 1.4   Apr 25 2008 15:27:30   jankovii
// IN 765715 - P20060104ET-#69 AMS Report shows Field "Type" as Blank and value = Yes.
// 
//    Rev 1.3   Mar 02 2007 11:06:08   ZHANGCEL
// Incident #765715 -- Set RecordType  to "F" for "PendingWithAMSFund".
// 
//    Rev 1.2   Nov 14 2004 14:33:16   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Mar 21 2003 18:06:34   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.0   Nov 27 2002 11:39:02   HSUCHIN
// Initial Revision
*/