
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Estate Allocations Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/EsteAllocInq.doc">EsteAllocInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class EsteAllocInqView extends IFastView implements Serializable
{

   /**
    * Full Redemtion amount member variable.
    */
   private String _FundClassAmtFullPW = null;
   
   /**
    * Fund Price member variable.
    */
   private String _FundNAV = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Entity ID member array.
    */
   private String[] _BenefEntityID = null;
   
   /**
    * ADCD member array.
    */
   private String[] _BenefAddrCode = null;
   
   /**
    * AddrLevel member array.
    */
   private String[] _BenefAddrLevel = null;
   
   /**
    * BenefPrcnt member array.
    */
   private String[] _BenefPrcnt = null;
   
   /**
    * Amount member array.
    */
   private String[] _BenefAmount = null;
   
   /**
    * Units member array.
    */
   private String[] _BenefUnits = null;
   
   /**
    * BenefName member array.
    */
   private String[] _BenefName = null;
   
   /**
    * Beneficiary Record Type member array.
    */
   private String[] _BenefRecType = null;
   

   /**
    * Constructs the EsteAllocInqView object.
    * 
    */
   public EsteAllocInqView()
   {
      super ( new EsteAllocInqRequest() );
   }

   /**
    * Constructs the EsteAllocInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public EsteAllocInqView( String hostEncoding )
   {
      super ( new EsteAllocInqRequest( hostEncoding ) );
   }

   /**
    * Gets the EsteAllocInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The EsteAllocInqRequest object.
    */
   public final EsteAllocInqRequest getRequest()
   {
      return (EsteAllocInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Full Redemtion amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Full Redemtion amount or null.
    */
   public final String getFundClassAmtFullPW()
   {
      return _FundClassAmtFullPW;
   }
	
   /**
    * Gets the Full Redemtion amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Full Redemtion amount or the specified default value.
    */
   public final String getFundClassAmtFullPW( String defaultValue )
   {
      return _FundClassAmtFullPW == null ? defaultValue : _FundClassAmtFullPW;
   }
                  
   /**
    * Gets the Fund Price field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund Price or null.
    */
   public final String getFundNAV()
   {
      return _FundNAV;
   }
	
   /**
    * Gets the Fund Price field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Price or the specified default value.
    */
   public final String getFundNAV( String defaultValue )
   {
      return _FundNAV == null ? defaultValue : _FundNAV;
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
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity ID or null.
    */
   public final String getBenefEntityID( int index )
   {
      return _BenefEntityID[index];
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity ID or the specified default value.
    */
   public final String getBenefEntityID( int index, String defaultValue )
   {
      return _BenefEntityID[index] == null ? defaultValue : _BenefEntityID[index];
   }
    
   /**
    * Gets the array of Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity ID values.
    */
   public final String[] getBenefEntityIDArray()
   {
      return _BenefEntityID;
   }
    
   /**
    * Gets the ADCD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ADCD or null.
    */
   public final String getBenefAddrCode( int index )
   {
      return _BenefAddrCode[index];
   }
    
   /**
    * Gets the ADCD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ADCD or the specified default value.
    */
   public final String getBenefAddrCode( int index, String defaultValue )
   {
      return _BenefAddrCode[index] == null ? defaultValue : _BenefAddrCode[index];
   }
    
   /**
    * Gets the array of ADCD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ADCD values.
    */
   public final String[] getBenefAddrCodeArray()
   {
      return _BenefAddrCode;
   }
    
   /**
    * Gets the AddrLevel field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AddrLevel or null.
    */
   public final String getBenefAddrLevel( int index )
   {
      return _BenefAddrLevel[index];
   }
    
   /**
    * Gets the AddrLevel field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrLevel or the specified default value.
    */
   public final String getBenefAddrLevel( int index, String defaultValue )
   {
      return _BenefAddrLevel[index] == null ? defaultValue : _BenefAddrLevel[index];
   }
    
   /**
    * Gets the array of AddrLevel fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AddrLevel values.
    */
   public final String[] getBenefAddrLevelArray()
   {
      return _BenefAddrLevel;
   }
    
   /**
    * Gets the BenefPrcnt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BenefPrcnt or null.
    */
   public final String getBenefPrcnt( int index )
   {
      return _BenefPrcnt[index];
   }
    
   /**
    * Gets the BenefPrcnt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BenefPrcnt or the specified default value.
    */
   public final String getBenefPrcnt( int index, String defaultValue )
   {
      return _BenefPrcnt[index] == null ? defaultValue : _BenefPrcnt[index];
   }
    
   /**
    * Gets the array of BenefPrcnt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BenefPrcnt values.
    */
   public final String[] getBenefPrcntArray()
   {
      return _BenefPrcnt;
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount or null.
    */
   public final String getBenefAmount( int index )
   {
      return _BenefAmount[index];
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getBenefAmount( int index, String defaultValue )
   {
      return _BenefAmount[index] == null ? defaultValue : _BenefAmount[index];
   }
    
   /**
    * Gets the array of Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount values.
    */
   public final String[] getBenefAmountArray()
   {
      return _BenefAmount;
   }
    
   /**
    * Gets the Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Units or null.
    */
   public final String getBenefUnits( int index )
   {
      return _BenefUnits[index];
   }
    
   /**
    * Gets the Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Units or the specified default value.
    */
   public final String getBenefUnits( int index, String defaultValue )
   {
      return _BenefUnits[index] == null ? defaultValue : _BenefUnits[index];
   }
    
   /**
    * Gets the array of Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Units values.
    */
   public final String[] getBenefUnitsArray()
   {
      return _BenefUnits;
   }
    
   /**
    * Gets the BenefName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BenefName or null.
    */
   public final String getBenefName( int index )
   {
      return _BenefName[index];
   }
    
   /**
    * Gets the BenefName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BenefName or the specified default value.
    */
   public final String getBenefName( int index, String defaultValue )
   {
      return _BenefName[index] == null ? defaultValue : _BenefName[index];
   }
    
   /**
    * Gets the array of BenefName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BenefName values.
    */
   public final String[] getBenefNameArray()
   {
      return _BenefName;
   }
    
   /**
    * Gets the Beneficiary Record Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficiary Record Type or null.
    */
   public final String getBenefRecType( int index )
   {
      return _BenefRecType[index];
   }
    
   /**
    * Gets the Beneficiary Record Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Record Type or the specified default value.
    */
   public final String getBenefRecType( int index, String defaultValue )
   {
      return _BenefRecType[index] == null ? defaultValue : _BenefRecType[index];
   }
    
   /**
    * Gets the array of Beneficiary Record Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficiary Record Type values.
    */
   public final String[] getBenefRecTypeArray()
   {
      return _BenefRecType;
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
      _FundClassAmtFullPW = responseBuffer.decodeString(responseBuffer.getNextField());
      _FundNAV = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _BenefEntityID = resizeArray( _BenefEntityID, _RepeatCount );
      _BenefAddrCode = resizeArray( _BenefAddrCode, _RepeatCount );
      _BenefAddrLevel = resizeArray( _BenefAddrLevel, _RepeatCount );
      _BenefPrcnt = resizeArray( _BenefPrcnt, _RepeatCount );
      _BenefAmount = resizeArray( _BenefAmount, _RepeatCount );
      _BenefUnits = resizeArray( _BenefUnits, _RepeatCount );
      _BenefName = resizeArray( _BenefName, _RepeatCount );
      _BenefRecType = resizeArray( _BenefRecType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _BenefEntityID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenefAddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenefAddrLevel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenefPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenefAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenefUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenefName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenefRecType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
