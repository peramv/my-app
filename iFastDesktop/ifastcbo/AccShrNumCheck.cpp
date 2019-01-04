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
// ^FILE   : AccShrNumCheck.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Janauary, 20 2000
//
// ^CLASS    : AccShrNumCheck
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accshrnumcheck.hpp"
#include <ifastdataimpl\dse_dstc0120_req.hpp>
#include <ifastdataimpl\dse_dstc0120_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCSHRNUMCHECK;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccShrNumCheck" );
   const I_CHAR * const YES = I_( "Y" );
}

namespace CND
{
   extern const long ERR_ACCOUNT_NUM_CANNOT_BE_LEFT_EMPTY;
   extern const long ERR_ACCOUNT_NUMBER_EXISTS;
   extern const long ERR_SHAREHOLDER_NUMBER_EXISTS;
   extern const long ERR_SHAREHOLDER_NUM_CANNOT_BE_LEFT_EMPTY;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctNumCtrl;
   extern CLASS_IMPORT const BFTextFieldId ShrNumCtrl;
}

//******************************************************************************
AccShrNumCheck::AccShrNumCheck( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();

}

//******************************************************************************
AccShrNumCheck::~AccShrNumCheck( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AccShrNumCheck::initNew(const DString& shrNum, 
   const BFDataGroupId& idDataGroup /*= BF::HOST*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

/*
 * The purpose of this view is mainly to check if the user input for either an account num 
 * or a shareholder num is not a duplicate on the database. However, is the view is called
 * with the shr number set then it returns all account numbers belonging to a shareholder, if 
 * that shareholder exists.
 */
//******************************************************************************
SEVERITY AccShrNumCheck::initCheck(const DString& shrNum, 
   const DString& accountNum, const DString& dstrCallByProc,
   const DString& dstrTrack, const DString& dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );   

   DString tempAccountNum( accountNum );
   DString tempShrNum( shrNum );

   tempAccountNum.strip().stripLeading( '0' );
   tempShrNum.strip().stripLeading( '0' );

   //creating account in manual mode
   DString accNumCtrl;
   if( getWorkSession().getOption( ifds::AcctNumCtrl, accNumCtrl, BF::HOST ) <= WARNING )
   {
      if( accNumCtrl.upperCase() == I_( "M" ) )
      {
         if( tempAccountNum == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_NUM_CANNOT_BE_LEFT_EMPTY );
         }
      }
      else
      {
         //should have either one assigned to NULL_STRING
         assert( ( tempShrNum != NULL_STRING && tempAccountNum == NULL_STRING ) ||
                 ( tempShrNum == NULL_STRING && tempAccountNum != NULL_STRING ) );
      }
   }


   BFData requestData(ifds::DSTC0120_REQ);
   BFData *responseData = new BFData(ifds::DSTC0120_VW);
   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::ShrNum, tempShrNum );
   requestData.setElementValue( ifds::AccountNum, tempAccountNum );      
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
   requestData.setElementValue(ifds::CalledByProc, dstrCallByProc);
   
   if( ReceiveData(DSTC_REQUEST::ACCSHRNUMCHECK, requestData, 
         *responseData, DSTCRequestor( getSecurity(), true) ) > WARNING )
      delete responseData;

   //creating account in manual mode
   if( accNumCtrl.upperCase() == I_( "M" ) )
   {
      DString strFound;
      responseData->getElementValue( ifds::DataFound, strFound);

      if( strFound == YES )
         ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_NUMBER_EXISTS );

   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY AccShrNumCheck::init(const DString& shrNum, const DString& dstrCallByProc,
   const DString& dstrTrack, const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );   

   DString tempShrNum( shrNum );
   tempShrNum.strip().stripLeading( '0' );

   //creating account in manual mode
   DString shrNumCtrl;

   if (getWorkSession().getOption( ifds::ShrNumCtrl, shrNumCtrl, BF::HOST )<= WARNING )
   {
      if( shrNumCtrl.upperCase() == I_( "M" ) )
      {
         if( tempShrNum == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_SHAREHOLDER_NUM_CANNOT_BE_LEFT_EMPTY );     
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
      else
      {
         assert( tempShrNum != NULL_STRING );
      }
   }


   BFData requestData(ifds::DSTC0120_REQ);
   BFData *responseData = new BFData(ifds::DSTC0120_VW);

   DString mgmtCoIdOut;
   requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut ));
   requestData.setElementValue(ifds::ShrNum, tempShrNum);  
   requestData.setElementValue(ifds::Track, dstrTrack);
   requestData.setElementValue(ifds::Activity, dstrPageName);
   requestData.setElementValue(ifds::CalledByProc, dstrCallByProc);
   if( ReceiveData(DSTC_REQUEST::ACCSHRNUMCHECK, requestData, 
         *responseData, DSTCRequestor( getSecurity(), true) ) > WARNING )
      delete responseData;

   if( shrNumCtrl.upperCase() == I_( "M" ) )
   {
      DString strFound;
      responseData->getElementValue( ifds::DataFound, strFound);

      if( strFound == YES )
         ADDCONDITIONFROMFILE( CND::ERR_SHAREHOLDER_NUMBER_EXISTS );

   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccShrNumCheck::initAccNum(const DString& dstrAcctNum, const DString& dstrTrack,
                                    const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initAccNum" ) );   

   // checks if the input account num is valid
   DString tempAccountNum( dstrAcctNum );

   tempAccountNum.strip().stripLeading( '0' );

   BFData requestData(ifds::DSTC0120_REQ);
   BFData *responseData = new BFData(ifds::DSTC0120_VW);
   DString mgmtCoIdOut;

   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::ShrNum, NULL_STRING );
   requestData.setElementValue( ifds::AccountNum, tempAccountNum );      
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
   if (ReceiveData(DSTC_REQUEST::ACCSHRNUMCHECK, requestData, 
         *responseData, DSTCRequestor( getSecurity()) ) > WARNING)
      delete responseData;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccShrNumCheck::initShrNum(const DString& dstrShrtNum, const DString& dstrTrack,
                                    const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initAccNum" ) );   

   // checks if the input shareholder num is valid
   DString tempShrNum( dstrShrtNum );

   tempShrNum.strip().stripLeading( '0' );

   BFData requestData(ifds::DSTC0120_REQ);
   BFData *responseData = new BFData(ifds::DSTC0120_VW);
   DString mgmtCoIdOut;

   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::ShrNum, tempShrNum );
   requestData.setElementValue( ifds::AccountNum, NULL_STRING );      
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
   if( ReceiveData(DSTC_REQUEST::ACCSHRNUMCHECK, requestData, 
         *responseData, DSTCRequestor( getSecurity()) ) > WARNING )
      delete responseData;

   return(GETCURRENTHIGHESTSEVERITY());
}
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccShrNumCheck.cpp-arc  $
 * 
 *    Rev 1.15   Jan 27 2010 17:57:02   wutipong
 * IN1877040 -- More fix to remove hard-coding.
 * 
 *    Rev 1.14   Jan 22 2010 07:45:22   wutipong
 * IN1877040 - Phatak Anil - WAM ACCT - CLEARSTREAM ACCT (NEW ACCT TO OPEN)
 * 
 *    Rev 1.13   May 22 2003 14:11:48   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.12   Mar 21 2003 17:55:34   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:53:56   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:54:56   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:26:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   07 Feb 2002 17:29:48   KOVACSRO
 * Added a new init, initShrNum.
 * 
 *    Rev 1.7   13 Dec 2001 17:14:52   KOVACSRO
 * Added a new init, used only for AccountNum check.
 * 
 *    Rev 1.6   09 May 2001 11:46:34   HSUCHIN
 * Sync up with SSB
 * 
 *    Rev 1.4.1.1   May 02 2001 09:45:14   OLTEANCR
 * added init2(..)
 * 
 *    Rev 1.4.1.0   Apr 25 2001 14:13:50   OLTEANCR
 * Modif. init(...) 
 * 
 *    Rev 1.4   Jan 18 2001 16:03:26   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.3   Dec 17 2000 20:22:22   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.2   15 Nov 2000 15:30:14   SMITHDAV
 * Use new ReceiveData and do some cleanup.
 * 
 *    Rev 1.1   Oct 30 2000 14:05:08   YINGBAOL
 * change sync.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:48   SMITHDAV
 * Initial revision.
// 
//    Rev 1.1   Jan 21 2000 11:11:46   POPESCUS
// the user can change the account number and the shareholder number
// 
// 
*/