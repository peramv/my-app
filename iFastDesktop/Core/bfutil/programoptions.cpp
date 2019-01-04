#include "stdafx.h"
#include <bfutil/programoptions.hpp>
#include <iostream>
#include <fstream>
#include <assert.h>

#include <string.h>

namespace bf {
namespace opts {

   std::string P_Option::s_TypeBool("Boolean");
   std::string P_Option::s_TypeDecimal("Decimal");
   std::string P_Option::s_TypeNumeric("Number");
   std::string P_Option::s_TypeString("String");
   std::string P_Option::s_TypeFile("File");
   std::string P_Option::s_TypePath("Path");
   std::string P_Option::s_TypeHelp("Help");
   std::string P_Option::s_TypeUnknown("Unknown");
   
   static ARG_VECTOR line2argv( const std::string& );
   static bool break_word( bool, char );
   
   ProgramOptions::~ProgramOptions()
   {
      OPTION_LIST_ITER itOpt = listOptions_.begin();
      for ( ; listOptions_.end() != itOpt; ++itOpt ) {
         delete( (*itOpt) );
      }
   
      OPTION_VALUE_MAP_ITER itValue = mapValues_.begin();
      for ( ; mapValues_.end() != itValue; ++itValue ) {
         delete( (*itValue).second );
      }
   }
   
   bool ProgramOptions::isSet( char chShortName ) const
   {
      const P_Option* pOption = getOption( chShortName );
      if ( NULL == pOption ) {
         return( false );
      }
      return( isSet( pOption ) );
   }
   
   bool ProgramOptions::isSet( const std::string& strLongName ) const
   {
      const P_Option* pOption = getOption( strLongName );
      if ( NULL == pOption ) {
         return( false );
      }
      return( isSet( pOption ) );
   }
   
   bool ProgramOptions::isSet( const P_Option* pOption ) const
   {
      OPTION_VALUE_MAP_CONST_ITER it = mapValues_.find( pOption );
      if ( mapValues_.end() != it ) {
         return( true );
      }
      return( false );
   }
   
   const ProgramOptions::OptionValueBase* 
   ProgramOptions::getValue( char chShortName ) const
   {
      const P_Option* pOption = getOption( chShortName );
      if ( NULL == pOption ) {
         std::string s = "Option ";
         s += chShortName;
         s += " is not valid.";
         throw ProgramOptionsException( NULL, s );
      }
      return( getValue( pOption ) );
   }
   
   const ProgramOptions::OptionValueBase* 
   ProgramOptions::getValue( const std::string& strLongName ) const
   {
      const P_Option* pOption = getOption( strLongName );
      if ( NULL == pOption ) {
         throw ProgramOptionsException( NULL, "Option " + strLongName + " is not valid." );
      }
      return( getValue( pOption ) );
   }
   
   const ProgramOptions::OptionValueBase* 
   ProgramOptions::getValue( const P_Option* pOption ) const 
   {
      if ( NULL == pOption ) {
         throw ProgramOptionsException( NULL, "incorrect call to ProgramOptions::getValue()" );
      }
      if ( pOption->isMultiple() ) {
         throw ProgramOptionsException( pOption, "scalar value requested for option, but option is array" );
      }
   
      OPTION_VALUE_MAP_CONST_ITER it = mapValues_.find( pOption );
      if ( mapValues_.end() != it ) {
         return( (*it).second );
      }
      return( NULL );
   }

   std::string ProgramOptions::getStringValue( char chShortName ) const
   {
      const P_Option* pOption = getOption( chShortName );
      if( NULL == pOption ) {
         std::string s = "Option "; s+= chShortName; s+=" is not valid.";
         throw ProgramOptionsException( NULL, s );
      }
      return( getStringValue( pOption ) );
   }
   std::string ProgramOptions::getStringValue( const std::string& strLongName ) const
   {
      const P_Option* pOption = getOption( strLongName );
      if( NULL == pOption ) {
         throw ProgramOptionsException( NULL, "Option " + strLongName + " is not valid." );
      }
      return( getStringValue( pOption ) );
   }
   std::string ProgramOptions::getStringValue( const P_Option* pOption ) const
   {
      return( dynamic_cast< const ProgramOptions::OptionValue<std::string> * >(getValue(pOption))->get() );
   }

