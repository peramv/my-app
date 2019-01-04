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
// ^FILE   : FeeModelProcess.hpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FeeModelProcess
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

class   FeeModelList; 
class   FeeModelSearchCriteria;

class IFASTBP_LINKAGE FeeModelProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   FeeModelProcess();
   FeeModelProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FeeModelProcess();
   SEVERITY getHistoricalParameters(const BFContainerId &idContainer, BFFieldId &recordIdField, DString &tableId, DString &dstrKeys);
   SEVERITY getHistoricalParameters(const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical);
   virtual SEVERITY ok2(GenericInterface *rpGICaller);
   const DString& getHoldingCompCode() { return m_HoldingCompCode;};

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


/*   void *getPtrForContainer(
                           const BFContainerId& idContainer, const BFDataGroupId& idDataGroup
                           );
*/
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual const BFProperties *doGetFieldAttributes( const GenericInterface *rpGICaller,
                                                    const BFContainerId& idContainer,
                                                    const BFFieldId &idField,
                                                    const BFDataGroupId& idDataGroup );
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   virtual SEVERITY doSetField(
                        const GenericInterface *rpGICaller,
                        const BFContainerId& idContainer,
                        const BFFieldId& idField,
                        const BFDataGroupId& idDataGroup,
                        const DString& strValue,
                        bool bFormatted
                        );
   virtual SEVERITY FeeModelProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                                    E_SEARCHACTION eSearchAction );

   virtual bool doMoreRecordsExist(GenericInterface *rpGICaller,
                                   const BFContainerId& idSearch );

   virtual bool doOk( GenericInterface *rpGICaller );
   const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
//   void  adjustKey();
   void  doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag);
private:
   GenericInterface *_rpChildGI;
   FeeModelList* _pFeeModelList; 
   DString m_dstrEndKey;
   DString m_dstrPrevKey;
   double m_dispNum;
   double m_More;
   double m_totalNum;
   DString m_frSCR;
	DString m_dstrEmptykey;   
   DString m_HoldingCompCode;
   DString m_HoldingCompName;
   DString m_SrcHoldingCompCode;
   DString m_SrcHoldingCompName;
   DString m_SrcFeeModelCode;
   DString m_SrcFeeModelDesc;
   DString m_SearchAll;
   DString m_AsofDate;
   FeeModelSearchCriteria* m_pFeeModelSearchCriteria;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FeeModelProcess.hpp-arc  $
//
//   Rev 1.2   Sep 20 2004 16:26:40   YINGBAOL
//PET1117:FN05 Fix more than 25 records issue
//
//   Rev 1.1   Aug 10 2004 11:11:36   FENGYONG
//PET117 FN5 - Client Condition Fee
//
//   Rev 1.0   Aug 09 2004 10:01:18   FENGYONG
//Initial revision.
//
//   Rev 1.11   Mar 10 2004 13:14:24   HERNANDO
//PET965 FN11 - Added getHistoricalParameters.
//
//   Rev 1.10   Dec 08 2003 15:40:44   HSUCHIN
//PTS 10024902 - bug fix with mfaccount refresh to show updated cautions list.
//
//   Rev 1.9   Aug 18 2003 16:09:20   HERNANDO
//Added keys to getHistoricalParameters.
//
//   Rev 1.8   Mar 21 2003 17:39:40   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Mar 05 2003 11:22:34   PURDYECH
//IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
//
//   Rev 1.6   Jan 29 2003 16:22:08   popescu
//Added the historical button for FeeParamSysDlg and FeeParamDlg
//
//   Rev 1.5   Oct 09 2002 23:53:14   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:52:24   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:21:10   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:17:02   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Feb 22 2002 14:20:38   YINGBAOL
//more function added
 * 
 */
