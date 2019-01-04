#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1

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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : LSIFCodesList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May 2004
//
// ^CLASS    : LSIFCodesList
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

class IFASTCBO_LINKAGE LSIFCodesList : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey (const DString &lsifcode, DString &strKeyOut);
public:
   LSIFCodesList (BFAbstractCBO &parent);
   virtual ~LSIFCodesList ();
   SEVERITY init (
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   DString getLSIFCodesSubstitutionList ();
   DString getDSCOverrideFlag (const DString &lsifCode);
protected:
   virtual void getStrKey (DString &strKey, const BFData *data);
private:
};

///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/LSIFCodesList.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:49:10   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   May 09 2004 20:17:34   popescu
//Initial revision.
//
//   Rev 1.0   May 06 2004 18:43:40   popescu
//Initial revision.
*/