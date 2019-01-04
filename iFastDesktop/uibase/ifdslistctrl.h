#pragma once

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

/*** Defines not yet available in MS VC++ 6.0 ********************************/
#ifndef COLOR_HOTLIGHT
   #define COLOR_HOTLIGHT 26
#endif

#include <vector>
#include <dstring.hpp>
#include <bfutil\clientlocalecontext.hpp>
#include <bfproc\bfcontainerid.hpp>
#include <bfdata\bffieldid.hpp>
#include <bfproc\genericinterface.hpp>

#include <uibase\dstlistctrl.h>

#include <boost\type_traits.hpp>
#include <boost\static_assert.hpp>
#include <bfutil/localetraits.hpp>

class DSTMsg;
class DString;
class BFSubstitutionSet;
class BFFieldId;
class BaseDlg;

class IFDSListCtrl;
class IFDSListBase;

class IFDSListCtrlColumnInfo
{
public:
   IFDSListCtrlColumnInfo()
   : name_( I_( "" ) )
   , fmt_( LVCFMT_LEFT )
   , cx_( 100 )
   , bEnableHiding_( true )
   , pFieldId_( NULL )
   {}

   DString name_;
   int fmt_;
   int cx_;
   bool bEnableHiding_;
   const BFFieldId* pFieldId_;

   const BFFieldId* getFieldId() const { return pFieldId_; }
};

typedef std::vector< IFDSListCtrlColumnInfo > COLUMN_INFO_VECTOR;


/**
 * This abstract class defines the data associated with a row within 
 * an IFDSListCtrl ListView control.  Every IFDSListCtrlAdapter 
 * requires a concrete class which is derived from this class.
 * 
 * @author Chris Purdye
 * @version 1.0
 * @see IFDSListCtrlAdapter
 */
class IFDSListCtrlRowDataBase
{
public:
   virtual ~IFDSListCtrlRowDataBase() {}
   /**
    * This member function is called whenever the data elements of the
    * IFDSListCtrlRowDataBase-derived class are to be set.  The function
    * is called only for the *current* container item so normal 
    * AbstractProcess member functions (e.g. getField()) can be called
    * safely.
    * 
    * @param pParent Pointer to the parent dialog of the IFDSListCtrl to which this object
    *                is associated.
    * @param pCtrl   Pointer to the IFDSListCtrl object to which this object is related.
    * @param pKey    Pointer to the key associated with this object.
    */
   virtual void update( BaseDlg* pParent, IFDSListCtrl* pCtrl, const DString* pKey ) = 0;
};

/**
 * Every instance of an IFDSListCtrl requires an instance of an 
 * adapter class.  The adapter class specializes the behaviour of 
 * the IFDSListCtrl object to allow it to sort on columns, display
 * row data, and manipulate column ordering.  
 * 
 * This interface class is used by IFDSListCtrl to access the concrete
 * adpater class developed by the application programmer.  The developer
 * should use the template class IFDSListCtrlAdapter as the base class
 * of the concrete adapter class
 * 
 * @author Chris Purdye
 * @version 1.0
 * @see IFDSListCtrlAdapter
 * @see IFDSListCtrl
 */
class IFDSListCtrlAdapterBase
{
public:
   /**
    * This member function is called during initialization of the 
    * associated IFDSListCtrl object.  The application developer can
    * override the initialization options here.
    * 
    * @param pCtrl  Pointer to the associated IFDSListCtrl object.
    */
   virtual void init( IFDSListCtrl* pCtrl ) { return; }

   /**
    * This function is called by IFDSListCtrl in response to the Win32
    * notification message LVN_GETDISPINFO.  The template class 
    * IFDSListCtrlAdapter implements a custom version of this function.
    * 
    * The application developer should not need to override this function.
    * 
    * @param pCtrl     Pointer to the associated IFDSListCtrl object
    * @param pDispInfo Pointer the LV_DISPINFO struct passed from Windows
    * 
    * @return This function should always return 0.
    */
   virtual LRESULT getDispInfo( IFDSListCtrl* pCtrl, LV_DISPINFO* pDispInfo ) = 0;

   /**
    * This function is called by IFDSListCtrl in response to the Win32
    * notification message LVN_COLUMNCLICK.  The template class
    * IFDSListCtrlAdapter implements a customized version of this function.
    * 
    * The application developer should not need to override this function.
    * 
    * @param pCtrl  Pointer to the associated IFDSListCtrl object
    * @param pNMHDR Pointer to the NMHDR struct passed from Windows.
    * 
    * @return This function should always return 0.
    */
   virtual LRESULT columnClick( IFDSListCtrl* pCtrl, LPNMLISTVIEW pNMHDR ) = 0;

