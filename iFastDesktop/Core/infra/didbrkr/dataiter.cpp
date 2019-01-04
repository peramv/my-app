#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef DIDBRKR_H
   #include "didbrkr.h"
#endif 

#ifndef DATAITER_HPP
   #include "dataiter.hpp"
#endif   

#ifndef CONDITIONMANAGER_HPP
   #include "ConditionManager.hpp"
#endif 

#ifndef DATAPROPERTIES_HPP
   #include "dataproperties.hpp"
#endif

#ifndef DATAELEMENTPROPERTIES_HPP
   #include "dataelementproperties.hpp"
#endif


DataIter::DataIter( const Data &inData, bool includeAppendedElements )
 : vectorIndex( 0 ), componentCount( 0 ),
   dataRef( inData )
{
   includeAppended = includeAppendedElements;
   if ( dataRef.getProperties() )
   {
      componentCount = static_cast< const DataProperties * >
         ( dataRef.getProperties() )->getPropertyCount();
   }
   reset();
}


DataIter::~DataIter()
{
}


void DataIter::reset()
{
   const DataProperties *rpDP = dataRef.getDataProperties();

   vectorIndex = 0;
   // Make sure we start sitting on an element
   while ( vectorIndex < componentCount )
   {  // try to get from properties
      const DataComponentProperties &rpDCP = rpDP->getProperty( vectorIndex );
      if ( DataComponentProperties::eDEP == rpDCP.getType() )
      {  // We have an element
         break;
      }
      vectorIndex++;
   }

   if ( dataRef._fieldNameMap )
   {
      mapIter = dataRef._fieldNameMap->begin();
   }
}


void DataIter::operator++()
{
   const DataProperties *rpDP = dataRef.getDataProperties();

   while ( ++vectorIndex < componentCount )
   {  // try to get from properties
      const DataComponentProperties &rpDCP = rpDP->getProperty( vectorIndex );
      if ( DataComponentProperties::eDEP == rpDCP.getType() )
      {  // We have an element
         return;
      }
   }

   if ( includeAppended && dataRef._fieldNameMap )
   {
      if ( mapIter != dataRef._fieldNameMap->end() )
      {
         mapIter++;
      }
   }
}


unsigned long DataIter::operator()() const
{
   if ( vectorIndex < componentCount )
   {  // Get id from property
      return dataRef.getDataProperties()->getProperty( vectorIndex ).getId();
   }
   else if ( includeAppended && dataRef._fieldNameMap && 
      ( mapIter != dataRef._fieldNameMap->end() ) )
   {
      return ( *mapIter ).second;
   }

   DString msg( I_( "comp=") );
   DString myName( I_( "iterator out of range" ) );
   msg += myName;
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
                     I_("DataElement &DataIter::operator()()"),
                     DIDBRKR_COMPONENT_NOT_FOUND, msg.c_str() );
}


DataIter::operator int () const
{
   if ( vectorIndex < componentCount )
   {
      return 1;
   }
   else if ( includeAppended && dataRef._fieldNameMap &&
             ( mapIter != dataRef._fieldNameMap->end() ))
   {
      return 1;
   }
   else
   {
      return 0;
   }
}


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
// $Log:   Y:/VCS/iFastAWD/didbrkr/dataiter.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:24   kovacsro
// Initial revision.
// 
//    Rev 1.7   Mar 02 2001 14:12:10   dt24433
// Changed to return element ids instead of DataElement references.  DataElement
// references are no longer available for property based elements because of memory/performance improvements.
// 
