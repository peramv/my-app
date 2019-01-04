#ifndef CBOINSTANCEFIELDINFO_HPP
#define CBOINSTANCEFIELDINFO_HPP

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999 by DST Systems, Inc.
 */

/**@pkg DICBOCORE */    


#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef INSTANCEFIELDINFO_HPP
#include "instancefieldinfo.hpp"
#endif

/**@#-*/
using namespace std;
/**@#+*/

// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif


/**
 * This class provides management of field values, masks, and field-level
 * flags that are defined by CBOBaseImpl class.
 *
 * This class is a specialization of InstanceFieldInfo where the field-level
 * flags are established as those defined by class CBOBaseImpl. */
class CBOBASE_LINKAGE CBOInstanceFieldInfo : public InstanceFieldInfo
{
   public:
      
      /** Constructor
       * @param nField Number of fields to manage
       * @param ulGroupFlag Initial value of group bit flag */
      CBOInstanceFieldInfo( int nFields,
                            unsigned long ulGroupFlag = 0x0000 );

      /** Copy constructor */
      CBOInstanceFieldInfo( const CBOInstanceFieldInfo& copy );

      /** Destructor */
      ~CBOInstanceFieldInfo();

      /** Assignment operator */
      CBOInstanceFieldInfo& operator=( const CBOInstanceFieldInfo& copy );

   private:
      CBOInstanceFieldInfo();
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
// $Log:   Y:/VCS/iFastAWD/inc/cboinstancefieldinfo.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:14   kovacsro
//Initial revision.
// 
//    Rev 1.6   28 Nov 2001 12:41:48   dt14177
// fixed linkage define
// 
//    Rev 1.5   Jan 05 2000 07:15:26   DT29758
// Java-doc modifications
// 
//    Rev 1.3   Jan 04 2000 04:46:10   DT29758
//  
// 
//    Rev 1.2   Dec 30 1999 08:04:22   DT29758
// Modified comments to Java-Doc style
// 
//    Rev 1.1   Nov 11 1999 16:31:16   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0   Jun 21 1999 17:07:12   DT22388
//  
// 
//    Rev 1.2   Mar 17 1999 15:11:16   DT21815
// Added ccdoc comments/documentation.
// 
//    Rev 1.1   Jan 14 1999 11:47:36   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.0   29 Jul 1998 23:58:10   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.2   Mar 10 1998 14:41:00   DT21815
// Added comment header block and comment revision block.
//
//




#endif