   long ProgramOptions::getNumericValue( char chShortName ) const
   {
      const P_Option* pOption = getOption( chShortName );
      if( NULL == pOption ) {
         std::string s = "Option "; s+= chShortName; s+=" is not valid.";
         throw ProgramOptionsException( NULL, s );
      }
      return( getNumericValue( pOption ) );
   }
   long ProgramOptions::getNumericValue( const std::string& strLongName ) const
   {
      const P_Option* pOption = getOption( strLongName );
      if( NULL == pOption ) {
         throw ProgramOptionsException( NULL, "Option " + strLongName + " is not valid." );
      }
      return( getNumericValue( pOption ) );
   }
   long ProgramOptions::getNumericValue( const P_Option* pOption ) const
   {
      return( dynamic_cast< const ProgramOptions::OptionValue<long> * >(getValue(pOption))->get() );
   }

   double ProgramOptions::getDecimalValue( char chShortName ) const
   {
      const P_Option* pOption = getOption( chShortName );
      if( NULL == pOption ) {
         std::string s = "Option "; s+= chShortName; s+=" is not valid.";
         throw ProgramOptionsException( NULL, s );
      }
      return( getDecimalValue( pOption ) );
   }
   double ProgramOptions::getDecimalValue( const std::string& strLongName ) const
   {
      const P_Option* pOption = getOption( strLongName );
      if( NULL == pOption ) {
         throw ProgramOptionsException( NULL, "Option " + strLongName + " is not valid." );
      }
      return( getDecimalValue( pOption ) );
   }
   double ProgramOptions::getDecimalValue( const P_Option* pOption ) const
   {
      return( dynamic_cast< const ProgramOptions::OptionValue<double> * >(getValue(pOption))->get() );
   }

   bool ProgramOptions::getBooleanValue( char chShortName ) const
   {
      const P_Option* pOption = getOption( chShortName );
      if( NULL == pOption ) {
         std::string s = "Option "; s+= chShortName; s+=" is not valid.";
         throw ProgramOptionsException( NULL, s );
      }
      return( getBooleanValue( pOption ) );
   }
   bool ProgramOptions::getBooleanValue( const std::string& strLongName ) const
   {
      const P_Option* pOption = getOption( strLongName );
      if( NULL == pOption ) {
         throw ProgramOptionsException( NULL, "Option " + strLongName + " is not valid." );
      }
      return( getBooleanValue( pOption ) );
   }
   bool ProgramOptions::getBooleanValue( const P_Option* pOption ) const
   {
      return( dynamic_cast< const ProgramOptions::OptionValue<bool> * >(getValue(pOption))->get() );
   }

   
   
   std::vector< const ProgramOptions::OptionValueBase* >
   ProgramOptions::getMultiValues( char chShortName ) const
   {
      const P_Option* pOption = getOption( chShortName );
      if ( NULL == pOption ) {
         std::string s = "Option ";
         s += chShortName;
         s += " is not valid.";
         throw ProgramOptionsException( NULL, s );
      }
      return( getMultiValues( pOption ) );
   }
   
   std::vector< const ProgramOptions::OptionValueBase* >
   ProgramOptions::getMultiValues( const std::string& strLongName ) const
   {
      const P_Option* pOption = getOption( strLongName );
      if ( NULL == pOption ) {
         throw ProgramOptionsException( NULL, "Option " + strLongName + " is not valid." );
      }
      return( getMultiValues( pOption ) );
   }
   
   std::vector< const ProgramOptions::OptionValueBase* >
   ProgramOptions::getMultiValues( const P_Option* pOption ) const 
   {
      std::vector< const ProgramOptions::OptionValueBase* > vValues;
      if ( NULL == pOption ) {
         throw ProgramOptionsException( NULL, "incorrect call to ProgramOptions::getMultiValues()" );
      }
      if ( !pOption->isMultiple() ) {
         throw ProgramOptionsException( pOption, "multiple values requested but option is scalar" );
      }
   
      OPTION_VALUE_MAP_CONST_ITER it = mapValues_.lower_bound( pOption );
      OPTION_VALUE_MAP_CONST_ITER itEnd = mapValues_.upper_bound( pOption );
      for ( ; itEnd != it; ++it ) {
         vValues.push_back( (*it).second );
      }
      return( vValues );
   }
   
