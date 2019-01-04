package com.ifds.stubEditor.data;

import com.ifds.rts.*;
import javax.swing.table.*;
import java.util.*;
import java.text.ParseException;
import java.io.UnsupportedEncodingException;

public abstract class SeRepeatSectionData extends AbstractTableModel implements SeSectionData
{

   private final ArrayList _recordList = new ArrayList();
   private boolean _dirty = true;
   
   /*
    *
    */
   public SeRepeatSectionData()
   {
      super();
   }

   /*
    *
    */
   public int getRowCount() 
   {
      return _recordList.size();
   }
   
   /*
    *
    */
   public Object getValueAt( int rowIndex, int columnIndex ) 
   {
      return ( (SeRecordData)_recordList.get( rowIndex ) ).getField( columnIndex );
   }

   /*
    *
    */
   public SeRecordData getRecord( int index ) 
   {
      return (SeRecordData)_recordList.get( index );
   }

   /*
    *
    */
   public SeFieldData getRecord( int recordIndex, int columnIndex ) 
   {
      return (SeFieldData)getValueAt( recordIndex, columnIndex );
   }

   /*
    *
    */
   public void addRecord( SeRecordData record ) 
   {
      _recordList.add( record );
      this.fireTableRowsInserted( _recordList.size()-1, _recordList.size()-1 );
      _dirty = true;
   }

   /*
    *
    */
   public void setRecord( int recordIndex, SeRecordData record ) 
   {
      _recordList.set( recordIndex, record );
      this.fireTableRowsUpdated( recordIndex, recordIndex );
      _dirty = true;
   }

   /*
    *
    */
   public void removeRecord( int recordIndex ) 
   {
      _recordList.remove( recordIndex );
      this.fireTableRowsDeleted( recordIndex, recordIndex );
      _dirty = true;
   }

   /*
    *
    */
   public abstract SeRecordData newRecord();

   /*
    *
    */
   public void initFromBuffer(RTSDecodeBuffer buffer) throws ParseException, UnsupportedEncodingException
   {

      _recordList.clear();

      int repeatCount = buffer.decodeInteger( buffer.getNextField() ).intValue(); // repeatCount field

      for ( int index=0; index<repeatCount; index++ )
      {
         SeRecordData record = newRecord();
         record.initFromBuffer( buffer );
         _recordList.add( record );
      }
      _dirty = false;
   }

   /*
    *
    */
   public void saveToBuffer(RTSEncodeBuffer buffer) throws ParseException, UnsupportedEncodingException 
   {
      buffer.appendField( new Integer( _recordList.size() ) ); // repeatCount field

      Iterator iter = _recordList.iterator();
      while ( iter.hasNext() )
         ( (SeRecordData)iter.next() ).saveToBuffer( buffer );
      
      _dirty = false;
   }

   /*
    *
    */
   public boolean isDirty()
   {
      if ( _dirty )
         return true;
      
      Iterator iter = _recordList.iterator();
      while ( iter.hasNext() )
      {
         if ( ( (SeRecordData)iter.next() ).isDirty() )
         {
            _dirty = true;
            return true;
         }
      }

      return false;

   }

   /*
    *
    */
   public boolean isRepeatSection()
   {
      return true;
   }

}

