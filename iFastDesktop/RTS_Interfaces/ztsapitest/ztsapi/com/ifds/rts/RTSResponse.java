package com.ifds.rts;


import java.lang.Object;
import java.util.*;
import java.text.*;
import java.io.*;


/**
 * This class represents the RTS Response.
 * This class implements decoding of RTS data types to Java Data types.
 */
public class RTSResponse implements Serializable
{
   private final SimpleDateFormat dateFmt = new SimpleDateFormat("MMddyyyy");   //Simple date format cannot be made static

   private String  _MsgType = null;
   private Integer _TransactionID = null;
   private Integer _ResponseID = null;
   private Integer _ResponseType = null;
   private Integer _PHandleID = null;
   private Long    _PThreadID = null;
   private Integer _InstanceID = null;

   private String _responseString = null;
   
//   private String separator = System.getProperty("SEPARATOR")!=null? System.getProperty("SEPARATOR") : ",";
   private String separator = "\u00fe";
   
   private int _BufferPos;
   private int _FieldCount;

   private final RTSTraceListener _traceListener;

   RTSResponse( StringBuffer responseBuffer, RTSTraceListener traceListener ) throws IOException
   {
      _traceListener = traceListener;
      _responseString = responseBuffer.toString();
      
      if ( _traceListener != null )
         _traceListener.traceResponseBuffer( _responseString );
      
      decodeHeader();
   }

   private void decodeHeader()
   {
      _MsgType = _responseString.substring(0,1);
      _TransactionID = new Integer(_responseString.substring(1,6));
      _ResponseID= new Integer(_responseString.substring(6,11));
      _ResponseType= new Integer(_responseString.substring(11,16));
      _PHandleID= new Integer(_responseString.substring(16,21));
      _PThreadID= new Long(_responseString.substring(21,31));
      _InstanceID= new Integer(_responseString.substring(31,36));
      separator = _responseString.substring(36,1);

      _BufferPos=37;
      _FieldCount=0;
      
      if ( _traceListener != null )
         _traceListener.traceDecodeHeader( _MsgType,
                                           _TransactionID,
                                           _ResponseID,
                                           _ResponseType,
                                           _PHandleID,
                                           _PThreadID,
                                           _InstanceID );
   }


   public final Boolean decodeBoolean(String s) throws ParseException
   {
      Boolean val = null;

      if ( s.charAt(0) != 'T' )
      {
         if ( s.charAt(1) == 'Y' )
            val = Boolean.TRUE;
         else
            val =  Boolean.FALSE;
      }

      if ( _traceListener != null )
         _traceListener.traceDecodeField( val );

      return val;
   }


   public final Date decodeDate(String s) throws ParseException
   {
      Date val = null;

      if ( s.charAt(0) != 'T' )
         val = dateFmt.parse(s.substring(1));

      if ( _traceListener != null )
         _traceListener.traceDecodeField( val );
      
      return val;
   }

   public final Double decodeDouble(String s) throws ParseException
   {
      Double val = null;
      
      if ( s.charAt(0) != 'T' )
         val = new Double(s.substring(1));

      if ( _traceListener != null )
         _traceListener.traceDecodeField( val );
      
      return val;
   }

   public final Integer decodeInteger(String s) throws ParseException
   {
      Integer val = null;
      
      if ( s.charAt(0) != 'T' )
         val = new Integer(s.substring(1));

      if ( _traceListener != null )
         _traceListener.traceDecodeField( val );
      
      return val;
   }

   public final String decodeString(String s) throws ParseException
   {
      String val = null;

      if ( s.charAt(0) != 'T' )
         val = s.substring(1);

      if ( _traceListener != null )
         _traceListener.traceDecodeField( val );
      
      return val;
   }

   public final String getNextField() throws ParseException
   {
      StringBuffer s = new StringBuffer(""); 
      int max = _responseString.length();

      // make sure we do not call this function more times than
      // the total number of fields in the buffer
      // i.e. are we at the end of the buffer already ?
      if ( _BufferPos >= max )
      {
         throw new ParseException("RTSResponse.getNextField() attempt to get more fields (Field " + (_FieldCount+1) + ") than there are in the response buffer class<" + this.getClass().getName() + "> [Number of fields = " + _FieldCount + "]", _BufferPos );
      }
      // 
      // in the worst case we have to traverse to the end
      // of the string, starting from the place we left last
      // which is 0 for the first call to the function.
      //
      boolean Escaped = false;
      char c;
      int i;
      for ( i = _BufferPos; i < max; i++ )
      {
         c = _responseString.charAt(i);
         if ( Escaped == false )
         {
            if ( c == '\\' )
            {
               Escaped = true;
               continue;
            }
            if ( c == separator.charAt(0) ) break;
         }
         s.append(c);
         Escaped = false;
      } // end for

//      if ( _traceListener != null )
//         _traceListener.traceGetField( s.toString(), _BufferPos, _FieldCount );
      
      _BufferPos = i+1;
      _FieldCount++;
      
      return s.toString();
   }

   public final Integer getInstanceID()
   {
      return _InstanceID;
   }

   public final String getMsgType()
   {
      return _MsgType;
   }

   public final Integer getPHandleID()
   {
      return _PHandleID;
   }

   public final Long getPThreadID() 
   {
      return _PThreadID;
   }

   public final Integer getResponseID()
   {
      return _ResponseID;
   }

   public final Integer getResponseType()
   {
      return _ResponseType;
   }

   public final Integer getTransactionID()
   {
      return _TransactionID;
   }

}