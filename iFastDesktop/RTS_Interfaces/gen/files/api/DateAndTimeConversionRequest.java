// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Date and Time Conversion Inq request.
 * For additional view information see <A HREF="../../../../viewspecs/DateAndTimeConversion.doc">DateAndTimeConversion.doc</A>.
 * 
 * @author RTS Generated
 */
public class DateAndTimeConversionRequest extends IFastRequest implements Serializable
{

   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Type of screen to update member array.
    */
   private String[] _UpdType = new String[25];
            
   /**
    * Table in cswacl to be updated member array.
    */
   private String[] _TableTag = new String[25];
            
   /**
    * Repeating Field 1 member array.
    */
   private String[] _Repeating1 = new String[25];
            
   /**
    * Repeating Field 2 member array.
    */
   private String[] _Repeating2 = new String[25];
            
   /**
    * Repeating Field 3 member array.
    */
   private String[] _Repeating3 = new String[25];
            
   /**
    * Repeating Field 4 member array.
    */
   private String[] _Repeating4 = new String[25];
            
   /**
    * Repeating Field 5 member array.
    */
   private String[] _Repeating5 = new String[25];
            
   /**
    * Repeating Field 6 member array.
    */
   private String[] _Repeating6 = new String[25];
            
   /**
    * Repeating Field 7 member array.
    */
   private String[] _Repeating7 = new String[25];
            
   /**
    * Repeating Field 8 member array.
    */
   private String[] _Repeating8 = new String[25];
            
   /**
    * Repeating Field 9 member array.
    */
   private String[] _Repeating9 = new String[25];
            
   /**
    * Repeating Field 10 member array.
    */
   private String[] _Repeating10 = new String[25];
            
   /**
    * Repeating Field 11 member array.
    */
   private String[] _Repeating11 = new String[25];
            
   /**
    * Repeating Field 12 member array.
    */
   private String[] _Repeating12 = new String[25];
            
   /**
    * Repeating Field 13 member array.
    */
   private String[] _Repeating13 = new String[25];
            
   /**
    * Repeating Field 14 member array.
    */
   private String[] _Repeating14 = new String[25];
            
   /**
    * Repeating Field 15 member array.
    */
   private String[] _Repeating15 = new String[25];
            
   /**
    * Repeating Field 16 member array.
    */
   private String[] _Repeating16 = new String[25];
            
   /**
    * Repeating Field 17 member array.
    */
   private String[] _Repeating17 = new String[25];
            
   /**
    * Repeating Field 18 member array.
    */
   private String[] _Repeating18 = new String[25];
            
   /**
    * Repeating Field 19 member array.
    */
   private String[] _Repeating19 = new String[25];
            
   /**
    * Repeating Field 20 member array.
    */
   private String[] _Repeating20 = new String[25];
            
   /**
    * Repeating Field 21 member array.
    */
   private String[] _Repeating21 = new String[25];
            
   /**
    * Repeating Field 22 member array.
    */
   private String[] _Repeating22 = new String[25];
            
   /**
    * Repeating Field 23 member array.
    */
   private String[] _Repeating23 = new String[25];
            
   /**
    * Repeating Field 24 member array.
    */
   private String[] _Repeating24 = new String[25];
            
   /**
    * Repeating Field 25 member array.
    */
   private String[] _Repeating25 = new String[25];
            
   /**
    * Repeating Field 26 member array.
    */
   private String[] _Repeating26 = new String[25];
            
   /**
    * Repeating Field 27 member array.
    */
   private String[] _Repeating27 = new String[25];
            
   /**
    * Repeating Field 28 member array.
    */
   private String[] _Repeating28 = new String[25];
            
   /**
    * Repeating Field 29 member array.
    */
   private String[] _Repeating29 = new String[25];
            
   /**
    * Repeating Field 30 member array.
    */
   private String[] _Repeating30 = new String[25];
            
   /**
    * Repeating Field 31 member array.
    */
   private String[] _Repeating31 = new String[25];
            
   /**
    * Repeating Field 32 member array.
    */
   private String[] _Repeating32 = new String[25];
            
   /**
    * Repeating Field 33 member array.
    */
   private String[] _Repeating33 = new String[25];
            
   /**
    * Repeating Field 34 member array.
    */
   private String[] _Repeating34 = new String[25];
            
   /**
    * Repeating Field 35 member array.
    */
   private String[] _Repeating35 = new String[25];
            

   /**
    * Constructs the DateAndTimeConversionRequest object.
    * 
    */
   DateAndTimeConversionRequest()
   {
      super ( 145 );
   }

   /**
    * Constructs the DateAndTimeConversionRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   DateAndTimeConversionRequest( String hostEncoding )
   {
      super ( 145, hostEncoding );
   }

   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the UserId field for the request.
    * 
    * @param value  Value that the UserId will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the LanguageCode field for the request.
    * 
    * @param value  Value that the LanguageCode will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the CompanyId field for the request.
    * 
    * @param value  Value that the CompanyId will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Type of screen to update field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Type of screen to update will be set to.
    */
   public final void setUpdType( int index, String value )
   {
      assertUnsent();
      _UpdType[index] = value;
   }
	
