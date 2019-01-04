// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Advisor Pending Trades Listing request.
 * For additional view information see <A HREF="../../../../viewspecs/AdvPendTrades.doc">AdvPendTrades.doc</A>.
 * 
 * @author RTS Generated
 */
public class AdvPendTradesRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionID = "";
            
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
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales Rep Code member variable.
    */
   private String _SalesRepCode = "";
            
   /**
    * Request FundGroup member variable.
    */
   private String _ReqFundGroup = "";
            
   /**
    * Request Fund member variable.
    */
   private String _ReqFund = "";
            
   /**
    * Request Class member variable.
    */
   private String _ReqClass = "";
            
   /**
    * From Date - LastNR from v94 member variable.
    */
   private Date _FromDate = null;
            
   /**
    * To Date - NextNR from v94 member variable.
    */
   private Date _ToDate = null;
            

   /**
    * Constructs the AdvPendTradesRequest object.
    * 
    */
   AdvPendTradesRequest()
   {
      super ( 342 );
   }

   /**
    * Constructs the AdvPendTradesRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AdvPendTradesRequest( String hostEncoding )
   {
      super ( 342, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
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
    * Sets the Broker Code field for the request.
    * 
    * @param value  Value that the Broker Code will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Branch Code field for the request.
    * 
    * @param value  Value that the Branch Code will be set to.
    */
   public final void setBranchCode( String value )
   {
      assertUnsent();
      _BranchCode = value;
   }
	
   /**
    * Sets the Sales Rep Code field for the request.
    * 
    * @param value  Value that the Sales Rep Code will be set to.
    */
   public final void setSalesRepCode( String value )
   {
      assertUnsent();
      _SalesRepCode = value;
   }
	
   /**
    * Sets the Request FundGroup field for the request.
    * 
    * @param value  Value that the Request FundGroup will be set to.
    */
   public final void setReqFundGroup( String value )
   {
      assertUnsent();
      _ReqFundGroup = value;
   }
	
   /**
    * Sets the Request Fund field for the request.
    * 
    * @param value  Value that the Request Fund will be set to.
    */
   public final void setReqFund( String value )
   {
      assertUnsent();
      _ReqFund = value;
   }
	
   /**
    * Sets the Request Class field for the request.
    * 
    * @param value  Value that the Request Class will be set to.
    */
   public final void setReqClass( String value )
   {
      assertUnsent();
      _ReqClass = value;
   }
	
   /**
    * Sets the From Date - LastNR from v94 field for the request.
    * 
    * @param value  Value that the From Date - LastNR from v94 will be set to.
    */
   public final void setFromDate( Date value )
   {
      assertUnsent();
      _FromDate = value;
   }
	
   /**
    * Sets the To Date - NextNR from v94 field for the request.
    * 
    * @param value  Value that the To Date - NextNR from v94 will be set to.
    */
   public final void setToDate( Date value )
   {
      assertUnsent();
      _ToDate = value;
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
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SalesRepCode );
      requestBuffer.appendField( _ReqFundGroup );
      requestBuffer.appendField( _ReqFund );
      requestBuffer.appendField( _ReqClass );
      requestBuffer.appendField( _FromDate );
      requestBuffer.appendField( _ToDate );
   }

}

