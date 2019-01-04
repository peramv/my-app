package com.ifds.stubEditor;

import com.ifds.stubEditor.data.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class SeRecordDialog extends JDialog implements ActionListener
{
   private final SeRecordData _recordData;

   private final JButton _closeButton;

   public SeRecordDialog( SeRecordData recordData )
   {
      super();
      
      _recordData = recordData;

      setModal( true );
      setBounds( 30, 30, 900, 400 );
      
      JPanel contentPanel = new JPanel( new BorderLayout( 0, 0) );
      contentPanel.setBorder( BorderFactory.createEmptyBorder(10,10,10,10));
      getContentPane(). add( contentPanel );

      contentPanel.add( new JScrollPane( new SeRecordPanel( _recordData ) ), BorderLayout.CENTER );

      JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 0, 0));
      contentPanel.add( buttonPanel, BorderLayout.SOUTH );
      
      _closeButton = new JButton("Close");
      buttonPanel.add( _closeButton );
      _closeButton.addActionListener(this);
   }

   public void actionPerformed(ActionEvent event) 
   {
      Object source = event.getSource();
      if ( source == _closeButton )
      {
         closeAction(event);
      }
   }

   void closeAction(ActionEvent event)
   {
      setVisible( false );
   }
   
}

