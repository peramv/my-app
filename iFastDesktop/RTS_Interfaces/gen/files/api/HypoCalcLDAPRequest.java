// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Hypothetical Redemption (LDAP Clients) request.
 * For additional view information see <A HREF="../../../../viewspecs/HypoCalcLDAP.doc">HypoCalcLDAP.doc</A>.
 * 
 * @author RTS Generated
 */
public class HypoCalcLDAPRequest extends IFastRequest implements Serializable
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
    * Account number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Trade Date member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Gross or Net member variable.
    */
   private Boolean _GrossOrNet = new Boolean(false);
            
   /**
    * Dollars or Units member variable.
    */
   private String _AmountType = "";
            
   /**
    * Full Redemption member variable.
    */
   private Boolean _FullRedem = new Boolean(false);
            
   /**
    * Redemption Code member variable.
    */
   private String _RedCode = "";
            
   /**
    * DSC free rule is at acct level or fund level? member variable.
    */
   private Boolean _AcctLvlDSCFee = new Boolean(false);
            
            
   /**
    * Record count member variable.
    */
   private int _ReqRepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = new String[100];
            
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = new String[100];
            
   /**
    * Redemption Amount/ Units member array.
    */
   private String[] _Amount = new String[100];
            

   /**
    * Constructs the HypoCalcLDAPRequest object.
    * 
    */
   HypoCalcLDAPRequest()
   {
      super ( 398 );
   }

   /**
    * Constructs the HypoCalcLDAPRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   HypoCalcLDAPRequest( String hostEncoding )
   {
      super ( 398, hostEncoding );
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
    * Sets the Account number field for the request.
    * 
    * @param value  Value that the Account number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Trade Date field for the request.
    * 
    * @param value  Value that the Trade Date will be set to.
    */
   public final void setTradeDate( Date value )
   {
      assertUnsent();
      _TradeDate = value;
   }
	
   /**
    * Sets the Gross or Net field for the request.
    * 
    * @param value  Value that the Gross or Net will be set to.
    */
   public final void setGrossOrNet( Boolean value )
   {
      assertUnsent();
      _GrossOrNet = value;
   }
	
   /**
    * Sets the Dollars or Units field for the request.
    * 
    * @param value  Value that the Dollars or Units will be set to.
    */
   public final void setAmountType( String value )
   {
      assertUnsent();
      _AmountType = value;
   }
	
   /**
    * Sets the Full Redemption field for the request.
    * 
    * @param value  Value that the Full Redemption will be set to.
    */
   public final void setFullRedem( Boolean value )
   {
      assertUnsent();
      _FullRedem = value;
   }
	
   /**
    * Sets the Redemption Code field for the request.
    * 
    * @param value  Value that the Redemption Code will be set to.
    */
   public final void setRedCode( String value )
   {
      assertUnsent();
      _RedCode = value;
   }
	
   /**
    * Sets the DSC free rule is at acct level or fund level? field for the request.
    * 
    * @param value  Value that the DSC free rule is at acct level or fund level? will be set to.
    */
   public final void setAcctLvlDSCFee( Boolean value )
   {
      assertUnsent();
      _AcctLvlDSCFee = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setReqRepeatCount( int value )
   {
      _ReqRepeatCount = value;
   }
         
   /**
    * Sets the Fund Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setFundCode( int index, String value )
   {
      assertUnsent();
      _FundCode[index] = value;
   }
	
   /**
    * Sets the Class Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Class Code will be set to.
    */
   public final void setClassCode( int index, String value )
   {
      assertUnsent();
      _ClassCode[index] = value;
   }
	
   /**
    * Sets the Redemption Amount/ Units field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Redemption Amount/ Units will be set to.
    */
   public final void setAmount( int index, String value )
   {
      assertUnsent();
      _Amount[index] = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _GrossOrNet );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _FullRedem );
      requestBuffer.appendField( _RedCode );
      requestBuffer.appendField( _AcctLvlDSCFee );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( new Integer(_ReqRepeatCount) );  // add record count
      for ( int x = 0; x < _ReqRepeatCount; x++ )
      {
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _ClassCode[x] );
         requestBuffer.appendField( _Amount[x] );
      }
   }

}