   /**
    * This function creates a new instance of the IFDSListCtrlRowData 
    * class.  The template class IFDSListCtrlAdapter implements a 
    * specialized version of this function to create the proper type.
    * 
    * @return Pointer to an IFDSListCtrlRowDataBase-derived object.
    * @see IFDSListCtrlAdapter#newItemData IFDSListCtrlAdapter::newItemData
    * @see IFDSListCtrlRowDataBase
    */
   virtual IFDSListCtrlRowDataBase* newItemData() = 0;

   /**
    * This member function is called by IFDSListCtrl before the columns
    * are inserted into the ListView.  The application developer can alter
    * the order and attributes of the columns in this function.
    * 
    * @param pCtrl    Pointer to the associated IFDSListCtrl object
    * @param vColumns Reference to a vector of ListView columns objects,
    *                 IFDSListCtrlColumnInfo.
    */
   virtual void prepareColumns( IFDSListCtrl* pCtrl,
                                COLUMN_INFO_VECTOR& vColumns )
   { return; }

public:
   /**
    * Member function which calls the application developer written compare
    * function during processing of the LVM_SORT message.
    * 
    * The application developer should not have to override this function.
    * 
    * @param pCtrl   Pointer to the associated IFDSListCtrl object
    * @param lParam1 First parameter passed by Windows during item comparison
    * @param lParam2 Second parameter passed by Windows during item comparison
    * 
    * @return This function passes back the return value of IFDSListCtrlAdapter::compare
    * @see IFDSListCtrlAdapater#compare IFDSListCtrlAdapater::compare
    */
   virtual int compareIndirect( IFDSListBase* pCtrl, LPARAM lParam1, LPARAM lParam2 ) = 0;

};

/**
 * Abstract template class which is used by the application developer
 * to create concrete adapter classes for IFDSListCtrl.
 * 
 * The developer needs to specify the type of the RowData for the
 * IFDSListCtrl as a template argument.
 * 
 * @author Chris Purdye
 * @version 1.0
 * @see IFDSListCtrlRowDataBase
 */
template< class _ID >
class IFDSListCtrlAdapter : public IFDSListCtrlAdapterBase
{
private:
   // Will generate Compile Error C2027 if _ID is not derived from IFDSListCtrlRowDataBase
   BOOST_STATIC_ASSERT( ( ::boost::is_convertible< _ID*, IFDSListCtrlRowDataBase* >::value ) );

public:
   /**
    * Convenience typedef for the specialized IFDSListCtrlRowDataBase
    * object which parameterizes this template.
    * 
    * @see IFDSListCtrlRowDataBase
    */
   typedef _ID RowData;

public:
   /**
    * This member function is called whenever the ListView control needs
    * to compare two items  during a sort operation.
    * 
    * This member function <i>must</i> be overridden by the application
    * developer.
    * 
    * @param pCtrl      Pointer to the associated IFDSListCtrl object
    * @param iSortColumn
    *                   index of the column which provides the primary sorting data.
    * @param bAscending true if the sort is being done in ascending order.  false if the
    *                   sort is being done in descending order.
    * @param pRowData1  Pointer to the row data for the first item being compared
    * @param pRowData2  Pointer to the row data for the second item being compared
    * @param lParam1    Raw LPARAM value for first item.  The LPARAM value is passed from
    *                   windows during sort processing.  The value may be passed to certain
    *                   class member functions of IFDSListCtrl to determine other characteristics
    *                   of the item.
    * @param lParam2    Raw LPARAM value for second item.
    * 
    * @return A negative value if the first item is less than the second item.
    *         A positive value if the first item is greater than the second item.
    *         0 if the two items are equal.
    */
   virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pRowData1, RowData* pRowData2, LPARAM lParam1, LPARAM lParam2 ) = 0;

   /**
    * This member function is called whenever the ListView control asks
    * the application for its cell data.
    * 
    * This member function <i>must</i> be overridden by the application
    * developer.
    * 
    * @param pCtrl     Pointer to the associated IFDSListCtrl object.
    * @param pRowData  Pointer to the row data for the item.
    * @param pDispInfo Pointer to the LV_DISPINFO struct which was passed from Windows
    * 
    * @return This function should always return 0.
    * @see LPNMLVDISPINFOW LV_DISPINFO
    * @see IFDSListCtrlRowDataBase
    * @see IFDSListCtrl
    */
   virtual LRESULT onGetDispInfo( IFDSListCtrl* pCtrl, RowData* pRowData, LV_DISPINFO* pDispInfo ) = 0;

