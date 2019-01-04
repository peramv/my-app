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
//    Copyright 2000 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : RRIF_LIF_LRIF_InfoList.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : Feb 07, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RRIF_LIF_LRIF_InfoList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "rrif_lif_lrif_infolist.hpp"
#include "rrif_lif_lrif_info.hpp"
#include "accountentityxref.hpp"
#include "fromfundalloclist.hpp"
#include "shareholder.hpp"
#include "taxtyperule.hpp"
#include "taxtyperulelist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0067_vw.hpp>
#include <ifastdataimpl\dse_dstc0067_req.hpp>
#include <ifastdataimpl\dse_dstc0068_vw.hpp>
#include <ifastdataimpl\dse_dstc0068_req.hpp>
#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RRIF_LIF_LRIF_INFO;
   extern CLASS_IMPORT const DSTCRequest RRIF_LIF_LRIF_ALLOC;
   extern CLASS_IMPORT const DSTCRequest ACTIVE_BATCH;
}
namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RRIF_LIF_LRIF_InfoList" );

   // Other literals
   const I_CHAR * const MORE_AVAILABLE = I_( "MoreAvailable" );
   const I_CHAR * const NEXT_KEY = I_( "NextKey" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const RIF_ID_FIELD = I_( "RIFId" );
   const I_CHAR * const STATUS = I_("GoodBad");
   const I_CHAR * const RRIF_AWD = I_( "RIF_AWD" );   // RRIF,LIF,LRIF AWD


}

namespace TRID
{
   extern const I_CHAR *RRIF_LIF_LRIF_INFO;
   extern const I_CHAR *RRIF_LIF_LRIF_ALLOC;
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_NO_RIF_ALLOCATION_INFO;
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_NO_RIF_SETUP_INFO;
   extern const long ERR_RRIF_EXIST_IN_SAME_YEAR;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId TitleRestrict;
   extern CLASS_IMPORT const BFTextFieldId isRRIFOverrUnusedAmtApplic;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeSchedule;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_FIELD_INFO;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//    Field DD Id,            State Flags,   Group Flags 
   { ifds::AccountNum,                 BFCBO::NONE, 0 },
   { ifds::isRRIFOverrUnusedAmtApplic, BFCBO::NONE, 0 },
   
};

//******************************************************************************

static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );
//******************************************************************************

RRIF_LIF_LRIF_InfoList::RRIF_LIF_LRIF_InfoList( BFAbstractCBO &parent ) 
:  MFCanBFCbo( parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList(); //this is a list; yingbao
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);

   _dstrBatchTrace = NULL_STRING;
   _dstrBatchName = NULL_STRING;
   _dstrEffectiveDate = NULL_STRING;
   //_pRecvDataRRIF_LIF_LRIF_Alloc = NULL;
   _pRecvDataRRIF_LIF_LRIF_Info = NULL;
   _pRequestDataRRIF_INFO =  new BFData( ifds::DSTC0067_REQ);
   //_pRequestDataRRIF_Alloc =  new BFData( ifds::DSTC0068_REQ);


}

//******************************************************************************

RRIF_LIF_LRIF_InfoList::~RRIF_LIF_LRIF_InfoList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( _pRequestDataRRIF_INFO )
   {
      delete _pRequestDataRRIF_INFO; _pRequestDataRRIF_INFO = NULL;
   }
   //if(_pRequestDataRRIF_Alloc){delete _pRequestDataRRIF_Alloc; _pRequestDataRRIF_Alloc = NULL;}

}

//******************************************************************************

