/*
 * @(#)RTSTransaction.java	2.0 99/08/17
 * 
 * Copyright (c) 1999 DST Canada, Inc. All Rights Reserved.
 * 
 * This software is the confidential and proprietary information of DST
 * Canada, Inc. ("Confidential Information").  You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered into
 * with DST.
 * 
 * DST MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, OR NON-INFRINGEMENT. DST SHALL NOT BE LIABLE FOR ANY DAMAGES
 * SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
 * THIS SOFTWARE OR ITS DERIVATIVES.
 */
package com.ifds.rts;

import java.util.*;
import java.net.*;
import java.text.*;
import java.io.*;

/**
 * RTSTransaction
 * Superclass for RTS Transactions.
 *
 * @see RTSJAPP.RTSSession
 * @see RTSJAPP.RTSCommunication
 * @see ZTSResponse.RTSResponse
 *
 * @version	2.0, 99/08/17
 */

public class RTSTransaction implements Serializable
{

   // RTS ProviderID+ClientID+DatabaseID
   private static final String rtsHeaderPrefix = new String("010000");   
   // RTS UserID+Password+PHandleID+PThreadID+Flags+InstanceID
   private static final String rtsHeaderSuffix = new String("                000000000000000000001");   

   private static final int maxRetries = 5;
   private static final int sleepTime = 50; //50 milliseconds


   private static final StringBuffer tempBuffer = new StringBuffer();

   private final SimpleDateFormat dateFmt = new SimpleDateFormat("MMddyyyy");   //Simple date format cannot be made static
   private static final DecimalFormat deciFmt = new DecimalFormat("#0.00##");    //can be static
   private static final DecimalFormat tranFmt = new DecimalFormat("00000");      //can be static

   private final StringBuffer _requestBuffer;
   private final RTSTraceListener _traceListener;
   private boolean _firstField = true;

   /**
    *
    */
   public RTSTransaction( int transactionID )
   {
      _requestBuffer = new StringBuffer(1024);
      _traceListener = null;
      formatHeader(transactionID);
   }

   /**
    *
    */
   public RTSTransaction( int transactionID, RTSTraceListener traceListener )
   {
      _requestBuffer = new StringBuffer(1024);
      _traceListener = traceListener;
      formatHeader(transactionID);
   }

   /**
    *
    */
   private final void formatHeader( int transactionID ) 
   {
      _requestBuffer.insert( 0,  rtsHeaderPrefix );  
      _requestBuffer.insert( 6,  tranFmt.format(transactionID) );
      _requestBuffer.insert( 11, rtsHeaderSuffix);  
      _requestBuffer.setLength( 48 );
   }

   /**
    *
    */
   private final void appendEncodedField( String field ) 
   {
      if ( _firstField )
      {
         _requestBuffer.append( "F" );
         _requestBuffer.append( field );
         _firstField = false;
      }
      else
      {
         _requestBuffer.append( ",F" );
         _requestBuffer.append( field );
      }

   }

   /**
    *
    */
   private final void appendUnknownField() 
   {
      if ( _firstField )
      {
         _requestBuffer.append( "T" );
         _firstField = false;
      }
      else
      {
         _requestBuffer.append( ",T" );
      }

   }


   /**
    *  append Boolean value to request buffer
    */
   public final void appendField(Boolean val)
   {

      if ( _traceListener != null)
         _traceListener.traceAppendField( val );

      if ( val == null )
         appendUnknownField();
      else if ( val.booleanValue() == true )
         appendEncodedField("Y");
      else
         appendEncodedField("N");

   }

   /**
    *  append Date value to request buffer
    */
   public final void appendField(Date val)
   {

      if ( _traceListener != null)
         _traceListener.traceAppendField( val );
      
      if ( val == null )
         appendUnknownField();
      else
         appendEncodedField( dateFmt.format(val) );
   }

   /**
    *  append Double value to request buffer
    */
   public final void appendField(Double val)
   {

      if ( _traceListener != null)
         _traceListener.traceAppendField( val );
      
      if ( val == null )
         appendUnknownField();
      else
         appendEncodedField( quoteString( deciFmt.format(val) ) );
   }

   /**
    *  append Integer value to request buffer
    */
   public final void appendField(Integer val)
   {
      if ( _traceListener != null)
         _traceListener.traceAppendField( val );
      
      if ( val == null )
         appendUnknownField();
      else
         appendEncodedField( val.toString() );
   }

