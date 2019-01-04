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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE      : PaymentInstrValidation.hpp
// ^AUTHOR    : Celia Zhang
// ^DATE      : 10/1608/2006
//
// ^CLASS     : PaymentInstrValidation
// ^SUBCLASS  :
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

class IFASTCBO_LINKAGE PaymentInstrValidation : public MFCanBFCbo, private boost::noncopyable
{
public:
   PaymentInstrValidation (BFAbstractCBO &parent);
   virtual ~PaymentInstrValidation();

   SEVERITY init( const DString &dstrBrokerCode,
						const DString &dstrBranchCode,
						const DString &dstrSalesRepCode,
						const DString &dstrPaymentFor,
						const DString &dstrEffectiveDate,
						const DString &dstrStopDate );   
private:
	BFData *_pRequestData;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/PaymentInstrValidation.hpp-arc  $
//
//   Rev 1.0   Oct 18 2006 15:46:12   ZHANGCEL
//Initial revision.
