
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RRSP Receipt Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ReceiptInq.doc">ReceiptInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ReceiptInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Receipt Number member array.
    */
   private Integer[] _RcptNum = null;
   
   /**
    * Issued or Not Issued member array.
    */
   private Boolean[] _Issued = null;
   
   /**
    * Receipt Status member array.
    */
   private String[] _RcptStatus = null;
   
   /**
    * Date Receipt Issued member array.
    */
   private Date[] _IssueDate = null;
   
   /**
    * Receipt Amount member array.
    */
   private String[] _RcptAmount = null;
   
   /**
    * Number of Duplicates issued member array.
    */
   private Integer[] _Duplicates = null;
   
   /**
    * Type of Receipt member array.
    */
   private String[] _ReceiptType = null;
   
   /**
    * Previous Receipt Number member array.
    */
   private Integer[] _PrevRcptNo = null;
   
   /**
    * Owner's Name member array.
    */
   private String[] _Name1 = null;
   
   /**
    * Owner's SIN member array.
    */
   private String[] _SIN = null;
   
   /**
    * Address line 1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * Address line 2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * Address line 3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * Address line 4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * Address line 5 member array.
    */
   private String[] _AddrLine5 = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Contributor's Name member array.
    */
   private String[] _CName1 = null;
   
   /**
    * Contributor's Sin member array.
    */
   private String[] _CSin = null;
   
   /**
    * Caution member array.
    */
   private String[] _Caution = null;
   
   /**
    * Modifcation Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Modifcation User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Username member array.
    */
   private String[] _Username = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   

   /**
    * Constructs the ReceiptInqView object.
    * 
    */
   public ReceiptInqView()
   {
      super ( new ReceiptInqRequest() );
   }

   /**
    * Constructs the ReceiptInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ReceiptInqView( String hostEncoding )
   {
      super ( new ReceiptInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ReceiptInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ReceiptInqRequest object.
    */
   public final ReceiptInqRequest getRequest()
   {
      return (ReceiptInqRequest)getIFastRequest();
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
    * Gets the Receipt Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Receipt Number or null.
    */
   public final Integer getRcptNum( int index )
   {
      return _RcptNum[index];
   }
    
   /**
    * Gets the Receipt Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Receipt Number or the specified default value.
    */
   public final int getRcptNum( int index, int defaultValue )
   {
      return _RcptNum[index] == null ? defaultValue : _RcptNum[index].intValue();
   }
    
   /**
    * Gets the array of Receipt Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Receipt Number values.
    */
   public final Integer[] getRcptNumArray()
   {
      return _RcptNum;
   }
    
   /**
    * Gets the Issued or Not Issued field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Issued or Not Issued or null.
    */
   public final Boolean getIssued( int index )
   {
      return _Issued[index];
   }
    
   /**
    * Gets the Issued or Not Issued field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Issued or Not Issued or the specified default value.
    */
   public final boolean getIssued( int index, boolean defaultValue )
   {
      return _Issued[index] == null ? defaultValue : _Issued[index].booleanValue();
   }
    
   /**
    * Gets the array of Issued or Not Issued fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Issued or Not Issued values.
    */
   public final Boolean[] getIssuedArray()
   {
      return _Issued;
   }
    
   /**
    * Gets the Receipt Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Receipt Status or null.
    */
   public final String getRcptStatus( int index )
   {
      return _RcptStatus[index];
   }
    
   /**
    * Gets the Receipt Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Receipt Status or the specified default value.
    */
   public final String getRcptStatus( int index, String defaultValue )
   {
      return _RcptStatus[index] == null ? defaultValue : _RcptStatus[index];
   }
    
   /**
    * Gets the array of Receipt Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Receipt Status values.
    */
   public final String[] getRcptStatusArray()
   {
      return _RcptStatus;
   }
    
   /**
    * Gets the Date Receipt Issued field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date Receipt Issued or null.
    */
   public final Date getIssueDate( int index )
   {
      return _IssueDate[index];
   }
    
   /**
    * Gets the Date Receipt Issued field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date Receipt Issued or the specified default value.
    */
   public final Date getIssueDate( int index, Date defaultValue )
   {
      return _IssueDate[index] == null ? defaultValue : _IssueDate[index];
   }
    
   /**
    * Gets the array of Date Receipt Issued fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date Receipt Issued values.
    */
   public final Date[] getIssueDateArray()
   {
      return _IssueDate;
   }
    
   /**
    * Gets the Receipt Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Receipt Amount or null.
    */
   public final String getRcptAmount( int index )
   {
      return _RcptAmount[index];
   }
    
   /**
    * Gets the Receipt Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Receipt Amount or the specified default value.
    */
   public final String getRcptAmount( int index, String defaultValue )
   {
      return _RcptAmount[index] == null ? defaultValue : _RcptAmount[index];
   }
    
   /**
    * Gets the array of Receipt Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Receipt Amount values.
    */
   public final String[] getRcptAmountArray()
   {
      return _RcptAmount;
   }
    
   /**
    * Gets the Number of Duplicates issued field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Number of Duplicates issued or null.
    */
   public final Integer getDuplicates( int index )
   {
      return _Duplicates[index];
   }
    
   /**
    * Gets the Number of Duplicates issued field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Number of Duplicates issued or the specified default value.
    */
   public final int getDuplicates( int index, int defaultValue )
   {
      return _Duplicates[index] == null ? defaultValue : _Duplicates[index].intValue();
   }
    
   /**
    * Gets the array of Number of Duplicates issued fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Number of Duplicates issued values.
    */
   public final Integer[] getDuplicatesArray()
   {
      return _Duplicates;
   }
    
   /**
    * Gets the Type of Receipt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Type of Receipt or null.
    */
   public final String getReceiptType( int index )
   {
      return _ReceiptType[index];
   }
    
   /**
    * Gets the Type of Receipt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Type of Receipt or the specified default value.
    */
   public final String getReceiptType( int index, String defaultValue )
   {
      return _ReceiptType[index] == null ? defaultValue : _ReceiptType[index];
   }
    
   /**
    * Gets the array of Type of Receipt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Type of Receipt values.
    */
   public final String[] getReceiptTypeArray()
   {
      return _ReceiptType;
   }
    
   /**
    * Gets the Previous Receipt Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Previous Receipt Number or null.
    */
   public final Integer getPrevRcptNo( int index )
   {
      return _PrevRcptNo[index];
   }
    
   /**
    * Gets the Previous Receipt Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Previous Receipt Number or the specified default value.
    */
   public final int getPrevRcptNo( int index, int defaultValue )
   {
      return _PrevRcptNo[index] == null ? defaultValue : _PrevRcptNo[index].intValue();
   }
    
   /**
    * Gets the array of Previous Receipt Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Previous Receipt Number values.
    */
   public final Integer[] getPrevRcptNoArray()
   {
      return _PrevRcptNo;
   }
    
   /**
    * Gets the Owner's Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Owner's Name or null.
    */
   public final String getName1( int index )
   {
      return _Name1[index];
   }
    
   /**
    * Gets the Owner's Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Owner's Name or the specified default value.
    */
   public final String getName1( int index, String defaultValue )
   {
      return _Name1[index] == null ? defaultValue : _Name1[index];
   }
    
   /**
    * Gets the array of Owner's Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Owner's Name values.
    */
   public final String[] getName1Array()
   {
      return _Name1;
   }
    
   /**
    * Gets the Owner's SIN field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Owner's SIN or null.
    */
   public final String getSIN( int index )
   {
      return _SIN[index];
   }
    
   /**
    * Gets the Owner's SIN field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Owner's SIN or the specified default value.
    */
   public final String getSIN( int index, String defaultValue )
   {
      return _SIN[index] == null ? defaultValue : _SIN[index];
   }
    
   /**
    * Gets the array of Owner's SIN fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Owner's SIN values.
    */
   public final String[] getSINArray()
   {
      return _SIN;
   }
    
   /**
    * Gets the Address line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address line 1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the Address line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address line 1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of Address line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address line 1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the Address line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address line 2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the Address line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address line 2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of Address line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address line 2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the Address line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address line 3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the Address line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address line 3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of Address line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address line 3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the Address line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address line 4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the Address line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address line 4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of Address line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address line 4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the Address line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address line 5 or null.
    */
   public final String getAddrLine5( int index )
   {
      return _AddrLine5[index];
   }
    
   /**
    * Gets the Address line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address line 5 or the specified default value.
    */
   public final String getAddrLine5( int index, String defaultValue )
   {
      return _AddrLine5[index] == null ? defaultValue : _AddrLine5[index];
   }
    
   /**
    * Gets the array of Address line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address line 5 values.
    */
   public final String[] getAddrLine5Array()
   {
      return _AddrLine5;
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Postal Code or null.
    */
   public final String getPostalCode( int index )
   {
      return _PostalCode[index];
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Postal Code or the specified default value.
    */
   public final String getPostalCode( int index, String defaultValue )
   {
      return _PostalCode[index] == null ? defaultValue : _PostalCode[index];
   }
    
   /**
    * Gets the array of Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Postal Code values.
    */
   public final String[] getPostalCodeArray()
   {
      return _PostalCode;
   }
    
   /**
    * Gets the Contributor's Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contributor's Name or null.
    */
   public final String getCName1( int index )
   {
      return _CName1[index];
   }
    
   /**
    * Gets the Contributor's Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contributor's Name or the specified default value.
    */
   public final String getCName1( int index, String defaultValue )
   {
      return _CName1[index] == null ? defaultValue : _CName1[index];
   }
    
   /**
    * Gets the array of Contributor's Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contributor's Name values.
    */
   public final String[] getCName1Array()
   {
      return _CName1;
   }
    
   /**
    * Gets the Contributor's Sin field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contributor's Sin or null.
    */
   public final String getCSin( int index )
   {
      return _CSin[index];
   }
    
   /**
    * Gets the Contributor's Sin field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contributor's Sin or the specified default value.
    */
   public final String getCSin( int index, String defaultValue )
   {
      return _CSin[index] == null ? defaultValue : _CSin[index];
   }
    
   /**
    * Gets the array of Contributor's Sin fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contributor's Sin values.
    */
   public final String[] getCSinArray()
   {
      return _CSin;
   }
    
   /**
    * Gets the Caution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Caution or null.
    */
   public final String getCaution( int index )
   {
      return _Caution[index];
   }
    
   /**
    * Gets the Caution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Caution or the specified default value.
    */
   public final String getCaution( int index, String defaultValue )
   {
      return _Caution[index] == null ? defaultValue : _Caution[index];
   }
    
   /**
    * Gets the array of Caution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Caution values.
    */
   public final String[] getCautionArray()
   {
      return _Caution;
   }
    
   /**
    * Gets the Modifcation Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modifcation Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modifcation Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modifcation Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modifcation Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modifcation Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Modifcation User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modifcation User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modifcation User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modifcation User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modifcation User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modifcation User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Username field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Username or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Username field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Username or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Username fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Username values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
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
      
      _RcptNum = resizeArray( _RcptNum, _RepeatCount );
      _Issued = resizeArray( _Issued, _RepeatCount );
      _RcptStatus = resizeArray( _RcptStatus, _RepeatCount );
      _IssueDate = resizeArray( _IssueDate, _RepeatCount );
      _RcptAmount = resizeArray( _RcptAmount, _RepeatCount );
      _Duplicates = resizeArray( _Duplicates, _RepeatCount );
      _ReceiptType = resizeArray( _ReceiptType, _RepeatCount );
      _PrevRcptNo = resizeArray( _PrevRcptNo, _RepeatCount );
      _Name1 = resizeArray( _Name1, _RepeatCount );
      _SIN = resizeArray( _SIN, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _CName1 = resizeArray( _CName1, _RepeatCount );
      _CSin = resizeArray( _CSin, _RepeatCount );
      _Caution = resizeArray( _Caution, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RcptNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Issued[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RcptStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IssueDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RcptAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Duplicates[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ReceiptType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PrevRcptNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Name1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SIN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CName1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CSin[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Caution[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
