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
//    Copyright 2005 by IFDS.
//
//******************************************************************************
//
// ^FILE   : EntityAloneProcess.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 01/29/2005
//
// ----------------------------------------------------------

#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include "iFastHistoricalParameters.hpp"

class EntityList;
class EntitySearchList;
class IFASTBP_LINKAGE EntityAloneProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
   EntityAloneProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~EntityAloneProcess();

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
 
   virtual  bool doRefresh(
                          GenericInterface *rpGICaller,
                          const I_CHAR *szOriginalCommand
                          );

   void *getPtrForContainer( const BFContainerId& idContainer, 
                            const BFDataGroupId& idDataGroup
                           );
   bool doModelessSetFocus( GenericInterface *rpGICaller );
   bool doModelessChildComplete( const Command &cmd );
   virtual SEVERITY getHistoricalParameters(
      const BFContainerId &idContainer, 
      BFFieldId &recordIdField, 
      DString &tableId, 
      DString &dstrKeys);

   virtual void  doGetField(
                               const GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId& idField,
                               const BFDataGroupId& idDataGroup,
                               DString &strValueOut,
                               bool bFormatted
                               ) const;

   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );


   SEVERITY performSearch( GenericInterface *rpGI, 
                                           const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
private:
   SEVERITY  populateWorkSessionEntityList( );
   SEVERITY populateEntityByKey(const DString dstrKey = NULL_STRING  );
   DString _entity_id,_searchUsing,_firstValue,_secondValue;
   GenericInterface *_rpChildGI;
   EntitySearchList*    _pEntitySearchList;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EntityAloneProcess.hpp-arc  $
//
//   Rev 1.1   Mar 09 2005 16:07:24   yingbaol
//PET1171,FN01:EU saving entity update
//
//   Rev 1.0   Mar 01 2005 09:57:04   yingbaol
//Initial revision.
 * 
 *
 */