   bool ProgramOptions::parse() 
   {
      if( true == bAutoHelp_ ) {
         // if the --help option hasn't been set, then add it...
         const P_Option* pOption = getOption( "help" );
         if( NULL == pOption ) {
            addOption( 0x00, "help", "this help", bf::opts::help );
         }
      }
   
      // check environment variable for values
      if ( !strEnvName_.empty() ) {
         char  *s;
         s = getenv( strEnvName_.c_str() );
         if ( s != NULL ) {
            processLine( s );
         }
      }
   
      // parse the command line
      return( opt_process( vArgs_ ) );
   }
   
   void ProgramOptions::setOptionValue( const std::string& strLongName, const std::string& strValue )
   {
      const P_Option* pOption = getOption( strLongName );
      if ( NULL == pOption ) {
         // might be a boolean option with 'no' prepended
         if ( strLongName.size() > 2 &&
              'n' == strLongName[0] &&
              'o' == strLongName[1] ) {
            pOption = getOption( strLongName.substr( 2 ) );
            if ( NULL != pOption ) {
               if ( pOption->isBool() ) {
                  setOptionValue( pOption, "-" );
                  return;
               }
               throw ProgramOptionsException( pOption, "Option " + strLongName.substr(2) + " is not boolean:  can't specify \"no\"" );
            }
         }
         throw ProgramOptionsException( NULL, "Option " + strLongName + " is not valid." );
      }
      setOptionValue( pOption, strValue );
   }
   
   void ProgramOptions::setOptionValue( char chShortName, const std::string& strValue )
   {
      const P_Option* pOption = getOption( chShortName );
      if ( NULL == pOption ) {
         std::string s = "Option ";
         s += chShortName;
         s += " is not valid.";
         throw ProgramOptionsException( NULL, s );
      }
      setOptionValue( getOption( chShortName ), strValue );
   }
   
   void ProgramOptions::setOptionValue( const P_Option* pOption, const std::string& strValue )
   {
      if ( NULL == pOption ) {
         // add an error message!
         throw ProgramOptionsException( NULL, "incorrect call to ProgramOptions::setOptionValue()" );
      } else {
         OptionValueBase* pV = NULL;
         std::string strMessage;
   
         if ( pOption->isBool() ) {
            if ( "-" == strValue ) {
               pV = new OptionValue<bool>( false, pOption );
            } else {
               pV= new OptionValue<bool>( true, pOption );
            }
         } else if ( pOption->isNumeric() ) {
            char* pEnd = NULL;
            long l = strtol( strValue.c_str(), &pEnd, pOption->isHex() ? 16 : 10 );
            if ( validate( pOption, l, strMessage  ) ) {
               pV= new OptionValue<long>( l, pOption ); 
            } else {
               addOptionError( pOption, strMessage );
            }
         } else if ( pOption->isDecimal() ) {
            double d = atof( strValue.c_str() );
            if ( validate( pOption, d, strMessage ) ) {
               pV= new OptionValue<double>( d, pOption ); 
            } else {
               addOptionError( pOption, strMessage );
            }
         } else if ( pOption->isString() ) {
            if ( validate( pOption, strValue, strMessage ) ) {
               pV= new OptionValue<std::string>( strValue, pOption ); 
            } else {
               addOptionError( pOption, strMessage );
            }
         } else if ( pOption->isFile() ) {
            if ( validate( pOption, strValue, strMessage ) ) {
               pV= new OptionValue<std::string>( strValue, pOption ); 
            } else {
               addOptionError( pOption, strMessage );
            }
         } else if ( pOption->isPath() ) {
            if ( validate( pOption, strValue, strMessage ) ) {
               pV= new OptionValue<std::string>( strValue, pOption ); 
            } else {
               addOptionError( pOption, strMessage );
            }
         } else {
            // error in definition of option
            assert( 0 );
         }
   
         if ( NULL != pV ) {
            if ( pOption->isMultiple() ) {
               mapValues_.insert( OPTION_VALUE_MAP::value_type( pOption, pV ) );
            } else {
               OPTION_VALUE_MAP_ITER it = mapValues_.find( pOption );
               if ( mapValues_.end() != it ) {
                  delete( (*it).second );
                  mapValues_.erase( it );
               }
               mapValues_.insert( OPTION_VALUE_MAP::value_type( pOption, pV ) );
            }
         }
      }
   }
   
   
   const char s_chDelim = '-';
   const char s_chFile = '@';
   const char s_chAltDelim = '/';
   
