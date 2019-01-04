package com.ifds.iFast.api;

import com.ifds.rts.RTSResponseDecodeBuffer;

/**
 * An exception thrown by IFastView.recieve() or
 * IFastView.recieveAll() if there is a host
 * processing exception.<br><br>
 * 
 * This may be thrown if:<br>
 * - the host database is down<br>
 * - the API request classes versions are out-of-sync with the host<br>
 * - critical processing failures occur on the host.<br>
 */
public class IFastSystemResponseException extends Exception
{
   IFastSystemResponseException( String message )
   {

      super( "iFast system response: " + message );
   }
   
   IFastSystemResponseException( RTSResponseDecodeBuffer responseBuffer )
   {
         super( formatMessage( responseBuffer ) );
   }

   private static String formatMessage( RTSResponseDecodeBuffer responseBuffer )
   {

      String code = "????";
      String message = "?? Unparsable message ??";

      try
      {
         code = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      catch ( Exception e )
      {
      }

      try
      {
         message = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      catch ( Exception e )
      {
      }

      return ( "iFast system response [" + code + "]: " + message );

   }

}
