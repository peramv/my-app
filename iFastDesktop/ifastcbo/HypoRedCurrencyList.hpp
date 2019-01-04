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
// ^FILE   : HypoRedCurrencyList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/29/2002
//
// ^CLASS    : HypoRedCurrencyList
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

class HypoRedDetailList;

class IFASTCBO_LINKAGE HypoRedCurrencyList : public MFCanBFCbo, private boost::noncopyable
{
public:

   HypoRedCurrencyList( BFAbstractCBO &parent );
   virtual ~HypoRedCurrencyList();

   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

	/**
    * used to add or update total for a currency
    * @param idDataGroup  - the identifier of the data group with which the change should be done
    * @param data  - a BFData object that should contain all the information about the update, such as
	 * FundCurrency, Amount, DSC, Fee, WithHoldTax
   */
	void changeCurrencyTotal(const BFDataGroupId& idDataGroup, const BFData &data);
	
protected:

	/**
    * virtual function. Should be overwritten in order to do special processing on new list element creation
    * @param pBase         - here will be filled in the new object
    * @param strKey        - here will be filled in string key
    * @param idDataGroup  - the identifier of the data group with which we want to add a new object
   */
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );
   /**
    * returns the default stringKey for new items.It is made by '999' plus an integer sequential number padded left with '0' to 7 positions
    * @param strKey - DString reference where we want to store the key
   */
   void getStrKeyForNewItem( DString & strKey );

private:

	DString m_strKeyForNewItem;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedCurrencyList.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:44:38   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Mar 21 2003 18:14:14   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 25 2002 09:39:56   KOVACSRO
//Added implementation.
//
//   Rev 1.0   Oct 29 2002 10:51:36   KOVACSRO
//Initial Revision
// 
 
*/

