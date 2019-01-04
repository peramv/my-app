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
// ^FILE   : AccountTradesList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : February  02, 2001
//
// ^CLASS    : AccountTradesList
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

class IFASTCBO_LINKAGE AccountTradesList : public MFCanBFCbo, private boost::noncopyable
{
public:
   AccountTradesList (BFAbstractCBO &parent);
   virtual ~AccountTradesList ();
   SEVERITY init ( const DString &accountNum, 
                   const BFDataGroupId &idDataGroup,
                   const DString &dstrTrack = I_ ("N"),
                   const DString &dstrPageName = NULL_STRING
                 );
protected:
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountTradesList.hpp-arc  $
//
//   Rev 1.15   Nov 06 2004 00:39:38   popescu
//PET 1117/06, synch changes
// 
 * 
 * 
 */

