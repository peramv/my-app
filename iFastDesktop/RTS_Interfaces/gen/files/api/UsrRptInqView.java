
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * GUI User Report Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/UsrRptInq.doc">UsrRptInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class UsrRptInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * ForUser Id member array.
    */
   private String[] _ForUserID = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * User Profile ID member array.
    */
   private String[] _UserProfileID = null;
   
   /**
    * User Active member array.
    */
   private Boolean[] _UserActive = null;
   
   /**
    * User Type member array.
    */
   private String[] _UserType = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Choose Password member array.
    */
   private Boolean[] _ChoosePasswd = null;
   
   /**
    * Change Password member array.
    */
   private Boolean[] _ChangePasswd = null;
   
   /**
    * Reset Password member array.
    */
   private Boolean[] _ResetPasswd = null;
   
   /**
    * Date Password Changed member array.
    */
   private Date[] _DatePasswdChanged = null;
   
   /**
    * Failed Logons member array.
    */
   private Integer[] _FailedLogons = null;
   
   /**
    * Created By member array.
    */
   private String[] _CreatedBy = null;
   
   /**
    * Created On member array.
    */
   private Date[] _CreatedOn = null;
   
   /**
    * Modified By member array.
    */
   private String[] _ModifiedBy = null;
   
   /**
    * Modified On member array.
    */
   private Date[] _ModifiedOn = null;
   
   /**
    * Broker member array.
    */
   private String[] _Broker = null;
   
   /**
    * Branch member array.
    */
   private String[] _Branch = null;
   
   /**
    * Sales Rep member array.
    */
   private String[] _SlsRep = null;
   
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = null;
   
   /**
    * EntityID member array.
    */
   private String[] _EntityID = null;
   

   /**
    * Constructs the UsrRptInqView object.
    * 
    */
   public UsrRptInqView()
   {
      super ( new UsrRptInqRequest() );
   }

   /**
    * Constructs the UsrRptInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public UsrRptInqView( String hostEncoding )
   {
      super ( new UsrRptInqRequest( hostEncoding ) );
   }

   /**
    * Gets the UsrRptInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The UsrRptInqRequest object.
    */
   public final UsrRptInqRequest getRequest()
   {
      return (UsrRptInqRequest)getIFastRequest();
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
    * Gets the ForUser Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ForUser Id or null.
    */
   public final String getForUserID( int index )
   {
      return _ForUserID[index];
   }
    
   /**
    * Gets the ForUser Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ForUser Id or the specified default value.
    */
   public final String getForUserID( int index, String defaultValue )
   {
      return _ForUserID[index] == null ? defaultValue : _ForUserID[index];
   }
    
   /**
    * Gets the array of ForUser Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ForUser Id values.
    */
   public final String[] getForUserIDArray()
   {
      return _ForUserID;
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Name or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Name values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the User Profile ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Profile ID or null.
    */
   public final String getUserProfileID( int index )
   {
      return _UserProfileID[index];
   }
    
   /**
    * Gets the User Profile ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Profile ID or the specified default value.
    */
   public final String getUserProfileID( int index, String defaultValue )
   {
      return _UserProfileID[index] == null ? defaultValue : _UserProfileID[index];
   }
    
   /**
    * Gets the array of User Profile ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Profile ID values.
    */
   public final String[] getUserProfileIDArray()
   {
      return _UserProfileID;
   }
    
   /**
    * Gets the User Active field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Active or null.
    */
   public final Boolean getUserActive( int index )
   {
      return _UserActive[index];
   }
    
   /**
    * Gets the User Active field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Active or the specified default value.
    */
   public final boolean getUserActive( int index, boolean defaultValue )
   {
      return _UserActive[index] == null ? defaultValue : _UserActive[index].booleanValue();
   }
    
   /**
    * Gets the array of User Active fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Active values.
    */
   public final Boolean[] getUserActiveArray()
   {
      return _UserActive;
   }
    
   /**
    * Gets the User Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Type or null.
    */
   public final String getUserType( int index )
   {
      return _UserType[index];
   }
    
   /**
    * Gets the User Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Type or the specified default value.
    */
   public final String getUserType( int index, String defaultValue )
   {
      return _UserType[index] == null ? defaultValue : _UserType[index];
   }
    
   /**
    * Gets the array of User Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Type values.
    */
   public final String[] getUserTypeArray()
   {
      return _UserType;
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the Choose Password field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Choose Password or null.
    */
   public final Boolean getChoosePasswd( int index )
   {
      return _ChoosePasswd[index];
   }
    
   /**
    * Gets the Choose Password field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Choose Password or the specified default value.
    */
   public final boolean getChoosePasswd( int index, boolean defaultValue )
   {
      return _ChoosePasswd[index] == null ? defaultValue : _ChoosePasswd[index].booleanValue();
   }
    
   /**
    * Gets the array of Choose Password fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Choose Password values.
    */
   public final Boolean[] getChoosePasswdArray()
   {
      return _ChoosePasswd;
   }
    
   /**
    * Gets the Change Password field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Change Password or null.
    */
   public final Boolean getChangePasswd( int index )
   {
      return _ChangePasswd[index];
   }
    
   /**
    * Gets the Change Password field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Change Password or the specified default value.
    */
   public final boolean getChangePasswd( int index, boolean defaultValue )
   {
      return _ChangePasswd[index] == null ? defaultValue : _ChangePasswd[index].booleanValue();
   }
    
   /**
    * Gets the array of Change Password fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Change Password values.
    */
   public final Boolean[] getChangePasswdArray()
   {
      return _ChangePasswd;
   }
    
   /**
    * Gets the Reset Password field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reset Password or null.
    */
   public final Boolean getResetPasswd( int index )
   {
      return _ResetPasswd[index];
   }
    
   /**
    * Gets the Reset Password field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reset Password or the specified default value.
    */
   public final boolean getResetPasswd( int index, boolean defaultValue )
   {
      return _ResetPasswd[index] == null ? defaultValue : _ResetPasswd[index].booleanValue();
   }
    
   /**
    * Gets the array of Reset Password fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reset Password values.
    */
   public final Boolean[] getResetPasswdArray()
   {
      return _ResetPasswd;
   }
    
   /**
    * Gets the Date Password Changed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date Password Changed or null.
    */
   public final Date getDatePasswdChanged( int index )
   {
      return _DatePasswdChanged[index];
   }
    
   /**
    * Gets the Date Password Changed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date Password Changed or the specified default value.
    */
   public final Date getDatePasswdChanged( int index, Date defaultValue )
   {
      return _DatePasswdChanged[index] == null ? defaultValue : _DatePasswdChanged[index];
   }
    
   /**
    * Gets the array of Date Password Changed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date Password Changed values.
    */
   public final Date[] getDatePasswdChangedArray()
   {
      return _DatePasswdChanged;
   }
    
   /**
    * Gets the Failed Logons field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Failed Logons or null.
    */
   public final Integer getFailedLogons( int index )
   {
      return _FailedLogons[index];
   }
    
   /**
    * Gets the Failed Logons field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Failed Logons or the specified default value.
    */
   public final int getFailedLogons( int index, int defaultValue )
   {
      return _FailedLogons[index] == null ? defaultValue : _FailedLogons[index].intValue();
   }
    
   /**
    * Gets the array of Failed Logons fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Failed Logons values.
    */
   public final Integer[] getFailedLogonsArray()
   {
      return _FailedLogons;
   }
    
   /**
    * Gets the Created By field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created By or null.
    */
   public final String getCreatedBy( int index )
   {
      return _CreatedBy[index];
   }
    
   /**
    * Gets the Created By field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created By or the specified default value.
    */
   public final String getCreatedBy( int index, String defaultValue )
   {
      return _CreatedBy[index] == null ? defaultValue : _CreatedBy[index];
   }
    
   /**
    * Gets the array of Created By fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created By values.
    */
   public final String[] getCreatedByArray()
   {
      return _CreatedBy;
   }
    
   /**
    * Gets the Created On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created On or null.
    */
   public final Date getCreatedOn( int index )
   {
      return _CreatedOn[index];
   }
    
   /**
    * Gets the Created On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created On or the specified default value.
    */
   public final Date getCreatedOn( int index, Date defaultValue )
   {
      return _CreatedOn[index] == null ? defaultValue : _CreatedOn[index];
   }
    
   /**
    * Gets the array of Created On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created On values.
    */
   public final Date[] getCreatedOnArray()
   {
      return _CreatedOn;
   }
    
   /**
    * Gets the Modified By field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified By or null.
    */
   public final String getModifiedBy( int index )
   {
      return _ModifiedBy[index];
   }
    
   /**
    * Gets the Modified By field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified By or the specified default value.
    */
   public final String getModifiedBy( int index, String defaultValue )
   {
      return _ModifiedBy[index] == null ? defaultValue : _ModifiedBy[index];
   }
    
   /**
    * Gets the array of Modified By fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified By values.
    */
   public final String[] getModifiedByArray()
   {
      return _ModifiedBy;
   }
    
   /**
    * Gets the Modified On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified On or null.
    */
   public final Date getModifiedOn( int index )
   {
      return _ModifiedOn[index];
   }
    
   /**
    * Gets the Modified On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified On or the specified default value.
    */
   public final Date getModifiedOn( int index, Date defaultValue )
   {
      return _ModifiedOn[index] == null ? defaultValue : _ModifiedOn[index];
   }
    
   /**
    * Gets the array of Modified On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified On values.
    */
   public final Date[] getModifiedOnArray()
   {
      return _ModifiedOn;
   }
    
   /**
    * Gets the Broker field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker or null.
    */
   public final String getBroker( int index )
   {
      return _Broker[index];
   }
    
   /**
    * Gets the Broker field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker or the specified default value.
    */
   public final String getBroker( int index, String defaultValue )
   {
      return _Broker[index] == null ? defaultValue : _Broker[index];
   }
    
   /**
    * Gets the array of Broker fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker values.
    */
   public final String[] getBrokerArray()
   {
      return _Broker;
   }
    
   /**
    * Gets the Branch field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch or null.
    */
   public final String getBranch( int index )
   {
      return _Branch[index];
   }
    
   /**
    * Gets the Branch field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch or the specified default value.
    */
   public final String getBranch( int index, String defaultValue )
   {
      return _Branch[index] == null ? defaultValue : _Branch[index];
   }
    
   /**
    * Gets the array of Branch fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch values.
    */
   public final String[] getBranchArray()
   {
      return _Branch;
   }
    
   /**
    * Gets the Sales Rep field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep or null.
    */
   public final String getSlsRep( int index )
   {
      return _SlsRep[index];
   }
    
   /**
    * Gets the Sales Rep field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep or the specified default value.
    */
   public final String getSlsRep( int index, String defaultValue )
   {
      return _SlsRep[index] == null ? defaultValue : _SlsRep[index];
   }
    
   /**
    * Gets the array of Sales Rep fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep values.
    */
   public final String[] getSlsRepArray()
   {
      return _SlsRep;
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
    * Gets the EntityID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EntityID or null.
    */
   public final String getEntityID( int index )
   {
      return _EntityID[index];
   }
    
   /**
    * Gets the EntityID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EntityID or the specified default value.
    */
   public final String getEntityID( int index, String defaultValue )
   {
      return _EntityID[index] == null ? defaultValue : _EntityID[index];
   }
    
   /**
    * Gets the array of EntityID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EntityID values.
    */
   public final String[] getEntityIDArray()
   {
      return _EntityID;
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
      
      _ForUserID = resizeArray( _ForUserID, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _UserProfileID = resizeArray( _UserProfileID, _RepeatCount );
      _UserActive = resizeArray( _UserActive, _RepeatCount );
      _UserType = resizeArray( _UserType, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _ChoosePasswd = resizeArray( _ChoosePasswd, _RepeatCount );
      _ChangePasswd = resizeArray( _ChangePasswd, _RepeatCount );
      _ResetPasswd = resizeArray( _ResetPasswd, _RepeatCount );
      _DatePasswdChanged = resizeArray( _DatePasswdChanged, _RepeatCount );
      _FailedLogons = resizeArray( _FailedLogons, _RepeatCount );
      _CreatedBy = resizeArray( _CreatedBy, _RepeatCount );
      _CreatedOn = resizeArray( _CreatedOn, _RepeatCount );
      _ModifiedBy = resizeArray( _ModifiedBy, _RepeatCount );
      _ModifiedOn = resizeArray( _ModifiedOn, _RepeatCount );
      _Broker = resizeArray( _Broker, _RepeatCount );
      _Branch = resizeArray( _Branch, _RepeatCount );
      _SlsRep = resizeArray( _SlsRep, _RepeatCount );
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
      _EntityID = resizeArray( _EntityID, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ForUserID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UserProfileID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UserActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _UserType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChoosePasswd[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ChangePasswd[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ResetPasswd[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DatePasswdChanged[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FailedLogons[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CreatedBy[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreatedOn[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModifiedBy[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModifiedOn[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Broker[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Branch[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRep[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
