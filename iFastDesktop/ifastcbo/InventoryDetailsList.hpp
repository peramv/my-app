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
//    Copyright 2003 by International Financial.
//
//******************************************************************************
//
// ^FILE   :InventoryDetailsList
// ^DATE   : 
//
// ^CLASS  : InventoryDetailsList
// ^PARENT : ListBase
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

class BFData;

class IFASTCBO_LINKAGE InventoryDetailsList : public MFCanBFCbo, private boost::noncopyable
{
public:

   //******************************************************************************
   // Constructor
   // @param   BFBase - pointer to the parent BFBase
   //******************************************************************************

   InventoryDetailsList( BFAbstractCBO &parent );

   //******************************************************************************
   // Destructor
   //******************************************************************************

   virtual ~InventoryDetailsList();

   //******************************************************************************
   // Overloaded Function - Initalize CBO and executes view call
   // @param   const DString& dstrInvSummId - Inventory Summary ID ( Required )
   // @param   const DString& dstrTrack - Tracking flag ( used by eAdvisor )
   // @param   const DString& dstrPageName - Page Name value ( used by eAdvisor )
   // @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
   //******************************************************************************

   SEVERITY init( const DString& dstrInvSummId, 
                  const DString& dstrTrack= I_("N"),                  
                  const DString& dstrPageName = NULL_STRING );

   //******************************************************************************
   // getMore retrieves more data.
   // @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.   
   //******************************************************************************

   SEVERITY getMore ( );   

private:

   BFData *_pRequestData;                //Stores the request data object to be used by getMore
	BFData *_pResponseData;
};

///#endif //INVENTORYDETAILSLIST_HPP

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InventoryDetailsList.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:48:40   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   May 06 2004 16:48:58   HERNANDO
//Initial revision.
*/