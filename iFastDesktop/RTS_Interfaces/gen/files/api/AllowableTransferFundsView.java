
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Allowable Transfer(TO) Funds view.
 * For additional view information see <A HREF="../../../../viewspecs/AllowableTransferFunds.doc">AllowableTransferFunds.doc</A>.
 * 
 * @author RTS Generated
 */
public class AllowableTransferFundsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund To member array.
    */
   private String[] _FundToCode = null;
   
   /**
    * Class To member array.
    */
   private String[] _ClassToCode = null;
   
   /**
    * New Money?  Y/N member array.
    */
   private Boolean[] _NewMoney = null;
   
   /**
    * Sponsor member array.
    */
   private String[] _Sponsor = null;
   

   /**
    * Constructs the AllowableTransferFundsView object.
    * 
    */
   public AllowableTransferFundsView()
   {
      super ( new AllowableTransferFundsRequest() );
   }

   /**
    * Constructs the AllowableTransferFundsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AllowableTransferFundsView( String hostEncoding )
   {
      super ( new AllowableTransferFundsRequest( hostEncoding ) );
   }

   /**
    * Gets the AllowableTransferFundsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AllowableTransferFundsRequest object.
    */
   public final AllowableTransferFundsRequest getRequest()
   {
      return (AllowableTransferFundsRequest)getIFastRequest();
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
    * Gets the Fund To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund To or null.
    */
   public final String getFundToCode( int index )
   {
      return _FundToCode[index];
   }
    
   /**
    * Gets the Fund To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund To or the specified default value.
    */
   public final String getFundToCode( int index, String defaultValue )
   {
      return _FundToCode[index] == null ? defaultValue : _FundToCode[index];
   }
    
   /**
    * Gets the array of Fund To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund To values.
    */
   public final String[] getFundToCodeArray()
   {
      return _FundToCode;
   }
    
   /**
    * Gets the Class To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class To or null.
    */
   public final String getClassToCode( int index )
   {
      return _ClassToCode[index];
   }
    
   /**
    * Gets the Class To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class To or the specified default value.
    */
   public final String getClassToCode( int index, String defaultValue )
   {
      return _ClassToCode[index] == null ? defaultValue : _ClassToCode[index];
   }
    
   /**
    * Gets the array of Class To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class To values.
    */
   public final String[] getClassToCodeArray()
   {
      return _ClassToCode;
   }
    
   /**
    * Gets the New Money?  Y/N field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the New Money?  Y/N or null.
    */
   public final Boolean getNewMoney( int index )
   {
      return _NewMoney[index];
   }
    
   /**
    * Gets the New Money?  Y/N field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the New Money?  Y/N or the specified default value.
    */
   public final boolean getNewMoney( int index, boolean defaultValue )
   {
      return _NewMoney[index] == null ? defaultValue : _NewMoney[index].booleanValue();
   }
    
   /**
    * Gets the array of New Money?  Y/N fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of New Money?  Y/N values.
    */
   public final Boolean[] getNewMoneyArray()
   {
      return _NewMoney;
   }
    
   /**
    * Gets the Sponsor field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sponsor or null.
    */
   public final String getSponsor( int index )
   {
      return _Sponsor[index];
   }
    
   /**
    * Gets the Sponsor field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sponsor or the specified default value.
    */
   public final String getSponsor( int index, String defaultValue )
   {
      return _Sponsor[index] == null ? defaultValue : _Sponsor[index];
   }
    
   /**
    * Gets the array of Sponsor fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sponsor values.
    */
   public final String[] getSponsorArray()
   {
      return _Sponsor;
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
      
      _FundToCode = resizeArray( _FundToCode, _RepeatCount );
      _ClassToCode = resizeArray( _ClassToCode, _RepeatCount );
      _NewMoney = resizeArray( _NewMoney, _RepeatCount );
      _Sponsor = resizeArray( _Sponsor, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundToCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassToCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NewMoney[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Sponsor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
