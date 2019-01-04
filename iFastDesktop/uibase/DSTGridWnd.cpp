// DSTGridWnd.cpp : implementation file
//
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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DSTGridWnd.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/03/2000
//
// ^CLASS    : DSTGridWnd
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#define WIN32UIBASE_DLL

#include "stdafx.h"
#include "WRAgentSvc.h"
#include "DSTGridWnd.h"

#include "BaseDlg.h"
#include <bfcbo\BFProperties.hpp>
#include <bfproc\AbstractProcess.hpp>
#include <bfdata\bfdatafieldproperties.hpp>
#include <bfdata\bffieldid.hpp>
#include "dstoledatetime.h"
#include <configmanager.hpp>
#include <vector>
#include <algorithm>

const DString DSTGridWnd::s_empty_( I_( "" ) );

struct SubstitutionCodeDesc
{
   DString strCode;
   DString strDesc;
};

typedef std::vector<SubstitutionCodeDesc> vSubstitutionCodeDesc;

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR *CLASSNAME          = I_( "DSTGridWnd" );
   const I_CHAR *WORKSTATION        = I_( "WORKSTATION" );
   const I_CHAR *DEFAULTWORKSTATION = I_("DefaultWorkstation");
   const I_CHAR *GR                 = I_( "GR_" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

const int m_TimerEvent = 1234;
const int m_TimerLength = 400;

//*********************************************************************************
bool DSTGridWnd::codeAscending(const SubstitutionCodeDesc& input1, 
                               const SubstitutionCodeDesc& input2)
{
   DString strCode1 = input1.strCode;
   DString strCode2 = input2.strCode;
   int result = strCode1.compare(strCode2);

   if(result == 0) 
      return strCode1.size() < strCode2.size();
   else 
      return (result < 0);
}

//*********************************************************************************
bool DSTGridWnd::codeDescending(const SubstitutionCodeDesc& input1, 
                                const SubstitutionCodeDesc& input2)
{
   DString strCode1 = input1.strCode;
   DString strCode2 = input2.strCode;
   int result = strCode1.compare(strCode2);

   if(result == 0) 
      return strCode1.size() > strCode2.size();
   else 
      return (result > 0);
}

//*********************************************************************************
bool DSTGridWnd::descAscending(const SubstitutionCodeDesc& input1, 
                               const SubstitutionCodeDesc& input2)
{
   DString strDesc1 = input1.strDesc;
   DString strDesc2 = input2.strDesc;
   int result = strDesc1.compare(strDesc2);

   if(result == 0) 
      return strDesc1.size() < strDesc2.size();
   else 
      return (result < 0);
}

//*********************************************************************************
bool DSTGridWnd::descDescending(const SubstitutionCodeDesc& input1, 
                                const SubstitutionCodeDesc& input2)
{
   DString strDesc1 = input1.strDesc;
   DString strDesc2 = input2.strDesc;
   int result = strDesc1.compare(strDesc2);

   if(result == 0) 
      return strDesc1.size() > strDesc2.size();
   else 
      return (result > 0);
}

//*********************************************************************************
DSTComboProperties::DSTComboProperties()
: idSubstitution( ifds::NullFieldId )
, comboList(NULL_STRING)
, nInitMode(DSTGridWnd::USE_SUBSTITUTION_LIST)
{
}

//*********************************************************************************
DSTCellProperties::DSTCellProperties( DSTGridWnd * pParentGrid, ROWCOL nRow, ROWCOL nCol ) :
m_nRow ( nRow ),
m_nCol ( nCol ),
m_pParentGrid( pParentGrid ),
nAlignment ( DT_LEFT ),
cellCtrlType ( GX_IDS_CTRL_EDIT ),
nIconId ( -1 ),
idField ( ifds::NullFieldId ),
listItemKey( NULL_STRING ),
controlId( 0 ),
nCellState ( DSTGridWnd::USE_FIELD_PROPERTY ),
m_bRegistered( false ),
m_mask( NULL_STRING ),
m_sev(NO_SEVERITY)   ,
m_dstrAllowedChar( NULL_STRING ) //Default allows all characters,
{
}

//*********************************************************************************
void DSTCellProperties::onNotify( E_EVENT_GROUP eEventCateg, E_EVENT eEventId, const DString &hint )
{
   m_pParentGrid->SetCurrCellProp( m_nRow, m_nCol, this );
};

//*********************************************************************************
DSTCellProperties::~DSTCellProperties( )
{
};

//*********************************************************************************
DSTHeaderProperties::DSTHeaderProperties():
nWidth( 100 ),
nAlignment( DT_LEFT )
{};


// CNumericEditControl control

GRID_IMPLEMENT_CONTROL(CNumericEditControl, CGXEditControl)

CNumericEditControl::CNumericEditControl(CGXGridCore* pGrid, UINT nID) : CGXEditControl(pGrid, nID) 
{
}

BEGIN_MESSAGE_MAP(CNumericEditControl, CGXEditControl) 
//{{AFX_MSG_MAP(CNumericEditControl)
//}}AFX_MSG_MAP 
END_MESSAGE_MAP()
// GetControlText
//
// Convert the value which is stored in the style object into
// the text which should be displayed in the cell.
//
/*
BOOL CNumericEditControl::GetControlText( CString& sResult, 
                                          ROWCOL nRow, 
                                          ROWCOL nCol, 
                                          LPCTSTR pszRawValue, 
                                          const CGXStyle& style)
{
 // base class version will store current text in sResult
   if (!CGXEditControl::GetControlText(sResult, nRow, nCol, pszRawValue, style)) 
      return FALSE; 
    if (!sResult.IsEmpty())
   { 
      // gather information
   // ... value
   double d = atof(style.GetValueRef());

   // ... format
   CString sFormat;
   style.GetUserAttribute(IDS_UA_NUMEDITFORMAT, sFormat);

   // Now, format the text
   _stprintf(sResult.GetBuffer(128), sFormat, d);
   sResult.ReleaseBuffer();
   }
   return TRUE;
}
*/

BOOL CNumericEditControl::ValidateString(const CString& sEdit)
{
   DString dstLocaleStr = ClientLocaleContext::get().getLocale();

// cycle through string and check each character if it is a digit
   for (int n = 0; n < sEdit.GetLength(); n++)
   {
      if( dstLocaleStr == I_("deDE") )
      {
         if (!isdigit(sEdit[n]) && sEdit[n] != ',') 
            return FALSE; 
      }
      else
      {
         if (!isdigit(sEdit[n]) && sEdit[n] != '.') 
            return FALSE; 
      }
   }
   return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
//CAlphaNumericEditControl control
//Implements the control 
//Excludes all characters other than the specfic set from being entered
///////////////////////////////////////////////////////////////////////////////
GRID_IMPLEMENT_CONTROL(CAlphaNumericEditControl, CGXEditControl)

CAlphaNumericEditControl::CAlphaNumericEditControl(CGXGridCore* pGrid, UINT nID) : CGXEditControl(pGrid, nID) 
{
}

BEGIN_MESSAGE_MAP(CAlphaNumericEditControl, CGXEditControl) 
//{{AFX_MSG_MAP(CNumericEditControl)
//}}AFX_MSG_MAP 
END_MESSAGE_MAP()  

void CAlphaNumericEditControl::GetAllowedCharacters( DString& dstrAllowedChar )
{

 ASSERT( m_nRow != 0 || m_nCol > 1 );

 CGXControl *ptrCGXCtrl		 = NULL;
 CGXGridCore* ptrCGXGridCore = NULL;
 DSTCellProperties* pCell	 = NULL;
 CGXStyle	  Style;

 dstrAllowedChar = NULL_STRING;
 ptrCGXCtrl		 = dynamic_cast <CGXControl * > (this);
 ptrCGXGridCore  = ptrCGXCtrl ? ptrCGXCtrl->Grid(): NULL ;
 ASSERT( ptrCGXGridCore != NULL );
 if( ptrCGXGridCore  )
 {
	(dynamic_cast< DSTGridWnd* > (ptrCGXGridCore))->GetStyleRowCol(m_nRow,m_nCol, Style );
	pCell = Style.GetIncludeItemDataPtr() ? 
			reinterpret_cast <DSTCellProperties *>( Style.GetItemDataPtr()) : NULL;
	dstrAllowedChar = pCell ? pCell->m_dstrAllowedChar : NULL_STRING;
 }   

}

BOOL CAlphaNumericEditControl::ValidateString(const CString& sEdit)
{
  DString dstrAllowedChar = NULL_STRING;
  GetAllowedCharacters( dstrAllowedChar );
  if(!dstrAllowedChar.empty())
  {
    CString cstrAllowedChar = dstrAllowedChar.c_str(); 
	for (int n = 0; n < sEdit.GetLength(); n++)
	{	
		if(cstrAllowedChar.Find( sEdit[n] ) < 0 )
			 return FALSE;	  
	}
  }
   return TRUE;
}
CAlphaNumericEditControl::~CAlphaNumericEditControl()
{    	
};
//******************************************************************************
/////////////////////////////////////////////////////////////////////////////
// DSTGridWnd

//*********************************************************************************
IMPLEMENT_USING_WR_AGENT(DSTGridWnd)
DSTGridWnd::DSTGridWnd(
                      BaseDlg *pParentDlg,
                      const I_CHAR *dialogName,
                      UINT controlId,
                      const I_CHAR *gridName,
                      const BFContainerId& idContainer,
                      UINT controlGroupID,
                      UINT flags):
BaseControl( pParentDlg, controlId, controlGroupID),
CGXGridWnd(),
m_gridType ( ATTRIBUTE ),
m_bHideLeftHeader( true ),
m_controlGroupID( controlGroupID ),
idContainer_( idContainer ),
m_strDialogName( dialogName ),
m_strGridName(gridName),
m_idTopSubstitution( ifds::NullFieldId ),
m_idLeftSubstitution( ifds::NullFieldId ),
m_strAttributeCodes( NULL_STRING ),
m_useCBOSubstitutions(false),
m_curRow(-1),
m_newRow(-1),
m_Timer(0),
m_turnOnSorting( false ),
m_sortAscending( false ),
m_currentKey( NULL_STRING ),
m_flags (flags)
{
   SubclassDlgItem( controlId, reinterpret_cast <CWnd *>( pParentDlg ));

   m_pParentDlg     = pParentDlg;
   m_pParentProcess = dynamic_cast< AbstractProcess * >( m_pParentDlg->getParent());
   m_controlId     = controlId;

   Initialize();
   GetParam()->EnableTrackColWidth();
   GetParam()->EnableSelection( GX_SELCELL );

   m_pParentDlg->GetDlgFont( m_logFont );

   // set default row height
   TEXTMETRIC tm;
   HDC hDC = ::GetDC( NULL );
   GetTextMetrics( hDC, &tm );
   SetDefaultRowHeight( tm.tmHeight + tm.tmExternalLeading + 4 );
   ::ReleaseDC( NULL, hDC );

   // enable mouse over msg
   //m_bDisableMouseMoveOver = FALSE;

   // enable tooltips
   EnableGridToolTips();
   GetParam()->GetStylesMap()->AddUserAttribute( GX_IDS_UA_TOOLTIPTEXT,
                                                 CGXStyle().SetWrapText( TRUE ).SetAutoSize( TRUE ));

   GetParam()->GetStylesMap()->AddUserAttribute( GX_IDS_UA_INPUTMASK,
                                                 CGXStyle().SetWrapText( TRUE ).SetAutoSize( TRUE ));

   GetParam()->SetActivateCellFlags(GX_CAFOCUS_CLICKONCELL);
   //registering the numeric control
   RegisterControl(IDS_CTRL_NUMEDIT, new CNumericEditControl(this, IDS_CTRL_NUMEDIT));
   RegisterControl(IDS_CTRL_ALPHNUMEDIT,  new CAlphaNumericEditControl(this, IDS_CTRL_ALPHNUMEDIT));
   // icon list
   m_icons = new CImageList();
   ASSERT( m_icons != NULL );    // serious allocation failure checking
   m_icons->Create( 16, 16, ILC_COLOR | ILC_MASK, 4, 4 );
   //m_icons->Add( AfxGetApp()->LoadIcon( IDI_NO_ERR_ICON ));
   m_icons->Add( LoadIcon( NULL, IDI_ASTERISK ));
   m_icons->Add( LoadIcon( NULL, IDI_EXCLAMATION ));
   m_icons->Add( LoadIcon( NULL, IDI_HAND ));

   // register icon ctrl
//   RegisterControl( GX_IDS_CTRL_ICON, new DSTIconCtrl( this ));
//   RegisterControl( GX_IDS_CTRL_DATETIME, new DSTDatePicker( this ));

   DSTOleDateTime dt;
   DString tmp;
   dt.getDisplayFormat( tmp );
   m_dateFormat = tmp.c_str( );
}

//*********************************************************************************
DSTGridWnd::~DSTGridWnd()
{
   privClearContainer();
   delete m_icons;
}


BEGIN_MESSAGE_MAP( DSTGridWnd, CGXGridWnd )
//{{AFX_MSG_MAP( DSTGridWnd )
ON_WM_CHAR()
ON_WM_TIMER()
// NOTE - the ClassWizard will add and remove mapping macros here.
WR_AGENT_MSG_MAP_ENTRY
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
IMPLEMENT_WR_AGENT_GRID_MSG(DSTGridWnd)


/////////////////////////////////////////////////////////////////////////////
// DSTGridWnd message handlers

// when in LIST mode, prevent resizing col 0
//*********************************************************************************
BOOL DSTGridWnd::OnTrackColWidth( ROWCOL nCol )
{
   return( m_gridType == LIST )? nCol != 0 : TRUE;
}

//*********************************************************************************
void DSTGridWnd::UpdateItem( int idx, const DString& rowKey )
{
   EXECHISTI( I_("UpdateItem(int, const DString&)" ) );
   DSTCellProperties *cell;

   InsertRows( idx, 1 );

   DString dummy;
   BFContainerId idDummyContainer;

   AbstractProcess * pParentProc = dynamic_cast < AbstractProcess * >( m_pParentDlg->getParent() );

   for( int i = 0; i < m_topHeader.size(); i++ )
   {
      if( m_topHeader[i]->strKey != NULL_STRING )
      {
         cell              = new DSTCellProperties( this, idx, m_topHeader[i]->nCol + m_bHideLeftHeader );
         m_cell.push_back( cell );
         cell->controlId   = m_controlId;
         cell->idContainer = idContainer_;
         cell->idField     = BFFieldId::getId( m_topHeader[i]->strKey );
         cell->colKey      = m_topHeader[i]->strKey;
         cell->rowKey      = rowKey;
         cell->listItemKey = rowKey; // for list, listItemKey == rowKey
         cell->cb.nSortingMode = DSTGridWnd::GRD_CMB_SORT_STATE::NO_SORT;

         m_pParentDlg->GetCellProperties( m_controlId, 
                                          cell->rowKey, 
                                          cell->colKey,
                                          idDummyContainer,
                                          cell->idField,
                                          dummy, 
                                          cell->nCellState,
                                          cell->cellCtrlType, 
                                          cell->cb.nInitMode,
                                          cell->cb.idSubstitution, 
                                          cell->cb.comboList, 
                                          cell->m_mask,
                                          cell->cb.nSortingMode, 
										  cell->m_dstrAllowedChar );
		 //if the whole grid is not updateable, make the cell read only
         if( !IsUpdateable() )
            cell->nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;

         HideCols( 0, 0, m_bHideLeftHeader );

         pParentProc->registerObserver( m_pParentDlg, cell->idContainer, cell->idField, pParentProc->getDataGroupId(), *cell );

         SetCurrCellProp( idx, m_topHeader[i]->nCol + m_bHideLeftHeader , cell );
      }
   }
}

//*********************************************************************************
BOOL DSTGridWnd::OnValidateCell( ROWCOL nRow, ROWCOL nCol )
{
   SEVERITY sevRtn = NO_CONDITION;
   bool formatted = true;
   bool bUpdated = false;

   if( nCol < 0 || nRow < 0 ) return(TRUE); // ignore header
   if( m_gridType == ATTRIBUTE &&  nCol == 0 ) return(TRUE); //ignore attribute column
   if( m_pParentDlg->IsCancelInProgress() )// don't need to validate if it was cancelled
      return(TRUE);

   DString strCurrentListKey(NULL_STRING), strCellListKey(NULL_STRING);
   DSTCellProperties * cell = GetCellPropertiesPtr( nRow, nCol );

   if( cell && cell->nCellState != DSTGridWnd::SKIPPED )
   {
      DString strKey;

      // get old value
      CString strOldValue;
      strOldValue = GetValueRowCol( nRow, nCol );
      // get current cell value
      CString sValue;
      if( cell->cellCtrlType == GX_IDS_CTRL_DATETIMENOCAL || cell->cellCtrlType == GX_IDS_CTRL_DATETIME )
      {
//CP20030204         CGXDateTimeCtrl* pCGXDateTimeCtrl = dynamic_cast< CGXDateTimeCtrl* >(GetCurrentCellControl( ));
         CGXDateTimeCtrl* pCGXDateTimeCtrl = dynamic_cast< CGXDateTimeCtrl* >(GetControl( nRow, nCol ));
         if( pCGXDateTimeCtrl )
         {
            DSTOleDateTime lDSTOleDateTime(pCGXDateTimeCtrl->GetDateTime());
            lDSTOleDateTime.DSTHostFormat( sValue );
            strOldValue.Remove('/');
            if( strOldValue.Compare(sValue) )
               bUpdated = true;
         };
         formatted = false;
      }
      else
      {
//CP20030204         GetCurrentCellControl()->GetCurrentText( sValue );
         GetControl( nRow, nCol )->GetCurrentText( sValue );
         DString tmpStr = sValue;
         BaseDlg::DisplayUnFormat( tmpStr, cell->idField );
         sValue = tmpStr.c_str();
//         const CGXStyle& rStyle = LookupStyleRowCol( nRow, nCol );
//         sValue = rStyle.GetValue();
         if( strOldValue.Compare(sValue) )
            bUpdated = true;
      }
      //because we're not guaranteed that the timing is right for this method if the container is repeatable
      //have to save the current item in the container and at the end restore it
      if( m_pParentProcess->isRepeatable( cell->idContainer ) )
      {
         strCurrentListKey = m_pParentProcess->getCurrentListItemKey(m_pParentDlg, cell->idContainer);
         m_pParentProcess->setCurrentListItem( m_pParentDlg, cell->idContainer, cell->listItemKey );
         strCellListKey = cell->listItemKey;
      }
      // check dlg level helper
      if( m_pParentDlg->SetCellValue( m_controlId, cell->rowKey,
                                      cell->colKey, LPCTSTR( sValue ), formatted, sevRtn ) != true )
      {
         if( formatted && isComboCell(cell->cellCtrlType) )
         {
            DString dstrDesc(sValue), dstrCode;
            formatted = false;
            if( cell->cb.nInitMode == USE_SUBSTITUTION_LIST )
            {
               GetSubstituionCodeFromDesc( cell->idContainer, cell->cb.idSubstitution, dstrDesc, dstrCode );
            }
            else if( cell->cb.nInitMode == USE_IDI_STRING )
            {
               GetSubstituionCodeFromDesc( cell->cb.comboList, dstrDesc, dstrCode );

               if( m_pParentProcess->isRepeatable( cell->idContainer ) )
               {
                  m_pParentDlg->OnGridSetCellValueSetKey( cell->controlId, cell->rowKey, dstrCode );
                  //cell->listItemKey = dstrCode;
               }
            }
            sValue = dstrCode.c_str();
         }
         m_pParentProcess->setField( m_pParentDlg, cell->idContainer, cell->idField, LPCTSTR( sValue ), formatted ) ;
      }
      //if necessary, restore the list item
      if( strCurrentListKey != strCellListKey )
      {
         //if Stingray would work fine, it should never happen
         m_pParentProcess->setCurrentListItem( m_pParentDlg, cell->idContainer, strCurrentListKey );
      }

      m_pParentDlg->OnGridSetCellValue( m_controlId, cell->rowKey, cell->colKey, LPCTSTR( sValue ));

      // prepare tooltip and icon

      SEVERITY nSeverity = m_pParentProcess->getErrors( m_pParentDlg, cell->idContainer,
                                                        cell->idField, m_conditions );

      cell->nIconId = -1;

      cell->m_sev = nSeverity;

      if( nSeverity > NO_CONDITION )
      {
         if( nSeverity > WARNING )
         {
            cell->nIconId = 2;
         }
         else if( nSeverity == WARNING )
         {
            cell->nIconId = 1;
         }
         else if( nSeverity == INFORMATIONAL )
         {
            cell->nIconId = 0;
         }

         CString Msg;

         SetMessageFromConditions( m_conditions, Msg );

         SetStyleRange( CGXRange( nRow,nCol ), CGXStyle()
                        .SetUserAttribute( GX_IDS_UA_TOOLTIPTEXT, Msg ));
      }

      if( bUpdated )
      {
         m_pParentDlg->setUpdateFlag( true );
         m_pParentDlg->GridControlUpdated( m_controlId, cell->rowKey,
                                           cell->colKey, LPCTSTR( sValue ), formatted, nSeverity );
      }
   }


   return(TRUE);
}

//
//*********************************************************************************
void DSTGridWnd::GetSubstituionCodeFromDesc( const DString& dstrIdi, const DString& dstrDesc, DString& dstrCode )
{
   dstrCode = NULL_STRING;
   I_CHAR *rpStr = const_cast< I_CHAR * >( dstrIdi.c_str() );

   while( *rpStr != '\0' )
   {
      DString dstrTag, dstrValue;
      rpStr = parseIdiString( rpStr, dstrTag, dstrValue );
      if( dstrValue == dstrDesc )
      {
         dstrCode = dstrTag;
         break;
      }
   }
}

//*********************************************************************************
void DSTGridWnd::GetSubstituionCodeFromDesc( const BFContainerId& idContainer, const BFFieldId &idSubstition, const DString& dstrDesc, DString& dstrCode )
{
   AbstractProcess * pProcess = dynamic_cast< AbstractProcess * >( m_pParentDlg->getParent() );
   if( !pProcess )
      return;

   const BFProperties * pBFProp = pProcess->getFieldAttributes( m_pParentDlg, idContainer, idSubstition );
   if( !pBFProp )
      return;

   DString *pdstrSubst = pBFProp->getAllSubstituteValues();

   DString dstrIdi(*pdstrSubst);

   if( dstrIdi == NULL_STRING )
   {
      const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idSubstition );
      if( NULL != pProps->getSubstitutionSet( ClientLocaleContext::get() ) )
      {
         pProps->getAllSubstituteValues( dstrIdi, ClientLocaleContext::get(), true );
      }
   }

   GetSubstituionCodeFromDesc( dstrIdi, dstrDesc, dstrCode );
}

// associate CellProperties pointer to a cell
//*********************************************************************************
void DSTGridWnd::SetCellPropertiesPtr( ROWCOL nRow, ROWCOL nCol, DSTCellProperties *pDSTCellProperties )
{
   SetStyleRange( CGXRange( nRow, nCol ), CGXStyle().SetItemDataPtr( pDSTCellProperties ));
}

// get CellProperties pointer associated to the cell
//*********************************************************************************
DSTCellProperties * DSTGridWnd::GetCellPropertiesPtr( ROWCOL nRow, ROWCOL nCol )
{
   CGXStyle style;
   GetStyleRowCol( nRow, nCol, style );

   // get col info
   return( style.GetIncludeItemDataPtr())?
   reinterpret_cast <DSTCellProperties *>( style.GetItemDataPtr()) : NULL;
}

//*********************************************************************************
void DSTGridWnd::SetMessageFromConditions( CONDITIONVECTOR &conditions, CString& Msg )
{  // Set up message from conditions
//TODO may want to save pointer to condition vector so can support CTRL+ALT+F1
   Msg = NULL_STRING;
   std::set<DString> packedCondSet;
   bool bFirst = true;

   for( int i = 0; i < conditions.size(); i++ )
   {
      DString strMsg = conditions[i]->getMessage();
      if( packedCondSet.insert(strMsg).second )
      {
         if( !bFirst )
            Msg += _T( " " );
         CString strTemp = strMsg.c_str();
         Msg += strTemp;
         bFirst = false;
      }
   }
}

//*********************************************************************************
void DSTGridWnd::BuildComboStr( const DString& dstrIdi, CString& comboStr )
{
   DString strValue;
   DString strTag;
   I_CHAR *rpStr = const_cast< I_CHAR * >( dstrIdi.c_str() );

   bool bFirstEntry = true;
   bool bHasBlankEntry = false;

   while( *rpStr != '\0' )
   {
      strTag = I_( "" );
      rpStr = parseIdiString( rpStr, strTag, strValue );
      // Allow the addition of 'blank' entries ... but only one!
      // CP 20030130
      if( NULL_STRING != strTag || !bHasBlankEntry )
      {
         if( NULL_STRING == strTag )
         {
            bHasBlankEntry = true;
         }

         if( bFirstEntry ) 
         {
            bFirstEntry = false;
         }
         else
         {
            comboStr += _T( "\n" );
         }
         // The Stingray ComboBox will display "(null)" if the string has no characters in it
         // In order to avoid this we put in a single blank if necessary ... CP20030130
         comboStr += strValue.empty() ? I_( " " ) : strValue.c_str();
      }
   }
}

//*********************************************************************************
void DSTGridWnd::InitCombobox( ROWCOL nRow, ROWCOL nCol, 
                               int nInitMode, 
                               int nSortingMode,
                               const BFFieldId &idSubstitutionList )
{
   EXECHISTI(I_("InitComboBox(ROWCOL,ROWCOL,int,int,const BFFieldId&)") );
   CString comboStr;

   switch( nInitMode )
   {
      case USE_SUBSTITUTION_LIST:
         {
            DString strIdi;

            AbstractProcess * pProcess = dynamic_cast< AbstractProcess * >( m_pParentDlg->getParent() );

            if( pProcess )
            {
               DSTCellProperties * pCell = GetCellPropertiesPtr( nRow, nCol );
               const BFProperties * lBFprop = pProcess->getFieldAttributes( m_pParentDlg, pCell->idContainer, idSubstitutionList );
               if( lBFprop )
               {
                  lBFprop->getSubstituteValues(strIdi);
               }
            }
            // bfbase already handle this
            //if ( strIdi == NULL_STRING )
            //{
            //       assert( lSubstitutionListId != -1 );
            //   DataElementProperties *dp = const_cast < DataElementProperties * >
            //          ( m_pParentDlg->getFieldAttributes( m_pParentDlg, idSubstitutionList ));
            //          
            //      if ( dp->hasSubstitutes() )
            //      {
            //          dp->getAllSubstituteValues( strIdi, NULL, true );
            //   }
            //}

            if ( nSortingMode != NO_SORT )
            {
               DString strTempIdi(strIdi);
               strIdi = NULL_STRING;
               SortComboStr(nSortingMode,strTempIdi,strIdi);
            }

            BuildComboStr( strIdi, comboStr );
         }
         break;

      case USE_IDI_STRING:
         {
            DString strIdi;
            DSTCellProperties * cell = GetCellPropertiesPtr( nRow, nCol );
            strIdi = cell->cb.comboList.c_str();

            if ( nSortingMode != NO_SORT )
            {
               DString strTempIdi(strIdi);
               strIdi = NULL_STRING;
               SortComboStr(nSortingMode,strTempIdi,strIdi);
            }

            BuildComboStr( strIdi, comboStr );
         }
         break;

      default:
         {
            DSTCellProperties * cell = GetCellPropertiesPtr( nRow, nCol );
            comboStr = cell->cb.comboList.c_str();
         }
         break;
   }

   SetStyleRange( CGXRange( nRow, nCol ), CGXStyle().SetChoiceList( comboStr ));
}

//*********************************************************************************
void DSTGridWnd::SortComboStr( int iSortMode, const DString& dstrIdiIn, DString& dstrIdiOut )
{
   vSubstitutionCodeDesc substitutionCodeDescs;

   DString strValue;
   DString strTag;
   I_CHAR *rpStr = const_cast<I_CHAR *>( dstrIdiIn.c_str() );

   while( *rpStr != '\0' )
   {
      strTag = I_( "" );
      rpStr = parseIdiString( rpStr, strTag, strValue );

      SubstitutionCodeDesc newElement;
      newElement.strCode = strTag;
      newElement.strDesc = strValue;

      substitutionCodeDescs.push_back(newElement);
   }

   if( iSortMode == CODE_ASCENDING )
   {
      sort(substitutionCodeDescs.begin(), 
           substitutionCodeDescs.end(), 
           DSTGridWnd::codeAscending );

      vSubstitutionCodeDesc::iterator iterSubstitutionCodeDescs = 
         substitutionCodeDescs.begin();

      dstrIdiOut = I_("");
      while( iterSubstitutionCodeDescs != substitutionCodeDescs.end() )
      {
         dstrIdiOut += (*iterSubstitutionCodeDescs).strCode;
         dstrIdiOut += I_("=");
         dstrIdiOut += (*iterSubstitutionCodeDescs).strDesc;
         dstrIdiOut += I_(";");
         ++iterSubstitutionCodeDescs;
      }
   }
   else if ( iSortMode == CODE_DESCENDING )
   {
      sort(substitutionCodeDescs.begin(), 
           substitutionCodeDescs.end(), 
           DSTGridWnd::codeDescending);

      vSubstitutionCodeDesc::iterator iterSubstitutionCodeDescs = 
         substitutionCodeDescs.begin();

      dstrIdiOut = I_("");
      while( iterSubstitutionCodeDescs != substitutionCodeDescs.end() )
      {
         dstrIdiOut += (*iterSubstitutionCodeDescs).strCode;
         dstrIdiOut += I_("=");
         dstrIdiOut += (*iterSubstitutionCodeDescs).strDesc;
         dstrIdiOut += I_(";");
         ++iterSubstitutionCodeDescs;
      }
   }
   else if ( iSortMode == DESC_ASCENDING )
   {
      sort(substitutionCodeDescs.begin(), 
           substitutionCodeDescs.end(), 
           DSTGridWnd::descAscending );

      vSubstitutionCodeDesc::iterator iterSubstitutionCodeDescs = 
         substitutionCodeDescs.begin();

      dstrIdiOut = I_("");
      while( iterSubstitutionCodeDescs != substitutionCodeDescs.end() )
      {
         dstrIdiOut += (*iterSubstitutionCodeDescs).strCode;
         dstrIdiOut += I_("=");
         dstrIdiOut += (*iterSubstitutionCodeDescs).strDesc;
         dstrIdiOut += I_(";");
         ++iterSubstitutionCodeDescs;
      }
   }
   else if( iSortMode == DESC_DESCENDING )
   {
      sort(substitutionCodeDescs.begin(), 
           substitutionCodeDescs.end(), 
           DSTGridWnd::descDescending );

      vSubstitutionCodeDesc::iterator iterSubstitutionCodeDescs = 
         substitutionCodeDescs.begin();

      dstrIdiOut = I_("");
      while( iterSubstitutionCodeDescs != substitutionCodeDescs.end() )
      {
         dstrIdiOut += (*iterSubstitutionCodeDescs).strCode;
         dstrIdiOut += I_("=");
         dstrIdiOut += (*iterSubstitutionCodeDescs).strDesc;
         dstrIdiOut += I_(";");
         ++iterSubstitutionCodeDescs;
      }
   }
   else
   {
      dstrIdiOut = dstrIdiIn;
   }

   substitutionCodeDescs.clear();
}

//*********************************************************************************
void DSTGridWnd::CreateHeader( const BFFieldId &idTopSubstitution, const BFFieldId &idLeftSubstitution )
{
   EXECHISTI(I_("CreateHeader()") );
   for( int i = 0; i < m_cell.size(); i++ )
      delete m_cell[i];
   m_cell.clear();

   m_idTopSubstitution  = idTopSubstitution;
   m_idLeftSubstitution = idLeftSubstitution;

   SetColCount( 0 );
   SetRowCount( 0 );

   int numCol = PrepareHeader( idTopSubstitution, true );
   int numRow = PrepareHeader( idLeftSubstitution, false );

   //m_gridType = ( numCol && numRow )? ATTRIBUTE : LIST;


   // for list type grid we are not showing column 0
   int RowHeaderColumns = ( m_gridType == LIST )? 0 : 1;

   SetColCount( numCol - RowHeaderColumns );
   SetRowCount( numRow );

   if( m_gridType == ATTRIBUTE )
   {
      SetColCount( 0 );
      SetRowCount( 0 );
      SetColCount( numCol - RowHeaderColumns );
      SetRowCount( numRow );
   }

   m_bHideLeftHeader = !numRow;
   HideCols( 0, 0, m_bHideLeftHeader );

   for( int i = 0; i < m_topHeader.size(); i++ )
   {
      SetStyleRange( CGXRange( 0, m_topHeader[i]->nCol + 1 - RowHeaderColumns ), CGXStyle()
                     .SetFont( CGXFont().SetLogFont( m_logFont ))
                     //.SetHorizontalAlignment( DT_RIGHT )   //DT_LEFT
                     .SetValue( m_topHeader[i]->strValue.c_str())
                     .SetItemDataPtr( m_topHeader[i] ));

   }

   for( int i = 0; i < m_leftHeader.size(); i++ )
   {
      SetStyleRange( CGXRange( i + 1, 0 ), CGXStyle()
                     .SetFont( CGXFont().SetLogFont( m_logFont ))
                     .SetValue( m_leftHeader[i]->strValue.c_str())
                     .SetItemDataPtr( m_leftHeader[i] ));
   }
   LoadSettings();

   if( m_gridType == LIST )
   {
      CGXProperties* pProp = GetParam( )->GetProperties( );
      pProp->SetDisplayHorzLines(FALSE);
      pProp->SetDisplayVertLines(FALSE);

      GetParam( )->SetActivateCellFlags(FALSE);
      GetParam( )->EnableMoveCols(FALSE);
      GetParam( )->EnableSelection(GX_SELFULL);
      GetParam( )->SetSpecialMode(GX_MODELBOX_SS);
   }
}

//*********************************************************************************
void DSTGridWnd::ClearGrid()
{
   EXECHISTI(I_("ClearGrid()") );
//CP   LockWindowUpdate();
   // remove contents
   privClearContainer();

   SetRowCount( 0 );
   SetColCount( 0 );
//CP   UnlockWindowUpdate();
//CP   RedrawWindow();
}

//*********************************************************************************
void DSTGridWnd::ClearContents()
{
   EXECHISTI(I_("ClearContents()") );
//CP   LockWindowUpdate();
   privClearContents();
//CP   UnlockWindowUpdate();
//CP   RedrawWindow();
}

// return the number of header items
//*********************************************************************************
int DSTGridWnd::PrepareHeader( const BFFieldId &idSubstitution, bool bIsTopHeader )
{
   EXECHISTI(I_("PrepareHeader()") );
   HEADER      * Header;
   HEADERMAP   * HeaderMap;

   if( bIsTopHeader )
   {
      HeaderMap = &m_topHeaderMap;
      Header    = &m_topHeader;
   }
   else
   {
      HeaderMap = &m_leftHeaderMap;
      Header    = &m_leftHeader;
   }

   HeaderMap->clear();
   for( int i = 0; i < Header->size(); i++ )
   {
      delete ( *Header )[i];
   }
   Header->clear();

   if( idSubstitution == ifds::NullFieldId )
   {
      return(0);
   }

   DString strIdi;
   DString strTag;
   DString strValue;

   if( m_useCBOSubstitutions )
   {
      AbstractProcess * pParentProcess = dynamic_cast<AbstractProcess *>( m_pParentDlg->getParent() );
      if( !pParentProcess )
      {
         assert( 0 );
         return(0);
      }
      const BFProperties * pBFProperties = pParentProcess->getFieldAttributes( m_pParentDlg, BF::NullContainerId, idSubstitution );

      if( pBFProperties )
         pBFProperties->getSubstituteValues( strIdi );
   }
   else
   {
      const BFDataFieldProperties* pProps = m_pParentDlg->getFieldAttributes( m_pParentDlg, idSubstitution );
      if( NULL != pProps->getSubstitutionSet( ClientLocaleContext::get() ) )
      {
         pProps->getAllSubstituteValues( strIdi, ClientLocaleContext::get(), true );
      }
      else
      {  // problem ??
         assert( 0 );
         return(0);
      }
   }
   DSTHeaderProperties *HeaderProperties;

   int count = 0;

   I_CHAR *rpStr = const_cast< I_CHAR * >( strIdi.c_str());

   while( *rpStr != '\0' )
   {
      rpStr = parseIdiString( rpStr, strTag, strValue );
      if( strTag != NULL_STRING && !bExcludeThisCode( strTag ) && !HideTheCode( strTag ) )
      {
         HeaderMap->insert( HEADERMAP::value_type( strTag, count ));
         HeaderProperties = new DSTHeaderProperties;
         HeaderProperties->nCol = count++;
         HeaderProperties->strKey = strTag;
         HeaderProperties->strValue = strValue;
         Header->push_back( HeaderProperties );
      }
   }

   return(count);
}

//********************************************************************************
bool DSTGridWnd::HideTheCode(DString& dstrTag )
{

   return(m_pParentDlg->HideGridRowColumn(dstrTag));

}
//*********************************************************************************
void DSTGridWnd::reLoadGrid (bool bSetSelection /*=true*/)
{
   EXECHISTI(I_("reLoadGrid()") );

   ClearGrid();
   CreateHeader (m_idTopSubstitution, m_idLeftSubstitution);
   LockUpdate(TRUE);
   LoadGrid (bSetSelection);
   LockUpdate(FALSE);
   RedrawWindow();
}

//*********************************************************************************
void DSTGridWnd::LoadGrid (bool bSetSelection /*=true*/)
{
   EXECHISTI(I_("LoadGrid()") );
   // clear m_cell
//  for( int i = 0; i < m_cell.size(); i++ )delete m_cell[i];
//  m_cell.clear();

//CP   LockWindowUpdate();
   bReadyForIcon = false;
   switch( m_gridType )
   {
      case LIST:
         PopulateListGrid( idContainer_, bSetSelection);
         break;

      case ATTRIBUTE:
         PopulateAttriGrid( idContainer_);
         break;
      default:
         break;
   }
//CP   UnlockWindowUpdate();
//CP   RedrawWindow();

   bReadyForIcon = true;
}


//*********************************************************************************
void DSTGridWnd::PopulateAttriGrid( const BFContainerId& idContainer)
{
   EXECHISTI(I_("PopulateAttriGrid()") );
   const DString *tmpKey;

   AbstractProcess * pParentProc = dynamic_cast < AbstractProcess * >( m_pParentDlg->getParent() );
   if( pParentProc->isRepeatable( idContainer) )
   {

      tmpKey = &m_pParentProcess->getCurrentListItemKey( m_pParentDlg, idContainer );
      if( tmpKey->empty() ) //the container is empty, we don't have to fill in the properties
         return;
   }
   for( int row = 1; row < m_leftHeader.size() + 1; ++row )
      for( int col=1; col < m_topHeader.size(); ++col )
      {
         refreshCell( row, col, pParentProc, idContainer );
      }
}

//*********************************************************************************
void DSTGridWnd::reloadCell( const DString& rowKey, const DString& colKey )
{
   ROWCOL iRow = getRowFromKey( rowKey );
   ROWCOL iCol = getColFromKey( colKey );
   if (iRow == 0 || iCol == 0)
      return;
   AbstractProcess * pParentProc = dynamic_cast < AbstractProcess * >( m_pParentDlg->getParent() );
   refreshCell( iRow, iCol, pParentProc, idContainer_ );
   Invalidate( TRUE );     // invalidate the window.  Should be more specific (i.e. only the cell), but I'm too lazy.  CP20030204
}

//*********************************************************************************
ROWCOL DSTGridWnd::getRowFromKey( const DString& rowKey ) const
{
   DSTCellProperties* pCell = NULL;
   ROWCOL iRow = 1;
   ROWCOL cRows = const_cast< DSTGridWnd* >( this )->GetRowCount() + 1;
   for( iRow = 1; iRow < cRows; ++iRow )
   {
      pCell = const_cast< DSTGridWnd* >( this )->GetCellPropertiesPtr( iRow, 1 );
      if( pCell && pCell->rowKey == rowKey )
      {
         return( iRow );
      }
   }
   return( 0 );
}

//*********************************************************************************
ROWCOL DSTGridWnd::getColFromKey( const DString& colKey ) const
{
   DSTCellProperties* pCell = NULL;
   ROWCOL iCol = 1;
   ROWCOL cCols = const_cast< DSTGridWnd* >( this )->GetColCount() + 1;
   for( iCol = 1; iCol < cCols; ++iCol )
   {
      pCell = const_cast< DSTGridWnd* >( this )->GetCellPropertiesPtr( 1, iCol );
      if( pCell && pCell->colKey == colKey )
      {
         return( iCol );
      }
   }
   return( 0 );
}


//*********************************************************************************
BOOL DSTGridWnd::refreshCell( ROWCOL row, 
                              ROWCOL col, 
                              AbstractProcess* pParentProc, 
                              const BFContainerId& idContainer )
{
   EXECHISTI(I_("refreshCell()") );
   DSTCellProperties* cell = GetCellPropertiesPtr( row, col );
   if( NULL == cell )
   {
      cell = new DSTCellProperties( this, row, col );
      m_cell.push_back( cell );
   }
   else
      cell->deRegisterObserver();

   cell->colKey      = m_topHeader[col]->strKey;
   cell->rowKey      = m_leftHeader[row-1]->strKey;
   cell->controlId   = m_controlId;
   cell->idContainer = idContainer;
   cell->cb.nSortingMode = DSTGridWnd::GRD_CMB_SORT_STATE::NO_SORT;
   m_pParentDlg->GetCellProperties( m_controlId, 
                                    cell->rowKey, 
                                    cell->colKey,
                                    cell->idContainer, 
                                    cell->idField,
                                    cell->listItemKey, 
                                    cell->nCellState,
                                    cell->cellCtrlType, 
                                    cell->cb.nInitMode,
                                    cell->cb.idSubstitution, 
                                    cell->cb.comboList, 
                                    cell->m_mask, 
                                    cell->cb.nSortingMode,
									cell->m_dstrAllowedChar);

   // set combo property if the dlg has not do so
   if( cell->cellCtrlType == GX_IDS_CTRL_CBS_DROPDOWNLIST && cell->cb.nInitMode == USE_SUBSTITUTION_LIST
       && cell->cb.idSubstitution == ifds::NullFieldId )
      cell->cb.idSubstitution = cell->idField;

   //if the whole grid is not updateable, make the cell read only
   if( !IsUpdateable() )
      cell->nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;

   pParentProc->registerObserver( m_pParentDlg, cell->idContainer, cell->idField, pParentProc->getDataGroupId(), *cell );

   // remember list key

   if( m_pParentProcess->isRepeatable( cell->idContainer ) )
   {
      const DString* tmpKey;
      tmpKey = &m_pParentProcess->getCurrentListItemKey( m_pParentDlg, cell->idContainer );
      cell->listItemKey = *tmpKey;       // It was out of if { }, but tmpkey is a empty pointer when this is no repeat record
   }

   SetCurrCellProp( row, col, cell );

//CP20030131   // restore list key
//CP20030131/*
//CP20030131   if( m_pParentProcess->isRepeatable( cell->containerId ))
//CP20030131      m_pParentProcess->setCurrentListItem(
//CP20030131      m_pParentDlg, cell->containerId,  *tmpKey );
//CP20030131*/
   return( TRUE );
}

//*********************************************************************************
void DSTGridWnd::PopulateListGrid( const BFContainerId& idContainer, bool bSetSelection /*=true*/ )
{
   EXECHISTI(I_("PopulateListGrid()") );
   idContainer_ = idContainer;

   // remember list key
   const DString *tmpKey = &m_pParentProcess->getCurrentListItemKey( m_pParentDlg, idContainer_ );

   // remove all rows
   SetRowCount( 0 );

   int nItem = 0;

   const DString *key = &m_pParentProcess->getFirstListItemKey( m_pParentDlg, idContainer_ );

//CP   LockWindowUpdate();
   while( !key->empty() )
   {
      if( m_pParentDlg->GridControlFilter( m_controlId, *key ) )
         UpdateItem( ++nItem, *key );
      key = &( m_pParentProcess->getNextListItemKey( m_pParentDlg, idContainer_ ));
   }
//CP   UnlockWindowUpdate();
//CP   RedrawWindow();

   // restore list key
   if( !tmpKey->empty() )
      m_pParentProcess->trySetCurrentListItem( m_pParentDlg, idContainer_,  *tmpKey );

   // select first row
   if (nItem > 0 && bSetSelection)
   {
      m_curRow = SelectRow( m_currentKey );
      HandleSelection ( m_curRow == -1? 1 : m_curRow );
   }
   else if (nItem > 0 && !bSetSelection)
   {
//for the time the user does not want the selection to be set, 
//we need to update the member variables   
      UINT controlId = GetControlID();
      DSTCellProperties *cell = GetCellPropertiesPtr( nItem, 1 );
      DString &strKey = cell->rowKey;

      m_curRow = nItem;
      m_currentKey = cell->rowKey;
      if (!m_currentKey.empty())
      {
         m_pParentProcess->setCurrentListItem( m_pParentDlg, idContainer_, m_currentKey);
      }
   }
   else
   {
      m_curRow = -1;
   }
   m_newRow = m_curRow;
}

//*********************************************************************************
void DSTGridWnd::SetCurrCellProp( ROWCOL nRow, ROWCOL nCol, DSTCellProperties *cell )
{
   if ((long)nRow < 0)
      return;
   DString str( NULL_STRING );
   bool bUpdated = false;
   bool bFormatted = true;

   if( cell->nCellState != DSTGridWnd::SKIPPED )
   {
      // get old value
      CString strOldValue;
      strOldValue = GetValueRowCol( nRow, nCol );

      if( cell->cellCtrlType == GX_IDS_CTRL_DATETIME || cell->cellCtrlType == GX_IDS_CTRL_DATETIMENOCAL 
          || cell->cellCtrlType == GX_IDS_CTRL_CHECKBOX3D ||  cell->cellCtrlType == GX_IDS_CTRL_CHECKBOX )
         bFormatted = false;
      if( m_pParentDlg->GetCellValue( m_controlId, cell->rowKey,
                                      cell->colKey, str, bFormatted ) != true )
      {
         // provide containerId and idField in GetCellProperties of dlg
         assert( cell->idContainer.isValid() && cell->idField != ifds::NullFieldId );
         m_pParentProcess->getField( m_pParentDlg, cell->idContainer, cell->idField, str,bFormatted );
      }
      str.strip();

      CString strCopy = str.c_str();
      if( !bFormatted )
      {
         strOldValue.Remove('/');
         if( strCopy == I_("Yes") ) strCopy = I_("1");
         else if( strCopy == I_("No") ) strCopy = I_("0");
      }
      if( strOldValue.Compare(strCopy) )//control updated
         bUpdated = true;

      // check box need to do convertion
      if( cell->cellCtrlType == GX_IDS_CTRL_CHECKBOX3D ||
          cell->cellCtrlType == GX_IDS_CTRL_CHECKBOX )
      {
         if( I_("Y") == str   ||  I_("Yes") == str || I_("1")   == str )
             str =  I_("1"); 
         else
             str = I_("0");
      }

   }

/////////////////////////////////////////////////
   SEVERITY nSeverity = m_pParentProcess->getErrors( m_pParentDlg, cell->idContainer,
                                                     cell->idField, m_conditions );

   cell->nIconId = -1;

   CString Msg = _T("");

   if( nSeverity > NO_CONDITION )
   {
      if( nSeverity > WARNING )
      {
         cell->nIconId = 2;
      }
      else if( nSeverity == WARNING )
      {
         cell->nIconId = 1;
      }
      else if( nSeverity == INFORMATIONAL )
      {
         cell->nIconId = 0;
      }

      SetMessageFromConditions( m_conditions, Msg );
   }
   if( bUpdated )
   {
      m_pParentDlg->GridControlUpdated( m_controlId, cell->rowKey,
                                        cell->colKey, str, bFormatted, NO_SEVERITY );
      m_pParentDlg->setUpdateFlag( true );
   }

/////////////////////////////////////////////////
   GetParam()->SetLockReadOnly( FALSE );
   CGXStyle cellStyle;

   cellStyle.SetFont( CGXFont().SetLogFont( m_logFont ))
   .SetControl( cell->cellCtrlType )
   //  .SetHorizontalAlignment( DT_RIGHT)  //cell->nAlignment ) 
   .SetItemDataPtr( cell )
   .SetUserAttribute( GX_IDS_UA_TOOLTIPTEXT, Msg );

   if( cell->cellCtrlType == GX_IDS_CTRL_DATETIME || cell->cellCtrlType == GX_IDS_CTRL_DATETIMENOCAL )
   {
      cellStyle.SetUserAttribute(GX_IDS_UA_CUSTOMFORMAT , m_dateFormat );

      // format date
      CString tmp;
      dt.DSTFormatWithHostFormat( str, tmp );
      //dt.DSTDisplayFormat( str, tmp );
      str = LPCTSTR( tmp );
   }

   if( cell->cellCtrlType == GX_IDS_CTRL_MASKEDIT )
   {
      cellStyle.SetUserAttribute( GX_IDS_UA_INPUTMASK, cell->m_mask.c_str() );
   }

   if( cell->cellCtrlType == IDS_CTRL_NUMEDIT )
   {
      cellStyle.SetControl(IDS_CTRL_NUMEDIT);
   }

   BaseDlg::DisplayFormat( str, cell->idField );
   cellStyle.SetValue( str.c_str());

   if( m_gridType == ATTRIBUTE && ( cell->cellCtrlType == GX_IDS_CTRL_EDIT || IDS_CTRL_NUMEDIT ==  cell->cellCtrlType ))
   {
      const BFProperties* pProps = (m_pParentProcess->getFieldAttributes(
                                                                        m_pParentDlg, cell->idContainer, cell->idField) );
      if( pProps )
         cellStyle.SetMaxLength(pProps->getMaxLength());
   }

   SetStyleRange( CGXRange( nRow, nCol ), cellStyle );

//  CGXStyle style;
//  GetStyleRowCol( nRow, nCol, style );

   GetParam()->SetLockReadOnly( TRUE ) ;

   if( cell->cellCtrlType == GX_IDS_CTRL_CBS_DROPDOWNLIST )
   {
      InitCombobox( nRow, nCol, cell->cb.nInitMode,
                                cell->cb.nSortingMode,
                                cell->cb.idSubstitution );
   }
   if( cell->cellCtrlType == IDS_CTRL_ALPHNUMEDIT )
   {
      cellStyle.SetControl(IDS_CTRL_ALPHNUMEDIT); 
   }
   SetCellPropertiesPtr( nRow,  nCol, cell );
}

// get the value and properties for a cell and set them
//*********************************************************************************
void DSTGridWnd::SetCell( ROWCOL nRow, ROWCOL nCol, DSTCellProperties *cell )
{
   DString str( NULL_STRING );

   if( cell->nCellState != DSTGridWnd::SKIPPED )
   {
      if( m_pParentDlg->GetCellValue( m_controlId, cell->rowKey,
                                      cell->colKey, str, true ) != true )
      {
         if( m_pParentProcess->isRepeatable( cell->idContainer ) )
            m_pParentProcess->setCurrentListItem( m_pParentDlg, cell->idContainer, cell->listItemKey );

         m_pParentProcess->getField( m_pParentDlg,
                                     cell->idContainer, cell->idField, str );
      }
      str.strip();
   }

   GetParam()->SetLockReadOnly( FALSE );

   BaseDlg::DisplayFormat( str, cell->idField );
   SetStyleRange( CGXRange( nRow, nCol ), CGXStyle()
                  .SetFont( CGXFont().SetLogFont( m_logFont ))
                  .SetControl( cell->cellCtrlType )
                  .SetValue( str.c_str())
                  //.SetHorizontalAlignment(DT_RIGHT) //cell->nAlignment )
                  .SetItemDataPtr( cell ));

   GetParam()->SetLockReadOnly( TRUE ) ;

   if( cell->cellCtrlType == GX_IDS_CTRL_CBS_DROPDOWNLIST )
   {
      InitCombobox( nRow, nCol, cell->cb.nInitMode,
                                cell->cb.nSortingMode,
                                cell->cb.idSubstitution );
   }
}

//*********************************************************************************
void DSTGridWnd::privClearContainer()
{
   EXECHISTI(I_("privClearContainer()") );
   int i;

   privClearContents();

   for( i = 0; i < m_topHeader.size(); ++i ) {
      delete m_topHeader[i];
   }
   m_topHeader.clear();

   for( i = 0; i < m_leftHeader.size(); ++i ) {
      delete m_leftHeader[i];
   }
   m_leftHeader.clear();
}

//******************************************************************************
void DSTGridWnd::privClearContents()
{
   EXECHISTI(I_("privClearContents()") );
   for( int i = 0; i < m_cell.size(); ++i )
   {
      delete m_cell[i];
   }
   m_cell.clear();

}

//*********************************************************************************
void DSTGridWnd::OnDrawItem( CDC *pDC, ROWCOL nRow, ROWCOL nCol, const CRect& rectDraw, const CGXStyle& style )
{
   ASSERT( pDC != NULL && pDC->IsKindOf( RUNTIME_CLASS( CDC )));
   // ASSERTION-> Invalid Device Context ->END
   ASSERT( nRow <= GetRowCount() && nCol <= GetColCount());
   // ASSERTION-> Cell coordinates out of range ->END

   // TRACE( _T( "CGXGridCore::OnDrawItem( %lu, %lu, ( %d,%d,%d,%d ), pDC )\n" ),
   //    nRow, nCol, ( RECT ) rectItem );
   m_pParentDlg->GetDlgFont( m_logFont );
   CGXStyle* pStyle = const_cast< CGXStyle* >( &style );
   pStyle->SetFont( CGXFont().SetLogFont( m_logFont ));
#ifdef TICKCOUNT
   DWORD tick1 = GetTickCount();
#endif

   CGXControl* pControl = GetRegisteredControl( style.GetControl());
   ASSERT( pControl && pControl->IsKindOf( CONTROL_CLASS( CGXControl )));
   // ASSERTION-> The control returned by GetControl is not derived from CGXControl. ->END

   // if this is the current cell, is control initialized correctly?
   if( nRow && nCol
       && IsCurrentCell( nRow, nCol )
       && !pControl->IsInit( nRow, nCol ) )
   {
      // TRACE0( "Warning! Current cell has been  reinitialized in OnDrawItem\n" );
      // This is ok and will happen after you change the cell type of
      // the current cell with SetStyleRange, ..!

      pControl->Init( nRow, nCol );
   }

// draw icon
   CRect r = rectDraw;
   if( bReadyForIcon )
      DrawIcon( pDC, nRow, nCol, r );

   pControl->Draw( pDC, r, nRow, nCol, style, m_pStyleStandard );

#ifdef TICKCOUNT
   tickDrawItem += GetTickCount()-tick1;
#endif
}

//*********************************************************************************
void DSTGridWnd::DrawIcon( CDC *pDC, ROWCOL nRow, ROWCOL nCol,CRect& rectDraw )
{
   if( nRow >0 && nCol > 0 )
   {
      DSTCellProperties * cell = GetCellPropertiesPtr( nRow,  nCol );

      if( cell && cell->nCellState != DSTGridWnd::SKIPPED )
      {
         UINT nIcon = cell->nIconId;
         if( nIcon == 1 || nIcon == 2 || nIcon == 0 )
         {
            CRect r = rectDraw;
            r.right = r.left + ( r.Height() < 16 ? 16 : r.Height() ); // set bounds of user draw space

            CPoint iconpos = r.TopLeft();
            iconpos.Offset( (r.Width()-16)/2, (r.Height()-16)/2 ); // centre the icon

            CBrush brush( ::GetSysColor( COLOR_WINDOW ) );
            pDC->SelectObject( &brush );
            pDC->PatBlt( r.left, r.top, r.Width(), r.Height(), PATCOPY ); // clear the draw space

            m_icons->Draw( pDC, nIcon, iconpos, ILD_TRANSPARENT ); // draw the icon

            rectDraw.left = r.right;
         }
      }
   }
}

//*************************************************************************************
bool DSTGridWnd::isValueInList(CString& dstrValue,CString& dstrList )
{
   int iPos;
   bool bRet = false;
   while( dstrList.GetLength() )
   {
      CString listValue;
      int nRem = 0;
      iPos = dstrList.FindOneOf( _T( "\a\n" ) );
      if( iPos != -1 )
      {
         listValue = dstrList.Left ( iPos );

      }
      else
      {
         listValue = dstrList;
         nRem = dstrList.GetLength();
      }
      if( listValue == dstrValue )
      {
         bRet =  true;
         break;
      }
      dstrList.Delete(0, iPos + nRem +1 );
   }
   return(bRet);
}

//*********************************************************************************
BOOL DSTGridWnd::OnEndEditing(ROWCOL nRow, ROWCOL nCol)
{
   if( nRow >0 && nCol > 0 )
   {
      DSTCellProperties * cell = GetCellPropertiesPtr( nRow,  nCol );

      if( cell && isComboCell(cell->cellCtrlType) )
      {
         CString strValue;
         strValue = GetValueRowCol( nRow, nCol );
         if( strValue != m_oldComboValue.c_str() )
         {
            CString comboStr;
            CGXStyle style;
            GetStyleRowCol( nRow, nCol, style );
            comboStr = style.GetChoiceList( );
            if( !isValueInList(strValue,comboStr ) )
            {
               SetCurrCellProp(nRow, nCol, cell );
            }

         }
      }

   }
   return(true);
}

//*********************************************************************************
//  check read only before allow editing
BOOL DSTGridWnd::OnStartEditing( ROWCOL nRow, ROWCOL nCol )
{
   if( nRow >0 && nCol > 0 )
   {
      DSTCellProperties * cell = GetCellPropertiesPtr( nRow,  nCol );

      if( cell && cell->nCellState != DSTGridWnd::SKIPPED )
      {
         if( isComboCell(cell->cellCtrlType) )

            m_oldComboValue = GetValueRowCol( nRow, nCol );

         // set skipped cell to read only
//          if( cell->nCellState != DSTGridWnd::SKIPPED ) return FALSE;

         if( m_pParentProcess->isRepeatable( cell->idContainer ) )
            m_pParentProcess->setCurrentListItem( m_pParentDlg, cell->idContainer, cell->listItemKey );

         const BFProperties *pProp = m_pParentProcess->getFieldAttributes(
                                                                         m_pParentDlg, cell->idContainer, cell->idField );

         return(!(( cell->nCellState == READ_ONLY ) ||
                  ( cell->nCellState == USE_FIELD_PROPERTY && ( pProp && pProp->isReadOnly()))));
      }
   }

   return(FALSE);
}

//******************************************************************************
bool DSTGridWnd::SaveSettings()
{
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, I_("SaveSettings") );

   bool result = false;

//   Store();
//   CanSelectCurrentCell( false , ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol)

   try
   {
      int count = GetColCount();

      if( count > 0 )
      {
         ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
         Configuration workstation = pWorkstation->retrieveConfig( m_strDialogName );

         int  colWidth = 0;
//         col.mask = LVCF_WIDTH | LVCF_FMT;

         DString title( GR );
         title += m_strGridName;

         DString strHold( title );
         strHold += I_( ".colcount=" );
         strHold += asString( count );
         workstation.set( strHold );

         if( m_idTopSubstitution != ifds::NullFieldId )
         {
            HEADERMAP_ITER Iter ;
            HEADERMAP_ITER IterEnd = m_topHeaderMap.end();

            Iter =    m_topHeaderMap.begin();
            while( Iter != IterEnd )
            {
               if( (*Iter).first != NULL_STRING )
               {
                  ROWCOL nCol = (*Iter).second;
                  if( m_gridType == LIST ) ++nCol;
                  colWidth = GetColWidth( nCol );

                  if( colWidth )
                  {  // Save settings
                     strHold = title;
                     strHold += I_( "." );
                     strHold += (*Iter).first;
                     strHold += I_( "=" );
                     strHold += asString( colWidth );
                     CGXStyle style;

                     GetColStyle(nCol,style);
                     UINT unAlignment = style.GetHorizontalAlignment( );
                     strHold +=I_(",");
                     strHold += asString( unAlignment );
                     workstation.set( strHold );
                  }
               }
               ++Iter;
            }
         };

         pWorkstation->storeConfig( workstation );
         pWorkstation->persist();   // Throws on bad reg config

         result = true;
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

   return(result);
}

//******************************************************************************
bool DSTGridWnd::LoadSettings()
{
   int count;
   bool useDefault=false;
   DString strHold;
   DString title( GR );
   title += m_strGridName;

   ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
   Configuration workstation = pWorkstation->retrieveConfig( m_strDialogName );

   // Get column count
   strHold = title;
   strHold += I_( ".colcount" );
   strHold = workstation.getValueAsString( strHold );
   if( strHold.empty() )
   {
      // try to get the default column setting
      pWorkstation = ConfigManager::getManager( DEFAULTWORKSTATION );
      workstation = pWorkstation->retrieveConfig( m_strDialogName );
      strHold = title;
      strHold += I_( ".colcount" );
      strHold = workstation.getValueAsString( strHold );
      if( strHold.empty() )
         useDefault=true;
   }
   else
   {
      count = asInteger( strHold );
      if( count <= 0 )
      {
         useDefault=true;
      }
   }

   int  colWidth = 0;
   UINT unAlignment = 0;
//   LVCOLUMN col;
//   col.mask = LVCF_WIDTH | LVCF_FMT;
//  DString fmt;

   if( m_idTopSubstitution != ifds::NullFieldId )
   {
      HEADERMAP_ITER Iter ;
      HEADERMAP_ITER IterEnd = m_topHeaderMap.end();

      Iter =    m_topHeaderMap.begin();
      while( Iter != IterEnd )
      {
         if( (*Iter).first != NULL_STRING )
         {
            colWidth = 100;
            unAlignment = 0;

            strHold = title;
            strHold += I_( "." );
            strHold += (*Iter).first;

            if( !useDefault )
            {
               strHold = workstation.getValueAsString( strHold );
               if( !strHold.empty() )
               {
                  i_sscanf(strHold.c_str(), I_("%d,%d"), &colWidth, &unAlignment);
               }
            }
            ROWCOL nCol = (*Iter).second;
            if( m_gridType == LIST ) ++nCol;

            // sanity check on column width
            colWidth = std::max( 0, std::min( colWidth, 1000 ) );

            SetColWidth( nCol, nCol, colWidth );              
            SetStyleRange( CGXRange().SetCols(nCol),CGXStyle().SetHorizontalAlignment( unAlignment ) );
         }
         ++Iter;
      }
   };

   return(true);
}

//******************************************************************************
BOOL DSTGridWnd::OnActivateGrid( BOOL bActivate )
{
   if( bActivate == TRUE )
   {
      DoSetFocus();
   }
   else
   {
      //DoKillFocus();//no need to call it : everything it is done in OnValidateCell
      Store();//??if Stingray would work fine, we shouldn't call Store() here
      SaveSettings();
   }
   return(TRUE);
}

/******************************************************************************
void DSTGridWnd::OnGridKillFocus(CWnd* pNewWnd)
{
   CGXGridWnd::OnGridKillFocus( pNewWnd );

    Store();
    DoKillFocus();
   SaveSettings();

}

//******************************************************************************
void DSTGridWnd::OnGridSetFocus(CWnd* pOldWnd)
{
   CGXGridWnd::OnGridSetFocus( pOldWnd );
   DoSetFocus();
}*/

//******************************************************************************
void DSTGridWnd::DoGetText(DString &strValueOut, int index) const
{

}

//******************************************************************************
void DSTGridWnd::DoInit(void)
{
   SetFlags (m_flags);
}

//******************************************************************************
bool DSTGridWnd::DoSetText(const DString &strValueIn, int index)
{
   return(true);
}

//******************************************************************************
bool DSTGridWnd::Store()
{
   CGXControl* pCGXControl = GetCurrentCellControl( );
   if( pCGXControl )
   {
      pCGXControl->Store();
      pCGXControl->OnEndEditing();
   }
   if( pCGXControl && pCGXControl->GetModify() )
      pCGXControl->OnValidate( );

   return(true);
};

//******************************************************************************
void DSTGridWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   if( nChar == 22 ) return; // temp take out ctrl+v
   if( nChar != 9 )
      CGXGridWnd::OnChar(nChar, nRepCnt, nFlags);
   else
   {
      if( m_pParentDlg )
      {
         CWnd* pWndNext = m_pParentDlg->GetNextDlgTabItem( this );
         if( pWndNext != NULL )
            pWndNext->SetFocus();
      };
   };
}

//******************************************************************************
bool DSTGridWnd::doSetCtrlReadOnly(bool bReadOnly)
{
   SetUpdateable(!bReadOnly);
   LoadGrid();
   return(true);
}

//*******************************************************************************
bool DSTGridWnd::bExcludeThisCode( DString& strCode )
{
   return(m_strAttributeCodes != NULL_STRING &&
         m_strAttributeCodes.find( strCode ) != DString::npos);
}

//******************************************************************************
void DSTGridWnd::OnChangedSelection(const CGXRange* pRange, BOOL bIsDragging, BOOL bKey)
{
   if( m_gridType == LIST )
   {
      KillTimer(m_Timer);

      if( !pRange || pRange->bottom < 1 || m_curRow == pRange->bottom ) return;

      if( m_curRow == -1 )
      {
         m_curRow = pRange->bottom;
      }

      m_newRow = pRange->bottom;

      // store current row data
      m_pParentDlg->ProcessControls();

      if (m_newRow != -1)// if (m_curRow != -1)
      {
// update current grid row
         DSTCellProperties *cell;
         for (int i = 0; i < m_topHeader.size(); i++)
         {
            cell = GetCellPropertiesPtr( m_newRow, i+1 );//GetCellPropertiesPtr( m_curRow, i+1 );
//set selection on the parent container before changing the curr cell properties
            m_pParentDlg->getParent()->setCurrentListItem (m_pParentDlg, idContainer_, cell->rowKey);
            SetCurrCellProp( m_newRow, i+1, cell );//SetCurrCellProp( m_curRow, i+1, cell );
         }
      }

      m_Timer = SetTimer(m_TimerEvent, m_TimerLength, NULL);
   }
}

//******************************************************************************
void DSTGridWnd::HandleSelection( int iItem )
{
   UINT controlId = GetControlID();
   DSTCellProperties *cell = GetCellPropertiesPtr( iItem, 1 );
   DString &strKey = cell->rowKey;

   m_curRow = iItem;
   m_currentKey = cell->rowKey;

   m_pParentDlg->getParent()->setCurrentListItem( m_pParentDlg, idContainer_, strKey );
   m_pParentDlg->ConnectControlsToData( controlId, true );
   m_pParentDlg->LoadControls( controlId );
}

//******************************************************************************
BOOL DSTGridWnd::OnLButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt)
{
  DSTCellProperties *cell; 
  if( m_turnOnSorting && !nRow )
   {
      DString strKey;
      if( m_curRow != -1 ) // only the list type use m_curRow
      {
         // get current selection
         cell = GetCellPropertiesPtr( m_curRow, 1 );
         strKey = cell->rowKey;
      }

      CGXSortInfoArray sortInfo;
      sortInfo.SetSize(1);      
      sortInfo[0].nRC = nCol;   
      sortInfo[0].sortType = CGXSortInfo::autodetect;   
      sortInfo[0].sortOrder = (m_sortAscending = !m_sortAscending)? CGXSortInfo::ascending : CGXSortInfo::descending;   
      SortRows(CGXRange().SetTable(), sortInfo);

      // restore selection after sorting
      if( m_curRow != -1 ) // if there were selection
      {
         m_curRow = SelectRow( strKey );
      }
   }
   else
   {
      m_curRow = nRow;
      cell = GetCellPropertiesPtr( m_curRow, nCol );
      //if it is a check box ,allow the user to tick with single click
      if( GX_IDS_CTRL_CHECKBOX3D == cell->cellCtrlType ||
         GX_IDS_CTRL_CHECKBOX  == cell->cellCtrlType )
           SetCheckBoxTicked(nRow, nCol);
   }

   return(TRUE);
}
//******************************************************************************
void DSTGridWnd::SetCheckBoxTicked(ROWCOL nRow, ROWCOL nCol)
{
  DSTCellProperties *cell = GetCellPropertiesPtr( nRow, nCol );
  CGXControl * pCheckBox = GetControl( nRow, nCol );
  if( pCheckBox->IsReadOnly() )
      return;
  CString strChecked;
  pCheckBox->GetValue(strChecked);
  strChecked =  strChecked == _T("1")? _T("0"): _T("1") ;
  DString value = strChecked == _T("1")? I_("Y") : I_("N");
  m_pParentProcess->setField( m_pParentDlg, cell->idContainer, cell->idField, 
                              value, false ) ;
  m_pParentDlg->OnGridSetCellValue( m_controlId, cell->rowKey, cell->colKey, value);
  SetCurrCellProp(nRow, nCol, cell );
}
//******************************************************************************
void DSTGridWnd::OnClickedButtonRowCol(ROWCOL nRow, ROWCOL nCol)
{
   DSTCellProperties *cell = GetCellPropertiesPtr( nRow, nCol );

   if( cell->cellCtrlType == GX_IDS_CTRL_CHECKBOX3D ||
       cell->cellCtrlType == GX_IDS_CTRL_CHECKBOX )
   {
      CGXControl * pCheckBox = GetControl( nRow, nCol );
      //Don't check condition IsReadOnly here..if(!pCheckBox->IsReadOnly()) instead overide the setfield functionality 
      //let the process/cbo handle these special  processing as the implememtation can vary from case to case..
      CString strChecked;
      pCheckBox->GetValue(strChecked);
      DString value = strChecked == _T("1")? I_("Y") : I_("N");
      m_pParentProcess->setField( m_pParentDlg, cell->idContainer, cell->idField, 
                                  value, false ) ;
      m_pParentDlg->OnGridSetCellValue( m_controlId, cell->rowKey, cell->colKey, value);

   }
}

