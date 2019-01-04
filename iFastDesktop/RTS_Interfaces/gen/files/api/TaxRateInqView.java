
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Tax Rate Information Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/TaxRateInq.doc">TaxRateInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TaxRateInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * TaxJurisCode member array.
    */
   private String[] _TaxJurisCode = null;
   
   /**
    * TaxJurisName member array.
    */
   private String[] _TaxJurisName = null;
   
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * FedIncRate member array.
    */
   private String[] _FedIncRate = null;
   
   /**
    * FedRedRate member array.
    */
   private String[] _FedRedRate = null;
   
   /**
    * ProvIncRate member array.
    */
   private String[] _ProvIncRate = null;
   
   /**
    * ProvRedRate member array.
    */
   private String[] _ProvRedRate = null;
   
   /**
    * ProcessDate member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * LowerBound member array.
    */
   private String[] _LowerBound = null;
   
   /**
    * UpperBound member array.
    */
   private String[] _UpperBound = null;
   
   /**
    * PerPenRate member array.
    */
   private String[] _PerPenRate = null;
   
   /**
    * LumpPenRate member array.
    */
   private String[] _LumpPenRate = null;
   
   /**
    * PAmtThreasholdCode member array.
    */
   private String[] _PAmtThreasholdCode = null;
   
   /**
    * PAmtThreasholdDesc member array.
    */
   private String[] _PAmtThreasholdDesc = null;
   
   /**
    * UserName member array.
    */
   private String[] _Username = null;
   
   /**
    * ModDate member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * ModName member array.
    */
   private String[] _ModName = null;
   
   /**
    * TaxRateRid member array.
    */
   private Integer[] _TaxRateRid = null;
   

   /**
    * Constructs the TaxRateInqView object.
    * 
    */
   public TaxRateInqView()
   {
      super ( new TaxRateInqRequest() );
   }

   /**
    * Constructs the TaxRateInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TaxRateInqView( String hostEncoding )
   {
      super ( new TaxRateInqRequest( hostEncoding ) );
   }

   /**
    * Gets the TaxRateInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TaxRateInqRequest object.
    */
   public final TaxRateInqRequest getRequest()
   {
      return (TaxRateInqRequest)getIFastRequest();
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
    * Gets the TaxJurisCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TaxJurisCode or null.
    */
   public final String getTaxJurisCode( int index )
   {
      return _TaxJurisCode[index];
   }
    
   /**
    * Gets the TaxJurisCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TaxJurisCode or the specified default value.
    */
   public final String getTaxJurisCode( int index, String defaultValue )
   {
      return _TaxJurisCode[index] == null ? defaultValue : _TaxJurisCode[index];
   }
    
   /**
    * Gets the array of TaxJurisCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TaxJurisCode values.
    */
   public final String[] getTaxJurisCodeArray()
   {
      return _TaxJurisCode;
   }
    
   /**
    * Gets the TaxJurisName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TaxJurisName or null.
    */
   public final String getTaxJurisName( int index )
   {
      return _TaxJurisName[index];
   }
    
   /**
    * Gets the TaxJurisName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TaxJurisName or the specified default value.
    */
   public final String getTaxJurisName( int index, String defaultValue )
   {
      return _TaxJurisName[index] == null ? defaultValue : _TaxJurisName[index];
   }
    
   /**
    * Gets the array of TaxJurisName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TaxJurisName values.
    */
   public final String[] getTaxJurisNameArray()
   {
      return _TaxJurisName;
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EffectiveDate or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EffectiveDate or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of EffectiveDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EffectiveDate values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the FedIncRate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FedIncRate or null.
    */
   public final String getFedIncRate( int index )
   {
      return _FedIncRate[index];
   }
    
   /**
    * Gets the FedIncRate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FedIncRate or the specified default value.
    */
   public final String getFedIncRate( int index, String defaultValue )
   {
      return _FedIncRate[index] == null ? defaultValue : _FedIncRate[index];
   }
    
   /**
    * Gets the array of FedIncRate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FedIncRate values.
    */
   public final String[] getFedIncRateArray()
   {
      return _FedIncRate;
   }
    
   /**
    * Gets the FedRedRate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FedRedRate or null.
    */
   public final String getFedRedRate( int index )
   {
      return _FedRedRate[index];
   }
    
   /**
    * Gets the FedRedRate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FedRedRate or the specified default value.
    */
   public final String getFedRedRate( int index, String defaultValue )
   {
      return _FedRedRate[index] == null ? defaultValue : _FedRedRate[index];
   }
    
   /**
    * Gets the array of FedRedRate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FedRedRate values.
    */
   public final String[] getFedRedRateArray()
   {
      return _FedRedRate;
   }
    
   /**
    * Gets the ProvIncRate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProvIncRate or null.
    */
   public final String getProvIncRate( int index )
   {
      return _ProvIncRate[index];
   }
    
   /**
    * Gets the ProvIncRate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProvIncRate or the specified default value.
    */
   public final String getProvIncRate( int index, String defaultValue )
   {
      return _ProvIncRate[index] == null ? defaultValue : _ProvIncRate[index];
   }
    
   /**
    * Gets the array of ProvIncRate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProvIncRate values.
    */
   public final String[] getProvIncRateArray()
   {
      return _ProvIncRate;
   }
    
   /**
    * Gets the ProvRedRate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProvRedRate or null.
    */
   public final String getProvRedRate( int index )
   {
      return _ProvRedRate[index];
   }
    
   /**
    * Gets the ProvRedRate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProvRedRate or the specified default value.
    */
   public final String getProvRedRate( int index, String defaultValue )
   {
      return _ProvRedRate[index] == null ? defaultValue : _ProvRedRate[index];
   }
    
   /**
    * Gets the array of ProvRedRate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProvRedRate values.
    */
   public final String[] getProvRedRateArray()
   {
      return _ProvRedRate;
   }
    
   /**
    * Gets the ProcessDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProcessDate or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the ProcessDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProcessDate or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of ProcessDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProcessDate values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the LowerBound field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LowerBound or null.
    */
   public final String getLowerBound( int index )
   {
      return _LowerBound[index];
   }
    
   /**
    * Gets the LowerBound field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LowerBound or the specified default value.
    */
   public final String getLowerBound( int index, String defaultValue )
   {
      return _LowerBound[index] == null ? defaultValue : _LowerBound[index];
   }
    
   /**
    * Gets the array of LowerBound fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LowerBound values.
    */
   public final String[] getLowerBoundArray()
   {
      return _LowerBound;
   }
    
   /**
    * Gets the UpperBound field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UpperBound or null.
    */
   public final String getUpperBound( int index )
   {
      return _UpperBound[index];
   }
    
   /**
    * Gets the UpperBound field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UpperBound or the specified default value.
    */
   public final String getUpperBound( int index, String defaultValue )
   {
      return _UpperBound[index] == null ? defaultValue : _UpperBound[index];
   }
    
   /**
    * Gets the array of UpperBound fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UpperBound values.
    */
   public final String[] getUpperBoundArray()
   {
      return _UpperBound;
   }
    
   /**
    * Gets the PerPenRate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PerPenRate or null.
    */
   public final String getPerPenRate( int index )
   {
      return _PerPenRate[index];
   }
    
   /**
    * Gets the PerPenRate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PerPenRate or the specified default value.
    */
   public final String getPerPenRate( int index, String defaultValue )
   {
      return _PerPenRate[index] == null ? defaultValue : _PerPenRate[index];
   }
    
   /**
    * Gets the array of PerPenRate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PerPenRate values.
    */
   public final String[] getPerPenRateArray()
   {
      return _PerPenRate;
   }
    
   /**
    * Gets the LumpPenRate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LumpPenRate or null.
    */
   public final String getLumpPenRate( int index )
   {
      return _LumpPenRate[index];
   }
    
   /**
    * Gets the LumpPenRate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LumpPenRate or the specified default value.
    */
   public final String getLumpPenRate( int index, String defaultValue )
   {
      return _LumpPenRate[index] == null ? defaultValue : _LumpPenRate[index];
   }
    
   /**
    * Gets the array of LumpPenRate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LumpPenRate values.
    */
   public final String[] getLumpPenRateArray()
   {
      return _LumpPenRate;
   }
    
   /**
    * Gets the PAmtThreasholdCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PAmtThreasholdCode or null.
    */
   public final String getPAmtThreasholdCode( int index )
   {
      return _PAmtThreasholdCode[index];
   }
    
   /**
    * Gets the PAmtThreasholdCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAmtThreasholdCode or the specified default value.
    */
   public final String getPAmtThreasholdCode( int index, String defaultValue )
   {
      return _PAmtThreasholdCode[index] == null ? defaultValue : _PAmtThreasholdCode[index];
   }
    
   /**
    * Gets the array of PAmtThreasholdCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PAmtThreasholdCode values.
    */
   public final String[] getPAmtThreasholdCodeArray()
   {
      return _PAmtThreasholdCode;
   }
    
   /**
    * Gets the PAmtThreasholdDesc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PAmtThreasholdDesc or null.
    */
   public final String getPAmtThreasholdDesc( int index )
   {
      return _PAmtThreasholdDesc[index];
   }
    
   /**
    * Gets the PAmtThreasholdDesc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAmtThreasholdDesc or the specified default value.
    */
   public final String getPAmtThreasholdDesc( int index, String defaultValue )
   {
      return _PAmtThreasholdDesc[index] == null ? defaultValue : _PAmtThreasholdDesc[index];
   }
    
   /**
    * Gets the array of PAmtThreasholdDesc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PAmtThreasholdDesc values.
    */
   public final String[] getPAmtThreasholdDescArray()
   {
      return _PAmtThreasholdDesc;
   }
    
   /**
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UserName or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UserName or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of UserName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UserName values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the ModDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ModDate or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the ModDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ModDate or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of ModDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ModDate values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the ModName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ModName or null.
    */
   public final String getModName( int index )
   {
      return _ModName[index];
   }
    
   /**
    * Gets the ModName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ModName or the specified default value.
    */
   public final String getModName( int index, String defaultValue )
   {
      return _ModName[index] == null ? defaultValue : _ModName[index];
   }
    
   /**
    * Gets the array of ModName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ModName values.
    */
   public final String[] getModNameArray()
   {
      return _ModName;
   }
    
   /**
    * Gets the TaxRateRid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TaxRateRid or null.
    */
   public final Integer getTaxRateRid( int index )
   {
      return _TaxRateRid[index];
   }
    
   /**
    * Gets the TaxRateRid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TaxRateRid or the specified default value.
    */
   public final int getTaxRateRid( int index, int defaultValue )
   {
      return _TaxRateRid[index] == null ? defaultValue : _TaxRateRid[index].intValue();
   }
    
   /**
    * Gets the array of TaxRateRid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TaxRateRid values.
    */
   public final Integer[] getTaxRateRidArray()
   {
      return _TaxRateRid;
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
      
      _TaxJurisCode = resizeArray( _TaxJurisCode, _RepeatCount );
      _TaxJurisName = resizeArray( _TaxJurisName, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _FedIncRate = resizeArray( _FedIncRate, _RepeatCount );
      _FedRedRate = resizeArray( _FedRedRate, _RepeatCount );
      _ProvIncRate = resizeArray( _ProvIncRate, _RepeatCount );
      _ProvRedRate = resizeArray( _ProvRedRate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _LowerBound = resizeArray( _LowerBound, _RepeatCount );
      _UpperBound = resizeArray( _UpperBound, _RepeatCount );
      _PerPenRate = resizeArray( _PerPenRate, _RepeatCount );
      _LumpPenRate = resizeArray( _LumpPenRate, _RepeatCount );
      _PAmtThreasholdCode = resizeArray( _PAmtThreasholdCode, _RepeatCount );
      _PAmtThreasholdDesc = resizeArray( _PAmtThreasholdDesc, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModName = resizeArray( _ModName, _RepeatCount );
      _TaxRateRid = resizeArray( _TaxRateRid, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TaxJurisCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxJurisName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FedIncRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedRedRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvIncRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvRedRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LowerBound[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UpperBound[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PerPenRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LumpPenRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PAmtThreasholdCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PAmtThreasholdDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxRateRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
