package com.ifds.stubEditor.data;

import com.ifds.rts.*;
import java.lang.reflect.*;
import java.io.*;
import java.text.ParseException;

public abstract class SeResponseData extends SeStubData
{
   
   /*
    *
    */
   public SeResponseData()
   {
      super();
   }

   /*
    *
    */
   public SeResponseData( File file, String encoding ) throws IOException
   {
      super( file, encoding );
   }

   /*
    *
    */
   public abstract int getTransactionId();
   public abstract int getResponseId();
   public abstract int getResponseTypeId();

   /*
    *
    */
   public final RTSBuffer asBuffer( String encoding ) throws ParseException, UnsupportedEncodingException
   {
      RTSEncodeBuffer _buffer = new RTSResponseEncodeBuffer( encoding,
                                                             getTransactionId(), 
                                                             getResponseId(), 
                                                             getResponseTypeId() );

      saveToBuffer( _buffer );
      return _buffer;

   }

   /*
    *
    */
   protected final RTSDecodeBuffer readBufferFromFile( File file, String encoding ) throws IOException, ParseException
   {
      RTSReader reader = new RTSReader( new FileInputStream( file ) );
      return reader.readResponse( encoding );
   }

   /*
    *
    */
   private static SeResponseData newInstance( int transactionId,
                                              Class[] paramTypes, 
                                              Object[] params ) throws InstantiationException
   {
      try
      {
         Class responseDataClass = Class.forName( "com.ifds.stubEditor.data.Response" + transactionId + "Data" );
   
         if ( responseDataClass.isAssignableFrom( Class.forName( "com.ifds.stubEditor.data.SeResponseData" ) ) )
            throw new ClassNotFoundException("Response" + transactionId + "Data not an type of SeResponseData.");

         return (SeResponseData)responseDataClass.getConstructor( paramTypes ).newInstance( params );
      }
      catch ( ClassNotFoundException e )
      {
         //System.err.println(e);
         e.printStackTrace();
         throw new InstantiationException( "[" + e.toString() + "]" );
      }
      catch ( NoSuchMethodException e )
      {
         //System.err.println(e);
         e.printStackTrace();
         throw new InstantiationException( "[" + e.toString() + "]" );
      }
      catch ( IllegalAccessException e )
      {
         //System.err.println(e);
         e.printStackTrace();
         throw new InstantiationException( "[" + e.toString() + "]" );
      }
      catch ( InvocationTargetException e )
      {
         //System.err.println(e);
         e.printStackTrace();
         e.getTargetException().printStackTrace();
         throw new InstantiationException( "[" + e.toString() + "]" );
      }

   }

   /*
    *
    */
   public static SeResponseData fromTransactionId( int transactionId ) throws InstantiationException
   {
      Class[] parameterTypes = { };
      Object[] parameters = { };
      return newInstance( transactionId, parameterTypes, parameters );
   }
   
   /*
    *
    */
   public static SeResponseData fromResponseFile( File stubFile, String encoding ) throws IOException, ParseException, InstantiationException
   {
      RTSReader reader = new RTSReader( new FileInputStream( stubFile ) );
      try
      {
         RTSResponseDecodeBuffer responseBuffer = reader.readResponse( encoding );
         String transactionId = responseBuffer.getTransactionID();

         Class[] parameterTypes = { stubFile.getClass(), encoding.getClass() };
         Object[] parameters = { stubFile, encoding };
         return newInstance( Integer.parseInt(transactionId), parameterTypes, parameters );

      }
      finally 
      {
         reader.close();
      }
   }


}
