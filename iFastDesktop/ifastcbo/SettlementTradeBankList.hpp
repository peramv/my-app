#error "This file is obsolete!"
//use SettlementTradeBankInstructionsList.hpp instead

//#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : SettlementTradeBankList.hpp
// ^AUTHOR : 
// ^DATE   : June 9, 2002
//
// ^CLASS  : SettlementTradeBankList
// ^PARENT : BFBase
//
// ^CLASS DESCRIPTION :
//******************************************************************************
/*
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class SettlementTrade;
class BankInstr;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE SettlementTradeBankList : public MFCanBFCbo, private boost::noncopyable
{
public:

   SettlementTradeBankList( BFAbstractCBO &parent );
   ~SettlementTradeBankList();

   SEVERITY getBankInstructions( const BFDataGroupId& idDataGroup );
   SEVERITY copyToSettlementTrade( SettlementTrade* pSettlementTrade, const BFDataGroupId& idDataGroup );
   SEVERITY removeBankInstr( const BFDataGroupId& idDataGroup );
   void getBankKey( DString& dstrKey, const BFDataGroupId& idDataGroup );
};

*/
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTradeBankList.hpp-arc  $
//
//   Rev 1.6   Nov 14 2004 14:54:22   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   Jun 10 2003 16:11:36   popescu
//Changed the SettlementTrade bank instructions files to match new design for bank instructions that are not on host
//
//   Rev 1.4   May 22 2003 14:13:10   popescu
//Replaced name 'BankInstr' with 'BankInstructions'; 
//simplified child lists getters for the Shareholder object
//
//   Rev 1.3   Mar 21 2003 18:24:22   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Oct 09 2002 23:55:00   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   Aug 29 2002 12:53:38   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.0   Jun 11 2002 21:34:28   HSUCHIN
//Initial revision.
*/
