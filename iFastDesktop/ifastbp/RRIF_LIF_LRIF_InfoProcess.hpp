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


#include <bfproc\abstractprocess.hpp>

// Forward references
//class EntityList;
class RemarksList;
class MFAccount;
class RRIF_LIF_LRIF_InfoList;
//class RRIFFundAllocList;
class RRIF_LIF_LRIF_PaymentsCalculation;


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
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE RRIF_LIF_LRIF_InfoProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   RRIF_LIF_LRIF_InfoProcess();
   RRIF_LIF_LRIF_InfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RRIF_LIF_LRIF_InfoProcess();

protected:
   /**
      * Used to bring a modeless dialog (via parent process) to the top of the
      * window stack.
      * @param rpGICaller - A reference pointer to the calling object.
      * @returns true if successful, check conditions if false
      */
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
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
   virtual bool doModelessChildComplete( const Command &cmd );
   /**
     * Implementation to support the cancel method.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, call getErrors for errors if false
     */
/*   virtual bool doCancel(
      GenericInterface *rpGI
      );*/
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
     * Implementation to support the ok method.  This method would be invoked
     * when the user completes the logon screen.  The logon process will 
     * attempt to logon and return accordingly.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doOk( GenericInterface *rpGI );
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
   //virtual const DString& getFirstListItemKey(
   //   const GenericInterface *rpGICaller,
   //   const BFContainerId& idList
   //   );
   /**
     * This is an override of the virtual function from AbstractProcess. For
     * MFAccountHoldingList, we need a specialized behavior: only interest 
     * accrual funds should be returned by the iterator.
     * This method is used to get the key to the next item in a list.  This 
     * will also set the first item as the current item in the list.
     * An exception will be thrown if the list cannot be found.
     * See note about lists in class document block.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idList - ID of list we are using.
     * @returns the key to the next list item.  This will be an empty string
     * if at the end of the list.
     */
   //virtual const DString& getNextListItemKey(
   //   const GenericInterface *rpGICaller,
   //   const BFContainerId& idList
   //   );
   //virtual void setCurrentListItem( const GenericInterface *rpGICaller,
   //										const BFContainerId& idList, const DString& dstrListItemKey );
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   bool doSend( GenericInterface *rpGICaller, const I_CHAR * szMessage );
   virtual SEVERITY doValidateAll(BFAbstractCBO *rpWSD,  const BFDataGroupId& idDataGroup   );
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );
   virtual void doGetField ( const GenericInterface *rpGICaller,  
                             const BFContainerId &idContainer, 
                             const BFFieldId &idField, 
                             const BFDataGroupId &idDataGroup, 
                             DString &strValueOut, 
                             bool bFormtted) const;

private:
   SEVERITY initLists( const DString& dstrAccountNum );
   //void resetRRIF_LIF_LRIF_AllocList( 
   //										const DString& dstrRRIF_LIF_LRIF_InfoListKey );

   GenericInterface *_rpChildGI;
   DString _strAccountNum;
   DString _strShareholderNum;
   DString _strLastName;
   DString _strFirstName;
   DString _dstrOrgKey;
   DString _dstrDestKey;
   RRIF_LIF_LRIF_InfoList *_pRRIF_LIF_LRIF_InfoList;
   //RRIFFundAllocList *_pRRIF_LIF_LRIF_AllocList;
   RRIF_LIF_LRIF_PaymentsCalculation *_pRRIF_LIF_LRIF_PaymentsCalculation;
};

