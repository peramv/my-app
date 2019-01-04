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
//
// ^FILE   : ListSelectionDlg.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 12/98
//
// ----------------------------------------------------------
//
// ^CLASS    : ListSelectionDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a simple list selection dialog
//
//******************************************************************************
#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef LISTSELECTIONDLG_H
   #include "ListSelectionDlg.h"
#endif

#ifndef FUNDINFOPROCESSINCLUDES_HPP
   #include <ifastbp\FundInfoProcessIncludes.h>
#endif

#ifndef ALLOCATIONSPROCESSINCLUDES_H
   #include <ifastbp\AllocationsProcessIncludes.h>
#endif

#ifndef MFCANINTERPROCPARAM_HPP
   #include <ifastbp\MFCANInterProcParam.hpp>
#endif

#ifndef INCLUDED_VECTOR
#define INCLUDED_VECTOR
#include <vector>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_LIST_SELECTION;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ListSelectionDlg > dlgCreator( CMD_GUI_LIST_SELECTION );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct TESTCOMMAND
{
   const I_CHAR *szCommand;
   //CPint iCmd;
};

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REG_PLAN_TRANSFER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SYS_INDEX;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENTITY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACC_DETAILS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SYSTEMATIC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CERTIFICATE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DEMOGRAPHICS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REMARKS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCRUALS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_MARKET_VALUE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACB;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CHEQUE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CONFIRMATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_COA;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SHAREHOLDER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CASH_DIVIDEND;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DISTRIBUTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RRIF_LIF_LRIF_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FINANCIAL_INSTITUTION;

//CMD_BPROC_ALLOCATION,                  CMDID_BPROC_ALLOCATION,
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ALLOCATIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MGMTDETAILS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_WHEREUSED;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MINMAXINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESPBENREL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ESOPINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEE_PARAMETER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SETTLEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMS_GLOBAL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMSBROKER;

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEE_PARAMETER_SYSTEM;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER_ADDRESS;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRANS_CANCEL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_COMMITMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ESTATE_ALLOCATION;

namespace
{
    const I_CHAR *CLASSNAME = I_( "ListSelectionDlg" );

    static TESTCOMMAND cmds[] =
    {
        CMD_BPROC_REG_PLAN_TRANSFER,
        CMD_BPROC_SYS_INDEX,
        CMD_BPROC_BANK_INSTRUCTIONS,
        CMD_BPROC_FUNDINFO,
        CMD_BPROC_ENTITY,
        CMD_BPROC_ACC_DETAILS,
        CMD_BPROC_SYSTEMATIC,
        CMD_BPROC_CERTIFICATE,
        CMD_BPROC_ADDRESSES,
        CMD_BPROC_DEMOGRAPHICS,
        CMD_BPROC_REMARKS,
        CMD_BPROC_ACCRUALS, 
        CMD_BPROC_BANK_INSTRUCTIONS,
        CMD_BPROC_HISTORICAL_MARKET_VALUE,
        CMD_BPROC_TRANS_HISTORY,
        CMD_BPROC_ACB,
        CMD_BPROC_CHEQUE,
        CMD_BPROC_CONFIRMATION,
        CMD_BPROC_COA,
        CMD_BPROC_SHAREHOLDER,
        CMD_BPROC_CASH_DIVIDEND,
        CMD_BPROC_DISTRIBUTION,

        CMD_BPROC_RRIF_LIF_LRIF_INFO,
        CMD_BPROC_FINANCIAL_INSTITUTION,

        //CMD_BPROC_ALLOCATION,                  CMDID_BPROC_ALLOCATION,
        CMD_BPROC_ALLOCATIONS,
        CMD_BPROC_MGMTDETAILS,
        CMD_BPROC_ACCINFO,
        CMD_BPROC_WHEREUSED,
        CMD_BPROC_MINMAXINFO,
        CMD_BPROC_RESPBENREL,
        CMD_BPROC_ESOPINFO,
        CMD_BPROC_FEE_PARAMETER,
        CMD_BPROC_SETTLEMENT,
        CMD_BPROC_AMS_GLOBAL,
        CMD_BPROC_FEE_PARAMETER_SYSTEM,
        CMD_BPROC_AMSBROKER,
        CMD_BPROC_BROKER_ADDRESS,
        CMD_GUI_TRANS_CANCEL,
        CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE,
        CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION,
        CMD_BPROC_ACCOUNT_COMMITMENT,
        CMD_BPROC_ESTATE_ALLOCATION,
        NULL
    };
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
}

