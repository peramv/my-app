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
// ^FILE   : HypoRedAcctHolding.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/29/2002
//
// ^CLASS    : HypoRedAcctHolding
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


class IFASTCBO_LINKAGE HypoRedAcctHolding : public MFCanBFCbo, private boost::noncopyable
{
public:

   HypoRedAcctHolding( BFAbstractCBO &parent );
   virtual ~HypoRedAcctHolding();

   SEVERITY init( const BFData& data, const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

protected:

   void getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
	void setFundName(const BFDataGroupId& idDataGroup);
	SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );


private:

   SEVERITY validateAmount(const DString& strValue, const BFDataGroupId& idDataGroup);
	void formatUnits(DString& strValue, const BFDataGroupId& idDataGroup);
	void formatAmount(DString& strValue, const BFDataGroupId& idDataGroup);
	bool isMoneyMarketFund();
	SEVERITY validateCertificate(const BFDataGroupId& idDataGroup);
	SEVERITY validateEscrow(const BFDataGroupId& idDataGroup);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedAcctHolding.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:44:28   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Mar 21 2003 18:13:54   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 25 2002 09:36:44   KOVACSRO
//Added implementation.
//
//   Rev 1.0   Oct 29 2002 10:51:34   KOVACSRO
//Initial Revision
// 
 
*/

