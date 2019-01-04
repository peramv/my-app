
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Group Code  List view.
 * For additional view information see <A HREF="../../../../viewspecs/GroupCodeDetails.doc">GroupCodeDetails.doc</A>.
 * 
 * @author RTS Generated
 */
public class GroupCodeDetailsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Group Name member array.
    */
   private String[] _GroupName = null;
   
   /**
    * Shareholder Group Code member array.
    */
   private String[] _rxGroupCode = null;
   
   /**
    * Purchase Stop Flag member array.
    */
   private Boolean[] _StopPurchase = null;
   
   /**
    * Redemption Stop Flag member array.
    */
   private Boolean[] _StopRed = null;
   
   /**
    * Group Type member array.
    */
   private String[] _GroupType = null;
   
   /**
    * Account Level Confirmation Override member array.
    */
   private Boolean[] _AccConfOverride = null;
   
   /**
    * Transfer In Stop Flag member array.
    */
   private Boolean[] _StopXferIn = null;
   
   /**
    * Transfer Out Stop Flag member array.
    */
   private Boolean[] _StopXferOut = null;
   
   /**
    * AMS Code Valid member array.
    */
   private Boolean[] _AMS = null;
   
   /**
    * Agency Code member array.
    */
   private String[] _BrokerCode = null;
   
   /**
    * Branch Code member array.
    */
   private String[] _BranchCode = null;
   
   /**
    * Sales Rep Code member array.
    */
   private String[] _SalesRepCode = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Tax Type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Trustee Fee Charge Level member array.
    */
   private String[] _FeeChrLevel = null;
   
   /**
    * Setup Fee member array.
    */
   private String[] _SetupFee = null;
   
   /**
    * Group Contribution Limit member array.
    */
   private String[] _GrpContribLimit = null;
   
   /**
    * SWP Minimum Balance member array.
    */
   private String[] _SWPMinBal = null;
   
   /**
    * Locked In Code member array.
    */
   private String[] _LockedInCode = null;
   
   /**
    * Suppress Confirm member array.
    */
   private Boolean[] _SuppConfirm = null;
   
   /**
    * Flag indicates whether the shareholder group has at least one contract with GMWB feature member array.
    */
   private Boolean[] _hasGWOContract = null;
   

   /**
    * Constructs the GroupCodeDetailsView object.
    * 
    */
   public GroupCodeDetailsView()
   {
      super ( new GroupCodeDetailsRequest() );
   }

   /**
    * Constructs the GroupCodeDetailsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public GroupCodeDetailsView( String hostEncoding )
   {
      super ( new GroupCodeDetailsRequest( hostEncoding ) );
   }

   /**
    * Gets the GroupCodeDetailsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The GroupCodeDetailsRequest object.
    */
   public final GroupCodeDetailsRequest getRequest()
   {
      return (GroupCodeDetailsRequest)getIFastRequest();
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
    * Gets the Group Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Group Name or null.
    */
   public final String getGroupName( int index )
   {
      return _GroupName[index];
   }
    
   /**
    * Gets the Group Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Name or the specified default value.
    */
   public final String getGroupName( int index, String defaultValue )
   {
      return _GroupName[index] == null ? defaultValue : _GroupName[index];
   }
    
   /**
    * Gets the array of Group Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Group Name values.
    */
   public final String[] getGroupNameArray()
   {
      return _GroupName;
   }
    
   /**
    * Gets the Shareholder Group Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Group Code or null.
    */
   public final String getrxGroupCode( int index )
   {
      return _rxGroupCode[index];
   }
    
   /**
    * Gets the Shareholder Group Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Group Code or the specified default value.
    */
   public final String getrxGroupCode( int index, String defaultValue )
   {
      return _rxGroupCode[index] == null ? defaultValue : _rxGroupCode[index];
   }
    
   /**
    * Gets the array of Shareholder Group Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Group Code values.
    */
   public final String[] getrxGroupCodeArray()
   {
      return _rxGroupCode;
   }
    
   /**
    * Gets the Purchase Stop Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Purchase Stop Flag or null.
    */
   public final Boolean getStopPurchase( int index )
   {
      return _StopPurchase[index];
   }
    
   /**
    * Gets the Purchase Stop Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Purchase Stop Flag or the specified default value.
    */
   public final boolean getStopPurchase( int index, boolean defaultValue )
   {
      return _StopPurchase[index] == null ? defaultValue : _StopPurchase[index].booleanValue();
   }
    
   /**
    * Gets the array of Purchase Stop Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Purchase Stop Flag values.
    */
   public final Boolean[] getStopPurchaseArray()
   {
      return _StopPurchase;
   }
    
   /**
    * Gets the Redemption Stop Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Stop Flag or null.
    */
   public final Boolean getStopRed( int index )
   {
      return _StopRed[index];
   }
    
   /**
    * Gets the Redemption Stop Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Stop Flag or the specified default value.
    */
   public final boolean getStopRed( int index, boolean defaultValue )
   {
      return _StopRed[index] == null ? defaultValue : _StopRed[index].booleanValue();
   }
    
   /**
    * Gets the array of Redemption Stop Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Stop Flag values.
    */
   public final Boolean[] getStopRedArray()
   {
      return _StopRed;
   }
    
   /**
    * Gets the Group Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Group Type or null.
    */
   public final String getGroupType( int index )
   {
      return _GroupType[index];
   }
    
   /**
    * Gets the Group Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Type or the specified default value.
    */
   public final String getGroupType( int index, String defaultValue )
   {
      return _GroupType[index] == null ? defaultValue : _GroupType[index];
   }
    
   /**
    * Gets the array of Group Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Group Type values.
    */
   public final String[] getGroupTypeArray()
   {
      return _GroupType;
   }
    
   /**
    * Gets the Account Level Confirmation Override field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Level Confirmation Override or null.
    */
   public final Boolean getAccConfOverride( int index )
   {
      return _AccConfOverride[index];
   }
    
   /**
    * Gets the Account Level Confirmation Override field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Level Confirmation Override or the specified default value.
    */
   public final boolean getAccConfOverride( int index, boolean defaultValue )
   {
      return _AccConfOverride[index] == null ? defaultValue : _AccConfOverride[index].booleanValue();
   }
    
   /**
    * Gets the array of Account Level Confirmation Override fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Level Confirmation Override values.
    */
   public final Boolean[] getAccConfOverrideArray()
   {
      return _AccConfOverride;
   }
    
   /**
    * Gets the Transfer In Stop Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer In Stop Flag or null.
    */
   public final Boolean getStopXferIn( int index )
   {
      return _StopXferIn[index];
   }
    
   /**
    * Gets the Transfer In Stop Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer In Stop Flag or the specified default value.
    */
   public final boolean getStopXferIn( int index, boolean defaultValue )
   {
      return _StopXferIn[index] == null ? defaultValue : _StopXferIn[index].booleanValue();
   }
    
   /**
    * Gets the array of Transfer In Stop Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer In Stop Flag values.
    */
   public final Boolean[] getStopXferInArray()
   {
      return _StopXferIn;
   }
    
   /**
    * Gets the Transfer Out Stop Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Out Stop Flag or null.
    */
   public final Boolean getStopXferOut( int index )
   {
      return _StopXferOut[index];
   }
    
   /**
    * Gets the Transfer Out Stop Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Out Stop Flag or the specified default value.
    */
   public final boolean getStopXferOut( int index, boolean defaultValue )
   {
      return _StopXferOut[index] == null ? defaultValue : _StopXferOut[index].booleanValue();
   }
    
   /**
    * Gets the array of Transfer Out Stop Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Out Stop Flag values.
    */
   public final Boolean[] getStopXferOutArray()
   {
      return _StopXferOut;
   }
    
   /**
    * Gets the AMS Code Valid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Code Valid or null.
    */
   public final Boolean getAMS( int index )
   {
      return _AMS[index];
   }
    
   /**
    * Gets the AMS Code Valid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Code Valid or the specified default value.
    */
   public final boolean getAMS( int index, boolean defaultValue )
   {
      return _AMS[index] == null ? defaultValue : _AMS[index].booleanValue();
   }
    
   /**
    * Gets the array of AMS Code Valid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Code Valid values.
    */
   public final Boolean[] getAMSArray()
   {
      return _AMS;
   }
    
   /**
    * Gets the Agency Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Agency Code or null.
    */
   public final String getBrokerCode( int index )
   {
      return _BrokerCode[index];
   }
    
   /**
    * Gets the Agency Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Agency Code or the specified default value.
    */
   public final String getBrokerCode( int index, String defaultValue )
   {
      return _BrokerCode[index] == null ? defaultValue : _BrokerCode[index];
   }
    
   /**
    * Gets the array of Agency Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Agency Code values.
    */
   public final String[] getBrokerCodeArray()
   {
      return _BrokerCode;
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Code or null.
    */
   public final String getBranchCode( int index )
   {
      return _BranchCode[index];
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Code or the specified default value.
    */
   public final String getBranchCode( int index, String defaultValue )
   {
      return _BranchCode[index] == null ? defaultValue : _BranchCode[index];
   }
    
   /**
    * Gets the array of Branch Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Code values.
    */
   public final String[] getBranchCodeArray()
   {
      return _BranchCode;
   }
    
   /**
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Code or null.
    */
   public final String getSalesRepCode( int index )
   {
      return _SalesRepCode[index];
   }
    
   /**
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Code or the specified default value.
    */
   public final String getSalesRepCode( int index, String defaultValue )
   {
      return _SalesRepCode[index] == null ? defaultValue : _SalesRepCode[index];
   }
    
   /**
    * Gets the array of Sales Rep Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Code values.
    */
   public final String[] getSalesRepCodeArray()
   {
      return _SalesRepCode;
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
    * Gets the Trustee Fee Charge Level field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trustee Fee Charge Level or null.
    */
   public final String getFeeChrLevel( int index )
   {
      return _FeeChrLevel[index];
   }
    
   /**
    * Gets the Trustee Fee Charge Level field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trustee Fee Charge Level or the specified default value.
    */
   public final String getFeeChrLevel( int index, String defaultValue )
   {
      return _FeeChrLevel[index] == null ? defaultValue : _FeeChrLevel[index];
   }
    
   /**
    * Gets the array of Trustee Fee Charge Level fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trustee Fee Charge Level values.
    */
   public final String[] getFeeChrLevelArray()
   {
      return _FeeChrLevel;
   }
    
   /**
    * Gets the Setup Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Setup Fee or null.
    */
   public final String getSetupFee( int index )
   {
      return _SetupFee[index];
   }
    
   /**
    * Gets the Setup Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Setup Fee or the specified default value.
    */
   public final String getSetupFee( int index, String defaultValue )
   {
      return _SetupFee[index] == null ? defaultValue : _SetupFee[index];
   }
    
   /**
    * Gets the array of Setup Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Setup Fee values.
    */
   public final String[] getSetupFeeArray()
   {
      return _SetupFee;
   }
    
   /**
    * Gets the Group Contribution Limit field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Group Contribution Limit or null.
    */
   public final String getGrpContribLimit( int index )
   {
      return _GrpContribLimit[index];
   }
    
   /**
    * Gets the Group Contribution Limit field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Contribution Limit or the specified default value.
    */
   public final String getGrpContribLimit( int index, String defaultValue )
   {
      return _GrpContribLimit[index] == null ? defaultValue : _GrpContribLimit[index];
   }
    
   /**
    * Gets the array of Group Contribution Limit fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Group Contribution Limit values.
    */
   public final String[] getGrpContribLimitArray()
   {
      return _GrpContribLimit;
   }
    
   /**
    * Gets the SWP Minimum Balance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SWP Minimum Balance or null.
    */
   public final String getSWPMinBal( int index )
   {
      return _SWPMinBal[index];
   }
    
   /**
    * Gets the SWP Minimum Balance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SWP Minimum Balance or the specified default value.
    */
   public final String getSWPMinBal( int index, String defaultValue )
   {
      return _SWPMinBal[index] == null ? defaultValue : _SWPMinBal[index];
   }
    
   /**
    * Gets the array of SWP Minimum Balance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SWP Minimum Balance values.
    */
   public final String[] getSWPMinBalArray()
   {
      return _SWPMinBal;
   }
    
   /**
    * Gets the Locked In Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Locked In Code or null.
    */
   public final String getLockedInCode( int index )
   {
      return _LockedInCode[index];
   }
    
   /**
    * Gets the Locked In Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Locked In Code or the specified default value.
    */
   public final String getLockedInCode( int index, String defaultValue )
   {
      return _LockedInCode[index] == null ? defaultValue : _LockedInCode[index];
   }
    
   /**
    * Gets the array of Locked In Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Locked In Code values.
    */
   public final String[] getLockedInCodeArray()
   {
      return _LockedInCode;
   }
    
   /**
    * Gets the Suppress Confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Suppress Confirm or null.
    */
   public final Boolean getSuppConfirm( int index )
   {
      return _SuppConfirm[index];
   }
    
   /**
    * Gets the Suppress Confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suppress Confirm or the specified default value.
    */
   public final boolean getSuppConfirm( int index, boolean defaultValue )
   {
      return _SuppConfirm[index] == null ? defaultValue : _SuppConfirm[index].booleanValue();
   }
    
   /**
    * Gets the array of Suppress Confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Suppress Confirm values.
    */
   public final Boolean[] getSuppConfirmArray()
   {
      return _SuppConfirm;
   }
    
   /**
    * Gets the Flag indicates whether the shareholder group has at least one contract with GMWB feature field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates whether the shareholder group has at least one contract with GMWB feature or null.
    */
   public final Boolean gethasGWOContract( int index )
   {
      return _hasGWOContract[index];
   }
    
   /**
    * Gets the Flag indicates whether the shareholder group has at least one contract with GMWB feature field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates whether the shareholder group has at least one contract with GMWB feature or the specified default value.
    */
   public final boolean gethasGWOContract( int index, boolean defaultValue )
   {
      return _hasGWOContract[index] == null ? defaultValue : _hasGWOContract[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates whether the shareholder group has at least one contract with GMWB feature fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates whether the shareholder group has at least one contract with GMWB feature values.
    */
   public final Boolean[] gethasGWOContractArray()
   {
      return _hasGWOContract;
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
      
      _GroupName = resizeArray( _GroupName, _RepeatCount );
      _rxGroupCode = resizeArray( _rxGroupCode, _RepeatCount );
      _StopPurchase = resizeArray( _StopPurchase, _RepeatCount );
      _StopRed = resizeArray( _StopRed, _RepeatCount );
      _GroupType = resizeArray( _GroupType, _RepeatCount );
      _AccConfOverride = resizeArray( _AccConfOverride, _RepeatCount );
      _StopXferIn = resizeArray( _StopXferIn, _RepeatCount );
      _StopXferOut = resizeArray( _StopXferOut, _RepeatCount );
      _AMS = resizeArray( _AMS, _RepeatCount );
      _BrokerCode = resizeArray( _BrokerCode, _RepeatCount );
      _BranchCode = resizeArray( _BranchCode, _RepeatCount );
      _SalesRepCode = resizeArray( _SalesRepCode, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _FeeChrLevel = resizeArray( _FeeChrLevel, _RepeatCount );
      _SetupFee = resizeArray( _SetupFee, _RepeatCount );
      _GrpContribLimit = resizeArray( _GrpContribLimit, _RepeatCount );
      _SWPMinBal = resizeArray( _SWPMinBal, _RepeatCount );
      _LockedInCode = resizeArray( _LockedInCode, _RepeatCount );
      _SuppConfirm = resizeArray( _SuppConfirm, _RepeatCount );
      _hasGWOContract = resizeArray( _hasGWOContract, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _GroupName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxGroupCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopPurchase[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopRed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GroupType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccConfOverride[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopXferIn[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopXferOut[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AMS[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SalesRepCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeChrLevel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SetupFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrpContribLimit[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SWPMinBal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LockedInCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SuppConfirm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _hasGWOContract[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
