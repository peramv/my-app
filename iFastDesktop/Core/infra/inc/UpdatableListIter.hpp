#ifndef UPDATABLELISTITER_HPP
#define UPDATABLELISTITER_HPP

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


#ifndef UPDATABLELISTBASE_HPP
#include "updatablelistbase.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
#include "conditionmanager.hpp"
#endif

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif

// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif

/** Helper Class to iterate through and access an UpdatableList */
class CBOBASE_LINKAGE UpdatableListIter
{
public:

   // Traversal types
   enum ITERTYPE
   {
      NON_DELETED,
      NON_CHANGED,
      DELETED,
      UPDATED,
      ADDED,
      ALL
   };


   /** 
    * Get a CBOBase pointer to the current object, if available
    *
    * @returns a const pointer to a CBOBase object 
    */
   const CBOBase *getConstObject() const;

   /** 
    * Get a const Data object pointer, if available out of list
    *
    * @returns const Data object from a list 
    */
   const Data* getDataObject() const;

   /** 
    * Retrieve a DString value for the current position
    *
    * @param strField - name of field
    * @param strOut - string supplied to be filled
    * @param fFormatted - formatting flag
    * @returns SEVERITY(condition) 
    */
   SEVERITY getField(const DString &strField, DString &strOut, bool fFormatted = true) const;

   /** 
    * Overloaded operator to determine if iteration is valid
    *
    * @returns non-zero value if iteration is valid, otherwise 0 
    */
   operator int () const;

   /** 
    * Increment operator to advance the state of the iterator 
    */
   void operator++();

   /** 
    * Return a UPDLISTITER node for the current position 
    */
   UPDLIST_ITER operator()() const;

   /** Constructor */
   UpdatableListIter( UpdatableListBase &rList,  ITERTYPE type=ALL);

   /** Destructor */
   ~UpdatableListIter();

protected:

   UpdatableListBase *pList;
   UPDLIST_ITER updListIter;
   ITERTYPE iterType;

private:

   UpdatableListIter();
   UpdatableListIter( const UpdatableListIter &copy );
   UpdatableListIter& operator=( const UpdatableListIter &copy );

   void getNextMatchingPos( bool fStartIter );

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
// $Log:   Y:/VCS/iFastAWD/inc/UpdatableListIter.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:14   kovacsro
//Initial revision.
// 
//    Rev 1.6   28 Nov 2001 12:41:28   dt14177
// fixed linkage define
// 
//    Rev 1.5   Dec 27 2000 17:12:32   dt39990
// Organized methods in alphabetical listing
// 
// 
// 
//    Rev 1.4   29 Nov 2000 10:31:48   dt14177
// cleanup
// 
//    Rev 1.3   Jan 04 2000 04:46:06   DT29758
//  
// 
//    Rev 1.2   Dec 30 1999 08:04:02   DT29758
// Modified comments to Java-Doc style
// 
//    Rev 1.1   Nov 12 1999 10:01:12   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
// 
//    Rev 1.0   Jun 21 1999 17:06:42   DT22388
//  
// 
//    Rev 1.2   Jan 14 1999 15:27:22   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.1   Sep 01 1998 16:38:44   djoo
// Renamed getObject to getConstObject. Also changed
// return type to const CBOBase *.
// 
//    Rev 1.0   Sep 01 1998 11:00:46   DTWK
//  
//
#endif // UPDATABLELISTITER_HPP
