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
// Copyright 2009 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : InvestorAuthorizationList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June 2009
//
// ^CLASS    : InvestorAuthorizationList
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

//Forward declarations
class PaymentInstructions;

class IFASTCBO_LINKAGE InvestorAuthorizationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   InvestorAuthorizationList( BFAbstractCBO &parent );
   virtual ~InvestorAuthorizationList(void);

// Initialize function
   SEVERITY init( const DString &accountNum,
                  const BFDataGroupId& idDataGroup,
                  const DString &dstrTrack     = I_( "N" ),
                  const DString &dstrPageName  = NULL_STRING);

   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, 
                           long lValidateGroup );

protected:
    virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
    virtual SEVERITY doCreateNewObject(BFCBO *&pBase, DString &strKey, 
                                       const BFDataGroupId& idDataGroup );

private:
    DString _accountNum;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestorAuthorizationList.hpp-arc  $
//
//   Rev 1.5   23 Jul 2009 12:58:54   popescu
//PET156681 FN14 H36 Investor Authorization, some more fixes
//
//   Rev 1.4   Jul 23 2009 08:39:28   dchatcha
//PET156681 FN14 H36 Investor Authorization, fix on update existing IA record.
//
//   Rev 1.3   Jul 22 2009 08:41:34   dchatcha
//PET156681 FN14 H36 Investor Authorization, Code review. 
//
//   Rev 1.2   Jul 16 2009 19:34:52   dchatcha
//PET156681 FN14 H36 Investor Authorization, Integration issues.
//
//   Rev 1.1   Jul 09 2009 15:16:50   dchatcha
//PET156681 FN14 H36 Investor Authorization.
//
//   Rev 1.0   29 Jun 2009 16:26:06   popescu
//Initial revision.
//
 */
