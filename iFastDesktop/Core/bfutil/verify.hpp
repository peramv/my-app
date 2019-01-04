#pragma once

#include <string>
#include <map>
#include <list>
#include <sstream>
#include <assert.h>

#include <condition.hpp>

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

namespace bfutil
{
   /**
    * Define a version number for a library.  The Major, Minor and Revision 
    * number can be specified.  The object can be constructed from three
    * integer values, or from a string with a user-defined format.
    * 
    * @author Chris Purdye
    * @version 1.1
    */
   class LibraryVersion
   {
   public:
      LibraryVersion() 
      : strVersion_( I_( "" ) )
      , verMajor_( 0 )
      , verMinor_( 0 )
      , verRevision_( -1 )
      , verSupplementary_( -1 )
      {}
      /**
       * Construct this LibraryVersion object with a user-defined version
       * string.  This allows the programmer to specify <i>any</i> string
       * as a legitimate version string.
       * 
       * @param pszVersion Pointer to a NULL terminated UNICODE string which contains a
       *                   version string.
       */
      LibraryVersion( const I_CHAR* pszVersion ) 
      : strVersion_( pszVersion )
      , verMajor_( 0 )
      , verMinor_( 0 )
      , verRevision_( -1 )
      , verSupplementary_( -1 )
      {}
      /**
       * Construct this LibraryVersion object with a Major Version Number,
       * a Minor Version Number, a Revision Number, and an optional
       * Supplementary Number.
       * 
       * @param verMajor Major Version Number
       * @param verMinor Minor Version Number within Major Version
       * @param verRevision
       *                 Revision Number within Minor Version.
       * @param verSupplementary
       *                 Supplementary Version number.  This is only displayed if the revision number 
       *                 has a value non-negative value.
       */
      LibraryVersion( unsigned int verMajor, unsigned int verMinor, int verRevision, int verSupplementary = -1 )
      : strVersion_( I_( "" ) )
      , verMajor_( verMajor )
      , verMinor_( verMinor )
      , verRevision_( verRevision )
      , verSupplementary_( verSupplementary )
      {}
      ~LibraryVersion() {}

      /**
       * Check to see if this LibraryVersion object is equal to another one.
       * 
       * There are some considerations when determining equality.  
       * <ol>
       * <li>If <i>either</i> object has a user-defined version string then 
       * both objects must have the same user-defined version string.
       * <li>If <i>neither</i> object has a user-defined version string then
       * the Major, Minor, Revision, and Supplementary numbers must be equal.
       * </ol>
       * 
       * @param rhs    Other LibraryVersion object
       * 
       * @return true if they are equal.
       */
      bool operator==( const LibraryVersion& rhs ) const
      {
         if( strVersion_.length() != 0 || rhs.strVersion_.length() != 0 ) {
            return( strVersion_ == rhs.strVersion_ );
         } else {
            if( verMajor_ == rhs.verMajor_ &&
                verMinor_ == rhs.verMinor_ &&
                verRevision_ == rhs.verRevision_ &&
                verSupplementary_ == rhs.verSupplementary_ ) {
               return( true );
            }
         }
         return( false );
      }

      bool operator!=( const LibraryVersion& rhs )  const
      {
         return( !(*this == rhs ) );
      }

      /**
       * Return a version string.  If a user-defined version string has been
       * defined, either through construction or by called setVersion() then
       * the user-defined version string is returned.  Otherwise a string
       * in the format "Major.Minor.Revision.Supplementary" will be returned.
       * 
       * Note that if Revision was not specified (i.e. is negative) then
       * neither the Revision <i>nor</i> the Supplementary Number will be 
       * included.  If only the Supplementary Number was not specified then
       * only the Supplementary Number will be excluded from the version string.
       * 
       * @return A I_STRING object containing the version string.
       */
      I_STRING getVersionString() const {
         if( strVersion_.length() == 0 ) {
            i_stringstream iss;
            iss << verMajor_ << I_( "." ) << verMinor_;
            if( 0 <= verRevision_ ) {
               iss << I_( "." ) << verRevision_;
               if( 0<= verSupplementary_ ) {
                  iss << I_( "." ) << verSupplementary_;
               }
            }
            return( iss.str() );
         }
         return( strVersion_ );
      }

      const I_STRING& getVersion() const { return strVersion_; }
      int getMajorVersion() const { return verMajor_; }
      int getMinorVersion() const { return verMinor_; }
      int getRevision() const { return verRevision_; }
      int getSupplementary() const { return verSupplementary_; }

      void setVersion( const I_CHAR* pszVersion ) { strVersion_ = pszVersion; }
      void setMajorVersion( unsigned int verMajor ) { verMajor_ = verMajor; }
      void setMinorVersion( unsigned int verMinor ) { verMinor_ = verMinor; }
      void setRevision( int verRevision ) { verRevision_ = verRevision; }
      void setSupplementary( int verSupplementary ) { verSupplementary_ = verSupplementary; }

