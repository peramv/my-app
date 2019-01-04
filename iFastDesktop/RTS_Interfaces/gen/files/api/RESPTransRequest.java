// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * RESP Transaction Hist/Pend Inquriy request.
 * For additional view information see <A HREF="../../../../viewspecs/RESPTrans.doc">RESPTrans.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPTransRequest extends IFastRequest implements Serializable
{

            
   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
   /**
    * AccountNum member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * HistoryPending member variable.
    */
   private String _HistoryPending = "";
            
            
            
   /**
    * Request Transaction Id member variable.
    */
   private String _ReqTransId = "0";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * Deposit Type member variable.
    */
   private Integer _DepositType = null;
            
   /**
    * Redemption Code member variable.
    */
   private String _RESPRedCode = "";
            
   /**
    * Beneficiary Name member variable.
    */
   private String _RESPBeneName = "";
            
   /**
    * RESP Beneficiary ID member variable.
    */
   private String _RESPBenefID = "0";
            
   /**
    * From Date member variable.
    */
   private Date _FromDate = null;
            
   /**
    * To Date member variable.
    */
   private Date _ToDate = null;
            
   /**
    * Transfer Status member variable.
    */
   private String _TfrStat = "";
            
   /**
    * Reported to HRDC member variable.
    */
   private String _RepHRDC = "";
            

   /**
    * Constructs the RESPTransRequest object.
    * 
    */
   RESPTransRequest()
   {
      super ( 111 );
   }

   /**
    * Constructs the RESPTransRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   RESPTransRequest( String hostEncoding )
   {
      super ( 111, hostEncoding );
   }

   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the UserId field for the request.
    * 
    * @param value  Value that the UserId will be set to.
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
    * Sets the CompanyId field for the request.
    * 
    * @param value  Value that the CompanyId will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the AccountNum field for the request.
    * 
    * @param value  Value that the AccountNum will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the HistoryPending field for the request.
    * 
    * @param value  Value that the HistoryPending will be set to.
    */
   public final void setHistoryPending( String value )
   {
      assertUnsent();
      _HistoryPending = value;
   }
	
   /**
    * Sets the Request Transaction Id field for the request.
    * 
    * @param value  Value that the Request Transaction Id will be set to.
    */
   public final void setReqTransId( String value )
   {
      assertUnsent();
      _ReqTransId = value;
   }
	
   /**
    * Sets the Transaction Type field for the request.
    * 
    * @param value  Value that the Transaction Type will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the Deposit Type field for the request.
    * 
    * @param value  Value that the Deposit Type will be set to.
    */
   public final void setDepositType( Integer value )
   {
      assertUnsent();
      _DepositType = value;
   }
	
   /**
    * Sets the Redemption Code field for the request.
    * 
    * @param value  Value that the Redemption Code will be set to.
    */
   public final void setRESPRedCode( String value )
   {
      assertUnsent();
      _RESPRedCode = value;
   }
	
   /**
    * Sets the Beneficiary Name field for the request.
    * 
    * @param value  Value that the Beneficiary Name will be set to.
    */
   public final void setRESPBeneName( String value )
   {
      assertUnsent();
      _RESPBeneName = value;
   }
	
   /**
    * Sets the RESP Beneficiary ID field for the request.
    * 
    * @param value  Value that the RESP Beneficiary ID will be set to.
    */
   public final void setRESPBenefID( String value )
   {
      assertUnsent();
      _RESPBenefID = value;
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
    * Sets the Transfer Status field for the request.
    * 
    * @param value  Value that the Transfer Status will be set to.
    */
   public final void setTfrStat( String value )
   {
      assertUnsent();
      _TfrStat = value;
   }
	
   /**
    * Sets the Reported to HRDC field for the request.
    * 
    * @param value  Value that the Reported to HRDC will be set to.
    */
   public final void setRepHRDC( String value )
   {
      assertUnsent();
      _RepHRDC = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _HistoryPending );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _ReqTransId );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _DepositType );
      requestBuffer.appendField( _RESPRedCode );
      requestBuffer.appendField( _RESPBeneName );
      requestBuffer.appendField( _RESPBenefID );
      requestBuffer.appendField( _FromDate );
      requestBuffer.appendField( _ToDate );
      requestBuffer.appendField( _TfrStat );
      requestBuffer.appendField( _RepHRDC );
   }

}

