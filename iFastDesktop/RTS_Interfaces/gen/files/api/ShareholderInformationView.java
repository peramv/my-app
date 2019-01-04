
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Shareholder Information Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ShareholderInformation.doc">ShareholderInformation.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShareholderInformationView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Response Shareholder Number member array.
    */
   private String[] _rxShrNum = null;
   
   /**
    * Name1 member array.
    */
   private String[] _Name1 = null;
   
   /**
    * Name2 member array.
    */
   private String[] _Name2 = null;
   
   /**
    * Tax Jurisdiction Code member array.
    */
   private String[] _TaxJurisCode = null;
   
   /**
    * Tax Jurisdiction Name member array.
    */
   private String[] _TaxJurisName = null;
   
   /**
    * Residence Province Code member array.
    */
   private String[] _ResProvCode = null;
   
   /**
    * Residence Province Name member array.
    */
   private String[] _ResProvName = null;
   
   /**
    * Shareholder group code member array.
    */
   private String[] _GroupCode = null;
   
   /**
    * Shareholder group name1 member array.
    */
   private String[] _GroupName1 = null;
   
   /**
    * Used for family mailings if offered by fund company member array.
    */
   private String[] _FamilyCode = null;
   
   /**
    * Family Name member array.
    */
   private String[] _FamilyName = null;
   
   /**
    * Fund Relation Code member array.
    */
   private String[] _FundRelnCode = null;
   
   /**
    * Fund Relation Description member array.
    */
   private String[] _FundRelnDesc = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Date of Creation member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _Username = null;
   
   /**
    * Modify User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Shareholder group name2 member array.
    */
   private String[] _GroupName2 = null;
   
   /**
    * Modify Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Prim-Mstr Version Number member array.
    */
   private Integer[] _PrimMstrVer = null;
   
   /**
    * Prim-Mstr Record Id member array.
    */
   private Integer[] _PrimMstrRid = null;
   
   /**
    * Account Designation member array.
    */
   private String[] _AcctDesignation = null;
   
   /**
    * Account Designation Description member array.
    */
   private String[] _AcctDesignationDesc = null;
   
   /**
    * Consolidated EFT member array.
    */
   private Boolean[] _ConsolEFT = null;
   
   /**
    * Remarks exist member array.
    */
   private Boolean[] _Remarks = null;
   
   /**
    * Banking Instructions exist member array.
    */
   private Boolean[] _BankingInstr = null;
   
   /**
    * First Effective Date of shareholder member array.
    */
   private Date[] _FirstEffective = null;
   
   /**
    * Residency member array.
    */
   private Boolean[] _Residency = null;
   
   /**
    * Shareholer Type member array.
    */
   private String[] _ShType = null;
   
   /**
    * FamilyCode exists flag member array.
    */
   private Boolean[] _FamilyCodeExists = null;
   
   /**
    * Confidential member array.
    */
   private Boolean[] _Confidential = null;
   
   /**
    * Channel member array.
    */
   private String[] _Channel = null;
   
   /**
    * DTAexist member array.
    */
   private Boolean[] _DTAexist = null;
   
   /**
    * Shareholder - Fund Sponsor Agreement Exists member array.
    */
   private Boolean[] _ShrFndSpAgrExists = null;
   
   /**
    * Fee model Code member array.
    */
   private String[] _FeeModelCode = null;
   
   /**
    * Default Fund Broker Exists member array.
    */
   private Boolean[] _ShrFndBrkExist = null;
   

   /**
    * Constructs the ShareholderInformationView object.
    * 
    */
   public ShareholderInformationView()
   {
      super ( new ShareholderInformationRequest() );
   }

   /**
    * Constructs the ShareholderInformationView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShareholderInformationView( String hostEncoding )
   {
      super ( new ShareholderInformationRequest( hostEncoding ) );
   }

   /**
    * Gets the ShareholderInformationRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShareholderInformationRequest object.
    */
   public final ShareholderInformationRequest getRequest()
   {
      return (ShareholderInformationRequest)getIFastRequest();
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
    * Gets the Response Shareholder Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Response Shareholder Number or null.
    */
   public final String getrxShrNum( int index )
   {
      return _rxShrNum[index];
   }
    
   /**
    * Gets the Response Shareholder Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Response Shareholder Number or the specified default value.
    */
   public final String getrxShrNum( int index, String defaultValue )
   {
      return _rxShrNum[index] == null ? defaultValue : _rxShrNum[index];
   }
    
   /**
    * Gets the array of Response Shareholder Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Response Shareholder Number values.
    */
   public final String[] getrxShrNumArray()
   {
      return _rxShrNum;
   }
    
   /**
    * Gets the Name1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Name1 or null.
    */
   public final String getName1( int index )
   {
      return _Name1[index];
   }
    
   /**
    * Gets the Name1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name1 or the specified default value.
    */
   public final String getName1( int index, String defaultValue )
   {
      return _Name1[index] == null ? defaultValue : _Name1[index];
   }
    
   /**
    * Gets the array of Name1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Name1 values.
    */
   public final String[] getName1Array()
   {
      return _Name1;
   }
    
   /**
    * Gets the Name2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Name2 or null.
    */
   public final String getName2( int index )
   {
      return _Name2[index];
   }
    
   /**
    * Gets the Name2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name2 or the specified default value.
    */
   public final String getName2( int index, String defaultValue )
   {
      return _Name2[index] == null ? defaultValue : _Name2[index];
   }
    
   /**
    * Gets the array of Name2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Name2 values.
    */
   public final String[] getName2Array()
   {
      return _Name2;
   }
    
   /**
    * Gets the Tax Jurisdiction Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Jurisdiction Code or null.
    */
   public final String getTaxJurisCode( int index )
   {
      return _TaxJurisCode[index];
   }
    
   /**
    * Gets the Tax Jurisdiction Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Jurisdiction Code or the specified default value.
    */
   public final String getTaxJurisCode( int index, String defaultValue )
   {
      return _TaxJurisCode[index] == null ? defaultValue : _TaxJurisCode[index];
   }
    
   /**
    * Gets the array of Tax Jurisdiction Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Jurisdiction Code values.
    */
   public final String[] getTaxJurisCodeArray()
   {
      return _TaxJurisCode;
   }
    
   /**
    * Gets the Tax Jurisdiction Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Jurisdiction Name or null.
    */
   public final String getTaxJurisName( int index )
   {
      return _TaxJurisName[index];
   }
    
   /**
    * Gets the Tax Jurisdiction Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Jurisdiction Name or the specified default value.
    */
   public final String getTaxJurisName( int index, String defaultValue )
   {
      return _TaxJurisName[index] == null ? defaultValue : _TaxJurisName[index];
   }
    
   /**
    * Gets the array of Tax Jurisdiction Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Jurisdiction Name values.
    */
   public final String[] getTaxJurisNameArray()
   {
      return _TaxJurisName;
   }
    
   /**
    * Gets the Residence Province Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Residence Province Code or null.
    */
   public final String getResProvCode( int index )
   {
      return _ResProvCode[index];
   }
    
   /**
    * Gets the Residence Province Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Residence Province Code or the specified default value.
    */
   public final String getResProvCode( int index, String defaultValue )
   {
      return _ResProvCode[index] == null ? defaultValue : _ResProvCode[index];
   }
    
   /**
    * Gets the array of Residence Province Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Residence Province Code values.
    */
   public final String[] getResProvCodeArray()
   {
      return _ResProvCode;
   }
    
   /**
    * Gets the Residence Province Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Residence Province Name or null.
    */
   public final String getResProvName( int index )
   {
      return _ResProvName[index];
   }
    
   /**
    * Gets the Residence Province Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Residence Province Name or the specified default value.
    */
   public final String getResProvName( int index, String defaultValue )
   {
      return _ResProvName[index] == null ? defaultValue : _ResProvName[index];
   }
    
   /**
    * Gets the array of Residence Province Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Residence Province Name values.
    */
   public final String[] getResProvNameArray()
   {
      return _ResProvName;
   }
    
   /**
    * Gets the Shareholder group code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder group code or null.
    */
   public final String getGroupCode( int index )
   {
      return _GroupCode[index];
   }
    
   /**
    * Gets the Shareholder group code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder group code or the specified default value.
    */
   public final String getGroupCode( int index, String defaultValue )
   {
      return _GroupCode[index] == null ? defaultValue : _GroupCode[index];
   }
    
   /**
    * Gets the array of Shareholder group code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder group code values.
    */
   public final String[] getGroupCodeArray()
   {
      return _GroupCode;
   }
    
   /**
    * Gets the Shareholder group name1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder group name1 or null.
    */
   public final String getGroupName1( int index )
   {
      return _GroupName1[index];
   }
    
   /**
    * Gets the Shareholder group name1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder group name1 or the specified default value.
    */
   public final String getGroupName1( int index, String defaultValue )
   {
      return _GroupName1[index] == null ? defaultValue : _GroupName1[index];
   }
    
   /**
    * Gets the array of Shareholder group name1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder group name1 values.
    */
   public final String[] getGroupName1Array()
   {
      return _GroupName1;
   }
    
   /**
    * Gets the Used for family mailings if offered by fund company field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Used for family mailings if offered by fund company or null.
    */
   public final String getFamilyCode( int index )
   {
      return _FamilyCode[index];
   }
    
   /**
    * Gets the Used for family mailings if offered by fund company field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Used for family mailings if offered by fund company or the specified default value.
    */
   public final String getFamilyCode( int index, String defaultValue )
   {
      return _FamilyCode[index] == null ? defaultValue : _FamilyCode[index];
   }
    
   /**
    * Gets the array of Used for family mailings if offered by fund company fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Used for family mailings if offered by fund company values.
    */
   public final String[] getFamilyCodeArray()
   {
      return _FamilyCode;
   }
    
   /**
    * Gets the Family Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Family Name or null.
    */
   public final String getFamilyName( int index )
   {
      return _FamilyName[index];
   }
    
   /**
    * Gets the Family Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Family Name or the specified default value.
    */
   public final String getFamilyName( int index, String defaultValue )
   {
      return _FamilyName[index] == null ? defaultValue : _FamilyName[index];
   }
    
   /**
    * Gets the array of Family Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Family Name values.
    */
   public final String[] getFamilyNameArray()
   {
      return _FamilyName;
   }
    
   /**
    * Gets the Fund Relation Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Relation Code or null.
    */
   public final String getFundRelnCode( int index )
   {
      return _FundRelnCode[index];
   }
    
   /**
    * Gets the Fund Relation Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Relation Code or the specified default value.
    */
   public final String getFundRelnCode( int index, String defaultValue )
   {
      return _FundRelnCode[index] == null ? defaultValue : _FundRelnCode[index];
   }
    
   /**
    * Gets the array of Fund Relation Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Relation Code values.
    */
   public final String[] getFundRelnCodeArray()
   {
      return _FundRelnCode;
   }
    
   /**
    * Gets the Fund Relation Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Relation Description or null.
    */
   public final String getFundRelnDesc( int index )
   {
      return _FundRelnDesc[index];
   }
    
   /**
    * Gets the Fund Relation Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Relation Description or the specified default value.
    */
   public final String getFundRelnDesc( int index, String defaultValue )
   {
      return _FundRelnDesc[index] == null ? defaultValue : _FundRelnDesc[index];
   }
    
   /**
    * Gets the array of Fund Relation Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Relation Description values.
    */
   public final String[] getFundRelnDescArray()
   {
      return _FundRelnDesc;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Date of Creation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date of Creation or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date of Creation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Creation or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date of Creation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date of Creation values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Name or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of User Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Name values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Modify User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modify User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modify User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Shareholder group name2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder group name2 or null.
    */
   public final String getGroupName2( int index )
   {
      return _GroupName2[index];
   }
    
   /**
    * Gets the Shareholder group name2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder group name2 or the specified default value.
    */
   public final String getGroupName2( int index, String defaultValue )
   {
      return _GroupName2[index] == null ? defaultValue : _GroupName2[index];
   }
    
   /**
    * Gets the array of Shareholder group name2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder group name2 values.
    */
   public final String[] getGroupName2Array()
   {
      return _GroupName2;
   }
    
   /**
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modify Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Prim-Mstr Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prim-Mstr Version Number or null.
    */
   public final Integer getPrimMstrVer( int index )
   {
      return _PrimMstrVer[index];
   }
    
   /**
    * Gets the Prim-Mstr Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prim-Mstr Version Number or the specified default value.
    */
   public final int getPrimMstrVer( int index, int defaultValue )
   {
      return _PrimMstrVer[index] == null ? defaultValue : _PrimMstrVer[index].intValue();
   }
    
   /**
    * Gets the array of Prim-Mstr Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prim-Mstr Version Number values.
    */
   public final Integer[] getPrimMstrVerArray()
   {
      return _PrimMstrVer;
   }
    
   /**
    * Gets the Prim-Mstr Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Prim-Mstr Record Id or null.
    */
   public final Integer getPrimMstrRid( int index )
   {
      return _PrimMstrRid[index];
   }
    
   /**
    * Gets the Prim-Mstr Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prim-Mstr Record Id or the specified default value.
    */
   public final int getPrimMstrRid( int index, int defaultValue )
   {
      return _PrimMstrRid[index] == null ? defaultValue : _PrimMstrRid[index].intValue();
   }
    
   /**
    * Gets the array of Prim-Mstr Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Prim-Mstr Record Id values.
    */
   public final Integer[] getPrimMstrRidArray()
   {
      return _PrimMstrRid;
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
    * Gets the Account Designation Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Designation Description or null.
    */
   public final String getAcctDesignationDesc( int index )
   {
      return _AcctDesignationDesc[index];
   }
    
   /**
    * Gets the Account Designation Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Designation Description or the specified default value.
    */
   public final String getAcctDesignationDesc( int index, String defaultValue )
   {
      return _AcctDesignationDesc[index] == null ? defaultValue : _AcctDesignationDesc[index];
   }
    
   /**
    * Gets the array of Account Designation Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Designation Description values.
    */
   public final String[] getAcctDesignationDescArray()
   {
      return _AcctDesignationDesc;
   }
    
   /**
    * Gets the Consolidated EFT field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Consolidated EFT or null.
    */
   public final Boolean getConsolEFT( int index )
   {
      return _ConsolEFT[index];
   }
    
   /**
    * Gets the Consolidated EFT field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Consolidated EFT or the specified default value.
    */
   public final boolean getConsolEFT( int index, boolean defaultValue )
   {
      return _ConsolEFT[index] == null ? defaultValue : _ConsolEFT[index].booleanValue();
   }
    
   /**
    * Gets the array of Consolidated EFT fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Consolidated EFT values.
    */
   public final Boolean[] getConsolEFTArray()
   {
      return _ConsolEFT;
   }
    
   /**
    * Gets the Remarks exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks exist or null.
    */
   public final Boolean getRemarks( int index )
   {
      return _Remarks[index];
   }
    
   /**
    * Gets the Remarks exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks exist or the specified default value.
    */
   public final boolean getRemarks( int index, boolean defaultValue )
   {
      return _Remarks[index] == null ? defaultValue : _Remarks[index].booleanValue();
   }
    
   /**
    * Gets the array of Remarks exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks exist values.
    */
   public final Boolean[] getRemarksArray()
   {
      return _Remarks;
   }
    
   /**
    * Gets the Banking Instructions exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Banking Instructions exist or null.
    */
   public final Boolean getBankingInstr( int index )
   {
      return _BankingInstr[index];
   }
    
   /**
    * Gets the Banking Instructions exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Banking Instructions exist or the specified default value.
    */
   public final boolean getBankingInstr( int index, boolean defaultValue )
   {
      return _BankingInstr[index] == null ? defaultValue : _BankingInstr[index].booleanValue();
   }
    
   /**
    * Gets the array of Banking Instructions exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Banking Instructions exist values.
    */
   public final Boolean[] getBankingInstrArray()
   {
      return _BankingInstr;
   }
    
   /**
    * Gets the First Effective Date of shareholder field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the First Effective Date of shareholder or null.
    */
   public final Date getFirstEffective( int index )
   {
      return _FirstEffective[index];
   }
    
   /**
    * Gets the First Effective Date of shareholder field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the First Effective Date of shareholder or the specified default value.
    */
   public final Date getFirstEffective( int index, Date defaultValue )
   {
      return _FirstEffective[index] == null ? defaultValue : _FirstEffective[index];
   }
    
   /**
    * Gets the array of First Effective Date of shareholder fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of First Effective Date of shareholder values.
    */
   public final Date[] getFirstEffectiveArray()
   {
      return _FirstEffective;
   }
    
   /**
    * Gets the Residency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Residency or null.
    */
   public final Boolean getResidency( int index )
   {
      return _Residency[index];
   }
    
   /**
    * Gets the Residency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Residency or the specified default value.
    */
   public final boolean getResidency( int index, boolean defaultValue )
   {
      return _Residency[index] == null ? defaultValue : _Residency[index].booleanValue();
   }
    
   /**
    * Gets the array of Residency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Residency values.
    */
   public final Boolean[] getResidencyArray()
   {
      return _Residency;
   }
    
   /**
    * Gets the Shareholer Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholer Type or null.
    */
   public final String getShType( int index )
   {
      return _ShType[index];
   }
    
   /**
    * Gets the Shareholer Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholer Type or the specified default value.
    */
   public final String getShType( int index, String defaultValue )
   {
      return _ShType[index] == null ? defaultValue : _ShType[index];
   }
    
   /**
    * Gets the array of Shareholer Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholer Type values.
    */
   public final String[] getShTypeArray()
   {
      return _ShType;
   }
    
   /**
    * Gets the FamilyCode exists flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FamilyCode exists flag or null.
    */
   public final Boolean getFamilyCodeExists( int index )
   {
      return _FamilyCodeExists[index];
   }
    
   /**
    * Gets the FamilyCode exists flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FamilyCode exists flag or the specified default value.
    */
   public final boolean getFamilyCodeExists( int index, boolean defaultValue )
   {
      return _FamilyCodeExists[index] == null ? defaultValue : _FamilyCodeExists[index].booleanValue();
   }
    
   /**
    * Gets the array of FamilyCode exists flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FamilyCode exists flag values.
    */
   public final Boolean[] getFamilyCodeExistsArray()
   {
      return _FamilyCodeExists;
   }
    
   /**
    * Gets the Confidential field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Confidential or null.
    */
   public final Boolean getConfidential( int index )
   {
      return _Confidential[index];
   }
    
   /**
    * Gets the Confidential field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Confidential or the specified default value.
    */
   public final boolean getConfidential( int index, boolean defaultValue )
   {
      return _Confidential[index] == null ? defaultValue : _Confidential[index].booleanValue();
   }
    
   /**
    * Gets the array of Confidential fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Confidential values.
    */
   public final Boolean[] getConfidentialArray()
   {
      return _Confidential;
   }
    
   /**
    * Gets the Channel field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Channel or null.
    */
   public final String getChannel( int index )
   {
      return _Channel[index];
   }
    
   /**
    * Gets the Channel field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Channel or the specified default value.
    */
   public final String getChannel( int index, String defaultValue )
   {
      return _Channel[index] == null ? defaultValue : _Channel[index];
   }
    
   /**
    * Gets the array of Channel fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Channel values.
    */
   public final String[] getChannelArray()
   {
      return _Channel;
   }
    
   /**
    * Gets the DTAexist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DTAexist or null.
    */
   public final Boolean getDTAexist( int index )
   {
      return _DTAexist[index];
   }
    
   /**
    * Gets the DTAexist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DTAexist or the specified default value.
    */
   public final boolean getDTAexist( int index, boolean defaultValue )
   {
      return _DTAexist[index] == null ? defaultValue : _DTAexist[index].booleanValue();
   }
    
   /**
    * Gets the array of DTAexist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DTAexist values.
    */
   public final Boolean[] getDTAexistArray()
   {
      return _DTAexist;
   }
    
   /**
    * Gets the Shareholder - Fund Sponsor Agreement Exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder - Fund Sponsor Agreement Exists or null.
    */
   public final Boolean getShrFndSpAgrExists( int index )
   {
      return _ShrFndSpAgrExists[index];
   }
    
   /**
    * Gets the Shareholder - Fund Sponsor Agreement Exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder - Fund Sponsor Agreement Exists or the specified default value.
    */
   public final boolean getShrFndSpAgrExists( int index, boolean defaultValue )
   {
      return _ShrFndSpAgrExists[index] == null ? defaultValue : _ShrFndSpAgrExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Shareholder - Fund Sponsor Agreement Exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder - Fund Sponsor Agreement Exists values.
    */
   public final Boolean[] getShrFndSpAgrExistsArray()
   {
      return _ShrFndSpAgrExists;
   }
    
   /**
    * Gets the Fee model Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee model Code or null.
    */
   public final String getFeeModelCode( int index )
   {
      return _FeeModelCode[index];
   }
    
   /**
    * Gets the Fee model Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee model Code or the specified default value.
    */
   public final String getFeeModelCode( int index, String defaultValue )
   {
      return _FeeModelCode[index] == null ? defaultValue : _FeeModelCode[index];
   }
    
   /**
    * Gets the array of Fee model Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee model Code values.
    */
   public final String[] getFeeModelCodeArray()
   {
      return _FeeModelCode;
   }
    
   /**
    * Gets the Default Fund Broker Exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Default Fund Broker Exists or null.
    */
   public final Boolean getShrFndBrkExist( int index )
   {
      return _ShrFndBrkExist[index];
   }
    
   /**
    * Gets the Default Fund Broker Exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Fund Broker Exists or the specified default value.
    */
   public final boolean getShrFndBrkExist( int index, boolean defaultValue )
   {
      return _ShrFndBrkExist[index] == null ? defaultValue : _ShrFndBrkExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Default Fund Broker Exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Default Fund Broker Exists values.
    */
   public final Boolean[] getShrFndBrkExistArray()
   {
      return _ShrFndBrkExist;
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
      
      _rxShrNum = resizeArray( _rxShrNum, _RepeatCount );
      _Name1 = resizeArray( _Name1, _RepeatCount );
      _Name2 = resizeArray( _Name2, _RepeatCount );
      _TaxJurisCode = resizeArray( _TaxJurisCode, _RepeatCount );
      _TaxJurisName = resizeArray( _TaxJurisName, _RepeatCount );
      _ResProvCode = resizeArray( _ResProvCode, _RepeatCount );
      _ResProvName = resizeArray( _ResProvName, _RepeatCount );
      _GroupCode = resizeArray( _GroupCode, _RepeatCount );
      _GroupName1 = resizeArray( _GroupName1, _RepeatCount );
      _FamilyCode = resizeArray( _FamilyCode, _RepeatCount );
      _FamilyName = resizeArray( _FamilyName, _RepeatCount );
      _FundRelnCode = resizeArray( _FundRelnCode, _RepeatCount );
      _FundRelnDesc = resizeArray( _FundRelnDesc, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _GroupName2 = resizeArray( _GroupName2, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _PrimMstrVer = resizeArray( _PrimMstrVer, _RepeatCount );
      _PrimMstrRid = resizeArray( _PrimMstrRid, _RepeatCount );
      _AcctDesignation = resizeArray( _AcctDesignation, _RepeatCount );
      _AcctDesignationDesc = resizeArray( _AcctDesignationDesc, _RepeatCount );
      _ConsolEFT = resizeArray( _ConsolEFT, _RepeatCount );
      _Remarks = resizeArray( _Remarks, _RepeatCount );
      _BankingInstr = resizeArray( _BankingInstr, _RepeatCount );
      _FirstEffective = resizeArray( _FirstEffective, _RepeatCount );
      _Residency = resizeArray( _Residency, _RepeatCount );
      _ShType = resizeArray( _ShType, _RepeatCount );
      _FamilyCodeExists = resizeArray( _FamilyCodeExists, _RepeatCount );
      _Confidential = resizeArray( _Confidential, _RepeatCount );
      _Channel = resizeArray( _Channel, _RepeatCount );
      _DTAexist = resizeArray( _DTAexist, _RepeatCount );
      _ShrFndSpAgrExists = resizeArray( _ShrFndSpAgrExists, _RepeatCount );
      _FeeModelCode = resizeArray( _FeeModelCode, _RepeatCount );
      _ShrFndBrkExist = resizeArray( _ShrFndBrkExist, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxShrNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Name1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Name2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxJurisCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxJurisName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ResProvCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ResProvName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GroupCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GroupName1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FamilyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FamilyName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundRelnCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundRelnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GroupName2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _PrimMstrVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PrimMstrRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctDesignation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDesignationDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ConsolEFT[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Remarks[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BankingInstr[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FirstEffective[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Residency[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ShType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FamilyCodeExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Confidential[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Channel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DTAexist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ShrFndSpAgrExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeModelCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShrFndBrkExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
