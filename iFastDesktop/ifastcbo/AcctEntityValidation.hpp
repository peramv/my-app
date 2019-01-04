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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctEntityValidation.hpp
// ^AUTHOR : Shashi Kant
// ^DATE   : August, 2012
//
// ^CLASS    : AcctEntityValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <SrcPrag.h>
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AcctEntityValidation : public MFCanBFCbo, private boost::noncopyable
{
public:

   AcctEntityValidation( BFAbstractCBO &parent );
   virtual ~AcctEntityValidation();
   SEVERITY init (const DString &strAccountNum, 
					const DString &strTaxType, 
					const DString &strEntityId, 
					const DString &strNationalID, 
					const DString &strCOINationalID, 
					const DString &dstrPassport, 
					const DString &dstrCOIPassport);   

};

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctEntityValidation.hpp-arc  $
//
//   Rev 1.0   Aug 15 2012 13:53:46   wp040027
//Initial revision.
//