   /**
    * Sets the Table in cswacl to be updated field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Table in cswacl to be updated will be set to.
    */
   public final void setTableTag( int index, String value )
   {
      assertUnsent();
      _TableTag[index] = value;
   }
	
   /**
    * Sets the Repeating Field 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 1 will be set to.
    */
   public final void setRepeating1( int index, String value )
   {
      assertUnsent();
      _Repeating1[index] = value;
   }
	
   /**
    * Sets the Repeating Field 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 2 will be set to.
    */
   public final void setRepeating2( int index, String value )
   {
      assertUnsent();
      _Repeating2[index] = value;
   }
	
   /**
    * Sets the Repeating Field 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 3 will be set to.
    */
   public final void setRepeating3( int index, String value )
   {
      assertUnsent();
      _Repeating3[index] = value;
   }
	
   /**
    * Sets the Repeating Field 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 4 will be set to.
    */
   public final void setRepeating4( int index, String value )
   {
      assertUnsent();
      _Repeating4[index] = value;
   }
	
   /**
    * Sets the Repeating Field 5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 5 will be set to.
    */
   public final void setRepeating5( int index, String value )
   {
      assertUnsent();
      _Repeating5[index] = value;
   }
	
   /**
    * Sets the Repeating Field 6 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 6 will be set to.
    */
   public final void setRepeating6( int index, String value )
   {
      assertUnsent();
      _Repeating6[index] = value;
   }
	
   /**
    * Sets the Repeating Field 7 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 7 will be set to.
    */
   public final void setRepeating7( int index, String value )
   {
      assertUnsent();
      _Repeating7[index] = value;
   }
	
   /**
    * Sets the Repeating Field 8 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 8 will be set to.
    */
   public final void setRepeating8( int index, String value )
   {
      assertUnsent();
      _Repeating8[index] = value;
   }
	
   /**
    * Sets the Repeating Field 9 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 9 will be set to.
    */
   public final void setRepeating9( int index, String value )
   {
      assertUnsent();
      _Repeating9[index] = value;
   }
	
   /**
    * Sets the Repeating Field 10 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 10 will be set to.
    */
   public final void setRepeating10( int index, String value )
   {
      assertUnsent();
      _Repeating10[index] = value;
   }
	
   /**
    * Sets the Repeating Field 11 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 11 will be set to.
    */
   public final void setRepeating11( int index, String value )
   {
      assertUnsent();
      _Repeating11[index] = value;
   }
	
   /**
    * Sets the Repeating Field 12 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 12 will be set to.
    */
   public final void setRepeating12( int index, String value )
   {
      assertUnsent();
      _Repeating12[index] = value;
   }
	
   /**
    * Sets the Repeating Field 13 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 13 will be set to.
    */
   public final void setRepeating13( int index, String value )
   {
      assertUnsent();
      _Repeating13[index] = value;
   }
	
   /**
    * Sets the Repeating Field 14 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 14 will be set to.
    */
   public final void setRepeating14( int index, String value )
   {
      assertUnsent();
      _Repeating14[index] = value;
   }
	
   /**
    * Sets the Repeating Field 15 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 15 will be set to.
    */
   public final void setRepeating15( int index, String value )
   {
      assertUnsent();
      _Repeating15[index] = value;
   }
	
   /**
    * Sets the Repeating Field 16 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 16 will be set to.
    */
   public final void setRepeating16( int index, String value )
   {
      assertUnsent();
      _Repeating16[index] = value;
   }
	
   /**
    * Sets the Repeating Field 17 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 17 will be set to.
    */
   public final void setRepeating17( int index, String value )
   {
      assertUnsent();
      _Repeating17[index] = value;
   }
	
   /**
    * Sets the Repeating Field 18 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 18 will be set to.
    */
   public final void setRepeating18( int index, String value )
   {
      assertUnsent();
      _Repeating18[index] = value;
   }
	
   /**
    * Sets the Repeating Field 19 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 19 will be set to.
    */
   public final void setRepeating19( int index, String value )
   {
      assertUnsent();
      _Repeating19[index] = value;
   }
	
   /**
    * Sets the Repeating Field 20 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 20 will be set to.
    */
   public final void setRepeating20( int index, String value )
   {
      assertUnsent();
      _Repeating20[index] = value;
   }
	
   /**
    * Sets the Repeating Field 21 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 21 will be set to.
    */
   public final void setRepeating21( int index, String value )
   {
      assertUnsent();
      _Repeating21[index] = value;
   }
	
   /**
    * Sets the Repeating Field 22 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 22 will be set to.
    */
   public final void setRepeating22( int index, String value )
   {
      assertUnsent();
      _Repeating22[index] = value;
   }
	
