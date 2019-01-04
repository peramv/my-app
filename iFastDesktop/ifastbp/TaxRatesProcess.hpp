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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TaxRatesProcess.hpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 12/13/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : TaxRatesProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

// Forward references
class TaxRatesList;

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

class IFASTBP_LINKAGE TaxRatesProcess : public AbstractProcess
{
public:
//CP20030319   TaxRatesProcess();
   TaxRatesProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~TaxRatesProcess();

   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, 
                                    const BFContainerId& idContainer );
   virtual bool doGetData( GenericInterface * rpGICaller=NULL, BFData * rpData=NULL ) const;
   SEVERITY performSearch( GenericInterface *rpGICaller, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

protected:
   virtual bool doCancel( GenericInterface *rpGI  );
   virtual SEVERITY doInit();
   virtual bool doOk( GenericInterface *rpGI );
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doModelessChildComplete( const Command &cmd );

private:
   TaxRatesList *_pTaxRatesList;
   GenericInterface *_rpChildGI;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TaxRatesProcess.hpp-arc  $
 * 
 *    Rev 1.6   Mar 21 2003 17:49:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:53:40   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   22 May 2002 18:19:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:18:52   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Mar 22 2000 09:02:38   PETOLESC
 * Added Tax Rates and RESP dialogs.
 * 
 *    Rev 1.1   Feb 15 2000 18:56:52   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:24   SMITHDAV
 * Initial revision.
// 
//    Rev 1.3   Jan 17 2000 11:12:22   PETOLESC
// Minor code cleanup.
// 
//    Rev 1.1   Dec 30 1999 10:11:36   PETOLESC
// Cleaned the code.
// 
//    Rev 1.0   Dec 29 1999 17:25:14   PETOLESC
// Initial revision.
 * 
 *
 */
