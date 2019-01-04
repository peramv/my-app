
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * PAC Indexing Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/PACIndexInq.doc">PACIndexInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PACIndexInqView extends IFastView implements Serializable
{

   /**
    * Default Index Amount member variable.
    */
   private String _DefaultIndexAmt = null;
   
   /**
    * Default Index Type member variable.
    */
   private String _DefaultIndexType = null;
   
   /**
    * Default Index Frequency member variable.
    */
   private String _DefaultIndexFreq = null;
   
   /**
    * Default Start Date member variable.
    */
   private Date _DefaultStartDate = null;
   
   /**
    * Default End Date member variable.
    */
   private Date _DefaultEndDate = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Index Amount member array.
    */
   private String[] _IndexAmt = null;
   
   /**
    * Index Type member array.
    */
   private String[] _IndexType = null;
   
   /**
    * Index Frequency member array.
    */
   private String[] _IndexFrequency = null;
   
   /**
    * Start Date member array.
    */
   private Date[] _StartDate = null;
   
   /**
    * End Date member array.
    */
   private Date[] _EndDate = null;
   
   /**
    * Next Index Date member array.
    */
   private Date[] _NextIndexDate = null;
   
   /**
    * PAC-Index record id member array.
    */
   private Integer[] _PACIndexRId = null;
   
   /**
    * PAC-Index version number member array.
    */
   private Integer[] _PACIndexVer = null;
   
   /**
    * Bank Detl record Id to match PAC-Index records with PAC record member array.
    */
   private Integer[] _PACSWPId = null;
   

   /**
    * Constructs the PACIndexInqView object.
    * 
    */
   public PACIndexInqView()
   {
      super ( new PACIndexInqRequest() );
   }

   /**
    * Constructs the PACIndexInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PACIndexInqView( String hostEncoding )
   {
      super ( new PACIndexInqRequest( hostEncoding ) );
   }

   /**
    * Gets the PACIndexInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PACIndexInqRequest object.
    */
   public final PACIndexInqRequest getRequest()
   {
      return (PACIndexInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Default Index Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Index Amount or null.
    */
   public final String getDefaultIndexAmt()
   {
      return _DefaultIndexAmt;
   }
	
   /**
    * Gets the Default Index Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Index Amount or the specified default value.
    */
   public final String getDefaultIndexAmt( String defaultValue )
   {
      return _DefaultIndexAmt == null ? defaultValue : _DefaultIndexAmt;
   }
                  
   /**
    * Gets the Default Index Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Index Type or null.
    */
   public final String getDefaultIndexType()
   {
      return _DefaultIndexType;
   }
	
   /**
    * Gets the Default Index Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Index Type or the specified default value.
    */
   public final String getDefaultIndexType( String defaultValue )
   {
      return _DefaultIndexType == null ? defaultValue : _DefaultIndexType;
   }
                  
   /**
    * Gets the Default Index Frequency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Index Frequency or null.
    */
   public final String getDefaultIndexFreq()
   {
      return _DefaultIndexFreq;
   }
	
   /**
    * Gets the Default Index Frequency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Index Frequency or the specified default value.
    */
   public final String getDefaultIndexFreq( String defaultValue )
   {
      return _DefaultIndexFreq == null ? defaultValue : _DefaultIndexFreq;
   }
                  
   /**
    * Gets the Default Start Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Start Date or null.
    */
   public final Date getDefaultStartDate()
   {
      return _DefaultStartDate;
   }
	
   /**
    * Gets the Default Start Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Start Date or the specified default value.
    */
   public final Date getDefaultStartDate( Date defaultValue )
   {
      return _DefaultStartDate == null ? defaultValue : _DefaultStartDate;
   }
                  
   /**
    * Gets the Default End Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default End Date or null.
    */
   public final Date getDefaultEndDate()
   {
      return _DefaultEndDate;
   }
	
   /**
    * Gets the Default End Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default End Date or the specified default value.
    */
   public final Date getDefaultEndDate( Date defaultValue )
   {
      return _DefaultEndDate == null ? defaultValue : _DefaultEndDate;
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
    * Gets the Index Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Index Amount or null.
    */
   public final String getIndexAmt( int index )
   {
      return _IndexAmt[index];
   }
    
   /**
    * Gets the Index Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Index Amount or the specified default value.
    */
   public final String getIndexAmt( int index, String defaultValue )
   {
      return _IndexAmt[index] == null ? defaultValue : _IndexAmt[index];
   }
    
   /**
    * Gets the array of Index Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Index Amount values.
    */
   public final String[] getIndexAmtArray()
   {
      return _IndexAmt;
   }
    
   /**
    * Gets the Index Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Index Type or null.
    */
   public final String getIndexType( int index )
   {
      return _IndexType[index];
   }
    
   /**
    * Gets the Index Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Index Type or the specified default value.
    */
   public final String getIndexType( int index, String defaultValue )
   {
      return _IndexType[index] == null ? defaultValue : _IndexType[index];
   }
    
   /**
    * Gets the array of Index Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Index Type values.
    */
   public final String[] getIndexTypeArray()
   {
      return _IndexType;
   }
    
   /**
    * Gets the Index Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Index Frequency or null.
    */
   public final String getIndexFrequency( int index )
   {
      return _IndexFrequency[index];
   }
    
   /**
    * Gets the Index Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Index Frequency or the specified default value.
    */
   public final String getIndexFrequency( int index, String defaultValue )
   {
      return _IndexFrequency[index] == null ? defaultValue : _IndexFrequency[index];
   }
    
   /**
    * Gets the array of Index Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Index Frequency values.
    */
   public final String[] getIndexFrequencyArray()
   {
      return _IndexFrequency;
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Start Date or null.
    */
   public final Date getStartDate( int index )
   {
      return _StartDate[index];
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start Date or the specified default value.
    */
   public final Date getStartDate( int index, Date defaultValue )
   {
      return _StartDate[index] == null ? defaultValue : _StartDate[index];
   }
    
   /**
    * Gets the array of Start Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Start Date values.
    */
   public final Date[] getStartDateArray()
   {
      return _StartDate;
   }
    
   /**
    * Gets the End Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the End Date or null.
    */
   public final Date getEndDate( int index )
   {
      return _EndDate[index];
   }
    
   /**
    * Gets the End Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the End Date or the specified default value.
    */
   public final Date getEndDate( int index, Date defaultValue )
   {
      return _EndDate[index] == null ? defaultValue : _EndDate[index];
   }
    
   /**
    * Gets the array of End Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of End Date values.
    */
   public final Date[] getEndDateArray()
   {
      return _EndDate;
   }
    
   /**
    * Gets the Next Index Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Next Index Date or null.
    */
   public final Date getNextIndexDate( int index )
   {
      return _NextIndexDate[index];
   }
    
   /**
    * Gets the Next Index Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Index Date or the specified default value.
    */
   public final Date getNextIndexDate( int index, Date defaultValue )
   {
      return _NextIndexDate[index] == null ? defaultValue : _NextIndexDate[index];
   }
    
   /**
    * Gets the array of Next Index Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Next Index Date values.
    */
   public final Date[] getNextIndexDateArray()
   {
      return _NextIndexDate;
   }
    
   /**
    * Gets the PAC-Index record id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PAC-Index record id or null.
    */
   public final Integer getPACIndexRId( int index )
   {
      return _PACIndexRId[index];
   }
    
   /**
    * Gets the PAC-Index record id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC-Index record id or the specified default value.
    */
   public final int getPACIndexRId( int index, int defaultValue )
   {
      return _PACIndexRId[index] == null ? defaultValue : _PACIndexRId[index].intValue();
   }
    
   /**
    * Gets the array of PAC-Index record id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PAC-Index record id values.
    */
   public final Integer[] getPACIndexRIdArray()
   {
      return _PACIndexRId;
   }
    
   /**
    * Gets the PAC-Index version number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PAC-Index version number or null.
    */
   public final Integer getPACIndexVer( int index )
   {
      return _PACIndexVer[index];
   }
    
   /**
    * Gets the PAC-Index version number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC-Index version number or the specified default value.
    */
   public final int getPACIndexVer( int index, int defaultValue )
   {
      return _PACIndexVer[index] == null ? defaultValue : _PACIndexVer[index].intValue();
   }
    
   /**
    * Gets the array of PAC-Index version number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PAC-Index version number values.
    */
   public final Integer[] getPACIndexVerArray()
   {
      return _PACIndexVer;
   }
    
   /**
    * Gets the Bank Detl record Id to match PAC-Index records with PAC record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Detl record Id to match PAC-Index records with PAC record or null.
    */
   public final Integer getPACSWPId( int index )
   {
      return _PACSWPId[index];
   }
    
   /**
    * Gets the Bank Detl record Id to match PAC-Index records with PAC record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Detl record Id to match PAC-Index records with PAC record or the specified default value.
    */
   public final int getPACSWPId( int index, int defaultValue )
   {
      return _PACSWPId[index] == null ? defaultValue : _PACSWPId[index].intValue();
   }
    
   /**
    * Gets the array of Bank Detl record Id to match PAC-Index records with PAC record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Detl record Id to match PAC-Index records with PAC record values.
    */
   public final Integer[] getPACSWPIdArray()
   {
      return _PACSWPId;
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
      _DefaultIndexAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _DefaultIndexType = responseBuffer.decodeString(responseBuffer.getNextField());
      _DefaultIndexFreq = responseBuffer.decodeString(responseBuffer.getNextField());
      _DefaultStartDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _DefaultEndDate = responseBuffer.decodeDate(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _IndexAmt = resizeArray( _IndexAmt, _RepeatCount );
      _IndexType = resizeArray( _IndexType, _RepeatCount );
      _IndexFrequency = resizeArray( _IndexFrequency, _RepeatCount );
      _StartDate = resizeArray( _StartDate, _RepeatCount );
      _EndDate = resizeArray( _EndDate, _RepeatCount );
      _NextIndexDate = resizeArray( _NextIndexDate, _RepeatCount );
      _PACIndexRId = resizeArray( _PACIndexRId, _RepeatCount );
      _PACIndexVer = resizeArray( _PACIndexVer, _RepeatCount );
      _PACSWPId = resizeArray( _PACSWPId, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _IndexAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IndexType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IndexFrequency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EndDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _NextIndexDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _PACIndexRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PACIndexVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PACSWPId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
