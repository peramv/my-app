
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * System Activity Report Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/SysActInq.doc">SysActInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SysActInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Activity Date member array.
    */
   private Date[] _ActivityDate = null;
   
   /**
    * Activity Time member array.
    */
   private String[] _ActivityTime = null;
   
   /**
    * Activity Name member array.
    */
   private String[] _ActivityName = null;
   
   /**
    * For Company Code member array.
    */
   private String[] _rxForCompanyCode = null;
   
   /**
    * For User ID member array.
    */
   private String[] _rxForUserID = null;
   
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = null;
   
   /**
    * Entity ID member array.
    */
   private String[] _EntityID = null;
   
   /**
    * Shareholder Numnber member array.
    */
   private String[] _ShrNum = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   

   /**
    * Constructs the SysActInqView object.
    * 
    */
   public SysActInqView()
   {
      super ( new SysActInqRequest() );
   }

   /**
    * Constructs the SysActInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SysActInqView( String hostEncoding )
   {
      super ( new SysActInqRequest( hostEncoding ) );
   }

   /**
    * Gets the SysActInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SysActInqRequest object.
    */
   public final SysActInqRequest getRequest()
   {
      return (SysActInqRequest)getIFastRequest();
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
    * Gets the Activity Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Activity Date or null.
    */
   public final Date getActivityDate( int index )
   {
      return _ActivityDate[index];
   }
    
   /**
    * Gets the Activity Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Activity Date or the specified default value.
    */
   public final Date getActivityDate( int index, Date defaultValue )
   {
      return _ActivityDate[index] == null ? defaultValue : _ActivityDate[index];
   }
    
   /**
    * Gets the array of Activity Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Activity Date values.
    */
   public final Date[] getActivityDateArray()
   {
      return _ActivityDate;
   }
    
   /**
    * Gets the Activity Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Activity Time or null.
    */
   public final String getActivityTime( int index )
   {
      return _ActivityTime[index];
   }
    
   /**
    * Gets the Activity Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Activity Time or the specified default value.
    */
   public final String getActivityTime( int index, String defaultValue )
   {
      return _ActivityTime[index] == null ? defaultValue : _ActivityTime[index];
   }
    
   /**
    * Gets the array of Activity Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Activity Time values.
    */
   public final String[] getActivityTimeArray()
   {
      return _ActivityTime;
   }
    
   /**
    * Gets the Activity Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Activity Name or null.
    */
   public final String getActivityName( int index )
   {
      return _ActivityName[index];
   }
    
   /**
    * Gets the Activity Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Activity Name or the specified default value.
    */
   public final String getActivityName( int index, String defaultValue )
   {
      return _ActivityName[index] == null ? defaultValue : _ActivityName[index];
   }
    
   /**
    * Gets the array of Activity Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Activity Name values.
    */
   public final String[] getActivityNameArray()
   {
      return _ActivityName;
   }
    
   /**
    * Gets the For Company Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the For Company Code or null.
    */
   public final String getrxForCompanyCode( int index )
   {
      return _rxForCompanyCode[index];
   }
    
   /**
    * Gets the For Company Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the For Company Code or the specified default value.
    */
   public final String getrxForCompanyCode( int index, String defaultValue )
   {
      return _rxForCompanyCode[index] == null ? defaultValue : _rxForCompanyCode[index];
   }
    
   /**
    * Gets the array of For Company Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of For Company Code values.
    */
   public final String[] getrxForCompanyCodeArray()
   {
      return _rxForCompanyCode;
   }
    
   /**
    * Gets the For User ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the For User ID or null.
    */
   public final String getrxForUserID( int index )
   {
      return _rxForUserID[index];
   }
    
   /**
    * Gets the For User ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the For User ID or the specified default value.
    */
   public final String getrxForUserID( int index, String defaultValue )
   {
      return _rxForUserID[index] == null ? defaultValue : _rxForUserID[index];
   }
    
   /**
    * Gets the array of For User ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of For User ID values.
    */
   public final String[] getrxForUserIDArray()
   {
      return _rxForUserID;
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getAccountNum( int index )
   {
      return _AccountNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getAccountNum( int index, String defaultValue )
   {
      return _AccountNum[index] == null ? defaultValue : _AccountNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getAccountNumArray()
   {
      return _AccountNum;
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity ID or null.
    */
   public final String getEntityID( int index )
   {
      return _EntityID[index];
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity ID or the specified default value.
    */
   public final String getEntityID( int index, String defaultValue )
   {
      return _EntityID[index] == null ? defaultValue : _EntityID[index];
   }
    
   /**
    * Gets the array of Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity ID values.
    */
   public final String[] getEntityIDArray()
   {
      return _EntityID;
   }
    
   /**
    * Gets the Shareholder Numnber field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Numnber or null.
    */
   public final String getShrNum( int index )
   {
      return _ShrNum[index];
   }
    
   /**
    * Gets the Shareholder Numnber field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Numnber or the specified default value.
    */
   public final String getShrNum( int index, String defaultValue )
   {
      return _ShrNum[index] == null ? defaultValue : _ShrNum[index];
   }
    
   /**
    * Gets the array of Shareholder Numnber fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Numnber values.
    */
   public final String[] getShrNumArray()
   {
      return _ShrNum;
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
      
      _ActivityDate = resizeArray( _ActivityDate, _RepeatCount );
      _ActivityTime = resizeArray( _ActivityTime, _RepeatCount );
      _ActivityName = resizeArray( _ActivityName, _RepeatCount );
      _rxForCompanyCode = resizeArray( _rxForCompanyCode, _RepeatCount );
      _rxForUserID = resizeArray( _rxForUserID, _RepeatCount );
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
      _EntityID = resizeArray( _EntityID, _RepeatCount );
      _ShrNum = resizeArray( _ShrNum, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ActivityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ActivityTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ActivityName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxForCompanyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxForUserID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShrNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
