// ACBDlg.cpp : implementation file
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
// ^FILE   : ACBDlg.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/1999
//
// ^CLASS    : ACBDlg
// ^SUBCLASS : BaseMainDlg         
//
// ^CLASS DESCRIPTION : 990708
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "ACBDlg.h"

#include <uibase\ConditionMessageDialog.h>
#include <uibase\dstlistctrl.h>
#include <ConfigManager.hpp>

#include <ifastbp\acbprocessincludes.h>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastdataimpl\dse_dstc0004_VW.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastgui\ifasthistoricalinfo.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACB;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ACBDlg > dlgCreator( CMD_GUI_ACB );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctACBAvailable;
   extern CLASS_IMPORT const BFTextFieldId FndClsACBAvailable;
   extern CLASS_IMPORT const BFTextFieldId DispHistUnitACB;
   extern CLASS_IMPORT const BFTextFieldId ACBListHeading2;
   extern CLASS_IMPORT const BFTextFieldId ACBListHeading3; // P0185327_FN01 - ROC Depleting ACB
   extern CLASS_IMPORT const BFTextFieldId ACBListHeading4; // P0185327_FN01 - ROC Depleting ACB
   extern CLASS_IMPORT const BFTextFieldId ACBListHeading5; // P0186477 FN06 T5 Processing
   extern CLASS_IMPORT const BFTextFieldId ACBListHeading6; 
   extern CLASS_IMPORT const BFTextFieldId ACBListHeading7; 
   extern CLASS_IMPORT const BFTextFieldId ACBListHeading8;
   extern CLASS_IMPORT const BFDecimalFieldId ACBPlugAmt;
   extern CLASS_IMPORT const BFDateFieldId ACBPlugDate;
   extern CLASS_IMPORT const BFTextFieldId IsGIAFund;
   extern CLASS_IMPORT const BFDateFieldId T5AnniversaryDate;
}

/////////////////////////////////////////////////////////////////////////////
// ACBDlg dialog
namespace
{
   // trace literals
   const I_CHAR *CLASSNAME             = I_( "ACBDlg" );
   const I_CHAR *LV_ACB                = I_( "ACBList" ); 

   const I_CHAR *Y                     = I_( "Y" );
   const I_CHAR *N                     = I_( "N" );
   const I_CHAR *SAPERATOR             = I_( " " );
   const I_CHAR *M1                    = I_("-1");
   const I_CHAR *SPACE                 = I_(" ");

   const I_CHAR *AW                    = I_("AW");
   const I_CHAR *PW                    = I_("PW");
   const I_CHAR *TO                    = I_("TO");
   const I_CHAR *EO                    = I_("EO");
   const I_CHAR *AF                    = I_("AF");

   const I_CHAR * const MONEYOUTLIST   = I_( "PW,AW,AF,TO,EO,AF91" );

   const I_CHAR *pALLFUND              = I_( "AllFundMode" );
   const I_CHAR *pACCOUNTNUM           = I_( "AccountNum" );
   const I_CHAR *pFUNDCODE             = I_( "FundCode" );
   const I_CHAR *pCLASSCODE            = I_( "ClassCode" );

   const I_CHAR *ACCCURRENCY           = I_( "AccCurrency" );
   const I_CHAR *TRANSTYPEDESC         = I_( "TransTypeDesc" );

   const I_CHAR *ADJUSTEDCOST          = I_( "AdjustedCost" );
   const I_CHAR *ACBPERUNIT            = I_( "ACBPerUnit" );
}

namespace CND
{
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACB;
}

//******************************************************************************
ACBDlg::ACBDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ACBDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(ACBDlg)
   m_RealizedGain = I_("");
   m_AdjustedCost = I_("");
   m_UnitACB = I_("");
   m_CurrentNAV = I_("");
   m_MarketValue = I_("");
   m_AccountCurrency = I_("");
   m_FundCurrency = I_("");
   //}}AFX_DATA_INIT

   FundCode=M1;
}

//******************************************************************************
void ACBDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ACBDlg)
   //DDX_Control(pDX, IDC_LV_ACB_TRANS, m_ACBList);
   DDX_Control(pDX, IDC_CMB_FUND, m_FundList);
   DDX_Text(pDX, IDC_TXT_GAINS, m_RealizedGain);
   DDX_Text(pDX, IDC_TXT_ADJ_COST, m_AdjustedCost);
   DDX_Text(pDX, IDC_TXT_UNIT_ACB, m_UnitACB);
   DDX_Text(pDX, IDC_TXT_CURRENT_NAV, m_CurrentNAV);
   DDX_Text(pDX, IDC_TXT_MARKET_VALUE, m_MarketValue);
   DDX_Text(pDX, IDC_TXT_CURRENCY, m_AccountCurrency);
   DDX_Text(pDX, IDC_TXT_ACB_FUND_CURRENCY, m_FundCurrency);	
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(ACBDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ACBDlg)
ON_BN_CLICKED(IDC_MORE, OnMore)
//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LV_ACB_TRANS, OnItemchangedLvAcbTrans)
ON_CBN_SELENDOK(IDC_CMB_FUND, OnSelendokCmbFund)
ON_BN_CLICKED(IDC_BTN_HISTORICAL,OnBtnHistorical)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ACBDlg message handlers

