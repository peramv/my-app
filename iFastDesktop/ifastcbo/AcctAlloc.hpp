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
//    Copyright 2002 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctAlloc.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : AcctAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all account allocations
//
//******************************************************************************

#ifndef ABSTRACTALLOC_HPP
   #include <ifastcbo\AbstractAlloc.hpp>
#endif 

class FundAllocList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

namespace
{
   const I_CHAR * const ACCTALLOC           = I_("AcctAlloc");
   const I_CHAR * const FUNDALLOCATIONLIST  = I_("FundAllocationList");

}

namespace CND
{
   extern IFASTCBO_LINKAGE const I_CHAR *IFASTCBO_CONDITION;
}


class IFASTCBO_LINKAGE AcctAlloc : public AbstractAlloc
{
public:
   // X-structors
   AcctAlloc( BFAbstractCBO &parent );
   virtual ~AcctAlloc( void );

   template <class X> SEVERITY getFundAllocationList(X *&pFundAllocList, const BFDataGroupId& idDataGroup, bool bCreate = true, bool bGetDefault = true)
   {
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, ACCTALLOC, I_("getFundAllocationList") );

      pFundAllocList = dynamic_cast<X *>( BFCBO::getObject( FUNDALLOCATIONLIST, idDataGroup ) );
      if( !pFundAllocList && bCreate )
      {
         pFundAllocList = new X( *this );
         setObject( pFundAllocList, FUNDALLOCATIONLIST, OBJ_ACTIVITY_NONE, idDataGroup ); 
         pFundAllocList->initNew( idDataGroup, bGetDefault );
      }
      return(GETCURRENTHIGHESTSEVERITY());
   }

   SEVERITY getFundAllocationList(FundAllocList *&pFundAllocList, const BFDataGroupId& idDataGroup, bool bCreate, bool bGetDefault);
   SEVERITY hasInternationalWireFundAlloc(const DString& strSettleCurrency, const DString& strCountryCode,
                                          bool &bIsInternationalWire, const BFDataGroupId& idDataGroup);
protected:

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY getMFAccount( MFAccount *&pAcctOut, const BFDataGroupId& idDataGroup );
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY setAllocFields(const BFDataGroupId& idDataGroup);

private :

   SEVERITY validateAccountNum( const DString& strValue, const BFDataGroupId& idDataGroup ) ;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctAlloc.hpp-arc  $
//
//   Rev 1.7   Mar 21 2003 17:55:42   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:53:56   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:51:34   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   Jun 07 2002 17:20:34   KOVACSRO
//Added International Wire .
//
//   Rev 1.3   22 May 2002 18:21:58   PURDYECH
//BFData Implementation
//
//   Rev 1.2   08 May 2002 16:31:28   KOVACSRO
//More implementation.
//
//   Rev 1.1   12 Apr 2002 16:59:54   KOVACSRO
//More implementation.
 * 
 *
*/