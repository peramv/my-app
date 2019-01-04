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
//    Copyright 2002 by International Financial Data Services (Canada), Inc.
//
//******************************************************************************

#include <bfproc\bfprocessfactory.hpp>
#include <bfproc\abstractprocesscreator.hpp>
#include <dstring.hpp>

#include <boost\type_traits.hpp>
#include <boost\static_assert.hpp>

class GenericInterface;
class AbstractProcess;

/**
 * Function object class which instantiates a new 
 * AbstractProcess-derived class of type _C
 * 
 * @author Chris Purdye
 * @version 1.0
 */
template<class _C>
struct processCreatorFunc
{
   GenericInterface* operator()( GenericInterfaceContainer* pGIC, 
                                 GenericInterface* pGIParent,
                                 const Command& rCommand ) const {
      return( new _C( pGIC, pGIParent, rCommand ) );
   }
};

/**
 * Factory class to create instances of AbstractProcess-derived
 * class _AP.  Uses the function object class _C to actually
 * create the object
 * 
 * @author Chris Purdye
 * @version 1.0
 */
template< class _AP, class _C = processCreatorFunc<_AP> >
class ConcreteProcessCreator : public AbstractProcessCreator
{
private:
   // Will generate Compile Error C2027 if _AP is not derived from AbstractProcess
   BOOST_STATIC_ASSERT( ( ::boost::is_convertible< _AP*, AbstractProcess* >::value ) );
public:
   ConcreteProcessCreator( const DString& name ) 
   : AbstractProcessCreator( name )
   { BFProcessFactory::getInstance().registerCreator( this );}
   ~ConcreteProcessCreator() 
   {}

   GenericInterface* create( GenericInterfaceContainer* pGIC, 
                             GenericInterface* pGIParent,
                             const Command& rCommand ) const { return(_C()( pGIC, pGIParent, rCommand ));}
};



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfproc/concreteprocesscreator.hpp-arc  $
//
//   Rev 1.3   Jan 14 2003 11:04:18   PURDYECH
//DataGroupid parentage knowledge
//
//   Rev 1.2   Oct 09 2002 17:40:56   PURDYECH
//New PVCS Database
//
//   Rev 1.1   22 May 2002 18:08:52   PURDYECH
//BFData Implementation
//
