
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * LIP Pension Jurisdiction Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/LIPPenJurisInq.doc">LIPPenJurisInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class LIPPenJurisInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Tax Type - response member array.
    */
   private String[] _rxTaxType = null;
   
   /**
    * Pension Jurisdiction member array.
    */
   private String[] _PenJuris = null;
   
   /**
    * Minimum Age member array.
    */
   private Integer[] _MinAge = null;
   
   /**
    * Maximum Age member array.
    */
   private Integer[] _MaxAge = null;
   
   /**
    * Minimum Withdrawal member array.
    */
   private Integer[] _MinWithAge = null;
   
   /**
    * Unisex member array.
    */
   private Boolean[] _Unisex = null;
   
   /**
    * SexDistinct member array.
    */
   private Boolean[] _SexDistinct = null;
   
   /**
    * CarryForUnusedMax member array.
    */
   private Boolean[] _CarryForUnusedMax = null;
   
   /**
    * Flag indicating if spouse's age can be used when calculating min member array.
    */
   private String[] _UseSpAge = null;
   
   /**
    * Tax Type Schedule for Old and New LIF member array.
    */
   private String[] _TaxTypeSchedule = null;
   
   /**
    * Date after which Purchase is not allowed member array.
    */
   private Date[] _GrandFatheredDate = null;
   
   /**
    * EligExtTrfGainLoss member array.
    */
   private Boolean[] _EligExtTrfGainLoss = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Age Calculation Based On Date member array.
    */
   private String[] _AgeCalcBasedOn = null;
   

   /**
    * Constructs the LIPPenJurisInqView object.
    * 
    */
   public LIPPenJurisInqView()
   {
      super ( new LIPPenJurisInqRequest() );
   }

   /**
    * Constructs the LIPPenJurisInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public LIPPenJurisInqView( String hostEncoding )
   {
      super ( new LIPPenJurisInqRequest( hostEncoding ) );
   }

   /**
    * Gets the LIPPenJurisInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The LIPPenJurisInqRequest object.
    */
   public final LIPPenJurisInqRequest getRequest()
   {
      return (LIPPenJurisInqRequest)getIFastRequest();
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
    * Gets the Tax Type - response field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type - response or null.
    */
   public final String getrxTaxType( int index )
   {
      return _rxTaxType[index];
   }
    
   /**
    * Gets the Tax Type - response field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type - response or the specified default value.
    */
   public final String getrxTaxType( int index, String defaultValue )
   {
      return _rxTaxType[index] == null ? defaultValue : _rxTaxType[index];
   }
    
   /**
    * Gets the array of Tax Type - response fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type - response values.
    */
   public final String[] getrxTaxTypeArray()
   {
      return _rxTaxType;
   }
    
   /**
    * Gets the Pension Jurisdiction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pension Jurisdiction or null.
    */
   public final String getPenJuris( int index )
   {
      return _PenJuris[index];
   }
    
   /**
    * Gets the Pension Jurisdiction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pension Jurisdiction or the specified default value.
    */
   public final String getPenJuris( int index, String defaultValue )
   {
      return _PenJuris[index] == null ? defaultValue : _PenJuris[index];
   }
    
   /**
    * Gets the array of Pension Jurisdiction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pension Jurisdiction values.
    */
   public final String[] getPenJurisArray()
   {
      return _PenJuris;
   }
    
   /**
    * Gets the Minimum Age field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Age or null.
    */
   public final Integer getMinAge( int index )
   {
      return _MinAge[index];
   }
    
   /**
    * Gets the Minimum Age field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Age or the specified default value.
    */
   public final int getMinAge( int index, int defaultValue )
   {
      return _MinAge[index] == null ? defaultValue : _MinAge[index].intValue();
   }
    
   /**
    * Gets the array of Minimum Age fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Age values.
    */
   public final Integer[] getMinAgeArray()
   {
      return _MinAge;
   }
    
   /**
    * Gets the Maximum Age field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maximum Age or null.
    */
   public final Integer getMaxAge( int index )
   {
      return _MaxAge[index];
   }
    
   /**
    * Gets the Maximum Age field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Age or the specified default value.
    */
   public final int getMaxAge( int index, int defaultValue )
   {
      return _MaxAge[index] == null ? defaultValue : _MaxAge[index].intValue();
   }
    
   /**
    * Gets the array of Maximum Age fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maximum Age values.
    */
   public final Integer[] getMaxAgeArray()
   {
      return _MaxAge;
   }
    
   /**
    * Gets the Minimum Withdrawal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Withdrawal or null.
    */
   public final Integer getMinWithAge( int index )
   {
      return _MinWithAge[index];
   }
    
   /**
    * Gets the Minimum Withdrawal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Withdrawal or the specified default value.
    */
   public final int getMinWithAge( int index, int defaultValue )
   {
      return _MinWithAge[index] == null ? defaultValue : _MinWithAge[index].intValue();
   }
    
   /**
    * Gets the array of Minimum Withdrawal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Withdrawal values.
    */
   public final Integer[] getMinWithAgeArray()
   {
      return _MinWithAge;
   }
    
   /**
    * Gets the Unisex field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unisex or null.
    */
   public final Boolean getUnisex( int index )
   {
      return _Unisex[index];
   }
    
   /**
    * Gets the Unisex field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unisex or the specified default value.
    */
   public final boolean getUnisex( int index, boolean defaultValue )
   {
      return _Unisex[index] == null ? defaultValue : _Unisex[index].booleanValue();
   }
    
   /**
    * Gets the array of Unisex fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unisex values.
    */
   public final Boolean[] getUnisexArray()
   {
      return _Unisex;
   }
    
   /**
    * Gets the SexDistinct field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SexDistinct or null.
    */
   public final Boolean getSexDistinct( int index )
   {
      return _SexDistinct[index];
   }
    
   /**
    * Gets the SexDistinct field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SexDistinct or the specified default value.
    */
   public final boolean getSexDistinct( int index, boolean defaultValue )
   {
      return _SexDistinct[index] == null ? defaultValue : _SexDistinct[index].booleanValue();
   }
    
   /**
    * Gets the array of SexDistinct fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SexDistinct values.
    */
   public final Boolean[] getSexDistinctArray()
   {
      return _SexDistinct;
   }
    
   /**
    * Gets the CarryForUnusedMax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CarryForUnusedMax or null.
    */
   public final Boolean getCarryForUnusedMax( int index )
   {
      return _CarryForUnusedMax[index];
   }
    
   /**
    * Gets the CarryForUnusedMax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CarryForUnusedMax or the specified default value.
    */
   public final boolean getCarryForUnusedMax( int index, boolean defaultValue )
   {
      return _CarryForUnusedMax[index] == null ? defaultValue : _CarryForUnusedMax[index].booleanValue();
   }
    
   /**
    * Gets the array of CarryForUnusedMax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CarryForUnusedMax values.
    */
   public final Boolean[] getCarryForUnusedMaxArray()
   {
      return _CarryForUnusedMax;
   }
    
   /**
    * Gets the Flag indicating if spouse's age can be used when calculating min field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if spouse's age can be used when calculating min or null.
    */
   public final String getUseSpAge( int index )
   {
      return _UseSpAge[index];
   }
    
   /**
    * Gets the Flag indicating if spouse's age can be used when calculating min field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if spouse's age can be used when calculating min or the specified default value.
    */
   public final String getUseSpAge( int index, String defaultValue )
   {
      return _UseSpAge[index] == null ? defaultValue : _UseSpAge[index];
   }
    
   /**
    * Gets the array of Flag indicating if spouse's age can be used when calculating min fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if spouse's age can be used when calculating min values.
    */
   public final String[] getUseSpAgeArray()
   {
      return _UseSpAge;
   }
    
   /**
    * Gets the Tax Type Schedule for Old and New LIF field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type Schedule for Old and New LIF or null.
    */
   public final String getTaxTypeSchedule( int index )
   {
      return _TaxTypeSchedule[index];
   }
    
   /**
    * Gets the Tax Type Schedule for Old and New LIF field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type Schedule for Old and New LIF or the specified default value.
    */
   public final String getTaxTypeSchedule( int index, String defaultValue )
   {
      return _TaxTypeSchedule[index] == null ? defaultValue : _TaxTypeSchedule[index];
   }
    
   /**
    * Gets the array of Tax Type Schedule for Old and New LIF fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type Schedule for Old and New LIF values.
    */
   public final String[] getTaxTypeScheduleArray()
   {
      return _TaxTypeSchedule;
   }
    
   /**
    * Gets the Date after which Purchase is not allowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date after which Purchase is not allowed or null.
    */
   public final Date getGrandFatheredDate( int index )
   {
      return _GrandFatheredDate[index];
   }
    
   /**
    * Gets the Date after which Purchase is not allowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date after which Purchase is not allowed or the specified default value.
    */
   public final Date getGrandFatheredDate( int index, Date defaultValue )
   {
      return _GrandFatheredDate[index] == null ? defaultValue : _GrandFatheredDate[index];
   }
    
   /**
    * Gets the array of Date after which Purchase is not allowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date after which Purchase is not allowed values.
    */
   public final Date[] getGrandFatheredDateArray()
   {
      return _GrandFatheredDate;
   }
    
   /**
    * Gets the EligExtTrfGainLoss field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EligExtTrfGainLoss or null.
    */
   public final Boolean getEligExtTrfGainLoss( int index )
   {
      return _EligExtTrfGainLoss[index];
   }
    
   /**
    * Gets the EligExtTrfGainLoss field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EligExtTrfGainLoss or the specified default value.
    */
   public final boolean getEligExtTrfGainLoss( int index, boolean defaultValue )
   {
      return _EligExtTrfGainLoss[index] == null ? defaultValue : _EligExtTrfGainLoss[index].booleanValue();
   }
    
   /**
    * Gets the array of EligExtTrfGainLoss fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EligExtTrfGainLoss values.
    */
   public final Boolean[] getEligExtTrfGainLossArray()
   {
      return _EligExtTrfGainLoss;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Age Calculation Based On Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Age Calculation Based On Date or null.
    */
   public final String getAgeCalcBasedOn( int index )
   {
      return _AgeCalcBasedOn[index];
   }
    
   /**
    * Gets the Age Calculation Based On Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Age Calculation Based On Date or the specified default value.
    */
   public final String getAgeCalcBasedOn( int index, String defaultValue )
   {
      return _AgeCalcBasedOn[index] == null ? defaultValue : _AgeCalcBasedOn[index];
   }
    
   /**
    * Gets the array of Age Calculation Based On Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Age Calculation Based On Date values.
    */
   public final String[] getAgeCalcBasedOnArray()
   {
      return _AgeCalcBasedOn;
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
      
      _rxTaxType = resizeArray( _rxTaxType, _RepeatCount );
      _PenJuris = resizeArray( _PenJuris, _RepeatCount );
      _MinAge = resizeArray( _MinAge, _RepeatCount );
      _MaxAge = resizeArray( _MaxAge, _RepeatCount );
      _MinWithAge = resizeArray( _MinWithAge, _RepeatCount );
      _Unisex = resizeArray( _Unisex, _RepeatCount );
      _SexDistinct = resizeArray( _SexDistinct, _RepeatCount );
      _CarryForUnusedMax = resizeArray( _CarryForUnusedMax, _RepeatCount );
      _UseSpAge = resizeArray( _UseSpAge, _RepeatCount );
      _TaxTypeSchedule = resizeArray( _TaxTypeSchedule, _RepeatCount );
      _GrandFatheredDate = resizeArray( _GrandFatheredDate, _RepeatCount );
      _EligExtTrfGainLoss = resizeArray( _EligExtTrfGainLoss, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _AgeCalcBasedOn = resizeArray( _AgeCalcBasedOn, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxTaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PenJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MaxAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MinWithAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Unisex[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SexDistinct[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CarryForUnusedMax[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _UseSpAge[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxTypeSchedule[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrandFatheredDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EligExtTrfGainLoss[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AgeCalcBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
