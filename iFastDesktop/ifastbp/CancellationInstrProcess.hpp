#pragma once



//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : CancellationInstrProcess.hpp
// ^AUTHOR : 
// ^DATE   : 02/15/2005
//
// ----------------------------------------------------------
//
// ^CLASS    : CancellationInstrProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class TransCancellist;
class TransCancel;

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

class IFASTBP_LINKAGE CancellationInstrProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   CancellationInstrProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~CancellationInstrProcess();
protected:
   /**
     * Provide class specific implementation for some fields.
     * An exception will be thrown if the field cannot be found.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param strValue - A string reference where value is returned.
     * @param bFormatted - Flag where true means get data formatted.
     */
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
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
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();

   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );

   void * getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );   
   
   SEVERITY processParameters();
   SEVERITY performSearch (GenericInterface *rpGICaller, 
						   const BFContainerId& idSearch, 
						   E_SEARCHACTION eSearchAction );

	bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );

	bool doOk(GenericInterface *rpGICaller);

	virtual bool doSend( GenericInterface* rpGICaller, const I_CHAR * szMessage );

private:
  
	DString m_dstrSearchType;
	DString m_dstrSearchUsing;
	DString m_dstrTranStatus;
	DString m_dstrAdjustType;
   TransCancellist *_pTransCancellist;
   GenericInterface *_rpChildGI;
	CancelInstrSearchCriteria *_pCancelInstrSearchCriteria;
};

///#endif 



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/CancellationInstrProcess.hpp-arc  $
//
//   Rev 1.3   Nov 30 2005 13:09:46   porteanm
//PET1286 FN01 - Bulk Cancellation.
//
//   Rev 1.2   Nov 24 2005 16:19:52   porteanm
//PET1286 FN01 - Bulk Cancellation.
//
//   Rev 1.1   Nov 11 2005 16:56:40   ZHANGCEL
//PET 1286 FN01 - Make it works properly for Cancellation Instruction
//
//   Rev 1.0   Nov 04 2005 11:39:58   ZHANGCEL
//Initial revision.
 */