//******************************************************************************
void DSTGridWnd::OnTimer(UINT nIDEvent)
{
   if( nIDEvent == m_TimerEvent )
   {
      KillTimer(m_Timer);

      if( m_curRow != -1 && m_newRow != -1 )
      {
         /*
         // store current row data
         m_pParentDlg->ProcessControls();
   
         // update current grid row
         DSTCellProperties *cell;
         for ( int i = 0; i < m_topHeader.size(); i++ )
         {
           cell = GetCellPropertiesPtr( m_curRow, i+1 );
           SetCurrCellProp( m_curRow, i+1, cell );
         }
         */

         // select new row
         HandleSelection(m_newRow);
      }
   }
}

//******************************************************************************
void DSTGridWnd::ResetCurrentItem()
{
   if( m_curRow != -1 )
   {
      m_pParentDlg->getParent()->resetCurrentItem( idContainer_ );

      HandleSelection( m_curRow );

      // update current grid row
      DSTCellProperties *cell;
      for( int i = 0; i < m_topHeader.size(); i++ )
      {
         cell = GetCellPropertiesPtr( m_curRow, i+1 );
         SetCurrCellProp( m_curRow, i+1, cell );
      }
   }
}

//******************************************************************************
// select row by key. if key is not right, select first row
int DSTGridWnd::SelectRow( const DString& strKey )
{
   m_curRow = -1;

   if( strKey != NULL_STRING && GetRowCount() > 0 )
   {
      m_curRow = getRowFromKey( strKey );
      m_curRow = m_curRow > 0 ? m_curRow : 1;

//CP20030131      DSTCellProperties *cell;
//CP20030131      m_curRow = 1;
//CP20030131      for( int i=1; i< GetRowCount()+1; ++i )
//CP20030131      {
//CP20030131         cell = GetCellPropertiesPtr( i, 1 );
//CP20030131         if( cell->rowKey == strKey )
//CP20030131         {
//CP20030131            m_curRow = i;
//CP20030131            break;
//CP20030131         }
//CP20030131      }

      SetCurrentCell(m_curRow,1);
      SelectRange(CGXRange( ).SetTable( ), FALSE);
      SelectRange(CGXRange( ).SetRows(m_curRow), TRUE);
   }

   return(m_curRow);
}

