
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Trade Defaults Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/TradeDfltsInq.doc">TradeDfltsInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeDfltsInqView extends IFastView implements Serializable
{

   /**
    * Default Transaction Type member variable.
    */
   private String _TransTypeDefault = null;
   
   /**
    * Default Amount Type member variable.
    */
   private String _AmtTypeDefault = null;
   
   /**
    * Default PayType member variable.
    */
   private String _PayTypeDefault = null;
   
   /**
    * Default Clearing Method member variable.
    */
   private String _ClearMethodDefault = null;
   
   /**
    * Default File Processor member variable.
    */
   private String _FileProcessorDefault = null;
   
   /**
    * Default Settlement Currency member variable.
    */
   private Integer _SettleCurrDefault = null;
   
   /**
    * Can Suppress Confirms? Y/N member variable.
    */
   private Boolean _CanSuppressConfirm = null;
   
   /**
    * Applicable transtype for ROA member variable.
    */
   private String _ROATranstypes = null;
   
   /**
    * Default Exchange Rate member variable.
    */
   private Boolean _DefExchRate = null;
   
   /**
    * Indicate if MCH and SR applicable to environment member variable.
    */
   private Boolean _MCHSRActive = null;
   
   /**
    * MCH New Trade Default member variable.
    */
   private String _MCHNewTrade = null;
   
   /**
    * MCH Rebook Trade Default member variable.
    */
   private String _MCHRbkTrade = null;
   
   /**
    * MCH Individual Cancel Default member variable.
    */
   private String _MCHIndCancel = null;
   
   /**
    * MCH Bulk Cancel Default member variable.
    */
   private String _MCHBulkCancel = null;
   
   /**
    * MCH Bulk Rebook Default member variable.
    */
   private String _MCHBulkRbk = null;
   
   /**
    * SecRecon New Trade Default member variable.
    */
   private String _SRNewTrade = null;
   
   /**
    * SecRecon Rebook Trade Default member variable.
    */
   private String _SRRbkTrade = null;
   
   /**
    * SecRecon Individual Cancel Default member variable.
    */
   private String _SRIndCancel = null;
   
   /**
    * SecRecon Bulk Cancel Default member variable.
    */
   private String _SRBulkCancel = null;
   
   /**
    * SecRecon Bulk Rebook Default member variable.
    */
   private String _SRBulkRbk = null;
   
   /**
    * Flag indicating if intermediary is eligible to settle SWP through FUNDServ - system level member variable.
    */
   private Boolean _SWPSettleESGElig = null;
   
   /**
    * Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ - system levelapplicable for Money movement member variable.
    */
   private Boolean _CashIDSettleESGElig = null;
   
   /**
    * SDRT Reporting Flag member variable.
    */
   private Boolean _SDRTReportingFlag = null;
   
   /**
    * AWD Field Flag member variable.
    */
   private String _AWDFieldFlag = null;
   
   /**
    * PSD Advice Default member variable.
    */
   private String _PSDAdvcDflt = null;
   
   /**
    * Pymt Routing Mthd member variable.
    */
   private String _PymtRoutingMthd = null;
   
   /**
    * Trade Level Routing member variable.
    */
   private Boolean _TradeLevelRouting = null;
   
   /**
    * Def Pymt Routing Mthd member variable.
    */
   private String _DefPymtRoutingMthd = null;
   
   /**
    * UCIT Flag member variable.
    */
   private String _UCITFlag = null;
   
   /**
    * Skip Allowable Transfer member variable.
    */
   private String _SkipAllowableTransfer = null;
   
   /**
    * StopOverrideRule member variable.
    */
   private Boolean _StopOverrideRule = null;
   
   /**
    * BatchVerify member variable.
    */
   private Boolean _BatchVerify = null;
   
   /**
    * G1G2CalcMethd member variable.
    */
   private Integer _G1G2CalcMethd = null;
   

   /**
    * Constructs the TradeDfltsInqView object.
    * 
    */
   public TradeDfltsInqView()
   {
      super ( new TradeDfltsInqRequest() );
   }

   /**
    * Constructs the TradeDfltsInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TradeDfltsInqView( String hostEncoding )
   {
      super ( new TradeDfltsInqRequest( hostEncoding ) );
   }

   /**
    * Gets the TradeDfltsInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TradeDfltsInqRequest object.
    */
   public final TradeDfltsInqRequest getRequest()
   {
      return (TradeDfltsInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Default Transaction Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Transaction Type or null.
    */
   public final String getTransTypeDefault()
   {
      return _TransTypeDefault;
   }
	
   /**
    * Gets the Default Transaction Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Transaction Type or the specified default value.
    */
   public final String getTransTypeDefault( String defaultValue )
   {
      return _TransTypeDefault == null ? defaultValue : _TransTypeDefault;
   }
                  
   /**
    * Gets the Default Amount Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Amount Type or null.
    */
   public final String getAmtTypeDefault()
   {
      return _AmtTypeDefault;
   }
	
   /**
    * Gets the Default Amount Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Amount Type or the specified default value.
    */
   public final String getAmtTypeDefault( String defaultValue )
   {
      return _AmtTypeDefault == null ? defaultValue : _AmtTypeDefault;
   }
                  
   /**
    * Gets the Default PayType field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default PayType or null.
    */
   public final String getPayTypeDefault()
   {
      return _PayTypeDefault;
   }
	
   /**
    * Gets the Default PayType field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default PayType or the specified default value.
    */
   public final String getPayTypeDefault( String defaultValue )
   {
      return _PayTypeDefault == null ? defaultValue : _PayTypeDefault;
   }
                  
   /**
    * Gets the Default Clearing Method field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Clearing Method or null.
    */
   public final String getClearMethodDefault()
   {
      return _ClearMethodDefault;
   }
	
   /**
    * Gets the Default Clearing Method field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Clearing Method or the specified default value.
    */
   public final String getClearMethodDefault( String defaultValue )
   {
      return _ClearMethodDefault == null ? defaultValue : _ClearMethodDefault;
   }
                  
   /**
    * Gets the Default File Processor field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default File Processor or null.
    */
   public final String getFileProcessorDefault()
   {
      return _FileProcessorDefault;
   }
	
   /**
    * Gets the Default File Processor field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default File Processor or the specified default value.
    */
   public final String getFileProcessorDefault( String defaultValue )
   {
      return _FileProcessorDefault == null ? defaultValue : _FileProcessorDefault;
   }
                  
   /**
    * Gets the Default Settlement Currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Settlement Currency or null.
    */
   public final Integer getSettleCurrDefault()
   {
      return _SettleCurrDefault;
   }
	
   /**
    * Gets the Default Settlement Currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Settlement Currency or the specified default value.
    */
   public final int getSettleCurrDefault( int defaultValue )
   {
      return _SettleCurrDefault == null ? defaultValue : _SettleCurrDefault.intValue();
   }
                  
   /**
    * Gets the Can Suppress Confirms? Y/N field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Can Suppress Confirms? Y/N or null.
    */
   public final Boolean getCanSuppressConfirm()
   {
      return _CanSuppressConfirm;
   }
	
   /**
    * Gets the Can Suppress Confirms? Y/N field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Can Suppress Confirms? Y/N or the specified default value.
    */
   public final boolean getCanSuppressConfirm( boolean defaultValue )
   {
      return _CanSuppressConfirm == null ? defaultValue : _CanSuppressConfirm.booleanValue();
   }
                  
   /**
    * Gets the Applicable transtype for ROA field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Applicable transtype for ROA or null.
    */
   public final String getROATranstypes()
   {
      return _ROATranstypes;
   }
	
   /**
    * Gets the Applicable transtype for ROA field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Applicable transtype for ROA or the specified default value.
    */
   public final String getROATranstypes( String defaultValue )
   {
      return _ROATranstypes == null ? defaultValue : _ROATranstypes;
   }
                  
   /**
    * Gets the Default Exchange Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Exchange Rate or null.
    */
   public final Boolean getDefExchRate()
   {
      return _DefExchRate;
   }
	
   /**
    * Gets the Default Exchange Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Exchange Rate or the specified default value.
    */
   public final boolean getDefExchRate( boolean defaultValue )
   {
      return _DefExchRate == null ? defaultValue : _DefExchRate.booleanValue();
   }
                  
   /**
    * Gets the Indicate if MCH and SR applicable to environment field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Indicate if MCH and SR applicable to environment or null.
    */
   public final Boolean getMCHSRActive()
   {
      return _MCHSRActive;
   }
	
   /**
    * Gets the Indicate if MCH and SR applicable to environment field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicate if MCH and SR applicable to environment or the specified default value.
    */
   public final boolean getMCHSRActive( boolean defaultValue )
   {
      return _MCHSRActive == null ? defaultValue : _MCHSRActive.booleanValue();
   }
                  
   /**
    * Gets the MCH New Trade Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the MCH New Trade Default or null.
    */
   public final String getMCHNewTrade()
   {
      return _MCHNewTrade;
   }
	
   /**
    * Gets the MCH New Trade Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MCH New Trade Default or the specified default value.
    */
   public final String getMCHNewTrade( String defaultValue )
   {
      return _MCHNewTrade == null ? defaultValue : _MCHNewTrade;
   }
                  
   /**
    * Gets the MCH Rebook Trade Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the MCH Rebook Trade Default or null.
    */
   public final String getMCHRbkTrade()
   {
      return _MCHRbkTrade;
   }
	
   /**
    * Gets the MCH Rebook Trade Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MCH Rebook Trade Default or the specified default value.
    */
   public final String getMCHRbkTrade( String defaultValue )
   {
      return _MCHRbkTrade == null ? defaultValue : _MCHRbkTrade;
   }
                  
   /**
    * Gets the MCH Individual Cancel Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the MCH Individual Cancel Default or null.
    */
   public final String getMCHIndCancel()
   {
      return _MCHIndCancel;
   }
	
   /**
    * Gets the MCH Individual Cancel Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MCH Individual Cancel Default or the specified default value.
    */
   public final String getMCHIndCancel( String defaultValue )
   {
      return _MCHIndCancel == null ? defaultValue : _MCHIndCancel;
   }
                  
   /**
    * Gets the MCH Bulk Cancel Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the MCH Bulk Cancel Default or null.
    */
   public final String getMCHBulkCancel()
   {
      return _MCHBulkCancel;
   }
	
   /**
    * Gets the MCH Bulk Cancel Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MCH Bulk Cancel Default or the specified default value.
    */
   public final String getMCHBulkCancel( String defaultValue )
   {
      return _MCHBulkCancel == null ? defaultValue : _MCHBulkCancel;
   }
                  
   /**
    * Gets the MCH Bulk Rebook Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the MCH Bulk Rebook Default or null.
    */
   public final String getMCHBulkRbk()
   {
      return _MCHBulkRbk;
   }
	
   /**
    * Gets the MCH Bulk Rebook Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MCH Bulk Rebook Default or the specified default value.
    */
   public final String getMCHBulkRbk( String defaultValue )
   {
      return _MCHBulkRbk == null ? defaultValue : _MCHBulkRbk;
   }
                  
   /**
    * Gets the SecRecon New Trade Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SecRecon New Trade Default or null.
    */
   public final String getSRNewTrade()
   {
      return _SRNewTrade;
   }
	
   /**
    * Gets the SecRecon New Trade Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SecRecon New Trade Default or the specified default value.
    */
   public final String getSRNewTrade( String defaultValue )
   {
      return _SRNewTrade == null ? defaultValue : _SRNewTrade;
   }
                  
   /**
    * Gets the SecRecon Rebook Trade Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SecRecon Rebook Trade Default or null.
    */
   public final String getSRRbkTrade()
   {
      return _SRRbkTrade;
   }
	
   /**
    * Gets the SecRecon Rebook Trade Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SecRecon Rebook Trade Default or the specified default value.
    */
   public final String getSRRbkTrade( String defaultValue )
   {
      return _SRRbkTrade == null ? defaultValue : _SRRbkTrade;
   }
                  
   /**
    * Gets the SecRecon Individual Cancel Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SecRecon Individual Cancel Default or null.
    */
   public final String getSRIndCancel()
   {
      return _SRIndCancel;
   }
	
   /**
    * Gets the SecRecon Individual Cancel Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SecRecon Individual Cancel Default or the specified default value.
    */
   public final String getSRIndCancel( String defaultValue )
   {
      return _SRIndCancel == null ? defaultValue : _SRIndCancel;
   }
                  
   /**
    * Gets the SecRecon Bulk Cancel Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SecRecon Bulk Cancel Default or null.
    */
   public final String getSRBulkCancel()
   {
      return _SRBulkCancel;
   }
	
   /**
    * Gets the SecRecon Bulk Cancel Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SecRecon Bulk Cancel Default or the specified default value.
    */
   public final String getSRBulkCancel( String defaultValue )
   {
      return _SRBulkCancel == null ? defaultValue : _SRBulkCancel;
   }
                  
   /**
    * Gets the SecRecon Bulk Rebook Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SecRecon Bulk Rebook Default or null.
    */
   public final String getSRBulkRbk()
   {
      return _SRBulkRbk;
   }
	
   /**
    * Gets the SecRecon Bulk Rebook Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SecRecon Bulk Rebook Default or the specified default value.
    */
   public final String getSRBulkRbk( String defaultValue )
   {
      return _SRBulkRbk == null ? defaultValue : _SRBulkRbk;
   }
                  
   /**
    * Gets the Flag indicating if intermediary is eligible to settle SWP through FUNDServ - system level field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if intermediary is eligible to settle SWP through FUNDServ - system level or null.
    */
   public final Boolean getSWPSettleESGElig()
   {
      return _SWPSettleESGElig;
   }
	
   /**
    * Gets the Flag indicating if intermediary is eligible to settle SWP through FUNDServ - system level field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if intermediary is eligible to settle SWP through FUNDServ - system level or the specified default value.
    */
   public final boolean getSWPSettleESGElig( boolean defaultValue )
   {
      return _SWPSettleESGElig == null ? defaultValue : _SWPSettleESGElig.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ - system levelapplicable for Money movement field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ - system levelapplicable for Money movement or null.
    */
   public final Boolean getCashIDSettleESGElig()
   {
      return _CashIDSettleESGElig;
   }
	
   /**
    * Gets the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ - system levelapplicable for Money movement field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if intermediary is eligible to settle Cash ID through FUNDServ - system levelapplicable for Money movement or the specified default value.
    */
   public final boolean getCashIDSettleESGElig( boolean defaultValue )
   {
      return _CashIDSettleESGElig == null ? defaultValue : _CashIDSettleESGElig.booleanValue();
   }
                  
   /**
    * Gets the SDRT Reporting Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SDRT Reporting Flag or null.
    */
   public final Boolean getSDRTReportingFlag()
   {
      return _SDRTReportingFlag;
   }
	
   /**
    * Gets the SDRT Reporting Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SDRT Reporting Flag or the specified default value.
    */
   public final boolean getSDRTReportingFlag( boolean defaultValue )
   {
      return _SDRTReportingFlag == null ? defaultValue : _SDRTReportingFlag.booleanValue();
   }
                  
   /**
    * Gets the AWD Field Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AWD Field Flag or null.
    */
   public final String getAWDFieldFlag()
   {
      return _AWDFieldFlag;
   }
	
   /**
    * Gets the AWD Field Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AWD Field Flag or the specified default value.
    */
   public final String getAWDFieldFlag( String defaultValue )
   {
      return _AWDFieldFlag == null ? defaultValue : _AWDFieldFlag;
   }
                  
   /**
    * Gets the PSD Advice Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PSD Advice Default or null.
    */
   public final String getPSDAdvcDflt()
   {
      return _PSDAdvcDflt;
   }
	
   /**
    * Gets the PSD Advice Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PSD Advice Default or the specified default value.
    */
   public final String getPSDAdvcDflt( String defaultValue )
   {
      return _PSDAdvcDflt == null ? defaultValue : _PSDAdvcDflt;
   }
                  
   /**
    * Gets the Pymt Routing Mthd field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pymt Routing Mthd or null.
    */
   public final String getPymtRoutingMthd()
   {
      return _PymtRoutingMthd;
   }
	
   /**
    * Gets the Pymt Routing Mthd field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pymt Routing Mthd or the specified default value.
    */
   public final String getPymtRoutingMthd( String defaultValue )
   {
      return _PymtRoutingMthd == null ? defaultValue : _PymtRoutingMthd;
   }
                  
   /**
    * Gets the Trade Level Routing field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Trade Level Routing or null.
    */
   public final Boolean getTradeLevelRouting()
   {
      return _TradeLevelRouting;
   }
	
   /**
    * Gets the Trade Level Routing field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Level Routing or the specified default value.
    */
   public final boolean getTradeLevelRouting( boolean defaultValue )
   {
      return _TradeLevelRouting == null ? defaultValue : _TradeLevelRouting.booleanValue();
   }
                  
   /**
    * Gets the Def Pymt Routing Mthd field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Def Pymt Routing Mthd or null.
    */
   public final String getDefPymtRoutingMthd()
   {
      return _DefPymtRoutingMthd;
   }
	
   /**
    * Gets the Def Pymt Routing Mthd field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Def Pymt Routing Mthd or the specified default value.
    */
   public final String getDefPymtRoutingMthd( String defaultValue )
   {
      return _DefPymtRoutingMthd == null ? defaultValue : _DefPymtRoutingMthd;
   }
                  
   /**
    * Gets the UCIT Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the UCIT Flag or null.
    */
   public final String getUCITFlag()
   {
      return _UCITFlag;
   }
	
   /**
    * Gets the UCIT Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UCIT Flag or the specified default value.
    */
   public final String getUCITFlag( String defaultValue )
   {
      return _UCITFlag == null ? defaultValue : _UCITFlag;
   }
                  
   /**
    * Gets the Skip Allowable Transfer field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Skip Allowable Transfer or null.
    */
   public final String getSkipAllowableTransfer()
   {
      return _SkipAllowableTransfer;
   }
	
   /**
    * Gets the Skip Allowable Transfer field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Skip Allowable Transfer or the specified default value.
    */
   public final String getSkipAllowableTransfer( String defaultValue )
   {
      return _SkipAllowableTransfer == null ? defaultValue : _SkipAllowableTransfer;
   }
                  
   /**
    * Gets the StopOverrideRule field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the StopOverrideRule or null.
    */
   public final Boolean getStopOverrideRule()
   {
      return _StopOverrideRule;
   }
	
   /**
    * Gets the StopOverrideRule field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopOverrideRule or the specified default value.
    */
   public final boolean getStopOverrideRule( boolean defaultValue )
   {
      return _StopOverrideRule == null ? defaultValue : _StopOverrideRule.booleanValue();
   }
                  
   /**
    * Gets the BatchVerify field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BatchVerify or null.
    */
   public final Boolean getBatchVerify()
   {
      return _BatchVerify;
   }
	
   /**
    * Gets the BatchVerify field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BatchVerify or the specified default value.
    */
   public final boolean getBatchVerify( boolean defaultValue )
   {
      return _BatchVerify == null ? defaultValue : _BatchVerify.booleanValue();
   }
                  
   /**
    * Gets the G1G2CalcMethd field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the G1G2CalcMethd or null.
    */
   public final Integer getG1G2CalcMethd()
   {
      return _G1G2CalcMethd;
   }
	
   /**
    * Gets the G1G2CalcMethd field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the G1G2CalcMethd or the specified default value.
    */
   public final int getG1G2CalcMethd( int defaultValue )
   {
      return _G1G2CalcMethd == null ? defaultValue : _G1G2CalcMethd.intValue();
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
      _TransTypeDefault = responseBuffer.decodeString(responseBuffer.getNextField());
      _AmtTypeDefault = responseBuffer.decodeString(responseBuffer.getNextField());
      _PayTypeDefault = responseBuffer.decodeString(responseBuffer.getNextField());
      _ClearMethodDefault = responseBuffer.decodeString(responseBuffer.getNextField());
      _FileProcessorDefault = responseBuffer.decodeString(responseBuffer.getNextField());
      _SettleCurrDefault = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _CanSuppressConfirm = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ROATranstypes = responseBuffer.decodeString(responseBuffer.getNextField());
      _DefExchRate = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _MCHSRActive = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _MCHNewTrade = responseBuffer.decodeString(responseBuffer.getNextField());
      _MCHRbkTrade = responseBuffer.decodeString(responseBuffer.getNextField());
      _MCHIndCancel = responseBuffer.decodeString(responseBuffer.getNextField());
      _MCHBulkCancel = responseBuffer.decodeString(responseBuffer.getNextField());
      _MCHBulkRbk = responseBuffer.decodeString(responseBuffer.getNextField());
      _SRNewTrade = responseBuffer.decodeString(responseBuffer.getNextField());
      _SRRbkTrade = responseBuffer.decodeString(responseBuffer.getNextField());
      _SRIndCancel = responseBuffer.decodeString(responseBuffer.getNextField());
      _SRBulkCancel = responseBuffer.decodeString(responseBuffer.getNextField());
      _SRBulkRbk = responseBuffer.decodeString(responseBuffer.getNextField());
      _SWPSettleESGElig = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CashIDSettleESGElig = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SDRTReportingFlag = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AWDFieldFlag = responseBuffer.decodeString(responseBuffer.getNextField());
      _PSDAdvcDflt = responseBuffer.decodeString(responseBuffer.getNextField());
      _PymtRoutingMthd = responseBuffer.decodeString(responseBuffer.getNextField());
      _TradeLevelRouting = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DefPymtRoutingMthd = responseBuffer.decodeString(responseBuffer.getNextField());
      _UCITFlag = responseBuffer.decodeString(responseBuffer.getNextField());
      _SkipAllowableTransfer = responseBuffer.decodeString(responseBuffer.getNextField());
      _StopOverrideRule = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BatchVerify = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _G1G2CalcMethd = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  

   }

}
      
