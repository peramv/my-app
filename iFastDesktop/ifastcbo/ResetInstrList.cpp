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
//    Copyright 2003 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : ResetInstrList.cpp
// ^AUTHOR : 
// ^DATE   : Jan 15, 2003
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ResetInstrList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "mfaccount.hpp"
#include "mgmtcooptions.hpp"
#include "resetinstr.hpp"
#include "resetinstrlist.hpp"
#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>
#include <ifastdataimpl\dse_dstc0243_req.hpp>
#include <ifastdataimpl\dse_dstc0243_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ResetInstrList" );
   const I_CHAR * const CLIENT_REQ_RESET = I_("01");
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace CND
{
   extern const long ERR_DUP_RESET_INSTR;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESET_INSTR_LIST;
   extern CLASS_IMPORT const DSTCRequest ACTIVE_BATCH;
	
}

//*****************************************************************************
// Constructor
//*****************************************************************************

ResetInstrList::ResetInstrList( BFAbstractCBO &parent )
: _dstrAccountNum (NULL_STRING),
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   setObjectAsList( );
}

//*****************************************************************************
// Destructor
//*****************************************************************************

ResetInstrList::~ResetInstrList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY ResetInstrList::init(const BFDataGroupId& idDataGroup/*=BF::HOST*/, 
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   //just to be used by the DSTCWorksession template method, getObject_X
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY ResetInstrList::init ( const DString& dstrAccountNum, 
                       const DString& dstrResetDate,                       
                       const DString& dstrTrack,
                       const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   
   DString mgmtCoIdOut,dstrCurrBusDate;   
   //Hard code current business date for now.
   _dstrAccountNum = dstrAccountNum;   
   _pRequestData = new BFData(ifds::DSTC0243_REQ);
   if( _pRequestData )
   {
      _pRequestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      _pRequestData->setElementValue( ifds::AccountNum, dstrAccountNum );   
      /*if ( dstrResetDate == NULL_STRING ) {
         getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, BF::HOST, false );     
         _pRequestData->setElementValue( ifds::AsofDate, dstrCurrBusDate );      
      } else {
         _pRequestData->setElementValue( ifds::AsofDate, dstrResetDate );         
      }*/
      //_pRequestData->setElementValue( ifds::ExactMatch, I_("N") );
      _pRequestData->setElementValue( ifds::ResetDate, dstrResetDate );         
      _pRequestData->setElementValue( ifds::Track, dstrTrack );
      _pRequestData->setElementValue( ifds::Activity, dstrPageName );
      _pRequestData->setElementValue( ifds::NextKey, NULL_STRING );

      // Execute view call.
      SEVERITY sevRtn = NO_CONDITION;
      sevRtn = ReceiveData(DSTC_REQUEST::RESET_INSTR_LIST, *_pRequestData, ifds::DSTC0243_VW, 
         DSTCRequestor( getSecurity(), true) );
   }     
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
//*****************************************************************************
SEVERITY ResetInstrList::init ( const BFFieldId& idField, 
                       const DString& dstrValue,                       
                       const DString& dstrTrack,
                       const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init2" ) );
   if ( idField == ifds::AccountNum ) {
      init ( dstrValue, NULL_STRING, dstrTrack, dstrPageName );
   } else if ( idField == ifds::ResetDate ) {
      init ( NULL_STRING, dstrValue, dstrTrack, dstrPageName );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
//*****************************************************************************
SEVERITY ResetInstrList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   ResetInstr * pResetInstr = new ResetInstr( *this );
   pResetInstr->init( data );
   pObjOut = pResetInstr;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ResetInstrList::doCreateNewObject( BFCBO*& pBase, DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   ResetInstr* pResetInstr = new ResetInstr ( *this );   
	pResetInstr->init (idDataGroup);
   pBase = pResetInstr;

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
// getMore retrieves more data.
// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//******************************************************************************

SEVERITY ResetInstrList::getMore( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );
   
   ReceiveData(DSTC_REQUEST::RESET_INSTR_LIST, *_pRequestData, ifds::DSTC0243_VW, DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//******************************************************************************
void ResetInstrList::Reversal( const DString& oriKey, const DString& destKey, const BFDataGroupId& idDataGroup )
{
   ResetInstr* pOriResetInstr = NULL;
   ResetInstr* pDestResetInstr = NULL;

   for( BFObjIter Iter( *this, idDataGroup ); !Iter.end(); ++Iter )
   {
      if( Iter.getStringKey() == oriKey )
      {
         pOriResetInstr = dynamic_cast< ResetInstr * >( Iter.getObject( ) );
      }
      else if( Iter.getStringKey() == destKey )
      {
         pDestResetInstr = dynamic_cast< ResetInstr * >( Iter.getObject( ) );
      }
   }

   assert ( pOriResetInstr && pDestResetInstr );

   pDestResetInstr->Reversal(pOriResetInstr, idDataGroup);
}

//******************************************************************************
//******************************************************************************
int ResetInstrList::getNumOfReset( const DString& dstrFundCode, const DString& dstrClassCode, 
                                  const DString& dstrAccountNum, 
                                  const DString& dstrDate,
                                  const BFDataGroupId& idDataGroup )
{
   DString dstrFundCode2, dstrClassCode2, dstrAccountNum2, dstrResetType2,dstrDate2;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   std::set < DString > cancelReset;
   DString cancelID,resetID;   
 
   while( !iter.end() ) // find all reset that has been cancelled, and save it in the cancelReset
   {
      iter.getObject()->getField(ifds::CanResetId,cancelID,idDataGroup );
      cancelID.strip().stripLeading('0');
      if( cancelID != NULL_STRING )
      {
         cancelReset.insert( cancelID );
      }
      ++iter;
   }
   int numResets = 0;
   ResetInstr* pResetInstr;
   iter.begin();
   while ( !iter.end() )
   {
      pResetInstr = dynamic_cast <ResetInstr*> (iter.getObject());
      if( pResetInstr )
      {
         pResetInstr->getField ( ifds::ResetID, resetID, idDataGroup );
         pResetInstr->getField ( ifds::CanResetId, cancelID, idDataGroup );
         resetID.strip().stripLeading('0');
         cancelID.strip().stripLeading('0');
         if( cancelID != NULL_STRING ) // this is a cancel reset
         {
            ++iter;
            continue;
         }
         if( cancelReset.find( resetID ) != cancelReset.end() ) // the original reset has been cancelled
         {
            ++iter;
            continue;
         }         
         pResetInstr->getField ( ifds::FundCode, dstrFundCode2, idDataGroup );
         pResetInstr->getField ( ifds::ClassCode, dstrClassCode2, idDataGroup );
         pResetInstr->getField ( ifds::AccountNum, dstrAccountNum2, idDataGroup );
         pResetInstr->getField ( ifds::ResetType, dstrResetType2, idDataGroup );
         pResetInstr->getField ( ifds::ResetDate, dstrDate2, idDataGroup,false );
         dstrFundCode2.strip().upperCase();
			dstrClassCode2.strip().upperCase();
         dstrAccountNum2.strip();
         dstrDate2.strip();
         int iYr = DSTCommonFunctions::compareDateYear(dstrDate,dstrDate2 );
         if ( ( dstrFundCode == dstrFundCode2 ) && ( dstrClassCode == dstrClassCode2 ) 
            && ( dstrAccountNum == dstrAccountNum2 )&& ( dstrResetType2 == CLIENT_REQ_RESET ) &&
            iYr == 1 // only count for the same year
            )
         {
            ++numResets;
         }
      } 
      ++iter;
   }
   return numResets;
}

//******************************************************************************
//******************************************************************************

SEVERITY ResetInstrList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   std::set < DString > dupResetInstr;
   std::set < DString > cancelReset;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString cancelID,resetID;   
   while( !iter.end() ) // find all reset that has been cancelled, and save it in the cancelReset
   {
      iter.getObject()->getField(ifds::CanResetId,cancelID,idDataGroup );
      cancelID.strip().stripLeading('0');
      if( cancelID != NULL_STRING )
      {
         cancelReset.insert( cancelID );
      }
      ++iter;
   }
   DString dstr, dstrAccountNum, dstrFundCode, dstrClassCode, dstrResetType, dstrResetDate; 
   iter.begin();
   while( !iter.end() )
   {        
      bool bAdd =  false;
      BFAbstractCBO* cbo = iter.getObject(); // to speed up
      if( cbo )
      {
         cbo->getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );
         cbo->getField ( ifds::FundCode, dstrFundCode, idDataGroup );
         cbo->getField ( ifds::ClassCode, dstrClassCode, idDataGroup );
         cbo->getField ( ifds::ResetType, dstrResetType, idDataGroup );
         cbo->getField ( ifds::ResetDate, dstrResetDate, idDataGroup );
         cbo->getField ( ifds::ResetID, resetID, idDataGroup );
         cbo->getField ( ifds::CanResetId, cancelID, idDataGroup );
         resetID.strip().stripLeading('0');
         cancelID.strip().stripLeading('0');
         if( cancelID == NULL_STRING ) // this is the original reset
         {
            if( cancelReset.find( resetID ) == cancelReset.end() )
            {
               bAdd =  true;
            }         
         }
         if( bAdd )
         {  // now it is the reset which has not been canceled         
            dstr = dstrAccountNum.strip()+dstrFundCode.strip()+dstrClassCode.strip()/*+dstrResetType.strip()*/+dstrResetDate.strip();
            if ( !dupResetInstr.insert ( dstr ).second ) 
            {
               //Duplicate Reset Instruction.
               ADDCONDITIONFROMFILE ( CND::ERR_DUP_RESET_INSTR );
               return GETCURRENTHIGHESTSEVERITY();
             }
         }
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ResetInstrList::canDeleteObject( const DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canDeleteObject" ) );   

   DString mgmtCoIdOut;
   BFData request(ifds::DSTC0124_REQ);
   BFData response(ifds::DSTC0124_VW);
   const DSTCSecurity* pSecurity =  dynamic_cast<const DSTCSecurity *>(getSecurity());
   request.setElementValue( ifds::Track, I_("N") );
   request.setElementValue( ifds::Activity, NULL_STRING );   
   request.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );  

	return ( BFDataBroker::getInstance()->receive( DSTC_REQUEST::ACTIVE_BATCH, request, response, DSTCRequestor(getSecurity()) ) <= WARNING ) ;

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ResetInstrList.cpp-arc  $
// 
//    Rev 1.15   Aug 10 2005 10:54:24   AGUILAAM
// IN 376007 - modify fix, same functionality.
// 
//    Rev 1.14   Aug 09 2005 17:19:02   AGUILAAM
// IN 376007 - should not allow delete of reset when user has no active batch
// 
//    Rev 1.13   Aug 02 2005 16:39:22   AGUILAAM
// IN 329838 : call getBatchInfo within (new) init procedure only; 'no active batch' error from getBatchInfo when called from  doInitWithDefaultValues was causing Desktop to crash.
// 
//    Rev 1.12   Apr 05 2005 15:52:22   yingbaol
// Incident 243363: fix 2 issues, 1) wrong duplicate check; 2) wrong max reset instruction check.
// 
//    Rev 1.11   Nov 14 2004 14:52:18   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Jul 29 2003 10:30:24   HERNANDO
// PTS 10016740 - Removed reset type from duplicate check.
// 
//    Rev 1.9   May 28 2003 10:52:18   popescu
// Part of the cleaning of DSTCWorksession, not finalized yet, more to come....
// 
//    Rev 1.8   May 13 2003 08:41:50   sanchez
// Sync. up with v.1.6.1.0 PTS#10016796
// 
//    Rev 1.7   Mar 21 2003 18:21:56   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Feb 06 2003 15:05:46   HSUCHIN
// added 2 methods getNumOfReset to get the number of resets for the fund/class passed in and doValidateAll to check for duplicate resets.
// 
//    Rev 1.5   Feb 04 2003 11:45:54   HSUCHIN
// removed exactmatch field
// 
//    Rev 1.4   Jan 29 2003 16:25:40   HSUCHIN
// hardcoded Exact match for now
// 
//    Rev 1.3   Jan 27 2003 07:43:28   HSUCHIN
// added reversal support and method to get current accountnum
// 
//    Rev 1.2   Jan 26 2003 16:04:46   HSUCHIN
// hardcode cur bus date to request for now
// 
//    Rev 1.1   Jan 25 2003 17:36:32   HSUCHIN
// more enhancements
// 
//    Rev 1.0   Jan 24 2003 10:19:36   HSUCHIN
// Initial Revision
*/
