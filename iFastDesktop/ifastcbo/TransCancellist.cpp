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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TransCancellist.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : TransCancellist 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "transcancellist.hpp"

#include "transcancel.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0337_req.hpp>
#include <ifastdataimpl\dse_dstc0337_vw.hpp>
#include <ifastdataimpl\dse_dstc0127_req.hpp>
#include <ifastdataimpl\dse_dstc0127_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANS_CANCEL;
   extern CLASS_IMPORT const DSTCRequest TRANS_NUM;
}

namespace  
{
   const I_CHAR * const CLASSNAME    = I_( "TransCancellist");  
}


namespace CND
{
   //extern const long ERR_DATA_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
   extern const long WARN_CASH_DIVIDEND_PAID_AFTER;
}
namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}, 
};
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //Field DD Id,                State Flags,                        Group Flags
   { ifds::AccountNum,             BFCBO::NONE,                           0 },
   { ifds::TransId,                BFCBO::NONE,                           0 },   
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );
static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//*********************************************************************************
TransCancellist::TransCancellist( BFAbstractCBO &parent ) : MFCanBFCbo( parent )
,newCancellation (false)
,_transNum (NULL_STRING)
,_cashDivPaidAfter (NULL_STRING)
,_pRequestData (NULL)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   setObjectAsList();
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL );   
}

//*********************************************************************************
TransCancellist::~TransCancellist()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}