SEVERITY RRIF_LIF_LRIF_InfoList::init( const DString& dstrAccountNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   _strAccountNum = dstrAccountNum;
   setOverrideUnusedAmtApplicable( BF::HOST );

   EnquiryDataFromHost( true );

   setFieldNoValidate( ifds::AccountNum, dstrAccountNum, BF::HOST );
   
   clearUpdatedFlags( BF::HOST );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_InfoList::EnquiryDataFromHost( bool bFirst, 
                                                      const DString& dstrTrack,
                                                      const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   // 1. Retrieving RRIF/LIF/LRIF allocations - obsolete
   if( bFirst )
   {
      DString mgmtCoIdOut;
      _pRequestDataRRIF_INFO->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      //_pRequestDataRRIF_Alloc->setElementValue( ifds::CompanyId, mgmtCoIdOut );
      //_pRequestDataRRIF_Alloc->setElementValue( ifds::AccountNum, _strAccountNum);
      _pRequestDataRRIF_INFO->setElementValue( ifds::AccountNum, _strAccountNum);
      _pRequestDataRRIF_INFO->setElementValue( ifds::NextKey,NULL_STRING );
      //_pRequestDataRRIF_Alloc->setElementValue( ifds::NextKey,NULL_STRING );

      _pRequestDataRRIF_INFO->setElementValue( ifds::Track, dstrTrack );
      _pRequestDataRRIF_INFO->setElementValue( ifds::Activity, dstrPageName );
      //_pRequestDataRRIF_Alloc->setElementValue( ifds::Track, dstrTrack );
      //_pRequestDataRRIF_Alloc->setElementValue( ifds::Activity, dstrPageName );

   }
   //_pRecvDataRRIF_LIF_LRIF_Alloc =	new BFData(ifds::DSTC0068_VW);
/*
   SEVERITY sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::RRIF_LIF_LRIF_ALLOC, 
                                                            *_pRequestDataRRIF_Alloc, 
                                                            *_pRecvDataRRIF_LIF_LRIF_Alloc, 
                                                            DSTCRequestor( getSecurity(), false ),
                                                            &_moreRecordsAvailable );  	

   if( sevRtn > WARNING ) 
   {
      int count = CONDITIONCOUNT();
      Condition   *c = NULL;
      for( int i = 0; i < count; i++ )
      {
         c = GETCONDITION( i );
         int condCode = c->getCode();
         if( condCode == CND::ERR_NO_RIF_ALLOCATION_INFO )
         {
            CLEARCONDITION( i )
            break;
         }
      }
      sevRtn = GETCURRENTHIGHESTSEVERITY();
   }

   if( sevRtn > WARNING )
   {
      delete _pRecvDataRRIF_LIF_LRIF_Alloc;
      _pRecvDataRRIF_LIF_LRIF_Alloc = NULL;
      return sevRtn;
   }
*/
   // 2. Retrieving RRIF/LIF/LRIF info
   BFData* _pRecvDataRRIF_LIF_LRIF_Info = new BFData(ifds::DSTC0067_VW);
   SEVERITY sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::RRIF_LIF_LRIF_INFO, 
                                                            *_pRequestDataRRIF_INFO, 
                                                            *_pRecvDataRRIF_LIF_LRIF_Info, 
                                                            DSTCRequestor( getSecurity(), false),
																				&_moreRecordsAvailable);


   if( sevRtn > WARNING )
   {
      int count = CONDITIONCOUNT();
      Condition   *c = NULL;
      for( int i = 0; i < count; i++ )
      {
         c = GETCONDITION( i );
         int condCode = c->getCode();
         if( condCode == CND::ERR_NO_RIF_SETUP_INFO )
         {
            CLEARCONDITION( i )
            break;
         }
      }
   }

   sevRtn = GETCURRENTHIGHESTSEVERITY( );
   if( sevRtn > WARNING )
   {
      delete _pRecvDataRRIF_LIF_LRIF_Info;
      _pRecvDataRRIF_LIF_LRIF_Info = NULL;
      return(sevRtn);
   }


	DString dstrNextKey = _pRequestDataRRIF_INFO->getElementValue(ifds::NextKey);
   attachDataObject( *_pRecvDataRRIF_LIF_LRIF_Info, true, true );
   createObjectForEachRepeat( *_pRecvDataRRIF_LIF_LRIF_Info );
   return(GETCURRENTHIGHESTSEVERITY()); 
}


//******************************************************************************

SEVERITY RRIF_LIF_LRIF_InfoList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   setOverrideUnusedAmtApplicable( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY RRIF_LIF_LRIF_InfoList::search( bool bFirstRetrieve )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "search" ) );

   assert( !bFirstRetrieve );//currently bFirstRetrieve==true is not supported 
   if( bFirstRetrieve )
   {
      eraseDataObjectContainers();
      eraseObjectContainer();
   }

   return(EnquiryDataFromHost(false ));

}

