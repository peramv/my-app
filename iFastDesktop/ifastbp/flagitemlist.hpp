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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FlagItemList.hpp
// ^AUTHOR : Paul Dardeau
// ^DATE   : 06/18/1997
//
// ^CLASS  : FlagItemList
// ^PARENT : 
//
// ^CLASS DESCRIPTION :
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
// ----------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
//******************************************************************************

#ifndef COMMONPORT_H     
   #include <CommonPort.h>
///#endif

// Import/Export resolution
   #undef BFBASE_LINKAGE
   #ifdef BFBASE_DLL
      #define BFBASE_LINKAGE CLASS_EXPORT
   #else
      #define BFBASE_LINKAGE CLASS_IMPORT
///#endif

class BFBASE_LINKAGE FlagItemList
{
   // Public Methods
public:
   FlagItemList( int nFlags = 0,
                 int nItems = 0,
                 unsigned long ulGroupFlag = 0x0000 );
   FlagItemList( const FlagItemList& copy );
   ~FlagItemList();

   FlagItemList& operator=( const FlagItemList& copy );


   // methods for field-level flags
   bool isFlagSet( int nFlag, int nItem ) const;

   bool setFlag( int nFlag, int nItem );

   bool clearFlag( int nFlag, int nItem );


   // methods for group-level flags
   bool isGroupFlagSet( unsigned long ulGroupFlag ) const;

   bool setGroupFlag( unsigned long ulGroupFlag );

   bool clearGroupFlag( unsigned long ulGroupFlag );

   void getGroupFlag( unsigned long &ulGroupFlag );


   // Private Data
private:
   int                   _nFlags;           // How many bit flags
   int                   _nItems;           // How many items
   int                   _nItemFlagBytes;   // # bytes req'd for a item's flags
   int                   _nFlagBytes;       // # bytes req'd in total
   unsigned char  *      _pFlags;           // Pointer to buffer of flags
   unsigned long         _ulGroupFlag;      // Group bit flags
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   D:/scc/ifds/ifast/archives/ifastbp/flagitemlist.hpp-arc  $
 * 
 *    Rev 1.3   Oct 09 2002 23:53:14   PURDYECH
 * PVCS Database Conversion
* 
*    Rev 1.2   22 May 2002 18:21:02   PURDYECH
* BFData Implementation
* 
*    Rev 1.1   19 Mar 2002 13:17:04   PURDYECH
* Use #pragma once as include guard
* Remove compile time "including..." message
* 
*    Rev 1.0   Feb 15 2000 10:59:08   SMITHDAV
* Initial revision.
* 
*    Rev 1.0   Jul 07 1999 13:47:12   SMITHDAV
* Original revision.
// 
//    Rev 1.0   29 Jul 1998 23:58:26   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.5   Apr 10 1998 10:00:12   djoo
// Modified redundant include guard for 
// string.
// 
//    Rev 1.4   Mar 10 1998 13:05:44   DT21815
// Removed static array of bit masks (moved into source).
// Added header comment block and revision comment block.
//
//



///#endif

