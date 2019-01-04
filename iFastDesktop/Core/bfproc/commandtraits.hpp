#pragma once

#include <map>
#include <dstring.hpp>
#include <bfproc\commandenum.h>

#pragma warning( disable: 4275 )

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

class CommandTraits;

class BPBASE_LINKAGE CommandTraitsMap : public std::map< DString, const CommandTraits* > 
{
public:
   static CommandTraitsMap& getInstance();
   void add( const CommandTraits* traits );
   const CommandTraits* get( const DString& name );

private:
   CommandTraitsMap() {}
   CommandTraitsMap( const CommandTraitsMap& rhs );
};

class BPBASE_LINKAGE CommandTraits
{
public:
   CommandTraits()
   : command_( I_( "" ) )
   , webPageName_ ( I_( "" ) )
   {}
   CommandTraits(
                const DString& command,
                int commandType,
                int maxPerUserSession,
                int maxPerWorkSession,
                E_MODETYPE eAllowedModes,
                const DString& webPageName = I_( "" ),
                int windowHeight = -1,	// used only for browser based dialogs
                int windowWidth  = -1   // used only for browser based dialogs
                )
   : command_( command )
   , commandType_( commandType )
   , maxPerUserSession_( maxPerUserSession )
   , maxPerWorkSession_( maxPerWorkSession )
   , eAllowedModes_( eAllowedModes )
   , webPageName_ ( webPageName )
   , windowHeight_( windowHeight )
   , windowWidth_( windowWidth )
   {
      CommandTraitsMap::getInstance().add( this );
   }

   const DString& getName() const { return(command_);}
   const DString& getWebPageName() const { return(webPageName_);}
   int getType() const { return(commandType_);}
   int getMaxPerUserSession() const { return(maxPerUserSession_);}
   int getMaxPerWorkSession() const { return(maxPerWorkSession_);}
   E_MODETYPE getModes() const { return(eAllowedModes_);}
   int getWindowHeight() const { return windowHeight_; }
   int getWindowWidth() const { return windowWidth_; }

private:
   DString     command_;
   DString     webPageName_;
   int         commandType_;
   int         maxPerUserSession_;
   int         maxPerWorkSession_;
   E_MODETYPE  eAllowedModes_;
   int		   windowHeight_;	
   int		   windowWidth_;	
};
