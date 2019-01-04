
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * DTA Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/DTAInquiry.doc">DTAInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class DTAInquiryView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * DTAType member array.
    */
   private String[] _DTAType = null;
   
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * StopDate member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * TransitNo member array.
    */
   private Integer[] _TransitNo = null;
   
   /**
    * ModDate member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * ModUser member array.
    */
   private String[] _ModUser = null;
   
   /**
    * UserName member array.
    */
   private String[] _UserName = null;
   
   /**
    * ProcessDate member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Version member array.
    */
   private Integer[] _Version = null;
   
   /**
    * DTARecid member array.
    */
   private Integer[] _DTARecid = null;
   

   /**
    * Constructs the DTAInquiryView object.
    * 
    */
   public DTAInquiryView()
   {
      super ( new DTAInquiryRequest() );
   }

   /**
    * Constructs the DTAInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DTAInquiryView( String hostEncoding )
   {
      super ( new DTAInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the DTAInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DTAInquiryRequest object.
    */
   public final DTAInquiryRequest getRequest()
   {
      return (DTAInquiryRequest)getIFastRequest();
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
    * Gets the DTAType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DTAType or null.
    */
   public final String getDTAType( int index )
   {
      return _DTAType[index];
   }
    
   /**
    * Gets the DTAType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DTAType or the specified default value.
    */
   public final String getDTAType( int index, String defaultValue )
   {
      return _DTAType[index] == null ? defaultValue : _DTAType[index];
   }
    
   /**
    * Gets the array of DTAType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DTAType values.
    */
   public final String[] getDTATypeArray()
   {
      return _DTAType;
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
    * Gets the TransitNo field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransitNo or null.
    */
   public final Integer getTransitNo( int index )
   {
      return _TransitNo[index];
   }
    
   /**
    * Gets the TransitNo field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransitNo or the specified default value.
    */
   public final int getTransitNo( int index, int defaultValue )
   {
      return _TransitNo[index] == null ? defaultValue : _TransitNo[index].intValue();
   }
    
   /**
    * Gets the array of TransitNo fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransitNo values.
    */
   public final Integer[] getTransitNoArray()
   {
      return _TransitNo;
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
    * Gets the DTARecid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DTARecid or null.
    */
   public final Integer getDTARecid( int index )
   {
      return _DTARecid[index];
   }
    
   /**
    * Gets the DTARecid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DTARecid or the specified default value.
    */
   public final int getDTARecid( int index, int defaultValue )
   {
      return _DTARecid[index] == null ? defaultValue : _DTARecid[index].intValue();
   }
    
   /**
    * Gets the array of DTARecid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DTARecid values.
    */
   public final Integer[] getDTARecidArray()
   {
      return _DTARecid;
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
      
      _DTAType = resizeArray( _DTAType, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _TransitNo = resizeArray( _TransitNo, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _Version = resizeArray( _Version, _RepeatCount );
      _DTARecid = resizeArray( _DTARecid, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _DTAType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Version[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DTARecid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
