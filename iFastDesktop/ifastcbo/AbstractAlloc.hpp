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
// ^FILE   : AbstractAlloc.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 24/03/02
//
// ^CLASS    : AbstractAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all the allocations
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class FundDetail;
class AbstractAllocList;
class MFAccount;
class SplitCommissionList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AbstractAlloc : public MFCanBFCbo, private boost::noncopyable
{
public:
   friend class AbstractAllocList;
   // X-structors
   AbstractAlloc( BFAbstractCBO &parent );
   virtual ~AbstractAlloc( void );

   // pure virtual public methods
   virtual SEVERITY initNew( const BFDataGroupId& idDataGroup,
                             const DString& dstrTrack = I_("N"),
                             const DString& dstrPageName = NULL_STRING ) = 0;                
   virtual SEVERITY initExisting(const BFData &data)=0;
   virtual SEVERITY initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup);
   /**
    * returns the first BFBase pointer, that is NOT an AbstractAllocList, neither an AbstractAlloc
    */
   BFCBO *getTopLevelCBO();
   /**
    * returns the last AbstractAllocList, upwards
    */
   AbstractAllocList* getTopLevelAllocList();    
   void modelOffer(AbstractAlloc *pModel, const BFDataGroupId& idDataGroup);
   void getField( const BFFieldId& idField, 
                  DString & strValue, 
                  const BFDataGroupId& idDataGroup, 
                  bool formattedReturn = false ) const;

protected:

   //overwritten inhereted public methods 
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

   //non virtual protected methods                                     
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
    * returns a pointer to the parent allocation list if any, else returns NULL
    */
   AbstractAllocList* getParentList();
   bool isDefaultAlloc(){return(m_bInitDefault);};
   // this method should set the specific fields for the allocation 
   virtual SEVERITY setAllocFields(const BFDataGroupId& idDataGroup) = 0;
   /**
    * set the amount based on the total amount and percentage
    */
   SEVERITY setAmount( const BFDataGroupId& idDataGroup );
   //this metod should be overwritten for each derived class which calls modelOffer
   virtual BFData *getDataForModelOffer(){return(NULL);};
   virtual SEVERITY loadSubstitutions( const BFDataGroupId& idDataGroup ){return(NO_SEVERITY);};
   virtual void setAllocFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly=true);
private :

   /**
    * set the percentage based on the total amount and alloc amount
    */
   SEVERITY setPercentage( const BFDataGroupId& idDataGroup );
   //validations
   SEVERITY validatePercentage(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateAmount(const DString& strAmount, const BFDataGroupId& idDataGroup);

   bool m_bSettingAmountField;
   bool m_bSettingPercentField;
   bool m_bInitDefault;//this allocation is the default allocation
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AbstractAlloc.hpp-arc  $
//
//   Rev 1.9   Mar 21 2003 17:53:28   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.8   Oct 09 2002 23:53:50   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.7   Aug 29 2002 12:51:22   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.6   Aug 19 2002 15:19:08   KOVACSRO
//Added 1. getField and 2. setAllocFieldsReadOnly
//
//   Rev 1.5   Aug 06 2002 09:52:58   KOVACSRO
//Release 48. Added modelOffer.
//
//   Rev 1.4   22 May 2002 18:22:12   PURDYECH
//BFData Implementation
//
//   Rev 1.3   08 May 2002 16:28:58   KOVACSRO
//More implementation.
//
//   Rev 1.2   29 Apr 2002 15:48:42   KOVACSRO
//Added initDefault()
//
//   Rev 1.1   12 Apr 2002 16:59:00   KOVACSRO
//More implementation.
 * 
 *
*/