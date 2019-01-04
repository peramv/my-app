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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : JEntityProcess.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : JEntityProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class JEntityList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the entity process.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE JEntityProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   JEntityProcess();
   JEntityProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~JEntityProcess();

protected:
   virtual bool doGetData(
                         GenericInterface * rpGICaller=NULL,
                         BFData * rpData=NULL
                         ) const;
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
     * Implementation to support the modelessChildComplete method.
     * modelessChildComplete is used by the GenericInterfaceContainer to tell
     * the parent that the modeless child has been destroyed.
     * @param cmd - A reference to a command representing the object that has
     * been destroyed.
     * @returns true if this modeless object should end as well, false if not
     * done yet.  When returning true, the calling modelessChildComplete method
     * will call GenericInterfaceContainer::modelessDestroySelf to delete and
     * remove this object from the container
     */
//   virtual bool doMoreRecordsExist(
//      GenericInterface *rpGICaller,
//      int 
//      );
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();

private:
  
   GenericInterface *_rpChildGI;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JEntityProcess.hpp-arc  $
//
//   Rev 1.7   Sep 28 2004 10:31:10   YINGBAOL
//PET1145 FN01 Entity update
//
//   Rev 1.6   Mar 21 2003 17:43:44   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:53:24   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   22 May 2002 18:20:38   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:17:46   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   Aug 13 2000 12:27:44   YINGZ
//call JEntityList
//
//   Rev 1.1   Aug 11 2000 14:25:36   FENGYONG
//use AccountEntityXref replace EntityList
 *
 */
