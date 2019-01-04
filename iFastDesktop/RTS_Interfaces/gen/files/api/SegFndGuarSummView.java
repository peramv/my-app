
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Seg Fund Guarantee Summary view.
 * For additional view information see <A HREF="../../../../viewspecs/SegFndGuarSumm.doc">SegFndGuarSumm.doc</A>.
 * 
 * @author RTS Generated
 */
public class SegFndGuarSummView extends IFastView implements Serializable
{

   /**
    * Total Guarantee for Account member variable.
    */
   private String _GuarAcctTotal = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Contract Type member array.
    */
   private String[] _ContractType = null;
   
   /**
    * Policy Year member array.
    */
   private Integer[] _PolicyYear = null;
   
   /**
    * Policy Term member array.
    */
   private Integer[] _PolicyTerm = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Issue Date member array.
    */
   private Date[] _IssueDate = null;
   
   /**
    * Active member array.
    */
   private Boolean[] _Active = null;
   
   /**
    * Maturity Date member array.
    */
   private Date[] _MaturDate = null;
   
   /**
    * Guarantee Status member array.
    */
   private String[] _GuarStat = null;
   
   /**
    * indicator if guarantee units should be adjucted member array.
    */
   private Boolean[] _ReqGuarUnitAdjust = null;
   
   /**
    * indicator if guarantee is suspected member array.
    */
   private Boolean[] _GuarSuspect = null;
   
   /**
    * Seg-Guar-Mat record id member array.
    */
   private Integer[] _SegGuarMatRecId = null;
   
   /**
    * Total Guarantee for Contract member array.
    */
   private String[] _GuarContrTotal = null;
   

   /**
    * Constructs the SegFndGuarSummView object.
    * 
    */
   public SegFndGuarSummView()
   {
      super ( new SegFndGuarSummRequest() );
   }

   /**
    * Constructs the SegFndGuarSummView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SegFndGuarSummView( String hostEncoding )
   {
      super ( new SegFndGuarSummRequest( hostEncoding ) );
   }

   /**
    * Gets the SegFndGuarSummRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SegFndGuarSummRequest object.
    */
   public final SegFndGuarSummRequest getRequest()
   {
      return (SegFndGuarSummRequest)getIFastRequest();
   }
        
   /**
    * Gets the Total Guarantee for Account field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Total Guarantee for Account or null.
    */
   public final String getGuarAcctTotal()
   {
      return _GuarAcctTotal;
   }
	
