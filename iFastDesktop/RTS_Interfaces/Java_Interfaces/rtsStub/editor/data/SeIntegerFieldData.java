package com.ifds.stubEditor.data;

import com.ifds.rts.*;
import java.text.*;
import java.io.UnsupportedEncodingException;

class SeIntegerFieldData extends SeFieldData
{
   /*
    *
    */
   public void initFromBuffer( RTSDecodeBuffer buffer ) throws ParseException, UnsupportedEncodingException
   {
      Integer value = buffer.decodeInteger( buffer.getNextField() );
      if ( value != null)
      {
         setText( value.toString() );
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
         buffer.appendField( (Integer)null );
      else
      {
         try
         {
            buffer.appendField( new Integer( getText() ) );
         }
         catch ( Exception e )
         {
            throw new ParseException( "SeFieldData \"" + getText() + "\" cannot be parsed as Integer.", 0 );
         }
      }
      _dirty = false;
   }

}
