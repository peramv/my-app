
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Clan Plan Contract Information view.
 * For additional view information see <A HREF="../../../../viewspecs/ClanContr.doc">ClanContr.doc</A>.
 * 
 * @author RTS Generated
 */
public class ClanContrView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Clan Plan Record ID member array.
    */
   private Integer[] _ClanId = null;
   
   /**
    * Initial Factor member array.
    */
   private String[] _InitFactor = null;
   
   /**
    * Plan Term member array.
    */
   private Integer[] _PlanTerm = null;
   
   /**
    * Payment Amount member array.
    */
   private String[] _PaymentAmt = null;
   
   /**
    * Last Payment member array.
    */
   private Integer[] _LastPayment = null;
   
   /**
    * Commission member array.
    */
   private String[] _Commission = null;
   
   /**
    * Admin Fee Amount member array.
    */
   private String[] _AdminFeeAmt = null;
   
   /**
    * Initial Payment member array.
    */
   private String[] _InitPayment = null;
   
   /**
    * Rebate member array.
    */
   private String[] _Rebate = null;
   

   /**
    * Constructs the ClanContrView object.
    * 
    */
   public ClanContrView()
   {
      super ( new ClanContrRequest() );
   }

   /**
    * Constructs the ClanContrView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ClanContrView( String hostEncoding )
   {
      super ( new ClanContrRequest( hostEncoding ) );
   }

   /**
    * Gets the ClanContrRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ClanContrRequest object.
    */
   public final ClanContrRequest getRequest()
   {
      return (ClanContrRequest)getIFastRequest();
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
    * Gets the Clan Plan Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Clan Plan Record ID or null.
    */
   public final Integer getClanId( int index )
   {
      return _ClanId[index];
   }
    
   /**
    * Gets the Clan Plan Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Clan Plan Record ID or the specified default value.
    */
   public final int getClanId( int index, int defaultValue )
   {
      return _ClanId[index] == null ? defaultValue : _ClanId[index].intValue();
   }
    
   /**
    * Gets the array of Clan Plan Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Clan Plan Record ID values.
    */
   public final Integer[] getClanIdArray()
   {
      return _ClanId;
   }
    
   /**
    * Gets the Initial Factor field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Initial Factor or null.
    */
   public final String getInitFactor( int index )
   {
      return _InitFactor[index];
   }
    
   /**
    * Gets the Initial Factor field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Initial Factor or the specified default value.
    */
   public final String getInitFactor( int index, String defaultValue )
   {
      return _InitFactor[index] == null ? defaultValue : _InitFactor[index];
   }
    
   /**
    * Gets the array of Initial Factor fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Initial Factor values.
    */
   public final String[] getInitFactorArray()
   {
      return _InitFactor;
   }
    
   /**
    * Gets the Plan Term field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Plan Term or null.
    */
   public final Integer getPlanTerm( int index )
   {
      return _PlanTerm[index];
   }
    
   /**
    * Gets the Plan Term field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Plan Term or the specified default value.
    */
   public final int getPlanTerm( int index, int defaultValue )
   {
      return _PlanTerm[index] == null ? defaultValue : _PlanTerm[index].intValue();
   }
    
   /**
    * Gets the array of Plan Term fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Plan Term values.
    */
   public final Integer[] getPlanTermArray()
   {
      return _PlanTerm;
   }
    
   /**
    * Gets the Payment Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Amount or null.
    */
   public final String getPaymentAmt( int index )
   {
      return _PaymentAmt[index];
   }
    
   /**
    * Gets the Payment Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Amount or the specified default value.
    */
   public final String getPaymentAmt( int index, String defaultValue )
   {
      return _PaymentAmt[index] == null ? defaultValue : _PaymentAmt[index];
   }
    
   /**
    * Gets the array of Payment Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Amount values.
    */
   public final String[] getPaymentAmtArray()
   {
      return _PaymentAmt;
   }
    
   /**
    * Gets the Last Payment field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Payment or null.
    */
   public final Integer getLastPayment( int index )
   {
      return _LastPayment[index];
   }
    
   /**
    * Gets the Last Payment field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Payment or the specified default value.
    */
   public final int getLastPayment( int index, int defaultValue )
   {
      return _LastPayment[index] == null ? defaultValue : _LastPayment[index].intValue();
   }
    
   /**
    * Gets the array of Last Payment fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Payment values.
    */
   public final Integer[] getLastPaymentArray()
   {
      return _LastPayment;
   }
    
   /**
    * Gets the Commission field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission or null.
    */
   public final String getCommission( int index )
   {
      return _Commission[index];
   }
    
   /**
    * Gets the Commission field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission or the specified default value.
    */
   public final String getCommission( int index, String defaultValue )
   {
      return _Commission[index] == null ? defaultValue : _Commission[index];
   }
    
   /**
    * Gets the array of Commission fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission values.
    */
   public final String[] getCommissionArray()
   {
      return _Commission;
   }
    
   /**
    * Gets the Admin Fee Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Admin Fee Amount or null.
    */
   public final String getAdminFeeAmt( int index )
   {
      return _AdminFeeAmt[index];
   }
    
   /**
    * Gets the Admin Fee Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Admin Fee Amount or the specified default value.
    */
   public final String getAdminFeeAmt( int index, String defaultValue )
   {
      return _AdminFeeAmt[index] == null ? defaultValue : _AdminFeeAmt[index];
   }
    
   /**
    * Gets the array of Admin Fee Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Admin Fee Amount values.
    */
   public final String[] getAdminFeeAmtArray()
   {
      return _AdminFeeAmt;
   }
    
   /**
    * Gets the Initial Payment field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Initial Payment or null.
    */
   public final String getInitPayment( int index )
   {
      return _InitPayment[index];
   }
    
   /**
    * Gets the Initial Payment field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Initial Payment or the specified default value.
    */
   public final String getInitPayment( int index, String defaultValue )
   {
      return _InitPayment[index] == null ? defaultValue : _InitPayment[index];
   }
    
   /**
    * Gets the array of Initial Payment fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Initial Payment values.
    */
   public final String[] getInitPaymentArray()
   {
      return _InitPayment;
   }
    
   /**
    * Gets the Rebate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rebate or null.
    */
   public final String getRebate( int index )
   {
      return _Rebate[index];
   }
    
   /**
    * Gets the Rebate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rebate or the specified default value.
    */
   public final String getRebate( int index, String defaultValue )
   {
      return _Rebate[index] == null ? defaultValue : _Rebate[index];
   }
    
   /**
    * Gets the array of Rebate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rebate values.
    */
   public final String[] getRebateArray()
   {
      return _Rebate;
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
      
      _ClanId = resizeArray( _ClanId, _RepeatCount );
      _InitFactor = resizeArray( _InitFactor, _RepeatCount );
      _PlanTerm = resizeArray( _PlanTerm, _RepeatCount );
      _PaymentAmt = resizeArray( _PaymentAmt, _RepeatCount );
      _LastPayment = resizeArray( _LastPayment, _RepeatCount );
      _Commission = resizeArray( _Commission, _RepeatCount );
      _AdminFeeAmt = resizeArray( _AdminFeeAmt, _RepeatCount );
      _InitPayment = resizeArray( _InitPayment, _RepeatCount );
      _Rebate = resizeArray( _Rebate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ClanId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _InitFactor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PlanTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PaymentAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastPayment[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Commission[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdminFeeAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InitPayment[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Rebate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
