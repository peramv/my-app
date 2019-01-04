// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Regulatory Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctRegMnt.doc">AcctRegMnt.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctRegMntRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
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
    * Account member variable.
    */
   private String _Account = "0";
            
   /**
    * Request Indicia Search member variable.
    */
   private Boolean _ReqIndicia = new Boolean(false);
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * AcctRegDetailsUUID member array.
    */
   private String[] _AcctRegDetailsUUID = new String[25];
            
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * StopDate member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * FICategory member array.
    */
   private String[] _FICategory = new String[25];
            
   /**
    * FinInstRegDetlUUID member array.
    */
   private String[] _FinInstRegDetlUUID = new String[25];
            
   /**
    * ComplyAction member array.
    */
   private String[] _ComplyAction = new String[25];
            
   /**
    * Consented member array.
    */
   private String[] _Consented = new String[25];
            
   /**
    * Version member array.
    */
   private Integer[] _Version = new Integer[25];
            
   /**
    * ComplyRule member array.
    */
   private String[] _ComplyRule = new String[25];
            

   /**
    * Constructs the AcctRegMntRequest object.
    * 
    */
   AcctRegMntRequest()
   {
      super ( 452 );
   }

   /**
    * Constructs the AcctRegMntRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctRegMntRequest( String hostEncoding )
   {
      super ( 452, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
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
    * Sets the Account field for the request.
    * 
    * @param value  Value that the Account will be set to.
    */
   public final void setAccount( String value )
   {
      assertUnsent();
      _Account = value;
   }
	
   /**
    * Sets the Request Indicia Search field for the request.
    * 
    * @param value  Value that the Request Indicia Search will be set to.
    */
   public final void setReqIndicia( Boolean value )
   {
      assertUnsent();
      _ReqIndicia = value;
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
    * Sets the AcctRegDetailsUUID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AcctRegDetailsUUID will be set to.
    */
   public final void setAcctRegDetailsUUID( int index, String value )
   {
      assertUnsent();
      _AcctRegDetailsUUID[index] = value;
   }
	
   /**
    * Sets the EffectiveDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the EffectiveDate will be set to.
    */
   public final void setEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _EffectiveDate[index] = value;
   }
	
   /**
    * Sets the StopDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the StopDate will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the FICategory field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the FICategory will be set to.
    */
   public final void setFICategory( int index, String value )
   {
      assertUnsent();
      _FICategory[index] = value;
   }
	
   /**
    * Sets the FinInstRegDetlUUID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the FinInstRegDetlUUID will be set to.
    */
   public final void setFinInstRegDetlUUID( int index, String value )
   {
      assertUnsent();
      _FinInstRegDetlUUID[index] = value;
   }
	
   /**
    * Sets the ComplyAction field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ComplyAction will be set to.
    */
   public final void setComplyAction( int index, String value )
   {
      assertUnsent();
      _ComplyAction[index] = value;
   }
	
   /**
    * Sets the Consented field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Consented will be set to.
    */
   public final void setConsented( int index, String value )
   {
      assertUnsent();
      _Consented[index] = value;
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
    * Sets the ComplyRule field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ComplyRule will be set to.
    */
   public final void setComplyRule( int index, String value )
   {
      assertUnsent();
      _ComplyRule[index] = value;
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
      requestBuffer.appendField( _Account );
      requestBuffer.appendField( _ReqIndicia );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _AcctRegDetailsUUID[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _FICategory[x] );
         requestBuffer.appendField( _FinInstRegDetlUUID[x] );
         requestBuffer.appendField( _ComplyAction[x] );
         requestBuffer.appendField( _Consented[x] );
         requestBuffer.appendField( _Version[x] );
         requestBuffer.appendField( _ComplyRule[x] );
      }
   }

}

