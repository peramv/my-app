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
//    Copyright 2002 by International Financial.
//
//******************************************************************************

//******************************************************************************
//
// ^FILE   : FeeParamMaintProcess.hpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FeeParamMaintProcess
//    This class manages the Fee Parameters process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc/abstractprocess.hpp>
#include <ifastbp/ifasthistoricalparameters.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE FeeParamMaintProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   FeeParamMaintProcess();
   FeeParamMaintProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FeeParamMaintProcess();
   bool canUpdate();


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


   virtual  bool doRefresh(
                          GenericInterface *rpGICaller,
                          const I_CHAR *szOriginalCommand
                          );


   void *getPtrForContainer(
                           const BFContainerId& idContainer, const BFDataGroupId& idDataGroup
                           );

   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   virtual bool doOk( GenericInterface *rpGICaller );
   const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   void  doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag);
   virtual SEVERITY getHistoricalParameters(const BFContainerId& idContainer, BFFieldId &recordIdField, DString& tableId, DString& dstrKeys);
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );
   SEVERITY doValidateAll(BFAbstractCBO *bfWorkSession, const BFDataGroupId& idDataGroup);

private:
   GenericInterface *_rpChildGI;
   DString m_FeeParamListKey;
   DString m_FeeType;
};

