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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <commonport.h>
#include <bfproc\abstractprocessconstants.h>
#include <bfdata\bffieldid.hpp>
#include <bfproc\bfcontainerid.hpp>
#include <bfcbo\bfdatagroupid.hpp>

// Forward reference
class AbstractProcess;
class BFAbstractCBO;
class BFProperties;

/**
  * This class contains the details for a field used by a business process.
  *
  * For each business process,
  * these objects are stored in a map with the key being generated from the
  * fieldID and listID (so entries are unique by list).  If we need to support
  * the same name access across multiple CBOs then we have an open issue.
  *
  * When defining a static array of these structures in your subclass, set the
  * idField_ of the last item to 0 to note the end of the array.
  *
  * When defining list IDs, use 0 if there is no associated list or a number
  * > 0 and < 10000 to identify a list (this is the same number used for list ID
  * in UpdateableListDetails.
  * Also, when defining the static array entries you should either set the rpCBO
  * parameter to NULL (if no CBO will be associated) or a constant value which
  * will make it easy to substitute in a real CBO pointer during doInit.
  *
  * @author Jerry Leenerts
  * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/02/99</dd></dl>
  * @version 0.1
  */
class FieldDetails 
{
public:
   friend AbstractProcess;
   /**
    * Constructor for use in static arrays
    * 
    * @param containerID
    *                ID of container
    * @param fieldID ID of field
    * @param flag    E_FIELDPROCESS flag indicating type of processing
    * @param szTag   name of field, NULL if field is in the data dictionary
    */
   FieldDetails( const BFContainerId& idContainer, const BFFieldId &fieldID, E_FIELDPROCESSFLAG flag, const I_CHAR *szTag = NULL );
   /**
     * Copy constructor for moving to container.  Note that the pointer value 
     * will be saved, but the pointer will be marked as invalid.  The pointer
     * must be specifically set after this point for it to be useable.
     * @param ufd - A reference to another FieldDetails object.
     */
   FieldDetails( const FieldDetails &ufd );
   virtual ~FieldDetails();

   /**
     * Get the CBO id.
     * @returns an integer id.
     */
   const BFContainerId& getContainerID() const
   {
      return(idContainer_);
   }
   /**
    * Get current errors associated with the field.
    * An exception will be thrown if the associated CBO is not valid or field
    * not found.
    * 
    * @param rpPtr      BFCBO pointer for object to get field from.
    * @param idDataGroup   Group to use for rollback processing.
    * @param conditions upon return will contain all conditions currently associated with this field.
    *                   returns highest SEVERITY for the field
    * 
    * @return 
    */
   SEVERITY getErrors( BFAbstractCBO *rpPtr, const BFDataGroupId& idDataGroup, CONDITIONVECTOR &conditions); 
   /**
     * Get the field value.
     * An exception will be thrown if the associated CBO is not valid or field
     * not found.
     * @param rpPtr - BFBase pointer for object to get field from.
     * @param bFormatted - true = get formatted value, false = get raw value.
     * @param strValueOut - A string reference for the returned field value.
     * @param idDataGroup - Group to use for rollback processing.
     */
   void getField( BFAbstractCBO *rpPtr, bool bFormatted, DString &strValueOut, const BFDataGroupId& idDataGroup );
   /**
     * Get associated field attributes.
     * An exception will be thrown if the associated CBO is not valid or field
     * not found.
     * @param rpPtr - BFBase pointer for object to get field from.
     * @param idDataGroup - Group to use for rollback processing.
     * @returns const reference pointer to BFProperties for field
     */
   const BFProperties *getFieldAttributes( BFAbstractCBO *rpPtr, const BFDataGroupId& idDataGroup );
   /**
     * Get the field id.
     * @returns a long id.
     */
   const BFFieldId &getFieldID() const
   {
      return(idField_);
   }
   /**
     * Get the field name either from stored tag or data dictionary.
     * @returns a string reference with the tag.
     */
   const DString &getFieldName();
   // temporary
   E_FIELDPROCESSFLAG getFlag() const
   {
      return(_eProcessFlags);
   }
   /**
    * Set the field value.
    * An exception will be thrown if the associated CBO is not valid or field
    * not found.
    * 
    * @param rpPtr    Void pointer that is assumed to be a BFBase * for now.
    * @param bFormattedFlag
    *                 true = get formatted value, false = get raw value.
    * @param strValue A string reference to the value to set.
    * @param idDataGroup Group to use for rollback processing.
    * 
    * @return 
    */
   SEVERITY setField( void *rpPtr,
                      bool bFormattedFlag,
                      const DString &strValue,
                      const BFDataGroupId& idDataGroup );
private:
   E_FIELDPROCESSFLAG _eProcessFlags;   // SUBCLASS_PROCESS, RELAY_TO_PARENT
   const BFContainerId idContainer_;
   const BFFieldId idField_;
   DString _strName;     // Should only be used for non- data dictionary fields

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/FieldDetails.hpp-arc  $
 * 
 *    Rev 1.9   Jan 06 2003 16:43:44   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.8   Nov 27 2002 15:04:34   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.7   Oct 09 2002 17:40:56   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.6   Sep 02 2002 17:43:50   PURDYECH
 * fieldid problem
 * 
 *    Rev 1.5   Aug 29 2002 12:51:16   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 18:08:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   22 Mar 2002 15:11:52   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.2   Aug 02 2000 15:31:34   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Feb 15 2000 18:55:00   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:48   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Dec 07 1999 10:47:26   DT24433
 * use abstractprocessconstants.h
 * 
 *    Rev 1.7   Nov 19 1999 17:33:02   DT24433
 * changed return on getErrors
 * 
 *    Rev 1.6   Nov 11 1999 08:51:28   DT24433
 * added getFieldAttributes
 * 
 *    Rev 1.5   Nov 05 1999 15:23:54   DT24433
 * added getErrors
 * 
 *    Rev 1.4   21 Oct 1999 08:41:04   HSUCHIN
 * Changed getField parm from void * to BFBase *.
 * 
 *    Rev 1.3   Sep 21 1999 11:24:40   DT24433
 * removed unused constructor
 * 
 *    Rev 1.2   Aug 03 1999 15:02:28   DT24433
 * container changes
 * 
 *    Rev 1.1   Jul 08 1999 10:03:42   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

