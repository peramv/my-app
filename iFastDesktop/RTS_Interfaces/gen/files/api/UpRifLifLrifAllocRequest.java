// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account RRIF/LIF/LRIF Allocations  Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/UpRifLifLrifAlloc.doc">UpRifLifLrifAlloc.doc</A>.
 * 
 * @author RTS Generated
 */
public class UpRifLifLrifAllocRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
   /**
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * RIF/LIF/LRIF Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * CallNum - Basis for DateFrom member variable.
    */
   private String _CallNum = "";
            
   /**
    * Payment Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * Mandatory Amount per Payment member variable.
    */
   private String _MandAmtPay = "0";
            
   /**
    * Mandatory Amount per Year member variable.
    */
   private String _MandAmtYr = "0";
            
   /**
    * Maximum Amount per Year member variable.
    */
   private String _MaxAmtYr = "0";
            
   /**
    * Payment Option member variable.
    */
   private String _PayOption = "";
            
   /**
    * Spouse's Date of Birth member variable.
    */
   private Date _SpouseBirth = null;
            
   /**
    * Is account registered before 1993 member variable.
    */
   private Boolean _Qualified = new Boolean(false);
            
   /**
    * RRIF Detail Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Record Type member variable.
    */
   private String _RecordType = "";
            
   /**
    * Record is active or inactive member variable.
    */
   private String _GoodBad = "";
            
   /**
    * Effective Date for Calculation member variable.
    */
   private Date _EffectiveFrom = null;
            
   /**
    * Gross or Net Amount member variable.
    */
   private String _GrossOrNet = "";
            
   /**
    * Net Amount member variable.
    */
   private String _NetAmount = "0";
            
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Debit in January member variable.
    */
   private Boolean _January = new Boolean(false);
            
   /**
    * Debit in February member variable.
    */
   private Boolean _February = new Boolean(false);
            
   /**
    * Debit in March member variable.
    */
   private Boolean _March = new Boolean(false);
            
   /**
    * Debit in April member variable.
    */
   private Boolean _April = new Boolean(false);
            
   /**
    * Debit in May member variable.
    */
   private Boolean _May = new Boolean(false);
            
   /**
    * Debit in June member variable.
    */
   private Boolean _June = new Boolean(false);
            
   /**
    * Debit in July member variable.
    */
   private Boolean _July = new Boolean(false);
            
   /**
    * Debit in August member variable.
    */
   private Boolean _August = new Boolean(false);
            
   /**
    * Debit in September member variable.
    */
   private Boolean _September = new Boolean(false);
            
   /**
    * Debit in October member variable.
    */
   private Boolean _October = new Boolean(false);
            
   /**
    * Debit in November member variable.
    */
   private Boolean _November = new Boolean(false);
            
   /**
    * Debit in December member variable.
    */
   private Boolean _December = new Boolean(false);
            
   /**
    * Suppress Federal Tax member variable.
    */
   private Boolean _SuppFedTax = new Boolean(false);
            
   /**
    * Federal Tax Rate member variable.
    */
   private String _FedRate = "0";
            
   /**
    * Federal Tax Rate Unit member variable.
    */
   private String _FedRatePUD = "";
            
   /**
    * Suppress Provincial Tax Rate member variable.
    */
   private Boolean _SuppProvTax = new Boolean(false);
            
   /**
    * Provincial Tax Rate member variable.
    */
   private String _ProvRate = "0";
            
   /**
    * Provincial Tax Rate Unit member variable.
    */
   private String _ProvRatePUD = "";
            
   /**
    * Tax Calculation on Minimum Payment member variable.
    */
   private Boolean _TaxOnMin = new Boolean(false);
            
   /**
    * Override Yearly Mandatory Amount member variable.
    */
   private Boolean _OverrideAmtYr = new Boolean(false);
            
   /**
    * Last Process Date member variable.
    */
   private Date _LastProcDate = null;
            
   /**
    * Flag to view fed/ prov tax member variable.
    */
   private Boolean _CalcFedProvTax = new Boolean(false);
            
   /**
    * Record Id member variable.
    */
   private Integer _RIFId = null;
            
            
            
   /**
    * PrevYrBalPct member variable.
    */
   private String _PrevYrBalPct = "0";
            
   /**
    * Frequency member variable.
    */
   private String _Frequency = "";
            
   /**
    * Day Of Week member variable.
    */
   private String _DayOfWeek = "";
            
   /**
    * Days Of Month member variable.
    */
   private String _DaysOfMonth = "";
            
   /**
    * AWD Business Area member variable.
    */
   private String _AWDBusinessArea = "";
            
   /**
    * AWD Work Type member variable.
    */
   private String _AWDWorkType = "";
            
   /**
    * AWD Object Key member variable.
    */
   private String _AWDObjectKey = "";
            
   /**
    * AWD Obj Date Time member variable.
    */
   private String _AWDObjDateTime = "";
            
   /**
    * Override Unused  Max Amount member variable.
    */
   private Boolean _OverrideUnusedMax = new Boolean(false);
            
   /**
    * PY Unused Maximun Amount member variable.
    */
   private String _PYUnusedMax = "0";
            
   /**
    * External Assets member variable.
    */
   private String _ExternalAssets = "0";
            

   /**
    * Constructs the UpRifLifLrifAllocRequest object.
    * 
    */
   UpRifLifLrifAllocRequest()
   {
      super ( 130 );
   }

   /**
    * Constructs the UpRifLifLrifAllocRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   UpRifLifLrifAllocRequest( String hostEncoding )
   {
      super ( 130, hostEncoding );
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
    * Sets the RIF/LIF/LRIF Account Number field for the request.
    * 
    * @param value  Value that the RIF/LIF/LRIF Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the CallNum - Basis for DateFrom field for the request.
    * 
    * @param value  Value that the CallNum - Basis for DateFrom will be set to.
    */
   public final void setCallNum( String value )
   {
      assertUnsent();
      _CallNum = value;
   }
	
   /**
    * Sets the Payment Amount field for the request.
    * 
    * @param value  Value that the Payment Amount will be set to.
    */
   public final void setAmount( String value )
   {
      assertUnsent();
      _Amount = value;
   }
	
   /**
    * Sets the Mandatory Amount per Payment field for the request.
    * 
    * @param value  Value that the Mandatory Amount per Payment will be set to.
    */
   public final void setMandAmtPay( String value )
   {
      assertUnsent();
      _MandAmtPay = value;
   }
	
   /**
    * Sets the Mandatory Amount per Year field for the request.
    * 
    * @param value  Value that the Mandatory Amount per Year will be set to.
    */
   public final void setMandAmtYr( String value )
   {
      assertUnsent();
      _MandAmtYr = value;
   }
	
   /**
    * Sets the Maximum Amount per Year field for the request.
    * 
    * @param value  Value that the Maximum Amount per Year will be set to.
    */
   public final void setMaxAmtYr( String value )
   {
      assertUnsent();
      _MaxAmtYr = value;
   }
	
   /**
    * Sets the Payment Option field for the request.
    * 
    * @param value  Value that the Payment Option will be set to.
    */
   public final void setPayOption( String value )
   {
      assertUnsent();
      _PayOption = value;
   }
	
   /**
    * Sets the Spouse's Date of Birth field for the request.
    * 
    * @param value  Value that the Spouse's Date of Birth will be set to.
    */
   public final void setSpouseBirth( Date value )
   {
      assertUnsent();
      _SpouseBirth = value;
   }
	
   /**
    * Sets the Is account registered before 1993 field for the request.
    * 
    * @param value  Value that the Is account registered before 1993 will be set to.
    */
   public final void setQualified( Boolean value )
   {
      assertUnsent();
      _Qualified = value;
   }
	
   /**
    * Sets the RRIF Detail Effective Date field for the request.
    * 
    * @param value  Value that the RRIF Detail Effective Date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the Record Type field for the request.
    * 
    * @param value  Value that the Record Type will be set to.
    */
   public final void setRecordType( String value )
   {
      assertUnsent();
      _RecordType = value;
   }
	
   /**
    * Sets the Record is active or inactive field for the request.
    * 
    * @param value  Value that the Record is active or inactive will be set to.
    */
   public final void setGoodBad( String value )
   {
      assertUnsent();
      _GoodBad = value;
   }
	
   /**
    * Sets the Effective Date for Calculation field for the request.
    * 
    * @param value  Value that the Effective Date for Calculation will be set to.
    */
   public final void setEffectiveFrom( Date value )
   {
      assertUnsent();
      _EffectiveFrom = value;
   }
	
   /**
    * Sets the Gross or Net Amount field for the request.
    * 
    * @param value  Value that the Gross or Net Amount will be set to.
    */
   public final void setGrossOrNet( String value )
   {
      assertUnsent();
      _GrossOrNet = value;
   }
	
   /**
    * Sets the Net Amount field for the request.
    * 
    * @param value  Value that the Net Amount will be set to.
    */
   public final void setNetAmount( String value )
   {
      assertUnsent();
      _NetAmount = value;
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
    * Sets the Debit in January field for the request.
    * 
    * @param value  Value that the Debit in January will be set to.
    */
   public final void setJanuary( Boolean value )
   {
      assertUnsent();
      _January = value;
   }
	
   /**
    * Sets the Debit in February field for the request.
    * 
    * @param value  Value that the Debit in February will be set to.
    */
   public final void setFebruary( Boolean value )
   {
      assertUnsent();
      _February = value;
   }
	
   /**
    * Sets the Debit in March field for the request.
    * 
    * @param value  Value that the Debit in March will be set to.
    */
   public final void setMarch( Boolean value )
   {
      assertUnsent();
      _March = value;
   }
	
   /**
    * Sets the Debit in April field for the request.
    * 
    * @param value  Value that the Debit in April will be set to.
    */
   public final void setApril( Boolean value )
   {
      assertUnsent();
      _April = value;
   }
	
   /**
    * Sets the Debit in May field for the request.
    * 
    * @param value  Value that the Debit in May will be set to.
    */
   public final void setMay( Boolean value )
   {
      assertUnsent();
      _May = value;
   }
	
   /**
    * Sets the Debit in June field for the request.
    * 
    * @param value  Value that the Debit in June will be set to.
    */
   public final void setJune( Boolean value )
   {
      assertUnsent();
      _June = value;
   }
	
   /**
    * Sets the Debit in July field for the request.
    * 
    * @param value  Value that the Debit in July will be set to.
    */
   public final void setJuly( Boolean value )
   {
      assertUnsent();
      _July = value;
   }
	
   /**
    * Sets the Debit in August field for the request.
    * 
    * @param value  Value that the Debit in August will be set to.
    */
   public final void setAugust( Boolean value )
   {
      assertUnsent();
      _August = value;
   }
	
   /**
    * Sets the Debit in September field for the request.
    * 
    * @param value  Value that the Debit in September will be set to.
    */
   public final void setSeptember( Boolean value )
   {
      assertUnsent();
      _September = value;
   }
	
   /**
    * Sets the Debit in October field for the request.
    * 
    * @param value  Value that the Debit in October will be set to.
    */
   public final void setOctober( Boolean value )
   {
      assertUnsent();
      _October = value;
   }
	
   /**
    * Sets the Debit in November field for the request.
    * 
    * @param value  Value that the Debit in November will be set to.
    */
   public final void setNovember( Boolean value )
   {
      assertUnsent();
      _November = value;
   }
	
   /**
    * Sets the Debit in December field for the request.
    * 
    * @param value  Value that the Debit in December will be set to.
    */
   public final void setDecember( Boolean value )
   {
      assertUnsent();
      _December = value;
   }
	
   /**
    * Sets the Suppress Federal Tax field for the request.
    * 
    * @param value  Value that the Suppress Federal Tax will be set to.
    */
   public final void setSuppFedTax( Boolean value )
   {
      assertUnsent();
      _SuppFedTax = value;
   }
	
   /**
    * Sets the Federal Tax Rate field for the request.
    * 
    * @param value  Value that the Federal Tax Rate will be set to.
    */
   public final void setFedRate( String value )
   {
      assertUnsent();
      _FedRate = value;
   }
	
   /**
    * Sets the Federal Tax Rate Unit field for the request.
    * 
    * @param value  Value that the Federal Tax Rate Unit will be set to.
    */
   public final void setFedRatePUD( String value )
   {
      assertUnsent();
      _FedRatePUD = value;
   }
	
   /**
    * Sets the Suppress Provincial Tax Rate field for the request.
    * 
    * @param value  Value that the Suppress Provincial Tax Rate will be set to.
    */
   public final void setSuppProvTax( Boolean value )
   {
      assertUnsent();
      _SuppProvTax = value;
   }
	
   /**
    * Sets the Provincial Tax Rate field for the request.
    * 
    * @param value  Value that the Provincial Tax Rate will be set to.
    */
   public final void setProvRate( String value )
   {
      assertUnsent();
      _ProvRate = value;
   }
	
   /**
    * Sets the Provincial Tax Rate Unit field for the request.
    * 
    * @param value  Value that the Provincial Tax Rate Unit will be set to.
    */
   public final void setProvRatePUD( String value )
   {
      assertUnsent();
      _ProvRatePUD = value;
   }
	
   /**
    * Sets the Tax Calculation on Minimum Payment field for the request.
    * 
    * @param value  Value that the Tax Calculation on Minimum Payment will be set to.
    */
   public final void setTaxOnMin( Boolean value )
   {
      assertUnsent();
      _TaxOnMin = value;
   }
	
   /**
    * Sets the Override Yearly Mandatory Amount field for the request.
    * 
    * @param value  Value that the Override Yearly Mandatory Amount will be set to.
    */
   public final void setOverrideAmtYr( Boolean value )
   {
      assertUnsent();
      _OverrideAmtYr = value;
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
    * Sets the Flag to view fed/ prov tax field for the request.
    * 
    * @param value  Value that the Flag to view fed/ prov tax will be set to.
    */
   public final void setCalcFedProvTax( Boolean value )
   {
      assertUnsent();
      _CalcFedProvTax = value;
   }
	
   /**
    * Sets the Record Id field for the request.
    * 
    * @param value  Value that the Record Id will be set to.
    */
   public final void setRIFId( Integer value )
   {
      assertUnsent();
      _RIFId = value;
   }
	
   /**
    * Sets the PrevYrBalPct field for the request.
    * 
    * @param value  Value that the PrevYrBalPct will be set to.
    */
   public final void setPrevYrBalPct( String value )
   {
      assertUnsent();
      _PrevYrBalPct = value;
   }
	
   /**
    * Sets the Frequency field for the request.
    * 
    * @param value  Value that the Frequency will be set to.
    */
   public final void setFrequency( String value )
   {
      assertUnsent();
      _Frequency = value;
   }
	
   /**
    * Sets the Day Of Week field for the request.
    * 
    * @param value  Value that the Day Of Week will be set to.
    */
   public final void setDayOfWeek( String value )
   {
      assertUnsent();
      _DayOfWeek = value;
   }
	
   /**
    * Sets the Days Of Month field for the request.
    * 
    * @param value  Value that the Days Of Month will be set to.
    */
   public final void setDaysOfMonth( String value )
   {
      assertUnsent();
      _DaysOfMonth = value;
   }
	
   /**
    * Sets the AWD Business Area field for the request.
    * 
    * @param value  Value that the AWD Business Area will be set to.
    */
   public final void setAWDBusinessArea( String value )
   {
      assertUnsent();
      _AWDBusinessArea = value;
   }
	
   /**
    * Sets the AWD Work Type field for the request.
    * 
    * @param value  Value that the AWD Work Type will be set to.
    */
   public final void setAWDWorkType( String value )
   {
      assertUnsent();
      _AWDWorkType = value;
   }
	
   /**
    * Sets the AWD Object Key field for the request.
    * 
    * @param value  Value that the AWD Object Key will be set to.
    */
   public final void setAWDObjectKey( String value )
   {
      assertUnsent();
      _AWDObjectKey = value;
   }
	
   /**
    * Sets the AWD Obj Date Time field for the request.
    * 
    * @param value  Value that the AWD Obj Date Time will be set to.
    */
   public final void setAWDObjDateTime( String value )
   {
      assertUnsent();
      _AWDObjDateTime = value;
   }
	
   /**
    * Sets the Override Unused  Max Amount field for the request.
    * 
    * @param value  Value that the Override Unused  Max Amount will be set to.
    */
   public final void setOverrideUnusedMax( Boolean value )
   {
      assertUnsent();
      _OverrideUnusedMax = value;
   }
	
   /**
    * Sets the PY Unused Maximun Amount field for the request.
    * 
    * @param value  Value that the PY Unused Maximun Amount will be set to.
    */
   public final void setPYUnusedMax( String value )
   {
      assertUnsent();
      _PYUnusedMax = value;
   }
	
   /**
    * Sets the External Assets field for the request.
    * 
    * @param value  Value that the External Assets will be set to.
    */
   public final void setExternalAssets( String value )
   {
      assertUnsent();
      _ExternalAssets = value;
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
      requestBuffer.appendField( _CompanyID );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _CallNum );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _MandAmtPay );
      requestBuffer.appendField( _MandAmtYr );
      requestBuffer.appendField( _MaxAmtYr );
      requestBuffer.appendField( _PayOption );
      requestBuffer.appendField( _SpouseBirth );
      requestBuffer.appendField( _Qualified );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _RecordType );
      requestBuffer.appendField( _GoodBad );
      requestBuffer.appendField( _EffectiveFrom );
      requestBuffer.appendField( _GrossOrNet );
      requestBuffer.appendField( _NetAmount );
      requestBuffer.appendField( _StopDate );
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
      requestBuffer.appendField( _SuppFedTax );
      requestBuffer.appendField( _FedRate );
      requestBuffer.appendField( _FedRatePUD );
      requestBuffer.appendField( _SuppProvTax );
      requestBuffer.appendField( _ProvRate );
      requestBuffer.appendField( _ProvRatePUD );
      requestBuffer.appendField( _TaxOnMin );
      requestBuffer.appendField( _OverrideAmtYr );
      requestBuffer.appendField( _LastProcDate );
      requestBuffer.appendField( _CalcFedProvTax );
      requestBuffer.appendField( _RIFId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _PrevYrBalPct );
      requestBuffer.appendField( _Frequency );
      requestBuffer.appendField( _DayOfWeek );
      requestBuffer.appendField( _DaysOfMonth );
      requestBuffer.appendField( _AWDBusinessArea );
      requestBuffer.appendField( _AWDWorkType );
      requestBuffer.appendField( _AWDObjectKey );
      requestBuffer.appendField( _AWDObjDateTime );
      requestBuffer.appendField( _OverrideUnusedMax );
      requestBuffer.appendField( _PYUnusedMax );
      requestBuffer.appendField( _ExternalAssets );
   }

}