   private:
      I_STRING strVersion_;
      unsigned int verMajor_;
      unsigned int verMinor_;
      int verRevision_;
      int verSupplementary_;
   };

   /**
    * This object associates a library name with a list of condition files
    * and a LibraryVersion object.
    * 
    * @author Chris Purdye
    * @version 1.1
    */
   class BFUTIL_LINKAGE LibraryInfo
   {
   public:
      LibraryInfo()
      : strName_( I_( "" ) )
      , ver_()
      {}
      LibraryInfo( const I_STRING& strName )
      : strName_( strName )
      , ver_()
      {}
      ~LibraryInfo();

      struct ConditionInfo
      {
         I_STRING strFile_;
         unsigned int iCondition_;
      };

      typedef std::list< struct ConditionInfo > CONDITION_FILES;
      typedef CONDITION_FILES::iterator CONDITION_FILES_ITER;
      typedef CONDITION_FILES::const_iterator CONDITION_FILES_CONST_ITER;

      const I_STRING& getName() const { return strName_; }

      const LibraryVersion& getVersion() const { return ver_; }
      void setVersion( const I_CHAR* pszVersion ) { ver_.setVersion( pszVersion ); }
      void setVersion( unsigned int verMajor, unsigned int verMinor ) { 
         ver_.setMajorVersion( verMajor ); 
         ver_.setMinorVersion( verMinor ); 
         ver_.setRevision( -1 ); 
         ver_.setSupplementary( -1 );
      }
      void setVersion( unsigned int verMajor, unsigned int verMinor, int verRevision, int verSupplementary = -1 )  {
         ver_.setMajorVersion( verMajor ); 
         ver_.setMinorVersion( verMinor ); 
         ver_.setRevision( verRevision ); 
         ver_.setSupplementary( verSupplementary );
      }

      void addConditionFile( const I_STRING& strConditionFile, unsigned int iCondition )
      {
         struct ConditionInfo ci;
         ci.strFile_ = strConditionFile;
         ci.iCondition_ = iCondition;
         listConditionFiles_.push_back( ci );
      }

      const CONDITION_FILES& getConditionFiles() const { return listConditionFiles_; }

   private:
      const I_STRING strName_;
      LibraryVersion ver_;
      CONDITION_FILES listConditionFiles_;
   };

   class LibraryVerifier;
   extern BFUTIL_LINKAGE LibraryVerifier& getLibraryVerifier();

   /**
    * Singleton object which tracks all Core, Shared Application, and Client
    * Application libraries, condition files, and version numbers.  This
    * object allows the libraries and condition files to have their version
    * numbers verified.
    * 
    * @author Chris Purdye
    * @version 1.1
    */
   class BFUTIL_LINKAGE LibraryVerifier
   {
   public:
      virtual ~LibraryVerifier();

      enum Category { core, app_shared, app_client };

      void registerLibrary( enum Category eCat, const I_CHAR* pszLibrary, const I_CHAR* pszVersion );
      void registerLibrary( enum Category eCat, const I_CHAR* pszLibrary, int verMajor, int verMinor, int verRevision );
      void addConditionFile( enum Category eCat, const I_CHAR* pszLibrary, const I_CHAR* pszConditionFile, unsigned int iCondition );

      bool verify( enum Category eCat, const LibraryVersion& lv ) const;

      typedef std::map< const I_STRING, LibraryInfo* > LIBRARYMAP;
      typedef LIBRARYMAP::iterator LIBRARYMAP_ITER;
      typedef LIBRARYMAP::const_iterator LIBRARYMAP_CONST_ITER;

   private:
      friend LibraryVerifier& bfutil::getLibraryVerifier();

      LibraryVerifier();

      LIBRARYMAP mapLibrariesCore_;
      LIBRARYMAP mapLibrariesAppShared_;
      LIBRARYMAP mapLibrariesAppClient_;

      LIBRARYMAP& getMap( enum Category eCat ) {
         if( core == eCat ) { return mapLibrariesCore_; }
         else if( app_shared == eCat ) { return mapLibrariesAppShared_; }
         else if( app_client == eCat ) { return mapLibrariesAppClient_; }
         assert( 0 );
         throw;
      }

      const LIBRARYMAP& getMap( enum Category eCat ) const {
         if( core == eCat ) { return mapLibrariesCore_; }
         else if( app_shared == eCat ) { return mapLibrariesAppShared_; }
         else if( app_client == eCat ) { return mapLibrariesAppClient_; }
         assert( 0 );
         throw;
      }

      bool verifyDllVersions( enum Category eCat, const LibraryVersion& lv ) const;
      bool verifyConditionFiles( enum Category eCat, const LibraryVersion& lv ) const;

   };

}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/verify.hpp-arc  $
//
//   Rev 1.1   Feb 11 2004 16:51:16   PURDYECH
//Added supplementary version number
//
//   Rev 1.0   Jan 13 2004 10:10:48   PURDYECH
//Initial revision.
//
