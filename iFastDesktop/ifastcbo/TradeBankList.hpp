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
//******************************************************************************
//
// ^FILE   : TradeBankList.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : March 2, 2000
//
// ^CLASS  : TradeBankList
// ^PARENT : BFBase
//
// ^CLASS DESCRIPTION :
//    
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

class Trade;

class IFASTCBO_LINKAGE TradeBankList : public MFCanBFCbo, private boost::noncopyable
{
public:
   SEVERITY checkCustomBank( const BFDataGroupId& idDataGroup, const DString& dstBankKey, const Trade* pTrade );
   SEVERITY clearCustomBank( const BFDataGroupId& idDataGroup );
   SEVERITY refreshList( const BFDataGroupId& idDataGroup, 
                         const DString&  dstShrNum, 
                         const DString&  dstAcctNum, 
                         const DString&  dstSettleCurrency, 
                         const DString&  dstTransType, 
                         const DString& dstrTrack= I_("N"),
                         const DString& dstrPageName = NULL_STRING );

   SEVERITY getPendingTradeBank( const BFDataGroupId& idDataGroup, 
                                 const Trade* pTrade,
                                 const DString& dstSettleCurrency, 
                                 const DString& dstrTrack= I_("N"), 
                                 const DString& dstrPageName = NULL_STRING );               

   SEVERITY refreshList( const BFDataGroupId& idDataGroup );
   // X-structors
   TradeBankList( BFAbstractCBO &parent );
   //this will NOT create a custom bank; it gets a pointer to an already existing one
   void getCustomBank(BankInstructions*& pBankInstructionsOut, const BFDataGroupId& idDataGroup );
   virtual ~TradeBankList();

   // Initialize function
   SEVERITY init( const DString&  shareholderNum );
   SEVERITY init();

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );
   void setObjectFlags( const BFObjectKey & objKey, long& lStateFlags, long& lGroupFlags );

private:
   void getAcctUsageCode ( const DString& dstrTransPayType, DString& dstrAcctUseCode );
   DString m_dstSettleCurrency;
   DString m_dstShrNum;
   DString m_dstAcctNum;
   DString m_dstTransType;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeBankList.hpp-arc  $
 * 
 *    Rev 1.20   Nov 14 2004 14:57:50   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.19   May 22 2003 14:13:40   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.18   Mar 21 2003 18:27:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Oct 09 2002 23:55:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.16   Aug 29 2002 12:53:54   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.15   Jun 13 2002 17:26:48   KOVACSRO
 * Passing a Trade pointer (2) - for pending trade
 * 
 *    Rev 1.14   Jun 07 2002 17:38:44   KOVACSRO
 * Passing a trade pointer rather than several strings.
 * 
 *    Rev 1.13   22 May 2002 18:19:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   19 Mar 2002 13:18:56   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.11   Jul 04 2001 11:10:02   ZHANGCEL
 * Sync up with 1.8.1.4
 * 
 *    Rev 1.10   11 May 2001 10:52:10   HSUCHIN
 * Sync up with SSB (1.8.1.3)
 * 
 *    Rev 1.9   03 May 2001 14:05:04   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Jan 18 2001 16:13:04   YINGBAOL
 * add etrack
 * 
 *    Rev 1.7   Dec 05 2000 14:16:10   OLTEANCR
 * bug fix
 * 
 *    Rev 1.6   Dec 05 2000 11:40:32   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.5   Sep 06 2000 14:50:14   YINGBAOL
 * change sync.
 * 
 *    Rev 1.4   May 25 2000 14:14:10   BUZILA
 * added a new refresh function and some new data members
 * 
 *    Rev 1.3   May 02 2000 10:30:44   BUZILA
 * m3
 * 
 *    Rev 1.2   Mar 30 2000 09:59:08   BUZILA
 * Trade Banking changes
 * 
 *    Rev 1.1   Mar 20 2000 09:29:20   BUZILA
 * temp
 * 
 *    Rev 1.0   Mar 08 2000 16:49:04   BUZILA
 * Initial revision.
 * 
*/