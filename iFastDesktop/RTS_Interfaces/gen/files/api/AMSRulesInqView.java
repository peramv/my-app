
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * AMS Rules Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AMSRulesInq.doc">AMSRulesInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSRulesInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * RuleType member array.
    */
   private String[] _RuleType = null;
   
   /**
    * Override Decimal member array.
    */
   private String[] _OverRideDec = null;
   
   /**
    * OverRide Log member array.
    */
   private Boolean[] _OverRideLog = null;
   
   /**
    * OverRide Fund member array.
    */
   private Boolean[] _OverRideFund = null;
   
   /**
    * TaxJurisDecl member array.
    */
   private String[] _TaxJurisDecl = null;
   
   /**
    * ProvResDecl member array.
    */
   private String[] _ProvResDecl = null;
   
   /**
    * TaxTypeDecl member array.
    */
   private String[] _TaxTypeDecl = null;
   
   /**
    * Account Type Declaratation member array.
    */
   private String[] _AcctTypeDecl = null;
   
   /**
    * Account Designation Declaration member array.
    */
   private String[] _AcctDesigDecl = null;
   
   /**
    * OnLine EWI member array.
    */
   private String[] _OnLineEWi = null;
   
   /**
    * Cycle EWI member array.
    */
   private String[] _CycleEWI = null;
   
   /**
    * ESG EWI member array.
    */
   private String[] _ESGEWI = null;
   
   /**
    * AMSRuleID member array.
    */
   private Integer[] _AMSRuleID = null;
   
   /**
    * ModUser member array.
    */
   private String[] _ModUser = null;
   
   /**
    * ModDate member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * ProcessDate member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Username member array.
    */
   private String[] _UserName = null;
   

   /**
    * Constructs the AMSRulesInqView object.
    * 
    */
   public AMSRulesInqView()
   {
      super ( new AMSRulesInqRequest() );
   }

   /**
    * Constructs the AMSRulesInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AMSRulesInqView( String hostEncoding )
   {
      super ( new AMSRulesInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AMSRulesInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AMSRulesInqRequest object.
    */
   public final AMSRulesInqRequest getRequest()
   {
      return (AMSRulesInqRequest)getIFastRequest();
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
    * Gets the Override Decimal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Decimal or null.
    */
   public final String getOverRideDec( int index )
   {
      return _OverRideDec[index];
   }
    
   /**
    * Gets the Override Decimal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Decimal or the specified default value.
    */
   public final String getOverRideDec( int index, String defaultValue )
   {
      return _OverRideDec[index] == null ? defaultValue : _OverRideDec[index];
   }
    
   /**
    * Gets the array of Override Decimal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Decimal values.
    */
   public final String[] getOverRideDecArray()
   {
      return _OverRideDec;
   }
    
   /**
    * Gets the OverRide Log field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OverRide Log or null.
    */
   public final Boolean getOverRideLog( int index )
   {
      return _OverRideLog[index];
   }
    
   /**
    * Gets the OverRide Log field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OverRide Log or the specified default value.
    */
   public final boolean getOverRideLog( int index, boolean defaultValue )
   {
      return _OverRideLog[index] == null ? defaultValue : _OverRideLog[index].booleanValue();
   }
    
   /**
    * Gets the array of OverRide Log fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OverRide Log values.
    */
   public final Boolean[] getOverRideLogArray()
   {
      return _OverRideLog;
   }
    
   /**
    * Gets the OverRide Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OverRide Fund or null.
    */
   public final Boolean getOverRideFund( int index )
   {
      return _OverRideFund[index];
   }
    
   /**
    * Gets the OverRide Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OverRide Fund or the specified default value.
    */
   public final boolean getOverRideFund( int index, boolean defaultValue )
   {
      return _OverRideFund[index] == null ? defaultValue : _OverRideFund[index].booleanValue();
   }
    
   /**
    * Gets the array of OverRide Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OverRide Fund values.
    */
   public final Boolean[] getOverRideFundArray()
   {
      return _OverRideFund;
   }
    
   /**
    * Gets the TaxJurisDecl field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TaxJurisDecl or null.
    */
   public final String getTaxJurisDecl( int index )
   {
      return _TaxJurisDecl[index];
   }
    
   /**
    * Gets the TaxJurisDecl field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TaxJurisDecl or the specified default value.
    */
   public final String getTaxJurisDecl( int index, String defaultValue )
   {
      return _TaxJurisDecl[index] == null ? defaultValue : _TaxJurisDecl[index];
   }
    
   /**
    * Gets the array of TaxJurisDecl fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TaxJurisDecl values.
    */
   public final String[] getTaxJurisDeclArray()
   {
      return _TaxJurisDecl;
   }
    
   /**
    * Gets the ProvResDecl field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProvResDecl or null.
    */
   public final String getProvResDecl( int index )
   {
      return _ProvResDecl[index];
   }
    
   /**
    * Gets the ProvResDecl field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProvResDecl or the specified default value.
    */
   public final String getProvResDecl( int index, String defaultValue )
   {
      return _ProvResDecl[index] == null ? defaultValue : _ProvResDecl[index];
   }
    
   /**
    * Gets the array of ProvResDecl fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProvResDecl values.
    */
   public final String[] getProvResDeclArray()
   {
      return _ProvResDecl;
   }
    
   /**
    * Gets the TaxTypeDecl field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TaxTypeDecl or null.
    */
   public final String getTaxTypeDecl( int index )
   {
      return _TaxTypeDecl[index];
   }
    
   /**
    * Gets the TaxTypeDecl field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TaxTypeDecl or the specified default value.
    */
   public final String getTaxTypeDecl( int index, String defaultValue )
   {
      return _TaxTypeDecl[index] == null ? defaultValue : _TaxTypeDecl[index];
   }
    
   /**
    * Gets the array of TaxTypeDecl fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TaxTypeDecl values.
    */
   public final String[] getTaxTypeDeclArray()
   {
      return _TaxTypeDecl;
   }
    
   /**
    * Gets the Account Type Declaratation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Type Declaratation or null.
    */
   public final String getAcctTypeDecl( int index )
   {
      return _AcctTypeDecl[index];
   }
    
   /**
    * Gets the Account Type Declaratation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Type Declaratation or the specified default value.
    */
   public final String getAcctTypeDecl( int index, String defaultValue )
   {
      return _AcctTypeDecl[index] == null ? defaultValue : _AcctTypeDecl[index];
   }
    
   /**
    * Gets the array of Account Type Declaratation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Type Declaratation values.
    */
   public final String[] getAcctTypeDeclArray()
   {
      return _AcctTypeDecl;
   }
    
   /**
    * Gets the Account Designation Declaration field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Designation Declaration or null.
    */
   public final String getAcctDesigDecl( int index )
   {
      return _AcctDesigDecl[index];
   }
    
   /**
    * Gets the Account Designation Declaration field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Designation Declaration or the specified default value.
    */
   public final String getAcctDesigDecl( int index, String defaultValue )
   {
      return _AcctDesigDecl[index] == null ? defaultValue : _AcctDesigDecl[index];
   }
    
   /**
    * Gets the array of Account Designation Declaration fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Designation Declaration values.
    */
   public final String[] getAcctDesigDeclArray()
   {
      return _AcctDesigDecl;
   }
    
   /**
    * Gets the OnLine EWI field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OnLine EWI or null.
    */
   public final String getOnLineEWi( int index )
   {
      return _OnLineEWi[index];
   }
    
   /**
    * Gets the OnLine EWI field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OnLine EWI or the specified default value.
    */
   public final String getOnLineEWi( int index, String defaultValue )
   {
      return _OnLineEWi[index] == null ? defaultValue : _OnLineEWi[index];
   }
    
   /**
    * Gets the array of OnLine EWI fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OnLine EWI values.
    */
   public final String[] getOnLineEWiArray()
   {
      return _OnLineEWi;
   }
    
   /**
    * Gets the Cycle EWI field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cycle EWI or null.
    */
   public final String getCycleEWI( int index )
   {
      return _CycleEWI[index];
   }
    
   /**
    * Gets the Cycle EWI field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cycle EWI or the specified default value.
    */
   public final String getCycleEWI( int index, String defaultValue )
   {
      return _CycleEWI[index] == null ? defaultValue : _CycleEWI[index];
   }
    
   /**
    * Gets the array of Cycle EWI fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cycle EWI values.
    */
   public final String[] getCycleEWIArray()
   {
      return _CycleEWI;
   }
    
   /**
    * Gets the ESG EWI field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ESG EWI or null.
    */
   public final String getESGEWI( int index )
   {
      return _ESGEWI[index];
   }
    
   /**
    * Gets the ESG EWI field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ESG EWI or the specified default value.
    */
   public final String getESGEWI( int index, String defaultValue )
   {
      return _ESGEWI[index] == null ? defaultValue : _ESGEWI[index];
   }
    
   /**
    * Gets the array of ESG EWI fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ESG EWI values.
    */
   public final String[] getESGEWIArray()
   {
      return _ESGEWI;
   }
    
   /**
    * Gets the AMSRuleID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMSRuleID or null.
    */
   public final Integer getAMSRuleID( int index )
   {
      return _AMSRuleID[index];
   }
    
   /**
    * Gets the AMSRuleID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMSRuleID or the specified default value.
    */
   public final int getAMSRuleID( int index, int defaultValue )
   {
      return _AMSRuleID[index] == null ? defaultValue : _AMSRuleID[index].intValue();
   }
    
   /**
    * Gets the array of AMSRuleID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMSRuleID values.
    */
   public final Integer[] getAMSRuleIDArray()
   {
      return _AMSRuleID;
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
    * Gets the Username field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Username or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the Username field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Username or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of Username fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Username values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
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
      
      _RuleType = resizeArray( _RuleType, _RepeatCount );
      _OverRideDec = resizeArray( _OverRideDec, _RepeatCount );
      _OverRideLog = resizeArray( _OverRideLog, _RepeatCount );
      _OverRideFund = resizeArray( _OverRideFund, _RepeatCount );
      _TaxJurisDecl = resizeArray( _TaxJurisDecl, _RepeatCount );
      _ProvResDecl = resizeArray( _ProvResDecl, _RepeatCount );
      _TaxTypeDecl = resizeArray( _TaxTypeDecl, _RepeatCount );
      _AcctTypeDecl = resizeArray( _AcctTypeDecl, _RepeatCount );
      _AcctDesigDecl = resizeArray( _AcctDesigDecl, _RepeatCount );
      _OnLineEWi = resizeArray( _OnLineEWi, _RepeatCount );
      _CycleEWI = resizeArray( _CycleEWI, _RepeatCount );
      _ESGEWI = resizeArray( _ESGEWI, _RepeatCount );
      _AMSRuleID = resizeArray( _AMSRuleID, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RuleType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OverRideDec[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OverRideLog[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OverRideFund[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxJurisDecl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvResDecl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxTypeDecl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctTypeDecl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDesigDecl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OnLineEWi[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CycleEWI[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ESGEWI[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AMSRuleID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
