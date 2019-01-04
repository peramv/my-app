//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : AccrualsList.cpp
// ^AUTHOR : 
// ^DATE   : Jan 08, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AccrualsList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "accrualslist.hpp"
#include "accrualssearchcriteria.hpp"
#include <ifastdataimpl\dse_dstc0062_req.hpp>
#include <ifastdataimpl\dse_dstc0062_vw.hpp>
#include <ifastdataimpl\dse_dstc0199_req.hpp>
#include <ifastdataimpl\dse_dstc0199_vw.hpp>
//******************************************************************************
// MF - stands for Management Fee
//******************************************************************************

namespace CND
{
   extern const long ERR_START_DATE_USED;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AccrualSummary;
   extern CLASS_IMPORT const BFTextFieldId AccrualType;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFDateFieldId EndDate;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundType;
   extern CLASS_IMPORT const BFDateFieldId StartDate;
   extern CLASS_IMPORT const BFTextFieldId InclUnsettled;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INTEREST_ACCRUAL;
   extern CLASS_IMPORT const DSTCRequest MF_ACCRUAL;
}

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "AccrualsList" );
   const I_CHAR * const INTEREST_ACCRUAL        = I_( "01" );
   const I_CHAR * const INTEREST_ACCRUAL_CODE   = I_( "IA" );
   const I_CHAR * const MF_ACCRUAL              = I_( "02" );
   const I_CHAR * const MF_ACCRUAL_CODE         = I_( "MF" );
   const I_CHAR * const MF_REBATE_ACCRUAL       = I_( "03" );
   const I_CHAR * const MF_REBATE_ACCRUAL_CODE  = I_( "MR" );
   const I_CHAR * const SUMMARY                 = I_( "S" );
   const I_CHAR * const YES                     = I_( "Y" );
   const int PRECISION = 4;
}

//******************************************************************************
// Constructor
// @param   BFBase - pointer to the parent BFBase
//******************************************************************************

