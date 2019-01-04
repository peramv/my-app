
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Breakdown Per Fund view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctBrkdwnInq.doc">AcctBrkdwnInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctBrkdwnInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * ClassCode member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * AccountNum member array.
    */
   private String[] _AccountNum = null;
   
   /**
    * FirstName member array.
    */
   private String[] _FirstName = null;
   
   /**
    * LastName member array.
    */
   private String[] _LastName = null;
   
   /**
    * TotalAcctUnits member array.
    */
   private String[] _TotalAcctUnits = null;
   
   /**
    * TotalValPerAcct member array.
    */
   private String[] _TotalValPerAcct = null;
   
   /**
    * TotalAccrIntPerAcct member array.
    */
   private String[] _TotalAccrIntPerAcct = null;
   
   /**
    * AcctSettUnits member array.
    */
   private String[] _AcctSettUnits = null;
   
   /**
    * AcctSettAmt member array.
    */
   private String[] _AcctSettAmt = null;
   
   /**
    * AcctUnsettUnits member array.
    */
   private String[] _AcctUnsettUnits = null;
   
   /**
    * AcctUnsettAmt member array.
    */
   private String[] _AcctUnsettAmt = null;
   

   /**
    * Constructs the AcctBrkdwnInqView object.
    * 
    */
   public AcctBrkdwnInqView()
   {
      super ( new AcctBrkdwnInqRequest() );
   }

   /**
    * Constructs the AcctBrkdwnInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctBrkdwnInqView( String hostEncoding )
   {
      super ( new AcctBrkdwnInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctBrkdwnInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctBrkdwnInqRequest object.
    */
   public final AcctBrkdwnInqRequest getRequest()
   {
      return (AcctBrkdwnInqRequest)getIFastRequest();
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
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ClassCode or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the ClassCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ClassCode or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of ClassCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ClassCode values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the AccountNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AccountNum or null.
    */
   public final String getAccountNum( int index )
   {
      return _AccountNum[index];
   }
    
   /**
    * Gets the AccountNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AccountNum or the specified default value.
    */
   public final String getAccountNum( int index, String defaultValue )
   {
      return _AccountNum[index] == null ? defaultValue : _AccountNum[index];
   }
    
   /**
    * Gets the array of AccountNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AccountNum values.
    */
   public final String[] getAccountNumArray()
   {
      return _AccountNum;
   }
    
   /**
    * Gets the FirstName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FirstName or null.
    */
   public final String getFirstName( int index )
   {
      return _FirstName[index];
   }
    
   /**
    * Gets the FirstName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FirstName or the specified default value.
    */
   public final String getFirstName( int index, String defaultValue )
   {
      return _FirstName[index] == null ? defaultValue : _FirstName[index];
   }
    
   /**
    * Gets the array of FirstName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FirstName values.
    */
   public final String[] getFirstNameArray()
   {
      return _FirstName;
   }
    
   /**
    * Gets the LastName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LastName or null.
    */
   public final String getLastName( int index )
   {
      return _LastName[index];
   }
    
   /**
    * Gets the LastName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LastName or the specified default value.
    */
   public final String getLastName( int index, String defaultValue )
   {
      return _LastName[index] == null ? defaultValue : _LastName[index];
   }
    
   /**
    * Gets the array of LastName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LastName values.
    */
   public final String[] getLastNameArray()
   {
      return _LastName;
   }
    
   /**
    * Gets the TotalAcctUnits field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TotalAcctUnits or null.
    */
   public final String getTotalAcctUnits( int index )
   {
      return _TotalAcctUnits[index];
   }
    
   /**
    * Gets the TotalAcctUnits field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TotalAcctUnits or the specified default value.
    */
   public final String getTotalAcctUnits( int index, String defaultValue )
   {
      return _TotalAcctUnits[index] == null ? defaultValue : _TotalAcctUnits[index];
   }
    
   /**
    * Gets the array of TotalAcctUnits fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TotalAcctUnits values.
    */
   public final String[] getTotalAcctUnitsArray()
   {
      return _TotalAcctUnits;
   }
    
   /**
    * Gets the TotalValPerAcct field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TotalValPerAcct or null.
    */
   public final String getTotalValPerAcct( int index )
   {
      return _TotalValPerAcct[index];
   }
    
   /**
    * Gets the TotalValPerAcct field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TotalValPerAcct or the specified default value.
    */
   public final String getTotalValPerAcct( int index, String defaultValue )
   {
      return _TotalValPerAcct[index] == null ? defaultValue : _TotalValPerAcct[index];
   }
    
   /**
    * Gets the array of TotalValPerAcct fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TotalValPerAcct values.
    */
   public final String[] getTotalValPerAcctArray()
   {
      return _TotalValPerAcct;
   }
    
   /**
    * Gets the TotalAccrIntPerAcct field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TotalAccrIntPerAcct or null.
    */
   public final String getTotalAccrIntPerAcct( int index )
   {
      return _TotalAccrIntPerAcct[index];
   }
    
   /**
    * Gets the TotalAccrIntPerAcct field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TotalAccrIntPerAcct or the specified default value.
    */
   public final String getTotalAccrIntPerAcct( int index, String defaultValue )
   {
      return _TotalAccrIntPerAcct[index] == null ? defaultValue : _TotalAccrIntPerAcct[index];
   }
    
   /**
    * Gets the array of TotalAccrIntPerAcct fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TotalAccrIntPerAcct values.
    */
   public final String[] getTotalAccrIntPerAcctArray()
   {
      return _TotalAccrIntPerAcct;
   }
    
   /**
    * Gets the AcctSettUnits field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctSettUnits or null.
    */
   public final String getAcctSettUnits( int index )
   {
      return _AcctSettUnits[index];
   }
    
   /**
    * Gets the AcctSettUnits field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctSettUnits or the specified default value.
    */
   public final String getAcctSettUnits( int index, String defaultValue )
   {
      return _AcctSettUnits[index] == null ? defaultValue : _AcctSettUnits[index];
   }
    
   /**
    * Gets the array of AcctSettUnits fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctSettUnits values.
    */
   public final String[] getAcctSettUnitsArray()
   {
      return _AcctSettUnits;
   }
    
   /**
    * Gets the AcctSettAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctSettAmt or null.
    */
   public final String getAcctSettAmt( int index )
   {
      return _AcctSettAmt[index];
   }
    
   /**
    * Gets the AcctSettAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctSettAmt or the specified default value.
    */
   public final String getAcctSettAmt( int index, String defaultValue )
   {
      return _AcctSettAmt[index] == null ? defaultValue : _AcctSettAmt[index];
   }
    
   /**
    * Gets the array of AcctSettAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctSettAmt values.
    */
   public final String[] getAcctSettAmtArray()
   {
      return _AcctSettAmt;
   }
    
   /**
    * Gets the AcctUnsettUnits field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctUnsettUnits or null.
    */
   public final String getAcctUnsettUnits( int index )
   {
      return _AcctUnsettUnits[index];
   }
    
   /**
    * Gets the AcctUnsettUnits field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctUnsettUnits or the specified default value.
    */
   public final String getAcctUnsettUnits( int index, String defaultValue )
   {
      return _AcctUnsettUnits[index] == null ? defaultValue : _AcctUnsettUnits[index];
   }
    
   /**
    * Gets the array of AcctUnsettUnits fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctUnsettUnits values.
    */
   public final String[] getAcctUnsettUnitsArray()
   {
      return _AcctUnsettUnits;
   }
    
   /**
    * Gets the AcctUnsettAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctUnsettAmt or null.
    */
   public final String getAcctUnsettAmt( int index )
   {
      return _AcctUnsettAmt[index];
   }
    
   /**
    * Gets the AcctUnsettAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctUnsettAmt or the specified default value.
    */
   public final String getAcctUnsettAmt( int index, String defaultValue )
   {
      return _AcctUnsettAmt[index] == null ? defaultValue : _AcctUnsettAmt[index];
   }
    
   /**
    * Gets the array of AcctUnsettAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctUnsettAmt values.
    */
   public final String[] getAcctUnsettAmtArray()
   {
      return _AcctUnsettAmt;
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
      
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
      _FirstName = resizeArray( _FirstName, _RepeatCount );
      _LastName = resizeArray( _LastName, _RepeatCount );
      _TotalAcctUnits = resizeArray( _TotalAcctUnits, _RepeatCount );
      _TotalValPerAcct = resizeArray( _TotalValPerAcct, _RepeatCount );
      _TotalAccrIntPerAcct = resizeArray( _TotalAccrIntPerAcct, _RepeatCount );
      _AcctSettUnits = resizeArray( _AcctSettUnits, _RepeatCount );
      _AcctSettAmt = resizeArray( _AcctSettAmt, _RepeatCount );
      _AcctUnsettUnits = resizeArray( _AcctUnsettUnits, _RepeatCount );
      _AcctUnsettAmt = resizeArray( _AcctUnsettAmt, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TotalAcctUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TotalValPerAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TotalAccrIntPerAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctSettUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctSettAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctUnsettUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctUnsettAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
