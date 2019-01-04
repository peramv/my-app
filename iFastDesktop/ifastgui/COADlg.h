
#ifndef COADLG_H
#define COADLG_H
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
// ^FILE   : COADlg.h
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ^CLASS    : COADlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#define LAST_NAME_COLUMN         0
#define FIRST_NAME_COLUMN        1
#define TELEPHONE_NUM_COLUMN     2
#define ADDRESS_COLUMN           3

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#ifndef _GXALL_H_
   #include <gxall.h>
#endif

class COADlg : public BaseMainDlg
{
public:
   enum COA_Type
   {
      COA_TYPE_TITLE = 0, COA_TYPE_CAUTION, COA_TYPE_OPTION, COA_TYPE_ATTRIB
   };
   enum COA_ENTRY_ID
   {
      COA_NONE_ID,

      TTL_STOPS_ID,
      TTL_SCREENS_ID,
      TTL_FEES_ID,
      TTL_SUPRESS_ID,
      TTL_MISC_ID,
      TTL_NSCC_ID,

      STP_PURCH_ID,
      STP_REDEM_ID,
      STP_REDEM_SETTLE_ID,
      STP_XFERO_ID,
      STP_XFERI_ID,
      STP_FRREB_ID,
      STP_AMSREBALANCING_ID,

//                        STP_EXCHG_ID,

      SCR_REMARK_ID,
      SCR_BANK_ID,  
      SCR_SYSTR_ID, 
      SCR_PAC_ID,   
      SCR_SWP_ID,   
      SCR_SAVING_PLAN_ID,   
      SCR_RRIF_ID,
      SCR_ALLOC_ID, 
      SCR_ACB_ID,   
      SCR_ADDR_ID,  
      SCR_ENTITY_ID,
      SCR_DEFSCH_ID,
      SCR_INTACR_ID,
	  SCR_ACCIDENT_ID,
      SCR_ACCINF_ID,
      SCR_FEES_ID,  
      SCR_DISTR_ID, 
      SCR_DEMOGR_ID,
      SCR_CERTIF_ID,
      SCR_CHEQUE_ID,
      SCR_SHR_ID,   
      SCR_BENEF_ID,
      SCR_ESCROW_ID,
      SCR_CONTRACT_ID,
      SCR_GUARANTEE_ID,
      SCR_RESP_ID,
      SCR_YTD_ID,
      SCR_ACCT_FEE_ID,
      SCR_AS_PENSION_PLAN_ID,
      SCR_ESOP_ID,
      SCR_PENSION_INFO,
      SCR_ACCOUNTREVIEW_ID,
      SCR_ACCT_SPLIT_COMM,
      SCR_AMS_ID,
      SCR_HYPORED_ID,
      SCR_FOREIGN_CONTENT_WORKSHEET_ID,
      SCR_SHR_FAMILY_ID,
      SCR_ACCT_CATEGORY_ID,
      SCR_DIRECT_TRADING,
      SCR_ACCT_SETTLE_LOC,
      SCR_SHR_FUND_SPONSOR_AGREEMENT,
      SCR_SHR_FUND_BROKER,
      SCR_TAX_EXEMPT_AUTHORIZATION_ID,
      SCR_ACCT_FEE_MODEL,
      SCR_ACCT_CUT_OFF_ID,
      SCR_FUND_CLASS_LIMITATION,
      SCR_ACCT_LEVEL_SETTLEMENT_RULE,
      SCR_LIF_GAIN_LOSS_ID,
      SCR_INVESTOR_AUTHORIZATION,
      SCR_RESP_ACCOUNT_TERMINATION,
      SCR_RESP_ZERO_GRANT,
      SCR_RESP_INTERFACE_FILE,
      SCR_ACCT_GUARNT_GUARD_OPTN,
      SCR_ACCT_TRAILER_FEE,
      SCR_RESP_GOVT_FILING_AMENDMENT,
      SCR_CASHSWEEP_INSTR,
      SCR_MATURITYINT_INSTR,
      SCR_ACCT_OWNERSHIP_ALLOC,
      SCR_VALUE_VARIATION,
      SCR_ACCT_FEE_MODEL_ASSOCIATION,
      SCR_SHR_STATEMENT_SCHED,
      SCR_ACCOUNT_GROUP,
      SCR_PRIVATE_WEALTH_INFO,

