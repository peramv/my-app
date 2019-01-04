
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Tax Type Rule view.
 * For additional view information see <A HREF="../../../../viewspecs/TaxTypeRules.doc">TaxTypeRules.doc</A>.
 * 
 * @author RTS Generated
 */
public class TaxTypeRulesView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Tax Type Description member array.
    */
   private String[] _TaxTypeDesc = null;
   
   /**
    * Plan Type member array.
    */
   private String[] _PlanType = null;
   
   /**
    * Plan Type Description member array.
    */
   private String[] _PlanTypeDesc = null;
   
   /**
    * Valid Account Types member array.
    */
   private String[] _AccountTypes = null;
   
   /**
    * External or Self Directed member array.
    */
   private Boolean[] _SelfDirected = null;
   
   /**
    * List of valid 'to' Tax Types for transfers member array.
    */
   private String[] _TransferTypes = null;
   
   /**
    * Locked In member array.
    */
   private Boolean[] _LockedIn = null;
   
   /**
    * Taxation by Jurisdiction member array.
    */
   private Boolean[] _TaxByJuris = null;
   
   /**
    * Is Federal Jurisdiction allowed member array.
    */
   private Boolean[] _FedJurisAllowed = null;
   
   /**
    * Is Certificate required member array.
    */
   private Boolean[] _Certificate = null;
   
   /**
    * Is receipt required for Nominee member array.
    */
   private Boolean[] _NomTaxRcpt = null;
   
   /**
    * Legislative unseizable status member array.
    */
   private Boolean[] _Unseizable = null;
   
   /**
    * Available for non-Residents member array.
    */
   private Boolean[] _AvailNonRes = null;
   
   /**
    * For Reinvested Dividends only member array.
    */
   private Boolean[] _ReinDistOnly = null;
   
   /**
    * Minimum Applies member array.
    */
   private Boolean[] _MinimumApplies = null;
   
   /**
    * Maximum Applies member array.
    */
   private Boolean[] _MaximumApplies = null;
   
   /**
    * GIC Allowed member array.
    */
   private Boolean[] _GICallowed = null;
   
   /**
    * PAC Allowed member array.
    */
   private Boolean[] _PACallowed = null;
   
   /**
    * SWPallowed member array.
    */
   private Boolean[] _SWPallowed = null;
   
   /**
    * Admin Fee Code member array.
    */
   private String[] _AdminFeeDefn = null;
   
   /**
    * Address Code for default Mailing for Jan member array.
    */
   private String[] _MailList1 = null;
   
   /**
    * Address Code for default Mailing for Feb member array.
    */
   private String[] _MailList2 = null;
   
   /**
    * Address Code for default Mailing for Mar member array.
    */
   private String[] _MailList3 = null;
   
   /**
    * Address Code for default Mailing for Apr member array.
    */
   private String[] _MailList4 = null;
   
   /**
    * Address Code for default Mailing for May member array.
    */
   private String[] _MailList5 = null;
   
   /**
    * Address Code for default Mailing for Jun member array.
    */
   private String[] _MailList6 = null;
   
   /**
    * Address Code for default Mailing for Jul member array.
    */
   private String[] _MailList7 = null;
   
   /**
    * Address Code for default Mailing for Aug member array.
    */
   private String[] _MailList8 = null;
   
   /**
    * Address Code for default Mailing for Sep member array.
    */
   private String[] _MailList9 = null;
   
   /**
    * Address Code for default Mailing for Oct member array.
    */
   private String[] _MailList10 = null;
   
   /**
    * Address Code for default Mailing for Nov member array.
    */
   private String[] _MailList11 = null;
   
   /**
    * Address Code for default Mailing for Dec member array.
    */
   private String[] _MailList12 = null;
   
   /**
    * Is Cash Distrib Taxable for Residents member array.
    */
   private Boolean[] _TaxCashDist1 = null;
   
   /**
    * Is Cash Distrib Taxabl for non- Residents member array.
    */
   private Boolean[] _TaxCashDist2 = null;
   
   /**
    * Is Cash Distrib Taxable for Nominees member array.
    */
   private Boolean[] _TaxCashDist3 = null;
   
   /**
    * Tax Early Collaps for Residents member array.
    */
   private Boolean[] _TaxEarlyClose1 = null;
   
   /**
    * Tax Early Collaps for non-Residents member array.
    */
   private Boolean[] _TaxEarlyClose2 = null;
   
   /**
    * Tax Early Collaps for Nominees member array.
    */
   private Boolean[] _TaxEarlyClose3 = null;
   
   /**
    * Is Full Redempt taxable for Residents member array.
    */
   private Boolean[] _TaxFullRdmp1 = null;
   
   /**
    * Is Full Redempt taxable for non-Resident member array.
    */
   private Boolean[] _TaxFullRdmp2 = null;
   
   /**
    * Is Full Redempt taxable for Nominees member array.
    */
   private Boolean[] _TaxFullRdmp3 = null;
   
   /**
    * Is notional Distrib taxable for Residents member array.
    */
   private Boolean[] _TaxNotional1 = null;
   
   /**
    * Is notional Distrib taxable for  non-Resid member array.
    */
   private Boolean[] _TaxNotional2 = null;
   
   /**
    * Is notional Distrib taxable for Nominees member array.
    */
   private Boolean[] _TaxNotional3 = null;
   
   /**
    * Is partial Redempt taxable for Residents member array.
    */
   private Boolean[] _TaxPartRdmp1 = null;
   
   /**
    * Is partial Redempt taxable for non-Resid member array.
    */
   private Boolean[] _TaxPartRdmp2 = null;
   
   /**
    * Is partial Redempt taxable for Residents member array.
    */
   private Boolean[] _TaxPartRdmp3 = null;
   
   /**
    * Is Purchase taxable for Residents member array.
    */
   private Boolean[] _TaxPurchase1 = null;
   
   /**
    * Is Purchase taxable for non-Residents member array.
    */
   private Boolean[] _TaxPurchase2 = null;
   
   /**
    * Is Purchase taxable for Nominees member array.
    */
   private Boolean[] _TaxPurchase3 = null;
   
   /**
    * Is Reinv Distr taxable for Residents member array.
    */
   private Boolean[] _TaxReinvDist1 = null;
   
   /**
    * Is Reinv Distr taxable for non-Residents member array.
    */
   private Boolean[] _TaxReinvDist2 = null;
   
   /**
    * Is Reinv Distr taxable for Nominees member array.
    */
   private Boolean[] _TaxReinvDist3 = null;
   
   /**
    * Are Switches taxable for Residents member array.
    */
   private Boolean[] _TaxSwitches1 = null;
   
   /**
    * Are Switches taxable for non-Residents member array.
    */
   private Boolean[] _TaxSwitches2 = null;
   
   /**
    * Are Switches taxable for Nominees member array.
    */
   private Boolean[] _TaxSwitches3 = null;
   
   /**
    * Is transfer taxable for Residents member array.
    */
   private Boolean[] _TaxTransfers1 = null;
   
   /**
    * Is transfer taxable for non-Residents member array.
    */
   private Boolean[] _TaxTransfers2 = null;
   
   /**
    * Is transfer taxable for Nominees member array.
    */
   private Boolean[] _TaxTransfers3 = null;
   
   /**
    * Client Equivalent member array.
    */
   private String[] _ClientEquiv = null;
   
   /**
    * List of allowable deposit types member array.
    */
   private String[] _DepositTypes = null;
   
   /**
    * List of allowable red codes member array.
    */
   private String[] _RedCodes = null;
   
   /**
    * Account Designation member array.
    */
   private String[] _AcctDesignation = null;
   
   /**
    * ExclDTAAcctType member array.
    */
   private String[] _ExclDTAAcctType = null;
   
   /**
    * Tax Type Schedule member array.
    */
   private String[] _TaxTypeSchedule = null;
   
   /**
    * SINRequired member array.
    */
   private String[] _SINRequired = null;
   
   /**
    * MinAge member array.
    */
   private Integer[] _MinAge = null;
   
   /**
    * MaxAge member array.
    */
   private Integer[] _MaxAge = null;
   
   /**
    * TradeStartDate member array.
    */
   private Date[] _TradeStartDate = null;
   
   /**
    * TradeStopDate member array.
    */
   private Date[] _TradeStopDate = null;
   
   /**
    * Tax Types Settlement Currency member array.
    */
   private String[] _TaxTypeRuleCurrSet = null;
   
   /**
    * Maximum Fee Applicable member array.
    */
   private Boolean[] _MaxFeeAppl = null;
   
   /**
    * Maximum Fee member array.
    */
   private String[] _MaxFee = null;
   

   /**
    * Constructs the TaxTypeRulesView object.
    * 
    */
   public TaxTypeRulesView()
   {
      super ( new TaxTypeRulesRequest() );
   }

   /**
    * Constructs the TaxTypeRulesView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TaxTypeRulesView( String hostEncoding )
   {
      super ( new TaxTypeRulesRequest( hostEncoding ) );
   }

   /**
    * Gets the TaxTypeRulesRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TaxTypeRulesRequest object.
    */
   public final TaxTypeRulesRequest getRequest()
   {
      return (TaxTypeRulesRequest)getIFastRequest();
   }
        
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRepeatCount()
   {
      return _RepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RepeatCount += receivedRecordCount;
   }

   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type or null.
    */
   public final String getTaxType( int index )
   {
      return _TaxType[index];
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type or the specified default value.
    */
   public final String getTaxType( int index, String defaultValue )
   {
      return _TaxType[index] == null ? defaultValue : _TaxType[index];
   }
    
   /**
    * Gets the array of Tax Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type values.
    */
   public final String[] getTaxTypeArray()
   {
      return _TaxType;
   }
    
   /**
    * Gets the Tax Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type Description or null.
    */
   public final String getTaxTypeDesc( int index )
   {
      return _TaxTypeDesc[index];
   }
    
   /**
    * Gets the Tax Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type Description or the specified default value.
    */
   public final String getTaxTypeDesc( int index, String defaultValue )
   {
      return _TaxTypeDesc[index] == null ? defaultValue : _TaxTypeDesc[index];
   }
    
   /**
    * Gets the array of Tax Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type Description values.
    */
   public final String[] getTaxTypeDescArray()
   {
      return _TaxTypeDesc;
   }
    
   /**
    * Gets the Plan Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Plan Type or null.
    */
   public final String getPlanType( int index )
   {
      return _PlanType[index];
   }
    
   /**
    * Gets the Plan Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Plan Type or the specified default value.
    */
   public final String getPlanType( int index, String defaultValue )
   {
      return _PlanType[index] == null ? defaultValue : _PlanType[index];
   }
    
   /**
    * Gets the array of Plan Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Plan Type values.
    */
   public final String[] getPlanTypeArray()
   {
      return _PlanType;
   }
    
   /**
    * Gets the Plan Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Plan Type Description or null.
    */
   public final String getPlanTypeDesc( int index )
   {
      return _PlanTypeDesc[index];
   }
    
   /**
    * Gets the Plan Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Plan Type Description or the specified default value.
    */
   public final String getPlanTypeDesc( int index, String defaultValue )
   {
      return _PlanTypeDesc[index] == null ? defaultValue : _PlanTypeDesc[index];
   }
    
   /**
    * Gets the array of Plan Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Plan Type Description values.
    */
   public final String[] getPlanTypeDescArray()
   {
      return _PlanTypeDesc;
   }
    
   /**
    * Gets the Valid Account Types field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Valid Account Types or null.
    */
   public final String getAccountTypes( int index )
   {
      return _AccountTypes[index];
   }
    
   /**
    * Gets the Valid Account Types field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valid Account Types or the specified default value.
    */
   public final String getAccountTypes( int index, String defaultValue )
   {
      return _AccountTypes[index] == null ? defaultValue : _AccountTypes[index];
   }
    
   /**
    * Gets the array of Valid Account Types fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Valid Account Types values.
    */
   public final String[] getAccountTypesArray()
   {
      return _AccountTypes;
   }
    
   /**
    * Gets the External or Self Directed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the External or Self Directed or null.
    */
   public final Boolean getSelfDirected( int index )
   {
      return _SelfDirected[index];
   }
    
   /**
    * Gets the External or Self Directed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the External or Self Directed or the specified default value.
    */
   public final boolean getSelfDirected( int index, boolean defaultValue )
   {
      return _SelfDirected[index] == null ? defaultValue : _SelfDirected[index].booleanValue();
   }
    
   /**
    * Gets the array of External or Self Directed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of External or Self Directed values.
    */
   public final Boolean[] getSelfDirectedArray()
   {
      return _SelfDirected;
   }
    
   /**
    * Gets the List of valid 'to' Tax Types for transfers field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the List of valid 'to' Tax Types for transfers or null.
    */
   public final String getTransferTypes( int index )
   {
      return _TransferTypes[index];
   }
    
   /**
    * Gets the List of valid 'to' Tax Types for transfers field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the List of valid 'to' Tax Types for transfers or the specified default value.
    */
   public final String getTransferTypes( int index, String defaultValue )
   {
      return _TransferTypes[index] == null ? defaultValue : _TransferTypes[index];
   }
    
   /**
    * Gets the array of List of valid 'to' Tax Types for transfers fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of List of valid 'to' Tax Types for transfers values.
    */
   public final String[] getTransferTypesArray()
   {
      return _TransferTypes;
   }
    
   /**
    * Gets the Locked In field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Locked In or null.
    */
   public final Boolean getLockedIn( int index )
   {
      return _LockedIn[index];
   }
    
   /**
    * Gets the Locked In field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Locked In or the specified default value.
    */
   public final boolean getLockedIn( int index, boolean defaultValue )
   {
      return _LockedIn[index] == null ? defaultValue : _LockedIn[index].booleanValue();
   }
    
   /**
    * Gets the array of Locked In fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Locked In values.
    */
   public final Boolean[] getLockedInArray()
   {
      return _LockedIn;
   }
    
   /**
    * Gets the Taxation by Jurisdiction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Taxation by Jurisdiction or null.
    */
   public final Boolean getTaxByJuris( int index )
   {
      return _TaxByJuris[index];
   }
    
   /**
    * Gets the Taxation by Jurisdiction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Taxation by Jurisdiction or the specified default value.
    */
   public final boolean getTaxByJuris( int index, boolean defaultValue )
   {
      return _TaxByJuris[index] == null ? defaultValue : _TaxByJuris[index].booleanValue();
   }
    
   /**
    * Gets the array of Taxation by Jurisdiction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Taxation by Jurisdiction values.
    */
   public final Boolean[] getTaxByJurisArray()
   {
      return _TaxByJuris;
   }
    
   /**
    * Gets the Is Federal Jurisdiction allowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Federal Jurisdiction allowed or null.
    */
   public final Boolean getFedJurisAllowed( int index )
   {
      return _FedJurisAllowed[index];
   }
    
   /**
    * Gets the Is Federal Jurisdiction allowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Federal Jurisdiction allowed or the specified default value.
    */
   public final boolean getFedJurisAllowed( int index, boolean defaultValue )
   {
      return _FedJurisAllowed[index] == null ? defaultValue : _FedJurisAllowed[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Federal Jurisdiction allowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Federal Jurisdiction allowed values.
    */
   public final Boolean[] getFedJurisAllowedArray()
   {
      return _FedJurisAllowed;
   }
    
   /**
    * Gets the Is Certificate required field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Certificate required or null.
    */
   public final Boolean getCertificate( int index )
   {
      return _Certificate[index];
   }
    
   /**
    * Gets the Is Certificate required field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Certificate required or the specified default value.
    */
   public final boolean getCertificate( int index, boolean defaultValue )
   {
      return _Certificate[index] == null ? defaultValue : _Certificate[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Certificate required fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Certificate required values.
    */
   public final Boolean[] getCertificateArray()
   {
      return _Certificate;
   }
    
   /**
    * Gets the Is receipt required for Nominee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is receipt required for Nominee or null.
    */
   public final Boolean getNomTaxRcpt( int index )
   {
      return _NomTaxRcpt[index];
   }
    
   /**
    * Gets the Is receipt required for Nominee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is receipt required for Nominee or the specified default value.
    */
   public final boolean getNomTaxRcpt( int index, boolean defaultValue )
   {
      return _NomTaxRcpt[index] == null ? defaultValue : _NomTaxRcpt[index].booleanValue();
   }
    
   /**
    * Gets the array of Is receipt required for Nominee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is receipt required for Nominee values.
    */
   public final Boolean[] getNomTaxRcptArray()
   {
      return _NomTaxRcpt;
   }
    
   /**
    * Gets the Legislative unseizable status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Legislative unseizable status or null.
    */
   public final Boolean getUnseizable( int index )
   {
      return _Unseizable[index];
   }
    
   /**
    * Gets the Legislative unseizable status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Legislative unseizable status or the specified default value.
    */
   public final boolean getUnseizable( int index, boolean defaultValue )
   {
      return _Unseizable[index] == null ? defaultValue : _Unseizable[index].booleanValue();
   }
    
   /**
    * Gets the array of Legislative unseizable status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Legislative unseizable status values.
    */
   public final Boolean[] getUnseizableArray()
   {
      return _Unseizable;
   }
    
   /**
    * Gets the Available for non-Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Available for non-Residents or null.
    */
   public final Boolean getAvailNonRes( int index )
   {
      return _AvailNonRes[index];
   }
    
   /**
    * Gets the Available for non-Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Available for non-Residents or the specified default value.
    */
   public final boolean getAvailNonRes( int index, boolean defaultValue )
   {
      return _AvailNonRes[index] == null ? defaultValue : _AvailNonRes[index].booleanValue();
   }
    
   /**
    * Gets the array of Available for non-Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Available for non-Residents values.
    */
   public final Boolean[] getAvailNonResArray()
   {
      return _AvailNonRes;
   }
    
   /**
    * Gets the For Reinvested Dividends only field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the For Reinvested Dividends only or null.
    */
   public final Boolean getReinDistOnly( int index )
   {
      return _ReinDistOnly[index];
   }
    
   /**
    * Gets the For Reinvested Dividends only field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the For Reinvested Dividends only or the specified default value.
    */
   public final boolean getReinDistOnly( int index, boolean defaultValue )
   {
      return _ReinDistOnly[index] == null ? defaultValue : _ReinDistOnly[index].booleanValue();
   }
    
   /**
    * Gets the array of For Reinvested Dividends only fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of For Reinvested Dividends only values.
    */
   public final Boolean[] getReinDistOnlyArray()
   {
      return _ReinDistOnly;
   }
    
   /**
    * Gets the Minimum Applies field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Applies or null.
    */
   public final Boolean getMinimumApplies( int index )
   {
      return _MinimumApplies[index];
   }
    
   /**
    * Gets the Minimum Applies field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Applies or the specified default value.
    */
   public final boolean getMinimumApplies( int index, boolean defaultValue )
   {
      return _MinimumApplies[index] == null ? defaultValue : _MinimumApplies[index].booleanValue();
   }
    
   /**
    * Gets the array of Minimum Applies fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Applies values.
    */
   public final Boolean[] getMinimumAppliesArray()
   {
      return _MinimumApplies;
   }
    
   /**
    * Gets the Maximum Applies field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maximum Applies or null.
    */
   public final Boolean getMaximumApplies( int index )
   {
      return _MaximumApplies[index];
   }
    
   /**
    * Gets the Maximum Applies field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Applies or the specified default value.
    */
   public final boolean getMaximumApplies( int index, boolean defaultValue )
   {
      return _MaximumApplies[index] == null ? defaultValue : _MaximumApplies[index].booleanValue();
   }
    
   /**
    * Gets the array of Maximum Applies fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maximum Applies values.
    */
   public final Boolean[] getMaximumAppliesArray()
   {
      return _MaximumApplies;
   }
    
   /**
    * Gets the GIC Allowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GIC Allowed or null.
    */
   public final Boolean getGICallowed( int index )
   {
      return _GICallowed[index];
   }
    
   /**
    * Gets the GIC Allowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GIC Allowed or the specified default value.
    */
   public final boolean getGICallowed( int index, boolean defaultValue )
   {
      return _GICallowed[index] == null ? defaultValue : _GICallowed[index].booleanValue();
   }
    
   /**
    * Gets the array of GIC Allowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GIC Allowed values.
    */
   public final Boolean[] getGICallowedArray()
   {
      return _GICallowed;
   }
    
   /**
    * Gets the PAC Allowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PAC Allowed or null.
    */
   public final Boolean getPACallowed( int index )
   {
      return _PACallowed[index];
   }
    
   /**
    * Gets the PAC Allowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC Allowed or the specified default value.
    */
   public final boolean getPACallowed( int index, boolean defaultValue )
   {
      return _PACallowed[index] == null ? defaultValue : _PACallowed[index].booleanValue();
   }
    
   /**
    * Gets the array of PAC Allowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PAC Allowed values.
    */
   public final Boolean[] getPACallowedArray()
   {
      return _PACallowed;
   }
    
   /**
    * Gets the SWPallowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SWPallowed or null.
    */
   public final Boolean getSWPallowed( int index )
   {
      return _SWPallowed[index];
   }
    
   /**
    * Gets the SWPallowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SWPallowed or the specified default value.
    */
   public final boolean getSWPallowed( int index, boolean defaultValue )
   {
      return _SWPallowed[index] == null ? defaultValue : _SWPallowed[index].booleanValue();
   }
    
   /**
    * Gets the array of SWPallowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SWPallowed values.
    */
   public final Boolean[] getSWPallowedArray()
   {
      return _SWPallowed;
   }
    
   /**
    * Gets the Admin Fee Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Admin Fee Code or null.
    */
   public final String getAdminFeeDefn( int index )
   {
      return _AdminFeeDefn[index];
   }
    
   /**
    * Gets the Admin Fee Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Admin Fee Code or the specified default value.
    */
   public final String getAdminFeeDefn( int index, String defaultValue )
   {
      return _AdminFeeDefn[index] == null ? defaultValue : _AdminFeeDefn[index];
   }
    
   /**
    * Gets the array of Admin Fee Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Admin Fee Code values.
    */
   public final String[] getAdminFeeDefnArray()
   {
      return _AdminFeeDefn;
   }
    
   /**
    * Gets the Address Code for default Mailing for Jan field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for Jan or null.
    */
   public final String getMailList1( int index )
   {
      return _MailList1[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for Jan field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for Jan or the specified default value.
    */
   public final String getMailList1( int index, String defaultValue )
   {
      return _MailList1[index] == null ? defaultValue : _MailList1[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for Jan fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for Jan values.
    */
   public final String[] getMailList1Array()
   {
      return _MailList1;
   }
    
   /**
    * Gets the Address Code for default Mailing for Feb field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for Feb or null.
    */
   public final String getMailList2( int index )
   {
      return _MailList2[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for Feb field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for Feb or the specified default value.
    */
   public final String getMailList2( int index, String defaultValue )
   {
      return _MailList2[index] == null ? defaultValue : _MailList2[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for Feb fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for Feb values.
    */
   public final String[] getMailList2Array()
   {
      return _MailList2;
   }
    
   /**
    * Gets the Address Code for default Mailing for Mar field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for Mar or null.
    */
   public final String getMailList3( int index )
   {
      return _MailList3[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for Mar field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for Mar or the specified default value.
    */
   public final String getMailList3( int index, String defaultValue )
   {
      return _MailList3[index] == null ? defaultValue : _MailList3[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for Mar fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for Mar values.
    */
   public final String[] getMailList3Array()
   {
      return _MailList3;
   }
    
   /**
    * Gets the Address Code for default Mailing for Apr field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for Apr or null.
    */
   public final String getMailList4( int index )
   {
      return _MailList4[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for Apr field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for Apr or the specified default value.
    */
   public final String getMailList4( int index, String defaultValue )
   {
      return _MailList4[index] == null ? defaultValue : _MailList4[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for Apr fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for Apr values.
    */
   public final String[] getMailList4Array()
   {
      return _MailList4;
   }
    
   /**
    * Gets the Address Code for default Mailing for May field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for May or null.
    */
   public final String getMailList5( int index )
   {
      return _MailList5[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for May field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for May or the specified default value.
    */
   public final String getMailList5( int index, String defaultValue )
   {
      return _MailList5[index] == null ? defaultValue : _MailList5[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for May fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for May values.
    */
   public final String[] getMailList5Array()
   {
      return _MailList5;
   }
    
   /**
    * Gets the Address Code for default Mailing for Jun field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for Jun or null.
    */
   public final String getMailList6( int index )
   {
      return _MailList6[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for Jun field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for Jun or the specified default value.
    */
   public final String getMailList6( int index, String defaultValue )
   {
      return _MailList6[index] == null ? defaultValue : _MailList6[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for Jun fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for Jun values.
    */
   public final String[] getMailList6Array()
   {
      return _MailList6;
   }
    
   /**
    * Gets the Address Code for default Mailing for Jul field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for Jul or null.
    */
   public final String getMailList7( int index )
   {
      return _MailList7[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for Jul field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for Jul or the specified default value.
    */
   public final String getMailList7( int index, String defaultValue )
   {
      return _MailList7[index] == null ? defaultValue : _MailList7[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for Jul fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for Jul values.
    */
   public final String[] getMailList7Array()
   {
      return _MailList7;
   }
    
   /**
    * Gets the Address Code for default Mailing for Aug field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for Aug or null.
    */
   public final String getMailList8( int index )
   {
      return _MailList8[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for Aug field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for Aug or the specified default value.
    */
   public final String getMailList8( int index, String defaultValue )
   {
      return _MailList8[index] == null ? defaultValue : _MailList8[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for Aug fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for Aug values.
    */
   public final String[] getMailList8Array()
   {
      return _MailList8;
   }
    
   /**
    * Gets the Address Code for default Mailing for Sep field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for Sep or null.
    */
   public final String getMailList9( int index )
   {
      return _MailList9[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for Sep field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for Sep or the specified default value.
    */
   public final String getMailList9( int index, String defaultValue )
   {
      return _MailList9[index] == null ? defaultValue : _MailList9[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for Sep fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for Sep values.
    */
   public final String[] getMailList9Array()
   {
      return _MailList9;
   }
    
   /**
    * Gets the Address Code for default Mailing for Oct field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for Oct or null.
    */
   public final String getMailList10( int index )
   {
      return _MailList10[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for Oct field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for Oct or the specified default value.
    */
   public final String getMailList10( int index, String defaultValue )
   {
      return _MailList10[index] == null ? defaultValue : _MailList10[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for Oct fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for Oct values.
    */
   public final String[] getMailList10Array()
   {
      return _MailList10;
   }
    
   /**
    * Gets the Address Code for default Mailing for Nov field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for Nov or null.
    */
   public final String getMailList11( int index )
   {
      return _MailList11[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for Nov field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for Nov or the specified default value.
    */
   public final String getMailList11( int index, String defaultValue )
   {
      return _MailList11[index] == null ? defaultValue : _MailList11[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for Nov fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for Nov values.
    */
   public final String[] getMailList11Array()
   {
      return _MailList11;
   }
    
   /**
    * Gets the Address Code for default Mailing for Dec field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code for default Mailing for Dec or null.
    */
   public final String getMailList12( int index )
   {
      return _MailList12[index];
   }
    
   /**
    * Gets the Address Code for default Mailing for Dec field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code for default Mailing for Dec or the specified default value.
    */
   public final String getMailList12( int index, String defaultValue )
   {
      return _MailList12[index] == null ? defaultValue : _MailList12[index];
   }
    
   /**
    * Gets the array of Address Code for default Mailing for Dec fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code for default Mailing for Dec values.
    */
   public final String[] getMailList12Array()
   {
      return _MailList12;
   }
    
   /**
    * Gets the Is Cash Distrib Taxable for Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Cash Distrib Taxable for Residents or null.
    */
   public final Boolean getTaxCashDist1( int index )
   {
      return _TaxCashDist1[index];
   }
    
   /**
    * Gets the Is Cash Distrib Taxable for Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Cash Distrib Taxable for Residents or the specified default value.
    */
   public final boolean getTaxCashDist1( int index, boolean defaultValue )
   {
      return _TaxCashDist1[index] == null ? defaultValue : _TaxCashDist1[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Cash Distrib Taxable for Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Cash Distrib Taxable for Residents values.
    */
   public final Boolean[] getTaxCashDist1Array()
   {
      return _TaxCashDist1;
   }
    
   /**
    * Gets the Is Cash Distrib Taxabl for non- Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Cash Distrib Taxabl for non- Residents or null.
    */
   public final Boolean getTaxCashDist2( int index )
   {
      return _TaxCashDist2[index];
   }
    
   /**
    * Gets the Is Cash Distrib Taxabl for non- Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Cash Distrib Taxabl for non- Residents or the specified default value.
    */
   public final boolean getTaxCashDist2( int index, boolean defaultValue )
   {
      return _TaxCashDist2[index] == null ? defaultValue : _TaxCashDist2[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Cash Distrib Taxabl for non- Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Cash Distrib Taxabl for non- Residents values.
    */
   public final Boolean[] getTaxCashDist2Array()
   {
      return _TaxCashDist2;
   }
    
   /**
    * Gets the Is Cash Distrib Taxable for Nominees field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Cash Distrib Taxable for Nominees or null.
    */
   public final Boolean getTaxCashDist3( int index )
   {
      return _TaxCashDist3[index];
   }
    
   /**
    * Gets the Is Cash Distrib Taxable for Nominees field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Cash Distrib Taxable for Nominees or the specified default value.
    */
   public final boolean getTaxCashDist3( int index, boolean defaultValue )
   {
      return _TaxCashDist3[index] == null ? defaultValue : _TaxCashDist3[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Cash Distrib Taxable for Nominees fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Cash Distrib Taxable for Nominees values.
    */
   public final Boolean[] getTaxCashDist3Array()
   {
      return _TaxCashDist3;
   }
    
   /**
    * Gets the Tax Early Collaps for Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Early Collaps for Residents or null.
    */
   public final Boolean getTaxEarlyClose1( int index )
   {
      return _TaxEarlyClose1[index];
   }
    
   /**
    * Gets the Tax Early Collaps for Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Early Collaps for Residents or the specified default value.
    */
   public final boolean getTaxEarlyClose1( int index, boolean defaultValue )
   {
      return _TaxEarlyClose1[index] == null ? defaultValue : _TaxEarlyClose1[index].booleanValue();
   }
    
   /**
    * Gets the array of Tax Early Collaps for Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Early Collaps for Residents values.
    */
   public final Boolean[] getTaxEarlyClose1Array()
   {
      return _TaxEarlyClose1;
   }
    
   /**
    * Gets the Tax Early Collaps for non-Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Early Collaps for non-Residents or null.
    */
   public final Boolean getTaxEarlyClose2( int index )
   {
      return _TaxEarlyClose2[index];
   }
    
   /**
    * Gets the Tax Early Collaps for non-Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Early Collaps for non-Residents or the specified default value.
    */
   public final boolean getTaxEarlyClose2( int index, boolean defaultValue )
   {
      return _TaxEarlyClose2[index] == null ? defaultValue : _TaxEarlyClose2[index].booleanValue();
   }
    
   /**
    * Gets the array of Tax Early Collaps for non-Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Early Collaps for non-Residents values.
    */
   public final Boolean[] getTaxEarlyClose2Array()
   {
      return _TaxEarlyClose2;
   }
    
   /**
    * Gets the Tax Early Collaps for Nominees field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Early Collaps for Nominees or null.
    */
   public final Boolean getTaxEarlyClose3( int index )
   {
      return _TaxEarlyClose3[index];
   }
    
   /**
    * Gets the Tax Early Collaps for Nominees field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Early Collaps for Nominees or the specified default value.
    */
   public final boolean getTaxEarlyClose3( int index, boolean defaultValue )
   {
      return _TaxEarlyClose3[index] == null ? defaultValue : _TaxEarlyClose3[index].booleanValue();
   }
    
   /**
    * Gets the array of Tax Early Collaps for Nominees fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Early Collaps for Nominees values.
    */
   public final Boolean[] getTaxEarlyClose3Array()
   {
      return _TaxEarlyClose3;
   }
    
   /**
    * Gets the Is Full Redempt taxable for Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Full Redempt taxable for Residents or null.
    */
   public final Boolean getTaxFullRdmp1( int index )
   {
      return _TaxFullRdmp1[index];
   }
    
   /**
    * Gets the Is Full Redempt taxable for Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Full Redempt taxable for Residents or the specified default value.
    */
   public final boolean getTaxFullRdmp1( int index, boolean defaultValue )
   {
      return _TaxFullRdmp1[index] == null ? defaultValue : _TaxFullRdmp1[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Full Redempt taxable for Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Full Redempt taxable for Residents values.
    */
   public final Boolean[] getTaxFullRdmp1Array()
   {
      return _TaxFullRdmp1;
   }
    
   /**
    * Gets the Is Full Redempt taxable for non-Resident field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Full Redempt taxable for non-Resident or null.
    */
   public final Boolean getTaxFullRdmp2( int index )
   {
      return _TaxFullRdmp2[index];
   }
    
   /**
    * Gets the Is Full Redempt taxable for non-Resident field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Full Redempt taxable for non-Resident or the specified default value.
    */
   public final boolean getTaxFullRdmp2( int index, boolean defaultValue )
   {
      return _TaxFullRdmp2[index] == null ? defaultValue : _TaxFullRdmp2[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Full Redempt taxable for non-Resident fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Full Redempt taxable for non-Resident values.
    */
   public final Boolean[] getTaxFullRdmp2Array()
   {
      return _TaxFullRdmp2;
   }
    
   /**
    * Gets the Is Full Redempt taxable for Nominees field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Full Redempt taxable for Nominees or null.
    */
   public final Boolean getTaxFullRdmp3( int index )
   {
      return _TaxFullRdmp3[index];
   }
    
   /**
    * Gets the Is Full Redempt taxable for Nominees field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Full Redempt taxable for Nominees or the specified default value.
    */
   public final boolean getTaxFullRdmp3( int index, boolean defaultValue )
   {
      return _TaxFullRdmp3[index] == null ? defaultValue : _TaxFullRdmp3[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Full Redempt taxable for Nominees fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Full Redempt taxable for Nominees values.
    */
   public final Boolean[] getTaxFullRdmp3Array()
   {
      return _TaxFullRdmp3;
   }
    
   /**
    * Gets the Is notional Distrib taxable for Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is notional Distrib taxable for Residents or null.
    */
   public final Boolean getTaxNotional1( int index )
   {
      return _TaxNotional1[index];
   }
    
   /**
    * Gets the Is notional Distrib taxable for Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is notional Distrib taxable for Residents or the specified default value.
    */
   public final boolean getTaxNotional1( int index, boolean defaultValue )
   {
      return _TaxNotional1[index] == null ? defaultValue : _TaxNotional1[index].booleanValue();
   }
    
   /**
    * Gets the array of Is notional Distrib taxable for Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is notional Distrib taxable for Residents values.
    */
   public final Boolean[] getTaxNotional1Array()
   {
      return _TaxNotional1;
   }
    
   /**
    * Gets the Is notional Distrib taxable for  non-Resid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is notional Distrib taxable for  non-Resid or null.
    */
   public final Boolean getTaxNotional2( int index )
   {
      return _TaxNotional2[index];
   }
    
   /**
    * Gets the Is notional Distrib taxable for  non-Resid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is notional Distrib taxable for  non-Resid or the specified default value.
    */
   public final boolean getTaxNotional2( int index, boolean defaultValue )
   {
      return _TaxNotional2[index] == null ? defaultValue : _TaxNotional2[index].booleanValue();
   }
    
   /**
    * Gets the array of Is notional Distrib taxable for  non-Resid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is notional Distrib taxable for  non-Resid values.
    */
   public final Boolean[] getTaxNotional2Array()
   {
      return _TaxNotional2;
   }
    
   /**
    * Gets the Is notional Distrib taxable for Nominees field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is notional Distrib taxable for Nominees or null.
    */
   public final Boolean getTaxNotional3( int index )
   {
      return _TaxNotional3[index];
   }
    
   /**
    * Gets the Is notional Distrib taxable for Nominees field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is notional Distrib taxable for Nominees or the specified default value.
    */
   public final boolean getTaxNotional3( int index, boolean defaultValue )
   {
      return _TaxNotional3[index] == null ? defaultValue : _TaxNotional3[index].booleanValue();
   }
    
   /**
    * Gets the array of Is notional Distrib taxable for Nominees fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is notional Distrib taxable for Nominees values.
    */
   public final Boolean[] getTaxNotional3Array()
   {
      return _TaxNotional3;
   }
    
   /**
    * Gets the Is partial Redempt taxable for Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is partial Redempt taxable for Residents or null.
    */
   public final Boolean getTaxPartRdmp1( int index )
   {
      return _TaxPartRdmp1[index];
   }
    
   /**
    * Gets the Is partial Redempt taxable for Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is partial Redempt taxable for Residents or the specified default value.
    */
   public final boolean getTaxPartRdmp1( int index, boolean defaultValue )
   {
      return _TaxPartRdmp1[index] == null ? defaultValue : _TaxPartRdmp1[index].booleanValue();
   }
    
   /**
    * Gets the array of Is partial Redempt taxable for Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is partial Redempt taxable for Residents values.
    */
   public final Boolean[] getTaxPartRdmp1Array()
   {
      return _TaxPartRdmp1;
   }
    
   /**
    * Gets the Is partial Redempt taxable for non-Resid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is partial Redempt taxable for non-Resid or null.
    */
   public final Boolean getTaxPartRdmp2( int index )
   {
      return _TaxPartRdmp2[index];
   }
    
   /**
    * Gets the Is partial Redempt taxable for non-Resid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is partial Redempt taxable for non-Resid or the specified default value.
    */
   public final boolean getTaxPartRdmp2( int index, boolean defaultValue )
   {
      return _TaxPartRdmp2[index] == null ? defaultValue : _TaxPartRdmp2[index].booleanValue();
   }
    
   /**
    * Gets the array of Is partial Redempt taxable for non-Resid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is partial Redempt taxable for non-Resid values.
    */
   public final Boolean[] getTaxPartRdmp2Array()
   {
      return _TaxPartRdmp2;
   }
    
   /**
    * Gets the Is partial Redempt taxable for Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is partial Redempt taxable for Residents or null.
    */
   public final Boolean getTaxPartRdmp3( int index )
   {
      return _TaxPartRdmp3[index];
   }
    
   /**
    * Gets the Is partial Redempt taxable for Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is partial Redempt taxable for Residents or the specified default value.
    */
   public final boolean getTaxPartRdmp3( int index, boolean defaultValue )
   {
      return _TaxPartRdmp3[index] == null ? defaultValue : _TaxPartRdmp3[index].booleanValue();
   }
    
   /**
    * Gets the array of Is partial Redempt taxable for Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is partial Redempt taxable for Residents values.
    */
   public final Boolean[] getTaxPartRdmp3Array()
   {
      return _TaxPartRdmp3;
   }
    
   /**
    * Gets the Is Purchase taxable for Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Purchase taxable for Residents or null.
    */
   public final Boolean getTaxPurchase1( int index )
   {
      return _TaxPurchase1[index];
   }
    
   /**
    * Gets the Is Purchase taxable for Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Purchase taxable for Residents or the specified default value.
    */
   public final boolean getTaxPurchase1( int index, boolean defaultValue )
   {
      return _TaxPurchase1[index] == null ? defaultValue : _TaxPurchase1[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Purchase taxable for Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Purchase taxable for Residents values.
    */
   public final Boolean[] getTaxPurchase1Array()
   {
      return _TaxPurchase1;
   }
    
   /**
    * Gets the Is Purchase taxable for non-Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Purchase taxable for non-Residents or null.
    */
   public final Boolean getTaxPurchase2( int index )
   {
      return _TaxPurchase2[index];
   }
    
   /**
    * Gets the Is Purchase taxable for non-Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Purchase taxable for non-Residents or the specified default value.
    */
   public final boolean getTaxPurchase2( int index, boolean defaultValue )
   {
      return _TaxPurchase2[index] == null ? defaultValue : _TaxPurchase2[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Purchase taxable for non-Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Purchase taxable for non-Residents values.
    */
   public final Boolean[] getTaxPurchase2Array()
   {
      return _TaxPurchase2;
   }
    
   /**
    * Gets the Is Purchase taxable for Nominees field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Purchase taxable for Nominees or null.
    */
   public final Boolean getTaxPurchase3( int index )
   {
      return _TaxPurchase3[index];
   }
    
   /**
    * Gets the Is Purchase taxable for Nominees field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Purchase taxable for Nominees or the specified default value.
    */
   public final boolean getTaxPurchase3( int index, boolean defaultValue )
   {
      return _TaxPurchase3[index] == null ? defaultValue : _TaxPurchase3[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Purchase taxable for Nominees fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Purchase taxable for Nominees values.
    */
   public final Boolean[] getTaxPurchase3Array()
   {
      return _TaxPurchase3;
   }
    
   /**
    * Gets the Is Reinv Distr taxable for Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Reinv Distr taxable for Residents or null.
    */
   public final Boolean getTaxReinvDist1( int index )
   {
      return _TaxReinvDist1[index];
   }
    
   /**
    * Gets the Is Reinv Distr taxable for Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Reinv Distr taxable for Residents or the specified default value.
    */
   public final boolean getTaxReinvDist1( int index, boolean defaultValue )
   {
      return _TaxReinvDist1[index] == null ? defaultValue : _TaxReinvDist1[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Reinv Distr taxable for Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Reinv Distr taxable for Residents values.
    */
   public final Boolean[] getTaxReinvDist1Array()
   {
      return _TaxReinvDist1;
   }
    
   /**
    * Gets the Is Reinv Distr taxable for non-Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Reinv Distr taxable for non-Residents or null.
    */
   public final Boolean getTaxReinvDist2( int index )
   {
      return _TaxReinvDist2[index];
   }
    
   /**
    * Gets the Is Reinv Distr taxable for non-Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Reinv Distr taxable for non-Residents or the specified default value.
    */
   public final boolean getTaxReinvDist2( int index, boolean defaultValue )
   {
      return _TaxReinvDist2[index] == null ? defaultValue : _TaxReinvDist2[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Reinv Distr taxable for non-Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Reinv Distr taxable for non-Residents values.
    */
   public final Boolean[] getTaxReinvDist2Array()
   {
      return _TaxReinvDist2;
   }
    
   /**
    * Gets the Is Reinv Distr taxable for Nominees field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is Reinv Distr taxable for Nominees or null.
    */
   public final Boolean getTaxReinvDist3( int index )
   {
      return _TaxReinvDist3[index];
   }
    
   /**
    * Gets the Is Reinv Distr taxable for Nominees field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is Reinv Distr taxable for Nominees or the specified default value.
    */
   public final boolean getTaxReinvDist3( int index, boolean defaultValue )
   {
      return _TaxReinvDist3[index] == null ? defaultValue : _TaxReinvDist3[index].booleanValue();
   }
    
   /**
    * Gets the array of Is Reinv Distr taxable for Nominees fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is Reinv Distr taxable for Nominees values.
    */
   public final Boolean[] getTaxReinvDist3Array()
   {
      return _TaxReinvDist3;
   }
    
   /**
    * Gets the Are Switches taxable for Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Are Switches taxable for Residents or null.
    */
   public final Boolean getTaxSwitches1( int index )
   {
      return _TaxSwitches1[index];
   }
    
   /**
    * Gets the Are Switches taxable for Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Are Switches taxable for Residents or the specified default value.
    */
   public final boolean getTaxSwitches1( int index, boolean defaultValue )
   {
      return _TaxSwitches1[index] == null ? defaultValue : _TaxSwitches1[index].booleanValue();
   }
    
   /**
    * Gets the array of Are Switches taxable for Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Are Switches taxable for Residents values.
    */
   public final Boolean[] getTaxSwitches1Array()
   {
      return _TaxSwitches1;
   }
    
   /**
    * Gets the Are Switches taxable for non-Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Are Switches taxable for non-Residents or null.
    */
   public final Boolean getTaxSwitches2( int index )
   {
      return _TaxSwitches2[index];
   }
    
   /**
    * Gets the Are Switches taxable for non-Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Are Switches taxable for non-Residents or the specified default value.
    */
   public final boolean getTaxSwitches2( int index, boolean defaultValue )
   {
      return _TaxSwitches2[index] == null ? defaultValue : _TaxSwitches2[index].booleanValue();
   }
    
   /**
    * Gets the array of Are Switches taxable for non-Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Are Switches taxable for non-Residents values.
    */
   public final Boolean[] getTaxSwitches2Array()
   {
      return _TaxSwitches2;
   }
    
   /**
    * Gets the Are Switches taxable for Nominees field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Are Switches taxable for Nominees or null.
    */
   public final Boolean getTaxSwitches3( int index )
   {
      return _TaxSwitches3[index];
   }
    
   /**
    * Gets the Are Switches taxable for Nominees field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Are Switches taxable for Nominees or the specified default value.
    */
   public final boolean getTaxSwitches3( int index, boolean defaultValue )
   {
      return _TaxSwitches3[index] == null ? defaultValue : _TaxSwitches3[index].booleanValue();
   }
    
   /**
    * Gets the array of Are Switches taxable for Nominees fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Are Switches taxable for Nominees values.
    */
   public final Boolean[] getTaxSwitches3Array()
   {
      return _TaxSwitches3;
   }
    
   /**
    * Gets the Is transfer taxable for Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is transfer taxable for Residents or null.
    */
   public final Boolean getTaxTransfers1( int index )
   {
      return _TaxTransfers1[index];
   }
    
   /**
    * Gets the Is transfer taxable for Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is transfer taxable for Residents or the specified default value.
    */
   public final boolean getTaxTransfers1( int index, boolean defaultValue )
   {
      return _TaxTransfers1[index] == null ? defaultValue : _TaxTransfers1[index].booleanValue();
   }
    
   /**
    * Gets the array of Is transfer taxable for Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is transfer taxable for Residents values.
    */
   public final Boolean[] getTaxTransfers1Array()
   {
      return _TaxTransfers1;
   }
    
   /**
    * Gets the Is transfer taxable for non-Residents field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is transfer taxable for non-Residents or null.
    */
   public final Boolean getTaxTransfers2( int index )
   {
      return _TaxTransfers2[index];
   }
    
   /**
    * Gets the Is transfer taxable for non-Residents field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is transfer taxable for non-Residents or the specified default value.
    */
   public final boolean getTaxTransfers2( int index, boolean defaultValue )
   {
      return _TaxTransfers2[index] == null ? defaultValue : _TaxTransfers2[index].booleanValue();
   }
    
   /**
    * Gets the array of Is transfer taxable for non-Residents fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is transfer taxable for non-Residents values.
    */
   public final Boolean[] getTaxTransfers2Array()
   {
      return _TaxTransfers2;
   }
    
   /**
    * Gets the Is transfer taxable for Nominees field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is transfer taxable for Nominees or null.
    */
   public final Boolean getTaxTransfers3( int index )
   {
      return _TaxTransfers3[index];
   }
    
   /**
    * Gets the Is transfer taxable for Nominees field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is transfer taxable for Nominees or the specified default value.
    */
   public final boolean getTaxTransfers3( int index, boolean defaultValue )
   {
      return _TaxTransfers3[index] == null ? defaultValue : _TaxTransfers3[index].booleanValue();
   }
    
   /**
    * Gets the array of Is transfer taxable for Nominees fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is transfer taxable for Nominees values.
    */
   public final Boolean[] getTaxTransfers3Array()
   {
      return _TaxTransfers3;
   }
    
   /**
    * Gets the Client Equivalent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Client Equivalent or null.
    */
   public final String getClientEquiv( int index )
   {
      return _ClientEquiv[index];
   }
    
   /**
    * Gets the Client Equivalent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Client Equivalent or the specified default value.
    */
   public final String getClientEquiv( int index, String defaultValue )
   {
      return _ClientEquiv[index] == null ? defaultValue : _ClientEquiv[index];
   }
    
   /**
    * Gets the array of Client Equivalent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Client Equivalent values.
    */
   public final String[] getClientEquivArray()
   {
      return _ClientEquiv;
   }
    
   /**
    * Gets the List of allowable deposit types field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the List of allowable deposit types or null.
    */
   public final String getDepositTypes( int index )
   {
      return _DepositTypes[index];
   }
    
   /**
    * Gets the List of allowable deposit types field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the List of allowable deposit types or the specified default value.
    */
   public final String getDepositTypes( int index, String defaultValue )
   {
      return _DepositTypes[index] == null ? defaultValue : _DepositTypes[index];
   }
    
   /**
    * Gets the array of List of allowable deposit types fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of List of allowable deposit types values.
    */
   public final String[] getDepositTypesArray()
   {
      return _DepositTypes;
   }
    
   /**
    * Gets the List of allowable red codes field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the List of allowable red codes or null.
    */
   public final String getRedCodes( int index )
   {
      return _RedCodes[index];
   }
    
   /**
    * Gets the List of allowable red codes field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the List of allowable red codes or the specified default value.
    */
   public final String getRedCodes( int index, String defaultValue )
   {
      return _RedCodes[index] == null ? defaultValue : _RedCodes[index];
   }
    
   /**
    * Gets the array of List of allowable red codes fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of List of allowable red codes values.
    */
   public final String[] getRedCodesArray()
   {
      return _RedCodes;
   }
    
   /**
    * Gets the Account Designation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Designation or null.
    */
   public final String getAcctDesignation( int index )
   {
      return _AcctDesignation[index];
   }
    
   /**
    * Gets the Account Designation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Designation or the specified default value.
    */
   public final String getAcctDesignation( int index, String defaultValue )
   {
      return _AcctDesignation[index] == null ? defaultValue : _AcctDesignation[index];
   }
    
   /**
    * Gets the array of Account Designation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Designation values.
    */
   public final String[] getAcctDesignationArray()
   {
      return _AcctDesignation;
   }
    
   /**
    * Gets the ExclDTAAcctType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ExclDTAAcctType or null.
    */
   public final String getExclDTAAcctType( int index )
   {
      return _ExclDTAAcctType[index];
   }
    
   /**
    * Gets the ExclDTAAcctType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ExclDTAAcctType or the specified default value.
    */
   public final String getExclDTAAcctType( int index, String defaultValue )
   {
      return _ExclDTAAcctType[index] == null ? defaultValue : _ExclDTAAcctType[index];
   }
    
   /**
    * Gets the array of ExclDTAAcctType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ExclDTAAcctType values.
    */
   public final String[] getExclDTAAcctTypeArray()
   {
      return _ExclDTAAcctType;
   }
    
   /**
    * Gets the Tax Type Schedule field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type Schedule or null.
    */
   public final String getTaxTypeSchedule( int index )
   {
      return _TaxTypeSchedule[index];
   }
    
   /**
    * Gets the Tax Type Schedule field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type Schedule or the specified default value.
    */
   public final String getTaxTypeSchedule( int index, String defaultValue )
   {
      return _TaxTypeSchedule[index] == null ? defaultValue : _TaxTypeSchedule[index];
   }
    
   /**
    * Gets the array of Tax Type Schedule fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type Schedule values.
    */
   public final String[] getTaxTypeScheduleArray()
   {
      return _TaxTypeSchedule;
   }
    
   /**
    * Gets the SINRequired field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SINRequired or null.
    */
   public final String getSINRequired( int index )
   {
      return _SINRequired[index];
   }
    
   /**
    * Gets the SINRequired field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SINRequired or the specified default value.
    */
   public final String getSINRequired( int index, String defaultValue )
   {
      return _SINRequired[index] == null ? defaultValue : _SINRequired[index];
   }
    
   /**
    * Gets the array of SINRequired fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SINRequired values.
    */
   public final String[] getSINRequiredArray()
   {
      return _SINRequired;
   }
    
   /**
    * Gets the MinAge field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MinAge or null.
    */
   public final Integer getMinAge( int index )
   {
      return _MinAge[index];
   }
    
   /**
    * Gets the MinAge field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MinAge or the specified default value.
    */
   public final int getMinAge( int index, int defaultValue )
   {
      return _MinAge[index] == null ? defaultValue : _MinAge[index].intValue();
   }
    
   /**
    * Gets the array of MinAge fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MinAge values.
    */
   public final Integer[] getMinAgeArray()
   {
      return _MinAge;
   }
    
   /**
    * Gets the MaxAge field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MaxAge or null.
    */
   public final Integer getMaxAge( int index )
   {
      return _MaxAge[index];
   }
    
   /**
    * Gets the MaxAge field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MaxAge or the specified default value.
    */
   public final int getMaxAge( int index, int defaultValue )
   {
      return _MaxAge[index] == null ? defaultValue : _MaxAge[index].intValue();
   }
    
   /**
    * Gets the array of MaxAge fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MaxAge values.
    */
   public final Integer[] getMaxAgeArray()
   {
      return _MaxAge;
   }
    
   /**
    * Gets the TradeStartDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TradeStartDate or null.
    */
   public final Date getTradeStartDate( int index )
   {
      return _TradeStartDate[index];
   }
    
   /**
    * Gets the TradeStartDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TradeStartDate or the specified default value.
    */
   public final Date getTradeStartDate( int index, Date defaultValue )
   {
      return _TradeStartDate[index] == null ? defaultValue : _TradeStartDate[index];
   }
    
   /**
    * Gets the array of TradeStartDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TradeStartDate values.
    */
   public final Date[] getTradeStartDateArray()
   {
      return _TradeStartDate;
   }
    
   /**
    * Gets the TradeStopDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TradeStopDate or null.
    */
   public final Date getTradeStopDate( int index )
   {
      return _TradeStopDate[index];
   }
    
   /**
    * Gets the TradeStopDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TradeStopDate or the specified default value.
    */
   public final Date getTradeStopDate( int index, Date defaultValue )
   {
      return _TradeStopDate[index] == null ? defaultValue : _TradeStopDate[index];
   }
    
   /**
    * Gets the array of TradeStopDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TradeStopDate values.
    */
   public final Date[] getTradeStopDateArray()
   {
      return _TradeStopDate;
   }
    
   /**
    * Gets the Tax Types Settlement Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Types Settlement Currency or null.
    */
   public final String getTaxTypeRuleCurrSet( int index )
   {
      return _TaxTypeRuleCurrSet[index];
   }
    
   /**
    * Gets the Tax Types Settlement Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Types Settlement Currency or the specified default value.
    */
   public final String getTaxTypeRuleCurrSet( int index, String defaultValue )
   {
      return _TaxTypeRuleCurrSet[index] == null ? defaultValue : _TaxTypeRuleCurrSet[index];
   }
    
   /**
    * Gets the array of Tax Types Settlement Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Types Settlement Currency values.
    */
   public final String[] getTaxTypeRuleCurrSetArray()
   {
      return _TaxTypeRuleCurrSet;
   }
    
   /**
    * Gets the Maximum Fee Applicable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maximum Fee Applicable or null.
    */
   public final Boolean getMaxFeeAppl( int index )
   {
      return _MaxFeeAppl[index];
   }
    
   /**
    * Gets the Maximum Fee Applicable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Fee Applicable or the specified default value.
    */
   public final boolean getMaxFeeAppl( int index, boolean defaultValue )
   {
      return _MaxFeeAppl[index] == null ? defaultValue : _MaxFeeAppl[index].booleanValue();
   }
    
   /**
    * Gets the array of Maximum Fee Applicable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maximum Fee Applicable values.
    */
   public final Boolean[] getMaxFeeApplArray()
   {
      return _MaxFeeAppl;
   }
    
   /**
    * Gets the Maximum Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maximum Fee or null.
    */
   public final String getMaxFee( int index )
   {
      return _MaxFee[index];
   }
    
   /**
    * Gets the Maximum Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Fee or the specified default value.
    */
   public final String getMaxFee( int index, String defaultValue )
   {
      return _MaxFee[index] == null ? defaultValue : _MaxFee[index];
   }
    
   /**
    * Gets the array of Maximum Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maximum Fee values.
    */
   public final String[] getMaxFeeArray()
   {
      return _MaxFee;
   }
    
   /**
    * Implements the abstract base method to decode
    * the host formatted response.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   protected void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      // single-record section
      decodeMoreAvailableField( responseBuffer );
      decodeNextKeyField( responseBuffer );
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _TaxTypeDesc = resizeArray( _TaxTypeDesc, _RepeatCount );
      _PlanType = resizeArray( _PlanType, _RepeatCount );
      _PlanTypeDesc = resizeArray( _PlanTypeDesc, _RepeatCount );
      _AccountTypes = resizeArray( _AccountTypes, _RepeatCount );
      _SelfDirected = resizeArray( _SelfDirected, _RepeatCount );
      _TransferTypes = resizeArray( _TransferTypes, _RepeatCount );
      _LockedIn = resizeArray( _LockedIn, _RepeatCount );
      _TaxByJuris = resizeArray( _TaxByJuris, _RepeatCount );
      _FedJurisAllowed = resizeArray( _FedJurisAllowed, _RepeatCount );
      _Certificate = resizeArray( _Certificate, _RepeatCount );
      _NomTaxRcpt = resizeArray( _NomTaxRcpt, _RepeatCount );
      _Unseizable = resizeArray( _Unseizable, _RepeatCount );
      _AvailNonRes = resizeArray( _AvailNonRes, _RepeatCount );
      _ReinDistOnly = resizeArray( _ReinDistOnly, _RepeatCount );
      _MinimumApplies = resizeArray( _MinimumApplies, _RepeatCount );
      _MaximumApplies = resizeArray( _MaximumApplies, _RepeatCount );
      _GICallowed = resizeArray( _GICallowed, _RepeatCount );
      _PACallowed = resizeArray( _PACallowed, _RepeatCount );
      _SWPallowed = resizeArray( _SWPallowed, _RepeatCount );
      _AdminFeeDefn = resizeArray( _AdminFeeDefn, _RepeatCount );
      _MailList1 = resizeArray( _MailList1, _RepeatCount );
      _MailList2 = resizeArray( _MailList2, _RepeatCount );
      _MailList3 = resizeArray( _MailList3, _RepeatCount );
      _MailList4 = resizeArray( _MailList4, _RepeatCount );
      _MailList5 = resizeArray( _MailList5, _RepeatCount );
      _MailList6 = resizeArray( _MailList6, _RepeatCount );
      _MailList7 = resizeArray( _MailList7, _RepeatCount );
      _MailList8 = resizeArray( _MailList8, _RepeatCount );
      _MailList9 = resizeArray( _MailList9, _RepeatCount );
      _MailList10 = resizeArray( _MailList10, _RepeatCount );
      _MailList11 = resizeArray( _MailList11, _RepeatCount );
      _MailList12 = resizeArray( _MailList12, _RepeatCount );
      _TaxCashDist1 = resizeArray( _TaxCashDist1, _RepeatCount );
      _TaxCashDist2 = resizeArray( _TaxCashDist2, _RepeatCount );
      _TaxCashDist3 = resizeArray( _TaxCashDist3, _RepeatCount );
      _TaxEarlyClose1 = resizeArray( _TaxEarlyClose1, _RepeatCount );
      _TaxEarlyClose2 = resizeArray( _TaxEarlyClose2, _RepeatCount );
      _TaxEarlyClose3 = resizeArray( _TaxEarlyClose3, _RepeatCount );
      _TaxFullRdmp1 = resizeArray( _TaxFullRdmp1, _RepeatCount );
      _TaxFullRdmp2 = resizeArray( _TaxFullRdmp2, _RepeatCount );
      _TaxFullRdmp3 = resizeArray( _TaxFullRdmp3, _RepeatCount );
      _TaxNotional1 = resizeArray( _TaxNotional1, _RepeatCount );
      _TaxNotional2 = resizeArray( _TaxNotional2, _RepeatCount );
      _TaxNotional3 = resizeArray( _TaxNotional3, _RepeatCount );
      _TaxPartRdmp1 = resizeArray( _TaxPartRdmp1, _RepeatCount );
      _TaxPartRdmp2 = resizeArray( _TaxPartRdmp2, _RepeatCount );
      _TaxPartRdmp3 = resizeArray( _TaxPartRdmp3, _RepeatCount );
      _TaxPurchase1 = resizeArray( _TaxPurchase1, _RepeatCount );
      _TaxPurchase2 = resizeArray( _TaxPurchase2, _RepeatCount );
      _TaxPurchase3 = resizeArray( _TaxPurchase3, _RepeatCount );
      _TaxReinvDist1 = resizeArray( _TaxReinvDist1, _RepeatCount );
      _TaxReinvDist2 = resizeArray( _TaxReinvDist2, _RepeatCount );
      _TaxReinvDist3 = resizeArray( _TaxReinvDist3, _RepeatCount );
      _TaxSwitches1 = resizeArray( _TaxSwitches1, _RepeatCount );
      _TaxSwitches2 = resizeArray( _TaxSwitches2, _RepeatCount );
      _TaxSwitches3 = resizeArray( _TaxSwitches3, _RepeatCount );
      _TaxTransfers1 = resizeArray( _TaxTransfers1, _RepeatCount );
      _TaxTransfers2 = resizeArray( _TaxTransfers2, _RepeatCount );
      _TaxTransfers3 = resizeArray( _TaxTransfers3, _RepeatCount );
      _ClientEquiv = resizeArray( _ClientEquiv, _RepeatCount );
      _DepositTypes = resizeArray( _DepositTypes, _RepeatCount );
      _RedCodes = resizeArray( _RedCodes, _RepeatCount );
      _AcctDesignation = resizeArray( _AcctDesignation, _RepeatCount );
      _ExclDTAAcctType = resizeArray( _ExclDTAAcctType, _RepeatCount );
      _TaxTypeSchedule = resizeArray( _TaxTypeSchedule, _RepeatCount );
      _SINRequired = resizeArray( _SINRequired, _RepeatCount );
      _MinAge = resizeArray( _MinAge, _RepeatCount );
      _MaxAge = resizeArray( _MaxAge, _RepeatCount );
      _TradeStartDate = resizeArray( _TradeStartDate, _RepeatCount );
      _TradeStopDate = resizeArray( _TradeStopDate, _RepeatCount );
      _TaxTypeRuleCurrSet = resizeArray( _TaxTypeRuleCurrSet, _RepeatCount );
      _MaxFeeAppl = resizeArray( _MaxFeeAppl, _RepeatCount );
      _MaxFee = resizeArray( _MaxFee, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PlanType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PlanTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountTypes[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SelfDirected[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TransferTypes[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LockedIn[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxByJuris[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FedJurisAllowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Certificate[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _NomTaxRcpt[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Unseizable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AvailNonRes[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ReinDistOnly[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MinimumApplies[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MaximumApplies[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GICallowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PACallowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SWPallowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AdminFeeDefn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList6[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList7[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList8[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList9[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList10[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList11[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MailList12[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxCashDist1[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxCashDist2[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxCashDist3[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxEarlyClose1[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxEarlyClose2[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxEarlyClose3[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxFullRdmp1[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxFullRdmp2[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxFullRdmp3[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxNotional1[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxNotional2[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxNotional3[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxPartRdmp1[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxPartRdmp2[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxPartRdmp3[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxPurchase1[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxPurchase2[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxPurchase3[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxReinvDist1[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxReinvDist2[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxReinvDist3[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxSwitches1[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxSwitches2[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxSwitches3[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxTransfers1[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxTransfers2[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxTransfers3[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ClientEquiv[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DepositTypes[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedCodes[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDesignation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExclDTAAcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxTypeSchedule[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SINRequired[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MaxAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TradeStartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TradeStopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TaxTypeRuleCurrSet[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxFeeAppl[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MaxFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
