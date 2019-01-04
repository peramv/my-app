
#ifndef BASEMAINDLG_H
#define BASEMAINDLG_H 
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
// ^METHOD      : DlgDoHllapi
//
// ^DESCRIPTION : Start HLLAPI session, moving over fund and account from this
//                object.
//
// ^PARAMETERS  : 
//    ^^ const I_CHAR *type - type of HLLAPI to perform ("MAINT", "LOOKUPLE", ...)
//    ^^ bool awdFlag     - whether to invoke create AWD work dialog,
//                          default = false
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
//******************************************************************************

#ifndef ABSTRACTBASEMAINDLG_H
   #include <uibase\AbstractBaseMainDlg.h>
#endif

// Forward declares
class WindowFactory;

/**
 * This is the abstract base class for all main modal/modeless dialogs.
 *
 * This class provides support for using a dialog as either modal or modeless
 * along with various other features.  BaseMainDlg tries to add this support so
 * that the derived dialog usually does not have to concern itself with whether
 * it is running in a modal or modeless state.
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 12/10/98</dd></dl>
 * @version 0.1
 */
class BaseMainDlg : public AbstractBaseMainDlg
{
// Construction
public:
   BaseMainDlg ( UINT IDD, 
                 CWnd* pParent, 
                 GenericInterfaceContainer* pGIC, 
                 GenericInterface* pGIParent, 
                 const Command& rCommand, 
                 const DString &dialogName);
   virtual ~BaseMainDlg();
   friend WindowFactory;

