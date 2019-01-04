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
// ^FILE   : DSTComboBox.cpp
// ^AUTHOR : 
// ^DATE   : 10/11
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : DSTComboBox
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  : 
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"
#include "DSTComboBox.h"

#include "BaseDlg.h"
#include <bfcbo\BFProperties.hpp>
#include <ConfigManager.hpp>
#include <bfdata\bfdatafieldproperties.hpp>
#include <IDIString.hpp>
#include <assert.h>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR *MFDSTC = I_( "MFDSTC" );
   const I_CHAR *MARKET = I_( "Market" );
}

namespace CND
{
}
//******************************************************************************
//              Public Methods
//******************************************************************************

DSTComboBox::DSTComboBox( BaseDlg *rpParent,
                          UINT controlID) :
BaseControl( rpParent, controlID )
{
   SubclassDlgItem( controlID, reinterpret_cast <CWnd *>( rpParent ) );
   assert (((GetFlags () & CTRLFLAG_COMBO_EDIT) && (GetStyle () & CBS_DROPDOWN)) ||
            (GetStyle () & CBS_DROPDOWNLIST));
}

//******************************************************************************

DSTComboBox::~DSTComboBox()
{
   ClearSelections();
}

//******************************************************************************
// repeated item will not be added
void DSTComboBox::FillInListValues ( const BFContainerId& idContainer, 
                                     const BFFieldId &idField)
{
   BaseDlg *pBD=GetParentDlg();

   ResetContent();

   CStringList temp;

   DString str;
   int iIndex;
   const DString *pCurKey = &( pBD->getParent()->getCurrentListItemKey( pBD, idContainer ) );
   const DString *pKey=&(pBD->getParent()->getFirstListItemKey( pBD, idContainer ));

   if( (*pKey)!=NULL_STRING )
   {
      do
      {
         pBD->getParent()->getField( pBD, idContainer, idField, str );
         str.strip();
         if( temp.Find(str.c_str())==NULL )
         {
            temp.AddTail(str.c_str());
            iIndex = AddString(str.c_str());
            SetItemData( iIndex, reinterpret_cast< DWORD >( pKey ) );
         }
      }while( *(pKey=&(pBD->getParent()->getNextListItemKey( pBD, idContainer ))) != NULL_STRING );

      if( (*pCurKey)!=NULL_STRING )
         pBD->getParent()->setCurrentListItem(pBD, idContainer, *pCurKey);
   }
}

//******************************************************************************

void DSTComboBox::FillInSubstituteValues()
{
   DString strIdi;
   DString *strPtr;
   DString strValue;
   BaseDlg *pBD = GetParentDlg();
   const BFProperties *rpProp = GetProperties();

   ResetContent();
   ClearSelections();

   if( !rpProp )
   {  // No properties - try to use datadictionary
      const BFDataFieldProperties* pProps = BFDataFieldProperties::get( GetFieldID() );
      if( NULL != pProps->getSubstitutionSet( ClientLocaleContext::get() ) )
      {
         pProps->getAllSubstituteValues( strIdi, ClientLocaleContext::get(), true );
      }
   }
   else
   {
      rpProp->getSubstituteValues( strIdi );
   }

   I_CHAR *rpStr = const_cast< I_CHAR * >( strIdi.c_str() );

   DString *strTag = NULL;
   int iIndex;

   if( GetFlags() & CTRLFLAG_INITCOMBO_WITH_BLANK )
   {
      strTag = new DString ( NULL_STRING );
      iIndex = AddString( NULL_STRING );
      m_tagVector.push_back( strTag );
      assert( iIndex != CB_ERR && iIndex != CB_ERRSPACE );
      strPtr = m_tagVector[m_tagVector.size() - 1];
      SetItemData( iIndex, reinterpret_cast< DWORD >( strPtr ) );
   }

   while( *rpStr != '\0' )
   {
      strTag = new DString;
      rpStr = parseIdiString( rpStr, *strTag, strValue );
      if( *strTag != NULL_STRING )
      {
         if( GetFlags() & CTRLFLAG_INITCOMBO_BY_SUB_LIST_CODE )
            strValue = *strTag;

         iIndex = AddString( strValue.c_str() );
         m_tagVector.push_back( strTag );
         assert( iIndex != CB_ERR && iIndex != CB_ERRSPACE );
         strPtr = m_tagVector[m_tagVector.size() - 1];
         SetItemData( iIndex,
                      reinterpret_cast< DWORD >( strPtr ) );
      }
   }
}

