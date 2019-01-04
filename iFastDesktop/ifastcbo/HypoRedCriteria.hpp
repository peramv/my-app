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
// ^FILE   : HypoRedCriteria.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/29/2002
//
// ^CLASS    : HypoRedCriteria
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

class HypoRedSummaryList;
class HypoRedAcctHoldingsList;
class HypoRedCurrencyList;

class IFASTCBO_LINKAGE HypoRedCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:

   HypoRedCriteria( BFAbstractCBO &parent );
   virtual ~HypoRedCriteria();

   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY getHypoRedSummaryList( HypoRedSummaryList *&pHypoRedSummaryList, const BFDataGroupId& idDataGroup);

	SEVERITY getHypoRedAcctHoldingsList( HypoRedAcctHoldingsList *&pHypoRedAcctHoldingsList, 
                                   const BFDataGroupId& idDataGroup, bool bCreate = true);
	/**
    * retrieves a pointer to the currency list
    * @param bNew  - if true, it will delete the existing list, if any, and create a new, empty list
   */
	SEVERITY getCurrencyList( HypoRedCurrencyList *&pHypoRedCurrencyList, 
		const BFDataGroupId& idDataGroup, bool bNewList = false);

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
   SEVERITY doValidateField( const BFFieldId& idField,
                             const DString& strValue,
                             const BFDataGroupId& idDataGroup );

private:

	SEVERITY loadRedCodeSubstList( const BFDataGroupId& idDataGroup );
	bool isAcctLvlDSCAllowed();

	//field validations
   SEVERITY validateTradeDate ( const DString& strValue, const BFDataGroupId& idDataGroup );

	//cross edit validations
   SEVERITY validateGrossFullRedemption( const BFDataGroupId& idDataGroup );
   SEVERITY validateGrossAmtType( const BFDataGroupId& idDataGroup );
   SEVERITY validateFullRedCode( const BFDataGroupId& idDataGroup );

	//related changes
	SEVERITY fullRedCodeChanges(const BFDataGroupId& idDataGroup);
	SEVERITY fullRedChanges(const BFDataGroupId& idDataGroup);
	SEVERITY redCodeChanges(const BFDataGroupId& idDataGroup);

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedCriteria.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:44:32   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Mar 21 2003 18:14:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 25 2002 09:38:42   KOVACSRO
//Added implementation.
//
//   Rev 1.0   Oct 29 2002 10:51:36   KOVACSRO
//Initial Revision
// 
 
*/

