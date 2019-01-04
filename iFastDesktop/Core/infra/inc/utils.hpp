#ifndef UTILS_HPP
#define UTILS_HPP

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/**@pkg DICBOCORE */

#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef INCLUDED_LIST
#include <list>
#define INCLUDED_LIST
#endif

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif

#ifndef  INCLUDED_TIME_H
#include <time.h>
#define  INCLUDED_TIME_H
#endif

/**@#-*/
class Data;
class Frame;

typedef std::list<DString> str_list;
typedef str_list::const_iterator str_list_iter;
/**@#+*/


// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * extracts "words" from the text string and
 * puts them in the list
 * 
 * a "word" is contiguous characters which do
 * not contain the separators
 * 
 * @param text       - the string to parse into words
 * @param words      - (out) the list of words
 * @param separators - a string containing characters specified as
 *                   separators
 * @return 
 */
void CBOBASE_LINKAGE split( const DString & text,
                            str_list & words,
                          const DString & separators = I_(" ") );

/**
 * Returns system date in the form YYYYMMDD.
 * 
 * @param sDate  - (out) the system date
 * @return 
 */
void CBOBASE_LINKAGE getSystemDate( DString & sDate );

/**
 * Moves data from a file into a data object
 * 
 * @param strFileName
 *               - (in) the file which has the data
 * @param data   - (out) the recipient of data from the file
 * @return 
 */
bool CBOBASE_LINKAGE dataFromFile( const DStringA & strFileName,
                                   Data & data );

/**
 * Moves data from a file into a data object including
 *   the PB251 header
 * 
 * NOTE:
 *   The repeat count is no longer reliable because a view may
 * have more than 999 repeats
 * 
 * @param strFileName
 *               - (in) the file which has the data
 * @param data   - (out) the recipient of data from the file
 * @return 
 */
bool CBOBASE_LINKAGE readDataFromFile( 
                                    const DStringA & strFileName,
                                    Data & data );

/**
 * Moves data from a file into a data object including
 *   the PB251 header
 *
 * NOTE:
 *   The repeat count is no longer reliable because a view may
 * have more than 999 repeats
 * 
 * @param strFileName
 *               - (out) the file which is to receive the data
 * @param data   - (in) the object which has the data
 * @return 
 */
bool CBOBASE_LINKAGE writeDataToFile( 
                                    const DStringA & strFileName,
                                    const Data & data );

/**
 * Dumps all conditions from a Frame to cout
 * 
 * @param pFrame
 * @return 
 */
void CBOBASE_LINKAGE dumpConditions( Frame * pFrame);

/**
 * Class Dump is used to express a Data object in text format
 */
class CBOBASE_LINKAGE Dump
{
   public:

      /**
       * Constructor
       * 
       * @param strFileName
       * @param bUseIDIFormat
       *               - IDI format is of the form: TAG=VALUE;
       * @param bUseCounter
       */
      Dump( const DString & strFileName,
            bool bUseIDIFormat = true,
            bool bUseCounter = false );

      /**
       * Destructor
       */
      virtual ~Dump();

      /**
       * Dumps the data object to a file
       * 
       * @param viewData
       * @param nCount
       */
      void dumpToFile( const Data &viewData,
                       int nCount = 0 );

      /**
       * Dumps the string to a file
       * 
       * @param strOut
       * @param nCount
       */
      void dumpToFile( const DString& strOut,
                       int nCount = 0 );
      
      /**
       * Dumps the data object to the console
       * 
       * @param viewData
       */
      void dumpToConsole( const Data &viewData ); 


      /**
       * Dumps a string to the console
       * 
       * @param strOut
       */
      void dumpToConsole( const DString& strOut ); 


   private: // unimplemented methods

      Dump();
  
      Dump( const Dump &copy );
      const Dump &operator=( const Dump &copy );

   private: // attributes

      DString _strFileName;
      bool _bUseCounter;
      bool _bUseIDIFormat;

};

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
// $Log:   Y:/VCS/iFastAWD/inc/utils.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:18   kovacsro
//Initial revision.
// 
//    Rev 1.6   28 Nov 2001 12:42:28   dt14177
// fixed linkage define
// 
//    Rev 1.5   29 Nov 2000 14:12:56   dt14177
// fixed std:: namespace compile problems
// 
//    Rev 1.4   29 Nov 2000 12:03:34   dt14177
// cleanup

#endif // UTILS_HPP