   /**
    * Sets the Repeating Field 23 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 23 will be set to.
    */
   public final void setRepeating23( int index, String value )
   {
      assertUnsent();
      _Repeating23[index] = value;
   }
	
   /**
    * Sets the Repeating Field 24 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 24 will be set to.
    */
   public final void setRepeating24( int index, String value )
   {
      assertUnsent();
      _Repeating24[index] = value;
   }
	
   /**
    * Sets the Repeating Field 25 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 25 will be set to.
    */
   public final void setRepeating25( int index, String value )
   {
      assertUnsent();
      _Repeating25[index] = value;
   }
	
   /**
    * Sets the Repeating Field 26 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 26 will be set to.
    */
   public final void setRepeating26( int index, String value )
   {
      assertUnsent();
      _Repeating26[index] = value;
   }
	
   /**
    * Sets the Repeating Field 27 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 27 will be set to.
    */
   public final void setRepeating27( int index, String value )
   {
      assertUnsent();
      _Repeating27[index] = value;
   }
	
   /**
    * Sets the Repeating Field 28 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 28 will be set to.
    */
   public final void setRepeating28( int index, String value )
   {
      assertUnsent();
      _Repeating28[index] = value;
   }
	
   /**
    * Sets the Repeating Field 29 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 29 will be set to.
    */
   public final void setRepeating29( int index, String value )
   {
      assertUnsent();
      _Repeating29[index] = value;
   }
	
   /**
    * Sets the Repeating Field 30 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 30 will be set to.
    */
   public final void setRepeating30( int index, String value )
   {
      assertUnsent();
      _Repeating30[index] = value;
   }
	
   /**
    * Sets the Repeating Field 31 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 31 will be set to.
    */
   public final void setRepeating31( int index, String value )
   {
      assertUnsent();
      _Repeating31[index] = value;
   }
	
   /**
    * Sets the Repeating Field 32 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 32 will be set to.
    */
   public final void setRepeating32( int index, String value )
   {
      assertUnsent();
      _Repeating32[index] = value;
   }
	
   /**
    * Sets the Repeating Field 33 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 33 will be set to.
    */
   public final void setRepeating33( int index, String value )
   {
      assertUnsent();
      _Repeating33[index] = value;
   }
	
   /**
    * Sets the Repeating Field 34 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 34 will be set to.
    */
   public final void setRepeating34( int index, String value )
   {
      assertUnsent();
      _Repeating34[index] = value;
   }
	
   /**
    * Sets the Repeating Field 35 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating Field 35 will be set to.
    */
   public final void setRepeating35( int index, String value )
   {
      assertUnsent();
      _Repeating35[index] = value;
   }
	
   /**
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _UpdType[x] );
         requestBuffer.appendField( _TableTag[x] );
         requestBuffer.appendField( _Repeating1[x] );
         requestBuffer.appendField( _Repeating2[x] );
         requestBuffer.appendField( _Repeating3[x] );
         requestBuffer.appendField( _Repeating4[x] );
         requestBuffer.appendField( _Repeating5[x] );
         requestBuffer.appendField( _Repeating6[x] );
         requestBuffer.appendField( _Repeating7[x] );
         requestBuffer.appendField( _Repeating8[x] );
         requestBuffer.appendField( _Repeating9[x] );
         requestBuffer.appendField( _Repeating10[x] );
         requestBuffer.appendField( _Repeating11[x] );
         requestBuffer.appendField( _Repeating12[x] );
         requestBuffer.appendField( _Repeating13[x] );
         requestBuffer.appendField( _Repeating14[x] );
         requestBuffer.appendField( _Repeating15[x] );
         requestBuffer.appendField( _Repeating16[x] );
         requestBuffer.appendField( _Repeating17[x] );
         requestBuffer.appendField( _Repeating18[x] );
         requestBuffer.appendField( _Repeating19[x] );
         requestBuffer.appendField( _Repeating20[x] );
         requestBuffer.appendField( _Repeating21[x] );
         requestBuffer.appendField( _Repeating22[x] );
         requestBuffer.appendField( _Repeating23[x] );
         requestBuffer.appendField( _Repeating24[x] );
         requestBuffer.appendField( _Repeating25[x] );
         requestBuffer.appendField( _Repeating26[x] );
         requestBuffer.appendField( _Repeating27[x] );
         requestBuffer.appendField( _Repeating28[x] );
         requestBuffer.appendField( _Repeating29[x] );
         requestBuffer.appendField( _Repeating30[x] );
         requestBuffer.appendField( _Repeating31[x] );
         requestBuffer.appendField( _Repeating32[x] );
         requestBuffer.appendField( _Repeating33[x] );
         requestBuffer.appendField( _Repeating34[x] );
         requestBuffer.appendField( _Repeating35[x] );
      }
   }

}

