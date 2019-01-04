
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * KYC  Document List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/KCYDocListInq.doc">KCYDocListInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class KCYDocListInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Document  Code of the Doc Master member array.
    */
   private String[] _DocCode = null;
   
   /**
    * Comply Document  Description member array.
    */
   private String[] _Description = null;
   
   /**
    * Document Status member array.
    */
   private String[] _StatusCode = null;
   
   /**
    * Date the document was received member array.
    */
   private Date[] _ReceivedDate = null;
   
   /**
    * Remarks member array.
    */
   private String[] _Remarks = null;
   
   /**
    * AcctDocList RECID member array.
    */
   private Integer[] _AcctDocListRecID = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _Deff = null;
   
   /**
    * Expiration Date member array.
    */
   private Date[] _ExpiryDate = null;
   
   /**
    * Requested Date member array.
    */
   private Date[] _RequestDate = null;
   
   /**
    * Reference Number member array.
    */
   private String[] _RefNumber = null;
   
   /**
    * AcctDocListUUID member array.
    */
   private String[] _AcctDocListUUID = null;
   

   /**
    * Constructs the KCYDocListInqView object.
    * 
    */
   public KCYDocListInqView()
   {
      super ( new KCYDocListInqRequest() );
   }

   /**
    * Constructs the KCYDocListInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public KCYDocListInqView( String hostEncoding )
   {
      super ( new KCYDocListInqRequest( hostEncoding ) );
   }

   /**
    * Gets the KCYDocListInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The KCYDocListInqRequest object.
    */
   public final KCYDocListInqRequest getRequest()
   {
      return (KCYDocListInqRequest)getIFastRequest();
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
    * Gets the Document  Code of the Doc Master field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Document  Code of the Doc Master or null.
    */
   public final String getDocCode( int index )
   {
      return _DocCode[index];
   }
    
   /**
    * Gets the Document  Code of the Doc Master field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Document  Code of the Doc Master or the specified default value.
    */
   public final String getDocCode( int index, String defaultValue )
   {
      return _DocCode[index] == null ? defaultValue : _DocCode[index];
   }
    
   /**
    * Gets the array of Document  Code of the Doc Master fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Document  Code of the Doc Master values.
    */
   public final String[] getDocCodeArray()
   {
      return _DocCode;
   }
    
   /**
    * Gets the Comply Document  Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Comply Document  Description or null.
    */
   public final String getDescription( int index )
   {
      return _Description[index];
   }
    
   /**
    * Gets the Comply Document  Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comply Document  Description or the specified default value.
    */
   public final String getDescription( int index, String defaultValue )
   {
      return _Description[index] == null ? defaultValue : _Description[index];
   }
    
   /**
    * Gets the array of Comply Document  Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Comply Document  Description values.
    */
   public final String[] getDescriptionArray()
   {
      return _Description;
   }
    
   /**
    * Gets the Document Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Document Status or null.
    */
   public final String getStatusCode( int index )
   {
      return _StatusCode[index];
   }
    
   /**
    * Gets the Document Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Document Status or the specified default value.
    */
   public final String getStatusCode( int index, String defaultValue )
   {
      return _StatusCode[index] == null ? defaultValue : _StatusCode[index];
   }
    
   /**
    * Gets the array of Document Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Document Status values.
    */
   public final String[] getStatusCodeArray()
   {
      return _StatusCode;
   }
    
   /**
    * Gets the Date the document was received field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date the document was received or null.
    */
   public final Date getReceivedDate( int index )
   {
      return _ReceivedDate[index];
   }
    
   /**
    * Gets the Date the document was received field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date the document was received or the specified default value.
    */
   public final Date getReceivedDate( int index, Date defaultValue )
   {
      return _ReceivedDate[index] == null ? defaultValue : _ReceivedDate[index];
   }
    
   /**
    * Gets the array of Date the document was received fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date the document was received values.
    */
   public final Date[] getReceivedDateArray()
   {
      return _ReceivedDate;
   }
    
   /**
    * Gets the Remarks field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks or null.
    */
   public final String getRemarks( int index )
   {
      return _Remarks[index];
   }
    
   /**
    * Gets the Remarks field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks or the specified default value.
    */
   public final String getRemarks( int index, String defaultValue )
   {
      return _Remarks[index] == null ? defaultValue : _Remarks[index];
   }
    
   /**
    * Gets the array of Remarks fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks values.
    */
   public final String[] getRemarksArray()
   {
      return _Remarks;
   }
    
   /**
    * Gets the AcctDocList RECID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctDocList RECID or null.
    */
   public final Integer getAcctDocListRecID( int index )
   {
      return _AcctDocListRecID[index];
   }
    
   /**
    * Gets the AcctDocList RECID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctDocList RECID or the specified default value.
    */
   public final int getAcctDocListRecID( int index, int defaultValue )
   {
      return _AcctDocListRecID[index] == null ? defaultValue : _AcctDocListRecID[index].intValue();
   }
    
   /**
    * Gets the array of AcctDocList RECID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctDocList RECID values.
    */
   public final Integer[] getAcctDocListRecIDArray()
   {
      return _AcctDocListRecID;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getDeff( int index )
   {
      return _Deff[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getDeff( int index, Date defaultValue )
   {
      return _Deff[index] == null ? defaultValue : _Deff[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getDeffArray()
   {
      return _Deff;
   }
    
   /**
    * Gets the Expiration Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Expiration Date or null.
    */
   public final Date getExpiryDate( int index )
   {
      return _ExpiryDate[index];
   }
    
   /**
    * Gets the Expiration Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Expiration Date or the specified default value.
    */
   public final Date getExpiryDate( int index, Date defaultValue )
   {
      return _ExpiryDate[index] == null ? defaultValue : _ExpiryDate[index];
   }
    
   /**
    * Gets the array of Expiration Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Expiration Date values.
    */
   public final Date[] getExpiryDateArray()
   {
      return _ExpiryDate;
   }
    
   /**
    * Gets the Requested Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Requested Date or null.
    */
   public final Date getRequestDate( int index )
   {
      return _RequestDate[index];
   }
    
   /**
    * Gets the Requested Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Requested Date or the specified default value.
    */
   public final Date getRequestDate( int index, Date defaultValue )
   {
      return _RequestDate[index] == null ? defaultValue : _RequestDate[index];
   }
    
   /**
    * Gets the array of Requested Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Requested Date values.
    */
   public final Date[] getRequestDateArray()
   {
      return _RequestDate;
   }
    
   /**
    * Gets the Reference Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reference Number or null.
    */
   public final String getRefNumber( int index )
   {
      return _RefNumber[index];
   }
    
   /**
    * Gets the Reference Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reference Number or the specified default value.
    */
   public final String getRefNumber( int index, String defaultValue )
   {
      return _RefNumber[index] == null ? defaultValue : _RefNumber[index];
   }
    
   /**
    * Gets the array of Reference Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reference Number values.
    */
   public final String[] getRefNumberArray()
   {
      return _RefNumber;
   }
    
   /**
    * Gets the AcctDocListUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctDocListUUID or null.
    */
   public final String getAcctDocListUUID( int index )
   {
      return _AcctDocListUUID[index];
   }
    
   /**
    * Gets the AcctDocListUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctDocListUUID or the specified default value.
    */
   public final String getAcctDocListUUID( int index, String defaultValue )
   {
      return _AcctDocListUUID[index] == null ? defaultValue : _AcctDocListUUID[index];
   }
    
   /**
    * Gets the array of AcctDocListUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctDocListUUID values.
    */
   public final String[] getAcctDocListUUIDArray()
   {
      return _AcctDocListUUID;
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
      
      _DocCode = resizeArray( _DocCode, _RepeatCount );
      _Description = resizeArray( _Description, _RepeatCount );
      _StatusCode = resizeArray( _StatusCode, _RepeatCount );
      _ReceivedDate = resizeArray( _ReceivedDate, _RepeatCount );
      _Remarks = resizeArray( _Remarks, _RepeatCount );
      _AcctDocListRecID = resizeArray( _AcctDocListRecID, _RepeatCount );
      _Deff = resizeArray( _Deff, _RepeatCount );
      _ExpiryDate = resizeArray( _ExpiryDate, _RepeatCount );
      _RequestDate = resizeArray( _RequestDate, _RepeatCount );
      _RefNumber = resizeArray( _RefNumber, _RepeatCount );
      _AcctDocListUUID = resizeArray( _AcctDocListUUID, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _DocCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Description[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StatusCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReceivedDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Remarks[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDocListRecID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Deff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ExpiryDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RequestDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RefNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDocListUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
