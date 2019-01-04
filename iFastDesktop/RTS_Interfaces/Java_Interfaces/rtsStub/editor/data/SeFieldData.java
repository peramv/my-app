package com.ifds.stubEditor.data;

import com.ifds.rts.*;
import java.text.*;
import java.io.UnsupportedEncodingException;

public abstract class SeFieldData
{
   
   private String _text = "";
   private boolean _nullValue = true;
   protected boolean _dirty = true;
   
   /*
    *
    */
   public String getText()
   {
      return _text;
   }

   /*
    *
    */
   public void setText( String text )
   {
      if ( text == null )
      {
         _text = "";
         _nullValue = true;
      }
      else
      {
         _text = text;
      }
      
      _dirty = true;
   }

   /*
    *
    */
   public boolean isNull()
   {
      return _nullValue;
   }

   /*
    *
    */
   public void setNull( boolean value )
   {
      _nullValue = value;
      _dirty = true;
   }

   /*
    *
    */
   public String toString()
   {
      if ( _nullValue )
         return "<null-field>";
      else
         return _text;
   }

   /*
    *
    */
   public abstract void initFromBuffer(RTSDecodeBuffer buffer) throws ParseException, UnsupportedEncodingException;

   /*
    *
    */
   public abstract void saveToBuffer(RTSEncodeBuffer buffer) throws ParseException, UnsupportedEncodingException;

   /*
    *
    */
   public boolean isDirty()
   {
      return _dirty;
   }


}