   /**
     * Method to return the display label for Account Number in caption.
     */
   virtual CString GetCaptionAcctNumTxt();
   /**
     * Get the base caption for the dialog.
     */
   /**
     * Method to return the display label for Fund in caption.
     */
   virtual CString GetCaptionFundTxt();
   /**
     * Method to return the display label for Share Number in caption.
     */
   virtual CString GetCaptionShareNumTxt();

// TODO - these need to be removed
   void DDX_CBIndex(CDataExchange* pDX, int nIDC, int& index);
   void DDX_CBString(CDataExchange* pDX, int nIDC, CString& value);
   void DDX_CBStringExact(CDataExchange* pDX, int nIDC, CString& value);
   void DDX_Check(CDataExchange* pDX, int nIDC, int& value);
   void DDX_Control(CDataExchange* pDX, int nIDC, CWnd& rControl);
   void DDX_DateTimeCtrl(CDataExchange* pDX, int nIDC, CTime& value);
   void DDX_DateTimeCtrl(CDataExchange* pDX, int nIDC, COleDateTime& value);
   void DDX_LBIndex(CDataExchange* pDX, int nIDC, int& index);
   void DDX_LBString(CDataExchange* pDX, int nIDC, CString& value);
   void DDX_LBStringExact(CDataExchange* pDX, int nIDC, CString& value);
   void DDX_MonthCalCtrl(CDataExchange* pDX, int nIDC, CTime& value);
   void DDX_MonthCalCtrl(CDataExchange* pDX, int nIDC, COleDateTime& value);
   void DDX_OCBool(CDataExchange* pDX, int nIDC, DISPID& dispid, BOOL& value);
   void DDX_OCBoolRO(CDataExchange* pDX, int nIDC, DISPID& dispid, BOOL& value);
   void DDX_OCColor(CDataExchange* pDX, int nIDC, DISPID& dispid, OLE_COLOR& value);
   void DDX_OCColorRO(CDataExchange* pDX, int nIDC, DISPID& dispid, OLE_COLOR& value);
   void DDX_OCFloat(CDataExchange* pDX, int nIDC, DISPID& dispid, float& value);
   void DDX_OCFloat(CDataExchange* pDX, int nIDC, DISPID& dispid, double& value);
   void DDX_OCFloatRO(CDataExchange* pDX, int nIDC, DISPID& dispid, float& value);
   void DDX_OCFloatRO(CDataExchange* pDX, int nIDC, DISPID& dispid, double& value);
   void DDX_OCInt( CDataExchange* pDX, int nIDC, DISPID dispid, int& value );
   void DDX_OCInt( CDataExchange* pDX, int nIDC, DISPID dispid, long& value );
   void DDX_OCIntRO( CDataExchange* pDX, int nIDC, DISPID dispid, int& value );
   void DDX_OCIntRO( CDataExchange* pDX, int nIDC, DISPID dispid, long& value );
   void DDX_OCShort( CDataExchange* pDX, int nIDC, DISPID dispid, short& value );
   void DDX_OCShortRO( CDataExchange* pDX, int nIDC, DISPID dispid, short& value );
   void DDX_OCText( CDataExchange* pDX, int nIDC, DISPID dispid, CString& value ); 
   void DDX_OCTextRO( CDataExchange* pDX, int nIDC, DISPID dispid, CString& value );
   void DDX_Radio( CDataExchange* pDX, int nIDC, int& value );
   void DDX_Scroll( CDataExchange* pDX, int nIDC, int& value );
   void DDX_Slider( CDataExchange* pDX, int nIDC, int& value );
   void DDX_Text( CDataExchange* pDX, int nIDC, BYTE& value );
   void DDX_Text( CDataExchange* pDX, int nIDC, short& value );
   void DDX_Text( CDataExchange* pDX, int nIDC, int& value );
   void DDX_Text( CDataExchange* pDX, int nIDC, UINT& value );
   void DDX_Text( CDataExchange* pDX, int nIDC, long& value );
   void DDX_Text( CDataExchange* pDX, int nIDC, DWORD& value );
   void DDX_Text( CDataExchange* pDX, int nIDC, CString& value );
   void DDX_Text( CDataExchange* pDX, int nIDC, float& value );
   void DDX_Text( CDataExchange* pDX, int nIDC, double& value );
   void DDX_Text( CDataExchange* pDX, int nIDC, COleCurrency& value );
   void DDX_Text( CDataExchange* pDX, int nIDC, COleDateTime& value );
   void DDV_MaxChars( CDataExchange* pDX, CString const& value, int nChars );
   void DDV_MinMaxByte( CDataExchange* pDX, BYTE value, BYTE minVal, BYTE maxVal );
   void DDV_MinMaxDateTime( CDataExchange* pDX, CTime& refValue, const CTime* refMinRange, const CTime* refMaxRange );
   void DDV_MinMaxDateTime( CDataExchange* pDX, COleDateTime& refValue, const COleDateTime* refMinRange, const COleDateTime* refMaxRange );
   void DDV_MinMaxDouble( CDataExchange* pDX, double const& value, double minVal, double maxVal );
   void DDV_MinMaxDWord( CDataExchange* pDX, DWORD const& value, DWORD minVal, DWORD maxVal );
   void DDV_MinMaxFloat( CDataExchange* pDX, float value, float minVal, float maxVal );
   void DDV_MinMaxInt( CDataExchange* pDX, int value, int minVal, int maxVal );
   void DDV_MinMaxLong( CDataExchange* pDX, long value, long minVal, long maxVal );
   void DDV_MinMaxMonth( CDataExchange* pDX, CTime& refValue, const CTime* refMinRange, const CTime* refMaxRange );
   void DDV_MinMaxMonth( CDataExchange* pDX, COleDateTime& refValue, const COleDateTime* refMinRange, const COleDateTime* refMaxRange );
   void DDV_MinMaxSlider( CDataExchange* pDX, DWORD value, DWORD minVal, DWORD maxVal );
//   void DDV_MinMaxUnsigned( CDataExchange* pDX, unsigned value, unsigned minVal, unsigned maxVal );

   /**
    * Expose the GenericInterface::invokeCommand method at a public level.
    * 
    * @param rpGIParent
    * @param szCommand
    * @param type
    * @param bModal
    * @param rpModelessOut
    * 
    * @return 
    */
   E_COMMANDRETURN indirectInvokeCommand( GenericInterface *rpGIParent,
                                          const I_CHAR *szCommand,
                                          E_PROCESSTYPE type,
                                          bool bModal,
                                          GenericInterface **rpModelessOut )
   {
      return( invokeCommand( rpGIParent, szCommand, type, bModal, rpModelessOut ) );
   }

protected:
   static CRect DetailDlgRect;
   // Generated message map functions
   //{{AFX_MSG(BaseMainDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()