void ACBDlg::OnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));

   CWaitCursor wait;
   SetMessageStatusBar( TXT_LOAD_ACB );

   if (getParent()->performSearch (this, IFASTBP_PROC::ACB_LIST, SEARCH_NEXT_BLOCK) <= WARNING)
   {
      LoadListControl(IDC_LV_ACB_TRANS);
      PopulateACBList();
   }

   SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************
BOOL ACBDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();

   //DString dstrDispHistUnitACB;
   //DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   //dstWorkSession->getOption (ifds::DispHistUnitACB, dstrDispHistUnitACB, getParent()->getDataGroupId(), false);

   //bool bDispHistUnitACB = dstrDispHistUnitACB == I_("Y") ? true : false;

   ////P0185327_FN01 - ROC Depleting ACB
   //DString dstrACBUnitOffset(NULL_STRING);

   //dstWorkSession->getOption (ifds::ACBUnitOffset, dstrACBUnitOffset, getParent()->getDataGroupId(), false);

   //bool bShowHide = dstrACBUnitOffset == I_("Y");
   //BFFieldId idFieldDisplay;
   //// Modify the existing logic to support the new heading set
   //// The new heading set 5 is as same as heading set 1 but append TaxableAmount.
   //// Heading set 6 copied from 2 + append TaxableAmount. 7 from 3 + TaxableAmount
   //// 8 from 4 + TaxableAmount.
   //// We may revise the logic in the future to support dynamic heading set.
   //if(bShowHide)
   //{  
   //   if (bDispHistUnitACB)
   //   {
   //      if( !dstWorkSession->isTaxAnniversaryClient(getParent()->getDataGroupId()) )
   //         idFieldDisplay = ifds::ACBListHeading4;
   //      else
   //         idFieldDisplay = ifds::ACBListHeading8;
   //   }
   //   else
   //   {
   //      if( !dstWorkSession->isTaxAnniversaryClient(getParent()->getDataGroupId()) )
   //         idFieldDisplay = ifds::ACBListHeading3;
   //      else
   //         idFieldDisplay = ifds::ACBListHeading7;
   //   }
   //   //m_ACBList.Init(this, bDispHistUnitACB ? ifds::ACBListHeading4 : ifds::ACBListHeading3, IFASTBP_PROC::ACB_LIST, CLASSNAME, LV_ACB);
   //}
   //else
   //{
   //   if (bDispHistUnitACB)
   //   {
   //      if( !dstWorkSession->isTaxAnniversaryClient(getParent()->getDataGroupId()) )
   //         idFieldDisplay = ifds::ACBListHeading2;
   //      else
   //         idFieldDisplay = ifds::ACBListHeading6;
   //   }
   //   else
   //   {
   //      if( !dstWorkSession->isTaxAnniversaryClient(getParent()->getDataGroupId()) )
   //         idFieldDisplay = ifds::ACBListHeading;
   //      else
   //         idFieldDisplay = ifds::ACBListHeading5;
   //   }
   //   //m_ACBList.Init(this, bDispHistUnitACB ? ifds::ACBListHeading2 : ifds::ACBListHeading, IFASTBP_P::ACB_LIST, CLASSNAME, LV_ACB);
   //}

   //m_ACBList.Init(this, idFieldDisplay, IFASTBP_PROC::ACB_LIST, CLASSNAME, LV_ACB);
//   GetDlgItem (IDC_BTN_HISTORICAL)->EnableWindow (bShowHide);
//--

   //DisplayTitle();

   //UpdateData(FALSE);

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
SEVERITY ACBDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   getParameter( ACCCURRENCY, AccountCurrency);
   getParameter( pACCOUNTNUM, AccountNum );
   getParameter( pFUNDCODE, FundCode ); 
   getParameter( pCLASSCODE, ClassCode ); 

   AccountNum.stripAll();

   return NO_CONDITION;
}

