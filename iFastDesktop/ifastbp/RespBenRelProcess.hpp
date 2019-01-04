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


#include <bfproc\AbstractProcess.hpp>
///#endif

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//Forward references

class EntityIdsList;
class AccountEntityXref;


class IFASTBP_LINKAGE RespBenRelProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   RespBenRelProcess();
   RespBenRelProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RespBenRelProcess();

   const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   void setCurrentListItem( const GenericInterface *rpGICaller,
                            const BFContainerId& idList,
                            const DString& strListItemKey
                          );
protected:

   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   // virtual bool doModelessChildComplete( const Command &cmd );
   // virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
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

   void updateRESPPISeqs(const GenericInterface *rpGICaller);
   bool doSend( GenericInterface * rpGICaller, const I_CHAR * szMessage );
   SEVERITY doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup );

private:


   DString _strEmpty;         // Used only to return an empty string reference
   AccountEntityXref *_pAccountEntityXref;
   DString _strAccountNumber;
   DString _strCurrentRespBenName;
   DString _strCurrEntityId;//parameter pased by the calling window
   GenericInterface *_rpChildGI;
   DString strRESPParentSeq;
   DString strRESPDesInstSeq;
   bool bDesInsDisplayed;//keeps track if the designated institution is in the Entities joined to beneficiary or not

};


