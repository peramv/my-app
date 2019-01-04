// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * SEG Redemption/Transfer transaction Validations request.
 * For additional view information see <A HREF="../../../../viewspecs/SEGRdmTrfVal.doc">SEGRdmTrfVal.doc</A>.
 * 
 * @author RTS Generated
 */
public class SEGRdmTrfValRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Fund member variable.
    */
   private String _Fund = "";
            
   /**
    * Class member variable.
    */
   private String _Class = "";
            
   /**
    * Account that is transferred to member variable.
    */
   private String _AccountTo = "0";
            
   /**
    * Transferred to Fund member variable.
    */
   private String _FundTo = "";
            
   /**
    * Transferred to Class member variable.
    */
   private String _ClassTo = "";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * Redemption Code member variable.
    */
   private String _RedCode = "";
            
   /**
    * Amount member variable.
    */
   private String _TradeAmount = "0";
            
   /**
    * Effective Date member variable.
    */
   private Date _Deff = null;
            
   /**
    * Settlement Date member variable.
    */
   private Date _SettleDate = null;
            
   /**
    * Unit or Dollar amount member variable.
    */
   private String _PUD = "";
            
   /**
    * Transaction Number member variable.
    */
   private Integer _TransNum = null;
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Fund To member array.
    */
   private String[] _AllocFund = new String[25];
            
   /**
    * Class To member array.
    */
   private String[] _AllocClass = new String[25];
            
   /**
    * Allocated Percentage member array.
    */
   private String[] _AllocPercentage = new String[25];
            
   /**
    * Allocated Amount member array.
    */
   private String[] _AllocAmount = new String[25];
            

   /**
    * Constructs the SEGRdmTrfValRequest object.
    * 
    */
   SEGRdmTrfValRequest()
   {
      super ( 414 );
   }

   /**
    * Constructs the SEGRdmTrfValRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SEGRdmTrfValRequest( String hostEncoding )
   {
      super ( 414, hostEncoding );
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
    * Sets the Account that is transferred to field for the request.
    * 
    * @param value  Value that the Account that is transferred to will be set to.
    */
   public final void setAccountTo( String value )
   {
      assertUnsent();
      _AccountTo = value;
   }
	
   /**
    * Sets the Transferred to Fund field for the request.
    * 
    * @param value  Value that the Transferred to Fund will be set to.
    */
   public final void setFundTo( String value )
   {
      assertUnsent();
      _FundTo = value;
   }
	
   /**
    * Sets the Transferred to Class field for the request.
    * 
    * @param value  Value that the Transferred to Class will be set to.
    */
   public final void setClassTo( String value )
   {
      assertUnsent();
      _ClassTo = value;
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
    * Sets the Amount field for the request.
    * 
    * @param value  Value that the Amount will be set to.
    */
   public final void setTradeAmount( String value )
   {
      assertUnsent();
      _TradeAmount = value;
   }
	
   /**
    * Sets the Effective Date field for the request.
    * 
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setDeff( Date value )
   {
      assertUnsent();
      _Deff = value;
   }
	
   /**
    * Sets the Settlement Date field for the request.
    * 
    * @param value  Value that the Settlement Date will be set to.
    */
   public final void setSettleDate( Date value )
   {
      assertUnsent();
      _SettleDate = value;
   }
	
   /**
    * Sets the Unit or Dollar amount field for the request.
    * 
    * @param value  Value that the Unit or Dollar amount will be set to.
    */
   public final void setPUD( String value )
   {
      assertUnsent();
      _PUD = value;
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
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Fund To field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund To will be set to.
    */
   public final void setAllocFund( int index, String value )
   {
      assertUnsent();
      _AllocFund[index] = value;
   }
	
   /**
    * Sets the Class To field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Class To will be set to.
    */
   public final void setAllocClass( int index, String value )
   {
      assertUnsent();
      _AllocClass[index] = value;
   }
	
   /**
    * Sets the Allocated Percentage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocated Percentage will be set to.
    */
   public final void setAllocPercentage( int index, String value )
   {
      assertUnsent();
      _AllocPercentage[index] = value;
   }
	
   /**
    * Sets the Allocated Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocated Amount will be set to.
    */
   public final void setAllocAmount( int index, String value )
   {
      assertUnsent();
      _AllocAmount[index] = value;
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
      requestBuffer.appendField( _Fund );
      requestBuffer.appendField( _Class );
      requestBuffer.appendField( _AccountTo );
      requestBuffer.appendField( _FundTo );
      requestBuffer.appendField( _ClassTo );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _RedCode );
      requestBuffer.appendField( _TradeAmount );
      requestBuffer.appendField( _Deff );
      requestBuffer.appendField( _SettleDate );
      requestBuffer.appendField( _PUD );
      requestBuffer.appendField( _TransNum );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _AllocFund[x] );
         requestBuffer.appendField( _AllocClass[x] );
         requestBuffer.appendField( _AllocPercentage[x] );
         requestBuffer.appendField( _AllocAmount[x] );
      }
   }

}

