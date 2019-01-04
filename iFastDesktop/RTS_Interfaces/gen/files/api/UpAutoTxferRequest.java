// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Auto Transfer Details/Alloc Maint (discontinued) request.
 * For additional view information see <A HREF="../../../../viewspecs/UpAutoTxfer.doc">UpAutoTxfer.doc</A>.
 * 
 * @author RTS Generated
 */
public class UpAutoTxferRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
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
   private String _CompanyID = "";
            
   /**
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * Transfer From Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Automatic Transfer Record ID member variable.
    */
   private Integer _AutoTrfId = null;
            
   /**
    * Transfer From Fund member variable.
    */
   private String _FundCode = "";
            
   /**
    * Transfer From Class member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Transfer To Account member variable.
    */
   private String _AccountTo = "0";
            
   /**
    * Transfer To Fund member variable.
    */
   private String _FundToCode = "";
            
   /**
    * Transfer To Class member variable.
    */
   private String _ClassToCode = "";
            
   /**
    * Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * Amount Type Code member variable.
    */
   private String _AmountType = "";
            
   /**
    * Flat Fee Amount member variable.
    */
   private String _Fee = "0";
            
   /**
    * Percent Fee member variable.
    */
   private String _FeePercent = "0";
            
   /**
    * Back End Load Fee Applicable member variable.
    */
   private Boolean _BELFee = new Boolean(false);
            
   /**
    * Frequency Code member variable.
    */
   private String _Frequency = "";
            
   /**
    * Day in the week transfer occurs on member variable.
    */
   private Integer _DayOfWeek = null;
            
   /**
    * Transfer occurs at end of month member variable.
    */
   private Boolean _EndOfMonth = new Boolean(false);
            
   /**
    * January member variable.
    */
   private Boolean _January = new Boolean(false);
            
   /**
    * February member variable.
    */
   private Boolean _February = new Boolean(false);
            
   /**
    * March member variable.
    */
   private Boolean _March = new Boolean(false);
            
   /**
    * April member variable.
    */
   private Boolean _April = new Boolean(false);
            
   /**
    * May member variable.
    */
   private Boolean _May = new Boolean(false);
            
   /**
    * June member variable.
    */
   private Boolean _June = new Boolean(false);
            
   /**
    * July member variable.
    */
   private Boolean _July = new Boolean(false);
            
   /**
    * August member variable.
    */
   private Boolean _August = new Boolean(false);
            
   /**
    * September member variable.
    */
   private Boolean _September = new Boolean(false);
            
   /**
    * October member variable.
    */
   private Boolean _October = new Boolean(false);
            
   /**
    * November member variable.
    */
   private Boolean _November = new Boolean(false);
            
   /**
    * December member variable.
    */
   private Boolean _December = new Boolean(false);
            
   /**
    * Last Process Date member variable.
    */
   private Date _LastProcDate = null;
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Status Code member variable.
    */
   private Boolean _StatusCode = new Boolean(false);
            
   /**
    * Set As Default member variable.
    */
   private Boolean _SetAsDefault = new Boolean(false);
            
   /**
    * Version of Transfer information member variable.
    */
   private Integer _VersionNum = null;
            
            
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Allocation Run Mode member array.
    */
   private String[] _AllocModeAlloc = new String[25];
            
   /**
    * Allocation Level member array.
    */
   private Integer[] _Level = new Integer[25];
            
   /**
    * Allocation Transfer To Account Num member array.
    */
   private String[] _AllocAccountNum = new String[25];
            
   /**
    * Allocation Transfer to Fund Code member array.
    */
   private String[] _AllocFundToCode = new String[25];
            
   /**
    * Allocation Transfer to Class Code member array.
    */
   private String[] _AllocClassToCode = new String[25];
            
   /**
    * Allocation Percentage member array.
    */
   private String[] _AllocPercentage = new String[25];
            
   /**
    * Allocation Amount member array.
    */
   private String[] _AllocAmount = new String[25];
            
   /**
    * Distrib-Detl Recid member array.
    */
   private Integer[] _DistribDetlRid = new Integer[25];
            

   /**
    * Constructs the UpAutoTxferRequest object.
    * 
    */
   UpAutoTxferRequest()
   {
      super ( 95 );
   }

   /**
    * Constructs the UpAutoTxferRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   UpAutoTxferRequest( String hostEncoding )
   {
      super ( 95, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
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
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Run Mode field for the request.
    * 
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
   }
	
   /**
    * Sets the Transfer From Account Number field for the request.
    * 
    * @param value  Value that the Transfer From Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Automatic Transfer Record ID field for the request.
    * 
    * @param value  Value that the Automatic Transfer Record ID will be set to.
    */
   public final void setAutoTrfId( Integer value )
   {
      assertUnsent();
      _AutoTrfId = value;
   }
	
   /**
    * Sets the Transfer From Fund field for the request.
    * 
    * @param value  Value that the Transfer From Fund will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Transfer From Class field for the request.
    * 
    * @param value  Value that the Transfer From Class will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the Transfer To Account field for the request.
    * 
    * @param value  Value that the Transfer To Account will be set to.
    */
   public final void setAccountTo( String value )
   {
      assertUnsent();
      _AccountTo = value;
   }
	
   /**
    * Sets the Transfer To Fund field for the request.
    * 
    * @param value  Value that the Transfer To Fund will be set to.
    */
   public final void setFundToCode( String value )
   {
      assertUnsent();
      _FundToCode = value;
   }
	
   /**
    * Sets the Transfer To Class field for the request.
    * 
    * @param value  Value that the Transfer To Class will be set to.
    */
   public final void setClassToCode( String value )
   {
      assertUnsent();
      _ClassToCode = value;
   }
	
   /**
    * Sets the Amount field for the request.
    * 
    * @param value  Value that the Amount will be set to.
    */
   public final void setAmount( String value )
   {
      assertUnsent();
      _Amount = value;
   }
	
   /**
    * Sets the Amount Type Code field for the request.
    * 
    * @param value  Value that the Amount Type Code will be set to.
    */
   public final void setAmountType( String value )
   {
      assertUnsent();
      _AmountType = value;
   }
	
   /**
    * Sets the Flat Fee Amount field for the request.
    * 
    * @param value  Value that the Flat Fee Amount will be set to.
    */
   public final void setFee( String value )
   {
      assertUnsent();
      _Fee = value;
   }
	
   /**
    * Sets the Percent Fee field for the request.
    * 
    * @param value  Value that the Percent Fee will be set to.
    */
   public final void setFeePercent( String value )
   {
      assertUnsent();
      _FeePercent = value;
   }
	
   /**
    * Sets the Back End Load Fee Applicable field for the request.
    * 
    * @param value  Value that the Back End Load Fee Applicable will be set to.
    */
   public final void setBELFee( Boolean value )
   {
      assertUnsent();
      _BELFee = value;
   }
	
   /**
    * Sets the Frequency Code field for the request.
    * 
    * @param value  Value that the Frequency Code will be set to.
    */
   public final void setFrequency( String value )
   {
      assertUnsent();
      _Frequency = value;
   }
	
   /**
    * Sets the Day in the week transfer occurs on field for the request.
    * 
    * @param value  Value that the Day in the week transfer occurs on will be set to.
    */
   public final void setDayOfWeek( Integer value )
   {
      assertUnsent();
      _DayOfWeek = value;
   }
	
   /**
    * Sets the Transfer occurs at end of month field for the request.
    * 
    * @param value  Value that the Transfer occurs at end of month will be set to.
    */
   public final void setEndOfMonth( Boolean value )
   {
      assertUnsent();
      _EndOfMonth = value;
   }
	
   /**
    * Sets the January field for the request.
    * 
    * @param value  Value that the January will be set to.
    */
   public final void setJanuary( Boolean value )
   {
      assertUnsent();
      _January = value;
   }
	
   /**
    * Sets the February field for the request.
    * 
    * @param value  Value that the February will be set to.
    */
   public final void setFebruary( Boolean value )
   {
      assertUnsent();
      _February = value;
   }
	
   /**
    * Sets the March field for the request.
    * 
    * @param value  Value that the March will be set to.
    */
   public final void setMarch( Boolean value )
   {
      assertUnsent();
      _March = value;
   }
	
   /**
    * Sets the April field for the request.
    * 
    * @param value  Value that the April will be set to.
    */
   public final void setApril( Boolean value )
   {
      assertUnsent();
      _April = value;
   }
	
   /**
    * Sets the May field for the request.
    * 
    * @param value  Value that the May will be set to.
    */
   public final void setMay( Boolean value )
   {
      assertUnsent();
      _May = value;
   }
	
   /**
    * Sets the June field for the request.
    * 
    * @param value  Value that the June will be set to.
    */
   public final void setJune( Boolean value )
   {
      assertUnsent();
      _June = value;
   }
	
   /**
    * Sets the July field for the request.
    * 
    * @param value  Value that the July will be set to.
    */
   public final void setJuly( Boolean value )
   {
      assertUnsent();
      _July = value;
   }
	
   /**
    * Sets the August field for the request.
    * 
    * @param value  Value that the August will be set to.
    */
   public final void setAugust( Boolean value )
   {
      assertUnsent();
      _August = value;
   }
	
   /**
    * Sets the September field for the request.
    * 
    * @param value  Value that the September will be set to.
    */
   public final void setSeptember( Boolean value )
   {
      assertUnsent();
      _September = value;
   }
	
   /**
    * Sets the October field for the request.
    * 
    * @param value  Value that the October will be set to.
    */
   public final void setOctober( Boolean value )
   {
      assertUnsent();
      _October = value;
   }
	
   /**
    * Sets the November field for the request.
    * 
    * @param value  Value that the November will be set to.
    */
   public final void setNovember( Boolean value )
   {
      assertUnsent();
      _November = value;
   }
	
   /**
    * Sets the December field for the request.
    * 
    * @param value  Value that the December will be set to.
    */
   public final void setDecember( Boolean value )
   {
      assertUnsent();
      _December = value;
   }
	
   /**
    * Sets the Last Process Date field for the request.
    * 
    * @param value  Value that the Last Process Date will be set to.
    */
   public final void setLastProcDate( Date value )
   {
      assertUnsent();
      _LastProcDate = value;
   }
	
   /**
    * Sets the Effective Date field for the request.
    * 
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the Stop Date field for the request.
    * 
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( Date value )
   {
      assertUnsent();
      _StopDate = value;
   }
	
   /**
    * Sets the Status Code field for the request.
    * 
    * @param value  Value that the Status Code will be set to.
    */
   public final void setStatusCode( Boolean value )
   {
      assertUnsent();
      _StatusCode = value;
   }
	
   /**
    * Sets the Set As Default field for the request.
    * 
    * @param value  Value that the Set As Default will be set to.
    */
   public final void setSetAsDefault( Boolean value )
   {
      assertUnsent();
      _SetAsDefault = value;
   }
	
   /**
    * Sets the Version of Transfer information field for the request.
    * 
    * @param value  Value that the Version of Transfer information will be set to.
    */
   public final void setVersionNum( Integer value )
   {
      assertUnsent();
      _VersionNum = value;
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
    * Sets the Allocation Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Run Mode will be set to.
    */
   public final void setAllocModeAlloc( int index, String value )
   {
      assertUnsent();
      _AllocModeAlloc[index] = value;
   }
	
   /**
    * Sets the Allocation Level field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Level will be set to.
    */
   public final void setLevel( int index, Integer value )
   {
      assertUnsent();
      _Level[index] = value;
   }
	
   /**
    * Sets the Allocation Transfer To Account Num field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Transfer To Account Num will be set to.
    */
   public final void setAllocAccountNum( int index, String value )
   {
      assertUnsent();
      _AllocAccountNum[index] = value;
   }
	
   /**
    * Sets the Allocation Transfer to Fund Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Transfer to Fund Code will be set to.
    */
   public final void setAllocFundToCode( int index, String value )
   {
      assertUnsent();
      _AllocFundToCode[index] = value;
   }
	
   /**
    * Sets the Allocation Transfer to Class Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Transfer to Class Code will be set to.
    */
   public final void setAllocClassToCode( int index, String value )
   {
      assertUnsent();
      _AllocClassToCode[index] = value;
   }
	
   /**
    * Sets the Allocation Percentage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Percentage will be set to.
    */
   public final void setAllocPercentage( int index, String value )
   {
      assertUnsent();
      _AllocPercentage[index] = value;
   }
	
   /**
    * Sets the Allocation Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Amount will be set to.
    */
   public final void setAllocAmount( int index, String value )
   {
      assertUnsent();
      _AllocAmount[index] = value;
   }
	
   /**
    * Sets the Distrib-Detl Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distrib-Detl Recid will be set to.
    */
   public final void setDistribDetlRid( int index, Integer value )
   {
      assertUnsent();
      _DistribDetlRid[index] = value;
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
      requestBuffer.appendField( _CompanyID );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _AutoTrfId );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _AccountTo );
      requestBuffer.appendField( _FundToCode );
      requestBuffer.appendField( _ClassToCode );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _Fee );
      requestBuffer.appendField( _FeePercent );
      requestBuffer.appendField( _BELFee );
      requestBuffer.appendField( _Frequency );
      requestBuffer.appendField( _DayOfWeek );
      requestBuffer.appendField( _EndOfMonth );
      requestBuffer.appendField( _January );
      requestBuffer.appendField( _February );
      requestBuffer.appendField( _March );
      requestBuffer.appendField( _April );
      requestBuffer.appendField( _May );
      requestBuffer.appendField( _June );
      requestBuffer.appendField( _July );
      requestBuffer.appendField( _August );
      requestBuffer.appendField( _September );
      requestBuffer.appendField( _October );
      requestBuffer.appendField( _November );
      requestBuffer.appendField( _December );
      requestBuffer.appendField( _LastProcDate );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _StatusCode );
      requestBuffer.appendField( _SetAsDefault );
      requestBuffer.appendField( _VersionNum );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _AllocModeAlloc[x] );
         requestBuffer.appendField( _Level[x] );
         requestBuffer.appendField( _AllocAccountNum[x] );
         requestBuffer.appendField( _AllocFundToCode[x] );
         requestBuffer.appendField( _AllocClassToCode[x] );
         requestBuffer.appendField( _AllocPercentage[x] );
         requestBuffer.appendField( _AllocAmount[x] );
         requestBuffer.appendField( _DistribDetlRid[x] );
      }
   }

}

