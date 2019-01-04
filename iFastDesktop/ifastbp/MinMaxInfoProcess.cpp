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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : MinMaxInfoProcess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/18/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MinMaxInfoProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "minmaxinfoprocess.hpp"
#include <ifastcbo\minmaxinfolist.hpp>
#include "minmaxinfoprocessincludes.h"
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MINMAXINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MINMAXINFO;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MinMaxInfoProcess > processCreator( CMD_BPROC_MINMAXINFO );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "MinMaxInfoProcess" );
}

namespace MINMAX
{
   const I_CHAR * const ACCOUNT_NUMBER    = I_( "AccountNum" );
   const I_CHAR * const AS_OF_DATE        = I_( "AsofDate" );
   const I_CHAR * const TAX_TYPE          = I_( "TaxType" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319MinMaxInfoProcess::MinMaxInfoProcess() : 
MinMaxInfoProcess::MinMaxInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pMinMaxInfoList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MINMAXINFO_CBO, false , BF::NullContainerId, false, I_("MinMaxInfo"));

   addFieldDetails( ifds::MinAmtWith, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::MinAmtOut, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::OptAmtWith, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::OptAmtOut, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::TotAmtWith, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::TaxAmtWith, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::TotAmtOut, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::TaxAmtOut, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::OthAmtWith, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::MinAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::MinAmtShort, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::MaxAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::MaxAmtRemain, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::sMandMinAmtYr, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::sMinAmtWith, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::sMinAmtOut, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::sMinSched, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::sMinAmtShort, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::sMandMaxAmtYr, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::sMaxAmtWith, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::sMaxAmtOut, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::sMaxSched, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::sMaxAmtShort, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mCurrYrDep, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mCurrMktValue, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mPYEMktValue, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mMinAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mMinAmtRemain, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mMaxAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mMaxAmtRemain, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mFreeAmtRemain, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mFreeAmtUsed, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mSchedPayGrossAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mUnSchedWithGrossAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mTransfGrossAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mTotGrossAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mSchedPayChrg, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mUnSchedWithChrg, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mTransfChrg, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mTotChrg, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mSchedPymtTaxAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mUnSchedWithTaxAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mTransfTaxAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mTotTax, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mSchedPayNetAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mUnSchedWithNetAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mTransfNetAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::mTotNetAmt, IFASTBP_PROC::MINMAXINFO_CBO );
   addFieldDetails( ifds::UnLockGrossAmt, IFASTBP_PROC::MINMAXINFO_CBO, SUBCLASS_PROCESS );
   addFieldDetails( ifds::UnLockDeff, IFASTBP_PROC::MINMAXINFO_CBO );

//   addFieldDetails( AS_OF_DATE, BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************

MinMaxInfoProcess::~MinMaxInfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pMinMaxInfoList;
   _pMinMaxInfoList = NULL;
   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY MinMaxInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( MINMAX::ACCOUNT_NUMBER, _strAccountNum );
      getParameter( MINMAX::TAX_TYPE, _strTaxType );
      _strAccountNum.stripAll();

      //register NULL with base (the actual list has not been created yet)
//		setContainer( MINMAXINFO_CBO, 0 );


      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getMgmtCoOptions()->getField(ifds::CurrBusDate, _dstrAsofDate, getDataGroupId( ), false );
/*
      _pMinMaxInfoList = new MinMaxInfoList( *dstcWorkSession );
      sevRtn = _pMinMaxInfoList->init( strAccountNum, dstrAsofDate);
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MINMAXINFO_CBO, _pMinMaxInfoList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }*/
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

E_COMMANDRETURN MinMaxInfoProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( MINMAX::ACCOUNT_NUMBER, _strAccountNum );
      setParameter( MINMAX::TAX_TYPE, _strTaxType );

      rtn = invokeCommand( this, CMD_GUI_MINMAXINFO, PROC_NO_TYPE, isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}


//******************************************************************************
bool MinMaxInfoProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.

   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   SEVERITY sevRtn = SEVERE_ERROR;

   bool bRtn = false;
   try
   {

      getParameter( MINMAX::ACCOUNT_NUMBER, _strAccountNum );
      getParameter( MINMAX::TAX_TYPE, _strTaxType );
      getParameter( MINMAX::AS_OF_DATE, _dstrAsofDate );

      _strAccountNum.stripAll();			

		delete _pMinMaxInfoList;
		_pMinMaxInfoList = NULL;


/*
      sevRtn = _pMinMaxInfoList->init( _strAccountNum, dstrAsofDate );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MINMAXINFO_CBO, _pMinMaxInfoList );
      }
*/
      setParameter( MINMAX::ACCOUNT_NUMBER, _strAccountNum );
      setParameter( MINMAX::TAX_TYPE, _strTaxType );
      setParameter( MINMAX::AS_OF_DATE, _dstrAsofDate );

      if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
      {
         return(bRtn);// false
      }
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(bRtn);
}
//******************************************************************************

bool MinMaxInfoProcess::doModelessChildComplete( const Command &cmd )
{
   // All done, ready to be self destructed
   return( cmd.getKey() == CMD_GUI_MINMAXINFO );
}



//******************************************************************************

bool MinMaxInfoProcess::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   setParameter( MINMAX::ACCOUNT_NUMBER, _strAccountNum );
   setParameter( MINMAX::TAX_TYPE, _strTaxType );
   return(_rpChildGI->refresh( this, NULL ) );

}


