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
// ^FILE   : AbstractAllocList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 24/03/02
//
// ^CLASS    : AbstractAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all the allocation lists
//
//******************************************************************************

#ifndef IFASTCBO_HPP
   #include <ifastcbo\mfcancbo.hpp>
   #include <boost\utility.hpp>
#endif

class AbstractAlloc;
class FundDetail;


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

namespace CND
{
   extern IFASTCBO_LINKAGE const I_CHAR *IFASTCBO_CONDITION;
}
namespace ifds
{
   extern CLASS_IMPORT const BFDataId DSTC0060_VWRepeat_Record;
   extern CLASS_IMPORT const BFDecimalFieldId AllocAmount;

}

class IFASTCBO_LINKAGE AbstractAllocList : public MFCanBFCbo, private boost::noncopyable
{
public:
   friend class AbstractAlloc;

   // X-structors
   AbstractAllocList( BFAbstractCBO &parent );
   virtual ~AbstractAllocList( void );

   virtual SEVERITY initNew( const BFDataGroupId& idDataGroup,
                             bool bGetDefault = true,
                             const DString& dstrTrack = I_("N"),
                             const DString& dstrPageName = NULL_STRING ) = 0;                
   virtual SEVERITY initExisting( const DString& dstrTrack = I_("N"),
                                  const DString& dstrPageName = NULL_STRING ) = 0;
   //we can add a new allocation to the list, in three different ways
   //1. add a dummy allocation bGetDefault=false, bCopyParent = false
   //2. add an allocation that will have all the data copied from it's parent (the so called 100% allocation bGetDefault=false, bCopyParent = true
   //3. add a dummy allocation that will go and get the default child allocation list bGetDefault=true, bCopyParent = false
   //it doesn't make sense to ask for a new allocation having bGetDefault=true, bCopyParent = true 
   virtual SEVERITY addNewAllocation( const DString& strKey, 
                                      const BFDataGroupId& idDataGroup,
                                      bool bGetDefault = true,  //get the default allocation list for the new allocation
                                      bool bCopyParent = false, //copy the data from the parent for the new allocation
                                      bool bAddChildren = true) //add the children allocations too
   {
		return NO_CONDITION;
	}
   //we have to add an existing 100% allocation to the list, whenever there are no allocations for the pending trade (BA rule, not ours)
   // never need to get the default allocation here
   // we always need to copy data from it's parent (the so called 100% allocation 
   virtual SEVERITY addExistingAllocation( const DString& strKey, 
                                           const BFDataGroupId& idDataGroup,
                                           bool bAddChildren = true) //add the children allocations too
	{
		return NO_CONDITION;
	
	}
   /**
     * @param idDataGroup   - the data group identifier 
    * deletes all the allocation objects in the list
    */
   virtual SEVERITY clearAllocations( const BFDataGroupId& idDataGroup ) = 0;

   virtual void modelOffer(AbstractAllocList *Model, const BFDataGroupId& idDataGroup);

   /**
    * @param strKey         - the allocation's key   
     * @param idDataGroup   - the data group identifier 
    * @param pAbstractAlloc - an AbstractAlloc pointer reference 
    * it looks for strKey, NON_DELETED allocation
    */
   void getAllocation(const DString& strKey, 
                      AbstractAlloc *& pAbstractAlloc, 
                      const BFDataGroupId& idDataGroup);

   void getTotalAmount(DString &strTotalAmount, const BFDataGroupId& idDataGroup, bool bFormatted = true);
   void getTotalPercentage(DString &strTotalPercentage, const BFDataGroupId& idDataGroup, bool bFormatted = true);
   /**
     * @param idDataGroup   - the data group identifier 
    * @param dstrSplitComm - a string reference; will be Y if there is at leat one allocation that has SplitComm field set to Y
    */
   void GetSplitCommFlag ( const BFDataGroupId& idDataGroup, DString &dstrSplitComm );
   /**
    * if the allocation list is a child of an allocation, returns an AbstractAlloc* to it's parent
    * if the allocation list is a first level allocation, returns a NULL pointer
    */
   AbstractAlloc *getParentAllocation();
   SEVERITY setField( const BFFieldId& idField,
                      const DString& strValue,
                      const BFDataGroupId& idDataGroup,
                      bool  lFormatted = true,
                      bool  lSideEffect = false,
                      bool  bCheckCurrentValue = true);
   /**
    * returns the last AbstractAllocList, upwards
    */
   AbstractAllocList* getTopLevelAllocList();
   //returns the number of NON_DELETED allocations in the list
   int getAllocNum(const BFDataGroupId& idDataGroup);
   virtual void setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup);
