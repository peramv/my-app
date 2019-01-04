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
// ^FILE   : ShrAllocTypeList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 24/03/02
//
// ^CLASS    : ShrAllocTypeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : the former shareholder level allocation list
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class ShrAllocType;
class DefAcctAllocList;
class DefAcctAlloc;
class DefFundAllocList;
class DefFundAlloc;
class FundDetail;
class AbstractAlloc;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ShrAllocTypeList : public MFCanBFCbo, private boost::noncopyable
{
public:
   friend DefAcctAllocList;
   friend DefAcctAlloc;
   friend DefFundAllocList;
   friend DefFundAlloc;
   // X-structors
   ShrAllocTypeList( BFAbstractCBO &parent );
   virtual ~ShrAllocTypeList( void );

   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );                
   SEVERITY initExisting( const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING );
   SEVERITY addNewAllocation( const DString& strKey, 
                              const BFDataGroupId& idDataGroup,
                              bool bAddChildren = true);
   SEVERITY addNewShrAllocType( const DString& dstrAllocType,
                                const DString& dstrAccountNum,
                                const BFDataGroupId& idDataGroup,
                                const DString &effectiveDate = NULL_STRING);
   //void modelOffer(AbstractAllocList *Model, const BFDataGroupId& idDataGroup) = 0;

   /**
    * @param strKey         - the allocation's key   
     * @param idDataGroup   - the data group identifier 
    * @param pAbstractAlloc - an AbstractAlloc pointer reference 
    * it looks for strKey, NON_DELETED allocation
    */
   SEVERITY getShrAllocType(const DString& strKey, 
                            ShrAllocType *& pShrAllocType, 
                            const BFDataGroupId& idDataGroup);
   SEVERITY getShrAllocType(const DString& dstrAccountNum, 
                            const DString& dstrAllocationType,
                            ShrAllocType *& pShrAllocType, 
                            const BFDataGroupId& idDataGroup);
   SEVERITY removeShrAllocType(const DString& dstrAccountNum, 
                              const DString& dstrAllocationType,
                              const DString& dstrEffectiveDate,
                              const BFDataGroupId& idDataGroup);

   //retrieves a pointer to the latest default account allocation list for the specified TransType
   SEVERITY getDefaultAcctAllocList( const DString& dstrTransTypeIn, 
                                     DefAcctAllocList*& pAcctAllocationList,
                                     const BFDataGroupId& idDataGroup,
                                     const DString& dstrAccountNum = NULL_STRING,
                                     const DString& effectiveDate = NULL_STRING);
   //retrieves a pointer to the latest default account allocation list for the specified TransType
   //which has the specified account in the list

   SEVERITY getDefaultFundAllocList( const DString &dstrTransTypeIn, 
                                     const DString &dstrAcctNumIn,
                                     DefFundAllocList*& pFundAllocationList,
                                     const BFDataGroupId& idDataGroup,
                                     const DString& effectiveDate = NULL_STRING);

   void setAcctAllocFlags(const BFDataGroupId& idDataGroup);
   bool hasDefaultAllocations(const DString& strAccNum, const BFDataGroupId& idDataGroup);

protected:
   //overwritten inhereted public methods 
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

   /**
    * because ShrAllocTypeList is a top level list, this method will always return NULL
    */
   AbstractAlloc *getParentAllocation(){return(NULL);};

   /**
    * returns a pointer to the Shareholder CBO
    */
   MFCanBFCbo *getTopLevelCBO(){return(dynamic_cast<MFCanBFCbo*>(getParent()));};
   const BFData* getView58(){return(_pView58Data);};
   /**
     * returns the default stringKey for new items.It is made by '999' plus an integer sequential number padded left with '0' to 7 positions
     * @param strKey - DString reference where we want to store the key
    */
   void getStrKeyForNewItem( DString & strKey );
   virtual void getStrKey( DString &strKey, const BFData *data = NULL );


private :

	//retrieves the latest shareholder allocation for the specified type
	//if strAccountNum is not empty, retrieves the latest shareholder allocation
   //which has the specified account number in the default account allocation list
	SEVERITY getLatestDefaultShrAlloc( const BFDataGroupId& idDataGroup, 
                                      const DString& dstrTransTypeIn,
												  const DString& strAccountNum,
                                      ShrAllocType*& pAllocation,
                                      const DString& effectiveDate);
   BFData *_pView58Data;
   DString m_strKeyForNewItem;

};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrAllocTypeList.hpp-arc  $
//
//   Rev 1.11   14 Sep 2007 10:59:44   popescu
//Incident 1003183 (GAP2360/02) - fixed AMS allocations
//
//   Rev 1.10   Nov 14 2004 14:55:34   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.9   Feb 12 2004 15:57:00   YINGBAOL
//PTS 10021233: Multi allocation at account level is not been supported
//
//   Rev 1.8   Mar 21 2003 18:24:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Nov 28 2002 18:21:48   HERNANDO
//Added some functions.
//
//   Rev 1.6   Nov 18 2002 13:27:44   KOVACSRO
//syncup 1.5.1
//
//   Rev 1.5.1.0   Nov 18 2002 13:25:16   KOVACSRO
//1. Added    getDefaultAcctAllocList which has an AccountNum parameter, so it will retrieve a pointer to the latest def. acct. alloc. list which contains the specified account
//2. Added AccountNum param. to the existing getLatestDefaultShrAlloc
//
//   Rev 1.5   Oct 09 2002 23:55:02   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:53:40   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   Jul 31 2002 15:00:32   KOVACSRO
//Added getStrKeyForNewItem
//
//   Rev 1.2   22 May 2002 18:20:00   PURDYECH
//BFData Implementation
//