AccrualsList::AccrualsList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),  
_pRequestData ( 0 ),
_dstrAccrualType ( NULL_STRING ),
_dstrTotalEarned ( NULL_STRING ),
_dstrTotalPaid ( NULL_STRING ),
_dstrTotalAccumTotal ( NULL_STRING ),
_dstrTotalGSTPaid ( NULL_STRING ),
_dstrTotalGSTOutstanding ( NULL_STRING ),
_dstrTotalNRTaxPaid ( NULL_STRING ),
_dstrTotalNRTaxOutstanding ( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
// Destructor
//******************************************************************************

AccrualsList::~AccrualsList()
{
   if( _pRequestData )
      delete _pRequestData;
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Overloaded Function - Initalize CBO and executes view call
// @param   const DString& dstrAccountNumber - Account Number ( Required )
// @param   const DString& dstrFundCode - Fund Code ( Required )
// @param   const DString& dstrClassCode - Class Code ( Required )
// @param   const DString& dstrStartDate - Start Date ( Required )
// @param   const DString& dstrEndDate - End Date ( Required )
// @param   const DString& dstrInclUnsettled - Include Unsettled Trade is either
//                                             I_("Y") or I_("N") ( Required )
// @param   const DString& dstrSummary - Summary Information is either I_("Y") or 
//                                       I_("N") ( Required )
// @param   const DString& dstrType - Type of Accrual has the values INTEREST_ACCRUAL,
//                                    MF_ACCRUAL or MF_REBATE_ACCRUAL. ( Required )
// @param   const DString& dstrTrack - Tracking flag ( used by eAdvisor )
// @param   const DString& dstrPageName - Page Name value ( used by eAdvisor )
// @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//******************************************************************************


SEVERITY AccrualsList::init( const DString& dstrAccountNumber, 
                             const DString& dstrFundCode,
                             const DString& dstrClassCode, 
                             const DString& dstrStartDate, 
                             const DString& dstrEndDate, 
                             const DString& dstrInclUnsettled,
                             const DString& dstrSummary,
                             const DString& dstrType,
                             const DString& dstrTrack,
                             const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;

   if( dstrType == INTEREST_ACCRUAL )
   {
      _pRequestData = new BFData(ifds::DSTC0062_REQ);
      _pRequestData->setElementValue( ifds::AccrualType, INTEREST_ACCRUAL_CODE );
   }
   else if( dstrType == MF_ACCRUAL )
   {
      _pRequestData = new BFData(ifds::DSTC0199_REQ);
      _pRequestData->setElementValue( ifds::AccrualType, MF_ACCRUAL_CODE );
   }
   else if( dstrType == MF_REBATE_ACCRUAL )
   {
      _pRequestData = new BFData(ifds::DSTC0199_REQ);
      _pRequestData->setElementValue( ifds::AccrualType, MF_REBATE_ACCRUAL_CODE );
   }
   else
      return(SEVERE_ERROR);

   // Setup request data object.

   _pRequestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue( ifds::AccountNum,  dstrAccountNumber  );   
   _pRequestData->setElementValue( ifds::EndDate, dstrEndDate, false, false );
   _pRequestData->setElementValue( ifds::InclUnsettled, dstrInclUnsettled );
   if( dstrSummary == YES )
   {
      _pRequestData->setElementValue( ifds::StartDate, NULL_STRING, false, false );
      _pRequestData->setElementValue( ifds::FundCode, NULL_STRING );
      _pRequestData->setElementValue( ifds::ClassCode, NULL_STRING );
   }
   else
   {
      _pRequestData->setElementValue( ifds::FundCode, dstrFundCode );
      _pRequestData->setElementValue( ifds::ClassCode, dstrClassCode );
      _pRequestData->setElementValue( ifds::StartDate, dstrStartDate, false, false );
   }
   _pRequestData->setElementValue( ifds::Summary, dstrSummary );
   _pRequestData->setElementValue( ifds::Track, dstrTrack );
   _pRequestData->setElementValue( ifds::Activity, dstrPageName );
   _pRequestData->setElementValue( ifds::NextKey, NULL_STRING );

   // Store the Accural Type for getMore functionality.
   _dstrAccrualType = dstrType;                                 

   // Execute view call.
   SEVERITY sevRtn = NO_CONDITION;
   const BFDataGroupId& idDataGroup = BF::HOST;
   if( dstrType == INTEREST_ACCRUAL )
   {
      sevRtn = ReceiveData(DSTC_REQUEST::INTEREST_ACCRUAL, *_pRequestData, ifds::DSTC0062_VW, DSTCRequestor( getSecurity(), false) );
      if( sevRtn > WARNING )
         return(GETCURRENTHIGHESTSEVERITY());
      if( dstrSummary == I_("Y") )
      {
         BFObjIter iter ( *this, idDataGroup );
         iter.begin();
         DString dstrTemp;
         double lTotalIntValue, lTotalIntPaid, lTotalAccumTotal;
         lTotalIntValue = lTotalIntPaid = lTotalAccumTotal = 0;
         while( !iter.end() )
         {
            iter.getObject()->getField ( ifds::IntValue, dstrTemp, idDataGroup );
            lTotalIntValue += DSTCommonFunctions::convertToDouble ( dstrTemp );
            iter.getObject()->getField ( ifds::IntPaid, dstrTemp, idDataGroup );
            lTotalIntPaid  += DSTCommonFunctions::convertToDouble ( dstrTemp );
            iter.getObject()->getField ( ifds::AccumTotal, dstrTemp, idDataGroup );
            lTotalAccumTotal += DSTCommonFunctions::convertToDouble ( dstrTemp );
            ++iter;
         }
         _dstrTotalEarned = DSTCommonFunctions::doubleToDString ( ifds::Amount, lTotalIntValue );
         _dstrTotalPaid = DSTCommonFunctions::doubleToDString ( ifds::Amount, lTotalIntPaid );
         _dstrTotalAccumTotal = DSTCommonFunctions::doubleToDString ( ifds::Amount, lTotalAccumTotal );         
         _dstrAsofDate = NULL_STRING;
         _dstrAsofDateFormatted = NULL_STRING;
      }
      else
      {
         BFObjIter iter ( *this, idDataGroup );
         iter.begin();
         DString dstrRecType;
         while( !iter.end() )
         {
            iter.getObject()->getField ( ifds::RecType, dstrRecType, idDataGroup );
            if( dstrRecType == SUMMARY )
               break;
            else
               ++iter;
         }
         iter.getObject()->getField ( ifds::IntValue, _dstrTotalEarned, idDataGroup, true );         
         DSTCommonFunctions::formattedField ( ifds::IntValue, PRECISION,_dstrTotalEarned );
         iter.getObject()->getField ( ifds::IntPaid, _dstrTotalPaid, idDataGroup, true );
         DSTCommonFunctions::formattedField ( ifds::IntPaid, PRECISION,_dstrTotalPaid );
         iter.getObject()->getField ( ifds::AccumTotal, _dstrTotalAccumTotal, idDataGroup, true );
         DSTCommonFunctions::formattedField ( ifds::AccumTotal, PRECISION,_dstrTotalAccumTotal );
         iter.getObject()->getField ( ifds::AsofDate, _dstrAsofDate, idDataGroup );
         iter.getObject()->getField ( ifds::AsofDate, _dstrAsofDateFormatted, idDataGroup, true );
      }
   }
   else if( dstrType == MF_ACCRUAL || dstrType == MF_REBATE_ACCRUAL )
   {
      sevRtn = ReceiveData(DSTC_REQUEST::MF_ACCRUAL, *_pRequestData, ifds::DSTC0199_VW, DSTCRequestor( getSecurity(), false) );
      if( sevRtn > WARNING )
         return(GETCURRENTHIGHESTSEVERITY());
      if( dstrSummary == I_( "Y" ) )
      {
         BFObjIter iter ( *this, idDataGroup );
         iter.begin();
         DString dstrTemp;
         double lTotalAmount, lTotalAmtPaid, lTotalAccumTotal, lTotalGSTPaid;
         double lTotalGSTOutstanding, lTotalNRPaid, lTotalNROutstanding;
         lTotalAmount = lTotalAmtPaid = lTotalAccumTotal = lTotalGSTPaid = 0;
         lTotalGSTOutstanding =  lTotalNRPaid = lTotalNROutstanding = 0;

         while( !iter.end() )
         {
            iter.getObject()->getField ( ifds::Amount, dstrTemp, idDataGroup );
            lTotalAmount += DSTCommonFunctions::convertToDouble ( dstrTemp );
            iter.getObject()->getField ( ifds::AmtPaid, dstrTemp, idDataGroup );
            lTotalAmtPaid  += DSTCommonFunctions::convertToDouble ( dstrTemp );
            iter.getObject()->getField ( ifds::AccumTotal, dstrTemp, idDataGroup );
            lTotalAccumTotal += DSTCommonFunctions::convertToDouble ( dstrTemp );
            iter.getObject()->getField ( ifds::GSTPaid, dstrTemp, idDataGroup );
            lTotalGSTPaid += DSTCommonFunctions::convertToDouble ( dstrTemp );
            iter.getObject()->getField ( ifds::GSTOutstanding, dstrTemp, idDataGroup );
            lTotalGSTOutstanding  += DSTCommonFunctions::convertToDouble ( dstrTemp );
            iter.getObject()->getField ( ifds::NRPaid, dstrTemp, idDataGroup );
            lTotalNRPaid += DSTCommonFunctions::convertToDouble ( dstrTemp );
            iter.getObject()->getField ( ifds::NROutstanding, dstrTemp, idDataGroup );
            lTotalNROutstanding += DSTCommonFunctions::convertToDouble ( dstrTemp );
            ++iter;
         }
         _dstrTotalEarned = DSTCommonFunctions::doubleToDString ( ifds::Amount, lTotalAmount );
         _dstrTotalPaid = DSTCommonFunctions::doubleToDString ( ifds::Amount, lTotalAmtPaid );
         _dstrTotalAccumTotal = DSTCommonFunctions::doubleToDString ( ifds::Amount, lTotalAccumTotal );
         _dstrTotalGSTPaid = DSTCommonFunctions::doubleToDString ( ifds::Amount, lTotalGSTPaid );
         _dstrTotalGSTOutstanding = DSTCommonFunctions::doubleToDString ( ifds::Amount, lTotalGSTOutstanding );
         _dstrTotalNRTaxPaid = DSTCommonFunctions::doubleToDString ( ifds::Amount, lTotalNRPaid );
         _dstrTotalNRTaxOutstanding = DSTCommonFunctions::doubleToDString ( ifds::Amount, lTotalNROutstanding );
         _dstrAsofDate = NULL_STRING;
         _dstrAsofDateFormatted = NULL_STRING;
      }
      else
      {
         BFObjIter iter ( *this, idDataGroup );
         iter.begin();
         DString dstrRecType;
         while( !iter.end() )
         {
            iter.getObject()->getField ( ifds::RecType, dstrRecType, idDataGroup );
            if( dstrRecType == SUMMARY )
               break;
            else
               ++iter;
         }
         iter.getObject()->getField ( ifds::Amount, _dstrTotalEarned, idDataGroup );
         iter.getObject()->getField ( ifds::AmtPaid, _dstrTotalPaid, idDataGroup );
         iter.getObject()->getField ( ifds::AccumTotal, _dstrTotalAccumTotal, idDataGroup );
         iter.getObject()->getField ( ifds::GSTPaid, _dstrTotalGSTPaid, idDataGroup );
         iter.getObject()->getField ( ifds::GSTOutstanding, _dstrTotalGSTOutstanding, idDataGroup );
         iter.getObject()->getField ( ifds::NRPaid, _dstrTotalNRTaxPaid, idDataGroup );
         iter.getObject()->getField ( ifds::NROutstanding, _dstrTotalNRTaxOutstanding, idDataGroup );
         iter.getObject()->getField ( ifds::AsofDate, _dstrAsofDate, idDataGroup );
         iter.getObject()->getField ( ifds::AsofDate, _dstrAsofDateFormatted, idDataGroup, true );
      }
   }
   DString dstrTemp;
   if( (_dstrAsofDate != NULL_STRING) && ( DSTCommonFunctions::CompareDates ( _dstrAsofDate, dstrStartDate ) != DSTCommonFunctions::EQUAL ) )
   {
      DString error = I_( "" );      
      dstrTemp = _dstrAsofDateFormatted;      
      addIDITagValue( error, I_("DATE"), dstrTemp );
      ADDCONDITIONFROMFILEIDI( CND::ERR_START_DATE_USED, error );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Overloaded Function - Inits CBO and executes view call
// @param   AccrualsSearchCriteria *pAccrualsSearchCriteria - pointer to AccrualsSearchCriteria CBO
//                               containing information such as Accrual Type.
// @param   const BFDataGroupId& idDataGroup - Data Group.
// @param   const DString& dstrTrack - Tracking flag ( used by eAdvisor )
// @param   const DString& dstrPageName - Page Name value ( used by eAdvisor )
// @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//******************************************************************************

SEVERITY AccrualsList::init( const AccrualsSearchCriteria *pAccrualsSearchCriteria, 
                             const BFDataGroupId& idDataGroup, const DString& dstrTrack, const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   // Extract the search criteria information and call overloaded function init.

   SEVERITY sev = NO_CONDITION;
   DString dstrAccountNum, dstrAccrualType, dstrStartDate, dstrEndDate, dstrInclUnsettled, dstrFundCode, dstrClassCode, dstrSummary;
   pAccrualsSearchCriteria->getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );
   pAccrualsSearchCriteria->getField ( ifds::AccrualType, dstrAccrualType, idDataGroup );
   pAccrualsSearchCriteria->getField ( ifds::StartDate, dstrStartDate, idDataGroup );   
   pAccrualsSearchCriteria->getField ( ifds::EndDate, dstrEndDate, idDataGroup );   
   pAccrualsSearchCriteria->getField ( ifds::InclUnsettled, dstrInclUnsettled, idDataGroup );   
   pAccrualsSearchCriteria->getField ( ifds::FundCode, dstrFundCode, idDataGroup );   
   pAccrualsSearchCriteria->getField ( ifds::ClassCode, dstrClassCode, idDataGroup );   
   pAccrualsSearchCriteria->getField ( ifds::AccrualSummary, dstrSummary, idDataGroup );   

   return(init ( dstrAccountNum, dstrFundCode, dstrClassCode, dstrStartDate, dstrEndDate, dstrInclUnsettled, 
                 dstrSummary, dstrAccrualType, dstrTrack, dstrPageName ));
}

//******************************************************************************
// getMore retrieves more data for the current search criteria
// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//                    SEVERE_ERROR if the accural type is not defined to be
//                    INTEREST_ACCRUAL/MF_ACCRUAL/MF_REBATE_ACCRUAL
//******************************************************************************

SEVERITY AccrualsList::getMore( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   // Determine the type of accrual and issue view call for more data.

   if( _dstrAccrualType == INTEREST_ACCRUAL )
      ReceiveData(DSTC_REQUEST::INTEREST_ACCRUAL, *_pRequestData, ifds::DSTC0062_VW, DSTCRequestor( getSecurity(), false) );
   else if( _dstrAccrualType == MF_ACCRUAL || _dstrAccrualType == MF_REBATE_ACCRUAL )
   {
      DString dstrRunTotal;
      getField ( ifds::RunTotal, dstrRunTotal, BF::HOST, false );
      _pRequestData->setElementValue( ifds::RunTotal, dstrRunTotal );
      ReceiveData(DSTC_REQUEST::MF_ACCRUAL, *_pRequestData, ifds::DSTC0199_VW, DSTCRequestor( getSecurity(), false) );
   }
   else
      return(SEVERE_ERROR);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccrualsList.cpp-arc  $
// 
//    Rev 1.11   Mar 21 2003 17:55:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.10   Nov 29 2002 15:40:22   ZHANGCEL
// Synced up to 1.9
// 
//    Rev 1.9   Oct 09 2002 23:53:54   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Sep 24 2002 16:40:38   HSUCHIN
// sync up with 1.6.1.0
// 
//    Rev 1.7   Aug 29 2002 12:54:56   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   Jul 17 2002 13:44:10   HSUCHIN
// bug fix - DSTCommonFunction::formatToolTipDate is no longer use since getMask fails. 
// 
//    Rev 1.5   05 Jun 2002 14:05:24   SMITHDAV
// Change occurances of
// DSTCommonFunctions::DATE_ORDER::EQUAL
// to DSTCommonFunctions::EQUAL.
// 
//    Rev 1.4   22 May 2002 22:23:16   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   16 Apr 2002 14:49:30   HSUCHIN
// changed impl to calculate totals
// 
//    Rev 1.2   12 Mar 2002 10:27:18   HSUCHIN
// fix data for summary request
// 
//    Rev 1.1   26 Feb 2002 16:54:08   HSUCHIN
// datadictionary sync up
// 
//    Rev 1.0   21 Feb 2002 16:07:00   HSUCHIN
// Initial revision.
*/
