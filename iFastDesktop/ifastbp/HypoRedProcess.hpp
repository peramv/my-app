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
//    Copyright 2002 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : HypoRedProcess.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/29/2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : HypoRedProcess
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

class IFASTBP_LINKAGE HypoRedProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   HypoRedProcess();
   HypoRedProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~HypoRedProcess();
   bool hasChargeBackFund();

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
   void *getPtrForContainer(
                           const BFContainerId& idContainer,
                           const BFDataGroupId& idDataGroup
                           );

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
   bool doModelessChildComplete(
                               const Command &cmd
                               );

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
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   /**
    * virtual function. Should be overwritten in order to do CBO level validation
    * @param idDataGroup   - the identifier of the data group with which we want the object validated
    * @param lValidateGroup - the validation group for which we want to validate
   */
   SEVERITY doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup );
	/**
     * This method implements the base functionality for ok processing,
     * including committing all updated groups and submitting a transaction,
     * if required.  This may be overridden if the derived process needs more
     * than the base functionality.
     * @param rpGICaller - A reference pointer to the calling GenericInterface.
     * returns returns highest SEVERITY encountered, check conditions
     */
   SEVERITY ok2(
      GenericInterface *rpGICaller
      );
   /**
     * This method is used to implement subclass overrides for getField.  The business
     * process must determine where to locate the field.
     * Override this method and set appropriate flags via addFieldDetails,
     * if the derived class must process getField differently than this
     * base class does.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param fieldID - ID of field we are getting.
     * @param idDataGroup - group ID to use for CBO processing
     * @param strValue - A string reference where value is returned.
     * @param bFormatted - Flag where true means get data formatted.
     */
   void doGetField(
      const GenericInterface *rpGICaller,
      const BFContainerId& idContainer,
      const BFFieldId& fieldID,
      const BFDataGroupId& idDataGroup,
      DString &strValueOut,
      bool bFormatted
      ) const;
	/**
     * This method is used to implement subclass overrides for setField.  The business
     * process must determine where to locate the field.
     * Override this method and set appropriate flags via addFieldDetails,
     * if the derived class must process setField differently than this
     * base class does.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param fieldID - ID of field we are getting.
     * @param idDataGroup - group ID to use for CBO processing
     * @param strValue - A string reference for the value of the field to be
     * set.
     * @param bFormatted - Flag where true means incoming data is formatted.
     * @returns SEVERITY indicating any errors/warnings encountered.
     */
   SEVERITY doSetField(
      const GenericInterface *rpGICaller,
      const BFContainerId& idContainer,
      const BFFieldId& fieldID,
      const BFDataGroupId& idDataGroup,
      const DString& strValue,
      bool bFormatted
      );
private:
   DString _strAccountNum;
   GenericInterface *_rpChildGI;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HypoRedProcess.hpp-arc  $
//
//   Rev 1.2   Mar 21 2003 17:41:30   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 22 2002 16:56:58   KOVACSRO
//Added implementation.
//
//   Rev 1.0   Oct 29 2002 10:54:14   KOVACSRO
//Initial Revision
// 

  */