//*****************************************************************************
// Public methods
//*****************************************************************************

ListSelectionDlg::ListSelectionDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ListSelectionDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_psvDisplay( NULL )
, m_mode( NO_MODE )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(ListSelectionDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//*****************************************************************************

void ListSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ListSelectionDlg)
   DDX_Control(pDX, IDC_LST_VALUE, m_Values);
   //}}AFX_DATA_MAP
}

//*****************************************************************************

SEVERITY ListSelectionDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );
   // Set data in interProcessData
//   m_psvDisplay = CallGlobal::getInstance()->_psvParm1;
//   m_strTitle = CallGlobal::getInstance()->_sParm1;
   m_mode = STRING_VECTOR;
   return(NO_CONDITION);
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(ListSelectionDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ListSelectionDlg)
ON_LBN_DBLCLK(IDC_LST_VALUE, OnDblclkLstValue)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL ListSelectionDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   if( !m_strTitle.empty() )
   {
      SetWindowText( m_strTitle.c_str() );
   }

   int i = 0;
   while( cmds[i].szCommand != 0 )
   {
      m_Values.AddString( cmds[i].szCommand );
      ++i;
   }

   if( m_Values.GetCount() > 0 )
   {
      m_Values.SetCurSel( 0 );
   }

   return(TRUE);  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

bool ListSelectionDlg::Cancel() 
{  // Don't pass anything back
   TRACE_METHOD( CLASSNAME, CANCEL );

   if( STRING_VECTOR == m_mode )
   {
      // Set data in interProcessData
//      CallGlobal::getInstance()->_iParm1 = -1;
   }
   return(true);
}

//******************************************************************************