public:
   /**
    * This member function is called whenever a column in a ListView control
    * is clicked.  By default this function invokes a sort on that
    * column.
    * 
    * The application developer <i>may</i> override this function, but 
    * probably should not need to.
    * 
    * @param pCtrl  Pointer to the associated IFDSListCtrl object
    * @param pNMHDR Pointer to the NMLISTVIEW struct which was passed from Windows.
    * 
    * @return This function should always return 0.
    */
   virtual LRESULT onColumnClick( IFDSListCtrl* pCtrl, LPNMLISTVIEW pNMHDR )
   {
      LRESULT lResult = 0;
      pCtrl->SortItems( compareFunc, reinterpret_cast< DWORD >( pCtrl ) );
      return( lResult );
   }

public:
   /**
    * This function creates a new instance of the RowData.
    * 
    * @return A pointer to the new RowData object.
    * @see IFDSListCtrlRowDataBase
    */
   virtual IFDSListCtrlRowDataBase* newItemData() { return new _ID; }

   /**
    * This function is called from IFDSListCtrl whenever two items need
    * to be compared during a sort operation.
    * 
    * The application developer should not need to override this function.
    * 
    * @param pCtrl   Pointer to the associated IFDSListCtrl object
    * @param lParam1 First parameter passed from LVM_SORTITEMS
    * @param lParam2 Second parameter passed from LVM_SORTITEMS
    * 
    * @return -1 if first item is less than second item.
    *         +1 if first item is greater than second item.
    *         0 if both items are equal.
    */
   virtual int compareIndirect( IFDSListBase* pCtrl, LPARAM lParam1, LPARAM lParam2 )
   {
      RowData* pData1 = reinterpret_cast< RowData* >( IFDSListBase::getItemRowData( lParam1 ) );
      RowData* pData2 = reinterpret_cast< RowData* >( IFDSListBase::getItemRowData( lParam2 ) );
      int iSortColumn = pCtrl->getSortColumn();
      return( compare( pCtrl, abs( iSortColumn ), ( iSortColumn >= 0 ), pData1, pData2, lParam1, lParam2 ) );
   }

   // worker functions
   static int CALLBACK compareFunc( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
   {
      IFDSListBase* pCtrl = reinterpret_cast< IFDSListBase* >( lParamSort );
      return( pCtrl->getAdapter()->compareIndirect( pCtrl, lParam1, lParam2 ) );
   }

   /**
    * Convenience function to return a strongly typed pointer to the 
    * user specified RowData object associated with the specified row.
    * 
    * @param pCtrl  Pointer to the associated IFDSListCtrl object
    * @param iItem  0-based index of the ListView item
    * 
    * @return Pointer to the RowData object for the specified item.  NULL if the
    *         item index was out of range.
    */
   RowData* getItemRowData( IFDSListCtrl* pCtrl, int iItem )
   {
      LPARAM lParam = pCtrl->GetItemData( iItem );
      if( 0 != lParam ) 
      {
         return( reinterpret_cast< RowData* >( IFDSListBase::getItemRowData( lParam ) ) );
      }
      return( NULL );
   }

   /**
    * Member function to process LVN_GETDISPINFO notification message.
    * 
    * This function should not need to be overridden by the application 
    * developer
    * 
    * @param pCtrl     Pointer to the associated IFDSListCtrl object
    * @param pDispInfo Pointer to the LV_DISPINFO struct passed from Windows
    * 
    * @return This function should return 0.
    */
   virtual LRESULT getDispInfo( IFDSListCtrl* pCtrl, LV_DISPINFO* pDispInfo )
   {
    const bfutil::LocaleTraits& localeTraitsE = bfutil::LocaleTraits::get( ClientLocaleContext::get() );
    I_CHAR RadixSeparatorE = localeTraitsE.getRadixSeparator();
	I_CHAR GroupseparatorE = localeTraitsE.getGroupSeparator();

	DString dstrRadixSeparatorE, dstrGroupseparatorE;
	dstrRadixSeparatorE = localeTraitsE.getRadixSeparator();
	dstrGroupseparatorE = localeTraitsE.getGroupSeparator(); 

    const bfutil::LocaleTraits& localeTraitsDisp = bfutil::LocaleTraits::get( ClientLocaleContext::get(), true );
    I_CHAR RadixSeparatorDisp = localeTraitsDisp.getRadixSeparator();
	I_CHAR GroupseparatorDisp = localeTraitsDisp.getGroupSeparator();

      int iSubItem = pDispInfo->item.iSubItem;
      pDispInfo->item.iSubItem = pCtrl->getLogicalIndex( pDispInfo->item.iSubItem );
      RowData* pItemData = getItemRowData( pCtrl, pDispInfo->item.iItem );
      LRESULT l = onGetDispInfo( pCtrl, pItemData, pDispInfo );

	  const BFFieldId* pFieldId = pCtrl->getColumnField( pDispInfo->item.iSubItem );	  
	  DString dstLocaleStr = ClientLocaleContext::get().getLocale();
	  if( dstLocaleStr == I_("deDE") )
	  {		
		bool bdecimal = false;
		DString strText = pDispInfo->item.pszText;
		strText.stripAll('%');
		bdecimal = strText.isDecimal();

		if( bdecimal )	  
		{
			//Check if current format is default (ENG)
			DString strtmp = pDispInfo->item.pszText;
			int posGE = strtmp.find(dstrGroupseparatorE);
			int posRE = strtmp.find(dstrRadixSeparatorE);
			bool _bDispE = ( posRE > 0 ) && ( posGE < posRE );

			if( _bDispE )
			{
				DString tmp = pDispInfo->item.pszText;
				int cnt = tmp.length();
				for( int i=0; i< cnt; i++ )
				{
					if( pDispInfo->item.pszText[i] == GroupseparatorE )
					{
						pDispInfo->item.pszText[i] = GroupseparatorDisp;
					}
					else if( pDispInfo->item.pszText[i] == RadixSeparatorE )
					{
						pDispInfo->item.pszText[i] = RadixSeparatorDisp;
					}
				}
			}
		}
	  }

      pDispInfo->item.iSubItem = iSubItem;
      return( l );
   }

   /**
    * Member function to process LVN_COLUMNCLICK notification message.
    * 
    * This function should not need to be overridden by the application
    * developer.
    * 
    * @param pCtrl     Pointer to the associated IFDSListCtrl object
    * @param pNMHDR    Pointer to the NMLISTVIEW struct passed from Windows
    * 
    * @return This function should return 0.
    */
   virtual LRESULT columnClick( IFDSListCtrl* pCtrl, LPNMLISTVIEW pNMHDR )
   {
      return( onColumnClick( pCtrl, pNMHDR ) );
   }
};



