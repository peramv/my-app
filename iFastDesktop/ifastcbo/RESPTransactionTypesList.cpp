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
// ^FILE   : RESPTransactionTypesList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPTransactionTypesList.hpp"
#include "RESPTransactionType.hpp"

#include <ifastdataimpl\dse_dstc0410_req.hpp>
#include <ifastdataimpl\dse_dstc0410_vw.hpp>
#include <ifastdataimpl\dse_dstc0410_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESP_TRANS_TYPES_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME		= I_( "RESPTransactionTypesList" );
   const I_CHAR * const NOT_REPORTED    = I_( "NR" );
   const I_CHAR * const REPORTED		= I_( "R" );
   const I_CHAR * const RED_CODES		= I_( "64,65" );
   const I_CHAR * const DEPOSIT_TYPES	= I_( "17" );

}


//******************************************************************************
RESPTransactionTypesList::RESPTransactionTypesList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), _requestData(ifds::DSTC0410_REQ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList( );
}


//******************************************************************************
RESPTransactionTypesList::~RESPTransactionTypesList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//********************************************************************************
SEVERITY RESPTransactionTypesList::init (const DString& dstrAccountNum,
										 const DString& dstrTransId,
										 const DString& dstrHistoryPending,
                                         const DString& dstrTrack,
                                         const DString& dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init( int, DString& )"));

	DString mgmtCoIdOut;

	_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	_requestData.setElementValue( ifds::Track, dstrTrack );
	_requestData.setElementValue( ifds::Activity, dstrPageName );
	_requestData.setElementValue( ifds::AccountNum, dstrAccountNum);
	_requestData.setElementValue( ifds::TransId, dstrTransId);
	_requestData.setElementValue( ifds::HistoryPending, dstrHistoryPending);
 
	ReceiveData( DSTC_REQUEST::RESP_TRANS_TYPES_INQUIRY, _requestData, ifds::DSTC0410_VW, DSTCRequestor( getSecurity(), true));
   
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RESPTransactionTypesList::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY RESPTransactionTypesList::doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
    pBase = new RESPTransactionType(*this );
    ((RESPTransactionType* )pBase)->initNew(idDataGroup );
      
	return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY RESPTransactionTypesList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   
   pObjOut = new RESPTransactionType( *this );
   ((RESPTransactionType* )pObjOut)->init(const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************************
void RESPTransactionTypesList::getSubstitionList(DString& transTypeSubList, const BFDataGroupId& idDataGroup)
{
	DString	dstrTransTypeDesc, dstrTransTypeDesc1;
	DString dstrTransRecId;
	DString dstrALL = I_("ALL");
	DString dstrAll = I_("All");
	DString dstrALLContrib = I_("ALLCONTR");
	DString dstrAllContrib = I_("All Contributions");
	

	BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
	BFObjIter iter1( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

	transTypeSubList = dstrALL + I_("=") + dstrAll + I_(";");
	transTypeSubList += dstrALLContrib + I_("=") + dstrAllContrib + I_(";");

	bool bHasDuplicate = false;
	int count = 0; 

	while( !iter.end() )
	{
		BFAbstractCBO* pObj = iter.getObject();
		if( pObj )
		{
			pObj->getField(ifds::TransTypeDesc, dstrTransTypeDesc,idDataGroup,false );
			pObj->getField(ifds::TransRecId, dstrTransRecId,idDataGroup,false );
			dstrTransTypeDesc.strip();

			count = 0;
			bHasDuplicate = false;

			iter1.begin();
			while( !iter1.end() )
			{
				BFAbstractCBO* pObj1 = iter1.getObject();
				if( pObj1 )
				{
					pObj1->getField(ifds::TransTypeDesc, dstrTransTypeDesc1,idDataGroup,false );
					dstrTransTypeDesc1.strip();

					if (dstrTransTypeDesc == dstrTransTypeDesc1)
					{
						count++;
						if (count > 1)
						{
							bHasDuplicate = true;
							iter1.removeObjectFromMap(true);
							break;
						}
					}
				}
				++iter1;
			} 

			if (!bHasDuplicate)
				transTypeSubList += dstrTransRecId + I_("=") + dstrTransTypeDesc + I_(";");	
		}
		++iter;
	}  
}

//*********************************************************************************************
void RESPTransactionTypesList::getDescStatHRDCInfo (DString& transTypeDesc,
									                DString& transferStatus,
									                DString& repHRDC,
									                const BFDataGroupId& idDataGroup)
{
	
	BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

   transferStatus = I_("1") ;
   repHRDC = NOT_REPORTED ;
   while( !iter.end() )
    {
		BFAbstractCBO* pObj = iter.getObject();

        if( pObj )
        {
			DString tmpRepHRDC;

            pObj->getField(ifds::TransRecId, transTypeDesc,idDataGroup,false );
            pObj->getField(ifds::TfrStat, transferStatus,idDataGroup,false );
            pObj->getField(ifds::RepHRDC, tmpRepHRDC,idDataGroup,false );

			repHRDC =  tmpRepHRDC == I_("N") ? NOT_REPORTED : REPORTED;
		
			break;
        }

        ++iter;
     }    
}

//*********************************************************************************************
SEVERITY RESPTransactionTypesList::getTransTypeInfo(const DString& dstrTransId, 
												    DString &dstrTransType,
												    DString &dstrRedCode,
												    DString &dstrDepositType,
												    const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTransTypeInfo" ) );

	DString	dstrTmpTransId;

	dstrTransType = NULL_STRING;
	dstrRedCode = NULL_STRING;
	dstrDepositType = NULL_STRING;

	BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

    while( !iter.end() )
    {
		BFAbstractCBO* pObj = iter.getObject();

        if( pObj )
        {
            pObj->getField(ifds::TransRecId, dstrTmpTransId,idDataGroup,false );
            dstrTmpTransId.strip();
           	
			if (dstrTransId == dstrTmpTransId)
			{
				pObj->getField(ifds::RedCode, dstrRedCode,idDataGroup,false );
				pObj->getField(ifds::DepositType, dstrDepositType,idDataGroup,false );
				pObj->getField(ifds::TransType, dstrTransType,idDataGroup,false );

				break;
			}
        }
        ++iter;
     }   

	 return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************************
SEVERITY RESPTransactionTypesList::isTransferStatusApplicable (const DString& dstrTransId, 
												               DString &dstrApplicable,
												    	       const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isTransferStatusApplicable" ) );

	DString	dstrTmpTransId;
	DString dstrRedCode;
	DString dstrDepositType;

	BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

    while( !iter.end() )
    {
		BFAbstractCBO* pObj = iter.getObject();

        if( pObj )
        {
            pObj->getField(ifds::TransRecId, dstrTmpTransId,idDataGroup,false );
            dstrTmpTransId.strip();
           	
			if (dstrTransId == dstrTmpTransId)
			{
				pObj->getField(ifds::RedCode, dstrRedCode,idDataGroup,false );
				pObj->getField(ifds::DepositType, dstrDepositType,idDataGroup,false );
				break;
			}
        }
        ++iter;
     }   

	if (DSTCommonFunctions::codeInList (dstrRedCode, RED_CODES) ||
	    DSTCommonFunctions::codeInList (dstrDepositType, DEPOSIT_TYPES))
	{
		dstrApplicable = I_("Y");
	}
	else
	{
		dstrApplicable = I_("N");
	}
	 
	return(GETCURRENTHIGHESTSEVERITY());
}


