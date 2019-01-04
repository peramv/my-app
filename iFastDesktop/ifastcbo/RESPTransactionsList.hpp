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
// ^FILE   : RESPTransactionsList.hpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 20/01/2000
//
// ^CLASS    : RESPTransactionsList
// ^SUBCLASS :
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

class RESPTransactionsDetails;

class IFASTCBO_LINKAGE RESPTransactionsList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   RESPTransactionsList( BFAbstractCBO &parent );
   virtual ~RESPTransactionsList( void );

   // Initialize function
   SEVERITY init ( const DString& dstrAccountNum, 
                   const DString& dstrHistoryPending, 
                   const DString& dstrTransId,
				   const DString& dstrTransType,
				   const DString& dstrRESPBenefId,
				   const DString& dstrRESPBenefName,
				   const DString& dstrFromDate,
				   const DString& dstrToDate,
				   const DString& dstrDepositType,
				   const DString& dstrRedCode,
                   const DString& dstrTfrStat,
				   const DString& dstrRepHRDC,
				   const BFDataGroupId& idDataGroup = BF::HOST);

   SEVERITY initNew (const DString& accountNum, const DString historyPending);

   SEVERITY getMore();

   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
   BFData _requestData; 
   DString _accountNum;
   BFDataGroupId _idDataGroup;
};

///#endif

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPTransactionsList.hpp-arc  $
 * 
 *    Rev 1.11   Aug 06 2010 14:05:02   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.10   May 13 2010 01:32:20   popescu
 * RESP-QESI fixes
 * 
 *    Rev 1.9   Mar 29 2010 23:01:20   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.8   Mar 29 2010 10:57:10   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.7   Nov 14 2004 14:52:28   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.6   Oct 09 2002 23:54:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Aug 29 2002 12:53:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 18:20:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:18:14   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   03 May 2001 14:04:46   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.1   Mar 22 2000 09:02:38   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.1   Feb 07 2000 11:02:28   PETOLESC
// Minor corrections and code cleaning.
 * 
 *
 */