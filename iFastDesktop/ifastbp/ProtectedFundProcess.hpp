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
//    AUTHOR : Serban Popescu
//    DATE   : 01/08/2003
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Forward references
class ProtectedFundList;
class BFFieldId;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the ProtectedFundList process
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 01/08/2003</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE ProtectedFundProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
//CP20030319   ProtectedFundProcess();
   ProtectedFundProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ProtectedFundProcess();
protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual bool setCommitDataGroupAsHost();
   virtual SEVERITY getHistoricalParameters(const BFContainerId& idContainer,
      BFFieldId &recordIdField, DString& tableId, DString& dstrKeys);
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:
   ProtectedFundList *_pProtectedFundList;
   GenericInterface *_rpChildGI;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ProtectedFundProcess.hpp-arc  $
//
//   Rev 1.8   Mar 10 2004 13:19:10   HERNANDO
//PET965 FN11 - Added getHistoricalParameters.
//
//   Rev 1.7   Aug 18 2003 16:10:20   HERNANDO
//Added keys to getHistoricalParameters.
//
//   Rev 1.6   Mar 21 2003 17:46:14   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Mar 05 2003 11:22:50   PURDYECH
//IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
//
//   Rev 1.4   Jan 28 2003 13:15:58   popescu
//Historical Info feature implementation
//
//   Rev 1.3   Jan 22 2003 15:52:44   popescu
//Fixes related with not being able to commit the changes to backend if the dialog ProtectedFundDialog is modal
//
//   Rev 1.2   Jan 20 2003 15:43:28   popescu
//Checked in for unit testing the ProtectedFundSetup feature
//
//   Rev 1.1   Jan 10 2003 10:08:30   popescu
//No change.
//
//   Rev 1.0   Jan 09 2003 16:10:56   popescu
//Initial revision.
 * 
 *
 */