//******************************************************************************
void DSTGridWnd::setContainer( const BFContainerId& idContainer )
{
   idContainer_ = idContainer;
}

//******************************************************************************
SEVERITY DSTGridWnd::AddRow ( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::GUI_CONDITION, CLASSNAME, I_("AddRow") );

   const DString *pNewItemKey = &( m_pParentDlg->getParent()->
                                   getKeyForNewListItem( m_pParentDlg, idContainer_ ) );
   assert( pNewItemKey );

   if( pNewItemKey )
   {  // Add successful
      UpdateItem( GetRowCount()+1, *pNewItemKey );
      SelectRow ( *pNewItemKey );
   }

   return(GETHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DSTGridWnd::DeleteRow ( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::GUI_CONDITION, CLASSNAME, I_("DeleteRow") );   

   if( m_curRow != -1 )
   {
      DSTCellProperties *cell = GetCellPropertiesPtr( m_curRow, 1 );
      ROWCOL nNextRow =  m_curRow == GetRowCount()? m_curRow - 1: m_curRow +1;  
      DSTCellProperties* cellNext = nNextRow < 0? NULL:GetCellPropertiesPtr( nNextRow, 1 );
      DString &strKey = cell->rowKey;
      // Need to set because this may be first update which would create a new
      //  iterator
      m_pParentDlg->getParent()->setCurrentListItem( m_pParentDlg,
                                                     idContainer_, strKey );
      if( m_pParentDlg->getParent()->deleteItemFromList( m_pParentDlg,
                                                         idContainer_ ) <= WARNING )
      {  // Remove from list
         //SetDeleting( true );
         RemoveRows( m_curRow, m_curRow );

         if( !GetRowCount() )
         {
/*            if ( IsAutoAdd() )  // Add this in the future??
            {  // If no more, must create new object
               AddRow();
            }
            else
            {  // Disable associated controls here*/
            m_pParentDlg->ConnectControlsToData( GetControlID(), false );
            //reset the row count.
            m_curRow = -1;
            //}
         }
         else
         {
            if( m_curRow >= GetRowCount() )
            {  // Deleted last item in list, so back up one
               m_curRow--;
            }
            if( m_curRow <= GetRowCount() )
            {  // Select another item
               //DSTCellProperties *cell = GetCellPropertiesPtr( m_curRow, 1 );
               //DString &strKey = cell->rowKey;
               if( cellNext )
               {
                  DString &strKey = cellNext->rowKey;
                  SelectRow( strKey );
               }
            }
         }
         //SetDeleting( false );
      }
   }

   return(GETHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DSTGridWnd::GetMaxErrorState()
{
   SEVERITY maxSev = NO_SEVERITY;
   ROWCOL nRows = GetRowCount();
   ROWCOL nCols = GetColCount();
   for( int i=1; i<=nRows; i++ )
   {
      for( int j=1; j<=nCols; j++ )
      {
         DSTCellProperties * cell = GetCellPropertiesPtr( i, j );
         if( cell && cell->nCellState != DSTGridWnd::SKIPPED && cell->m_sev > maxSev )
            maxSev = cell->m_sev;
      }
   }
   return(maxSev);
}

//******************************************************************************
const DString& DSTGridWnd::GetCurrentRowKey ()
{
   if (m_curRow != -1)
   {
      DSTCellProperties *cell = GetCellPropertiesPtr (m_curRow, 1);

      if (cell != NULL)
      {
         return cell->rowKey;
      }
   }
   return DSTGridWnd::s_empty_;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTGridWnd.cpp-arc  $
//
//23-Oct-2014.Robs-fixing the task # issue .Renaming T78456 to T78460 in the checkin comments
//   Rev 1.126   Apr 15 2010 18:10:42   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading - F4 Browser screen helper...
//
//   Rev 1.125   Jul 28 2009 07:21:32   dchatcha
//PET 157825 - FN 13 - Dilution Allocation Enhancements, Default NO_SORT for combo box type.
//
//   Rev 1.124   Jul 24 2009 01:00:38   dchatcha
//PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
//
//   Rev 1.123   Mar 24 2009 10:31:34   purdyech
//Changes for ZTS.  Release 9 for Phase II of POC
//
//   Rev 1.122   Feb 20 2009 14:01:46   purdyech
//ZTS Revision 6
//
//   Rev 1.121   Oct 06 2008 07:21:40   wongsakw
//revert to Rev1.119 because IN 1210534 code review failed.
//
//   Rev 1.120   Aug 14 2008 14:12:46   wongsakw
//in 1210534 Desktop trading focus issue
//
//   Rev 1.119   Apr 05 2006 10:27:02   fengyong
//Incident #582374 - Grid control on trading screen not being refreshed correctly.
//
//   Rev 1.118   Nov 15 2005 11:47:46   fengyong
//Incident 455379 - numeric string validation fix
//
//   Rev 1.117   Sep 27 2005 10:32:42   fengyong
//Incident #40519 - resize grid control together with the screen resizing
//
//   Rev 1.116   Jun 24 2005 17:01:08   Fengyong
//PET1250 FN02 - EuroPean numeric enhancement
//
//   Rev 1.115   Jun 10 2005 12:52:38   popescu
//Incident# 280865 - grid should not steal focus if there is a control with focus on it, due to the fact that the error state is greater then WARNING
//
//   Rev 1.114   Mar 08 2005 12:31:14   popescu
//Incident #257469, fixed grid selection; 
//
//   Rev 1.113   Feb 25 2005 14:36:44   yingbaol
//Incident#251642:  fix selecting next row when user delete a row.
//
//   Rev 1.112   Feb 18 2005 13:35:08   popescu
//Incident# 237774, set current selection on the parent container before restoring the properties of the current cell
//
//   Rev 1.111   Feb 17 2005 18:52:56   popescu
//Incident # 243445, more fixes related with the grid refresh
//
//   Rev 1.110   Feb 17 2005 16:43:24   popescu
//Incident # 243445, added a new parameter to LoadGrid method that will determine, whether the grid selection should be set or not, based on the dialogs business flow - default parameter is true (always set the selection)
//
//   Rev 1.109   Jan 10 2005 18:54:12   popescu
//PTS 10037268, fee rate should only be entered as numeric
//
//   Rev 1.108   Oct 01 2004 18:15:14   popescu
//PET 1117/06, SSB Germany - Added 'flags' parameter to the grid control - not very useful for the moment
//
//   Rev 1.107   Aug 19 2004 14:27:22   popescu
//PTS 10033225, replaced  '/r/n' with ' ' (space) between two conditions messages; (tool tip message shows an ugly [][], for chars '/r/n').
//
//   Rev 1.106   Oct 01 2003 16:50:06   PURDYECH
//Added public function clearContents() to remove the contents of a Grid without removing the headers, etc.
//
//   Rev 1.105   May 01 2003 15:29:22   PURDYECH
//Columns were not being set to correct width if there was no registry entry.  No we correctly deal with this boundary case.  Also, we sanity check the column width before setting it ... must be no less than 0 and no more than 1000 pels.
 * 
 *    Rev 1.104   Mar 20 2003 15:08:48   PURDYECH
 * Merge back from branch.
 * 
 *    Rev 1.103   Jan 30 2003 14:09:14   PURDYECH
 * Fixed little typos.
 * 
 *    Rev 1.102   Jan 30 2003 14:06:24   PURDYECH
 * Added support to allow blank entries to be added to a ComboBox cell by adding I_("=;") to the substitution list.
 * 
 *    Rev 1.101   Jan 14 2003 11:05:20   PURDYECH
 * DataGroupid parentage knowledge
 * 
 *    Rev 1.100   Jan 06 2003 16:46:44   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.99   Nov 27 2002 15:06:34   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.98   Nov 14 2002 10:48:58   SMITHDAV
 * Sync-up from old source database.
 * 
 *    Rev 1.97   Oct 09 2002 17:42:44   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.96   Oct 07 2002 14:02:46   KOVACSRO
 * Added GetMaxErrorState()
 * 
 *    Rev 1.95   Sep 24 2002 17:43:44   KOVACSRO
 * Pack conditions (don't show the same error message twice)
 * 
 *    Rev 1.94   Sep 19 2002 12:05:12   PURDYECH
 * BFFieldId has lost its operator long() method, so BFFieldId can no longer be compared to ints.  Code was changed to reflect this.
 * 
 *    Rev 1.93   Sep 19 2002 10:43:18   YINGBAOL
 * fix dynamic change gridType issue
 * 
 *    Rev 1.92   Sep 12 2002 15:26:22   YINGBAOL
 * suuport dynamic show/hide grid
 * 
 *    Rev 1.91   Sep 05 2002 14:01:00   HSUCHIN
 * added support for add/delete from Stingray Grid
 * 
 *    Rev 1.90   Sep 05 2002 10:43:00   DINACORN
 * Added setContainer().
 * 
 *    Rev 1.89   Aug 29 2002 12:57:34   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.88   Aug 27 2002 15:41:28   KOVACSRO
 * set max. length for an edit control (PTS 10009486)
 * 
 *    Rev 1.87   Aug 08 2002 13:33:36   KOVACSRO
 * Added GridControlUpdated
 * 
 *    Rev 1.86   Aug 08 2002 11:19:50   KOVACSRO
 * Release 48: Added bFormatted parameter to GetCellValue
 * 
 *    Rev 1.85   Jul 30 2002 15:53:50   YINGBAOL
 * fix cell null pointer
 * 
 *    Rev 1.84   Jul 26 2002 13:30:44   YINGBAOL
 * fix problem focus on other coontrol rather than Grid 
 * 
 *    Rev 1.83   Jul 25 2002 11:51:52   YINGBAOL
 * Fix Combobox issue-----PTS10008601
 * 
 *    Rev 1.82   23 Jul 2002 10:24:38   YINGZ
 * rollback
 * 
 *    Rev 1.80   Jul 09 2002 09:20:16   YINGBAOL
 * skip Ctrl_V
 * 
 *    Rev 1.79   Jul 05 2002 10:46:52   PURDYECH
 * Include file cleanup.
 * 
 *    Rev 1.78   Jun 28 2002 09:57:06   YINGBAOL
 * column alignment support
 * 
 *    Rev 1.77   19 Jun 2002 11:52:04   YINGZ
 * positioning
 * 
 *    Rev 1.76   Jun 18 2002 13:11:08   KOVACSRO
 * Added formatted parameter to setCellValue.
 * 
 *    Rev 1.75   17 Jun 2002 16:36:22   YINGZ
 * position key when reload
 * 
 *    Rev 1.74   15 Jun 2002 16:10:26   YINGZ
 * check in
 * 
 *    Rev 1.73   14 Jun 2002 10:49:32   YINGZ
 * fix drop down problem
 * 
 *    Rev 1.72   12 Jun 2002 17:06:04   YINGZ
 * fix
 * 
 *    Rev 1.71   Jun 06 2002 15:38:36   YINGZ
 * allow disable sorting
 * 
 *    Rev 1.70   Jun 06 2002 14:53:50   YINGZ
 * bug free version
 * 
 *    Rev 1.69   Jun 06 2002 11:48:26   YINGZ
 * take out !
 * 
 *    Rev 1.66   Jun 06 2002 09:44:44   YINGZ
 * test
 * 
 *    Rev 1.65   Jun 05 2002 16:47:34   YINGZ
 * support reset
 * 
 *    Rev 1.64   Jun 05 2002 14:14:22   YINGZ
 * support timer list
 * 
 *    Rev 1.63   05 Jun 2002 13:54:14   SMITHDAV
 * Fix grid refresh bug. Added trySetCurrentKey functions.
 * 
 *    Rev 1.62   Jun 04 2002 15:20:24   YINGZ
 * fix
 * 
 *    Rev 1.61   Jun 04 2002 14:40:48   YINGZ
 * support check box
 * 
 *    Rev 1.59   Jun 03 2002 15:43:22   YINGZ
 * support drag
 * 
 *    Rev 1.58   May 30 2002 11:48:42   YINGZ
 * list/sorting support
 * 
 *    Rev 1.57   May 30 2002 10:10:34   YINGZ
 * check
 * 
 *    Rev 1.56   May 28 2002 12:21:20   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.55   May 23 2002 09:55:46   PURDYECH
 * BFData Implementation Verification Corrections
 * 
 *    Rev 1.54   22 Apr 2002 17:32:06   SMITHDAV
 * Fix warning/error icon display problem as per 
 * PTS....7859
 * 
 *    Rev 1.53   Mar 20 2002 17:08:36   VADEANUM
 * Added OnGridSetCellValueSetKey().
 *
 *    Rev 1.52   20 Mar 2002 16:36:26   KOVACSRO
 * Because Stingray doesn't call OnValidateCell() when focus is lost, have to force it by calling Store() in OnActivateGrid().
 *
 *    Rev 1.51   Mar 20 2002 15:46:18   HERNANDO
 * Support for WinRunner Agent.
 *
 *    Rev 1.50   15 Mar 2002 13:00:58   KOVACSRO
 * If value changed, notify the parent dialog.
 *
 *    Rev 1.49   14 Mar 2002 15:49:02   KOVACSRO
 * Syncup 1.37-1.47
 *
 *    Rev 1.48   13 Mar 2002 17:44:04   KOVACSRO
 * Restored 1.36 and fixed OnValidateCell(). Removed doKillFocus() because it doesn't apply to the grid.
 *
 *    Rev 1.35   Jun 26 2001 19:01:56   PURDYECH
 * More Infrastructure Release 1.9 Integration stuff.
 *
 *    Rev 1.34   30 May 2001 15:43:02   YINGZ
 * support exclusion
 *
 *    Rev 1.33   17 May 2001 09:43:24   YINGZ
 * support reinitgrid
 *
 *    Rev 1.32   May 14 2001 15:19:30   YINGBAOL
 * fix date format issue for Morgan
 *
 *    Rev 1.31   11 May 2001 11:03:06   YINGZ
 * better support combo
 *
 *    Rev 1.30   08 May 2001 14:26:56   YINGZ
 * data group fix
 *
 *    Rev 1.29   27 Apr 2001 13:50:04   BUZILAMI
 * notifying the dialog on grid value changes
 *
 *    Rev 1.28   Apr 26 2001 13:21:00   YINGZ
 * fix stingery date display problem
 *
 *    Rev 1.27   Apr 16 2001 10:57:26   YINGBAOL
 * we do not need to check first list item key if the  list is only CBO
 *
 *    Rev 1.26   Apr 06 2001 12:07:04   YINGZ
 * make changes to datagroup
 *
 *    Rev 1.25   03 Apr 2001 11:57:22   KOVACSRO
 * Permission check stuff.
 *
 *    Rev 1.24   30 Mar 2001 17:41:08   KOVACSRO
 * Implemented SetCtrlReadOnly().
 *
 *    Rev 1.23   07 Mar 2001 15:44:42   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 *
 *    Rev 1.22   Jan 10 2001 13:29:52   YINGBAOL
 * add edit_mask
 *
 *    Rev 1.21   Oct 30 2000 15:58:36   HUANGSHA
 * added function GetSubsCodeFromDesc() to save the substitution code instead of Desc
 *
 *    Rev 1.20   Oct 18 2000 17:33:40   ZHANGCEL
 * Fixed the bug for populating data for non-repeatble record CBO
 *
 *    Rev 1.19   Jun 13 2000 17:55:50   DT24433
 * new Infra interfaces use ClientLocale
 *
 *    Rev 1.18   Jun 01 2000 13:40:26   BUZILA
 * storing the value on killFocus
 *
 *    Rev 1.17   May 29 2000 14:59:52   BUZILA
 * loading combo entries from the current field preperties instead of dataElementProperties.
 *
 *    Rev 1.16   May 29 2000 09:20:52   BUZILA
 * maskedEdits
 *
 *    Rev 1.15   May 15 2000 16:14:10   BUZILA
 * fix error icons display in grid
 *
 *    Rev 1.14   May 09 2000 10:18:22   BUZILA
 * grid fixes
 *
 *    Rev 1.13   May 02 2000 10:18:28   BUZILA
 * M3
 *
 *    Rev 1.12   Apr 28 2000 18:20:12   BUZILA
 * M3
 *
 *    Rev 1.11   Apr 06 2000 16:38:38   BUZILA
 * avoid repositioning at each cell processing in populateAttriGrid
 *
 *    Rev 1.10   Apr 04 2000 12:59:24   BUZILA
 * implemented SaveSettings/LoadSettings
 *
 *    Rev 1.9   Mar 30 2000 09:28:26   BUZILA
 * LIST grid column hiding fixed
 *
 *    Rev 1.8   Mar 22 2000 12:56:32   BUZILA
 * Grid changes
 *
 *    Rev 1.7   Mar 17 2000 14:23:00   YINGZ
 * restore list item
 *
 *    Rev 1.6   Mar 17 2000 13:54:24   YINGZ
 * add filter function for grid
 *
 *    Rev 1.5   Mar 14 2000 09:45:04   YINGZ
 * change nReadOnly to nCellState to provide more state
 *
 *    Rev 1.4   Mar 13 2000 15:21:48   YINGZ
 * skip a cell
 *
 *    Rev 1.3   Mar 13 2000 14:57:02   YINGZ
 * enable skip a cell
 *
 *    Rev 1.2   Mar 09 2000 11:35:42   YINGZ
 * modify comment 8 ))
 *
 *    Rev 1.1   Mar 09 2000 11:25:32   YINGZ
 * add OnStartEditing
 *
 *    Rev 1.0   Mar 08 2000 16:22:50   YINGZ
 * Initial revision.
*/