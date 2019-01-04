// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Entity Search Identity Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/EntSrcIDUpd.doc">EntSrcIDUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntSrcIDUpdRequest extends IFastRequest implements Serializable
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
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Entity ID member array.
    */
   private String[] _EntityId = new String[25];
            
   /**
    * Type of Identification member array.
    */
   private String[] _IDType = new String[25];
            
   /**
    * Identification Value member array.
    */
   private String[] _IDValue = new String[25];
            
   /**
    * ID Issue Date member array.
    */
   private Date[] _IDDate = new Date[25];
            
   /**
    * Entity-SearchID Table Version Number member array.
    */
   private Integer[] _EntitySearchIdVer = new Integer[25];
            
   /**
    * Entity-SearchID Table RECID member array.
    */
   private Integer[] _EntitySearchIdRid = new Integer[25];
            
   /**
    * ID Status member array.
    */
   private String[] _IDStatus = new String[25];
            
   /**
    * Country Of Issue member array.
    */
   private String[] _CountryofIssue = new String[25];
            
   /**
    * IdExpireDate member array.
    */
   private Date[] _IdExpireDate = new Date[25];
            

   /**
    * Constructs the EntSrcIDUpdRequest object.
    * 
    */
   EntSrcIDUpdRequest()
   {
      super ( 79 );
   }

   /**
    * Constructs the EntSrcIDUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EntSrcIDUpdRequest( String hostEncoding )
   {
      super ( 79, hostEncoding );
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
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Entity ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity ID will be set to.
    */
   public final void setEntityId( int index, String value )
   {
      assertUnsent();
      _EntityId[index] = value;
   }
	
   /**
    * Sets the Type of Identification field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Type of Identification will be set to.
    */
   public final void setIDType( int index, String value )
   {
      assertUnsent();
      _IDType[index] = value;
   }
	
   /**
    * Sets the Identification Value field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Identification Value will be set to.
    */
   public final void setIDValue( int index, String value )
   {
      assertUnsent();
      _IDValue[index] = value;
   }
	
   /**
    * Sets the ID Issue Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ID Issue Date will be set to.
    */
   public final void setIDDate( int index, Date value )
   {
      assertUnsent();
      _IDDate[index] = value;
   }
	
   /**
    * Sets the Entity-SearchID Table Version Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity-SearchID Table Version Number will be set to.
    */
   public final void setEntitySearchIdVer( int index, Integer value )
   {
      assertUnsent();
      _EntitySearchIdVer[index] = value;
   }
	
   /**
    * Sets the Entity-SearchID Table RECID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity-SearchID Table RECID will be set to.
    */
   public final void setEntitySearchIdRid( int index, Integer value )
   {
      assertUnsent();
      _EntitySearchIdRid[index] = value;
   }
	
   /**
    * Sets the ID Status field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ID Status will be set to.
    */
   public final void setIDStatus( int index, String value )
   {
      assertUnsent();
      _IDStatus[index] = value;
   }
	
   /**
    * Sets the Country Of Issue field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Country Of Issue will be set to.
    */
   public final void setCountryofIssue( int index, String value )
   {
      assertUnsent();
      _CountryofIssue[index] = value;
   }
	
   /**
    * Sets the IdExpireDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the IdExpireDate will be set to.
    */
   public final void setIdExpireDate( int index, Date value )
   {
      assertUnsent();
      _IdExpireDate[index] = value;
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
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _EntityId[x] );
         requestBuffer.appendField( _IDType[x] );
         requestBuffer.appendField( _IDValue[x] );
         requestBuffer.appendField( _IDDate[x] );
         requestBuffer.appendField( _EntitySearchIdVer[x] );
         requestBuffer.appendField( _EntitySearchIdRid[x] );
         requestBuffer.appendField( _IDStatus[x] );
         requestBuffer.appendField( _CountryofIssue[x] );
         requestBuffer.appendField( _IdExpireDate[x] );
      }
   }

}

