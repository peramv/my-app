package com.ifds.stubServer;


 import java.net.*;

import java.io.*;
import com.ifds.rts.*;

   import java.util.*;


public class testThread extends Thread                 
{
   public static String serverIP;
   public static int serverPort;

   private Socket serverConnection;
   private Set reqSet;

   public testThread(Set reqSet)
   {
      this.reqSet=reqSet;
   }

   public void run()
   {
      Socket serverConnection=null;
      try
      {

         serverConnection = new Socket( serverIP, serverPort );

         PrintWriter output=new PrintWriter(serverConnection.getOutputStream(),true);

         Iterator iter = reqSet.iterator();
         String key, value, str;
         while (iter.hasNext())
         {
            key = (String)iter.next();

            System.out.println(key +"sent");
             
            output.println(key+"\n");
         }

         serverConnection.close();
      } catch (IOException e)
      {
         //System.out.println(e);
      }
   }
}


