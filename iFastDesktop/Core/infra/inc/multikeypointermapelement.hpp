#ifndef MULTIKEYPOINTERMAPELEMENT_HPP
#define MULTIKEYPOINTERMAPELEMENT_HPP

#  pragma message( "including "__FILE__ )

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

#ifndef INCLUDED_SET
#define INCLUDED_SET
   #include <set>
#endif


template <class A> class MultiKeyPointerMapElement
{

public:

   MultiKeyPointerMapElement() :
         m_pElement( 0 ),
         m_fDeleteElementOnDestruct( false )
   {
   }


   MultiKeyPointerMapElement( 
      A *pElement, bool fDeleteElementOnDestruct = false ) :
         m_pElement( pElement ),
         m_fDeleteElementOnDestruct( fDeleteElementOnDestruct )
   {
   }

   ~MultiKeyPointerMapElement()
   {
      if ( m_fDeleteElementOnDestruct )
      {
         delete m_pElement;
      }
   }


   MultiKeyPointerMapElement( const MultiKeyPointerMapElement& copy ) :
      m_pElement( copy.m_pElement ),
      m_fDeleteElementOnDestruct( copy.m_fDeleteElementOnDestruct )
   {
   }


   MultiKeyPointerMapElement& operator=( const MultiKeyPointerMapElement& copy )
   {
      m_pElement = copy.m_pElement;
      m_fDeleteElementOnDestruct = copy.m_fDeleteElementOnDestruct;
      return *this;
   }


   const MultiKeyPointerMapElement& operator==( 
      const MultiKeyPointerMapElement& comp ) const
   {
      if ( m_fDeleteElementOnDestruct !=
           comp.m_fDeleteElementOnDestruct )
      {  
         return false;
      }

      if ( m_pElement !=
           comp.m_pElement )
      {  
         return false;
      }
   }


   bool getDeleteElementOnDestruct() const
   {
      return m_fDeleteElementOnDestruct;
   }


   void setDeleteElementOnDestruct( bool fDeleteElementOnDestruct )
   {
      m_fDeleteElementOnDestruct = fDeleteElementOnDestruct;
   }


   A* getElement() const
   {
      return m_pElement;
   }


   void setElement( A* pElement )
   {
      m_pElement = pElement;
   }


private:

   bool m_fDeleteElementOnDestruct;
   A *m_pElement;

};



template <class A, class B>
void copyMultiKeyPointerMap( const A &source, A &target )
{
   target.clear();

   A::iterator iterDel = target.begin();

   std::map< B *, B * > mapPointers;

   MultiKeyPointerMapElement< B > elementAdd;

   A::const_iterator iterCopy = source.begin();

   while ( source.end() != iterCopy )
   {
      const MultiKeyPointerMapElement<B> * pElement =
         &( *iterCopy ).second;

      std::map< B *, B * >::iterator iterMap =
         mapPointers.find( pElement->getElement() );

      if ( mapPointers.end() != iterMap )
      {
         elementAdd.setDeleteElementOnDestruct( false );
         elementAdd.setElement( ( *iterMap ).second );
      }
      else
      {
         B *pInnerElement = new B( *( pElement->getElement() ) );
         mapPointers[ pElement->getElement() ] = pInnerElement;
         elementAdd.setDeleteElementOnDestruct( true );
         elementAdd.setElement( pInnerElement );
      }

      target[ ( *iterCopy ).first ] = elementAdd;

      ++iterCopy;
   }
}



#endif // MULTIKEYPOINTERMAPELEMENT_HPP



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
// $Log:   Y:/VCS/iFastAWD/inc/multikeypointermapelement.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:20   kovacsro
//Initial revision.
//
//   Rev 1.2   21 Nov 2000 16:18:56   dt14177
//more cleanup
//
//   Rev 1.1   27 Oct 2000 15:41:54   dt14177
//cleanup
//
//   Rev 1.0   Aug 24 2000 07:14:46   dtwk
// 
// 

