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
// ^FILE   : FeeParamConfigList.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : Feb. 27, 2002
//
// ^CLASS    : FeeParamConfigList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0253_req.hpp>
#include <ifastdataimpl\dse_dstc0253_vw.hpp>
#include "feeparamConfigList.hpp"
#include "feeparamConfig.hpp"

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM_CONFIG_LIST;
}


namespace  
{
   const I_CHAR * const CLASSNAME = I_( "FeeParamConfigList" );  
   const I_CHAR * const IDI_CODE    = I_("CODE");  
   const I_CHAR * const ACCOUNT_LEVEL				= I_("ACCOUNT");
   const I_CHAR * const SYSTEM_LEVEL				= I_("SYSTEM");
   const I_CHAR * const FUND_SPONSOR            = I_("FDSPON");
   const I_CHAR * const FEEMODEL                = I_("FEEMODEL");
   const I_CHAR * const FNDBROKER               = I_("FNDBROKER");
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//*********************************************************************************
FeeParamConfigList::FeeParamConfigList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   setVersionable( false );

}

//*********************************************************************************
FeeParamConfigList::~FeeParamConfigList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY FeeParamConfigList::init( const DString& dstrTrack,
                                   const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   BFData requestData(ifds::DSTC0253_REQ);
	DString mgmtCoIdOut;
	requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut ));
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName); 

   AsyncReceiveData (DSTC_REQUEST::FEE_PARAM_CONFIG_LIST, 
                     requestData, 
                     ifds::DSTC0253_VW, 
                     DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY FeeParamConfigList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );


   pObjOut =  new FeeParamConfig( *this );
   ((FeeParamConfig* )pObjOut )->init(data);

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
void FeeParamConfigList::getStrKey( DString &strKey, const BFData *data )
{
	DString dstrFeeCode, dstrLevel;
	if (data)
	{
		dstrFeeCode = data->getElementValue(I_("FeeCode"));
		dstrFeeCode.strip().upperCase().stripLeading('0');
		dstrFeeCode.padLeft(2,'0');
		dstrLevel = data->getElementValue(I_("FeeLevel"));
		strKey = dstrFeeCode + dstrLevel.strip().upperCase();
	}
	else 
	{
		BFCBO::getStrKey( strKey , NULL );
	}

}
//************************************************************************************
void FeeParamConfigList::buildKeyForSystemLevel( const DString& dstrFeeCode,DString &strKey )
{
	DString dstrTemp(dstrFeeCode);
	dstrTemp.strip().upperCase().stripLeading('0');
	dstrTemp.padLeft(2,'0');
	strKey = dstrTemp + SYSTEM_LEVEL;
}
//************************************************************************************
void FeeParamConfigList::buildKeyForAccountLevel( const DString& dstrFeeCode,DString &strKey )
{
	DString dstrTemp(dstrFeeCode);
	dstrTemp.strip().upperCase().stripLeading('0');
	dstrTemp.padLeft(2,'0');
	strKey = dstrTemp + ACCOUNT_LEVEL;
}

//************************************************************************************
void FeeParamConfigList::buildKeyForFundSponsorLevel( const DString& dstrFeeCode,DString &strKey )
{
   DString dstrTemp(dstrFeeCode);
	dstrTemp.strip().upperCase().stripLeading('0');
	dstrTemp.padLeft(2,'0');
	strKey = dstrTemp + FEEMODEL;
}

//************************************************************************************
void FeeParamConfigList::buildKeyForFundBrokerLevel( const DString& dstrFeeCode,DString &strKey )
{
	DString dstrTemp(dstrFeeCode);
	dstrTemp.strip().upperCase().stripLeading('0');
	dstrTemp.padLeft(2,'0');
	strKey = dstrTemp + FNDBROKER;
}

//********************************************************************************
// FeeCode substitute list should be always at SYSTEM LEVEL except FeeCode = 180.
//

SEVERITY FeeParamConfigList::getFeeCodeList( DString &dstrFeeCodeList, const DString & Level )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeCodeList" ) );

	DString dstrCode, dstrDes, dstrLevel;
	dstrFeeCodeList = NULL_STRING;
    std::set<DString> setFeeCode;

	BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();
	while( !iter.end() )
	{
		iter.getObject()->getField( ifds::FeeCode,dstrCode,BF::HOST,false );
		iter.getObject()->getField( ifds::FeeCode,dstrDes,BF::HOST,true );
		iter.getObject()->getField( ifds::FeeLevel,dstrLevel,BF::HOST,true );
		
		dstrCode.strip().upperCase();
		if ( dstrLevel == Level )
		{
			if ( setFeeCode.find ( dstrCode ) == setFeeCode.end() )
			{
				setFeeCode.insert( dstrCode );
				dstrDes.strip();
				dstrFeeCodeList += dstrCode + I_("=") + dstrDes + I_(";");  
			}
		}

		else if ( (Level == ACCOUNT_LEVEL && dstrLevel == SYSTEM_LEVEL ) )
		{
			if ( setFeeCode.find ( dstrCode ) == setFeeCode.end() )
			{
				setFeeCode.insert( dstrCode );
				dstrDes.strip();
				dstrFeeCodeList += dstrCode + I_("=") + dstrDes + I_(";");  
			}
		}

      else if( Level == FEEMODEL && dstrLevel == Level )
      {
			if ( setFeeCode.find ( dstrCode ) == setFeeCode.end() )
			{
				setFeeCode.insert( dstrCode );
				dstrDes.strip();
				dstrFeeCodeList += dstrCode + I_("=") + dstrDes + I_(";");  
			}
      }

		++iter;
	}

	return(GETCURRENTHIGHESTSEVERITY());

}

