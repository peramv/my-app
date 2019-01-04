//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, databases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : propertyrepository.cpp
// ^AUTHOR : Chris Kennedy
// ^DATE   : 06/01/1999
//
// ----------------------------------------------------------
//
// ^CLASS : PropertyRepository
//
// ^INHERITS FROM : None
//
// ^MEMBER VARIABLES :
//    ^NAME :        m_dpiMap
//    ^TYPE :        DPIMapType
//    ^DESCRIPTION : Map of pointers to DataPropertiesImpl based on id's
//
//    ^NAME :        m_deMap
//    ^TYPE :        DEMapType
//    ^DESCRIPTION : Map of pointers to DataElementProperties based on id's
//
//    ^NAME :        m_dataSetToIdMap
//    ^TYPE :        NameMapType
//    ^DESCRIPTION : Map of data set id's based on names
//
//    ^NAME :        m_fieldToIdMap
//    ^TYPE :        NameMapType
//    ^DESCRIPTION : Map of field id's based on names
//
//    ^NAME :        m_countryCode
//    ^TYPE :        DString
//    ^DESCRIPTION : The current country code ( locale )
//
//    ^NAME :        m_dataSource
//    ^TYPE :        RepositoryFile
//    ^DESCRIPTION : Pointer to data source ( most likely a RepositoryFile )
//
//    ^NAME :        _pInstance
//    ^TYPE :        static PropertyRepository
//    ^DESCRIPTION : Pointer to single instance of PropertyRepository
//
#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#include <string>

#ifndef PROPERTYREPOSITORY_HPP
   #include "propertyrepository.hpp"
#endif

#ifndef BINFILEHEADER_HPP
   #include "binfileheader.hpp"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif

#ifndef DATAELEMENT_HPP
   #include "dataelement.hpp"
#endif

#ifndef DATAPROPERTIESIMPL_HPP
   #include "datapropertiesimpl.hpp"
#endif

#ifndef DIDBRKR_H
   #include "didbrkr.h"
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

#ifndef REPOSITORYFILE_HPP
   #include "repositoryfile.hpp"
#endif

typedef DataProperties DP;
typedef DataComponentProperties DCP;
typedef DataElementProperties DEP;
typedef DataComponent DC;
typedef DataElement DE;
typedef DataPropertiesImpl DPI;

namespace
{
   const I_CHAR *CLASS_NAME = I_( "PropertyRepository" );
   const int BINARY_REDEFINABLE_FLAG = 1;
   static CriticalSectionLock s_lock;
}

const DString PropertyRepository::EMPTY_STRING = NULL_STRING;

PropertyRepository *PropertyRepository::_pInstance = NULL;
bool PropertyRepository::s_fCaseSensitive = true;
bool PropertyRepository::s_fIgnoreCaseOnSubKeys = false;

PropertyRepository *PropertyRepository::getInstance( void )
{
   if ( PropertyRepository::_pInstance )
   {
      return PropertyRepository::_pInstance;
   }

   Guard crit( &s_lock );

   if ( PropertyRepository::_pInstance )
   {
      return PropertyRepository::_pInstance;
   }

   // Set up static case sensitivity flags
   ConfigManager *theMgr = ConfigManager::getManager( I_("DataBroker") );

   Configuration cfgOptions = theMgr->retrieveConfig( I_( "DBOptions" ) );
   DString dstrCaseSensisitive = cfgOptions.getValueAsString( I_( "CaseSensitive" ) );
   DString dstrIgnoreCaseOnSubKeys = cfgOptions.getValueAsString( I_( "IgnoreCaseOnSubKeys" ) );

   if ( dstrCaseSensisitive.upperCase() == I_( "NO" ) )
   {
      s_fCaseSensitive = false;
   }
   else
   {
      s_fCaseSensitive = true;
   }

   if ( dstrIgnoreCaseOnSubKeys.length() > 0 )
   {
      s_fIgnoreCaseOnSubKeys = true;
   }
   else
   {
      s_fIgnoreCaseOnSubKeys = false;
   }
   // Create instance (which uses case sensitivity flag
   PropertyRepository::_pInstance = new PropertyRepository();
   if ( !PropertyRepository::_pInstance )
   {
      THROWFROMBASE( DIDBRKR_COMPONENT_NAME, I_("getInstance"),
                     BASE_ALLOC_FAIL );
   }
   if ( !PropertyRepository::_pInstance->m_dataSource )
   {
      delete PropertyRepository::_pInstance;
      PropertyRepository::_pInstance = NULL;
   }
   else
   {
      _pInstance->_initInstance();
   }
   
   return PropertyRepository::_pInstance;
}


