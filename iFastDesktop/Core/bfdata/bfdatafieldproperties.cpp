#include "stdafx.h"
#include "bfdatafieldproperties.hpp"

const DString& s_VarText_FldProp_DVF( const ClientLocale& locale )
{
   static const DString dstrDefValue( I_("") );
   return( dstrDefValue );
}
const DString& s_VarText_FldProp_FLF( const ClientLocale& locale )
{
   static const DString dstrFldLabel( I_("") );
   return( dstrFldLabel );
}
const BFDataFieldProperties s_VarText_FldProp(
       BFDataFieldProperties::Type::vartext // field is a vartext field
      ,idVarTextField // generic field
      ,-1 // variable length
      ,0 // minimum length
      ,0 // decmials
      ,NULL  // mask chooser function
      ,s_VarText_FldProp_DVF // default value
      ,NULL // default value (integer)
      ,NULL // default value (double)
      ,s_VarText_FldProp_FLF // label
      ,I_("") // field name
      ,false // allow Nulls
      ,None // justification
      ,NULL // no substitution set
      );



BFDataFieldPropertiesMap& BFDataFieldProperties::getMap()
{
   static BFDataFieldPropertiesMap s_map;
   return( s_map );
}

const BFDataFieldProperties* BFDataFieldProperties::get( const BFFieldId& id )
{
   if( id > idVarTextField )
   {
      // variable text fields always have the same properties
      return &s_VarText_FldProp;
   }
   BFDataFieldPropertiesMap& propMap = getMap();
   BFDataFieldPropertiesMap::const_iterator it = propMap.find( id );
   if( it == propMap.end() ) BF_THROW( BFDataFieldPropertiesException );
   const BFDataFieldProperties* pProp = (*it).second;
   return(pProp);
}

bool BFDataFieldProperties::getAllSubstituteValues(
                                                  DString &subValues,
                                                  const ClientLocale& locale,
                                                  bool bUsePropertiesOrder /*= false*/ ) const
{
   const BFSubstitutionSet* pSubSet = getSubstitutionSet( locale );
   if( NULL == pSubSet )
   {
      return( false );
   }

   subValues = NULL_STRING;
   pSubSet->getAsIDI( subValues, bUsePropertiesOrder );
   return(true);
}


