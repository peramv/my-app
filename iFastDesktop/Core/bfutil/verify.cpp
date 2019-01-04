#include "stdafx.h"
#include <bfutil/verify.hpp>
#include <bf/log/log.hpp>
#include <conditionmanager.hpp>

namespace bfutil
{
   LibraryVerifier& getLibraryVerifier() 
   {
      static LibraryVerifier instance;
      return( instance );
   }

   LibraryVerifier::LibraryVerifier()
   {}

   LibraryVerifier::~LibraryVerifier()
   {}

   void LibraryVerifier::registerLibrary( enum Category eCat, 
                                          const I_CHAR* pszLibrary,
                                          const I_CHAR* pszVersion )
   {
      const I_STRING strLib( pszLibrary );

      LIBRARYMAP_ITER it = getMap( eCat ).find( strLib );
      if( getMap( eCat ).end() == it ) 
      {
         // it's not registered, so create a new LibraryInfo object and insert it 
         // into the map
         LibraryInfo* pLi = new LibraryInfo( strLib );
         pLi->setVersion( pszVersion );
         getMap( eCat ).insert( LIBRARYMAP::value_type( strLib, pLi ) );
      }
   }

   void LibraryVerifier::registerLibrary( enum Category eCat, 
                                          const I_CHAR* pszLibrary,
                                          int verMajor, int verMinor, int verRevision )
   {
      const I_STRING strLib( pszLibrary );

      LIBRARYMAP_ITER it = getMap( eCat ).find( strLib );
      if( getMap( eCat ).end() == it ) 
      {
         // it's not registered, so create a new LibraryInfo object and insert it 
         // into the map
         LibraryInfo* pLi = new LibraryInfo( strLib );
         pLi->setVersion( verMajor, verMinor, verRevision );
         getMap( eCat ).insert( LIBRARYMAP::value_type( strLib, pLi ) );
      }
   }

   void LibraryVerifier::addConditionFile( enum Category eCat, 
                                           const I_CHAR* pszLibrary,       // name of library
                                           const I_CHAR* pszConditionFile, // name of condition file
                                           unsigned int iCondition )
   {
      const I_STRING strLib( pszLibrary );

      LIBRARYMAP_ITER it = getMap( eCat ).find( strLib );
      if( getMap( eCat ).end() != it ) 
      {
         // it's registered, so get the LibraryInfo object create a new LibraryInfo object and insert it 
         // into the map
         LibraryInfo* pLi = (*it).second;
         pLi->addConditionFile( I_STRING( pszConditionFile ), iCondition );
      }
   }

   bool LibraryVerifier::verify( enum Category eCat, const LibraryVersion& lv ) const
   {
      // make sure that all library components are valid
      bool bRc = true;
      if( false == verifyDllVersions( eCat, lv ) ) {
         bRc = false;
      }
      if( false == verifyConditionFiles( eCat, lv ) ) {
         bRc = false;
      }
      return( bRc );
   }

   bool LibraryVerifier::verifyDllVersions( enum Category eCat, const LibraryVersion& lv ) const 
   {
      bool bRc = true;
      // go through each Dll and see if the versions are equal to the
      // specified one
      LIBRARYMAP_CONST_ITER it = getMap( eCat ).begin();
      for( ; getMap( eCat ).end() != it; ++it ) {
         const LibraryInfo* pLi = (*it).second;
         if( lv != pLi->getVersion() ) {
            bf::log::LogStream ls( bf::log::config );
            ls << I_( "Version problem:  Library " ) << (*it).first.c_str() << I_( " is " ) << pLi->getVersion().getVersionString().c_str() << I_( ", but expected " ) << lv.getVersionString().c_str() << bf::log::endlf;
            bRc = false;
         }
      }
      return( bRc );
   }

   bool LibraryVerifier::verifyConditionFiles( enum Category eCat, const LibraryVersion& lv ) const
   {
      bool bRc = true;
      // go through each dll and check all associated condition files

      I_STRING strPath = ConditionManager::getInstance()->getPath();
      strPath += I_("\\");

      LIBRARYMAP_CONST_ITER it = getMap( eCat ).begin();
      for( ; getMap( eCat ).end() != it; ++it ) {
         const LibraryInfo* pLi = (*it).second;
         const LibraryInfo::CONDITION_FILES& rCF = pLi->getConditionFiles();
         LibraryInfo::CONDITION_FILES_CONST_ITER cfIter = rCF.begin();
         for( ; rCF.end() != cfIter; ++cfIter )
         {
            // does this file exist?
            I_STRING strCndFile = strPath;
            strCndFile += (*cfIter).strFile_;
            strCndFile += I_( ".cnd" );

            if( -1 == ::GetFileAttributesW( strCndFile.c_str() ) ) {
               bf::log::LogStream ls( bf::log::config );
               ls << I_( "Version problem:  Condition File " ) << strCndFile.c_str() << I_( " can not be found." ) << bf::log::endlf;
               bRc = false;
            } else if( 0 != (*cfIter).iCondition_ ) {
               Condition c( DString( (*cfIter).strFile_ ), 
                            DString( I_( "" ) ),
                            (*cfIter).iCondition_,
                            I_("IteratedCondition"),
                            "",
                            0,
                            FALSE,
                            strPath.c_str() );
               const I_CHAR* pszMessage = c.getMessage();

               DString dstrCndVer( pszMessage );
               dstrCndVer.strip();
               DString dstrReqCndVer( lv.getVersionString().c_str() );
               dstrReqCndVer.strip();

               if( dstrCndVer != dstrReqCndVer ) {
                  bf::log::LogStream ls( bf::log::config );
                  ls << I_( "Version problem:  Condition File " ) << strCndFile.c_str() << I_( " is " );
                  ls << dstrCndVer.c_str() << I_( ", but expected " ) << dstrReqCndVer.c_str() << bf::log::endlf;
                  bRc = false;
               }
            }
         }
      }
      return( bRc );
   }
}