void PropertyRepository::_initInstance( void )
{
   m_dataSource->initInstance();
   m_register.registerSingleton( _deregister, ( void * )this );
}


void PropertyRepository::_killInstance( void )
{
   if ( PropertyRepository::_pInstance )
   {
      delete PropertyRepository::_pInstance;
      PropertyRepository::_pInstance = NULL;
   }
}


PropertyRepository::~PropertyRepository()
{
   if ( m_dataSource )
   {
      delete m_dataSource;
   }

   for ( DPIMapType::iterator iter = m_dpiMap.begin(); iter != m_dpiMap.end();
         ++iter )
   {
      delete ( *iter ).second;
   }

   for ( DEMapType::iterator iter2 = m_deMap.begin(); iter2 != m_deMap.end();
         ++iter2 )
   {
      delete ( *iter2 ).second;
   }
}


DataPropertiesImpl *PropertyRepository::getDataSet( const DString &dataSetName,
                                                    const ClientLocale& clientLocale,
                                                    int repeat )
{
   unsigned long id = getFieldIdFromName( dataSetName );
   if ( ULONG_MAX != id )
   {
      return getDataSet( id, clientLocale, repeat );
   }
   return NULL;
}


DataPropertiesImpl *PropertyRepository::getDataSet( unsigned long dataSetId,
                                                    const ClientLocale& clientLocale,
                                                    int repeat )
{
   {
      Guard crit( &s_lock );
      DPIMapType::iterator iter = m_dpiMap.find( dataSetId );
      if ( iter != m_dpiMap.end() )
      {
         return (*iter).second;
      }
   }

   Guard crit( &s_lock );
   DPIMapType::iterator iter2 = m_dpiMap.find( dataSetId );
   if ( iter2 != m_dpiMap.end() )
   {
      return (*iter2).second;
   }

   bool done = false;
   string_vector stringVec;
   DString fieldId, repeatCount, flags, dataSetName;
   DataComponentProperties *dcpProps = NULL;
   DataPropertiesImpl *returnDPI = NULL;
   DataPropertiesImpl::DCPPtrVectorType dcpPtrVector;
   DString dstrType;
   m_dataSource->getDataSet( dataSetId, clientLocale, dataSetName, stringVec, dstrType );
   string_vector::iterator iter = stringVec.begin();
   while ( iter != stringVec.end() )
   {
      fieldId = (*iter);
      ++iter;
      repeatCount = (*iter);
      ++iter;
      flags = (*iter);
      ++iter;

      dcpProps = _getPropsPtr( convertToULong( fieldId ),
                               &clientLocale,
                               repeatCount.asInteger() );

// DTWK thread safe?
      if ( BINARY_REDEFINABLE_FLAG == flags.asInteger() )
      {
         _addRedefine( dcpProps->getName(), dataSetName );
      }
      else
      {
         dcpPtrVector.push_back( dcpProps );
      }
   }
   if ( dcpPtrVector.size() > 0 )
   {
      returnDPI = new DataPropertiesImpl( dataSetName,
                                          repeat != 0,
                                          dcpPtrVector );
      m_dataSetToIdMap[ dataSetName ] = dataSetId;
      m_dpiMap[ dataSetId ] = returnDPI;
      returnDPI->setId( dataSetId );
   }
   return returnDPI;
}


