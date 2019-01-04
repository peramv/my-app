#pragma once





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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DateValidation.hpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : May 5,2000
//
// ^CLASS    : DateValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Date Validation
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class DateValidation;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DateValidation : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey ( const DString &validationType,
                          const DString &tradeDate,
                          const DString &settleDate,
                          const DString &depositDate,
                          const DString &valueDate,
                          const DString &transType,
                          const DString &payType,
                          const DString &broker,
                          const DString &fundCode,
                          const DString &classCode,
                          const DString &toFund,
                          const DString &toClass,
                          const DString &orderType,
                          const DString &dealDate,
                          const DString &dealTime,
                          const DString &settleCurrency,
                          const DString &amount,
                          const DString &amountType,
                          DString &strKey,
                          const DString &AccountNum   = NULL_STRING,
                          const DString &AccountNumTo = NULL_STRING,
                          const DString &fromCurrency = NULL_STRING,
                          const DString &toCurrency   = NULL_STRING,
                          const DString &settleInDate = NULL_STRING,
                          const DString &valuationDt  = NULL_STRING,
                          const DString &dstrNetworkID = NULL_STRING,
						  const DString &tradeInDate = NULL_STRING,
						  const DString &valuationInDate = NULL_STRING
                        );

public:
   DateValidation (BFAbstractCBO &parent);
   virtual ~DateValidation();

   SEVERITY init();
   SEVERITY init ( const DString &validationType,
                   const DString &tradeDate,
                   const DString &settleDate,
                   const DString &depositDate,
                   const DString &valueDate,
                   const DString &transType,
                   const DString &payType,
                   const DString &broker,
                   const DString &fundCode,
                   const DString &classCode,
                   const DString &toFund,
                   const DString &toClass,
                   const DString &orderType,
                   const DString &dealDate,
                   const DString &dealTime,
                   const DString &settleCurrency,
                   const DString &amount,
                   const DString &amountType,   
                   const DString &settleInDate,
                   const DString &brokerTo,
                   const DString &accountNum   = NULL_STRING,
                   const DString &accountNumTo = NULL_STRING,
                   const DString &fromCurrency = NULL_STRING,
                   const DString &toCurrency   = NULL_STRING,
                   const DString &dstrTrack    = I_("N"),
                   const DString &dstrPageName = NULL_STRING,
                   const DString &valuationDt  = NULL_STRING,
				   const DString &dstrNetworkID = NULL_STRING,
				   const DString &tradeInDate = NULL_STRING,
				   const DString &valuationInDate = NULL_STRING
                 );
   void getField ( const BFFieldId &idField, 
                   DString &strValue, 
                   const BFDataGroupId &idDataGroup, 
                   bool formattedReturn  = false
                 ) const;
   SEVERITY addConditions ( const DString &validationType,
                            const BFDataGroupId &idDataGroup,
							const BFFieldId &idField,
                            CONDITIONVECTOR *&pConditionVector
                          );
protected:
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DateValidation.hpp-arc  $
// 
//    Rev 1.25   Jan 20 2012 15:39:06   wp040027
// P0188394_Performance Fees - Order Entry
// 
//    Rev 1.24   Mar 11 2008 20:02:22   daechach
// PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
// 
//    Rev 1.23   Sep 05 2007 14:41:16   jankovii
// IN #953708 - Unable to change Settle Out and Settle In dates at the same time.
// 
//    Rev 1.22   Mar 30 2007 14:04:14   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.20   Mar 21 2007 13:23:42   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.19   Jul 06 2005 11:49:16   hernando
// PET1250 FN01 - Added AccountNum.
// 
//    Rev 1.18   Jan 06 2005 17:21:02   popescu
// PTS 10037460 , Date validation object should add the conditions on the condition vector
// 
//    Rev 1.17   Dec 14 2004 17:39:08   popescu
// PET 1117/06/56 added validation for trade cut-off date
// 
//    Rev 1.16   Nov 14 2004 14:30:18   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.15   Nov 04 2004 17:37:22   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.14   Mar 21 2003 18:02:26   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.13   Oct 09 2002 23:54:10   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.12   Sep 27 2002 14:53:54   KOVACSRO
// 1. Added isChanged()
// 2.Cleanup
// 
//    Rev 1.11   Aug 29 2002 12:52:06   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.10   Jun 07 2002 17:34:50   KOVACSRO
// Added ValueDate
// 
//    Rev 1.9   22 May 2002 18:21:28   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   19 Mar 2002 13:15:30   PURDYECH
// Use #pragma once as include guard
// Remove compile time "including..." message
// 
//    Rev 1.7   03 May 2001 14:03:58   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.6   Feb 13 2001 16:22:04   HSUCHIN
// added virtual function donotifyResponse for async receivedata
// 
//    Rev 1.5   30 Jan 2001 15:17:28   PURDYECH
// Changed the signature of the init method with loads of const DString arguments so that it takes references
// 
//    Rev 1.4   Jan 18 2001 16:11:52   YINGBAOL
// add etrack
// 
//    Rev 1.3   Jan 12 2001 13:09:48   WINNIE
// new parameters for request related to transfer/exchange
// 
//    Rev 1.2   Dec 14 2000 16:19:24   JANKAREN
// new redemption logic for FeeCurrency and EffectiveDate
// 
//    Rev 1.1   Sep 01 2000 15:26:44   HUANGSHA
// added pClientLocale in setField(...)
// 
//    Rev 1.0   May 11 2000 10:24:48   WINNIE
// Initial revision.
*/