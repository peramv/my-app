// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Security Recon - Account Level Update request.
 * For additional view information see <A HREF="../../../../viewspecs/SecAcctUpd.doc">SecAcctUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class SecAcctUpdRequest extends IFastRequest implements Serializable
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
    * Fund Broker Code member variable.
    */
   private String _FundBrokerCode = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Acct SettlLoc Version member array.
    */
   private Integer[] _AcctSettlLocVersion = new Integer[25];
            
   /**
    * Settlement Loc Code member array.
    */
   private String[] _SettlLocCode = new String[25];
            
   /**
    * Default Settlement Location member array.
    */
   private Boolean[] _DefaultSettlLoc = new Boolean[25];
            
   /**
    * AcctSettlLoc RecID member array.
    */
   private Integer[] _AcctSettlLocRID = new Integer[25];
            

   /**
    * Constructs the SecAcctUpdRequest object.
    * 
    */
   SecAcctUpdRequest()
   {
      super ( 274 );
   }

   /**
    * Constructs the SecAcctUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SecAcctUpdRequest( String hostEncoding )
   {
      super ( 274, hostEncoding );
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
    * Sets the Fund Broker Code field for the request.
    * 
    * @param value  Value that the Fund Broker Code will be set to.
    */
   public final void setFundBrokerCode( String value )
   {
      assertUnsent();
      _FundBrokerCode = value;
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
    * Sets the RunMode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RunMode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Acct SettlLoc Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Acct SettlLoc Version will be set to.
    */
   public final void setAcctSettlLocVersion( int index, Integer value )
   {
      assertUnsent();
      _AcctSettlLocVersion[index] = value;
   }
	
   /**
    * Sets the Settlement Loc Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Settlement Loc Code will be set to.
    */
   public final void setSettlLocCode( int index, String value )
   {
      assertUnsent();
      _SettlLocCode[index] = value;
   }
	
   /**
    * Sets the Default Settlement Location field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Default Settlement Location will be set to.
    */
   public final void setDefaultSettlLoc( int index, Boolean value )
   {
      assertUnsent();
      _DefaultSettlLoc[index] = value;
   }
	
   /**
    * Sets the AcctSettlLoc RecID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AcctSettlLoc RecID will be set to.
    */
   public final void setAcctSettlLocRID( int index, Integer value )
   {
      assertUnsent();
      _AcctSettlLocRID[index] = value;
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
      requestBuffer.appendField( _FundBrokerCode );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _AcctSettlLocVersion[x] );
         requestBuffer.appendField( _SettlLocCode[x] );
         requestBuffer.appendField( _DefaultSettlLoc[x] );
         requestBuffer.appendField( _AcctSettlLocRID[x] );
      }
   }

}