DEP::ELEMENTTYPE PropertyRepository::getStoredTypeFromString(
                                                      const DString &fieldType )
{
   if ( I_(" X") == fieldType )
   {
      return DEP::STRING;
   }
   else if ( I_(" 9") == fieldType )
   {
      return DEP::INTEGER;
   }
   else if ( I_(" S") == fieldType )
   {
      return DEP::DECIMAL;
   }
   else if ( I_(" B") == fieldType )
   {
      return DEP::BINARY;
   }
   else if ( I_(" F") == fieldType )
   {
      return DEP::BOOLEAN;
   }
   else if ( I_(" D") == fieldType )
   {
      return DEP::I18N_DATE;
   }
   else if ( I_(" T") == fieldType )
   {
      return DEP::I18N_TIME;
   }
   else if ( I_("DN") == fieldType )
   {
      return DEP::I18N_DECIMAL;
   }
   else if ( I_(" I") == fieldType )
   {
      return DEP::I18N_INTEGER;
   }
   else if ( I_(" %") == fieldType )
   {
      return DEP::I18N_PERCENT;
   }
   else if ( I_(" $") == fieldType )
   {
      return DEP::I18N_CURRENCY;
   }
   else if ( I_("  ") == fieldType || I_(" N") == fieldType )
   {
      return DEP::NO_TYPE;
   }
   return DEP::STRING;
}


bool PropertyRepository::getStringFromStoredType( DEP::ELEMENTTYPE type,
                                                  DString &dstrType ) const
{
   switch ( type )
   {
   case DEP::STRING:
      dstrType = I_(" X");
      break;

   case DEP::INTEGER:
      dstrType = I_(" 9");
      break;

   case DEP::DECIMAL:
      dstrType = I_(" S");
      break;

   case DEP::BINARY:
      dstrType = I_(" B");
      break;

   case DEP::BOOLEAN:
      dstrType = I_(" F");
      break;

   case DEP::I18N_DATE:
      dstrType = I_(" D");
      break;

   case DEP::I18N_TIME:
      dstrType = I_(" T");
      break;

   case DEP::I18N_DECIMAL:
      dstrType = I_("DN");
      break;

   case DEP::I18N_INTEGER:
      dstrType = I_(" I");
      break;

   case DEP::I18N_PERCENT:
      dstrType = I_(" %");
      break;

   case DEP::I18N_CURRENCY:
      dstrType = I_(" $");
      break;

   case DEP::NO_TYPE:
      dstrType = I_(" N");
      break;

   default:
      dstrType = NULL_STRING;
      break;
   }

   return false;
}


DEP::JUSTIFICATION PropertyRepository::_getJustificationFromChar( I_CHAR fJust )
{
   switch( fJust )
   {
      case 'R':
         return DEP::RIGHT;
         break;

      case 'C':
         return DEP::CENTER;
         break;

      case 'L':
         return DEP::LEFT;
         break;

      default:
         return DEP::NO_JUSTIFICATION;
         break;
   }
   return DEP::LEFT;
}


DCP *PropertyRepository::getPropsPtr( const DString &fieldName,
                                      const ClientLocale *pClientLocale )
{
   if ( !pClientLocale )
   {
      pClientLocale = &ClientLocale::getDefaultClientLocale();
   }

   unsigned long fieldId = getFieldIdFromName( fieldName );
   if ( ULONG_MAX != fieldId )
   {
      return _getPropsPtr( fieldId, pClientLocale, 0 );
   }
   return (DCP *)0;
}


