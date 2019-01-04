#pragma once

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

//CP20021120/**@pkg BFAWDI */    

#include <commonport.h>
#include <dstring.hpp>

#undef BFAWDI_LINKAGE
#ifdef BFAWDI_DLL
   #define BFAWDI_LINKAGE CLASS_EXPORT
#else
   #define BFAWDI_LINKAGE CLASS_IMPORT
#endif

/**
 * This class is used to build criteria for a performing a lookup on the AWD
 * server.
 *
 * A single BFAwdLookupCriteria object represents either a single comparison or
 * a single order by criterium.
 *
 * <b>Note:</b>Depending on settings on the AWD server and the field that is
 * used for the ordering criteria, the order by criteria may be ignored.
 *
 * @see CriteriaVector
 */
class BFAWDI_LINKAGE BFAwdLookupCriteria
{
public:
   enum Comparison
   {
      UNDEFINED = -1,
      EQUAL_TO,
      LESS_THAN,
      GREATER_THAN,
      GREATER_THAN_OR_EQUAL,
      LESS_THAN_OR_EQUAL,
      NOT_EQUAL
   };

   enum Order
   {
      NO_ORDER = -1,
      ASCENDING,
      DESCENDING
   };

public:
   /**
    * Constructor.  Used to define lookup criteria for comparison.
    *
    * @param field - An AWD field (AWD data dictionary entry - short name)
    * @param compare - Type of comparison
    * @param value - Value to use for comparison
    */
   BFAwdLookupCriteria( const DString &field,
                        const Comparison compare,
                        const DString &value );

   /**
    * Constructor.  Used to define lookup criteria for ordering.
    *
    * @param field - An AWD field (AWD data dictionary entry - short name)
    * @param order - ASCENDING or DESCENDING
    */
   BFAwdLookupCriteria( const DString &field,
                        const Order order = ASCENDING );

   /**
    * Default constructor
    */
   BFAwdLookupCriteria();

   /**
    * Copy Constructor
    *
    * @param copy   The BFAwdCriteria object to copy.
    */
   BFAwdLookupCriteria( const BFAwdLookupCriteria &copy );

   /**
    * Destructor
    */
   virtual ~BFAwdLookupCriteria();

public:
   /**
    * Used to determine if the criteria has been properly initialized
    * as either a comparison or ordering criteria.
    *
    * @return True if is a valid criteria object.
    */
   bool isValid() const;

   /**
    * Used to determin if this criteria object is an ordering
    * criteria.
    *
    * @return True if the criteria is an order by object.
    */
   bool isOrderBy() const { return(NO_ORDER != m_order);}

   /**
    * If this criteria is for ordering, this will return either
    * ASCENDING or DESCENDING.  If not, this will return NO_ORDER.
    *
    * @return The order by which the results should be returned.
    */
   Order getOrder() const { return(m_order);}

   /**
    * Returns the name of the field to compare with or order by.
    *
    * @return The name of the field.
    */
   const DString &getField() const { return(m_field);}

   /**
    * If this criteria is a comparison criteria, this will return the
    * comparison type.
    *
    * @return The type of comparison.
    */
   const Comparison getComparison() const { return(m_compare);}

   /**
    * If this criteria is a comparison critera, then this will return the
    * value to compare with.
    *
    * @return The value to use for comparison.
    */
   const DString &getValue() const { return(m_value);}

   /**
    * Assignment operator.
    *
    * @param copy - The BFAwdCriteria object to copy.
    *
    * @return Reference to self.
    */
   BFAwdLookupCriteria &operator=( const BFAwdLookupCriteria &copy );

private:
   DString m_field;
   DString m_value;
   Comparison m_compare;
   Order m_order;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfawdi/bfawdlookupcriteria.hpp-arc  $
//
//   Rev 1.2   Nov 27 2002 14:51:46   PURDYECH
//Documentation Cleanup
//
//   Rev 1.1   Oct 09 2002 17:39:54   PURDYECH
//New PVCS Database
//
//   Rev 1.0   28 May 2002 12:11:20   SMITHDAV
//Initial revision.
// 
//    Rev 1.4   23 Oct 2000 11:22:10   dt14177
// cleanup
// 
//    Rev 1.3   Apr 24 2000 10:38:32   DMUM
//  
//
//    Rev 1.2   May 18 1999 08:50:12   DMUM
//
//
//    Rev 1.1   Apr 09 1999 13:26:20   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.2.0   Mar 31 1999 13:14:52   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0.1.0   Feb 09 1999 10:15:14   DMUM
// Added documentation
//
//    Rev 1.0   Jan 20 1999 09:08:46   DMUM
//
//
//

