package com.ifds.stubServer;



public class threadPool extends Thread                 
{
   private Queue requestQue, runnableQue;

   public threadPool(Queue reqQue, Queue runQue)
   {
      requestQue = reqQue;
      runnableQue = runQue;
   }

   public void run()
   {
      while (true)
      {
         try
         {
            Runnable runner = requestQue.next();
            runner.run();
            runnableQue.add(runner);
         } catch (IllegalAccessException iae)
         {
         } catch (InstantiationException ie)
         {
         }
      }
   }
}


