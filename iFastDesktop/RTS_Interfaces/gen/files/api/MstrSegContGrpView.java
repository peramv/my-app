
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Master Seg Contract/Group Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/MstrSegContGrp.doc">MstrSegContGrp.doc</A>.
 * 
 * @author RTS Generated
 */
public class MstrSegContGrpView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Group Code member array.
    */
   private String[] _GroupCode = null;
   
   /**
    * Contract Type member array.
    */
   private String[] _ContractType = null;
   
   /**
    * Contract Type Id member array.
    */
   private Integer[] _ContractTypeId = null;
   
   /**
    * Miniimum Term member array.
    */
   private Integer[] _MinTerm = null;
   
   /**
    * Maximum Term member array.
    */
   private Integer[] _MaxTerm = null;
   
   /**
    * Anniv Date Type member array.
    */
   private String[] _AnnivDateType = null;
   
   /**
    * Contract Maturity Date Based On member array.
    */
   private String[] _ContMatDateBasedOn = null;
   
   /**
    * Deposit Maturity Date Based On member array.
    */
   private String[] _MatDateBasedOn = null;
   
   /**
    * Flag indicating if Contract is GWO contract. member array.
    */
   private Boolean[] _IsGWOContract = null;
   
   /**
    * Contract Version member array.
    */
   private Integer[] _ContractVer = null;
   
   /**
    * Flag indicating that the version is a default member array.
    */
   private Boolean[] _DefaultVer = null;
   
   /**
    * Closing Period term member array.
    */
   private Integer[] _ClsPerTerm = null;
   
   /**
    * Indicating if new contract can be setup member array.
    */
   private Boolean[] _NewContrAllowed = null;
   
   /**
    * Maximum Age Restriction member array.
    */
   private Integer[] _MaxAge = null;
   
   /**
    * comma delimited list of Tax Types member array.
    */
   private String[] _TaxType = null;
   
   /**
    * comma delimited list of pension jurisdictions member array.
    */
   private String[] _PensionJuris = null;
   
   /**
    * LinkedCont attribute storing linked contract type member array.
    */
   private String[] _LinkedContract = null;
   
   /**
    * MinAge member array.
    */
   private String[] _MinAge = null;
   
   /**
    * DfCMDBaseOn member array.
    */
   private String[] _DfCMDBaseOn = null;
   
   /**
    * NewMoney member array.
    */
   private String[] _NewMoney = null;
   
   /**
    * TaxApl member array.
    */
   private String[] _TaxApl = null;
   
   /**
    * TopUpClass member array.
    */
   private String[] _TopUpClass = null;
   
   /**
    * TopUpFund member array.
    */
   private String[] _TopUpFund = null;
   
   /**
    * Flag that indicates if NMCR contract member array.
    */
   private Boolean[] _NMCRContract = null;
   
   /**
    * RGrFnd member array.
    */
   private String[] _RGrFnd = null;
   
   /**
    * RGrCls member array.
    */
   private String[] _RGrCls = null;
   

   /**
    * Constructs the MstrSegContGrpView object.
    * 
    */
   public MstrSegContGrpView()
   {
      super ( new MstrSegContGrpRequest() );
   }

   /**
    * Constructs the MstrSegContGrpView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public MstrSegContGrpView( String hostEncoding )
   {
      super ( new MstrSegContGrpRequest( hostEncoding ) );
   }

   /**
    * Gets the MstrSegContGrpRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The MstrSegContGrpRequest object.
    */
   public final MstrSegContGrpRequest getRequest()
   {
      return (MstrSegContGrpRequest)getIFastRequest();
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
    * Gets the Group Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Group Code or null.
    */
   public final String getGroupCode( int index )
   {
      return _GroupCode[index];
   }
    
   /**
    * Gets the Group Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Code or the specified default value.
    */
   public final String getGroupCode( int index, String defaultValue )
   {
      return _GroupCode[index] == null ? defaultValue : _GroupCode[index];
   }
    
   /**
    * Gets the array of Group Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Group Code values.
    */
   public final String[] getGroupCodeArray()
   {
      return _GroupCode;
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
    * Gets the Miniimum Term field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Miniimum Term or null.
    */
   public final Integer getMinTerm( int index )
   {
      return _MinTerm[index];
   }
    
   /**
    * Gets the Miniimum Term field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Miniimum Term or the specified default value.
    */
   public final int getMinTerm( int index, int defaultValue )
   {
      return _MinTerm[index] == null ? defaultValue : _MinTerm[index].intValue();
   }
    
   /**
    * Gets the array of Miniimum Term fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Miniimum Term values.
    */
   public final Integer[] getMinTermArray()
   {
      return _MinTerm;
   }
    
   /**
    * Gets the Maximum Term field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maximum Term or null.
    */
   public final Integer getMaxTerm( int index )
   {
      return _MaxTerm[index];
   }
    
   /**
    * Gets the Maximum Term field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Term or the specified default value.
    */
   public final int getMaxTerm( int index, int defaultValue )
   {
      return _MaxTerm[index] == null ? defaultValue : _MaxTerm[index].intValue();
   }
    
   /**
    * Gets the array of Maximum Term fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maximum Term values.
    */
   public final Integer[] getMaxTermArray()
   {
      return _MaxTerm;
   }
    
   /**
    * Gets the Anniv Date Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Anniv Date Type or null.
    */
   public final String getAnnivDateType( int index )
   {
      return _AnnivDateType[index];
   }
    
   /**
    * Gets the Anniv Date Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Anniv Date Type or the specified default value.
    */
   public final String getAnnivDateType( int index, String defaultValue )
   {
      return _AnnivDateType[index] == null ? defaultValue : _AnnivDateType[index];
   }
    
   /**
    * Gets the array of Anniv Date Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Anniv Date Type values.
    */
   public final String[] getAnnivDateTypeArray()
   {
      return _AnnivDateType;
   }
    
   /**
    * Gets the Contract Maturity Date Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Maturity Date Based On or null.
    */
   public final String getContMatDateBasedOn( int index )
   {
      return _ContMatDateBasedOn[index];
   }
    
   /**
    * Gets the Contract Maturity Date Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Maturity Date Based On or the specified default value.
    */
   public final String getContMatDateBasedOn( int index, String defaultValue )
   {
      return _ContMatDateBasedOn[index] == null ? defaultValue : _ContMatDateBasedOn[index];
   }
    
   /**
    * Gets the array of Contract Maturity Date Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Maturity Date Based On values.
    */
   public final String[] getContMatDateBasedOnArray()
   {
      return _ContMatDateBasedOn;
   }
    
   /**
    * Gets the Deposit Maturity Date Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Deposit Maturity Date Based On or null.
    */
   public final String getMatDateBasedOn( int index )
   {
      return _MatDateBasedOn[index];
   }
    
   /**
    * Gets the Deposit Maturity Date Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deposit Maturity Date Based On or the specified default value.
    */
   public final String getMatDateBasedOn( int index, String defaultValue )
   {
      return _MatDateBasedOn[index] == null ? defaultValue : _MatDateBasedOn[index];
   }
    
   /**
    * Gets the array of Deposit Maturity Date Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Deposit Maturity Date Based On values.
    */
   public final String[] getMatDateBasedOnArray()
   {
      return _MatDateBasedOn;
   }
    
   /**
    * Gets the Flag indicating if Contract is GWO contract. field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if Contract is GWO contract. or null.
    */
   public final Boolean getIsGWOContract( int index )
   {
      return _IsGWOContract[index];
   }
    
   /**
    * Gets the Flag indicating if Contract is GWO contract. field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Contract is GWO contract. or the specified default value.
    */
   public final boolean getIsGWOContract( int index, boolean defaultValue )
   {
      return _IsGWOContract[index] == null ? defaultValue : _IsGWOContract[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if Contract is GWO contract. fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if Contract is GWO contract. values.
    */
   public final Boolean[] getIsGWOContractArray()
   {
      return _IsGWOContract;
   }
    
   /**
    * Gets the Contract Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Version or null.
    */
   public final Integer getContractVer( int index )
   {
      return _ContractVer[index];
   }
    
   /**
    * Gets the Contract Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Version or the specified default value.
    */
   public final int getContractVer( int index, int defaultValue )
   {
      return _ContractVer[index] == null ? defaultValue : _ContractVer[index].intValue();
   }
    
   /**
    * Gets the array of Contract Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Version values.
    */
   public final Integer[] getContractVerArray()
   {
      return _ContractVer;
   }
    
   /**
    * Gets the Flag indicating that the version is a default field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating that the version is a default or null.
    */
   public final Boolean getDefaultVer( int index )
   {
      return _DefaultVer[index];
   }
    
   /**
    * Gets the Flag indicating that the version is a default field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating that the version is a default or the specified default value.
    */
   public final boolean getDefaultVer( int index, boolean defaultValue )
   {
      return _DefaultVer[index] == null ? defaultValue : _DefaultVer[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating that the version is a default fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating that the version is a default values.
    */
   public final Boolean[] getDefaultVerArray()
   {
      return _DefaultVer;
   }
    
   /**
    * Gets the Closing Period term field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Closing Period term or null.
    */
   public final Integer getClsPerTerm( int index )
   {
      return _ClsPerTerm[index];
   }
    
   /**
    * Gets the Closing Period term field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Closing Period term or the specified default value.
    */
   public final int getClsPerTerm( int index, int defaultValue )
   {
      return _ClsPerTerm[index] == null ? defaultValue : _ClsPerTerm[index].intValue();
   }
    
   /**
    * Gets the array of Closing Period term fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Closing Period term values.
    */
   public final Integer[] getClsPerTermArray()
   {
      return _ClsPerTerm;
   }
    
   /**
    * Gets the Indicating if new contract can be setup field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Indicating if new contract can be setup or null.
    */
   public final Boolean getNewContrAllowed( int index )
   {
      return _NewContrAllowed[index];
   }
    
   /**
    * Gets the Indicating if new contract can be setup field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicating if new contract can be setup or the specified default value.
    */
   public final boolean getNewContrAllowed( int index, boolean defaultValue )
   {
      return _NewContrAllowed[index] == null ? defaultValue : _NewContrAllowed[index].booleanValue();
   }
    
   /**
    * Gets the array of Indicating if new contract can be setup fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Indicating if new contract can be setup values.
    */
   public final Boolean[] getNewContrAllowedArray()
   {
      return _NewContrAllowed;
   }
    
   /**
    * Gets the Maximum Age Restriction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maximum Age Restriction or null.
    */
   public final Integer getMaxAge( int index )
   {
      return _MaxAge[index];
   }
    
   /**
    * Gets the Maximum Age Restriction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Age Restriction or the specified default value.
    */
   public final int getMaxAge( int index, int defaultValue )
   {
      return _MaxAge[index] == null ? defaultValue : _MaxAge[index].intValue();
   }
    
   /**
    * Gets the array of Maximum Age Restriction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maximum Age Restriction values.
    */
   public final Integer[] getMaxAgeArray()
   {
      return _MaxAge;
   }
    
   /**
    * Gets the comma delimited list of Tax Types field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the comma delimited list of Tax Types or null.
    */
   public final String getTaxType( int index )
   {
      return _TaxType[index];
   }
    
   /**
    * Gets the comma delimited list of Tax Types field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the comma delimited list of Tax Types or the specified default value.
    */
   public final String getTaxType( int index, String defaultValue )
   {
      return _TaxType[index] == null ? defaultValue : _TaxType[index];
   }
    
   /**
    * Gets the array of comma delimited list of Tax Types fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of comma delimited list of Tax Types values.
    */
   public final String[] getTaxTypeArray()
   {
      return _TaxType;
   }
    
   /**
    * Gets the comma delimited list of pension jurisdictions field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the comma delimited list of pension jurisdictions or null.
    */
   public final String getPensionJuris( int index )
   {
      return _PensionJuris[index];
   }
    
   /**
    * Gets the comma delimited list of pension jurisdictions field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the comma delimited list of pension jurisdictions or the specified default value.
    */
   public final String getPensionJuris( int index, String defaultValue )
   {
      return _PensionJuris[index] == null ? defaultValue : _PensionJuris[index];
   }
    
   /**
    * Gets the array of comma delimited list of pension jurisdictions fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of comma delimited list of pension jurisdictions values.
    */
   public final String[] getPensionJurisArray()
   {
      return _PensionJuris;
   }
    
   /**
    * Gets the LinkedCont attribute storing linked contract type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LinkedCont attribute storing linked contract type or null.
    */
   public final String getLinkedContract( int index )
   {
      return _LinkedContract[index];
   }
    
   /**
    * Gets the LinkedCont attribute storing linked contract type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LinkedCont attribute storing linked contract type or the specified default value.
    */
   public final String getLinkedContract( int index, String defaultValue )
   {
      return _LinkedContract[index] == null ? defaultValue : _LinkedContract[index];
   }
    
   /**
    * Gets the array of LinkedCont attribute storing linked contract type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LinkedCont attribute storing linked contract type values.
    */
   public final String[] getLinkedContractArray()
   {
      return _LinkedContract;
   }
    
   /**
    * Gets the MinAge field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MinAge or null.
    */
   public final String getMinAge( int index )
   {
      return _MinAge[index];
   }
    
   /**
    * Gets the MinAge field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MinAge or the specified default value.
    */
   public final String getMinAge( int index, String defaultValue )
   {
      return _MinAge[index] == null ? defaultValue : _MinAge[index];
   }
    
   /**
    * Gets the array of MinAge fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MinAge values.
    */
   public final String[] getMinAgeArray()
   {
      return _MinAge;
   }
    
   /**
    * Gets the DfCMDBaseOn field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DfCMDBaseOn or null.
    */
   public final String getDfCMDBaseOn( int index )
   {
      return _DfCMDBaseOn[index];
   }
    
   /**
    * Gets the DfCMDBaseOn field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DfCMDBaseOn or the specified default value.
    */
   public final String getDfCMDBaseOn( int index, String defaultValue )
   {
      return _DfCMDBaseOn[index] == null ? defaultValue : _DfCMDBaseOn[index];
   }
    
   /**
    * Gets the array of DfCMDBaseOn fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DfCMDBaseOn values.
    */
   public final String[] getDfCMDBaseOnArray()
   {
      return _DfCMDBaseOn;
   }
    
   /**
    * Gets the NewMoney field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NewMoney or null.
    */
   public final String getNewMoney( int index )
   {
      return _NewMoney[index];
   }
    
   /**
    * Gets the NewMoney field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NewMoney or the specified default value.
    */
   public final String getNewMoney( int index, String defaultValue )
   {
      return _NewMoney[index] == null ? defaultValue : _NewMoney[index];
   }
    
   /**
    * Gets the array of NewMoney fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NewMoney values.
    */
   public final String[] getNewMoneyArray()
   {
      return _NewMoney;
   }
    
   /**
    * Gets the TaxApl field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TaxApl or null.
    */
   public final String getTaxApl( int index )
   {
      return _TaxApl[index];
   }
    
   /**
    * Gets the TaxApl field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TaxApl or the specified default value.
    */
   public final String getTaxApl( int index, String defaultValue )
   {
      return _TaxApl[index] == null ? defaultValue : _TaxApl[index];
   }
    
   /**
    * Gets the array of TaxApl fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TaxApl values.
    */
   public final String[] getTaxAplArray()
   {
      return _TaxApl;
   }
    
   /**
    * Gets the TopUpClass field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TopUpClass or null.
    */
   public final String getTopUpClass( int index )
   {
      return _TopUpClass[index];
   }
    
   /**
    * Gets the TopUpClass field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TopUpClass or the specified default value.
    */
   public final String getTopUpClass( int index, String defaultValue )
   {
      return _TopUpClass[index] == null ? defaultValue : _TopUpClass[index];
   }
    
   /**
    * Gets the array of TopUpClass fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TopUpClass values.
    */
   public final String[] getTopUpClassArray()
   {
      return _TopUpClass;
   }
    
   /**
    * Gets the TopUpFund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TopUpFund or null.
    */
   public final String getTopUpFund( int index )
   {
      return _TopUpFund[index];
   }
    
   /**
    * Gets the TopUpFund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TopUpFund or the specified default value.
    */
   public final String getTopUpFund( int index, String defaultValue )
   {
      return _TopUpFund[index] == null ? defaultValue : _TopUpFund[index];
   }
    
   /**
    * Gets the array of TopUpFund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TopUpFund values.
    */
   public final String[] getTopUpFundArray()
   {
      return _TopUpFund;
   }
    
   /**
    * Gets the Flag that indicates if NMCR contract field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicates if NMCR contract or null.
    */
   public final Boolean getNMCRContract( int index )
   {
      return _NMCRContract[index];
   }
    
   /**
    * Gets the Flag that indicates if NMCR contract field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if NMCR contract or the specified default value.
    */
   public final boolean getNMCRContract( int index, boolean defaultValue )
   {
      return _NMCRContract[index] == null ? defaultValue : _NMCRContract[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicates if NMCR contract fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicates if NMCR contract values.
    */
   public final Boolean[] getNMCRContractArray()
   {
      return _NMCRContract;
   }
    
   /**
    * Gets the RGrFnd field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RGrFnd or null.
    */
   public final String getRGrFnd( int index )
   {
      return _RGrFnd[index];
   }
    
   /**
    * Gets the RGrFnd field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RGrFnd or the specified default value.
    */
   public final String getRGrFnd( int index, String defaultValue )
   {
      return _RGrFnd[index] == null ? defaultValue : _RGrFnd[index];
   }
    
   /**
    * Gets the array of RGrFnd fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RGrFnd values.
    */
   public final String[] getRGrFndArray()
   {
      return _RGrFnd;
   }
    
   /**
    * Gets the RGrCls field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RGrCls or null.
    */
   public final String getRGrCls( int index )
   {
      return _RGrCls[index];
   }
    
   /**
    * Gets the RGrCls field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RGrCls or the specified default value.
    */
   public final String getRGrCls( int index, String defaultValue )
   {
      return _RGrCls[index] == null ? defaultValue : _RGrCls[index];
   }
    
   /**
    * Gets the array of RGrCls fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RGrCls values.
    */
   public final String[] getRGrClsArray()
   {
      return _RGrCls;
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
      
      _GroupCode = resizeArray( _GroupCode, _RepeatCount );
      _ContractType = resizeArray( _ContractType, _RepeatCount );
      _ContractTypeId = resizeArray( _ContractTypeId, _RepeatCount );
      _MinTerm = resizeArray( _MinTerm, _RepeatCount );
      _MaxTerm = resizeArray( _MaxTerm, _RepeatCount );
      _AnnivDateType = resizeArray( _AnnivDateType, _RepeatCount );
      _ContMatDateBasedOn = resizeArray( _ContMatDateBasedOn, _RepeatCount );
      _MatDateBasedOn = resizeArray( _MatDateBasedOn, _RepeatCount );
      _IsGWOContract = resizeArray( _IsGWOContract, _RepeatCount );
      _ContractVer = resizeArray( _ContractVer, _RepeatCount );
      _DefaultVer = resizeArray( _DefaultVer, _RepeatCount );
      _ClsPerTerm = resizeArray( _ClsPerTerm, _RepeatCount );
      _NewContrAllowed = resizeArray( _NewContrAllowed, _RepeatCount );
      _MaxAge = resizeArray( _MaxAge, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _PensionJuris = resizeArray( _PensionJuris, _RepeatCount );
      _LinkedContract = resizeArray( _LinkedContract, _RepeatCount );
      _MinAge = resizeArray( _MinAge, _RepeatCount );
      _DfCMDBaseOn = resizeArray( _DfCMDBaseOn, _RepeatCount );
      _NewMoney = resizeArray( _NewMoney, _RepeatCount );
      _TaxApl = resizeArray( _TaxApl, _RepeatCount );
      _TopUpClass = resizeArray( _TopUpClass, _RepeatCount );
      _TopUpFund = resizeArray( _TopUpFund, _RepeatCount );
      _NMCRContract = resizeArray( _NMCRContract, _RepeatCount );
      _RGrFnd = resizeArray( _RGrFnd, _RepeatCount );
      _RGrCls = resizeArray( _RGrCls, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _GroupCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContractType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContractTypeId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MinTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MaxTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AnnivDateType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContMatDateBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MatDateBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IsGWOContract[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ContractVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DefaultVer[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ClsPerTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _NewContrAllowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MaxAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PensionJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LinkedContract[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinAge[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DfCMDBaseOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NewMoney[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxApl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TopUpClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TopUpFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NMCRContract[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RGrFnd[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RGrCls[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
