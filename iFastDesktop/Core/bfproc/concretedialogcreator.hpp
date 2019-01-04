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
class BaseMainDlg;


/**
 * Function object class which instantiates a new 
 * BaseMainDlg-derived class of type _C
 * 
 * @author Chris Purdye
 * @version 1.0
 */
template< class _C > 
struct dialogCreatorFunc
{
   GenericInterface* operator()( GenericInterfaceContainer* pGIC, 
                                 GenericInterface* pGIParent,
                                 const Command& rCommand ) const {
      return( new _C( NULL, pGIC, pGIParent, rCommand ) );
   }
};

/**
 * Factory class to create instances of BaseMainDlg-derived
 * class _BMD.  Uses the function object class _C to actually
 * create the object
 * 
 * @author Chris Purdye
 * @version 1.0
 */
template< class _BMD, class _C = dialogCreatorFunc< _BMD > >
class ConcreteDialogCreator : public AbstractProcessCreator
{
private:
   // Will generate Compile Error C2027 if _BMD is not derived from BaseMainDlg
   BOOST_STATIC_ASSERT( ( ::boost::is_convertible< _BMD*, BaseMainDlg* >::value ) );
public:
   ConcreteDialogCreator( const DString& name ) 
   : AbstractProcessCreator( name )
   { BFProcessFactory::getInstance().registerCreator( this );}
   ~ConcreteDialogCreator() 
   {}

   virtual GenericInterface* create( GenericInterfaceContainer* pGIC, 
                                     GenericInterface* pGIParent,
                                     const Command& rCommand ) const 
   { 
      return(_C()( pGIC, pGIParent, rCommand ) );
   }
};




//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfproc/concretedialogcreator.hpp-arc  $
//
//   Rev 1.4   Jan 14 2003 11:04:16   PURDYECH
//DataGroupid parentage knowledge
//
//   Rev 1.3   Jan 06 2003 16:43:36   PURDYECH
//BFDataGroupId and BFContainerId changeover
//
//   Rev 1.2   Oct 09 2002 17:40:54   PURDYECH
//New PVCS Database
//
//   Rev 1.1   22 May 2002 18:08:52   PURDYECH
//BFData Implementation
//