DCP *PropertyRepository::_getPropsPtr( unsigned long fieldId,
                                       const ClientLocale *pClientLocale,
                                       int repeat )
{
   {
      Guard crit( &s_lock );

      DEMapType::iterator iter = m_deMap.find( fieldId );
      if ( iter != m_deMap.end() )
      {
         DEP *origDep = (*iter).second;
         if ( origDep->hasFieldLocale( *pClientLocale ) )
         {
            return (*iter).second;
         }
      }
      DPIMapType::iterator iter2 = m_dpiMap.find( fieldId );
      if ( iter2 != m_dpiMap.end() )
      {
         DataProperties *dpPtr = new DataProperties( (*iter2).second );
         dpPtr->setId( fieldId );
         return dpPtr;
      }
   }

   Guard crit( &s_lock );

   DEMapType::iterator iter = m_deMap.find( fieldId );
   if ( iter != m_deMap.end() )
   {
      DEP *origDep = (*iter).second;
      if ( origDep->hasFieldLocale( *pClientLocale ) )
      {
         return (*iter).second;
      }
   }
   DPIMapType::iterator iter2 = m_dpiMap.find( fieldId );
   if ( iter2 != m_dpiMap.end() )
   {
      DataProperties *dpPtr = new DataProperties( (*iter2).second );
      dpPtr->setId( fieldId );
      return dpPtr;
   }

   DString fieldType;
   m_dataSource->getFieldType( fieldId, fieldType );

   if ( I_(" V") == fieldType || I_(" R") == fieldType )
   {
      DString dstrType;
      DPI *dpiPtr = getDataSet( fieldId, *pClientLocale, repeat );
      DataProperties *dpPtr = new DataProperties( dpiPtr );
      dpPtr->setId( fieldId );
      dpPtr->setCameFromRepository( false );
      return (dpPtr);
   }
   else
   {
      return (getField( fieldId, *pClientLocale ));
   }
}


DEP *PropertyRepository::getField( unsigned long fieldId,
                                   const ClientLocale& clientLocale )
{
   MAKEFRAME( DIDBRKR_COMPONENT_NAME,
              I_( "PropertyRepository::getField" ) );

   DEP * pDEP;

   {
      Guard crit( &s_lock );
      DEMapType::iterator iter = m_deMap.find( fieldId );
      if ( iter != m_deMap.end() )
      {
         pDEP = (*iter).second;
         if ( pDEP->hasFieldLocale( clientLocale ) )
         {
            return ( pDEP );
         }
      }
   }

   Guard crit( &s_lock );
   DEMapType::iterator iter = m_deMap.find( fieldId );
   if ( iter != m_deMap.end() )
   {
      pDEP = (*iter).second;
      if ( pDEP->hasFieldLocale( clientLocale ) )
      {
         return ( pDEP );
      }
   }


   pDEP = m_dataSource->getField( fieldId, clientLocale, true );

   if ( pDEP )
   {
      pDEP->setCameFromRepository( true );
      m_deMap[ fieldId ] = pDEP;

//@@@
//@@@ A flag needs to be added to the DEP to indicate that the field is
//@@@ redefinable when its fieldType == I_( " 1" ). Then this flag can be
//@@@ checked here and _addRedefinableField( ... ) called.
//@@@
//      // All redefinable elements are DEP::STRING
//      if ( DEP::STRING == storedType && I_(" 1") == fieldType )
//      {
//         // A field can be redefined by itself (this also ensures that
//         // redefinable fields have at least one entry in the set of redefines
//         _addRedefinableField( fieldName );
//      }
   }

   return ( pDEP );
}


DEP *PropertyRepository::getField( const DString &fieldName,
                                   const ClientLocale& clientLocale )
{
   unsigned long fieldId = getFieldIdFromName( fieldName );
   if ( ULONG_MAX != fieldId )
   {
      return getField( fieldId, clientLocale );
   }
   DString msg( I_("ele=") );
   msg += fieldName;
   THROWFROMFILEIDI( DIDBRKR_COMPONENT_NAME,
         I_("PropertyRepository::getField( const DString &, const DString & )"),
                     DIDBRKR_ELEMENT_NOT_FOUND, msg.c_str() );
   return( (DEP *)NULL );
}


DString PropertyRepository::getClient()
{
   return m_dataSource->getClient();
}


unsigned long PropertyRepository::getFieldIdFromName( const DString &fieldName )
{
   return m_dataSource->getFieldIdFromName( fieldName );
}


const DString &PropertyRepository::getFieldNameFromId( unsigned long id, DString &fieldName )
{
   const DEP *dep = getField( id, ClientLocale::getDefaultClientLocale() );
   if ( dep )
   {
      fieldName = dep->getName();
   }
   else
   {
      fieldName = EMPTY_STRING;
   }
   return fieldName;
}


