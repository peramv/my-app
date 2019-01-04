package com.ifds.rts;

import java.io.IOException;


public class UnexpectedByteIOException extends RuntimeException
{
   public UnexpectedByteIOException( IOException e )
   {
      super( "Unexpectede byte IO exception" + e.getMessage() );
      _e = e;
   }

   public IOException getIOException()
   {
      return _e;
   }

   private IOException _e;
}

