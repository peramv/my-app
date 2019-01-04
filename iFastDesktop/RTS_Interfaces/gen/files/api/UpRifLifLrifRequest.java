// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account RRIF/LIF/LRIF Details Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/UpRifLifLrif.doc">UpRifLifLrif.doc</A>.
 * 
 * @author RTS Generated
 */
public class UpRifLifLrifRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Record ID member variable.
    */
   private Integer _RIFId = null;
            
   /**
    * Suppress Federal Tax member variable.
    */
   private Boolean _SuppFedTax = new Boolean(false);
            
   /**
    * Suppress Provincial Tax member variable.
    */
   private Boolean _SuppProvTax = new Boolean(false);
            
   /**
    * Federal Tax Rate member variable.
    */
   private String _FedRate = "0";
            
   /**
    * Federal Tax Rate Unit member variable.
    */
   private String _FedRatePUD = "";
            
   /**
    * Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * Amount Type Code member variable.
    */
   private String _AmountType = "";
            
   /**
    * Amount Gross or Net (RIF/LIF/LRIF) member variable.
    */
   private String _GrossOrNet = "";
            
   /**
    * Provincial Tax Rate member variable.
    */
   private String _ProvRate = "0";
            
   /**
    * Provincial Tax Rate Unit member variable.
    */
   private String _ProvRatePUD = "";
            
   /**
    * Net Amount of Taxes member variable.
    */
   private String _NetAmount = "0";
            
   /**
    * Payment Type Code member variable.
    */
   private String _RIFPayType = "";
            
   /**
    * Payment Option member variable.
    */
   private String _PayOption = "";
            
   /**
    * Institution Code to debit member variable.
    */
   private Integer _InstCode = null;
            
   /**
    * Transit Code member variable.
    */
   private String _TransitCode = "";
            
   /**
    * Bank Account to debit member variable.
    */
   private String _BankAcctNum = "";
            
   /**
    * Tax calculation on Minimum Payment member variable.
    */
   private Boolean _TaxOnMin = new Boolean(false);
            
   /**
    * Maximum Payment Amount per Year member variable.
    */
   private String _MaxAmtYr = "0";
            
   /**
    * Mandatory Amount per Year member variable.
    */
   private String _MandAmtYr = "0";
            
   /**
    * Override Yearly Mandatory Amount member variable.
    */
   private Boolean _OverrideAmtYr = new Boolean(false);
            
   /**
    * Source of Fund member variable.
    */
   private String _RIFSrcOfFund = "";
            
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
    * RIF occurs at end of month member variable.
    */
   private Boolean _EndOfMonth = new Boolean(false);
            
   /**
    * Address Code member variable.
    */
   private String _AddrCode = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Index Rate member variable.
    */
   private String _IndexRate = "0";
            
   /**
    * Version of RRIF-Detail record member variable.
    */
   private Integer _RRIFDetlVer = null;
            
   /**
    * Account registered before 1993 member variable.
    */
   private Boolean _Qualified = new Boolean(false);
            
   /**
    * Batch Trace member variable.
    */
   private Integer _RRIFBatchTrace = null;
            
   /**
    * Spouse's Date of Birth member variable.
    */
   private Date _SpouseBirth = null;
            
   /**
    * Cansim Rate member variable.
    */
   private String _CansimRate = "0";
            
   /**
    * Set RIF/LIF/LRIF alloc as default member variable.
    */
   private Boolean _SetAsDefault = new Boolean(false);
            
   /**
    * Flag indication if RRIF rec was modified member variable.
    */
   private Boolean _RRIFModified = new Boolean(false);
            
   /**
    * Batch Name member variable.
    */
   private String _BatchName = "";
            
   /**
    * Batch Trace member variable.
    */
   private Integer _BatchTrace = null;
            
   /**
    * Batch Effective Date member variable.
    */
   private Date _BatchEffectiveDate = null;
            
            
            
   /**
    * Mand Amount per Pay member variable.
    */
   private String _MandAmtPay = "0";
            
   /**
    * Min withdrawal age member variable.
    */
   private Integer _MinWithAge = null;
            
   /**
    * Transfer Account member variable.
    */
   private String _TranAccount = "0";
            
   /**
    * Previous Year Balance Percent Rate member variable.
    */
   private String _PrevYrBalPct = "0";
            
   /**
    * Bank Type member variable.
    */
   private String _BankType = "";
            
   /**
    * Bank Contact member variable.
    */
   private String _BankContact = "";
            
   /**
    * Bank Country member variable.
    */
   private String _BankCntry = "";
            
   /**
    * Bank Postal Code member variable.
    */
   private String _BankPstl = "";
            
   /**
    * Bank Address Line 1 member variable.
    */
   private String _BankAddr1 = "";
            
   /**
    * Bank Address Line 2 member variable.
    */
   private String _BankAddr2 = "";
            
   /**
    * Bank Address Line 3 member variable.
    */
   private String _BankAddr3 = "";
            
   /**
    * Bank Addres Line 4 member variable.
    */
   private String _BankAddr4 = "";
            
   /**
    * Bank Address Line 5 member variable.
    */
   private String _BankAddr5 = "";
            
   /**
    * Bank ID Number member variable.
    */
   private String _BankIDNum = "";
            
   /**
    * Institution/ Bank Name member variable.
    */
   private String _InstName = "";
            
   /**
    * Set new RT alloc as default member variable.
    */
   private Boolean _SetRTAsDefault = new Boolean(false);
            
   /**
    * Override Unused Max member variable.
    */
   private Boolean _OverrideUnusedMax = new Boolean(false);
            
   /**
    * PY Unused Max member variable.
    */
   private String _PYUnusedMax = "0";
            
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
    * Date to determine year of plan member variable.
    */
   private Date _OrigPlanDeff = null;
            
   /**
    * External Assets member variable.
    */
   private String _ExternalAssets = "0";
            
   /**
    * Source Of Fund member variable.
    */
   private String _SrcOfFund = "";
            
   /**
    * Source Of Account member variable.
    */
   private String _SrcOfAccount = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Allocations Run Mode member array.
    */
   private String[] _AllocRunMode = new String[25];
            
   /**
    * Allocation Fund To Code member array.
    */
   private String[] _AllocFundToCode = new String[25];
            
   /**
    * Allocation Class To Code member array.
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
    * Distrib- Detl record Id member array.
    */
   private Integer[] _DistribDetlRid = new Integer[25];
            
   /**
    * RRIF Allocation Type (To or From) member array.
    */
   private String[] _RRIFAllocType = new String[25];
            

   /**
    * Constructs the UpRifLifLrifRequest object.
    * 
    */
   UpRifLifLrifRequest()
   {
      super ( 129 );
   }

   /**
    * Constructs the UpRifLifLrifRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   UpRifLifLrifRequest( String hostEncoding )
   {
      super ( 129, hostEncoding );
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
    * Sets the Record ID field for the request.
    * 
    * @param value  Value that the Record ID will be set to.
    */
   public final void setRIFId( Integer value )
   {
      assertUnsent();
      _RIFId = value;
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
    * Sets the Suppress Provincial Tax field for the request.
    * 
    * @param value  Value that the Suppress Provincial Tax will be set to.
    */
   public final void setSuppProvTax( Boolean value )
   {
      assertUnsent();
      _SuppProvTax = value;
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
    * Sets the Amount Gross or Net (RIF/LIF/LRIF) field for the request.
    * 
    * @param value  Value that the Amount Gross or Net (RIF/LIF/LRIF) will be set to.
    */
   public final void setGrossOrNet( String value )
   {
      assertUnsent();
      _GrossOrNet = value;
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
    * Sets the Net Amount of Taxes field for the request.
    * 
    * @param value  Value that the Net Amount of Taxes will be set to.
    */
   public final void setNetAmount( String value )
   {
      assertUnsent();
      _NetAmount = value;
   }
	
   /**
    * Sets the Payment Type Code field for the request.
    * 
    * @param value  Value that the Payment Type Code will be set to.
    */
   public final void setRIFPayType( String value )
   {
      assertUnsent();
      _RIFPayType = value;
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
    * Sets the Institution Code to debit field for the request.
    * 
    * @param value  Value that the Institution Code to debit will be set to.
    */
   public final void setInstCode( Integer value )
   {
      assertUnsent();
      _InstCode = value;
   }
	
   /**
    * Sets the Transit Code field for the request.
    * 
    * @param value  Value that the Transit Code will be set to.
    */
   public final void setTransitCode( String value )
   {
      assertUnsent();
      _TransitCode = value;
   }
	
   /**
    * Sets the Bank Account to debit field for the request.
    * 
    * @param value  Value that the Bank Account to debit will be set to.
    */
   public final void setBankAcctNum( String value )
   {
      assertUnsent();
      _BankAcctNum = value;
   }
	
   /**
    * Sets the Tax calculation on Minimum Payment field for the request.
    * 
    * @param value  Value that the Tax calculation on Minimum Payment will be set to.
    */
   public final void setTaxOnMin( Boolean value )
   {
      assertUnsent();
      _TaxOnMin = value;
   }
	
   /**
    * Sets the Maximum Payment Amount per Year field for the request.
    * 
    * @param value  Value that the Maximum Payment Amount per Year will be set to.
    */
   public final void setMaxAmtYr( String value )
   {
      assertUnsent();
      _MaxAmtYr = value;
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
    * Sets the Source of Fund field for the request.
    * 
    * @param value  Value that the Source of Fund will be set to.
    */
   public final void setRIFSrcOfFund( String value )
   {
      assertUnsent();
      _RIFSrcOfFund = value;
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
    * Sets the RIF occurs at end of month field for the request.
    * 
    * @param value  Value that the RIF occurs at end of month will be set to.
    */
   public final void setEndOfMonth( Boolean value )
   {
      assertUnsent();
      _EndOfMonth = value;
   }
	
   /**
    * Sets the Address Code field for the request.
    * 
    * @param value  Value that the Address Code will be set to.
    */
   public final void setAddrCode( String value )
   {
      assertUnsent();
      _AddrCode = value;
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
    * Sets the Index Rate field for the request.
    * 
    * @param value  Value that the Index Rate will be set to.
    */
   public final void setIndexRate( String value )
   {
      assertUnsent();
      _IndexRate = value;
   }
	
   /**
    * Sets the Version of RRIF-Detail record field for the request.
    * 
    * @param value  Value that the Version of RRIF-Detail record will be set to.
    */
   public final void setRRIFDetlVer( Integer value )
   {
      assertUnsent();
      _RRIFDetlVer = value;
   }
	
   /**
    * Sets the Account registered before 1993 field for the request.
    * 
    * @param value  Value that the Account registered before 1993 will be set to.
    */
   public final void setQualified( Boolean value )
   {
      assertUnsent();
      _Qualified = value;
   }
	
   /**
    * Sets the Batch Trace field for the request.
    * 
    * @param value  Value that the Batch Trace will be set to.
    */
   public final void setRRIFBatchTrace( Integer value )
   {
      assertUnsent();
      _RRIFBatchTrace = value;
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
    * Sets the Cansim Rate field for the request.
    * 
    * @param value  Value that the Cansim Rate will be set to.
    */
   public final void setCansimRate( String value )
   {
      assertUnsent();
      _CansimRate = value;
   }
	
   /**
    * Sets the Set RIF/LIF/LRIF alloc as default field for the request.
    * 
    * @param value  Value that the Set RIF/LIF/LRIF alloc as default will be set to.
    */
   public final void setSetAsDefault( Boolean value )
   {
      assertUnsent();
      _SetAsDefault = value;
   }
	
   /**
    * Sets the Flag indication if RRIF rec was modified field for the request.
    * 
    * @param value  Value that the Flag indication if RRIF rec was modified will be set to.
    */
   public final void setRRIFModified( Boolean value )
   {
      assertUnsent();
      _RRIFModified = value;
   }
	
   /**
    * Sets the Batch Name field for the request.
    * 
    * @param value  Value that the Batch Name will be set to.
    */
   public final void setBatchName( String value )
   {
      assertUnsent();
      _BatchName = value;
   }
	
   /**
    * Sets the Batch Trace field for the request.
    * 
    * @param value  Value that the Batch Trace will be set to.
    */
   public final void setBatchTrace( Integer value )
   {
      assertUnsent();
      _BatchTrace = value;
   }
	
   /**
    * Sets the Batch Effective Date field for the request.
    * 
    * @param value  Value that the Batch Effective Date will be set to.
    */
   public final void setBatchEffectiveDate( Date value )
   {
      assertUnsent();
      _BatchEffectiveDate = value;
   }
	
   /**
    * Sets the Mand Amount per Pay field for the request.
    * 
    * @param value  Value that the Mand Amount per Pay will be set to.
    */
   public final void setMandAmtPay( String value )
   {
      assertUnsent();
      _MandAmtPay = value;
   }
	
   /**
    * Sets the Min withdrawal age field for the request.
    * 
    * @param value  Value that the Min withdrawal age will be set to.
    */
   public final void setMinWithAge( Integer value )
   {
      assertUnsent();
      _MinWithAge = value;
   }
	
   /**
    * Sets the Transfer Account field for the request.
    * 
    * @param value  Value that the Transfer Account will be set to.
    */
   public final void setTranAccount( String value )
   {
      assertUnsent();
      _TranAccount = value;
   }
	
   /**
    * Sets the Previous Year Balance Percent Rate field for the request.
    * 
    * @param value  Value that the Previous Year Balance Percent Rate will be set to.
    */
   public final void setPrevYrBalPct( String value )
   {
      assertUnsent();
      _PrevYrBalPct = value;
   }
	
   /**
    * Sets the Bank Type field for the request.
    * 
    * @param value  Value that the Bank Type will be set to.
    */
   public final void setBankType( String value )
   {
      assertUnsent();
      _BankType = value;
   }
	
   /**
    * Sets the Bank Contact field for the request.
    * 
    * @param value  Value that the Bank Contact will be set to.
    */
   public final void setBankContact( String value )
   {
      assertUnsent();
      _BankContact = value;
   }
	
   /**
    * Sets the Bank Country field for the request.
    * 
    * @param value  Value that the Bank Country will be set to.
    */
   public final void setBankCntry( String value )
   {
      assertUnsent();
      _BankCntry = value;
   }
	
   /**
    * Sets the Bank Postal Code field for the request.
    * 
    * @param value  Value that the Bank Postal Code will be set to.
    */
   public final void setBankPstl( String value )
   {
      assertUnsent();
      _BankPstl = value;
   }
	
   /**
    * Sets the Bank Address Line 1 field for the request.
    * 
    * @param value  Value that the Bank Address Line 1 will be set to.
    */
   public final void setBankAddr1( String value )
   {
      assertUnsent();
      _BankAddr1 = value;
   }
	
   /**
    * Sets the Bank Address Line 2 field for the request.
    * 
    * @param value  Value that the Bank Address Line 2 will be set to.
    */
   public final void setBankAddr2( String value )
   {
      assertUnsent();
      _BankAddr2 = value;
   }
	
   /**
    * Sets the Bank Address Line 3 field for the request.
    * 
    * @param value  Value that the Bank Address Line 3 will be set to.
    */
   public final void setBankAddr3( String value )
   {
      assertUnsent();
      _BankAddr3 = value;
   }
	
   /**
    * Sets the Bank Addres Line 4 field for the request.
    * 
    * @param value  Value that the Bank Addres Line 4 will be set to.
    */
   public final void setBankAddr4( String value )
   {
      assertUnsent();
      _BankAddr4 = value;
   }
	
   /**
    * Sets the Bank Address Line 5 field for the request.
    * 
    * @param value  Value that the Bank Address Line 5 will be set to.
    */
   public final void setBankAddr5( String value )
   {
      assertUnsent();
      _BankAddr5 = value;
   }
	
   /**
    * Sets the Bank ID Number field for the request.
    * 
    * @param value  Value that the Bank ID Number will be set to.
    */
   public final void setBankIDNum( String value )
   {
      assertUnsent();
      _BankIDNum = value;
   }
	
   /**
    * Sets the Institution/ Bank Name field for the request.
    * 
    * @param value  Value that the Institution/ Bank Name will be set to.
    */
   public final void setInstName( String value )
   {
      assertUnsent();
      _InstName = value;
   }
	
   /**
    * Sets the Set new RT alloc as default field for the request.
    * 
    * @param value  Value that the Set new RT alloc as default will be set to.
    */
   public final void setSetRTAsDefault( Boolean value )
   {
      assertUnsent();
      _SetRTAsDefault = value;
   }
	
   /**
    * Sets the Override Unused Max field for the request.
    * 
    * @param value  Value that the Override Unused Max will be set to.
    */
   public final void setOverrideUnusedMax( Boolean value )
   {
      assertUnsent();
      _OverrideUnusedMax = value;
   }
	
   /**
    * Sets the PY Unused Max field for the request.
    * 
    * @param value  Value that the PY Unused Max will be set to.
    */
   public final void setPYUnusedMax( String value )
   {
      assertUnsent();
      _PYUnusedMax = value;
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
    * Sets the Date to determine year of plan field for the request.
    * 
    * @param value  Value that the Date to determine year of plan will be set to.
    */
   public final void setOrigPlanDeff( Date value )
   {
      assertUnsent();
      _OrigPlanDeff = value;
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
    * Sets the Source Of Fund field for the request.
    * 
    * @param value  Value that the Source Of Fund will be set to.
    */
   public final void setSrcOfFund( String value )
   {
      assertUnsent();
      _SrcOfFund = value;
   }
	
   /**
    * Sets the Source Of Account field for the request.
    * 
    * @param value  Value that the Source Of Account will be set to.
    */
   public final void setSrcOfAccount( String value )
   {
      assertUnsent();
      _SrcOfAccount = value;
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
    * Sets the Allocations Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocations Run Mode will be set to.
    */
   public final void setAllocRunMode( int index, String value )
   {
      assertUnsent();
      _AllocRunMode[index] = value;
   }
	
   /**
    * Sets the Allocation Fund To Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Fund To Code will be set to.
    */
   public final void setAllocFundToCode( int index, String value )
   {
      assertUnsent();
      _AllocFundToCode[index] = value;
   }
	
   /**
    * Sets the Allocation Class To Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Class To Code will be set to.
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
    * Sets the Distrib- Detl record Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distrib- Detl record Id will be set to.
    */
   public final void setDistribDetlRid( int index, Integer value )
   {
      assertUnsent();
      _DistribDetlRid[index] = value;
   }
	
   /**
    * Sets the RRIF Allocation Type (To or From) field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RRIF Allocation Type (To or From) will be set to.
    */
   public final void setRRIFAllocType( int index, String value )
   {
      assertUnsent();
      _RRIFAllocType[index] = value;
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
      requestBuffer.appendField( _RIFId );
      requestBuffer.appendField( _SuppFedTax );
      requestBuffer.appendField( _SuppProvTax );
      requestBuffer.appendField( _FedRate );
      requestBuffer.appendField( _FedRatePUD );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _GrossOrNet );
      requestBuffer.appendField( _ProvRate );
      requestBuffer.appendField( _ProvRatePUD );
      requestBuffer.appendField( _NetAmount );
      requestBuffer.appendField( _RIFPayType );
      requestBuffer.appendField( _PayOption );
      requestBuffer.appendField( _InstCode );
      requestBuffer.appendField( _TransitCode );
      requestBuffer.appendField( _BankAcctNum );
      requestBuffer.appendField( _TaxOnMin );
      requestBuffer.appendField( _MaxAmtYr );
      requestBuffer.appendField( _MandAmtYr );
      requestBuffer.appendField( _OverrideAmtYr );
      requestBuffer.appendField( _RIFSrcOfFund );
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
      requestBuffer.appendField( _EndOfMonth );
      requestBuffer.appendField( _AddrCode );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _IndexRate );
      requestBuffer.appendField( _RRIFDetlVer );
      requestBuffer.appendField( _Qualified );
      requestBuffer.appendField( _RRIFBatchTrace );
      requestBuffer.appendField( _SpouseBirth );
      requestBuffer.appendField( _CansimRate );
      requestBuffer.appendField( _SetAsDefault );
      requestBuffer.appendField( _RRIFModified );
      requestBuffer.appendField( _BatchName );
      requestBuffer.appendField( _BatchTrace );
      requestBuffer.appendField( _BatchEffectiveDate );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _MandAmtPay );
      requestBuffer.appendField( _MinWithAge );
      requestBuffer.appendField( _TranAccount );
      requestBuffer.appendField( _PrevYrBalPct );
      requestBuffer.appendField( _BankType );
      requestBuffer.appendField( _BankContact );
      requestBuffer.appendField( _BankCntry );
      requestBuffer.appendField( _BankPstl );
      requestBuffer.appendField( _BankAddr1 );
      requestBuffer.appendField( _BankAddr2 );
      requestBuffer.appendField( _BankAddr3 );
      requestBuffer.appendField( _BankAddr4 );
      requestBuffer.appendField( _BankAddr5 );
      requestBuffer.appendField( _BankIDNum );
      requestBuffer.appendField( _InstName );
      requestBuffer.appendField( _SetRTAsDefault );
      requestBuffer.appendField( _OverrideUnusedMax );
      requestBuffer.appendField( _PYUnusedMax );
      requestBuffer.appendField( _Frequency );
      requestBuffer.appendField( _DayOfWeek );
      requestBuffer.appendField( _DaysOfMonth );
      requestBuffer.appendField( _AWDBusinessArea );
      requestBuffer.appendField( _AWDWorkType );
      requestBuffer.appendField( _AWDObjectKey );
      requestBuffer.appendField( _AWDObjDateTime );
      requestBuffer.appendField( _OrigPlanDeff );
      requestBuffer.appendField( _ExternalAssets );
      requestBuffer.appendField( _SrcOfFund );
      requestBuffer.appendField( _SrcOfAccount );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _AllocRunMode[x] );
         requestBuffer.appendField( _AllocFundToCode[x] );
         requestBuffer.appendField( _AllocClassToCode[x] );
         requestBuffer.appendField( _AllocPercentage[x] );
         requestBuffer.appendField( _AllocAmount[x] );
         requestBuffer.appendField( _DistribDetlRid[x] );
         requestBuffer.appendField( _RRIFAllocType[x] );
      }
   }

}

