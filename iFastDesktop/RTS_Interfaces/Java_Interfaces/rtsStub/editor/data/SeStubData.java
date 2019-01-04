package com.ifds.stubEditor.data;

import com.ifds.rts.*;
import java.util.*;
import java.io.*;
import java.text.ParseException;
import java.io.UnsupportedEncodingException;

public abstract class SeStubData
{
   private File _file = null;
   private String _encoding = null;
   private final ArrayList _sectionList = new ArrayList();
   
   /*
    *
    */
   public SeStubData()
   {
      _file = null;
      _encoding = null;
   }

   /*
    *
    */
   public SeStubData( File file, String encoding ) throws IOException
   {
      _file = file;
      _encoding = encoding;
   }

   /*
    *
    */
   protected final void initFromBuffer( RTSDecodeBuffer buffer ) throws ParseException, UnsupportedEncodingException
   {
      Iterator iter = _sectionList.iterator();

      while ( iter.hasNext() )
         ( (SeSectionData)iter.next() ).initFromBuffer(buffer);

   }

   /*
    *
    */
   protected final void saveToBuffer( RTSEncodeBuffer buffer ) throws ParseException, UnsupportedEncodingException
   {
      Iterator iter = _sectionList.iterator();

      while ( iter.hasNext() )
         ( (SeSectionData)iter.next() ).saveToBuffer(buffer);

   }

   /*
    *
    */
   public final boolean isDirty()
   {
      Iterator iter = _sectionList.iterator();
      while ( iter.hasNext() )
      {
         if ( ( (SeSectionData)iter.next() ).isDirty() )
            return true;
      }

      return false;

   }

   /*
    *
    */
   public final void addSection( SeSectionData section )
   {
      _sectionList.add( section );
   }

   /*
    *
    */
   public final int getSectionCount()
   {
      return _sectionList.size();
   }

   /*
    *
    */
   public final SeSectionData getSection( int index )
   {
      return (SeSectionData)_sectionList.get( index );
   }
   
   /*
    *
    */
   public final boolean hasValidFile()
   {
      return ( _file != null && _file.canWrite() );
   }

   /*
    *
    */
   public final void save() throws IOException, ParseException
   {

      RTSWriter writer = new RTSWriter( new FileOutputStream( _file ) );
      writer.write( asBuffer( _encoding ) );
   }

   /*
    *
    */
   public final void saveAs( File file, String encoding ) throws IOException, ParseException
   {
      File previousFile = _file;
      String previousEncoding = _encoding;

      _file = file;
      _encoding = encoding;

      try
      {
         save();
      }
      catch( IOException e )
      {
         _file = previousFile;
         _encoding = previousEncoding;
         throw e;
      }
   }

   /*
    *
    */
   protected final void load() throws IOException, ParseException
   {

      if ( _file.exists() )
      {
         initFromBuffer( readBufferFromFile( _file, _encoding ) );
      }
      else if ( !_file.canWrite() )
         throw new FileNotFoundException( "File \"" + _file.getAbsolutePath() + "\" not avaialable for write." );
   }

   /*
    *
    */
   public abstract RTSBuffer asBuffer( String encoding ) throws ParseException, UnsupportedEncodingException;

   /*
    *
    */
   protected abstract RTSDecodeBuffer readBufferFromFile( File file, String encoding ) throws IOException, ParseException;

   /*
    *
    */
   public static SeStubData fromStubFile( File stubFile, String encoding ) throws IOException, ParseException, InstantiationException
   {
      System.out.println( "Opening stub file: " + stubFile.toString() + " [" + encoding +"]" );
      if ( isResponseFile( stubFile ) )
         return SeResponseData.fromResponseFile( stubFile, encoding );
      else
         return SeRequestData.fromRequestFile( stubFile, encoding );
   }

   /*
    *
    */
   private static boolean isResponseFile( File stubFile ) throws IOException
   {
      FileInputStream inStream = new FileInputStream( stubFile );
      
      try
      {
         int c = inStream.read();
   
         if ( c== -1 )
            throw new EOFException();
   
         if ( (char)c == 'B' || (char)c == 'S' )
            return true;
      
         return false;
      }
      finally 
      {
         inStream.close();
      }
   }

}

