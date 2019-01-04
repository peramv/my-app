
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Regulatory Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctRegInq.doc">AcctRegInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctRegInqView extends IFastView implements Serializable
{

   /**
    * Last Review Date member variable.
    */
   private Date _LastReview = null;
   
   private int _RepeatCount = 0;
   
   /**
    * AcctRegDetailsUUID member array.
    */
   private String[] _AcctRegDetailsUUID = null;
   
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * StopDate member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * FICategory member array.
    */
   private String[] _FICategory = null;
   
   /**
    * FinInstRegDetlUUID member array.
    */
   private String[] _FinInstRegDetlUUID = null;
   
   /**
    * ComplyAction member array.
    */
   private String[] _ComplyAction = null;
   
   /**
    * Consented member array.
    */
   private String[] _Consented = null;
   
   /**
    * Version member array.
    */
   private Integer[] _Version = null;
   
   /**
    * ProcessDate member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * UserName member array.
    */
   private String[] _UserName = null;
   
   /**
    * ModDate member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * ModUser member array.
    */
   private String[] _ModUser = null;
   
   /**
    * ComplyRule member array.
    */
   private String[] _ComplyRule = null;
   
   /**
    * AcctRegDetails Record Id member array.
    */
   private Integer[] _AcctRegDetailsRId = null;
   
   /**
    * Country of Domicile member array.
    */
   private String[] _CntryDomicile = null;
   

   /**
    * Constructs the AcctRegInqView object.
    * 
    */
   public AcctRegInqView()
   {
      super ( new AcctRegInqRequest() );
   }

   /**
    * Constructs the AcctRegInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctRegInqView( String hostEncoding )
   {
      super ( new AcctRegInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctRegInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctRegInqRequest object.
    */
   public final AcctRegInqRequest getRequest()
   {
      return (AcctRegInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Last Review Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Last Review Date or null.
    */
   public final Date getLastReview()
   {
      return _LastReview;
   }
	
   /**
    * Gets the Last Review Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Review Date or the specified default value.
    */
   public final Date getLastReview( Date defaultValue )
   {
      return _LastReview == null ? defaultValue : _LastReview;
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
    * Gets the AcctRegDetailsUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctRegDetailsUUID or null.
    */
   public final String getAcctRegDetailsUUID( int index )
   {
      return _AcctRegDetailsUUID[index];
   }
    
   /**
    * Gets the AcctRegDetailsUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctRegDetailsUUID or the specified default value.
    */
   public final String getAcctRegDetailsUUID( int index, String defaultValue )
   {
      return _AcctRegDetailsUUID[index] == null ? defaultValue : _AcctRegDetailsUUID[index];
   }
    
   /**
    * Gets the array of AcctRegDetailsUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctRegDetailsUUID values.
    */
   public final String[] getAcctRegDetailsUUIDArray()
   {
      return _AcctRegDetailsUUID;
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
    * Gets the StopDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StopDate or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the StopDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopDate or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of StopDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StopDate values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the FICategory field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FICategory or null.
    */
   public final String getFICategory( int index )
   {
      return _FICategory[index];
   }
    
   /**
    * Gets the FICategory field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FICategory or the specified default value.
    */
   public final String getFICategory( int index, String defaultValue )
   {
      return _FICategory[index] == null ? defaultValue : _FICategory[index];
   }
    
   /**
    * Gets the array of FICategory fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FICategory values.
    */
   public final String[] getFICategoryArray()
   {
      return _FICategory;
   }
    
   /**
    * Gets the FinInstRegDetlUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FinInstRegDetlUUID or null.
    */
   public final String getFinInstRegDetlUUID( int index )
   {
      return _FinInstRegDetlUUID[index];
   }
    
   /**
    * Gets the FinInstRegDetlUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FinInstRegDetlUUID or the specified default value.
    */
   public final String getFinInstRegDetlUUID( int index, String defaultValue )
   {
      return _FinInstRegDetlUUID[index] == null ? defaultValue : _FinInstRegDetlUUID[index];
   }
    
   /**
    * Gets the array of FinInstRegDetlUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FinInstRegDetlUUID values.
    */
   public final String[] getFinInstRegDetlUUIDArray()
   {
      return _FinInstRegDetlUUID;
   }
    
   /**
    * Gets the ComplyAction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ComplyAction or null.
    */
   public final String getComplyAction( int index )
   {
      return _ComplyAction[index];
   }
    
   /**
    * Gets the ComplyAction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ComplyAction or the specified default value.
    */
   public final String getComplyAction( int index, String defaultValue )
   {
      return _ComplyAction[index] == null ? defaultValue : _ComplyAction[index];
   }
    
   /**
    * Gets the array of ComplyAction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ComplyAction values.
    */
   public final String[] getComplyActionArray()
   {
      return _ComplyAction;
   }
    
   /**
    * Gets the Consented field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Consented or null.
    */
   public final String getConsented( int index )
   {
      return _Consented[index];
   }
    
   /**
    * Gets the Consented field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Consented or the specified default value.
    */
   public final String getConsented( int index, String defaultValue )
   {
      return _Consented[index] == null ? defaultValue : _Consented[index];
   }
    
   /**
    * Gets the array of Consented fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Consented values.
    */
   public final String[] getConsentedArray()
   {
      return _Consented;
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version or null.
    */
   public final Integer getVersion( int index )
   {
      return _Version[index];
   }
    
   /**
    * Gets the Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version or the specified default value.
    */
   public final int getVersion( int index, int defaultValue )
   {
      return _Version[index] == null ? defaultValue : _Version[index].intValue();
   }
    
   /**
    * Gets the array of Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version values.
    */
   public final Integer[] getVersionArray()
   {
      return _Version;
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
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UserName or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UserName or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of UserName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UserName values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
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
    * Gets the ModUser field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ModUser or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the ModUser field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ModUser or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of ModUser fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ModUser values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the ComplyRule field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ComplyRule or null.
    */
   public final String getComplyRule( int index )
   {
      return _ComplyRule[index];
   }
    
   /**
    * Gets the ComplyRule field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ComplyRule or the specified default value.
    */
   public final String getComplyRule( int index, String defaultValue )
   {
      return _ComplyRule[index] == null ? defaultValue : _ComplyRule[index];
   }
    
   /**
    * Gets the array of ComplyRule fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ComplyRule values.
    */
   public final String[] getComplyRuleArray()
   {
      return _ComplyRule;
   }
    
   /**
    * Gets the AcctRegDetails Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctRegDetails Record Id or null.
    */
   public final Integer getAcctRegDetailsRId( int index )
   {
      return _AcctRegDetailsRId[index];
   }
    
   /**
    * Gets the AcctRegDetails Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctRegDetails Record Id or the specified default value.
    */
   public final int getAcctRegDetailsRId( int index, int defaultValue )
   {
      return _AcctRegDetailsRId[index] == null ? defaultValue : _AcctRegDetailsRId[index].intValue();
   }
    
   /**
    * Gets the array of AcctRegDetails Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctRegDetails Record Id values.
    */
   public final Integer[] getAcctRegDetailsRIdArray()
   {
      return _AcctRegDetailsRId;
   }
    
   /**
    * Gets the Country of Domicile field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country of Domicile or null.
    */
   public final String getCntryDomicile( int index )
   {
      return _CntryDomicile[index];
   }
    
   /**
    * Gets the Country of Domicile field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country of Domicile or the specified default value.
    */
   public final String getCntryDomicile( int index, String defaultValue )
   {
      return _CntryDomicile[index] == null ? defaultValue : _CntryDomicile[index];
   }
    
   /**
    * Gets the array of Country of Domicile fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country of Domicile values.
    */
   public final String[] getCntryDomicileArray()
   {
      return _CntryDomicile;
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
      _LastReview = responseBuffer.decodeDate(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _AcctRegDetailsUUID = resizeArray( _AcctRegDetailsUUID, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _FICategory = resizeArray( _FICategory, _RepeatCount );
      _FinInstRegDetlUUID = resizeArray( _FinInstRegDetlUUID, _RepeatCount );
      _ComplyAction = resizeArray( _ComplyAction, _RepeatCount );
      _Consented = resizeArray( _Consented, _RepeatCount );
      _Version = resizeArray( _Version, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ComplyRule = resizeArray( _ComplyRule, _RepeatCount );
      _AcctRegDetailsRId = resizeArray( _AcctRegDetailsRId, _RepeatCount );
      _CntryDomicile = resizeArray( _CntryDomicile, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AcctRegDetailsUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FICategory[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FinInstRegDetlUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ComplyAction[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Consented[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Version[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ComplyRule[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctRegDetailsRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CntryDomicile[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
