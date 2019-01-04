// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * KYC Atribute List Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/KYCAttribMnt.doc">KYCAttribMnt.doc</A>.
 * 
 * @author RTS Generated
 */
public class KYCAttribMntRequest extends IFastRequest implements Serializable
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
    * AccountNum member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * EntityId member variable.
    */
   private String _EntityId = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * AttribType member array.
    */
   private String[] _AttribType = new String[25];
            
   /**
    * AttribCode member array.
    */
   private String[] _AttribCode = new String[25];
            
   /**
    * AttribStat member array.
    */
   private String[] _AttribStat = new String[25];
            
   /**
    * AttribDesc member array.
    */
   private String[] _AttribDesc = new String[25];
            

   /**
    * Constructs the KYCAttribMntRequest object.
    * 
    */
   KYCAttribMntRequest()
   {
      super ( 466 );
   }

   /**
    * Constructs the KYCAttribMntRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   KYCAttribMntRequest( String hostEncoding )
   {
      super ( 466, hostEncoding );
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
    * Sets the AccountNum field for the request.
    * 
    * @param value  Value that the AccountNum will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the EntityId field for the request.
    * 
    * @param value  Value that the EntityId will be set to.
    */
   public final void setEntityId( String value )
   {
      assertUnsent();
      _EntityId = value;
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
    * Sets the AttribType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AttribType will be set to.
    */
   public final void setAttribType( int index, String value )
   {
      assertUnsent();
      _AttribType[index] = value;
   }
	
   /**
    * Sets the AttribCode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AttribCode will be set to.
    */
   public final void setAttribCode( int index, String value )
   {
      assertUnsent();
      _AttribCode[index] = value;
   }
	
   /**
    * Sets the AttribStat field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AttribStat will be set to.
    */
   public final void setAttribStat( int index, String value )
   {
      assertUnsent();
      _AttribStat[index] = value;
   }
	
   /**
    * Sets the AttribDesc field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AttribDesc will be set to.
    */
   public final void setAttribDesc( int index, String value )
   {
      assertUnsent();
      _AttribDesc[index] = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _EntityId );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _AttribType[x] );
         requestBuffer.appendField( _AttribCode[x] );
         requestBuffer.appendField( _AttribStat[x] );
         requestBuffer.appendField( _AttribDesc[x] );
      }
   }

}

