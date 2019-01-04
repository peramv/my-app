
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Portfolio Plan Information Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/PortfolioPlanInfoInq.doc">PortfolioPlanInfoInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PortfolioPlanInfoInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * ProdPortfolioPlanUUID member array.
    */
   private String[] _ProdPortfolioPlanUUID = null;
   
   /**
    * Plan Code member array.
    */
   private String[] _PlanCode = null;
   
   /**
    * Name member array.
    */
   private String[] _Name = null;
   
   /**
    * Default Plan member array.
    */
   private Boolean[] _DefaultPlan = null;
   

   /**
    * Constructs the PortfolioPlanInfoInqView object.
    * 
    */
   public PortfolioPlanInfoInqView()
   {
      super ( new PortfolioPlanInfoInqRequest() );
   }

   /**
    * Constructs the PortfolioPlanInfoInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PortfolioPlanInfoInqView( String hostEncoding )
   {
      super ( new PortfolioPlanInfoInqRequest( hostEncoding ) );
   }

   /**
    * Gets the PortfolioPlanInfoInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PortfolioPlanInfoInqRequest object.
    */
   public final PortfolioPlanInfoInqRequest getRequest()
   {
      return (PortfolioPlanInfoInqRequest)getIFastRequest();
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
    * Gets the ProdPortfolioPlanUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProdPortfolioPlanUUID or null.
    */
   public final String getProdPortfolioPlanUUID( int index )
   {
      return _ProdPortfolioPlanUUID[index];
   }
    
   /**
    * Gets the ProdPortfolioPlanUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProdPortfolioPlanUUID or the specified default value.
    */
   public final String getProdPortfolioPlanUUID( int index, String defaultValue )
   {
      return _ProdPortfolioPlanUUID[index] == null ? defaultValue : _ProdPortfolioPlanUUID[index];
   }
    
   /**
    * Gets the array of ProdPortfolioPlanUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProdPortfolioPlanUUID values.
    */
   public final String[] getProdPortfolioPlanUUIDArray()
   {
      return _ProdPortfolioPlanUUID;
   }
    
   /**
    * Gets the Plan Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Plan Code or null.
    */
   public final String getPlanCode( int index )
   {
      return _PlanCode[index];
   }
    
   /**
    * Gets the Plan Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Plan Code or the specified default value.
    */
   public final String getPlanCode( int index, String defaultValue )
   {
      return _PlanCode[index] == null ? defaultValue : _PlanCode[index];
   }
    
   /**
    * Gets the array of Plan Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Plan Code values.
    */
   public final String[] getPlanCodeArray()
   {
      return _PlanCode;
   }
    
   /**
    * Gets the Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Name or null.
    */
   public final String getName( int index )
   {
      return _Name[index];
   }
    
   /**
    * Gets the Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name or the specified default value.
    */
   public final String getName( int index, String defaultValue )
   {
      return _Name[index] == null ? defaultValue : _Name[index];
   }
    
   /**
    * Gets the array of Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Name values.
    */
   public final String[] getNameArray()
   {
      return _Name;
   }
    
   /**
    * Gets the Default Plan field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Default Plan or null.
    */
   public final Boolean getDefaultPlan( int index )
   {
      return _DefaultPlan[index];
   }
    
   /**
    * Gets the Default Plan field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Plan or the specified default value.
    */
   public final boolean getDefaultPlan( int index, boolean defaultValue )
   {
      return _DefaultPlan[index] == null ? defaultValue : _DefaultPlan[index].booleanValue();
   }
    
   /**
    * Gets the array of Default Plan fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Default Plan values.
    */
   public final Boolean[] getDefaultPlanArray()
   {
      return _DefaultPlan;
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
      
      _ProdPortfolioPlanUUID = resizeArray( _ProdPortfolioPlanUUID, _RepeatCount );
      _PlanCode = resizeArray( _PlanCode, _RepeatCount );
      _Name = resizeArray( _Name, _RepeatCount );
      _DefaultPlan = resizeArray( _DefaultPlan, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ProdPortfolioPlanUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PlanCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Name[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DefaultPlan[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
