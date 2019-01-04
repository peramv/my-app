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

#include <commonport.h>
#include <bfproc\commandenum.h>
#include <bfdata\bfdata.hpp>
#include <map>

/**
 * Class that manages inter-process parameters and "global" data.
 *
 * Parameter data is stored and obtained by string tags.  This data is temporary
 * in nature.  Parameters should be set prior to invoking a command.  The 
 * receiving process/dialog must retrieve the parameters during the init method.
 * The base architecture will automatically clear the parameter data after the
 * completion of the init call.
 * For DSTC, this class is created by the WorkSessionProcess (for sharing data
 * among all the processes and dialogs for that WorkSession) and is readily 
 * accessable through the GenericInterface.
 * 
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 02/10/99</dd></dl>
 * @version 0.1
 */

// Import/Export resolution
#undef CLASS_LINKAGE
#ifdef BPBASE_DLL
   #define CLASS_LINKAGE CLASS_EXPORT
#else
   #define CLASS_LINKAGE CLASS_IMPORT
#endif

class CLASS_LINKAGE InterProcessData
{
// Construction
public:
   InterProcessData();
   virtual ~InterProcessData()
   {}

   /**
     * Clear all parameters.
     */
   void clearParameters();
   /**
     * Get parameter value for a given tag.
     * @param strTag - A const string reference with the tag name for the
     * parameter.
     * @param strValueOut - A string reference that will be filled with the
     * parameter value.
     */
   void getParameter( const DString &strTag, DString &strValueOut ) const;
   /**
     * Set parameter value for a given tag.
     * @param strTag - A string with the tag name for the parameter.
     * @param strValue - A string with the value to be passed.
     * @returns string with parameter value, if the tag name is not found an 
     * empy string is returned.
     */
   void setParameter( const DString &strTag, const DString &strValue );

   typedef std::map< DString, DString > ParmMap;
   const ParmMap& getParmMap() const { return mapParms_; }
protected:
private:
   ParmMap  mapParms_;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfproc/InterProcessData.hpp-arc  $
//
//   Rev 1.12   Jan 09 2008 09:20:30   purdyech
//Expose the ParmsMap so that it can be iterated.
//
//   Rev 1.11   May 14 2004 16:13:26   SMITHDAV
//Removed "global data areas" from InterProcessData" and cleaned up the related interfaces. They are now in the BFSession objects.
//
//   Rev 1.10   May 10 2004 15:08:48   SMITHDAV
//Move work-session level "global data" to the BFWorksession from InterProcessData.
 * 
 *    Rev 1.9   Nov 27 2002 15:04:46   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.8   Oct 09 2002 17:40:58   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.7   Aug 29 2002 12:51:16   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   Jun 17 2002 11:36:24   PURDYECH
 * Back parameters with a map'o'DStrings instead of a BFData object.  This ensures that a value which is set in with setParameter will not be transmogrified by formatting during the setElementValue/getElementValue logic.
 * 
 *    Rev 1.5   Jun 06 2002 17:19:04   PURDYECH
 * Removed _emptyData ... it's no longer needed.
 * 
 *    Rev 1.4   May 28 2002 12:17:22   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.3   22 Mar 2002 15:11:58   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.2   Mar 08 2000 11:39:24   DT24433
 * let creator determine datasets to use
 * 
 *    Rev 1.1   Feb 15 2000 18:55:02   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:50   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Nov 10 1999 11:48:14   DT24433
 * split USER & WORK globals
 * 
 *    Rev 1.1   Jul 08 1999 10:03:50   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
