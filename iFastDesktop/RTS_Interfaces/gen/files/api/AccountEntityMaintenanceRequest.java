// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Entity Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/AccountEntityMaintenance.doc">AccountEntityMaintenance.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountEntityMaintenanceRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
            
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Entity ID member array.
    */
   private String[] _EntityId = new String[25];
            
   /**
    * Entity Type member array.
    */
   private String[] _EntityType = new String[25];
            
   /**
    * Sequence Number member array.
    */
   private Integer[] _SeqNumber = new Integer[25];
            
   /**
    * Relationship Code member array.
    */
   private String[] _RelateCode = new String[25];
            
   /**
    * Default Address Code member array.
    */
   private String[] _AddrCode = new String[25];
            
   /**
    * Authorized to Trade member array.
    */
   private Boolean[] _AuthorizedToTrade = new Boolean[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Account Entity Table Version NUm member array.
    */
   private Integer[] _AcctEntVer = new Integer[25];
            
   /**
    * Benefit Percentage member array.
    */
   private String[] _BenPercentage = new String[25];
            
   /**
    * Benefit Irrevocable member array.
    */
   private Boolean[] _Irrevocable = new Boolean[25];
            
   /**
    * Benef Entity Table Version Num member array.
    */
   private Integer[] _AcctEntBenefVer = new Integer[25];
            
   /**
    * Joint Disposition Code member array.
    */
   private String[] _DispositionCode = new String[25];
            
   /**
    * Joint Type member array.
    */
   private String[] _JointType = new String[25];
            
   /**
    * Joint Entity Table Version Num member array.
    */
   private Integer[] _AcctEntJointVer = new Integer[25];
            
   /**
    * Escrow Fund Code member array.
    */
   private String[] _EscrowFund = new String[25];
            
   /**
    * Escrow Class Code member array.
    */
   private String[] _EscrowClass = new String[25];
            
   /**
    * Assigned Amount member array.
    */
   private String[] _AmtAssigned = new String[25];
            
   /**
    * Amount Type (Units or Dollar) member array.
    */
   private String[] _AmountType = new String[25];
            
   /**
    * Reason Code for Escrow member array.
    */
   private String[] _ReasonCode = new String[25];
            
   /**
    * Escrow Effective Date member array.
    */
   private Date[] _EscrowDeff = new Date[25];
            
   /**
    * Escrow Stop Date member array.
    */
   private Date[] _EscrowStopDate = new Date[25];
            
   /**
    * Assign Detail Table Version Num member array.
    */
   private Integer[] _AssignDetlVer = new Integer[25];
            
   /**
    * Acct Entity Record Id member array.
    */
   private Integer[] _AcctEntRid = new Integer[25];
            
   /**
    * Beneficiary Entity Record Id member array.
    */
   private Integer[] _AcctEntBenefRid = new Integer[25];
            
   /**
    * Joint Entity Record Id member array.
    */
   private Integer[] _AcctEntJointRid = new Integer[25];
            
   /**
    * Assign Detail Record Id member array.
    */
   private Integer[] _AssignDetlRid = new Integer[25];
            
   /**
    * Sequence Number of RESP Parent/Legal Guardian member array.
    */
   private Integer[] _RESPParentSeq = new Integer[25];
            
   /**
    * Sequence Number of RESP Designated Institution member array.
    */
   private Integer[] _RESPDesInstSeq = new Integer[25];
            
   /**
    * HRDC Relationship member array.
    */
   private String[] _HRDCRelateCode = new String[25];
            
   /**
    * Tax Jurisdiction member array.
    */
   private String[] _TaxJurisCode = new String[25];
            
   /**
    * Reason Code member array.
    */
   private String[] _RESPReasonCode = new String[25];
            
   /**
    * Flag if Letter of Notification was generated member array.
    */
   private Boolean[] _LetterReq = new Boolean[25];
            
   /**
    * Flag if contributions reported to HRSDC to attract CESG award. member array.
    */
   private Boolean[] _GrantRequest = new Boolean[25];
            
   /**
    * Primary Care Giver's Entity ID member array.
    */
   private String[] _RESPPCGId = new String[25];
            
   /**
    * RESPBenefInfo record Id member array.
    */
   private Integer[] _RESPBenefInfoRid = new Integer[25];
            
   /**
    * RESPBenefInfo.Version member array.
    */
   private Integer[] _RESPBenefInfoVer = new Integer[25];
            
   /**
    * Flag if records 511 should be created member array.
    */
   private Boolean[] _CreateRec511 = new Boolean[25];
            
   /**
    * Cut-off date to report contributions thorugh 511 records. member array.
    */
   private Date[] _Rec511CutOffDate = new Date[25];
            
   /**
    * Death Settlement Date member array.
    */
   private Date[] _DeathSettlementDate = new Date[25];
            
   /**
    * Loan Type member array.
    */
   private String[] _LoanType = new String[25];
            
   /**
    * Loan Number member array.
    */
   private String[] _LoanNumber = new String[25];
            
   /**
    * Reference Code member array.
    */
   private String[] _RefCode = new String[25];
            
   /**
    * Reference Type member array.
    */
   private String[] _RefType = new String[25];
            
   /**
    * Account Ownership Percentage member array.
    */
   private String[] _PercentOwn = new String[25];
            
   /**
    * Associated Entity member array.
    */
   private String[] _AssocEntityID = new String[25];
            

   /**
    * Constructs the AccountEntityMaintenanceRequest object.
    * 
    */
   AccountEntityMaintenanceRequest()
   {
      super ( 77 );
   }

   /**
    * Constructs the AccountEntityMaintenanceRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AccountEntityMaintenanceRequest( String hostEncoding )
   {
      super ( 77, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User Id field for the request.
    * 
    * @param value  Value that the User Id will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the Language Code field for the request.
    * 
    * @param value  Value that the Language Code will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company Id field for the request.
    * 
    * @param value  Value that the Company Id will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Entity ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity ID will be set to.
    */
   public final void setEntityId( int index, String value )
   {
      assertUnsent();
      _EntityId[index] = value;
   }
	
   /**
    * Sets the Entity Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity Type will be set to.
    */
   public final void setEntityType( int index, String value )
   {
      assertUnsent();
      _EntityType[index] = value;
   }
	
   /**
    * Sets the Sequence Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Sequence Number will be set to.
    */
   public final void setSeqNumber( int index, Integer value )
   {
      assertUnsent();
      _SeqNumber[index] = value;
   }
	
   /**
    * Sets the Relationship Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Relationship Code will be set to.
    */
   public final void setRelateCode( int index, String value )
   {
      assertUnsent();
      _RelateCode[index] = value;
   }
	
   /**
    * Sets the Default Address Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Default Address Code will be set to.
    */
   public final void setAddrCode( int index, String value )
   {
      assertUnsent();
      _AddrCode[index] = value;
   }
	
   /**
    * Sets the Authorized to Trade field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Authorized to Trade will be set to.
    */
   public final void setAuthorizedToTrade( int index, Boolean value )
   {
      assertUnsent();
      _AuthorizedToTrade[index] = value;
   }
	
   /**
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _EffectiveDate[index] = value;
   }
	
   /**
    * Sets the Account Entity Table Version NUm field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Account Entity Table Version NUm will be set to.
    */
   public final void setAcctEntVer( int index, Integer value )
   {
      assertUnsent();
      _AcctEntVer[index] = value;
   }
	
   /**
    * Sets the Benefit Percentage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Benefit Percentage will be set to.
    */
   public final void setBenPercentage( int index, String value )
   {
      assertUnsent();
      _BenPercentage[index] = value;
   }
	
   /**
    * Sets the Benefit Irrevocable field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Benefit Irrevocable will be set to.
    */
   public final void setIrrevocable( int index, Boolean value )
   {
      assertUnsent();
      _Irrevocable[index] = value;
   }
	
   /**
    * Sets the Benef Entity Table Version Num field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Benef Entity Table Version Num will be set to.
    */
   public final void setAcctEntBenefVer( int index, Integer value )
   {
      assertUnsent();
      _AcctEntBenefVer[index] = value;
   }
	
   /**
    * Sets the Joint Disposition Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Joint Disposition Code will be set to.
    */
   public final void setDispositionCode( int index, String value )
   {
      assertUnsent();
      _DispositionCode[index] = value;
   }
	
   /**
    * Sets the Joint Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Joint Type will be set to.
    */
   public final void setJointType( int index, String value )
   {
      assertUnsent();
      _JointType[index] = value;
   }
	
   /**
    * Sets the Joint Entity Table Version Num field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Joint Entity Table Version Num will be set to.
    */
   public final void setAcctEntJointVer( int index, Integer value )
   {
      assertUnsent();
      _AcctEntJointVer[index] = value;
   }
	
   /**
    * Sets the Escrow Fund Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Escrow Fund Code will be set to.
    */
   public final void setEscrowFund( int index, String value )
   {
      assertUnsent();
      _EscrowFund[index] = value;
   }
	
   /**
    * Sets the Escrow Class Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Escrow Class Code will be set to.
    */
   public final void setEscrowClass( int index, String value )
   {
      assertUnsent();
      _EscrowClass[index] = value;
   }
	
   /**
    * Sets the Assigned Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Assigned Amount will be set to.
    */
   public final void setAmtAssigned( int index, String value )
   {
      assertUnsent();
      _AmtAssigned[index] = value;
   }
	
   /**
    * Sets the Amount Type (Units or Dollar) field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Amount Type (Units or Dollar) will be set to.
    */
   public final void setAmountType( int index, String value )
   {
      assertUnsent();
      _AmountType[index] = value;
   }
	
   /**
    * Sets the Reason Code for Escrow field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reason Code for Escrow will be set to.
    */
   public final void setReasonCode( int index, String value )
   {
      assertUnsent();
      _ReasonCode[index] = value;
   }
	
   /**
    * Sets the Escrow Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Escrow Effective Date will be set to.
    */
   public final void setEscrowDeff( int index, Date value )
   {
      assertUnsent();
      _EscrowDeff[index] = value;
   }
	
   /**
    * Sets the Escrow Stop Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Escrow Stop Date will be set to.
    */
   public final void setEscrowStopDate( int index, Date value )
   {
      assertUnsent();
      _EscrowStopDate[index] = value;
   }
	
   /**
    * Sets the Assign Detail Table Version Num field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Assign Detail Table Version Num will be set to.
    */
   public final void setAssignDetlVer( int index, Integer value )
   {
      assertUnsent();
      _AssignDetlVer[index] = value;
   }
	
   /**
    * Sets the Acct Entity Record Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Acct Entity Record Id will be set to.
    */
   public final void setAcctEntRid( int index, Integer value )
   {
      assertUnsent();
      _AcctEntRid[index] = value;
   }
	
   /**
    * Sets the Beneficiary Entity Record Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Beneficiary Entity Record Id will be set to.
    */
   public final void setAcctEntBenefRid( int index, Integer value )
   {
      assertUnsent();
      _AcctEntBenefRid[index] = value;
   }
	
   /**
    * Sets the Joint Entity Record Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Joint Entity Record Id will be set to.
    */
   public final void setAcctEntJointRid( int index, Integer value )
   {
      assertUnsent();
      _AcctEntJointRid[index] = value;
   }
	
   /**
    * Sets the Assign Detail Record Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Assign Detail Record Id will be set to.
    */
   public final void setAssignDetlRid( int index, Integer value )
   {
      assertUnsent();
      _AssignDetlRid[index] = value;
   }
	
   /**
    * Sets the Sequence Number of RESP Parent/Legal Guardian field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Sequence Number of RESP Parent/Legal Guardian will be set to.
    */
   public final void setRESPParentSeq( int index, Integer value )
   {
      assertUnsent();
      _RESPParentSeq[index] = value;
   }
	
   /**
    * Sets the Sequence Number of RESP Designated Institution field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Sequence Number of RESP Designated Institution will be set to.
    */
   public final void setRESPDesInstSeq( int index, Integer value )
   {
      assertUnsent();
      _RESPDesInstSeq[index] = value;
   }
	
   /**
    * Sets the HRDC Relationship field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the HRDC Relationship will be set to.
    */
   public final void setHRDCRelateCode( int index, String value )
   {
      assertUnsent();
      _HRDCRelateCode[index] = value;
   }
	
   /**
    * Sets the Tax Jurisdiction field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Tax Jurisdiction will be set to.
    */
   public final void setTaxJurisCode( int index, String value )
   {
      assertUnsent();
      _TaxJurisCode[index] = value;
   }
	
   /**
    * Sets the Reason Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reason Code will be set to.
    */
   public final void setRESPReasonCode( int index, String value )
   {
      assertUnsent();
      _RESPReasonCode[index] = value;
   }
	
   /**
    * Sets the Flag if Letter of Notification was generated field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Flag if Letter of Notification was generated will be set to.
    */
   public final void setLetterReq( int index, Boolean value )
   {
      assertUnsent();
      _LetterReq[index] = value;
   }
	
   /**
    * Sets the Flag if contributions reported to HRSDC to attract CESG award. field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Flag if contributions reported to HRSDC to attract CESG award. will be set to.
    */
   public final void setGrantRequest( int index, Boolean value )
   {
      assertUnsent();
      _GrantRequest[index] = value;
   }
	
   /**
    * Sets the Primary Care Giver's Entity ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Primary Care Giver's Entity ID will be set to.
    */
   public final void setRESPPCGId( int index, String value )
   {
      assertUnsent();
      _RESPPCGId[index] = value;
   }
	
   /**
    * Sets the RESPBenefInfo record Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESPBenefInfo record Id will be set to.
    */
   public final void setRESPBenefInfoRid( int index, Integer value )
   {
      assertUnsent();
      _RESPBenefInfoRid[index] = value;
   }
	
   /**
    * Sets the RESPBenefInfo.Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESPBenefInfo.Version will be set to.
    */
   public final void setRESPBenefInfoVer( int index, Integer value )
   {
      assertUnsent();
      _RESPBenefInfoVer[index] = value;
   }
	
   /**
    * Sets the Flag if records 511 should be created field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Flag if records 511 should be created will be set to.
    */
   public final void setCreateRec511( int index, Boolean value )
   {
      assertUnsent();
      _CreateRec511[index] = value;
   }
	
   /**
    * Sets the Cut-off date to report contributions thorugh 511 records. field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Cut-off date to report contributions thorugh 511 records. will be set to.
    */
   public final void setRec511CutOffDate( int index, Date value )
   {
      assertUnsent();
      _Rec511CutOffDate[index] = value;
   }
	
   /**
    * Sets the Death Settlement Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Death Settlement Date will be set to.
    */
   public final void setDeathSettlementDate( int index, Date value )
   {
      assertUnsent();
      _DeathSettlementDate[index] = value;
   }
	
   /**
    * Sets the Loan Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Loan Type will be set to.
    */
   public final void setLoanType( int index, String value )
   {
      assertUnsent();
      _LoanType[index] = value;
   }
	
   /**
    * Sets the Loan Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Loan Number will be set to.
    */
   public final void setLoanNumber( int index, String value )
   {
      assertUnsent();
      _LoanNumber[index] = value;
   }
	
   /**
    * Sets the Reference Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reference Code will be set to.
    */
   public final void setRefCode( int index, String value )
   {
      assertUnsent();
      _RefCode[index] = value;
   }
	
   /**
    * Sets the Reference Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reference Type will be set to.
    */
   public final void setRefType( int index, String value )
   {
      assertUnsent();
      _RefType[index] = value;
   }
	
   /**
    * Sets the Account Ownership Percentage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Account Ownership Percentage will be set to.
    */
   public final void setPercentOwn( int index, String value )
   {
      assertUnsent();
      _PercentOwn[index] = value;
   }
	
   /**
    * Sets the Associated Entity field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Associated Entity will be set to.
    */
   public final void setAssocEntityID( int index, String value )
   {
      assertUnsent();
      _AssocEntityID[index] = value;
   }
	
   /**
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _AccountNum );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _EntityId[x] );
         requestBuffer.appendField( _EntityType[x] );
         requestBuffer.appendField( _SeqNumber[x] );
         requestBuffer.appendField( _RelateCode[x] );
         requestBuffer.appendField( _AddrCode[x] );
         requestBuffer.appendField( _AuthorizedToTrade[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _AcctEntVer[x] );
         requestBuffer.appendField( _BenPercentage[x] );
         requestBuffer.appendField( _Irrevocable[x] );
         requestBuffer.appendField( _AcctEntBenefVer[x] );
         requestBuffer.appendField( _DispositionCode[x] );
         requestBuffer.appendField( _JointType[x] );
         requestBuffer.appendField( _AcctEntJointVer[x] );
         requestBuffer.appendField( _EscrowFund[x] );
         requestBuffer.appendField( _EscrowClass[x] );
         requestBuffer.appendField( _AmtAssigned[x] );
         requestBuffer.appendField( _AmountType[x] );
         requestBuffer.appendField( _ReasonCode[x] );
         requestBuffer.appendField( _EscrowDeff[x] );
         requestBuffer.appendField( _EscrowStopDate[x] );
         requestBuffer.appendField( _AssignDetlVer[x] );
         requestBuffer.appendField( _AcctEntRid[x] );
         requestBuffer.appendField( _AcctEntBenefRid[x] );
         requestBuffer.appendField( _AcctEntJointRid[x] );
         requestBuffer.appendField( _AssignDetlRid[x] );
         requestBuffer.appendField( _RESPParentSeq[x] );
         requestBuffer.appendField( _RESPDesInstSeq[x] );
         requestBuffer.appendField( _HRDCRelateCode[x] );
         requestBuffer.appendField( _TaxJurisCode[x] );
         requestBuffer.appendField( _RESPReasonCode[x] );
         requestBuffer.appendField( _LetterReq[x] );
         requestBuffer.appendField( _GrantRequest[x] );
         requestBuffer.appendField( _RESPPCGId[x] );
         requestBuffer.appendField( _RESPBenefInfoRid[x] );
         requestBuffer.appendField( _RESPBenefInfoVer[x] );
         requestBuffer.appendField( _CreateRec511[x] );
         requestBuffer.appendField( _Rec511CutOffDate[x] );
         requestBuffer.appendField( _DeathSettlementDate[x] );
         requestBuffer.appendField( _LoanType[x] );
         requestBuffer.appendField( _LoanNumber[x] );
         requestBuffer.appendField( _RefCode[x] );
         requestBuffer.appendField( _RefType[x] );
         requestBuffer.appendField( _PercentOwn[x] );
         requestBuffer.appendField( _AssocEntityID[x] );
      }
   }

}

