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
// ^FILE   : TransCancellation.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : TransCancellation 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include "TransCancellation.hpp"
#include "dstcommonfunction.hpp"
#include "DilutionAllocList.hpp"
#include "DilutionAlloc.hpp"

#include "mgmtco.hpp"

#include <dataimpl\dse_dstc0337_req.hpp>
#include <dataimpl\dse_dstc0337_vw.hpp>
#include <dataimpl\dse_dstc0127_req.hpp>
#include <dataimpl\dse_dstc0127_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANS_CANCEL;
   extern CLASS_IMPORT const DSTCRequest TRANS_NUM;
}

namespace  
{
   const I_CHAR * const CLASSNAME    = I_( "TransCancellation");  
   
   const I_CHAR * const UNVERIFIED	 = I_("01");
   const I_CHAR * const VERIFIED	 = I_("02");
   const I_CHAR * const DELETED		 = I_("03");

   const I_CHAR * const YES	 = I_("Y");
   const I_CHAR * const NO	 = I_("N");
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const VERIFY_CANCEL_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const TRANCE_CANCELLATION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Batch;
   extern CLASS_IMPORT const BFDecimalFieldId Trace;
   extern CLASS_IMPORT const BFTextFieldId ReadOnly;
   extern CLASS_IMPORT const BFTextFieldId NextKey;
   extern CLASS_IMPORT const BFTextFieldId VerCancTrd;
   extern CLASS_IMPORT const BFTextFieldId AccountableMandatory;
   extern CLASS_IMPORT const BFTextFieldId SupTransNo;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercent;
}
namespace CND
{
   //extern const long ERR_DATA_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
}



//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags
   
   { ifds::TransNum,	   BFCBO::REQUIRED,	0 }, 
   { ifds::Accountable,	   BFCBO::NONE,	0 },      
   { ifds::RvCode,		   BFCBO::REQUIRED,	0 },   
   { ifds::OnStmt,		   BFCBO::REQUIRED,	0 },      

   { ifds::ConfirmRequired, BFCBO::REQUIRED,	0 },   
   { ifds::CancelCheque,   BFCBO::REQUIRED,	0 },
   { ifds::TranStatus,    BFCBO::NONE,   0 }, 
   { ifds::Remarks1,       BFCBO::NONE,	0 },
   { ifds::Remarks2,	   BFCBO::NONE,	0 },
   { ifds::Remarks3,	   BFCBO::NONE,	0 },
   { ifds::ModPermission,	   BFCBO::NONE,	0 },
   { ifds::Version,			 BFCBO::NONE,	0 },
   { ifds::TransType,        BFCBO::NONE,   0},
   { ifds::TransId,        BFCBO::NONE,   0},
   { ifds::Batch,          BFCBO::NONE,   0 }, 
   { ifds::Trace,          BFCBO::NONE,   0 }, 

   { ifds::ReadOnly,	   BFCBO::CALCULATED_FIELD,	0 },   
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//*********************************************************************************
TransCancellation::TransCancellation( BFAbstractCBO &parent ) : MFCanBFCbo( parent )
,requestData337( NULL )
,newCancellation( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL );
   setObjectAsList();
}

//*********************************************************************************
TransCancellation::~TransCancellation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if ( requestData337 != NULL )
   {
      delete requestData337;
   }
}


//*********************************************************************************
SEVERITY TransCancellation::init ( const DString &transNum,							    
                                const BFDataGroupId &idDataGroup, 
                                const DString &dstrTrack, /*=I_("N")*/
                                const DString &dstrPageName /*=NULL_STRING*/
                              )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