//******************************************************************************
/*
void RRIF_LIF_LRIF_InfoList::getStrKey ( DString &dstrKey, const Data *data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );
   DString status, strkey1;
   if( data ){
      strkey1 = data->getElementValue( RIF_ID_FIELD ).strip();
      status = data->getElementValue( STATUS ).strip();
      dstrKey = status == I_("Y")?I_("AAA"):I_("BBB"); 
      dstrKey += strkey1;
   }	
   else
      BFBase::getStrKey( dstrKey, NULL );
}
*/
//******************************************************************************

SEVERITY RRIF_LIF_LRIF_InfoList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   DString dstrKey;
   getStrKey( dstrKey, &data );
   RRIF_LIF_LRIF_Info *pRRIF_LIF_LRIF_Info = new RRIF_LIF_LRIF_Info( *this );
   pRRIF_LIF_LRIF_Info->setInitExistingFlag(true);
   pRRIF_LIF_LRIF_Info->init( const_cast< BFData & >( data ) );
   pRRIF_LIF_LRIF_Info->setInitExistingFlag(false);
   pObjOut = pRRIF_LIF_LRIF_Info;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY RRIF_LIF_LRIF_InfoList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   RRIF_LIF_LRIF_Info *pRRIF_LIF_LRIF_Info = new RRIF_LIF_LRIF_Info( *this );
   pRRIF_LIF_LRIF_Info->init( idDataGroup );

   pBase = pRRIF_LIF_LRIF_Info;

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
//getBachParam
// implemented by Yingbao
void RRIF_LIF_LRIF_InfoList::getBachParam(DString& strBachTrace,DString& strBatchName,DString& dstrEffectDate)
{
   SEVERITY sevRtn = setBatchParam();  

   if( sevRtn > WARNING )
      return;  // Add copy is not allowed if active batch is not available

   strBachTrace = _dstrBatchTrace;
   strBatchName = _dstrBatchName;
   dstrEffectDate = _dstrEffectiveDate;
}

//**********************************************************************************************
//setBatchParam
// implemented by Yingbao
SEVERITY RRIF_LIF_LRIF_InfoList::setBatchParam()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setBatchParam" ) );

   if( _dstrBatchName != NULL_STRING )
   {
      return(NO_CONDITION); // i.e. active batch name has been retrieve, no need to make view call
   }

   BFData requestData(ifds::DSTC0124_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::BatchTrace, _dstrBatchTrace );
   requestData.setElementValue( ifds::rxBatchName, _dstrBatchName );
   requestData.setElementValue( ifds::EffectiveDate, _dstrEffectiveDate, true, false );

   BFData responseData(ifds::DSTC0124_VW);

   SEVERITY sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::ACTIVE_BATCH, 
                                                            requestData, 
                                                            responseData, 
                                                            DSTCRequestor( getSecurity(), true) );

   if( sevRtn <= WARNING )
   {
      responseData.getElementValue( ifds::BatchTrace, _dstrBatchTrace );
      responseData.getElementValue( ifds::rxBatchName, _dstrBatchName );
      responseData.getElementValue( ifds::EffectiveDate, _dstrEffectiveDate );       
   };

   return(sevRtn);
}