   bool ProgramOptions::opt_process( const ARG_VECTOR& vArgs )
   {
      enum {
         none, positional, short_option, long_option
      } eType = none;
   
      char chShortName = 0x00;
      std::string strLongName;
      std::string value;
   
      int iArg = 0;
      int iC = 0;
   
      // Loop through the options in the argument vector
      ARG_VECTOR_CONST_ITER itArgs = vArgs.begin();
      for ( ; vArgs.end() != itArgs; ++itArgs, iC = 0 ) {
         const std::string& strArg = (*itArgs);
         char c = strArg[ iC++ ];
   
         if ( positional == eType ) {
            // this argument is positional
            listPositional_.push_back( strArg );
            eType = none;
            continue;
         } else if ( long_option == eType ) {
            // last option was long ... this must be a value
            setOptionValue( strLongName, strArg );
            strLongName = "";
            value = "";
            eType = none;
            continue;
         } else if ( short_option == eType ) {
            setOptionValue( chShortName, strArg );
            chShortName = 0x00;
            value = "";
            eType = none;
            continue;
         }
   
         switch ( c ) {
            case s_chFile:
               processFile( strArg.substr( iC ) );
               break;
            case s_chDelim:
               if ( s_chDelim == strArg[iC] ) {
                  ++iC;
                  eType = long_option;
   
                  // get the name of the long option
                  strLongName = strArg.substr(iC);
                  if ( "" == strLongName ) {
                     // long argument is just --, which means that
                     // the next argument is positional.
                     // used if a positional argument starts with - or --
                     eType = positional;  
                     continue;
                  } else {
                     int iPos = strLongName.find( '=' );
                     if ( strLongName.npos != iPos ) {
                        value = strLongName.substr( iPos + 1 );
                        strLongName = strLongName.substr( 0, iPos );
   
                        const P_Option* pOption = getOption( strLongName );
                        if( NULL != pOption && pOption->isHelp() ) {
                           longUsage();
                           return( false );
                        }
   
                        setOptionValue( strLongName, value );
                        eType = none;
                     } else {
                        const P_Option* pOption = getOption( strLongName );
                        if ( NULL == pOption &&
                             strLongName.size() > 2 ) {
                           pOption = getOption( strLongName.substr( 2 ) );
                           if ( NULL != pOption &&
                                pOption->isBool() ) {
                              setOptionValue( pOption, "-" );
                              eType = none;
                           } else {
                              // error!
                           }
                        } else if( NULL == pOption ) {
                           // error!
                        } else if ( pOption->isBool() ) {
                           setOptionValue( pOption, "" );
                           eType = none;
                        } else if( pOption->isHelp() ) {
                           longUsage();
                           return( false );
                        }
                     }
                  }
               } else {
                  // short options are tricky...
                  // either they are a concatenation of boolean options,
                  // or they are a single option with a qualifier
                  // or they are a single option with the qualifier next
   
                  for ( ; 0x00 != strArg[iC]; ++iC ) {
                     eType = short_option;
                     chShortName = strArg[iC];
   
                     const P_Option* pOption = getOption( chShortName );
                     if ( NULL == pOption ) {
                        // no such option ... error
                     } else {
                        if ( pOption->isBool() ) {
                           // peek ahead ... if next char is '-' then turn option off
                           if ( s_chDelim == strArg[iC + 1] ) {
                              setOptionValue( chShortName, "-" );
                              ++iC;
                           } else {
                              if( '+' == strArg[iC + 1] ) {
                                 // option is in the -o+ form, so must skip past the plus sign
                                 ++iC;
                              }
                              setOptionValue( chShortName, "" );
                           }
                           eType = none;
                        } else {
                           // not a boolean option.  peek ahead to see if there is an argument
                           if ( 0x00 != strArg[iC + 1] ) {
                              setOptionValue( chShortName, std::string( &( strArg[iC + 1] ) ) );
                              eType = none;
                              break;
                           }
                        }
                     }
                  }
               }
               break;
            default:
               eType = none;
               listPositional_.push_back( strArg );
               break;
         }
      }
      return( true );
   }/*opt_process*/
   
