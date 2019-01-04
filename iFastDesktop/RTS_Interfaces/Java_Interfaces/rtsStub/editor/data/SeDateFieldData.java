package com.ifds.stubEditor.data;

import com.ifds.rts.*;
import java.text.*;
import java.util.Date;
import java.io.UnsupportedEncodingException;

class SeDateFieldData extends SeFieldData
{
   private final SimpleDateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy");
   
   /*
    *
    */
   public void initFromBuffer( RTSDecodeBuffer buffer ) throws ParseException, UnsupportedEncodingException 
   {
      Date value = buffer.decodeDate( buffer.getNextField() );
      if ( value != null)
      {
         setText( dateFormat.format( value ) );
         setNull( false );
      }
      else
      {
         setText( "" );
         setNull( true );
      }
      _dirty = false;
   }

   /*
    *
    */
   public void saveToBuffer( RTSEncodeBuffer buffer ) throws ParseException, UnsupportedEncodingException
   {
      if ( isNull() )
         buffer.appendField( (Date)null );
      else
      {
         try
         {
            buffer.appendField( dateFormat.parse( getText() ) );
         }
         catch ( Exception e )
         {
            throw new ParseException( "SeFieldData \"" + getText() + "\" cannot be parsed as Date.", 0 );
         }
      }
      _dirty = false;
   }

}
