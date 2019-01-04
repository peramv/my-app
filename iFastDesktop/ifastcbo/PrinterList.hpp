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
// ^FILE   : PrinterList.hpp
// ^AUTHOR : 
// ^DATE   : Nov 25, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : PrinterList
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

class IFASTCBO_LINKAGE PrinterList : public MFCanBFCbo, private boost::noncopyable
{
   public:
	//******************************************************************************
	// Constructor
	// @param   BFBase - pointer to the parent BFBase
	//******************************************************************************
	PrinterList( BFAbstractCBO &parent );

	//******************************************************************************
	// Destructor
	//******************************************************************************
	~PrinterList();

	//******************************************************************************
	//******************************************************************************
	SEVERITY init( const DString& dstrCompanyId,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

	//******************************************************************************
	// getMore retrieves more data.
	// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
	//                    SEVERE_ERROR if the accural type is not defined to be
	//                    INTEREST_ACCRUAL/MF_ACCRUAL/MF_REBATE_ACCRUAL
	//******************************************************************************
	SEVERITY getMore( );

   private:
   BFData* _pRequestData;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PrinterList.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:51:10   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Mar 21 2003 18:20:16   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Dec 08 2002 22:04:42   HSUCHIN
//added companyid to init
//
//   Rev 1.0   Nov 27 2002 11:40:42   HSUCHIN
//Initial Revision
*/