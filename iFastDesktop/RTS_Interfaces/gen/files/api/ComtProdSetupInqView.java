
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Commitment Product Setup Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ComtProdSetupInq.doc">ComtProdSetupInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ComtProdSetupInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * CommitmentUUID member array.
    */
   private String[] _CommitmentUUID = null;
   
   /**
    * Commitment Code member array.
    */
   private String[] _CommitCode = null;
   
   /**
    * Commitment Description member array.
    */
   private String[] _Description = null;
   
   /**
    * Commitment Effective Date member array.
    */
   private Date[] _Deff = null;
   
   /**
    * Commitment Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Valid Tax Type List member array.
    */
   private String[] _ValidTaxTypes = null;
   
   /**
    * Valid Pay Frequency member array.
    */
   private String[] _ValidPayFreq = null;
   
   /**
    * Parent Fund member array.
    */
   private String[] _ParentFund = null;
   
   /**
    * Parent Class member array.
    */
   private String[] _ParentClass = null;
   

   /**
    * Constructs the ComtProdSetupInqView object.
    * 
    */
   public ComtProdSetupInqView()
   {
      super ( new ComtProdSetupInqRequest() );
   }

   /**
    * Constructs the ComtProdSetupInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ComtProdSetupInqView( String hostEncoding )
   {
      super ( new ComtProdSetupInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ComtProdSetupInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ComtProdSetupInqRequest object.
    */
   public final ComtProdSetupInqRequest getRequest()
   {
      return (ComtProdSetupInqRequest)getIFastRequest();
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
    * Gets the CommitmentUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CommitmentUUID or null.
    */
   public final String getCommitmentUUID( int index )
   {
      return _CommitmentUUID[index];
   }
    
   /**
    * Gets the CommitmentUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CommitmentUUID or the specified default value.
    */
   public final String getCommitmentUUID( int index, String defaultValue )
   {
      return _CommitmentUUID[index] == null ? defaultValue : _CommitmentUUID[index];
   }
    
   /**
    * Gets the array of CommitmentUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CommitmentUUID values.
    */
   public final String[] getCommitmentUUIDArray()
   {
      return _CommitmentUUID;
   }
    
   /**
    * Gets the Commitment Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Code or null.
    */
   public final String getCommitCode( int index )
   {
      return _CommitCode[index];
   }
    
   /**
    * Gets the Commitment Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Code or the specified default value.
    */
   public final String getCommitCode( int index, String defaultValue )
   {
      return _CommitCode[index] == null ? defaultValue : _CommitCode[index];
   }
    
   /**
    * Gets the array of Commitment Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Code values.
    */
   public final String[] getCommitCodeArray()
   {
      return _CommitCode;
   }
    
   /**
    * Gets the Commitment Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Description or null.
    */
   public final String getDescription( int index )
   {
      return _Description[index];
   }
    
   /**
    * Gets the Commitment Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Description or the specified default value.
    */
   public final String getDescription( int index, String defaultValue )
   {
      return _Description[index] == null ? defaultValue : _Description[index];
   }
    
   /**
    * Gets the array of Commitment Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Description values.
    */
   public final String[] getDescriptionArray()
   {
      return _Description;
   }
    
   /**
    * Gets the Commitment Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Effective Date or null.
    */
   public final Date getDeff( int index )
   {
      return _Deff[index];
   }
    
   /**
    * Gets the Commitment Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Effective Date or the specified default value.
    */
   public final Date getDeff( int index, Date defaultValue )
   {
      return _Deff[index] == null ? defaultValue : _Deff[index];
   }
    
   /**
    * Gets the array of Commitment Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Effective Date values.
    */
   public final Date[] getDeffArray()
   {
      return _Deff;
   }
    
   /**
    * Gets the Commitment Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Commitment Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Commitment Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Valid Tax Type List field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Valid Tax Type List or null.
    */
   public final String getValidTaxTypes( int index )
   {
      return _ValidTaxTypes[index];
   }
    
   /**
    * Gets the Valid Tax Type List field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valid Tax Type List or the specified default value.
    */
   public final String getValidTaxTypes( int index, String defaultValue )
   {
      return _ValidTaxTypes[index] == null ? defaultValue : _ValidTaxTypes[index];
   }
    
   /**
    * Gets the array of Valid Tax Type List fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Valid Tax Type List values.
    */
   public final String[] getValidTaxTypesArray()
   {
      return _ValidTaxTypes;
   }
    
   /**
    * Gets the Valid Pay Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Valid Pay Frequency or null.
    */
   public final String getValidPayFreq( int index )
   {
      return _ValidPayFreq[index];
   }
    
   /**
    * Gets the Valid Pay Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valid Pay Frequency or the specified default value.
    */
   public final String getValidPayFreq( int index, String defaultValue )
   {
      return _ValidPayFreq[index] == null ? defaultValue : _ValidPayFreq[index];
   }
    
   /**
    * Gets the array of Valid Pay Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Valid Pay Frequency values.
    */
   public final String[] getValidPayFreqArray()
   {
      return _ValidPayFreq;
   }
    
   /**
    * Gets the Parent Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Parent Fund or null.
    */
   public final String getParentFund( int index )
   {
      return _ParentFund[index];
   }
    
   /**
    * Gets the Parent Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Parent Fund or the specified default value.
    */
   public final String getParentFund( int index, String defaultValue )
   {
      return _ParentFund[index] == null ? defaultValue : _ParentFund[index];
   }
    
   /**
    * Gets the array of Parent Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Parent Fund values.
    */
   public final String[] getParentFundArray()
   {
      return _ParentFund;
   }
    
   /**
    * Gets the Parent Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Parent Class or null.
    */
   public final String getParentClass( int index )
   {
      return _ParentClass[index];
   }
    
   /**
    * Gets the Parent Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Parent Class or the specified default value.
    */
   public final String getParentClass( int index, String defaultValue )
   {
      return _ParentClass[index] == null ? defaultValue : _ParentClass[index];
   }
    
   /**
    * Gets the array of Parent Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Parent Class values.
    */
   public final String[] getParentClassArray()
   {
      return _ParentClass;
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
      
      _CommitmentUUID = resizeArray( _CommitmentUUID, _RepeatCount );
      _CommitCode = resizeArray( _CommitCode, _RepeatCount );
      _Description = resizeArray( _Description, _RepeatCount );
      _Deff = resizeArray( _Deff, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _ValidTaxTypes = resizeArray( _ValidTaxTypes, _RepeatCount );
      _ValidPayFreq = resizeArray( _ValidPayFreq, _RepeatCount );
      _ParentFund = resizeArray( _ParentFund, _RepeatCount );
      _ParentClass = resizeArray( _ParentClass, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _CommitmentUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommitCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Description[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Deff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ValidTaxTypes[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ValidPayFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ParentFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ParentClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
