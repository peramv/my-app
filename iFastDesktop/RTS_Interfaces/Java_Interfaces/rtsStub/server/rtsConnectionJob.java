 package com.ifds.stubServer;

import java.net.*;

import java.io.*;
import java.text.ParseException;
import com.ifds.rts.*;

public class rtsConnectionJob extends connectionJob
{
   public static String server ;
   public static int port;


   public RTSBuffer doRun( RTSRequestDecodeBuffer requestBuffer ) throws IOException, ParseException
   {
      String filename = stubFilename.getOrAddStubFilename(requestBuffer.toString());
      File responseFile = new File( stubDir, filename+res_fileExt );

      long time0 = System.currentTimeMillis();
      RTSResponseDecodeBuffer responseBuffer=null;

      Socket serverConnection = new Socket( server, port );

      RTSWriter serverWriter = new RTSWriter( serverConnection.getOutputStream() );
      serverWriter.write( requestBuffer );
      //System.out.println("\nRequest written to host "+requestBuffer.getTransactionID() );


      // dump request data. we only do this in rtsConnectionJob
      RTSWriter fileWriter = new RTSWriter( new FileOutputStream(stubDir+filename+req_fileExt) );
      fileWriter.write( requestBuffer );
      fileWriter.close();

      RTSReader serverReader = new RTSReader( serverConnection.getInputStream() );
      responseBuffer = serverReader.readResponse( "ISO8859-1" );
      //System.out.println("\nResponse read from host " + responseBuffer.getTransactionID() + "\nResponse>" + responseBuffer.toString() );

      serverConnection.close();
      // dump response data
      fileWriter = new RTSWriter( new FileOutputStream(responseFile) );
      fileWriter.write( responseBuffer );
      fileWriter.close();
      
      System.out.println("View "+requestBuffer.getTransactionID() +" costs " + (System.currentTimeMillis()-time0) 
                         + "ms and is saved to " +stubDir+responseFile.getName());
      return responseBuffer;
   }
}