void PropertyRepository::getMask( unsigned long maskId, DString &maskString,
                                  unsigned long &numLanguages,
                                  const ClientLocale *pClientLocale,
                                  bool fExactMatch )
{
   m_dataSource->getMask( maskId, maskString, numLanguages, pClientLocale,
                          fExactMatch );
   return;
}


void PropertyRepository::getSubstitutionSet( unsigned long setId,
                                             DString &subSetString,
                                             unsigned long &numLanguages,
                                             const ClientLocale *pClientLocale,
                                             bool fExactMatch )
{
   m_dataSource->getSubstitutionSet( setId, subSetString, numLanguages,
                                     pClientLocale, fExactMatch );
   return;
}


bool PropertyRepository::isValid( const DString &elementName,
                                  const DString &valueString,
                                  const ClientLocale *pClientLocale )
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   DEP *depPtr = getField( elementName, *pLocClientLocale );
   if ( depPtr )
   {
      DString tempValue( valueString );
      return depPtr->isValid( tempValue, pLocClientLocale );
   }
   return false;
}


bool PropertyRepository::isValid( unsigned long fieldId,
                                  const DString &valueString,
                                  const ClientLocale *pClientLocale )
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   DEP *depPtr = getField( fieldId, *pLocClientLocale );
   if ( depPtr )
   {
      DString tempValue( valueString );
      return depPtr->isValid( tempValue, pLocClientLocale );
   }
   return false;
}


bool PropertyRepository::isValidForHost( const DString &elementName,
                                         const DString &valueString )
{
   DEP *depPtr =
      getField( elementName, ClientLocale::getDefaultInfraClientLocale() );
   if ( depPtr )
   {
      DString tempValue( valueString );
      return depPtr->isValidForHost( tempValue );
   }
   return false;
}


bool PropertyRepository::isValidForHost( unsigned long fieldId,
                                         const DString &valueString )
{
   DEP *depPtr =
      getField( fieldId, ClientLocale::getDefaultInfraClientLocale() );
   if ( depPtr )
   {
      DString tempValue( valueString );
      return depPtr->isValidForHost( tempValue );
   }
   return false;
}


bool PropertyRepository::formatValue( const DString &elementName,
                                      DString &valueString,
                                      bool checkValidity,
                                      const ClientLocale *pClientLocale,
                                      const DString &i18nFormat,
                                      unsigned long ulStripFlags )
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   bool retVal = false;
   DEP *depPtr = getField( elementName, *pLocClientLocale );
   if ( depPtr )
   {
      DataElement dataEl( NULL_STRING, depPtr );
      if ( retVal = dataEl.setValue( valueString, checkValidity,
                                     pLocClientLocale, false ) )
      {
         valueString = dataEl.getValue( DataElement::USE_SUBSTITUTES |
                                           DataElement::USE_MASK,
                                        pLocClientLocale,
                                        i18nFormat );

         if ( depPtr->getStoredType() == DEP::STRING )
         {
            if ( ulStripFlags & DataElement::STRIP_LEADING )
            {
               stripLeading( valueString );
            }
            if ( ulStripFlags & DataElement::STRIP_TRAILING )
            {
               stripTrailing( valueString );
            }
         }
      }
   }

   return retVal;
}


bool PropertyRepository::formatValue( unsigned long fieldId,
                                      DString &valueString,
                                      bool checkValidity,
                                      const ClientLocale *pClientLocale,
                                      const DString &i18nFormat,
                                      unsigned long ulStripFlags )
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();

   bool retVal = false;
   DEP *depPtr = getField( fieldId, *pLocClientLocale );
   if ( depPtr )
   {
      DataElement dataEl( NULL_STRING, depPtr );
      if ( retVal = dataEl.setValue( valueString, checkValidity,
                                     pLocClientLocale, false ) )
      {
         valueString = dataEl.getValue( DataElement::USE_SUBSTITUTES |
                                           DataElement::USE_MASK,
                                        pLocClientLocale,
                                        i18nFormat );

         if ( depPtr->getStoredType() == DEP::STRING )
         {
            if ( ulStripFlags & DataElement::STRIP_LEADING )
            {
               stripLeading( valueString );
            }
            if ( ulStripFlags & DataElement::STRIP_TRAILING )
            {
               stripTrailing( valueString );
            }
         }
      }
   }
   return retVal;
}


