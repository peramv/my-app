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
// ^FILE   : SWPAmountCalculation.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SWPAmountCalculation
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

class IFASTCBO_LINKAGE SWPAmountCalculation : public MFCanBFCbo, private boost::noncopyable
{
public:

	static void buildKey (const DString &accountNum,
						  const DString &amountType,    
						  const DString &effectiveDate,    
						  const DString &stopDate, 
						  const DString &endOfMonth,
						  const DString &january,
						  const DString &february,        
						  const DString &march,
						  const DString &april,       
						  const DString &may,
						  const DString &june,       
						  const DString &july,
						  const DString &august,
  						  const DString &september,
  						  const DString &october,
  						  const DString &november,
  						  const DString &december,
						  DString &strKey);

public:

	SWPAmountCalculation (BFAbstractCBO &parent);
	
	virtual ~SWPAmountCalculation();
	
	SEVERITY init(const DString &accountNum,
				  const DString &amountType,
				  const DString &effectiveDate,
				  const DString &stopDate,
				  const DString &endOfMonth,
				  const DString &january,
				  const DString &february,        
				  const DString &march,
				  const DString &april,       
				  const DString &may,
				  const DString &june,       
				  const DString &july,
				  const DString &august,
				  const DString &september,
				  const DString &october,
				  const DString &november,
				  const DString &december,
				  const DString &dstrTrack = I_("N"),
				  const DString &dstrPageName = NULL_STRING);

private:

};
///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SWPAmountCalculation.hpp-arc  $
//
//   Rev 1.0   May 11 2012 13:18:18   jankovii
//Initial revision.

*/