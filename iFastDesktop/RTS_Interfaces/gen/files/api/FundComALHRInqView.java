
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * FUNDcom Acct Lev Hypo Redem Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundComALHRInq.doc">FundComALHRInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundComALHRInqView extends IFastView implements Serializable
{

   /**
    * CDNRedeem member variable.
    */
   private Boolean _CDNFundsExist = null;
   
   /**
    * USRedeem member variable.
    */
   private Boolean _USFundsExist = null;
   
   /**
    * CDN DSCFreeAmt member variable.
    */
   private String _CDNFreeAmt = null;
   
   /**
    * CDN GrossAmt member variable.
    */
   private String _CDNTotalGrossAmt = null;
   
   /**
    * CDN DednAmt member variable.
    */
   private String _CDNTotalDeductAmt = null;
   
   /**
    * CDN NetAmt member variable.
    */
   private String _CDNTotalNetAmt = null;
   
   /**
    * US DSCFreeAmt member variable.
    */
   private String _USFreeAmt = null;
   
   /**
    * US GrossAmt member variable.
    */
   private String _USTotalGrossAmt = null;
   
   /**
    * US DednAmt member variable.
    */
   private String _USTotalDeductAmt = null;
   
   /**
    * US NetAmt member variable.
    */
   private String _USTotalNetAmt = null;
   
   private int _RepeatCount = 0;
   
   /**
    * FundID member array.
    */
   private String[] _rxBaycom = null;
   
   /**
    * FundCode member array.
    */
   private String[] _FundCode = null;
   
   /**
    * ClassCode member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * FundCurrency member array.
    */
   private String[] _FundCurrency = null;
   
   /**
    * LastPriced member array.
    */
   private Date[] _LastValDate = null;
   
   /**
    * NAV member array.
    */
   private String[] _UnitPrice = null;
   
   /**
    * Units member array.
    */
   private String[] _Units = null;
   
   /**
    * GrossNetRedemption member array.
    */
   private Boolean[] _rxGrossOrNet = null;
   
   /**
    * Amount member array.
    */
   private String[] _GrossAmt = null;
   
   /**
    * NetAmt member array.
    */
   private String[] _NetAmt = null;
   
   /**
    * ClientCommission member array.
    */
   private String[] _Commission = null;
   
   /**
    * Fees member array.
    */
   private String[] _Fees = null;
   
   /**
    * ShortTermFee member array.
    */
   private String[] _ShortTermFee = null;
   
   /**
    * AdminFee member array.
    */
   private String[] _AdminFee = null;
   
   /**
    * MgmtFee member array.
    */
   private String[] _MgmtFee = null;
   
   /**
    * PerformFee member array.
    */
   private String[] _PerformFee = null;
   
   /**
    * OtherFee member array.
    */
   private String[] _OtherFee = null;
   
   /**
    * Penalty member array.
    */
   private String[] _Penalty = null;
   
   /**
    * DSC member array.
    */
   private String[] _DSC = null;
   
   /**
    * GST member array.
    */
   private String[] _GST = null;
   
   /**
    * WHoldTax1 member array.
    */
   private String[] _FedTax = null;
   
   /**
    * WHoldTax2 member array.
    */
   private String[] _ProvTax = null;
   
   /**
    * LSIFClawbackFed member array.
    */
   private String[] _LSIFClawbackFed = null;
   
   /**
    * LSIFClawbackProv member array.
    */
   private String[] _LSIFClawbackProv = null;
   
   /**
    * Clawback member array.
    */
   private String[] _Clawback = null;
   
   /**
    * Total member array.
    */
   private String[] _TotalFees = null;
   

   /**
    * Constructs the FundComALHRInqView object.
    * 
    */
   public FundComALHRInqView()
   {
      super ( new FundComALHRInqRequest() );
   }

   /**
    * Constructs the FundComALHRInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundComALHRInqView( String hostEncoding )
   {
      super ( new FundComALHRInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundComALHRInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundComALHRInqRequest object.
    */
   public final FundComALHRInqRequest getRequest()
   {
      return (FundComALHRInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the CDNRedeem field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the CDNRedeem or null.
    */
   public final Boolean getCDNFundsExist()
   {
      return _CDNFundsExist;
   }
	
   /**
    * Gets the CDNRedeem field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CDNRedeem or the specified default value.
    */
   public final boolean getCDNFundsExist( boolean defaultValue )
   {
      return _CDNFundsExist == null ? defaultValue : _CDNFundsExist.booleanValue();
   }
                  
   /**
    * Gets the USRedeem field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the USRedeem or null.
    */
   public final Boolean getUSFundsExist()
   {
      return _USFundsExist;
   }
	
   /**
    * Gets the USRedeem field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the USRedeem or the specified default value.
    */
   public final boolean getUSFundsExist( boolean defaultValue )
   {
      return _USFundsExist == null ? defaultValue : _USFundsExist.booleanValue();
   }
                  
   /**
    * Gets the CDN DSCFreeAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the CDN DSCFreeAmt or null.
    */
   public final String getCDNFreeAmt()
   {
      return _CDNFreeAmt;
   }
	
   /**
    * Gets the CDN DSCFreeAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CDN DSCFreeAmt or the specified default value.
    */
   public final String getCDNFreeAmt( String defaultValue )
   {
      return _CDNFreeAmt == null ? defaultValue : _CDNFreeAmt;
   }
                  
   /**
    * Gets the CDN GrossAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the CDN GrossAmt or null.
    */
   public final String getCDNTotalGrossAmt()
   {
      return _CDNTotalGrossAmt;
   }
	
   /**
    * Gets the CDN GrossAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CDN GrossAmt or the specified default value.
    */
   public final String getCDNTotalGrossAmt( String defaultValue )
   {
      return _CDNTotalGrossAmt == null ? defaultValue : _CDNTotalGrossAmt;
   }
                  
   /**
    * Gets the CDN DednAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the CDN DednAmt or null.
    */
   public final String getCDNTotalDeductAmt()
   {
      return _CDNTotalDeductAmt;
   }
	
   /**
    * Gets the CDN DednAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CDN DednAmt or the specified default value.
    */
   public final String getCDNTotalDeductAmt( String defaultValue )
   {
      return _CDNTotalDeductAmt == null ? defaultValue : _CDNTotalDeductAmt;
   }
                  
   /**
    * Gets the CDN NetAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the CDN NetAmt or null.
    */
   public final String getCDNTotalNetAmt()
   {
      return _CDNTotalNetAmt;
   }
	
   /**
    * Gets the CDN NetAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CDN NetAmt or the specified default value.
    */
   public final String getCDNTotalNetAmt( String defaultValue )
   {
      return _CDNTotalNetAmt == null ? defaultValue : _CDNTotalNetAmt;
   }
                  
   /**
    * Gets the US DSCFreeAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the US DSCFreeAmt or null.
    */
   public final String getUSFreeAmt()
   {
      return _USFreeAmt;
   }
	
   /**
    * Gets the US DSCFreeAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the US DSCFreeAmt or the specified default value.
    */
   public final String getUSFreeAmt( String defaultValue )
   {
      return _USFreeAmt == null ? defaultValue : _USFreeAmt;
   }
                  
   /**
    * Gets the US GrossAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the US GrossAmt or null.
    */
   public final String getUSTotalGrossAmt()
   {
      return _USTotalGrossAmt;
   }
	
   /**
    * Gets the US GrossAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the US GrossAmt or the specified default value.
    */
   public final String getUSTotalGrossAmt( String defaultValue )
   {
      return _USTotalGrossAmt == null ? defaultValue : _USTotalGrossAmt;
   }
                  
   /**
    * Gets the US DednAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the US DednAmt or null.
    */
   public final String getUSTotalDeductAmt()
   {
      return _USTotalDeductAmt;
   }
	
   /**
    * Gets the US DednAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the US DednAmt or the specified default value.
    */
   public final String getUSTotalDeductAmt( String defaultValue )
   {
      return _USTotalDeductAmt == null ? defaultValue : _USTotalDeductAmt;
   }
                  
   /**
    * Gets the US NetAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the US NetAmt or null.
    */
   public final String getUSTotalNetAmt()
   {
      return _USTotalNetAmt;
   }
	
   /**
    * Gets the US NetAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the US NetAmt or the specified default value.
    */
   public final String getUSTotalNetAmt( String defaultValue )
   {
      return _USTotalNetAmt == null ? defaultValue : _USTotalNetAmt;
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
    * Gets the FundID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundID or null.
    */
   public final String getrxBaycom( int index )
   {
      return _rxBaycom[index];
   }
    
   /**
    * Gets the FundID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundID or the specified default value.
    */
   public final String getrxBaycom( int index, String defaultValue )
   {
      return _rxBaycom[index] == null ? defaultValue : _rxBaycom[index];
   }
    
   /**
    * Gets the array of FundID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundID values.
    */
   public final String[] getrxBaycomArray()
   {
      return _rxBaycom;
   }
    
   /**
    * Gets the FundCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundCode or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the FundCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundCode or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of FundCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundCode values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ClassCode or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ClassCode or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of ClassCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ClassCode values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the FundCurrency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundCurrency or null.
    */
   public final String getFundCurrency( int index )
   {
      return _FundCurrency[index];
   }
    
   /**
    * Gets the FundCurrency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundCurrency or the specified default value.
    */
   public final String getFundCurrency( int index, String defaultValue )
   {
      return _FundCurrency[index] == null ? defaultValue : _FundCurrency[index];
   }
    
   /**
    * Gets the array of FundCurrency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundCurrency values.
    */
   public final String[] getFundCurrencyArray()
   {
      return _FundCurrency;
   }
    
   /**
    * Gets the LastPriced field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LastPriced or null.
    */
   public final Date getLastValDate( int index )
   {
      return _LastValDate[index];
   }
    
   /**
    * Gets the LastPriced field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LastPriced or the specified default value.
    */
   public final Date getLastValDate( int index, Date defaultValue )
   {
      return _LastValDate[index] == null ? defaultValue : _LastValDate[index];
   }
    
   /**
    * Gets the array of LastPriced fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LastPriced values.
    */
   public final Date[] getLastValDateArray()
   {
      return _LastValDate;
   }
    
   /**
    * Gets the NAV field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NAV or null.
    */
   public final String getUnitPrice( int index )
   {
      return _UnitPrice[index];
   }
    
   /**
    * Gets the NAV field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NAV or the specified default value.
    */
   public final String getUnitPrice( int index, String defaultValue )
   {
      return _UnitPrice[index] == null ? defaultValue : _UnitPrice[index];
   }
    
   /**
    * Gets the array of NAV fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NAV values.
    */
   public final String[] getUnitPriceArray()
   {
      return _UnitPrice;
   }
    
   /**
    * Gets the Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Units or null.
    */
   public final String getUnits( int index )
   {
      return _Units[index];
   }
    
   /**
    * Gets the Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Units or the specified default value.
    */
   public final String getUnits( int index, String defaultValue )
   {
      return _Units[index] == null ? defaultValue : _Units[index];
   }
    
   /**
    * Gets the array of Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Units values.
    */
   public final String[] getUnitsArray()
   {
      return _Units;
   }
    
   /**
    * Gets the GrossNetRedemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GrossNetRedemption or null.
    */
   public final Boolean getrxGrossOrNet( int index )
   {
      return _rxGrossOrNet[index];
   }
    
   /**
    * Gets the GrossNetRedemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrossNetRedemption or the specified default value.
    */
   public final boolean getrxGrossOrNet( int index, boolean defaultValue )
   {
      return _rxGrossOrNet[index] == null ? defaultValue : _rxGrossOrNet[index].booleanValue();
   }
    
   /**
    * Gets the array of GrossNetRedemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GrossNetRedemption values.
    */
   public final Boolean[] getrxGrossOrNetArray()
   {
      return _rxGrossOrNet;
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount or null.
    */
   public final String getGrossAmt( int index )
   {
      return _GrossAmt[index];
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getGrossAmt( int index, String defaultValue )
   {
      return _GrossAmt[index] == null ? defaultValue : _GrossAmt[index];
   }
    
   /**
    * Gets the array of Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount values.
    */
   public final String[] getGrossAmtArray()
   {
      return _GrossAmt;
   }
    
   /**
    * Gets the NetAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NetAmt or null.
    */
   public final String getNetAmt( int index )
   {
      return _NetAmt[index];
   }
    
   /**
    * Gets the NetAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NetAmt or the specified default value.
    */
   public final String getNetAmt( int index, String defaultValue )
   {
      return _NetAmt[index] == null ? defaultValue : _NetAmt[index];
   }
    
   /**
    * Gets the array of NetAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NetAmt values.
    */
   public final String[] getNetAmtArray()
   {
      return _NetAmt;
   }
    
   /**
    * Gets the ClientCommission field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ClientCommission or null.
    */
   public final String getCommission( int index )
   {
      return _Commission[index];
   }
    
   /**
    * Gets the ClientCommission field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ClientCommission or the specified default value.
    */
   public final String getCommission( int index, String defaultValue )
   {
      return _Commission[index] == null ? defaultValue : _Commission[index];
   }
    
   /**
    * Gets the array of ClientCommission fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ClientCommission values.
    */
   public final String[] getCommissionArray()
   {
      return _Commission;
   }
    
   /**
    * Gets the Fees field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fees or null.
    */
   public final String getFees( int index )
   {
      return _Fees[index];
   }
    
   /**
    * Gets the Fees field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fees or the specified default value.
    */
   public final String getFees( int index, String defaultValue )
   {
      return _Fees[index] == null ? defaultValue : _Fees[index];
   }
    
   /**
    * Gets the array of Fees fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fees values.
    */
   public final String[] getFeesArray()
   {
      return _Fees;
   }
    
   /**
    * Gets the ShortTermFee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ShortTermFee or null.
    */
   public final String getShortTermFee( int index )
   {
      return _ShortTermFee[index];
   }
    
   /**
    * Gets the ShortTermFee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ShortTermFee or the specified default value.
    */
   public final String getShortTermFee( int index, String defaultValue )
   {
      return _ShortTermFee[index] == null ? defaultValue : _ShortTermFee[index];
   }
    
   /**
    * Gets the array of ShortTermFee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ShortTermFee values.
    */
   public final String[] getShortTermFeeArray()
   {
      return _ShortTermFee;
   }
    
   /**
    * Gets the AdminFee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AdminFee or null.
    */
   public final String getAdminFee( int index )
   {
      return _AdminFee[index];
   }
    
   /**
    * Gets the AdminFee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AdminFee or the specified default value.
    */
   public final String getAdminFee( int index, String defaultValue )
   {
      return _AdminFee[index] == null ? defaultValue : _AdminFee[index];
   }
    
   /**
    * Gets the array of AdminFee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AdminFee values.
    */
   public final String[] getAdminFeeArray()
   {
      return _AdminFee;
   }
    
   /**
    * Gets the MgmtFee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MgmtFee or null.
    */
   public final String getMgmtFee( int index )
   {
      return _MgmtFee[index];
   }
    
   /**
    * Gets the MgmtFee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MgmtFee or the specified default value.
    */
   public final String getMgmtFee( int index, String defaultValue )
   {
      return _MgmtFee[index] == null ? defaultValue : _MgmtFee[index];
   }
    
   /**
    * Gets the array of MgmtFee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MgmtFee values.
    */
   public final String[] getMgmtFeeArray()
   {
      return _MgmtFee;
   }
    
   /**
    * Gets the PerformFee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PerformFee or null.
    */
   public final String getPerformFee( int index )
   {
      return _PerformFee[index];
   }
    
   /**
    * Gets the PerformFee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PerformFee or the specified default value.
    */
   public final String getPerformFee( int index, String defaultValue )
   {
      return _PerformFee[index] == null ? defaultValue : _PerformFee[index];
   }
    
   /**
    * Gets the array of PerformFee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PerformFee values.
    */
   public final String[] getPerformFeeArray()
   {
      return _PerformFee;
   }
    
   /**
    * Gets the OtherFee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OtherFee or null.
    */
   public final String getOtherFee( int index )
   {
      return _OtherFee[index];
   }
    
   /**
    * Gets the OtherFee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OtherFee or the specified default value.
    */
   public final String getOtherFee( int index, String defaultValue )
   {
      return _OtherFee[index] == null ? defaultValue : _OtherFee[index];
   }
    
   /**
    * Gets the array of OtherFee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OtherFee values.
    */
   public final String[] getOtherFeeArray()
   {
      return _OtherFee;
   }
    
   /**
    * Gets the Penalty field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Penalty or null.
    */
   public final String getPenalty( int index )
   {
      return _Penalty[index];
   }
    
   /**
    * Gets the Penalty field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Penalty or the specified default value.
    */
   public final String getPenalty( int index, String defaultValue )
   {
      return _Penalty[index] == null ? defaultValue : _Penalty[index];
   }
    
   /**
    * Gets the array of Penalty fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Penalty values.
    */
   public final String[] getPenaltyArray()
   {
      return _Penalty;
   }
    
   /**
    * Gets the DSC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC or null.
    */
   public final String getDSC( int index )
   {
      return _DSC[index];
   }
    
   /**
    * Gets the DSC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC or the specified default value.
    */
   public final String getDSC( int index, String defaultValue )
   {
      return _DSC[index] == null ? defaultValue : _DSC[index];
   }
    
   /**
    * Gets the array of DSC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC values.
    */
   public final String[] getDSCArray()
   {
      return _DSC;
   }
    
   /**
    * Gets the GST field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GST or null.
    */
   public final String getGST( int index )
   {
      return _GST[index];
   }
    
   /**
    * Gets the GST field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GST or the specified default value.
    */
   public final String getGST( int index, String defaultValue )
   {
      return _GST[index] == null ? defaultValue : _GST[index];
   }
    
   /**
    * Gets the array of GST fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GST values.
    */
   public final String[] getGSTArray()
   {
      return _GST;
   }
    
   /**
    * Gets the WHoldTax1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the WHoldTax1 or null.
    */
   public final String getFedTax( int index )
   {
      return _FedTax[index];
   }
    
   /**
    * Gets the WHoldTax1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the WHoldTax1 or the specified default value.
    */
   public final String getFedTax( int index, String defaultValue )
   {
      return _FedTax[index] == null ? defaultValue : _FedTax[index];
   }
    
   /**
    * Gets the array of WHoldTax1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of WHoldTax1 values.
    */
   public final String[] getFedTaxArray()
   {
      return _FedTax;
   }
    
   /**
    * Gets the WHoldTax2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the WHoldTax2 or null.
    */
   public final String getProvTax( int index )
   {
      return _ProvTax[index];
   }
    
   /**
    * Gets the WHoldTax2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the WHoldTax2 or the specified default value.
    */
   public final String getProvTax( int index, String defaultValue )
   {
      return _ProvTax[index] == null ? defaultValue : _ProvTax[index];
   }
    
   /**
    * Gets the array of WHoldTax2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of WHoldTax2 values.
    */
   public final String[] getProvTaxArray()
   {
      return _ProvTax;
   }
    
   /**
    * Gets the LSIFClawbackFed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LSIFClawbackFed or null.
    */
   public final String getLSIFClawbackFed( int index )
   {
      return _LSIFClawbackFed[index];
   }
    
   /**
    * Gets the LSIFClawbackFed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LSIFClawbackFed or the specified default value.
    */
   public final String getLSIFClawbackFed( int index, String defaultValue )
   {
      return _LSIFClawbackFed[index] == null ? defaultValue : _LSIFClawbackFed[index];
   }
    
   /**
    * Gets the array of LSIFClawbackFed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LSIFClawbackFed values.
    */
   public final String[] getLSIFClawbackFedArray()
   {
      return _LSIFClawbackFed;
   }
    
   /**
    * Gets the LSIFClawbackProv field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LSIFClawbackProv or null.
    */
   public final String getLSIFClawbackProv( int index )
   {
      return _LSIFClawbackProv[index];
   }
    
   /**
    * Gets the LSIFClawbackProv field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LSIFClawbackProv or the specified default value.
    */
   public final String getLSIFClawbackProv( int index, String defaultValue )
   {
      return _LSIFClawbackProv[index] == null ? defaultValue : _LSIFClawbackProv[index];
   }
    
   /**
    * Gets the array of LSIFClawbackProv fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LSIFClawbackProv values.
    */
   public final String[] getLSIFClawbackProvArray()
   {
      return _LSIFClawbackProv;
   }
    
   /**
    * Gets the Clawback field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Clawback or null.
    */
   public final String getClawback( int index )
   {
      return _Clawback[index];
   }
    
   /**
    * Gets the Clawback field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Clawback or the specified default value.
    */
   public final String getClawback( int index, String defaultValue )
   {
      return _Clawback[index] == null ? defaultValue : _Clawback[index];
   }
    
   /**
    * Gets the array of Clawback fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Clawback values.
    */
   public final String[] getClawbackArray()
   {
      return _Clawback;
   }
    
   /**
    * Gets the Total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Total or null.
    */
   public final String getTotalFees( int index )
   {
      return _TotalFees[index];
   }
    
   /**
    * Gets the Total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total or the specified default value.
    */
   public final String getTotalFees( int index, String defaultValue )
   {
      return _TotalFees[index] == null ? defaultValue : _TotalFees[index];
   }
    
   /**
    * Gets the array of Total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Total values.
    */
   public final String[] getTotalFeesArray()
   {
      return _TotalFees;
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
      _CDNFundsExist = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _USFundsExist = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CDNFreeAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _CDNTotalGrossAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _CDNTotalDeductAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _CDNTotalNetAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _USFreeAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _USTotalGrossAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _USTotalDeductAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _USTotalNetAmt = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxBaycom = resizeArray( _rxBaycom, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _FundCurrency = resizeArray( _FundCurrency, _RepeatCount );
      _LastValDate = resizeArray( _LastValDate, _RepeatCount );
      _UnitPrice = resizeArray( _UnitPrice, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _rxGrossOrNet = resizeArray( _rxGrossOrNet, _RepeatCount );
      _GrossAmt = resizeArray( _GrossAmt, _RepeatCount );
      _NetAmt = resizeArray( _NetAmt, _RepeatCount );
      _Commission = resizeArray( _Commission, _RepeatCount );
      _Fees = resizeArray( _Fees, _RepeatCount );
      _ShortTermFee = resizeArray( _ShortTermFee, _RepeatCount );
      _AdminFee = resizeArray( _AdminFee, _RepeatCount );
      _MgmtFee = resizeArray( _MgmtFee, _RepeatCount );
      _PerformFee = resizeArray( _PerformFee, _RepeatCount );
      _OtherFee = resizeArray( _OtherFee, _RepeatCount );
      _Penalty = resizeArray( _Penalty, _RepeatCount );
      _DSC = resizeArray( _DSC, _RepeatCount );
      _GST = resizeArray( _GST, _RepeatCount );
      _FedTax = resizeArray( _FedTax, _RepeatCount );
      _ProvTax = resizeArray( _ProvTax, _RepeatCount );
      _LSIFClawbackFed = resizeArray( _LSIFClawbackFed, _RepeatCount );
      _LSIFClawbackProv = resizeArray( _LSIFClawbackProv, _RepeatCount );
      _Clawback = resizeArray( _Clawback, _RepeatCount );
      _TotalFees = resizeArray( _TotalFees, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxBaycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastValDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UnitPrice[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxGrossOrNet[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GrossAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Commission[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Fees[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShortTermFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdminFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgmtFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PerformFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OtherFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Penalty[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DSC[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GST[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvTax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LSIFClawbackFed[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LSIFClawbackProv[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Clawback[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TotalFees[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
