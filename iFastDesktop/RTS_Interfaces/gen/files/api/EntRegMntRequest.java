// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Entity Regulatory Detail Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/EntRegMnt.doc">EntRegMnt.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntRegMntRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mod member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Entity Id member array.
    */
   private String[] _EntityId = new String[25];
            
   /**
    * EntRegDetlUUID member array.
    */
   private String[] _EntRegDetlUUID = new String[25];
            
   /**
    * Regulation member array.
    */
   private String[] _Regulation = new String[25];
            
   /**
    * FATCA Classification member array.
    */
   private String[] _FATCAClass = new String[25];
            
   /**
    * Start Date member array.
    */
   private Date[] _StartDate = new Date[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Version member array.
    */
   private Integer[] _Version = new Integer[25];
            

   /**
    * Constructs the EntRegMntRequest object.
    * 
    */
   EntRegMntRequest()
   {
      super ( 457 );
   }

   /**
    * Constructs the EntRegMntRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EntRegMntRequest( String hostEncoding )
   {
      super ( 457, hostEncoding );
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
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
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
    * Sets the Run Mod field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mod will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Entity Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity Id will be set to.
    */
   public final void setEntityId( int index, String value )
   {
      assertUnsent();
      _EntityId[index] = value;
   }
	
   /**
    * Sets the EntRegDetlUUID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the EntRegDetlUUID will be set to.
    */
   public final void setEntRegDetlUUID( int index, String value )
   {
      assertUnsent();
      _EntRegDetlUUID[index] = value;
   }
	
   /**
    * Sets the Regulation field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Regulation will be set to.
    */
   public final void setRegulation( int index, String value )
   {
      assertUnsent();
      _Regulation[index] = value;
   }
	
   /**
    * Sets the FATCA Classification field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the FATCA Classification will be set to.
    */
   public final void setFATCAClass( int index, String value )
   {
      assertUnsent();
      _FATCAClass[index] = value;
   }
	
   /**
    * Sets the Start Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Start Date will be set to.
    */
   public final void setStartDate( int index, Date value )
   {
      assertUnsent();
      _StartDate[index] = value;
   }
	
   /**
    * Sets the Stop Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Version will be set to.
    */
   public final void setVersion( int index, Integer value )
   {
      assertUnsent();
      _Version[index] = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _EntityId[x] );
         requestBuffer.appendField( _EntRegDetlUUID[x] );
         requestBuffer.appendField( _Regulation[x] );
         requestBuffer.appendField( _FATCAClass[x] );
         requestBuffer.appendField( _StartDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _Version[x] );
      }
   }

}

