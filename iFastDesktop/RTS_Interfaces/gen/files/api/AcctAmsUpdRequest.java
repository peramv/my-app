// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Acount AMS Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctAmsUpd.doc">AcctAmsUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctAmsUpdRequest extends IFastRequest implements Serializable
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
    * AMS Type member array.
    */
   private String[] _AMSType = new String[25];
            
   /**
    * AMS Code member array.
    */
   private String[] _AMSCode = new String[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Next Process Date member array.
    */
   private Date[] _NextProcDate = new Date[25];
            
   /**
    * Frequency Override member array.
    */
   private Integer[] _FreqOverride = new Integer[25];
            
   /**
    * Sched SetUp Freq Id member array.
    */
   private Integer[] _SchedSetupFreqID = new Integer[25];
            
   /**
    * AMS Status member array.
    */
   private Integer[] _AMSStat = new Integer[25];
            
   /**
    * Threshold Percentage member array.
    */
   private String[] _ThresholdPrcnt = new String[25];
            
   /**
    * Rebalance member array.
    */
   private Boolean[] _Rebalance = new Boolean[25];
            
   /**
    * Update PACSWP member array.
    */
   private Boolean[] _UpdatePACSWP = new Boolean[25];
            
   /**
    * AcctAMSRID member array.
    */
   private Integer[] _AcctAMSRID = new Integer[25];
            
   /**
    * Currency member array.
    */
   private String[] _Currency = new String[25];
            

   /**
    * Constructs the AcctAmsUpdRequest object.
    * 
    */
   AcctAmsUpdRequest()
   {
      super ( 381 );
   }

   /**
    * Constructs the AcctAmsUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctAmsUpdRequest( String hostEncoding )
   {
      super ( 381, hostEncoding );
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
    * Sets the AMS Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AMS Type will be set to.
    */
   public final void setAMSType( int index, String value )
   {
      assertUnsent();
      _AMSType[index] = value;
   }
	
   /**
    * Sets the AMS Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AMS Code will be set to.
    */
   public final void setAMSCode( int index, String value )
   {
      assertUnsent();
      _AMSCode[index] = value;
   }
	
   /**
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _EffectiveDate[index] = value;
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
    * Sets the Next Process Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Next Process Date will be set to.
    */
   public final void setNextProcDate( int index, Date value )
   {
      assertUnsent();
      _NextProcDate[index] = value;
   }
	
   /**
    * Sets the Frequency Override field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Frequency Override will be set to.
    */
   public final void setFreqOverride( int index, Integer value )
   {
      assertUnsent();
      _FreqOverride[index] = value;
   }
	
   /**
    * Sets the Sched SetUp Freq Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Sched SetUp Freq Id will be set to.
    */
   public final void setSchedSetupFreqID( int index, Integer value )
   {
      assertUnsent();
      _SchedSetupFreqID[index] = value;
   }
	
   /**
    * Sets the AMS Status field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AMS Status will be set to.
    */
   public final void setAMSStat( int index, Integer value )
   {
      assertUnsent();
      _AMSStat[index] = value;
   }
	
   /**
    * Sets the Threshold Percentage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Threshold Percentage will be set to.
    */
   public final void setThresholdPrcnt( int index, String value )
   {
      assertUnsent();
      _ThresholdPrcnt[index] = value;
   }
	
   /**
    * Sets the Rebalance field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Rebalance will be set to.
    */
   public final void setRebalance( int index, Boolean value )
   {
      assertUnsent();
      _Rebalance[index] = value;
   }
	
   /**
    * Sets the Update PACSWP field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Update PACSWP will be set to.
    */
   public final void setUpdatePACSWP( int index, Boolean value )
   {
      assertUnsent();
      _UpdatePACSWP[index] = value;
   }
	
   /**
    * Sets the AcctAMSRID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AcctAMSRID will be set to.
    */
   public final void setAcctAMSRID( int index, Integer value )
   {
      assertUnsent();
      _AcctAMSRID[index] = value;
   }
	
   /**
    * Sets the Currency field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Currency will be set to.
    */
   public final void setCurrency( int index, String value )
   {
      assertUnsent();
      _Currency[index] = value;
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
         requestBuffer.appendField( _AMSType[x] );
         requestBuffer.appendField( _AMSCode[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _NextProcDate[x] );
         requestBuffer.appendField( _FreqOverride[x] );
         requestBuffer.appendField( _SchedSetupFreqID[x] );
         requestBuffer.appendField( _AMSStat[x] );
         requestBuffer.appendField( _ThresholdPrcnt[x] );
         requestBuffer.appendField( _Rebalance[x] );
         requestBuffer.appendField( _UpdatePACSWP[x] );
         requestBuffer.appendField( _AcctAMSRID[x] );
         requestBuffer.appendField( _Currency[x] );
      }
   }

}

