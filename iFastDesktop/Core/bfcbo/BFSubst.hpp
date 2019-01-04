#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif   

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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFSubst.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : January 2000
//
// ----------------------------------------------------------
//
// ^CLASS : BFSubst
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//
//******************************************************************************

#include <srcprag.h>
#include <commonport.h>
#include <map>
#include <dstring.hpp>

#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * This class does substitution list processing
 * 
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> January 19, 2000 </dd></dl>
 * @version 0.1
 */
class BFBASE_LINKAGE BFSubst
{
public:
   /**
     * constructor
     */
   BFSubst();
   /**
     * destructor
     */
   virtual ~BFSubst();
   /**
     * adds a substitution pair
     * @param dstCode  - the code
     * @param dstValue - the value
     */
   void addSubst( const DString & dstCode, const DString & dstValue );
   /**
     * adds a substitution pair
     * @param dstCode  - the code
     * @param iValue   - the value
     */
   void addSubst( const DString & dstCode, int iValue );
   /**
     * deletes a substitution pair
     * @param dstCode  - the code
     */
   void deleteSubst( const DString & dstCode );
   /**
     * gets the list
     * @param dstList - where the IDI string should be put
     */
   void getList( DString & dstList);
   /**
     * hides a pair
     * @param dstCode  - the code
     */
   void hideSubst( const DString & dstCode );
   /**
     * shows a pair
     * @param dstCode  - the code
     */
   void showSubst( const DString & dstCode );
   /**
     * clears out all the pairs
     */
   void clearSubst( );

private :
   struct SubstMapEntry
   {
      DString m_dstValue;
      bool    m_visible;
      SubstMapEntry( const DString& dstValue, bool visible):m_dstValue( dstValue ), m_visible( visible ){};
   };

   typedef std::map< DString, SubstMapEntry*, std::less< DString > >    SUBST_MAP;
   SUBST_MAP _substMap;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/BFSubst.hpp-arc  $
//
//   Rev 1.4   Oct 09 2002 17:40:10   PURDYECH
//New PVCS Database
//
//   Rev 1.3   22 Mar 2002 15:11:44   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.2   03 May 2001 14:03:26   SMITHDAV
//Session management restructuring.
//
//   Rev 1.1   Jul 21 2000 17:09:42   BUZILA
//documentation added
//
//   Rev 1.0   Apr 03 2000 08:57:50   BUZILA
//Initial revision.
 * 
 *    Rev 1.1   Feb 15 2000 18:54:56   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:44   SMITHDAV
 * Initial revision.
// 
//    Rev 1.0   Jan 19 2000 10:13:24   BUZILA
// Initial revision.
// 
//
*/
