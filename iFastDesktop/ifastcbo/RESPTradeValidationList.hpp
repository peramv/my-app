#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : RESPTradeValidationList.hpp
// ^AUTHOR : 
// ^DATE   : Aprl 2010
//
// ^CLASS    : RESPTradeValidationList
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

class IFASTCBO_LINKAGE RESPTradeValidationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   RESPTradeValidationList( BFAbstractCBO &parent );
   virtual ~RESPTradeValidationList(void);

// Initialize function
   SEVERITY init( const DString &accountNum,
                  const DString& transType,
                  const DString& fundCode,
                  const DString& classCode,
                  const DString& depType,
                  const DString& redCode,
                  const DString& tradeDate,
                  const DString& settleDate,
                  const DString& amountType,
                  const DString& amount,
                  const DString& grossOrNet,
                  const DString& respBenefId,
                  const DString& fee,
                  const DString& flatPrcnt,
                  const DString& ocRdmYear,
                  const DString& respContrDetlTaxYear,
                  const DString& assistedContrAmt,
                  const BFDataGroupId& idDataGroup,
                  const DString &dstrTrack     = I_( "N" ),
                  const DString &dstrPageName  = NULL_STRING);

protected:
    virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPTradeValidationList.hpp-arc  $
//
//   Rev 1.2   May 27 2010 06:08:34   kitticha
//PETP0165541 FN02 QESI Phase2.
//
//   Rev 1.1   Apr 22 2010 03:57:56   dchatcha
//PET0165541 FN01 QESI RESP Trading.
//
//   Rev 1.0   Apr 21 2010 23:28:14   dchatcha
//Initial revision.
 */