//******************************************************************************
void DSTComboBox::FillInSubstituteValues ( const BFContainerId& idSubstitute, 
                                           const BFFieldId &idSubstituteItem )
{
   idSubstitute_ = idSubstitute;
   BaseDlg *pBD=GetParentDlg();

   ResetContent();

   DString dstrDesc;

   const DString *pKey = &( pBD->getParent()->getFirstListItemKey( pBD, idSubstitute ) );
   if( (*pKey)!=NULL_STRING )
   {
      do
      {
         pBD->getParent()->getField( pBD,  idSubstitute, idSubstituteItem, dstrDesc );
         int iIndex = AddString( dstrDesc.c_str() );
         assert( iIndex != CB_ERR && iIndex != CB_ERRSPACE );
         SetItemData( iIndex, reinterpret_cast< DWORD >( pKey ) );
         pKey = &( pBD->getParent()->getNextListItemKey( pBD, idSubstitute ) );
      } 
      while( *pKey != NULL_STRING );
   }
}


//******************************************************************************
// key is stored in item data to help get the field out
void DSTComboBox::FillInTwoListValues( const BFContainerId& idContainer, 
                                       const BFFieldId &idField1, 
                                       const BFFieldId &idField2, 
                                       const DString& Separator, 
                                       const DString& ExtraLine)
{
   BaseDlg *pBD=GetParentDlg();

   ResetContent();

   DString str1, str2;
   int iIndex;

   if( ExtraLine != NULL_STRING )
   {
      iIndex = AddString( ExtraLine.c_str() );
      SetItemData( iIndex, -1 );
   }

   const DString *pCurKey = &( pBD->getParent()->getCurrentListItemKey( pBD, idContainer ) );
   const DString *pKey=&(pBD->getParent()->getFirstListItemKey( pBD, idContainer ));

   if( (*pKey)!=NULL_STRING )
   {
      do
      {
         pBD->getParent()->getField( pBD, idContainer, idField1, str1 );
         str1.strip();
         pBD->getParent()->getField( pBD, idContainer, idField2, str2 );
         str2.strip();

         str1+=Separator+str2;
         iIndex = AddString(str1.c_str());
         SetItemData( iIndex, reinterpret_cast< DWORD >( pKey ) );
      }while( *(pKey=&(pBD->getParent()->getNextListItemKey( pBD, idContainer ))) != NULL_STRING );

      if( (*pCurKey)!=NULL_STRING )
         pBD->getParent()->setCurrentListItem(pBD, idContainer, *pCurKey);
   }
}

//******************************************************************************
int DSTComboBox::SetCurSelWithNotify (int idx)
{  // Set selection and notify parent
   int rtn = SetCurSel( idx );
   // We want our owner to be notified that our content has changed. Since
   // we are limit to list (user can't type free-form text), selecting a
   // code is like using the arrow key so we send a CBN_SELCHANGE.
   ::SendMessage( ::GetParent( m_hWnd ), WM_COMMAND,
                  MAKELONG( ::GetWindowLong( m_hWnd, GWL_ID ), CBN_SELCHANGE ),
                  ( LPARAM ) m_hWnd );

   return(rtn);
}

//******************************************************************************
void DSTComboBox::SetSavedSelection()
{
   SetCurSel (m_iSaveSelection);
}

