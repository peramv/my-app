// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Shareholder Family Update request.
 * For additional view information see <A HREF="../../../../viewspecs/ShrFamilyUpd.doc">ShrFamilyUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrFamilyUpdRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Recid of Shareholder Family record member array.
    */
   private Integer[] _ShrFamilyRId = new Integer[25];
            
   /**
    * Family Code member array.
    */
   private String[] _FamilyCode = new String[25];
            
   /**
    * Type member array.
    */
   private String[] _Type = new String[25];
            
   /**
    * Role member array.
    */
   private String[] _Role = new String[25];
            
   /**
    * Family Name member array.
    */
   private String[] _FamilyName = new String[25];
            

   /**
    * Constructs the ShrFamilyUpdRequest object.
    * 
    */
   ShrFamilyUpdRequest()
   {
      super ( 234 );
   }

   /**
    * Constructs the ShrFamilyUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShrFamilyUpdRequest( String hostEncoding )
   {
      super ( 234, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User Id field for the request.
    * 
    * @param value  Value that the User Id will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the Language Code field for the request.
    * 
    * @param value  Value that the Language Code will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company Id field for the request.
    * 
    * @param value  Value that the Company Id will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Shareholder Number field for the request.
    * 
    * @param value  Value that the Shareholder Number will be set to.
    */
   public final void setShrNum( String value )
   {
      assertUnsent();
      _ShrNum = value;
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
    * Sets the RunMode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RunMode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Recid of Shareholder Family record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Recid of Shareholder Family record will be set to.
    */
   public final void setShrFamilyRId( int index, Integer value )
   {
      assertUnsent();
      _ShrFamilyRId[index] = value;
   }
	
   /**
    * Sets the Family Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Family Code will be set to.
    */
   public final void setFamilyCode( int index, String value )
   {
      assertUnsent();
      _FamilyCode[index] = value;
   }
	
   /**
    * Sets the Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Type will be set to.
    */
   public final void setType( int index, String value )
   {
      assertUnsent();
      _Type[index] = value;
   }
	
   /**
    * Sets the Role field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Role will be set to.
    */
   public final void setRole( int index, String value )
   {
      assertUnsent();
      _Role[index] = value;
   }
	
   /**
    * Sets the Family Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Family Name will be set to.
    */
   public final void setFamilyName( int index, String value )
   {
      assertUnsent();
      _FamilyName[index] = value;
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
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _ShrFamilyRId[x] );
         requestBuffer.appendField( _FamilyCode[x] );
         requestBuffer.appendField( _Type[x] );
         requestBuffer.appendField( _Role[x] );
         requestBuffer.appendField( _FamilyName[x] );
      }
   }

}

