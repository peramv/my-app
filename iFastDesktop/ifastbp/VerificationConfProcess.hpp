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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class VerificationConf;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE VerificationConfProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   VerificationConfProcess();
   VerificationConfProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~VerificationConfProcess();

protected:
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   /**
     * Implementation for the refresh method.  Not implemented yet.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(
                         GenericInterface *rpGICaller,
                         const I_CHAR *szOriginalCommand
                         )
   {
      return(false);
   }
private:
/*
   typedef std::map< DString, DString, std::less< DString > >  PARAM_MAP;
   typedef PARAM_MAP::iterator                                 PARAM_MAP_ITER;
   typedef PARAM_MAP::value_type                               PARAM_MAP_VALUE_TYPE;

   PARAM_MAP _params;
  */

   VerificationConf *_pVerificationConf;
   GenericInterface *_rpChildGI;
   void RIPFileOut();
   void ExtractValue( DString &dstrField, DString &dstrValue, DString &dstrInStream);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/VerificationConfProcess.hpp-arc  $
//
//   Rev 1.8   Mar 21 2003 17:50:02   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 23:53:44   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   19 Mar 2002 13:20:14   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.5   Nov 24 2000 14:52:54   HSUCHIN
//Added RIP Processing output.  Output is template driven
//
//   Rev 1.4   Oct 11 2000 15:32:44   VASILEAD
//Took out ServerData
//
//   Rev 1.2   Aug 08 2000 13:44:00   YINGZ
//add VerificationStringProcessor
//
//   Rev 1.1   Aug 03 2000 14:41:52   VASILEAD
//Added tracking support to VerifConf
//
//   Rev 1.0   Jul 26 2000 09:37:34   VASILEAD
//Initial revision.
 * 
 *    Rev 1.2   Mar 24 2000 12:22:50   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.1   Feb 29 2000 15:29:30   FENGYONG
// Add CurrentDate
// 
//    Rev 1.0   Nov 24 1999 09:26:36   FENGYONG
// Initial revision.
 * 
 *
 */

