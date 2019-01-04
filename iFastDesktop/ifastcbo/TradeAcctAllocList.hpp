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
// ^FILE   : TradeAcctAllocList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/04/02
//
// ^CLASS    : TradeAcctAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Trade account allocation list
//
//******************************************************************************

#ifndef ACCTALLOCLIST_HPP
   #include <ifastcbo\AcctAllocList.hpp>
#endif

class DefAcctAllocList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradeAcctAllocList : public AcctAllocList
{
public:

   // X-structors
   TradeAcctAllocList( BFAbstractCBO &parent );
   virtual ~TradeAcctAllocList( void );

   SEVERITY initExisting( const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING );
   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     bool bGetDefault = true,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY addNewAllocation( const DString& strKey, 
                              const BFDataGroupId& idDataGroup,
                              bool bGetDefault = true,  
                              bool bCopyParent = false, 
                              bool bAddChildren = true);
   SEVERITY addExistingAllocation( const DString& strKey, 
                                   const BFDataGroupId& idDataGroup,
                                   bool bAddChildren = true);
   void getStrKey( DString &strKey, const BFData *data = NULL );
   void getStrKeyForNewItem( DString & strKey );
   const BFData* getView60(){return(_pView60Data);};
   void  getTrackParam(DString& strTrack, DString& strActivity)
   {
      strTrack = _dstrTrack;
      strActivity = _dstrActivity;
   }
   void changeFieldsForRebook();

protected:

   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY setListFields(const BFDataGroupId& idDataGroup);
   void getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue);
   SEVERITY getDefaultAllocList(AbstractAllocList*& pDefaultAllocationList, const BFDataGroupId& idDataGroup);
   
private :

   BFData *_pView60Data;
   DString  _dstrTrack,_dstrActivity;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeAcctAllocList.hpp-arc  $
//
//   Rev 1.8   Jul 08 2005 09:33:16   Yingbaol
//PET1235,FN01:transaction cancellation rebook
//
//   Rev 1.7   Nov 14 2004 14:57:40   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Mar 21 2003 18:26:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Nov 29 2002 10:53:34   KOVACSRO
//override getDefaultAllocList
//
//   Rev 1.4   Oct 09 2002 23:55:10   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Aug 29 2002 12:53:52   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   22 May 2002 18:19:18   PURDYECH
//BFData Implementation
//
//   Rev 1.1   08 May 2002 16:41:16   KOVACSRO
//More implementation.
//
//   Rev 1.0   29 Apr 2002 16:56:22   KOVACSRO
//Initial revision.
 * 
 *
*/
