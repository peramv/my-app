// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * AMS Allocation Update request.
 * For additional view information see <A HREF="../../../../viewspecs/AMSAllocMaint.doc">AMSAllocMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSAllocMaintRequest extends IFastRequest implements Serializable
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
    * AMS Code member variable.
    */
   private String _AMSCode = "";
            
   /**
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * AMS Code Version member variable.
    */
   private Integer _AMSCodeVer = null;
            
   /**
    * Rebalance Percent member variable.
    */
   private String _RBLPrcnt = "0";
            
   /**
    * Currency member variable.
    */
   private String _Currency = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * AMS Type member variable.
    */
   private String _AMSType = "";
            
   /**
    * AMS Name member variable.
    */
   private String _AMSDesc = "";
            
   /**
    * Default Allocations required ? member variable.
    */
   private Boolean _DefaultAlloc = new Boolean(false);
            
   /**
    * Fund Allocations required ? member variable.
    */
   private Boolean _FundAlloc = new Boolean(false);
            
   /**
    * English  Short Name member variable.
    */
   private String _EnglishShortName = "";
            
   /**
    * English  Long Name member variable.
    */
   private String _EnglishLongName = "";
            
   /**
    * English Name member variable.
    */
   private String _EnglishName = "";
            
   /**
    * French Short Name member variable.
    */
   private String _FrenchShortName = "";
            
   /**
    * French Long Name member variable.
    */
   private String _FrenchLongName = "";
            
   /**
    * French Name member variable.
    */
   private String _FrenchName = "";
            
   /**
    * Foreign Rel Fund member variable.
    */
   private String _ForeignRelFund = "";
            
   /**
    * Foreign Rel Class member variable.
    */
   private String _ForeignRelClass = "";
            
   /**
    * Rounding Fund member variable.
    */
   private String _RoundingFund = "";
            
   /**
    * Rounding Class member variable.
    */
   private String _RoundingClass = "";
            
   /**
    * Grandfathered As-of Date member variable.
    */
   private Date _GrandFatheredDate = null;
            
   /**
    * Next Rebalancing Date member variable.
    */
   private Date _NextRebalDate = null;
            
   /**
    * Threshold Amount member variable.
    */
   private String _ThresholdAmt = "0";
            
   /**
    * Wire Eligible member variable.
    */
   private Boolean _WireElig = new Boolean(false);
            
   /**
    * Day of the Week member variable.
    */
   private Integer _DayofWeek = null;
            
   /**
    * Verify Precreate member variable.
    */
   private Boolean _VerifyPrecreate = new Boolean(false);
            
   /**
    * Associated Fund member variable.
    */
   private String _AssocFund = "";
            
   /**
    * Associated Class member variable.
    */
   private String _AssocClass = "";
            
   /**
    * SchedSetupFreqID member variable.
    */
   private Integer _SchedSetupFreqID = null;
            
   /**
    * Flag to indicate if traded via parent fund class member variable.
    */
   private String _ParentFndClsTrdg = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Allocation RunMode member array.
    */
   private String[] _AMSAllocRunMode = new String[25];
            
   /**
    * Allocation Record ID member array.
    */
   private Integer[] _AMSAllocRId = new Integer[25];
            
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = new String[25];
            
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = new String[25];
            
   /**
    * Percentage of Allocation member array.
    */
   private String[] _PrcntAlloc = new String[25];
            
   /**
    * Allocation Version Number member array.
    */
   private Integer[] _AllocVer = new Integer[25];
            

   /**
    * Constructs the AMSAllocMaintRequest object.
    * 
    */
   AMSAllocMaintRequest()
   {
      super ( 219 );
   }

   /**
    * Constructs the AMSAllocMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AMSAllocMaintRequest( String hostEncoding )
   {
      super ( 219, hostEncoding );
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
    * Sets the AMS Code field for the request.
    * 
    * @param value  Value that the AMS Code will be set to.
    */
   public final void setAMSCode( String value )
   {
      assertUnsent();
      _AMSCode = value;
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
    * Sets the AMS Code Version field for the request.
    * 
    * @param value  Value that the AMS Code Version will be set to.
    */
   public final void setAMSCodeVer( Integer value )
   {
      assertUnsent();
      _AMSCodeVer = value;
   }
	
   /**
    * Sets the Rebalance Percent field for the request.
    * 
    * @param value  Value that the Rebalance Percent will be set to.
    */
   public final void setRBLPrcnt( String value )
   {
      assertUnsent();
      _RBLPrcnt = value;
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
    * Sets the AMS Type field for the request.
    * 
    * @param value  Value that the AMS Type will be set to.
    */
   public final void setAMSType( String value )
   {
      assertUnsent();
      _AMSType = value;
   }
	
   /**
    * Sets the AMS Name field for the request.
    * 
    * @param value  Value that the AMS Name will be set to.
    */
   public final void setAMSDesc( String value )
   {
      assertUnsent();
      _AMSDesc = value;
   }
	
   /**
    * Sets the Default Allocations required ? field for the request.
    * 
    * @param value  Value that the Default Allocations required ? will be set to.
    */
   public final void setDefaultAlloc( Boolean value )
   {
      assertUnsent();
      _DefaultAlloc = value;
   }
	
   /**
    * Sets the Fund Allocations required ? field for the request.
    * 
    * @param value  Value that the Fund Allocations required ? will be set to.
    */
   public final void setFundAlloc( Boolean value )
   {
      assertUnsent();
      _FundAlloc = value;
   }
	
   /**
    * Sets the English  Short Name field for the request.
    * 
    * @param value  Value that the English  Short Name will be set to.
    */
   public final void setEnglishShortName( String value )
   {
      assertUnsent();
      _EnglishShortName = value;
   }
	
   /**
    * Sets the English  Long Name field for the request.
    * 
    * @param value  Value that the English  Long Name will be set to.
    */
   public final void setEnglishLongName( String value )
   {
      assertUnsent();
      _EnglishLongName = value;
   }
	
   /**
    * Sets the English Name field for the request.
    * 
    * @param value  Value that the English Name will be set to.
    */
   public final void setEnglishName( String value )
   {
      assertUnsent();
      _EnglishName = value;
   }
	
   /**
    * Sets the French Short Name field for the request.
    * 
    * @param value  Value that the French Short Name will be set to.
    */
   public final void setFrenchShortName( String value )
   {
      assertUnsent();
      _FrenchShortName = value;
   }
	
   /**
    * Sets the French Long Name field for the request.
    * 
    * @param value  Value that the French Long Name will be set to.
    */
   public final void setFrenchLongName( String value )
   {
      assertUnsent();
      _FrenchLongName = value;
   }
	
   /**
    * Sets the French Name field for the request.
    * 
    * @param value  Value that the French Name will be set to.
    */
   public final void setFrenchName( String value )
   {
      assertUnsent();
      _FrenchName = value;
   }
	
   /**
    * Sets the Foreign Rel Fund field for the request.
    * 
    * @param value  Value that the Foreign Rel Fund will be set to.
    */
   public final void setForeignRelFund( String value )
   {
      assertUnsent();
      _ForeignRelFund = value;
   }
	
   /**
    * Sets the Foreign Rel Class field for the request.
    * 
    * @param value  Value that the Foreign Rel Class will be set to.
    */
   public final void setForeignRelClass( String value )
   {
      assertUnsent();
      _ForeignRelClass = value;
   }
	
   /**
    * Sets the Rounding Fund field for the request.
    * 
    * @param value  Value that the Rounding Fund will be set to.
    */
   public final void setRoundingFund( String value )
   {
      assertUnsent();
      _RoundingFund = value;
   }
	
   /**
    * Sets the Rounding Class field for the request.
    * 
    * @param value  Value that the Rounding Class will be set to.
    */
   public final void setRoundingClass( String value )
   {
      assertUnsent();
      _RoundingClass = value;
   }
	
   /**
    * Sets the Grandfathered As-of Date field for the request.
    * 
    * @param value  Value that the Grandfathered As-of Date will be set to.
    */
   public final void setGrandFatheredDate( Date value )
   {
      assertUnsent();
      _GrandFatheredDate = value;
   }
	
   /**
    * Sets the Next Rebalancing Date field for the request.
    * 
    * @param value  Value that the Next Rebalancing Date will be set to.
    */
   public final void setNextRebalDate( Date value )
   {
      assertUnsent();
      _NextRebalDate = value;
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
    * Sets the Wire Eligible field for the request.
    * 
    * @param value  Value that the Wire Eligible will be set to.
    */
   public final void setWireElig( Boolean value )
   {
      assertUnsent();
      _WireElig = value;
   }
	
   /**
    * Sets the Day of the Week field for the request.
    * 
    * @param value  Value that the Day of the Week will be set to.
    */
   public final void setDayofWeek( Integer value )
   {
      assertUnsent();
      _DayofWeek = value;
   }
	
   /**
    * Sets the Verify Precreate field for the request.
    * 
    * @param value  Value that the Verify Precreate will be set to.
    */
   public final void setVerifyPrecreate( Boolean value )
   {
      assertUnsent();
      _VerifyPrecreate = value;
   }
	
   /**
    * Sets the Associated Fund field for the request.
    * 
    * @param value  Value that the Associated Fund will be set to.
    */
   public final void setAssocFund( String value )
   {
      assertUnsent();
      _AssocFund = value;
   }
	
   /**
    * Sets the Associated Class field for the request.
    * 
    * @param value  Value that the Associated Class will be set to.
    */
   public final void setAssocClass( String value )
   {
      assertUnsent();
      _AssocClass = value;
   }
	
   /**
    * Sets the SchedSetupFreqID field for the request.
    * 
    * @param value  Value that the SchedSetupFreqID will be set to.
    */
   public final void setSchedSetupFreqID( Integer value )
   {
      assertUnsent();
      _SchedSetupFreqID = value;
   }
	
   /**
    * Sets the Flag to indicate if traded via parent fund class field for the request.
    * 
    * @param value  Value that the Flag to indicate if traded via parent fund class will be set to.
    */
   public final void setParentFndClsTrdg( String value )
   {
      assertUnsent();
      _ParentFndClsTrdg = value;
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
    * Sets the Allocation RunMode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation RunMode will be set to.
    */
   public final void setAMSAllocRunMode( int index, String value )
   {
      assertUnsent();
      _AMSAllocRunMode[index] = value;
   }
	
   /**
    * Sets the Allocation Record ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Record ID will be set to.
    */
   public final void setAMSAllocRId( int index, Integer value )
   {
      assertUnsent();
      _AMSAllocRId[index] = value;
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
    * Sets the Percentage of Allocation field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Percentage of Allocation will be set to.
    */
   public final void setPrcntAlloc( int index, String value )
   {
      assertUnsent();
      _PrcntAlloc[index] = value;
   }
	
   /**
    * Sets the Allocation Version Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Version Number will be set to.
    */
   public final void setAllocVer( int index, Integer value )
   {
      assertUnsent();
      _AllocVer[index] = value;
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
      requestBuffer.appendField( _AMSCode );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _AMSCodeVer );
      requestBuffer.appendField( _RBLPrcnt );
      requestBuffer.appendField( _Currency );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _AMSType );
      requestBuffer.appendField( _AMSDesc );
      requestBuffer.appendField( _DefaultAlloc );
      requestBuffer.appendField( _FundAlloc );
      requestBuffer.appendField( _EnglishShortName );
      requestBuffer.appendField( _EnglishLongName );
      requestBuffer.appendField( _EnglishName );
      requestBuffer.appendField( _FrenchShortName );
      requestBuffer.appendField( _FrenchLongName );
      requestBuffer.appendField( _FrenchName );
      requestBuffer.appendField( _ForeignRelFund );
      requestBuffer.appendField( _ForeignRelClass );
      requestBuffer.appendField( _RoundingFund );
      requestBuffer.appendField( _RoundingClass );
      requestBuffer.appendField( _GrandFatheredDate );
      requestBuffer.appendField( _NextRebalDate );
      requestBuffer.appendField( _ThresholdAmt );
      requestBuffer.appendField( _WireElig );
      requestBuffer.appendField( _DayofWeek );
      requestBuffer.appendField( _VerifyPrecreate );
      requestBuffer.appendField( _AssocFund );
      requestBuffer.appendField( _AssocClass );
      requestBuffer.appendField( _SchedSetupFreqID );
      requestBuffer.appendField( _ParentFndClsTrdg );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _AMSAllocRunMode[x] );
         requestBuffer.appendField( _AMSAllocRId[x] );
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _ClassCode[x] );
         requestBuffer.appendField( _PrcntAlloc[x] );
         requestBuffer.appendField( _AllocVer[x] );
      }
   }

}