bool PropertyRepository::unformatValue( const DString &elementName,
                                        DString &valueString,
                                        const ClientLocale *pClientLocale,
                                        const DString &i18nFormat,
                                        bool checkValidity )
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();
   DEP *depPtr = getField( elementName, *pLocClientLocale );
   if ( depPtr )
   {
      if ( i18nFormat.length() || depPtr->hasMask() )
      {
         try
         {
            depPtr->removeMaskFromValue( valueString,
                                         pLocClientLocale,
                                         i18nFormat );
         }
         catch ( ConditionException &ce )
         {
            // We don't need to do anything but catch the exceptions
            // The method returns false by default
            if ( ( ce.getCode() != DIDBRKR_I18N_MASK_FORMAT_ERROR ) ||
                 ( i_strcmp( ce.getComponentName(), DIDBRKR_COMPONENT_NAME ) ) )
            {
               throw;
            }

            return false;
         }
      }
      else
      {
         if ( depPtr->hasSubstitutes( pLocClientLocale ) )
         {
            if ( checkValidity )
            {
               DString dstrTemp( valueString );
               valueString = depPtr->getKeyFromValue( dstrTemp, pClientLocale );

               if ( valueString == dstrTemp )
               {
                  return false;
               }
            }
            else
            {
               valueString =
                  depPtr->getKeyFromValue( valueString, pClientLocale );
            }
         }
      }
   }
   else
   {
      return false;
   }

   return true;
}


bool PropertyRepository::unformatValue( unsigned long fieldId,
                                        DString &valueString,
                                        const ClientLocale *pClientLocale,
                                        const DString &i18nFormat,
                                        bool checkValidity )
{
   const ClientLocale *pLocClientLocale =
      pClientLocale ? pClientLocale : &ClientLocale::getDefaultClientLocale();
   DEP *depPtr = getField( fieldId, *pLocClientLocale );
   if ( depPtr )
   {
      if ( i18nFormat.length() || depPtr->hasMask() )
      {
         try
         {
            depPtr->removeMaskFromValue( valueString,
                                         pLocClientLocale,
                                         i18nFormat );
         }
         catch ( ConditionException &ce )
         {
            // We don't need to do anything but catch the exceptions
            // The method returns false by default
            if ( ( ce.getCode() != DIDBRKR_I18N_MASK_FORMAT_ERROR ) ||
                 ( i_strcmp( ce.getComponentName(), DIDBRKR_COMPONENT_NAME ) ) )
            {
               throw;
            }

            return false;
         }
      }
      else
      {
         if ( depPtr->hasSubstitutes( pLocClientLocale ) )
         {
            if ( checkValidity )
            {
               DString dstrTemp( valueString );
               valueString = depPtr->getKeyFromValue( dstrTemp, pClientLocale );

               if ( valueString == dstrTemp )
               {
                  return false;
               }
            }
            else
            {
               valueString =
                  depPtr->getKeyFromValue( valueString, pClientLocale );
            }
         }
      }
   }
   else
   {
      return false;
   }

   return true;
}


bool PropertyRepository::isValidRedefine( const DString &dstrField,
                                          const DString &dstrDataSet )
{
   Guard crit( &s_lock );
   RedefineMapType::iterator iterRedefMap = m_redefineMap.find( dstrField );

   if ( m_redefineMap.end() != iterRedefMap )
   {
      string_vector &vecRedefs = ( *iterRedefMap ).second;
      string_vector::iterator iterRedefVec =
            findInContainer< string_vector, DString >( vecRedefs, dstrDataSet );

      if ( vecRedefs.end() != iterRedefVec )
      {
         return true;
      }
   }

   return false;
}


/* private */