   void ProgramOptions::dump() const
   {
      // dump argv
      ARG_VECTOR_CONST_ITER itArgs = vArgs_.begin();
      for ( ; vArgs_.end() != itArgs; ++itArgs ) {
         std::cout << (*itArgs).c_str() << std::endl;
      }
      std::cout << std::endl;
   
   
      // display allowable options:
      std::cout << "Allowable options:" << std::endl;
      OPTION_LIST_CONST_ITER itOpt = listOptions_.begin();
      for ( ; listOptions_.end() != itOpt; ++itOpt ) {
         P_Option* pOpt = (*itOpt);
         std::cout << "   " << pOpt->getName() << ": ";
         if ( pOpt->isBool() ) {
            std::cout << "boolean";
         } else if ( pOpt->isDecimal() ) {
            std::cout << "decimal";
         } else if ( pOpt->isNumeric() ) {
            std::cout << "numeric";
         } else if ( pOpt->isString() ) {
            std::cout << "string";
         } else if ( pOpt->isFile() ) {
            std::cout << "file";
         } else if ( pOpt->isPath() ) {
            std::cout << "path";
         }
         std::cout << std::endl;
      }
      std::cout << std::endl;
   
      // display option values:
      std::cout << "Values set:" << std::endl;
      OPTION_VALUE_MAP_CONST_ITER itValue = mapValues_.begin();
      for ( ; mapValues_.end() != itValue; ++itValue ) {
         const OptionValueBase* pV = (*itValue).second;
         const P_Option* pOpt = pV->getOption();
         if ( NULL == pOpt ) {
            std::cout << "Error:  NULL option pointer";
         } else {
            std::cout << "   " << pOpt->getName() << ": ";
            if ( pOpt->isBool() ) {
               std::cout << dynamic_cast< const OptionValue<bool>* >( pV )->get();
            } else if ( pOpt->isNumeric() ) {
               std::cout << dynamic_cast< const OptionValue<long>* >( pV )->get();
            } else if ( pOpt->isDecimal() ) {
               std::cout << dynamic_cast< const OptionValue<double>* >( pV )->get();
            } else if ( pOpt->isString() ) {
               std::cout << dynamic_cast< const OptionValue<std::string>* >( pV )->get().c_str();
            } else if ( pOpt->isFile() ) {
               std::cout << dynamic_cast< const OptionValue<std::string>* >( pV )->get().c_str();
            } else if ( pOpt->isPath() ) {
               std::cout << dynamic_cast< const OptionValue<std::string>* >( pV )->get().c_str();
            } else {
               std::cout << "Unknown type";
            }
         }
         std::cout << std::endl;
      }
      std::cout << std::endl;
   
      // display positonal values:
      std::cout << "Positional values:" << std::endl;
      POSITIONAL_LIST_CONST_ITER itPos = listPositional_.begin();
      for ( ; listPositional_.end() != itPos; ++itPos ) {
         std::cout << (*itPos).c_str() << std::endl;
      }
   }
   
   int ProgramOptions::processLine( const std::string& strLine )
   {
      if ( strLine.empty() ) {
         return( 0 );
      }
   
      ARG_VECTOR vArgs = line2argv( strLine);
      opt_process( vArgs );
      return( vArgs.size() );
   
   }
   
   bool ProgramOptions::processFile( const std::string& strFile )
   {
      bool bRc = true;
      std::ifstream inFile( strFile.c_str() );
   
      std::string strLine;
      if ( inFile.is_open() ) {
         while ( !inFile.eof() ) {
            std::getline( inFile, strLine );
            processLine( strLine );
         }
      } else {
         // throw "couldn't open options file" exception!
         bRc = false;
      }
   
      return bRc;
   }
   
   const char QUOTE = '\"';
   const char ESCAPE = '\\';
   
