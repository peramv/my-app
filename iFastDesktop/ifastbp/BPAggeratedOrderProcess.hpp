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
//    Copyright 2005 by DST IFDS Inc.
//
//******************************************************************************
//
// ^FILE   : BPAggregatedOrderProcess.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 01/15/2005
//
// ----------------------------------------------------------
//
// ^CLASS    : BPAggregatedOrderProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

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
 * @author   Yingbao Li 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 01/15/2005</dd></dl>
 * @version 0.1
 */


class IFASTBP_LINKAGE BPAggregatedOrderProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   BPAggregatedOrderProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~BPAggregatedOrderProcess();

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
 
  virtual bool doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand);
  virtual bool doOk( GenericInterface* rpGICaller );
     

private:


};


///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/*



 *
 */