      FEE_ADMFEE_ID,
      FEE_WTHDTX_ID,
      FEE_FEEWVD_ID,
      FEE_BANK_CHARGE_ID,

      GST_EXEMPT_ID,
      PST_EXEMPT_ID,

      SPR_EMPCNF_ID,
      SPR_CONFIRM_ID,

      MSC_EMPL_ID,
      MSC_INTRFOR_ID,
      MSC_STATUS_ID,
      MSC_UNSZBL_ID,
      MSC_RESP_ID,
      MSC_CONSOLID_EFT_ID,
      MSC_TELFAX_AGREEMENT_ID,
      MSC_CLEARING_ID,
      MSC_MARKET_MAIL,
      MSC_NETWORKCONTROLIND,
      MSC_NETWORK_ID,
      MSC_PW_CONSOL_TYPE_ID,
      MSC_ID_CONSOL_TYPE_ID,
      MSC_ED_CONSOL_TYPE_ID,
      MSC_ID_SIBLING_ONLY,
      MSC_AFFLUENT,
      MSC_UNLOCK_DATE,
      MSC_UNLOCK_AMOUNT,
      MSC_EXEMPT_PERIOD,
      MSC_ORGTYPE,
      MSC_SUBORGTYPE,
      MSC_DOC_PRINT_FORMAT,
      //NSCC-XYZ MSC_CLEARINGFIRM,

      //NSCC 
      NSC_CLEARINGFIRM,
      NSC_PARTICIPANTID,
      NSC_AGENTFORFIRM,
      NSC_TPA,
      NSC_SOCIAL_CODE,


      CAT_TITLE_ID,
      CAT_CAUTION_ID,
      CAT_OPTION_ID,
      CAT_ATTRIB_ID,

      FEE_MGMT_FEE_PAY_OPTN,

      FEE_EARLY_REDEMPTION_FEE_OPT,
      FEE_SHORT_TERM_TRFER_FEE,
      FEE_NEXT_MFR_PROCESS_DATE,

      HLD_DIV_PAYMENT,
      STP_REASON_ID,
      STP_ADDITIONAL_REASON_ID,
      SCR_DOC_LIST_ID,
      STP_STOP_NFU,
      MSC_NONFINANCIAL_CONFIRM,
      MSC_SETTLEMENT_CURRENCY,
      MSC_STOP_ADJDATE, //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
      MSC_T5_ANNIVERSARY_DATE,
      SCR_ACCT_REGIS_MAINT,
      SCR_ENT_REGIS_MAINT,
      SCR_TAX_SLIPS,
      MSC_AGGREGATION_TYPE,
	  SCR_RESP_GRANT_INFO,
	  SCR_RESP_GRANT_INFO2,
	  SCR_RESP_NOTIONAL_ACTIVITY,
	  SCR_REGISTERED_PLAN_TRANSFER,
	  SCR_ACCT_ROUNDING_RULE,
	  SCR_ACCT_DELETION_REVIEW,
	  MSC_INVESTOR_CLASSIFICATION,
	  SCR_RDSP_ACCOUNT_INFO,
	  SCR_RDSP_NOTIONAL_ACTIVITY,
	  SCR_RDSP_NOTIONAL_BALANCE,
   };
   enum CHOICE_TYPE
   {
      CHOICE_TYPE_YES_NO,
      CHOICE_TYPE_CHANGE,
      CHOICE_TYPE_VIEW,
      CHOICE_TYPE_USER,
      CHOICE_TYPE_FIELD_SUBST
   };

private:
   class COAGrid : public CGXGridWnd
   {
      public :
      COAGrid():m_COADlg(NULL){

      };
      virtual ~COAGrid(){


      };
      BOOL OnValidateCell(ROWCOL nRow, ROWCOL nCol);
      BOOL OnLButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
      BOOL OnDeleteCell(ROWCOL nRow, ROWCOL nCol);
      BOOL OnActivateGrid( BOOL bActivate );
      BOOL MoveCurrentCell(int direction, UINT nCell = 1, BOOL bCanSelectRange = TRUE);
      BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags);

