#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

//defines the table ids used in calling view 249, historical 
namespace AUDITTYPE
{
   extern CLASS_EXPORT I_CHAR * const BKD              = I_("BKD");
   extern CLASS_EXPORT I_CHAR * const FDE              = I_("FDE");
   extern CLASS_EXPORT I_CHAR * const FEP              = I_("FEP");
   extern CLASS_EXPORT I_CHAR * const SCD              = I_("SCD");
   extern CLASS_EXPORT I_CHAR * const PFR              = I_("PFR");
   extern CLASS_EXPORT I_CHAR * const PFC              = I_("PFC");
   extern CLASS_EXPORT I_CHAR * const PFF              = I_("PFF");
   extern CLASS_EXPORT I_CHAR * const SLS              = I_("SLS");
   extern CLASS_EXPORT I_CHAR * const BRK              = I_("BRK");
   extern CLASS_EXPORT I_CHAR * const BRKTX            = I_("BRKTX");
   extern CLASS_EXPORT I_CHAR * const AMSMT            = I_("AMSMT");
   extern CLASS_EXPORT I_CHAR * const AMSRU            = I_("AMSRU");
   extern CLASS_EXPORT I_CHAR * const TRG              = I_("TRG");
   extern CLASS_EXPORT I_CHAR * const PYEN             = I_("PYEN");       // Pay Entity
   extern CLASS_EXPORT I_CHAR * const PYIN             = I_("PYIN");       // Pay Instructions
   extern CLASS_EXPORT I_CHAR * const ATLOC            = I_("ATLOC");      // Settlement Location Account Level
   extern CLASS_EXPORT I_CHAR * const STLOC            = I_("STLOC");      // Settlement Location System Level
   extern CLASS_EXPORT I_CHAR * const SHADDR           = I_("SHADDR");     // Shareholder Address
   extern CLASS_EXPORT I_CHAR * const ACCTMAIL         = I_("ACCTMAIL");   // Account Mailing Information
   extern CLASS_EXPORT I_CHAR * const SHADISBK         = I_("SHADISBK");   // Distribution Bank Instruction
   extern CLASS_EXPORT I_CHAR * const SHADIS           = I_("SHADIS");     // Distribution
   extern CLASS_EXPORT I_CHAR * const SHENTD           = I_("SHENTD");
   extern CLASS_EXPORT I_CHAR * const DELOPN           = I_("DELOPN");
   extern CLASS_EXPORT I_CHAR * const SHENTJ           = I_("SHENTJ");
   extern CLASS_EXPORT I_CHAR * const SHENTB           = I_("SHENTB");
   extern CLASS_EXPORT I_CHAR * const SHENTA           = I_("SHENTA");
   extern CLASS_EXPORT I_CHAR * const ENTIDT           = I_("ENTIDT");
   extern CLASS_EXPORT I_CHAR * const ASDETL           = I_("ASDETL");
   extern CLASS_EXPORT I_CHAR * const ENTIDS           = I_("ENTIDS");
   extern CLASS_EXPORT I_CHAR * const BKACCT           = I_("BKACCT");     // Bank Account Instructions
   extern CLASS_EXPORT I_CHAR * const ATSET            = I_("ATSET");
   extern CLASS_EXPORT I_CHAR * const OMNBUS           = I_("OMNBUS");
   extern CLASS_EXPORT I_CHAR * const ACTAMS           = I_("ACTAMS");
   extern CLASS_EXPORT I_CHAR * const KYC              = I_("KYC");
   extern CLASS_EXPORT I_CHAR * const ACCT             = I_("ACCT");
   extern CLASS_EXPORT I_CHAR * const ACCTCONTROL      = I_("ACTCLR");
   extern CLASS_EXPORT I_CHAR * const REGDOCUMENT      = I_("MISCDOC");
   extern CLASS_EXPORT I_CHAR * const CHQDT            = I_("CHQDTL");
   extern CLASS_EXPORT I_CHAR * const ACT_AUTH         = I_("ACTATH");
   extern CLASS_EXPORT I_CHAR * const DAILY_FEE        = I_("DLYFEE");
   extern CLASS_EXPORT I_CHAR * const ACT_CATEGORY     = I_("ACAT");
   extern CLASS_EXPORT I_CHAR * const ATF              = I_("ATF");
   extern CLASS_EXPORT I_CHAR * const TRNDEC           = I_("TRNDEC"); //P0185327_FN01 - ROC Depleting ACB
   extern CLASS_EXPORT I_CHAR * const SHR_FAMILY       = I_("SHRFAM");
   extern CLASS_EXPORT I_CHAR * const SYS_FAMILY       = I_("FAMILY");
   extern CLASS_EXPORT I_CHAR * const ACCTREGDETAILS   = I_("ACTREG");
   extern CLASS_EXPORT I_CHAR * const ENTREGDETAILS    = I_("ENTREG");
   extern CLASS_EXPORT I_CHAR * const ENTREGJURISDETAILS = I_("ENTJUR");

