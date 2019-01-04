#pragma once

#include <xercesc\dom\domdocument.hpp>
#include <xercesc\dom\domelement.hpp>
#include <xercesc\dom\domxpathresult.hpp>


namespace gui {

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

      friend class GuiConfig;
   };

   static gui::GuiConfig* myGuiConfig;

   class HostConnection
   {
   public:

   	   DString hostAddress;
	   DString hostPort;
	   DString companyCode;
	   DString hostEnv;

	   HostConnection(DString& Address, DString& Port, DString CompanyCode, DString& Env)
	   {
		   hostAddress = Address;
		   hostPort = Port;
		   companyCode = CompanyCode;
		   hostEnv = Env;
	   }   
   };

   /**
    *
    */
   class GuiConfig {
   public:
	  
	  static GuiConfig* getInstance();	  
	  gui::GuiConfig::GuiConfig();
      void init( std::string &opts );
      ~GuiConfig();

      template<typename _Ty, typename _PC, typename _PO> _Ty getPropertyValue( const ConfigProperty<_Ty, _PC, _PO> &property ) const {

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

      template<typename _Ty, typename _PC, typename _PO> _Ty getCurrentValue( const ConfigIterator &iter,
                                                                               const ConfigProperty<_Ty, _PC, _PO> &property ) const {

         if ( iter.currElem_ != NULL ) {

            std::wstring configText = getElementText( iter.currElem_ );
            if ( configText.size() >0 ) {
               _PC parse;
               return parse( configText );
            }
         }

         // return the default ??should throw??
         return property.defaultValue;
      }

      ConfigIterator iterator( const std::wstring &pathName, const std::wstring &iterElement ) const;
	  ConfigIterator iteratorchildren( gui::ConfigIterator iterParent, const std::wstring &iterElement ) const;
      bool next( ConfigIterator &iter );	  

	  typedef std::map < DString, HostConnection *>  HOST_CONNECTION_MAP;
	  typedef HOST_CONNECTION_MAP::iterator  EHOST_CONNECTION_MAP_ITER;
	  HOST_CONNECTION_MAP hostConnectionsMap;

	  void addConnection(DString& hostAddress, DString& hostPort, DString companyCode, DString& hostEnv)
	  {
			EHOST_CONNECTION_MAP_ITER it = hostConnectionsMap.begin();
            while( it != hostConnectionsMap.end() )
            {
               if( (*it).first == hostEnv )
               {
                  return;
               }
               it++;
            } 
			HostConnection * _connection = new HostConnection(hostAddress, hostPort, companyCode, hostEnv);
			DString _key =  hostEnv + I_(";") + hostPort + I_(";") + hostAddress + I_(";") + companyCode;
            hostConnectionsMap.insert (HOST_CONNECTION_MAP::value_type (_key, _connection));
	  };

	  DString getCurrentEnv(DString& hostAddress, DString& hostPort, DString companyCode)
	  {
			EHOST_CONNECTION_MAP_ITER it = hostConnectionsMap.begin();
            while( it != hostConnectionsMap.end() )
            {
				HostConnection * _connection = (*it).second;
				if( _connection->hostAddress == hostAddress 
					&& _connection->hostPort == hostPort 
					&& _connection->companyCode == companyCode )
                {
					return _connection->hostEnv;
                }
                it++;
            } 
			return NULL_STRING;
	  }	  

   private:

      std::wstring getTextForPath( const std::wstring &pathName ) const;

      xercesc::DOMElement *getElementForPath( const std::wstring &pathName ) const;

      static std::wstring getTextForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem );
      static xercesc::DOMElement *getElementForPath( const std::wstring &pathName, xercesc::DOMElement *parentElem );

      static xercesc::DOMElement *getElementFirstChild(const std::wstring &childName, xercesc::DOMElement *parentElem);
      static xercesc::DOMElement *getElementNextSibling(const std::wstring &siblingName, xercesc::DOMElement *inSiblingElem);
      static std::wstring getElementText(xercesc::DOMElement *elem);

      xercesc::DOMDocument* doc_;
      xercesc::DOMElement *rootElem_;

	  
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

   typedef ConfigProperty< DString, ParseConfigDString, ParseConfigDString > DStringProperty;

} // namespace gui