   /**
     * This method will get data for parms and invoke the Admin dates process.
     * The caller is responsible for setting the correct current item if the 
     * container passed in is a list container.  Also, all 4 fields for parms
     * must exist in the container (and have the same names).  See code for
     * details.
     * @param idContainer - container to get data for parms from.
     */
   void ShowAdminDates(
                      const BFContainerId& idContainer
                      );

   virtual bool canCancel();

/**
 *	 This method sets paramters to CsiComponent
 *	 @param strName - Name of the parameter
 *  @param sreValue - Value of the parameter
 *  @return - void
 */
   void setCsiParameter(const DStringA& strName, const DStringA& strValue); 

/**
 * This method execute a CsiProcess
 * @param strProcessName - the name of process to be executed
 * returns - void 
 */
   void executeCsiProcess(const DStringA& strProcessName );

private:
};

#endif  // BASEMAINDLG_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BaseMainDlg.h-arc  $
 * 
 *    Rev 1.11   Sep 30 2005 10:31:26   popescu
 * Incident# 403519 - aligned all dialogs to pass in the CLASSNAME in the constructor
 * 
 *    Rev 1.10   Sep 15 2005 12:57:52   popescu
 * Incident # 403519 - saved/restored the size of the dialog in the registry
 * 
 *    Rev 1.9   Mar 21 2003 18:33:32   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Mar 05 2003 11:26:28   PURDYECH
 * Added indirectInvokeCommand method.  This method allows outside callers to use the protected invokeCommand method.
 * 
 *    Rev 1.7   Oct 09 2002 23:55:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   19 Mar 2002 13:44:30   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.5   Jan 28 2002 11:27:24   YINGBAOL
 * HLLAPI Change
 * 
 *    Rev 1.4   29 Jun 2001 10:57:08   YINGZ
 * add canCancel to support cancel machenism
 * 
 *    Rev 1.3   Mar 02 2000 11:15:00   DT24433
 * changes for new base class
 * 
 *    Rev 1.2   Feb 28 2000 16:54:14   DT24433
 * removed Ok/Cancel
 * 
 *    Rev 1.1   Feb 15 2000 18:59:12   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:08   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.14   Jan 26 2000 19:40:06   DT24433
 * added transaction error flag and send method
 * 
 *    Rev 1.13   Dec 09 1999 19:21:14   DT24433
 * added ShowAdminDates
 * 
 *    Rev 1.12   Dec 06 1999 16:54:34   YINGZ
 * add SetShrAcctCaption for new style caption
 * 
 *    Rev 1.11   Nov 04 1999 13:37:58   DT24433
 * added OnOk/OnCancel processing
 * 
 *    Rev 1.10   Aug 25 1999 14:22:48   HSUCHIN
 * Override DDX and DDV calls from Dialog classes.  The DDX, DDV functions now checks to see if the control exist before performing the data exchange.
 * 
 *    Rev 1.9   Aug 24 1999 14:56:26   DT24433
 * misc. cleanup
 * 
 *    Rev 1.8   Aug 13 1999 17:27:24   YINGZ
 * change the way the name is displayed
 * 
 *    Rev 1.7   Aug 04 1999 11:23:40   PRAGERYA
 * Date fix
 * 
 *    Rev 1.6   Aug 04 1999 11:17:46   PRAGERYA
 * Fixing date
 * 
 *    Rev 1.5   Aug 03 1999 17:09:40   BUZILA
 * added savePosition and loadPosition methods
 * 
 *    Rev 1.4   Jul 28 1999 10:41:58   YINGZ
 * allow cascade for all dlg
 * 
 *    Rev 1.3   Jul 09 1999 16:55:52   YINGZ
 * change listview support to use Jerry's fix
 * 
 *    Rev 1.2   Jul 09 1999 16:48:44   YINGZ
 * change listview support to use Jerry's fix
 * 
 *    Rev 1.1   Jul 08 1999 10:04:42   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
