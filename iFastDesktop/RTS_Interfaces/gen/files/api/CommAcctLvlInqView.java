
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * SplitComm Inquiry at Account Level view.
 * For additional view information see <A HREF="../../../../viewspecs/CommAcctLvlInq.doc">CommAcctLvlInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class CommAcctLvlInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Comm Level or Rectype member array.
    */
   private Integer[] _CommLevel = null;
   
   /**
    * Gross or Net member array.
    */
   private Boolean[] _GrossNet = null;
   
   /**
    * Pay Type member array.
    */
   private String[] _PayType = null;
   
   /**
    * Split Percentage member array.
    */
   private String[] _CommPercent = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Agency Code member array.
    */
   private String[] _AgencyCode = null;
   
   /**
    * Branch Code member array.
    */
   private String[] _BranchCode = null;
   
   /**
    * Agent Code member array.
    */
   private String[] _AgentCode = null;
   
   /**
    * Entity Name member array.
    */
   private String[] _EntityName = null;
   
   /**
    * Comm Level Description member array.
    */
   private String[] _CommLvlDesc = null;
   
   /**
    * Split Comm Recid member array.
    */
   private Integer[] _SplCommRid = null;
   
   /**
    * Active member array.
    */
   private Boolean[] _Active = null;
   
   /**
    * Commission Broker Name member array.
    */
   private String[] _CommBrokName = null;
   
   /**
    * Commission Branch Name member array.
    */
   private String[] _CommBranName = null;
   
   /**
    * Commission SlsRep Name member array.
    */
   private String[] _CommRepName = null;
   

   /**
    * Constructs the CommAcctLvlInqView object.
    * 
    */
   public CommAcctLvlInqView()
   {
      super ( new CommAcctLvlInqRequest() );
   }

   /**
    * Constructs the CommAcctLvlInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public CommAcctLvlInqView( String hostEncoding )
   {
      super ( new CommAcctLvlInqRequest( hostEncoding ) );
   }

   /**
    * Gets the CommAcctLvlInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The CommAcctLvlInqRequest object.
    */
   public final CommAcctLvlInqRequest getRequest()
   {
      return (CommAcctLvlInqRequest)getIFastRequest();
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
    * Gets the Comm Level or Rectype field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Comm Level or Rectype or null.
    */
   public final Integer getCommLevel( int index )
   {
      return _CommLevel[index];
   }
    
   /**
    * Gets the Comm Level or Rectype field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comm Level or Rectype or the specified default value.
    */
   public final int getCommLevel( int index, int defaultValue )
   {
      return _CommLevel[index] == null ? defaultValue : _CommLevel[index].intValue();
   }
    
   /**
    * Gets the array of Comm Level or Rectype fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Comm Level or Rectype values.
    */
   public final Integer[] getCommLevelArray()
   {
      return _CommLevel;
   }
    
   /**
    * Gets the Gross or Net field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross or Net or null.
    */
   public final Boolean getGrossNet( int index )
   {
      return _GrossNet[index];
   }
    
   /**
    * Gets the Gross or Net field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross or Net or the specified default value.
    */
   public final boolean getGrossNet( int index, boolean defaultValue )
   {
      return _GrossNet[index] == null ? defaultValue : _GrossNet[index].booleanValue();
   }
    
   /**
    * Gets the array of Gross or Net fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross or Net values.
    */
   public final Boolean[] getGrossNetArray()
   {
      return _GrossNet;
   }
    
   /**
    * Gets the Pay Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Type or null.
    */
   public final String getPayType( int index )
   {
      return _PayType[index];
   }
    
   /**
    * Gets the Pay Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Type or the specified default value.
    */
   public final String getPayType( int index, String defaultValue )
   {
      return _PayType[index] == null ? defaultValue : _PayType[index];
   }
    
   /**
    * Gets the array of Pay Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Type values.
    */
   public final String[] getPayTypeArray()
   {
      return _PayType;
   }
    
   /**
    * Gets the Split Percentage field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Percentage or null.
    */
   public final String getCommPercent( int index )
   {
      return _CommPercent[index];
   }
    
   /**
    * Gets the Split Percentage field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Percentage or the specified default value.
    */
   public final String getCommPercent( int index, String defaultValue )
   {
      return _CommPercent[index] == null ? defaultValue : _CommPercent[index];
   }
    
   /**
    * Gets the array of Split Percentage fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Percentage values.
    */
   public final String[] getCommPercentArray()
   {
      return _CommPercent;
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
    * Gets the Agency Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Agency Code or null.
    */
   public final String getAgencyCode( int index )
   {
      return _AgencyCode[index];
   }
    
   /**
    * Gets the Agency Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Agency Code or the specified default value.
    */
   public final String getAgencyCode( int index, String defaultValue )
   {
      return _AgencyCode[index] == null ? defaultValue : _AgencyCode[index];
   }
    
   /**
    * Gets the array of Agency Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Agency Code values.
    */
   public final String[] getAgencyCodeArray()
   {
      return _AgencyCode;
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Code or null.
    */
   public final String getBranchCode( int index )
   {
      return _BranchCode[index];
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Code or the specified default value.
    */
   public final String getBranchCode( int index, String defaultValue )
   {
      return _BranchCode[index] == null ? defaultValue : _BranchCode[index];
   }
    
   /**
    * Gets the array of Branch Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Code values.
    */
   public final String[] getBranchCodeArray()
   {
      return _BranchCode;
   }
    
   /**
    * Gets the Agent Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Agent Code or null.
    */
   public final String getAgentCode( int index )
   {
      return _AgentCode[index];
   }
    
   /**
    * Gets the Agent Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Agent Code or the specified default value.
    */
   public final String getAgentCode( int index, String defaultValue )
   {
      return _AgentCode[index] == null ? defaultValue : _AgentCode[index];
   }
    
   /**
    * Gets the array of Agent Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Agent Code values.
    */
   public final String[] getAgentCodeArray()
   {
      return _AgentCode;
   }
    
   /**
    * Gets the Entity Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Name or null.
    */
   public final String getEntityName( int index )
   {
      return _EntityName[index];
   }
    
   /**
    * Gets the Entity Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Name or the specified default value.
    */
   public final String getEntityName( int index, String defaultValue )
   {
      return _EntityName[index] == null ? defaultValue : _EntityName[index];
   }
    
   /**
    * Gets the array of Entity Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Name values.
    */
   public final String[] getEntityNameArray()
   {
      return _EntityName;
   }
    
   /**
    * Gets the Comm Level Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Comm Level Description or null.
    */
   public final String getCommLvlDesc( int index )
   {
      return _CommLvlDesc[index];
   }
    
   /**
    * Gets the Comm Level Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comm Level Description or the specified default value.
    */
   public final String getCommLvlDesc( int index, String defaultValue )
   {
      return _CommLvlDesc[index] == null ? defaultValue : _CommLvlDesc[index];
   }
    
   /**
    * Gets the array of Comm Level Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Comm Level Description values.
    */
   public final String[] getCommLvlDescArray()
   {
      return _CommLvlDesc;
   }
    
   /**
    * Gets the Split Comm Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Comm Recid or null.
    */
   public final Integer getSplCommRid( int index )
   {
      return _SplCommRid[index];
   }
    
   /**
    * Gets the Split Comm Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Comm Recid or the specified default value.
    */
   public final int getSplCommRid( int index, int defaultValue )
   {
      return _SplCommRid[index] == null ? defaultValue : _SplCommRid[index].intValue();
   }
    
   /**
    * Gets the array of Split Comm Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Comm Recid values.
    */
   public final Integer[] getSplCommRidArray()
   {
      return _SplCommRid;
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
    * Gets the Commission Broker Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Broker Name or null.
    */
   public final String getCommBrokName( int index )
   {
      return _CommBrokName[index];
   }
    
   /**
    * Gets the Commission Broker Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Broker Name or the specified default value.
    */
   public final String getCommBrokName( int index, String defaultValue )
   {
      return _CommBrokName[index] == null ? defaultValue : _CommBrokName[index];
   }
    
   /**
    * Gets the array of Commission Broker Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Broker Name values.
    */
   public final String[] getCommBrokNameArray()
   {
      return _CommBrokName;
   }
    
   /**
    * Gets the Commission Branch Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission Branch Name or null.
    */
   public final String getCommBranName( int index )
   {
      return _CommBranName[index];
   }
    
   /**
    * Gets the Commission Branch Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Branch Name or the specified default value.
    */
   public final String getCommBranName( int index, String defaultValue )
   {
      return _CommBranName[index] == null ? defaultValue : _CommBranName[index];
   }
    
   /**
    * Gets the array of Commission Branch Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission Branch Name values.
    */
   public final String[] getCommBranNameArray()
   {
      return _CommBranName;
   }
    
   /**
    * Gets the Commission SlsRep Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission SlsRep Name or null.
    */
   public final String getCommRepName( int index )
   {
      return _CommRepName[index];
   }
    
   /**
    * Gets the Commission SlsRep Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission SlsRep Name or the specified default value.
    */
   public final String getCommRepName( int index, String defaultValue )
   {
      return _CommRepName[index] == null ? defaultValue : _CommRepName[index];
   }
    
   /**
    * Gets the array of Commission SlsRep Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission SlsRep Name values.
    */
   public final String[] getCommRepNameArray()
   {
      return _CommRepName;
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
      
      _CommLevel = resizeArray( _CommLevel, _RepeatCount );
      _GrossNet = resizeArray( _GrossNet, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _CommPercent = resizeArray( _CommPercent, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _AgencyCode = resizeArray( _AgencyCode, _RepeatCount );
      _BranchCode = resizeArray( _BranchCode, _RepeatCount );
      _AgentCode = resizeArray( _AgentCode, _RepeatCount );
      _EntityName = resizeArray( _EntityName, _RepeatCount );
      _CommLvlDesc = resizeArray( _CommLvlDesc, _RepeatCount );
      _SplCommRid = resizeArray( _SplCommRid, _RepeatCount );
      _Active = resizeArray( _Active, _RepeatCount );
      _CommBrokName = resizeArray( _CommBrokName, _RepeatCount );
      _CommBranName = resizeArray( _CommBranName, _RepeatCount );
      _CommRepName = resizeArray( _CommRepName, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _CommLevel[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _GrossNet[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommPercent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AgencyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AgentCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommLvlDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SplCommRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Active[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CommBrokName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommBranName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommRepName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
