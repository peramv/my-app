package com.ifds.stubEditor.data;

import com.ifds.rts.*;
import java.text.*;
import java.io.UnsupportedEncodingException;

class SeTextFieldData extends SeFieldData
{
   /*
    *
    */
   public void initFromBuffer(RTSDecodeBuffer buffer) throws ParseException, UnsupportedEncodingException 
   {
      String value = buffer.decodeString( buffer.getNextField() );
      if ( value != null)
      {
         setText( value );
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
   public void saveToBuffer(RTSEncodeBuffer buffer) throws ParseException, UnsupportedEncodingException 
   {
      if ( isNull() )
         buffer.appendField( (String)null );
      else
         buffer.appendField( getText() );
      _dirty = false;
   }

}
