// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Controls Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctCtrlsInq.doc">AcctCtrlsInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctCtrlsInqRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * List Rule Type member variable.
    */
   private String _RuleType = "";
            
   /**
    * Fund member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Start Date member variable.
    */
   private Date _StartDate = null;
            
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Duplicate Check member variable.
    */
   private Boolean _DuplicateCheck = new Boolean(false);
            
   /**
    * AcctControls RID member variable.
    */
   private Integer _AcctControlsRID = null;
            
   /**
    * Inquiry Type to separate the logic to inquire the AcctControl record by RuleType member variable.
    */
   private String _InquiryType = "";
            

   /**
    * Constructs the AcctCtrlsInqRequest object.
    * 
    */
   AcctCtrlsInqRequest()
   {
      super ( 386 );
   }

   /**
    * Constructs the AcctCtrlsInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctCtrlsInqRequest( String hostEncoding )
   {
      super ( 386, hostEncoding );
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
    * Sets the List Rule Type field for the request.
    * 
    * @param value  Value that the List Rule Type will be set to.
    */
   public final void setRuleType( String value )
   {
      assertUnsent();
      _RuleType = value;
   }
	
   /**
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the Start Date field for the request.
    * 
    * @param value  Value that the Start Date will be set to.
    */
   public final void setStartDate( Date value )
   {
      assertUnsent();
      _StartDate = value;
   }
	
   /**
    * Sets the Stop Date field for the request.
    * 
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( Date value )
   {
      assertUnsent();
      _StopDate = value;
   }
	
   /**
    * Sets the Duplicate Check field for the request.
    * 
    * @param value  Value that the Duplicate Check will be set to.
    */
   public final void setDuplicateCheck( Boolean value )
   {
      assertUnsent();
      _DuplicateCheck = value;
   }
	
   /**
    * Sets the AcctControls RID field for the request.
    * 
    * @param value  Value that the AcctControls RID will be set to.
    */
   public final void setAcctControlsRID( Integer value )
   {
      assertUnsent();
      _AcctControlsRID = value;
   }
	
   /**
    * Sets the Inquiry Type to separate the logic to inquire the AcctControl record by RuleType field for the request.
    * 
    * @param value  Value that the Inquiry Type to separate the logic to inquire the AcctControl record by RuleType will be set to.
    */
   public final void setInquiryType( String value )
   {
      assertUnsent();
      _InquiryType = value;
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
      requestBuffer.appendField( _RuleType );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _StartDate );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _DuplicateCheck );
      requestBuffer.appendField( _AcctControlsRID );
      requestBuffer.appendField( _InquiryType );
   }

}

