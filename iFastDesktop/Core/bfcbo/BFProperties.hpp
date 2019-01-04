#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
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
// ^FILE   : BFProperties.hpp
// ^AUTHOR : Mihai Virgil Buzila 
// ^DATE   : October 1999
//
// ^CLASS    : BFProperties
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <commonport.h>
#include <dstring.hpp>

// Forward references
class BFDataFieldProperties;
class BFFieldId;

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * This class contains the properties related to a field
 * 
 * @author Mihai Virgil Buzila
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> October, 1999 </dd></dl>
 * @version 0.1
 */
class BFBASE_LINKAGE BFProperties  
{
public:
   /**
    * constructor
    * 
    * @param pProps The field properties associated with this BFProperties object
    */
   BFProperties(const BFDataFieldProperties* pProps );

   BFProperties( const BFProperties& rhs );
   /**
    * destructor
    */
   virtual ~BFProperties();

   BFProperties& operator=( const BFProperties& rhs );

   /**
    * returns the maximum lenght of the field
    */
   int   getMaxLength() const { return(_mMaxLength);}
   /**
    * returns the minimum lenght of the field
    */
   int   getMinLength() const { return(_mMinLength);}
   /**
    * returns the default value of the field
    */
   const DString &getDefaultValue( DString &strValueOut ) const;
   /**
    * returns true if the field is required
    */
   bool  isRequired() const { return(_mRequired);}
   /**
    * returns true if the field is read only
    */
   bool  isReadOnly() const { return(_mReadOnly);}
   /**
    * gets all substite values associated with this field
    * @param strValueOut   - where the subst list should be filled in
    */
   bool  getAllSubstituteValues( DString &strValueOut ) const; 
   /**
    * gets the mask for this field 
    * @param strValueOut   - where the mask should be filled in
    */
   bool  getMask( DString &strValueOut ) const; 
   /**
    * gets the label for this field 
    * @param strValueOut - where the label should be filled in
    */
   const DString &getFieldLabel( DString &strValueOut ) const;
   /**
    * gets the substitute values for this field 
    * @param strValueOut - where the substitute values should be filled in
    */
   void  getSubstituteValues( DString &strValueOut ) const;
   /**
    * gets all substitute values for this field 
    */
   DString* getAllSubstituteValues() const
   {
      return(_pAllSubstituteValues); 
   }
   /**
    * initialises subst values
    * @param allSubstString  - what string should be used
    */
   void initUnformattedSubstValues( const DString &allSubstString );
   /**
    * sets the subst values
    * @param substValues - string containing the subst values
    */
   void setSubstituteValues( DString * substValues );
   /**
    * appends string value to subst set
    * @param strValue - string containing subst values
    */
   void appendValueToSubst( const DString &strValue ) ;
   /**
    * sets all subst values
    * @param strValues - string containing all subst values
    */
   void setAllSubstituteValues( const DString &strValues );

   bool isDynamicCreatedSubst(){ return(_bDynamicCreatedSubst);}
   bool isValidKey(const DString& strKey);
   bool isValidValue(const DString& strValue);
   bool formatValue( const BFFieldId& idField, DString & InRetValue, bool bFormat );
   bool unformatValue( const BFFieldId& idField, DString & InRetValue, bool bUnformat );
   void reinitAllSubstValues();

private :   
   bool isSubstFormattedValueSet(){ return(_isSubstFormattedValueSet);};
   void checkSubstValues();

   void setReadOnly( bool readonly );
   void setMask( const DString & mask );

   void setRequired( bool required );

   const BFDataFieldProperties* pProps_;

   int                     _mMinLength;
   int                     _mMaxLength;
   DString  *              _pMask;
   DString  *              _pDefaultValue;
   DString  *              _pSubstituteValues;
   DString  *              _pAllSubstituteValues;
   DString  *              _pFieldLabel;
   bool                    _mRequired;
   bool                    _mReadOnly;

   bool                    _isSubstFormattedValueSet;
   bool                    _bDynamicCreatedSubst;
   friend class BFCBO;

   struct item
   {
      DString m_key;
      DString m_value;
      item( const DString & lKey, const DString & lValue ): m_key(lKey), m_value( lValue )
      {}
   };
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfcbo/BFProperties.hpp-arc  $
//
//   Rev 1.20   05 May 2009 10:08:12   popescu
//Added support for drop down comboxes. The value typed in is appended to the subst set.
 * 
 *    Rev 1.19   Nov 27 2002 15:02:46   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.18   Oct 09 2002 17:40:08   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.17   Sep 03 2002 11:08:48   PURDYECH
 * Further BFFieldId fixes
 * 
 *    Rev 1.16   Aug 29 2002 12:51:14   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.15   Aug 16 2002 14:07:22   PURDYECH
 * Added copy ctor and assignment operator
 * 
 *    Rev 1.14   Jun 05 2002 16:25:56   PURDYECH
 * FormatField/UnformatField changes
 * 
 *    Rev 1.13   22 May 2002 22:21:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   22 May 2002 18:08:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   22 Mar 2002 15:11:40   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.10   May 29 2001 10:22:18   YINGBAOL
 * add formatValue method
 * 
 *    Rev 1.9   03 May 2001 14:03:24   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Nov 21 2000 09:52:02   YINGBAOL
 * add isValidKey and isValidValue methods
 * 
 *    Rev 1.7   Nov 02 2000 16:29:20   HUANGSHA
 * added variable to indicate the dynamic created subst
 * 
 *    Rev 1.6   Sep 27 2000 15:10:44   VASILEAD
 * Added ClientLocale to BFProperties
 * 
 *    Rev 1.5   Jul 21 2000 17:09:40   BUZILA
 * documentation added
 * 
 *    Rev 1.4   Jun 13 2000 17:39:32   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.3   May 31 2000 16:42:06   BUZILA
 * adding masks
 * 
 *    Rev 1.2   May 11 2000 16:17:58   BUZILA
 * reimplementation
 * 
 *    Rev 1.1   Feb 15 2000 18:54:58   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:46   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Dec 19 1999 16:38:36   BUZILA
// changes related to substitutionLists handling
// 
//    Rev 1.4   Nov 20 1999 19:38:24   BUZILA
// added BFProperties repository
// 
//    Rev 1.3   Nov 11 1999 07:06:54   DT24433
// added external linkage lines
// 
//    Rev 1.2   Nov 10 1999 17:30:18   DT24433
// made get methods const and added revision area
 * 
 */
