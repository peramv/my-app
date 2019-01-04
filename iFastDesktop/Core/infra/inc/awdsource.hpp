#ifndef AWDSOURCE_HPP
#define AWDSOURCE_HPP

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

/**@pkg DIAWDI */    

#ifndef AWDDATA_HPP
   #include "awddata.hpp"
#endif

#undef DIAWDI_LINKAGE
#ifdef DIAWDI_DLL
   #define DIAWDI_LINKAGE CLASS_EXPORT
#else
   #define DIAWDI_LINKAGE CLASS_IMPORT
#endif

/**
 * An AwdSource object represents a source object on an AWD server.  Since the
 * class AwdSource is a pure virtual class, it may only be instantiated through
 * the AwdInterface by calling the method AwdInterface::retrieveSource().
 */
class DIAWDI_LINKAGE AwdSource
{
   // Public enums & typedefs
   public:
      enum ObjectFormat
      {
         NO_FORMAT       = 0,
         IBM_IOCA        = 'I',
         IBM_PTOCA       = 'P',
         ASCII_text      = 'A',
         PCX             = 'X',
         MODCA           = 'M',
         Voice_recording = 'V'
      };

   // Constuctor and Destructor
   public:
      /**
       * Default constructor
       */
      AwdSource();


      /**
       * Default destructor
       */
      virtual ~AwdSource();

   // Public
   public:
      /**
       * Used to get the current format of the source
       *
       * @return The object format.
       */
      ObjectFormat getObjectFormat() const
      {
         return m_format;
      }

      /**
       * Returns the AwdKey representing the object's key on the AWD server.
       *
       * @return Pointer to an AwdKey object.
       */
      const AwdKey *getKey() const;

      /**
       * Returns the AwdData object representing the object on the AWD server
       * and containing all AWD & LOB values.
       *
       * @return Reference to an AwdData object.
       */
      const AwdData &getData() const;

      /**
       * Returns the source type (OBJT) for the object.
       *
       * @return The source type
       */
      const DString &getSourceType() const;

      /**
       * Used to get specific LOB values for the object.
       *
       * @param name - AWD Data dictionary short name.
       *
       * @return The LOB value.
       */
      const DString &getLobValue( const DString &name ) const;

   // Public virtual
   public:
      /**
       * The pure virtual method will invoke the AWD Image window to display
       * the actual image for the source.
       */
      virtual void displayImage() = 0;

   // Private Members
   private:
      AwdSource( const AwdSource &copy );
      const AwdSource &operator=( const AwdSource &copy );

   // Protected members
   protected:
      AwdData m_data;
      ObjectFormat m_format;
};



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
// $Log:   Y:/VCS/iFastAWD/inc/awdsource.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:54   kovacsro
//Initial revision.
// 
//    Rev 1.3   23 Oct 2000 12:00:18   dt14177
// cleanup
// 
//    Rev 1.2   Apr 17 2000 15:00:02   DMUM
// Comments to JavaDoc
//
//    Rev 1.1   Aug 26 1999 12:58:52   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of a source.
//
//    Rev 1.0.1.0   Aug 04 1999 10:32:38   DMUM
// Added comments
//
//    Rev 1.0   Aug 04 1999 09:48:46   DMUM
//
//
//

#endif // AWDSOURCE_HPP

