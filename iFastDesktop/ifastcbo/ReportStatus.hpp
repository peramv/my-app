//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial
//
//*****************************************************************************
//
// ^FILE   : ReportStatus.hpp
// ^AUTHOR : 
// ^DATE   : Nov 25, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ReportStatus
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class ReportParamList;
class IFASTCBO_LINKAGE ReportStatus : public MFCanBFCbo, private boost::noncopyable
{
   public:
	//******************************************************************************
	// Constructor
	// @param   BFBase - pointer to the parent BFBase
	//******************************************************************************
	ReportStatus( BFAbstractCBO &parent );

	//******************************************************************************
	// Destructor
	//******************************************************************************
	~ReportStatus();

   SEVERITY init ( const BFData& data );

   SEVERITY createReportParamList ( ReportParamList*& pReportParamList, const BFDataGroupId& idDataGroup );

   void getReportParamList ( ReportParamList*& pReportParamList, const BFDataGroupId& idDataGroup );

   SEVERITY printReport ( const DString& dstrPrinterName, const BFDataGroupId& idDataGroup );

   private:
   ReportParamList* _pReportParamList;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReportStatus.hpp-arc  $
//
//   Rev 1.4   Nov 14 2004 14:52:06   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   Mar 21 2003 18:21:32   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Dec 08 2002 22:05:56   HSUCHIN
//implemented printreport method
//
//   Rev 1.1   Nov 29 2002 14:52:16   HSUCHIN
//check in for rel 50
//
//   Rev 1.0   Nov 27 2002 11:40:44   HSUCHIN
//Initial Revision
*/