// receive data from back end

    DString mgmtCoIdOut;	
	requestData337 = new BFData(ifds::DSTC0337_REQ);
	requestData337->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	requestData337->setElementValue( ifds::Track, dstrTrack );
	requestData337->setElementValue( ifds::Activity, dstrPageName );
	requestData337->setElementValue( ifds::NextKey, NULL_STRING);
	requestData337->setElementValue( ifds::TransNum, transNum);

	BFData* responseData = new BFData (ifds::DSTC0337_VW);	

	if( ReceiveData ( DSTC_REQUEST::TRANS_CANCEL, 
						*requestData337, 
						*responseData, 
						DSTCRequestor( getSecurity(),false,true ) 
                     )  >= WARNING )
	{
		int count = CONDITIONCOUNT();
		Condition   *c = NULL;
		for( int i = 0; i < count; i++ )
		{
			c = GETCONDITION( i );
			int condCode = c->getCode();
			if( condCode == CND::ERR_DATA_NOT_FOUND )
			{
				CLEARCONDITION( i )
				newCancellation = true;
				break;
			}
		}
	}

	//temp fix for the list CBOs
	

	DString transNum_(transNum);
	CommonInit( newCancellation, transNum_, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TransCancellation::buildKey (const DString &transNum, DString &strKey)
{
   DString transNum_(transNum);
   
   transNum_.strip().upperCase();
   strKey = I_("TransNum=") + transNum;
}

//******************************************************************************

SEVERITY TransCancellation::getDilutionAllocList ( const BFDataGroupId& idDataGroup, 
										           DilutionAllocList *&pDilutionAllocList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDilutionAllocList" ) );

   DString dstrTransId;
   getField(ifds::TransId,dstrTransId,idDataGroup,false);

   pDilutionAllocList = dynamic_cast<DilutionAllocList*>(BFCBO::getObject( I_( "DilutionAllocList" ), idDataGroup ) );
   if( !pDilutionAllocList )
   {
	 if( newCancellation )
	 {
		  pDilutionAllocList = new DilutionAllocList( *this );
		  pDilutionAllocList->initNew(idDataGroup);
	 }	
	 if( dstrTransId != NULL_STRING )
	 {
		  pDilutionAllocList = new DilutionAllocList( *this );
		  pDilutionAllocList->init(dstrTransId, idDataGroup );
	 }
	if( pDilutionAllocList )
	 {
		 if( GETCURRENTHIGHESTSEVERITY() < WARNING )
		 {
			 setObject( pDilutionAllocList, I_( "DilutionAllocList" ), 
				OBJ_ACTIVITY_NONE, idDataGroup ); 
		 }
		 else
		 {
			delete pDilutionAllocList;
			pDilutionAllocList = NULL;
		 }
	  }
   }	 

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void TransCancellation::setReadOnlyFields ( bool readonly, const BFDataGroupId &idDataGroup)
{
    setFieldReadOnly (ifds::Accountable, idDataGroup, readonly);
	setFieldReadOnly (ifds::RvCode, idDataGroup, readonly);
	setFieldReadOnly (ifds::OnStmt, idDataGroup, readonly);

	setFieldReadOnly (ifds::ConfirmRequired, idDataGroup, readonly);
	setFieldReadOnly (ifds::CancelCheque, idDataGroup, readonly);
	setFieldReadOnly (ifds::Batch, idDataGroup, readonly);
	setFieldReadOnly (ifds::Remarks1, idDataGroup, readonly);
	setFieldReadOnly (ifds::Remarks2, idDataGroup, readonly);
	setFieldReadOnly (ifds::Remarks3, idDataGroup, readonly);
}

//******************************************************************************
void TransCancellation::CommonInit( bool newCancellation, DString &transNum, const BFDataGroupId &idDataGroup )
{	
	convertFields(idDataGroup, false);

	setFieldReadOnly (ifds::TransNum, idDataGroup, true);
	setFieldReadOnly (ifds::TranStatus, idDataGroup, true);

	DString dstrReadOnly = NO;

	bool bTransCancel = false, bVerification = false;
	bTransCancel = getWorkSession().hasReadPermission( UAF::TRANCE_CANCELLATION  );
	bVerification = getWorkSession().hasReadPermission( UAF::VERIFY_CANCEL_INSTRUCTION  );

	if( newCancellation /* dstrModPerm == NULL_STRING */ )
	{
		if( !bTransCancel )
		{
			dstrReadOnly = YES;
			setReadOnlyFields(true, idDataGroup );
		}
		else 
		{
			DString dstrVerifyCancel=NO;

			getWorkSession().getOption (ifds::VerCancTrd, dstrVerifyCancel, BF::HOST, false);
			if( dstrVerifyCancel == YES )
				setFieldNoValidate (ifds::TranStatus, UNVERIFIED, idDataGroup, false, false, true);	
			else
				setFieldNoValidate (ifds::TranStatus, VERIFIED, idDataGroup, false, false, true);

			setFieldNoValidate (ifds::OnStmt, NO, idDataGroup, false, false, true);
			setFieldNoValidate (ifds::ConfirmRequired, YES, idDataGroup, false, false, true);
			setFieldNoValidate (ifds::CancelCheque, YES, idDataGroup, false, false, true);			

			setFieldNoValidate (ifds::TransNum, transNum, idDataGroup, false, false, true);
		}
	}
	else	
	{
		DString dstrModPerm, dstrTranStatus;

		getField(ifds::ModPermission,dstrModPerm,idDataGroup,false);
		getField(ifds::TranStatus,dstrTranStatus,idDataGroup,false);

		if(   dstrTranStatus == VERIFIED || 
			( dstrModPerm == I_("1") && !bTransCancel ) ||
			( dstrModPerm == I_("2") && !bVerification )    )
		{			
			dstrReadOnly = YES;
			setReadOnlyFields(true, idDataGroup );
		}
	}

	setFieldNoValidate (ifds::ReadOnly, dstrReadOnly, idDataGroup, false, false, true);

	//init batch by call view 127
	getBatchNum( idDataGroup );	

	DString dstrDilution;
	getWorkSession().getOption (ifds::AccountableMandatory, dstrDilution, BF::HOST, false);
	if( dstrDilution == YES && dstrReadOnly != YES )
	{
		DilutionAllocList * pDilutionAllocList = NULL;
		getDilutionAllocList( idDataGroup, pDilutionAllocList );	

		DString dstrAccountable;
		getField(ifds::Accountable,dstrAccountable,idDataGroup,false);

		if( !newCancellation )
		{
			if( pDilutionAllocList )
			{
				BFObjIter iter(*pDilutionAllocList, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);
				if( iter.getNumberOfItemsInList () == 0 )
				{
					pDilutionAllocList->addNewAllocation(dstrAccountable, BF::HOST, false, true);
				}
			}
		}
		else
		{
			pDilutionAllocList->addNewAllocation( NULL_STRING, BF::HOST, false, true);
		}
	}
}

//******************************************************************************
SEVERITY TransCancellation::getBatchNum ( const BFDataGroupId &idDataGroup,
                                const DString &track /*= I_("N")*/,
                                const DString &pageName /*= NULL_STRING*/)
{
      MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getBatchNum"));

      BFData query127 (ifds::DSTC0127_REQ);
	  BFData *response = new BFData (ifds::DSTC0127_VW);

	  DString mgmtCoIdOut;
      query127.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	  query127.setElementValue (ifds::Track, track);
	  query127.setElementValue (ifds::Activity, pageName);
      query127.setElementValue (ifds::SupTransNo, YES);	  

      if (BFDataBroker::getInstance ()->
            receive ( DSTC_REQUEST::TRANS_NUM, 
                      query127, 
		              *response, 
                      DSTCRequestor (getSecurity ())) <= WARNING)
	   {
		   DString batch, batchTrace;
		   response->getElementValue (ifds::rxBatchName, batch);
		   response->getElementValue (ifds::BatchTrace, batchTrace);
		   
           batch.strip();
		   batchTrace.strip();
           setFieldNoValidate (ifds::Batch, batch, idDataGroup, false);
		   setFieldReadOnly (ifds::Batch, idDataGroup, true);

           setFieldNoValidate (ifds::Trace, batchTrace, idDataGroup, false);
		   setFieldReadOnly (ifds::Trace, idDataGroup, true);
      }

	  if (response)
      {
         delete response;
         response = NULL;
      }

	  return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY TransCancellation::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   return GETCURRENTHIGHESTSEVERITY();
}
//*********************************************************************************
SEVERITY TransCancellation::ValidateAccountable( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   //getdilutionlist, if number of records < = 1 then accountable code required.
   DString dstrAccountable;
   getField(ifds::Accountable,dstrAccountable,idDataGroup,false);

   DilutionAllocList * pDilutionList = NULL;
   pDilutionList = dynamic_cast<DilutionAllocList*>(BFCBO::getObject( I_( "DilutionAllocList" ), idDataGroup ) );
   if( pDilutionList )
   {
	   BFObjIter iter1(*pDilutionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
       if( iter1.getNumberOfItemsInList() <=1 && dstrAccountable == NULL_STRING )
	   {
		   ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );
	   }
   }
   else if( dstrAccountable == NULL_STRING ) 
   {
	   ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//************************************************************************************
SEVERITY TransCancellation::setField( const BFFieldId& idField, const DString& dstrValue,
                               const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect, bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );   

   BFCBO::setField( idField, dstrValue, idDataGroup, bFormatted, bSideEffect );

   if( idField == ifds::Accountable )
   {
	   DString dstrReadOnly, dstrAccountable;
	   getField(ifds::ReadOnly,dstrReadOnly,idDataGroup,false);
	   dstrAccountable = dstrValue;

	   if( dstrReadOnly != YES ) 
	   {
			if( dstrValue == NULL_STRING )
			{
				setFieldReadOnly (ifds::Accountable, idDataGroup, true );
			}
			else
			{
				setFieldReadOnly (ifds::Accountable, idDataGroup, false );
				//if only one dilution record then set accountable to that record.
				DilutionAllocList * pDilutionAllocList = NULL;
				getDilutionAllocList( idDataGroup, pDilutionAllocList );
				BFObjIter iter(*pDilutionAllocList, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);
				if( iter.getNumberOfItemsInList () == 1 )
				{
					DilutionAlloc *pDilutionAlloc_ = dynamic_cast <DilutionAlloc*> (iter.getObject ());   
					if ( pDilutionAlloc_ )
					{
						pDilutionAlloc_->setField(ifds::Accountable, dstrAccountable, idDataGroup );
						pDilutionAlloc_->setField(ifds::AllocPercent, I_("100"), idDataGroup );
					}
				}
			}
	   }
   }	
   if( idField == ifds::TranStatus )
   {
	   if( dstrValue == DELETED )
	   {
		    DilutionAllocList * pDilutionAllocList = NULL;
		    getDilutionAllocList( idDataGroup, pDilutionAllocList );

			BFObjIter bfIter( *pDilutionAllocList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED, false );
			bfIter.begin();
			while( !bfIter.end() )
			{				
				bfIter.deleteObject ();
			}
	   }
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void TransCancellation::getField(const BFFieldId& idField, DString &dstrFieldValue, 
                              const BFDataGroupId& idDataGroup, bool formattedReturn) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getField"));   
/*
   BFObjIter bfIter( *this, idDataGroup, true );
   if( !bfIter.end() )
   {
	   BFCBO *pBFCBO = dynamic_cast< BFCBO* > ( bfIter.getObject() );
	   if( pBFCBO )
       {
          pBFCBO->getField( idField, dstrFieldValue, idDataGroup, false);
	   }
   }
*/
   BFCBO::getField(idField, dstrFieldValue, idDataGroup, false );
}

//******************************************************************************
void TransCancellation::convertFields( const BFDataGroupId& idDataGroup, bool formattedReturn ) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getField"));   

   DString dstrFieldValue;
   BFObjIter bfIter( *this, idDataGroup, true );
   if( !bfIter.end() )
   {
	   BFCBO *pBFCBO = dynamic_cast< BFCBO* > ( bfIter.getObject() );
	   if( pBFCBO )
       {
		   int cnt = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
		   for( int i=0;i<cnt;i++)
		   {
				pBFCBO->getField( classFieldInfo[i].getFieldId(), dstrFieldValue, idDataGroup, false);
				setFieldNoValidate ( classFieldInfo[i].getFieldId(), dstrFieldValue, idDataGroup, false, false, true);
		   }
	   }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransCancellation.cpp-arc  $
// 
//    Rev 1.10   Mar 15 2005 16:29:42   Fengyong
// PET 1190 FN05 - Add TransId to convert fields
// 
//    Rev 1.9   Mar 15 2005 11:51:16   georgeet
// PET1190FN05 - fix get field problem 
// 
//    Rev 1.8   Mar 14 2005 15:50:06   georgeet
// PET1190 FN05 - Add version ans TransType to field info
// 
//    Rev 1.7   Mar 14 2005 15:23:06   georgeet
// PET1190 FN05 - Syncup with view 337, change non repeat view to repeat
// 
//    Rev 1.6   Mar 09 2005 13:30:56   Fengyong
// PET1190 FN04 - Batch trace number added
// 
//    Rev 1.5   Mar 08 2005 19:36:14   Fengyong
// PET1190 FN04 - If set TranStatus Deleted, then delete also dilution records
// 
//    Rev 1.4   Mar 08 2005 15:54:10   Fengyong
// PET1190 FN04 - set default value for fields
// 
//    Rev 1.3   Mar 08 2005 13:33:56   Fengyong
// PET1190 FN04 - Uncommon enhance code after DD sync up
// 
//    Rev 1.2   Mar 07 2005 14:00:16   Fengyong
// PET1190FN04 - accountableCode validation
// 
//    Rev 1.1   Mar 04 2005 16:56:22   Fengyong
// PET1190 FN04 - TranCancel tempary check in for other coder
// 
//    Rev 1.0   Mar 03 2005 18:34:50   Fengyong
// Initial revision.
*/
