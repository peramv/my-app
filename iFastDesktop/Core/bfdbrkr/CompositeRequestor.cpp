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
// ^FILE   :  HostRequestor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <srcprag.h>
#include "compositerequestor.hpp"
#include "bfrequest.hpp"
#include <assert.h>


//******************************************************************************
CompositeRequestor::CompositeRequestor()
: _count(0),
_elements(NULL)
{
}

//******************************************************************************
CompositeRequestor::CompositeRequestor(const CompositeRequestor &copy)
: _count(0),
_elements(NULL)
{
   _count = copy._count;
   _elements = new BFRequestor*[_count];

   for( int i=0; i<_count; i++ )
      _elements[i] = copy._elements[i]->clone();

}

//******************************************************************************
CompositeRequestor::~CompositeRequestor()
{
   for( int i=0; i < _count; i++ )
      delete _elements[i];

   delete _elements;
}

//******************************************************************************
SEVERITY 
CompositeRequestor::receive( const BFRequest &request, BFData &queryData, BFData &receivedData, bool *outMoreAvailable /*= NULL*/ )
{

   for( int i=0; i < _count; i++ )
      _elements[i]->receive(request, queryData, receivedData, outMoreAvailable );

   return(NO_SEVERITY);
}

int 
CompositeRequestor::getCompositeCount() const
{
   return(_count);
}

BFRequestor **
CompositeRequestor::getCompositeElements() const 
{
   return(_elements);
}


CompositeRequestor operator+(const BFRequestor &requestor1, const BFRequestor &requestor2)
{
   const CompositeRequestor *inComposite1 = NULL;
   const CompositeRequestor *inComposite2 = NULL;

   int count = 0;
   if( typeid(requestor1) == typeid(CompositeRequestor) )
   {
      inComposite1 = dynamic_cast<const CompositeRequestor *>(&requestor1);
      count += inComposite1->_count;
   }
   else
      count++;

   if( typeid(requestor2) == typeid(CompositeRequestor) )
   {
      inComposite2 = dynamic_cast<const CompositeRequestor *>(&requestor2);
      count += inComposite2->_count;
   }
   else
      count++;

   CompositeRequestor composite;

   composite._count = count;
   composite._elements = new BFRequestor*[count];

   int i=0;
   if( inComposite1 )
   {
      for( int j=0; j < inComposite1->_count; j++ )
      {
         composite._elements[i] = inComposite1->_elements[j]->clone();
         i++;
      }
   }
   else
   {
      composite._elements[i] = requestor1.clone();
      i++;
   }

   if( inComposite2 )
   {
      for( int j=0; j < inComposite2->_count; j++ )
      {
         composite._elements[i] = inComposite2->_elements[j]->clone();
         i++;
      }
   }
   else
   {
      composite._elements[i] = requestor2.clone();
      i++;
   }

   return(composite);

}
