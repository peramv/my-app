
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Entity Associates Accounts view.
 * For additional view information see <A HREF="../../../../viewspecs/EntityAccts.doc">EntityAccts.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntityAcctsView extends IFastView implements Serializable
{

   /**
    * Inidates if duplicate record exist member variable.
    */
   private Boolean _DuplicateExists = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Account Number member array.
    */
   private String[] _rxAccountNum = null;
   
   /**
    * Entity Type member array.
    */
   private String[] _EntityType = null;
   
   /**
    * Entity Type Description member array.
    */
   private String[] _EntityTypeDesc = null;
   
   /**
    * Shareholder Number member array.
    */
   private String[] _ShrNum = null;
   
   /**
    * Tax Type Description member array.
    */
   private String[] _TaxTypeDesc = null;
   
   /**
    * Account Type Description member array.
    */
   private String[] _AcctTypeDesc = null;
   
   /**
    * Account Status Description member array.
    */
   private String[] _AcctStatusDesc = null;
   
   /**
    * Account Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Account Settled Market Value member array.
    */
   private String[] _AccountBalance = null;
   
   /**
    * Entity Type Sequence member array.
    */
   private Integer[] _EntityTypeSeq = null;
   
   /**
    * Account Designation member array.
    */
   private String[] _AcctDesignation = null;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Account Type member array.
    */
   private String[] _AcctType = null;
   
   /**
    * Account Status member array.
    */
   private String[] _AcctStatus = null;
   
   /**
    * Currency Code member array.
    */
   private String[] _CurrencyCode = null;
   
   /**
    * Registration Information member array.
    */
   private String[] _RegistrationInfo = null;
   
   /**
    * Where Use member array.
    */
   private String[] _WhereUse = null;
   
   /**
    * Where Use Code member array.
    */
   private String[] _WhereUseCode = null;
   
   /**
    * EntitiyWhereUse Record ID member array.
    */
   private Integer[] _EntityWhereUseRid = null;
   
   /**
    * EntityWhereUse Version member array.
    */
   private Integer[] _EntityWhereUseVer = null;
   
   /**
    * Effective date of entity usage member array.
    */
   private Date[] _rxEffectiveDate = null;
   
   /**
    * Date the entity usage stops member array.
    */
   private Date[] _rxStopDate = null;
   
   /**
    * Entity ID member array.
    */
   private String[] _rxEntityID = null;
   

   /**
    * Constructs the EntityAcctsView object.
    * 
    */
   public EntityAcctsView()
   {
      super ( new EntityAcctsRequest() );
   }

   /**
    * Constructs the EntityAcctsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public EntityAcctsView( String hostEncoding )
   {
      super ( new EntityAcctsRequest( hostEncoding ) );
   }

   /**
    * Gets the EntityAcctsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The EntityAcctsRequest object.
    */
   public final EntityAcctsRequest getRequest()
   {
      return (EntityAcctsRequest)getIFastRequest();
   }
        
   /**
    * Gets the Inidates if duplicate record exist field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Inidates if duplicate record exist or null.
    */
   public final Boolean getDuplicateExists()
   {
      return _DuplicateExists;
   }
	
   /**
    * Gets the Inidates if duplicate record exist field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Inidates if duplicate record exist or the specified default value.
    */
   public final boolean getDuplicateExists( boolean defaultValue )
   {
      return _DuplicateExists == null ? defaultValue : _DuplicateExists.booleanValue();
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
   public final String getrxAccountNum( int index )
   {
      return _rxAccountNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getrxAccountNum( int index, String defaultValue )
   {
      return _rxAccountNum[index] == null ? defaultValue : _rxAccountNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getrxAccountNumArray()
   {
      return _rxAccountNum;
   }
    
   /**
    * Gets the Entity Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type or null.
    */
   public final String getEntityType( int index )
   {
      return _EntityType[index];
   }
    
   /**
    * Gets the Entity Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type or the specified default value.
    */
   public final String getEntityType( int index, String defaultValue )
   {
      return _EntityType[index] == null ? defaultValue : _EntityType[index];
   }
    
   /**
    * Gets the array of Entity Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type values.
    */
   public final String[] getEntityTypeArray()
   {
      return _EntityType;
   }
    
   /**
    * Gets the Entity Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type Description or null.
    */
   public final String getEntityTypeDesc( int index )
   {
      return _EntityTypeDesc[index];
   }
    
   /**
    * Gets the Entity Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type Description or the specified default value.
    */
   public final String getEntityTypeDesc( int index, String defaultValue )
   {
      return _EntityTypeDesc[index] == null ? defaultValue : _EntityTypeDesc[index];
   }
    
   /**
    * Gets the array of Entity Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type Description values.
    */
   public final String[] getEntityTypeDescArray()
   {
      return _EntityTypeDesc;
   }
    
   /**
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Number or null.
    */
   public final String getShrNum( int index )
   {
      return _ShrNum[index];
   }
    
   /**
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number or the specified default value.
    */
   public final String getShrNum( int index, String defaultValue )
   {
      return _ShrNum[index] == null ? defaultValue : _ShrNum[index];
   }
    
   /**
    * Gets the array of Shareholder Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Number values.
    */
   public final String[] getShrNumArray()
   {
      return _ShrNum;
   }
    
   /**
    * Gets the Tax Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type Description or null.
    */
   public final String getTaxTypeDesc( int index )
   {
      return _TaxTypeDesc[index];
   }
    
   /**
    * Gets the Tax Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type Description or the specified default value.
    */
   public final String getTaxTypeDesc( int index, String defaultValue )
   {
      return _TaxTypeDesc[index] == null ? defaultValue : _TaxTypeDesc[index];
   }
    
   /**
    * Gets the array of Tax Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type Description values.
    */
   public final String[] getTaxTypeDescArray()
   {
      return _TaxTypeDesc;
   }
    
   /**
    * Gets the Account Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Type Description or null.
    */
   public final String getAcctTypeDesc( int index )
   {
      return _AcctTypeDesc[index];
   }
    
   /**
    * Gets the Account Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Type Description or the specified default value.
    */
   public final String getAcctTypeDesc( int index, String defaultValue )
   {
      return _AcctTypeDesc[index] == null ? defaultValue : _AcctTypeDesc[index];
   }
    
   /**
    * Gets the array of Account Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Type Description values.
    */
   public final String[] getAcctTypeDescArray()
   {
      return _AcctTypeDesc;
   }
    
   /**
    * Gets the Account Status Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Status Description or null.
    */
   public final String getAcctStatusDesc( int index )
   {
      return _AcctStatusDesc[index];
   }
    
   /**
    * Gets the Account Status Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Status Description or the specified default value.
    */
   public final String getAcctStatusDesc( int index, String defaultValue )
   {
      return _AcctStatusDesc[index] == null ? defaultValue : _AcctStatusDesc[index];
   }
    
   /**
    * Gets the array of Account Status Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Status Description values.
    */
   public final String[] getAcctStatusDescArray()
   {
      return _AcctStatusDesc;
   }
    
   /**
    * Gets the Account Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Currency or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Account Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Currency or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Account Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Currency values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the Account Settled Market Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Settled Market Value or null.
    */
   public final String getAccountBalance( int index )
   {
      return _AccountBalance[index];
   }
    
   /**
    * Gets the Account Settled Market Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Settled Market Value or the specified default value.
    */
   public final String getAccountBalance( int index, String defaultValue )
   {
      return _AccountBalance[index] == null ? defaultValue : _AccountBalance[index];
   }
    
   /**
    * Gets the array of Account Settled Market Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Settled Market Value values.
    */
   public final String[] getAccountBalanceArray()
   {
      return _AccountBalance;
   }
    
   /**
    * Gets the Entity Type Sequence field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type Sequence or null.
    */
   public final Integer getEntityTypeSeq( int index )
   {
      return _EntityTypeSeq[index];
   }
    
   /**
    * Gets the Entity Type Sequence field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type Sequence or the specified default value.
    */
   public final int getEntityTypeSeq( int index, int defaultValue )
   {
      return _EntityTypeSeq[index] == null ? defaultValue : _EntityTypeSeq[index].intValue();
   }
    
   /**
    * Gets the array of Entity Type Sequence fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type Sequence values.
    */
   public final Integer[] getEntityTypeSeqArray()
   {
      return _EntityTypeSeq;
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
    * Gets the Account Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Status or null.
    */
   public final String getAcctStatus( int index )
   {
      return _AcctStatus[index];
   }
    
   /**
    * Gets the Account Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Status or the specified default value.
    */
   public final String getAcctStatus( int index, String defaultValue )
   {
      return _AcctStatus[index] == null ? defaultValue : _AcctStatus[index];
   }
    
   /**
    * Gets the array of Account Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Status values.
    */
   public final String[] getAcctStatusArray()
   {
      return _AcctStatus;
   }
    
   /**
    * Gets the Currency Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Code or null.
    */
   public final String getCurrencyCode( int index )
   {
      return _CurrencyCode[index];
   }
    
   /**
    * Gets the Currency Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Code or the specified default value.
    */
   public final String getCurrencyCode( int index, String defaultValue )
   {
      return _CurrencyCode[index] == null ? defaultValue : _CurrencyCode[index];
   }
    
   /**
    * Gets the array of Currency Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Code values.
    */
   public final String[] getCurrencyCodeArray()
   {
      return _CurrencyCode;
   }
    
   /**
    * Gets the Registration Information field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Registration Information or null.
    */
   public final String getRegistrationInfo( int index )
   {
      return _RegistrationInfo[index];
   }
    
   /**
    * Gets the Registration Information field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Registration Information or the specified default value.
    */
   public final String getRegistrationInfo( int index, String defaultValue )
   {
      return _RegistrationInfo[index] == null ? defaultValue : _RegistrationInfo[index];
   }
    
   /**
    * Gets the array of Registration Information fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Registration Information values.
    */
   public final String[] getRegistrationInfoArray()
   {
      return _RegistrationInfo;
   }
    
   /**
    * Gets the Where Use field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Where Use or null.
    */
   public final String getWhereUse( int index )
   {
      return _WhereUse[index];
   }
    
   /**
    * Gets the Where Use field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Where Use or the specified default value.
    */
   public final String getWhereUse( int index, String defaultValue )
   {
      return _WhereUse[index] == null ? defaultValue : _WhereUse[index];
   }
    
   /**
    * Gets the array of Where Use fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Where Use values.
    */
   public final String[] getWhereUseArray()
   {
      return _WhereUse;
   }
    
   /**
    * Gets the Where Use Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Where Use Code or null.
    */
   public final String getWhereUseCode( int index )
   {
      return _WhereUseCode[index];
   }
    
   /**
    * Gets the Where Use Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Where Use Code or the specified default value.
    */
   public final String getWhereUseCode( int index, String defaultValue )
   {
      return _WhereUseCode[index] == null ? defaultValue : _WhereUseCode[index];
   }
    
   /**
    * Gets the array of Where Use Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Where Use Code values.
    */
   public final String[] getWhereUseCodeArray()
   {
      return _WhereUseCode;
   }
    
   /**
    * Gets the EntitiyWhereUse Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EntitiyWhereUse Record ID or null.
    */
   public final Integer getEntityWhereUseRid( int index )
   {
      return _EntityWhereUseRid[index];
   }
    
   /**
    * Gets the EntitiyWhereUse Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EntitiyWhereUse Record ID or the specified default value.
    */
   public final int getEntityWhereUseRid( int index, int defaultValue )
   {
      return _EntityWhereUseRid[index] == null ? defaultValue : _EntityWhereUseRid[index].intValue();
   }
    
   /**
    * Gets the array of EntitiyWhereUse Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EntitiyWhereUse Record ID values.
    */
   public final Integer[] getEntityWhereUseRidArray()
   {
      return _EntityWhereUseRid;
   }
    
   /**
    * Gets the EntityWhereUse Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EntityWhereUse Version or null.
    */
   public final Integer getEntityWhereUseVer( int index )
   {
      return _EntityWhereUseVer[index];
   }
    
   /**
    * Gets the EntityWhereUse Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EntityWhereUse Version or the specified default value.
    */
   public final int getEntityWhereUseVer( int index, int defaultValue )
   {
      return _EntityWhereUseVer[index] == null ? defaultValue : _EntityWhereUseVer[index].intValue();
   }
    
   /**
    * Gets the array of EntityWhereUse Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EntityWhereUse Version values.
    */
   public final Integer[] getEntityWhereUseVerArray()
   {
      return _EntityWhereUseVer;
   }
    
   /**
    * Gets the Effective date of entity usage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective date of entity usage or null.
    */
   public final Date getrxEffectiveDate( int index )
   {
      return _rxEffectiveDate[index];
   }
    
   /**
    * Gets the Effective date of entity usage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective date of entity usage or the specified default value.
    */
   public final Date getrxEffectiveDate( int index, Date defaultValue )
   {
      return _rxEffectiveDate[index] == null ? defaultValue : _rxEffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective date of entity usage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective date of entity usage values.
    */
   public final Date[] getrxEffectiveDateArray()
   {
      return _rxEffectiveDate;
   }
    
   /**
    * Gets the Date the entity usage stops field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date the entity usage stops or null.
    */
   public final Date getrxStopDate( int index )
   {
      return _rxStopDate[index];
   }
    
   /**
    * Gets the Date the entity usage stops field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date the entity usage stops or the specified default value.
    */
   public final Date getrxStopDate( int index, Date defaultValue )
   {
      return _rxStopDate[index] == null ? defaultValue : _rxStopDate[index];
   }
    
   /**
    * Gets the array of Date the entity usage stops fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date the entity usage stops values.
    */
   public final Date[] getrxStopDateArray()
   {
      return _rxStopDate;
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity ID or null.
    */
   public final String getrxEntityID( int index )
   {
      return _rxEntityID[index];
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity ID or the specified default value.
    */
   public final String getrxEntityID( int index, String defaultValue )
   {
      return _rxEntityID[index] == null ? defaultValue : _rxEntityID[index];
   }
    
   /**
    * Gets the array of Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity ID values.
    */
   public final String[] getrxEntityIDArray()
   {
      return _rxEntityID;
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
      _DuplicateExists = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxAccountNum = resizeArray( _rxAccountNum, _RepeatCount );
      _EntityType = resizeArray( _EntityType, _RepeatCount );
      _EntityTypeDesc = resizeArray( _EntityTypeDesc, _RepeatCount );
      _ShrNum = resizeArray( _ShrNum, _RepeatCount );
      _TaxTypeDesc = resizeArray( _TaxTypeDesc, _RepeatCount );
      _AcctTypeDesc = resizeArray( _AcctTypeDesc, _RepeatCount );
      _AcctStatusDesc = resizeArray( _AcctStatusDesc, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _AccountBalance = resizeArray( _AccountBalance, _RepeatCount );
      _EntityTypeSeq = resizeArray( _EntityTypeSeq, _RepeatCount );
      _AcctDesignation = resizeArray( _AcctDesignation, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _AcctType = resizeArray( _AcctType, _RepeatCount );
      _AcctStatus = resizeArray( _AcctStatus, _RepeatCount );
      _CurrencyCode = resizeArray( _CurrencyCode, _RepeatCount );
      _RegistrationInfo = resizeArray( _RegistrationInfo, _RepeatCount );
      _WhereUse = resizeArray( _WhereUse, _RepeatCount );
      _WhereUseCode = resizeArray( _WhereUseCode, _RepeatCount );
      _EntityWhereUseRid = resizeArray( _EntityWhereUseRid, _RepeatCount );
      _EntityWhereUseVer = resizeArray( _EntityWhereUseVer, _RepeatCount );
      _rxEffectiveDate = resizeArray( _rxEffectiveDate, _RepeatCount );
      _rxStopDate = resizeArray( _rxStopDate, _RepeatCount );
      _rxEntityID = resizeArray( _rxEntityID, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxAccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShrNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctStatusDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountBalance[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityTypeSeq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctDesignation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrencyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegistrationInfo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WhereUse[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WhereUseCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityWhereUseRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EntityWhereUseVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxEffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _rxStopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _rxEntityID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
