
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Seg Fund Guarantee Detail Part 2 view.
 * For additional view information see <A HREF="../../../../viewspecs/SegFndGuarInq2.doc">SegFndGuarInq2.doc</A>.
 * 
 * @author RTS Generated
 */
public class SegFndGuarInq2View extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Net Asset Value before Redemption per Policy Period member array.
    */
   private String[] _NAVBefRedPeriod = null;
   
   /**
    * Net Asset Value before Redemption per Account member array.
    */
   private String[] _NAVBefRedAcct = null;
   
   /**
    * Redemption Amount per Policy Period member array.
    */
   private String[] _RedAmountPeriod = null;
   
   /**
    * Redemption Amount per Account member array.
    */
   private String[] _RedAmountAcct = null;
   
   /**
    * Percentage of NAV member array.
    */
   private String[] _Percentage = null;
   
   /**
    * Net Asset Value after Redemption per Policy Period member array.
    */
   private String[] _NAVAftRedPeriod = null;
   
   /**
    * Net Asset Value after Redemption per Account member array.
    */
   private String[] _NAVAftRedAcct = null;
   
   /**
    * Guarantee Before Redemption per Policy Period member array.
    */
   private String[] _GuarBefRedPeriod = null;
   
   /**
    * Guarantee Before Redemption per Account member array.
    */
   private String[] _GuarBefRedAcct = null;
   
   /**
    * Guarantee Reduction per Policy Period member array.
    */
   private String[] _GuarRedctnPeriod = null;
   
   /**
    * Guarantee Reduction per Account member array.
    */
   private String[] _GuarRedctnAcct = null;
   
   /**
    * Guarantee After Redemption per Policy Period member array.
    */
   private String[] _GuarAftRedPeriod = null;
   
   /**
    * Guarantee After Redemption per Account member array.
    */
   private String[] _GuarAftRedAcct = null;
   
   /**
    * New Maturity Date member array.
    */
   private Date[] _ResetMaturDate = null;
   
   /**
    * Reset Market Value member array.
    */
   private String[] _ResetNAV = null;
   
   /**
    * Previous Guarantee member array.
    */
   private String[] _PrevGuar = null;
   
   /**
    * Guarantee amount after reset member array.
    */
   private String[] _ResetGuarAmount = null;
   
   /**
    * Running Total of Guarantee member array.
    */
   private String[] _GuarRunTot = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   

   /**
    * Constructs the SegFndGuarInq2View object.
    * 
    */
   public SegFndGuarInq2View()
   {
      super ( new SegFndGuarInq2Request() );
   }

   /**
    * Constructs the SegFndGuarInq2View object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SegFndGuarInq2View( String hostEncoding )
   {
      super ( new SegFndGuarInq2Request( hostEncoding ) );
   }

   /**
    * Gets the SegFndGuarInq2Request object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SegFndGuarInq2Request object.
    */
   public final SegFndGuarInq2Request getRequest()
   {
      return (SegFndGuarInq2Request)getIFastRequest();
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
    * Gets the Net Asset Value before Redemption per Policy Period field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net Asset Value before Redemption per Policy Period or null.
    */
   public final String getNAVBefRedPeriod( int index )
   {
      return _NAVBefRedPeriod[index];
   }
    
   /**
    * Gets the Net Asset Value before Redemption per Policy Period field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Asset Value before Redemption per Policy Period or the specified default value.
    */
   public final String getNAVBefRedPeriod( int index, String defaultValue )
   {
      return _NAVBefRedPeriod[index] == null ? defaultValue : _NAVBefRedPeriod[index];
   }
    
   /**
    * Gets the array of Net Asset Value before Redemption per Policy Period fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net Asset Value before Redemption per Policy Period values.
    */
   public final String[] getNAVBefRedPeriodArray()
   {
      return _NAVBefRedPeriod;
   }
    
   /**
    * Gets the Net Asset Value before Redemption per Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net Asset Value before Redemption per Account or null.
    */
   public final String getNAVBefRedAcct( int index )
   {
      return _NAVBefRedAcct[index];
   }
    
   /**
    * Gets the Net Asset Value before Redemption per Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Asset Value before Redemption per Account or the specified default value.
    */
   public final String getNAVBefRedAcct( int index, String defaultValue )
   {
      return _NAVBefRedAcct[index] == null ? defaultValue : _NAVBefRedAcct[index];
   }
    
   /**
    * Gets the array of Net Asset Value before Redemption per Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net Asset Value before Redemption per Account values.
    */
   public final String[] getNAVBefRedAcctArray()
   {
      return _NAVBefRedAcct;
   }
    
   /**
    * Gets the Redemption Amount per Policy Period field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Amount per Policy Period or null.
    */
   public final String getRedAmountPeriod( int index )
   {
      return _RedAmountPeriod[index];
   }
    
   /**
    * Gets the Redemption Amount per Policy Period field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Amount per Policy Period or the specified default value.
    */
   public final String getRedAmountPeriod( int index, String defaultValue )
   {
      return _RedAmountPeriod[index] == null ? defaultValue : _RedAmountPeriod[index];
   }
    
   /**
    * Gets the array of Redemption Amount per Policy Period fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Amount per Policy Period values.
    */
   public final String[] getRedAmountPeriodArray()
   {
      return _RedAmountPeriod;
   }
    
   /**
    * Gets the Redemption Amount per Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Amount per Account or null.
    */
   public final String getRedAmountAcct( int index )
   {
      return _RedAmountAcct[index];
   }
    
   /**
    * Gets the Redemption Amount per Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Amount per Account or the specified default value.
    */
   public final String getRedAmountAcct( int index, String defaultValue )
   {
      return _RedAmountAcct[index] == null ? defaultValue : _RedAmountAcct[index];
   }
    
   /**
    * Gets the array of Redemption Amount per Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Amount per Account values.
    */
   public final String[] getRedAmountAcctArray()
   {
      return _RedAmountAcct;
   }
    
   /**
    * Gets the Percentage of NAV field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percentage of NAV or null.
    */
   public final String getPercentage( int index )
   {
      return _Percentage[index];
   }
    
   /**
    * Gets the Percentage of NAV field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage of NAV or the specified default value.
    */
   public final String getPercentage( int index, String defaultValue )
   {
      return _Percentage[index] == null ? defaultValue : _Percentage[index];
   }
    
   /**
    * Gets the array of Percentage of NAV fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percentage of NAV values.
    */
   public final String[] getPercentageArray()
   {
      return _Percentage;
   }
    
   /**
    * Gets the Net Asset Value after Redemption per Policy Period field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net Asset Value after Redemption per Policy Period or null.
    */
   public final String getNAVAftRedPeriod( int index )
   {
      return _NAVAftRedPeriod[index];
   }
    
   /**
    * Gets the Net Asset Value after Redemption per Policy Period field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Asset Value after Redemption per Policy Period or the specified default value.
    */
   public final String getNAVAftRedPeriod( int index, String defaultValue )
   {
      return _NAVAftRedPeriod[index] == null ? defaultValue : _NAVAftRedPeriod[index];
   }
    
   /**
    * Gets the array of Net Asset Value after Redemption per Policy Period fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net Asset Value after Redemption per Policy Period values.
    */
   public final String[] getNAVAftRedPeriodArray()
   {
      return _NAVAftRedPeriod;
   }
    
   /**
    * Gets the Net Asset Value after Redemption per Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net Asset Value after Redemption per Account or null.
    */
   public final String getNAVAftRedAcct( int index )
   {
      return _NAVAftRedAcct[index];
   }
    
   /**
    * Gets the Net Asset Value after Redemption per Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Asset Value after Redemption per Account or the specified default value.
    */
   public final String getNAVAftRedAcct( int index, String defaultValue )
   {
      return _NAVAftRedAcct[index] == null ? defaultValue : _NAVAftRedAcct[index];
   }
    
   /**
    * Gets the array of Net Asset Value after Redemption per Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net Asset Value after Redemption per Account values.
    */
   public final String[] getNAVAftRedAcctArray()
   {
      return _NAVAftRedAcct;
   }
    
   /**
    * Gets the Guarantee Before Redemption per Policy Period field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Before Redemption per Policy Period or null.
    */
   public final String getGuarBefRedPeriod( int index )
   {
      return _GuarBefRedPeriod[index];
   }
    
   /**
    * Gets the Guarantee Before Redemption per Policy Period field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Before Redemption per Policy Period or the specified default value.
    */
   public final String getGuarBefRedPeriod( int index, String defaultValue )
   {
      return _GuarBefRedPeriod[index] == null ? defaultValue : _GuarBefRedPeriod[index];
   }
    
   /**
    * Gets the array of Guarantee Before Redemption per Policy Period fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Before Redemption per Policy Period values.
    */
   public final String[] getGuarBefRedPeriodArray()
   {
      return _GuarBefRedPeriod;
   }
    
   /**
    * Gets the Guarantee Before Redemption per Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Before Redemption per Account or null.
    */
   public final String getGuarBefRedAcct( int index )
   {
      return _GuarBefRedAcct[index];
   }
    
   /**
    * Gets the Guarantee Before Redemption per Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Before Redemption per Account or the specified default value.
    */
   public final String getGuarBefRedAcct( int index, String defaultValue )
   {
      return _GuarBefRedAcct[index] == null ? defaultValue : _GuarBefRedAcct[index];
   }
    
   /**
    * Gets the array of Guarantee Before Redemption per Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Before Redemption per Account values.
    */
   public final String[] getGuarBefRedAcctArray()
   {
      return _GuarBefRedAcct;
   }
    
   /**
    * Gets the Guarantee Reduction per Policy Period field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Reduction per Policy Period or null.
    */
   public final String getGuarRedctnPeriod( int index )
   {
      return _GuarRedctnPeriod[index];
   }
    
   /**
    * Gets the Guarantee Reduction per Policy Period field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Reduction per Policy Period or the specified default value.
    */
   public final String getGuarRedctnPeriod( int index, String defaultValue )
   {
      return _GuarRedctnPeriod[index] == null ? defaultValue : _GuarRedctnPeriod[index];
   }
    
   /**
    * Gets the array of Guarantee Reduction per Policy Period fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Reduction per Policy Period values.
    */
   public final String[] getGuarRedctnPeriodArray()
   {
      return _GuarRedctnPeriod;
   }
    
   /**
    * Gets the Guarantee Reduction per Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Reduction per Account or null.
    */
   public final String getGuarRedctnAcct( int index )
   {
      return _GuarRedctnAcct[index];
   }
    
   /**
    * Gets the Guarantee Reduction per Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Reduction per Account or the specified default value.
    */
   public final String getGuarRedctnAcct( int index, String defaultValue )
   {
      return _GuarRedctnAcct[index] == null ? defaultValue : _GuarRedctnAcct[index];
   }
    
   /**
    * Gets the array of Guarantee Reduction per Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Reduction per Account values.
    */
   public final String[] getGuarRedctnAcctArray()
   {
      return _GuarRedctnAcct;
   }
    
   /**
    * Gets the Guarantee After Redemption per Policy Period field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee After Redemption per Policy Period or null.
    */
   public final String getGuarAftRedPeriod( int index )
   {
      return _GuarAftRedPeriod[index];
   }
    
   /**
    * Gets the Guarantee After Redemption per Policy Period field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee After Redemption per Policy Period or the specified default value.
    */
   public final String getGuarAftRedPeriod( int index, String defaultValue )
   {
      return _GuarAftRedPeriod[index] == null ? defaultValue : _GuarAftRedPeriod[index];
   }
    
   /**
    * Gets the array of Guarantee After Redemption per Policy Period fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee After Redemption per Policy Period values.
    */
   public final String[] getGuarAftRedPeriodArray()
   {
      return _GuarAftRedPeriod;
   }
    
   /**
    * Gets the Guarantee After Redemption per Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee After Redemption per Account or null.
    */
   public final String getGuarAftRedAcct( int index )
   {
      return _GuarAftRedAcct[index];
   }
    
   /**
    * Gets the Guarantee After Redemption per Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee After Redemption per Account or the specified default value.
    */
   public final String getGuarAftRedAcct( int index, String defaultValue )
   {
      return _GuarAftRedAcct[index] == null ? defaultValue : _GuarAftRedAcct[index];
   }
    
   /**
    * Gets the array of Guarantee After Redemption per Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee After Redemption per Account values.
    */
   public final String[] getGuarAftRedAcctArray()
   {
      return _GuarAftRedAcct;
   }
    
   /**
    * Gets the New Maturity Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the New Maturity Date or null.
    */
   public final Date getResetMaturDate( int index )
   {
      return _ResetMaturDate[index];
   }
    
   /**
    * Gets the New Maturity Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the New Maturity Date or the specified default value.
    */
   public final Date getResetMaturDate( int index, Date defaultValue )
   {
      return _ResetMaturDate[index] == null ? defaultValue : _ResetMaturDate[index];
   }
    
   /**
    * Gets the array of New Maturity Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of New Maturity Date values.
    */
   public final Date[] getResetMaturDateArray()
   {
      return _ResetMaturDate;
   }
    
   /**
    * Gets the Reset Market Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reset Market Value or null.
    */
   public final String getResetNAV( int index )
   {
      return _ResetNAV[index];
   }
    
   /**
    * Gets the Reset Market Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reset Market Value or the specified default value.
    */
   public final String getResetNAV( int index, String defaultValue )
   {
      return _ResetNAV[index] == null ? defaultValue : _ResetNAV[index];
   }
    
   /**
    * Gets the array of Reset Market Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reset Market Value values.
    */
   public final String[] getResetNAVArray()
   {
      return _ResetNAV;
   }
    
   /**
    * Gets the Previous Guarantee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Previous Guarantee or null.
    */
   public final String getPrevGuar( int index )
   {
      return _PrevGuar[index];
   }
    
   /**
    * Gets the Previous Guarantee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Previous Guarantee or the specified default value.
    */
   public final String getPrevGuar( int index, String defaultValue )
   {
      return _PrevGuar[index] == null ? defaultValue : _PrevGuar[index];
   }
    
   /**
    * Gets the array of Previous Guarantee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Previous Guarantee values.
    */
   public final String[] getPrevGuarArray()
   {
      return _PrevGuar;
   }
    
   /**
    * Gets the Guarantee amount after reset field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee amount after reset or null.
    */
   public final String getResetGuarAmount( int index )
   {
      return _ResetGuarAmount[index];
   }
    
   /**
    * Gets the Guarantee amount after reset field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee amount after reset or the specified default value.
    */
   public final String getResetGuarAmount( int index, String defaultValue )
   {
      return _ResetGuarAmount[index] == null ? defaultValue : _ResetGuarAmount[index];
   }
    
   /**
    * Gets the array of Guarantee amount after reset fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee amount after reset values.
    */
   public final String[] getResetGuarAmountArray()
   {
      return _ResetGuarAmount;
   }
    
   /**
    * Gets the Running Total of Guarantee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Running Total of Guarantee or null.
    */
   public final String getGuarRunTot( int index )
   {
      return _GuarRunTot[index];
   }
    
   /**
    * Gets the Running Total of Guarantee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Running Total of Guarantee or the specified default value.
    */
   public final String getGuarRunTot( int index, String defaultValue )
   {
      return _GuarRunTot[index] == null ? defaultValue : _GuarRunTot[index];
   }
    
   /**
    * Gets the array of Running Total of Guarantee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Running Total of Guarantee values.
    */
   public final String[] getGuarRunTotArray()
   {
      return _GuarRunTot;
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Date or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Date or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Date values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
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
      
      _NAVBefRedPeriod = resizeArray( _NAVBefRedPeriod, _RepeatCount );
      _NAVBefRedAcct = resizeArray( _NAVBefRedAcct, _RepeatCount );
      _RedAmountPeriod = resizeArray( _RedAmountPeriod, _RepeatCount );
      _RedAmountAcct = resizeArray( _RedAmountAcct, _RepeatCount );
      _Percentage = resizeArray( _Percentage, _RepeatCount );
      _NAVAftRedPeriod = resizeArray( _NAVAftRedPeriod, _RepeatCount );
      _NAVAftRedAcct = resizeArray( _NAVAftRedAcct, _RepeatCount );
      _GuarBefRedPeriod = resizeArray( _GuarBefRedPeriod, _RepeatCount );
      _GuarBefRedAcct = resizeArray( _GuarBefRedAcct, _RepeatCount );
      _GuarRedctnPeriod = resizeArray( _GuarRedctnPeriod, _RepeatCount );
      _GuarRedctnAcct = resizeArray( _GuarRedctnAcct, _RepeatCount );
      _GuarAftRedPeriod = resizeArray( _GuarAftRedPeriod, _RepeatCount );
      _GuarAftRedAcct = resizeArray( _GuarAftRedAcct, _RepeatCount );
      _ResetMaturDate = resizeArray( _ResetMaturDate, _RepeatCount );
      _ResetNAV = resizeArray( _ResetNAV, _RepeatCount );
      _PrevGuar = resizeArray( _PrevGuar, _RepeatCount );
      _ResetGuarAmount = resizeArray( _ResetGuarAmount, _RepeatCount );
      _GuarRunTot = resizeArray( _GuarRunTot, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _NAVBefRedPeriod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NAVBefRedAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedAmountPeriod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedAmountAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Percentage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NAVAftRedPeriod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NAVAftRedAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuarBefRedPeriod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuarBefRedAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuarRedctnPeriod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuarRedctnAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuarAftRedPeriod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuarAftRedAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ResetMaturDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ResetNAV[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PrevGuar[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ResetGuarAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuarRunTot[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
