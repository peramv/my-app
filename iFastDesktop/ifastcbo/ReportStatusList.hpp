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
// ^FILE   : ReportStatusList.hpp
// ^AUTHOR : 
// ^DATE   : Nov 25, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ReportStatusList
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

class IFASTCBO_LINKAGE ReportStatusList : public MFCanBFCbo, private boost::noncopyable
{
   public:
	//******************************************************************************
	// Constructor
	// @param   BFBase - pointer to the parent BFBase
	//******************************************************************************
	ReportStatusList( BFAbstractCBO &parent );

	//******************************************************************************
	// Destructor
	//******************************************************************************
	~ReportStatusList();

	//******************************************************************************
	//******************************************************************************
	SEVERITY init( const DString& dstrCompanyId,
                  const DString& dstrStartDate,
                  const DString& dstrEndDate,
				      const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

	//******************************************************************************
	// getMore retrieves more data.
	// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
	//                    SEVERE_ERROR if the accural type is not defined to be
	//                    INTEREST_ACCRUAL/MF_ACCRUAL/MF_REBATE_ACCRUAL
	//******************************************************************************
	SEVERITY getMore( );

   void getCompanyId ( DString& dstrCompanyId );

   protected:

   SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );

   private:
   BFData* _pRequestData;
   DString _dstrCompanyId;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReportStatusList.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:52:10   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Dec 08 2002 22:08:38   HSUCHIN
//added method to get company id
//
//   Rev 1.1   Nov 29 2002 14:51:50   HSUCHIN
//check in for 50
//
//   Rev 1.0   Nov 27 2002 11:40:46   HSUCHIN
//Initial Revision
*/