//***********************************************************************
//doValidateAll  yingbao
// we check RRIF_LIF_LRIF_Info Sattus if is good, it should have a valid allocationList 
//  
SEVERITY RRIF_LIF_LRIF_InfoList:: doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   BFObjIter iter2( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   
   bool bHasAllocations = false;

   while (!iter2.end())
   {
      RRIF_LIF_LRIF_Info* pRRIF_LIF_LRIF_Info = dynamic_cast<RRIF_LIF_LRIF_Info* >(iter2.getObject());
      if (pRRIF_LIF_LRIF_Info)
      {
         FromFundAllocList  *pFromFundAllocList = NULL;

         bHasAllocations = pRRIF_LIF_LRIF_Info->getFromFundAllocList(pFromFundAllocList, idDataGroup, false) <= WARNING && 
                           pFromFundAllocList;
         if (bHasAllocations)
         {
            BFObjIter iter3( *pFromFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
            
            bHasAllocations = iter3.getNumberOfItemsInList () > 0;
            break;
         }
      }
      ++iter2; 
   }
   
   BFObjIter iter1( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   if( iter1.isDummy() && !bHasAllocations) return(NO_CONDITION);
   if (iter1.isDummy() && bHasAllocations) iter1.getObject() ->setNonDummyFlag ();
   while( !iter1.end() )
   {
      RRIF_LIF_LRIF_Info* pRRIF_LIF_LRIF_Info = dynamic_cast<RRIF_LIF_LRIF_Info* >(iter1.getObject() );
      if( pRRIF_LIF_LRIF_Info )
         pRRIF_LIF_LRIF_Info->ValidateAllocationList(idDataGroup);
      ++iter1; 
   }

   // If RRIF already exist in the same year, system should not allow set up of another one.

   DString strEffectiveDate1, strEffectiveDate2, strGoodBad1, strGoodBad2, strGoodKey;
   int iEffectiveDateYear1, iEffectiveDateYear2;
   bool bmodified ( false );

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      RRIF_LIF_LRIF_Info* pRRIF_Info = dynamic_cast<RRIF_LIF_LRIF_Info*>(iter.getObject() );

      pRRIF_Info->getField(ifds::GoodBad, strGoodBad1, idDataGroup);
      if( strGoodBad1 == YES )
      {
         (iter.getObject() )->getField(ifds::EffectiveFrom, strEffectiveDate1, idDataGroup);
         iEffectiveDateYear1 = pRRIF_Info->extractFieldFromDate( strEffectiveDate1 );

         BFObjIter iter0( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
         iter0.positionByKey( iter.getStringKey() );
         ++iter;

         for( ++iter0; !iter0.end(); ++iter0 )
         {
            (iter0.getObject() )->getField(ifds::GoodBad, strGoodBad2, idDataGroup);
            if( strGoodBad2 == YES )
            {
               (iter0.getObject() )->getField(ifds::EffectiveFrom, strEffectiveDate2, idDataGroup);
               iEffectiveDateYear2 = dynamic_cast<RRIF_LIF_LRIF_Info* >(iter0.getObject() )->extractFieldFromDate( strEffectiveDate2 );
               if( iEffectiveDateYear1 == iEffectiveDateYear2 )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_RRIF_EXIST_IN_SAME_YEAR );
                  break;
               }
            }
         }
         if( !bmodified )
            bmodified = ( isNew() || pRRIF_Info->isUpdatedForDataGroup( idDataGroup, true ) );
      }
      else
         ++iter;
   }

   if( bmodified )
   {
      DString dstrTitleRestrict (NO);
      getWorkSession().getOption( ifds::TitleRestrict, dstrTitleRestrict, idDataGroup, false );

      if( dstrTitleRestrict == YES )
      {
         DString acctNum;
         getField(ifds::AccountNum, acctNum, idDataGroup);
         acctNum.strip().stripLeading( '0' );

         AccountEntityXref *pAccountEntityXref = NULL;
         SEVERITY sevRtn = getWorkSession().getAccountEntityXref( idDataGroup, pAccountEntityXref ) ;

         if( sevRtn <= WARNING )
         {
            DString strKey, dstrCurrBusDate;
            getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );    

            if( acctNum != NULL_STRING || _strAccountNum != NULL_STRING )
               SEVERITY sevRtn = pAccountEntityXref->escrowAccount( _strAccountNum, RRIF_AWD, NULL_STRING, dstrCurrBusDate, idDataGroup);

         } // if found AccountEntityXref
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//*******************************************************************
//yingbao AddCopy
void RRIF_LIF_LRIF_InfoList::AddCopy(DString &orgKey, DString &destKey, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "AddCopy" ) );

   SEVERITY sevRtn = setBatchParam();

   if( sevRtn > WARNING )
      return;  // Add copy is not allowed if active batch is not available

   RRIF_LIF_LRIF_Info *pOrgRRIF_LIF_LRIF_Info = NULL, *pDestRRIF_LIF_LRIF_Info = NULL;

   for( BFObjIter Iter( *this, idDataGroup ); !Iter.end(); ++Iter )
   {
      if( Iter.getStringKey() == orgKey )
      {
         pOrgRRIF_LIF_LRIF_Info = dynamic_cast< RRIF_LIF_LRIF_Info * >( Iter.getObject( ) );
      }
      else if( Iter.getStringKey() == destKey )
      {
         pDestRRIF_LIF_LRIF_Info = dynamic_cast< RRIF_LIF_LRIF_Info * >( Iter.getObject( ) );
      }
   }

   assert ( pOrgRRIF_LIF_LRIF_Info && pDestRRIF_LIF_LRIF_Info );

   pDestRRIF_LIF_LRIF_Info->ModelOffer(pOrgRRIF_LIF_LRIF_Info, idDataGroup);
}

