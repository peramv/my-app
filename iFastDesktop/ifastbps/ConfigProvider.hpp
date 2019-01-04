#pragma once

#include <bfutil\programoptions.hpp>
#include <xercesc\dom\domdocument.hpp>
#include <xercesc\dom\domelement.hpp>
#include <xercesc\dom\domxpathresult.hpp>


namespace bps {

   /**
    *
    */
   template<typename _Ty, typename _PC, typename _PO > struct ConfigProperty {
      typedef _Ty Type;
      typedef _PC ParseConfig;
      typedef _PO ParseOption;

      ConfigProperty( const std::wstring &path, const Type &def )
      : cmdLineOpt('\0')
      , pathName(path)
      , defaultValue(def)
      {
      }

      ConfigProperty( char opt, const std::wstring &path, const Type &def )
      : cmdLineOpt(opt)
      , pathName(path)
      , defaultValue(def)
      {
      }

      const char cmdLineOpt;
      const std::wstring pathName;
      const Type defaultValue;
   };

   /**
    *
    */
   class ConfigIterator {
   public:
      bool hasNext() { 
         return currElem_!=NULL; 
      }

   private:
      ConfigIterator( xercesc::DOMElement *elem, const std::wstring &iterElemName ) 
      : started_(false)
      , currElem_(elem)
      , iterElementName_(iterElemName) 
      {
      }

      bool started_;
      xercesc::DOMElement *currElem_;
      const std::wstring iterElementName_;

      friend class ConfigProvider;
   };

   /**
    *
    */
   class ConfigProvider {
   public:
      ConfigProvider( const bf::opts::ProgramOptions &opts );
      ~ConfigProvider();

      template<typename _Ty, typename _PC, typename _PO> _Ty getPropertyValue( const ConfigProperty<_Ty, _PC, _PO> &property ) const {

         // try command line first
         char cmdLineOpt = property.cmdLineOpt;
         if ( cmdLineOpt != '\0' && programOpts_.isSet(cmdLineOpt) ) {
            const bf::opts::ProgramOptions::OptionValue<_PO::OType> * optValue = 
               ( dynamic_cast< const bf::opts::ProgramOptions::OptionValue<_PO::OType> * >(programOpts_.getValue(cmdLineOpt)) ) ;
            if ( optValue != NULL ) {
               _PO parse;
               return parse( optValue );
            }
         }

         // next try the config file
         const std::wstring &pathName = property.pathName;
         if ( pathName.size() != 0 ) {
            std::wstring configText = getTextForPath(property.pathName);
            if ( configText.size() >0 ) {
               _PC parse;
               return parse( configText );
            }
         }

         // return the default
         return property.defaultValue;
      }

      template<typename _Ty, typename _PC, typename _PO> _Ty getPropertyValue( const ConfigIterator &iter,
                                                                               const ConfigProperty<_Ty, _PC, _PO> &property ) const {

         if ( iter.currElem_ != NULL ) {

            std::wstring configText = getTextForPath( property.pathName, iter.currElem_ );
            if ( configText.size() >0 ) {
               _PC parse;
               return parse( configText );
            }
         }

         // return the default ??should throw??
         return property.defaultValue;
      }

      ConfigIterator iterator( const std::wstring &pathName, const std::wstring &iterElement ) const;
      bool next( ConfigIterator &iter );

   private:

      std::wstring getTextForPath( const std::wstring &pathName ) const;

      xercesc::DOMElement *getElementForPath( const std::wstring &pathName ) const;

      static std::wstring getTextForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem );
      static xercesc::DOMElement *getElementForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem );

      static xercesc::DOMElement *getElementFirstChild(const std::wstring &childName, xercesc::DOMElement *parentElem);
      static xercesc::DOMElement *getElementNextSibling(const std::wstring &siblingName, xercesc::DOMElement *inSiblingElem);
      static std::wstring getElementText(xercesc::DOMElement *elem);

      const bf::opts::ProgramOptions &programOpts_;
      xercesc::DOMDocument* doc_;
      xercesc::DOMElement *rootElem_;
   };

   /**
    *
    */
   template<typename _Ty> class ParseOption {
   public:
      typedef _Ty OType;
      OType operator()( const bf::opts::ProgramOptions::OptionValue<OType> *optValue ) {
         return optValue->get();
      }
   };

   /**
    *
    */
   class ParseOptionDString {
   public:
      typedef std::string OType;
      DString operator()( const bf::opts::ProgramOptions::OptionValue<OType> *optValue ) {
         return optValue->get();
      }
   };

   /**
    *
    */
   template<char _S> class ParseOptionFirst {
   public:
      typedef std::string OType;
      DString operator()( const bf::opts::ProgramOptions::OptionValue<OType> *optValue ) {
         std::string strValue =  optValue->get();
         int iSeparator = strValue.find( '@' );
         if( iSeparator != strValue.npos )
         {
            return DString(strValue.substr( 0, iSeparator ));
         }
         return DString(strValue);
      }
   };

   /**
    *
    */
   template<char _S> class ParseOptionSecond {
   public:
      typedef std::string OType;
      DString operator()( const bf::opts::ProgramOptions::OptionValue<OType> *optValue ) {
         std::string strValue =  optValue->get();
         int iSeparator = strValue.find( '@' );
         if( iSeparator != strValue.npos )
         {
            return DString(strValue.substr( iSeparator+1 ));
         }
         return I_("");
      }
   };

   /**
    *
    */
   class ParseConfigDString { 
   public:
      DString operator()( const std::wstring &strVal ) { 
         return DString(strVal);
      }
   };

   /**
   *
   */
   class ParseConfigDecNum { 
   public:
      long operator()( const std::wstring &strVal ) { 
         wchar_t *pEnd = NULL;
         return ( wcstol( strVal.c_str(), &pEnd, 10 ));
      }
   };

   /**
    *
    */
   class ParseConfigHexNum { 
   public:
      long operator()( const std::wstring &strVal ) { 
         wchar_t *pEnd = NULL;
         return ( wcstol( strVal.c_str(), &pEnd, 16 ));
      }
   };

   /**
    *
    */
   class ParseConfigBoolean { 
   public:
      bool operator()( const std::wstring &strVal ) {
         // read the following lines as: 
         //            upperStrVal = strVal.toupper();
         // std is beautiful
         std::wstring upperStrVal(strVal);
         std::use_facet< std::ctype<wchar_t> > ( std::locale() ).toupper( &upperStrVal[0], &upperStrVal[upperStrVal.size()] );

         if ( upperStrVal == L"Y" || upperStrVal == L"YES" ) {
            return true;
         }
         if ( upperStrVal == L"T" || upperStrVal == L"TRUE" ) {
            return true;
         }
         return false;
      }
   };

   // basic property types
   typedef ConfigProperty< DString, ParseConfigDString, ParseOptionDString > DStringProperty;
   typedef ConfigProperty< long, ParseConfigDecNum, ParseOption<long> > DecNumericProperty;
   typedef ConfigProperty< long, ParseConfigHexNum, ParseOption<long> > HexNumericProperty;
   typedef ConfigProperty< bool, ParseConfigBoolean, ParseOption<bool> > BooleanProperty;


} // namespace bps

