package com.ifds.stubServer;

import java.net.*;
import java.io.*;

public class stubServer
{
   private static final short file_type = 0;
   private static final short rts_type = 1;

   private final static String usage =
   "Usage: java stubServer [mode] [listening port] [directory read/write stub file] [host address] [host port]\n"+
   "       [mode]: 0/1-read data from stub file/host and send the data back to the client\n" +
   "       [listening port]: the port this server is listening\n"+
   "       [directory read/write stub file]: directory read/write stub file\n"+
   "       [host address]: host address\n" +
   "       [host port]: host port\n";

   private static void usage() {
      System.err.println(usage);
      System.exit(1);
   }
   public static void main(String args[])
   {
      if (args.length < 1) usage();
      try
      {
         int port, mode, rtsPort;
         String stubDir, rtsIP;

         try
         {
            mode = Integer.parseInt(args[0]);
         } catch (Exception e)
         {
            mode = file_type;
         }

         System.out.println("mode = " +mode);

         try
         {
            port = Integer.parseInt(args[1]);
         } catch (Exception e)
         {
            port = 2002;
         }

         System.out.println("port = "+port);

         try
         {
            connectionJob.stubDir = args[2];
         } catch (Exception e)
         {
            connectionJob.stubDir = "";
         }

         System.out.println("stub directory = " +connectionJob.stubDir);

         try
         {
            File dir = new File( connectionJob.stubDir );

            if ( !dir.exists() )
            {
               dir.mkdir();
               System.out.println("Note: stub directory: " +connectionJob.stubDir + " did not exist and is now created.");
            }
         } catch ( NullPointerException ne )
         {
            // don't need to do anything
         } catch ( SecurityException se )
         {
            System.out.println(se);
         }

         if ( mode == rts_type )
         {
            try
            {
               rtsConnectionJob.server = args[3];
            } catch (Exception e)
            {
               System.err.println("\n\nError: you must specify host address.");
               System.exit(1);
            }

            System.out.println("host address = " +rtsConnectionJob.server);

            try
            {
               rtsConnectionJob.port = Integer.parseInt(args[4]);
            } catch (Exception e)
            {
               System.err.println("\n\nError: you must specify host port.");
               System.exit(1);
            }

            System.out.println("rts port = "+rtsConnectionJob.port);

            if ( rtsConnectionJob.port == port)
            {
               System.err.println("\n\nError: server port and host port cannot be the same.");
               System.exit(1);
            }

         }


         // load stub file info
         connectionJob.stubFilename = new stubNameTable(connectionJob.stubDir);


         ServerSocket serverSocket=null;
         try
         {
            serverSocket=new ServerSocket(port);
         } catch ( IOException e )
         {
            System.err.println("\n\nError: server port already in use.");
            System.exit(1);
         }

         //create the Queue that holds the requests
         Queue requestQue = new Queue(5,10);

         //create the Queue that holds the runnables
         Queue runnableQue = new Queue(10, 10, connectionJob.class);

         //create the Runnable pool that contains 10
         //runnables
         for (int i=0;i<100;i++)
         {
            Runnable runner;
            switch ( mode )
            {
            case rts_type:
               runner = new rtsConnectionJob();
               break;

            default:
               runner = new fileConnectionJob();
               break;
            }
            runnableQue.add(runner);
         }



         //create the Thread pool that contains 10 Threads
         for (int i=0;i<20;i++)
         {
            Thread thread = new threadPool(requestQue,
                                           runnableQue);
            thread.start();
         }

         System.out.println("\n\nStub server is ready.\n\n");




         //wait and accept connections
         while (true)
         {
            try
            {
               //get the request
               Socket request = serverSocket.accept();

               //get a runnable
               connectionJob runner = (connectionJob)
                                      runnableQue.next();

               //re-initialize the runner
               runner.init(request);
               //add it to the que so a thread can handle it
               requestQue.add(runner);
            } catch (java.io.IOException ioe)
            {
               System.out.println("Problems handling request"
                                  + ioe);
            }
         }
      } catch (Exception e)
      {
         System.out.println("Problem starting the server....");
         e.printStackTrace(System.out);
         System.exit(-1);
      }
   }
}
