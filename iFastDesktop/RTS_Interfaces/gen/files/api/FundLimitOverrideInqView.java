
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Limitation Override Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundLimitOverrideInq.doc">FundLimitOverrideInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundLimitOverrideInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Tax Jurisdiction member array.
    */
   private String[] _TaxJuris = null;
   
   /**
    * Province of Residence member array.
    */
   private String[] _ProvRes = null;
   
   /**
    * Taxation Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Account Type member array.
    */
   private String[] _AcctType = null;
   
   /**
    * Account Designation member array.
    */
   private String[] _AcctDesignation = null;
   
   /**
    * Stop Flag member array.
    */
   private Boolean[] _StopFlag = null;
   
   /**
    * Stop Flag Error Severity member array.
    */
   private String[] _StopFlagEWI = null;
   
   /**
    * Minimum Initial Amount member array.
    */
   private String[] _MinInitAmt = null;
   
   /**
    * Minimum Initial Amount Error Severity member array.
    */
   private String[] _MinInitAmtEWI = null;
   
   /**
    * Minimum Subsequent Amount member array.
    */
   private String[] _MinSubsequentAmt = null;
   
   /**
    * Minimum Subsequent Amount Error Severity member array.
    */
   private String[] _MinSubsequentAmtEWI = null;
   
   /**
    * RuleType member array.
    */
   private String[] _RuleType = null;
   

   /**
    * Constructs the FundLimitOverrideInqView object.
    * 
    */
   public FundLimitOverrideInqView()
   {
      super ( new FundLimitOverrideInqRequest() );
   }

   /**
    * Constructs the FundLimitOverrideInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundLimitOverrideInqView( String hostEncoding )
   {
      super ( new FundLimitOverrideInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundLimitOverrideInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundLimitOverrideInqRequest object.
    */
   public final FundLimitOverrideInqRequest getRequest()
   {
      return (FundLimitOverrideInqRequest)getIFastRequest();
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
    * Gets the Tax Jurisdiction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Jurisdiction or null.
    */
   public final String getTaxJuris( int index )
   {
      return _TaxJuris[index];
   }
    
   /**
    * Gets the Tax Jurisdiction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Jurisdiction or the specified default value.
    */
   public final String getTaxJuris( int index, String defaultValue )
   {
      return _TaxJuris[index] == null ? defaultValue : _TaxJuris[index];
   }
    
   /**
    * Gets the array of Tax Jurisdiction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Jurisdiction values.
    */
   public final String[] getTaxJurisArray()
   {
      return _TaxJuris;
   }
    
   /**
    * Gets the Province of Residence field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Province of Residence or null.
    */
   public final String getProvRes( int index )
   {
      return _ProvRes[index];
   }
    
   /**
    * Gets the Province of Residence field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Province of Residence or the specified default value.
    */
   public final String getProvRes( int index, String defaultValue )
   {
      return _ProvRes[index] == null ? defaultValue : _ProvRes[index];
   }
    
   /**
    * Gets the array of Province of Residence fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Province of Residence values.
    */
   public final String[] getProvResArray()
   {
      return _ProvRes;
   }
    
   /**
    * Gets the Taxation Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Taxation Type or null.
    */
   public final String getTaxType( int index )
   {
      return _TaxType[index];
   }
    
   /**
    * Gets the Taxation Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Taxation Type or the specified default value.
    */
   public final String getTaxType( int index, String defaultValue )
   {
      return _TaxType[index] == null ? defaultValue : _TaxType[index];
   }
    
   /**
    * Gets the array of Taxation Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Taxation Type values.
    */
   public final String[] getTaxTypeArray()
   {
      return _TaxType;
   }
    
   /**
    * Gets the Account Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Type or null.
    */
   public final String getAcctType( int index )
   {
      return _AcctType[index];
   }
    
   /**
    * Gets the Account Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Type or the specified default value.
    */
   public final String getAcctType( int index, String defaultValue )
   {
      return _AcctType[index] == null ? defaultValue : _AcctType[index];
   }
    
   /**
    * Gets the array of Account Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Type values.
    */
   public final String[] getAcctTypeArray()
   {
      return _AcctType;
   }
    
   /**
    * Gets the Account Designation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Designation or null.
    */
   public final String getAcctDesignation( int index )
   {
      return _AcctDesignation[index];
   }
    
   /**
    * Gets the Account Designation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Designation or the specified default value.
    */
   public final String getAcctDesignation( int index, String defaultValue )
   {
      return _AcctDesignation[index] == null ? defaultValue : _AcctDesignation[index];
   }
    
   /**
    * Gets the array of Account Designation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Designation values.
    */
   public final String[] getAcctDesignationArray()
   {
      return _AcctDesignation;
   }
    
   /**
    * Gets the Stop Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Flag or null.
    */
   public final Boolean getStopFlag( int index )
   {
      return _StopFlag[index];
   }
    
   /**
    * Gets the Stop Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Flag or the specified default value.
    */
   public final boolean getStopFlag( int index, boolean defaultValue )
   {
      return _StopFlag[index] == null ? defaultValue : _StopFlag[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Flag values.
    */
   public final Boolean[] getStopFlagArray()
   {
      return _StopFlag;
   }
    
   /**
    * Gets the Stop Flag Error Severity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Flag Error Severity or null.
    */
   public final String getStopFlagEWI( int index )
   {
      return _StopFlagEWI[index];
   }
    
   /**
    * Gets the Stop Flag Error Severity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Flag Error Severity or the specified default value.
    */
   public final String getStopFlagEWI( int index, String defaultValue )
   {
      return _StopFlagEWI[index] == null ? defaultValue : _StopFlagEWI[index];
   }
    
   /**
    * Gets the array of Stop Flag Error Severity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Flag Error Severity values.
    */
   public final String[] getStopFlagEWIArray()
   {
      return _StopFlagEWI;
   }
    
   /**
    * Gets the Minimum Initial Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Initial Amount or null.
    */
   public final String getMinInitAmt( int index )
   {
      return _MinInitAmt[index];
   }
    
   /**
    * Gets the Minimum Initial Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Initial Amount or the specified default value.
    */
   public final String getMinInitAmt( int index, String defaultValue )
   {
      return _MinInitAmt[index] == null ? defaultValue : _MinInitAmt[index];
   }
    
   /**
    * Gets the array of Minimum Initial Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Initial Amount values.
    */
   public final String[] getMinInitAmtArray()
   {
      return _MinInitAmt;
   }
    
   /**
    * Gets the Minimum Initial Amount Error Severity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Initial Amount Error Severity or null.
    */
   public final String getMinInitAmtEWI( int index )
   {
      return _MinInitAmtEWI[index];
   }
    
   /**
    * Gets the Minimum Initial Amount Error Severity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Initial Amount Error Severity or the specified default value.
    */
   public final String getMinInitAmtEWI( int index, String defaultValue )
   {
      return _MinInitAmtEWI[index] == null ? defaultValue : _MinInitAmtEWI[index];
   }
    
   /**
    * Gets the array of Minimum Initial Amount Error Severity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Initial Amount Error Severity values.
    */
   public final String[] getMinInitAmtEWIArray()
   {
      return _MinInitAmtEWI;
   }
    
   /**
    * Gets the Minimum Subsequent Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Subsequent Amount or null.
    */
   public final String getMinSubsequentAmt( int index )
   {
      return _MinSubsequentAmt[index];
   }
    
   /**
    * Gets the Minimum Subsequent Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Subsequent Amount or the specified default value.
    */
   public final String getMinSubsequentAmt( int index, String defaultValue )
   {
      return _MinSubsequentAmt[index] == null ? defaultValue : _MinSubsequentAmt[index];
   }
    
   /**
    * Gets the array of Minimum Subsequent Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Subsequent Amount values.
    */
   public final String[] getMinSubsequentAmtArray()
   {
      return _MinSubsequentAmt;
   }
    
   /**
    * Gets the Minimum Subsequent Amount Error Severity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Subsequent Amount Error Severity or null.
    */
   public final String getMinSubsequentAmtEWI( int index )
   {
      return _MinSubsequentAmtEWI[index];
   }
    
   /**
    * Gets the Minimum Subsequent Amount Error Severity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Subsequent Amount Error Severity or the specified default value.
    */
   public final String getMinSubsequentAmtEWI( int index, String defaultValue )
   {
      return _MinSubsequentAmtEWI[index] == null ? defaultValue : _MinSubsequentAmtEWI[index];
   }
    
   /**
    * Gets the array of Minimum Subsequent Amount Error Severity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Subsequent Amount Error Severity values.
    */
   public final String[] getMinSubsequentAmtEWIArray()
   {
      return _MinSubsequentAmtEWI;
   }
    
   /**
    * Gets the RuleType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RuleType or null.
    */
   public final String getRuleType( int index )
   {
      return _RuleType[index];
   }
    
   /**
    * Gets the RuleType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RuleType or the specified default value.
    */
   public final String getRuleType( int index, String defaultValue )
   {
      return _RuleType[index] == null ? defaultValue : _RuleType[index];
   }
    
   /**
    * Gets the array of RuleType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RuleType values.
    */
   public final String[] getRuleTypeArray()
   {
      return _RuleType;
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
      
      _TaxJuris = resizeArray( _TaxJuris, _RepeatCount );
      _ProvRes = resizeArray( _ProvRes, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _AcctType = resizeArray( _AcctType, _RepeatCount );
      _AcctDesignation = resizeArray( _AcctDesignation, _RepeatCount );
      _StopFlag = resizeArray( _StopFlag, _RepeatCount );
      _StopFlagEWI = resizeArray( _StopFlagEWI, _RepeatCount );
      _MinInitAmt = resizeArray( _MinInitAmt, _RepeatCount );
      _MinInitAmtEWI = resizeArray( _MinInitAmtEWI, _RepeatCount );
      _MinSubsequentAmt = resizeArray( _MinSubsequentAmt, _RepeatCount );
      _MinSubsequentAmtEWI = resizeArray( _MinSubsequentAmtEWI, _RepeatCount );
      _RuleType = resizeArray( _RuleType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TaxJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvRes[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDesignation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopFlag[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopFlagEWI[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinInitAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinInitAmtEWI[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinSubsequentAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinSubsequentAmtEWI[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RuleType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