bool ListSelectionDlg::PreOk() 
{  
    // Get selected item and return
    MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, OK );
    int         iSel;       // The selection

    // They selected an item.
    iSel = m_Values.GetCurSel();
    if( LB_ERR != iSel )
    {  // Set any parameters and the modal flag as appropriate
        bool bModal = false;   // Default to modeless

        
        if( i_strcmp( CMD_BPROC_REG_PLAN_TRANSFER, cmds[iSel].szCommand ) == 0 )
        {
//            setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, I_("1000000362") );
//            setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, I_("1000000004") );
            setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, I_("1000000004") );
        }
        else if( i_strcmp( CMD_BPROC_SYS_INDEX, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, I_("1234") );
            setParameter( MFCAN_IP_PARAM::PAC_SWP_ID,  I_("000000199910") );
        }
        else if( i_strcmp( CMD_BPROC_BANK_INSTRUCTIONS, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::SHAREHOLDER );
            setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM,  I_( "7683381150" ) );
        }
        else if( i_strcmp( CMD_BPROC_FUNDINFO, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( FUND_CODE_VALUE,   NULL_STRING );
            setParameter( CLASS_CODE_VALUE,  NULL_STRING );
            setParameter( FROM_DATE_VALUE,   NULL_STRING );
            setParameter( TO_DATE_VALUE,     NULL_STRING ); 
            setParameter( PREV_DATE_PRESSED_VALUE, I_("Y") ); 
            setParameter( NEXT_DATE_PRESSED_VALUE, I_("N") ); 
        }
        else if( i_strcmp( CMD_BPROC_ENTITY, cmds[iSel].szCommand ) == 0 )
        {
            //setParameter( I_( "AccountNum" ),  I_( "50443" ) ); //I_( "463471001" ) );
            setParameter( I_( "AccountNum" ),  I_( "5047892001" ) );
        }
        else if( i_strcmp( CMD_BPROC_ADDRESSES, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "ShareholderNum" ), I_( "54635" ) ); //yingbao

            setParameter( I_( "AccountNum" ), I_( "50443" ) ); //yingbao
            setParameter( I_( "EntityID" ), I_( "997" ) ); //yingbao
        }
        else if( i_strcmp( CMD_BPROC_ACC_DETAILS, cmds[iSel].szCommand ) == 0 )
        {
            //setParameter( I_( "AccountNumber" ), I_( "28225" ) ); 
            setParameter( I_( "EntityId" )  , I_( "0,000,000,166" ) );
            setParameter( I_( "InputAcctNum" )  , I_( "" )   );
            setParameter( I_( "InputShrNum" )  , I_( "" )   );
            setParameter( I_( "NumEntry" )  , I_( "" )   );
        }
        else if( i_strcmp( CMD_BPROC_CERTIFICATE, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "InAcctNum" )  , I_( "6429" ) );
            setParameter( I_( "InFund" )  , I_( "" )   );
            setParameter( I_( "InCertNum" )  , I_( "" )   );
            setParameter( I_( "InXrefNum" )  , I_( "" )   );
        }
        else if( i_strcmp( CMD_BPROC_DEMOGRAPHICS, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "50443" ) );
        }
        else if( i_strcmp( CMD_BPROC_REMARKS, cmds[iSel].szCommand ) == 0 )
        {
            //setParameter( I_("ShareholderNum"), I_( "212662" ) );
            //setParameter( I_( "AccountNum" ), I_( "159053" ) );
            setParameter( I_( "AccountNum" ), I_( "553941001" ) );
        }
        else if( i_strcmp( CMD_BPROC_BANK_INSTRUCTIONS, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "50443" ) );
            setParameter( I_( "BankInstrType" ), I_( "Default" ) );
            //setParameter( I_("ShareholderNum"), I_( "178194" ) );
        }
        else if( i_strcmp( CMD_BPROC_ACCRUALS, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "6429" ) );
        }
        else if( i_strcmp( CMD_BPROC_HISTORICAL_MARKET_VALUE, cmds[iSel].szCommand ) == 0 )
        {
            //setParameter( I_( "AccountNum" ), I_( "6429" ) );
            setParameter( I_( "AccountNum" ), I_( "159053" ) );
        }
        else if( i_strcmp( CMD_BPROC_TRANS_HISTORY, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum"      ), I_( "159053" ) ); 
            setParameter( I_( "FundCode"        ), I_( "GRIC" ) ); 
            setParameter( I_( "ClassCode"       ), I_( "B" ) ); 
            setParameter( I_( "NumEntry"        ), I_( "0" ) ); 
            setParameter( I_( "AllFundMode"     ), I_( "Y" ) ); 
            setParameter( I_( "TransId"         ), I_("-1") );
            setParameter( I_( "ShareholderNum"  ), I_( "212662" ) );
        }
        else if( i_strcmp( CMD_BPROC_ACB, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "3814" ) ); 
            setParameter( I_( "FundCode" ), I_( "TELC" ) ); 
            setParameter( I_( "ClassCode" ), I_( "B" ) ); 
            setParameter( I_( "AllFundMode" ), I_( "N" ) ); 
        }
        else if( i_strcmp( CMD_BPROC_CHEQUE, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "159053" ) ); 
        }
        else if( i_strcmp( CMD_BPROC_CASH_DIVIDEND, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "39404" ) ); 
        }
        else if( i_strcmp( CMD_BPROC_DISTRIBUTION, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "159053" ) ); 
        }
        else if( i_strcmp( CMD_BPROC_ALLOCATIONS, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( ALLOCATIONSPROC::ACCOUNT_NUM, I_( "159053" ) );
            setParameter( ALLOCATIONSPROC::ALLOCATION_TYPE, 
                        ALLOCATIONSPROC::SHAREHOLDER_DEFAULT );
            setParameter(MFCAN_IP_PARAM::CALLER, I_("Default"));
        }
        else if( i_strcmp( CMD_BPROC_SYSTEMATIC, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "115501")); 
        }
        else if( i_strcmp( CMD_BPROC_CONFIRMATION, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "1081")); 
        }
        else if( i_strcmp( CMD_BPROC_COA, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "159053")); 
        }
        else if( i_strcmp( CMD_BPROC_SHAREHOLDER, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "1081")); 
        }
        else if( i_strcmp( CMD_BPROC_RRIF_LIF_LRIF_INFO, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "1365899001")); 
        }
        else if( i_strcmp( CMD_BPROC_MINMAXINFO, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "187468")); 
        }
        else if( i_strcmp( CMD_BPROC_MGMTDETAILS, cmds[iSel].szCommand ) == 0 )
        {
        }
        else if( i_strcmp( CMD_BPROC_RESPBENREL, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "4958617001"));
        }
        else if( i_strcmp( CMD_BPROC_FINANCIAL_INSTITUTION, cmds[iSel].szCommand ) == 0 )
        {
        }
        else if( i_strcmp( CMD_BPROC_ESOPINFO, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "590094359"));
        }
        else if( i_strcmp( CMD_BPROC_FEE_PARAMETER, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "84822001"));
        }

        else if( i_strcmp( CMD_BPROC_SETTLEMENT, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "84822001"));
        }
        else if( i_strcmp( CMD_BPROC_AMSBROKER, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "BrokerCode" ), I_( ""));
            bModal = true;
        }
        else if( i_strcmp( CMD_BPROC_BROKER_ADDRESS, cmds[iSel].szCommand ) == 0 )
        {
           setParameter( I_( "AccountNum" ), I_( "2295"));
           bModal = true;
        }
        else if( i_strcmp( CMD_GUI_TRANS_CANCEL, cmds[iSel].szCommand ) == 0 )
        {
            //setParameter( I_( "AccountNum" ), I_( "2295"));
            bModal = true;
        }
        else if( i_strcmp( CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "7566656001" ) ); 
            bModal = true;
        }
        else if( i_strcmp( CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION, cmds[iSel].szCommand ) == 0 )
        {
            setParameter( I_( "AccountNum" ), I_( "2" ) ); 
            bModal = true;
        }
        else if( i_strcmp( CMD_BPROC_ACCOUNT_COMMITMENT, cmds[iSel].szCommand ) == 0 )
        {
            bModal = true;
        }
        else if( i_strcmp( CMD_BPROC_ESTATE_ALLOCATION, cmds[iSel].szCommand ) == 0 )
        {
            bModal = true;
        }

        try
        {
            E_COMMANDRETURN eRtn;
            // eRtn = CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession, CMD_BPROC_SEARCH, 
            //               PROC_NO_TYPE, true, NULL );
            eRtn = invokeCommand( getParent(), cmds[iSel].szCommand, PROC_NO_TYPE, bModal, NULL );
            switch( eRtn )
            {
            case CMD_OK:
            case CMD_CANCEL:
            case CMD_MODELESS_INPROCESS:
                break;
            default:
                // Display error
                ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
                break;
            }
        }
        catch( ConditionException &ce )
        {
            ConditionMessageBox( ce );
        }
        catch( ... )
        {
            DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
        }
        // Allow users to stay on screen
        return(false);
    }

    if( STRING_VECTOR == m_mode )
    {
        // Set data in interProcessData
        // CallGlobal::getInstance()->_iParm1 = iSel;
    }

    return(true);
}

