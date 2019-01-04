package com.ifds.stubEditor;

import com.ifds.stubEditor.data.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class SeField extends JComponent implements DocumentListener, ActionListener
{
   private final SeFieldData _fieldData;

   private final JTextField _textField;
   private final JCheckBox _notNullIndicator;

   public SeField( String name, SeFieldData fieldData )
   {
      super();
      setLayout( new FlowLayout( FlowLayout.LEFT ) );
      setAlignmentX( RIGHT_ALIGNMENT );
      setAlignmentY( CENTER_ALIGNMENT );
      setName( name );

      _fieldData = fieldData;
      
      add( new JLabel( name ) );
      add( new JSeparator() );

      _notNullIndicator = new JCheckBox();
      _notNullIndicator.setSelected( !_fieldData.isNull() );
      add( _notNullIndicator );

      _textField = new JTextField( _fieldData.getText(), 25 );
      _textField.setEnabled( !_fieldData.isNull() );
      add( _textField );

      refresh();
      
      _notNullIndicator.addActionListener( this );
      _textField.addActionListener( this );
      _textField.getDocument().addDocumentListener( this );
   }

   public String getText()
   {
      return _textField.getText();
   }

   public void setText( String text )
   {
      _textField.setText( text );
   }

   public void actionPerformed(ActionEvent event) 
   {
      Object source = event.getSource();
      if ( source == _notNullIndicator )
      {
         notNullIndicatorAction(event);
      }
   }
   
   void notNullIndicatorAction(ActionEvent event)
   {
      if ( _fieldData.isNull() == _notNullIndicator.isSelected() )
      {
         _fieldData.setNull( !_notNullIndicator.isSelected() );
         refresh();
      }

   }
   
   void refresh()
   {
      if ( _fieldData.isNull() )
      {
         _notNullIndicator.setSelected( false );
         _textField.setEnabled( false );
         _textField.setText("<null>");
      }
      else
      {
         _notNullIndicator.setSelected( true );
         _textField.setEnabled( true );
         _textField.setText(_fieldData.getText());
      }
   }

   public void insertUpdate(DocumentEvent e) 
   {
      updateText();
   }
   
   public void removeUpdate(DocumentEvent e) 
   {
      updateText();
   }

   public void changedUpdate(DocumentEvent e) 
   {
      updateText();
   }

   private void updateText()
   {
      if ( !_fieldData.isNull() && !_fieldData.getText().equals( _textField.getText() ) )
      {
         _fieldData.setText( _textField.getText() );
      }
   }

}




