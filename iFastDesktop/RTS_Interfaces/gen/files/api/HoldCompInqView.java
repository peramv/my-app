
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Holding Company Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/HoldCompInq.doc">HoldCompInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class HoldCompInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Entity ID member array.
    */
   private String[] _EntityID = null;
   
   /**
    * Where Use Key member array.
    */
   private String[] _WhereUseKey = null;
   
   /**
    * Holding Company Name member array.
    */
   private String[] _HoldingCoName = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _Deff = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Aggregation Method member array.
    */
   private String[] _AggrMethod = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Username member array.
    */
   private String[] _Username = null;
   
   /**
    * Mod Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * GBCD member array.
    */
   private Boolean[] _GBCD = null;
   
   /**
    * Company Usage member array.
    */
   private String[] _CoUsage = null;
   
   /**
    * LangCode member array.
    */
   private String[] _LangCode = null;
   
   /**
    * EntityWhereUseRID member array.
    */
   private Integer[] _EntityWhereUseRID = null;
   
   /**
    * EntityWhereUse Version member array.
    */
   private Integer[] _EntityWhereUseVer = null;
   
   /**
    * Flag that indicate ifFeeModel record Exist member array.
    */
   private Boolean[] _FeeModelExist = null;
   
   /**
    * Flag that indicate if FeeAggregation record Exist member array.
    */
   private Boolean[] _FeeAggregationExist = null;
   
   /**
    * Flag that indicate if BillingInstr record Exist member array.
    */
   private Boolean[] _BillingInstrExist = null;
   
   /**
    * Flag that indicate if ReportGroup record Exist member array.
    */
   private Boolean[] _ReportGroupExist = null;
   
   /**
    * First Child Record Effective Date member array.
    */
   private Date[] _FirstChildRecDeff = null;
   
   /**
    * ShrAcctFeeConfig Last Process Date member array.
    */
   private Date[] _ShrAcctLastProcDate = null;
   

   /**
    * Constructs the HoldCompInqView object.
    * 
    */
   public HoldCompInqView()
   {
      super ( new HoldCompInqRequest() );
   }

   /**
    * Constructs the HoldCompInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public HoldCompInqView( String hostEncoding )
   {
      super ( new HoldCompInqRequest( hostEncoding ) );
   }

   /**
    * Gets the HoldCompInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The HoldCompInqRequest object.
    */
   public final HoldCompInqRequest getRequest()
   {
      return (HoldCompInqRequest)getIFastRequest();
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
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity ID or null.
    */
   public final String getEntityID( int index )
   {
      return _EntityID[index];
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity ID or the specified default value.
    */
   public final String getEntityID( int index, String defaultValue )
   {
      return _EntityID[index] == null ? defaultValue : _EntityID[index];
   }
    
   /**
    * Gets the array of Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity ID values.
    */
   public final String[] getEntityIDArray()
   {
      return _EntityID;
   }
    
   /**
    * Gets the Where Use Key field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Where Use Key or null.
    */
   public final String getWhereUseKey( int index )
   {
      return _WhereUseKey[index];
   }
    
   /**
    * Gets the Where Use Key field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Where Use Key or the specified default value.
    */
   public final String getWhereUseKey( int index, String defaultValue )
   {
      return _WhereUseKey[index] == null ? defaultValue : _WhereUseKey[index];
   }
    
   /**
    * Gets the array of Where Use Key fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Where Use Key values.
    */
   public final String[] getWhereUseKeyArray()
   {
      return _WhereUseKey;
   }
    
   /**
    * Gets the Holding Company Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Holding Company Name or null.
    */
   public final String getHoldingCoName( int index )
   {
      return _HoldingCoName[index];
   }
    
   /**
    * Gets the Holding Company Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Holding Company Name or the specified default value.
    */
   public final String getHoldingCoName( int index, String defaultValue )
   {
      return _HoldingCoName[index] == null ? defaultValue : _HoldingCoName[index];
   }
    
   /**
    * Gets the array of Holding Company Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Holding Company Name values.
    */
   public final String[] getHoldingCoNameArray()
   {
      return _HoldingCoName;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getDeff( int index )
   {
      return _Deff[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getDeff( int index, Date defaultValue )
   {
      return _Deff[index] == null ? defaultValue : _Deff[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getDeffArray()
   {
      return _Deff;
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
    * Gets the Aggregation Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Aggregation Method or null.
    */
   public final String getAggrMethod( int index )
   {
      return _AggrMethod[index];
   }
    
   /**
    * Gets the Aggregation Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Aggregation Method or the specified default value.
    */
   public final String getAggrMethod( int index, String defaultValue )
   {
      return _AggrMethod[index] == null ? defaultValue : _AggrMethod[index];
   }
    
   /**
    * Gets the array of Aggregation Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Aggregation Method values.
    */
   public final String[] getAggrMethodArray()
   {
      return _AggrMethod;
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
    * Gets the Username field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Username or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Username field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Username or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Username fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Username values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Mod Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Mod User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the GBCD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GBCD or null.
    */
   public final Boolean getGBCD( int index )
   {
      return _GBCD[index];
   }
    
   /**
    * Gets the GBCD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GBCD or the specified default value.
    */
   public final boolean getGBCD( int index, boolean defaultValue )
   {
      return _GBCD[index] == null ? defaultValue : _GBCD[index].booleanValue();
   }
    
   /**
    * Gets the array of GBCD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GBCD values.
    */
   public final Boolean[] getGBCDArray()
   {
      return _GBCD;
   }
    
   /**
    * Gets the Company Usage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Company Usage or null.
    */
   public final String getCoUsage( int index )
   {
      return _CoUsage[index];
   }
    
   /**
    * Gets the Company Usage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Company Usage or the specified default value.
    */
   public final String getCoUsage( int index, String defaultValue )
   {
      return _CoUsage[index] == null ? defaultValue : _CoUsage[index];
   }
    
   /**
    * Gets the array of Company Usage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Company Usage values.
    */
   public final String[] getCoUsageArray()
   {
      return _CoUsage;
   }
    
   /**
    * Gets the LangCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LangCode or null.
    */
   public final String getLangCode( int index )
   {
      return _LangCode[index];
   }
    
   /**
    * Gets the LangCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LangCode or the specified default value.
    */
   public final String getLangCode( int index, String defaultValue )
   {
      return _LangCode[index] == null ? defaultValue : _LangCode[index];
   }
    
   /**
    * Gets the array of LangCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LangCode values.
    */
   public final String[] getLangCodeArray()
   {
      return _LangCode;
   }
    
   /**
    * Gets the EntityWhereUseRID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EntityWhereUseRID or null.
    */
   public final Integer getEntityWhereUseRID( int index )
   {
      return _EntityWhereUseRID[index];
   }
    
   /**
    * Gets the EntityWhereUseRID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EntityWhereUseRID or the specified default value.
    */
   public final int getEntityWhereUseRID( int index, int defaultValue )
   {
      return _EntityWhereUseRID[index] == null ? defaultValue : _EntityWhereUseRID[index].intValue();
   }
    
   /**
    * Gets the array of EntityWhereUseRID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EntityWhereUseRID values.
    */
   public final Integer[] getEntityWhereUseRIDArray()
   {
      return _EntityWhereUseRID;
   }
    
   /**
    * Gets the EntityWhereUse Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EntityWhereUse Version or null.
    */
   public final Integer getEntityWhereUseVer( int index )
   {
      return _EntityWhereUseVer[index];
   }
    
   /**
    * Gets the EntityWhereUse Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EntityWhereUse Version or the specified default value.
    */
   public final int getEntityWhereUseVer( int index, int defaultValue )
   {
      return _EntityWhereUseVer[index] == null ? defaultValue : _EntityWhereUseVer[index].intValue();
   }
    
   /**
    * Gets the array of EntityWhereUse Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EntityWhereUse Version values.
    */
   public final Integer[] getEntityWhereUseVerArray()
   {
      return _EntityWhereUseVer;
   }
    
   /**
    * Gets the Flag that indicate ifFeeModel record Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicate ifFeeModel record Exist or null.
    */
   public final Boolean getFeeModelExist( int index )
   {
      return _FeeModelExist[index];
   }
    
   /**
    * Gets the Flag that indicate ifFeeModel record Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicate ifFeeModel record Exist or the specified default value.
    */
   public final boolean getFeeModelExist( int index, boolean defaultValue )
   {
      return _FeeModelExist[index] == null ? defaultValue : _FeeModelExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicate ifFeeModel record Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicate ifFeeModel record Exist values.
    */
   public final Boolean[] getFeeModelExistArray()
   {
      return _FeeModelExist;
   }
    
   /**
    * Gets the Flag that indicate if FeeAggregation record Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicate if FeeAggregation record Exist or null.
    */
   public final Boolean getFeeAggregationExist( int index )
   {
      return _FeeAggregationExist[index];
   }
    
   /**
    * Gets the Flag that indicate if FeeAggregation record Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicate if FeeAggregation record Exist or the specified default value.
    */
   public final boolean getFeeAggregationExist( int index, boolean defaultValue )
   {
      return _FeeAggregationExist[index] == null ? defaultValue : _FeeAggregationExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicate if FeeAggregation record Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicate if FeeAggregation record Exist values.
    */
   public final Boolean[] getFeeAggregationExistArray()
   {
      return _FeeAggregationExist;
   }
    
   /**
    * Gets the Flag that indicate if BillingInstr record Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicate if BillingInstr record Exist or null.
    */
   public final Boolean getBillingInstrExist( int index )
   {
      return _BillingInstrExist[index];
   }
    
   /**
    * Gets the Flag that indicate if BillingInstr record Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicate if BillingInstr record Exist or the specified default value.
    */
   public final boolean getBillingInstrExist( int index, boolean defaultValue )
   {
      return _BillingInstrExist[index] == null ? defaultValue : _BillingInstrExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicate if BillingInstr record Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicate if BillingInstr record Exist values.
    */
   public final Boolean[] getBillingInstrExistArray()
   {
      return _BillingInstrExist;
   }
    
   /**
    * Gets the Flag that indicate if ReportGroup record Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicate if ReportGroup record Exist or null.
    */
   public final Boolean getReportGroupExist( int index )
   {
      return _ReportGroupExist[index];
   }
    
   /**
    * Gets the Flag that indicate if ReportGroup record Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicate if ReportGroup record Exist or the specified default value.
    */
   public final boolean getReportGroupExist( int index, boolean defaultValue )
   {
      return _ReportGroupExist[index] == null ? defaultValue : _ReportGroupExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicate if ReportGroup record Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicate if ReportGroup record Exist values.
    */
   public final Boolean[] getReportGroupExistArray()
   {
      return _ReportGroupExist;
   }
    
   /**
    * Gets the First Child Record Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the First Child Record Effective Date or null.
    */
   public final Date getFirstChildRecDeff( int index )
   {
      return _FirstChildRecDeff[index];
   }
    
   /**
    * Gets the First Child Record Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the First Child Record Effective Date or the specified default value.
    */
   public final Date getFirstChildRecDeff( int index, Date defaultValue )
   {
      return _FirstChildRecDeff[index] == null ? defaultValue : _FirstChildRecDeff[index];
   }
    
   /**
    * Gets the array of First Child Record Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of First Child Record Effective Date values.
    */
   public final Date[] getFirstChildRecDeffArray()
   {
      return _FirstChildRecDeff;
   }
    
   /**
    * Gets the ShrAcctFeeConfig Last Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ShrAcctFeeConfig Last Process Date or null.
    */
   public final Date getShrAcctLastProcDate( int index )
   {
      return _ShrAcctLastProcDate[index];
   }
    
   /**
    * Gets the ShrAcctFeeConfig Last Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ShrAcctFeeConfig Last Process Date or the specified default value.
    */
   public final Date getShrAcctLastProcDate( int index, Date defaultValue )
   {
      return _ShrAcctLastProcDate[index] == null ? defaultValue : _ShrAcctLastProcDate[index];
   }
    
   /**
    * Gets the array of ShrAcctFeeConfig Last Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ShrAcctFeeConfig Last Process Date values.
    */
   public final Date[] getShrAcctLastProcDateArray()
   {
      return _ShrAcctLastProcDate;
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
      
      _EntityID = resizeArray( _EntityID, _RepeatCount );
      _WhereUseKey = resizeArray( _WhereUseKey, _RepeatCount );
      _HoldingCoName = resizeArray( _HoldingCoName, _RepeatCount );
      _Deff = resizeArray( _Deff, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _AggrMethod = resizeArray( _AggrMethod, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _GBCD = resizeArray( _GBCD, _RepeatCount );
      _CoUsage = resizeArray( _CoUsage, _RepeatCount );
      _LangCode = resizeArray( _LangCode, _RepeatCount );
      _EntityWhereUseRID = resizeArray( _EntityWhereUseRID, _RepeatCount );
      _EntityWhereUseVer = resizeArray( _EntityWhereUseVer, _RepeatCount );
      _FeeModelExist = resizeArray( _FeeModelExist, _RepeatCount );
      _FeeAggregationExist = resizeArray( _FeeAggregationExist, _RepeatCount );
      _BillingInstrExist = resizeArray( _BillingInstrExist, _RepeatCount );
      _ReportGroupExist = resizeArray( _ReportGroupExist, _RepeatCount );
      _FirstChildRecDeff = resizeArray( _FirstChildRecDeff, _RepeatCount );
      _ShrAcctLastProcDate = resizeArray( _ShrAcctLastProcDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _EntityID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WhereUseKey[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HoldingCoName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Deff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AggrMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GBCD[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CoUsage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LangCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityWhereUseRID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EntityWhereUseVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FeeModelExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeAggregationExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BillingInstrExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ReportGroupExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FirstChildRecDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ShrAcctLastProcDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