//******************************************************************************
void ACBDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog")); 

   DString dstrDispHistUnitACB;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   dstWorkSession->getOption (ifds::DispHistUnitACB, dstrDispHistUnitACB, getParent()->getDataGroupId(), false);

   bool bDispHistUnitACB = dstrDispHistUnitACB == I_("Y") ? true : false;

   //P0185327_FN01 - ROC Depleting ACB
   DString dstrACBUnitOffset(NULL_STRING);

   dstWorkSession->getOption (ifds::ACBUnitOffset, dstrACBUnitOffset, getParent()->getDataGroupId(), false);

   bool bShowHide = dstrACBUnitOffset == I_("Y");
   BFFieldId idFieldDisplay;
   // Modify the existing logic to support the new heading set
   // The new heading set 5 is as same as heading set 1 but append TaxableAmount.
   // Heading set 6 copied from 2 + append TaxableAmount. 7 from 3 + TaxableAmount
   // 8 from 4 + TaxableAmount.
   // We may revise the logic in the future to support dynamic heading set.
   if(bShowHide)
   {  
      if (bDispHistUnitACB)
      {
         if( !dstWorkSession->isTaxAnniversaryClient(getParent()->getDataGroupId()) )
            idFieldDisplay = ifds::ACBListHeading4;
         else
            idFieldDisplay = ifds::ACBListHeading8;
      }
      else
      {
         if( !dstWorkSession->isTaxAnniversaryClient(getParent()->getDataGroupId()) )
            idFieldDisplay = ifds::ACBListHeading3;
         else
            idFieldDisplay = ifds::ACBListHeading7;
      }
   }
   else
   {
      if (bDispHistUnitACB)
      {
         if( !dstWorkSession->isTaxAnniversaryClient(getParent()->getDataGroupId()) )
            idFieldDisplay = ifds::ACBListHeading2;
         else
            idFieldDisplay = ifds::ACBListHeading6;
      }
      else
      {
         if( !dstWorkSession->isTaxAnniversaryClient(getParent()->getDataGroupId()) )
            idFieldDisplay = ifds::ACBListHeading;
         else
            idFieldDisplay = ifds::ACBListHeading5;
      }
   }

   AddListControl( CLASSNAME, 
                   IDC_LV_ACB_TRANS, 
                   LV_ACB, 
                   idFieldDisplay, 
                   IFASTBP_PROC::ACB_LIST,
                   0,
                   true,
                   LISTFLAG_NOT_AUTO_ADD );

   AddControl ( CTRL_EDIT, 
                IDC_EDT_ACB_PLUG_AMOUNT, 
                IFASTBP_PROC::ACB_LIST, 
                ifds::ACBPlugAmt );

   AddControl( CTRL_STATIC, IDC_STC_ACB_PLUG_DATE, IFASTBP_PROC::ACB_LIST, ifds::ACBPlugDate );
   AddControl( CTRL_STATIC, IDC_STATIC_NEXT_T5_ANNIVERSARY_DATE_VALUE, IFASTBP_PROC::MFACCOUNT_CBO, ifds::T5AnniversaryDate);
   AddControl( CTRL_STATIC, IDC_STATIC_MARKET_VALUE, IFASTBP_PROC::ACB_LIST, ifds::GIAOpenMktValue);

   GetDlgItem (IDC_BTN_HISTORICAL)->EnableWindow (bShowHide);

   PopulateFundAndFundClass();

   OnSelendokCmbFund();
}

//******************************************************************************
void ACBDlg::PopulateACBList()
{
   TRACE_METHOD( CLASSNAME, I_("PopulateACBList"));

   DisplayTitle();

   //m_ACBList.PopulateList();
   ConnectListToData (IDC_LV_ACB_TRANS, true);
   LoadListControl (IDC_LV_ACB_TRANS);

   DString str,str1;
   const DString *ty=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::ACB_LIST ));

   if( (*ty)!=NULL_STRING )
   {
      DString rxFundCode, rxFundClass, adjustedCost, aCBPerUnit;

      getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::rxFundCode, rxFundCode );
      rxFundCode.stripAll().upperCase();

      getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::rxClassCode, rxFundClass );
      rxFundClass.stripAll().upperCase();

      getCurNAV(rxFundCode,rxFundClass,m_CurrentNAV, m_FundCurrency);
      getMarketValue(rxFundCode,rxFundClass,m_MarketValue);
      getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::AdjustedCost, adjustedCost);
      adjustedCost.stripAll();
      getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::ACBPerUnit, aCBPerUnit);
      aCBPerUnit.stripAll();

      DString dstrFndClsACBAvailable;

      //to set the list cursor on the current item
      getParent()->getCurrentListItemKey(this, IFASTBP_PROC::FUND_LIST);
      getParent()->getField(this, IFASTBP_PROC::FUND_LIST, ifds::FndClsACBAvailable, dstrFndClsACBAvailable, false);

      if ( dstrFndClsACBAvailable == I_("N") ) 
      {
         m_AdjustedCost.LoadString(TXT_SUPPRESS_ACB_ACCOUNT);
         m_UnitACB.LoadString(TXT_SUPPRESS_ACB_ACCOUNT);
      } 
      else
      {
         DisplayFormat(adjustedCost, (BFFieldId)ifds::AdjustedCost );
         m_AdjustedCost=adjustedCost.c_str();
         DisplayFormat(aCBPerUnit, ( BFFieldId )ifds::ACBPerUnit );
         m_UnitACB=aCBPerUnit.c_str();
      }

      m_AccountCurrency=AccountCurrency.stripAll().c_str();

      updatePlugControls();
      displayT5EventDate();
      displayGIAOpeningMV();

      UpdateData(FALSE);
   }

   if( GetList (IDC_LV_ACB_TRANS)->GetItemCount () > 0 )
   {
      bool bMoreRecordsExist=getParent()->doMoreRecordsExist( this ,IFASTBP_PROC::ACB_LIST );
      GetDlgItem(IDC_MORE)->EnableWindow(bMoreRecordsExist);
   }
}

//******************************************************************************
void ACBDlg::DisplayTitle()
{
   TRACE_METHOD( CLASSNAME, I_("DisplayTitle"));

   DString dstrShrNum;
   getParent()->getField(this, ifds::ShrNum, dstrShrNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   SetAccount( AccountNum );

   DString dstrEntityName;

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), AccountNum,dstrEntityName );

   SetShrAcctCaption(dstrShrNum, AccountNum, dstrEntityName);
}

