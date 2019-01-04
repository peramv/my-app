package com.ifds.stubServer;

import java.net.Socket;

import java.io.*;
import com.ifds.rts.*;
import java.text.ParseException;

public abstract class connectionJob extends Object implements Runnable
{
   protected static final String req_fileExt = ".req";
   protected static final String res_fileExt = ".res";
   private Socket connection;
   public static String stubDir;
   public static stubNameTable stubFilename;

   public connectionJob()
   {
   }

   public connectionJob(Socket s)
   {
      connection = s;
   }

   public void init(Socket s)
   {
      //reassign the socket
      connection = s;
   }

   protected abstract RTSBuffer doRun( RTSRequestDecodeBuffer requestBuffer ) throws IOException, ParseException;

   public void run()
   {
      String filename;
      try {
         do {
            RTSReader reader = new RTSReader( connection.getInputStream() );
            RTSRequestDecodeBuffer requestBuffer = reader.readRequest( "ISO8859-1" );

            //System.out.println("\nStart process view "+requestBuffer.getTransactionID() + "\nRequest>" + newReqString );

            RTSBuffer responseBuffer = doRun( requestBuffer );

            RTSWriter writer  = new RTSWriter( connection.getOutputStream() );
            writer.write( responseBuffer );

            //System.out.println("\nResponse>" + responseBuffer.toString() );
            //System.out.println("Finish process view "+requestBuffer.getTransactionID()+"\n");
         } while(true);
      } 
      catch (Exception e) {
         e.printStackTrace();
      }
   }

}
