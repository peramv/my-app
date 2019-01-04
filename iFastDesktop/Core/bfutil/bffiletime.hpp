#pragma once

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

/**
 * Simple wrapper around the Win32 FILETIME struct.  The primary purpose
 * of this class is to allow us to determine the number of days between
 * two filetime objects.
 * 
 * @author Chris Purdye
 * @see FILETIME
 */
class BFUTIL_LINKAGE BFFileTime
{
public:
   /**
    * Constructor.  This will default the FILETIME struct to 0.
    */
   BFFileTime()
   {
      ft_.dwHighDateTime = 0;
      ft_.dwLowDateTime = 0;
   }
   /**
    * Constructor.
    * 
    * @param ft     Populate this BFFileTime object from a FILETIME struct.
    */
   BFFileTime( const FILETIME& ft )
   {
      ft_.dwHighDateTime = ft.dwHighDateTime;
      ft_.dwLowDateTime = ft.dwLowDateTime;
   }
   /**
    * Constructor.
    * 
    * @param l      A filetime value represented as a 64 bit integer.
    */
   BFFileTime( LONGLONG l )
   {
      memcpy( &ft_, &l, sizeof(ft_) );
   }

   /**
    * Copy constructor.
    * 
    * @param rhs    The BFFileTime object to copy from.
    */
   BFFileTime( const BFFileTime& rhs )
   {
      *this = rhs;
   }

   /**
    * Assignment operator.
    * 
    * @param rhs    The BFFileTime object to assign from.
    * 
    * @return This BFFileTime object.  The object will have the same value as the 
    *         rhs BFFileTime object.
    */
   inline BFFileTime& operator=( const BFFileTime& rhs )
   {
      if( this != &rhs )
      {
         memcpy( &ft_, &rhs.ft_, sizeof( ft_ ) );
      }
      return( *this );
   }

   /**
    * Return a pointer to the underlying FILETIME struct.
    * 
    * @return A pointer to the underlying FILETIME struct.
    */
   inline operator FILETIME*()
   {
      return(&ft_);
   }

   /**
    * Return a 64 bit integer representation of this BFFileTime object.
    * 
    * @return A 64 bit integer representation of this BFFileTime object.
    */
   inline operator LONGLONG() const
   {
      LONGLONG li;
      memcpy( &li, &ft_, sizeof(ft_) );
      return( li );
   }

   inline const BFFileTime operator-=( const BFFileTime& rhs )
   {
      LONGLONG liLHS = *this;
      LONGLONG liRHS = rhs;
      return( BFFileTime( liLHS - liRHS ) );
   }

   friend LONGLONG operator-( const BFFileTime& lhs, const BFFileTime& rhs );


private:
   FILETIME ft_;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/bffiletime.hpp-arc  $
//
//   Rev 1.2   Apr 16 2003 09:43:58   PURDYECH
//Doxygen documentation standard
//
//   Rev 1.1   Oct 09 2002 17:41:12   PURDYECH
//New PVCS Database
//
//   Rev 1.0   22 May 2002 16:30:36   PURDYECH
//Initial revision.
//
