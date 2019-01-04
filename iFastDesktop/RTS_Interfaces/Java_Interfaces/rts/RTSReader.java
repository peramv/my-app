package com.ifds.rts;

import java.io.*;
import java.text.ParseException;

/**
 * RTSReader will read an RTS encode request or response from 
 * an input stream. Typically the input stream will be for an
 * open socket to an RTS host or client, however, any input 
 * stream may be used to back the reader.
 */
public final class RTSReader
{
   private final BufferedInputStream _inStream;

   /**
    * Constructs an RTSReader backed by the given input stream. The
    * default character encoding is assumed for the stream.
    * 
    * @param inStream Open stream which backs the RTSReader.
    */
   public RTSReader( InputStream inStream )
   {
      _inStream = new BufferedInputStream( inStream, 2048 );
   }

   /**
    * Reads the next RTS encoded record from the backing
    * stream, and returns a new RTSResponseDecodeBuffer.
    * This method blocks until a record is returned, an
    * interupt is posted to the thread or an IOException
    * it thrown.
    * 
    * @param encoding The character encoding of the buffers field data.
    * @return Response buffer constructed from the underlying stream.
    * @exception IOException
    */
   public RTSResponseDecodeBuffer readResponse( String encoding ) throws IOException, ParseException
   {
      byte[] responseBytes = readBuffer();
      
      if ( RTSTraceWriter._traceFileWriter != null )
         RTSTraceWriter._traceFileWriter.traceResponseRead( new String( responseBytes ) );
      
      RTSTraceWriter.traceClientViewsResponseRead(new String( responseBytes ), Thread.currentThread().getName());

      return new RTSResponseDecodeBuffer( responseBytes, encoding );
   }

   /**
    * Reads the next RTS encoded record from the backing
    * stream, and returns a new RTSRequestDecodeBuffer.
    * This method blocks until a record is returned, an
    * interupt is posted to the thread or an IOException
    * it thrown.
    * 
    * @param encoding The character encoding of the buffers field data.
    * @return Request buffer constructed from the underlying stream.
    * @exception IOException
    */
   public RTSRequestDecodeBuffer readRequest( String encoding ) throws IOException, ParseException
   {
      byte[] requestBytes = readBuffer();
      
      if ( RTSTraceWriter._traceFileWriter != null )
         RTSTraceWriter._traceFileWriter.traceRequestRead( new String( requestBytes ) );
      
      return new RTSRequestDecodeBuffer( requestBytes, encoding );
   }

   /**
    *
    */
   private byte[] readBuffer() throws IOException
   {

      ByteArrayOutputStream outStream = new ByteArrayOutputStream() ;

      boolean escaped = false;
      while ( true )
      {
         int b = _inStream.read();

         if ( b == -1 )
            throw new EOFException();

         if ( !escaped && b == '\n' )
            return outStream.toByteArray();

         outStream.write( b );
         
         if ( escaped )
            escaped = false;
         else if ( b == '\\' )
            escaped = true;

      }

   }

   /**
    * Closes the underlying input stream.
    * 
    * @exception IOException
    */
   public void close() throws IOException
   {
      _inStream.close();
   }

}