//**********************************************************************************
SEVERITY RRIF_LIF_LRIF_InfoList::setOverrideUnusedAmtApplicable( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setOverrideUnusedAmtApplicable" ) );

	bool bIsEnabled = false;

	DString dstrIsRRIFUnusedMaxApp;
	getWorkSession().getOption( ifds::IsRRIFUnusedMaxApp, dstrIsRRIFUnusedMaxApp, idDataGroup, false );
	
	bool bCarryForwardUnusedMax = false,
		 bPermission37          = false;
	if ( I_( "Y" ) == dstrIsRRIFUnusedMaxApp )
	{		
		DString dstrProvReg;
		MFAccount *pAccount = dynamic_cast<MFAccount*> (getParent());
		if ( NULL != pAccount )
		{
			pAccount->getField( ifds::PensionJuris, dstrProvReg, idDataGroup );
		
			/*if ( dstrProvReg.stripAll().empty() )
			{	
				DString dstrShrNum;
				pAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup );

				Shareholder *pShareholder = NULL;
				getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder );
				if ( NULL != pShareholder )
					pShareholder->getField( ifds::TaxJurisCode, dstrProvReg, idDataGroup );
			}*/

		   TaxTypeRule *pTaxTypeRule = NULL;
		   if ( pAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
		   {
		      bCarryForwardUnusedMax = pTaxTypeRule->isCarryForwardUnusedMaxApplic( dstrProvReg, idDataGroup );
		   }
		}
		
		bPermission37 = getWorkSession().hasUpdatePermission(UAF::RIF_LIF_LRIF_FIELD_INFO);
	}
    
	DString dstrIsRRIFOverrUnusedAmtApplic = I_( "N" );
	if ( I_( "Y" ) == dstrIsRRIFUnusedMaxApp && 
		 bCarryForwardUnusedMax && 
		 bPermission37 ) 
	{
		dstrIsRRIFOverrUnusedAmtApplic = I_( "Y" );
	}
	setFieldNoValidate( ifds::isRRIFOverrUnusedAmtApplic, dstrIsRRIFOverrUnusedAmtApplic, idDataGroup );

	return GETCURRENTHIGHESTSEVERITY();
}

//change for CHG0041174 starts
//******************************************************************************
bool RRIF_LIF_LRIF_InfoList::areAllRRIFRecordsInactive (const BFDataGroupId& idDataGroup)
{
	bool bAreAllRRIFRecordsInactive = true;
	BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
	
	DString strGoodBad;
	
	while (!iter.end()) 
	{
		RRIF_LIF_LRIF_Info* pRRIF_Info = dynamic_cast<RRIF_LIF_LRIF_Info*>(iter.getObject() );

		if (pRRIF_Info)
		{
			pRRIF_Info->getField(ifds::GoodBad, strGoodBad, idDataGroup);
			if( strGoodBad == YES )
			{
				bAreAllRRIFRecordsInactive = false;
				break;
			}
		++iter;
		}
	}
	return bAreAllRRIFRecordsInactive;
}
//change for CHG0041174 ends
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIF_LIF_LRIF_InfoList.cpp-arc  $
 * 
 *    Rev 1.40   Oct 04 2010 06:39:44   kitticha
 * PET0168176 FN01 Locked In Product Changes.
 * 
 *    Rev 1.39   15 Apr 2008 12:10:02   kovacsro
 * PET2255 FN47 - New Ontario LIF
 * 
 *    Rev 1.38   Nov 09 2006 15:57:38   ZHANGCEL
 * PET2216 FN35 -- Remove code to check shareholder's TaxJurisCode
 * 
 *    Rev 1.37   Sep 07 2006 16:57:26   porteanm
 * PET2216 FN35 - RRIF Locked-In products - RRIF Unused Amt. 
 * 
 *    Rev 1.36   Sep 01 2005 19:43:28   popescu
 * Incident# 394973 - when user enter only allocation,RRIF record did not get saved.
 * 
 *    Rev 1.35   Nov 14 2004 14:53:16   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.34   Sep 26 2003 15:48:30   YINGBAOL
 * PTS 10022269
 * 
 *    Rev 1.33   Mar 21 2003 18:22:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.32   Oct 09 2002 23:54:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.31   Aug 29 2002 12:56:32   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.30   Aug 06 2002 10:03:26   KOVACSRO
 * Release 48. Converted allocations.
 * 
 *    Rev 1.29   Jul 31 2002 10:15:26   YINGBAOL
 * we don't dovalidateall if it dummy
 * 
 *    Rev 1.28   Jun 19 2002 15:03:26   KOVACSRO
 * formatted versus unformatted.
 * 
 *    Rev 1.27   22 May 2002 18:29:46   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.26   May 15 2002 14:04:24   YINGBAOL
 * check pointer before call ValidateAllocationList
 * 
 *    Rev 1.25   May 08 2002 13:38:14   YINGBAOL
 * PTS10007955
 * 
 *    Rev 1.24   Nov 01 2001 10:20:40   YINGBAOL
 * remove sorting accroding to QA's requirement.
 * 
 *    Rev 1.23   02 Oct 2001 10:54:06   WINNIE
 * implement title restriction
 * 
 *    Rev 1.22   Aug 25 2001 15:36:40   YINGBAOL
 * sort list by status---always put Good in front of bad
 * 
 *    Rev 1.21   Jul 26 2001 16:24:28   ZHANGCEL
 * Added the logic for duplicate RRIF checking
 * 
 *    Rev 1.20   03 May 2001 14:07:04   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.19   Apr 03 2001 15:16:50   YINGBAOL
 * change validation logic for bank since view100 has been changed
 * 
 *    Rev 1.18   Jan 26 2001 16:10:00   ZHANGCEL
 * Synchronized to C2/C3: added setBankListPtr() in init( int iWorkSessionId )
 * 
 *    Rev 1.17   Jan 18 2001 16:09:42   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.16   Dec 17 2000 20:24:24   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.15   Dec 06 2000 10:16:12   WINNIE
 * rename ACCTIVE_BATCH to ACTIVE_BATCH
 * 
 *    Rev 1.14   Dec 04 2000 15:59:56   WINNIE
 * Bug fix to avoid error for opening Default Allocation screen which complain no active batch; call view for active batch only if active batch has never been retrieved
 * 
 *    Rev 1.13   Nov 16 2000 13:34:52   YINGBAOL
 * fixed more button
 * 
 *    Rev 1.12   Nov 02 2000 13:22:34   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.11   Oct 23 2000 11:43:12   YINGBAOL
 * change request for RIF Info
 * 
 *    Rev 1.10   Oct 22 2000 14:39:02   WINNIE
 * clear condition when no data found
 * 
 *    Rev 1.9   Oct 17 2000 14:54:02   YINGBAOL
 * add addcopy fundction and fix other issues
 * 
 *    Rev 1.8   Oct 03 2000 13:29:18   YINGBAOL
 * fix dummy item issue for the list
 * 
 *    Rev 1.7   Sep 28 2000 15:04:36   YINGBAOL
 * greate change in order to make it work
 * 
 *    Rev 1.6   Aug 30 2000 14:38:12   PETOLESC
 * Modified crossedits and logic to call view 130.
 * 
 *    Rev 1.5   Jun 09 2000 18:01:38   PETOLESC
 * Save work.
 * 
 *    Rev 1.4   May 19 2000 17:30:12   PETOLESC
 * save work
 * 
 *    Rev 1.3   Apr 27 2000 10:30:04   PETOLESC
 * Corrected condition when empty list.
 * 
 *    Rev 1.2   Mar 30 2000 09:34:00   YINGBAOL
 * change
 * 
 *    Rev 1.0   Feb 15 2000 11:00:04   SMITHDAV
 * Initial revision.
// 
*/