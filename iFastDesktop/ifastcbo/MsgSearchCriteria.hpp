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
//******************************************************************************
//
// ^FILE      : MsgSearchCriteria.hpp
// ^CLASS     : MsgSearchCriteria
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

//Forward declarations
class FundClassRules;

class IFASTCBO_LINKAGE MsgSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:
   MsgSearchCriteria (BFAbstractCBO &parent);
   virtual ~MsgSearchCriteria();

   SEVERITY init (
      const DString &fillSearchType, 
      const BFDataGroupId &idDataGroup);

protected:
   SEVERITY doValidateField (
      const BFFieldId &idField, 
      const DString &strValue, 
      const BFDataGroupId &idDataGroup);
   SEVERITY doApplyRelatedChanges (
      const BFFieldId &idField, 
      const BFDataGroupId &idDataGroup);

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgSearchCriteria.hpp-arc  $
//
//   Rev 1.0   Feb 21 2005 11:14:26   hernando
//Initial revision.
