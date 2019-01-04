package com.ifds.stubEditor.data;

import com.ifds.rts.*;
import java.text.*;
import java.io.UnsupportedEncodingException;

class SeBooleanFieldData extends SeFieldData
{
   /*
    *
    */
   public void initFromBuffer( RTSDecodeBuffer buffer ) throws ParseException, UnsupportedEncodingException
   {
      Boolean value = buffer.decodeBoolean( buffer.getNextField() );
      if ( value != null)
      {
         setText( (value.booleanValue())?"true":"false" );
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
         buffer.appendField( (Boolean)null );
      else
      {
         if ( getText().equals("true") )
            buffer.appendField( Boolean.TRUE );
         else if ( getText().equals("false") )
            buffer.appendField( Boolean.FALSE );
         else
            throw new ParseException( "SeFieldData \"" + getText() + "\" cannot be parsed as Boolean.", 0 );
      }
      _dirty = false;
   }

}
