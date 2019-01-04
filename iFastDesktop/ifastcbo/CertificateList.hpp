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
// ^FILE   : CertificateList.hpp
// ^AUTHOR : Brian Hicks
// ^DATE   : June 11, 1999
//
// ^CLASS    : CertificateList
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

class IFASTCBO_LINKAGE CertificateList : public MFCanBFCbo, private boost::noncopyable
{
public:
   CertificateList( BFAbstractCBO &parent );
   virtual ~CertificateList();

   SEVERITY init( DString& AcctNum, 
                  DString& Fund, 
                  DString& CertNum, 
                  DString& XrefNum,
                  bool bIgnoreDataNotFound = true, 
                  bool bIgnoreNotEnoughInfo = false,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING); 

   bool certIssueUnitsExist( const DString& dstrFund, const DString& dstrClass, double& dIssueUnits, const BFDataGroupId& idDataGroup);

private:
};

///#endif
