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
// ^FILE   : AccountContractList.hpp
// ^AUTHOR : 
// ^DATE   : Jan 9, 2002
//
// ^CLASS  : AccountContractList
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

class IFASTCBO_LINKAGE AccountContractList : public MFCanBFCbo, private boost::noncopyable
{
public:

   //******************************************************************************
   // Constructor
   // @param   BFBase - pointer to the parent BFBase
   //******************************************************************************

   AccountContractList( BFAbstractCBO &parent );

   //******************************************************************************
   // Destructor
   //******************************************************************************

   virtual ~AccountContractList();

   //******************************************************************************
   // Overloaded Function - Initalize CBO and executes view call
   // @param   const DString& dstrAccountNumber - Account Number ( Required )
   // @param   const DString& dstrFundCode - Fund Code 
   // @param   const DString& dstrClassCode - Class Code 
   // @param   const DString& dstrTrack - Tracking flag ( used by eAdvisor )
   // @param   const DString& dstrPageName - Page Name value ( used by eAdvisor )
   // @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
   //******************************************************************************

   SEVERITY init( const DString& strAccountNumber, 
                  const DString& dstrFundCode,
                  const DString& dstrClassCode,
                  const DString& dstrTrack= I_("N"),                  
                  const DString& dstrPageName = NULL_STRING );

   //******************************************************************************
   // getMore retrieves more data.
   // @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.   
   //******************************************************************************

   SEVERITY getMore ( );   

private:

   BFData *_pRequestData;                //Stores the request data object to be used by getMore
};

///#endif //ACCOUNTCONTRACTLIST_HPP

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountContractList.hpp-arc  $
//
//   Rev 1.1   Mar 21 2003 17:53:54   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Jan 17 2003 13:30:24   HSUCHIN
//Initial Revision
*/