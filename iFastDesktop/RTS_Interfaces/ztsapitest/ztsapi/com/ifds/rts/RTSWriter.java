package com.ifds.rts;

import java.io.*;

/**
 * RTSWriter will write an RTS encode buffer to an otuput 
 * stream. Typically the output stream will be for an
 * open socket to an RTS host of client, however, any 
 * output  stream may be used to back the reader.
 */
public class RTSWriter
{
   private final BufferedOutputStream _outStream;

   /**
    * Constructs an RTSWriter backed by the given output stream. The
    * default character encoding is assumed for the stream.
    * 
    * @param outStream Open stream which backs the RTSWriter.
    */
   public RTSWriter( OutputStream outStream )
   {
      _outStream = new BufferedOutputStream( outStream, 2048 );
   }

   /**
    * Writer the passed buffer to the backing output stream
    * in RTS record format.
    * 
    * @param buffer the RTS encoded buffer to be written.
    * @exception IOException
    */
   public void write( RTSBuffer buffer ) throws IOException
   {
      byte[] bytes = buffer.toByteArray();
      _outStream.write( bytes, 0, bytes.length );
      _outStream.write('\n');  //set the RTS 'EOT' character
      _outStream.flush();
      
      if ( RTSTraceWriter._traceFileWriter != null )
         RTSTraceWriter._traceFileWriter.traceBufferWritten( new String( bytes ) );

      RTSTraceWriter.traceClientViewsBufferWritten(new String( bytes ),Thread.currentThread().getName());
   }

   /**
    * Closes the underlying output stream.
    * 
    * @exception IOException
    */
   public void close() throws IOException
   {
      _outStream.close();
   }
}