int mymbtowc( wchar_t *outBuff, const char *inBuff, int numCharsToConvert )
{
        wchar_t *outPtr = outBuff;
        char *inPtr = const_cast< char * >(inBuff);
        for ( int i = 0; i < numCharsToConvert && inPtr; i++ )
        {
                mbtowc( outPtr++, inPtr++, MB_CUR_MAX );
        }
        return inPtr - inBuff;
}

PropertyRepository::PropertyRepository() :
   m_dataSource( NULL )
{
   ConfigManager *theMgr = ConfigManager::getManager( I_("DataBroker") );
   Configuration theConfig = theMgr->retrieveConfig( I_("DataPath") );
   DStringA envPath = theConfig.getValueAsString( I_("RepositorySource") );

   if (envPath.empty())
   {
      envPath = GetGlobalRepositorySourcePath ();
   }
   if ( envPath.length() )
   {
      m_dataSource = new RepositoryFile( envPath.getImp() );
   }
}


void PropertyRepository::_addRedefinableField( const DString &dstrFieldName )
{
   _addRedefine( dstrFieldName, dstrFieldName );
}


void PropertyRepository::_addRedefine( const DString &dstrFieldName,
                                       const DString &dstrDataSet )
{
// DTWK check for leaks when adding the same values multiple times
   RedefineMapType::iterator iterRedefMap = m_redefineMap.find( dstrFieldName );

   if ( m_redefineMap.end() == iterRedefMap )
   {
      string_vector vecRedefs;
      vecRedefs.insert( vecRedefs.end(), dstrFieldName );

      if ( dstrFieldName != dstrDataSet )
      {
         vecRedefs.insert( vecRedefs.end(), dstrDataSet );
      }
      m_redefineMap[ dstrFieldName ] = vecRedefs;
   }
   else
   {
      string_vector &vecRedefs = ( *iterRedefMap ).second;

      if ( vecRedefs.end() ==
           findInContainer< string_vector, DString >( vecRedefs, dstrDataSet ) )
      {
         vecRedefs.insert( vecRedefs.end(), dstrDataSet );
      }
   }
}


