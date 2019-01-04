
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Seg Fund Contract Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/SegFndContInq.doc">SegFndContInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SegFndContInqView extends IFastView implements Serializable
{

   /**
    * ShrGroup of Account Master member variable.
    */
   private String _AcctGroup = null;
   
   /**
    * AccType of Account Master member variable.
    */
   private String _AcctType = null;
   
   /**
    * The last effective date of Account Historical member variable.
    */
   private Date _FirstEffective = null;
   
   /**
    * Status of Account Master member variable.
    */
   private String _AcctStatus = null;
   
   /**
    * Tax type of Account Master member variable.
    */
   private String _TaxType = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * UserName member array.
    */
   private String[] _Username = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Contract Type member array.
    */
   private String[] _ContractType = null;
   
   /**
    * Contract Type Id member array.
    */
   private Integer[] _ContractTypeId = null;
   
   /**
    * ModUser member array.
    */
   private String[] _ModUser = null;
   
   /**
    * PolicyNum member array.
    */
   private String[] _PolicyNum = null;
   
   /**
    * ModDate member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * ContractTerm member array.
    */
   private Integer[] _ContractTerm = null;
   
   /**
    * ContractTermDesc member array.
    */
   private String[] _ContractTermDesc = null;
   
   /**
    * IssueDate member array.
    */
   private Date[] _IssueDate = null;
   
   /**
    * AnnivMonth member array.
    */
   private Integer[] _AnnivMonth = null;
   
   /**
    * AnnivDay member array.
    */
   private Integer[] _AnnivDay = null;
   
   /**
    * LastResetDate member array.
    */
   private Date[] _LastResetDate = null;
   
   /**
    * Province member array.
    */
   private String[] _Province = null;
   
   /**
    * ProvinceName member array.
    */
   private String[] _ProvinceName = null;
   
   /**
    * AgeBasedOn member array.
    */
   private String[] _AgeBasedOn = null;
   
   /**
    * AgeBasedOnDesc member array.
    */
   private String[] _AgeBasedOnDesc = null;
   
   /**
    * LegalMaturityDate member array.
    */
   private Date[] _LegalMaturityDate = null;
   
   /**
    * StatusCode member array.
    */
   private String[] _StatusCode = null;
   
   /**
    * StatusDesc member array.
    */
   private String[] _StatusDesc = null;
   
   /**
    * BailMaturityDate member array.
    */
   private Date[] _BailMaturityDate = null;
   
   /**
    * CotAcctVer member array.
    */
   private Integer[] _CotAcctVer = null;
   
   /**
    * CotAcctRid member array.
    */
   private Integer[] _CotAcctRid = null;
   
   /**
    * Policy Year member array.
    */
   private Integer[] _PolicyYear = null;
   
   /**
    * Contract Maturity Date member array.
    */
   private Date[] _ContMaturityDate = null;
   
   /**
    * Closing Decade Start Date member array.
    */
   private Date[] _CDStartDate = null;
   
   /**
    * Flag indicating if Seg transaction exists member array.
    */
   private Boolean[] _SegTransExist = null;
   
   /**
    * Reduction Age Date member array.
    */
   private Date[] _RedAgeDate = null;
   
   /**
    * indicates kinds of problems with guarantees member array.
    */
   private String[] _SuspectGuarType = null;
   
   /**
    * indicates if guarantee match trans units member array.
    */
   private Boolean[] _ReqGuarUnitAdjust = null;
   
   /**
    * indicates if User Defined Mat date can be modified member array.
    */
   private Boolean[] _ModPerm = null;
   
   /**
    * GWO Contract Anniversary Date member array.
    */
   private Date[] _GWOCotAnnivDate = null;
   
   /**
    * Settlement Date member array.
    */
   private Date[] _SettlementDate = null;
   
   /**
    * Contract version of Cot Account Contract member array.
    */
   private Integer[] _ContractVer = null;
   
   /**
    * Default Mature Date Base on member array.
    */
   private String[] _ContractMatBasedOn = null;
   
   /**
    * User Mature Date of Cot Account Contract member array.
    */
   private Date[] _RefMatDate = null;
   
   /**
    * LWA Rate Age Used of Cot Account Contract member array.
    */
   private Integer[] _LWAAgeUsed = null;
   
   /**
    * LWA Start Date of Cot Account Contract member array.
    */
   private Date[] _LWAStartDate = null;
   
   /**
    * LWA Rate Applicable of Cot Accoun Contract member array.
    */
   private String[] _LWARateApplied = null;
   
   /**
    * Requires Guarantee Unit Adjust of Cot Account Contract member array.
    */
   private Boolean[] _ReqUnitAdj = null;
   
   /**
    * Maturity ID member array.
    */
   private String[] _MaturityID = null;
   
   /**
    * Closing Period Term member array.
    */
   private Integer[] _ClsPerTerm = null;
   
   /**
    * LWA Election Date member array.
    */
   private Date[] _LWAElectDate = null;
   
   /**
    * Contract Maturity Policy Year member array.
    */
   private Integer[] _CMPolicyYear = null;
   
   /**
    * Contract Maturity Policy Term member array.
    */
   private Integer[] _CMPolicyTerm = null;
   
   /**
    * Contract Maturity Maturity Date member array.
    */
   private Date[] _CMMaturityDate = null;
   
   /**
    * Flag indicating if guarantee fee are applicabble member array.
    */
   private Boolean[] _GuaranteeFeeAppl = null;
   
   /**
    * Guarantee Payment Option member array.
    */
   private String[] _GuaranteePayOption = null;
   
   /**
    * Flag to indicate if elected or not member array.
    */
   private Boolean[] _IsElected = null;
   
   /**
    * TOExistAfterPreElectReset member array.
    */
   private Boolean[] _TOExistAfterPreElectReset = null;
   

   /**
    * Constructs the SegFndContInqView object.
    * 
    */
   public SegFndContInqView()
   {
      super ( new SegFndContInqRequest() );
   }

   /**
    * Constructs the SegFndContInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SegFndContInqView( String hostEncoding )
   {
      super ( new SegFndContInqRequest( hostEncoding ) );
   }

   /**
    * Gets the SegFndContInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SegFndContInqRequest object.
    */
   public final SegFndContInqRequest getRequest()
   {
      return (SegFndContInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the ShrGroup of Account Master field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ShrGroup of Account Master or null.
    */
   public final String getAcctGroup()
   {
      return _AcctGroup;
   }
	
   /**
    * Gets the ShrGroup of Account Master field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ShrGroup of Account Master or the specified default value.
    */
   public final String getAcctGroup( String defaultValue )
   {
      return _AcctGroup == null ? defaultValue : _AcctGroup;
   }
                  
   /**
    * Gets the AccType of Account Master field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AccType of Account Master or null.
    */
   public final String getAcctType()
   {
      return _AcctType;
   }
	
   /**
    * Gets the AccType of Account Master field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AccType of Account Master or the specified default value.
    */
   public final String getAcctType( String defaultValue )
   {
      return _AcctType == null ? defaultValue : _AcctType;
   }
                  
   /**
    * Gets the The last effective date of Account Historical field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the The last effective date of Account Historical or null.
    */
   public final Date getFirstEffective()
   {
      return _FirstEffective;
   }
	
   /**
    * Gets the The last effective date of Account Historical field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the The last effective date of Account Historical or the specified default value.
    */
   public final Date getFirstEffective( Date defaultValue )
   {
      return _FirstEffective == null ? defaultValue : _FirstEffective;
   }
                  
   /**
    * Gets the Status of Account Master field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Status of Account Master or null.
    */
   public final String getAcctStatus()
   {
      return _AcctStatus;
   }
	
   /**
    * Gets the Status of Account Master field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Status of Account Master or the specified default value.
    */
   public final String getAcctStatus( String defaultValue )
   {
      return _AcctStatus == null ? defaultValue : _AcctStatus;
   }
                  
   /**
    * Gets the Tax type of Account Master field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax type of Account Master or null.
    */
   public final String getTaxType()
   {
      return _TaxType;
   }
	
   /**
    * Gets the Tax type of Account Master field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax type of Account Master or the specified default value.
    */
   public final String getTaxType( String defaultValue )
   {
      return _TaxType == null ? defaultValue : _TaxType;
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
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UserName or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UserName or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of UserName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UserName values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Date or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Date or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Date values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Contract Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Type or null.
    */
   public final String getContractType( int index )
   {
      return _ContractType[index];
   }
    
   /**
    * Gets the Contract Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Type or the specified default value.
    */
   public final String getContractType( int index, String defaultValue )
   {
      return _ContractType[index] == null ? defaultValue : _ContractType[index];
   }
    
   /**
    * Gets the array of Contract Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Type values.
    */
   public final String[] getContractTypeArray()
   {
      return _ContractType;
   }
    
   /**
    * Gets the Contract Type Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Type Id or null.
    */
   public final Integer getContractTypeId( int index )
   {
      return _ContractTypeId[index];
   }
    
   /**
    * Gets the Contract Type Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Type Id or the specified default value.
    */
   public final int getContractTypeId( int index, int defaultValue )
   {
      return _ContractTypeId[index] == null ? defaultValue : _ContractTypeId[index].intValue();
   }
    
   /**
    * Gets the array of Contract Type Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Type Id values.
    */
   public final Integer[] getContractTypeIdArray()
   {
      return _ContractTypeId;
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
    * Gets the PolicyNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PolicyNum or null.
    */
   public final String getPolicyNum( int index )
   {
      return _PolicyNum[index];
   }
    
   /**
    * Gets the PolicyNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PolicyNum or the specified default value.
    */
   public final String getPolicyNum( int index, String defaultValue )
   {
      return _PolicyNum[index] == null ? defaultValue : _PolicyNum[index];
   }
    
   /**
    * Gets the array of PolicyNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PolicyNum values.
    */
   public final String[] getPolicyNumArray()
   {
      return _PolicyNum;
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
    * Gets the ContractTerm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ContractTerm or null.
    */
   public final Integer getContractTerm( int index )
   {
      return _ContractTerm[index];
   }
    
   /**
    * Gets the ContractTerm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ContractTerm or the specified default value.
    */
   public final int getContractTerm( int index, int defaultValue )
   {
      return _ContractTerm[index] == null ? defaultValue : _ContractTerm[index].intValue();
   }
    
   /**
    * Gets the array of ContractTerm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ContractTerm values.
    */
   public final Integer[] getContractTermArray()
   {
      return _ContractTerm;
   }
    
   /**
    * Gets the ContractTermDesc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ContractTermDesc or null.
    */
   public final String getContractTermDesc( int index )
   {
      return _ContractTermDesc[index];
   }
    
   /**
    * Gets the ContractTermDesc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ContractTermDesc or the specified default value.
    */
   public final String getContractTermDesc( int index, String defaultValue )
   {
      return _ContractTermDesc[index] == null ? defaultValue : _ContractTermDesc[index];
   }
    
   /**
    * Gets the array of ContractTermDesc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ContractTermDesc values.
    */
   public final String[] getContractTermDescArray()
   {
      return _ContractTermDesc;
   }
    
   /**
    * Gets the IssueDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IssueDate or null.
    */
   public final Date getIssueDate( int index )
   {
      return _IssueDate[index];
   }
    
   /**
    * Gets the IssueDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IssueDate or the specified default value.
    */
   public final Date getIssueDate( int index, Date defaultValue )
   {
      return _IssueDate[index] == null ? defaultValue : _IssueDate[index];
   }
    
   /**
    * Gets the array of IssueDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IssueDate values.
    */
   public final Date[] getIssueDateArray()
   {
      return _IssueDate;
   }
    
   /**
    * Gets the AnnivMonth field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AnnivMonth or null.
    */
   public final Integer getAnnivMonth( int index )
   {
      return _AnnivMonth[index];
   }
    
   /**
    * Gets the AnnivMonth field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AnnivMonth or the specified default value.
    */
   public final int getAnnivMonth( int index, int defaultValue )
   {
      return _AnnivMonth[index] == null ? defaultValue : _AnnivMonth[index].intValue();
   }
    
   /**
    * Gets the array of AnnivMonth fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AnnivMonth values.
    */
   public final Integer[] getAnnivMonthArray()
   {
      return _AnnivMonth;
   }
    
   /**
    * Gets the AnnivDay field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AnnivDay or null.
    */
   public final Integer getAnnivDay( int index )
   {
      return _AnnivDay[index];
   }
    
   /**
    * Gets the AnnivDay field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AnnivDay or the specified default value.
    */
   public final int getAnnivDay( int index, int defaultValue )
   {
      return _AnnivDay[index] == null ? defaultValue : _AnnivDay[index].intValue();
   }
    
   /**
    * Gets the array of AnnivDay fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AnnivDay values.
    */
   public final Integer[] getAnnivDayArray()
   {
      return _AnnivDay;
   }
    
   /**
    * Gets the LastResetDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LastResetDate or null.
    */
   public final Date getLastResetDate( int index )
   {
      return _LastResetDate[index];
   }
    
   /**
    * Gets the LastResetDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LastResetDate or the specified default value.
    */
   public final Date getLastResetDate( int index, Date defaultValue )
   {
      return _LastResetDate[index] == null ? defaultValue : _LastResetDate[index];
   }
    
   /**
    * Gets the array of LastResetDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LastResetDate values.
    */
   public final Date[] getLastResetDateArray()
   {
      return _LastResetDate;
   }
    
   /**
    * Gets the Province field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Province or null.
    */
   public final String getProvince( int index )
   {
      return _Province[index];
   }
    
   /**
    * Gets the Province field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Province or the specified default value.
    */
   public final String getProvince( int index, String defaultValue )
   {
      return _Province[index] == null ? defaultValue : _Province[index];
   }
    
   /**
    * Gets the array of Province fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Province values.
    */
   public final String[] getProvinceArray()
   {
      return _Province;
   }
    
   /**
    * Gets the ProvinceName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProvinceName or null.
    */
   public final String getProvinceName( int index )
   {
      return _ProvinceName[index];
   }
    
   /**
    * Gets the ProvinceName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProvinceName or the specified default value.
    */
   public final String getProvinceName( int index, String defaultValue )
   {
      return _ProvinceName[index] == null ? defaultValue : _ProvinceName[index];
   }
    
   /**
    * Gets the array of ProvinceName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProvinceName values.
    */
   public final String[] getProvinceNameArray()
   {
      return _ProvinceName;
   }
    
   /**
    * Gets the AgeBasedOn field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AgeBasedOn or null.
    */
   public final String getAgeBasedOn( int index )
   {
      return _AgeBasedOn[index];
   }
    
   /**
    * Gets the AgeBasedOn field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AgeBasedOn or the specified default value.
    */
   public final String getAgeBasedOn( int index, String defaultValue )
   {
      return _AgeBasedOn[index] == null ? defaultValue : _AgeBasedOn[index];
   }
    
   /**
    * Gets the array of AgeBasedOn fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AgeBasedOn values.
    */
   public final String[] getAgeBasedOnArray()
   {
      return _AgeBasedOn;
   }
    
   /**
    * Gets the AgeBasedOnDesc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AgeBasedOnDesc or null.
    */
   public final String getAgeBasedOnDesc( int index )
   {
      return _AgeBasedOnDesc[index];
   }
    
   /**
    * Gets the AgeBasedOnDesc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AgeBasedOnDesc or the specified default value.
    */
   public final String getAgeBasedOnDesc( int index, String defaultValue )
   {
      return _AgeBasedOnDesc[index] == null ? defaultValue : _AgeBasedOnDesc[index];
   }
    
   /**
    * Gets the array of AgeBasedOnDesc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AgeBasedOnDesc values.
    */
   public final String[] getAgeBasedOnDescArray()
   {
      return _AgeBasedOnDesc;
   }
    
   /**
    * Gets the LegalMaturityDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LegalMaturityDate or null.
    */
   public final Date getLegalMaturityDate( int index )
   {
      return _LegalMaturityDate[index];
   }
    
   /**
    * Gets the LegalMaturityDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LegalMaturityDate or the specified default value.
    */
   public final Date getLegalMaturityDate( int index, Date defaultValue )
   {
      return _LegalMaturityDate[index] == null ? defaultValue : _LegalMaturityDate[index];
   }
    
   /**
    * Gets the array of LegalMaturityDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LegalMaturityDate values.
    */
   public final Date[] getLegalMaturityDateArray()
   {
      return _LegalMaturityDate;
   }
    
   /**
    * Gets the StatusCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StatusCode or null.
    */
   public final String getStatusCode( int index )
   {
      return _StatusCode[index];
   }
    
   /**
    * Gets the StatusCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StatusCode or the specified default value.
    */
   public final String getStatusCode( int index, String defaultValue )
   {
      return _StatusCode[index] == null ? defaultValue : _StatusCode[index];
   }
    
   /**
    * Gets the array of StatusCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StatusCode values.
    */
   public final String[] getStatusCodeArray()
   {
      return _StatusCode;
   }
    
   /**
    * Gets the StatusDesc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StatusDesc or null.
    */
   public final String getStatusDesc( int index )
   {
      return _StatusDesc[index];
   }
    
   /**
    * Gets the StatusDesc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StatusDesc or the specified default value.
    */
   public final String getStatusDesc( int index, String defaultValue )
   {
      return _StatusDesc[index] == null ? defaultValue : _StatusDesc[index];
   }
    
   /**
    * Gets the array of StatusDesc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StatusDesc values.
    */
   public final String[] getStatusDescArray()
   {
      return _StatusDesc;
   }
    
   /**
    * Gets the BailMaturityDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BailMaturityDate or null.
    */
   public final Date getBailMaturityDate( int index )
   {
      return _BailMaturityDate[index];
   }
    
   /**
    * Gets the BailMaturityDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BailMaturityDate or the specified default value.
    */
   public final Date getBailMaturityDate( int index, Date defaultValue )
   {
      return _BailMaturityDate[index] == null ? defaultValue : _BailMaturityDate[index];
   }
    
   /**
    * Gets the array of BailMaturityDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BailMaturityDate values.
    */
   public final Date[] getBailMaturityDateArray()
   {
      return _BailMaturityDate;
   }
    
   /**
    * Gets the CotAcctVer field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CotAcctVer or null.
    */
   public final Integer getCotAcctVer( int index )
   {
      return _CotAcctVer[index];
   }
    
   /**
    * Gets the CotAcctVer field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CotAcctVer or the specified default value.
    */
   public final int getCotAcctVer( int index, int defaultValue )
   {
      return _CotAcctVer[index] == null ? defaultValue : _CotAcctVer[index].intValue();
   }
    
   /**
    * Gets the array of CotAcctVer fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CotAcctVer values.
    */
   public final Integer[] getCotAcctVerArray()
   {
      return _CotAcctVer;
   }
    
   /**
    * Gets the CotAcctRid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CotAcctRid or null.
    */
   public final Integer getCotAcctRid( int index )
   {
      return _CotAcctRid[index];
   }
    
   /**
    * Gets the CotAcctRid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CotAcctRid or the specified default value.
    */
   public final int getCotAcctRid( int index, int defaultValue )
   {
      return _CotAcctRid[index] == null ? defaultValue : _CotAcctRid[index].intValue();
   }
    
   /**
    * Gets the array of CotAcctRid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CotAcctRid values.
    */
   public final Integer[] getCotAcctRidArray()
   {
      return _CotAcctRid;
   }
    
   /**
    * Gets the Policy Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Policy Year or null.
    */
   public final Integer getPolicyYear( int index )
   {
      return _PolicyYear[index];
   }
    
   /**
    * Gets the Policy Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Policy Year or the specified default value.
    */
   public final int getPolicyYear( int index, int defaultValue )
   {
      return _PolicyYear[index] == null ? defaultValue : _PolicyYear[index].intValue();
   }
    
   /**
    * Gets the array of Policy Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Policy Year values.
    */
   public final Integer[] getPolicyYearArray()
   {
      return _PolicyYear;
   }
    
   /**
    * Gets the Contract Maturity Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Maturity Date or null.
    */
   public final Date getContMaturityDate( int index )
   {
      return _ContMaturityDate[index];
   }
    
   /**
    * Gets the Contract Maturity Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Maturity Date or the specified default value.
    */
   public final Date getContMaturityDate( int index, Date defaultValue )
   {
      return _ContMaturityDate[index] == null ? defaultValue : _ContMaturityDate[index];
   }
    
   /**
    * Gets the array of Contract Maturity Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Maturity Date values.
    */
   public final Date[] getContMaturityDateArray()
   {
      return _ContMaturityDate;
   }
    
   /**
    * Gets the Closing Decade Start Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Closing Decade Start Date or null.
    */
   public final Date getCDStartDate( int index )
   {
      return _CDStartDate[index];
   }
    
   /**
    * Gets the Closing Decade Start Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Closing Decade Start Date or the specified default value.
    */
   public final Date getCDStartDate( int index, Date defaultValue )
   {
      return _CDStartDate[index] == null ? defaultValue : _CDStartDate[index];
   }
    
   /**
    * Gets the array of Closing Decade Start Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Closing Decade Start Date values.
    */
   public final Date[] getCDStartDateArray()
   {
      return _CDStartDate;
   }
    
   /**
    * Gets the Flag indicating if Seg transaction exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if Seg transaction exists or null.
    */
   public final Boolean getSegTransExist( int index )
   {
      return _SegTransExist[index];
   }
    
   /**
    * Gets the Flag indicating if Seg transaction exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Seg transaction exists or the specified default value.
    */
   public final boolean getSegTransExist( int index, boolean defaultValue )
   {
      return _SegTransExist[index] == null ? defaultValue : _SegTransExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if Seg transaction exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if Seg transaction exists values.
    */
   public final Boolean[] getSegTransExistArray()
   {
      return _SegTransExist;
   }
    
   /**
    * Gets the Reduction Age Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reduction Age Date or null.
    */
   public final Date getRedAgeDate( int index )
   {
      return _RedAgeDate[index];
   }
    
   /**
    * Gets the Reduction Age Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reduction Age Date or the specified default value.
    */
   public final Date getRedAgeDate( int index, Date defaultValue )
   {
      return _RedAgeDate[index] == null ? defaultValue : _RedAgeDate[index];
   }
    
   /**
    * Gets the array of Reduction Age Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reduction Age Date values.
    */
   public final Date[] getRedAgeDateArray()
   {
      return _RedAgeDate;
   }
    
   /**
    * Gets the indicates kinds of problems with guarantees field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the indicates kinds of problems with guarantees or null.
    */
   public final String getSuspectGuarType( int index )
   {
      return _SuspectGuarType[index];
   }
    
   /**
    * Gets the indicates kinds of problems with guarantees field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the indicates kinds of problems with guarantees or the specified default value.
    */
   public final String getSuspectGuarType( int index, String defaultValue )
   {
      return _SuspectGuarType[index] == null ? defaultValue : _SuspectGuarType[index];
   }
    
   /**
    * Gets the array of indicates kinds of problems with guarantees fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of indicates kinds of problems with guarantees values.
    */
   public final String[] getSuspectGuarTypeArray()
   {
      return _SuspectGuarType;
   }
    
   /**
    * Gets the indicates if guarantee match trans units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the indicates if guarantee match trans units or null.
    */
   public final Boolean getReqGuarUnitAdjust( int index )
   {
      return _ReqGuarUnitAdjust[index];
   }
    
   /**
    * Gets the indicates if guarantee match trans units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the indicates if guarantee match trans units or the specified default value.
    */
   public final boolean getReqGuarUnitAdjust( int index, boolean defaultValue )
   {
      return _ReqGuarUnitAdjust[index] == null ? defaultValue : _ReqGuarUnitAdjust[index].booleanValue();
   }
    
   /**
    * Gets the array of indicates if guarantee match trans units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of indicates if guarantee match trans units values.
    */
   public final Boolean[] getReqGuarUnitAdjustArray()
   {
      return _ReqGuarUnitAdjust;
   }
    
   /**
    * Gets the indicates if User Defined Mat date can be modified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the indicates if User Defined Mat date can be modified or null.
    */
   public final Boolean getModPerm( int index )
   {
      return _ModPerm[index];
   }
    
   /**
    * Gets the indicates if User Defined Mat date can be modified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the indicates if User Defined Mat date can be modified or the specified default value.
    */
   public final boolean getModPerm( int index, boolean defaultValue )
   {
      return _ModPerm[index] == null ? defaultValue : _ModPerm[index].booleanValue();
   }
    
   /**
    * Gets the array of indicates if User Defined Mat date can be modified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of indicates if User Defined Mat date can be modified values.
    */
   public final Boolean[] getModPermArray()
   {
      return _ModPerm;
   }
    
   /**
    * Gets the GWO Contract Anniversary Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GWO Contract Anniversary Date or null.
    */
   public final Date getGWOCotAnnivDate( int index )
   {
      return _GWOCotAnnivDate[index];
   }
    
   /**
    * Gets the GWO Contract Anniversary Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GWO Contract Anniversary Date or the specified default value.
    */
   public final Date getGWOCotAnnivDate( int index, Date defaultValue )
   {
      return _GWOCotAnnivDate[index] == null ? defaultValue : _GWOCotAnnivDate[index];
   }
    
   /**
    * Gets the array of GWO Contract Anniversary Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GWO Contract Anniversary Date values.
    */
   public final Date[] getGWOCotAnnivDateArray()
   {
      return _GWOCotAnnivDate;
   }
    
   /**
    * Gets the Settlement Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Date or null.
    */
   public final Date getSettlementDate( int index )
   {
      return _SettlementDate[index];
   }
    
   /**
    * Gets the Settlement Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Date or the specified default value.
    */
   public final Date getSettlementDate( int index, Date defaultValue )
   {
      return _SettlementDate[index] == null ? defaultValue : _SettlementDate[index];
   }
    
   /**
    * Gets the array of Settlement Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Date values.
    */
   public final Date[] getSettlementDateArray()
   {
      return _SettlementDate;
   }
    
   /**
    * Gets the Contract version of Cot Account Contract field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract version of Cot Account Contract or null.
    */
   public final Integer getContractVer( int index )
   {
      return _ContractVer[index];
   }
    
   /**
    * Gets the Contract version of Cot Account Contract field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract version of Cot Account Contract or the specified default value.
    */
   public final int getContractVer( int index, int defaultValue )
   {
      return _ContractVer[index] == null ? defaultValue : _ContractVer[index].intValue();
   }
    
   /**
    * Gets the array of Contract version of Cot Account Contract fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract version of Cot Account Contract values.
    */
   public final Integer[] getContractVerArray()
   {
      return _ContractVer;
   }
    
   /**
    * Gets the Default Mature Date Base on field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Default Mature Date Base on or null.
    */
   public final String getContractMatBasedOn( int index )
   {
      return _ContractMatBasedOn[index];
   }
    
   /**
    * Gets the Default Mature Date Base on field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Mature Date Base on or the specified default value.
    */
   public final String getContractMatBasedOn( int index, String defaultValue )
   {
      return _ContractMatBasedOn[index] == null ? defaultValue : _ContractMatBasedOn[index];
   }
    
   /**
    * Gets the array of Default Mature Date Base on fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Default Mature Date Base on values.
    */
   public final String[] getContractMatBasedOnArray()
   {
      return _ContractMatBasedOn;
   }
    
   /**
    * Gets the User Mature Date of Cot Account Contract field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Mature Date of Cot Account Contract or null.
    */
   public final Date getRefMatDate( int index )
   {
      return _RefMatDate[index];
   }
    
   /**
    * Gets the User Mature Date of Cot Account Contract field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Mature Date of Cot Account Contract or the specified default value.
    */
   public final Date getRefMatDate( int index, Date defaultValue )
   {
      return _RefMatDate[index] == null ? defaultValue : _RefMatDate[index];
   }
    
   /**
    * Gets the array of User Mature Date of Cot Account Contract fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Mature Date of Cot Account Contract values.
    */
   public final Date[] getRefMatDateArray()
   {
      return _RefMatDate;
   }
    
   /**
    * Gets the LWA Rate Age Used of Cot Account Contract field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LWA Rate Age Used of Cot Account Contract or null.
    */
   public final Integer getLWAAgeUsed( int index )
   {
      return _LWAAgeUsed[index];
   }
    
   /**
    * Gets the LWA Rate Age Used of Cot Account Contract field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LWA Rate Age Used of Cot Account Contract or the specified default value.
    */
   public final int getLWAAgeUsed( int index, int defaultValue )
   {
      return _LWAAgeUsed[index] == null ? defaultValue : _LWAAgeUsed[index].intValue();
   }
    
   /**
    * Gets the array of LWA Rate Age Used of Cot Account Contract fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LWA Rate Age Used of Cot Account Contract values.
    */
   public final Integer[] getLWAAgeUsedArray()
   {
      return _LWAAgeUsed;
   }
    
   /**
    * Gets the LWA Start Date of Cot Account Contract field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LWA Start Date of Cot Account Contract or null.
    */
   public final Date getLWAStartDate( int index )
   {
      return _LWAStartDate[index];
   }
    
   /**
    * Gets the LWA Start Date of Cot Account Contract field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LWA Start Date of Cot Account Contract or the specified default value.
    */
   public final Date getLWAStartDate( int index, Date defaultValue )
   {
      return _LWAStartDate[index] == null ? defaultValue : _LWAStartDate[index];
   }
    
   /**
    * Gets the array of LWA Start Date of Cot Account Contract fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LWA Start Date of Cot Account Contract values.
    */
   public final Date[] getLWAStartDateArray()
   {
      return _LWAStartDate;
   }
    
   /**
    * Gets the LWA Rate Applicable of Cot Accoun Contract field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LWA Rate Applicable of Cot Accoun Contract or null.
    */
   public final String getLWARateApplied( int index )
   {
      return _LWARateApplied[index];
   }
    
   /**
    * Gets the LWA Rate Applicable of Cot Accoun Contract field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LWA Rate Applicable of Cot Accoun Contract or the specified default value.
    */
   public final String getLWARateApplied( int index, String defaultValue )
   {
      return _LWARateApplied[index] == null ? defaultValue : _LWARateApplied[index];
   }
    
   /**
    * Gets the array of LWA Rate Applicable of Cot Accoun Contract fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LWA Rate Applicable of Cot Accoun Contract values.
    */
   public final String[] getLWARateAppliedArray()
   {
      return _LWARateApplied;
   }
    
   /**
    * Gets the Requires Guarantee Unit Adjust of Cot Account Contract field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Requires Guarantee Unit Adjust of Cot Account Contract or null.
    */
   public final Boolean getReqUnitAdj( int index )
   {
      return _ReqUnitAdj[index];
   }
    
   /**
    * Gets the Requires Guarantee Unit Adjust of Cot Account Contract field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Requires Guarantee Unit Adjust of Cot Account Contract or the specified default value.
    */
   public final boolean getReqUnitAdj( int index, boolean defaultValue )
   {
      return _ReqUnitAdj[index] == null ? defaultValue : _ReqUnitAdj[index].booleanValue();
   }
    
   /**
    * Gets the array of Requires Guarantee Unit Adjust of Cot Account Contract fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Requires Guarantee Unit Adjust of Cot Account Contract values.
    */
   public final Boolean[] getReqUnitAdjArray()
   {
      return _ReqUnitAdj;
   }
    
   /**
    * Gets the Maturity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maturity ID or null.
    */
   public final String getMaturityID( int index )
   {
      return _MaturityID[index];
   }
    
   /**
    * Gets the Maturity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity ID or the specified default value.
    */
   public final String getMaturityID( int index, String defaultValue )
   {
      return _MaturityID[index] == null ? defaultValue : _MaturityID[index];
   }
    
   /**
    * Gets the array of Maturity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maturity ID values.
    */
   public final String[] getMaturityIDArray()
   {
      return _MaturityID;
   }
    
   /**
    * Gets the Closing Period Term field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Closing Period Term or null.
    */
   public final Integer getClsPerTerm( int index )
   {
      return _ClsPerTerm[index];
   }
    
   /**
    * Gets the Closing Period Term field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Closing Period Term or the specified default value.
    */
   public final int getClsPerTerm( int index, int defaultValue )
   {
      return _ClsPerTerm[index] == null ? defaultValue : _ClsPerTerm[index].intValue();
   }
    
   /**
    * Gets the array of Closing Period Term fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Closing Period Term values.
    */
   public final Integer[] getClsPerTermArray()
   {
      return _ClsPerTerm;
   }
    
   /**
    * Gets the LWA Election Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LWA Election Date or null.
    */
   public final Date getLWAElectDate( int index )
   {
      return _LWAElectDate[index];
   }
    
   /**
    * Gets the LWA Election Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LWA Election Date or the specified default value.
    */
   public final Date getLWAElectDate( int index, Date defaultValue )
   {
      return _LWAElectDate[index] == null ? defaultValue : _LWAElectDate[index];
   }
    
   /**
    * Gets the array of LWA Election Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LWA Election Date values.
    */
   public final Date[] getLWAElectDateArray()
   {
      return _LWAElectDate;
   }
    
   /**
    * Gets the Contract Maturity Policy Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Maturity Policy Year or null.
    */
   public final Integer getCMPolicyYear( int index )
   {
      return _CMPolicyYear[index];
   }
    
   /**
    * Gets the Contract Maturity Policy Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Maturity Policy Year or the specified default value.
    */
   public final int getCMPolicyYear( int index, int defaultValue )
   {
      return _CMPolicyYear[index] == null ? defaultValue : _CMPolicyYear[index].intValue();
   }
    
   /**
    * Gets the array of Contract Maturity Policy Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Maturity Policy Year values.
    */
   public final Integer[] getCMPolicyYearArray()
   {
      return _CMPolicyYear;
   }
    
   /**
    * Gets the Contract Maturity Policy Term field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Maturity Policy Term or null.
    */
   public final Integer getCMPolicyTerm( int index )
   {
      return _CMPolicyTerm[index];
   }
    
   /**
    * Gets the Contract Maturity Policy Term field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Maturity Policy Term or the specified default value.
    */
   public final int getCMPolicyTerm( int index, int defaultValue )
   {
      return _CMPolicyTerm[index] == null ? defaultValue : _CMPolicyTerm[index].intValue();
   }
    
   /**
    * Gets the array of Contract Maturity Policy Term fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Maturity Policy Term values.
    */
   public final Integer[] getCMPolicyTermArray()
   {
      return _CMPolicyTerm;
   }
    
   /**
    * Gets the Contract Maturity Maturity Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Maturity Maturity Date or null.
    */
   public final Date getCMMaturityDate( int index )
   {
      return _CMMaturityDate[index];
   }
    
   /**
    * Gets the Contract Maturity Maturity Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Maturity Maturity Date or the specified default value.
    */
   public final Date getCMMaturityDate( int index, Date defaultValue )
   {
      return _CMMaturityDate[index] == null ? defaultValue : _CMMaturityDate[index];
   }
    
   /**
    * Gets the array of Contract Maturity Maturity Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Maturity Maturity Date values.
    */
   public final Date[] getCMMaturityDateArray()
   {
      return _CMMaturityDate;
   }
    
   /**
    * Gets the Flag indicating if guarantee fee are applicabble field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if guarantee fee are applicabble or null.
    */
   public final Boolean getGuaranteeFeeAppl( int index )
   {
      return _GuaranteeFeeAppl[index];
   }
    
   /**
    * Gets the Flag indicating if guarantee fee are applicabble field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if guarantee fee are applicabble or the specified default value.
    */
   public final boolean getGuaranteeFeeAppl( int index, boolean defaultValue )
   {
      return _GuaranteeFeeAppl[index] == null ? defaultValue : _GuaranteeFeeAppl[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if guarantee fee are applicabble fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if guarantee fee are applicabble values.
    */
   public final Boolean[] getGuaranteeFeeApplArray()
   {
      return _GuaranteeFeeAppl;
   }
    
   /**
    * Gets the Guarantee Payment Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Payment Option or null.
    */
   public final String getGuaranteePayOption( int index )
   {
      return _GuaranteePayOption[index];
   }
    
   /**
    * Gets the Guarantee Payment Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Payment Option or the specified default value.
    */
   public final String getGuaranteePayOption( int index, String defaultValue )
   {
      return _GuaranteePayOption[index] == null ? defaultValue : _GuaranteePayOption[index];
   }
    
   /**
    * Gets the array of Guarantee Payment Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Payment Option values.
    */
   public final String[] getGuaranteePayOptionArray()
   {
      return _GuaranteePayOption;
   }
    
   /**
    * Gets the Flag to indicate if elected or not field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag to indicate if elected or not or null.
    */
   public final Boolean getIsElected( int index )
   {
      return _IsElected[index];
   }
    
   /**
    * Gets the Flag to indicate if elected or not field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag to indicate if elected or not or the specified default value.
    */
   public final boolean getIsElected( int index, boolean defaultValue )
   {
      return _IsElected[index] == null ? defaultValue : _IsElected[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag to indicate if elected or not fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag to indicate if elected or not values.
    */
   public final Boolean[] getIsElectedArray()
   {
      return _IsElected;
   }
    
   /**
    * Gets the TOExistAfterPreElectReset field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TOExistAfterPreElectReset or null.
    */
   public final Boolean getTOExistAfterPreElectReset( int index )
   {
      return _TOExistAfterPreElectReset[index];
   }
    
   /**
    * Gets the TOExistAfterPreElectReset field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TOExistAfterPreElectReset or the specified default value.
    */
   public final boolean getTOExistAfterPreElectReset( int index, boolean defaultValue )
   {
      return _TOExistAfterPreElectReset[index] == null ? defaultValue : _TOExistAfterPreElectReset[index].booleanValue();
   }
    
   /**
    * Gets the array of TOExistAfterPreElectReset fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TOExistAfterPreElectReset values.
    */
   public final Boolean[] getTOExistAfterPreElectResetArray()
   {
      return _TOExistAfterPreElectReset;
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
      _AcctGroup = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctType = responseBuffer.decodeString(responseBuffer.getNextField());
      _FirstEffective = responseBuffer.decodeDate(responseBuffer.getNextField());
      _AcctStatus = responseBuffer.decodeString(responseBuffer.getNextField());
      _TaxType = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ContractType = resizeArray( _ContractType, _RepeatCount );
      _ContractTypeId = resizeArray( _ContractTypeId, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _PolicyNum = resizeArray( _PolicyNum, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ContractTerm = resizeArray( _ContractTerm, _RepeatCount );
      _ContractTermDesc = resizeArray( _ContractTermDesc, _RepeatCount );
      _IssueDate = resizeArray( _IssueDate, _RepeatCount );
      _AnnivMonth = resizeArray( _AnnivMonth, _RepeatCount );
      _AnnivDay = resizeArray( _AnnivDay, _RepeatCount );
      _LastResetDate = resizeArray( _LastResetDate, _RepeatCount );
      _Province = resizeArray( _Province, _RepeatCount );
      _ProvinceName = resizeArray( _ProvinceName, _RepeatCount );
      _AgeBasedOn = resizeArray( _AgeBasedOn, _RepeatCount );
      _AgeBasedOnDesc = resizeArray( _AgeBasedOnDesc, _RepeatCount );
      _LegalMaturityDate = resizeArray( _LegalMaturityDate, _RepeatCount );
      _StatusCode = resizeArray( _StatusCode, _RepeatCount );
      _StatusDesc = resizeArray( _StatusDesc, _RepeatCount );
      _BailMaturityDate = resizeArray( _BailMaturityDate, _RepeatCount );
      _CotAcctVer = resizeArray( _CotAcctVer, _RepeatCount );
      _CotAcctRid = resizeArray( _CotAcctRid, _RepeatCount );
      _PolicyYear = resizeArray( _PolicyYear, _RepeatCount );
      _ContMaturityDate = resizeArray( _ContMaturityDate, _RepeatCount );
      _CDStartDate = resizeArray( _CDStartDate, _RepeatCount );
      _SegTransExist = resizeArray( _SegTransExist, _RepeatCount );
      _RedAgeDate = resizeArray( _RedAgeDate, _RepeatCount );
      _SuspectGuarType = resizeArray( _SuspectGuarType, _RepeatCount );
      _ReqGuarUnitAdjust = resizeArray( _ReqGuarUnitAdjust, _RepeatCount );
      _ModPerm = resizeArray( _ModPerm, _RepeatCount );
      _GWOCotAnnivDate = resizeArray( _GWOCotAnnivDate, _RepeatCount );
      _SettlementDate = resizeArray( _SettlementDate, _RepeatCount );
      _ContractVer = resizeArray( _ContractVer, _RepeatCount );
      _ContractMatBasedOn = resizeArray( _ContractMatBasedOn, _RepeatCount );
      _RefMatDate = resizeArray( _RefMatDate, _RepeatCount );
      _LWAAgeUsed = resizeArray( _LWAAgeUsed, _RepeatCount );
      _LWAStartDate = resizeArray( _LWAStartDate, _RepeatCount );
      _LWARateApplied = resizeArray( _LWARateApplied, _RepeatCount );
      _ReqUnitAdj = resizeArray( _ReqUnitAdj, _RepeatCount );
      _MaturityID = resizeArray( _MaturityID, _RepeatCount );
      _ClsPerTerm = resizeArray( _ClsPerTerm, _RepeatCount );
      _LWAElectDate = resizeArray( _LWAElectDate, _RepeatCount );
      _CMPolicyYear = resizeArray( _CMPolicyYear, _RepeatCount );
      _CMPolicyTerm = resizeArray( _CMPolicyTerm, _RepeatCount );
      _CMMaturityDate = resizeArray( _CMMaturityDate, _RepeatCount );
      _GuaranteeFeeAppl = resizeArray( _GuaranteeFeeAppl, _RepeatCount );
      _GuaranteePayOption = resizeArray( _GuaranteePayOption, _RepeatCount );
      _IsElected = resizeArray( _IsElected, _RepeatCount );
      _TOExistAfterPreElectReset = resizeArray( _TOExistAfterPreElectReset, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ContractType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContractTypeId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PolicyNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ContractTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ContractTermDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IssueDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AnnivMonth[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AnnivDay[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _LastResetDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Province[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvinceName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AgeBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AgeBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LegalMaturityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StatusCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StatusDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BailMaturityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _CotAcctVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CotAcctRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PolicyYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ContMaturityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _CDStartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SegTransExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RedAgeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SuspectGuarType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReqGuarUnitAdjust[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ModPerm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GWOCotAnnivDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SettlementDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ContractVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ContractMatBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RefMatDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LWAAgeUsed[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _LWAStartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _LWARateApplied[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReqUnitAdj[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MaturityID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClsPerTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _LWAElectDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _CMPolicyYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CMPolicyTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CMMaturityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GuaranteeFeeAppl[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GuaranteePayOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IsElected[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TOExistAfterPreElectReset[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
