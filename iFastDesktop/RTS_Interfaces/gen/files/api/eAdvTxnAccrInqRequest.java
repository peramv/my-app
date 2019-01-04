// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * eAdvisor Transaction Interest Accrual Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/eAdvTxnAccrInq.doc">eAdvTxnAccrInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class eAdvTxnAccrInqRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
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
   private String _CompanyID = "";
            
            
            
            
            
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
    * From Date member variable.
    */
   private Date _FromDate = null;
            
   /**
    * To Date member variable.
    */
   private Date _ToDate = null;
            
   /**
    * Include Unsettled Trade member variable.
    */
   private Boolean _InclUnsettled = new Boolean(false);
            
   /**
    * Exclude Cancelled Trades member variable.
    */
   private Boolean _ExcludeCancelled = new Boolean(false);
            
   /**
    * Exclude Reversed Trades member variable.
    */
   private Boolean _ExcludeReversals = new Boolean(false);
            
   /**
    * Reporting Currency member variable.
    */
   private String _ReportingCurrency = "";
            

   /**
    * Constructs the eAdvTxnAccrInqRequest object.
    * 
    */
   eAdvTxnAccrInqRequest()
   {
      super ( 319 );
   }

   /**
    * Constructs the eAdvTxnAccrInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   eAdvTxnAccrInqRequest( String hostEncoding )
   {
      super ( 319, hostEncoding );
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
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
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
    * Sets the Include Unsettled Trade field for the request.
    * 
    * @param value  Value that the Include Unsettled Trade will be set to.
    */
   public final void setInclUnsettled( Boolean value )
   {
      assertUnsent();
      _InclUnsettled = value;
   }
	
   /**
    * Sets the Exclude Cancelled Trades field for the request.
    * 
    * @param value  Value that the Exclude Cancelled Trades will be set to.
    */
   public final void setExcludeCancelled( Boolean value )
   {
      assertUnsent();
      _ExcludeCancelled = value;
   }
	
   /**
    * Sets the Exclude Reversed Trades field for the request.
    * 
    * @param value  Value that the Exclude Reversed Trades will be set to.
    */
   public final void setExcludeReversals( Boolean value )
   {
      assertUnsent();
      _ExcludeReversals = value;
   }
	
   /**
    * Sets the Reporting Currency field for the request.
    * 
    * @param value  Value that the Reporting Currency will be set to.
    */
   public final void setReportingCurrency( String value )
   {
      assertUnsent();
      _ReportingCurrency = value;
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
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _FromDate );
      requestBuffer.appendField( _ToDate );
      requestBuffer.appendField( _InclUnsettled );
      requestBuffer.appendField( _ExcludeCancelled );
      requestBuffer.appendField( _ExcludeReversals );
      requestBuffer.appendField( _ReportingCurrency );
   }

}

