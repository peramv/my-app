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
// ^FILE   : RedemptionValidation.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 04/25/2003
//
// ^CLASS    : RedemptionValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RedemptionValidation : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey (
      const DString &transType,
      const DString &accountNum,
      const DString &effectiveDate,    
      const DString &fundCode,
      const DString &classCode,        
      const DString &amount,
      const DString &amountType,       
      const DString &redCode,
      const DString &settleDate,       
      const DString &settleCurrency,
      const DString &lsifCode,
  	  const DString &grossNet,
      DString &strKey);
public:
   RedemptionValidation (BFAbstractCBO &parent);
   virtual ~RedemptionValidation();
   SEVERITY init( 
      const DString &transType,
      const DString &accountNum,
      const DString &effectiveDate,    
      const DString &fundCode,
      const DString &classCode,        
      const DString &amount,
      const DString &amountType,       
      const DString &redCode,
      const DString &settleDate,       
      const DString &settleCurrency,
      const DString &strLSIFCode,
  	  const DString &grossNet,
	  const DString &taxable = I_("N"),
	  const DString &dstrTrack = I_("N"),
	  const DString &dstrPageName = NULL_STRING);
private:

};
///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RedemptionValidation.hpp-arc  $
//
//   Rev 1.6   Apr 17 2009 10:44:46   jankovii
//PET 157825 FN04 Manual RRIF Redemption.
//
//   Rev 1.5   Nov 14 2004 14:51:42   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   May 13 2004 21:06:42   popescu
//PET 985, FN 01, LSIF Trade entry
//
//   Rev 1.3   Oct 02 2003 12:21:14   HSUCHIN
//added revision control loggin.
*/