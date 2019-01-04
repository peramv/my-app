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
// ^FILE   : FundGroupTypeList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : Jan 9, 2003
//
// ^CLASS    : FundGroupTypeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class FundMaster;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundGroupTypeList : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundGroupTypeList( BFAbstractCBO &parent );
   virtual ~FundGroupTypeList();

   SEVERITY init (
      const DString &fundGroupType, 
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   void getStrKey (
      DString &strKey, 
      const BFData *data);
   DString getStrKey (
      const DString &strFundCode, 
      const DString &strClassCode, 
      const DString &strType, 
      const DString &strGroup);
   bool isFundExist (
      const DString &strFundCode, 
      const DString &strTypeCode, 
      const DString &strGroupCode);
   bool isFundClassExist (
      const DString &strFundCode, 
      const DString &strClassCode, 
      const DString &strTypeCode, 
      const DString &strGroupCode);

   DString getFundGroupCode(const DString &fundCode, 
                            const DString &classCode);
protected:

private:
};

///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundGroupTypeList.hpp-arc  $
//
//   Rev 1.4   Nov 14 2004 14:42:36   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   Feb 26 2004 13:43:14   popescu
//PTS 10026434, changed name of parameters for method getFundGroupTypeList to signal a broader use
//
//   Rev 1.2   Apr 15 2003 10:48:40   linmay
//Sync up with 1.0.1.0
//
//   Rev 1.1   Mar 21 2003 18:11:34   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Jan 13 2003 10:15:28   KOVACSRO
//Initial revision.
 * 
*/