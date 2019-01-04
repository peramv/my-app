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
//    Copyright 2018 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BICCodeWarnMSG.hpp
// ^AUTHOR : 
// ^DATE   : 10 May 2018
//
// ^CLASS    : BICCodeWarnMSG
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

class IFASTCBO_LINKAGE EntitySearchIDValueValidation : public MFCanBFCbo, private boost::noncopyable
{

public:
	EntitySearchIDValueValidation(BFAbstractCBO &parent);
	virtual ~EntitySearchIDValueValidation();

	   SEVERITY init( const DString &SrchEntType, 
					const DString &SrchIdType,
					const DString &SrchEntityIDs,
					const DString &dstrTrack = I_("N"), 
					const DString &dstrPageName = NULL_STRING
				  );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Transfer.hpp-arc  $*/

