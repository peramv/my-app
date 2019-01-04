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
// ^FILE   : RESPTradeSearchCriteria.hpp
// ^AUTHOR : 
// ^DATE   : 31/08/2010
//
// ^CLASS    : RESPTradeSearchCriteria
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


class RESPTransactionsList;

class IFASTCBO_LINKAGE RESPTradeSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:

   RESPTradeSearchCriteria( BFAbstractCBO &parent );
   virtual ~RESPTradeSearchCriteria();

   SEVERITY init (const DString& dstrAccountNum, 
	              const DString &dstrTransId,
				  const DString &dstrTradeDate,
				  const DString &dstrHistoryPending,
	              const BFDataGroupId& idDataGroup);

   SEVERITY getRESPTransactionsList( RESPTransactionsList *&pRESPTransactionsList, 
	                                 const DString& accountNum,
                                     const DString& historyPending,
                                     const DString& transId, 
                                     const BFDataGroupId& idDataGroup, 
                                     bool inquireDatabase = true );


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
private:

	SEVERITY loadRESPBenefSubstList (const BFDataGroupId& idDataGroup);
	SEVERITY loadRESPTransactionsSubstList (const BFDataGroupId& idDataGroup);

	void initWithDefaultValuesAll(const BFDataGroupId& idDataGroup);
	void initWithDefaultValuesOne(const BFDataGroupId& idDataGroup);
	DString getCurrentBusDate();

	//field validations
	SEVERITY validateFromDate (const DString &dstrFromDate, const BFDataGroupId& idDataGroup);
	SEVERITY validateToDate (const DString &dstrToDate, const BFDataGroupId& idDataGroup);

	SEVERITY transTypeRelatedChanges (const DString &dstrTransId, const BFDataGroupId& idDataGroup );

	DString m_dstrAccountNum;
	DString m_dstrAcctEffectiveDate;
	DString m_dstrAcctInceptionDate;
	DString m_dstrTransId;
	DString m_dstrTradeDate;
	DString m_dstrHistoryPending;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log::   
*/

