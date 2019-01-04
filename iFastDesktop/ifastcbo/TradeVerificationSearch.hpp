//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TradeVerificationSearch.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : JuLY 22 2014
//
//********************************************************************************
#include "stdafx.h"
#include <ifastcbo\TradeSearchCriteria.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif
class TradeVerificationList;
class IFASTCBO_LINKAGE TradeVerificationSearch :  public MFCanBFCbo, private boost::noncopyable
{
public:

   TradeVerificationSearch( BFAbstractCBO &parent );
   virtual ~TradeVerificationSearch();
   SEVERITY init(const BFDataGroupId& idDataGroup = BF::HOST, 
                 const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);
   virtual SEVERITY getTradeVerificationList( TradeVerificationList *&pTradeVerificationList, const BFDataGroupId& idDataGroup, bool bCreate = true);                    
   //virtual SEVERITY getPendingTradeList( PendingTradeList *&pPendingList, const BFDataGroupId& idDataGroup );
   bool isValidForInquiry(const BFDataGroupId& idDataGroup);
protected:

   /**
    * virtual function. Should be overwritten in order to store custom default values into the CBO
    * @param idDataGroup  - the identifier of the data group with which the initialisation should be done
   */
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   /**
    * virtual function. It should be overwritten in order to have special processing in a setField after the validation succeeds on in 
    * setFieldNoValidate after the value is stored in the CBO
    * @param idField      - the identifier of the field for which we want to apply the related changes
    * @param idDataGroup  - the identifier of the data group for which we want to apply the related field changes
   */
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   /**
    * virtual function. It should be overwriten in order to do field validation. It is called by
    * validateField
    * @param idField     - the identifier of the field for which we are doing the validation
    * @param strValue     - the value of the field on which the validation is based on
    * @param idDataGroup - the identifier of the data group for which we are doing the validation
   */
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   bool isSWIFT();
   bool isCriteriaEntered(const BFDataGroupId& idDataGroup);
private:   
   virtual void clearRequiredFlags(const BFDataGroupId& idDataGroup);
   virtual void clearSearchFields(const BFDataGroupId& idDataGroup);
   SEVERITY loadSearchTypeSubstList( const BFDataGroupId& idDataGroup );
   SEVERITY validateTransNum(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateWireOrdNum(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateFundNumber( const BFDataGroupId &idDataGroup, const DString &dstrFundNumber);
   SEVERITY validateFundClassCode ( const BFDataGroupId  &idDataGroup );
   SEVERITY validateFundWKN( const BFDataGroupId &idDataGroup,const DString &dstrFundWKN );
   SEVERITY validateFundISIN( const BFDataGroupId &idDataGroup,const DString &dstrFundISIN);
   SEVERITY validateNSCCControlNumber(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY setFundByFundNumber(const BFDataGroupId &idDataGroup, const DString &dstrFundNumber);
   SEVERITY setFundbyFundClass(const BFDataGroupId &idDataGroup, const DString &dstrFundCode, const DString &dstrClassCode);
   SEVERITY setFundByWKN(const BFDataGroupId &idDataGroup, const DString &dstrFundWKN);
   SEVERITY setFundByISIN(const BFDataGroupId &idDataGroup, const DString &dstrFundISIN);
   SEVERITY setSearchTypeSubstSet(const BFFieldId& idField, const BFDataGroupId &idDataGroup);
   void loadTransTypeSubstList( const BFDataGroupId& idDataGroup );
   SEVERITY loadNetworkIDValues (const BFDataGroupId &idDataGroup);
   void loadPlatformSetSubstList (const BFDataGroupId &idDataGroup);
   TradeVerificationList* _pTradeVerificationList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradeVerificationSerach.hppp-arc  $
// 
//    Rev 1.0  22 July 2014
// Initial revision.
*/
