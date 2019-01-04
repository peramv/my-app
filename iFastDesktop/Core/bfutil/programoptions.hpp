#pragma once
#pragma warning( disable: 4786 )
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <assert.h>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif


namespace bf {
namespace opts {

   const unsigned long required     = 0x0001;   // reserved:  must be specified
   const unsigned long boolean      = 0x0002;   // boolean:  use --[no]opt or -o-
   const unsigned long multiple     = 0x0004;   // can appear more than once
   const unsigned long numeric      = 0x0008;   // has associated integer value
   const unsigned long string       = 0x0010;   // has associated string value
   const unsigned long decimal      = 0x0020;   // has associated floating point value
   const unsigned long longName     = 0x0040;   // reserved
   const unsigned long shortName    = 0x0080;   // reserved
   const unsigned long file         = 0x0100;   // has associated filename value
   const unsigned long path         = 0x0200;   // has associated path value
   const unsigned long help         = 0x0400;   // display usage information

   const unsigned long positional   = 0x0400;   // argument is positional ... how to specify?

   const unsigned long hex          = 0x0800;

   const unsigned long long_bool_no = 0x8000;

   typedef std::vector< std::string > ARG_VECTOR;
   typedef ARG_VECTOR::iterator ARG_VECTOR_ITER;
   typedef ARG_VECTOR::const_iterator ARG_VECTOR_CONST_ITER;
   
   
   class ProgramOptions;
   
   class BFUTIL_LINKAGE P_Option
   {
   public:
   
      P_Option( char chShortName, 
                const std::string& strLongName, 
                const std::string& strDesc,
                unsigned long options )
      : chShortName_( chShortName )
      , strLongName_( strLongName )
      , strDesc_( strDesc )
      , options_( options )
      {
      }
   
      static std::string s_TypeBool;
      static std::string s_TypeDecimal;
      static std::string s_TypeNumeric;
      static std::string s_TypeString;
      static std::string s_TypeFile;
      static std::string s_TypePath;
      static std::string s_TypeHelp;
      static std::string s_TypeUnknown;
   
      friend ProgramOptions;
   
      virtual ~P_Option() {}
   
      bool isBool() const { return( (options_ & bf::opts::boolean) == bf::opts::boolean ); }
      bool isRequired() const { return( ( options_ & bf::opts::required) == bf::opts::required ); }
      bool isMultiple() const { return( ( options_ & bf::opts::multiple) == bf::opts::multiple ); }
      bool isNumeric() const { return( ( options_ & bf::opts::numeric) == bf::opts::numeric); }
      bool isHex() const { return( ( options_ & bf::opts::hex) == bf::opts::hex); }
      bool isDecimal() const { return( ( options_ & bf::opts::decimal) == bf::opts::decimal); }
      bool isString() const { return( ( options_ & bf::opts::string) == bf::opts::string); }
      bool isFile() const { return( ( options_ & bf::opts::file) == bf::opts::file); }
      bool isPath() const { return( ( options_ & bf::opts::path) == bf::opts::path); }
      bool isHelp() const { return( ( options_ & bf::opts::help) == bf::opts::help); }
   
      char getShortName() const { return chShortName_; }
      const std::string& getLongName() const { return strLongName_; }
   
      const std::string& getTypeName() const {
         if( isBool() ) return( s_TypeBool );
         if( isNumeric() ) return( s_TypeNumeric );
         if( isDecimal() ) return( s_TypeDecimal );
         if( isString() ) return( s_TypeString );
         if( isFile() ) return( s_TypeFile );
         if( isPath() ) return( s_TypePath );
         if( isHelp() ) return( s_TypeHelp );
         assert(0);
         return( s_TypeUnknown );
      }
   
      bool operator==( const P_Option& rhs ) const 
      {
         if( 0x00 != chShortName_ && 
             chShortName_ == rhs.chShortName_ ) {
            return( true );
         } else if( "" != strLongName_ &&
                    strLongName_ == rhs.strLongName_ ) {
            return( true );
         } else if( 0x00 == chShortName_ &&
                    0x00 == rhs.chShortName_ &&
                    "" == strLongName_ &&
                    "" == rhs.strLongName_ ) {
            return( true );
         }
         return( false );
      }
   
      bool operator!=( const P_Option& rhs ) const 
      {
         return( !( *this == rhs ) );
      }
   
      const std::string& getDescription() const { return strDesc_; }
   
      std::string getName() const 
      {
         std::string str;
         if( "" != strLongName_ ) {
            str = strLongName_;
            if( 0x00 != chShortName_ ) {
               str += "(";
               str += chShortName_;
               str += ")";
            }
         } else {
            if( 0x00 != chShortName_ ) {
               str += chShortName_;
            }
         }
         return( str );
      }
   
   private:
      P_Option( char chShortName, 
                const std::string& strLongName,
                unsigned long options )
      : chShortName_( chShortName )
      , strLongName_( strLongName )
      , strDesc_( "" )
      , options_( options )
      {
      }
   
   
      char chShortName_;
      const std::string strLongName_;
      const std::string strDesc_;
      unsigned long options_;
   };
   