//******************************************************************************
void ACBDlg::PopulateFundAndFundClass()
{
   TRACE_METHOD( CLASSNAME, I_("PopulateFundAndFundClass"));

   m_FundList.ResetContent();

   DString str,str1;
   CString tmp;
   const DString *ty=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::FUND_LIST ));

   if( (*ty)!=NULL_STRING )
   {
      do
      {
         getParent()->getField( this, IFASTBP_PROC::FUND_LIST, ifds::rxFundCode, str );
         str.stripAll().upperCase();
         getParent()->getField( this, IFASTBP_PROC::FUND_LIST, ifds::rxClassCode, str1 );
         str1.stripAll().upperCase();
         makeFundClassString(str,str1,tmp);
         m_FundList.InsertString(-1,tmp);
      }while( *(ty=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::FUND_LIST ))) != NULL_STRING );
   }

   if( m_FundList.GetCount()>0 )
   {
      makeFundClassString(FundCode,ClassCode,tmp);
      m_FundList.SelectString(0,tmp);
   }
//	else // only to achieve the one line combobox!
//		m_FundList.InsertString(-1,_T(""));
}

////******************************************************************************
//void ACBDlg::OnItemchangedLvAcbTrans(NMHDR* pNMHDR, LRESULT* pResult) 
//{
//   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//
//   //if( LVN_SELECTED )
//   //{
//   //   POSITION pos = m_ACBList.GetFirstSelectedItemPosition();
//
//   //   if( pos != NULL )
//   //   {
//   //      DString str;
//   //      CString TransType;
//
//   //      DString *strKey=(DString*)m_ACBList.GetItemData( m_ACBList.GetNextSelectedItem( pos ) );
//   //      getParent()->setCurrentListItem(this,IFASTBP_PROC::ACB_LIST,*strKey);
//
//   //      // get TransType
//   //      getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::TransType, str, false );
//
//   //      if (DSTCommonFunctions::codeInList (str.strip().upperCase(), MONEYOUTLIST))
//   //      {
//   //         getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::GainOrLossAmt, str );
//   //         str.stripAll();
//   //         AccountCurrency.stripAll().c_str();
//   //         str+=(SPACE+AccountCurrency);
//   //         m_RealizedGain=str.c_str();
//   //      }
//   //      else
//   //         m_RealizedGain=NULL_STRING;
//
//   //      UpdateData(FALSE);
//   //   }
//   //}
//   *pResult = 0;
//}

//******************************************************************************
void  ACBDlg::DoListItemChanged(UINT listControlID,
                                        const DString &strKey, 
                                        bool bIsNewItem, 
                                        bool bIsDummyItem)
{
   DString str;
   if( listControlID == IDC_LV_ACB_TRANS )
   {
      if( GetList (listControlID)->GetItemCount () > 0 )
      {
         DString str;
         CString TransType;

         // get TransType
         getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::TransType, str, false );

         if (DSTCommonFunctions::codeInList (str.strip().upperCase(), MONEYOUTLIST))
         {
            DString dstrGainOrLossAmt, dstrGainOrLossCurrency;
            getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::GainOrLossAmt, dstrGainOrLossAmt );
            getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::GainOrLossCurrency, dstrGainOrLossCurrency, false);
            //getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::Currency, dstrGainOrLossCurrency, false);
            dstrGainOrLossAmt.stripAll();
            dstrGainOrLossCurrency.stripAll();
            
            str = dstrGainOrLossAmt + SPACE + dstrGainOrLossCurrency;
            m_RealizedGain=str.c_str();
         }
         else
         {
            m_RealizedGain=NULL_STRING;
         }

         DString rxFundCode, rxFundClass, adjustedCost, aCBPerUnit;

         getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::rxFundCode, rxFundCode );
         rxFundCode.stripAll().upperCase();

         getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::rxClassCode, rxFundClass );
         rxFundClass.stripAll().upperCase();

         getCurNAV(rxFundCode,rxFundClass,m_CurrentNAV, m_FundCurrency);
         getMarketValue(rxFundCode,rxFundClass,m_MarketValue);
         getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::AdjustedCost, adjustedCost);
         adjustedCost.stripAll();
         getParent()->getField( this, IFASTBP_PROC::ACB_LIST, ifds::ACBPerUnit, aCBPerUnit);
         aCBPerUnit.stripAll();

         DString dstrFndClsACBAvailable;

         //to set the list cursor on the current item
         getParent()->getCurrentListItemKey(this, IFASTBP_PROC::FUND_LIST);
         getParent()->getField(this, IFASTBP_PROC::FUND_LIST, ifds::FndClsACBAvailable, dstrFndClsACBAvailable, false);

         if ( dstrFndClsACBAvailable == I_("N") ) 
         {
            m_AdjustedCost.LoadString(TXT_SUPPRESS_ACB_ACCOUNT);
            m_UnitACB.LoadString(TXT_SUPPRESS_ACB_ACCOUNT);
         } 
         else
         {
            DisplayFormat(adjustedCost, (BFFieldId)ifds::AdjustedCost );
            m_AdjustedCost=adjustedCost.c_str();
            DisplayFormat(aCBPerUnit, ( BFFieldId )ifds::ACBPerUnit );
         }

         updatePlugControls();
         displayGIAOpeningMV();

         UpdateData(FALSE);
      }
   }
}

//******************************************************************************
void ACBDlg::makeFundClassString(DString &FundCode, DString &Class, CString &out)
{
   out=NULL_STRING;
   FundCode.stripAll();
   Class.stripAll();
   if( FundCode!=M1 )
   {
      out=FundCode.c_str();
      out+=SAPERATOR;
      out+=Class.c_str();
   }
}

