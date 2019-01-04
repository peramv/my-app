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
//    Copyright 2002 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AMSDeltaAlloc.hpp
// ^AUTHOR : Thanisorn Sangkrajang
// ^DATE   : Jan. 10, 2018
//
// ^CLASS    : AMSDeltaAlloc
// ^SUBCLASS :  AbstractFundAlloc
//
// ^CLASS DESCRIPTION : AMS Hypothetical report proposed fund allocation.
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

class IFASTCBO_LINKAGE AMSDeltaAlloc : public MFCanBFCbo
{
public:
   // X-structors
   AMSDeltaAlloc( BFAbstractCBO &parent );
   virtual ~AMSDeltaAlloc( void );

   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY initExisting(const BFData &data);

protected:

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
	
private :
	
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AMSDeltaAlloc.hpp-arc  $
//   Rev 1.0   Jan 10 2018 - Thanisorn S.
//Initial Revision
*/