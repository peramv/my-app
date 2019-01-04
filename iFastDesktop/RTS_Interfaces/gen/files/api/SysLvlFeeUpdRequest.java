// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * System Level Fee Parms/Scale Update request.
 * For additional view information see <A HREF="../../../../viewspecs/SysLvlFeeUpd.doc">SysLvlFeeUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class SysLvlFeeUpdRequest extends IFastRequest implements Serializable
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
    * Fee ID member variable.
    */
   private Integer _FeeID = null;
            
   /**
    * Fund member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class member variable.
    */
   private String _ClassCode = "";
            
   /**
    * From Fund member variable.
    */
   private String _FromFundCode = "";
            
   /**
    * From Class member variable.
    */
   private String _FromClassCode = "";
            
   /**
    * Fee Code/ Definition member variable.
    */
   private Integer _FeeCode = null;
            
   /**
    * Fee Type member variable.
    */
   private String _FeeType = "";
            
   /**
    * Rate member variable.
    */
   private String _Rate = "0";
            
   /**
    * Maximum Fee member variable.
    */
   private String _MaxFee = "0";
            
   /**
    * Minimum Fee member variable.
    */
   private String _MinFee = "0";
            
   /**
    * EffectiveDate member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Frequency MinMax is applied member variable.
    */
   private String _FreqMinMaxApp = "";
            
   /**
    * Charge on Full Redemption member variable.
    */
   private Boolean _ChrgOnFullRed = new Boolean(false);
            
   /**
    * Charge on Partial Redemption member variable.
    */
   private Boolean _ChrgOnPrtlRed = new Boolean(false);
            
   /**
    * Commission Group member variable.
    */
   private String _CommGroup = "";
            
   /**
    * Agency Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Allow Override Type member variable.
    */
   private String _AllowOverrideType = "";
            
   /**
    * Calculation based on member variable.
    */
   private String _BasedOn = "";
            
   /**
    * Currency member variable.
    */
   private String _Currency = "";
            
   /**
    * Who pays member variable.
    */
   private String _WhoPays = "";
            
   /**
    * Shareholder Group member variable.
    */
   private String _ShGroup = "";
            
   /**
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales Rep Code member variable.
    */
   private String _SlsRepCode = "";
            
   /**
    * Family Code member variable.
    */
   private String _FamilyCode = "";
            
   /**
    * Fee Model Code member variable.
    */
   private String _FeeModelCode = "";
            
   /**
    * Charge Option member variable.
    */
   private String _ChargeOption = "";
            
   /**
    * Applied Method member variable.
    */
   private String _AppliedMethod = "";
            
   /**
    * FundList member variable.
    */
   private String _FundList = "";
            
   /**
    * Threshold Amount member variable.
    */
   private String _ThresholdAmt = "0";
            
   /**
    * Threshold Currency member variable.
    */
   private String _ThresholdCurrency = "";
            
   /**
    * Distribution Channel member variable.
    */
   private String _DistribChannel = "";
            
   /**
    * Tax Inclusive flag member variable.
    */
   private String _TaxInclusive = "";
            
   /**
    * Fund Link member variable.
    */
   private String _FundLink = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Scale Detl Recid member array.
    */
   private Integer[] _ScaleDetlRid = new Integer[100];
            
   /**
    * Scale Rate member array.
    */
   private String[] _ScaleRate = new String[100];
            
   /**
    * Upper Bound member array.
    */
   private String[] _UpperBound = new String[100];
            
   /**
    * Lower Bound member array.
    */
   private String[] _LowerBound = new String[100];
            
   /**
    * Level member array.
    */
   private Integer[] _Level = new Integer[100];
            
   /**
    * Scale Effective Date member array.
    */
   private Date[] _ScaleEffectiveDate = new Date[100];
            
   /**
    * Scale Min Fee member array.
    */
   private String[] _ScaleMinFee = new String[100];
            
   /**
    * Scale Max Fee member array.
    */
   private String[] _ScaleMaxFee = new String[100];
            
   /**
    * Scale Run Mode member array.
    */
   private String[] _ScaleRunMode = new String[100];
            
   /**
    * Investment Term member array.
    */
   private Integer[] _InvestTerm = new Integer[100];
            
   /**
    * Threshold/Scale Run Mode member array.
    */
   private String[] _TSRunMode = new String[100];
            
   /**
    * Record Type member array.
    */
   private String[] _RecType = new String[100];
            
   /**
    * Threshold RangeID member array.
    */
   private Integer[] _ThrshldRangeID = new Integer[100];
            
   /**
    * Threshold Level member array.
    */
   private Integer[] _ThrshldLevel = new Integer[100];
            
   /**
    * Threshold Upper Amount member array.
    */
   private String[] _ThrshldUpper = new String[100];
            
   /**
    * Threshold Lower Amount member array.
    */
   private String[] _ThrshldLower = new String[100];
            
   /**
    * Thresholdrange recid member array.
    */
   private Integer[] _ThrshldRecID = new Integer[100];
            
   /**
    * ThresholdRange Version member array.
    */
   private Integer[] _ThrshldVersion = new Integer[100];
            

   /**
    * Constructs the SysLvlFeeUpdRequest object.
    * 
    */
   SysLvlFeeUpdRequest()
   {
      super ( 232 );
   }

   /**
    * Constructs the SysLvlFeeUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SysLvlFeeUpdRequest( String hostEncoding )
   {
      super ( 232, hostEncoding );
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
    * Sets the Fee ID field for the request.
    * 
    * @param value  Value that the Fee ID will be set to.
    */
   public final void setFeeID( Integer value )
   {
      assertUnsent();
      _FeeID = value;
   }
	
   /**
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the From Fund field for the request.
    * 
    * @param value  Value that the From Fund will be set to.
    */
   public final void setFromFundCode( String value )
   {
      assertUnsent();
      _FromFundCode = value;
   }
	
   /**
    * Sets the From Class field for the request.
    * 
    * @param value  Value that the From Class will be set to.
    */
   public final void setFromClassCode( String value )
   {
      assertUnsent();
      _FromClassCode = value;
   }
	
   /**
    * Sets the Fee Code/ Definition field for the request.
    * 
    * @param value  Value that the Fee Code/ Definition will be set to.
    */
   public final void setFeeCode( Integer value )
   {
      assertUnsent();
      _FeeCode = value;
   }
	
   /**
    * Sets the Fee Type field for the request.
    * 
    * @param value  Value that the Fee Type will be set to.
    */
   public final void setFeeType( String value )
   {
      assertUnsent();
      _FeeType = value;
   }
	
   /**
    * Sets the Rate field for the request.
    * 
    * @param value  Value that the Rate will be set to.
    */
   public final void setRate( String value )
   {
      assertUnsent();
      _Rate = value;
   }
	
   /**
    * Sets the Maximum Fee field for the request.
    * 
    * @param value  Value that the Maximum Fee will be set to.
    */
   public final void setMaxFee( String value )
   {
      assertUnsent();
      _MaxFee = value;
   }
	
   /**
    * Sets the Minimum Fee field for the request.
    * 
    * @param value  Value that the Minimum Fee will be set to.
    */
   public final void setMinFee( String value )
   {
      assertUnsent();
      _MinFee = value;
   }
	
   /**
    * Sets the EffectiveDate field for the request.
    * 
    * @param value  Value that the EffectiveDate will be set to.
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
    * Sets the Frequency MinMax is applied field for the request.
    * 
    * @param value  Value that the Frequency MinMax is applied will be set to.
    */
   public final void setFreqMinMaxApp( String value )
   {
      assertUnsent();
      _FreqMinMaxApp = value;
   }
	
   /**
    * Sets the Charge on Full Redemption field for the request.
    * 
    * @param value  Value that the Charge on Full Redemption will be set to.
    */
   public final void setChrgOnFullRed( Boolean value )
   {
      assertUnsent();
      _ChrgOnFullRed = value;
   }
	
   /**
    * Sets the Charge on Partial Redemption field for the request.
    * 
    * @param value  Value that the Charge on Partial Redemption will be set to.
    */
   public final void setChrgOnPrtlRed( Boolean value )
   {
      assertUnsent();
      _ChrgOnPrtlRed = value;
   }
	
   /**
    * Sets the Commission Group field for the request.
    * 
    * @param value  Value that the Commission Group will be set to.
    */
   public final void setCommGroup( String value )
   {
      assertUnsent();
      _CommGroup = value;
   }
	
   /**
    * Sets the Agency Code field for the request.
    * 
    * @param value  Value that the Agency Code will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Allow Override Type field for the request.
    * 
    * @param value  Value that the Allow Override Type will be set to.
    */
   public final void setAllowOverrideType( String value )
   {
      assertUnsent();
      _AllowOverrideType = value;
   }
	
   /**
    * Sets the Calculation based on field for the request.
    * 
    * @param value  Value that the Calculation based on will be set to.
    */
   public final void setBasedOn( String value )
   {
      assertUnsent();
      _BasedOn = value;
   }
	
   /**
    * Sets the Currency field for the request.
    * 
    * @param value  Value that the Currency will be set to.
    */
   public final void setCurrency( String value )
   {
      assertUnsent();
      _Currency = value;
   }
	
   /**
    * Sets the Who pays field for the request.
    * 
    * @param value  Value that the Who pays will be set to.
    */
   public final void setWhoPays( String value )
   {
      assertUnsent();
      _WhoPays = value;
   }
	
   /**
    * Sets the Shareholder Group field for the request.
    * 
    * @param value  Value that the Shareholder Group will be set to.
    */
   public final void setShGroup( String value )
   {
      assertUnsent();
      _ShGroup = value;
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
   public final void setSlsRepCode( String value )
   {
      assertUnsent();
      _SlsRepCode = value;
   }
	
   /**
    * Sets the Family Code field for the request.
    * 
    * @param value  Value that the Family Code will be set to.
    */
   public final void setFamilyCode( String value )
   {
      assertUnsent();
      _FamilyCode = value;
   }
	
   /**
    * Sets the Fee Model Code field for the request.
    * 
    * @param value  Value that the Fee Model Code will be set to.
    */
   public final void setFeeModelCode( String value )
   {
      assertUnsent();
      _FeeModelCode = value;
   }
	
   /**
    * Sets the Charge Option field for the request.
    * 
    * @param value  Value that the Charge Option will be set to.
    */
   public final void setChargeOption( String value )
   {
      assertUnsent();
      _ChargeOption = value;
   }
	
   /**
    * Sets the Applied Method field for the request.
    * 
    * @param value  Value that the Applied Method will be set to.
    */
   public final void setAppliedMethod( String value )
   {
      assertUnsent();
      _AppliedMethod = value;
   }
	
   /**
    * Sets the FundList field for the request.
    * 
    * @param value  Value that the FundList will be set to.
    */
   public final void setFundList( String value )
   {
      assertUnsent();
      _FundList = value;
   }
	
   /**
    * Sets the Threshold Amount field for the request.
    * 
    * @param value  Value that the Threshold Amount will be set to.
    */
   public final void setThresholdAmt( String value )
   {
      assertUnsent();
      _ThresholdAmt = value;
   }
	
   /**
    * Sets the Threshold Currency field for the request.
    * 
    * @param value  Value that the Threshold Currency will be set to.
    */
   public final void setThresholdCurrency( String value )
   {
      assertUnsent();
      _ThresholdCurrency = value;
   }
	
   /**
    * Sets the Distribution Channel field for the request.
    * 
    * @param value  Value that the Distribution Channel will be set to.
    */
   public final void setDistribChannel( String value )
   {
      assertUnsent();
      _DistribChannel = value;
   }
	
   /**
    * Sets the Tax Inclusive flag field for the request.
    * 
    * @param value  Value that the Tax Inclusive flag will be set to.
    */
   public final void setTaxInclusive( String value )
   {
      assertUnsent();
      _TaxInclusive = value;
   }
	
   /**
    * Sets the Fund Link field for the request.
    * 
    * @param value  Value that the Fund Link will be set to.
    */
   public final void setFundLink( String value )
   {
      assertUnsent();
      _FundLink = value;
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
    * Sets the Scale Detl Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Scale Detl Recid will be set to.
    */
   public final void setScaleDetlRid( int index, Integer value )
   {
      assertUnsent();
      _ScaleDetlRid[index] = value;
   }
	
   /**
    * Sets the Scale Rate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Scale Rate will be set to.
    */
   public final void setScaleRate( int index, String value )
   {
      assertUnsent();
      _ScaleRate[index] = value;
   }
	
   /**
    * Sets the Upper Bound field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Upper Bound will be set to.
    */
   public final void setUpperBound( int index, String value )
   {
      assertUnsent();
      _UpperBound[index] = value;
   }
	
   /**
    * Sets the Lower Bound field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Lower Bound will be set to.
    */
   public final void setLowerBound( int index, String value )
   {
      assertUnsent();
      _LowerBound[index] = value;
   }
	
   /**
    * Sets the Level field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Level will be set to.
    */
   public final void setLevel( int index, Integer value )
   {
      assertUnsent();
      _Level[index] = value;
   }
	
   /**
    * Sets the Scale Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Scale Effective Date will be set to.
    */
   public final void setScaleEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _ScaleEffectiveDate[index] = value;
   }
	
   /**
    * Sets the Scale Min Fee field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Scale Min Fee will be set to.
    */
   public final void setScaleMinFee( int index, String value )
   {
      assertUnsent();
      _ScaleMinFee[index] = value;
   }
	
   /**
    * Sets the Scale Max Fee field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Scale Max Fee will be set to.
    */
   public final void setScaleMaxFee( int index, String value )
   {
      assertUnsent();
      _ScaleMaxFee[index] = value;
   }
	
   /**
    * Sets the Scale Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Scale Run Mode will be set to.
    */
   public final void setScaleRunMode( int index, String value )
   {
      assertUnsent();
      _ScaleRunMode[index] = value;
   }
	
   /**
    * Sets the Investment Term field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Investment Term will be set to.
    */
   public final void setInvestTerm( int index, Integer value )
   {
      assertUnsent();
      _InvestTerm[index] = value;
   }
	
   /**
    * Sets the Threshold/Scale Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Threshold/Scale Run Mode will be set to.
    */
   public final void setTSRunMode( int index, String value )
   {
      assertUnsent();
      _TSRunMode[index] = value;
   }
	
   /**
    * Sets the Record Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Record Type will be set to.
    */
   public final void setRecType( int index, String value )
   {
      assertUnsent();
      _RecType[index] = value;
   }
	
   /**
    * Sets the Threshold RangeID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Threshold RangeID will be set to.
    */
   public final void setThrshldRangeID( int index, Integer value )
   {
      assertUnsent();
      _ThrshldRangeID[index] = value;
   }
	
   /**
    * Sets the Threshold Level field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Threshold Level will be set to.
    */
   public final void setThrshldLevel( int index, Integer value )
   {
      assertUnsent();
      _ThrshldLevel[index] = value;
   }
	
   /**
    * Sets the Threshold Upper Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Threshold Upper Amount will be set to.
    */
   public final void setThrshldUpper( int index, String value )
   {
      assertUnsent();
      _ThrshldUpper[index] = value;
   }
	
   /**
    * Sets the Threshold Lower Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Threshold Lower Amount will be set to.
    */
   public final void setThrshldLower( int index, String value )
   {
      assertUnsent();
      _ThrshldLower[index] = value;
   }
	
   /**
    * Sets the Thresholdrange recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Thresholdrange recid will be set to.
    */
   public final void setThrshldRecID( int index, Integer value )
   {
      assertUnsent();
      _ThrshldRecID[index] = value;
   }
	
   /**
    * Sets the ThresholdRange Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ThresholdRange Version will be set to.
    */
   public final void setThrshldVersion( int index, Integer value )
   {
      assertUnsent();
      _ThrshldVersion[index] = value;
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
      requestBuffer.appendField( _FeeID );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _FromFundCode );
      requestBuffer.appendField( _FromClassCode );
      requestBuffer.appendField( _FeeCode );
      requestBuffer.appendField( _FeeType );
      requestBuffer.appendField( _Rate );
      requestBuffer.appendField( _MaxFee );
      requestBuffer.appendField( _MinFee );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _FreqMinMaxApp );
      requestBuffer.appendField( _ChrgOnFullRed );
      requestBuffer.appendField( _ChrgOnPrtlRed );
      requestBuffer.appendField( _CommGroup );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _AllowOverrideType );
      requestBuffer.appendField( _BasedOn );
      requestBuffer.appendField( _Currency );
      requestBuffer.appendField( _WhoPays );
      requestBuffer.appendField( _ShGroup );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SlsRepCode );
      requestBuffer.appendField( _FamilyCode );
      requestBuffer.appendField( _FeeModelCode );
      requestBuffer.appendField( _ChargeOption );
      requestBuffer.appendField( _AppliedMethod );
      requestBuffer.appendField( _FundList );
      requestBuffer.appendField( _ThresholdAmt );
      requestBuffer.appendField( _ThresholdCurrency );
      requestBuffer.appendField( _DistribChannel );
      requestBuffer.appendField( _TaxInclusive );
      requestBuffer.appendField( _FundLink );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _ScaleDetlRid[x] );
         requestBuffer.appendField( _ScaleRate[x] );
         requestBuffer.appendField( _UpperBound[x] );
         requestBuffer.appendField( _LowerBound[x] );
         requestBuffer.appendField( _Level[x] );
         requestBuffer.appendField( _ScaleEffectiveDate[x] );
         requestBuffer.appendField( _ScaleMinFee[x] );
         requestBuffer.appendField( _ScaleMaxFee[x] );
         requestBuffer.appendField( _ScaleRunMode[x] );
         requestBuffer.appendField( _InvestTerm[x] );
         requestBuffer.appendField( _TSRunMode[x] );
         requestBuffer.appendField( _RecType[x] );
         requestBuffer.appendField( _ThrshldRangeID[x] );
         requestBuffer.appendField( _ThrshldLevel[x] );
         requestBuffer.appendField( _ThrshldUpper[x] );
         requestBuffer.appendField( _ThrshldLower[x] );
         requestBuffer.appendField( _ThrshldRecID[x] );
         requestBuffer.appendField( _ThrshldVersion[x] );
      }
   }

}

