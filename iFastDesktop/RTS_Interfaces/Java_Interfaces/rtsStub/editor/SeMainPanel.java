package com.ifds.stubEditor;

import com.ifds.stubEditor.data.*;
import java.awt.*;
import javax.swing.*;

public class SeMainPanel extends JPanel
{
   private final SeStubData _stubData;
   
   /*
    *
    */
   public SeMainPanel( SeStubData stubData )
   {
      super();
      this.setLayout( new SeMainPanelLayout() );
      this.setBorder( BorderFactory.createEmptyBorder(10,10,10,10));

      _stubData = stubData;

      int sectionCount = _stubData.getSectionCount();
      
      for ( int index = 0; index < sectionCount; index++ )
      {
         SeSectionData section = _stubData.getSection( index );
         if ( section.isRepeatSection() )
         {
            add( new SeRepeatSectionPanel( (SeRepeatSectionData)section ) );
         }
         else
         {
            add( new SeRecordPanel( (SeRecordData)section ) );
//            add( new JScrollPane( new SeRecordPanel( (SeRecordData)section ) ) );
         }
      }
   }

   private class SeMainPanelLayout implements LayoutManager
   {
      private final static int vGap = 5;
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
       * Calculates the preferred size dimensions for the specified
       * panel given the components in the specified parent container.
       * @param parent the component to be laid out
       *
       * @see #minimumLayoutSize
       */
      public Dimension preferredLayoutSize(Container parent) 
      {

         Insets borderInsets = parent.getInsets();
         int prefWidth = parent.getWidth();
         int prefHeight = borderInsets.top + borderInsets.bottom + vGap;
         
         int compCount = parent.getComponentCount();
         for ( int index = 0; index < compCount; index++ )
         {
            prefHeight += parent.getComponent(compCount).getPreferredSize().getHeight();
         }
         
         Dimension d = new Dimension(prefWidth, prefHeight);
         System.out.println("ResposnePanel.preferredLayoutSize() d:" + d.toString() );
         return d;
      }

      /**
       * Calculates the minimum size dimensions for the specified
       * panel given the components in the specified parent container.
       * @param parent the component to be laid out
       * @see #preferredLayoutSize
       */
      public Dimension minimumLayoutSize(Container parent) 
      {
         Insets borderInsets = parent.getInsets();
         int minWidth = parent.getWidth();
         int minHeight = borderInsets.top + borderInsets.bottom + vGap;
         
         int compCount = parent.getComponentCount();

         for ( int index = 0; index < compCount; index++ )
         {
            minWidth += parent.getComponent(compCount).getMinimumSize().getHeight();
         }
         
         Dimension d = new Dimension(minWidth, minHeight);
         System.out.println("ResposnePanel.preferredLayoutSize() d:" + d.toString() );
         return d;
      }

      /**
       * Lays out the container in the specified panel.
       * @param parent the component which needs to be laid out
       */
      public void layoutContainer(Container parent) 
      {
         Insets borderInsets = parent.getInsets();
         int innerX = borderInsets.left;
         int innerY = borderInsets.top;
         int containerWidth = parent.getWidth() - borderInsets.left - borderInsets.right;
         int containerHeight = parent.getHeight() - borderInsets.top - borderInsets.bottom;
         int y = innerY;
         
         int compCount = parent.getComponentCount();
         
         if ( compCount == 0 )
            return;

         Component comp = parent.getComponent(0);

         comp.setBounds( innerX, innerY, containerWidth, (int)comp.getPreferredSize().getHeight() ) ;
         // components preferred height may have changed with the change in width, so size again... crazy!!
         comp.setSize( containerWidth, (int)comp.getPreferredSize().getHeight() );
         y += comp.getPreferredSize().getHeight();

         System.out.println("ResposnePanel.layoutContainer() fixed.bounds:" + comp.getBounds() );
         
         if ( compCount == 1 )
            return;

         int repeatPaneHeight = (containerHeight - y)/(compCount-1);

         for ( int index = 1; index < compCount; index++ )
         {
            y += vGap;
            comp = parent.getComponent(index);
            comp.setBounds( innerX, y, containerWidth, repeatPaneHeight );
            y += repeatPaneHeight;
            System.out.println("ResposnePanel.layoutContainer() repeat.bounds:" + comp.getBounds() );
         }         

      }

   }
}