   /**
    * Gets the Total Guarantee for Account field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Guarantee for Account or the specified default value.
    */
   public final String getGuarAcctTotal( String defaultValue )
   {
      return _GuarAcctTotal == null ? defaultValue : _GuarAcctTotal;
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
    * Gets the Policy Term field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Policy Term or null.
    */
   public final Integer getPolicyTerm( int index )
   {
      return _PolicyTerm[index];
   }
    
   /**
    * Gets the Policy Term field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Policy Term or the specified default value.
    */
   public final int getPolicyTerm( int index, int defaultValue )
   {
      return _PolicyTerm[index] == null ? defaultValue : _PolicyTerm[index].intValue();
   }
    
   /**
    * Gets the array of Policy Term fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Policy Term values.
    */
   public final Integer[] getPolicyTermArray()
   {
      return _PolicyTerm;
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
    * Gets the Issue Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Issue Date or null.
    */
   public final Date getIssueDate( int index )
   {
      return _IssueDate[index];
   }
    
   /**
    * Gets the Issue Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Issue Date or the specified default value.
    */
   public final Date getIssueDate( int index, Date defaultValue )
   {
      return _IssueDate[index] == null ? defaultValue : _IssueDate[index];
   }
    
   /**
    * Gets the array of Issue Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Issue Date values.
    */
   public final Date[] getIssueDateArray()
   {
      return _IssueDate;
   }
    
   /**
    * Gets the Active field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Active or null.
    */
   public final Boolean getActive( int index )
   {
      return _Active[index];
   }
    
   /**
    * Gets the Active field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Active or the specified default value.
    */
   public final boolean getActive( int index, boolean defaultValue )
   {
      return _Active[index] == null ? defaultValue : _Active[index].booleanValue();
   }
    
   /**
    * Gets the array of Active fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Active values.
    */
   public final Boolean[] getActiveArray()
   {
      return _Active;
   }
    
   /**
    * Gets the Maturity Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maturity Date or null.
    */
   public final Date getMaturDate( int index )
   {
      return _MaturDate[index];
   }
    
   /**
    * Gets the Maturity Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity Date or the specified default value.
    */
   public final Date getMaturDate( int index, Date defaultValue )
   {
      return _MaturDate[index] == null ? defaultValue : _MaturDate[index];
   }
    
   /**
    * Gets the array of Maturity Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maturity Date values.
    */
   public final Date[] getMaturDateArray()
   {
      return _MaturDate;
   }
    
   /**
    * Gets the Guarantee Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Guarantee Status or null.
    */
   public final String getGuarStat( int index )
   {
      return _GuarStat[index];
   }
    
   /**
    * Gets the Guarantee Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Status or the specified default value.
    */
   public final String getGuarStat( int index, String defaultValue )
   {
      return _GuarStat[index] == null ? defaultValue : _GuarStat[index];
   }
    
   /**
    * Gets the array of Guarantee Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Guarantee Status values.
    */
   public final String[] getGuarStatArray()
   {
      return _GuarStat;
   }
    
   /**
    * Gets the indicator if guarantee units should be adjucted field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the indicator if guarantee units should be adjucted or null.
    */
   public final Boolean getReqGuarUnitAdjust( int index )
   {
      return _ReqGuarUnitAdjust[index];
   }
    
   /**
    * Gets the indicator if guarantee units should be adjucted field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the indicator if guarantee units should be adjucted or the specified default value.
    */
   public final boolean getReqGuarUnitAdjust( int index, boolean defaultValue )
   {
      return _ReqGuarUnitAdjust[index] == null ? defaultValue : _ReqGuarUnitAdjust[index].booleanValue();
   }
    
   /**
    * Gets the array of indicator if guarantee units should be adjucted fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of indicator if guarantee units should be adjucted values.
    */
   public final Boolean[] getReqGuarUnitAdjustArray()
   {
      return _ReqGuarUnitAdjust;
   }
    
   /**
    * Gets the indicator if guarantee is suspected field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the indicator if guarantee is suspected or null.
    */
   public final Boolean getGuarSuspect( int index )
   {
      return _GuarSuspect[index];
   }
    
   /**
    * Gets the indicator if guarantee is suspected field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the indicator if guarantee is suspected or the specified default value.
    */
   public final boolean getGuarSuspect( int index, boolean defaultValue )
   {
      return _GuarSuspect[index] == null ? defaultValue : _GuarSuspect[index].booleanValue();
   }
    
   /**
    * Gets the array of indicator if guarantee is suspected fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of indicator if guarantee is suspected values.
    */
   public final Boolean[] getGuarSuspectArray()
   {
      return _GuarSuspect;
   }
    
   /**
    * Gets the Seg-Guar-Mat record id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Seg-Guar-Mat record id or null.
    */
   public final Integer getSegGuarMatRecId( int index )
   {
      return _SegGuarMatRecId[index];
   }
    
   /**
    * Gets the Seg-Guar-Mat record id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Seg-Guar-Mat record id or the specified default value.
    */
   public final int getSegGuarMatRecId( int index, int defaultValue )
   {
      return _SegGuarMatRecId[index] == null ? defaultValue : _SegGuarMatRecId[index].intValue();
   }
    
   /**
    * Gets the array of Seg-Guar-Mat record id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Seg-Guar-Mat record id values.
    */
   public final Integer[] getSegGuarMatRecIdArray()
   {
      return _SegGuarMatRecId;
   }
    
   /**
    * Gets the Total Guarantee for Contract field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Total Guarantee for Contract or null.
    */
   public final String getGuarContrTotal( int index )
   {
      return _GuarContrTotal[index];
   }
    
   /**
    * Gets the Total Guarantee for Contract field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Guarantee for Contract or the specified default value.
    */
   public final String getGuarContrTotal( int index, String defaultValue )
   {
      return _GuarContrTotal[index] == null ? defaultValue : _GuarContrTotal[index];
   }
    
   /**
    * Gets the array of Total Guarantee for Contract fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Total Guarantee for Contract values.
    */
   public final String[] getGuarContrTotalArray()
   {
      return _GuarContrTotal;
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
      _GuarAcctTotal = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _ContractType = resizeArray( _ContractType, _RepeatCount );
      _PolicyYear = resizeArray( _PolicyYear, _RepeatCount );
      _PolicyTerm = resizeArray( _PolicyTerm, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _IssueDate = resizeArray( _IssueDate, _RepeatCount );
      _Active = resizeArray( _Active, _RepeatCount );
      _MaturDate = resizeArray( _MaturDate, _RepeatCount );
      _GuarStat = resizeArray( _GuarStat, _RepeatCount );
      _ReqGuarUnitAdjust = resizeArray( _ReqGuarUnitAdjust, _RepeatCount );
      _GuarSuspect = resizeArray( _GuarSuspect, _RepeatCount );
      _SegGuarMatRecId = resizeArray( _SegGuarMatRecId, _RepeatCount );
      _GuarContrTotal = resizeArray( _GuarContrTotal, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ContractType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PolicyYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PolicyTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _IssueDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Active[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MaturDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GuarStat[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReqGuarUnitAdjust[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GuarSuspect[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SegGuarMatRecId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _GuarContrTotal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
