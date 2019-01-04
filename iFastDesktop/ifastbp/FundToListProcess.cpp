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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FundToListProcess.cpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 01/12/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundToListProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "fundtolistprocess.hpp"
#include <ifastcbo\feeinfoinquiry.hpp>
#include <ifastcbo\currencyclass.hpp>
#include <dataimpl\dse_dstc0136_vw.hpp>
#include <dataimpl\dse_dstc0099_vw.hpp>
#include <dataimpl\dse_dstc0148_vw.hpp>
#include <dataimpl\dse_dstc0107_vw.hpp>
#include <ifastcbo\fundtolist.hpp>
#include "fundtolistprocessincludes.h"
#include <ifastcbo\mgmtco.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDTOLIST;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FundToListProcess > processCreator( CMD_BPROC_FUNDTOLIST );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "FundToListProcess" );
   const DString EMPTY_STRING;
}

namespace FUNDTOLISTLIT  //stands for account details literals
{
   const I_CHAR * const FUNDCODE = I_( "TXFundCode" );  
   const I_CHAR * const CLASSCODE = I_( "TXClassCode" );  
   const I_CHAR * const FUNDSPONSOR = I_( "FundSponsorCode" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

namespace ifds
{  // Conditions used
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
}


using namespace FUNDTOLISTLIT;

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FundToListProcess::FundToListProcess() : 
FundToListProcess::FundToListProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pFundToList( NULL ),
_pFundDetailsList( NULL ),
_pTranslationList( NULL ),
_pFundMasterList( NULL ),
_pFundSponsorsList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::FUND_TO_LIST, true );
   addContainer( IFASTBP_PROC::FUNDDETAILS_LIST, true );
   addContainer( IFASTBP_PROC::FUNDMASTER_LIST, true );
   addContainer( IFASTBP_PROC::FUNDSPONSORS_LIST, true );
   addContainer( IFASTBP_PROC::TRANSLATION_LIST, true );
   addContainer( IFASTBP_PROC::FEEINFOINQUIRY_CBO, true );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUND_TO_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::FUND_TO_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::FromFund, IFASTBP_PROC::FUND_TO_LIST );
   addFieldDetails( ifds::FromClass, IFASTBP_PROC::FUND_TO_LIST );
   addFieldDetails( ifds::ToFund, IFASTBP_PROC::FUND_TO_LIST );
   addFieldDetails( ifds::ToClass, IFASTBP_PROC::FUND_TO_LIST );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUNDMASTER_LIST );
   addFieldDetails( ifds::FundGroup, IFASTBP_PROC::FUNDMASTER_LIST );

   addFieldDetails( ifds::FundGroup, IFASTBP_PROC::FUNDSPONSORS_LIST );
   addFieldDetails( ifds::FundGroupDesc, IFASTBP_PROC::FUNDSPONSORS_LIST );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUNDDETAILS_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::FUNDDETAILS_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::FUNDDETAILS_LIST );
   addFieldDetails( ifds::LoadType, IFASTBP_PROC::FUNDDETAILS_LIST );

   addFieldDetails(ifds::LangCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundName, IFASTBP_PROC::TRANSLATION_LIST );

   addFieldDetails( ifds::AcqRate, IFASTBP_PROC::FEEINFOINQUIRY_CBO );
   addFieldDetails( ifds::AcqFeeType, IFASTBP_PROC::FEEINFOINQUIRY_CBO);
   addFieldDetails( ifds::ClientLvlTfr, IFASTBP_PROC::FEEINFOINQUIRY_CBO);
   addFieldDetails( ifds::ClientLvlExch, IFASTBP_PROC::FEEINFOINQUIRY_CBO,SUBCLASS_PROCESS);


}

//******************************************************************************

FundToListProcess::~FundToListProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _pTranslationList = NULL;
   if( _pFundToList )
   {
      delete _pFundToList;   _pFundToList = NULL;
   }
   if( _pFeeInfoInquiry )
   {
      delete _pFeeInfoInquiry;   _pFeeInfoInquiry = NULL;
   }

}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY FundToListProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   DString _pFundSponsor,_pFundCode = NULL_STRING, _pClassCode = NULL_STRING;
   try
   {
      MgmtCo &mgmtCoOut = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo();

      getParameter( FUNDSPONSOR,       _pFundSponsor);

      sevRtn = mgmtCoOut.getFundDetailList( _pFundDetailsList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDDETAILS_LIST, _pFundDetailsList );
      }

      sevRtn = mgmtCoOut.getFundMasterList( _pFundMasterList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDMASTER_LIST, _pFundMasterList );
      }

      sevRtn = mgmtCoOut.getFundSponsorsList( _pFundSponsorsList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDSPONSORS_LIST, _pFundSponsorsList );
      }

      sevRtn = mgmtCoOut.getTranslationList( _pTranslationList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::TRANSLATION_LIST, _pTranslationList );
      }

      //sevRtn = mgmtCoOut.getFundToList( getWorkSessionID(), _pFundToList, _pFundCode, _pClassCode, _pFundSponsor );
      _pFundToList = new FundToList( *getBFWorkSession() );
      sevRtn = _pFundToList->init( _pFundCode, _pClassCode, _pFundSponsor);

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUND_TO_LIST, _pFundToList );
      }

      _pFeeInfoInquiry = new FeeInfoInquiry( *getBFWorkSession() );
      sevRtn = _pFeeInfoInquiry->init( _pFundCode, _pClassCode, _pFundSponsor);

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FEEINFOINQUIRY_CBO, _pFeeInfoInquiry );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN FundToListProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************