      void LoadSettings();
      void SaveSettings();

      void setCOADlg(COADlg * pCOADlg)
      {
         m_COADlg = pCOADlg;
      };
   private :
      COADlg * m_COADlg;
   };

   class COAElement
   {

   public :
      COAElement( COA_ENTRY_ID lId, const CString & lDispName, COA_Type lType, const CString & lCommand, bool lHasChange, COA_ENTRY_ID lParent, 
                  WORD  lControlType, CHOICE_TYPE eChoiceType = CHOICE_TYPE_YES_NO );
      virtual ~COAElement();
      CString        m_DisplayName;
      CString        m_Command;
      bool           m_HasChange;
      COA_Type       m_Type;
      bool           m_Visible;
      bool           m_Filtered;
      bool           m_Enabled;
      COA_ENTRY_ID   m_Parent;
      COA_ENTRY_ID   m_Id;
      CString        m_Value;
      CString        m_ChoiceList;
      CHOICE_TYPE    m_ChoiceType;
      WORD           m_ControlType;
      CString        m_ComboValue;
      void           setComboValue(const CString& cstrValue){
         m_ComboValue = cstrValue;
      };

      CString&       getComboValue(){
         return(m_ComboValue);
      }; 

      CString      & getDisplayName() { return(m_DisplayName);};
      CString      & getCommand()     { return(m_Command);};
      bool           getHasChange()   { return(m_HasChange);};
      COA_Type       getType()        { return(m_Type);};
      bool           isTitle()        { return(m_Type == COA_TYPE_TITLE);};
      bool           isVisible()      { return(m_Visible && m_Filtered);};
      void           setVisible( bool lVisible)  { m_Visible = lVisible;};
      COA_ENTRY_ID   getParent()      { return(m_Parent);};
      COA_ENTRY_ID   getId()          { return(m_Id);};
      CString        getDispType();
      CString     &  getChoiceList()  {return(m_ChoiceList);};
      void           setChoiceList( );
      void           setFiltered( bool lFiltered)  { m_Filtered = lFiltered;};
      bool           isEnabled()                   { return(m_Enabled);};
      void           setEnabled( bool lEnabled )   { m_Enabled = lEnabled;};
      void           setEnabledAndValue( bool lEnabled, const CString & newValue )
      {
         setEnabled( lEnabled );
         m_Value = m_Enabled ? newValue : I_("");
      };     
      WORD      getControlType(){return(m_ControlType);};
      void      setControlType( WORD  lControlType){ m_ControlType = lControlType;};

      CString & getValue() {
         return(m_Value);
      };
      void      setValue( const CString & newValue ){ 
         m_Value = newValue;
      };


   private:
      COAElement();
      COAElement& operator=( const COAElement &copy );
      COAElement( const COAElement &copy );

   };
   struct COAElementKey
   {
      long group;
      long entryID; 
      COAElementKey( long idGroup, long lentryID ):group(idGroup), entryID(lentryID){};
   };
   class less_COAElementKey
   {
   public:
      bool operator() ( const COAElementKey &a, const COAElementKey &b ) const
      {
         if( a.group != b.group )
         {
            return(a.group < b.group);
         }
         else if( a.entryID != b.entryID )
         {
            return(a.entryID < b.entryID);
         }
         else
         {
            return(false);
         }
      }

   };
   class COAElementMap : public std::map< COAElementKey, COAElement *, less_COAElementKey  >  
   {
   public :
      bool hasExpandedTitles( )
      {
         iterator it = begin();
         while( it != end() )
         {
            if( (*it).second->m_Visible )
               return(true);
            it++;
         };
         return(false);
      };

      COAElement * operator [](int pos)
      {
         iterator it = begin();
         int i = 0;
         while( it != end() )
         {
            if( (*it).second->isTitle() || (*it).second->isVisible() )
            {
               if( i == pos )
                  return(*it).second;
               i++;
            }
            it++;
         };
         return(NULL);
      };

      int itemCount()
      {
         int i = 0;
         iterator it = begin();
         while( it != end() )
         {
            if( (*it).second->isTitle() || (*it).second->isVisible() )
               i++;
            it++;
         };
         return(i);
      };
      iterator find( long lId)
      {
         iterator it = begin();
         while( it != end() )
         {
            if( (*it).first.entryID == lId )
               break;
            it++;
         };
         return(it);
      }
      void changeGroupState( long group, bool expanded )
      {
         int i = 0;
         iterator it = begin();
         while( it != end() )
         {
            if( (*it).first.group == group )
               (*it).second->setVisible( expanded );
            it++;
         };
      };
      void filterCOA( long filtCrit )
      {
         int i = 0;
         iterator it = begin();
         while( it != end() )
         {
            if( filtCrit != COA_TYPE_TITLE && (*it).second->getType() != COA_TYPE_TITLE && (*it).second->getType() != filtCrit )
               (*it).second->setFiltered( false );
            else
               (*it).second->setFiltered( true );
            it++;
         };
      };

      int findNextMatch( long startfrom, CString & cstrCrit )
      {
         int noItems = itemCount();
         int i, curItem;
         CString dispName;

         for( i = startfrom; i < startfrom + noItems ; i++ )
         {
            curItem = i % noItems;
            if( operator[]( curItem )->isTitle() || operator[]( curItem )->isVisible() )
            {
               dispName = operator[]( curItem )->getDisplayName();
               dispName.MakeUpper();
               dispName.TrimLeft();
               if( !operator[]( curItem )->isTitle() && dispName.Find( cstrCrit ) == 0 )
                  return(curItem);
            };
         };
         return(-1);
      };
/*
      int findNextMatch( long startfrom, CString & cstrCrit )
      {
         int i = 1;
         iterator it = begin();
         while ( i <= startfrom )
         {
            ++i,++it; 
         };
         CString dispName;
         while ( true ) 
         {
            if( it == end())
            {
               it = begin();
               i = 1;
            };
            if ( (*it).second->isTitle() || (*it).second->isVisible() )
            {
               dispName = (*it).second->getDisplayName();
               dispName.MakeUpper();
               dispName.TrimLeft();
               if ( !(*it).second->isTitle() && dispName.Find( cstrCrit ) == 0 )
                  return i;
               else if (i++ == startfrom)
                  return -1;
            };
            it++;
         };
         return -1;
      };
*/

      int getFirstStartingWith( TCHAR lCrit)
      {
         int i = 0;
         iterator it = begin();
         CString dispName;
         while( it != end() )
         {
            if( (*it).second->isTitle() || (*it).second->isVisible() )
            {
               dispName = (*it).second->getDisplayName();
               dispName.MakeUpper();
               dispName.TrimLeft();
               if( !(*it).second->isTitle() && dispName[0] == lCrit )
                  return(i);
               else
                  i++;
            };
            it++;
         };
         return(-1);
      };

   };
