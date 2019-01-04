
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Valid Shareholder/Account view.
 * For additional view information see <A HREF="../../../../viewspecs/ValidShareholderAccount.doc">ValidShareholderAccount.doc</A>.
 * 
 * @author RTS Generated
 */
public class ValidShareholderAccountView extends IFastView implements Serializable
{

   /**
    * Shareholder/Account exists member variable.
    */
   private Boolean _DataFound = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Account Number member array.
    */
   private String[] _rxAcctNum = null;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Spouse's Date of Birth member array.
    */
   private Date[] _SpouseDOfB = null;
   

   /**
    * Constructs the ValidShareholderAccountView object.
    * 
    */
   public ValidShareholderAccountView()
   {
      super ( new ValidShareholderAccountRequest() );
   }

   /**
    * Constructs the ValidShareholderAccountView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ValidShareholderAccountView( String hostEncoding )
   {
      super ( new ValidShareholderAccountRequest( hostEncoding ) );
   }

   /**
    * Gets the ValidShareholderAccountRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ValidShareholderAccountRequest object.
    */
   public final ValidShareholderAccountRequest getRequest()
   {
      return (ValidShareholderAccountRequest)getIFastRequest();
   }
        
   /**
    * Gets the Shareholder/Account exists field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder/Account exists or null.
    */
   public final Boolean getDataFound()
   {
      return _DataFound;
   }
	
   /**
    * Gets the Shareholder/Account exists field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder/Account exists or the specified default value.
    */
   public final boolean getDataFound( boolean defaultValue )
   {
      return _DataFound == null ? defaultValue : _DataFound.booleanValue();
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
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getrxAcctNum( int index )
   {
      return _rxAcctNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getrxAcctNum( int index, String defaultValue )
   {
      return _rxAcctNum[index] == null ? defaultValue : _rxAcctNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getrxAcctNumArray()
   {
      return _rxAcctNum;
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type or null.
    */
   public final String getTaxType( int index )
   {
      return _TaxType[index];
   }
    
   /**
    * Gets the Tax Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type or the specified default value.
    */
   public final String getTaxType( int index, String defaultValue )
   {
      return _TaxType[index] == null ? defaultValue : _TaxType[index];
   }
    
   /**
    * Gets the array of Tax Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type values.
    */
   public final String[] getTaxTypeArray()
   {
      return _TaxType;
   }
    
   /**
    * Gets the Spouse's Date of Birth field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Spouse's Date of Birth or null.
    */
   public final Date getSpouseDOfB( int index )
   {
      return _SpouseDOfB[index];
   }
    
   /**
    * Gets the Spouse's Date of Birth field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Spouse's Date of Birth or the specified default value.
    */
   public final Date getSpouseDOfB( int index, Date defaultValue )
   {
      return _SpouseDOfB[index] == null ? defaultValue : _SpouseDOfB[index];
   }
    
   /**
    * Gets the array of Spouse's Date of Birth fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Spouse's Date of Birth values.
    */
   public final Date[] getSpouseDOfBArray()
   {
      return _SpouseDOfB;
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
      _DataFound = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxAcctNum = resizeArray( _rxAcctNum, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _SpouseDOfB = resizeArray( _SpouseDOfB, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SpouseDOfB[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