   extern CLASS_EXPORT I_CHAR * const HOLDING_COMPANY  = I_("HLDENT");
   extern CLASS_EXPORT I_CHAR * const FEE_PARM_THRESHOLD  = I_("THRHD");
   extern CLASS_EXPORT I_CHAR * const FEE_MODEL        = I_("FEEMO");
   extern CLASS_EXPORT I_CHAR * const FEE_SCALE        = I_("FEESCL");
   extern CLASS_EXPORT I_CHAR * const FEE_PARM         = I_("FEEPRM");
   extern CLASS_EXPORT I_CHAR * const WHERE_USED       = I_("ENTWH");
   extern CLASS_EXPORT I_CHAR * const DILUTION_ALLOC   = I_("SPTACC");
   extern CLASS_EXPORT I_CHAR * const ENTITY_RISK      = I_("ENTRK");
   extern CLASS_EXPORT I_CHAR * const ACTRDR		   = I_("ACTRDR");
   extern CLASS_EXPORT I_CHAR * const CUTOFF		   = I_("CUTOFF");
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastids/ifastauditids.cpp-arc  $
// 
//    Rev 1.30   Nov 08 2011 12:09:32   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.29   Sep 14 2011 10:12:22   panatcha
// P0185327_FN01 - ROC Depleting ACB
// 
//    Rev 1.28   Jan 12 2011 02:33:54   wutipong
// IN2310764 - Historical screen with wrong display in PAC and Auto Transfer
// 
//    Rev 1.27   Nov 29 2010 02:25:56   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.26   Jul 14 2010 13:33:06   jankovii
// PET0170770_FN01_Anti Dilution Levy
// 
//    Rev 1.25   Jul 08 2009 07:42:26   dchatcha
// PET 156681 - FN 14 - Investor Authorization.
// 
//    Rev 1.24   Sep 11 2008 10:44:40   jankovii
// PET 5517 FN71 Stale Cheque.
// 
//    Rev 1.23   Sep 08 2008 16:01:38   jankovii
// PET 5517 FN71 - Stale Cheque.
// 
//    Rev 1.22   Aug 01 2008 09:25:18   jankovii
// PET 59888 FN01 AML Enhancement.
// 
//    Rev 1.21   Mar 11 2008 19:28:30   daechach
// PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
// 
//    Rev 1.20   Aug 01 2007 17:52:12   kovacsro
// PET2372 FN02 FDP-AIM KYC
// 
//    Rev 1.19   Jul 27 2007 10:26:16   smithdav
// PET 2360 FN02 - Historical Button support.
// 
//    Rev 1.18   Oct 05 2005 10:37:46   AGUILAAM
// PET1286_FN02_Verification of Aggregated Order Fund Price
// 
//    Rev 1.17   Nov 05 2004 17:36:00   AGUILAAM
// PET1170_FN21: settlement instructions enhancement
// 
//    Rev 1.16   Sep 27 2004 18:00:48   HERNANDO
// PTS10034084 - Replaced Bank Instruction Audit IDs with BKACCT.
// 
//    Rev 1.15   Apr 19 2004 12:19:56   HERNANDO
// PTS10028962 - Added ENTIDS.
// 
//    Rev 1.14   Feb 24 2004 15:41:12   HERNANDO
// PET965 FN11 - Renamed SHRADIS to SHADIS.
// 
//    Rev 1.13   Feb 22 2004 13:52:50   HERNANDO
// PET965 FN11 - Added SHENTD, DELOPN, SHENTJ, SHENTB, SHENTA, ENTIDT, and ASDETL.
// 
//    Rev 1.12   Feb 02 2004 14:00:18   HERNANDO
// PET965 FN11 - Added SHADDR, ACCTMAIL, BRKBANK, BCHBANK, REPBANK, FNDBANK, SHRBANK, CLNBANK, SHRADIS, and SHADISBK.
// 
//    Rev 1.11   Nov 24 2003 18:14:46   HERNANDO
// PET892 FN1 - Changed ASTLOC and STLLOC to ATLOC and STLOC respectively according to the view side changes.
// 
//    Rev 1.10   Nov 19 2003 14:15:02   HERNANDO
// PET892 FN1 - Added ASTLOC and STLLOC for Settlement Location at Account Level and System Level respectively.
// 
//    Rev 1.9   Aug 13 2003 18:14:32   HERNANDO
// Changed PYENT to PYEN and PYINS to PYIN.  Amelia says one thing, Jocelyn says another.
// 
//    Rev 1.8   Aug 12 2003 10:50:38   HERNANDO
// Added PYENT and PYINS.
// 
//    Rev 1.7   Jul 31 2003 13:28:50   FENGYONG
// Add TRG for demographic
// 
//    Rev 1.6   Jul 31 2003 12:56:18   linmay
// modified audit type for cibc ams
// 
//    Rev 1.5   Jul 23 2003 11:15:34   linmay
// added new audit type for CIBC AMS
// 
//    Rev 1.4   Feb 17 2003 18:28:42   popescu
// Added a new audit type for  the BrokerInterimTaxOut
// 
//    Rev 1.3   Feb 11 2003 14:42:14   popescu
// changes related to the Historical information for Broker and Sales rep, as well as displaying the names for them in the Historical Info Search dialog
// 
//    Rev 1.2   Feb 05 2003 12:07:00   popescu
// Changes related to adding a new audit type id, for PAC/SWP and testing the FeeParam/Sys Historical button
// 
//    Rev 1.1   Jan 26 2003 17:00:48   popescu
// Added new ids which will be used for the Audit Historical Info
// 
//    Rev 1.0   Jan 26 2003 13:35:16   popescu
// Initial Revision
 * 
 */