//*********************************************************************************
SEVERITY TransCancellist::init ( const DString &transNum,	
                                 const DString& cashDivPaidAfter,
                                 const BFDataGroupId &idDataGroup, 
                                 const DString &dstrTradeDate,
                                 const DString &dstrFundCode,
                                 const DString &dstrClassCode,
                                 const DString &dstrSearchType,
                                 const DString &dstrTranStatus,
                                 const DString &dstrAdjustType,
                                 const DString &dstrTradeAdjustId, 
                                 const DString &dstrSettleDate,
                                 const DString &dstrTransType,
                                 const DString &dstrTrack, /*=I_("N")*/
                                 const DString &dstrPageName /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

// receive data from back end    
   _transNum         = transNum;
   _cashDivPaidAfter = cashDivPaidAfter;
   _dstrTradeDate    = dstrTradeDate;
   _dstrFund         = dstrFundCode;
   _dstrClass        = dstrClassCode;
   _dstrSettleDate   = dstrSettleDate;
   _dstrTransType    = dstrTransType;

   DString dstrLocalSearchType = dstrSearchType;
   if ( !dstrTradeAdjustId.empty() )
		dstrLocalSearchType = I_( "TradeAdjustID" );
   
   DString mgmtCoIdOut;	
   
   _pRequestData = new BFData (ifds::DSTC0337_REQ);

	_pRequestData->setElementValue( ifds::CompanyId,     getMgmtCoId( mgmtCoIdOut ) );
	_pRequestData->setElementValue( ifds::Track,         dstrTrack );
	_pRequestData->setElementValue( ifds::Activity,      dstrPageName );
	_pRequestData->setElementValue( ifds::NextKey,       NULL_STRING );
	_pRequestData->setElementValue( ifds::TransNum,      transNum);
	_pRequestData->setElementValue( ifds::TradeDate,     dstrTradeDate );
	_pRequestData->setElementValue( ifds::FundCode,      dstrFundCode);
	_pRequestData->setElementValue( ifds::ClassCode,     dstrClassCode);
	_pRequestData->setElementValue( ifds::SearchType,    dstrLocalSearchType );
	_pRequestData->setElementValue( ifds::TranStatus,    dstrTranStatus);
	_pRequestData->setElementValue( ifds::AdjustType,    dstrAdjustType);
	_pRequestData->setElementValue( ifds::TradeAdjustID, dstrTradeAdjustId );

	if( ReceiveData ( DSTC_REQUEST::TRANS_CANCEL, 
                     *_pRequestData, 
						   ifds::DSTC0337_VW, 
						   DSTCRequestor (getSecurity(), false, true)) >= WARNING)
	{
		if ( dstrSearchType != NULL_STRING )
		{
			newCancellation = false;
		}
		else
		{
			int count = CONDITIONCOUNT();
			Condition *c = NULL;
			for(int i = 0; i < count; i++)
			{
				c = GETCONDITION (i);
				int condCode = c->getCode();
				if (condCode == CND::ERR_DATA_NOT_FOUND)
				{
					CLEARCONDITION (i)
					newCancellation = true;
					break;
				}
			}
		}
	}	
	if (newCancellation)
	{
		BFObjectKey objKey (transNum, idDataGroup);

      getNewListItem (objKey);
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransCancellist::getTransCancel ( const DString &transNum, 
                                           TransCancel *&pTransCancel, 
                                           const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTransCancel" ) );

	pTransCancel = NULL;

	BFObjIter iter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false);

   while (!iter.end())
	{				
   	DString transNum_;

      iter.getObject ()->getField (ifds::TransNum, transNum_, idDataGroup, false);
		if (transNum_ == transNum)
		{
			pTransCancel = dynamic_cast <TransCancel*> (iter.getObject ());
			break;
		}
      ++iter;
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY TransCancellist::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   if (isUpdated (true) && _cashDivPaidAfter == I_("Y"))
   {
      ADDCONDITIONFROMFILE (CND::WARN_CASH_DIVIDEND_PAID_AFTER);
   }  
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY TransCancellist::doCreateObject (const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doCreateObject" ));

   pObjOut =  new TransCancel( *this );
   ((TransCancel* )pObjOut )->init( data, _dstrTradeDate, _dstrSettleDate );
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY TransCancellist::doCreateNewObject (BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doCreateNewObject" ));
   TransCancel* pTransCancel = new TransCancel (*this);
   pTransCancel->setObjectNew ();
   pTransCancel->initNew( idDataGroup, _transNum, _dstrTradeDate, _dstrSettleDate, _dstrTransType );
   pBase = pTransCancel;
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY TransCancellist::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if (doMoreRecordsExist())
   {
      const DSTCSecurity* pSecurity =  dynamic_cast<const DSTCSecurity *>(getSecurity());
      ReceiveData ( DSTC_REQUEST::TRANS_CANCEL, 
                    *_pRequestData, 
                    ifds::DSTC0337_VW, 
                    DSTCRequestor (getSecurity(), false));
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY TransCancellist::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (idField == ifds::AccountNum || idField == ifds::TransId)
   {
      setUpdatedFlag( idField, idDataGroup, false );				  
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransCancellist.cpp-arc  $
// 
//    Rev 1.15   Nov 03 2010 04:17:24   kitticha
// PET0165541 FN03 - QESI Phase3.
// 
//    Rev 1.14   Oct 29 2010 05:39:42   kitticha
// PET0165541 FN03 - QESI Phase3.
// 
//    Rev 1.13   Nov 14 2006 16:49:42   porteanm
// Incident 676881 - Pass TransType to 338 (TransCancel).
// 
//    Rev 1.12   Mar 10 2006 13:54:02   porteanm
// Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
// 
//    Rev 1.11   Mar 02 2006 17:34:48   ZHANGCEL
// PET1334 - FN01 -- ESG Settlement enhancement
// 
//    Rev 1.10   Dec 29 2005 13:07:42   porteanm
// Incident 501804 - Allow multiple Bulk Cancellation Instructions for the same Trade Date/Fund/Class.
// 
//    Rev 1.9   Nov 28 2005 10:23:32   popescu
// PET 1286 FN01 - Bulk Cancellation - fixed the 'More' button
// 
//    Rev 1.8   Nov 11 2005 16:57:24   ZHANGCEL
// PET 1286 FN01 - Make it works properly for Cancellation Instruction
// 
//    Rev 1.7   Nov 09 2005 19:53:34   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.6   Nov 08 2005 19:16:38   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.5   Nov 04 2005 11:01:30   ZHANGCEL
// PET 1286  FN01 -- Add TradeDate and CancellationInstr search related issue
// 
//    Rev 1.4   Sep 01 2005 14:02:22   popescu
// Incident# 388632 - trans cancel screen code overhaul
// 
//    Rev 1.3   Jul 08 2005 09:34:08   Yingbaol
// PET1235,FN01:transaction cancellation rebook
// 
//    Rev 1.2   Apr 01 2005 13:43:12   Fengyong
// PET 1190 FN 05 - add dovalidateall
// 
//    Rev 1.1   Mar 16 2005 16:44:42   Fengyong
// PET1190 FN05 - remove getstrKey function
// 
//    Rev 1.0   Mar 16 2005 15:38:14   Fengyong
// Initial revision.
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
