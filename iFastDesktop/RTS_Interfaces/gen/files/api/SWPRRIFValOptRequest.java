// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * SWP/RRIF validations for GWA/LWA option request.
 * For additional view information see <A HREF="../../../../viewspecs/SWPRRIFValOpt.doc">SWPRRIFValOpt.doc</A>.
 * 
 * @author RTS Generated
 */
public class SWPRRIFValOptRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
   /**
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Validation Type member variable.
    */
   private String _ValidationType = "";
            
   /**
    * Transaction Number member variable.
    */
   private Integer _Transnum = null;
            
   /**
    * Fund member variable.
    */
   private String _Fund = "";
            
   /**
    * Class member variable.
    */
   private String _Class = "";
            
   /**
    * From Date member variable.
    */
   private Date _Deff = null;
            
   /**
    * To Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Payment Option member variable.
    */
   private String _PayOption = "";
            
   /**
    * RecID if either Bank-Detl or RRIF-Detail member variable.
    */
   private Integer _RecordID = null;
            

   /**
    * Constructs the SWPRRIFValOptRequest object.
    * 
    */
   SWPRRIFValOptRequest()
   {
      super ( 438 );
   }

   /**
    * Constructs the SWPRRIFValOptRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SWPRRIFValOptRequest( String hostEncoding )
   {
      super ( 438, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
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
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Run Mode field for the request.
    * 
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
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
    * Sets the Validation Type field for the request.
    * 
    * @param value  Value that the Validation Type will be set to.
    */
   public final void setValidationType( String value )
   {
      assertUnsent();
      _ValidationType = value;
   }
	
   /**
    * Sets the Transaction Number field for the request.
    * 
    * @param value  Value that the Transaction Number will be set to.
    */
   public final void setTransnum( Integer value )
   {
      assertUnsent();
      _Transnum = value;
   }
	
   /**
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFund( String value )
   {
      assertUnsent();
      _Fund = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClass( String value )
   {
      assertUnsent();
      _Class = value;
   }
	
   /**
    * Sets the From Date field for the request.
    * 
    * @param value  Value that the From Date will be set to.
    */
   public final void setDeff( Date value )
   {
      assertUnsent();
      _Deff = value;
   }
	
   /**
    * Sets the To Date field for the request.
    * 
    * @param value  Value that the To Date will be set to.
    */
   public final void setStopDate( Date value )
   {
      assertUnsent();
      _StopDate = value;
   }
	
   /**
    * Sets the Payment Option field for the request.
    * 
    * @param value  Value that the Payment Option will be set to.
    */
   public final void setPayOption( String value )
   {
      assertUnsent();
      _PayOption = value;
   }
	
   /**
    * Sets the RecID if either Bank-Detl or RRIF-Detail field for the request.
    * 
    * @param value  Value that the RecID if either Bank-Detl or RRIF-Detail will be set to.
    */
   public final void setRecordID( Integer value )
   {
      assertUnsent();
      _RecordID = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _ValidationType );
      requestBuffer.appendField( _Transnum );
      requestBuffer.appendField( _Fund );
      requestBuffer.appendField( _Class );
      requestBuffer.appendField( _Deff );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _PayOption );
      requestBuffer.appendField( _RecordID );
   }

}