DataPropertiesImpl * PropertyRepository::_findLoadedDataSet( const DString &dstrName )
{
   NameMapType::iterator iter2 = m_dataSetToIdMap.find( dstrName );
   if ( iter2 != m_dataSetToIdMap.end() )
   {
      DPIMapType::iterator iter3 = m_dpiMap.find( (*iter2).second );
      if ( iter3 != m_dpiMap.end() )
      {
         return (*iter3).second;
      }
   }

   return 0;
}


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
// $Log:   Y:/VCS/iFastAWD/didbrkr/propertyrepository.cpp-arc  $
// 
//    Rev 1.1   Nov 03 2011 23:05:52   popescu
// Repository object fix - couldn't be created due to path not found. Read the global repository path.
// 
//    Rev 1.0   28 Jan 2008 13:21:32   kovacsro
// Initial revision.
// 
//    Rev 1.46   11 Jan 2002 12:47:44   dt14177
// fixed memory leak
// 
//    Rev 1.45   Sep 24 2001 15:42:00   DT11159
// Must continue to check for field type " R" until the new
// DDTool is used in the production builds to create the .bin
// file.  At that time, checking for just " V" will be enough.
//
//    Rev 1.44   Sep 21 2001 16:19:56   DT11159
// Made changes to support the new bin file format.
//
//    Rev 1.43   Jul 05 2001 09:25:18   dt24433
// Fixed getFieldNameFromId to use string parameter passed in.
//
//    Rev 1.42   May 21 2001 14:38:46   DT21858
// Now uses srcprag.h correctly
//
//    Rev 1.41   May 18 2001 15:21:22   dt24433
// Switched to Guard\CriticalSectionLock from CriticalSection\MutexSemaphore.
// Added support for ignoreCaseOnSubKeys (performance).
//
//    Rev 1.40   Mar 02 2001 14:50:34   dt24433
// Changed implementation for getting case sensitivity flag.
// Removed unused methods.
// Changed to use mutex instead of SWMR lock.
// getFiledNameFromId changed to do more efficient lookup instead of always going back to the file.
//
//    Rev 1.39   Jan 19 2001 16:56:30   DT11159
// Load all element properties when a Data object is initialized.
//
//    Rev 1.38   Jan 04 2001 16:46:58   DT11159
// Changes to improve performance of Data objects.
//
//    Rev 1.37   Nov 22 2000 07:05:14   dt17817
// Reduce runtime memory requirements of Data objects
//
//    Rev 1.36   Sep 30 2000 14:24:40   dt17817
// Added flag to check validity of substitutions to PropertyRepository::unformatValue()
//
//    Rev 1.35   Sep 27 2000 16:43:22   dt17817
// DataElement::setValue parameter list changed, needed to sync with the changes
// so calls to formatValue() would work again
//
//    Rev 1.34   Sep 08 2000 12:30:32   dt17817
// Fix problem where Conditions were created in getField() when a client/market was specified and no
//    client/market override existed.
// Fix problem where "base" (non overrideable) fields were not found if a client/market was specified
//
//    Rev 1.33   Sep 05 2000 06:20:02   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
//
//
//    Rev 1.32   Aug 24 2000 07:27:00   dtwk
// Add in more support for clients and markets
//
//
//    Rev 1.31   Aug 09 2000 08:42:12   dtwk
// Add in support for clients and markets
//
//    Rev 1.30   Jun 08 2000 11:49:54   dtwk
// Add support for case-insensitivity
//
//    Rev 1.29   May 31 2000 09:33:12   dtwk
// Change locale string to ClientLocale object
//
//    Rev 1.28   Apr 10 2000 11:47:32   dtwk
// Updates for thread-safety
//
//    Rev 1.27   Apr 04 2000 10:01:58   dtwk
// Updates for thread safety
//
//    Rev 1.26   Dec 12 1999 13:05:54   dtwk
// Fix for problem with instantiating a repeatable data set
// before instantiating a data set that contains the repeat data
// set as one of it's fields
//
//    Rev 1.25   Nov 29 1999 07:31:54   dtwk
// Add support for redefines
//
//    Rev 1.24   Nov 09 1999 07:15:06   dtwk
// Add parameter to formatValue for STRIP_TRAILING and STRIP_LEADING
//
//    Rev 1.23   Nov 08 1999 07:29:30   dtwk
// Fix PropertyRepository::unformatValue to work with substitutions
//
//    Rev 1.22   Oct 07 1999 14:05:46   DCYK
// Add support for CLIENT field in bin file.
//
//
//    Rev 1.21   Oct 06 1999 11:35:46   DCYK
// Add support for redefines.
//
//
//    Rev 1.20   Sep 03 1999 12:52:42   dtwk
// Add isValidForHost
// Tweak method signature for unformatValue
// Fix return codes for formatValue
//
//    Rev 1.19   Aug 26 1999 13:51:26   dtwk
// Remove parameter from formatValue for Jerry
//
//    Rev 1.18   Aug 20 1999 15:59:34   DCYK
// Call "removeMaskFromValue" from isValid.
//
//
//    Rev 1.17   Aug 20 1999 15:35:44   DCYK
// Added locale parameter to isValid, added isI18NValid function.
//
//
//    Rev 1.16   Aug 16 1999 14:46:26   DCYK
// Added "unformatValue".  Added more parameters to "formatValue".  Re-ordered parameters.
//
//
//    Rev 1.15   Aug 06 1999 14:21:20   DCYK
// Performance improvements.
//
//
//    Rev 1.14   Aug 05 1999 16:38:00   DCYK
// Performance improvements from Tom H. & Michael M.
//
//
//    Rev 1.13   Aug 04 1999 09:49:52   DCYK
// Fix bug returning severity from from getField.
// Add isValid and formatValue methods.
//
//
//    Rev 1.12   Jul 29 1999 15:12:46   DCYK
// Un-comment call in fieldHasLocale.
//
//
//    Rev 1.11   Jul 28 1999 14:19:24   DCYK
// Performance improvements.
//
//
//    Rev 1.10   Jul 26 1999 09:51:08   DCYK
// Change "USen" to "enUS".
//
