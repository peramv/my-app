#pragma once
//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : ReportStatusCriteria.hpp
// ^AUTHOR : 
// ^DATE   : Nov 27, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ReportStatusCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "mfcancbo.hpp"
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class ReportStatusList;
class IFASTCBO_LINKAGE ReportStatusCriteria : public MFCanBFCbo, private boost::noncopyable
{
   public:
   //*****************************************************************************
   // Constructor
   //*****************************************************************************
   ReportStatusCriteria( BFAbstractCBO &parent );

   //*****************************************************************************
   // Destructor
   //*****************************************************************************
   ~ReportStatusCriteria();

   //*****************************************************************************
   //*****************************************************************************
   void init( const BFDataGroupId& idDataGroup );

   SEVERITY getReportStatusList ( ReportStatusList*& pReportStatusList, const BFDataGroupId& idDataGroup );

   SEVERITY createReportStatusList ( ReportStatusList*& pReportStatusList, const BFDataGroupId& idDataGroup );   

   private:

   SEVERITY createMgmtCoSubList ( DString& dstrSubList );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReportStatusCriteria.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:52:08   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Mar 21 2003 18:21:36   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Nov 29 2002 13:51:38   HSUCHIN
//Initial Revision
*/
