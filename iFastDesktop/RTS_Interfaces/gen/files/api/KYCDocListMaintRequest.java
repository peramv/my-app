// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * KYC  Document List Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/KYCDocListMaint.doc">KYCDocListMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class KYCDocListMaintRequest extends IFastRequest implements Serializable
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
    * Entity ID member variable.
    */
   private String _EntityID = "0";
            
   /**
    * Type of the Regulatory Standard member variable.
    */
   private String _ComplyRule = "";
            
   /**
    * AWDBusinessArea member variable.
    */
   private String _AWDBusinessArea = "";
            
   /**
    * AWDWorkType member variable.
    */
   private String _AWDWorkType = "";
            
   /**
    * AWDObjectKey member variable.
    */
   private String _AWDObjectKey = "";
            
   /**
    * AWDObjDateTime member variable.
    */
   private String _AWDObjDateTime = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Document  Code of the Doc Master member array.
    */
   private String[] _DocCode = new String[100];
            
   /**
    * Document Status member array.
    */
   private String[] _StatusCode = new String[100];
            
   /**
    * Date the Document was received member array.
    */
   private Date[] _ReceivedDate = new Date[100];
            
   /**
    * Remarks member array.
    */
   private String[] _Remarks = new String[100];
            
   /**
    * AcctDocList RECID member array.
    */
   private Integer[] _AcctDocListRecID = new Integer[100];
            
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[100];
            
   /**
    * Effective Date member array.
    */
   private Date[] _Deff = new Date[100];
            
   /**
    * Expiration Date member array.
    */
   private Date[] _ExpiryDate = new Date[100];
            
   /**
    * Requested Date member array.
    */
   private Date[] _RequestDate = new Date[100];
            
   /**
    * Reference Number member array.
    */
   private String[] _RefNumber = new String[100];
            
   /**
    * AcctDocListUUID member array.
    */
   private String[] _AcctDocListUUID = new String[100];
            

   /**
    * Constructs the KYCDocListMaintRequest object.
    * 
    */
   KYCDocListMaintRequest()
   {
      super ( 390 );
   }

   /**
    * Constructs the KYCDocListMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   KYCDocListMaintRequest( String hostEncoding )
   {
      super ( 390, hostEncoding );
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
    * Sets the Entity ID field for the request.
    * 
    * @param value  Value that the Entity ID will be set to.
    */
   public final void setEntityID( String value )
   {
      assertUnsent();
      _EntityID = value;
   }
	
   /**
    * Sets the Type of the Regulatory Standard field for the request.
    * 
    * @param value  Value that the Type of the Regulatory Standard will be set to.
    */
   public final void setComplyRule( String value )
   {
      assertUnsent();
      _ComplyRule = value;
   }
	
   /**
    * Sets the AWDBusinessArea field for the request.
    * 
    * @param value  Value that the AWDBusinessArea will be set to.
    */
   public final void setAWDBusinessArea( String value )
   {
      assertUnsent();
      _AWDBusinessArea = value;
   }
	
   /**
    * Sets the AWDWorkType field for the request.
    * 
    * @param value  Value that the AWDWorkType will be set to.
    */
   public final void setAWDWorkType( String value )
   {
      assertUnsent();
      _AWDWorkType = value;
   }
	
   /**
    * Sets the AWDObjectKey field for the request.
    * 
    * @param value  Value that the AWDObjectKey will be set to.
    */
   public final void setAWDObjectKey( String value )
   {
      assertUnsent();
      _AWDObjectKey = value;
   }
	
   /**
    * Sets the AWDObjDateTime field for the request.
    * 
    * @param value  Value that the AWDObjDateTime will be set to.
    */
   public final void setAWDObjDateTime( String value )
   {
      assertUnsent();
      _AWDObjDateTime = value;
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
    * Sets the Document  Code of the Doc Master field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Document  Code of the Doc Master will be set to.
    */
   public final void setDocCode( int index, String value )
   {
      assertUnsent();
      _DocCode[index] = value;
   }
	
   /**
    * Sets the Document Status field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Document Status will be set to.
    */
   public final void setStatusCode( int index, String value )
   {
      assertUnsent();
      _StatusCode[index] = value;
   }
	
   /**
    * Sets the Date the Document was received field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Date the Document was received will be set to.
    */
   public final void setReceivedDate( int index, Date value )
   {
      assertUnsent();
      _ReceivedDate[index] = value;
   }
	
   /**
    * Sets the Remarks field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks will be set to.
    */
   public final void setRemarks( int index, String value )
   {
      assertUnsent();
      _Remarks[index] = value;
   }
	
   /**
    * Sets the AcctDocList RECID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AcctDocList RECID will be set to.
    */
   public final void setAcctDocListRecID( int index, Integer value )
   {
      assertUnsent();
      _AcctDocListRecID[index] = value;
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
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setDeff( int index, Date value )
   {
      assertUnsent();
      _Deff[index] = value;
   }
	
   /**
    * Sets the Expiration Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Expiration Date will be set to.
    */
   public final void setExpiryDate( int index, Date value )
   {
      assertUnsent();
      _ExpiryDate[index] = value;
   }
	
   /**
    * Sets the Requested Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Requested Date will be set to.
    */
   public final void setRequestDate( int index, Date value )
   {
      assertUnsent();
      _RequestDate[index] = value;
   }
	
   /**
    * Sets the Reference Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reference Number will be set to.
    */
   public final void setRefNumber( int index, String value )
   {
      assertUnsent();
      _RefNumber[index] = value;
   }
	
   /**
    * Sets the AcctDocListUUID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AcctDocListUUID will be set to.
    */
   public final void setAcctDocListUUID( int index, String value )
   {
      assertUnsent();
      _AcctDocListUUID[index] = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _EntityID );
      requestBuffer.appendField( _ComplyRule );
      requestBuffer.appendField( _AWDBusinessArea );
      requestBuffer.appendField( _AWDWorkType );
      requestBuffer.appendField( _AWDObjectKey );
      requestBuffer.appendField( _AWDObjDateTime );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _DocCode[x] );
         requestBuffer.appendField( _StatusCode[x] );
         requestBuffer.appendField( _ReceivedDate[x] );
         requestBuffer.appendField( _Remarks[x] );
         requestBuffer.appendField( _AcctDocListRecID[x] );
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _Deff[x] );
         requestBuffer.appendField( _ExpiryDate[x] );
         requestBuffer.appendField( _RequestDate[x] );
         requestBuffer.appendField( _RefNumber[x] );
         requestBuffer.appendField( _AcctDocListUUID[x] );
      }
   }

}