//******************************************************************************
void ACBDlg::OnSelendokCmbFund() 
{
   TRACE_METHOD( CLASSNAME, I_("OnSelendokCmbFund"));

   ClearText();

   if( m_FundList.GetCount()>0 )
   {
      CWaitCursor wait;
      CString tmp;

      if (m_FundList.GetCurSel() == -1)
      {
         //when no selected item exist, always set it to the first one
         m_FundList.SetCurSel(0);
      }

      m_FundList.GetLBText(m_FundList.GetCurSel(),tmp);
      if( !tmp.IsEmpty() )
      {
         getFunandClass(tmp, FundCode,ClassCode);

         setParameter( pACCOUNTNUM, AccountNum );
         setParameter( pFUNDCODE, FundCode ); 
         setParameter( pCLASSCODE, ClassCode ); 
         SetMessageStatusBar( TXT_LOAD_ACB );

         getParent()->performSearch( NULL, BF::NullContainerId, SEARCH_START);
         getParameter( ACCCURRENCY, AccountCurrency);

         PopulateACBList();
         SetMessageStatusBar(NULL_STRING);
      }
   }
   else
   {
      DisplayTitle();
      //m_ACBList.DeleteAllItems();
      m_FundList.InsertString(-1,_T(""));
   }

   updatePlugControls();
}

//******************************************************************************
void ACBDlg::getFunandClass(CString &src, DString &fundCode, DString &fundClass)
{
   int count=src.Find(SAPERATOR);

   CString tmp;
   tmp=src.Left(count);
   fundCode=tmp.GetBuffer(0);
   tmp.ReleaseBuffer(-1);
   tmp=src.Right(src.GetLength()-count-1);
   fundClass=tmp.GetBuffer(0);
   tmp.ReleaseBuffer(-1);
}

//******************************************************************************
void ACBDlg::getCurNAV(DString &FundCode, DString &ClassCode, CString &NAV, CString &cstrFundCurrency )
{
   CString tmp,tmp1;
   DString str,str1;
   const DString *ty=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::FUND_LIST ));

   if( (*ty)!=NULL_STRING )
   {
      do
      {
         getParent()->getField( this, IFASTBP_PROC::FUND_LIST, ifds::rxFundCode, str );
         str.stripAll().upperCase();
         getParent()->getField( this, IFASTBP_PROC::FUND_LIST, ifds::rxClassCode, str1 );
         str1.stripAll().upperCase();
         makeFundClassString(str,str1,tmp);
         m_FundList.GetLBText(m_FundList.GetCurSel(),tmp1);
         if( tmp==tmp1 )
         {
            getParent()->getField( this, IFASTBP_PROC::FUND_LIST, ifds::FundNAV, str );
            DisplayFormat(str, (BFFieldId)ifds::FundNAV);
            str.stripAll();
            NAV=str.c_str();

            str = I_( "" );
            getParent()->getField( this, IFASTBP_PROC::FUND_LIST, ifds::FundCurrency, str, false );
            str.stripAll();
            cstrFundCurrency=str.c_str();
            return;
         }
      }while( *(ty=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::FUND_LIST ))) != NULL_STRING );
   }
}

//******************************************************************************
void ACBDlg::getMarketValue(DString &FundCode, DString &ClassCode, CString &MV)
{
   CString tmp,tmp1;
   DString str,str1;

   const DString *ty=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::FUND_LIST ));

   if( (*ty)!=NULL_STRING )
   {
      do
      {
         getParent()->getField( this, IFASTBP_PROC::FUND_LIST, ifds::rxFundCode, str );
         str.stripAll().upperCase();
         getParent()->getField( this, IFASTBP_PROC::FUND_LIST, ifds::rxClassCode, str1 );
         str1.stripAll().upperCase();
         makeFundClassString(str,str1,tmp);
         m_FundList.GetLBText(m_FundList.GetCurSel(),tmp1);
         if( tmp==tmp1 )
         {
            getParent()->getField( this, IFASTBP_PROC::FUND_LIST, ifds::ACBSettledValue, str );
            DisplayFormat( str, (BFFieldId)ifds::SettledValue );
            str.stripAll();
            MV=str.c_str();
            return;
         }
      }while( *(ty=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::FUND_LIST ))) != NULL_STRING );
   }
}

//******************************************************************************
bool ACBDlg::isFndClsACBAvailable(DString fundCode, DString classCode)
{
   const DString *ty=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::FUND_LIST ));
   bool isFndClassACBAvailable = true;

   fundCode.stripAll().upperCase();
   classCode.stripAll().upperCase();
   if( (*ty)!=NULL_STRING )
   {
      do
      {
         DString rxFundCode, rxClassCode;

         getParent()->getField(this, IFASTBP_PROC::FUND_LIST, ifds::rxFundCode, rxFundCode);
         rxFundCode.stripAll().upperCase();
         getParent()->getField(this, IFASTBP_PROC::FUND_LIST, ifds::rxClassCode, rxClassCode);
         rxClassCode.stripAll().upperCase();
         if (fundCode == rxFundCode && classCode == rxClassCode)
         {
            DString fndClsACBAvailable;

            getParent()->getField( this, IFASTBP_PROC::FUND_LIST, 
               ifds::FndClsACBAvailable, fndClsACBAvailable, false );
            if (fndClsACBAvailable == I_("Y")) 
            {
               isFndClassACBAvailable = true;
            } else if (fndClsACBAvailable == I_("N")) 
            {
               isFndClassACBAvailable = false;
            } else
            {
               assert( 0 );
            }
         }
      }while( *(ty=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::FUND_LIST ))) != NULL_STRING );
   }

   return isFndClassACBAvailable;
}

