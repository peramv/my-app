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
// ^FILE   : RegulatoryValidationErrorList.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Sep 2015
//
// ^CLASS    : RegulatoryValidationErrorList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
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

class IFASTCBO_LINKAGE RegulatoryValidationErrorList : public MFCanBFCbo, private boost::noncopyable
{
public:
   RegulatoryValidationErrorList (BFAbstractCBO &parent);
   virtual ~RegulatoryValidationErrorList (void);
   SEVERITY init (const DString& dstrAccountNum , 
                  const DString& dstrFund       , 
                  const DString& dstrDate       , 
                  const DString& dstrTransType  ,
                  const DString& dstrRegulation  =     NULL_STRING,
                  const DString& dstrTrack       =     I_("N"), 
                  const DString& dstrPageName    =     NULL_STRING);

   SEVERITY  doRegulatoryValidations(const DString& dstrAccountNum,                                                                     
                                     const DString& dstrFund, 
                                     const DString& dstrDate,
                                     const BFDataGroupId& idDataGroup, 
                                     const DString& dstrTransType,
                                     const DString& dstrRegulation =     NULL_STRING);

protected:
   void getStrKey (DString &strKey, const BFData *data);
private:
   SEVERITY displayRegulatoryValidationErrors (const BFDataGroupId& idDataGroup, const DString& dstrEWI , 
                                           const DString& dstrRegulation =  NULL_STRING );
   BFData   m_requestData; 
   
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RegulatoryValidationErrorList.hpp-arc  $
//    Rev 1.0  Sep 14 2015 
// Initial revision.
*/