// forward declaration of 'helper' class for IFDSListBase
class IFDSListCtrlHelper;

/**
 * This class provides the basic Win32 functionality for IFDSListCtrl.
 * 
 * MFC has two different classes which wrap the ListView control:  
 * CListCtrl and CListView.  CListCtrl is a class which supports
 * free standing ListView controls.  CListView treats the ListView
 * control as though it were a <i>View</i> of a Document-View model.
 * This class was originally designed to provide the Win32 functionality
 * for both CListCtrl and CListView, but CListView is not necessary
 * for the iFAST architecture so it is not currently implemented.
 * 
 * @author Chris Purdye
 * @version 1.0
 * @see IFDSListCtrl
 * @see IFDSListCtrlHelper
 */
class WIN32UIBASE_LINKAGE IFDSListBase
{
public:
   IFDSListBase();
   ~IFDSListBase();

   IFDSListBase& privInit();
   IFDSListBase& colorSortColumn(bool bEnable = true, int nSortColumn = 0);

protected:
   // functions used to draw elements within the listview
   virtual void drawSmallIcon(CDC* pDC, LVITEM* pItem, LPRECT pRect) const;
   virtual void drawStateIcon(CDC* pDC, LVITEM* pItem, LPRECT pRect) const;
   virtual void drawSubItemText(CDC* pDC, LVITEM* pItem, LVCOLUMN* pColumn, LPRECT pRect) const;

public:
   IFDSListBase& enableColumnHiding(int iColumn, bool bEnableIt = true);
   IFDSListBase& enableSortIcon(bool bEnable = true, int nSortColumn = 0);

   int getColumnCount() const
   {
      return(static_cast<int>(aColumnData_.size()));
   }

   int  getSortColumn() const {return(iSortColumn_);}
   bool getState( DString& dstrState ) const;
   bool keepIconLeft(bool bKeepLeft = true);
   bool restoreState( const DString& configName, const DString& valueName );
   bool saveState( const DString& configName, const DString& valueName ) const;
   IFDSListBase& setSortColumn(int iColumn);
   bool setState( const DString& dstrState );
   void showColumn(int iColumn, bool bShowIt = true);

   int insertColumns( const COLUMN_INFO_VECTOR& rvColInfo );
	bool sortByInsertionOrder();

