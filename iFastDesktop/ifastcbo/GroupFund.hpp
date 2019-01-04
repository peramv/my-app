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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE      : GroupFund.hpp
// ^AUTHOR    : 
// ^DATE      : April 11, 2000
//
// ^CLASS     : GroupFund
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

namespace DBR
{
   extern CLASS_IMPORT const long DetlEffectiveDate;
};

class FundDetail;

class IFASTCBO_LINKAGE GroupFund : public MFCanBFCbo, private boost::noncopyable
{
public:
   GroupFund( BFAbstractCBO &parent );
   virtual ~GroupFund();

   SEVERITY init( const BFData &viewData );
   SEVERITY validateFndClsTradeType( const DString dstrTradeDate, const BFDataGroupId& idDataGroup );

   void getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;

private:
   void storeFundDetailPtr( const BFDataGroupId& idDataGroup = BF::HOST);
   FundDetail* m_pFundDetail;
   BFCBO * m_pFundMaster;
};

///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GroupFund.hpp-arc  $
//
//   Rev 1.13   Nov 29 2004 13:25:40   hernando
//PET1117 - Tuning Project - Revised use of FundDetailList.
//
//   Rev 1.12   Nov 14 2004 14:43:34   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.11   Mar 21 2003 18:12:38   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.10   Oct 09 2002 23:54:34   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.9   Aug 29 2002 12:52:36   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.8   22 May 2002 18:21:00   PURDYECH
//BFData Implementation
//
//   Rev 1.7   19 Mar 2002 13:17:16   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.6   25 Feb 2002 12:15:52   WINNIE
//logic of checking stop flag has been removed, no need to have transtype as parameter
//
//   Rev 1.5   03 May 2001 14:04:16   SMITHDAV
//Session management restructuring.
//
//   Rev 1.4   Feb 13 2001 17:14:22   FENGYONG
//compare tradedate to both fundmasterlist and funddetailslist and change && to || when validateFndClsTradeType
//
//   Rev 1.3   Sep 01 2000 14:42:20   ZHANGCEL
//Added ClientLocale parameter in getField()
//
//   Rev 1.2   May 04 2000 14:09:04   BUZILA
//changed tha way FunDetails is found. Now we are using getParent mechanism
//
//   Rev 1.1   Apr 14 2000 17:55:34   WINNIE
//Move validation to Groupfund and MFAccount CBO to allow other CBO to use the same method. Bug fix for NumOfDecimals function
//
//   Rev 1.0   Apr 13 2000 10:34:12   BUZILA
//Initial revision.
 * 
*/