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
// ^FILE   : EntityList.hpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 1999
//
// ^CLASS    : EntityList
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

class IFASTCBO_LINKAGE EntityList : public MFCanBFCbo, private boost::noncopyable
{

public:
   EntityList (BFAbstractCBO &parent);
   virtual ~EntityList();

   SEVERITY init (const DString& accNum, 
      const DString& dstrTrack= I_("N"), 
      const DString& dstrPageName = NULL_STRING);

protected:   
   SEVERITY doDeleteObject (const DString &strKey, 
      const BFDataGroupId &idDataGroup, 
      bool bIsObjectDestroyed);
   void setObjectFlags (const BFObjectKey &objKey, 
      long &lStateFlags, 
      long &lGroupFlags);
   SEVERITY doCreateObject (const BFData& data, 
      BFCBO *&pObjOut );
   SEVERITY doCreateNewObject (BFCBO *&pBase, 
      DString &strKey, 
      const BFDataGroupId& idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityList.hpp-arc  $
 * 
 *    Rev 1.11   Nov 14 2004 14:36:44   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.10   Jan 02 2004 15:12:08   popescu
 * PTS 10025696, NASU flow crash 
 * 
*/