#define IFASTCBO_DLL

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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : MFAccountHoldingList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/26/99
//
// ^CLASS    : MFAccountHoldingList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "mfaccountholdinglist.hpp"
#include "accountholdingsbycurrencylist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "fundmasterlist.hpp"
#include "funddetaillist.hpp"
#include <ifastdataimpl\dse_dstc0020_vw.hpp>
#include <ifastdataimpl\dse_dstc0020_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MFACCOUNT_HOLDINGS;
}

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "MFAccountHoldingList" );
   const I_CHAR *  SPACE= I_( " " );
}

namespace CND
{
   extern const long ERR_NO_FUNDS_FOR_ACCOUNT;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId FundCategory;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
}

//******************************************************************************
MFAccountHoldingList::MFAccountHoldingList( BFAbstractCBO &parent )
: _pFundMasterList ( NULL ),
  MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   getMgmtCo().getFundMasterList( _pFundMasterList );
}

//******************************************************************************
MFAccountHoldingList::~MFAccountHoldingList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY MFAccountHoldingList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccountHoldingList::init( const DString &accountNum,
                                     const DString &asofDate,
                                     const DString &fundCode,
                                     const DString &classCode,
												 const DString &activeOnly,
                                     const DString &dstrTrack,
                                     const DString &dstrPageName,
                                     const DString &accBalMode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0020_REQ);
   BFData *receivedData = new BFData(ifds::DSTC0020_VW);

   _accountNum = accountNum;
   _accountNum.strip();

   DString mgmtCoIdOut;

   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::AccountNum, accountNum); 
   queryData.setElementValue (ifds::AsofDate, asofDate, false, false); 
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);
   queryData.setElementValue (ifds::CalculateACB, I_("N"), false, false);
	queryData.setElementValue (ifds::ActiveOnly, activeOnly, false, false);
   queryData.setElementValue (ifds::FundCode, fundCode);
   queryData.setElementValue (ifds::ClassCode, classCode);
   queryData.setElementValue (ifds::ConvertAmount, I_("Y"), false, false);
   queryData.setElementValue (ifds::AccBalMode, accBalMode);

   ReceiveData ( DSTC_REQUEST::MFACCOUNT_HOLDINGS, 
                 queryData, 
                 *receivedData, 
                 DSTCRequestor (getSecurity()));

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY MFAccountHoldingList::init (BFData& InstData)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   createObjectForEachRepeat(InstData);
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY MFAccountHoldingList::initObject (const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&>(data), false, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MFAccountHoldingList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new MFAccountHoldingList((BFAbstractCBO&)(*this));
   ( ( MFAccountHoldingList* ) ( pObjOut ) )->initObject( const_cast<BFData&>(data));

   MFAccount *pMFAcc;
   DString dump (_accountNum);

   SEVERITY sevRtn = getWorkSession().getMFAccount (BF::HOST, dump, pMFAcc);
   if( WARNING > sevRtn )
   {
      AccountHoldingsByCurrencyList *pAccountHoldingsByCurrencyList;

      pMFAcc->getAccountHoldingsByCurrencyList (pAccountHoldingsByCurrencyList, BF::HOST);
      pAccountHoldingsByCurrencyList->createCurrencyObject( data, BF::HOST );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void MFAccountHoldingList::getField( const BFFieldId& idField, DString& strFieldValue, 
                                     const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );

   if( (idField == ifds::SettledValue || 
        idField == ifds::CombValueFundCurr /*|| -- SettledUnits does not need to be formated 
        idField == ifds::SettledUnits*/
       ) && formattedReturn)
   {
      DString currency, fundCode, classCode;
      getField( ifds::rxFundCode, fundCode, idDataGroup, true );
      getField( ifds::rxClassCode, classCode, idDataGroup, true );
      CurrencyClass::getFundCurrency( getWorkSession(), fundCode, classCode, currency );
      currency.strip();

      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( currency, strFieldValue, strFieldValue );
   }
   else if( (idField == ifds::rxFundCode) | (idField == ifds::rxClassCode) )
   {
      strFieldValue.upperCase();
   }
   else if ( (idField == ifds::rxOpenDate) || (idField == ifds::rxCloseDate))
   {
      DSTCommonFunctions::FormatDate( strFieldValue );
   }
}

//******************************************************************************
void MFAccountHoldingList::getStrKey (DString& strKey, const BFData *data)
{
   if (data)
   {
      DString strFund         = data->getElementValue( ifds::rxFundCode );
      DString strClass        = data->getElementValue( ifds::rxClassCode );
      DString dstrFundGroup   = data->getElementValue( ifds::FundGroup );
         
      getStrKey (strKey, dstrFundGroup.strip(), strFund.strip(), strClass.strip());
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}
//******************************************************************************
void MFAccountHoldingList:: getStrKey ( DString& dstKey, 
                                        const DString &dstrFundCategory, 
                                        const DString &dstFund, 
                                        const DString &dstClass)
{
   TRACE_METHOD (CLASSNAME, I_( "getStrKey" ));

   dstKey = NULL_STRING;   
   dstKey = dstrFundCategory + SPACE + dstFund + SPACE + dstClass;   
   dstKey.upperCase();
}

//******************************************************************************
bool MFAccountHoldingList::isFundInHoldings ( const DString &dstrFundCode, 
                                              const DString &dstrClassCode, 
                                              const BFDataGroupId &idDataGroup)
{
   DString dstrCmpFundCode, 
      dstrCmpClassCode;
   
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   while (!iter.end ()) 
   {
      iter.getObject()->getField (ifds::rxFundCode, dstrCmpFundCode, idDataGroup);
      iter.getObject()->getField (ifds::rxClassCode, dstrCmpClassCode, idDataGroup);
      if (( dstrFundCode == dstrCmpFundCode.strip() ) && ( dstrClassCode == dstrCmpClassCode.strip()))
         return true;
      ++iter;
   }
   return false;
}

//*********************************************************************************
bool MFAccountHoldingList::hasHeldGICFund(const BFDataGroupId& idDataGroup)
{
   DString dstrFundCode;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   FundMasterList *pFundMasterList;
   if (getMgmtCo().getFundMasterList(pFundMasterList) > WARNING)
   {
      return false;
   }
   while ( !iter.end () ) {
      iter.getObject()->getField ( ifds::rxFundCode, dstrFundCode, idDataGroup );
		dstrFundCode.strip();
		if( pFundMasterList->isGICFund(dstrFundCode) )
		{
			return true;			
		}     		
		++iter;
   }
	return false;
}
bool MFAccountHoldingList::hasNonAMSFunds(const BFDataGroupId& idDataGroup)
{
   bool retVal = false;
   DString dstrFundCode;
   DString dstrClassCode;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   FundDetailList *pFundDetailList = NULL;
   if (getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING && pFundDetailList)
   {
      while (!retVal && !iter.end()) 
      {
         iter.getObject()->getField ( ifds::rxFundCode, dstrFundCode, idDataGroup );
         iter.getObject()->getField ( ifds::rxClassCode, dstrClassCode, idDataGroup );
		   dstrFundCode.upperCase().strip();
         dstrClassCode.upperCase().strip();
		   if(!getWorkSession().isAMSFundClass(dstrFundCode, dstrClassCode, idDataGroup))
		   {
			   retVal = true;			
		   }     		
		   ++iter;
      }
   }
	return retVal;
}
//***********************************************************************************
double MFAccountHoldingList::getBalance( BFAbstractCBO* bfcbo,const BFDataGroupId& idDataGroup )
{
	DString dstrSettle,dstrUnsettle;
	bfcbo->getField ( ifds::SettledUnits, dstrSettle, idDataGroup );
   bfcbo->getField ( ifds::UnsettledUnits, dstrUnsettle, idDataGroup );
   double dBalance = DSTCommonFunctions::convertToDouble(dstrSettle) +
								DSTCommonFunctions::convertToDouble(dstrUnsettle);

	return dBalance;

}

//***********************************************************************************
double MFAccountHoldingList::getSettledFundBalanceForAmtType( const DString &dstrFundCode,
                                                              const DString &dstrClassCode,
								                                      const DString &dstrAmtType,
                                                              const BFDataGroupId &idDataGroup )
{	
	DString dstrSettledFundBalance = 0;

	BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

//walk the list, match the fund and class, 
//and retrive the settled value/units

      BFData matchCriteria;
      matchCriteria.setElementValue (ifds::rxFundCode,  dstrFundCode,  true );
      matchCriteria.setElementValue (ifds::rxClassCode, dstrClassCode, true );
      iter.positionOnNextMatch (matchCriteria, idDataGroup);
      if (!iter.end())
      {
         DString dstrLocalAmtType( dstrAmtType );         
         dstrLocalAmtType.upperCase();

         if ( dstrAmtType == I_("U") ) //units
         {
           iter.getObject()->getField (ifds::SettledUnits, dstrSettledFundBalance, idDataGroup, false);           
         }
         else //anything else
         {
           iter.getObject()->getField (ifds::SettledValue, dstrSettledFundBalance, idDataGroup, false);
         }
      }

	return DSTCommonFunctions::convertToDouble( dstrSettledFundBalance );
}


//***********************************************************************************
bool MFAccountHoldingList::hasHeldMultiCurrencyFund( const BFDataGroupId& idDataGroup )
{
   BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
	DString dstrFundCurr1,dstrFundCurr2, dstrSettle1,dstrUnSettle1, dstrSettle2, dstrUnSettle2;
	while ( !iter1.end () ) {
		BFAbstractCBO*  pcbo = iter1.getObject();
      pcbo->getField ( ifds::FundCurrency, dstrFundCurr1, idDataGroup,false );
		dstrFundCurr1.strip();
		DString dstrKey = iter1.getStringKey();
		if( getBalance( pcbo,idDataGroup ) != 0.0 ) // find first record with non 0.0 balance
		{
		   BFObjIter iter2( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
			iter2.positionByKey( dstrKey );
			++iter2;
			while( !iter2.end() )
			{
				BFAbstractCBO*  pcbo2 = iter2.getObject();
				pcbo2->getField ( ifds::FundCurrency, dstrFundCurr2, idDataGroup,false );
				dstrFundCurr2.strip();
				if( getBalance( pcbo2,idDataGroup ) != 0.0 && dstrFundCurr1 != dstrFundCurr2 ) 
				{
					return true;				
				}
				++iter2;
			}
		}
		++iter1;
   }
	return false;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MFAccountHoldingList.cpp-arc  $
 * 
 *    Rev 1.34   May 29 2007 12:13:26   jankovii
 * Incident #899142 - cannot place trade.
 * 
 *    Rev 1.33   Nov 24 2005 18:22:46   popescu
 * BPS Performance issue - change the name of the method to fix the signature 
 * 
 *    Rev 1.32   Nov 24 2005 13:22:36   popescu
 * BPS Performance issue - added FundCode/ClassCode to view 20 to improve performance.
 * 
 *    Rev 1.31   Nov 19 2005 15:52:12   popescu
 * BPS Performance issue - cached view call 20 and passed params fund/class in as params
 * 
 *    Rev 1.30   Sep 01 2005 13:19:52   AGUILAAM
 * PET1250_FN07_Fund Merge: support display of active only or all  holdings based on generic control
 * 
 *    Rev 1.29   Apr 12 2005 10:30:32   porteanm
 * PET1190 FN14 - Wire order redemption against unsettled units.
 * 
 *    Rev 1.28   Jan 13 2005 16:03:38   zhangcel
 * PTS Ticket 10037623 -- Bug fix for SettledUnit. It does not need to be formated
 * 
 *    Rev 1.27   Nov 25 2004 11:43:54   popescu
 * PET 1117/06, settle locations
 * 
 *    Rev 1.26   Nov 14 2004 14:50:04   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.25   May 11 2004 15:49:36   popescu
 * PET 985, FN 01, LSIF Trade Entry, added handy methods to fund master list, to check whether a fund is LSIF/Money Market, GIC
 * 
 *    Rev 1.24   Aug 11 2003 11:55:14   YINGBAOL
 * add mothod hasHeldGICFund,getBalance and hasHeldMultiCurrencyFund mothod
 * 
 *    Rev 1.23   Apr 22 2003 09:08:22   linmay
 * Ticket #PTS10016120, Sync up with Version 1.20.1.1
 * 
 *    Rev 1.22   Apr 15 2003 10:53:20   linmay
 * Sync up with 1.20.1.0
 * 
 *    Rev 1.21   Mar 21 2003 18:18:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.20   Feb 05 2003 17:16:28   HSUCHIN
 * added new method to check if fund is in holdings
 * 
 *    Rev 1.19   Jan 09 2003 17:20:46   HSUCHIN
 * minor fix to key
 * 
 *    Rev 1.18   Jan 09 2003 17:08:20   HSUCHIN
 * bug fix to getStrKey getting the FundGroup.  It now looks up FundMaster to get Fund Category instead of Fund Group
 * 
 *    Rev 1.17   Dec 19 2002 13:40:04   sanchez
 * Modified gotStrKey(DString& strKey, const BFData* data).  Special sorting for Viscount accounts.  use FundGroup and fundClass for sorting.
 * 
 *    Rev 1.16   Oct 09 2002 23:54:46   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 12:56:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   Jun 10 2002 17:03:36   KOVACSRO
 * Formatted versus unformatted.
 * 
 *    Rev 1.13   22 May 2002 18:29:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   28 Dec 2001 10:34:00   KOVACSRO
 * Changed CalculateACB field to "N"
 * 
 *    Rev 1.11   27 Dec 2001 16:57:10   KOVACSRO
 * no change (but we'll have to implement the logic for calculating ACB)
 * 
 *    Rev 1.10   11 May 2001 08:21:14   HSUCHIN
 * Sync up with EFan (1.7.1.1)
 * 
 *    Rev 1.9   03 May 2001 14:06:46   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Mar 12 2001 12:58:48   VASILEAD
 * Modified for FUNDcom release
 * 
 *    Rev 1.7   Jan 18 2001 16:05:40   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.6   Dec 18 2000 16:42:06   YINGZ
 * CHECK IN
 * 
 *    Rev 1.5   Nov 01 2000 15:30:12   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.4   Sep 01 2000 15:25:44   HUANGSHA
 * added pClientLocale in setField(...)
 * 
 *    Rev 1.3   May 04 2000 16:56:20   WINNIE
 * change CURRENCY_HPP to CURRENCYCLASS_HPP
 * 
 *    Rev 1.2   Apr 15 2000 15:28:28   WINNIE
 * fix for index set up in funtolist; fix allowable exchange edit chk; fix account balance ;
 * 
 *    Rev 1.1   Apr 07 2000 18:24:48   WINNIE
 * add index to get account fund class balance 
 * 
 *    Rev 1.0   Feb 15 2000 11:00:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Jan 05 2000 20:10:58   BUZILA
 * adding list flag
 * 
 *    Rev 1.9   Dec 12 1999 16:25:48   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/