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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE      : ProtectedFund.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : 01/08/2003
//
// ^CLASS     : ProtectedFund
// ^SUBCLASS  :
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

//Forward declarations
class FundClassRules;

class IFASTCBO_LINKAGE ProtectedFund : public MFCanBFCbo, private boost::noncopyable
{
public:
   ProtectedFund( BFAbstractCBO &parent );
   virtual ~ProtectedFund();

   SEVERITY init(const BFData &viewData);
   SEVERITY init(const BFDataGroupId& idDataGroup);
protected:
   SEVERITY ProtectedFund::doValidateField( const BFFieldId& idField, 
      const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup);
private:
   SEVERITY validateDate(const BFDataGroupId& idDataGroup );
   SEVERITY setFundClassCode(const BFDataGroupId& idDataGroup);
   SEVERITY setFundNumber(const BFDataGroupId& idDataGroup);
   FundClassRules* m_pFundClassRules;
   bool m_bSettingFundClass;
   bool m_bSettingFundNumber;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ProtectedFund.hpp-arc  $
//
//   Rev 1.6   Nov 14 2004 14:51:12   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   Mar 21 2003 18:20:22   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Jan 26 2003 15:50:56   popescu
//Added the Revsion Control entry section
 */