   COLUMN_INFO_VECTOR prepareColumns( const BFSubstitutionSet* pSubSet ) const;
   COLUMN_INFO_VECTOR prepareColumns( const BFFieldId& idField, const ClientLocale& rLocale = ClientLocaleContext::get() ) const;
   COLUMN_INFO_VECTOR prepareColumns( const ClientLocale& rLocale = ClientLocaleContext::get() ) const;
   bool removeColumns();

   const BFFieldId* getColumnField( int iColumn ) const;

   static LPARAM getItemRowData( LPARAM lParam );
   static const LVITEM* getColumnLVItem( LPARAM lParam, int iColumn );

   bool hasErrorIcon() const { return bHasErrorIcon_; }
   IFDSListBase& setHasErrorIcon( bool b ) { bHasErrorIcon_ = b; return( *this ); }

public:
   virtual IFDSListCtrlAdapterBase* getAdapter() = 0;

protected:
   virtual const BFFieldId& getColumnControlField() const = 0;

private:
   void ctor();

   enum VISUAL_STYLE
   {
      Unknown, NotPresent, Present
   };

   friend class IFDSListCtrl;

   class COLUMN_DATA
   {
   public:
      COLUMN_DATA()
      : pFieldId_( NULL )
      , bHidingAllowed_(false)
      , bVisible_(true)
      , cx_(0)
      , iOrder_(0)
      , pLVColumn_(0) {}
      ~COLUMN_DATA();

      const BFFieldId* pFieldId_;
      bool bHidingAllowed_;
      bool bVisible_;
      int cx_;
      int iOrder_;
      LVCOLUMN* pLVColumn_;
   };
   typedef std::vector< COLUMN_DATA* > COLUMN_VECTOR;

   struct ITEM_DATA
   {
      ITEM_DATA(): lParam_(0){}
      ~ITEM_DATA();

      LPARAM lParam_;   // user data
      DString strKey_;  // this will be the IFDS Key String
      int iInsert_;   // insertion index
      std::vector< LVITEM* > apLVItem_;   // LVITEM entries - one for each column

      static int s_iInsert_;
   };

   static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
   static int CALLBACK insertionOrderCompare( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );

   void createSortIcons();
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
   LVCOLUMN* dupLVColumn(LVCOLUMN* pLVColumn) const;
   LVITEM* dupLVItem(LVITEM* pLVItem) const;
   int getLabelWidth(CDC* pDC, LVITEM* pItem, LONG nMaxWidth) const;
   LVITEM* getLVItem(int nItem, int nSubItem = 0) const;
public:
   int getLogicalIndex(int nPhysicalColumn) const;
private:
   int getLogicalOrder(int nPhysicalOrder) const;
   int getPhysicalIndex(int iColumn ) const;
   int getPhysicalOrder(int nColumnOrder) const;
   bool getRealSubItemRect(int iItem, int iSubItem, int nArea,
                           CRect& ref);
   bool getStateIconRect(int nItem, LPRECT pRect);
   int indexToOrder(int nIndex);
   void invalidateNonItemArea();
   void justifyFirstColumn(int nFormat);