//********************************************************************************
// FeeCode substitute list should be always at SYSTEM LEVEL except FeeCode = 180.
//

SEVERITY FeeParamConfigList::getFeeCodeList( DString &dstrFeeCodeList, const DString & Level, const DString & dstrFundGroupType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeCodeList" ) );

	DString dstrCode, dstrDes, dstrLevel, dstrType;
	dstrFeeCodeList = NULL_STRING;
    std::set<DString> setFeeCode;

	BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );		
    iter.begin();
	while( !iter.end() )
	{
		iter.getObject()->getField( ifds::FeeCode,dstrCode,BF::HOST,false );
		iter.getObject()->getField( ifds::FeeCode,dstrDes,BF::HOST,true );
		iter.getObject()->getField( ifds::FeeLevel,dstrLevel,BF::HOST,true );
        iter.getObject()->getField( ifds::FundGroupType,dstrType,BF::HOST,true );
		
		dstrCode.strip().upperCase();
		if ( dstrLevel == Level && dstrType == dstrFundGroupType )
		{
			if ( setFeeCode.find ( dstrCode ) == setFeeCode.end() )
			{
				setFeeCode.insert( dstrCode );
				dstrDes.strip();
				dstrFeeCodeList += dstrCode + I_("=") + dstrDes + I_(";");  
			}
		}

		++iter;
	}

	return(GETCURRENTHIGHESTSEVERITY());

}

//****************************************************************************
//    get possible distinct fee code in the system
//    The method will be used to retrieve default set up for fee paramters
//    The available feecode will be return in the feeCodList
//    Yingbao added, March 18,2005 
//
bool FeeParamConfigList::getAllFeeCodeInTheList(DString& feeCodList )
{
   DString dstrCode;   
   feeCodList=NULL_STRING;
   std::set<DString> feeCodeSet;

	BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );		
	while( !iter.end() )
	{
		iter.getObject()->getField( ifds::FeeCode,dstrCode,BF::HOST,false );
      if ( feeCodeSet.find ( dstrCode ) == feeCodeSet.end() )
		{
			feeCodeSet.insert( dstrCode );      
			feeCodList += dstrCode +  I_(";");  
      }
		++iter;
	}
   return ( feeCodList != NULL_STRING );
}

SEVERITY FeeParamConfigList::getFeeParamConfig(FeeParamConfig*& pFeeParamConfig, DString& dstrFeeCode, 
                                               const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeParamConfig" ) );

   pFeeParamConfig = NULL;
   DString dstrLevel;
	BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	DString dstrFeeCodeComp;
	for (;!iter.end();++iter)
	{
		(iter.getObject() )->getField(ifds::FeeCode, dstrFeeCodeComp, idDataGroup,false);
		(iter.getObject() )->getField(ifds::FeeLevel, dstrLevel, idDataGroup,false );

		if (dstrFeeCodeComp != dstrFeeCode )
		{
			continue;
		}
		else 
		{
			if ( dstrLevel.upperCase() == SYSTEM_LEVEL )
			{
				pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
				break;
			}
			else
			{
				pFeeParamConfig = dynamic_cast <FeeParamConfig*>(iter.getObject());
			}
		}
	}

   return(GETCURRENTHIGHESTSEVERITY());
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParamConfigList.cpp-arc  $
// 
//    Rev 1.17   24 Jul 2008 12:00:46   popescu
// Incident - 1190617 - set all the data init calls to be asynch
// 
//    Rev 1.16   Mar 21 2005 10:19:18   yingbaol
// Incident240192: Speed up getDefault fee parameter
// 
//    Rev 1.15   Jan 29 2005 16:34:36   popescu
// PTS 10038434, handling of  two new fees (114 and 115) existing in pending trades, part of aggregated orders
// 
//    Rev 1.14   Dec 10 2004 14:35:24   hernando
// PET1117 - Recovered version feature.
// 
//    Rev 1.13   Nov 23 2004 17:25:02   Fengyong
// PET1117FN54 - adjustment after first day intergretion test
// 
//    Rev 1.12   Nov 18 2004 13:28:02   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.11   Nov 14 2004 14:40:18   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Nov 04 2004 17:37:30   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.9   Nov 02 2004 10:57:54   FENGYONG
// PTS10035397 - FUNDSPONSOR - FEEMODEL
// 
//    Rev 1.8   Sep 09 2004 10:59:18   FENGYONG
// filter feetype
// 
//    Rev 1.7   Aug 10 2004 11:24:16   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.6   Nov 19 2003 11:02:46   linmay
// modified getFeeCodeList for PTS#10024210
// 
//    Rev 1.5   Aug 30 2003 16:07:10   YINGBAOL
// AMS Fee Calculation enhancement
// 
//    Rev 1.4   Aug 08 2003 15:28:58   linmay
// PTS #10020525, modified getFeeCodeList()
// 
//    Rev 1.3   Jun 26 2003 11:00:56   linmay
// added FeeLevel as string key for Pinnacle Flat Fee
// 
//    Rev 1.2   Mar 21 2003 18:09:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Mar 10 2003 14:46:38   linmay
// created
// 
//    Rev 1.0   Mar 06 2003 13:52:18   linmay
// Initial Revision
// 
*/
