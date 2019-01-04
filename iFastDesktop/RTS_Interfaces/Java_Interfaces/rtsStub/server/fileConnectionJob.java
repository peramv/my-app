package com.ifds.stubServer;

import java.net.Socket;

import java.io.*;
import java.text.ParseException;
import com.ifds.rts.*;

public class fileConnectionJob extends connectionJob {
   public RTSBuffer doRun( RTSRequestDecodeBuffer requestBuffer ) throws IOException, ParseException {
      File responseFile = new File( stubDir, stubFilename.getStubFilename(requestBuffer.toString())+res_fileExt );
      
      long time0 = System.currentTimeMillis();
      
      RTSReader fileReader = null;
      RTSResponseDecodeBuffer responseBuffer=null;
      
      try {
         fileReader = new RTSReader( new FileInputStream(responseFile) );
      } catch (FileNotFoundException e) {
         //if stub is not found, send data not found
         try{
            fileReader = new RTSReader( new FileInputStream("0.res") );
            System.out.println(stubDir+responseFile.getName()+" is not available. read from 0.res instead");
         }
         catch(FileNotFoundException e0) {
            System.out.println("0.res not available");
         }
      }
      
      if( fileReader != null ){
         responseBuffer = fileReader.readResponse( "ISO8859-1" );
         fileReader.close();
      }
      
      System.out.println("View "+requestBuffer.getTransactionID() +" costs " + (System.currentTimeMillis()-time0)
      + "ms to read from " +stubDir+responseFile.getName());
      return responseBuffer;
   }
}
