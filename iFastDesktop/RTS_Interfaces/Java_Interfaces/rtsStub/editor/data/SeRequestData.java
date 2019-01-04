package com.ifds.stubEditor.data;

import com.ifds.rts.*;
import java.lang.reflect.*;
import java.io.*;
import java.text.ParseException;

public abstract class SeRequestData extends SeStubData
{
   
   /*
    *
    */
   public SeRequestData()
   {
      super();
   }

   /*
    *
    */
   public SeRequestData( File file, String encoding ) throws IOException
   {
      super( file, encoding );
   }

   /*
    *
    */
   public abstract int getTransactionId();

   /*
    *
    */
   public final RTSBuffer asBuffer( String encoding ) throws ParseException, UnsupportedEncodingException
   {
      RTSEncodeBuffer _buffer = new RTSRequestEncodeBuffer( encoding, getTransactionId() );

      saveToBuffer( _buffer );
      return _buffer;

   }

   /*
    *
    */
   protected final RTSDecodeBuffer readBufferFromFile( File file, String encoding ) throws IOException, ParseException
   {
      RTSReader reader = new RTSReader( new FileInputStream( file ) );
      return reader.readRequest( encoding );
   }

   /*
    *
    */
   private static SeRequestData newInstance( int transactionId,
                                              Class[] paramTypes, 
                                              Object[] params ) throws InstantiationException
   {
      try
      {
         Class requestDataClass = Class.forName( "com.ifds.stubEditor.data.Request" + transactionId + "Data" );
   
         if ( requestDataClass.isAssignableFrom( Class.forName( "com.ifds.stubEditor.data.SeRequestData" ) ) )
            throw new ClassNotFoundException("Request" + transactionId + "Data not an type of SeRequestData.");

         return (SeRequestData)requestDataClass.getConstructor( paramTypes ).newInstance( params );
      }
      catch ( ClassNotFoundException e )
      {
         System.err.println(e.getMessage());
         throw new InstantiationException( e.getMessage() );
      }
      catch ( NoSuchMethodException e )
      {
         System.err.println(e.getMessage());
         throw new InstantiationException( e.getMessage() );
      }
      catch ( IllegalAccessException e )
      {
         System.err.println(e.getMessage());
         throw new InstantiationException( e.getMessage() );
      }
      catch ( InvocationTargetException e )
      {
         System.err.println( e.getTargetException().getMessage() );
         e.getTargetException().printStackTrace();
         throw new InstantiationException( e.getMessage() );
      }

   }

   /*
    *
    */
   public static SeRequestData fromTransactionId( int transactionId ) throws InstantiationException
   {
      Class[] parameterTypes = { };
      Object[] parameters = { };
      return newInstance( transactionId, parameterTypes, parameters );
   }
   
   /*
    *
    */
   public static SeRequestData fromRequestFile( File stubFile, String encoding ) throws IOException, ParseException, InstantiationException
   {
      RTSReader reader = new RTSReader( new FileInputStream( stubFile ) );
      try
      {
         RTSRequestDecodeBuffer requestBuffer = reader.readRequest( encoding );
         String transactionId = requestBuffer.getTransactionID();

         Class[] parameterTypes = { stubFile.getClass() };
         Object[] parameters = { stubFile };
         return newInstance( Integer.parseInt(transactionId), parameterTypes, parameters );

      }
      finally 
      {
         reader.close();
      }
   }
 
}