   /**
    *  append String value to request buffer
    */
   public final void appendField(String val)
   {
      if ( _traceListener != null)
         _traceListener.traceAppendField( val );

      if ( val == null )
         appendUnknownField();
      else
         appendEncodedField( quoteString(val) );
   }

   /**
    *
    */
   private static String quoteString( String s )
   {

      if ( /*(s.indexOf(',')==-1) &&*/ (s.indexOf('\\') == -1) && (s.indexOf('\n') == -1) )
      {
         return s;
      }

      tempBuffer.setLength(0);
      for ( int x = 0; x < s.length(); x ++ )
      {
         if ( /*s.charAt(x) == ',' ||*/ s.charAt(x) == '\\' || s.charAt(x) == '\n' ) 
            tempBuffer.append("\\");
         tempBuffer.append(s.charAt(x));
      }

      return tempBuffer.toString();
   }


   /**
    *
    */
   private static Socket createSocket( String ipAddress, int portNumber ) throws IOException
   {

      Socket rtsSocket;

      int numTries = 0;

      while ( true )
      {
         //make new socket connection to RTS Server, close connection after reading response or on error.
         try
         {
            rtsSocket = new Socket( ipAddress, portNumber );
         }
         catch ( IOException ioe )
         {
            numTries++;
            if ( numTries > maxRetries )
            {
               throw new IOException("RTS Connection Error : " + ioe.toString());
            }
            try { Thread.sleep(sleepTime); } catch ( Exception e ) { }
            continue;
         }
         break;
      }

      return rtsSocket;
   
   }

   /**
    * 
    */
   public RTSResponse send( String ipAddress, int portNumber ) throws IOException
   {

      Socket rtsSocket = createSocket( ipAddress, portNumber );

      try
      {
         return send( rtsSocket );
      }
      finally
      {
         rtsSocket.close();
      }

   }

   /**
    * 
    */
   public RTSResponse send( String ipAddress, int portNumber, String encoding ) throws IOException
   {

      Socket rtsSocket = createSocket( ipAddress, portNumber );

      try
      {
         return send( createSocket( ipAddress, portNumber ), encoding );
      }
      finally
      {
         rtsSocket.close();
      }
   
   }

   /**
    *
    */
   public RTSResponse send( Socket rtsSocket ) throws IOException
   {
      return send( rtsSocket.getOutputStream(), rtsSocket.getInputStream() );
   }

   /**
    *
    */
   public RTSResponse send( Socket rtsSocket, String encoding ) throws IOException
   {
      return send( rtsSocket.getOutputStream(), rtsSocket.getInputStream(), encoding );
   }

   /**
    *
    */
   public RTSResponse send( OutputStream requestStream, InputStream responseStream ) throws IOException
   {
      return send( new OutputStreamWriter( requestStream ), 
                   new InputStreamReader( responseStream ) );
   }

   /**
    *
    */
   public RTSResponse send( OutputStream requestStream, InputStream responseStream, String encoding ) throws IOException
   {
      return send( new OutputStreamWriter( requestStream, encoding ), 
                   new InputStreamReader( responseStream, encoding ) );
   }

   /**
    *
    */
   public RTSResponse send( Writer requestWriter, Reader responseReader ) throws IOException
   {
      
      StringBuffer responseBuffer = new StringBuffer(2048);
      responseReader = new BufferedReader( responseReader, 2048);

      if ( _requestBuffer.charAt( _requestBuffer.length() -1 ) != '\n' )
         _requestBuffer.append("\n");  //set the RTS 'EOT' character

      if ( _traceListener != null)
         _traceListener.traceTransactionBuffer( _requestBuffer.toString() );

      requestWriter.write( _requestBuffer.toString() );
      requestWriter.flush();
      
      boolean escaped = false;
      while ( true )
      {
         int c = responseReader.read();

         if ( c == -1 )
            throw new IOException("-1 returned from read(), at end of stream");

         responseBuffer.append( (char)c );

         if ( escaped )
         {
            escaped = false;
         }
         else
         {
            if ( c == '\\' )
            {
               escaped = true;
            }
            else if ( c == '\n' )
            {
               //chop RTS EOT character
               responseBuffer.setLength( responseBuffer.length() - 1 );
               return new RTSResponse( responseBuffer, _traceListener );
            }
         }
      }

   }


}