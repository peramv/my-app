// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Acount  Controls Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctCtrlUpd.doc">AcctCtrlUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctCtrlUpdRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Fund member array.
    */
   private String[] _FundCode = new String[25];
            
   /**
    * Class member array.
    */
   private String[] _ClassCode = new String[25];
            
   /**
    * Rule Type member array.
    */
   private String[] _RuleType = new String[25];
            
   /**
    * Start Date member array.
    */
   private Date[] _StartDate = new Date[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Override Amount member array.
    */
   private String[] _OverrideAmt = new String[25];
            
   /**
    * Override Logical member array.
    */
   private Boolean[] _OverrideLog = new Boolean[25];
            
   /**
    * Override Character member array.
    */
   private String[] _OverrideChar = new String[25];
            
   /**
    * AcctControlsID member array.
    */
   private Integer[] _AcctControlsID = new Integer[25];
            
   /**
    * AcctControls Version member array.
    */
   private Integer[] _AcctControlsVer = new Integer[25];
            
   /**
    * AcctControlsRID member array.
    */
   private Integer[] _AcctControlsRID = new Integer[25];
            

   /**
    * Constructs the AcctCtrlUpdRequest object.
    * 
    */
   AcctCtrlUpdRequest()
   {
      super ( 387 );
   }

   /**
    * Constructs the AcctCtrlUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctCtrlUpdRequest( String hostEncoding )
   {
      super ( 387, hostEncoding );
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
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Fund field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund will be set to.
    */
   public final void setFundCode( int index, String value )
   {
      assertUnsent();
      _FundCode[index] = value;
   }
	
   /**
    * Sets the Class field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Class will be set to.
    */
   public final void setClassCode( int index, String value )
   {
      assertUnsent();
      _ClassCode[index] = value;
   }
	
   /**
    * Sets the Rule Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Rule Type will be set to.
    */
   public final void setRuleType( int index, String value )
   {
      assertUnsent();
      _RuleType[index] = value;
   }
	
   /**
    * Sets the Start Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Start Date will be set to.
    */
   public final void setStartDate( int index, Date value )
   {
      assertUnsent();
      _StartDate[index] = value;
   }
	
   /**
    * Sets the Stop Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the Override Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Override Amount will be set to.
    */
   public final void setOverrideAmt( int index, String value )
   {
      assertUnsent();
      _OverrideAmt[index] = value;
   }
	
   /**
    * Sets the Override Logical field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Override Logical will be set to.
    */
   public final void setOverrideLog( int index, Boolean value )
   {
      assertUnsent();
      _OverrideLog[index] = value;
   }
	
   /**
    * Sets the Override Character field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Override Character will be set to.
    */
   public final void setOverrideChar( int index, String value )
   {
      assertUnsent();
      _OverrideChar[index] = value;
   }
	
   /**
    * Sets the AcctControlsID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AcctControlsID will be set to.
    */
   public final void setAcctControlsID( int index, Integer value )
   {
      assertUnsent();
      _AcctControlsID[index] = value;
   }
	
   /**
    * Sets the AcctControls Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AcctControls Version will be set to.
    */
   public final void setAcctControlsVer( int index, Integer value )
   {
      assertUnsent();
      _AcctControlsVer[index] = value;
   }
	
   /**
    * Sets the AcctControlsRID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AcctControlsRID will be set to.
    */
   public final void setAcctControlsRID( int index, Integer value )
   {
      assertUnsent();
      _AcctControlsRID[index] = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _ClassCode[x] );
         requestBuffer.appendField( _RuleType[x] );
         requestBuffer.appendField( _StartDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _OverrideAmt[x] );
         requestBuffer.appendField( _OverrideLog[x] );
         requestBuffer.appendField( _OverrideChar[x] );
         requestBuffer.appendField( _AcctControlsID[x] );
         requestBuffer.appendField( _AcctControlsVer[x] );
         requestBuffer.appendField( _AcctControlsRID[x] );
      }
   }

}

