/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/** @pkg DITABUSCORE */

// %NO_GEN%

#ifndef NAMEIMPL_HPP
#define NAMEIMPL_HPP

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
   #include <string>
#endif

#ifndef CBOINSTANCEFIELDINFO_HPP
   #include "cboinstancefieldinfo.hpp"
#endif

#ifndef CBOBASEIMPL_HPP
   #include "cbobaseimpl.hpp"
#endif

// %BEGIN_INTERFACE%
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

// %END_INTERFACE%


//forward declares

//defines for identifying subclasses using substitution at compile time
#undef  $ParentImplClass$
#define $ParentImplClass$  CBOBaseImpl

#undef  $ImplClass$
#define $ImplClass$  NameImpl

// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

/**
 * Maintain data set by LegalOwner and parse registration lines
 */

class DITABUSCORE_LINKAGE NameImpl : public CBOBaseImpl
{
   public:
      // %BEGIN_INTERFACE%
      enum FIELD { UNUSED,
                   MAX_FIELDS };

      enum OBJECT
      {
         UNUSED_OBJECT,
         MAX_OBJECTS
      };


      /**
       * Constructor
       * 
       * You will need to call the init() method
       * in order to set the defaults.
       */
      NameImpl();

      /**
       * Copy constructor
       * 
       * @param copy
       */
      NameImpl( const NameImpl &copy );

      /**
       * Destructor
       */
      ~NameImpl();

      /**
       * Assignment operator
       * 
       * @param copy
       * @return 
       */
      NameImpl & operator=( const NameImpl &copy );

      /**
       * Initialization method
       * 
       * @param maxLineCount -
       *               Maximum number of address lines
       * @param maxLineLength -
       *               Maximum number of characters in an address
       *               line
       * @return Maximum severity
       */
      SEVERITY init( int maxLineCount = 5, 
                     int maxLineLength = 35 );

      /**
       * move a copy of the indicated address line
       * to the return area indicated
       * 
       * @param nIndex - this indicates which line to return
       * @param strTextLine
       *               - this indicates where to put the copy of
       *                 the address line
       * @return 
       */
      bool getLine( int nIndex, DString & strTextLine ) const;

      /**
       * This indicates the number of address lines
       * which contains text (0==none)
       * 
       * @return The index of the last line containing text
       */
      virtual int getNumCurrentLines( void ) const;

      /**
       * Getter for maxNumLines
       * 
       * @return 
       */
      int getNumMaxLines( void ) const;

      /**
       * Getter for maxLineLength
       * 
       * @return 
       */
      int getMaxLineLength() const;

      /**
       * Assigns the text to the address line
       * indicated by the index
       * 
       * @param nLineNum - the index of the line to receive the
       *                   copy
       * @param strTextLine - the text to copy
       * @return 
       */
      bool setLine( int nLineNum, const DString& strTextLine );

      /**
       * Equality operator
       * 
       * @param rhs
       * @return 
       */
      virtual bool operator==( const NameImpl &rhs ) const;

      /**
       * Setter for maxNumLines
       * 
       * @param num
       * @return 
       */
      virtual bool setNumMaxLines( int num );
      // %END_INTERFACE%



   // private methods
   private:
      int  _makeLinesContiguous( void );
      void _setLineCount( void );


   // private data
   private:
      int       _nMaxLineCount;
      int       _nCurrentLineCount;
      int       _nMaxLineLength;
      DString   *_pNameLines;


      //include common declarations
      #include "common_impl_hpp.hpp"
};

#endif

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/inc/nameimpl.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:24   kovacsro
//Initial revision.
// 
//    Rev 1.2   30 Oct 2000 10:56:36   dt14177
// cleanup
// 
//    Rev 1.1   Nov 11 1999 16:32:36   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0.1.2   Sep 02 1999 17:41:42   DT22388
// Fixed code in the operator==() method
// so that an assert would not be fired
// in the getLine() method. And performed
// some code clean up.
// 
//    Rev 1.0.1.1   Jul 22 1999 13:36:02   DT22388
// Performed code clean-up and added #undefs
// for the substitution string i.e. $strParentImplClass$.
// Also, added #includes for test classes.
// 
// 
//    Rev 1.0.1.0   Jul 12 1999 18:38:24   DT22388
// added new method setNumMaxLines()
// 
//    Rev 1.0   Jun 21 1999 16:44:40   DT22388
//  

