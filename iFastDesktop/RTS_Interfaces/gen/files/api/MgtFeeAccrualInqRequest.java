// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Mgt Fee & Mgt Fee Rebate Accrual Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/MgtFeeAccrualInq.doc">MgtFeeAccrualInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class MgtFeeAccrualInqRequest extends IFastRequest implements Serializable
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
    * Company ID member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Fund member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Starting Date member variable.
    */
   private Date _StartDate = null;
            
   /**
    * Ending Date member variable.
    */
   private Date _EndDate = null;
            
   /**
    * Summary Flag - field allowing inquire on summary accrual record member variable.
    */
   private Boolean _Summary = new Boolean(false);
            
   /**
    * Accrual Type - MF (mgt fee) or MFR (mgt fee rebate) member variable.
    */
   private String _AccrualType = "";
            
   /**
    * Accumulated Mgmt fee member variable.
    */
   private String _rxRunTotal = "0";
            

   /**
    * Constructs the MgtFeeAccrualInqRequest object.
    * 
    */
   MgtFeeAccrualInqRequest()
   {
      super ( 199 );
   }

   /**
    * Constructs the MgtFeeAccrualInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   MgtFeeAccrualInqRequest( String hostEncoding )
   {
      super ( 199, hostEncoding );
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
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
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
    * Sets the Starting Date field for the request.
    * 
    * @param value  Value that the Starting Date will be set to.
    */
   public final void setStartDate( Date value )
   {
      assertUnsent();
      _StartDate = value;
   }
	
   /**
    * Sets the Ending Date field for the request.
    * 
    * @param value  Value that the Ending Date will be set to.
    */
   public final void setEndDate( Date value )
   {
      assertUnsent();
      _EndDate = value;
   }
	
   /**
    * Sets the Summary Flag - field allowing inquire on summary accrual record field for the request.
    * 
    * @param value  Value that the Summary Flag - field allowing inquire on summary accrual record will be set to.
    */
   public final void setSummary( Boolean value )
   {
      assertUnsent();
      _Summary = value;
   }
	
   /**
    * Sets the Accrual Type - MF (mgt fee) or MFR (mgt fee rebate) field for the request.
    * 
    * @param value  Value that the Accrual Type - MF (mgt fee) or MFR (mgt fee rebate) will be set to.
    */
   public final void setAccrualType( String value )
   {
      assertUnsent();
      _AccrualType = value;
   }
	
   /**
    * Sets the Accumulated Mgmt fee field for the request.
    * 
    * @param value  Value that the Accumulated Mgmt fee will be set to.
    */
   public final void setrxRunTotal( String value )
   {
      assertUnsent();
      _rxRunTotal = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _StartDate );
      requestBuffer.appendField( _EndDate );
      requestBuffer.appendField( _Summary );
      requestBuffer.appendField( _AccrualType );
      requestBuffer.appendField( _rxRunTotal );
   }

}