   BOOL OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
   BOOL OnCommand(WPARAM wParam);
   void OnContextMenu(CWnd* pWnd);
   void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
   LRESULT OnDeleteAllItems();
   LRESULT OnDeleteColumn(WPARAM wParam);
   LRESULT OnDeleteItem(WPARAM wParam);
   void OnDestroy();
   BOOL OnEraseBkgnd(CDC* pDC);
   LRESULT OnFindItem(WPARAM wParam, LPARAM lParam);  
   LRESULT OnGetColumn(WPARAM wParam, LPARAM lParam);
   LRESULT OnGetColumnWidth(WPARAM wParam);
   LRESULT OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam);
   BOOL OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
   LRESULT OnGetItem(LPARAM lParam);
   LRESULT OnGetItemText(WPARAM wParam, LPARAM lParam);
   int OnHitTest(LPARAM lParam);
   void OnHScroll();
   LRESULT OnInsertColumn(WPARAM wParam, LPARAM lParam);
   LRESULT OnInsertItem(LPARAM lParam);
   void OnKeyDown(UINT nChar);
   void OnKeyUp(UINT nChar);
   void OnKillFocus();
   void OnLButtonDblClk(CPoint point);
   void OnLButtonDown(CPoint point);
   void OnLButtonUp();
   void OnMouseMove(CPoint point) ;
   BOOL OnNotify(LPARAM lParam);
   LRESULT OnSetBkColor();
   LRESULT OnSetColumn(WPARAM wParam, LPARAM lParam);
   LRESULT OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam);
   LRESULT OnSetColumnWidth(WPARAM wParam, LPARAM lParam);
   LRESULT OnSetExtendedStyle(WPARAM wParam, LPARAM lParam);
   void OnSetFocus();
   LRESULT OnSetImageList(WPARAM wParam, LPARAM lParam);
   LRESULT OnSetItem(LPARAM lParam);
   LRESULT OnSetItemText(WPARAM wParam, LPARAM lParam);
   LRESULT OnSortItems(WPARAM wParam, LPARAM lParam);
   void OnSysColorChange();
   int orderToIndex(int nOrder);
   void prepareHotUnderlining();
   void setHotCursor(const CPoint& point);
   void setSortIcon();

   static VISUAL_STYLE s_visualStyle_;
   static const int s_nFirstColXOff_;
   static const int s_nNextColXOff_;
   int nIconXOff_; // offset of icon may vary of unknown reason
   IFDSListCtrlHelper* pListCtrl_;

   COLUMN_VECTOR aColumnData_;
   bool bHasErrorIcon_;
   int nColumnHidingAllowed_;
   bool bSortIconEnabled_;       // show/hide the Up/Down bitmaps in the column header
   bool bInsertionSort_;         // true if sorting is done by insertion index
   bool bColorSortColumn_;       // different background colour for sort column
   CImageList imglstSortIcons_;  
   CBitmap* pBmpUpArrow_;          // Up Arrow bitmap
   CBitmap* pBmpDownArrow_;        // Down Arrow bitmap
   int nUpArrow_;                
   int nDownArrow_;
   COLORREF rgbColSort_;        // RGB Color background for sort column
   int iSortColumn_;
   int nFormatOfSubItem0_;
   bool bKeepIconLeft_;
   bool bLocked_;
   bool bControl_;
   bool bIconXOffCalculated_;
   DWORD dwExtendedStyle_;
   int nHotItem_;
   COLORREF dwHotLite_;
   HCURSOR hcursorCustom_;
   HCURSOR hcursorArrow_;
   HCURSOR hcursorHand_;

   PFNLVCOMPARE pfnLVCompare_;
   LPARAM lParamSort_;
   bool bOnGetDispinfo_;

   CImageList *pConditionImages_;
};

/**
 * Abstract base class to extend behaviour of DSTListCtrl (!!).
 * 
 * This class is the base for the template class IFDSAdaptedListCtrl.
 * It provides a wrapper to IFDSListBase (!!!) and if that's not
 * sufficiently complicated it overrides much of the implementation
 * of DSTListCtrl to provide column sorting, column ordering, condition
 * tool tips, and improved performance.
 * 
 * @author Chris Purdye
 * @version 1.0
 * @see IFDSListBase
 * @see DSTListCtrl
 * @see IFDSAdaptedListCtrl
 */
class WIN32UIBASE_LINKAGE IFDSListCtrl: public DSTListCtrl, public IFDSListBase
{
public:
   IFDSListCtrl()
   : DSTListCtrl( NULL, I_( "" ), 0, 0, 0, true )
   , IFDSListBase()
   , pToolTip_( NULL )
   {
      pListCtrl_ = reinterpret_cast<IFDSListCtrlHelper*>(this);
   }
   IFDSListCtrl( BaseDlg* pDialog,
                 const I_CHAR* pszDialogName,
                 UINT controlID,
                 UINT parentControlID,
                 UINT flags,
                 bool bShowSelAlways,
                 bool bShowConditions )
   : DSTListCtrl( pDialog, pszDialogName, controlID, parentControlID, flags, bShowSelAlways )
   , IFDSListBase()
   , pToolTip_( NULL )
   {
      bHasErrorIcon_ = bShowConditions;
      pListCtrl_ = reinterpret_cast<IFDSListCtrlHelper*>(this);
   }
   virtual ~IFDSListCtrl();

   virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct){
      IFDSListBase::DrawItem(lpDrawItemStruct);
   }

   virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

   /**
    * Override of DSTListCtrl::Init.  This function initializes the object
    * when it is first associated with the ListView control.
    * 
    * @param pDialog Pointer to parent dialog.
    * @param idSubstitute
    *                FieldId of the field whose corresponding substitution set provides
    *                the basis for the ListView control's column headings.
    * @param idContainer
    *                ContainerID of the ListView control.
    * @param pszListName
    *                Name of the ListView.  This is used to save/restore the state of
    *                the control in the registry.
    */
   virtual void Init( BaseDlg* pDialog,
                      const BFFieldId& idSubstitute,
                      const BFContainerId& idContainer,
                      const I_CHAR* pszListName );

   IFDSListCtrl& privInit();

   /**
    * Return a reference to the BFFieldId object which has the substitution
    * set which defines the ListView control's columns.
    * 
    * @return Reference to BFFieldId object.  BF::NullFieldId if there is no
    *         Column Control Field.
    */
   virtual const BFFieldId& getColumnControlField() const { return m_idSubstitute; }

   /**
    * This function gets the key associated with a specific row.
    * 
    * @param iItem  0-based index of the item
    * 
    * @return Pointer to the key.  This will be NULL if the item index is out-of-range
    */
   const DString* getKey( int iItem ) const;

   /**
    * This function associates a key with the specified item.
    * 
    * @param iItem  0-based index of the item.
    * @param rKey   Reference to the key.
    */
   void setKey( int iItem, const DString& rKey );

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(IFDSListCtrl)
protected:
   virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
   //}}AFX_VIRTUAL

   // Generated message map functions