//******************************************************************************
void DSTComboBox::SetSelectionByData (const DString &dstrData)
{
   // we need a case in sensitive compare here since progress is not case sensitive 
   DString tmp;
   for( int i = 0; i < GetCount(); ++i )
   {
      tmp = *(reinterpret_cast< DString * >( GetItemData( i ) ) );
      tmp.strip();

      if( tmp.stricmp(dstrData) == 0 )
      {
         SetCurSel( i );
         return;
      }
   } 
   SetCurSel( -1 );
}

//******************************************************************************
//              Message Handlers
//******************************************************************************

BEGIN_MESSAGE_MAP(DSTComboBox, CComboBox)
//{{AFX_MSG_MAP(DSTComboBox)
ON_WM_MOUSEMOVE()
ON_WM_CHAR()
ON_CONTROL_REFLECT_EX(CBN_KILLFOCUS, OnKillfocus)
ON_CONTROL_REFLECT_EX(CBN_SETFOCUS, OnSetfocus)
ON_CONTROL_REFLECT(CBN_SELENDOK, OnSelendok)
//}}AFX_MSG_MAP
ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

//******************************************************************************

void DSTComboBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{  // The auto-expander accumulates characters and tries to match an item
   if( nChar == VK_BACK )
   {
      int newLength = m_autoExpand.length() ? m_autoExpand.length() - 1 : 0;
      m_autoExpand.erase( newLength );
   }
   else
   {
      /**
      if ( !isalpha( nChar ) && !isdigit( nChar ) && nChar != ' ' )
      {  // ignore non-alpha keys
         return;
      }
      m_autoExpand += toupper( nChar );
      */
      if( _istcntrl(nChar) )
         return;
      m_autoExpand += nChar;
      m_autoExpand.upperCase();
   }

   if( m_autoExpand.length() )
   {
      if( !AutoExpand( m_autoExpand ) && !AllowExtension( m_autoExpand ) )
      {  // Couldn't find a match on this one, back up
         MessageBeep( 0xffffffff );
         m_autoExpand.erase( m_autoExpand.length() - 1 );
      }
   }
   else
   {  // If the auto-expand string is empty, select the initial selection
      SetSavedSelection();
   }

//	CComboBox::OnChar(nChar, nRepCnt, nFlags);
}

//******************************************************************************

BOOL DSTComboBox::OnKillfocus() 
{
   // Clear autoexpand for next round
   m_autoExpand = NULL_STRING;
   DoKillFocus();
   
   if ((GetFlags() & CTRLFLAG_COMBO_EDIT) && IsUpdateable() && !GetParentDlg()->IsCancelInProgress())
   {
      CString cstr;
      DString selection;
      int i = GetCurSel();
      
      if (i != CB_ERR)
      {
         selection = *(reinterpret_cast <DString *>(GetItemData (i )));
      }
      else
      {
         GetWindowText (cstr);
         selection = LPCTSTR (cstr);
      }
      FillInSubstituteValues ();
      SetSelectionByData (selection);
   }
   return (FALSE);
}

//******************************************************************************

LRESULT DSTComboBox::OnMouseLeave(WPARAM , LPARAM )
{
   MouseLeave();

   return(0);
}

//******************************************************************************

void DSTComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
   if( IsError() /*&& !IsToolTipVisible()*/ )
   {
      TriggerToolTip(); 
   }

   CComboBox::OnMouseMove(nFlags, point);
}

//******************************************************************************

void DSTComboBox::OnSelendok() 
{
   DoChangeUpdate();
}

//******************************************************************************

BOOL DSTComboBox::OnSetfocus() 
{
   DoSetFocus();

   return(FALSE);
}

//******************************************************************************

BOOL DSTComboBox::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message==WM_KEYDOWN && (int)(pMsg->wParam)==VK_F11 )
   {
      ToggleToolTip();
   }

   return(CComboBox::PreTranslateMessage(pMsg));
}

