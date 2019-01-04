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
// ^FILE   : RegPlanTransferProcess.hpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ----------------------------------------------------------
//
// ^CLASS    : RegPlanTransferProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

// Forward references
class RegPlanTransferList;
class MFAccount;
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastbp\ifasthistoricalparameters.hpp>

/**
 * Class that manages the entity process.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE RegPlanTransferProcess : public AbstractProcess,
      public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   RegPlanTransferProcess();
   RegPlanTransferProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RegPlanTransferProcess();
   SEVERITY getNext();
   SEVERITY copyData( GenericInterface *rpGI, const DString& fromKey, const DString& toKey );

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
   virtual bool doRefresh( GenericInterface *rpGICaller,
                           const I_CHAR *szOriginalCommand );
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
   
   void doPostOk( GenericInterface *rpGICaller,
                   bool bSuccessFlag );

   SEVERITY doSetField( const GenericInterface *rpGICaller,
                        const BFContainerId& idContainer,
                        const BFFieldId& idField,
                        const BFDataGroupId& idDataGroup,
                        const DString& strValue,
                        bool bFormatted );

   /**
     * Search a proper entity and get the DofBirth of that entity base on
     * Business rule.
     * @param strDofBirth - The DofBirth which will be passed to CBO for validating.
     */
   void GetDofBirth( const BFDataGroupId& idDataGroup, DString &strDofBirth );
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;


   const BFProperties *doGetFieldAttributes( const GenericInterface *rpGICaller, 
                                             const BFContainerId& idContainer, 
                                             const BFFieldId& idField, 
                                             const BFDataGroupId& idDataGroup );

   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );
   void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
   
   virtual bool doMoreRecordsExist(GenericInterface *rpGICaller,
                                   const BFContainerId& idSearch );

   virtual bool doOk (GenericInterface* rpGICaller);
   
   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

private:

   // Private member function

   // Private member data
   RegPlanTransferList *_pRegPlanTransferList;
   GenericInterface *_rpChildGI;
   MFAccount* _pMFAccount;
   DString _strAccountNum;
   DString strShareholdNum;
   DString strKey;
   DString strTransIdEmpty;
//   DString strDofBirth;
//   DString strEntityType;
   DString strSeqNumber;
   DString _dstrOrgKey;
   DString _dstrDestKey;
   DString _dstrSpouseName;
   DString _dstrAskDofBirthSp;
   DString _dstrAskDofBirthEntity;
   DString _dstrOwnerName;
   DString _dstrEntityIdOw;
   DString _dstrEntityIdSp;
   DString _dstrNewShareholder;
   DString _dstrNewAccount;
   bool _bIsDuringNASU;
};

///#endif 