//******************************************************************************
SEVERITY MinMaxInfoProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch") );
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      getParameter( MINMAX::ACCOUNT_NUMBER, _strAccountNum );
      getParameter( MINMAX::AS_OF_DATE, _dstrAsofDate );

      delete _pMinMaxInfoList;
      _pMinMaxInfoList = new MinMaxInfoList( *getBFWorkSession() );
      sevRtn = _pMinMaxInfoList->init( _strAccountNum, _dstrAsofDate );
      if( sevRtn <= WARNING )
      {
         setContainer( IFASTBP_PROC::MINMAXINFO_CBO, _pMinMaxInfoList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//*********************************************************************************
void *MinMaxInfoProcess::getPtrForContainer( const BFContainerId& idContainer,
                                           const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   try
   {
      if( IFASTBP_PROC::MINMAXINFO_CBO == idContainer )
      {
			 if(    _pMinMaxInfoList == NULL )
			 {
				_pMinMaxInfoList = new MinMaxInfoList( *getBFWorkSession() );
				_pMinMaxInfoList->init( _strAccountNum, _dstrAsofDate);
			 }
      }
		ptr = _pMinMaxInfoList;

	}
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      //Show we throw?
   }
   return(ptr);

}

//******************************************************************************
void MinMaxInfoProcess::doGetField ( const GenericInterface *rpGICaller,
                                 const BFContainerId &idContainer,
                                 const BFFieldId &idField,
                                 const BFDataGroupId &idDataGroup, 
                                 DString &strValueOut,
                                 bool bFormatted) const
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doGetField"));

   strValueOut = NULL_STRING;
   if( idField == ifds::UnLockGrossAmt )
   {
	   //show a positive number
	   BFAbstractCBO *rpPtr = const_cast<MinMaxInfoProcess*> (this)->
                              getCBOItem ( IFASTBP_PROC::MINMAXINFO_CBO, 
                                           idDataGroup);
         if (rpPtr)
         {
			 rpPtr->getField ( idField, strValueOut, idDataGroup, bFormatted);
			 if( !strValueOut.strip().empty() )
			 {
                strValueOut.strip( '-' );
			 }
		 }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MinMaxInfoProcess.cpp-arc  $
 * 
 *    Rev 1.20   16 May 2008 16:08:30   kovacsro
 * PET2255_FN47 - show positive value for Last Unlocking amount, regardless.
 * 
 *    Rev 1.19   11 Apr 2008 12:00:16   kovacsro
 * PET2255-FN47_Ontario Locked-In Products - added 2 new fields on MinMax screen
 * 
 *    Rev 1.18   Jul 02 2003 16:03:20   YINGBAOL
 * promot error message if view call has error
 * 
 *    Rev 1.17   Mar 21 2003 17:45:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.16   Oct 09 2002 23:53:30   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 16:45:10   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.14   Aug 29 2002 12:54:34   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   22 May 2002 18:24:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   27 Mar 2002 19:55:32   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.11   Jun 07 2001 11:05:52   YINGBAOL
 * fix refresh issue
 * 
 *    Rev 1.10   11 May 2001 16:33:36   YINGZ
 * code sync up
 * 
 *    Rev 1.9   03 May 2001 14:05:36   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Jan 17 2001 12:08:10   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.7   15 Dec 2000 13:07:18   PURDYECH
 * Removed a silly typing error from Precompiled Header changeover.
 * 
 *    Rev 1.6   15 Dec 2000 12:43:44   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.5   Nov 30 2000 10:15:32   ZHANGCEL
 * added " const " for variables in the namespace
 * 
 *    Rev 1.4   Oct 19 2000 14:31:26   ZHANGCEL
 * Hourse keeping
 * 
 *    Rev 1.2   Aug 02 2000 15:32:02   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Mar 21 2000 14:31:28   ZHANGCEL
 * Milestone check in
 * 
 *    Rev 1.0   Mar 20 2000 15:48:00   ZHANGCEL
 * Initial revision.
// 
//    Rev 1.1   Feb 29 2000 15:32:14   ZHANGCEL
// Added two new parameters
 * 
 *
 */
