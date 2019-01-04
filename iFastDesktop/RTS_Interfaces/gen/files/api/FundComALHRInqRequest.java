// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * FUNDcom Acct Lev Hypo Redem Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/FundComALHRInq.doc">FundComALHRInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundComALHRInqRequest extends IFastRequest implements Serializable
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
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * AccountNum member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * RedeemAll member variable.
    */
   private Boolean _FullRedem = new Boolean(false);
            
   /**
    * RedeemAllType member variable.
    */
   private String _FullRedemType = "";
            
            
   /**
    * Record count member variable.
    */
   private int _ReqRepeatCount = 0;
   
   /**
    * FundID member array.
    */
   private String[] _Baycom = new String[25];
            
   /**
    * AmountType member array.
    */
   private String[] _AmountType = new String[25];
            
   /**
    * Amount member array.
    */
   private String[] _Amount = new String[25];
            
   /**
    * GrossNetRedemption member array.
    */
   private Boolean[] _GrossOrNet = new Boolean[25];
            

   /**
    * Constructs the FundComALHRInqRequest object.
    * 
    */
   FundComALHRInqRequest()
   {
      super ( 399 );
   }

   /**
    * Constructs the FundComALHRInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FundComALHRInqRequest( String hostEncoding )
   {
      super ( 399, hostEncoding );
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
    * Sets the RedeemAll field for the request.
    * 
    * @param value  Value that the RedeemAll will be set to.
    */
   public final void setFullRedem( Boolean value )
   {
      assertUnsent();
      _FullRedem = value;
   }
	
   /**
    * Sets the RedeemAllType field for the request.
    * 
    * @param value  Value that the RedeemAllType will be set to.
    */
   public final void setFullRedemType( String value )
   {
      assertUnsent();
      _FullRedemType = value;
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
    * Sets the FundID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the FundID will be set to.
    */
   public final void setBaycom( int index, String value )
   {
      assertUnsent();
      _Baycom[index] = value;
   }
	
   /**
    * Sets the AmountType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AmountType will be set to.
    */
   public final void setAmountType( int index, String value )
   {
      assertUnsent();
      _AmountType[index] = value;
   }
	
   /**
    * Sets the Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Amount will be set to.
    */
   public final void setAmount( int index, String value )
   {
      assertUnsent();
      _Amount[index] = value;
   }
	
   /**
    * Sets the GrossNetRedemption field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the GrossNetRedemption will be set to.
    */
   public final void setGrossOrNet( int index, Boolean value )
   {
      assertUnsent();
      _GrossOrNet[index] = value;
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
      requestBuffer.appendField( _FullRedem );
      requestBuffer.appendField( _FullRedemType );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( new Integer(_ReqRepeatCount) );  // add record count
      for ( int x = 0; x < _ReqRepeatCount; x++ )
      {
         requestBuffer.appendField( _Baycom[x] );
         requestBuffer.appendField( _AmountType[x] );
         requestBuffer.appendField( _Amount[x] );
         requestBuffer.appendField( _GrossOrNet[x] );
      }
   }

}

