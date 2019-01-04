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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DecodeAcctID.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : Octoble 07, 2005
//
// ^CLASS    : DecodeAcctID
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Populate name fields for settlement chq
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

class IFASTCBO_LINKAGE DecodeAcctID : public MFCanBFCbo, private boost::noncopyable
{
public:
   DecodeAcctID( BFAbstractCBO &parent );

   virtual ~DecodeAcctID(void);

   SEVERITY init( const DString& dstrAccountID,
                  const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );


private:
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DecodeAcctID.hpp-arc  $
//
//   Rev 1.0   Oct 24 2005 17:35:58   ZHANGCEL
//Initial revision.
*/

