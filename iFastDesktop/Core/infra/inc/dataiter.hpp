#ifndef DATAITER_HPP
#define DATAITER_HPP

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

/**@pkg DIDBRKR */ 

#pragma message( "including "__FILE__ )

#ifndef DATA_HPP
   #include "data.hpp"
#endif

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

class DIDBRKR_LINKAGE DataIter
{
public:

   /**
    * Constructor for DataIter objects.
    * 
    * 
    * @param inData - (in) Data object to iterate over
    * @param includeAppendedElements - (in) if false, then DataElements added
    *        by the addElement or setElementValue functions will not be
    *        iterated through.  Defaults to true.
    *
    */
   DataIter( const Data &inData, bool includeAppendedElements = true );

   ~DataIter();

   /**
    * Increments the iterator to the next element
    * 
    */
   void operator++();

   /**
    * Returns the id of the current element
    * 
    * @return element id
    * @exception ConditionException& DIDBRKR_COMPONENT_NOT_FOUND - If the
    *            iterator has gone past the last element.
    *
    */
   unsigned long operator()() const;

   /**
    * Returns an integer representation of the currently pointed to
    * DataElement.
    * 
    * @return Returns a positive integer if the iterator is pointing to a
    *         element object.  Returns zero if the iterator is past the
    *         last object.
    *
    */
   operator int () const;

   /**
    * Resets the iterator to point to the first DataElement.
    * 
    */
   void reset();

private:
   const Data &dataRef;
   int vectorIndex;
   int componentCount;
   bool includeAppended;
   Data::FieldNameMap::iterator mapIter;

   DataIter( const DataIter & );
   DataIter& operator=( const DataIter & );
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
// $Log:   Y:/VCS/iFastAWD/inc/dataiter.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:54   kovacsro
//Initial revision.
// 
//    Rev 1.4   Mar 02 2001 14:11:34   dt24433
// Changed to return element ids instead of DataElement references.  DataElement
// references are no longer available for property based elements because of memory/performance improvements.
// 

#endif