package com.ifds.stubServer;
  
  
import java.net.*;
import java.io.*;
import java.util.*;


public class stubServerMan
{
   private final static String usage =
   "Usage: java stubServerMan [mode] [directory read/write stub file] [stub server address] [stub server port]\n"+
   "       [mode]: 0/1/2/3 display stub file info/recreate stub file info/merge stub file info/test server\n"+
   "       [directory read/write stub file]: directory read/write stub file\n"+
   "       [stub server address]: stub server address\n"+
   "       [stub server port]: \n";
   static String stubDir;
   private static void usage() {
      System.err.println(usage);
      System.exit(1);
   }
   public static void main(String args[])
   {
      if (args.length < 1) usage();
      int mode;


      stubServerMan aMan = new stubServerMan();
      try
      {
         mode = Integer.parseInt(args[0]);
      } catch (Exception e)
      {
         mode = 0;
      }

      System.out.println("mode = " +mode);

      try
      {
         stubDir = args[1];
      } catch (Exception e)
      {
         stubDir = "";
      }

      System.out.println("directory read/write stub file = " +stubDir);

      if ( mode == 3 )
      {
         try
         {
            testThread.serverIP = args[2];
         } catch (Exception e)
         {
            System.err.println("\n\nError: you must specify stub server address.");
            System.exit(1);
         }

         System.out.println("stub server address = " +testThread.serverIP);

         try
         {
            testThread.serverPort = Integer.parseInt(args[3]);
         } catch (Exception e)
         {
            System.err.println("\n\nError: you must specify stub server port.");
            System.exit(1);
         }

         System.out.println("stub server port = " +testThread.serverPort);
      }

      stubNameTable sn = new stubNameTable(stubDir);
      switch (mode)
      {
      case 0:
         sn.displayStubInfo();
         break;

      case 1:
         sn.recreateStubInfo();
         break;

      case 2:
         sn.mergeStubInfo();
         break;

      case 3:
         aMan.serverTest();
         break;
      }

      System.out.println("\n\n");
   }


   private void serverTest()
   {
      stubNameTable sn = new stubNameTable(stubDir);
      HashMap hm=sn.getStubInfoHashMap();


      if ( hm!=null)
      {
         Set hmKeySet = hm.keySet();
         for (int i=0;i<1000;i++)
         {
            Thread thread = new testThread(hmKeySet );
            thread.start();
         }
      }
   }
}