//******************************************************************************
bool ACBDlg::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{  
   getParameter( ACCCURRENCY, AccountCurrency);
   getParameter( pACCOUNTNUM, AccountNum );
   getParameter( pFUNDCODE, FundCode ); 
   getParameter( pCLASSCODE, ClassCode ); 

   PopulateFundAndFundClass();

   OnSelendokCmbFund();

   DisplayTitle();

   return(true);
}

//******************************************************************************
void ACBDlg::ClearText()
{
   m_RealizedGain=NULL_STRING;
   m_AdjustedCost=NULL_STRING;
   m_UnitACB=NULL_STRING;
   m_CurrentNAV=NULL_STRING;
   m_MarketValue=NULL_STRING;
   m_AccountCurrency=NULL_STRING; 
   m_FundCurrency=NULL_STRING;
   UpdateData(FALSE);
}

//******************************************************************************
bool ACBDlg::GetOverrideItemString(long lSubstituteId, 
                                           const DString &ColumnKey, 
                                           DString &strOut)
{
   if( lSubstituteId == ifds::ACBListHeading.getId() )
   {
      CString tmp;
      
      if (ColumnKey == ADJUSTEDCOST || ColumnKey == ACBPERUNIT)
      {
         DString rxFundCode, rxClassCode;
         getParent()->getField(this, IFASTBP_PROC::ACB_LIST, ifds::rxFundCode, rxFundCode);
         getParent()->getField(this, IFASTBP_PROC::ACB_LIST, ifds::rxClassCode, rxClassCode);
         if (!isFndClsACBAvailable(rxFundCode, rxClassCode))
         {
            tmp.LoadString(TXT_SUPPRESS_ACB_FUND);
            strOut = tmp.GetBuffer(0);
            tmp.ReleaseBuffer(-1);

            return true;
         }
      }
   }
   return(false);
}

//******************************************************************************
//P0185327_FN01 - ROC Depleting ACB
void ACBDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));

   CWaitCursor wait;

   IFastHistoricalInfo historicalInfo;

   historicalInfo( this, IFASTBP_PROC::ACB_LIST );
}

//******************************************************************************
void ACBDlg::OnBtnReset() 
{
   ResetListItem( IDC_LV_ACB_TRANS );
}

//******************************************************************************
bool ACBDlg::GetDataForControl( UINT controlID,
                                DString &strValueOut,
                                bool bFormatted,
                                int index ) const
{
   bool bReturn = false;
   
   DString str12319999;
   DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pDSTWorkSession->getDateInHostFormat (str12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, BF::HOST);

   if( controlID == IDC_STC_ACB_PLUG_DATE )
   {
      DString fieldValue(NULL_STRING);
      strValueOut = NULL_STRING;
      const BFFieldId& bfFieldId = GetControl(controlID)->GetFieldID();

      getParent()->getField( this, IFASTBP_PROC::ACB_LIST, bfFieldId, fieldValue, false );
      
      if(fieldValue.strip().upperCase().empty())
      {
         fieldValue = str12319999;
      }
      
      if(bFormatted)
      {
         BFDate date(fieldValue, BFDate::DATE_FORMAT::DF_MMDDCCYY );
         const ClientLocale& locale = ClientLocaleContext::get();
         const BFDate::DATE_FORMAT& fmt = getDateFormatFromClientLocale(locale);
         const DString dstrDateOut = date.get(fmt);
         if ( !dstrDateOut.empty() )
         {
            strValueOut += dstrDateOut;
         }
      }
      else
      {
         strValueOut += fieldValue;
      }

      bReturn = true;
   }

   return bReturn;
}

//*************************************************************************
BFDate::DATE_FORMAT ACBDlg::getDateFormatFromClientLocale(const ClientLocale& rLocale) const
{
   static const DString dstrConfiguration( I_( "DisplayMasks" ) );
   DString dstrKey = rLocale.getLocale() + I_( "-D" );

   DString mask = GetConfigValueAsString( ConfigManager::getApplication(), 
                                          dstrConfiguration,
                                          dstrKey );
   if( mask.size() == 0 )
   {
      static const DString dstrHostConfiguration( I_( "HostMasks" ) );
      static const DString dstrType( I_( "D" ) );
      DString dstrHostKey;
      dstrHostKey.append( dstrType );

      DString hostMask = GetConfigValueAsString( I_( "DICORE" ),
                                                 dstrHostConfiguration,
                                                 dstrHostKey );

      if( hostMask.size() == 0 )
      {
         return BFDate::DATE_FORMAT::DF_MMDDCCYY;
      }
      else
      {
         return inferMaskFormat( hostMask );
      }
   }
   else
   {
      return inferMaskFormat( mask );
   }
}

