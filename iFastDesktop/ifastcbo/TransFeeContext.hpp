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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TransFeeContext.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : TransFeeContext
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
class Trade;
class PendingTradeDetails;

class IFASTCBO_LINKAGE TransFeeContext : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   TransFeeContext (BFAbstractCBO &parent);
   virtual ~TransFeeContext();
// Init context methods
   SEVERITY initTradeContext ( Trade *pTrade,
                               const BFDataGroupId &idDataGroup);
   SEVERITY initPendingTradeContext ( PendingTradeDetails *pTrade,
                                      const BFDataGroupId &idDataGroup);
   TransFeeContext& operator= (const TransFeeContext &copy);
   bool operator== (const TransFeeContext &o);
   bool isContextValid (const BFDataGroupId &idDataGroup);
protected:
private:
   
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransFeeContext.hpp-arc  $
//
//   Rev 1.5   Jan 20 2005 11:03:36   popescu
//PTS 10038127, fixed internal error when user clicks on the 'Fees' button in trans  history screen
//
//   Rev 1.4   Nov 24 2004 21:36:34   popescu
//PET 1117/06/56. trade processing, settle location
//
//   Rev 1.3   Nov 15 2004 16:24:14   popescu
//PET 1117/06, more synch to .NET changes
//
//   Rev 1.1   Nov 09 2004 16:51:12   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.0   Nov 05 2004 21:30:24   popescu
//Initial revision.
//
//Initial revision.
//
 */
