
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Shareholder remarks view.
 * For additional view information see <A HREF="../../../../viewspecs/ShrRemarksInq.doc">ShrRemarksInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrRemarksInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Remark is about a transaction member array.
    */
   private Boolean[] _TransNote = null;
   
   /**
    * Remarks line 1 member array.
    */
   private String[] _Remark1 = null;
   
   /**
    * Remarks line 2 member array.
    */
   private String[] _Remark2 = null;
   
   /**
    * Remarks line 3 member array.
    */
   private String[] _Remark3 = null;
   
   /**
    * Remarks line 4 member array.
    */
   private String[] _Remark4 = null;
   
   /**
    * Remarks line 5 member array.
    */
   private String[] _Remark5 = null;
   
   /**
    * Remarks line 6 member array.
    */
   private String[] _Remark6 = null;
   
   /**
    * Remarks line 7 member array.
    */
   private String[] _Remark7 = null;
   
   /**
    * Remarks line 8 member array.
    */
   private String[] _Remark8 = null;
   
   /**
    * Remarks line 9 member array.
    */
   private String[] _Remark9 = null;
   
   /**
    * Remarks line 10 member array.
    */
   private String[] _Remark10 = null;
   
   /**
    * Note status code member array.
    */
   private Boolean[] _Active = null;
   
   /**
    * Date remark is effective from member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Date remark was created member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User id who created remark member array.
    */
   private String[] _Username = null;
   
   /**
    * Date remarks was last modified member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * User id who last modified remark member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Remarks-Detl Version Number member array.
    */
   private Integer[] _RemarksDetlVer = null;
   
   /**
    * Recid of Remarks-Detl record member array.
    */
   private Integer[] _RemarksDetlRid = null;
   
   /**
    * Remark Type member array.
    */
   private String[] _RemarkType = null;
   
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = null;
   

   /**
    * Constructs the ShrRemarksInqView object.
    * 
    */
   public ShrRemarksInqView()
   {
      super ( new ShrRemarksInqRequest() );
   }

   /**
    * Constructs the ShrRemarksInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShrRemarksInqView( String hostEncoding )
   {
      super ( new ShrRemarksInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ShrRemarksInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShrRemarksInqRequest object.
    */
   public final ShrRemarksInqRequest getRequest()
   {
      return (ShrRemarksInqRequest)getIFastRequest();
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
    * Gets the Remark is about a transaction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remark is about a transaction or null.
    */
   public final Boolean getTransNote( int index )
   {
      return _TransNote[index];
   }
    
   /**
    * Gets the Remark is about a transaction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remark is about a transaction or the specified default value.
    */
   public final boolean getTransNote( int index, boolean defaultValue )
   {
      return _TransNote[index] == null ? defaultValue : _TransNote[index].booleanValue();
   }
    
   /**
    * Gets the array of Remark is about a transaction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remark is about a transaction values.
    */
   public final Boolean[] getTransNoteArray()
   {
      return _TransNote;
   }
    
   /**
    * Gets the Remarks line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 1 or null.
    */
   public final String getRemark1( int index )
   {
      return _Remark1[index];
   }
    
   /**
    * Gets the Remarks line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 1 or the specified default value.
    */
   public final String getRemark1( int index, String defaultValue )
   {
      return _Remark1[index] == null ? defaultValue : _Remark1[index];
   }
    
   /**
    * Gets the array of Remarks line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 1 values.
    */
   public final String[] getRemark1Array()
   {
      return _Remark1;
   }
    
   /**
    * Gets the Remarks line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 2 or null.
    */
   public final String getRemark2( int index )
   {
      return _Remark2[index];
   }
    
   /**
    * Gets the Remarks line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 2 or the specified default value.
    */
   public final String getRemark2( int index, String defaultValue )
   {
      return _Remark2[index] == null ? defaultValue : _Remark2[index];
   }
    
   /**
    * Gets the array of Remarks line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 2 values.
    */
   public final String[] getRemark2Array()
   {
      return _Remark2;
   }
    
   /**
    * Gets the Remarks line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 3 or null.
    */
   public final String getRemark3( int index )
   {
      return _Remark3[index];
   }
    
   /**
    * Gets the Remarks line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 3 or the specified default value.
    */
   public final String getRemark3( int index, String defaultValue )
   {
      return _Remark3[index] == null ? defaultValue : _Remark3[index];
   }
    
   /**
    * Gets the array of Remarks line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 3 values.
    */
   public final String[] getRemark3Array()
   {
      return _Remark3;
   }
    
   /**
    * Gets the Remarks line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 4 or null.
    */
   public final String getRemark4( int index )
   {
      return _Remark4[index];
   }
    
   /**
    * Gets the Remarks line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 4 or the specified default value.
    */
   public final String getRemark4( int index, String defaultValue )
   {
      return _Remark4[index] == null ? defaultValue : _Remark4[index];
   }
    
   /**
    * Gets the array of Remarks line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 4 values.
    */
   public final String[] getRemark4Array()
   {
      return _Remark4;
   }
    
   /**
    * Gets the Remarks line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 5 or null.
    */
   public final String getRemark5( int index )
   {
      return _Remark5[index];
   }
    
   /**
    * Gets the Remarks line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 5 or the specified default value.
    */
   public final String getRemark5( int index, String defaultValue )
   {
      return _Remark5[index] == null ? defaultValue : _Remark5[index];
   }
    
   /**
    * Gets the array of Remarks line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 5 values.
    */
   public final String[] getRemark5Array()
   {
      return _Remark5;
   }
    
   /**
    * Gets the Remarks line 6 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 6 or null.
    */
   public final String getRemark6( int index )
   {
      return _Remark6[index];
   }
    
   /**
    * Gets the Remarks line 6 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 6 or the specified default value.
    */
   public final String getRemark6( int index, String defaultValue )
   {
      return _Remark6[index] == null ? defaultValue : _Remark6[index];
   }
    
   /**
    * Gets the array of Remarks line 6 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 6 values.
    */
   public final String[] getRemark6Array()
   {
      return _Remark6;
   }
    
   /**
    * Gets the Remarks line 7 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 7 or null.
    */
   public final String getRemark7( int index )
   {
      return _Remark7[index];
   }
    
   /**
    * Gets the Remarks line 7 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 7 or the specified default value.
    */
   public final String getRemark7( int index, String defaultValue )
   {
      return _Remark7[index] == null ? defaultValue : _Remark7[index];
   }
    
   /**
    * Gets the array of Remarks line 7 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 7 values.
    */
   public final String[] getRemark7Array()
   {
      return _Remark7;
   }
    
   /**
    * Gets the Remarks line 8 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 8 or null.
    */
   public final String getRemark8( int index )
   {
      return _Remark8[index];
   }
    
   /**
    * Gets the Remarks line 8 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 8 or the specified default value.
    */
   public final String getRemark8( int index, String defaultValue )
   {
      return _Remark8[index] == null ? defaultValue : _Remark8[index];
   }
    
   /**
    * Gets the array of Remarks line 8 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 8 values.
    */
   public final String[] getRemark8Array()
   {
      return _Remark8;
   }
    
   /**
    * Gets the Remarks line 9 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 9 or null.
    */
   public final String getRemark9( int index )
   {
      return _Remark9[index];
   }
    
   /**
    * Gets the Remarks line 9 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 9 or the specified default value.
    */
   public final String getRemark9( int index, String defaultValue )
   {
      return _Remark9[index] == null ? defaultValue : _Remark9[index];
   }
    
   /**
    * Gets the array of Remarks line 9 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 9 values.
    */
   public final String[] getRemark9Array()
   {
      return _Remark9;
   }
    
   /**
    * Gets the Remarks line 10 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 10 or null.
    */
   public final String getRemark10( int index )
   {
      return _Remark10[index];
   }
    
   /**
    * Gets the Remarks line 10 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 10 or the specified default value.
    */
   public final String getRemark10( int index, String defaultValue )
   {
      return _Remark10[index] == null ? defaultValue : _Remark10[index];
   }
    
   /**
    * Gets the array of Remarks line 10 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 10 values.
    */
   public final String[] getRemark10Array()
   {
      return _Remark10;
   }
    
   /**
    * Gets the Note status code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Note status code or null.
    */
   public final Boolean getActive( int index )
   {
      return _Active[index];
   }
    
   /**
    * Gets the Note status code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Note status code or the specified default value.
    */
   public final boolean getActive( int index, boolean defaultValue )
   {
      return _Active[index] == null ? defaultValue : _Active[index].booleanValue();
   }
    
   /**
    * Gets the array of Note status code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Note status code values.
    */
   public final Boolean[] getActiveArray()
   {
      return _Active;
   }
    
   /**
    * Gets the Date remark is effective from field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date remark is effective from or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Date remark is effective from field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date remark is effective from or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Date remark is effective from fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date remark is effective from values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Date remark was created field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date remark was created or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date remark was created field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date remark was created or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date remark was created fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date remark was created values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the User id who created remark field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User id who created remark or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the User id who created remark field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User id who created remark or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of User id who created remark fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User id who created remark values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Date remarks was last modified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date remarks was last modified or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Date remarks was last modified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date remarks was last modified or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Date remarks was last modified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date remarks was last modified values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the User id who last modified remark field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User id who last modified remark or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the User id who last modified remark field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User id who last modified remark or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of User id who last modified remark fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User id who last modified remark values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Remarks-Detl Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks-Detl Version Number or null.
    */
   public final Integer getRemarksDetlVer( int index )
   {
      return _RemarksDetlVer[index];
   }
    
   /**
    * Gets the Remarks-Detl Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks-Detl Version Number or the specified default value.
    */
   public final int getRemarksDetlVer( int index, int defaultValue )
   {
      return _RemarksDetlVer[index] == null ? defaultValue : _RemarksDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of Remarks-Detl Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks-Detl Version Number values.
    */
   public final Integer[] getRemarksDetlVerArray()
   {
      return _RemarksDetlVer;
   }
    
   /**
    * Gets the Recid of Remarks-Detl record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recid of Remarks-Detl record or null.
    */
   public final Integer getRemarksDetlRid( int index )
   {
      return _RemarksDetlRid[index];
   }
    
   /**
    * Gets the Recid of Remarks-Detl record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recid of Remarks-Detl record or the specified default value.
    */
   public final int getRemarksDetlRid( int index, int defaultValue )
   {
      return _RemarksDetlRid[index] == null ? defaultValue : _RemarksDetlRid[index].intValue();
   }
    
   /**
    * Gets the array of Recid of Remarks-Detl record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recid of Remarks-Detl record values.
    */
   public final Integer[] getRemarksDetlRidArray()
   {
      return _RemarksDetlRid;
   }
    
   /**
    * Gets the Remark Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remark Type or null.
    */
   public final String getRemarkType( int index )
   {
      return _RemarkType[index];
   }
    
   /**
    * Gets the Remark Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remark Type or the specified default value.
    */
   public final String getRemarkType( int index, String defaultValue )
   {
      return _RemarkType[index] == null ? defaultValue : _RemarkType[index];
   }
    
   /**
    * Gets the array of Remark Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remark Type values.
    */
   public final String[] getRemarkTypeArray()
   {
      return _RemarkType;
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getAccountNum( int index )
   {
      return _AccountNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getAccountNum( int index, String defaultValue )
   {
      return _AccountNum[index] == null ? defaultValue : _AccountNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getAccountNumArray()
   {
      return _AccountNum;
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
      
      _TransNote = resizeArray( _TransNote, _RepeatCount );
      _Remark1 = resizeArray( _Remark1, _RepeatCount );
      _Remark2 = resizeArray( _Remark2, _RepeatCount );
      _Remark3 = resizeArray( _Remark3, _RepeatCount );
      _Remark4 = resizeArray( _Remark4, _RepeatCount );
      _Remark5 = resizeArray( _Remark5, _RepeatCount );
      _Remark6 = resizeArray( _Remark6, _RepeatCount );
      _Remark7 = resizeArray( _Remark7, _RepeatCount );
      _Remark8 = resizeArray( _Remark8, _RepeatCount );
      _Remark9 = resizeArray( _Remark9, _RepeatCount );
      _Remark10 = resizeArray( _Remark10, _RepeatCount );
      _Active = resizeArray( _Active, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _RemarksDetlVer = resizeArray( _RemarksDetlVer, _RepeatCount );
      _RemarksDetlRid = resizeArray( _RemarksDetlRid, _RepeatCount );
      _RemarkType = resizeArray( _RemarkType, _RepeatCount );
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TransNote[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Remark1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remark2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remark3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remark4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remark5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remark6[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remark7[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remark8[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remark9[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remark10[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Active[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RemarksDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RemarksDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RemarkType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
