
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * FUNDcom Account Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FUNDComAcctInq.doc">FUNDComAcctInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FUNDComAcctInqView extends IFastView implements Serializable
{

   /**
    * Total Number of Records available member variable.
    */
   private Integer _TotalRecords = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Account Number member array.
    */
   private String[] _rxAccountNum = null;
   
   /**
    * Social Insurance Number member array.
    */
   private String[] _rxSIN = null;
   
   /**
    * Last Name member array.
    */
   private String[] _rxLastName = null;
   
   /**
    * First Name member array.
    */
   private String[] _rxFirstName = null;
   
   /**
    * Account Type member array.
    */
   private String[] _AcctType = null;
   
   /**
    * Account Designation member array.
    */
   private String[] _AcctDes = null;
   
   /**
    * Account Status member array.
    */
   private String[] _AcctStatus = null;
   
   /**
    * Alt Account Number member array.
    */
   private String[] _rxAltAccount = null;
   
   /**
    * Broker Code member array.
    */
   private String[] _rxBrokerCode = null;
   
   /**
    * Sales Rep Code member array.
    */
   private String[] _rxSalesRepCode = null;
   
   /**
    * In Trust or Joint member array.
    */
   private Boolean[] _rxInTrustJoint = null;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * In Trust Joint Name member array.
    */
   private String[] _InTrustJointName = null;
   
   /**
    * Intermediary Code member array.
    */
   private String[] _rxIntermCode = null;
   
   /**
    * Intermediary Account member array.
    */
   private String[] _rxInterAcct = null;
   
   /**
    * Salutation member array.
    */
   private String[] _Salutation = null;
   
   /**
    * Start Index for Related Entity member array.
    */
   private Integer[] _RelEntStartIdx = null;
   
   /**
    * End Index for Related Entity member array.
    */
   private Integer[] _RelEntEndIdx = null;
   
   private int _RelEntCount = 0;
   
   /**
    * Entity Type of Related Entity member array.
    */
   private String[] _EntityType = null;
   
   /**
    * Entity Type Seq of Related Entity member array.
    */
   private Integer[] _EntityTypeSeq = null;
   
   /**
    * First Name of related entity member array.
    */
   private String[] _RelEntFName = null;
   
   /**
    * Last Name of related entity member array.
    */
   private String[] _RelEntLName = null;
   
   /**
    * Salutation for related entity member array.
    */
   private String[] _RelEntSalut = null;
   
   /**
    * Account of related entity member array.
    */
   private String[] _RelEntAccountNum = null;
   
   /**
    * SIN of related entity member array.
    */
   private String[] _RelEntSIN = null;
   
   /**
    * Related Entity Index member array.
    */
   private Integer[] _RelEntIdx = null;
   

   /**
    * Constructs the FUNDComAcctInqView object.
    * 
    */
   public FUNDComAcctInqView()
   {
      super ( new FUNDComAcctInqRequest() );
   }

   /**
    * Constructs the FUNDComAcctInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FUNDComAcctInqView( String hostEncoding )
   {
      super ( new FUNDComAcctInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FUNDComAcctInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FUNDComAcctInqRequest object.
    */
   public final FUNDComAcctInqRequest getRequest()
   {
      return (FUNDComAcctInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Total Number of Records available field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Number of Records available or null.
    */
   public final Integer getTotalRecords()
   {
      return _TotalRecords;
   }
	
   /**
    * Gets the Total Number of Records available field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Number of Records available or the specified default value.
    */
   public final int getTotalRecords( int defaultValue )
   {
      return _TotalRecords == null ? defaultValue : _TotalRecords.intValue();
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
    * Gets the Social Insurance Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Social Insurance Number or null.
    */
   public final String getrxSIN( int index )
   {
      return _rxSIN[index];
   }
    
   /**
    * Gets the Social Insurance Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Social Insurance Number or the specified default value.
    */
   public final String getrxSIN( int index, String defaultValue )
   {
      return _rxSIN[index] == null ? defaultValue : _rxSIN[index];
   }
    
   /**
    * Gets the array of Social Insurance Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Social Insurance Number values.
    */
   public final String[] getrxSINArray()
   {
      return _rxSIN;
   }
    
   /**
    * Gets the Last Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Name or null.
    */
   public final String getrxLastName( int index )
   {
      return _rxLastName[index];
   }
    
   /**
    * Gets the Last Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Name or the specified default value.
    */
   public final String getrxLastName( int index, String defaultValue )
   {
      return _rxLastName[index] == null ? defaultValue : _rxLastName[index];
   }
    
   /**
    * Gets the array of Last Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Name values.
    */
   public final String[] getrxLastNameArray()
   {
      return _rxLastName;
   }
    
   /**
    * Gets the First Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the First Name or null.
    */
   public final String getrxFirstName( int index )
   {
      return _rxFirstName[index];
   }
    
   /**
    * Gets the First Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the First Name or the specified default value.
    */
   public final String getrxFirstName( int index, String defaultValue )
   {
      return _rxFirstName[index] == null ? defaultValue : _rxFirstName[index];
   }
    
   /**
    * Gets the array of First Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of First Name values.
    */
   public final String[] getrxFirstNameArray()
   {
      return _rxFirstName;
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
   public final String getAcctDes( int index )
   {
      return _AcctDes[index];
   }
    
   /**
    * Gets the Account Designation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Designation or the specified default value.
    */
   public final String getAcctDes( int index, String defaultValue )
   {
      return _AcctDes[index] == null ? defaultValue : _AcctDes[index];
   }
    
   /**
    * Gets the array of Account Designation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Designation values.
    */
   public final String[] getAcctDesArray()
   {
      return _AcctDes;
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
    * Gets the Alt Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Alt Account Number or null.
    */
   public final String getrxAltAccount( int index )
   {
      return _rxAltAccount[index];
   }
    
   /**
    * Gets the Alt Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Alt Account Number or the specified default value.
    */
   public final String getrxAltAccount( int index, String defaultValue )
   {
      return _rxAltAccount[index] == null ? defaultValue : _rxAltAccount[index];
   }
    
   /**
    * Gets the array of Alt Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Alt Account Number values.
    */
   public final String[] getrxAltAccountArray()
   {
      return _rxAltAccount;
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Code or null.
    */
   public final String getrxBrokerCode( int index )
   {
      return _rxBrokerCode[index];
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Code or the specified default value.
    */
   public final String getrxBrokerCode( int index, String defaultValue )
   {
      return _rxBrokerCode[index] == null ? defaultValue : _rxBrokerCode[index];
   }
    
   /**
    * Gets the array of Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Code values.
    */
   public final String[] getrxBrokerCodeArray()
   {
      return _rxBrokerCode;
   }
    
   /**
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Code or null.
    */
   public final String getrxSalesRepCode( int index )
   {
      return _rxSalesRepCode[index];
   }
    
   /**
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Code or the specified default value.
    */
   public final String getrxSalesRepCode( int index, String defaultValue )
   {
      return _rxSalesRepCode[index] == null ? defaultValue : _rxSalesRepCode[index];
   }
    
   /**
    * Gets the array of Sales Rep Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Code values.
    */
   public final String[] getrxSalesRepCodeArray()
   {
      return _rxSalesRepCode;
   }
    
   /**
    * Gets the In Trust or Joint field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the In Trust or Joint or null.
    */
   public final Boolean getrxInTrustJoint( int index )
   {
      return _rxInTrustJoint[index];
   }
    
   /**
    * Gets the In Trust or Joint field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the In Trust or Joint or the specified default value.
    */
   public final boolean getrxInTrustJoint( int index, boolean defaultValue )
   {
      return _rxInTrustJoint[index] == null ? defaultValue : _rxInTrustJoint[index].booleanValue();
   }
    
   /**
    * Gets the array of In Trust or Joint fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of In Trust or Joint values.
    */
   public final Boolean[] getrxInTrustJointArray()
   {
      return _rxInTrustJoint;
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
    * Gets the In Trust Joint Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the In Trust Joint Name or null.
    */
   public final String getInTrustJointName( int index )
   {
      return _InTrustJointName[index];
   }
    
   /**
    * Gets the In Trust Joint Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the In Trust Joint Name or the specified default value.
    */
   public final String getInTrustJointName( int index, String defaultValue )
   {
      return _InTrustJointName[index] == null ? defaultValue : _InTrustJointName[index];
   }
    
   /**
    * Gets the array of In Trust Joint Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of In Trust Joint Name values.
    */
   public final String[] getInTrustJointNameArray()
   {
      return _InTrustJointName;
   }
    
   /**
    * Gets the Intermediary Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Intermediary Code or null.
    */
   public final String getrxIntermCode( int index )
   {
      return _rxIntermCode[index];
   }
    
   /**
    * Gets the Intermediary Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Intermediary Code or the specified default value.
    */
   public final String getrxIntermCode( int index, String defaultValue )
   {
      return _rxIntermCode[index] == null ? defaultValue : _rxIntermCode[index];
   }
    
   /**
    * Gets the array of Intermediary Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Intermediary Code values.
    */
   public final String[] getrxIntermCodeArray()
   {
      return _rxIntermCode;
   }
    
   /**
    * Gets the Intermediary Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Intermediary Account or null.
    */
   public final String getrxInterAcct( int index )
   {
      return _rxInterAcct[index];
   }
    
   /**
    * Gets the Intermediary Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Intermediary Account or the specified default value.
    */
   public final String getrxInterAcct( int index, String defaultValue )
   {
      return _rxInterAcct[index] == null ? defaultValue : _rxInterAcct[index];
   }
    
   /**
    * Gets the array of Intermediary Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Intermediary Account values.
    */
   public final String[] getrxInterAcctArray()
   {
      return _rxInterAcct;
   }
    
   /**
    * Gets the Salutation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Salutation or null.
    */
   public final String getSalutation( int index )
   {
      return _Salutation[index];
   }
    
   /**
    * Gets the Salutation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Salutation or the specified default value.
    */
   public final String getSalutation( int index, String defaultValue )
   {
      return _Salutation[index] == null ? defaultValue : _Salutation[index];
   }
    
   /**
    * Gets the array of Salutation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Salutation values.
    */
   public final String[] getSalutationArray()
   {
      return _Salutation;
   }
    
   /**
    * Gets the Start Index for Related Entity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Start Index for Related Entity or null.
    */
   public final Integer getRelEntStartIdx( int index )
   {
      return _RelEntStartIdx[index];
   }
    
   /**
    * Gets the Start Index for Related Entity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start Index for Related Entity or the specified default value.
    */
   public final int getRelEntStartIdx( int index, int defaultValue )
   {
      return _RelEntStartIdx[index] == null ? defaultValue : _RelEntStartIdx[index].intValue();
   }
    
   /**
    * Gets the array of Start Index for Related Entity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Start Index for Related Entity values.
    */
   public final Integer[] getRelEntStartIdxArray()
   {
      return _RelEntStartIdx;
   }
    
   /**
    * Gets the End Index for Related Entity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the End Index for Related Entity or null.
    */
   public final Integer getRelEntEndIdx( int index )
   {
      return _RelEntEndIdx[index];
   }
    
   /**
    * Gets the End Index for Related Entity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the End Index for Related Entity or the specified default value.
    */
   public final int getRelEntEndIdx( int index, int defaultValue )
   {
      return _RelEntEndIdx[index] == null ? defaultValue : _RelEntEndIdx[index].intValue();
   }
    
   /**
    * Gets the array of End Index for Related Entity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of End Index for Related Entity values.
    */
   public final Integer[] getRelEntEndIdxArray()
   {
      return _RelEntEndIdx;
   }
    
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRelEntCount()
   {
      return _RelEntCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRelEntCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RelEntCount += receivedRecordCount;
   }

   /**
    * Gets the Entity Type of Related Entity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type of Related Entity or null.
    */
   public final String getEntityType( int index )
   {
      return _EntityType[index];
   }
    
   /**
    * Gets the Entity Type of Related Entity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type of Related Entity or the specified default value.
    */
   public final String getEntityType( int index, String defaultValue )
   {
      return _EntityType[index] == null ? defaultValue : _EntityType[index];
   }
    
   /**
    * Gets the array of Entity Type of Related Entity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type of Related Entity values.
    */
   public final String[] getEntityTypeArray()
   {
      return _EntityType;
   }
    
   /**
    * Gets the Entity Type Seq of Related Entity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Type Seq of Related Entity or null.
    */
   public final Integer getEntityTypeSeq( int index )
   {
      return _EntityTypeSeq[index];
   }
    
   /**
    * Gets the Entity Type Seq of Related Entity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type Seq of Related Entity or the specified default value.
    */
   public final int getEntityTypeSeq( int index, int defaultValue )
   {
      return _EntityTypeSeq[index] == null ? defaultValue : _EntityTypeSeq[index].intValue();
   }
    
   /**
    * Gets the array of Entity Type Seq of Related Entity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Type Seq of Related Entity values.
    */
   public final Integer[] getEntityTypeSeqArray()
   {
      return _EntityTypeSeq;
   }
    
   /**
    * Gets the First Name of related entity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the First Name of related entity or null.
    */
   public final String getRelEntFName( int index )
   {
      return _RelEntFName[index];
   }
    
   /**
    * Gets the First Name of related entity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the First Name of related entity or the specified default value.
    */
   public final String getRelEntFName( int index, String defaultValue )
   {
      return _RelEntFName[index] == null ? defaultValue : _RelEntFName[index];
   }
    
   /**
    * Gets the array of First Name of related entity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of First Name of related entity values.
    */
   public final String[] getRelEntFNameArray()
   {
      return _RelEntFName;
   }
    
   /**
    * Gets the Last Name of related entity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Name of related entity or null.
    */
   public final String getRelEntLName( int index )
   {
      return _RelEntLName[index];
   }
    
   /**
    * Gets the Last Name of related entity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Name of related entity or the specified default value.
    */
   public final String getRelEntLName( int index, String defaultValue )
   {
      return _RelEntLName[index] == null ? defaultValue : _RelEntLName[index];
   }
    
   /**
    * Gets the array of Last Name of related entity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Name of related entity values.
    */
   public final String[] getRelEntLNameArray()
   {
      return _RelEntLName;
   }
    
   /**
    * Gets the Salutation for related entity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Salutation for related entity or null.
    */
   public final String getRelEntSalut( int index )
   {
      return _RelEntSalut[index];
   }
    
   /**
    * Gets the Salutation for related entity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Salutation for related entity or the specified default value.
    */
   public final String getRelEntSalut( int index, String defaultValue )
   {
      return _RelEntSalut[index] == null ? defaultValue : _RelEntSalut[index];
   }
    
   /**
    * Gets the array of Salutation for related entity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Salutation for related entity values.
    */
   public final String[] getRelEntSalutArray()
   {
      return _RelEntSalut;
   }
    
   /**
    * Gets the Account of related entity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account of related entity or null.
    */
   public final String getRelEntAccountNum( int index )
   {
      return _RelEntAccountNum[index];
   }
    
   /**
    * Gets the Account of related entity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account of related entity or the specified default value.
    */
   public final String getRelEntAccountNum( int index, String defaultValue )
   {
      return _RelEntAccountNum[index] == null ? defaultValue : _RelEntAccountNum[index];
   }
    
   /**
    * Gets the array of Account of related entity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account of related entity values.
    */
   public final String[] getRelEntAccountNumArray()
   {
      return _RelEntAccountNum;
   }
    
   /**
    * Gets the SIN of related entity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SIN of related entity or null.
    */
   public final String getRelEntSIN( int index )
   {
      return _RelEntSIN[index];
   }
    
   /**
    * Gets the SIN of related entity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SIN of related entity or the specified default value.
    */
   public final String getRelEntSIN( int index, String defaultValue )
   {
      return _RelEntSIN[index] == null ? defaultValue : _RelEntSIN[index];
   }
    
   /**
    * Gets the array of SIN of related entity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SIN of related entity values.
    */
   public final String[] getRelEntSINArray()
   {
      return _RelEntSIN;
   }
    
   /**
    * Gets the Related Entity Index field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Related Entity Index or null.
    */
   public final Integer getRelEntIdx( int index )
   {
      return _RelEntIdx[index];
   }
    
   /**
    * Gets the Related Entity Index field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Related Entity Index or the specified default value.
    */
   public final int getRelEntIdx( int index, int defaultValue )
   {
      return _RelEntIdx[index] == null ? defaultValue : _RelEntIdx[index].intValue();
   }
    
   /**
    * Gets the array of Related Entity Index fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Related Entity Index values.
    */
   public final Integer[] getRelEntIdxArray()
   {
      return _RelEntIdx;
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
      _TotalRecords = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxAccountNum = resizeArray( _rxAccountNum, _RepeatCount );
      _rxSIN = resizeArray( _rxSIN, _RepeatCount );
      _rxLastName = resizeArray( _rxLastName, _RepeatCount );
      _rxFirstName = resizeArray( _rxFirstName, _RepeatCount );
      _AcctType = resizeArray( _AcctType, _RepeatCount );
      _AcctDes = resizeArray( _AcctDes, _RepeatCount );
      _AcctStatus = resizeArray( _AcctStatus, _RepeatCount );
      _rxAltAccount = resizeArray( _rxAltAccount, _RepeatCount );
      _rxBrokerCode = resizeArray( _rxBrokerCode, _RepeatCount );
      _rxSalesRepCode = resizeArray( _rxSalesRepCode, _RepeatCount );
      _rxInTrustJoint = resizeArray( _rxInTrustJoint, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _InTrustJointName = resizeArray( _InTrustJointName, _RepeatCount );
      _rxIntermCode = resizeArray( _rxIntermCode, _RepeatCount );
      _rxInterAcct = resizeArray( _rxInterAcct, _RepeatCount );
      _Salutation = resizeArray( _Salutation, _RepeatCount );
      _RelEntStartIdx = resizeArray( _RelEntStartIdx, _RepeatCount );
      _RelEntEndIdx = resizeArray( _RelEntEndIdx, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxAccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxSIN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxLastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDes[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxAltAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxSalesRepCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxInTrustJoint[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InTrustJointName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxIntermCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxInterAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Salutation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RelEntStartIdx[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RelEntEndIdx[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      
      // multi-record section
      int oldRelEntCount = _RelEntCount;
      decodeRelEntCount( responseBuffer );
      
      _EntityType = resizeArray( _EntityType, _RelEntCount );
      _EntityTypeSeq = resizeArray( _EntityTypeSeq, _RelEntCount );
      _RelEntFName = resizeArray( _RelEntFName, _RelEntCount );
      _RelEntLName = resizeArray( _RelEntLName, _RelEntCount );
      _RelEntSalut = resizeArray( _RelEntSalut, _RelEntCount );
      _RelEntAccountNum = resizeArray( _RelEntAccountNum, _RelEntCount );
      _RelEntSIN = resizeArray( _RelEntSIN, _RelEntCount );
      _RelEntIdx = resizeArray( _RelEntIdx, _RelEntCount );
        
      for (int x = oldRelEntCount ; x < _RelEntCount; x++)
      {
         _EntityType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityTypeSeq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RelEntFName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RelEntLName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RelEntSalut[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RelEntAccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RelEntSIN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RelEntIdx[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
