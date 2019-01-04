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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TradeSearchCriteria.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 02/24/2003
//
// ^CLASS    : TradeSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class PendingTradeList;
class TransactionList;

class IFASTCBO_LINKAGE TradeSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:

   TradeSearchCriteria( BFAbstractCBO &parent );
   virtual ~TradeSearchCriteria();

   SEVERITY init(const BFDataGroupId& idDataGroup = BF::HOST, 
      const DString& dstrTrack = I_("N"), const DString& dstrPageName = NULL_STRING);

   SEVERITY getPendingList( PendingTradeList *&pPendingTradeList, const BFDataGroupId& idDataGroup);

   SEVERITY getPendingTradeList( PendingTradeList *&pPendingList, const BFDataGroupId& idDataGroup );

   SEVERITY getTransactionList( TransactionList *&pTransactionList, const BFDataGroupId& idDataGroup);

   bool isValidForInquiry(const BFDataGroupId& idDataGroup);
	//had to overrite this method because of the fancy (and odd!) things about 
   //9999/12/31 logic in DSTDateTime.cpp
   SEVERITY setField( const BFFieldId& fieldId,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true);

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
   SEVERITY doValidateField( const BFFieldId& idField,
                             const DString& strValue,
                             const BFDataGroupId& idDataGroup );
   //had to overrite this method because of the fancy (and odd!) things about 
   //9999/12/31 logic in DSTDateTime.cpp
   /*
   SEVERITY setField( const BFFieldId& fieldId,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted = true,
                              bool  lSideEffect = false,
                              bool  bCheckCurrentValue = true);*/
private:

   SEVERITY loadSearchTypeSubstList( const BFDataGroupId& idDataGroup );
   bool isSWIFT();
   void clearSearchFields(const BFDataGroupId& idDataGroup);
   bool isCriteriaEntered(const BFDataGroupId& idDataGroup);
   void reInitDates(const DString& strSearchType, const BFDataGroupId& idDataGroup);
   void clearDateFields(const BFDataGroupId& idDataGroup);
   DString getCurrentBusDate();
   void clearRequiredFlags(const BFDataGroupId& idDataGroup);

	//field validations
   SEVERITY validateSearchDates(const BFDataGroupId& idDataGroup);
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


	//related changes

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeSearchCriteria.hpp-arc  $
//
//   Rev 1.11   Mar 04 2009 23:49:22   dchatcha
//IN 1395049 - Not returning all the pending trades, introduced 'More' button for pending trade part of Aggregated order screen.
//
//   Rev 1.10   Feb 02 2009 14:36:20   daechach
//IN 1395049 - Not returning all the pending trades.
//
//   Rev 1.9   Mar 02 2006 16:28:54   jankovii
//PET 2072 FN01- NSCC Control Number.
//
//   Rev 1.8   Nov 04 2005 10:52:58   ZHANGCEL
//PET 1286  FN01 -- Add TradeDate search related functions
//
//   Rev 1.7   Dec 09 2004 18:01:12   zhangcel
//PET1117 FN 08 -- Added a function -- getPendingTradList
//
//   Rev 1.6   Dec 03 2004 17:08:46   zhangcel
//PET 1117 FN 08 -- Move setField from Protect ed to Public
//
//   Rev 1.5   Nov 14 2004 14:58:06   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   May 11 2004 11:32:10   ZHANGCEL
//PET1046_FN02 -- Trade Search by account enhancement
//
//   Rev 1.3   May 27 2003 18:30:12   popescu
//due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
//
//   Rev 1.2   Mar 21 2003 18:27:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Mar 04 2003 17:11:38   KOVACSRO
//Overwrite setField
//
//   Rev 1.0   Mar 03 2003 09:51:42   KOVACSRO
//Initial revision.
 
*/