const DString& FundToListProcess::getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETFIRSTLISTITEMKEY );
/*
   DString key;

   try
   {
      if( idList == FUND_TO_LIST )
      {
         BFObjIter iterFundToList( *_pFundToList, getGroupID( rpGICaller ), true, BFObjIter::ITERTYPE::NON_DELETED );

         DString searchKey;
         FundToList::buildPartialKeyForGetFundsTo( searchKey, _fromFundCode, _fromClassCode );
         
         if( iterFundToList.begin( XCHG_TYPE_NONE, BF_SUBTYPE_NONE, OBJ_NONE, BF_CAT_NOT_SPEC, searchKey ) )
         {
            DString key = iterFundToList.getStringKey();
            AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
            return iterFundToList.getStringKey();
         }
         return EMPTY_STRING;
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY,
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
*/
   return(AbstractProcess::getFirstListItemKey( rpGICaller, idList ));
}

//******************************************************************************

const DString& FundToListProcess::getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );
/*   DString key;

   try
   {
      if( idList == FUND_TO_LIST )
      {
         BFObjIter iterFundToList( *_pFundToList, getGroupID( rpGICaller ), true, BFObjIter::ITERTYPE::NON_DELETED );

         DString fundToListCurrentItemKey = getCurrentListItemKey( rpGICaller, idList );
         DString searchKey;
         FundToList::buildPartialKeyForGetFundsTo( searchKey, _fromFundCode, _fromClassCode );
         
         if( iterFundToList.begin( XCHG_TYPE_NONE, BF_SUBTYPE_NONE, OBJ_NONE, BF_CAT_NOT_SPEC, searchKey ) )
         {
            iterFundToList.positionByKey( fundToListCurrentItemKey );

            if( !++iterFundToList )
               return EMPTY_STRING;
            else
            {
               DString key = iterFundToList.getStringKey();
               AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
               return iterFundToList.getStringKey();
            }
         }
         return EMPTY_STRING;
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY,
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
*/
   return(AbstractProcess::getNextListItemKey( rpGICaller, idList ));
}

//******************************************************************************

SEVERITY FundToListProcess::doSetField( const GenericInterface *rpGICaller, const BFContainerId& idContainer,
                                        const BFFieldId& idField, const BFDataGroupId& idDataGroup, const DString& strValue, bool bFormatted )
{

   if( idContainer == IFASTBP_PROC::FUND_TO_LIST && idField == ifds::FundCode )
   {
      _fromFundCode = strValue;
   }
   else if( idContainer == IFASTBP_PROC::FUND_TO_LIST && idField == ifds::ClassCode )
   {
      _fromClassCode = strValue;
   }

   return(NO_CONDITION);
}

//******************************************************************************

void FundToListProcess::doGetField( const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup, DString &strValueOut, bool bFormatted ) const
{
   if( idField == ifds::ClientLvlExch )
   {
      _pFeeInfoInquiry->getField(ifds::ClientLvlExch, strValueOut, idDataGroup, true);
   }
}
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundToListProcess.cpp-arc  $
// 
//    Rev 1.16   Mar 21 2003 17:40:34   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.15   Mar 11 2003 13:49:50   PURDYECH
// Fixes to help the DataGroupId source code converters work more smoothly.
// 
//    Rev 1.14   Oct 09 2002 23:53:16   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.13   Aug 29 2002 16:44:56   SMITHDAV
// Condition split.
// 
//    Rev 1.12   Aug 29 2002 12:54:22   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.11   22 May 2002 18:24:16   PURDYECH
// BFData Implementation
// 
//    Rev 1.10   27 Mar 2002 19:54:54   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.9   Jun 08 2001 13:40:46   ZHANGCEL
// fix pron error
// 
//    Rev 1.8   Jun 06 2001 14:41:14   FENGYONG
// Add clientlvlexchFee
// 
//    Rev 1.7   03 May 2001 14:05:24   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.6   Mar 29 2001 14:05:38   FENGYONG
// change getfield
// 
//    Rev 1.5   Mar 21 2001 12:51:52   FENGYONG
// get fundtolist by fromfund,from class or fundsponsor
// 
//    Rev 1.4   Mar 02 2001 16:35:30   FENGYONG
// comment out getfirstlistitemkey and getnextlistitemkey
// 
//    Rev 1.3   15 Dec 2000 12:43:30   PURDYECH
// Use precompiled header stdafx.h.
// Removed unnecessary header files.
// 
//    Rev 1.2   Dec 11 2000 11:54:58   VASILEAD
// Added back end funds support
// 
//    Rev 1.1   Dec 05 2000 15:46:58   VASILEAD
// Added worksessionid for init
// 
//    Rev 1.0   Dec 04 2000 13:11:04   VASILEAD
// Initial revision.
 * 
 * 
 */


