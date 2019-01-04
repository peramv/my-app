package com.ifds.stubEditor.data;

import com.ifds.rts.*;
import java.util.*;
import java.text.ParseException;
import java.io.UnsupportedEncodingException;

public abstract class SeRecordData implements SeSectionData
{
   private final ArrayList _fieldList = new ArrayList();
   
   /*
    *
    */
   public SeRecordData()
   {
   }

   /*
    *
    */
   public SeFieldData getField( int index )
   {
      return (SeFieldData)_fieldList.get( index );

   }

   /*
    *
    */
   protected void addField( SeFieldData field )
   {
      _fieldList.add( field );
   }
   
   /*
    *
    */
   public int getFieldCount()
   {
      return _fieldList.size();
   }

   /*
    *
    */
   public abstract String getFieldName( int index );
   
   /*
    *
    */
   public void initFromBuffer( RTSDecodeBuffer buffer ) throws ParseException, UnsupportedEncodingException
   {
      
      Iterator iter = _fieldList.iterator();
      while ( iter.hasNext() )
         ( (SeFieldData)iter.next() ).initFromBuffer( buffer );
   }

   /*
    *
    */
   public void saveToBuffer( RTSEncodeBuffer buffer ) throws ParseException, UnsupportedEncodingException
   {
      Iterator iter = _fieldList.iterator();
      while ( iter.hasNext() )
         ( (SeFieldData)iter.next() ).saveToBuffer( buffer );
   }
   
   /*
    *
    */
   public boolean isDirty()
   {
      
      Iterator iter = _fieldList.iterator();
      while ( iter.hasNext() )
      {
         if ( ( (SeFieldData)iter.next() ).isDirty() )
            return true;
      }

      return false;

   }

   /*
    *
    */
   public boolean isRepeatSection()
   {
      return false;
   }
}