   class ProgramOptionsException
   {
   public:
      ProgramOptionsException( const P_Option* pOption,
                               const std::string& message )
      : pOption_( pOption )
      , strMessage_( message ) 
      {}
   
      const P_Option* getOption() const { return pOption_; }
      const std::string& getMessage() const { return strMessage_; }
   private:
      const P_Option* pOption_;
      const std::string strMessage_;
   };
   
   
   class BFUTIL_LINKAGE ProgramOptions
   {
   public:
      ProgramOptions( int argc, char** argv )
      : bAutoHelp_( true )
      , strEnvName_( "" )
      , strProgramName_( "" )
      , strTitle_( "" )
      , strUsage_( "[options]" )
      , cErrors_( 0 )
      {
         // convert argv to vector<string>, but skip argv[0] 'cause it's just the program name
         for( int iArg = 1; iArg < argc; ++iArg ) {
            vArgs_.push_back( argv[iArg] );
         }
   
         char szDrive[ _MAX_DRIVE ];
         char szDir[ _MAX_DIR ];
         char szFName[ _MAX_FNAME ];
         char szExt[ _MAX_EXT ];
         if( argc > 0 ) {
            _splitpath( argv[0], szDrive, szDir, szFName, szExt );
         } else {
            char szModFName[ _MAX_PATH ];
            GetModuleFileName( NULL, szModFName, sizeof( szModFName ) );
            _splitpath( szModFName, szDrive, szDir, szFName, szExt );
         }
         strProgramName_ = szFName;
         strEnvName_ = szFName;
      }
   
      ~ProgramOptions();
   
      class OptionValueBase;
   
      struct PositionalArg
      {
         std::string strName_;
         std::string strDesc_;
      };
      typedef std::vector< struct PositionalArg > POSITIONAL_ARG_LIST;
      typedef POSITIONAL_ARG_LIST::iterator POSITIONAL_ARG_LIST_ITER;
      typedef POSITIONAL_ARG_LIST::const_iterator POSITIONAL_ARG_LIST_CONST_ITER;
   
      typedef std::vector< std::string > POSITIONAL_LIST;
      typedef POSITIONAL_LIST::iterator POSITIONAL_LIST_ITER;
      typedef POSITIONAL_LIST::const_iterator POSITIONAL_LIST_CONST_ITER;
   
      typedef std::list< P_Option* > OPTION_LIST;
      typedef OPTION_LIST::iterator OPTION_LIST_ITER;
      typedef OPTION_LIST::const_iterator OPTION_LIST_CONST_ITER;
   
      typedef std::multimap< const P_Option*, const OptionValueBase* > OPTION_VALUE_MAP;
      typedef OPTION_VALUE_MAP::iterator OPTION_VALUE_MAP_ITER;
      typedef OPTION_VALUE_MAP::const_iterator OPTION_VALUE_MAP_CONST_ITER;
   
      struct FindOption {
         FindOption( const P_Option* r ) : r_( r ) {}
         bool operator()( const P_Option* p ) const
         {
            return( *p == *r_ );
         }
      private:
         const P_Option* r_;
      };
   
      const P_Option* addOption( char chShortName, 
                                 const std::string& strLongName, 
                                 const std::string& strDesc,
                                 unsigned long o )
      {
         // if option already exists then throw exception
         P_Option* pOpt = new P_Option( chShortName, strLongName, strDesc, o );
         OPTION_LIST_ITER it = std::find_if( listOptions_.begin(), listOptions_.end(), FindOption( pOpt ) );
         if( it != listOptions_.end() ) {
            throw ProgramOptionsException( pOpt, "Option " + pOpt->getName() + ": Duplicate program option definition" );
         }
   
         listOptions_.push_back( pOpt );
         return( pOpt );
      }
   
      // just used to add documentation...
      void addArgument( const std::string& strName, const std::string& strDesc )
      {
         struct PositionalArg s;
         s.strName_ = strName;
         s.strDesc_ = strDesc;
         listPositionalArgs_.push_back( s );
      }
   
      const P_Option* getOption( const std::string& strLongName ) const
      {
         if( strLongName.empty() ) {
            return NULL;
         }
   
         P_Option opt( 0x00, strLongName, 0 );
         OPTION_LIST_CONST_ITER it = std::find_if( listOptions_.begin(), listOptions_.end(), FindOption( &opt ) );
         if( listOptions_.end() != it ) {
            return( *it );
         }
         return( NULL );
      }
   
      const P_Option* getOption( char chShortName ) const
      {
         if( 0x00 == chShortName ) {
            return NULL;
         }
   
         P_Option opt( chShortName, "", 0 );
         OPTION_LIST_CONST_ITER it = std::find_if( listOptions_.begin(), listOptions_.end(), FindOption( &opt ) );
         if( listOptions_.end() != it ) {
            return( *it );
         }
         return( NULL );
      }
   
