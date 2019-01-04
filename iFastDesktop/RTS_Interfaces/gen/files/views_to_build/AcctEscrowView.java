
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Escrow Representative view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctEscrow.doc">AcctEscrow.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctEscrowView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * EntityId of Escrow Representative member array.
    */
   private String[] _EntityId = null;
   
   /**
    * Escrow's Salutation member array.
    */
   private String[] _Salutation = null;
   
   /**
    * Escrow Rep's Last Name member array.
    */
   private String[] _ERepLastName = null;
   
   /**
    * Escrow Rep's First Name member array.
    */
   private String[] _ERepFirstName = null;
   
   /**
    * Fund to which Escrow Applies member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class to which Escrow Applies member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Amount Assignd member array.
    */
   private String[] _AmtAssigned = null;
   
   /**
    * Amount Type member array.
    */
   private String[] _AmountType = null;
   
   /**
    * Amount Type Description member array.
    */
   private String[] _AmountTypeDesc = null;
   
   /**
    * Reason Code member array.
    */
   private String[] _ReasonCode = null;
   
   /**
    * Reason Description member array.
    */
   private String[] _ReasonDesc = null;
   
   /**
    * Default Address Code member array.
    */
   private String[] _DefaultAddrCode = null;
   
   /**
    * AuthorizedToTrade member array.
    */
   private Boolean[] _AuthorizedToTrade = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveFrom = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Created On member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Modified On member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Created By member array.
    */
   private String[] _Username = null;
   
   /**
    * Modified By member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Version Number member array.
    */
   private Integer[] _VersionNum = null;
   

   /**
    * Constructs the AcctEscrowView object.
    * 
    */
   public AcctEscrowView()
   {
      super ( new AcctEscrowRequest() );
   }

   /**
    * Constructs the AcctEscrowView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctEscrowView( String hostEncoding )
   {
      super ( new AcctEscrowRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctEscrowRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctEscrowRequest object.
    */
   public final AcctEscrowRequest getRequest()
   {
      return (AcctEscrowRequest)getIFastRequest();
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
    * Gets the EntityId of Escrow Representative field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EntityId of Escrow Representative or null.
    */
   public final String getEntityId( int index )
   {
      return _EntityId[index];
   }
    
   /**
    * Gets the EntityId of Escrow Representative field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EntityId of Escrow Representative or the specified default value.
    */
   public final String getEntityId( int index, String defaultValue )
   {
      return _EntityId[index] == null ? defaultValue : _EntityId[index];
   }
    
   /**
    * Gets the array of EntityId of Escrow Representative fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EntityId of Escrow Representative values.
    */
   public final String[] getEntityIdArray()
   {
      return _EntityId;
   }
    
   /**
    * Gets the Escrow's Salutation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Escrow's Salutation or null.
    */
   public final String getSalutation( int index )
   {
      return _Salutation[index];
   }
    
   /**
    * Gets the Escrow's Salutation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Escrow's Salutation or the specified default value.
    */
   public final String getSalutation( int index, String defaultValue )
   {
      return _Salutation[index] == null ? defaultValue : _Salutation[index];
   }
    
   /**
    * Gets the array of Escrow's Salutation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Escrow's Salutation values.
    */
   public final String[] getSalutationArray()
   {
      return _Salutation;
   }
    
   /**
    * Gets the Escrow Rep's Last Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Escrow Rep's Last Name or null.
    */
   public final String getERepLastName( int index )
   {
      return _ERepLastName[index];
   }
    
   /**
    * Gets the Escrow Rep's Last Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Escrow Rep's Last Name or the specified default value.
    */
   public final String getERepLastName( int index, String defaultValue )
   {
      return _ERepLastName[index] == null ? defaultValue : _ERepLastName[index];
   }
    
   /**
    * Gets the array of Escrow Rep's Last Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Escrow Rep's Last Name values.
    */
   public final String[] getERepLastNameArray()
   {
      return _ERepLastName;
   }
    
   /**
    * Gets the Escrow Rep's First Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Escrow Rep's First Name or null.
    */
   public final String getERepFirstName( int index )
   {
      return _ERepFirstName[index];
   }
    
   /**
    * Gets the Escrow Rep's First Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Escrow Rep's First Name or the specified default value.
    */
   public final String getERepFirstName( int index, String defaultValue )
   {
      return _ERepFirstName[index] == null ? defaultValue : _ERepFirstName[index];
   }
    
   /**
    * Gets the array of Escrow Rep's First Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Escrow Rep's First Name values.
    */
   public final String[] getERepFirstNameArray()
   {
      return _ERepFirstName;
   }
    
   /**
    * Gets the Fund to which Escrow Applies field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund to which Escrow Applies or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund to which Escrow Applies field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund to which Escrow Applies or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund to which Escrow Applies fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund to which Escrow Applies values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Class to which Escrow Applies field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class to which Escrow Applies or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class to which Escrow Applies field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class to which Escrow Applies or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class to which Escrow Applies fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class to which Escrow Applies values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the Amount Assignd field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount Assignd or null.
    */
   public final String getAmtAssigned( int index )
   {
      return _AmtAssigned[index];
   }
    
   /**
    * Gets the Amount Assignd field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Assignd or the specified default value.
    */
   public final String getAmtAssigned( int index, String defaultValue )
   {
      return _AmtAssigned[index] == null ? defaultValue : _AmtAssigned[index];
   }
    
   /**
    * Gets the array of Amount Assignd fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount Assignd values.
    */
   public final String[] getAmtAssignedArray()
   {
      return _AmtAssigned;
   }
    
   /**
    * Gets the Amount Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount Type or null.
    */
   public final String getAmountType( int index )
   {
      return _AmountType[index];
   }
    
   /**
    * Gets the Amount Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Type or the specified default value.
    */
   public final String getAmountType( int index, String defaultValue )
   {
      return _AmountType[index] == null ? defaultValue : _AmountType[index];
   }
    
   /**
    * Gets the array of Amount Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount Type values.
    */
   public final String[] getAmountTypeArray()
   {
      return _AmountType;
   }
    
   /**
    * Gets the Amount Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount Type Description or null.
    */
   public final String getAmountTypeDesc( int index )
   {
      return _AmountTypeDesc[index];
   }
    
   /**
    * Gets the Amount Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Type Description or the specified default value.
    */
   public final String getAmountTypeDesc( int index, String defaultValue )
   {
      return _AmountTypeDesc[index] == null ? defaultValue : _AmountTypeDesc[index];
   }
    
   /**
    * Gets the array of Amount Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount Type Description values.
    */
   public final String[] getAmountTypeDescArray()
   {
      return _AmountTypeDesc;
   }
    
   /**
    * Gets the Reason Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason Code or null.
    */
   public final String getReasonCode( int index )
   {
      return _ReasonCode[index];
   }
    
   /**
    * Gets the Reason Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason Code or the specified default value.
    */
   public final String getReasonCode( int index, String defaultValue )
   {
      return _ReasonCode[index] == null ? defaultValue : _ReasonCode[index];
   }
    
   /**
    * Gets the array of Reason Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason Code values.
    */
   public final String[] getReasonCodeArray()
   {
      return _ReasonCode;
   }
    
   /**
    * Gets the Reason Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason Description or null.
    */
   public final String getReasonDesc( int index )
   {
      return _ReasonDesc[index];
   }
    
   /**
    * Gets the Reason Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason Description or the specified default value.
    */
   public final String getReasonDesc( int index, String defaultValue )
   {
      return _ReasonDesc[index] == null ? defaultValue : _ReasonDesc[index];
   }
    
   /**
    * Gets the array of Reason Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason Description values.
    */
   public final String[] getReasonDescArray()
   {
      return _ReasonDesc;
   }
    
   /**
    * Gets the Default Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Default Address Code or null.
    */
   public final String getDefaultAddrCode( int index )
   {
      return _DefaultAddrCode[index];
   }
    
   /**
    * Gets the Default Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Address Code or the specified default value.
    */
   public final String getDefaultAddrCode( int index, String defaultValue )
   {
      return _DefaultAddrCode[index] == null ? defaultValue : _DefaultAddrCode[index];
   }
    
   /**
    * Gets the array of Default Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Default Address Code values.
    */
   public final String[] getDefaultAddrCodeArray()
   {
      return _DefaultAddrCode;
   }
    
   /**
    * Gets the AuthorizedToTrade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AuthorizedToTrade or null.
    */
   public final Boolean getAuthorizedToTrade( int index )
   {
      return _AuthorizedToTrade[index];
   }
    
   /**
    * Gets the AuthorizedToTrade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AuthorizedToTrade or the specified default value.
    */
   public final boolean getAuthorizedToTrade( int index, boolean defaultValue )
   {
      return _AuthorizedToTrade[index] == null ? defaultValue : _AuthorizedToTrade[index].booleanValue();
   }
    
   /**
    * Gets the array of AuthorizedToTrade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AuthorizedToTrade values.
    */
   public final Boolean[] getAuthorizedToTradeArray()
   {
      return _AuthorizedToTrade;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveFrom( int index )
   {
      return _EffectiveFrom[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveFrom( int index, Date defaultValue )
   {
      return _EffectiveFrom[index] == null ? defaultValue : _EffectiveFrom[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getEffectiveFromArray()
   {
      return _EffectiveFrom;
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Created On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created On or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Created On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created On or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Created On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created On values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Modified On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified On or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modified On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified On or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modified On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified On values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Created By field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created By or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Created By field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created By or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Created By fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created By values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Modified By field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified By or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modified By field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified By or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modified By fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified By values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Version Number or null.
    */
   public final Integer getVersionNum( int index )
   {
      return _VersionNum[index];
   }
    
   /**
    * Gets the Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Version Number or the specified default value.
    */
   public final int getVersionNum( int index, int defaultValue )
   {
      return _VersionNum[index] == null ? defaultValue : _VersionNum[index].intValue();
   }
    
   /**
    * Gets the array of Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Version Number values.
    */
   public final Integer[] getVersionNumArray()
   {
      return _VersionNum;
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
      
      _EntityId = resizeArray( _EntityId, _RepeatCount );
      _Salutation = resizeArray( _Salutation, _RepeatCount );
      _ERepLastName = resizeArray( _ERepLastName, _RepeatCount );
      _ERepFirstName = resizeArray( _ERepFirstName, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _AmtAssigned = resizeArray( _AmtAssigned, _RepeatCount );
      _AmountType = resizeArray( _AmountType, _RepeatCount );
      _AmountTypeDesc = resizeArray( _AmountTypeDesc, _RepeatCount );
      _ReasonCode = resizeArray( _ReasonCode, _RepeatCount );
      _ReasonDesc = resizeArray( _ReasonDesc, _RepeatCount );
      _DefaultAddrCode = resizeArray( _DefaultAddrCode, _RepeatCount );
      _AuthorizedToTrade = resizeArray( _AuthorizedToTrade, _RepeatCount );
      _EffectiveFrom = resizeArray( _EffectiveFrom, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _VersionNum = resizeArray( _VersionNum, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _EntityId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Salutation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ERepLastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ERepFirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmtAssigned[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReasonCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReasonDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DefaultAddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AuthorizedToTrade[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EffectiveFrom[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VersionNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
