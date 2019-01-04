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
// ^FILE   : ChqName.hpp
// ^AUTHOR : Amelia Aguila
// ^DATE   : July 2, 2004
//
// ^CLASS    : ChqName
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

class IFASTCBO_LINKAGE ChqName : public MFCanBFCbo, private boost::noncopyable
{
public:
   ChqName( BFAbstractCBO &parent );

   virtual ~ChqName(void);

   SEVERITY init( const DString& dstrAccountNum,
                  const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );


private:
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ChqName.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:29:38   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Jul 02 2004 12:11:16   AGUILAAM
//Initial revision.
// 
*/