      bool isSet( char chShortName ) const;
      bool isSet( const std::string& strLongName ) const;
   
      const OptionValueBase* getValue( char chShortName ) const;
      const OptionValueBase* getValue( const std::string& strLongName ) const;
      const OptionValueBase* getValue( const P_Option* pOption ) const;

      std::string getStringValue( char chShortName ) const;
      std::string getStringValue( const std::string& strLongName ) const;
      std::string getStringValue( const P_Option* pOption ) const;

      long getNumericValue( char chShortName ) const;
      long getNumericValue( const std::string& strLongName ) const;
      long getNumericValue( const P_Option* pOption ) const;
   
      double getDecimalValue( char chShortName ) const;
      double getDecimalValue( const std::string& strLongName ) const;
      double getDecimalValue( const P_Option* pOption ) const;

      bool getBooleanValue( char chShortName ) const;
      bool getBooleanValue( const std::string& strLongName ) const;
      bool getBooleanValue( const P_Option* pOption ) const;
   
      std::vector< const OptionValueBase* > getMultiValues( char chShortName ) const;
      std::vector< const OptionValueBase* > getMultiValues( const std::string& strLongName ) const;
      std::vector< const OptionValueBase* > getMultiValues( const P_Option* pOption ) const;
   
      std::string getPositionalArgument( int iPos ) const
      {
         if( listPositional_.size() > iPos ) {
            return "";
         }
         return( listPositional_[ iPos ] );
      }
   
      class OptionValueBase
      {
      public:
         OptionValueBase( const P_Option* pOption ) 
         : pOption_( pOption )
         {}
         virtual ~OptionValueBase() {}
         const P_Option* getOption() const { return pOption_; }
      private:
         const P_Option* pOption_;
      };
   
      template< typename _T > 
      class OptionValue : public OptionValueBase
      {
      public:
         OptionValue( const _T& v, const P_Option* pOption )
         : OptionValueBase( pOption )
         , v_( v )
         {}
         ~OptionValue() {}
   
         const _T& get() const { return v_; }
      private:
         _T v_;
      };
   
      const std::string& getEnvName() const { return strEnvName_; }
      void setEnvName( const std::string& v ) { strEnvName_ = v; }
   
      const std::string& getProgramName() const { return strProgramName_; }
      void setProgramName( const std::string& v ) { strProgramName_ = v; }
   
      const std::string& getTitle() const { return strTitle_; }
      void setTitle( const std::string& v ) { strTitle_ = v; }
   
      const std::string& getUsage() const { return strUsage_; }
      void setUsage( const std::string& v ) { strUsage_ = v; }
   
      bool getAutoHelp() const { return bAutoHelp_; }
      void disableAutoHelp() { bAutoHelp_ = false; }
      void enableAutoHelp() { bAutoHelp_ = true; }
   
      bool parse();
   
      void dump() const;
   
      int getErrorCount() const { return cErrors_; }
      const std::vector< std::string >& getErrorMessages() const { return vErrors_; }
   
      virtual void shortUsage() const;
      virtual void longUsage() const;
   
   protected:
      void setOptionValue( const std::string& strLongName, const std::string& strValue );
      void setOptionValue( char chShortName, const std::string& strValue );
      void setOptionValue( const P_Option* pOption, const std::string& strValue );
   
      virtual bool validate( const P_Option* pOption, long lValue, std::string& strMessage ) const { return true; }
      virtual bool validate( const P_Option* pOption, double dValue, std::string& strMessage ) const { return true; }
      virtual bool validate( const P_Option* pOption, const std::string& strValue, std::string& strMessage ) const { return true; }
   
   private:
      ARG_VECTOR vArgs_;
   
      bool bAutoHelp_;
   
      std::string strEnvName_;
      std::string strProgramName_;
      std::string strTitle_;
      std::string strUsage_;
   
      // tracking errors...
      int cErrors_;
      std::vector< std::string > vErrors_;
   
      POSITIONAL_ARG_LIST listPositionalArgs_;
      POSITIONAL_LIST listPositional_;
      OPTION_LIST listOptions_;
      OPTION_VALUE_MAP mapValues_;
   
      bool isSet( const P_Option* pOption ) const;
   
      bool opt_process( const std::vector< std::string >& vArgs );
      int processLine( const std::string& strLine );
      bool processFile( const std::string& strFile );
   
      void addOptionError( const P_Option* pOption, const std::string& strError )
      {
         ++cErrors_;
         std::string str = "The value of option " + pOption->getName() + " is incorrect: ";
         str += strError;
         vErrors_.push_back( str );  
      }
   
      void usage() const;
   
   };

}  // namespace bf::opts
}  // namespace bf

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/programoptions.hpp-arc  $
//
//   Rev 1.0   Jan 27 2004 16:05:36   PURDYECH
//Initial revision.
//
