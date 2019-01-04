
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Distribution Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundDistribInq.doc">FundDistribInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundDistribInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Distribution Type member array.
    */
   private String[] _DistribType = null;
   
   /**
    * Default Investment Option member array.
    */
   private String[] _DefInvestOpt = null;
   
   /**
    * Override Option member array.
    */
   private String[] _OverrideOpt = null;
   
   /**
    * Last Dividend Date member array.
    */
   private Date[] _LastDivdDate = null;
   

   /**
    * Constructs the FundDistribInqView object.
    * 
    */
   public FundDistribInqView()
   {
      super ( new FundDistribInqRequest() );
   }

   /**
    * Constructs the FundDistribInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundDistribInqView( String hostEncoding )
   {
      super ( new FundDistribInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundDistribInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundDistribInqRequest object.
    */
   public final FundDistribInqRequest getRequest()
   {
      return (FundDistribInqRequest)getIFastRequest();
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
    * Gets the Distribution Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distribution Type or null.
    */
   public final String getDistribType( int index )
   {
      return _DistribType[index];
   }
    
   /**
    * Gets the Distribution Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution Type or the specified default value.
    */
   public final String getDistribType( int index, String defaultValue )
   {
      return _DistribType[index] == null ? defaultValue : _DistribType[index];
   }
    
   /**
    * Gets the array of Distribution Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distribution Type values.
    */
   public final String[] getDistribTypeArray()
   {
      return _DistribType;
   }
    
   /**
    * Gets the Default Investment Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Default Investment Option or null.
    */
   public final String getDefInvestOpt( int index )
   {
      return _DefInvestOpt[index];
   }
    
   /**
    * Gets the Default Investment Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Investment Option or the specified default value.
    */
   public final String getDefInvestOpt( int index, String defaultValue )
   {
      return _DefInvestOpt[index] == null ? defaultValue : _DefInvestOpt[index];
   }
    
   /**
    * Gets the array of Default Investment Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Default Investment Option values.
    */
   public final String[] getDefInvestOptArray()
   {
      return _DefInvestOpt;
   }
    
   /**
    * Gets the Override Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Option or null.
    */
   public final String getOverrideOpt( int index )
   {
      return _OverrideOpt[index];
   }
    
   /**
    * Gets the Override Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Option or the specified default value.
    */
   public final String getOverrideOpt( int index, String defaultValue )
   {
      return _OverrideOpt[index] == null ? defaultValue : _OverrideOpt[index];
   }
    
   /**
    * Gets the array of Override Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Option values.
    */
   public final String[] getOverrideOptArray()
   {
      return _OverrideOpt;
   }
    
   /**
    * Gets the Last Dividend Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Dividend Date or null.
    */
   public final Date getLastDivdDate( int index )
   {
      return _LastDivdDate[index];
   }
    
   /**
    * Gets the Last Dividend Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Dividend Date or the specified default value.
    */
   public final Date getLastDivdDate( int index, Date defaultValue )
   {
      return _LastDivdDate[index] == null ? defaultValue : _LastDivdDate[index];
   }
    
   /**
    * Gets the array of Last Dividend Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Dividend Date values.
    */
   public final Date[] getLastDivdDateArray()
   {
      return _LastDivdDate;
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
      
      _DistribType = resizeArray( _DistribType, _RepeatCount );
      _DefInvestOpt = resizeArray( _DefInvestOpt, _RepeatCount );
      _OverrideOpt = resizeArray( _OverrideOpt, _RepeatCount );
      _LastDivdDate = resizeArray( _LastDivdDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _DistribType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DefInvestOpt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OverrideOpt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastDivdDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
