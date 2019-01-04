#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : Branch.hpp
// ^AUTHOR : 
// ^DATE   : Mar 04, 2003
//
// ^CLASS    : Branch
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

class IFASTCBO_LINKAGE Branch : public MFCanBFCbo, private boost::noncopyable
{

public:   

   //****************************************************************************
   // Constructor
   //****************************************************************************
   Branch( BFAbstractCBO &parent );

   //****************************************************************************
   // Destructor
   //****************************************************************************
   ~Branch();  

   //****************************************************************************
   //Initializes the CBO
   //@param const BFData& InstData - Data object to attach to BranchList.
   //@returns SEVERITY
   //****************************************************************************   
   SEVERITY init( const BFData& InstData ); 

   //****************************************************************************
   //Compares the date passed in with the effective and stop date of the Branch.
   //Returns NO_CONDITION when the date passed in is within the effective and stop
   //date range.
   //@param const DString& dstAsOfDate - Date to compare to.
   //       const BFDataGroupId& idDataGroup - current data group id.
   //@returns SEVERITY - ERR_BRANCH_INVALID_AS_OF_DATE - date is later than stop date
   //                    ERR_BRANCH_NOT_EFFECTIVE - date is before effective date.
   //****************************************************************************
   SEVERITY checkEffective( const DString& dstrAsOfDate, const BFDataGroupId& idDataGroup );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Branch.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:29:12   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Mar 21 2003 18:00:54   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Mar 05 2003 12:04:48   HSUCHIN
//Initial revision.
 */