   // line2argv(): converts a one-line string into an ARG_VECTOR
   static ARG_VECTOR
   line2argv( const std::string& strLine )
   {
      ARG_VECTOR vArgs;
      bool bInQuote = false;  // flag: inside quotation
      bool bEscaped = false;  // flag: current character is escaped
   
      int iBegin = 0;
      int iCurr = 0;
   
      std::string strArg;
      for ( iCurr = 0; iCurr <= strLine.size(); ++iCurr ) {
         char ch = strLine[iCurr];
   
         switch ( ch ) {
            case ESCAPE:
               if ( bEscaped ) {
                  strArg += ESCAPE;
               }
               bEscaped = bEscaped ? false : true;
               continue;
               break;
            case QUOTE:
               if ( !bEscaped ) {
                  bInQuote = bInQuote ? false : true;
               } else {
                  strArg += QUOTE;
               }
               break;
            case ' ':
            case '\t':
               if ( !bInQuote ) {
                  // text is currently not quoted, and we are at a break
                  if ( !strArg.empty() ) {
                     vArgs.push_back( strArg );
                  }
                  strArg = "";
               } else {
                  strArg += ch;
               }
               break;
            case 0x00:     // catches end-of-string condition...
               if ( !strArg.empty() ) {
                  vArgs.push_back( strArg );
               }
               break;
            default:
               // normal text, just skip over
               strArg += ch;
               break;
         }
         bEscaped = false;
      }
      return( vArgs );
   }
   
   static bool
   break_word( bool bInQuote, char ch )
   {
      if ( 0x00 == ch || ch == QUOTE ) {
         return(true);
      }
      if ( !bInQuote && isspace( ch ) ) {
         return(true);
      }
      return(false);
   }
   
   /* opt_usage: Write a usage statement describing registered options.
    * This is what the program writes in response to '--help' on the
    * command line.
    */
   
   const int OPTUSAGEDEBUG = 0;
   const int OPTDESCRIPTWIDTH = 43;
   const int OPTDESCRIPTOFFSET = 38;
   const int OPTMAXLONGNAMELEN = 14;
   
   // A function to justify text to a given width, useful for printing long description strings. 
   std::string opt_justify( const std::string& str, 
                            int width, 
                            int indent, 
                            int initial, 
                            const std::string& strPrefix ) 
   {
      std::string strJust;
      int p;
   
      // If str is empty, then return an empty string
      if ( str.empty() ) {
         return strJust;
      }
   
       /* Insert initial indent and prefix */
      for (int n = 0; n < initial; ++n) {
         strJust += ' ';
      }
   
      strJust += strPrefix;
   
      // Scan through input, breaking up into words
      p = 0;   // Position with justified column 
      for (int iStr = 0; iStr < str.size(); ++iStr) {
         // Skip any leading whitespace */
         for( ; isspace( str[iStr] ) || '\r' == str[iStr]; ++iStr )
            ;
         if (iStr >= str.size() ) {
            break;
         }
         // Search for next whitespace char
		 int kStr = 0;
         for( kStr = 0; !isspace(str[iStr + kStr]) && '\r' != str[iStr + kStr] && 0x00 != str[ iStr + kStr ]; ++kStr )
            ;
         // Do we need a line break?
         if( p + kStr + 1 >= width && p != 0 ) {
            strJust += '\n';
            for( int n = 0; n < indent; ++n )
               strJust += ' ';
            strJust += strPrefix;
            p = 0;
         }
   
         // Add the word to the output buffer
         // If not at the beginning of the line, add a space 
         if (p != 0) {
            strJust += ' ';
            ++p;
         }
         strJust += str.substr( iStr, kStr );
         p += kStr;
         iStr += kStr;
      }
   
      // Return the justified buffer - remember to free this! */
      return strJust;
   }
   
   void ProgramOptions::shortUsage() const
   {
      if( !strTitle_.empty() ) {
         std::cout << strTitle_.c_str() << std::endl;
      }
      std::cout << "Usage: " << strProgramName_.c_str() << " ";
      std::cout << strUsage_.c_str() << std::endl;
   }
   
   void ProgramOptions::longUsage() const
   {
      shortUsage();
      std::cout << std::endl;
      usage();
   }
   
