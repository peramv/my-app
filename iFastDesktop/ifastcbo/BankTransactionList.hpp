
#error "This file is obsolete"
/*
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
//    Copyright 2001 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : BankTransactionList.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 03/30/01
//
// ^CLASS  : BankTransactionList
// ^PARENT : BFBase
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


class IFASTCBO_LINKAGE BankTransactionList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // Creators
   BankTransactionList( BFAbstractCBO &parent );
   virtual ~BankTransactionList( void );

   // Initialize function
   SEVERITY init( const DString& strTransId, const DString& strPendingRid, 
      const DString& strTransPending, const DString& dstrTradeDate,
      const DString& dstrTrack= I_("N"), const DString& dstrPageName = NULL_STRING );

protected:
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
   DString m_dstrTradeDate;
   DString m_strBankType;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankTransactionList.hpp-arc  $
//
//   Rev 1.11   Nov 14 2004 14:29:10   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.10   Oct 19 2003 16:44:14   popescu
//CIBC, PET809, FN 13 banking work
//
//   Rev 1.9   May 23 2003 10:04:18   popescu
//Part of bank instructions cleaning up process, moved the bank types into the ifastids project
//
//   Rev 1.8   Mar 21 2003 18:00:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 23:54:06   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Aug 29 2002 12:51:56   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   Jul 05 2002 11:52:14   KOVACSRO
//Added BankType
//
//   Rev 1.4   22 May 2002 18:21:42   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:15:20   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   09 May 2001 15:04:54   HSUCHIN
//Sync up with SSB
//
//   Rev 1.1   03 May 2001 14:03:52   SMITHDAV
//Session management restructuring.
//
//   Rev 1.0   Apr 02 2001 16:55:00   YINGBAOL
//Initial revision.
// 


*/



