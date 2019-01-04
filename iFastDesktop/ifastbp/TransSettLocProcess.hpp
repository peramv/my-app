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
//    Copyright 2003 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TransSettLocProcess.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 10, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransSettLocProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>
///#endif

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class TransSettleLoc;

class IFASTBP_LINKAGE TransSettLocProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   TransSettLocProcess( GenericInterfaceContainer* pGIC, 
		                  GenericInterface* pGIParent, 
								const Command& rCommand );
   virtual ~TransSettLocProcess();

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
     * This is a method which may be overridden by a subclass to set container
     * pointers on demand.  This method is invoked whenever an attempt is
     * about to be made to use a container that hasn't been set yet.  The
     * pointer returned will be used to set the container pointer.
     * @param idList - ID of list to set pointer for.
     * @param idDataGroup - group ID currently being used.
     * @returns void pointer of list to use.
     */
   void *getPtrForContainer( const BFContainerId& idContainer,
                           const BFDataGroupId& idDataGroup );

   /**
     * This method is optional but must be overridden in the subclasses to 
     * support modeless child dialogs calling the modelessChildComplete method.
     * This method should not ever be called if the subclass has not overridden
     * it.  modelessChildComplete is used by the GenericInterfaceContainer to
     * tell the parent that the modeless child has been destroyed.
     * @param cmd - A reference to a command representing the object that has
     * been destroyed.
     * @returns true if this modeless object should end as well, false if not
     * done yet.  When returning true, the calling modelessChildComplete method
     * will call GenericInterfaceContainer::modelessDestroySelf to delete and
     * remove this object from the container
     */
   bool doModelessChildComplete( const Command &cmd );

   /**
     * This method is optional - override if subclass needs to be able to
     * relay the set focus to a child dialog.
     * Used to bring a modeless dialog (via parent process) to the top of the
     * window stack.  Note that if the process needs to change its state due
     * to a change in input parameters, then this would occur here and the
     * process would notify the child dialog of the need to refresh.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, check conditions if false
     */
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );   		

	bool doOk( GenericInterface* rpGICaller );   	

private:
	GenericInterface *_rpChildGI;      
	TransSettleLoc *_pFromTransSettleLoc;
	TransSettleLoc *_pToTransSettleLoc;

	// These 2 flags are kinda silly, just want to make sure we don't crash while deleting
	bool _blFromTransSettleLocCreated;
	bool _blToTransSettleLocCreated;
	
	bool _blUpdateableLocation;

	DString _dstrFromAccount;	
	DString _dstrFromScreen;
	DString _dstrPendingHist;
	DString _dstrMainListKey;
	DString _dstrFromClearingAccount;
	DString _dstrToClearingAccount;
	DString _dstrTransType;

	DString _dstrAccountTo;
	DString _dstrAccount;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/TransSettLocProcess.hpp-arc  $
//
//   Rev 1.2   Nov 27 2003 13:22:40   VADEANUM
//PET859 FN1 - Settlement Location at Trade Level support.
//
//   Rev 1.1   Nov 25 2003 11:50:40   VADEANUM
//PET859 FN1 - Settlement Location at Trade Level support - work in progress.
//
//   Rev 1.0   Nov 10 2003 15:24:06   VADEANUM
//Initial revision.
//