//*************************************************************************
BFDate::DATE_FORMAT ACBDlg::inferMaskFormat( const DString& dstrMask ) const
{
   // look for the dd|DD, the mm|MM, and the ccyy|CCYY|yyyy|YYYY
   int iDay = dstrMask.find( I_( "DD" ) );
   if( iDay == dstrMask.npos ) iDay = dstrMask.find( I_( "dd" ) );

   int iMonth = dstrMask.find( I_( "MM" ) );
   if( iMonth == dstrMask.npos ) iMonth = dstrMask.find( I_( "mm" ) );

   int iYear = dstrMask.find( I_( "CCYY" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "ccyy" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "YYYY" ) );
   if( iYear == dstrMask.npos ) iYear = dstrMask.find( I_( "yyyy" ) );

   // if day, month, or year are not known then give up
   if( iDay == dstrMask.npos ||
       iMonth == dstrMask.npos ||
       iYear == dstrMask.npos )
   {
      return( BFDate::DATE_FORMAT::DF_NULL );
   }

   // what is the separator?
   bool bFS = false;
   bool bFD = false;
   if( dstrMask.find( I_( "/" ) ) != dstrMask.npos ) bFS = true;
   else if( dstrMask.find( I_( "-" ) ) != dstrMask.npos ) bFD = true;

   if( iYear < iMonth )
   {
      // it's ISO
      if( bFS ) return( BFDate::DATE_FORMAT::DF_FSISO );
      if( bFD ) return( BFDate::DATE_FORMAT::DF_FDISO );
      return( BFDate::DATE_FORMAT::DF_ISO );
   }
   else if( iDay < iMonth )
   {
      // it's European format (dd/mm/yyyy)
      if( bFS ) return( BFDate::DATE_FORMAT::DF_FSEURO );
      if( bFD ) return( BFDate::DATE_FORMAT::DF_FDEURO );
      return( BFDate::DATE_FORMAT::DF_EURO );
   }
   else if( iMonth < iDay && iDay < iYear )
   {
      // it's US format
      if( bFS ) return( BFDate::DATE_FORMAT::DF_FSUS );
      if( bFD ) return( BFDate::DATE_FORMAT::DF_FDUS );
      return( BFDate::DATE_FORMAT::DF_US );
   }
   else
   {
      //unknown format! therefore forced it as mmddyyyy
      return( BFDate::DATE_FORMAT::DF_MMDDCCYY );
   }
}

////*************************************************************************
//void ACBDlg::ControlUpdated( UINT controlID, const DString &strValue )
//{
//	DString dstrAcctPurpose;
//   switch( controlID )
//   {
//      default:
//         break;
//   }
//}

//******************************************************************************
void ACBDlg::updatePlugControls(void)
{
   DString strACBPlugDate;
   getParent()->getField(this, IFASTBP_PROC::ACB_LIST, ifds::ACBPlugDate, strACBPlugDate, false);
   strACBPlugDate.strip().upperCase();
   if( !strACBPlugDate.empty() )
   {
      GetDlgItem (IDC_EDT_ACB_PLUG_AMOUNT)->ShowWindow (SW_SHOW);
      GetDlgItem (IDC_STC_ACB_PLUG_DATE)->ShowWindow (SW_SHOW);
      GetDlgItem (IDC_STATIC_GEN_10)->ShowWindow (SW_SHOW);
      GetDlgItem (IDC_STATIC_GEN_11)->ShowWindow (SW_SHOW);

      ConnectControlToData (IDC_EDT_ACB_PLUG_AMOUNT,true);
      LoadControl(IDC_EDT_ACB_PLUG_AMOUNT);
      ConnectControlToData(IDC_STC_ACB_PLUG_DATE, true);
      LoadControl(IDC_STC_ACB_PLUG_DATE);
   }
   else
   {
      GetDlgItem (IDC_EDT_ACB_PLUG_AMOUNT)->ShowWindow (SW_HIDE);
      GetDlgItem (IDC_STC_ACB_PLUG_DATE)->ShowWindow (SW_HIDE);
      GetDlgItem (IDC_STATIC_GEN_10)->ShowWindow (SW_HIDE);
      GetDlgItem (IDC_STATIC_GEN_11)->ShowWindow (SW_HIDE);
   }
}



//******************************************************************************
void ACBDlg::displayT5EventDate()
{
    //If the selected fund is an GIA fund and there is a T5 date on account, display T5 Anniversary Date.
    
    DString dstrIsGIAFund, dstrT5AnniversaryDate;
    bool displayT5Date;

    getParent()->getField(this, IFASTBP_PROC::ACB_LIST, ifds::IsGIAFund, dstrIsGIAFund);
    getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::T5AnniversaryDate, dstrT5AnniversaryDate, false);
    displayT5Date = dstrIsGIAFund == Y && !dstrT5AnniversaryDate.empty() && 
                    (DSTCommonFunctions::CompareDates(dstrT5AnniversaryDate, I_("12319999")) != DSTCommonFunctions::EQUAL);

    ConnectControlToData(IDC_STATIC_NEXT_T5_ANNIVERSARY_DATE_VALUE, displayT5Date);
    LoadControl(IDC_STATIC_NEXT_T5_ANNIVERSARY_DATE_VALUE);

    GetDlgItem (IDC_STATIC_NEXT_T5_ANNIVERSARY_DATE_LABEL)->ShowWindow(displayT5Date ? SW_SHOW:SW_HIDE);
    GetDlgItem (IDC_STATIC_NEXT_T5_ANNIVERSARY_DATE_VALUE)->ShowWindow(displayT5Date ? SW_SHOW:SW_HIDE);
}



