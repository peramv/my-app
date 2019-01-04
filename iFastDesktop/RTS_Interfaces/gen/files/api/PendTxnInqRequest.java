// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Pending Transactions request.
 * For additional view information see <A HREF="../../../../viewspecs/PendTxnInq.doc">PendTxnInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PendTxnInqRequest extends IFastRequest implements Serializable
{

            
   /**
    * SessionID member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyID member variable.
    */
   private String _CompanyId = "";
            
            
            
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * From Date member variable.
    */
   private Date _FromDate = null;
            
   /**
    * To Date member variable.
    */
   private Date _ToDate = null;
            
   /**
    * Field indicating if vew retruns pending, processed or both trades. member variable.
    */
   private String _RecordType = "";
            

   /**
    * Constructs the PendTxnInqRequest object.
    * 
    */
   PendTxnInqRequest()
   {
      super ( 365 );
   }

   /**
    * Constructs the PendTxnInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   PendTxnInqRequest( String hostEncoding )
   {
      super ( 365, hostEncoding );
   }

   /**
    * Sets the SessionID field for the request.
    * 
    * @param value  Value that the SessionID will be set to.
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
    * Sets the CompanyID field for the request.
    * 
    * @param value  Value that the CompanyID will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Fund Code field for the request.
    * 
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class Code field for the request.
    * 
    * @param value  Value that the Class Code will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the From Date field for the request.
    * 
    * @param value  Value that the From Date will be set to.
    */
   public final void setFromDate( Date value )
   {
      assertUnsent();
      _FromDate = value;
   }
	
   /**
    * Sets the To Date field for the request.
    * 
    * @param value  Value that the To Date will be set to.
    */
   public final void setToDate( Date value )
   {
      assertUnsent();
      _ToDate = value;
   }
	
   /**
    * Sets the Field indicating if vew retruns pending, processed or both trades. field for the request.
    * 
    * @param value  Value that the Field indicating if vew retruns pending, processed or both trades. will be set to.
    */
   public final void setRecordType( String value )
   {
      assertUnsent();
      _RecordType = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _FromDate );
      requestBuffer.appendField( _ToDate );
      requestBuffer.appendField( _RecordType );
   }

}

