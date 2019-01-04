//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DailyTransactionsFeeList.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan, 2004
//
// ^CLASS    : DailyTransactionsFeeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "dailytransactionsfee.hpp"
#include "dailytransactionsfeelist.hpp"
#include "dstcommonfunction.hpp"

#include <ifastdataimpl\dse_dstc0284_req.hpp>
#include <ifastdataimpl\dse_dstc0284_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DAILY_TRANSACTIONS_FEE_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("DailyTransactionsFeeList");
}

namespace CND
{  // Conditions used   
	extern const long ERR_DUPLICATE_RECORD;
	extern const long ERR_ANTI_DILUTION_LEVY_DEFAULT_RATE_DOES_NOT_EXIST;
}

namespace ifds
{
   //field ids used
   extern CLASS_IMPORT const BFTextFieldId RecordType;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId DuplicateCheck;
   extern CLASS_IMPORT const BFTextFieldId DuplicateExist;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                             //  Field DD Id,      State Flags,      Group Flags 
   {ifds::RecordType,       BFCBO::NONE,      0}, 
   {ifds::FeeCode,          BFCBO::NONE,      0}, 
   {ifds::FundCode,         BFCBO::NONE,      0}, 
   {ifds::ClassCode,        BFCBO::NONE,      0}, 
   {ifds::EffectiveDate,    BFCBO::NONE,      0}, 
   {ifds::DuplicateCheck,   BFCBO::NONE,      0}, 
   {ifds::StopDate,         BFCBO::NONE,      0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
DailyTransactionsFeeList::DailyTransactionsFeeList(BFAbstractCBO &parent)
: MFCanBFCbo(parent),
_pRequestData(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
}

//******************************************************************************
DailyTransactionsFeeList::~DailyTransactionsFeeList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}

//******************************************************************************
SEVERITY DailyTransactionsFeeList::init( const DString &dstrRecordType,
													  const DString &dstrFeeCode,
													  const DString &dstrFundCode,
													  const DString &dstrClassCode,
													  const DString &dstrEffectiveDate,
													  const DString &dstrStopDate,      /*I_( "9999/12/31" )*/
													  const DString &dstrRecId,         /* I_( "0" ) */
													  const DString &dstrDuplicateCheck /*=I_("N")*/,
													  const BFDataGroupId &idDataGroup /*=BF::HOST*/, 
													  const DString &dstrTrack /*= I_("N")*/, 
													  const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString recordType (dstrRecordType),
           feeCode (dstrFeeCode),
           fundCode (dstrFundCode),
           classCode (dstrClassCode),
           effectiveDate (dstrEffectiveDate),
			  stopDate( dstrStopDate ),
			  recId( dstrRecId ),
           duplicateCheck (dstrDuplicateCheck);
   
   recordType.stripAll().upperCase();
   feeCode.stripAll().upperCase();
   fundCode.stripAll().upperCase();
   classCode.stripAll().upperCase();
   effectiveDate.stripAll().upperCase();
   duplicateCheck.stripAll().upperCase();
	recId.stripAll();
	stopDate.stripAll().upperCase();

	if ( recId == NULL_STRING )
		recId = I_( "0" );
   
	setFieldNoValidate (ifds::RecordType,     recordType,     idDataGroup, false);
   setFieldNoValidate (ifds::FeeCode,        feeCode,        idDataGroup, false);
   setFieldNoValidate (ifds::FundCode,       fundCode,       idDataGroup, false);
   setFieldNoValidate (ifds::ClassCode,      classCode,      idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate,  effectiveDate,  idDataGroup, false);
	setFieldNoValidate (ifds::StopDate,       stopDate,       idDataGroup, false);	
   setFieldNoValidate (ifds::DuplicateCheck, duplicateCheck, idDataGroup, false);

   _pRequestData = new BFData (ifds::DSTC0284_REQ);

   DString mgmtCoIdOut;

   _pRequestData->setElementValue (ifds::RecordType,     recordType );
   _pRequestData->setElementValue (ifds::FeeCode,        feeCode );
   _pRequestData->setElementValue (ifds::FundCode,       fundCode );
   _pRequestData->setElementValue (ifds::ClassCode,      classCode );
   _pRequestData->setElementValue (ifds::EffectiveDate,  effectiveDate );
	_pRequestData->setElementValue (ifds::StopDate,       stopDate );
	_pRequestData->setElementValue (ifds::RecId,          recId );
   _pRequestData->setElementValue (ifds::DuplicateCheck, dstrDuplicateCheck );
   _pRequestData->setElementValue (ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue (ifds::Track,          dstrTrack );
   _pRequestData->setElementValue (ifds::Activity,       dstrPageName );

   ReceiveData( DSTC_REQUEST::DAILY_TRANSACTIONS_FEE_LIST, 
				    *_pRequestData, 
					 ifds::DSTC0284_VW, 
                DSTCRequestor (getSecurity(), false));

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY DailyTransactionsFeeList::doCreateNewObject( BFCBO *&pBase, 
																		DString &strKey, 
																		const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   DString recordType,
           feeCode,
           fundCode,
           classCode,
           effectiveDate;

   getField (ifds::RecordType,    recordType,    idDataGroup, false);
	// If Search Record Type is 'ALL' then default value for new record is 'Default'
	if ( recordType.stripAll() == I_( "00" ) )
		recordType = I_( "01" );
   getField (ifds::FeeCode,       feeCode,       idDataGroup, false);
   getField (ifds::FundCode,      fundCode,      idDataGroup, false);
   getField (ifds::ClassCode,     classCode,     idDataGroup, false);
   getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);

   DailyTransactionsFee *pDailyTransactionsFee = new DailyTransactionsFee (*this);

   if( pDailyTransactionsFee->init( recordType, 
												feeCode, 
												fundCode, 
												classCode, 
												effectiveDate,
												idDataGroup) <= WARNING)
   {
      pBase = pDailyTransactionsFee;
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY DailyTransactionsFeeList::doCreateObject (const BFData &data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   DailyTransactionsFee *pDailyTransactionsFee = 
      new DailyTransactionsFee (*this);

   if (pDailyTransactionsFee->init (data) <= WARNING)
   {
      pObjOut = pDailyTransactionsFee;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DailyTransactionsFeeList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));

   if (doMoreRecordsExist())
   {
      ReceiveData( DSTC_REQUEST::DAILY_TRANSACTIONS_FEE_LIST, 
						 *_pRequestData, 
						 ifds::DSTC0284_VW, 
						 DSTCRequestor(getSecurity(), false));
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void DailyTransactionsFeeList::getStrKey (DString &strKey, const BFData *data)
{
   if (data) 
   {
      DString recordType = data->getElementValue (ifds::RecordType);
      DString feeCode = data->getElementValue (ifds::FeeCode);
      DString fundCode = data->getElementValue (ifds::FundCode);
      DString classCode = data->getElementValue (ifds::ClassCode);
      DString effectiveDate = data->getElementValue (ifds::EffectiveDate);

      buildKey( strKey, 
					 recordType, 
					 feeCode, 
					 fundCode, 
					 classCode,
					 effectiveDate );
   }
   else
   {
      BFCBO::getStrKey (strKey, NULL);
   }
}

//creates a unique key for the list
//******************************************************************************
void DailyTransactionsFeeList::buildKey( DString &dstrKey, 
													  const DString &dstrRecordType, 
													  const DString &dstrFeeCode,
													  const DString &dstrFundCode, 
													  const DString &dstrClassCode,
													  const DString &dstrEffectiveDate)
{
   DString recordType (dstrRecordType);
   DString feeCode (dstrFeeCode);
   DString fundCode (dstrFundCode);
   DString classCode (dstrClassCode);
   DString effectiveDate (dstrEffectiveDate);
	
	dstrKey = I_("EffectiveDate=") + effectiveDate.stripAll().upperCase() +
			    I_(";FundCode=") + fundCode.stripAll().upperCase() + 
				 I_(";ClassCode=") + classCode.stripAll().upperCase() +
				 I_(";FeeCode=") + feeCode.stripAll().upperCase() + 
		       I_(";RecordType=") + recordType.stripAll().upperCase();
}

//********************************************************************
SEVERITY DailyTransactionsFeeList::checkDuplicate( const DString &dstrRecId,
																	const DailyTransactionsFee *pDailyTransactionsFeeToCheck, 
																	const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );   	
	
	bool blHasDuplicate = false;
	
	DString dstrRecordTypeToCheck, 
           dstrFeeCodeToCheck,
			  dstrFundCodeToCheck,
			  dstrClassCodeToCheck,
			  dstrEffectiveDateToCheck,
			  dstrStopDateToCheck,
			  dstrRecIdToCheck( dstrRecId );

   //get the values that are part of key, to check against them
	pDailyTransactionsFeeToCheck->getField (ifds::RecordType,    dstrRecordTypeToCheck,    idDataGroup, false);
   pDailyTransactionsFeeToCheck->getField (ifds::FeeCode,       dstrFeeCodeToCheck,       idDataGroup, false);
   pDailyTransactionsFeeToCheck->getField (ifds::FundCode,      dstrFundCodeToCheck,      idDataGroup, false);
   pDailyTransactionsFeeToCheck->getField (ifds::ClassCode,     dstrClassCodeToCheck,     idDataGroup, false);
   pDailyTransactionsFeeToCheck->getField (ifds::EffectiveDate, dstrEffectiveDateToCheck, idDataGroup, false);
	pDailyTransactionsFeeToCheck->getField (ifds::StopDate,      dstrStopDateToCheck,      idDataGroup, false);	

   dstrRecordTypeToCheck.stripAll().upperCase();
   dstrFeeCodeToCheck.stripAll().upperCase();
   dstrFundCodeToCheck.stripAll().upperCase();
   dstrClassCodeToCheck.stripAll().upperCase();
   dstrEffectiveDateToCheck.stripAll().upperCase();
	dstrStopDateToCheck.stripAll().upperCase();
	dstrRecIdToCheck.stripAll().upperCase();
	
	// Check if any duplicate has been just added in memory, but not yet committed
	iterateMemoryForDuplicateCheck( BFObjIter::ITERTYPE::ADDED, 
										     pDailyTransactionsFeeToCheck,
											  dstrRecordTypeToCheck, 
											  dstrFeeCodeToCheck, 
										     dstrFundCodeToCheck, 
										     dstrClassCodeToCheck, 
										     dstrEffectiveDateToCheck,
										     dstrStopDateToCheck,
											  idDataGroup,
											  blHasDuplicate );


	if ( !blHasDuplicate )
	{
		DailyTransactionsFeeList* dailyTransactionsFeeList = new DailyTransactionsFeeList((BFAbstractCBO&)(*this));

		// Make the View call to check the backend
		if( dailyTransactionsFeeList->init( dstrRecordTypeToCheck, 
													  dstrFeeCodeToCheck, 
													  dstrFundCodeToCheck, 
													  dstrClassCodeToCheck, 
													  dstrEffectiveDateToCheck,
													  dstrStopDateToCheck,
													  dstrRecIdToCheck,
													  I_("Y"), //check the duplicate													  
													  idDataGroup) <= WARNING )
		{         
			DString duplicateExist;
			dailyTransactionsFeeList->getField( ifds::DuplicateExist, duplicateExist, idDataGroup, false );
         
			blHasDuplicate = duplicateExist == I_("Y");
			
			if ( blHasDuplicate )
			{
				// Check the memory for possible deleted duplicates      
				bool blDeleted = false;
				iterateMemoryForDuplicateCheck( BFObjIter::ITERTYPE::DELETED, 
														  NULL,   // no need to check against itself
														  dstrRecordTypeToCheck, 
														  dstrFeeCodeToCheck, 
														  dstrFundCodeToCheck, 
														  dstrClassCodeToCheck, 
														  dstrEffectiveDateToCheck,
														  dstrStopDateToCheck,
														  idDataGroup,
														  blDeleted );			

				if ( blDeleted )
					blHasDuplicate = false;
				
				// For a Default Record, if duplicate found in the database and record not deleted in memory, 
				// then check if the corresponding record in memory has been modified.		
				if ( !blDeleted && I_( "01" ) == dstrRecordTypeToCheck )
				{
					// This list will really have only one record
					BFObjIter iterDuplicate( *dailyTransactionsFeeList, idDataGroup );
					iterDuplicate.begin();
  					while ( !iterDuplicate.end( ) )
					{
						DailyTransactionsFee *pDuplicateDailyTransactionsFee = 
								dynamic_cast<DailyTransactionsFee*> (iterDuplicate.getObject( ) );	
						if ( NULL != pDuplicateDailyTransactionsFee )
						{
							DString dstrDuplicateRecId, 
									  dstrMemoryEffectiveDate,dstrMemoryStopDate, 
									  dstrOrigEffectiveDate,dstrOrigStopDate;
							pDuplicateDailyTransactionsFee->getField( ifds::DailyFeeRid, dstrDuplicateRecId, idDataGroup, false );
							dstrDuplicateRecId.strip().upperCase();

							BFObjIter iterInMemory( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
							iterInMemory.begin();
							while (!iterInMemory.end())
							{            
								if ( iterInMemory.getKey().getActivity() != OBJ_ACTIVITY_ADDED )
								{
									DailyTransactionsFee *pMemoryDailyTransactionsFee = 
									dynamic_cast<DailyTransactionsFee*> (iterInMemory.getObject() );
                  
									if ( NULL != pMemoryDailyTransactionsFee &&
										  pMemoryDailyTransactionsFee->hasNonHostUpdates() )
									{
										DString dstrMemoryRecId;
										pMemoryDailyTransactionsFee->getField( ifds::DailyFeeRid, dstrMemoryRecId, idDataGroup );
										dstrMemoryRecId.strip().upperCase();

										if ( dstrMemoryRecId == dstrDuplicateRecId )
										{	
											pMemoryDailyTransactionsFee->getField( ifds::EffectiveDate, dstrMemoryEffectiveDate, idDataGroup );
											pMemoryDailyTransactionsFee->getField( ifds::StopDate,      dstrMemoryStopDate,      idDataGroup );
											
											pMemoryDailyTransactionsFee->getFieldBeforeImage( ifds::EffectiveDate, dstrOrigEffectiveDate );
											pMemoryDailyTransactionsFee->getFieldBeforeImage( ifds::StopDate,      dstrOrigStopDate );

											dstrMemoryEffectiveDate.strip().upperCase();
											dstrMemoryStopDate.strip().upperCase();
											dstrOrigEffectiveDate.strip().upperCase();
											dstrOrigStopDate.strip().upperCase();

											if ( dstrOrigEffectiveDate != dstrMemoryEffectiveDate ||
												  dstrOrigStopDate      != dstrMemoryStopDate )
											{
												// This has already been checked in the first section, memory check for 
												// newly added records, it's not a duplicate
												blHasDuplicate = false;
											}			

											break;
										}
									}
								}
								++iterInMemory;
							}							
						}

						// We should have only 1 record!
						++iterDuplicate;
					}
				}				
			}
		}
	}

	if ( blHasDuplicate )
	{
		ADDCONDITIONFROMFILE( CND::ERR_DUPLICATE_RECORD );
	}
   
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY DailyTransactionsFeeList::iterateMemoryForDuplicateCheck( enum BFObjIter::ITERTYPE iterType, 
																						 const DailyTransactionsFee *pDailyTransactionsFeeToCheck,
																						 const DString &dstrRecordTypeToCheck,
 																						 const DString &dstrFeeCodeToCheck,
																						 const DString &dstrFundCodeToCheck,
																						 const DString &dstrClassCodeToCheck,
																						 const DString &dstrEffectiveDateToCheck,
																						 const DString &dstrStopDateToCheck,
																						 const BFDataGroupId &idDataGroup,
																						 bool &blHasDuplicate )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "iterateMemoryForDuplicateCheck" ) );	

	blHasDuplicate = false;

	BFObjIter iterMemoryCheck( *this, idDataGroup, 0, iterType );
	iterMemoryCheck.begin();						
	while ( !iterMemoryCheck.end( ) )
	{
		DailyTransactionsFee *pMemoryCheckDailyTransactionsFee = dynamic_cast<DailyTransactionsFee*>(iterMemoryCheck.getObject());

		//do not chech against itself
		if(  NULL != pMemoryCheckDailyTransactionsFee &&
			  pMemoryCheckDailyTransactionsFee != pDailyTransactionsFeeToCheck )
		{
			DString dstrMemoryCheckRecordType, 
					  dstrMemoryCheckFeeCode,
					  dstrMemoryCheckFundCode,
					  dstrMemoryCheckClassCode,
					  dstrMemoryCheckEffectiveDate,
					  dstrMemoryCheckStopDate;

			pMemoryCheckDailyTransactionsFee->getField (ifds::RecordType,    dstrMemoryCheckRecordType,    idDataGroup, false );
			pMemoryCheckDailyTransactionsFee->getField (ifds::FeeCode,       dstrMemoryCheckFeeCode,       idDataGroup, false);
			pMemoryCheckDailyTransactionsFee->getField (ifds::FundCode,      dstrMemoryCheckFundCode,      idDataGroup, false);
			pMemoryCheckDailyTransactionsFee->getField (ifds::ClassCode,     dstrMemoryCheckClassCode,     idDataGroup, false);
			pMemoryCheckDailyTransactionsFee->getField (ifds::EffectiveDate, dstrMemoryCheckEffectiveDate, idDataGroup, false);
			pMemoryCheckDailyTransactionsFee->getField (ifds::StopDate,      dstrMemoryCheckStopDate,      idDataGroup, false);

			dstrMemoryCheckRecordType.stripAll().upperCase();
			dstrMemoryCheckFeeCode.stripAll().upperCase();
			dstrMemoryCheckFundCode.stripAll().upperCase();
			dstrMemoryCheckClassCode.stripAll().upperCase();
			dstrMemoryCheckEffectiveDate.stripAll().upperCase();
			dstrMemoryCheckStopDate.stripAll().upperCase();

			if ( dstrRecordTypeToCheck == dstrMemoryCheckRecordType && 
				  dstrFeeCodeToCheck    == dstrMemoryCheckFeeCode &&
				  dstrFundCodeToCheck   == dstrMemoryCheckFundCode && 
				  dstrClassCodeToCheck  == dstrMemoryCheckClassCode )
			{					
					if ( // If Daily, check for exact match for Effective Date and Stop Date
						  ( I_( "02" )    == dstrRecordTypeToCheck &&
							 DSTCommonFunctions::CompareDates( dstrEffectiveDateToCheck, dstrMemoryCheckEffectiveDate ) == DSTCommonFunctions::EQUAL &&
							 DSTCommonFunctions::CompareDates( dstrStopDateToCheck,      dstrMemoryCheckStopDate ) == DSTCommonFunctions::EQUAL ) ||							 
							 // If Default, check for date ovelaping
			  				 ( I_( "01" ) == dstrRecordTypeToCheck && 
							 ( !DSTCommonFunctions::CompareDates( dstrMemoryCheckStopDate,   dstrEffectiveDateToCheck ) == DSTCommonFunctions::FIRST_EARLIER &&
								!DSTCommonFunctions::CompareDates( dstrStopDateToCheck, dstrMemoryCheckEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER  ) ) )
					{
						blHasDuplicate = true;
						break;
					}												  					
			}
		}
		++iterMemoryCheck;
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY DailyTransactionsFeeList::checkDefaultExists( const DailyTransactionsFee *pDailyTransactionsFeeToCheck, 
																		 const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDefaultExists" ) ); 

	bool blDefaultExists = false;

	DString feeCode,
			  fundCode,
			  classCode,
			  effectiveDate,
			  stopDate;

   //get the values part of key, to check against 	
   pDailyTransactionsFeeToCheck->getField (ifds::FeeCode,       feeCode,       idDataGroup, false);
   pDailyTransactionsFeeToCheck->getField (ifds::FundCode,      fundCode,      idDataGroup, false);
   pDailyTransactionsFeeToCheck->getField (ifds::ClassCode,     classCode,     idDataGroup, false);
   pDailyTransactionsFeeToCheck->getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);
	pDailyTransactionsFeeToCheck->getField (ifds::StopDate,      stopDate,      idDataGroup, false);	
   
   feeCode.stripAll().upperCase();
   fundCode.stripAll().upperCase();
   classCode.stripAll().upperCase();
   effectiveDate.stripAll().upperCase();
	stopDate.stripAll().upperCase();	
   
   // check first whether in the list (in memory) the record exists, this catches the newly added items, as well 
   BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::ADDED );
	iter.begin();
   while( !iter.end() )
   {
      DailyTransactionsFee *pDailyTransactionsFee = dynamic_cast<DailyTransactionsFee*>(iter.getObject());

		//do not chech against itself
      if( pDailyTransactionsFee != pDailyTransactionsFeeToCheck &&
			 NULL != pDailyTransactionsFee )
      {
			DString recordType_;
         pDailyTransactionsFee->getField (ifds::RecordType, recordType_, idDataGroup, false );
			// check only if it is a Default record
			if ( I_( "01" ) == recordType_.stripAll() )
			{					
			   DString feeCode_,
					     fundCode_,
					     classCode_,
					     effectiveDate_,
					     stopDate_;

            pDailyTransactionsFee->getField(ifds::FeeCode,       feeCode_,       idDataGroup, false );
            pDailyTransactionsFee->getField(ifds::FundCode,      fundCode_,      idDataGroup, false );
            pDailyTransactionsFee->getField(ifds::ClassCode,     classCode_,     idDataGroup, false );
            pDailyTransactionsFee->getField(ifds::EffectiveDate, effectiveDate_, idDataGroup, false );
				pDailyTransactionsFee->getField(ifds::StopDate,      stopDate_,      idDataGroup, false );
            
            feeCode_.stripAll().upperCase();
            fundCode_.stripAll().upperCase();
            classCode_.stripAll().upperCase();
            effectiveDate_.stripAll().upperCase();
				stopDate_.stripAll().upperCase();

				if ( feeCode    == feeCode_   &&
	              fundCode   == fundCode_  && 
		           classCode  == classCode_ &&
					  // Effective Date check
					  ( DSTCommonFunctions::CompareDates( effectiveDate_, effectiveDate ) == DSTCommonFunctions::FIRST_EARLIER ||					    
			          DSTCommonFunctions::CompareDates( effectiveDate_, effectiveDate ) == DSTCommonFunctions::EQUAL ) &&
					  // Stop Date check
					  ( DSTCommonFunctions::CompareDates( effectiveDate, stopDate_ ) == DSTCommonFunctions::FIRST_EARLIER ||					    
			          DSTCommonFunctions::CompareDates( effectiveDate, stopDate_ ) == DSTCommonFunctions::EQUAL )  
			      )			
				{
					blDefaultExists = true;
	            break;
				}
		   }
      }
      ++iter;
   }

	// if no Default in memory, check the back-end
   if( !blDefaultExists )
   {
	   DailyTransactionsFeeList* dailyTransactionsFeeList = new DailyTransactionsFeeList((BFAbstractCBO&)(*this));

      if( dailyTransactionsFeeList->init( I_( "01" ), 
													  feeCode, 
													  fundCode, 
													  classCode, 
													  effectiveDate,
													  stopDate,
													  I_( "0" ),   // recid
													  I_("Y"),     //check the duplicate													  
													  idDataGroup) <= WARNING )
      {         
         DString duplicateExist;
         dailyTransactionsFeeList->getField( ifds::DuplicateExist, duplicateExist, idDataGroup, false);        
			blDefaultExists = duplicateExist == I_("Y");
         
			//if we found a duplicate, this might have been already deleted in the memory
         if( blDefaultExists )
         {  
				//check the memory again for possible deleted duplicates            
				BFObjIter iterInMemory (*this, idDataGroup, 0, BFObjIter::ITERTYPE::DELETED);				
				iterInMemory.begin();
            while (!iterInMemory.end())
            {               
               DailyTransactionsFee *pDeletedDailyTransactionsFee = dynamic_cast<DailyTransactionsFee*> (iterInMemory.getObject());                  
					if ( NULL != pDeletedDailyTransactionsFee )
					{
						DString deletedRecordType;
						pDeletedDailyTransactionsFee->getField( ifds::RecordType, deletedRecordType, idDataGroup, false );
						if ( I_( "01" ) == deletedRecordType.stripAll() )
						{
							DString deletedFeeCode,
								     deletedFundCode,
								     deletedClassCode,
								     deletedEffectiveDate,
								     deletedStopDate;

							pDeletedDailyTransactionsFee->getField( ifds::FeeCode,       deletedFeeCode,       idDataGroup, false );
							pDeletedDailyTransactionsFee->getField( ifds::FundCode,      deletedFundCode,      idDataGroup, false );
							pDeletedDailyTransactionsFee->getField( ifds::ClassCode,     deletedClassCode,     idDataGroup, false );
							pDeletedDailyTransactionsFee->getField( ifds::EffectiveDate, deletedEffectiveDate, idDataGroup, false );
							pDeletedDailyTransactionsFee->getField( ifds::StopDate,      deletedStopDate,      idDataGroup, false );
                  
							deletedFeeCode.stripAll().upperCase();
							deletedFundCode.stripAll().upperCase();
							deletedClassCode.stripAll().upperCase();
							deletedEffectiveDate.stripAll().upperCase();
							deletedStopDate.stripAll().upperCase();
                  
							if ( feeCode   == deletedFeeCode   &&
								  fundCode  == deletedFundCode  && 
								  classCode == deletedClassCode &&
								  // Effective Date check
								  ( DSTCommonFunctions::CompareDates( deletedEffectiveDate, effectiveDate ) == DSTCommonFunctions::FIRST_EARLIER ||					    
									 DSTCommonFunctions::CompareDates( deletedEffectiveDate, effectiveDate ) == DSTCommonFunctions::EQUAL ) &&
								  // Stop Date check
								  ( DSTCommonFunctions::CompareDates( effectiveDate, deletedStopDate ) == DSTCommonFunctions::FIRST_EARLIER ||					    
									 DSTCommonFunctions::CompareDates( effectiveDate, deletedStopDate ) == DSTCommonFunctions::EQUAL )  
								)									
							 {
									blDefaultExists = false;
									break;
							 }
						}
					}               
               ++iterInMemory;
            }

				// For this Default Record, if duplicate found in the database and record not deleted in memory, 
				// then check if the corresponding record in memory has been modified.		
				if ( blDefaultExists )
				{
					// This list will really have only one record
					BFObjIter iterDuplicate( *dailyTransactionsFeeList, idDataGroup );
					iterDuplicate.begin();
  					while ( !iterDuplicate.end( ) )
					{
						DailyTransactionsFee *pDuplicateDailyTransactionsFee = 
								dynamic_cast<DailyTransactionsFee*> (iterDuplicate.getObject( ) );	
						if ( NULL != pDuplicateDailyTransactionsFee )
						{
							DString dstrDuplicateRecId, 
									  dstrMemoryEffectiveDate,dstrMemoryStopDate, 
									  dstrOrigEffectiveDate,dstrOrigStopDate;
							pDuplicateDailyTransactionsFee->getField( ifds::DailyFeeRid, dstrDuplicateRecId, idDataGroup, false );
							dstrDuplicateRecId.strip().upperCase();

							BFObjIter iterInMemory( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
							iterInMemory.begin();
							while (!iterInMemory.end())
							{            
								if ( iterInMemory.getKey().getActivity() != OBJ_ACTIVITY_ADDED )
								{
									DailyTransactionsFee *pMemoryDailyTransactionsFee = 
									dynamic_cast<DailyTransactionsFee*> (iterInMemory.getObject() );
                  
									if ( NULL != pMemoryDailyTransactionsFee &&
										  pMemoryDailyTransactionsFee->hasNonHostUpdates() )
									{
										DString dstrMemoryRecId;
										pMemoryDailyTransactionsFee->getField( ifds::DailyFeeRid, dstrMemoryRecId, idDataGroup );
										dstrMemoryRecId.strip().upperCase();

										if ( dstrMemoryRecId == dstrDuplicateRecId )
										{	
											pMemoryDailyTransactionsFee->getField( ifds::EffectiveDate, dstrMemoryEffectiveDate, idDataGroup );
											pMemoryDailyTransactionsFee->getField( ifds::StopDate,      dstrMemoryStopDate,      idDataGroup );
											
											pMemoryDailyTransactionsFee->getFieldBeforeImage( ifds::EffectiveDate, dstrOrigEffectiveDate );
											pMemoryDailyTransactionsFee->getFieldBeforeImage( ifds::StopDate,      dstrOrigStopDate );

											dstrMemoryEffectiveDate.strip().upperCase();
											dstrMemoryStopDate.strip().upperCase();
											dstrOrigEffectiveDate.strip().upperCase();
											dstrOrigStopDate.strip().upperCase();

											if ( dstrOrigEffectiveDate != dstrMemoryEffectiveDate ||
												  dstrOrigStopDate      != dstrMemoryStopDate )
											{
												// Effective Date check againts Memory Effective and Stop Dates check
												if ( DSTCommonFunctions::CompareDates( effectiveDate, dstrMemoryEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER ||					    																	  
													  DSTCommonFunctions::CompareDates( dstrMemoryStopDate, effectiveDate ) == DSTCommonFunctions::FIRST_EARLIER )									
												{
													blDefaultExists = false;												
												}
											}			

											break;
										}
									}
								}
								++iterInMemory;
							}							
						}

						// We should have only 1 record!
						++iterDuplicate;
					}
				}				
         }
      }
   }

	if ( !blDefaultExists )
	{
		ADDCONDITIONFROMFILE( CND::ERR_ANTI_DILUTION_LEVY_DEFAULT_RATE_DOES_NOT_EXIST );
	}

	return GETCURRENTHIGHESTSEVERITY();
}


//********************************************************************
SEVERITY DailyTransactionsFeeList::getDailyTransactionFee( const DString &dstrRecordType, 
																			  const DString &dstrFeeCode,
																			  const DString &dstrFundCode, 
																			  const DString &dstrClassCode,
																			  const DString &dstrEffectiveDate,
																			  const BFDataGroupId &idDataGroup,
																			  DailyTransactionsFee *&pDailyTransactionsFee )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDailyTransactionFee"));

	pDailyTransactionsFee = NULL;

	DString dstrKey;
	buildKey( dstrKey, dstrRecordType, dstrFeeCode, dstrFundCode, dstrClassCode, dstrEffectiveDate);

	pDailyTransactionsFee = dynamic_cast<DailyTransactionsFee*>( getObject( dstrKey, idDataGroup ) );
	
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DailyTransactionsFeeList.cpp-arc  $
// 
//    Rev 1.11   Dec 15 2004 11:06:26   hernando
// PET910 - Added StopDate to Field Info array.
// 
//    Rev 1.10   Nov 14 2004 14:30:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Apr 05 2004 11:33:50   VADEANUM
// PTS 10028631 - Changed key based on Sue's/Lina's/Winnie's request.
// 
//    Rev 1.8   Mar 25 2004 17:48:00   VADEANUM
// PTS 10028525 - Duplicate check.
// 
//    Rev 1.7   Mar 05 2004 14:44:40   VADEANUM
// PET859 FN23 - ADL - use iterators with specialised type (i.e. ADDED, DELETED, etc)
// 
//    Rev 1.6   Mar 04 2004 09:41:00   VADEANUM
// PET859 FN23 - ADL - additional logic to Duplicate Check. It works for now, however, the algorithm needs optimization.
// 
//    Rev 1.5   Feb 25 2004 15:47:48   VADEANUM
// PET859 FN23 - ADl - separated duplicate check from default existance check.
// 
//    Rev 1.4   Feb 25 2004 13:38:12   VADEANUM
// PET859 FN23 - ADL - Layout change for 284, modified signature of DailyTransactionsFeesList::init().
// 
//    Rev 1.3   Feb 23 2004 10:29:18   VADEANUM
// PET 859 FN23 - ADL - fix for hasDuplicate flag.
// 
//    Rev 1.2   Feb 12 2004 13:30:06   VADEANUM
// PET859 FN23 - ADL - added StopDate and modified checkDuplicate().
// 
//    Rev 1.1   Feb 10 2004 16:33:56   VADEANUM
// PET 859 FN23 - ADL - added getDailyTransactionFee()
// 
//    Rev 1.0   Jan 28 2004 14:07:04   popescu
// Initial revision.
// 
// 
 */