//******************************************************************************
// Protected methods
//******************************************************************************

bool DSTComboBox::AutoExpand(
                            const DString &result)
{
   // Try to select from list
   int idx = FindString( -1, result.c_str() );
   if( CB_ERR != idx )
   {
      SetCurSelWithNotify( idx );
      return(true);
   }

   return(false);
}

//******************************************************************************

void DSTComboBox::DoClear()
{
   SetCurSel(-1);
}

//******************************************************************************

void DSTComboBox::DoGetText( DString &strValueOut,
                             int index) const
{
   CString cstr;
   int i = GetCurSel();
   if (GetFlags() & ( CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_INITCOMBO_BY_SUB_LIST_CODE | CTRLFLAG_COMBO_EDIT) )
   {
      if( i != CB_ERR )
      {
         strValueOut = *( reinterpret_cast< DString * >( GetItemData( i ) ) );
      }
      else if (GetFlags() & CTRLFLAG_COMBO_EDIT)
      {
         GetWindowText( cstr );
         strValueOut = LPCTSTR( cstr );
      }
   }
   else
   {
      if (i != CB_ERR)
      {
         GetLBText (i, cstr);
         strValueOut = LPCTSTR (cstr);
      }
      else if (GetFlags() & CTRLFLAG_COMBO_EDIT)
      {
         GetWindowText (cstr);
         strValueOut = LPCTSTR (cstr);
      }
   }
}

//******************************************************************************

void DSTComboBox::DoInit()
{
   if( IsUpdateable() )
   {  // Only load lists if updateable
      if( GetFlags() & ( CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_INITCOMBO_BY_SUB_LIST_CODE ) )
      {
         FillInSubstituteValues();
         SetLoadDisplayFormat( false );
      }
   }

   CEdit* pComboEdit = (CEdit*) CWnd::GetWindow (GW_CHILD);
   if (pComboEdit)
   {
      pComboEdit->SetReadOnly (!IsUpdateable ());
   }
}
//******************************************************************************
bool DSTComboBox::doSetCtrlReadOnly (bool bReadOnly)
{
   CEdit* pComboEdit = (CEdit*) CWnd::GetWindow (GW_CHILD);
   if (pComboEdit)
   {
      pComboEdit->SetReadOnly (!IsUpdateable ());
   }

   return false; //not done yet
}

