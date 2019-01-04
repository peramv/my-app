// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Trade History Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/TrdHisMaintReq.doc">TrdHisMaintReq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TrdHisMaintReqRequest extends IFastRequest implements Serializable
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
    * Record Type member variable.
    */
   private String _RecordType = "";
            
   /**
    * Transaction Number member variable.
    */
   private Integer _TransNum = null;
            
   /**
    * Transaction Id member variable.
    */
   private String _TransId = "0";
            
   /**
    * Authorization member variable.
    */
   private String _Authorized = "";
            
   /**
    * Batch Name member variable.
    */
   private String _BatchName = "";
            
   /**
    * Payment Info member variable.
    */
   private String _PaymentInfo = "";
            
   /**
    * TradeRestrict member variable.
    */
   private String _TradeRestrict = "";
            
   /**
    * TradeRestrictRes member variable.
    */
   private String _TradeRestrictRes = "";
            
   /**
    * SrcOfFndsChk member variable.
    */
   private String _SrcOfFndsChk = "";
            
   /**
    * ScreenDesc member variable.
    */
   private String _ScreenDesc = "";
            

   /**
    * Constructs the TrdHisMaintReqRequest object.
    * 
    */
   TrdHisMaintReqRequest()
   {
      super ( 393 );
   }

   /**
    * Constructs the TrdHisMaintReqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   TrdHisMaintReqRequest( String hostEncoding )
   {
      super ( 393, hostEncoding );
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
    * Sets the Record Type field for the request.
    * 
    * @param value  Value that the Record Type will be set to.
    */
   public final void setRecordType( String value )
   {
      assertUnsent();
      _RecordType = value;
   }
	
   /**
    * Sets the Transaction Number field for the request.
    * 
    * @param value  Value that the Transaction Number will be set to.
    */
   public final void setTransNum( Integer value )
   {
      assertUnsent();
      _TransNum = value;
   }
	
   /**
    * Sets the Transaction Id field for the request.
    * 
    * @param value  Value that the Transaction Id will be set to.
    */
   public final void setTransId( String value )
   {
      assertUnsent();
      _TransId = value;
   }
	
   /**
    * Sets the Authorization field for the request.
    * 
    * @param value  Value that the Authorization will be set to.
    */
   public final void setAuthorized( String value )
   {
      assertUnsent();
      _Authorized = value;
   }
	
   /**
    * Sets the Batch Name field for the request.
    * 
    * @param value  Value that the Batch Name will be set to.
    */
   public final void setBatchName( String value )
   {
      assertUnsent();
      _BatchName = value;
   }
	
   /**
    * Sets the Payment Info field for the request.
    * 
    * @param value  Value that the Payment Info will be set to.
    */
   public final void setPaymentInfo( String value )
   {
      assertUnsent();
      _PaymentInfo = value;
   }
	
   /**
    * Sets the TradeRestrict field for the request.
    * 
    * @param value  Value that the TradeRestrict will be set to.
    */
   public final void setTradeRestrict( String value )
   {
      assertUnsent();
      _TradeRestrict = value;
   }
	
   /**
    * Sets the TradeRestrictRes field for the request.
    * 
    * @param value  Value that the TradeRestrictRes will be set to.
    */
   public final void setTradeRestrictRes( String value )
   {
      assertUnsent();
      _TradeRestrictRes = value;
   }
	
   /**
    * Sets the SrcOfFndsChk field for the request.
    * 
    * @param value  Value that the SrcOfFndsChk will be set to.
    */
   public final void setSrcOfFndsChk( String value )
   {
      assertUnsent();
      _SrcOfFndsChk = value;
   }
	
   /**
    * Sets the ScreenDesc field for the request.
    * 
    * @param value  Value that the ScreenDesc will be set to.
    */
   public final void setScreenDesc( String value )
   {
      assertUnsent();
      _ScreenDesc = value;
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
      requestBuffer.appendField( _RecordType );
      requestBuffer.appendField( _TransNum );
      requestBuffer.appendField( _TransId );
      requestBuffer.appendField( _Authorized );
      requestBuffer.appendField( _BatchName );
      requestBuffer.appendField( _PaymentInfo );
      requestBuffer.appendField( _TradeRestrict );
      requestBuffer.appendField( _TradeRestrictRes );
      requestBuffer.appendField( _SrcOfFndsChk );
      requestBuffer.appendField( _ScreenDesc );
   }

}

