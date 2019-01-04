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
// ^FILE   : AcctAllocList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : AcctAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all the account allocation lists
//
//******************************************************************************

#include <ifastcbo\abstractalloclist.hpp>

class AcctAlloc;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AcctAllocList : public AbstractAllocList
{
public:
   // X-structors
   AcctAllocList( BFAbstractCBO &parent );
   virtual ~AcctAllocList( void );

   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     bool bGetDefault = true,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY clearAllocations( const BFDataGroupId& idDataGroup );
   template <class X> SEVERITY getAccountAllocation(const DString& dstrAccountNum,
                                                    X*& pAcctAlloc,
                                                    const BFDataGroupId& idDataGroup)
   {
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clearAllocations" ) );

      pAcctAlloc = NULL;
      DString strAccNumCopy(dstrAccountNum);
      if( strAccNumCopy.strip().stripLeading('0').empty() )
         return(GETCURRENTHIGHESTSEVERITY());

      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() )
      {
         DString strAccNum(NULL_STRING);
         BFAbstractCBO* pAlloc = iter.getObject();
         if( pAlloc )
         {
            pAlloc->getField( ifds::AccountNum, strAccNum, idDataGroup, false );
         }
         if( strAccNum.strip().stripLeading('0') == strAccNumCopy )
         {
            pAcctAlloc = dynamic_cast<X*>(pAlloc);
            break;
         }
         ++iter;
      }
      return(GETCURRENTHIGHESTSEVERITY());
   }
   SEVERITY hasInternationalWireAlloc(const DString& strSettleCurrency, const DString& strCountryCode,
                                      bool &bIsInternationalWire, const BFDataGroupId& idDataGroup);
protected:

   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& ieldId, const BFDataGroupId& idDataGroup );
   SEVERITY setListFields(const BFDataGroupId& idDataGroup);
   
   //calls getShrDefAllocList, but can be overriten by derived class
   SEVERITY getDefaultAllocList(AbstractAllocList*& pDefaultAllocationList, const BFDataGroupId& idDataGroup);

   //gets the default allocation list using shareholder default allocations for the specified TransType
   //and the specified account num
   SEVERITY getShrDefAllocList(AbstractAllocList* &pDefaultAllocationList, const BFDataGroupId& idDataGroup);
   //gets the default allocation list using shareholder default allocations for AMS rebalancing TransType
   //and the specified account num
   SEVERITY getRebalDefAllocList(AbstractAllocList* &pDefaultAllocationList, const BFDataGroupId& idDataGroup);
   //gets the default allocation list using account AMS allocations for the specified account num
   SEVERITY getAMSDefAllocList(AbstractAllocList* &pDefaultAllocationList, const BFDataGroupId& idDataGroup);
private :
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctAllocList.hpp-arc  $
//
//   Rev 1.9   Mar 21 2003 17:55:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.8   Nov 29 2002 10:45:42   KOVACSRO
//Added methods to retrieve different kinds of default allocations
//
//   Rev 1.7   Nov 18 2002 13:41:28   KOVACSRO
//Added comment.
//
//   Rev 1.6   Oct 09 2002 23:53:56   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:51:38   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   Jun 07 2002 17:32:10   KOVACSRO
//Added International Wire .
//
//   Rev 1.3   22 May 2002 18:21:58   PURDYECH
//BFData Implementation
//
//   Rev 1.2   29 Apr 2002 15:52:08   KOVACSRO
//Added getDefaultAllocList()
//
//   Rev 1.1   12 Apr 2002 17:00:20   KOVACSRO
//More implementation.
 * 
 *
*/