//******************************************************************************
void ACBDlg::displayGIAOpeningMV()
{
    //If the selected fund is an GIA fund, displays Opening Market Value for ecah transaction which user selects.

    DString dstrIsGIAFund;
    bool displayOpenMktMV = false;

    getParent()->getField(this, IFASTBP_PROC::ACB_LIST, ifds::IsGIAFund, dstrIsGIAFund);
    displayOpenMktMV = dstrIsGIAFund == Y;

    ConnectControlToData(IDC_STATIC_MARKET_VALUE, displayOpenMktMV);
    LoadControl(IDC_STATIC_MARKET_VALUE);

    GetDlgItem (IDC_STATIC_OPENING_MARKET_VALUE_LABEL)->ShowWindow(displayOpenMktMV ? SW_SHOW:SW_HIDE);
    GetDlgItem (IDC_STATIC_MARKET_VALUE)->ShowWindow(displayOpenMktMV ? SW_SHOW:SW_HIDE);
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ACBDlg.cpp-arc  $
 * 
 *    Rev 1.22   May 14 2012 09:30:42   kitticha
 * P0186477 FN06 - T5 Processing.
 * 
 *    Rev 1.21   Sep 15 2011 05:42:26   wutipong
 * IN2624492 - AF Gain/Loss - Not showing in desktop
 * 
 *    Rev 1.20   Sep 14 2011 23:45:42   wutipong
 * IN2428690 - Realized Gain/Loss for Admin Fee is not showing in Desktop
 * 
 *    Rev 1.19   Sep 14 2011 10:15:40   panatcha
 * P0185327_FN01 - ROC Depleting ACB
 * 
 *    Rev 1.18   Nov 30 2007 14:42:08   jankovii
 * Sync up: PET 5517 FN01B - Gap 1.
 * 
 *    Rev 1.17   19 Nov 2007 12:17:38   kovacsro
 * PET 2313 FN11 - added  ACBSettledValue
 * 
 *    Rev 1.16   Nov 09 2005 10:14:54   zhengcon
 * Fix incident #449373 (Viewing the Adjusted Cost Base screen creates an error message in Desktop), the problem is caused by no selection in fund list
 * 
 *    Rev 1.15   Sep 15 2005 15:09:26   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.14   Jun 24 2005 17:00:18   Fengyong
 * PET1250 FN02 - EuroPean numeric enhancement
 * 
 *    Rev 1.13   Sep 09 2004 10:24:46   ZHANGCEL
 * Code clean up by grouping transtype
 * 
 *    Rev 1.12   Jun 28 2004 16:39:10   AGUILAAM
 * PET1084_FN1 : display redirected transactions, applicable for ACB only
 * 
 *    Rev 1.11   Apr 15 2003 13:13:24   VADEANUM
 * PTS10009117 - Currency related calculations - Display Fund Currency Code not description (i.e. change flag for substitution)
 * 
 *    Rev 1.10   Apr 12 2003 16:28:44   VADEANUM
 * PTS10015590 - Use FndClsACBAvailable instead of acctACBAvailable.
 * 
 *    Rev 1.9   Apr 12 2003 15:34:52   VADEANUM
 * PTS10009117 - Currency related calculations - Display Fund Currency and clarify which Currency is used at the top right of the screen.
 * 
 *    Rev 1.8   Mar 21 2003 18:30:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Feb 05 2003 11:08:42   popescu
 * Displaying the ACB string when ACB cannot be calculated
 * 
 *    Rev 1.6   Oct 09 2002 23:55:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Sep 30 2002 11:01:30   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.4   22 May 2002 19:15:26   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   27 Mar 2002 20:00:46   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.2   03 May 2001 14:07:22   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.1   Aug 02 2000 13:44:46   VADEANUM
 * Title Bar Standards
 * 
 *    Rev 1.0   Feb 15 2000 11:01:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Sep 30 1999 09:54:44   YINGZ
 * use sub list
 * 
 *    Rev 1.9   Aug 17 1999 12:23:16   DT24433
 * changed getFieldFromCurrentListItem to getField
 * 
 *    Rev 1.8   Aug 08 1999 14:50:42   VASILEAD
 * changed to allow proper refresh
 * 
 *    Rev 1.7   Jul 30 1999 11:12:58   YINGZ
 * solve empty fund problem
 * 
 *    Rev 1.6   Jul 28 1999 16:22:52   YINGZ
 * Add to grey our realized gain
 * 
 *    Rev 1.5   Jul 27 1999 15:18:34   YINGZ
 * add support to new db data
 * 
 *    Rev 1.4   Jul 20 1999 14:24:26   YINGZ
 * ?
 * 
 *    Rev 1.3   Jul 09 1999 16:48:48   YINGZ
 * change listview support to use Jerry's fix
 * 
 *    Rev 1.2   Jul 09 1999 06:18:30   HUANGSHA
 * 990708 Test
 * 
 *    Rev 1.1   Jul 08 1999 10:04:26   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

