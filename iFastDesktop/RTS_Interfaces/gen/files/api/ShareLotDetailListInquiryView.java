
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Share Lot Detail List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ShareLotDetailListInquiry.doc">ShareLotDetailListInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShareLotDetailListInquiryView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * SharelotDetlUUID member array.
    */
   private String[] _SharelotDetlUUID = null;
   
   /**
    * TransType member array.
    */
   private String[] _TransType = null;
   
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * PrincipalGrossMoneyOut member array.
    */
   private String[] _PrincipalGrossMoneyOut = null;
   
   /**
    * MVA member array.
    */
   private String[] _MVA = null;
   
   /**
    * AdminFee member array.
    */
   private String[] _AdminFee = null;
   
   /**
    * NetOfFees member array.
    */
   private String[] _NetOfFees = null;
   
   /**
    * Calculated MVA member array.
    */
   private String[] _CalculatedMVA = null;
   
   /**
    * Reason Code member array.
    */
   private String[] _ReasonCode = null;
   

   /**
    * Constructs the ShareLotDetailListInquiryView object.
    * 
    */
   public ShareLotDetailListInquiryView()
   {
      super ( new ShareLotDetailListInquiryRequest() );
   }

   /**
    * Constructs the ShareLotDetailListInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShareLotDetailListInquiryView( String hostEncoding )
   {
      super ( new ShareLotDetailListInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the ShareLotDetailListInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShareLotDetailListInquiryRequest object.
    */
   public final ShareLotDetailListInquiryRequest getRequest()
   {
      return (ShareLotDetailListInquiryRequest)getIFastRequest();
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
    * Gets the SharelotDetlUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SharelotDetlUUID or null.
    */
   public final String getSharelotDetlUUID( int index )
   {
      return _SharelotDetlUUID[index];
   }
    
   /**
    * Gets the SharelotDetlUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SharelotDetlUUID or the specified default value.
    */
   public final String getSharelotDetlUUID( int index, String defaultValue )
   {
      return _SharelotDetlUUID[index] == null ? defaultValue : _SharelotDetlUUID[index];
   }
    
   /**
    * Gets the array of SharelotDetlUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SharelotDetlUUID values.
    */
   public final String[] getSharelotDetlUUIDArray()
   {
      return _SharelotDetlUUID;
   }
    
   /**
    * Gets the TransType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransType or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the TransType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransType or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of TransType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransType values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
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
    * Gets the PrincipalGrossMoneyOut field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PrincipalGrossMoneyOut or null.
    */
   public final String getPrincipalGrossMoneyOut( int index )
   {
      return _PrincipalGrossMoneyOut[index];
   }
    
   /**
    * Gets the PrincipalGrossMoneyOut field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PrincipalGrossMoneyOut or the specified default value.
    */
   public final String getPrincipalGrossMoneyOut( int index, String defaultValue )
   {
      return _PrincipalGrossMoneyOut[index] == null ? defaultValue : _PrincipalGrossMoneyOut[index];
   }
    
   /**
    * Gets the array of PrincipalGrossMoneyOut fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PrincipalGrossMoneyOut values.
    */
   public final String[] getPrincipalGrossMoneyOutArray()
   {
      return _PrincipalGrossMoneyOut;
   }
    
   /**
    * Gets the MVA field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MVA or null.
    */
   public final String getMVA( int index )
   {
      return _MVA[index];
   }
    
   /**
    * Gets the MVA field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MVA or the specified default value.
    */
   public final String getMVA( int index, String defaultValue )
   {
      return _MVA[index] == null ? defaultValue : _MVA[index];
   }
    
   /**
    * Gets the array of MVA fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MVA values.
    */
   public final String[] getMVAArray()
   {
      return _MVA;
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
    * Gets the NetOfFees field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NetOfFees or null.
    */
   public final String getNetOfFees( int index )
   {
      return _NetOfFees[index];
   }
    
   /**
    * Gets the NetOfFees field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NetOfFees or the specified default value.
    */
   public final String getNetOfFees( int index, String defaultValue )
   {
      return _NetOfFees[index] == null ? defaultValue : _NetOfFees[index];
   }
    
   /**
    * Gets the array of NetOfFees fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NetOfFees values.
    */
   public final String[] getNetOfFeesArray()
   {
      return _NetOfFees;
   }
    
   /**
    * Gets the Calculated MVA field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Calculated MVA or null.
    */
   public final String getCalculatedMVA( int index )
   {
      return _CalculatedMVA[index];
   }
    
   /**
    * Gets the Calculated MVA field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calculated MVA or the specified default value.
    */
   public final String getCalculatedMVA( int index, String defaultValue )
   {
      return _CalculatedMVA[index] == null ? defaultValue : _CalculatedMVA[index];
   }
    
   /**
    * Gets the array of Calculated MVA fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Calculated MVA values.
    */
   public final String[] getCalculatedMVAArray()
   {
      return _CalculatedMVA;
   }
    
   /**
    * Gets the Reason Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason Code or null.
    */
   public final String getReasonCode( int index )
   {
      return _ReasonCode[index];
   }
    
   /**
    * Gets the Reason Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason Code or the specified default value.
    */
   public final String getReasonCode( int index, String defaultValue )
   {
      return _ReasonCode[index] == null ? defaultValue : _ReasonCode[index];
   }
    
   /**
    * Gets the array of Reason Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason Code values.
    */
   public final String[] getReasonCodeArray()
   {
      return _ReasonCode;
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
      
      _SharelotDetlUUID = resizeArray( _SharelotDetlUUID, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _PrincipalGrossMoneyOut = resizeArray( _PrincipalGrossMoneyOut, _RepeatCount );
      _MVA = resizeArray( _MVA, _RepeatCount );
      _AdminFee = resizeArray( _AdminFee, _RepeatCount );
      _NetOfFees = resizeArray( _NetOfFees, _RepeatCount );
      _CalculatedMVA = resizeArray( _CalculatedMVA, _RepeatCount );
      _ReasonCode = resizeArray( _ReasonCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _SharelotDetlUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _PrincipalGrossMoneyOut[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MVA[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdminFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetOfFees[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CalculatedMVA[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReasonCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