//******************************************************************************
// if use combo to populate, scroll according to code
// otherwise, use display text
bool DSTComboBox::DoSetText(
                           const DString &strValueIn,
                           int index
                           )
{
   if( GetFlags() & ( CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_INITCOMBO_BY_SUB_LIST_CODE ) )
   {
      if( IsUpdateable() )
      {
         SetSelectionByData( strValueIn );
      }
      else
      {  // Need to reset and load
         ResetContent();
         ClearSelections();
         if( strValueIn != NULL_STRING )
         {  // Only bother if there is a value
            DString *strTag = new DString( strValueIn );
            DString *strPtr;
            DString strDesc(strValueIn);

            BaseDlg *pBD = GetParentDlg();
/*
           DataElementProperties *dp = const_cast < DataElementProperties * >
               ( pBD->getFieldAttributes( pBD, GetFieldID() ) );

            strDesc = dp->getSubstituteValue( *strTag ); 
        */
            BFProperties* pBFProperty = const_cast < BFProperties * >( GetProperties() );
            if( pBFProperty )
               pBFProperty->formatValue( GetFieldID(), strDesc, 
                                         ( GetFlags() & CTRLFLAG_INITCOMBO_BY_SUB_LIST ) == CTRLFLAG_INITCOMBO_BY_SUB_LIST );


            int iIndex = AddString( strDesc.c_str() );
            m_tagVector.push_back( strTag );
            assert( iIndex != CB_ERR && iIndex != CB_ERRSPACE );
            strPtr = m_tagVector[m_tagVector.size() - 1];
            SetItemData( iIndex,
                         reinterpret_cast< DWORD >( strPtr ) );
            SetCurSel( iIndex );
         }
      }
   }
   else
   {
      if( strValueIn == NULL_STRING )
      {
         if( !IsUpdateable() )
            ResetContent();
         SetCurSel( -1 );
      }
      else
      {
         int nResult = SelectString( -1, strValueIn.c_str() );
         if( !IsUpdateable() )
         {
            DWORD dwTemp = NULL;
            if( nResult != CB_ERR )
               dwTemp = GetItemData(nResult);
            ResetContent();
            if( nResult != CB_ERR )//add the value
            {
               DString *strTag = new DString( strValueIn );

               int iIndex = AddString( strValueIn.c_str() );
               assert( iIndex != CB_ERR && iIndex != CB_ERRSPACE );
               SetItemData( iIndex, dwTemp );
               SetCurSel( iIndex );
            }
         }
      }
   }
   return(true);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

void DSTComboBox::ClearSelections()
{
   int count = m_tagVector.size();

   for( int i = 0; i < count; i++ )
   {
      delete m_tagVector[i];
   }
   m_tagVector.clear();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTComboBox.cpp-arc  $
//
//   Rev 1.25   Jul 05 2010 02:15:36   dchatcha
//IN# 1984105 - Settlement from Broker trade will bring out shareholder default bank.
//
//   Rev 1.24   Jun 30 2010 03:29:20   kitticha
//IN#2045000 - Fixed the issue about OnKillFocus.
//
//   Rev 1.23   23 Jun 2009 00:28:54   popescu
//Fixed read only issues for the new style of combo box - when applying permission
//
//   Rev 1.22   13 May 2009 14:53:28   popescu
//Fixed read only issues for the new style of combo box
//
//   Rev 1.21   05 May 2009 10:27:50   popescu
//Removed an unecessary test
//
//   Rev 1.20   05 May 2009 10:08:18   popescu
//Added support for drop down comboxes. The value typed in is appended to the subst set.
//
//   Rev 1.19   Sep 27 2004 09:32:04   FENGYONG
//PTS10024458 - do not check visible before show error message
 * 
 *    Rev 1.18   Jan 06 2003 16:46:36   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.17   Oct 09 2002 17:42:42   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.16   Sep 10 2002 14:34:32   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.15   Aug 29 2002 12:57:32   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   Aug 02 2002 13:26:02   YINGBAOL
 * fix NULL pointer for Property
 * 
 *    Rev 1.13   Jul 05 2002 10:45:08   PURDYECH
 * Include file cleanup.
 * 
 *    Rev 1.12   22 May 2002 19:17:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   01 Apr 2002 16:21:44   HSUCHIN
 * FillInSubstitueValues now check for the CTRLFLAG_INITCOMBO_WITH_BLANK flag before inserting a blank into the combo box.
 * 
 *    Rev 1.10   Feb 25 2002 18:58:06   PURDYECH
 * Removed annoying compiler warnings.
 * 
 *    Rev 1.9   Jun 26 2001 17:36:30   HUANGSHA
 * fix the problem with the words search
 * 
 *    Rev 1.8   06 Jun 2001 17:03:06   YINGZ
 * support CTRLFLAG_INITCOMBO_BY_SUB_LIST_CODE
 * 
 *    Rev 1.7   Jun 06 2001 16:36:04   YINGBAOL
 * use BFProperties instead of infra
 * 
 *    Rev 1.6   04 May 2001 15:36:34   KOVACSRO
 * Keeping the item data when making the control read-only.
 * 
 *    Rev 1.5   04 May 2001 10:43:24   KOVACSRO
 * to be consistent with read only combo boxes.
 * 
 *    Rev 1.4   Feb 13 2001 13:53:28   YINGBAOL
 * take out dependence
 * 
 *    Rev 1.3   Feb 12 2001 14:50:24   YINGBAOL
 * retrieve market from databroker instead of registry
 * 
 *    Rev 1.2   Jun 13 2000 17:58:10   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.1   Mar 07 2000 10:27:44   ZHANGCEL
 * Commented the code that is for the pecifical use  for Increment C1
 * 
 *    Rev 1.0   Feb 15 2000 11:01:38   SMITHDAV
 * Initial revision.
// 
//    Rev 1.30   Jan 22 2000 14:53:16   YINGZ
// pass OnSetfocus to dlg
// 
//    Rev 1.29   Jan 19 2000 11:26:22   DT24433
// clear autoexpand string during killFocus so 1 char recognition works better
// 
//    Rev 1.28   Jan 18 2000 09:46:52   YINGZ
// using stricmp in SetSelectionByData for case insensitive comparison
// 
//    Rev 1.27   Jan 14 2000 16:10:56   YINGZ
// change sub list order to use data dictionary order
// 
//    Rev 1.26   Jan 10 2000 17:58:32   DT24433
// added read-only code for combos based on subst. lists
// 
//    Rev 1.25   Jan 03 2000 12:39:32   DT24433
// get substitutes from dictionary when don't have properties
// 
//    Rev 1.24   Dec 31 1999 12:59:42   DT24433
// change call for substitutes
// 
//    Rev 1.23   Dec 29 1999 12:21:14   DT24433
// get values from bfproperties
// 
//    Rev 1.22   Dec 23 1999 13:20:54   DT24433
// none
// 
//    Rev 1.21   Dec 21 1999 14:38:02   YINGZ
// change OnKillfocus, give dlg a chance to get the notification
// 
//    Rev 1.20   Dec 13 1999 11:13:28   YINGZ
// ?
// 
//    Rev 1.19   Dec 13 1999 11:00:32   YINGZ
// fix DoGetText
// 
//    Rev 1.18   Nov 26 1999 15:45:04   YINGZ
// take care of empty string in do settext
// 
//    Rev 1.17   Nov 15 1999 14:04:14   DT24433
// removed flag parm in constructor
// 
//    Rev 1.16   Nov 13 1999 16:16:40   YINGZ
// bug fixing
// 
//    Rev 1.15   Nov 13 1999 11:24:32   YINGZ
// fix key bug
// 
//    Rev 1.14   Nov 12 1999 17:11:46   YINGZ
// add onselchangeok
// 
//    Rev 1.13   Nov 12 1999 14:39:56   YINGZ
// add new functions
// 
//    Rev 1.12   Nov 05 1999 15:04:50   YINGZ
// set load format
// 
//    Rev 1.11   Nov 05 1999 12:43:36   YINGZ
// if combo use sub list, DoGetText return code
// 
//    Rev 1.10   Nov 05 1999 11:24:28   YINGZ
// just check in so it can be used
// 
//    Rev 1.9   Nov 02 1999 17:26:26   YINGZ
// add index
// 
//    Rev 1.8   Oct 28 1999 09:35:20   YINGZ
// for a clean Get from PVCS!
// 
//    Rev 1.7   Oct 22 1999 16:50:54   YINGZ
// other guy want to use it now
// 
//    Rev 1.6   Oct 19 1999 09:29:08   YINGZ
// set/kill focus
// 
//    Rev 1.5   Oct 18 1999 16:19:10   YINGZ
// modify OnMouseMove
// 
//    Rev 1.4   Oct 14 1999 15:56:42   DT24433
// use interface methods for working with tooltip display
// 
//    Rev 1.3   Oct 14 1999 15:37:20   YINGZ
// add tooltip support and move combobase function here
// 
//    Rev 1.2   Oct 14 1999 10:01:46   DT24433
// added new methods
// 
//    Rev 1.1   Oct 11 1999 17:50:42   DT24433
// added header/trailer junk
 * 
*/ 
