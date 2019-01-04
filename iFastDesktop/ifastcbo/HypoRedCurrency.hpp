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
// ^FILE   : HypoRedCurrency.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/29/2002
//
// ^CLASS    : HypoRedCurrency
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


class IFASTCBO_LINKAGE HypoRedCurrency : public MFCanBFCbo, private boost::noncopyable
{
public:

   HypoRedCurrency( BFAbstractCBO &parent );
   virtual ~HypoRedCurrency();

   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );
	/**
    * used to update total for a currency
    * @param idDataGroup  - the identifier of the data group with which the change should be done
    * @param data  - a BFData object that should contain all the information about the update, such as
	 * Amount, DSC, Fee, WithHoldTax
   */
	void updateTotal(const BFDataGroupId& idDataGroup, const BFData &data);

protected:

   void getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;


private:



};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedCurrency.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:44:34   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Mar 21 2003 18:14:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 25 2002 09:39:24   KOVACSRO
//Added updateTotal
//
//   Rev 1.0   Oct 29 2002 10:51:36   KOVACSRO
//Initial Revision
// 
 
*/

