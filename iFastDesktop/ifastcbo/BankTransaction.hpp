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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BankTransaction.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 03/30/2001
//
// ^CLASS    : BankTransaction
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\BankInstructions.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE BankTransaction : public BankInstructions
{
public:
   // X-structors
   BankTransaction( BFAbstractCBO &parent );
   virtual ~BankTransaction( void );

   SEVERITY init( const BFData& data, const DString& strTradeDate, const DString& strBankType );
   //void BankTransaction::init2( const DString& strDate );	
   void initNew( const DString& strTradeDate, const DString& strBankType, const BFDataGroupId& idDataGroup );

protected:
   virtual SEVERITY doValidateField( const BFFieldId& idField,
                                     const DString& strValue,
                                     const BFDataGroupId& idDataGroup );

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

private:
   //void setDefaultValues(const BFDataGroupId& idDataGroup,const DString& dstrDate);
   DString m_strTradeDate;
};

///#endif


/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankTransaction.hpp-arc  $
//
//   Rev 1.13   Nov 14 2004 14:29:08   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.12   Oct 19 2003 16:44:10   popescu
//CIBC, PET809, FN 13 banking work
//
//   Rev 1.11   May 22 2003 14:12:02   popescu
//Replaced name 'BankInstr' with 'BankInstructions'; 
//simplified child lists getters for the Shareholder object
//
//   Rev 1.10   Mar 21 2003 18:00:44   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.9   Oct 09 2002 23:54:06   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.8   Aug 29 2002 12:51:56   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.7   Jul 11 2002 13:40:34   KOVACSRO
//Added doApplyRelatedChanges.
//
//   Rev 1.6   Jul 05 2002 11:51:54   KOVACSRO
//Added BankType in init.
//
//   Rev 1.5   Jun 16 2002 16:59:00   KOVACSRO
//derived from BankInstr
//
//   Rev 1.4   22 May 2002 18:21:42   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:15:18   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   09 May 2001 15:01:18   HSUCHIN
//Sync up with SSB
//
//   Rev 1.1   03 May 2001 14:03:52   SMITHDAV
//Session management restructuring.
//
//   Rev 1.0   Apr 02 2001 16:54:58   YINGBAOL
//Initial revision.

 * 
 */
