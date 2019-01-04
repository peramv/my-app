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
// ^FILE   : WorkSessionEntityList.hpp
// ^AUTHOR :  Yingbao Li
// ^DATE   : 09/25/2001
//
// ^CLASS    : WorkSessionEntityList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

// Forward references

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE WorkSessionEntityList : public MFCanBFCbo, 
   private boost::noncopyable
{
public:
   WorkSessionEntityList (BFAbstractCBO &parent);
   virtual ~WorkSessionEntityList (void);

   SEVERITY init (const BFDataGroupId &idDataGroup, 
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   SEVERITY getNewEntity (const BFDataGroupId &idDataGroup, 
      Entity *&pEntityOut);
   SEVERITY getEntity (const BFDataGroupId &idDataGroup, 
      const DString &strEntityNum, 
      Entity *&pEntityOut);
   SEVERITY PopulateEntity (const BFDataGroupId &idDataGroup, 
      const BFData &entityData, 
      Entity *&pEntityOut);
   void fromFundBroker( bool bFundBroker)
   {
      _bFundBroker = bFundBroker;
   }
   bool isFundBroker()
   {
       return _bFundBroker;
   }
   SEVERITY refreshEntity (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doCreateNewObject(
      BFCBO *&pBase, 
      DString &strKey, 
      const BFDataGroupId &idDataGroup);


private:
    bool  _bFundBroker;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/WorkSessionEntityList.hpp-arc  $
//
//   Rev 1.9   May 02 2005 11:07:54   yingbaol
//Incident300186: EUSD option is not applicable for FundBroker 
//
//   Rev 1.8   Mar 01 2005 11:52:42   yingbaol
//PET1137,FN01: EU saving entity update
//
//   Rev 1.7   Nov 14 2004 14:59:28   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Jan 02 2004 15:12:14   popescu
//PTS 10025696, NASU flow crash 
//
//   Rev 1.5   Mar 21 2003 18:28:42   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:55:16   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Aug 29 2002 12:54:04   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   22 May 2002 18:18:30   PURDYECH
//BFData Implementation
//
//   Rev 1.1   19 Mar 2002 13:20:16   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   Oct 02 2001 15:01:06   YINGBAOL
//Initial revision.
// 

  
 *
 */