public:
   void setTitlesButtonCaption( bool lExpand);
   void LButtonDblClkGridCells( unsigned long nRow, unsigned long nCol );
   bool validateGridCells( unsigned long nRow, unsigned long nCol, const CString & value);
   void reDisplayGrid();
   void updateSettlementLocation( const DString &dstrValue );
   void updateSubOrgType( const DString &dstrValue );

   /**
    * Standard dialog constructor for DSTC
    */
   COADlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   virtual ~COADlg ();

// Dialog Data
   //{{AFX_DATA(COADlg)
   enum
   {
      IDD = IDD_COA
   };
   CEdit m_edtFind;
   CComboBox m_cmbView;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(COADlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit();
   bool doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand ){ return(true);};
   /**
     * This is the implementation for OnOk processing to be done.  BaseMainDlg
     * enforces its actions by making OnOk private.
     * @returns a bool with true = perform Ok, false = stop process
     */
   virtual bool PreOk();
   // Generated message map functions
   //{{AFX_MSG(COADlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnCollapse();
   afx_msg void OnSelchangeCmbView();
   afx_msg void OnBtnSearch();
   afx_msg void OnChangeEdtFind();
   afx_msg void OnBtnHistorical();
   //}}AFX_MSG
   virtual void OnPostInitDialog();

   DECLARE_MESSAGE_MAP()

   private:


   void expandCollapseAll( bool bExpandCollapse );
   bool setCOAField( const BFContainerId& idList, const BFFieldId& idField, const CString & value)
   {   
      return(getParent()->setField( this, idList, idField, (LPCTSTR)value ) <= WARNING ? true : false);
   };
   void addCOARow( COA_ENTRY_ID   lId, const UINT strID, /*const CString & lDispName,*/ COA_Type lType, const CString & lStrCommand, bool lHasChange, COA_ENTRY_ID lParent, 
                   WORD lControlType, CHOICE_TYPE eChoiceType = CHOICE_TYPE_YES_NO, bool bAddBlankSubstitution = false );
   void addCOARow( COA_ENTRY_ID   lId, const CString & lDispName, COA_Type lType, const CString & lStrCommand, bool lHasChange, COA_ENTRY_ID lParent, 
                   WORD lControlType, CHOICE_TYPE eChoiceType = CHOICE_TYPE_YES_NO, bool bAddBlankSubstitution = false );
   void retrieveValue( long cellId );
   bool launchProcess( const DString & procId, COA_ENTRY_ID lId = COA_NONE_ID  );
   void selectItemInList( int index, const DString* key );
   DString getSubstitutionList(COA_ENTRY_ID lId);
   BFFieldId getSubstitutionId(COA_ENTRY_ID lId);
   DString getDescriptions(const DString& strSubstList);
   void retrieveHypoRedValue(COAElement &rCOAElem );
   bool validateAffluent();
   void validateSubOrgType();
   bool setRemoveUnwantedChars(CString &value);

   //NSCC new functions
   void setParticipantID();
   bool validateClearingFirm();

   CString m_strTitle;        // Title of dialog
   CString m_AcctSubstValues;        
   COAGrid m_gridWindow;
   bool m_lInNASU;
   COAElementMap m_ElementMap;
};

