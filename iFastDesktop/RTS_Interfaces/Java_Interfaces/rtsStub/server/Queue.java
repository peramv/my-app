package com.ifds.stubServer;

import java.util.Vector;

public class Queue
{
   private Vector theQue;
   private Class runnableClass;

   public Queue(int initialSize, int growthFactor)
   {
      theQue = new Vector(initialSize, growthFactor);
   }

   public Queue(int initialSize, int growthFactor, Class
                runnable) throws ClassCastException
   {
      theQue = new Vector(initialSize, growthFactor);
      //determine if the runnable is a sub-class of
      //Runnable.class
      if (Runnable.class.isAssignableFrom(runnable))
         runnableClass = runnable;
      else
         throw new ClassCastException(runnable +
                                      " is not a java.lang.Runnable sub-class");
   }

   public synchronized void add(Object runner)
   {
      theQue.add(runner);

      if (runnableClass == null)
         notify();
   }


   public synchronized Runnable next()
   throws IllegalAccessException,InstantiationException
   {
      if (theQue.isEmpty() && runnableClass != null)
         return(Runnable) runnableClass.newInstance();

      while (theQue.isEmpty())
      {
         try
         {
            wait();
         }

         catch (InterruptedException ie)
         {
            System.out.println("Could not wait()");
            ie.printStackTrace(System.out);
         }
      }

      Runnable runner = (Runnable) theQue.remove(0);
      return runner;
   }
}


