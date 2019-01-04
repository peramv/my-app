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
//    DATE   : 23/11/99
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\abstractprocess.hpp>
#include <map>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class executes the new account setup!
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 23/11/1999</dd></dl>
 * @version 0.1
 */

class ServerData;

class NasuParams
{
public:
   NasuParams();
   ~NasuParams();

   void setParameter (const DString &name, const DString &value);
   DString getParameter (const DString &name);
private:
   typedef std::map< DString, DString > ParmMap;
   ParmMap  _mapParms;
};


class IFASTBP_LINKAGE NASUProcess : public AbstractProcess
{
// Construction
public:
//CP20030319   NASUProcess();
   NASUProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~NASUProcess();
   ServerData* getServerData();
protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh( GenericInterface *rpGICaller, 
                           const I_CHAR *szOriginalCommand )
   {
      return(false);
   };
   virtual bool setCommitDataGroupAsHost()
   {
      return(true);
   }
private:
   E_COMMANDRETURN doFlow( const struct _nasu flow[] );
   bool isEndOfNASU( const struct _nasu flow[], int nasundx );
   void setFlowParams( const I_CHAR* params[] );
   void getFlowParams( const I_CHAR* params[] );
   bool isSegFund();
   bool isAsPensionPlanType();
   bool hasAccountSplitComm();
   bool isESoPPlanType();
   bool hasPensionInfo();
   bool isAcctAMSPartOfNASU();
   bool isNewRESPTaxType ();
   bool isGuarGuardAllowed ();
   bool isCommitmentApplicable ();

   NasuParams _nasuParams;
   ServerData *_pServerData;
   DString flowPopupOptions;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/NASUProcess.hpp-arc  $
 * 
 *    Rev 1.24   Feb 24 2012 16:06:18   popescu
 * NASU - Added commitment.
 * 
 *    Rev 1.23   Sep 17 2010 07:18:22   kitticha
 * PETP0173756 FN02 Don't Bust the Rules.
 * 
 *    Rev 1.22   Mar 12 2010 14:24:24   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.21   01 May 2007 13:55:32   popescu
 * Incident: ? (got raised by Lux - C.Rigot) account# is invalid for acct cut off times trxn sent, and acct category
 * 
 *    Rev 1.20   Nov 09 2006 17:50:32   ZHANGCEL
 * PET 2286 FN01 -- Add Bank and Distribution in NASU flow
 * 
 *    Rev 1.19   Sep 20 2004 11:12:16   YINGBAOL
 * PET1117:FN05 FeeModel at account/shareholder level can be part of NASU
 * 
 *    Rev 1.18   Aug 11 2004 11:59:56   AGUILAAM
 * PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
 * 
 *    Rev 1.17   Feb 23 2004 14:33:16   popescu
 * PTS 10027142, Changed the nasuParams object from a BFData object to a map of strings, keyed by the name of  a parameter
 * 
 *    Rev 1.16   Nov 24 2003 13:35:08   popescu
 * PTS 10024286, read the NASUPopupOptions a generic control  setting that allows a management compnay to skip specific screens, during NASU flow
 * 
 *    Rev 1.15   Aug 18 2003 16:01:50   YINGBAOL
 * account level AMS will be part of the NASU flow
 * 
 *    Rev 1.14   Mar 21 2003 17:45:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Oct 09 2002 23:53:30   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Jul 05 2002 08:55:22   PURDYECH
 * Fixed include files
 * 
 *    Rev 1.11   Jun 02 2002 17:52:10   HSUCHIN
 * added pension info
 * 
 *    Rev 1.10   22 May 2002 18:20:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   19 Mar 2002 13:18:02   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.8   19 Sep 2001 14:54:40   KOVACSRO
 * Added isESOPPlanType().
 * 
 *    Rev 1.7   03 Sep 2001 13:24:56   HSUCHIN
 * added new function hasAcctSplitComm
 * 
 *    Rev 1.6   Aug 23 2001 16:04:12   JANKAREN
 * Added isAsPensionPlanType()
 * 
 *    Rev 1.5   14 May 2001 13:57:50   YINGZ
 * code sync up
 * 
 *    Rev 1.4   Oct 17 2000 15:36:36   KOVACSRO
 * cleanup.
 * 
 *    Rev 1.3   Oct 17 2000 13:17:36   KOVACSRO
 * Added isSegFund and bInvokeContractInfo()
 * 
 *    Rev 1.2   Oct 11 2000 11:55:06   VASILEAD
 * Added server updates support
 * 
 *    Rev 1.1   Apr 04 2000 17:46:34   DT24433
 * removed use of _workSession and added revision block
 *
 */

