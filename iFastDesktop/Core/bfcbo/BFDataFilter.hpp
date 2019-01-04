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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFDataFilter.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : April 12, 2000
//
// ^CLASS : BFDataFilter
//
//******************************************************************************

#include <bfcbo\bfabstractcbo.hpp>
#include <bfdata\bffieldid.hpp>

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif


/**
 * This class implements the data filtering inside CBOs
 * 
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> Apr 12, 2000 </dd></dl>
 * @version 0.1
 */
class BFBASE_LINKAGE BFDataFilter
{
public:
   /**
    * opcodes used in data comparation
    * <pre>
    *@@ OP_NONE              - no comparation
    *@@ OP_EQUAL             - equality comparation
    *@@ OP_LESS              - less comparation
    *@@ OP_LESS_OR_EQUAL     - less or equal comparation
    *@@ OP_GREATER           - greater comparation
    *@@ OP_GREATER_OR_EQUAL  - greater or equal comparation
    *@@ OP_NOT_EQUAL         - defferent comparation
    *@@ OP_FIND              - True if Substring Search found; use ~
    *@@ OP_NOT_FIND          - True if Substring Search not found; use !~
    * <pre>
    */
   enum OPCODES
   {
      OP_NONE,
      OP_EQUAL,
      OP_LESS,
      OP_LESS_OR_EQUAL,
      OP_GREATER,
      OP_GREATER_OR_EQUAL,
      OP_NOT_EQUAL,
      OP_FIND,
      OP_NOT_FIND
   };

   /**
    * This struct implements an atomic filtering element
    * 
    * @author Mihai Virgil Buzila
    * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> Apr 12, 2000 </dd></dl>
    * @version 0.1
    */
   struct DataFilterElement
   {
      /**
       * constructor
       */
      DataFilterElement( const BFFieldId &fieldId, OPCODES operation, const DString & fieldValue ): 
      m_fieldId( fieldId ), m_operation( operation ), m_fieldValue( fieldValue ){};

      /**
       * the field on which the filtering is based
       */
      const BFFieldId m_fieldId;
      /**
       * type of filtering
       */
      OPCODES m_operation;
      /**
       * value to be compared with
       */
      DString m_fieldValue;
   };
   /**
    * clears out the filter
    */
   void clearFilter( );

   /**
    * constructor
    */
   BFDataFilter( ){}
   /**
    * destructor
    */
   ~BFDataFilter( )
   {
      clearFilter( );
   };
   /**
    * sets the filter condition
    * 
    * @param lDataFilter
    *               here is the filter taken from
    * 
    * @return 
    */
   bool setFilter( const DString & lDataFilter );
   /**
    * determines if a CBO meets the filter condition
    * 
    * @param pObj   the CBO
    * @param idDataGroup
    *               the DataGroup of the CBO to match against
    * 
    * @return 
    */
   bool isVisible( const BFAbstractCBO * const pObj, const BFDataGroupId& idDataGroup );
   /**
    * gets the filter condition
    * 
    * @param dstFilter here is the filter stored
    */
   void getFilter( DString & dstFilter );

private:
   typedef std::vector< DataFilterElement* > DATAFILTERVECTOR;
   DATAFILTERVECTOR vect;
   bool addElement( const DString & lFilterElement);
   bool filterCompare( const DString & dstFieldValue, OPCODES lOperation, const DString & dstReferenceValue );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/BFDataFilter.hpp-arc  $
//
//   Rev 1.9   Jan 06 2003 16:40:32   PURDYECH
//BFDataGroupId changeover
//
//   Rev 1.8   Nov 27 2002 15:18:02   PURDYECH
//Documentation Changes
//
//   Rev 1.7   Oct 09 2002 17:40:02   PURDYECH
//New PVCS Database
//
//   Rev 1.6   Sep 07 2002 13:31:06   PURDYECH
//Was storing a reference to the field id instead of a copy
//
//   Rev 1.5   Aug 29 2002 12:51:14   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   Feb 25 2002 18:52:24   PURDYECH
//Phase 1 of BFData Rollout - Base Component Compatibility
//
//   Rev 1.3   03 May 2001 14:03:20   SMITHDAV
//Session management restructuring.
//
//   Rev 1.2   Jul 24 2000 09:33:48   HERNANDO
//Added Find and Not Find filter operations.  Use ~ and !~
//
//   Rev 1.1   Jul 21 2000 17:09:38   BUZILA
//documentation added
//
//   Rev 1.0   Apr 13 2000 10:34:56   BUZILA
//Initial revision.
 * 
 */