protected:
   /**
    * @param pDefaultAllocationList   - a pointer ref. to the Default allocation list
    * @param idDataGroup   - the data group identifier   
    * retrieves the default allocations for this list
    */
   virtual SEVERITY getDefaultAllocList(AbstractAllocList*& pDefaultAllocationList, const BFDataGroupId& idDataGroup)=0;

   /**
    * @param idDataGroup   - the data group identifier   
    * retrieves the default allocations for this list
    */
   template <class _X> 
   SEVERITY initDefaultAllocationList(const _X* pAllocType, const BFDataGroupId& idDataGroup)
   {
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initDefaultAllocationList" ) );

      //if anything there, cleanup first
      clearAllocations(idDataGroup);

      AbstractAllocList* pDefaultAllocationList;
      if( getDefaultAllocList(pDefaultAllocationList, idDataGroup)>WARNING || !pDefaultAllocationList )
         return(GETCURRENTHIGHESTSEVERITY());

      BFObjIter iter(*pDefaultAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
      int nNoOfItems = iter.getNumberOfItemsInList();
      if( nNoOfItems <= 0 )
         return(GETCURRENTHIGHESTSEVERITY());

      while( !iter.end() )
      {
         BFAbstractCBO *pBFCBO = iter.getObject();
         if( pBFCBO )
         {
            _X *pAlloc = new _X( *this );
            DString dstrKey;
            BFData data( ifds::DSTC0060_VWRepeat_Record );
            pAlloc->initDefault(pBFCBO, idDataGroup);
            pAlloc->getData(data, idDataGroup);
            getStrKey(dstrKey, &data);
            pAlloc->setNonDummyFlag();
            assert(dstrKey != NULL_STRING);
            setObject( pAlloc, dstrKey, OBJ_ACTIVITY_ADDED, idDataGroup );
         }
         ++iter;
      }
      //now set the amount field
      DString strTotalAmount;
      getField( ifds::Amount, strTotalAmount, idDataGroup, false );	  
      if( 0 != DSTCommonFunctions::convertToDouble (strTotalAmount) )
         setFieldNoValidate( ifds::Amount, strTotalAmount, idDataGroup, false );//this will set the amount for the allocations

      return(GETCURRENTHIGHESTSEVERITY());
   }

   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );

   /**
    * @param strFundCode   - the allocation's key   
    * @param strClassCode  - the allocation's key   
     * @param idDataGroup  - the data group identifier 
    * @param pFundDetail   - a FundDetail pointer reference 
    * retrieves the FundDetail for strFundCode, strClassCode
    */
   SEVERITY getFundDetail( const DString& strFundCode, 
                           const DString& strClassCode, 
                           FundDetail *&pFundDetail );   
   /**
    * @param idDataGroup   - the data group identifier 
    * @param dstrValue      - the unformatted value we want to format
    */
   virtual void getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue);
   void formatAmtUsingCurrency(const BFDataGroupId& idDataGroup, DString &dstrValue);
   void formatAmtUsingFromFund(const BFDataGroupId& idDataGroup, DString &dstrValue);

   /**
    * returns the first BFBase pointer, that is NOT an AbstractAllocList, neither an AbstractAlloc
    */
   BFCBO *getTopLevelCBO();
   /**
    * returns a pointer to the parent allocation list if any, else returns NULL
    */
   AbstractAllocList* getParentList();
   // this method should set the specific fields for the allocation list
   virtual SEVERITY setListFields(const BFDataGroupId& idDataGroup) = 0;
   // if there are any substitutions to be loaded, they should be loaded in this method
   virtual SEVERITY loadSubstitutions( const BFDataGroupId& idDataGroup ){return(NO_SEVERITY);};
   //if toFieldId is NULL_STRING, gets fromFieldId from pCBO and sets it
   SEVERITY setFieldFromCBO( BFCBO* pCBO, 
                             const BFFieldId& fromFieldId, 
                             const BFFieldId& toFieldId, 
                             const BFDataGroupId& idDataGroup, 
                             DString& strValue );
   //returns the sum of all the other allocations amount
   void getOtherAllocTotalAmount(DString &strTotalAmount, const BFDataGroupId& idDataGroup, bool bFormatted = true, AbstractAlloc* pCallingAlloc = NULL);
   //returns the sum of all the other allocations percentage
   void getOtherAllocTotalPercentage(DString &strTotalPercentage, const BFDataGroupId& idDataGroup, bool bFormatted = true, AbstractAlloc* pCallingAlloc = NULL);
   bool isMultiCurrency();
   /**
     * returns the default stringKey for new items.It is made by '999' plus an integer sequential number padded left with '0' to 7 positions
     * @param strKey - DString reference where we want to store the key
    */
   void getStrKeyForNewItem( DString & strKey );


   DString m_strKeyForNewItem;

private :
   /**
    * iterate through allocations and set their amount field, based on the percentage
    */
   SEVERITY setAmount( const BFDataGroupId& idDataGroup );
   //get total amount or total percent
   void getTotalValue( const BFFieldId& idField, 
                       DString &strTotalValue, 
                       const BFDataGroupId& idDataGroup, 
                       AbstractAlloc* pCallingAlloc = NULL);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AbstractAllocList.hpp-arc  $
//
//   Rev 1.13   Aug 25 2005 12:11:42   porteanm
//Incident 387964 - 0 Amount check.
//
//   Rev 1.12   Jun 09 2003 11:48:08   YINGBAOL
//RRIF enhancement
//
//   Rev 1.11   Mar 21 2003 17:53:34   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.10   Oct 09 2002 23:53:50   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.9   Aug 29 2002 12:51:22   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.8   Aug 14 2002 10:26:36   KOVACSRO
//Added getAllocNum
//
//   Rev 1.7   Aug 06 2002 09:53:28   KOVACSRO
//Release 48. Added modelOffer
//
//   Rev 1.6   Jul 31 2002 14:35:20   KOVACSRO
//Added getStrKeyForNewItem()
//
//   Rev 1.5   Jun 20 2002 13:35:18   KOVACSRO
//Added isMulticurrency
//
//   Rev 1.4   22 May 2002 18:22:12   PURDYECH
//BFData Implementation
//
//   Rev 1.3   08 May 2002 16:30:58   KOVACSRO
//More implementation.
//
//   Rev 1.2   29 Apr 2002 15:50:12   KOVACSRO
//more implementation
//
//   Rev 1.1   12 Apr 2002 16:59:34   KOVACSRO
//More implementation.
 * 
 *
*/