protected:
   //{{AFX_MSG(IFDSListCtrl)
   afx_msg void OnSysColorChange();
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnKillFocus(CWnd* pNewWnd);
   afx_msg void OnSetFocus(CWnd* pOldWnd);
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnDestroy();
   afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
   //}}AFX_MSG
   afx_msg BOOL    OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void    OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg LRESULT OnDeleteAllItems(WPARAM, LPARAM);
   afx_msg LRESULT OnDeleteColumn(WPARAM wParam, LPARAM);
   afx_msg LRESULT OnDeleteItem(WPARAM wParam, LPARAM);
   afx_msg LRESULT OnFindItem(WPARAM wParam, LPARAM lParam);  
   afx_msg LRESULT OnGetColumn(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnGetColumnWidth(WPARAM wParam, LPARAM);
   afx_msg BOOL    OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg LRESULT OnGetExtendedStyle(WPARAM, LPARAM);
   afx_msg LRESULT OnGetItem(WPARAM, LPARAM lParam);
   afx_msg LRESULT OnGetItemText(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnHitTest(WPARAM, LPARAM lParam);
   afx_msg LRESULT OnInsertColumn(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnInsertItem(WPARAM, LPARAM lParam);
   afx_msg LRESULT OnMouseLeave(WPARAM a=0, LPARAM b=0L);
   afx_msg LRESULT OnSetBkColor(WPARAM, LPARAM);
   afx_msg LRESULT OnSetColumn(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnSetColumnWidth(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnSetExtendedStyle(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnSetImageList(WPARAM wParam, LPARAM);
   afx_msg LRESULT OnSetItem(WPARAM, LPARAM lParam);
   afx_msg LRESULT OnSetItemText(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnSortItems(WPARAM wParam, LPARAM lParam);

   DECLARE_MESSAGE_MAP()

   /**
    * Attach existing Conditions to the specified item.  This will associate
    * a Condition icon to the row.
    * 
    * @param iItem  0-based index of item
    */
   void attachConditionToItem( int iItem );

   /*==========================================================================
    *------------------------ DSTListCtrl-related stuff -----------------------
    *==========================================================================*/
public:
   /**
    * This function loads associated data rows for the list.
    * 
    * @param pKey   Key to set as selection, NULL = first row
    */
   virtual void PopulateList( const DString* pKey );
   virtual void PopulateListType( const DString* pKey );

   /**
     * This function refreshes all list items from the container
     */
   virtual void RefreshAllItems();

   /**
     * This function refreshes the list item and controls associated with the item
     * @param bReregisterObservers - specify if we want to re-register the observers or not
     */
   virtual void RefreshCurrentItem(bool bReregisterObservers = false);

   /**
     * This function resets the associated list item back to the original data and
     * then refreshes the list item display and controls associated with the
     * item.
     */
   virtual void ResetCurrentItem();

   /**
    * This method is not used by IFDSListCtrl.  Use the prepareColumns
    * method of the Adapter class to modify the columns.
    * 
    * @param idSubstitute
    * @param nFormat
    * @param nWidth
    * 
    * @see IFDSListCtrlAdapterBase#prepareColumns IFDSListCtrlAdapterBase::prepareColumns
    * @deprecated Not required in IFDSListCtrl.  This function is an artifact of DSTListCtrl
    *             and will be removed once all DSTListCtrl classes are migrated to
    *             IFDSListCtrl.
    */
   virtual void SetColumnHeadings( const BFFieldId &idSubstitute, int nFormat = LVCFMT_LEFT, int nWidth = -1) { assert( false ); }

   virtual int NewItem( DWORD ItemData );

   virtual SEVERITY AddRow();     // Add item to list

   /**
    * Set selection state of the specified row
    * 
    * @param pKey     Key of row.
    * @param bSelect  true if row should be selected.
    * @param bVisible true if row should be made visible.
    */
   void SetSelection( const DString *pKey,
                      bool bSelect = true,
                      bool bVisible = true );

   /**
    * Set selection state of the specified row
    * 
    * @param iItem    0-based index of row
    * @param bSelect  true if row should be selected.
    * @param bVisible true if row should be made visible.
    */
   void SetSelection( int iItem,           
                      bool bSelect = true, 
                      bool bVisible = true );

   /**
    * Set selection state of the specified row, if the row is not find
    * calls the next available batch of data.
    * 
    * @param pKey     Key of row.
    * @param bSelect  true if row should be selected.
    * @param bVisible true if row should be made visible.
    */
   SEVERITY SetSelectionWithSearch( const DString *pKey,
                                    bool bSelect = true,
                                    bool bVisible = true );
   int GetNextSelection( int iIitem = -1 ) const;

   /**
    * This member function is not used by IFDSListCtrl.  Use IFDSListBase::setSortColumn instead.
    * 
    * @param nCol
    * @param pCaller
    * @param idList
    * @param idField
    * @param iSortOrder
    * @param wFlags
    * 
    * @return 
    * @see IFDSListBase#setSortColumn IFDSListBase::setSortColumn
    * @deprecated Not required in IFDSListCtrl.  This function is an artifact of DSTListCtrl
    *             and will be removed once all DSTListCtrl classes are migrated to
    *             IFDSListCtrl.
    */
   virtual int SetSortColumn( int nCol,
                      const GenericInterface *pCaller,
                      const BFContainerId& idList,
                      const BFFieldId &idField,
                      int iSortOrder = SORT_ASCENDING,
                      WORD wFlags = NOT_SPECIFIED ) { assert( false ); return( 0 ); }


   /*==========================================================================
    *---------------- Functions that are similar to BaseControl ---------------
    *==========================================================================*/

   /**
    * This function sets the connected state.
    * 
    * @param bFlag  true = connected, get properties & setup
    *               false = disconnected, disable control for user input
    * @param bShowHideBasedOnConnection
    *               true = use the connection state to
    *               show/hide list, false = don't affect visibility
    */
   virtual void ConnectToData( bool bFlag, bool bShowHideBasedOnConnection = false );

   /**
    * Get the key of the currently selected item
    * 
    * @return A const reference to the key of the currently selected item.
    */
   virtual const DString& GetCurrentKey() const;

protected:
   int getItemNo( const DString* pKey ) const;

   virtual void UpdateItem( int iItem );

   static const DString s_strEmpty_;

public:
   //  Tooltip display (DSTMsg) interface
   bool IsToolTipVisible();
   void MouseLeave();
   void ToggleToolTip();
   void HideToolTip();
   bool ToolTipExists() const { return(pToolTip_ != NULL); }
   void TriggerToolTip( int iItem );
   DSTMsg* GetToolTip();
   CWnd* GetWindow();

   SEVERITY getItemConditions( int iItem, CONDITIONVECTOR& rvConditions ) const;

   void ClearErrorState();
   void ShowToolTip( int iItem );

private:
   CONDITIONVECTOR vConditions_;
   DSTMsg* pToolTip_;
};

template< class _LCA >
class IFDSAdaptedListCtrl : public IFDSListCtrl
{
private:
   // Will generate Compile Error C2027 if _LCA is not derived from IFDSListCtrlAdapterBase
   BOOST_STATIC_ASSERT( ( ::boost::is_convertible< _LCA*, IFDSListCtrlAdapterBase* >::value ) );
public:

   IFDSAdaptedListCtrl()
   : IFDSListCtrl()
   {}

   IFDSAdaptedListCtrl( BaseDlg* pDialog,
                        const I_CHAR* pszDialogName,
                        UINT idControl,
                        UINT idParentControl,
                        UINT flags,
                        bool bShowSelAlways,
                        bool bShowConditions )
   : IFDSListCtrl( pDialog, pszDialogName, idControl, idParentControl, flags, bShowSelAlways, bShowConditions )
   {}

   virtual ~IFDSAdaptedListCtrl() {}

public:
   virtual IFDSListCtrlAdapterBase* getAdapter() { return &adapter_; }

   virtual bool SortOnColumn( int nCol )
   {
      setSortColumn( nCol );
      SortListCtrl();
      return( true );

   }
   virtual void SortListCtrl()
   {
      SortItems( adapter_.compareFunc, reinterpret_cast< DWORD >( this ) );
   }


private:
   _LCA adapter_;
};