   void ProgramOptions::usage() const
   {
      static const char *dformat =        " -%c                   %-14s  %s\n";
      static const char *lformat =                 " -%c, --%-14s %-14s  %s\n";
      static const char *pformat =                        " %-20s %-14s  %s\n";
      static const char *uformat =  " %-10s                              %s\n";
      static const char *aformat =                  "     --%-14s %-14s  %s\n";
   
      /* First we print the positional options */
      bool bFirst = true;
      for( int iPosArg = 0; iPosArg < listPositionalArgs_.size(); ++iPosArg ) {
         if( bFirst ) {
            std::cout << "The arguments are:" << std::endl;
            bFirst = false;
         }
   
         const struct PositionalArg& rPA = listPositionalArgs_[iPosArg];
   
         // Get a suitably formatted version of the description
         // descript may be NULL, but opt_justify always returns
         // a valid (perhaps empty) string.
         std::string desc = opt_justify( rPA.strDesc_,
                                         OPTDESCRIPTWIDTH,
                                         OPTDESCRIPTOFFSET,0,"");
         if( OPTUSAGEDEBUG ) {
            fprintf(stderr,"%2d u ",iPosArg);
         }
         if ( !rPA.strDesc_.empty() ) {
            printf(pformat, rPA.strName_.c_str(), "", desc.c_str() );
         } else {
            printf( uformat, "", desc.c_str() );
         }
         
      }
   
      // Second we print the delimited options
      bFirst = true;
      OPTION_LIST_CONST_ITER itOpt = listOptions_.begin();
      for( ; listOptions_.end() != itOpt; ++itOpt ) {
         if( bFirst ) {
            std::cout << "The options are:" << std::endl;
            bFirst = false;
         }
   
         const P_Option* pOption = (*itOpt);
   
         std::string strDesc;
         if( pOption->getLongName().size() > OPTMAXLONGNAMELEN ) {
            strDesc = opt_justify( pOption->getDescription(),
                                   OPTDESCRIPTWIDTH,
                                   OPTDESCRIPTOFFSET,
                                   OPTDESCRIPTOFFSET, "" );
         } else {
            strDesc = opt_justify( pOption->getDescription(),
                                   OPTDESCRIPTWIDTH,
                                   OPTDESCRIPTOFFSET, 0, "" );
         }
         if( 0x00 == pOption->getShortName() ) {
            if (OPTUSAGEDEBUG) fprintf(stderr,"a ");
            if( pOption->getLongName().size() > OPTMAXLONGNAMELEN ) {
               printf( aformat, pOption->getLongName().c_str(), pOption->getTypeName().c_str(), "" );
               printf( "%s\n",strDesc.c_str() );
            } else {
               printf( aformat, pOption->getLongName().c_str(), pOption->getTypeName().c_str(), strDesc.c_str() );
            }
         } else {
            if( !pOption->getLongName().empty() ) {
               if (OPTUSAGEDEBUG) fprintf(stderr,"l ");
               if( pOption->getLongName().size() > OPTMAXLONGNAMELEN ) {
                  printf( lformat, pOption->getShortName(), pOption->getLongName().c_str(), pOption->getTypeName().c_str(), "");
                  printf( "%s\n", strDesc.c_str() );
               } else {
                  printf( lformat, pOption->getShortName(), pOption->getLongName().c_str(), pOption->getTypeName().c_str(), strDesc.c_str() );
               }
            
            } else {
               if (OPTUSAGEDEBUG) fprintf(stderr,"d ");
               printf( dformat, pOption->getShortName(), pOption->getTypeName().c_str(), strDesc.c_str() );
            }
         }
      }
   }

}  // namespace bf::opts
}  // namespace bf

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/programoptions.cpp-arc  $
// 
//    Rev 1.2   Jun 24 2005 11:10:08   purdyech
// PET910 - Corrected flaw in boolean option handling when optional 'positive' modifier is used.
// 
//    Rev 1.1   Oct 22 2004 09:00:54   PURDYECH
// PET910 - .NET Conversion Fixes
// 
//    Rev 1.0   Jan 27 2004 16:05:32   PURDYECH
// Initial revision.
//
