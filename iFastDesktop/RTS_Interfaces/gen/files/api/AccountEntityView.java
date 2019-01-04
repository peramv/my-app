
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Entity view.
 * For additional view information see <A HREF="../../../../viewspecs/AccountEntity.doc">AccountEntity.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountEntityView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Entity Salutation member array.
    */
   private String[] _Salutation = null;
   
   /**
    * Entity Last Name member array.
    */
   private String[] _LastName = null;
   
   /**
    * Entity First Name member array.
    */
   private String[] _FirstName = null;
   
   /**
    * Entity ID member array.
    */
   private String[] _EntityId = null;
   
   /**
    * Entity Type member array.
    */
   private String[] _EntityType = null;
   
   /**
    * Entity Type Description member array.
    */
   private String[] _EntityTypeDesc = null;
   
   /**
    * Sequence Number member array.
    */
   private Integer[] _SeqNumber = null;
   
   /**
    * Relationship Code member array.
    */
   private String[] _RelateCode = null;
   
   /**
    * Relationship Code Description member array.
    */
   private String[] _RelateCodeShip = null;
   
   /**
    * Default Address Code member array.
    */
   private String[] _AddrCode = null;
   
   /**
    * Authurized to Trade member array.
    */
   private Boolean[] _AuthorizedToTrade = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
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
    * Benefit Percentage member array.
    */
   private String[] _BenPercentage = null;
   
   /**
    * Benefit Irrevocable member array.
    */
   private Boolean[] _Irrevocable = null;
   
   /**
    * Joint Deposition Code member array.
    */
   private String[] _DispositionCode = null;
   
   /**
    * Joint Deposition Description member array.
    */
   private String[] _DispostitionDesc = null;
   
   /**
    * Joint Type member array.
    */
   private String[] _JointType = null;
   
   /**
    * Joint Type Description member array.
    */
   private String[] _JointTypeDesc = null;
   
   /**
    * Escrow Fund Code member array.
    */
   private String[] _EscrowFund = null;
   
   /**
    * Escrow Class Code member array.
    */
   private String[] _EscrowClass = null;
   
   /**
    * Assgined Amount member array.
    */
   private String[] _AmtAssigned = null;
   
   /**
    * Amount Type (Units or Dollar) member array.
    */
   private String[] _AmountType = null;
   
   /**
    * Amount Type Description member array.
    */
   private String[] _AmountTypeDesc = null;
   
   /**
    * Reason Code for Escrow member array.
    */
   private String[] _ReasonCode = null;
   
   /**
    * Reason Description for Escrow member array.
    */
   private String[] _ReasonDesc = null;
   
   /**
    * Escrow Effective Date member array.
    */
   private Date[] _EscrowDeff = null;
   
   /**
    * Escrow Expirary Date member array.
    */
   private Date[] _EscrowStopDate = null;
   
   /**
    * Acct-Entity Version Number member array.
    */
   private Integer[] _AcctEntVer = null;
   
   /**
    * Acct-Entity Record Id member array.
    */
   private Integer[] _AcctEntRid = null;
   
   /**
    * Acct-Entity-Benef Version Number member array.
    */
   private Integer[] _AcctEntBenefVer = null;
   
   /**
    * Acct-Entity-Benef Record Id member array.
    */
   private Integer[] _AcctEntBenefRid = null;
   
   /**
    * Acct-Entity-Joint Version Number member array.
    */
   private Integer[] _AcctEntJointVer = null;
   
   /**
    * Acct-Entity-Joint Record Id member array.
    */
   private Integer[] _AcctEntJointRid = null;
   
   /**
    * Assign-Detl Version Number member array.
    */
   private Integer[] _AssignDetlVer = null;
   
   /**
    * Assign-Detl Record Id member array.
    */
   private Integer[] _AssignDetlRid = null;
   
   /**
    * RESP HRDC Relationship Code member array.
    */
   private String[] _HRDCRelateCode = null;
   
   /**
    * RESP HRCD Relate Code Desc member array.
    */
   private String[] _HRDCRelateDesc = null;
   
   /**
    * RESP Reason Code member array.
    */
   private String[] _RESPReasonCode = null;
   
   /**
    * RESP Reason Code Desc member array.
    */
   private String[] _RESPReasonDesc = null;
   
   /**
    * Tax Jurisdiction Code member array.
    */
   private String[] _TaxJurisCode = null;
   
   /**
    * Tax jurisdiction description member array.
    */
   private String[] _TaxJurisDesc = null;
   
   /**
    * Date when letter of notification was requested member array.
    */
   private Date[] _LetterDate = null;
   
   /**
    * Print the notification letter member array.
    */
   private Boolean[] _LetterReq = null;
   
   /**
    * Sequence Number of RESP Parent/Legal Guardian member array.
    */
   private Integer[] _RESPParentSeq = null;
   
   /**
    * Sequence Number of RESP Designated Institution member array.
    */
   private Integer[] _RESPDesInstSeq = null;
   
   /**
    * Flag if contributions reported to HRSDC to attract CESG award. member array.
    */
   private Boolean[] _GrantRequest = null;
   
   /**
    * Flag for GrandFatehered plans member array.
    */
   private Boolean[] _Tainted = null;
   
   /**
    * End date of beneficiary being tainted member array.
    */
   private Date[] _TaintEndDate = null;
   
   /**
    * Primary Care Giver's Entity ID member array.
    */
   private String[] _RESPPCGId = null;
   
   /**
    * RESPBenefInfo record Id member array.
    */
   private Integer[] _RESPBenefInfoRid = null;
   
   /**
    * RESPBenefInfo.Version member array.
    */
   private Integer[] _RESPBenefInfoVer = null;
   
   /**
    * Flag if CLB was taken by RESP beneficiary. member array.
    */
   private Boolean[] _CLBExists = null;
   
   /**
    * Flag if RESP beneficiary has transactions. member array.
    */
   private Boolean[] _TradeExists = null;
   
   /**
    * Flag if there is an existing Grant request member array.
    */
   private Boolean[] _GrantExists = null;
   
   /**
    * Flag if record 400 has been sent. member array.
    */
   private Boolean[] _Rec400Sent = null;
   
   /**
    * Date of Birth member array.
    */
   private Date[] _DofB = null;
   
   /**
    * TaxYear of the last TFSA Amendment filed to Government member array.
    */
   private Integer[] _TFSALastAmendTaxYear = null;
   
   /**
    * Death Settlement Date member array.
    */
   private Date[] _DeathSettlementDate = null;
   
   /**
    * Loan Type member array.
    */
   private String[] _LoanType = null;
   
   /**
    * Loan Number member array.
    */
   private String[] _LoanNumber = null;
   
   /**
    * Reference Code member array.
    */
   private String[] _RefCode = null;
   
   /**
    * Reference Type member array.
    */
   private String[] _RefType = null;
   
   /**
    * Account Ownership Percentage member array.
    */
   private String[] _PercentOwn = null;
   
   /**
    * Associated Entity member array.
    */
   private String[] _AssocEntityID = null;
   

   /**
    * Constructs the AccountEntityView object.
    * 
    */
   public AccountEntityView()
   {
      super ( new AccountEntityRequest() );
   }

   /**
    * Constructs the AccountEntityView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AccountEntityView( String hostEncoding )
   {
      super ( new AccountEntityRequest( hostEncoding ) );
   }

   /**
    * Gets the AccountEntityRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AccountEntityRequest object.
    */
   public final AccountEntityRequest getRequest()
   {
      return (AccountEntityRequest)getIFastRequest();
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
    * Gets the Entity Salutation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Salutation or null.
    */
   public final String getSalutation( int index )
   {
      return _Salutation[index];
   }
    
   /**
    * Gets the Entity Salutation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Salutation or the specified default value.
    */
   public final String getSalutation( int index, String defaultValue )
   {
      return _Salutation[index] == null ? defaultValue : _Salutation[index];
   }
    
   /**
    * Gets the array of Entity Salutation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Salutation values.
    */
   public final String[] getSalutationArray()
   {
      return _Salutation;
   }
    
   /**
    * Gets the Entity Last Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Last Name or null.
    */
   public final String getLastName( int index )
   {
      return _LastName[index];
   }
    
   /**
    * Gets the Entity Last Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Last Name or the specified default value.
    */
   public final String getLastName( int index, String defaultValue )
   {
      return _LastName[index] == null ? defaultValue : _LastName[index];
   }
    
   /**
    * Gets the array of Entity Last Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Last Name values.
    */
   public final String[] getLastNameArray()
   {
      return _LastName;
   }
    
   /**
    * Gets the Entity First Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity First Name or null.
    */
   public final String getFirstName( int index )
   {
      return _FirstName[index];
   }
    
   /**
    * Gets the Entity First Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity First Name or the specified default value.
    */
   public final String getFirstName( int index, String defaultValue )
   {
      return _FirstName[index] == null ? defaultValue : _FirstName[index];
   }
    
   /**
    * Gets the array of Entity First Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity First Name values.
    */
   public final String[] getFirstNameArray()
   {
      return _FirstName;
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity ID or null.
    */
   public final String getEntityId( int index )
   {
      return _EntityId[index];
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity ID or the specified default value.
    */
   public final String getEntityId( int index, String defaultValue )
   {
      return _EntityId[index] == null ? defaultValue : _EntityId[index];
   }
    
   /**
    * Gets the array of Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity ID values.
    */
   public final String[] getEntityIdArray()
   {
      return _EntityId;
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
    * Gets the Sequence Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sequence Number or null.
    */
   public final Integer getSeqNumber( int index )
   {
      return _SeqNumber[index];
   }
    
   /**
    * Gets the Sequence Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sequence Number or the specified default value.
    */
   public final int getSeqNumber( int index, int defaultValue )
   {
      return _SeqNumber[index] == null ? defaultValue : _SeqNumber[index].intValue();
   }
    
   /**
    * Gets the array of Sequence Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sequence Number values.
    */
   public final Integer[] getSeqNumberArray()
   {
      return _SeqNumber;
   }
    
   /**
    * Gets the Relationship Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Relationship Code or null.
    */
   public final String getRelateCode( int index )
   {
      return _RelateCode[index];
   }
    
   /**
    * Gets the Relationship Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Relationship Code or the specified default value.
    */
   public final String getRelateCode( int index, String defaultValue )
   {
      return _RelateCode[index] == null ? defaultValue : _RelateCode[index];
   }
    
   /**
    * Gets the array of Relationship Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Relationship Code values.
    */
   public final String[] getRelateCodeArray()
   {
      return _RelateCode;
   }
    
   /**
    * Gets the Relationship Code Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Relationship Code Description or null.
    */
   public final String getRelateCodeShip( int index )
   {
      return _RelateCodeShip[index];
   }
    
   /**
    * Gets the Relationship Code Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Relationship Code Description or the specified default value.
    */
   public final String getRelateCodeShip( int index, String defaultValue )
   {
      return _RelateCodeShip[index] == null ? defaultValue : _RelateCodeShip[index];
   }
    
   /**
    * Gets the array of Relationship Code Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Relationship Code Description values.
    */
   public final String[] getRelateCodeShipArray()
   {
      return _RelateCodeShip;
   }
    
   /**
    * Gets the Default Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Default Address Code or null.
    */
   public final String getAddrCode( int index )
   {
      return _AddrCode[index];
   }
    
   /**
    * Gets the Default Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Address Code or the specified default value.
    */
   public final String getAddrCode( int index, String defaultValue )
   {
      return _AddrCode[index] == null ? defaultValue : _AddrCode[index];
   }
    
   /**
    * Gets the array of Default Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Default Address Code values.
    */
   public final String[] getAddrCodeArray()
   {
      return _AddrCode;
   }
    
   /**
    * Gets the Authurized to Trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Authurized to Trade or null.
    */
   public final Boolean getAuthorizedToTrade( int index )
   {
      return _AuthorizedToTrade[index];
   }
    
   /**
    * Gets the Authurized to Trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Authurized to Trade or the specified default value.
    */
   public final boolean getAuthorizedToTrade( int index, boolean defaultValue )
   {
      return _AuthorizedToTrade[index] == null ? defaultValue : _AuthorizedToTrade[index].booleanValue();
   }
    
   /**
    * Gets the array of Authurized to Trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Authurized to Trade values.
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
    * Gets the Benefit Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Benefit Percentage or null.
    */
   public final String getBenPercentage( int index )
   {
      return _BenPercentage[index];
   }
    
   /**
    * Gets the Benefit Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Benefit Percentage or the specified default value.
    */
   public final String getBenPercentage( int index, String defaultValue )
   {
      return _BenPercentage[index] == null ? defaultValue : _BenPercentage[index];
   }
    
   /**
    * Gets the array of Benefit Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Benefit Percentage values.
    */
   public final String[] getBenPercentageArray()
   {
      return _BenPercentage;
   }
    
   /**
    * Gets the Benefit Irrevocable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Benefit Irrevocable or null.
    */
   public final Boolean getIrrevocable( int index )
   {
      return _Irrevocable[index];
   }
    
   /**
    * Gets the Benefit Irrevocable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Benefit Irrevocable or the specified default value.
    */
   public final boolean getIrrevocable( int index, boolean defaultValue )
   {
      return _Irrevocable[index] == null ? defaultValue : _Irrevocable[index].booleanValue();
   }
    
   /**
    * Gets the array of Benefit Irrevocable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Benefit Irrevocable values.
    */
   public final Boolean[] getIrrevocableArray()
   {
      return _Irrevocable;
   }
    
   /**
    * Gets the Joint Deposition Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Joint Deposition Code or null.
    */
   public final String getDispositionCode( int index )
   {
      return _DispositionCode[index];
   }
    
   /**
    * Gets the Joint Deposition Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Joint Deposition Code or the specified default value.
    */
   public final String getDispositionCode( int index, String defaultValue )
   {
      return _DispositionCode[index] == null ? defaultValue : _DispositionCode[index];
   }
    
   /**
    * Gets the array of Joint Deposition Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Joint Deposition Code values.
    */
   public final String[] getDispositionCodeArray()
   {
      return _DispositionCode;
   }
    
   /**
    * Gets the Joint Deposition Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Joint Deposition Description or null.
    */
   public final String getDispostitionDesc( int index )
   {
      return _DispostitionDesc[index];
   }
    
   /**
    * Gets the Joint Deposition Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Joint Deposition Description or the specified default value.
    */
   public final String getDispostitionDesc( int index, String defaultValue )
   {
      return _DispostitionDesc[index] == null ? defaultValue : _DispostitionDesc[index];
   }
    
   /**
    * Gets the array of Joint Deposition Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Joint Deposition Description values.
    */
   public final String[] getDispostitionDescArray()
   {
      return _DispostitionDesc;
   }
    
   /**
    * Gets the Joint Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Joint Type or null.
    */
   public final String getJointType( int index )
   {
      return _JointType[index];
   }
    
   /**
    * Gets the Joint Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Joint Type or the specified default value.
    */
   public final String getJointType( int index, String defaultValue )
   {
      return _JointType[index] == null ? defaultValue : _JointType[index];
   }
    
   /**
    * Gets the array of Joint Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Joint Type values.
    */
   public final String[] getJointTypeArray()
   {
      return _JointType;
   }
    
   /**
    * Gets the Joint Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Joint Type Description or null.
    */
   public final String getJointTypeDesc( int index )
   {
      return _JointTypeDesc[index];
   }
    
   /**
    * Gets the Joint Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Joint Type Description or the specified default value.
    */
   public final String getJointTypeDesc( int index, String defaultValue )
   {
      return _JointTypeDesc[index] == null ? defaultValue : _JointTypeDesc[index];
   }
    
   /**
    * Gets the array of Joint Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Joint Type Description values.
    */
   public final String[] getJointTypeDescArray()
   {
      return _JointTypeDesc;
   }
    
   /**
    * Gets the Escrow Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Escrow Fund Code or null.
    */
   public final String getEscrowFund( int index )
   {
      return _EscrowFund[index];
   }
    
   /**
    * Gets the Escrow Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Escrow Fund Code or the specified default value.
    */
   public final String getEscrowFund( int index, String defaultValue )
   {
      return _EscrowFund[index] == null ? defaultValue : _EscrowFund[index];
   }
    
   /**
    * Gets the array of Escrow Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Escrow Fund Code values.
    */
   public final String[] getEscrowFundArray()
   {
      return _EscrowFund;
   }
    
   /**
    * Gets the Escrow Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Escrow Class Code or null.
    */
   public final String getEscrowClass( int index )
   {
      return _EscrowClass[index];
   }
    
   /**
    * Gets the Escrow Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Escrow Class Code or the specified default value.
    */
   public final String getEscrowClass( int index, String defaultValue )
   {
      return _EscrowClass[index] == null ? defaultValue : _EscrowClass[index];
   }
    
   /**
    * Gets the array of Escrow Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Escrow Class Code values.
    */
   public final String[] getEscrowClassArray()
   {
      return _EscrowClass;
   }
    
   /**
    * Gets the Assgined Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Assgined Amount or null.
    */
   public final String getAmtAssigned( int index )
   {
      return _AmtAssigned[index];
   }
    
   /**
    * Gets the Assgined Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Assgined Amount or the specified default value.
    */
   public final String getAmtAssigned( int index, String defaultValue )
   {
      return _AmtAssigned[index] == null ? defaultValue : _AmtAssigned[index];
   }
    
   /**
    * Gets the array of Assgined Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Assgined Amount values.
    */
   public final String[] getAmtAssignedArray()
   {
      return _AmtAssigned;
   }
    
   /**
    * Gets the Amount Type (Units or Dollar) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount Type (Units or Dollar) or null.
    */
   public final String getAmountType( int index )
   {
      return _AmountType[index];
   }
    
   /**
    * Gets the Amount Type (Units or Dollar) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Type (Units or Dollar) or the specified default value.
    */
   public final String getAmountType( int index, String defaultValue )
   {
      return _AmountType[index] == null ? defaultValue : _AmountType[index];
   }
    
   /**
    * Gets the array of Amount Type (Units or Dollar) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount Type (Units or Dollar) values.
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
    * Gets the Reason Code for Escrow field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason Code for Escrow or null.
    */
   public final String getReasonCode( int index )
   {
      return _ReasonCode[index];
   }
    
   /**
    * Gets the Reason Code for Escrow field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason Code for Escrow or the specified default value.
    */
   public final String getReasonCode( int index, String defaultValue )
   {
      return _ReasonCode[index] == null ? defaultValue : _ReasonCode[index];
   }
    
   /**
    * Gets the array of Reason Code for Escrow fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason Code for Escrow values.
    */
   public final String[] getReasonCodeArray()
   {
      return _ReasonCode;
   }
    
   /**
    * Gets the Reason Description for Escrow field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason Description for Escrow or null.
    */
   public final String getReasonDesc( int index )
   {
      return _ReasonDesc[index];
   }
    
   /**
    * Gets the Reason Description for Escrow field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason Description for Escrow or the specified default value.
    */
   public final String getReasonDesc( int index, String defaultValue )
   {
      return _ReasonDesc[index] == null ? defaultValue : _ReasonDesc[index];
   }
    
   /**
    * Gets the array of Reason Description for Escrow fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason Description for Escrow values.
    */
   public final String[] getReasonDescArray()
   {
      return _ReasonDesc;
   }
    
   /**
    * Gets the Escrow Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Escrow Effective Date or null.
    */
   public final Date getEscrowDeff( int index )
   {
      return _EscrowDeff[index];
   }
    
   /**
    * Gets the Escrow Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Escrow Effective Date or the specified default value.
    */
   public final Date getEscrowDeff( int index, Date defaultValue )
   {
      return _EscrowDeff[index] == null ? defaultValue : _EscrowDeff[index];
   }
    
   /**
    * Gets the array of Escrow Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Escrow Effective Date values.
    */
   public final Date[] getEscrowDeffArray()
   {
      return _EscrowDeff;
   }
    
   /**
    * Gets the Escrow Expirary Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Escrow Expirary Date or null.
    */
   public final Date getEscrowStopDate( int index )
   {
      return _EscrowStopDate[index];
   }
    
   /**
    * Gets the Escrow Expirary Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Escrow Expirary Date or the specified default value.
    */
   public final Date getEscrowStopDate( int index, Date defaultValue )
   {
      return _EscrowStopDate[index] == null ? defaultValue : _EscrowStopDate[index];
   }
    
   /**
    * Gets the array of Escrow Expirary Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Escrow Expirary Date values.
    */
   public final Date[] getEscrowStopDateArray()
   {
      return _EscrowStopDate;
   }
    
   /**
    * Gets the Acct-Entity Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-Entity Version Number or null.
    */
   public final Integer getAcctEntVer( int index )
   {
      return _AcctEntVer[index];
   }
    
   /**
    * Gets the Acct-Entity Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-Entity Version Number or the specified default value.
    */
   public final int getAcctEntVer( int index, int defaultValue )
   {
      return _AcctEntVer[index] == null ? defaultValue : _AcctEntVer[index].intValue();
   }
    
   /**
    * Gets the array of Acct-Entity Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-Entity Version Number values.
    */
   public final Integer[] getAcctEntVerArray()
   {
      return _AcctEntVer;
   }
    
   /**
    * Gets the Acct-Entity Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-Entity Record Id or null.
    */
   public final Integer getAcctEntRid( int index )
   {
      return _AcctEntRid[index];
   }
    
   /**
    * Gets the Acct-Entity Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-Entity Record Id or the specified default value.
    */
   public final int getAcctEntRid( int index, int defaultValue )
   {
      return _AcctEntRid[index] == null ? defaultValue : _AcctEntRid[index].intValue();
   }
    
   /**
    * Gets the array of Acct-Entity Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-Entity Record Id values.
    */
   public final Integer[] getAcctEntRidArray()
   {
      return _AcctEntRid;
   }
    
   /**
    * Gets the Acct-Entity-Benef Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-Entity-Benef Version Number or null.
    */
   public final Integer getAcctEntBenefVer( int index )
   {
      return _AcctEntBenefVer[index];
   }
    
   /**
    * Gets the Acct-Entity-Benef Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-Entity-Benef Version Number or the specified default value.
    */
   public final int getAcctEntBenefVer( int index, int defaultValue )
   {
      return _AcctEntBenefVer[index] == null ? defaultValue : _AcctEntBenefVer[index].intValue();
   }
    
   /**
    * Gets the array of Acct-Entity-Benef Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-Entity-Benef Version Number values.
    */
   public final Integer[] getAcctEntBenefVerArray()
   {
      return _AcctEntBenefVer;
   }
    
   /**
    * Gets the Acct-Entity-Benef Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-Entity-Benef Record Id or null.
    */
   public final Integer getAcctEntBenefRid( int index )
   {
      return _AcctEntBenefRid[index];
   }
    
   /**
    * Gets the Acct-Entity-Benef Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-Entity-Benef Record Id or the specified default value.
    */
   public final int getAcctEntBenefRid( int index, int defaultValue )
   {
      return _AcctEntBenefRid[index] == null ? defaultValue : _AcctEntBenefRid[index].intValue();
   }
    
   /**
    * Gets the array of Acct-Entity-Benef Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-Entity-Benef Record Id values.
    */
   public final Integer[] getAcctEntBenefRidArray()
   {
      return _AcctEntBenefRid;
   }
    
   /**
    * Gets the Acct-Entity-Joint Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-Entity-Joint Version Number or null.
    */
   public final Integer getAcctEntJointVer( int index )
   {
      return _AcctEntJointVer[index];
   }
    
   /**
    * Gets the Acct-Entity-Joint Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-Entity-Joint Version Number or the specified default value.
    */
   public final int getAcctEntJointVer( int index, int defaultValue )
   {
      return _AcctEntJointVer[index] == null ? defaultValue : _AcctEntJointVer[index].intValue();
   }
    
   /**
    * Gets the array of Acct-Entity-Joint Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-Entity-Joint Version Number values.
    */
   public final Integer[] getAcctEntJointVerArray()
   {
      return _AcctEntJointVer;
   }
    
   /**
    * Gets the Acct-Entity-Joint Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-Entity-Joint Record Id or null.
    */
   public final Integer getAcctEntJointRid( int index )
   {
      return _AcctEntJointRid[index];
   }
    
   /**
    * Gets the Acct-Entity-Joint Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-Entity-Joint Record Id or the specified default value.
    */
   public final int getAcctEntJointRid( int index, int defaultValue )
   {
      return _AcctEntJointRid[index] == null ? defaultValue : _AcctEntJointRid[index].intValue();
   }
    
   /**
    * Gets the array of Acct-Entity-Joint Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-Entity-Joint Record Id values.
    */
   public final Integer[] getAcctEntJointRidArray()
   {
      return _AcctEntJointRid;
   }
    
   /**
    * Gets the Assign-Detl Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Assign-Detl Version Number or null.
    */
   public final Integer getAssignDetlVer( int index )
   {
      return _AssignDetlVer[index];
   }
    
   /**
    * Gets the Assign-Detl Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Assign-Detl Version Number or the specified default value.
    */
   public final int getAssignDetlVer( int index, int defaultValue )
   {
      return _AssignDetlVer[index] == null ? defaultValue : _AssignDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of Assign-Detl Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Assign-Detl Version Number values.
    */
   public final Integer[] getAssignDetlVerArray()
   {
      return _AssignDetlVer;
   }
    
   /**
    * Gets the Assign-Detl Record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Assign-Detl Record Id or null.
    */
   public final Integer getAssignDetlRid( int index )
   {
      return _AssignDetlRid[index];
   }
    
   /**
    * Gets the Assign-Detl Record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Assign-Detl Record Id or the specified default value.
    */
   public final int getAssignDetlRid( int index, int defaultValue )
   {
      return _AssignDetlRid[index] == null ? defaultValue : _AssignDetlRid[index].intValue();
   }
    
   /**
    * Gets the array of Assign-Detl Record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Assign-Detl Record Id values.
    */
   public final Integer[] getAssignDetlRidArray()
   {
      return _AssignDetlRid;
   }
    
   /**
    * Gets the RESP HRDC Relationship Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP HRDC Relationship Code or null.
    */
   public final String getHRDCRelateCode( int index )
   {
      return _HRDCRelateCode[index];
   }
    
   /**
    * Gets the RESP HRDC Relationship Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP HRDC Relationship Code or the specified default value.
    */
   public final String getHRDCRelateCode( int index, String defaultValue )
   {
      return _HRDCRelateCode[index] == null ? defaultValue : _HRDCRelateCode[index];
   }
    
   /**
    * Gets the array of RESP HRDC Relationship Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP HRDC Relationship Code values.
    */
   public final String[] getHRDCRelateCodeArray()
   {
      return _HRDCRelateCode;
   }
    
   /**
    * Gets the RESP HRCD Relate Code Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP HRCD Relate Code Desc or null.
    */
   public final String getHRDCRelateDesc( int index )
   {
      return _HRDCRelateDesc[index];
   }
    
   /**
    * Gets the RESP HRCD Relate Code Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP HRCD Relate Code Desc or the specified default value.
    */
   public final String getHRDCRelateDesc( int index, String defaultValue )
   {
      return _HRDCRelateDesc[index] == null ? defaultValue : _HRDCRelateDesc[index];
   }
    
   /**
    * Gets the array of RESP HRCD Relate Code Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP HRCD Relate Code Desc values.
    */
   public final String[] getHRDCRelateDescArray()
   {
      return _HRDCRelateDesc;
   }
    
   /**
    * Gets the RESP Reason Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP Reason Code or null.
    */
   public final String getRESPReasonCode( int index )
   {
      return _RESPReasonCode[index];
   }
    
   /**
    * Gets the RESP Reason Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Reason Code or the specified default value.
    */
   public final String getRESPReasonCode( int index, String defaultValue )
   {
      return _RESPReasonCode[index] == null ? defaultValue : _RESPReasonCode[index];
   }
    
   /**
    * Gets the array of RESP Reason Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP Reason Code values.
    */
   public final String[] getRESPReasonCodeArray()
   {
      return _RESPReasonCode;
   }
    
   /**
    * Gets the RESP Reason Code Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP Reason Code Desc or null.
    */
   public final String getRESPReasonDesc( int index )
   {
      return _RESPReasonDesc[index];
   }
    
   /**
    * Gets the RESP Reason Code Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Reason Code Desc or the specified default value.
    */
   public final String getRESPReasonDesc( int index, String defaultValue )
   {
      return _RESPReasonDesc[index] == null ? defaultValue : _RESPReasonDesc[index];
   }
    
   /**
    * Gets the array of RESP Reason Code Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP Reason Code Desc values.
    */
   public final String[] getRESPReasonDescArray()
   {
      return _RESPReasonDesc;
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
    * Gets the Tax jurisdiction description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax jurisdiction description or null.
    */
   public final String getTaxJurisDesc( int index )
   {
      return _TaxJurisDesc[index];
   }
    
   /**
    * Gets the Tax jurisdiction description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax jurisdiction description or the specified default value.
    */
   public final String getTaxJurisDesc( int index, String defaultValue )
   {
      return _TaxJurisDesc[index] == null ? defaultValue : _TaxJurisDesc[index];
   }
    
   /**
    * Gets the array of Tax jurisdiction description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax jurisdiction description values.
    */
   public final String[] getTaxJurisDescArray()
   {
      return _TaxJurisDesc;
   }
    
   /**
    * Gets the Date when letter of notification was requested field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date when letter of notification was requested or null.
    */
   public final Date getLetterDate( int index )
   {
      return _LetterDate[index];
   }
    
   /**
    * Gets the Date when letter of notification was requested field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date when letter of notification was requested or the specified default value.
    */
   public final Date getLetterDate( int index, Date defaultValue )
   {
      return _LetterDate[index] == null ? defaultValue : _LetterDate[index];
   }
    
   /**
    * Gets the array of Date when letter of notification was requested fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date when letter of notification was requested values.
    */
   public final Date[] getLetterDateArray()
   {
      return _LetterDate;
   }
    
   /**
    * Gets the Print the notification letter field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Print the notification letter or null.
    */
   public final Boolean getLetterReq( int index )
   {
      return _LetterReq[index];
   }
    
   /**
    * Gets the Print the notification letter field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Print the notification letter or the specified default value.
    */
   public final boolean getLetterReq( int index, boolean defaultValue )
   {
      return _LetterReq[index] == null ? defaultValue : _LetterReq[index].booleanValue();
   }
    
   /**
    * Gets the array of Print the notification letter fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Print the notification letter values.
    */
   public final Boolean[] getLetterReqArray()
   {
      return _LetterReq;
   }
    
   /**
    * Gets the Sequence Number of RESP Parent/Legal Guardian field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sequence Number of RESP Parent/Legal Guardian or null.
    */
   public final Integer getRESPParentSeq( int index )
   {
      return _RESPParentSeq[index];
   }
    
   /**
    * Gets the Sequence Number of RESP Parent/Legal Guardian field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sequence Number of RESP Parent/Legal Guardian or the specified default value.
    */
   public final int getRESPParentSeq( int index, int defaultValue )
   {
      return _RESPParentSeq[index] == null ? defaultValue : _RESPParentSeq[index].intValue();
   }
    
   /**
    * Gets the array of Sequence Number of RESP Parent/Legal Guardian fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sequence Number of RESP Parent/Legal Guardian values.
    */
   public final Integer[] getRESPParentSeqArray()
   {
      return _RESPParentSeq;
   }
    
   /**
    * Gets the Sequence Number of RESP Designated Institution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sequence Number of RESP Designated Institution or null.
    */
   public final Integer getRESPDesInstSeq( int index )
   {
      return _RESPDesInstSeq[index];
   }
    
   /**
    * Gets the Sequence Number of RESP Designated Institution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sequence Number of RESP Designated Institution or the specified default value.
    */
   public final int getRESPDesInstSeq( int index, int defaultValue )
   {
      return _RESPDesInstSeq[index] == null ? defaultValue : _RESPDesInstSeq[index].intValue();
   }
    
   /**
    * Gets the array of Sequence Number of RESP Designated Institution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sequence Number of RESP Designated Institution values.
    */
   public final Integer[] getRESPDesInstSeqArray()
   {
      return _RESPDesInstSeq;
   }
    
   /**
    * Gets the Flag if contributions reported to HRSDC to attract CESG award. field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag if contributions reported to HRSDC to attract CESG award. or null.
    */
   public final Boolean getGrantRequest( int index )
   {
      return _GrantRequest[index];
   }
    
   /**
    * Gets the Flag if contributions reported to HRSDC to attract CESG award. field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag if contributions reported to HRSDC to attract CESG award. or the specified default value.
    */
   public final boolean getGrantRequest( int index, boolean defaultValue )
   {
      return _GrantRequest[index] == null ? defaultValue : _GrantRequest[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag if contributions reported to HRSDC to attract CESG award. fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag if contributions reported to HRSDC to attract CESG award. values.
    */
   public final Boolean[] getGrantRequestArray()
   {
      return _GrantRequest;
   }
    
   /**
    * Gets the Flag for GrandFatehered plans field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag for GrandFatehered plans or null.
    */
   public final Boolean getTainted( int index )
   {
      return _Tainted[index];
   }
    
   /**
    * Gets the Flag for GrandFatehered plans field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag for GrandFatehered plans or the specified default value.
    */
   public final boolean getTainted( int index, boolean defaultValue )
   {
      return _Tainted[index] == null ? defaultValue : _Tainted[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag for GrandFatehered plans fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag for GrandFatehered plans values.
    */
   public final Boolean[] getTaintedArray()
   {
      return _Tainted;
   }
    
   /**
    * Gets the End date of beneficiary being tainted field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the End date of beneficiary being tainted or null.
    */
   public final Date getTaintEndDate( int index )
   {
      return _TaintEndDate[index];
   }
    
   /**
    * Gets the End date of beneficiary being tainted field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the End date of beneficiary being tainted or the specified default value.
    */
   public final Date getTaintEndDate( int index, Date defaultValue )
   {
      return _TaintEndDate[index] == null ? defaultValue : _TaintEndDate[index];
   }
    
   /**
    * Gets the array of End date of beneficiary being tainted fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of End date of beneficiary being tainted values.
    */
   public final Date[] getTaintEndDateArray()
   {
      return _TaintEndDate;
   }
    
   /**
    * Gets the Primary Care Giver's Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Primary Care Giver's Entity ID or null.
    */
   public final String getRESPPCGId( int index )
   {
      return _RESPPCGId[index];
   }
    
   /**
    * Gets the Primary Care Giver's Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Primary Care Giver's Entity ID or the specified default value.
    */
   public final String getRESPPCGId( int index, String defaultValue )
   {
      return _RESPPCGId[index] == null ? defaultValue : _RESPPCGId[index];
   }
    
   /**
    * Gets the array of Primary Care Giver's Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Primary Care Giver's Entity ID values.
    */
   public final String[] getRESPPCGIdArray()
   {
      return _RESPPCGId;
   }
    
   /**
    * Gets the RESPBenefInfo record Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESPBenefInfo record Id or null.
    */
   public final Integer getRESPBenefInfoRid( int index )
   {
      return _RESPBenefInfoRid[index];
   }
    
   /**
    * Gets the RESPBenefInfo record Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESPBenefInfo record Id or the specified default value.
    */
   public final int getRESPBenefInfoRid( int index, int defaultValue )
   {
      return _RESPBenefInfoRid[index] == null ? defaultValue : _RESPBenefInfoRid[index].intValue();
   }
    
   /**
    * Gets the array of RESPBenefInfo record Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESPBenefInfo record Id values.
    */
   public final Integer[] getRESPBenefInfoRidArray()
   {
      return _RESPBenefInfoRid;
   }
    
   /**
    * Gets the RESPBenefInfo.Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESPBenefInfo.Version or null.
    */
   public final Integer getRESPBenefInfoVer( int index )
   {
      return _RESPBenefInfoVer[index];
   }
    
   /**
    * Gets the RESPBenefInfo.Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESPBenefInfo.Version or the specified default value.
    */
   public final int getRESPBenefInfoVer( int index, int defaultValue )
   {
      return _RESPBenefInfoVer[index] == null ? defaultValue : _RESPBenefInfoVer[index].intValue();
   }
    
   /**
    * Gets the array of RESPBenefInfo.Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESPBenefInfo.Version values.
    */
   public final Integer[] getRESPBenefInfoVerArray()
   {
      return _RESPBenefInfoVer;
   }
    
   /**
    * Gets the Flag if CLB was taken by RESP beneficiary. field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag if CLB was taken by RESP beneficiary. or null.
    */
   public final Boolean getCLBExists( int index )
   {
      return _CLBExists[index];
   }
    
   /**
    * Gets the Flag if CLB was taken by RESP beneficiary. field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag if CLB was taken by RESP beneficiary. or the specified default value.
    */
   public final boolean getCLBExists( int index, boolean defaultValue )
   {
      return _CLBExists[index] == null ? defaultValue : _CLBExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag if CLB was taken by RESP beneficiary. fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag if CLB was taken by RESP beneficiary. values.
    */
   public final Boolean[] getCLBExistsArray()
   {
      return _CLBExists;
   }
    
   /**
    * Gets the Flag if RESP beneficiary has transactions. field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag if RESP beneficiary has transactions. or null.
    */
   public final Boolean getTradeExists( int index )
   {
      return _TradeExists[index];
   }
    
   /**
    * Gets the Flag if RESP beneficiary has transactions. field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag if RESP beneficiary has transactions. or the specified default value.
    */
   public final boolean getTradeExists( int index, boolean defaultValue )
   {
      return _TradeExists[index] == null ? defaultValue : _TradeExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag if RESP beneficiary has transactions. fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag if RESP beneficiary has transactions. values.
    */
   public final Boolean[] getTradeExistsArray()
   {
      return _TradeExists;
   }
    
   /**
    * Gets the Flag if there is an existing Grant request field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag if there is an existing Grant request or null.
    */
   public final Boolean getGrantExists( int index )
   {
      return _GrantExists[index];
   }
    
   /**
    * Gets the Flag if there is an existing Grant request field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag if there is an existing Grant request or the specified default value.
    */
   public final boolean getGrantExists( int index, boolean defaultValue )
   {
      return _GrantExists[index] == null ? defaultValue : _GrantExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag if there is an existing Grant request fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag if there is an existing Grant request values.
    */
   public final Boolean[] getGrantExistsArray()
   {
      return _GrantExists;
   }
    
   /**
    * Gets the Flag if record 400 has been sent. field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag if record 400 has been sent. or null.
    */
   public final Boolean getRec400Sent( int index )
   {
      return _Rec400Sent[index];
   }
    
   /**
    * Gets the Flag if record 400 has been sent. field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag if record 400 has been sent. or the specified default value.
    */
   public final boolean getRec400Sent( int index, boolean defaultValue )
   {
      return _Rec400Sent[index] == null ? defaultValue : _Rec400Sent[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag if record 400 has been sent. fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag if record 400 has been sent. values.
    */
   public final Boolean[] getRec400SentArray()
   {
      return _Rec400Sent;
   }
    
   /**
    * Gets the Date of Birth field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date of Birth or null.
    */
   public final Date getDofB( int index )
   {
      return _DofB[index];
   }
    
   /**
    * Gets the Date of Birth field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Birth or the specified default value.
    */
   public final Date getDofB( int index, Date defaultValue )
   {
      return _DofB[index] == null ? defaultValue : _DofB[index];
   }
    
   /**
    * Gets the array of Date of Birth fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date of Birth values.
    */
   public final Date[] getDofBArray()
   {
      return _DofB;
   }
    
   /**
    * Gets the TaxYear of the last TFSA Amendment filed to Government field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TaxYear of the last TFSA Amendment filed to Government or null.
    */
   public final Integer getTFSALastAmendTaxYear( int index )
   {
      return _TFSALastAmendTaxYear[index];
   }
    
   /**
    * Gets the TaxYear of the last TFSA Amendment filed to Government field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TaxYear of the last TFSA Amendment filed to Government or the specified default value.
    */
   public final int getTFSALastAmendTaxYear( int index, int defaultValue )
   {
      return _TFSALastAmendTaxYear[index] == null ? defaultValue : _TFSALastAmendTaxYear[index].intValue();
   }
    
   /**
    * Gets the array of TaxYear of the last TFSA Amendment filed to Government fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TaxYear of the last TFSA Amendment filed to Government values.
    */
   public final Integer[] getTFSALastAmendTaxYearArray()
   {
      return _TFSALastAmendTaxYear;
   }
    
   /**
    * Gets the Death Settlement Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Death Settlement Date or null.
    */
   public final Date getDeathSettlementDate( int index )
   {
      return _DeathSettlementDate[index];
   }
    
   /**
    * Gets the Death Settlement Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Death Settlement Date or the specified default value.
    */
   public final Date getDeathSettlementDate( int index, Date defaultValue )
   {
      return _DeathSettlementDate[index] == null ? defaultValue : _DeathSettlementDate[index];
   }
    
   /**
    * Gets the array of Death Settlement Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Death Settlement Date values.
    */
   public final Date[] getDeathSettlementDateArray()
   {
      return _DeathSettlementDate;
   }
    
   /**
    * Gets the Loan Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Loan Type or null.
    */
   public final String getLoanType( int index )
   {
      return _LoanType[index];
   }
    
   /**
    * Gets the Loan Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Loan Type or the specified default value.
    */
   public final String getLoanType( int index, String defaultValue )
   {
      return _LoanType[index] == null ? defaultValue : _LoanType[index];
   }
    
   /**
    * Gets the array of Loan Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Loan Type values.
    */
   public final String[] getLoanTypeArray()
   {
      return _LoanType;
   }
    
   /**
    * Gets the Loan Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Loan Number or null.
    */
   public final String getLoanNumber( int index )
   {
      return _LoanNumber[index];
   }
    
   /**
    * Gets the Loan Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Loan Number or the specified default value.
    */
   public final String getLoanNumber( int index, String defaultValue )
   {
      return _LoanNumber[index] == null ? defaultValue : _LoanNumber[index];
   }
    
   /**
    * Gets the array of Loan Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Loan Number values.
    */
   public final String[] getLoanNumberArray()
   {
      return _LoanNumber;
   }
    
   /**
    * Gets the Reference Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reference Code or null.
    */
   public final String getRefCode( int index )
   {
      return _RefCode[index];
   }
    
   /**
    * Gets the Reference Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reference Code or the specified default value.
    */
   public final String getRefCode( int index, String defaultValue )
   {
      return _RefCode[index] == null ? defaultValue : _RefCode[index];
   }
    
   /**
    * Gets the array of Reference Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reference Code values.
    */
   public final String[] getRefCodeArray()
   {
      return _RefCode;
   }
    
   /**
    * Gets the Reference Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reference Type or null.
    */
   public final String getRefType( int index )
   {
      return _RefType[index];
   }
    
   /**
    * Gets the Reference Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reference Type or the specified default value.
    */
   public final String getRefType( int index, String defaultValue )
   {
      return _RefType[index] == null ? defaultValue : _RefType[index];
   }
    
   /**
    * Gets the array of Reference Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reference Type values.
    */
   public final String[] getRefTypeArray()
   {
      return _RefType;
   }
    
   /**
    * Gets the Account Ownership Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Ownership Percentage or null.
    */
   public final String getPercentOwn( int index )
   {
      return _PercentOwn[index];
   }
    
   /**
    * Gets the Account Ownership Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Ownership Percentage or the specified default value.
    */
   public final String getPercentOwn( int index, String defaultValue )
   {
      return _PercentOwn[index] == null ? defaultValue : _PercentOwn[index];
   }
    
   /**
    * Gets the array of Account Ownership Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Ownership Percentage values.
    */
   public final String[] getPercentOwnArray()
   {
      return _PercentOwn;
   }
    
   /**
    * Gets the Associated Entity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Associated Entity or null.
    */
   public final String getAssocEntityID( int index )
   {
      return _AssocEntityID[index];
   }
    
   /**
    * Gets the Associated Entity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associated Entity or the specified default value.
    */
   public final String getAssocEntityID( int index, String defaultValue )
   {
      return _AssocEntityID[index] == null ? defaultValue : _AssocEntityID[index];
   }
    
   /**
    * Gets the array of Associated Entity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Associated Entity values.
    */
   public final String[] getAssocEntityIDArray()
   {
      return _AssocEntityID;
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
      
      _Salutation = resizeArray( _Salutation, _RepeatCount );
      _LastName = resizeArray( _LastName, _RepeatCount );
      _FirstName = resizeArray( _FirstName, _RepeatCount );
      _EntityId = resizeArray( _EntityId, _RepeatCount );
      _EntityType = resizeArray( _EntityType, _RepeatCount );
      _EntityTypeDesc = resizeArray( _EntityTypeDesc, _RepeatCount );
      _SeqNumber = resizeArray( _SeqNumber, _RepeatCount );
      _RelateCode = resizeArray( _RelateCode, _RepeatCount );
      _RelateCodeShip = resizeArray( _RelateCodeShip, _RepeatCount );
      _AddrCode = resizeArray( _AddrCode, _RepeatCount );
      _AuthorizedToTrade = resizeArray( _AuthorizedToTrade, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _BenPercentage = resizeArray( _BenPercentage, _RepeatCount );
      _Irrevocable = resizeArray( _Irrevocable, _RepeatCount );
      _DispositionCode = resizeArray( _DispositionCode, _RepeatCount );
      _DispostitionDesc = resizeArray( _DispostitionDesc, _RepeatCount );
      _JointType = resizeArray( _JointType, _RepeatCount );
      _JointTypeDesc = resizeArray( _JointTypeDesc, _RepeatCount );
      _EscrowFund = resizeArray( _EscrowFund, _RepeatCount );
      _EscrowClass = resizeArray( _EscrowClass, _RepeatCount );
      _AmtAssigned = resizeArray( _AmtAssigned, _RepeatCount );
      _AmountType = resizeArray( _AmountType, _RepeatCount );
      _AmountTypeDesc = resizeArray( _AmountTypeDesc, _RepeatCount );
      _ReasonCode = resizeArray( _ReasonCode, _RepeatCount );
      _ReasonDesc = resizeArray( _ReasonDesc, _RepeatCount );
      _EscrowDeff = resizeArray( _EscrowDeff, _RepeatCount );
      _EscrowStopDate = resizeArray( _EscrowStopDate, _RepeatCount );
      _AcctEntVer = resizeArray( _AcctEntVer, _RepeatCount );
      _AcctEntRid = resizeArray( _AcctEntRid, _RepeatCount );
      _AcctEntBenefVer = resizeArray( _AcctEntBenefVer, _RepeatCount );
      _AcctEntBenefRid = resizeArray( _AcctEntBenefRid, _RepeatCount );
      _AcctEntJointVer = resizeArray( _AcctEntJointVer, _RepeatCount );
      _AcctEntJointRid = resizeArray( _AcctEntJointRid, _RepeatCount );
      _AssignDetlVer = resizeArray( _AssignDetlVer, _RepeatCount );
      _AssignDetlRid = resizeArray( _AssignDetlRid, _RepeatCount );
      _HRDCRelateCode = resizeArray( _HRDCRelateCode, _RepeatCount );
      _HRDCRelateDesc = resizeArray( _HRDCRelateDesc, _RepeatCount );
      _RESPReasonCode = resizeArray( _RESPReasonCode, _RepeatCount );
      _RESPReasonDesc = resizeArray( _RESPReasonDesc, _RepeatCount );
      _TaxJurisCode = resizeArray( _TaxJurisCode, _RepeatCount );
      _TaxJurisDesc = resizeArray( _TaxJurisDesc, _RepeatCount );
      _LetterDate = resizeArray( _LetterDate, _RepeatCount );
      _LetterReq = resizeArray( _LetterReq, _RepeatCount );
      _RESPParentSeq = resizeArray( _RESPParentSeq, _RepeatCount );
      _RESPDesInstSeq = resizeArray( _RESPDesInstSeq, _RepeatCount );
      _GrantRequest = resizeArray( _GrantRequest, _RepeatCount );
      _Tainted = resizeArray( _Tainted, _RepeatCount );
      _TaintEndDate = resizeArray( _TaintEndDate, _RepeatCount );
      _RESPPCGId = resizeArray( _RESPPCGId, _RepeatCount );
      _RESPBenefInfoRid = resizeArray( _RESPBenefInfoRid, _RepeatCount );
      _RESPBenefInfoVer = resizeArray( _RESPBenefInfoVer, _RepeatCount );
      _CLBExists = resizeArray( _CLBExists, _RepeatCount );
      _TradeExists = resizeArray( _TradeExists, _RepeatCount );
      _GrantExists = resizeArray( _GrantExists, _RepeatCount );
      _Rec400Sent = resizeArray( _Rec400Sent, _RepeatCount );
      _DofB = resizeArray( _DofB, _RepeatCount );
      _TFSALastAmendTaxYear = resizeArray( _TFSALastAmendTaxYear, _RepeatCount );
      _DeathSettlementDate = resizeArray( _DeathSettlementDate, _RepeatCount );
      _LoanType = resizeArray( _LoanType, _RepeatCount );
      _LoanNumber = resizeArray( _LoanNumber, _RepeatCount );
      _RefCode = resizeArray( _RefCode, _RepeatCount );
      _RefType = resizeArray( _RefType, _RepeatCount );
      _PercentOwn = resizeArray( _PercentOwn, _RepeatCount );
      _AssocEntityID = resizeArray( _AssocEntityID, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _Salutation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SeqNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RelateCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RelateCodeShip[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AuthorizedToTrade[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenPercentage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Irrevocable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DispositionCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DispostitionDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _JointType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _JointTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EscrowFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EscrowClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmtAssigned[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReasonCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReasonDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EscrowDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EscrowStopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AcctEntVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctEntRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctEntBenefVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctEntBenefRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctEntJointVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctEntJointRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AssignDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AssignDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _HRDCRelateCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HRDCRelateDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPReasonCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPReasonDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxJurisCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxJurisDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LetterDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LetterReq[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RESPParentSeq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RESPDesInstSeq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _GrantRequest[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Tainted[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaintEndDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RESPPCGId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPBenefInfoRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RESPBenefInfoVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CLBExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TradeExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GrantExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Rec400Sent[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DofB[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TFSALastAmendTaxYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DeathSettlementDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LoanType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LoanNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RefCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RefType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PercentOwn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AssocEntityID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
