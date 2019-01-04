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
//    Copyright 2003 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : MktIndexFunds.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MktIndexFunds
// ^SUBCLASS :  
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE MktIndexFunds : public MFCanBFCbo
{
public:

   MktIndexFunds( BFAbstractCBO &parent );
   virtual ~MktIndexFunds( void );

   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY initExisting(const BFData &data);

protected:

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );

private :

	void checkUpdatePermission(const BFDataGroupId& idDataGroup);
   SEVERITY validateFundCode( const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateClassCode( const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateFundClass( const BFDataGroupId& idDataGroup ); 
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexFunds.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:50:30   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Mar 21 2003 18:19:14   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Jan 23 2003 10:31:50   HERNANDO
//Initial Revision
*/