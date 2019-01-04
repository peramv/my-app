// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Aggregated  Orders Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/AggrOrdInq.doc">AggrOrdInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AggrOrdInqRequest extends IFastRequest implements Serializable
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
    * Order Status member variable.
    */
   private String _OrdStatus = "";
            
   /**
    * Fund Broker member variable.
    */
   private String _FundBroker = "";
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Aggregation Reference Number member variable.
    */
   private String _OmnibusId = "";
            
   /**
    * Routing Reference Number member variable.
    */
   private String _RoutRefNum = "";
            
   /**
    * From Date member variable.
    */
   private Date _FromDate = null;
            
   /**
    * To Date member variable.
    */
   private Date _ToDate = null;
            
   /**
    * SearchType member variable.
    */
   private String _SearchType = "";
            
   /**
    * Fund Broker KV Number member variable.
    */
   private String _FndBrkKvNum = "";
            
   /**
    * Fund ID Type member variable.
    */
   private String _FundIdType = "";
            
   /**
    * Fund ID Value member variable.
    */
   private String _FundIDValue = "";
            
   /**
    * Amount Type member variable.
    */
   private String _rxAmountType = "";
            
   /**
    * Amount member variable.
    */
   private String _rxAmount = "0";
            
   /**
    * Transaction Type member variable.
    */
   private String _rxTransType = "";
            

   /**
    * Constructs the AggrOrdInqRequest object.
    * 
    */
   AggrOrdInqRequest()
   {
      super ( 323 );
   }

   /**
    * Constructs the AggrOrdInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AggrOrdInqRequest( String hostEncoding )
   {
      super ( 323, hostEncoding );
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
    * Sets the Order Status field for the request.
    * 
    * @param value  Value that the Order Status will be set to.
    */
   public final void setOrdStatus( String value )
   {
      assertUnsent();
      _OrdStatus = value;
   }
	
   /**
    * Sets the Fund Broker field for the request.
    * 
    * @param value  Value that the Fund Broker will be set to.
    */
   public final void setFundBroker( String value )
   {
      assertUnsent();
      _FundBroker = value;
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
    * Sets the Aggregation Reference Number field for the request.
    * 
    * @param value  Value that the Aggregation Reference Number will be set to.
    */
   public final void setOmnibusId( String value )
   {
      assertUnsent();
      _OmnibusId = value;
   }
	
   /**
    * Sets the Routing Reference Number field for the request.
    * 
    * @param value  Value that the Routing Reference Number will be set to.
    */
   public final void setRoutRefNum( String value )
   {
      assertUnsent();
      _RoutRefNum = value;
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
    * Sets the SearchType field for the request.
    * 
    * @param value  Value that the SearchType will be set to.
    */
   public final void setSearchType( String value )
   {
      assertUnsent();
      _SearchType = value;
   }
	
   /**
    * Sets the Fund Broker KV Number field for the request.
    * 
    * @param value  Value that the Fund Broker KV Number will be set to.
    */
   public final void setFndBrkKvNum( String value )
   {
      assertUnsent();
      _FndBrkKvNum = value;
   }
	
   /**
    * Sets the Fund ID Type field for the request.
    * 
    * @param value  Value that the Fund ID Type will be set to.
    */
   public final void setFundIdType( String value )
   {
      assertUnsent();
      _FundIdType = value;
   }
	
   /**
    * Sets the Fund ID Value field for the request.
    * 
    * @param value  Value that the Fund ID Value will be set to.
    */
   public final void setFundIDValue( String value )
   {
      assertUnsent();
      _FundIDValue = value;
   }
	
   /**
    * Sets the Amount Type field for the request.
    * 
    * @param value  Value that the Amount Type will be set to.
    */
   public final void setrxAmountType( String value )
   {
      assertUnsent();
      _rxAmountType = value;
   }
	
   /**
    * Sets the Amount field for the request.
    * 
    * @param value  Value that the Amount will be set to.
    */
   public final void setrxAmount( String value )
   {
      assertUnsent();
      _rxAmount = value;
   }
	
   /**
    * Sets the Transaction Type field for the request.
    * 
    * @param value  Value that the Transaction Type will be set to.
    */
   public final void setrxTransType( String value )
   {
      assertUnsent();
      _rxTransType = value;
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
      requestBuffer.appendField( _OrdStatus );
      requestBuffer.appendField( _FundBroker );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _OmnibusId );
      requestBuffer.appendField( _RoutRefNum );
      requestBuffer.appendField( _FromDate );
      requestBuffer.appendField( _ToDate );
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _FndBrkKvNum );
      requestBuffer.appendField( _FundIdType );
      requestBuffer.appendField( _FundIDValue );
      requestBuffer.appendField( _rxAmountType );
      requestBuffer.appendField( _rxAmount );
      requestBuffer.appendField( _rxTransType );
   }

}

