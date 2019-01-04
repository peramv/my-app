#ifndef ICOMMCHANNEL_H
#define ICOMMCHANNEL_H

#include "Messaging.h"

namespace MessagingFramework
{

/**
 * The ICommChannel interface is an abstract base class that provides
 * an interface for inter-process communications (IPC) and networking
 * technologies.
 */
class DIMESSAGE_LINKAGE ICommChannel
{
   public:
      /**
       * Destructor
       */
      virtual ~ICommChannel() {}


      /**
       * Reads a string from the communications channel into an allocated
       * buffer. The caller should *NOT* deallocate this buffer.
       *
       * @return pointer to the internal buffer that holds the read data
       */
      virtual char* read() = 0;


      /**
       * Reads a string from the communications channel into a buffer
       * allocated by the caller of this method.
       *
       * @param buffer - pointer to the buffer to populate
       * @param bufferLen - size of the buffer
       *
       * @return boolean indicating success/failure
       */
      virtual bool read( char* buffer, long bufferLen ) = 0;


      /**
       * Reads a variable number of strings from the communications
       * channel.  Each string read will be added to the specified vector.
       * This method should be used to read data that was written using
       * the write method that writes out a collection (vector) of strings.
       *
       * @param vecStrings - the vector to populate with strings read
       *
       * @return boolean indicating success/failure
       */
      virtual bool read( std::vector< std::string >& vecStrings ) = 0;


      /**
       * Writes a string to the communications channel.
       *
       * @param buffer - pointer to the buffer to write
       *
       * @return boolean indicating success/failure
       */
      virtual bool write( const char* buffer ) = 0;


      /**
       * Writes a string to the communications channel.
       *
       * @param buffer - pointer to the buffer to write
       * @param bufferLen - number of bytes to write from the buffer
       *
       * @return boolean indicating success/failure
       */
      virtual bool write( const char* buffer, long bufferLen ) = 0;


      /**
       * Writes a collection of strings to the communications channel.
       *
       * @param vecBuffers - vector of strings to write
       *
       * @return boolean indicating success/failure
       */
      virtual bool write( const std::vector< const char* >& vecBuffers ) = 0;


      /**
       * Closes the communications channel.
       *
       * @return boolean indicating success/failure
       */
      virtual bool close() = 0;


      /**
       * Determines whether the communications channel is still open.
       *
       * @return boolean indicating if the channel is open
       */
      virtual bool isOpen() const = 0;
};

}


#endif


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


