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
// ^FILE   : Remarks.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : March 19, 1999
//
// ^CLASS    : Remarks
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

class IFASTCBO_LINKAGE Remarks : public MFCanBFCbo, private boost::noncopyable
{
public:
   Remarks (BFAbstractCBO &parent);
   virtual ~Remarks();
   SEVERITY init (const BFData &data);
   SEVERITY init (const BFDataGroupId &idDataGroup);
   SEVERITY setField (
      const BFFieldId &idField, 
      const DString &dstrValue,
      const BFDataGroupId& idDataGroup, 
      bool bFormatted = true, 
      bool bSideEffect = false, 
      bool  bCheckCurrentValue = true);
   bool isRemarkInfoField(const BFFieldId &idField);
   void setAllFieldsReadOnly(const BFDataGroupId& idDataGroup);
protected:
   virtual SEVERITY doApplyRelatedChanges (
      const BFFieldId &idField, 
      const BFDataGroupId &idDataGroup);
   virtual void doInitWithDefaultValues (
      const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Remarks.hpp-arc  $
 * 
 *    Rev 1.10   Nov 14 2004 14:51:52   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.9   Feb 23 2004 10:41:38   popescu
 * PTS 10027283, moved the initialization of the effective date and remark type to the 'doInitWithDefaultValues' method, from init of new objects method. Also removed setting the update flag of the account field in init for new objects method, which makes the object always dirty.
 * 
 *
**/