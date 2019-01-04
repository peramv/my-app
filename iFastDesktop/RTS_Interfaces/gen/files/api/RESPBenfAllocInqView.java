
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RESP Beneficiary Allocation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/RESPBenfAllocInq.doc">RESPBenfAllocInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPBenfAllocInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * RESPBenefId member array.
    */
   private String[] _RESPBenefId = null;
   
   /**
    * RESPAllocAmt member array.
    */
   private String[] _RESPAllocAmt = null;
   
   /**
    * RESPAllocPrcnt member array.
    */
   private String[] _RESPAllocPrcnt = null;
   
   /**
    * BenefDofB member array.
    */
   private Date[] _BenefDofB = null;
   
   /**
    * Relation member array.
    */
   private String[] _Relation = null;
   
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * TaxJuris member array.
    */
   private String[] _TaxJuris = null;
   
   /**
    * RESPContrDetlVer member array.
    */
   private Integer[] _RESPContrDetlVer = null;
   
   /**
    * Flag indicate that pending grant should be cancelling before modifying RESP Alloc member array.
    */
   private Boolean[] _PendGrantExists = null;
   
   /**
    * Flag indicate that processed grant should be cancelling before modifying RESP Alloc member array.
    */
   private Boolean[] _ProcGrantExists = null;
   
   /**
    * Grant Transaction number list member array.
    */
   private String[] _GrantTransNumList = null;
   
   /**
    * Re Allocation member array.
    */
   private Boolean[] _ReAllocated = null;
   
   /**
    * Flag indicate that HRDC is reported member array.
    */
   private Boolean[] _HRDCReported = null;
   

   /**
    * Constructs the RESPBenfAllocInqView object.
    * 
    */
   public RESPBenfAllocInqView()
   {
      super ( new RESPBenfAllocInqRequest() );
   }

   /**
    * Constructs the RESPBenfAllocInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RESPBenfAllocInqView( String hostEncoding )
   {
      super ( new RESPBenfAllocInqRequest( hostEncoding ) );
   }

   /**
    * Gets the RESPBenfAllocInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RESPBenfAllocInqRequest object.
    */
   public final RESPBenfAllocInqRequest getRequest()
   {
      return (RESPBenfAllocInqRequest)getIFastRequest();
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
    * Gets the RESPBenefId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESPBenefId or null.
    */
   public final String getRESPBenefId( int index )
   {
      return _RESPBenefId[index];
   }
    
   /**
    * Gets the RESPBenefId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESPBenefId or the specified default value.
    */
   public final String getRESPBenefId( int index, String defaultValue )
   {
      return _RESPBenefId[index] == null ? defaultValue : _RESPBenefId[index];
   }
    
   /**
    * Gets the array of RESPBenefId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESPBenefId values.
    */
   public final String[] getRESPBenefIdArray()
   {
      return _RESPBenefId;
   }
    
   /**
    * Gets the RESPAllocAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESPAllocAmt or null.
    */
   public final String getRESPAllocAmt( int index )
   {
      return _RESPAllocAmt[index];
   }
    
   /**
    * Gets the RESPAllocAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESPAllocAmt or the specified default value.
    */
   public final String getRESPAllocAmt( int index, String defaultValue )
   {
      return _RESPAllocAmt[index] == null ? defaultValue : _RESPAllocAmt[index];
   }
    
   /**
    * Gets the array of RESPAllocAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESPAllocAmt values.
    */
   public final String[] getRESPAllocAmtArray()
   {
      return _RESPAllocAmt;
   }
    
   /**
    * Gets the RESPAllocPrcnt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESPAllocPrcnt or null.
    */
   public final String getRESPAllocPrcnt( int index )
   {
      return _RESPAllocPrcnt[index];
   }
    
   /**
    * Gets the RESPAllocPrcnt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESPAllocPrcnt or the specified default value.
    */
   public final String getRESPAllocPrcnt( int index, String defaultValue )
   {
      return _RESPAllocPrcnt[index] == null ? defaultValue : _RESPAllocPrcnt[index];
   }
    
   /**
    * Gets the array of RESPAllocPrcnt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESPAllocPrcnt values.
    */
   public final String[] getRESPAllocPrcntArray()
   {
      return _RESPAllocPrcnt;
   }
    
   /**
    * Gets the BenefDofB field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BenefDofB or null.
    */
   public final Date getBenefDofB( int index )
   {
      return _BenefDofB[index];
   }
    
   /**
    * Gets the BenefDofB field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BenefDofB or the specified default value.
    */
   public final Date getBenefDofB( int index, Date defaultValue )
   {
      return _BenefDofB[index] == null ? defaultValue : _BenefDofB[index];
   }
    
   /**
    * Gets the array of BenefDofB fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BenefDofB values.
    */
   public final Date[] getBenefDofBArray()
   {
      return _BenefDofB;
   }
    
   /**
    * Gets the Relation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Relation or null.
    */
   public final String getRelation( int index )
   {
      return _Relation[index];
   }
    
   /**
    * Gets the Relation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Relation or the specified default value.
    */
   public final String getRelation( int index, String defaultValue )
   {
      return _Relation[index] == null ? defaultValue : _Relation[index];
   }
    
   /**
    * Gets the array of Relation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Relation values.
    */
   public final String[] getRelationArray()
   {
      return _Relation;
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EffectiveDate or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the EffectiveDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EffectiveDate or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of EffectiveDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EffectiveDate values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the TaxJuris field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TaxJuris or null.
    */
   public final String getTaxJuris( int index )
   {
      return _TaxJuris[index];
   }
    
   /**
    * Gets the TaxJuris field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TaxJuris or the specified default value.
    */
   public final String getTaxJuris( int index, String defaultValue )
   {
      return _TaxJuris[index] == null ? defaultValue : _TaxJuris[index];
   }
    
   /**
    * Gets the array of TaxJuris fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TaxJuris values.
    */
   public final String[] getTaxJurisArray()
   {
      return _TaxJuris;
   }
    
   /**
    * Gets the RESPContrDetlVer field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESPContrDetlVer or null.
    */
   public final Integer getRESPContrDetlVer( int index )
   {
      return _RESPContrDetlVer[index];
   }
    
   /**
    * Gets the RESPContrDetlVer field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESPContrDetlVer or the specified default value.
    */
   public final int getRESPContrDetlVer( int index, int defaultValue )
   {
      return _RESPContrDetlVer[index] == null ? defaultValue : _RESPContrDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of RESPContrDetlVer fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESPContrDetlVer values.
    */
   public final Integer[] getRESPContrDetlVerArray()
   {
      return _RESPContrDetlVer;
   }
    
   /**
    * Gets the Flag indicate that pending grant should be cancelling before modifying RESP Alloc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicate that pending grant should be cancelling before modifying RESP Alloc or null.
    */
   public final Boolean getPendGrantExists( int index )
   {
      return _PendGrantExists[index];
   }
    
   /**
    * Gets the Flag indicate that pending grant should be cancelling before modifying RESP Alloc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicate that pending grant should be cancelling before modifying RESP Alloc or the specified default value.
    */
   public final boolean getPendGrantExists( int index, boolean defaultValue )
   {
      return _PendGrantExists[index] == null ? defaultValue : _PendGrantExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicate that pending grant should be cancelling before modifying RESP Alloc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicate that pending grant should be cancelling before modifying RESP Alloc values.
    */
   public final Boolean[] getPendGrantExistsArray()
   {
      return _PendGrantExists;
   }
    
   /**
    * Gets the Flag indicate that processed grant should be cancelling before modifying RESP Alloc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicate that processed grant should be cancelling before modifying RESP Alloc or null.
    */
   public final Boolean getProcGrantExists( int index )
   {
      return _ProcGrantExists[index];
   }
    
   /**
    * Gets the Flag indicate that processed grant should be cancelling before modifying RESP Alloc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicate that processed grant should be cancelling before modifying RESP Alloc or the specified default value.
    */
   public final boolean getProcGrantExists( int index, boolean defaultValue )
   {
      return _ProcGrantExists[index] == null ? defaultValue : _ProcGrantExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicate that processed grant should be cancelling before modifying RESP Alloc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicate that processed grant should be cancelling before modifying RESP Alloc values.
    */
   public final Boolean[] getProcGrantExistsArray()
   {
      return _ProcGrantExists;
   }
    
   /**
    * Gets the Grant Transaction number list field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Grant Transaction number list or null.
    */
   public final String getGrantTransNumList( int index )
   {
      return _GrantTransNumList[index];
   }
    
   /**
    * Gets the Grant Transaction number list field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Grant Transaction number list or the specified default value.
    */
   public final String getGrantTransNumList( int index, String defaultValue )
   {
      return _GrantTransNumList[index] == null ? defaultValue : _GrantTransNumList[index];
   }
    
   /**
    * Gets the array of Grant Transaction number list fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Grant Transaction number list values.
    */
   public final String[] getGrantTransNumListArray()
   {
      return _GrantTransNumList;
   }
    
   /**
    * Gets the Re Allocation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Re Allocation or null.
    */
   public final Boolean getReAllocated( int index )
   {
      return _ReAllocated[index];
   }
    
   /**
    * Gets the Re Allocation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Re Allocation or the specified default value.
    */
   public final boolean getReAllocated( int index, boolean defaultValue )
   {
      return _ReAllocated[index] == null ? defaultValue : _ReAllocated[index].booleanValue();
   }
    
   /**
    * Gets the array of Re Allocation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Re Allocation values.
    */
   public final Boolean[] getReAllocatedArray()
   {
      return _ReAllocated;
   }
    
   /**
    * Gets the Flag indicate that HRDC is reported field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicate that HRDC is reported or null.
    */
   public final Boolean getHRDCReported( int index )
   {
      return _HRDCReported[index];
   }
    
   /**
    * Gets the Flag indicate that HRDC is reported field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicate that HRDC is reported or the specified default value.
    */
   public final boolean getHRDCReported( int index, boolean defaultValue )
   {
      return _HRDCReported[index] == null ? defaultValue : _HRDCReported[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicate that HRDC is reported fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicate that HRDC is reported values.
    */
   public final Boolean[] getHRDCReportedArray()
   {
      return _HRDCReported;
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
      
      _RESPBenefId = resizeArray( _RESPBenefId, _RepeatCount );
      _RESPAllocAmt = resizeArray( _RESPAllocAmt, _RepeatCount );
      _RESPAllocPrcnt = resizeArray( _RESPAllocPrcnt, _RepeatCount );
      _BenefDofB = resizeArray( _BenefDofB, _RepeatCount );
      _Relation = resizeArray( _Relation, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _TaxJuris = resizeArray( _TaxJuris, _RepeatCount );
      _RESPContrDetlVer = resizeArray( _RESPContrDetlVer, _RepeatCount );
      _PendGrantExists = resizeArray( _PendGrantExists, _RepeatCount );
      _ProcGrantExists = resizeArray( _ProcGrantExists, _RepeatCount );
      _GrantTransNumList = resizeArray( _GrantTransNumList, _RepeatCount );
      _ReAllocated = resizeArray( _ReAllocated, _RepeatCount );
      _HRDCReported = resizeArray( _HRDCReported, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RESPBenefId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPAllocAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPAllocPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BenefDofB[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Relation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TaxJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RESPContrDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _PendGrantExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ProcGrantExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GrantTransNumList[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReAllocated[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _HRDCReported[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
