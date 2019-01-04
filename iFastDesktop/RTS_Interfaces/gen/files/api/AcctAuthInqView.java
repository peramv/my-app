
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Authorization Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctAuthInq.doc">AcctAuthInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctAuthInqView extends IFastView implements Serializable
{

   /**
    * Duplicate Exist member variable.
    */
   private Boolean _DuplicateExist = null;
   
   private int _RepeatCount = 0;
   
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
    * Fund Indicator member array.
    */
   private String[] _FundIndc = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _rxDeff = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _rxStopDate = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Mod Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Acct-Auth Version member array.
    */
   private Integer[] _AcctAuthVer = null;
   
   /**
    * Acct-Auth RID member array.
    */
   private Integer[] _rxAcctAuthRID = null;
   

   /**
    * Constructs the AcctAuthInqView object.
    * 
    */
   public AcctAuthInqView()
   {
      super ( new AcctAuthInqRequest() );
   }

   /**
    * Constructs the AcctAuthInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctAuthInqView( String hostEncoding )
   {
      super ( new AcctAuthInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctAuthInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctAuthInqRequest object.
    */
   public final AcctAuthInqRequest getRequest()
   {
      return (AcctAuthInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Duplicate Exist field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Duplicate Exist or null.
    */
   public final Boolean getDuplicateExist()
   {
      return _DuplicateExist;
   }
	
   /**
    * Gets the Duplicate Exist field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Duplicate Exist or the specified default value.
    */
   public final boolean getDuplicateExist( boolean defaultValue )
   {
      return _DuplicateExist == null ? defaultValue : _DuplicateExist.booleanValue();
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
    * Gets the Fund Indicator field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Indicator or null.
    */
   public final String getFundIndc( int index )
   {
      return _FundIndc[index];
   }
    
   /**
    * Gets the Fund Indicator field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Indicator or the specified default value.
    */
   public final String getFundIndc( int index, String defaultValue )
   {
      return _FundIndc[index] == null ? defaultValue : _FundIndc[index];
   }
    
   /**
    * Gets the array of Fund Indicator fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Indicator values.
    */
   public final String[] getFundIndcArray()
   {
      return _FundIndc;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getrxDeff( int index )
   {
      return _rxDeff[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getrxDeff( int index, Date defaultValue )
   {
      return _rxDeff[index] == null ? defaultValue : _rxDeff[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getrxDeffArray()
   {
      return _rxDeff;
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getrxStopDate( int index )
   {
      return _rxStopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getrxStopDate( int index, Date defaultValue )
   {
      return _rxStopDate[index] == null ? defaultValue : _rxStopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getrxStopDateArray()
   {
      return _rxStopDate;
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
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Name or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Name values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
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
    * Gets the Acct-Auth Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-Auth Version or null.
    */
   public final Integer getAcctAuthVer( int index )
   {
      return _AcctAuthVer[index];
   }
    
   /**
    * Gets the Acct-Auth Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-Auth Version or the specified default value.
    */
   public final int getAcctAuthVer( int index, int defaultValue )
   {
      return _AcctAuthVer[index] == null ? defaultValue : _AcctAuthVer[index].intValue();
   }
    
   /**
    * Gets the array of Acct-Auth Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-Auth Version values.
    */
   public final Integer[] getAcctAuthVerArray()
   {
      return _AcctAuthVer;
   }
    
   /**
    * Gets the Acct-Auth RID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-Auth RID or null.
    */
   public final Integer getrxAcctAuthRID( int index )
   {
      return _rxAcctAuthRID[index];
   }
    
   /**
    * Gets the Acct-Auth RID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-Auth RID or the specified default value.
    */
   public final int getrxAcctAuthRID( int index, int defaultValue )
   {
      return _rxAcctAuthRID[index] == null ? defaultValue : _rxAcctAuthRID[index].intValue();
   }
    
   /**
    * Gets the array of Acct-Auth RID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-Auth RID values.
    */
   public final Integer[] getrxAcctAuthRIDArray()
   {
      return _rxAcctAuthRID;
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
      _DuplicateExist = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _AgencyCode = resizeArray( _AgencyCode, _RepeatCount );
      _BranchCode = resizeArray( _BranchCode, _RepeatCount );
      _AgentCode = resizeArray( _AgentCode, _RepeatCount );
      _FundIndc = resizeArray( _FundIndc, _RepeatCount );
      _rxDeff = resizeArray( _rxDeff, _RepeatCount );
      _rxStopDate = resizeArray( _rxStopDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _AcctAuthVer = resizeArray( _AcctAuthVer, _RepeatCount );
      _rxAcctAuthRID = resizeArray( _rxAcctAuthRID, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AgencyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AgentCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundIndc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _rxStopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctAuthVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxAcctAuthRID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
