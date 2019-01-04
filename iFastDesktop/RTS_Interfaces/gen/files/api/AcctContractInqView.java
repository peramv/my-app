
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Contract Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctContractInq.doc">AcctContractInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctContractInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Contract ID member array.
    */
   private Integer[] _ContractID = null;
   
   /**
    * Start Date member array.
    */
   private Date[] _StartDate = null;
   
   /**
    * Maturity Date member array.
    */
   private Date[] _MaturityDate = null;
   
   /**
    * Guaranteed Amount at maturity member array.
    */
   private String[] _GuarAmt = null;
   
   /**
    * Guaranteed Units at maturity member array.
    */
   private String[] _GuarUnits = null;
   
   /**
    * Transaction ID member array.
    */
   private Integer[] _TransID = null;
   
   /**
    * Trade Amount member array.
    */
   private String[] _TransAmt = null;
   
   /**
    * Trade Units member array.
    */
   private String[] _TransUnits = null;
   
   /**
    * Reset ID -  link to ResetReq member array.
    */
   private Integer[] _ResetID = null;
   
   /**
    * Instruction Amount member array.
    */
   private String[] _InstrAmt = null;
   
   /**
    * Contract gap date member array.
    */
   private Date[] _ContractGapDate = null;
   
   /**
    * Date modified member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Modified by member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Created by member array.
    */
   private String[] _UserName = null;
   
   /**
    * Date created member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Fund in response member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class in response member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * ProtContract RecId member array.
    */
   private Integer[] _ProtContractRId = null;
   
   /**
    * Market Value member array.
    */
   private String[] _MktValue = null;
   
   /**
    * Amount Increased/Decreased member array.
    */
   private String[] _GainAmt = null;
   

   /**
    * Constructs the AcctContractInqView object.
    * 
    */
   public AcctContractInqView()
   {
      super ( new AcctContractInqRequest() );
   }

   /**
    * Constructs the AcctContractInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctContractInqView( String hostEncoding )
   {
      super ( new AcctContractInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctContractInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctContractInqRequest object.
    */
   public final AcctContractInqRequest getRequest()
   {
      return (AcctContractInqRequest)getIFastRequest();
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
    * Gets the Contract ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract ID or null.
    */
   public final Integer getContractID( int index )
   {
      return _ContractID[index];
   }
    
   /**
    * Gets the Contract ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract ID or the specified default value.
    */
   public final int getContractID( int index, int defaultValue )
   {
      return _ContractID[index] == null ? defaultValue : _ContractID[index].intValue();
   }
    
   /**
    * Gets the array of Contract ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract ID values.
    */
   public final Integer[] getContractIDArray()
   {
      return _ContractID;
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Start Date or null.
    */
   public final Date getStartDate( int index )
   {
      return _StartDate[index];
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start Date or the specified default value.
    */
   public final Date getStartDate( int index, Date defaultValue )
   {
      return _StartDate[index] == null ? defaultValue : _StartDate[index];
   }
    
   /**
    * Gets the array of Start Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Start Date values.
    */
   public final Date[] getStartDateArray()
   {
      return _StartDate;
   }
    
   /**
    * Gets the Maturity Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maturity Date or null.
    */
   public final Date getMaturityDate( int index )
   {
      return _MaturityDate[index];
   }
    
   /**
    * Gets the Maturity Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity Date or the specified default value.
    */
   public final Date getMaturityDate( int index, Date defaultValue )
   {
      return _MaturityDate[index] == null ? defaultValue : _MaturityDate[index];
   }
    
   /**
    * Gets the array of Maturity Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maturity Date values.
    */
   public final Date[] getMaturityDateArray()
   {
      return _MaturityDate;
   }
    
   /**
    * Gets the Guaranteed Amount at maturity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guaranteed Amount at maturity or null.
    */
   public final String getGuarAmt( int index )
   {
      return _GuarAmt[index];
   }
    
   /**
    * Gets the Guaranteed Amount at maturity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guaranteed Amount at maturity or the specified default value.
    */
   public final String getGuarAmt( int index, String defaultValue )
   {
      return _GuarAmt[index] == null ? defaultValue : _GuarAmt[index];
   }
    
   /**
    * Gets the array of Guaranteed Amount at maturity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guaranteed Amount at maturity values.
    */
   public final String[] getGuarAmtArray()
   {
      return _GuarAmt;
   }
    
   /**
    * Gets the Guaranteed Units at maturity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guaranteed Units at maturity or null.
    */
   public final String getGuarUnits( int index )
   {
      return _GuarUnits[index];
   }
    
   /**
    * Gets the Guaranteed Units at maturity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guaranteed Units at maturity or the specified default value.
    */
   public final String getGuarUnits( int index, String defaultValue )
   {
      return _GuarUnits[index] == null ? defaultValue : _GuarUnits[index];
   }
    
   /**
    * Gets the array of Guaranteed Units at maturity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guaranteed Units at maturity values.
    */
   public final String[] getGuarUnitsArray()
   {
      return _GuarUnits;
   }
    
   /**
    * Gets the Transaction ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction ID or null.
    */
   public final Integer getTransID( int index )
   {
      return _TransID[index];
   }
    
   /**
    * Gets the Transaction ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction ID or the specified default value.
    */
   public final int getTransID( int index, int defaultValue )
   {
      return _TransID[index] == null ? defaultValue : _TransID[index].intValue();
   }
    
   /**
    * Gets the array of Transaction ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction ID values.
    */
   public final Integer[] getTransIDArray()
   {
      return _TransID;
   }
    
   /**
    * Gets the Trade Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Amount or null.
    */
   public final String getTransAmt( int index )
   {
      return _TransAmt[index];
   }
    
   /**
    * Gets the Trade Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Amount or the specified default value.
    */
   public final String getTransAmt( int index, String defaultValue )
   {
      return _TransAmt[index] == null ? defaultValue : _TransAmt[index];
   }
    
   /**
    * Gets the array of Trade Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Amount values.
    */
   public final String[] getTransAmtArray()
   {
      return _TransAmt;
   }
    
   /**
    * Gets the Trade Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Units or null.
    */
   public final String getTransUnits( int index )
   {
      return _TransUnits[index];
   }
    
   /**
    * Gets the Trade Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Units or the specified default value.
    */
   public final String getTransUnits( int index, String defaultValue )
   {
      return _TransUnits[index] == null ? defaultValue : _TransUnits[index];
   }
    
   /**
    * Gets the array of Trade Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Units values.
    */
   public final String[] getTransUnitsArray()
   {
      return _TransUnits;
   }
    
   /**
    * Gets the Reset ID -  link to ResetReq field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reset ID -  link to ResetReq or null.
    */
   public final Integer getResetID( int index )
   {
      return _ResetID[index];
   }
    
   /**
    * Gets the Reset ID -  link to ResetReq field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reset ID -  link to ResetReq or the specified default value.
    */
   public final int getResetID( int index, int defaultValue )
   {
      return _ResetID[index] == null ? defaultValue : _ResetID[index].intValue();
   }
    
   /**
    * Gets the array of Reset ID -  link to ResetReq fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reset ID -  link to ResetReq values.
    */
   public final Integer[] getResetIDArray()
   {
      return _ResetID;
   }
    
   /**
    * Gets the Instruction Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Instruction Amount or null.
    */
   public final String getInstrAmt( int index )
   {
      return _InstrAmt[index];
   }
    
   /**
    * Gets the Instruction Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Instruction Amount or the specified default value.
    */
   public final String getInstrAmt( int index, String defaultValue )
   {
      return _InstrAmt[index] == null ? defaultValue : _InstrAmt[index];
   }
    
   /**
    * Gets the array of Instruction Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Instruction Amount values.
    */
   public final String[] getInstrAmtArray()
   {
      return _InstrAmt;
   }
    
   /**
    * Gets the Contract gap date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract gap date or null.
    */
   public final Date getContractGapDate( int index )
   {
      return _ContractGapDate[index];
   }
    
   /**
    * Gets the Contract gap date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract gap date or the specified default value.
    */
   public final Date getContractGapDate( int index, Date defaultValue )
   {
      return _ContractGapDate[index] == null ? defaultValue : _ContractGapDate[index];
   }
    
   /**
    * Gets the array of Contract gap date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract gap date values.
    */
   public final Date[] getContractGapDateArray()
   {
      return _ContractGapDate;
   }
    
   /**
    * Gets the Date modified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date modified or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Date modified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date modified or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Date modified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date modified values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Modified by field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified by or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modified by field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified by or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modified by fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified by values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Created by field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created by or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the Created by field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created by or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of Created by fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created by values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Date created field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date created or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date created field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date created or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date created fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date created values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Fund in response field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund in response or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund in response field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund in response or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund in response fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund in response values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class in response field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class in response or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class in response field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class in response or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class in response fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class in response values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the ProtContract RecId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProtContract RecId or null.
    */
   public final Integer getProtContractRId( int index )
   {
      return _ProtContractRId[index];
   }
    
   /**
    * Gets the ProtContract RecId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProtContract RecId or the specified default value.
    */
   public final int getProtContractRId( int index, int defaultValue )
   {
      return _ProtContractRId[index] == null ? defaultValue : _ProtContractRId[index].intValue();
   }
    
   /**
    * Gets the array of ProtContract RecId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProtContract RecId values.
    */
   public final Integer[] getProtContractRIdArray()
   {
      return _ProtContractRId;
   }
    
   /**
    * Gets the Market Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Market Value or null.
    */
   public final String getMktValue( int index )
   {
      return _MktValue[index];
   }
    
   /**
    * Gets the Market Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Market Value or the specified default value.
    */
   public final String getMktValue( int index, String defaultValue )
   {
      return _MktValue[index] == null ? defaultValue : _MktValue[index];
   }
    
   /**
    * Gets the array of Market Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Market Value values.
    */
   public final String[] getMktValueArray()
   {
      return _MktValue;
   }
    
   /**
    * Gets the Amount Increased/Decreased field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount Increased/Decreased or null.
    */
   public final String getGainAmt( int index )
   {
      return _GainAmt[index];
   }
    
   /**
    * Gets the Amount Increased/Decreased field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Increased/Decreased or the specified default value.
    */
   public final String getGainAmt( int index, String defaultValue )
   {
      return _GainAmt[index] == null ? defaultValue : _GainAmt[index];
   }
    
   /**
    * Gets the array of Amount Increased/Decreased fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount Increased/Decreased values.
    */
   public final String[] getGainAmtArray()
   {
      return _GainAmt;
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
      
      _ContractID = resizeArray( _ContractID, _RepeatCount );
      _StartDate = resizeArray( _StartDate, _RepeatCount );
      _MaturityDate = resizeArray( _MaturityDate, _RepeatCount );
      _GuarAmt = resizeArray( _GuarAmt, _RepeatCount );
      _GuarUnits = resizeArray( _GuarUnits, _RepeatCount );
      _TransID = resizeArray( _TransID, _RepeatCount );
      _TransAmt = resizeArray( _TransAmt, _RepeatCount );
      _TransUnits = resizeArray( _TransUnits, _RepeatCount );
      _ResetID = resizeArray( _ResetID, _RepeatCount );
      _InstrAmt = resizeArray( _InstrAmt, _RepeatCount );
      _ContractGapDate = resizeArray( _ContractGapDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _ProtContractRId = resizeArray( _ProtContractRId, _RepeatCount );
      _MktValue = resizeArray( _MktValue, _RepeatCount );
      _GainAmt = resizeArray( _GainAmt, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ContractID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _StartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _MaturityDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GuarAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GuarUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ResetID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _InstrAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContractGapDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProtContractRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MktValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GainAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
