package com.ifds.stubEditor;

import com.ifds.stubEditor.data.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.BevelBorder;

class SeRepeatSectionPanel extends JPanel implements ActionListener
{
   private final SeRepeatSectionData _repeatData;

   private final JTable _repeatTable;
   private final JButton _addButton;
   private final JButton _editButton;
   private final JButton _deleteButton;
   
   SeRepeatSectionPanel( SeRepeatSectionData repeatData )
   {
      super();
      this.setLayout( new BoxLayout( this, BoxLayout.Y_AXIS ) );
      this.setBorder( BorderFactory.createCompoundBorder( BorderFactory.createEtchedBorder(),
                                                          BorderFactory.createEmptyBorder(5,5,5,5) ) );

      _repeatData = repeatData;

      _repeatTable = new JTable( _repeatData );
      _repeatTable.setSelectionMode( ListSelectionModel.SINGLE_SELECTION );
      _repeatTable.changeSelection( 0, 0, false, false );
      _repeatTable.addMouseListener( 
         new MouseAdapter()
         {
            public void mouseClicked(MouseEvent event)
            {
               Object object = event.getSource();
               if ( object == _repeatTable && event.getClickCount() >1 )
               {
                  editAction(event);
               }
            }
         } );

      JScrollPane scrollPane = new JScrollPane( _repeatTable );
      add(scrollPane);
   
      JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 0, 0));
      add( buttonPanel );

      _addButton = new JButton("Add");
      buttonPanel.add( _addButton );
      _addButton.addActionListener(this);
      
      _editButton = new JButton("Edit");
      buttonPanel.add( _editButton );
      _editButton.addActionListener(this);
   
      _deleteButton = new JButton("Delete");
      buttonPanel.add( _deleteButton );
      _deleteButton.addActionListener(this);
   }
   
   public void actionPerformed(ActionEvent event) 
   {
      Object source = event.getSource();
      if ( source == _addButton )
      {
         addAction(event);
      }
      else if ( source == _editButton )
      {
         editAction(event);
      }
      else if ( source == _deleteButton )
      {
         deleteAction(event);
      }
   }

   void addAction(AWTEvent event)
   {
      SeRecordData newRecord = _repeatData.newRecord();
      (new SeRecordDialog( newRecord )).setVisible( true );
      _repeatData.addRecord(newRecord);
   }
   
   void editAction(AWTEvent event)
   {

      int rowIndex = _repeatTable.getSelectedRow();

      if ( rowIndex == -1 )
         return;

      SeRecordData record = _repeatData.getRecord(rowIndex);
      (new SeRecordDialog( record )).setVisible( true );

      _repeatData.setRecord( rowIndex, record );
   }

   void deleteAction(AWTEvent event)
   {
      int rowIndex = _repeatTable.getSelectedRow();
      
      if ( rowIndex != -1 && 
           JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(this,
                                                                   "Are you sure you want to delete the selected record?",
                                                                   "Confirm Delete" ,
                                                                   JOptionPane.YES_NO_OPTION,
                                                                   JOptionPane.QUESTION_MESSAGE ) )
      {
         _repeatData.removeRecord( rowIndex );
      }
   }

}
