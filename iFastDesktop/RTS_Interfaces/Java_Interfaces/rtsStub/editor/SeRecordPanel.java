package com.ifds.stubEditor;

import java.awt.*;
import com.ifds.stubEditor.data.*;
import javax.swing.*;
import java.util.*;

class SeRecordPanel extends JPanel
{
   private final SeRecordData _recordData;
   
   /**
    *
    */
   public SeRecordPanel( SeRecordData recordData )
   {
      super();
      setLayout( new SeRecordPanelLayout() );

      _recordData = recordData;

      int fieldCount = _recordData.getFieldCount();

      for ( int index = 0; index < fieldCount; index++ )
      {
         add( new SeField( _recordData.getFieldName(index), _recordData.getField(index) ) );
      }
   }

   private class SeRecordPanelLayout implements LayoutManager
   {
      private final static int hGap = 5;
      
      /**
       *
       */
      SeRecordPanelLayout()
      {
      }
      
      /**
       *
       */
      public void addLayoutComponent(String name, Component comp) 
      {
      }
   
      /**
       *
       */
      public void removeLayoutComponent(Component comp) 
      {
      }
   
      /**
       *
       */
      public Dimension preferredLayoutSize(Container parent) 
      {
         Dimension d = layoutSize(parent);
   //      System.out.println("Fixed.preferredLayoutSize() d:" + d.toString() );
         return d;
      }
   
      /**
       *
       */
      public Dimension minimumLayoutSize(Container parent) 
      {
         Dimension d = layoutSize(parent);
   //      System.out.println("Fixed.minimumLayoutSize() d:" + d.toString() );
         return d;
      }
   
      /**
       *
       */
      private Dimension layoutSize( Container parent )
      {
         int height = 0;
   
         int[] columnRights = getColumnRights( parent, getBestColumnWidths( parent ) );
   //      printIntArray( "Fixed.preferredLayoutSize() columnRights:", columnRights );
   
         int compCount = parent.getComponentCount();
   
         int compIndex = 0;
         for ( int rowIndex = 0; compIndex < compCount; rowIndex++ )
         {
            int rowHeight = 0;
            for ( int colIndex = 0; (colIndex < columnRights.length && compIndex < compCount); colIndex++, compIndex++ )
            {
               Component comp = parent.getComponent( compIndex );
               Dimension compSize = comp.getPreferredSize();
   
               if ( compSize.getHeight() > rowHeight )
                  rowHeight = (int)compSize.getHeight();
            }
            height += rowHeight;
         }         
   
         Dimension d = new Dimension( columnRights[columnRights.length-1], height );
   
         return d;
      }
   
      /**
       *
       */
      public void layoutContainer(Container parent) 
      {
         int right = parent.getWidth();
         int y = 0;
         
         int[] columnRights = getColumnRights( parent, getBestColumnWidths( parent ) );
   
         int compCount = parent.getComponentCount();
   
         int compIndex = 0;
         for ( int rowIndex = 0; compIndex < compCount; rowIndex++ )
         {
            int rowHeight = 0;
            for ( int colIndex = 0; (colIndex < columnRights.length && compIndex < compCount); colIndex++, compIndex++ )
            {
               Component comp = parent.getComponent( compIndex );
               Dimension compSize = comp.getPreferredSize();
               comp.setSize( compSize );
               comp.setLocation( columnRights[colIndex] - comp.getWidth(), y);
   //            System.out.println("Fixed.layoutContainer() comp.bounds:" + comp.getBounds() );
   
               if ( compSize.getHeight() > rowHeight )
                  rowHeight = (int)compSize.getHeight();
            }
            y+=rowHeight;
         }
   
      }
   
      /**
       *
       */
      private int[] getColumnRights( Container parent, int[] columnWidths )
      {
         int[] columnRights = new int[columnWidths.length];
         int x = 0;
   
         for ( int index = 0; index<columnWidths.length; index++ )
         {
            x += columnWidths[index];
            columnRights[index] = x;
            x += hGap;
         }
         
   //      printIntArray( "getColumnRights() columnRights", columnRights );
   
         return columnRights;
   
      }
   
      /**
       *
       */
      private int[] getBestColumnWidths( Container parent )
      {
         int availableColumnWidth = parent.getWidth();
   
         int[] columnWidths = null;
   
         for ( int colCount = 1; colCount <= parent.getComponentCount(); colCount++ )
         {
            availableColumnWidth -= hGap;
   
            int[] tempColumnWidths = getColumnWidths( parent, colCount );
   
            int totalWidth = 0;
            for ( int index = 0; index<tempColumnWidths.length; index++ )
               totalWidth += tempColumnWidths[index];
   
            if ( totalWidth > availableColumnWidth )
            {
               if ( columnWidths == null )
                  columnWidths = tempColumnWidths;
   
   //            printIntArray( "(1)getBestColumnWidths() columnWidths", columnWidths );
               return columnWidths;
            }
   
            columnWidths = tempColumnWidths;
            
         }
   
   //      printIntArray( "(2)getBestColumnWidths() columnWidths", columnWidths );
         return columnWidths;
   
      }
   
      /**
       *
       */
      private int[] getColumnWidths( Container parent, int columnCount )
      {
         int[] columnWidths = new int[columnCount];
         for ( int index = 0; index < columnCount; index++ )
            columnWidths[index] = 0;
   
         int compCount = parent.getComponentCount();
   
         for ( int compIndex = 0; compIndex < compCount; compIndex++ )
         {
            int currentCol = compIndex % columnCount;
            int compWidth = (int)parent.getComponent(compIndex).getPreferredSize().getWidth();
   
            if ( compWidth > columnWidths[currentCol] )
               columnWidths[currentCol] = compWidth;
         }
         
   //      printIntArray( "getColumnWidths() columnWidths", columnWidths );
   
         return columnWidths;
      }
   
      /**
       *
       */
      private void printIntArray( String prefix, int[] intArray )
      {
         System.out.print( prefix + ": ["  );
         for ( int index = 0; index < intArray.length; index++ )
            System.out.print( intArray[index] + "," );
         System.out.println( "]"  );
   
      }
   }
}

