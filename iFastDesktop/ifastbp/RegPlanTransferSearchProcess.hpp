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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RegPlanTransferSearchProcess.hpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ----------------------------------------------------------
//
// ^CLASS    : RegPlanTransferSearchProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

// Forward references
class RegPlanTransferList;
class RegPlanTransferSearchCriteria;

class MFAccount;
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

class IFASTBP_LINKAGE RegPlanTransferSearchProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   RegPlanTransferSearchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RegPlanTransferSearchProcess();
   SEVERITY getNext();
   bool doSend( GenericInterface* rpGICaller,const I_CHAR* szMessage );
   void doGetField(const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& fieldID, const BFDataGroupId& idDataGroup, DString &strValueOut, bool bFormatted ) const;

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


   const BFProperties *doGetFieldAttributes( const GenericInterface *rpGICaller, 
                                             const BFContainerId& idContainer, 
                                             const BFFieldId& idField, 
                                             const BFDataGroupId& idDataGroup );

   void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
   
   virtual bool doMoreRecordsExist(GenericInterface *rpGICaller,
                                   const BFContainerId& idSearch );

   
   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
   bool doModelessChildComplete( const Command &cmd );

private:

   // Private member function

   // Private member data
   RegPlanTransferList* pRegPlanTransferList;
   RegPlanTransferSearchCriteria* pSearchCriteria;
   GenericInterface *_rpChildGI;
   DString strKey;
   DString strSeqNumber;
};

///#endif 