//******************************************************************************
void ListSelectionDlg::OnDblclkLstValue() 
{
   OnCmdMsg(IDOK, 0, NULL, NULL);
//	OnOK();	
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ListSelectionDlg.cpp-arc  $
 * 
 *    Rev 1.30   25 Jul 2012 17:50:48   if991250
 * P0186484 : Estate Allocation
 * 
 *    Rev 1.29   Jan 20 2012 16:24:44   if991250
 * Account Commitment
 * 
 *    Rev 1.28   Jul 09 2009 12:40:18   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.27   Mar 11 2008 19:36:24   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.26   Sep 15 2005 15:13:42   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.25   Oct 04 2003 08:43:18   popescu
 * CIBC PET 809, FN13, removed references to BankSearch and BankList objects
 * 
 *    Rev 1.24   Sep 03 2003 17:16:08   popescu
 * fixes regarding calling the allocation screen, seems that more places that originally thought are using the allocation screen
 * 
 *    Rev 1.23   May 23 2003 10:04:32   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.22   May 22 2003 14:14:06   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.21   Apr 03 2003 09:40:12   YINGBAOL
 * Broker Address Enhancement
 * 
 *    Rev 1.20   Mar 21 2003 18:38:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.19   Mar 13 2003 18:29:14   FENGYONG
 * Add entry for brokerAMSdlg
 * 
 *    Rev 1.18   Jan 16 2003 11:27:34   linmay
 * added CMD_BPROC_FEE_PARAMETER_SYSTEM;
 * 
 *    Rev 1.17   Nov 25 2002 10:11:18   YINGBAOL
 * added launch AMS Global Dialog
 * 
 *    Rev 1.16   Oct 09 2002 23:55:46   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Jun 04 2002 10:46:26   YINGBAOL
 * add Settlement
 * 
 *    Rev 1.14   27 Mar 2002 20:01:14   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.13   21 Feb 2002 15:50:00   HSUCHIN
 * changed interest accruals id with accruals
 * 
 *    Rev 1.12   Feb 01 2002 15:24:20   YINGBAOL
 * add FeeDialog
 * 
 *    Rev 1.11   31 Jul 2001 17:04:44   KOVACSRO
 * Added ESoPInfo.
 * 
 *    Rev 1.10   03 May 2001 13:54:44   BUZILAMI
 * added SysIndexing
 * 
 *    Rev 1.9   Mar 23 2001 03:39:30   YINGBAOL
 * add bank search dialog
 * 
 *    Rev 1.8   07 Mar 2001 15:44:42   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 * 
 *    Rev 1.7   Feb 21 2001 16:06:46   BUZILAMI
 * changed BankAcct*.?pp => BankInstr*.?pp
 * 
 *    Rev 1.6   Feb 21 2001 10:39:30   BUZILAMI
 * Bank Acct changes
 * 
 *    Rev 1.5   Feb 13 2001 10:14:44   BUZILAMI
 * added BankAcct and made the dialog to do Ok processing on List double click
 * 
 *    Rev 1.4   Jul 21 2000 16:42:04   KOVACSRO
 * changed a parameter
 * 
 *    Rev 1.3   Jul 19 2000 16:54:04   KOVACSRO
 * added BPROC_RESPBENREL
 * 
 *    Rev 1.2   Mar 21 2000 14:28:24   ZHANGCEL
 * Added MinMaxInfo stuffs
 * 
 *    Rev 1.1   Mar 16 2000 09:45:30   YINGBAOL
 * added RRIF info
 * 
 *    Rev 1.0   Feb 15 2000 11:01:18   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.12   Nov 25 1999 15:37:52   PRAGERYA
 * Allocations enabled
 * 
 *    Rev 1.11   Nov 12 1999 15:17:36   YINGZ
 * change ok to preok
 * 
 *    Rev 1.10   Nov 02 1999 17:21:02   YINGZ
 * add info to open bank dlg
 * 
 *    Rev 1.9   Nov 02 1999 17:20:50   YINGBAOL
 * set parameter for address
 * 
 *    Rev 1.8   Sep 24 1999 10:13:56   PRAGERYA
 * "Milestone" check in
 * 
 *    Rev 1.7   Aug 04 1999 11:24:24   PRAGERYA
 * Date fix
 * 
 *    Rev 1.6   Aug 04 1999 11:16:56   PRAGERYA
 * Fixing date
 * 
 *    Rev 1.5   Aug 03 1999 16:33:26   BUZILA
 * 1
 * 
 *    Rev 1.4   Aug 03 2000 14:00:20   BUZILA
 * chg param for calling COA
 * 
 *    Rev 1.3   Jul 27 1999 16:06:22   BUZILA
 * Increment M2
 * 
 *    Rev 1.2   Jul 20 1999 11:19:04   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:05:24   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

