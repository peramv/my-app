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
// ^FILE   : ComboBase.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 10/7/1998
//
// ----------------------------------------------------------
//
// ^CLASS            : CComboBase
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"
#include "ComboBase.h"
#include <ConfigManager.hpp>
#include <bfproc\GenericInterface.hpp>
#include <bfdata\bffieldid.hpp>
#include <bfdata\bfdata.hpp>


#include <assert.h>

namespace
{
   const I_CHAR *MFDSTC = I_( "MFDSTC" );
   const I_CHAR *MARKET = I_( "Market" );
}

namespace CND
{
}
//******************************************************************************
// Public methods
//******************************************************************************

CComboBase::CComboBase()
: idSubstitute_( BF::NullContainerId )
, _idSubstituteDescription( BFFieldId::getId( I_( "Substitute_Description" ) ) )

{
}

//******************************************************************************

int CComboBase::SetCurSelWithNotify(
                                   int idx )
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

void CComboBase::SetSavedSelection()
{
   SetCurSel( m_iSaveSelection );
}

//******************************************************************************
// Message Handlers
//******************************************************************************

BEGIN_MESSAGE_MAP(CComboBase, CComboBox)
//{{AFX_MSG_MAP(CComboBase)
ON_WM_SETFOCUS()
ON_WM_CHAR()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************

void CComboBase::OnSetFocus(CWnd* pOldWnd) 
{  // Clear out the auto-expand string
   CComboBox::OnSetFocus(pOldWnd);
   m_autoExpand.erase();
   m_iSaveSelection = GetCurSel();
}

//******************************************************************************

void CComboBase::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{  // The auto-expander accumulates characters and tries to match an item
   if( nChar == VK_BACK )
   {
      int newLength = m_autoExpand.length() ? m_autoExpand.length() - 1 : 0;
      m_autoExpand.erase( newLength );
   }
   else
   {
      if( !isalpha( nChar ) && !isdigit( nChar ) && nChar != ' ' )
      {  // ignore non-alpha keys
         return;
      }
      m_autoExpand += toupper( nChar );
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
}

//******************************************************************************

void CComboBase::FillInSubstituteValues( GenericInterface *pGICaller,
                                         const BFContainerId& idSubstitute
                                       )
{
   idSubstitute_ = idSubstitute;
   _pGI=pGICaller;

   DString dstrDesc;
   const DString *pKey = &( pGICaller->getParent()->getFirstListItemKey( pGICaller, idSubstitute ) );
   do
   {
      pGICaller->getParent()->getField( pGICaller, idSubstitute,
                                        _idSubstituteDescription, dstrDesc );
      int iIndex = AddString( dstrDesc.c_str() );
      assert( iIndex != CB_ERR && iIndex != CB_ERRSPACE );
      SetItemData( iIndex, reinterpret_cast< DWORD >( pKey ) );
      pKey = &( pGICaller->getParent()->getNextListItemKey( pGICaller, 
                                                            idSubstitute ) );
   } 
   while( *pKey != NULL_STRING );
}


//******************************************************************************

void CComboBase::SetSelectionByData( const DString &dstrData )
{



   ConfigManager* theMgr = ConfigManager::getManager( I_( "DataBroker" ) );
   Configuration theConfig = theMgr->retrieveConfig( I_( "Market" ) );
   // hey ... this might not work for FAST ... but who cares!!!!!! - Chris Purdye 14Jun2002
   DString market = theConfig.getValueAsString( I_( "Market" ) );

   if( market == I_( "Canada" ) )     // Market3 is Canada
   {
      ResetContent();
      DString dstrDesc;
      bool done=false;
      const DString *pKey = &( _pGI->getParent()->getFirstListItemKey( _pGI, idSubstitute_ ) );
      do
      {
         if( *pKey==dstrData )
         {
            // Temporary to avoid link to mfdstcids - this class should go away anyway
            _pGI->getParent()->getField( _pGI,  idSubstitute_,
                                         _idSubstituteDescription, dstrDesc );
            int iIndex = AddString( dstrDesc.c_str() );
            assert( iIndex != CB_ERR && iIndex != CB_ERRSPACE );
            SetItemData( iIndex, reinterpret_cast< DWORD >( pKey ) );
            SetCurSel(0);
            done = true;
            return;
         }
         pKey = &( _pGI->getParent()->getNextListItemKey( _pGI, idSubstitute_ ) );
      } 
      while( *pKey != NULL_STRING );

      if( done == false )
      {
         int iIndex = AddString( NULL_STRING );
         assert( iIndex != CB_ERR && iIndex != CB_ERRSPACE );
         SetCurSel(0);
         return;
      }
   }
   // end of temp solution, should be removed in c2!

   for( int i = 0; i < GetCount(); ++i )
   {
      const DString & dstrKey = *( reinterpret_cast< DString * >(
                                                                GetItemData( i ) ) );
      if( dstrKey == dstrData )
      {
         SetCurSel( i );
         return;
      }
   }
   SetCurSel( -1 );

}

//******************************************************************************
// Protected methods
//******************************************************************************

bool CComboBase::AutoExpand(
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/uibase/combobase.cpp-arc  $
 * 
 *    Rev 1.9   Jan 06 2003 16:46:22   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 17:42:36   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.7   Sep 10 2002 14:34:26   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.6   Aug 29 2002 12:57:32   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   Jun 14 2002 17:04:26   PURDYECH
 * Use registry for market settings
 * 
 *    Rev 1.4   May 28 2002 12:21:20   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.3   Feb 13 2001 13:53:16   YINGBAOL
 * take out dependence
 * 
 *    Rev 1.2   Feb 12 2001 14:50:22   YINGBAOL
 * retrieve market from databroker instead of registry
 * 
 *    Rev 1.1   Mar 08 2000 13:38:04   DT24433
 * removed dependency on DBR namespace
 * 
 *    Rev 1.0   Feb 15 2000 11:01:38   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Sep 16 1999 15:53:20   YINGZ
 * if the combo is empty, still only one line, for c1
 * 
 *    Rev 1.9   Sep 16 1999 15:31:52   YINGZ
 * change SetSelectionByData so that in c1, only one line in comobo!
 * 
 *    Rev 1.8   Sep 01 1999 11:30:42   YINGBAOL
 * remove assert for select combobox
 * 
 *    Rev 1.7   Aug 20 1999 14:10:24   DT24433
 * changed getFieldFromCurrentListItem to getField
 * 
 *    Rev 1.6   Aug 18 1999 13:53:12   PRAGERYA
 * FillInSubstituteValues modified
 * 
 *    Rev 1.5   Aug 18 1999 13:36:16   YINGBAOL
 * modify for supporting Substitute_code
 * 
 *    Rev 1.4   Aug 18 1999 12:22:46   PRAGERYA
 * Substitute lists in combo boxes
 * 
 *    Rev 1.3   Aug 13 1999 10:24:54   PRAGERYA
 * Adding Increment 2 functionality
 * 
 *    Rev 1.2   Aug 10 1999 17:33:20   PRAGERYA
 * New method added
 * 
 *    Rev 1.1   Jul 08 1999 10:04:50   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
