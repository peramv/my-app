#pragma once

#include <xercesc\dom\domdocument.hpp>
#include <xercesc\dom\domelement.hpp>
#include <xercesc\dom\domxpathresult.hpp>
#include <ConfigManager.hpp>


namespace site {

   /**
    *
    */
   template<typename _Ty, typename _PC > struct ConfigProperty {
      typedef _Ty Type;
      typedef _PC ParseConfig;

      ConfigProperty( const std::wstring &path )
      : pathName(path)
      {
      }
      const std::wstring pathName;
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
      , iterElementName_(iterElemName) {
      }

      bool started_;
      xercesc::DOMElement *currElem_;
      const std::wstring iterElementName_;

      friend class SiteConfig;
   };

   /**
    *
    */
   class SiteConfig {
   public:

      static SiteConfig* s_mySiteConfig;

      static SiteConfig* getInstance();   
      site::SiteConfig::SiteConfig();

      ~SiteConfig();
      void init( const std::string& opts, ConfigManager* pDSTCMgr );
      template<typename _Ty, typename _PC> bool
            setParm( const DString& dstrRegKey,
                     const DString& dstrRegValue,
                     const DString& dstrXmlKey,
                     const ConfigProperty< _Ty, _PC>& xmlProperty,
                     bool bHardReplace ) {
         return( setParm( dstrRegKey, dstrRegValue, L"", dstrXmlKey, xmlProperty, bHardReplace ) ); 
      }
      template<typename _Ty, typename _PC> bool
            setParm( const DString& dstrRegKey,
                     const DString& dstrRegValue,
                     const DString& dstrXmlPath,
                     const DString& dstrXmlKey,
                     const ConfigProperty< _Ty, _PC>& xmlProperty,
                     bool bHardReplace )
      {
         site::ConfigIterator citer = getInstance()->iterator( dstrXmlPath.getImp(), dstrXmlKey.c_str() );
         if ( getInstance()->next(citer) ) {
            Configuration cfg = pDSTCMgr_->retrieveConfig( dstrRegKey );
            _Ty v;
            if( getInstance()->getPropertyValue(citer, xmlProperty, v) ) {
               if( bHardReplace ||
                   cfg.getValue( dstrRegValue ).isNull() ) {
                   cfg.set( dstrRegValue, v );
                   pDSTCMgr_->storeConfig( cfg );
                  return( true );
               }
               return( false );
            }
         }
         return( false );
      }

      template<typename _Ty, typename _PC> _Ty getPropertyValue( const ConfigProperty<_Ty, _PC> &property,
                                                                 _Ty& v) const {
         // next try the config file
         const std::wstring &pathName = property.pathName;
         if ( pathName.size() != 0 ) {
            std::wstring configText;
            if( getTextForPath(property.pathName, configText) ) {
               _PC parse;
               v = parse( configText );
               return( true );
            }
         }
         return( false ); 
      }

      template<typename _Ty, typename _PC> bool getPropertyValue( const ConfigIterator &iter,
                                                                  const ConfigProperty<_Ty, _PC> &property,
                                                                  _Ty& v) const {
         if ( iter.currElem_ != NULL ) {
            std::wstring configText;
            if( getTextForPath( property.pathName, iter.currElem_, configText ) ) {
               _PC parse;
               v = parse( configText );
               return( true );
            }
         }
         return false;
      }

      template<typename _Ty, typename _PC> bool getCurrentValue( const ConfigIterator &iter,
                                                                 const ConfigProperty<_Ty, _PC> &property,
                                                                 _Ty& v) const {
         if ( iter.currElem_ != NULL ) {
            std::wstring configText;
            if( getElementText( iter.currElem_, configText ) ) {
               _PC parse;
               v = parse( configText );
               return( true );
            }
         }
         return( false ); 
      }

      ConfigIterator iterator( const std::wstring &pathName, const std::wstring &iterElement ) const;
      ConfigIterator iteratorchildren( site::ConfigIterator iterParent, const std::wstring &iterElement ) const;
      bool next( ConfigIterator &iter );    

      DString getDescription() const;

      xercesc::DOMElement* getElementForPath( const std::wstring& pathName ) const;
      xercesc::DOMElement* addElementForPath( const std::wstring& pathName );
      bool removeElementForPath( const std::wstring& pathName );
      static bool getTextForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem, std::wstring& configText );
      static xercesc::DOMElement* getElementForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem );
      xercesc::DOMElement* addElementForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem );
      static xercesc::DOMElement* getElementFirstChild(const std::wstring &childName, xercesc::DOMElement *parentElem);
      static xercesc::DOMElement* getElementNextSibling(const std::wstring &siblingName, xercesc::DOMElement *inSiblingElem);
      static bool getElementText(xercesc::DOMElement *elem, std::wstring& configText);
      bool setElementText(xercesc::DOMElement *elem, const std::wstring& configText);
      bool getTextForPath( const std::wstring &pathName, std::wstring& configText ) const;
      bool setTextForPath( const std::wstring &pathName, const std::wstring& configText );
      std::string asString() const;
   private:


      xercesc::DOMDocument* doc_;
      xercesc::DOMElement *rootElem_;

      ConfigManager* pDSTCMgr_;
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
         return( wcstol( strVal.c_str(), &pEnd, 10 ));
      }
   };

   /**
    *
    */
   class ParseConfigHexNum {
   public:
      long operator()( const std::wstring &strVal ) {
         wchar_t *pEnd = NULL;
         return( wcstol( strVal.c_str(), &pEnd, 16 ));
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

   typedef ConfigProperty< DString, ParseConfigDString > DStringProperty;
   typedef ConfigProperty< long, ParseConfigDecNum > DecNumericProperty;
   typedef ConfigProperty< DWORD, ParseConfigHexNum > DWordProperty;
   typedef ConfigProperty< bool, ParseConfigBoolean > BooleanProperty;

} // namespace site