#endif // COADlg_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/COADlg.h-arc  $
 * 
 *    Rev 1.82   Jul 24 2012 19:13:46   dchatcha
 * P0179630 FN01 FATCA Project - Acct Ownership Allocation
 * 
 *    Rev 1.81   May 14 2012 09:34:54   kitticha
 * P0186477 FN06 - T5 Processing.
 * 
 *    Rev 1.80   May 14 2012 04:26:48   panatcha
 * P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
 * 
 *    Rev 1.79   Apr 16 2012 17:28:44   if991250
 * CPF Account Setup
 * 
 *    Rev 1.78   Jan 26 2012 05:57:38   panatcha
 * IN2747587 - guifn 223 - TFSA Amendment
 * 
 *    Rev 1.77   Jan 25 2012 09:00:24   panatcha
 * IN2747587 - guifn 223 - TFSA Amendment
 * 
 *    Rev 1.76   Jan 16 2012 13:44:32   wp040027
 * P0188394_Performance Fees - ERISA Functionality
 * 
 *    Rev 1.75   Nov 28 2011 09:22:46   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.74   Nov 15 2011 13:17:34   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.73   Oct 07 2011 14:29:42   dchatcha
 * P0191592 FN01 - NSCC Social Code
 * 
 *    Rev 1.72   Feb 01 2011 09:49:38   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.71   Oct 29 2010 07:06:10   dchatcha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.70   Sep 30 2010 10:09:52   jankovii
 * PET168727 FN22 - Trailer Fee Setup
 * 
 *    Rev 1.69   Sep 17 2010 06:33:14   kitticha
 * PETP0173756 FN02 Don't Bust the Rules.
 * 
 *    Rev 1.68   Jun 15 2010 11:28:34   jankovii
 * PET165541_FN09_QESI Phase 2
 * 
 *    Rev 1.67   Jul 09 2009 13:05:16   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.66   Apr 07 2009 10:26:48   jankovii
 * PET 157825 FN18 - MF and MFR Day 2.
 * 
 *    Rev 1.65   Dec 24 2008 10:15:52   jankovii
 * PET 142007 FN03 TFSA Phase 2.
 * 
 *    Rev 1.64   Nov 05 2008 14:40:08   jankovii
 * PET 5517 FN71 Unclaimed Property Phase 2.
 * 
 *    Rev 1.63   28 Aug 2008 11:43:44   kovacsro
 * PET142196FN01 Federal LockedIn RRSP - short term solution
 * 
 *    Rev 1.62   Jun 23 2008 14:40:00   jankovii
 * PET 59888 FN01 - AML Enhancement.
 * 
 *    Rev 1.61   06 May 2008 09:58:24   kovacsro
 * PET2255-FN47 New LIF - prepend the tax type to 'Gain/Loss'
 * 
 *    Rev 1.60   05 May 2008 14:51:24   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.59   Mar 11 2008 19:41:46   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.58   Dec 06 2007 19:42:16   smithdav
 * PET1200 FN02 - Dividend Processing enhancement.
 * 
 *    Rev 1.57   26 Oct 2007 16:33:00   kovacsro
 * IN# 1039915 - added validation for Affluent field
 * 
 *    Rev 1.56   Aug 14 2007 17:45:50   popescu
 * Incident# 962948 - made the afluent flag available in the COA dialog box
 * 
 *    Rev 1.55   Aug 08 2007 17:50:54   kovacsro
 * PET 2360 FN 29 - RESP
 * 
 *    Rev 1.54   Jan 24 2007 16:53:00   ZHANGCEL
 * PET2306 FN02 -- Add logic for the enhancement
 * 
 *    Rev 1.53   Oct 19 2006 09:37:28   fengyong
 * Temp check in for PET 2185 - Fund limitation
 * 
 *    Rev 1.52   Aug 31 2006 13:48:48   ZHANGCEL
 * PET2212 FN10 -- Add new row Consolidation type
 * 
 *    Rev 1.51   Feb 21 2006 10:44:28   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.50   Jul 07 2005 16:11:22   ZHANGCEL
 * PET1141 - FN05 -- Added a new function: validateClearingFirm
 * 
 *    Rev 1.49   Jul 06 2005 11:02:54   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.48   Jun 20 2005 11:25:22   hernando
 * PET1250 FN01 - Added SCR_ACCT_CUT_OFF_ID.
 * 
 *    Rev 1.47   Dec 21 2004 17:31:42   aguilaam
 * PTS 10037090 - add Market Mailing under Misc/COA Screen
 * 
 *    Rev 1.46   Nov 11 2004 16:28:54   vadeanum
 * PET1117 FN08 - Shareholder Fund Broker support.
 * 
 *    Rev 1.45   Sep 01 2004 16:07:02   YINGBAOL
 * PET1124:move "stop redemption settlement" below  stop redemption as winnie suggested.
 * 
 *    Rev 1.44   Aug 10 2004 11:28:04   FENGYONG
 * PET 1117 FN5 - Client Condition Fee
 * 
 *    Rev 1.43   Jul 29 2004 16:03:40   YINGBAOL
 * PET1124:Add Stop RedemptionSettlement  flag
 * 
 *    Rev 1.42   Jul 28 2004 14:59:14   ZHANGCEL
 * PET1082 FNrlc -- New Quebec withholding Tax
 * 
 *    Rev 1.41   Jul 26 2004 10:42:30   VADEANUM
 * PET1117 FN01 - Shareholder Static Data support.
 * 
 *    Rev 1.40   Apr 26 2004 13:32:50   VADEANUM
 * PET985 FN01 - Foreign Content - work in progress.
 * 
 *    Rev 1.39   Apr 05 2004 17:37:56   FENGYONG
 * PET944FN01 release 56.1 NSCC Broker
 * 
 *    Rev 1.38   Feb 18 2004 16:05:58   HERNANDO
 * PET965 FN11 - Added OnBtnHistorical.
 * 
 *    Rev 1.37   Nov 27 2003 10:35:28   HERNANDO
 * PET892 FN1 - Added Settlement Location.
 * 
 *    Rev 1.36   Oct 16 2003 12:34:54   FENGYONG
 * PET809 FN08 Direct Trading enhancement
 * 
 *    Rev 1.35   Aug 21 2003 09:20:26   linmay
 * added       MSC_TELFAX_AGREEMENT_ID
 * 
 *    Rev 1.34   Apr 29 2003 17:51:20   HERNANDO
 * Prudential AMS Rebalancing.  PET792.FN04.3 - Added ID.
 * 
 *    Rev 1.33   Mar 21 2003 18:34:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.32   Mar 14 2003 08:56:44   sanchez
 * Changes for Early Redemption Fee and Short Term Transfer Fee
 * 
 *    Rev 1.31   Jan 25 2003 17:06:26   KOVACSRO
 * Added Account Category ID
 * 
 *    Rev 1.30   Jan 13 2003 18:05:12   sanchez
 * Changes for Shareholer
 * 
 *    Rev 1.29   Dec 30 2002 10:16:18   sanchez
 *   -Added to COA_ENTRY_ID inum header FEE_MGMT_FEE_PAY_OPTN
 * 
 *    Rev 1.28   Nov 22 2002 15:26:48   KOVACSRO
 * Added retrieveHypoRedValue( ) private method.
 * 
 *    Rev 1.27   Nov 21 2002 13:09:54   KOVACSRO
 * Added HypoRed.
 * 
 *    Rev 1.26   Nov 06 2002 16:59:52   HERNANDO
 * Added AMS Option.
 * 
 *    Rev 1.25   Oct 09 2002 23:55:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.24   Aug 29 2002 12:57:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.23   Jul 11 2002 16:54:08   HSUCHIN
 * added account level split commission option
 * 
 *    Rev 1.22   Jun 10 2002 17:04:46   KOVACSRO
 * Support for Field substitution list.
 * 
 *    Rev 1.21   Jun 07 2002 15:24:08   KOVACSRO
 * BankCharges and EFT Consolidation.
 * 
 *    Rev 1.20   31 May 2002 16:32:56   HERNANDO
 * Added SCR_ACCOUNTREVIEW_ID
 * 
 *    Rev 1.19   May 31 2002 15:39:42   HSUCHIN
 * added pension info
 * 
 *    Rev 1.18   19 Mar 2002 13:44:34   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.17   Mar 18 2002 14:35:22   YINGBAOL
 * add PST Exempty
 * 
 *    Rev 1.16   Feb 26 2002 15:22:08   YINGBAOL
 * add Fee Parameter
 * 
 *    Rev 1.15   Feb 04 2002 15:45:24   JANKAREN
 * Added GSTExempt
 * 
 *    Rev 1.14   20 Nov 2001 11:10:28   HSUCHIN
 * added ProcessKey function to COADlg::COAGrid to handle tab sequence keys.
 * 
 *    Rev 1.13   19 Sep 2001 10:28:18   KOVACSRO
 * Added ESoP.
 * 
 *    Rev 1.12   Aug 23 2001 13:24:46   JANKAREN
 * Added As Pension Plan
 * 
 *    Rev 1.11   18 Aug 2001 11:07:24   HSUCHIN
 * added YTD to Screen selection
 * 
 *    Rev 1.10   05 Jun 2001 16:06:46   YINGZ
 * for others to compile
 * 
 *    Rev 1.9   Jun 04 2001 10:27:54   ZHANGCEL
 * Added SCR_GUARANTEE_ID and SCR_RESP_ID into the "enum COA_ENTRY_ID"
 * 
 *    Rev 1.8   Feb 16 2001 15:27:52   YINGBAOL
 * implement save and load stingery settings and put some hard copy string into DD
 * 
 *    Rev 1.7   Oct 27 2000 17:35:58   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.6   Sep 20 2000 14:24:12   ZHANGCEL
 * Debug
 * 
 *    Rev 1.5   Aug 04 2000 09:45:12   PETOLESC
 * Added FRREB stop field and RRIF screen.
 * 
 *    Rev 1.4   Apr 05 2000 10:50:52   DT24433
 * changed to use hasPermission, removed unused worksession variable
 * 
 *    Rev 1.3   Apr 03 2000 10:11:02   YINGZ
 * code sync
 * 
 *    Rev 1.2   Feb 28 2000 14:51:40   DT24433
 * removed Cancel
 * 
 *    Rev 1.1   Feb 15 2000 18:59:16   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:10   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.16   Feb 09 2000 12:10:22   HUANGSHA
 * Added TransType for invoking the systematic screen
 * 
 *    Rev 1.15   Feb 01 2000 13:06:50   BUZILA
 * some fixes
 * 
 *    Rev 1.14   Jan 24 2000 10:13:50   BUZILA
 * disabling HLLAPI for nasu
 * 
 *    Rev 1.13   Jan 22 2000 15:19:00   BUZILA
 * fixes
 * 
 *    Rev 1.12   Jan 21 2000 17:40:48   BUZILA
 * some fixes
 * 
 *    Rev 1.11   Jan 11 2000 09:08:48   BUZILA
 * changed search algorithm and collapse/expand button
 * 
 *    Rev 1.10   Dec 23 1999 14:14:12   BUZILA
 * added SetCOAField
 * 
 *    Rev 1.9   Dec 22 1999 18:01:50   BUZILA
 * changes due to COA flags movament
 * 
 *    Rev 1.8   Dec 10 1999 18:47:46   BUZILA
 * implemented collapse, search, filtering
 * 
 *    Rev 1.7   Nov 25 1999 15:12:56   BUZILA
 * fixes
 * 
 *    Rev 1.6   Nov 20 1999 19:39:16   BUZILA
 * fixes
 * 
 *    Rev 1.5   Nov 15 1999 14:46:20   BUZILA
 * fix
 * 
 *    Rev 1.4   Aug 12 1999 15:40:46   BUZILA
 * ch
 * 
 *    Rev 1.3.1.0   Aug 12 1999 15:27:34   BUZILA
 * Branch for Increment 2
 * 
 *    Rev 1.3   Jul 28 1999 12:03:40   BUZILA
 * moved gxall.h include at dialog level
 * 
 *    Rev 1.2   Jul 27 1999 16:06:20   BUZILA
 * Increment M2
 * 
 *    Rev 1.1   Jul 08 1999 10:04:48   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

