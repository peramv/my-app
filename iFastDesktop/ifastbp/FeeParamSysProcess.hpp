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
// ^FILE   : FeeParamSysProcess.hpp
// ^AUTHOR : Yingbao  Li, May Lin
// ^DATE   : January 10, 2002  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FeeParamSysProcess
//    This class manages the Fee Parameters process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc/abstractprocess.hpp>
#include <ifastbp/ifasthistoricalparameters.hpp>

// Forward references
class FeeParamSysList; 

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE FeeParamSysProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   FeeParamSysProcess();
   FeeParamSysProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   bool doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage);
   virtual ~FeeParamSysProcess();

   bool hasTransactionUpdates();
   SEVERITY ok2(GenericInterface *rpGICaller);
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


   virtual  bool doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand );


   void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doModelessChildComplete( const Command &cmd );

   virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller,  const BFContainerId& idSearch ); 
   virtual bool doOk( GenericInterface *rpGICaller );

	virtual void doGetField( const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted ) const;

	virtual SEVERITY   doSetField( const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId& idField,
                                  const BFDataGroupId& idDataGroup,
                                  const DString& strValue,
                                  bool bFormatted );

	virtual bool setCommitDataGroupAsHost()
	{
		return(true);
	};

   virtual SEVERITY getHistoricalParameters(const BFContainerId& idContainer, BFFieldId &recordIdField, DString& tableId, DString& dstrKeys);
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:
   GenericInterface *_rpChildGI;
   FeeParamSysSearchCriteria* _pFeeParamSysSearchCriteria;
   FeeParamSysList* _pFeeParamSysList;
//   DString       m_dstrBaseFilter;
   DString m_FeeModelCode;
   DString m_HoldingCompCode;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FeeParamSysProcess.hpp-arc  $
//
//   Rev 1.11   Mar 10 2004 13:17:24   HERNANDO
//PET965 FN11 - Added getHistoricalParameters.
//
//   Rev 1.10   Aug 18 2003 16:09:36   HERNANDO
//Added keys to getHistoricalParameters.
//
//   Rev 1.9   Jun 20 2003 16:18:26   linmay
//added fileterstr
//
//   Rev 1.8   Mar 21 2003 17:39:46   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Mar 05 2003 11:22:40   PURDYECH
//IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
//
//   Rev 1.6   Jan 29 2003 16:22:20   popescu
//Added the historical button for FeeParamSysDlg and FeeParamDlg
//
//   Rev 1.5   Jan 29 2003 15:48:46   YINGBAOL
//added setCommitDataGroupAsHost
//
//   Rev 1.4   Jan 18 2003 17:20:10   YINGBAOL
//implemet check update FeeParamSysList
//
//   Rev 1.3   Jan 15 2003 16:20:06   linmay
//added doOK()
//
//   Rev 1.2   Jan 15 2003 11:53:08   linmay
//added log comment
// 
*/