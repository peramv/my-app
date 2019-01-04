
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * User Access Security view.
 * For additional view information see <A HREF="../../../../viewspecs/UserAccessSecurity.doc">UserAccessSecurity.doc</A>.
 * 
 * @author RTS Generated
 */
public class UserAccessSecurityView extends IFastView implements Serializable
{

   /**
    * ecomm Share Group Access All member variable.
    */
   private Boolean _ShrGrpAccessAll = null;
   
   /**
    * ID Access member variable.
    */
   private String _IDAccess = null;
   
   /**
    * Access All SlsRep member variable.
    */
   private Boolean _AccessAllSlsRep = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Function ID member array.
    */
   private Integer[] _FunctionId = null;
   
   /**
    * Function Active Flag member array.
    */
   private Boolean[] _F_active = null;
   
   /**
    * Inquiry Permission member array.
    */
   private Boolean[] _InqPerm = null;
   
   /**
    * Add Permission member array.
    */
   private Boolean[] _AddPerm = null;
   
   /**
    * Modify Permission member array.
    */
   private Boolean[] _ModPerm = null;
   
   /**
    * Deletion Permission member array.
    */
   private Boolean[] _DelPerm = null;
   
   /**
    * Functional Category Associated with the Menu member array.
    */
   private String[] _FuncCategory = null;
   

   /**
    * Constructs the UserAccessSecurityView object.
    * 
    */
   public UserAccessSecurityView()
   {
      super ( new UserAccessSecurityRequest() );
   }

   /**
    * Constructs the UserAccessSecurityView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public UserAccessSecurityView( String hostEncoding )
   {
      super ( new UserAccessSecurityRequest( hostEncoding ) );
   }

   /**
    * Gets the UserAccessSecurityRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The UserAccessSecurityRequest object.
    */
   public final UserAccessSecurityRequest getRequest()
   {
      return (UserAccessSecurityRequest)getIFastRequest();
   }
        
   /**
    * Gets the ecomm Share Group Access All field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ecomm Share Group Access All or null.
    */
   public final Boolean getShrGrpAccessAll()
   {
      return _ShrGrpAccessAll;
   }
	
   /**
    * Gets the ecomm Share Group Access All field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ecomm Share Group Access All or the specified default value.
    */
   public final boolean getShrGrpAccessAll( boolean defaultValue )
   {
      return _ShrGrpAccessAll == null ? defaultValue : _ShrGrpAccessAll.booleanValue();
   }
                  
   /**
    * Gets the ID Access field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ID Access or null.
    */
   public final String getIDAccess()
   {
      return _IDAccess;
   }
	
   /**
    * Gets the ID Access field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Access or the specified default value.
    */
   public final String getIDAccess( String defaultValue )
   {
      return _IDAccess == null ? defaultValue : _IDAccess;
   }
                  
   /**
    * Gets the Access All SlsRep field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Access All SlsRep or null.
    */
   public final Boolean getAccessAllSlsRep()
   {
      return _AccessAllSlsRep;
   }
	
   /**
    * Gets the Access All SlsRep field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Access All SlsRep or the specified default value.
    */
   public final boolean getAccessAllSlsRep( boolean defaultValue )
   {
      return _AccessAllSlsRep == null ? defaultValue : _AccessAllSlsRep.booleanValue();
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
    * Gets the Function ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Function ID or null.
    */
   public final Integer getFunctionId( int index )
   {
      return _FunctionId[index];
   }
    
   /**
    * Gets the Function ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Function ID or the specified default value.
    */
   public final int getFunctionId( int index, int defaultValue )
   {
      return _FunctionId[index] == null ? defaultValue : _FunctionId[index].intValue();
   }
    
   /**
    * Gets the array of Function ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Function ID values.
    */
   public final Integer[] getFunctionIdArray()
   {
      return _FunctionId;
   }
    
   /**
    * Gets the Function Active Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Function Active Flag or null.
    */
   public final Boolean getF_active( int index )
   {
      return _F_active[index];
   }
    
   /**
    * Gets the Function Active Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Function Active Flag or the specified default value.
    */
   public final boolean getF_active( int index, boolean defaultValue )
   {
      return _F_active[index] == null ? defaultValue : _F_active[index].booleanValue();
   }
    
   /**
    * Gets the array of Function Active Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Function Active Flag values.
    */
   public final Boolean[] getF_activeArray()
   {
      return _F_active;
   }
    
   /**
    * Gets the Inquiry Permission field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Inquiry Permission or null.
    */
   public final Boolean getInqPerm( int index )
   {
      return _InqPerm[index];
   }
    
   /**
    * Gets the Inquiry Permission field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Inquiry Permission or the specified default value.
    */
   public final boolean getInqPerm( int index, boolean defaultValue )
   {
      return _InqPerm[index] == null ? defaultValue : _InqPerm[index].booleanValue();
   }
    
   /**
    * Gets the array of Inquiry Permission fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Inquiry Permission values.
    */
   public final Boolean[] getInqPermArray()
   {
      return _InqPerm;
   }
    
   /**
    * Gets the Add Permission field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Add Permission or null.
    */
   public final Boolean getAddPerm( int index )
   {
      return _AddPerm[index];
   }
    
   /**
    * Gets the Add Permission field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Add Permission or the specified default value.
    */
   public final boolean getAddPerm( int index, boolean defaultValue )
   {
      return _AddPerm[index] == null ? defaultValue : _AddPerm[index].booleanValue();
   }
    
   /**
    * Gets the array of Add Permission fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Add Permission values.
    */
   public final Boolean[] getAddPermArray()
   {
      return _AddPerm;
   }
    
   /**
    * Gets the Modify Permission field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify Permission or null.
    */
   public final Boolean getModPerm( int index )
   {
      return _ModPerm[index];
   }
    
   /**
    * Gets the Modify Permission field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify Permission or the specified default value.
    */
   public final boolean getModPerm( int index, boolean defaultValue )
   {
      return _ModPerm[index] == null ? defaultValue : _ModPerm[index].booleanValue();
   }
    
   /**
    * Gets the array of Modify Permission fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify Permission values.
    */
   public final Boolean[] getModPermArray()
   {
      return _ModPerm;
   }
    
   /**
    * Gets the Deletion Permission field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Deletion Permission or null.
    */
   public final Boolean getDelPerm( int index )
   {
      return _DelPerm[index];
   }
    
   /**
    * Gets the Deletion Permission field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deletion Permission or the specified default value.
    */
   public final boolean getDelPerm( int index, boolean defaultValue )
   {
      return _DelPerm[index] == null ? defaultValue : _DelPerm[index].booleanValue();
   }
    
   /**
    * Gets the array of Deletion Permission fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Deletion Permission values.
    */
   public final Boolean[] getDelPermArray()
   {
      return _DelPerm;
   }
    
   /**
    * Gets the Functional Category Associated with the Menu field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Functional Category Associated with the Menu or null.
    */
   public final String getFuncCategory( int index )
   {
      return _FuncCategory[index];
   }
    
   /**
    * Gets the Functional Category Associated with the Menu field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Functional Category Associated with the Menu or the specified default value.
    */
   public final String getFuncCategory( int index, String defaultValue )
   {
      return _FuncCategory[index] == null ? defaultValue : _FuncCategory[index];
   }
    
   /**
    * Gets the array of Functional Category Associated with the Menu fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Functional Category Associated with the Menu values.
    */
   public final String[] getFuncCategoryArray()
   {
      return _FuncCategory;
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
      _ShrGrpAccessAll = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _IDAccess = responseBuffer.decodeString(responseBuffer.getNextField());
      _AccessAllSlsRep = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _FunctionId = resizeArray( _FunctionId, _RepeatCount );
      _F_active = resizeArray( _F_active, _RepeatCount );
      _InqPerm = resizeArray( _InqPerm, _RepeatCount );
      _AddPerm = resizeArray( _AddPerm, _RepeatCount );
      _ModPerm = resizeArray( _ModPerm, _RepeatCount );
      _DelPerm = resizeArray( _DelPerm, _RepeatCount );
      _FuncCategory = resizeArray( _FuncCategory, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FunctionId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _F_active[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _InqPerm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AddPerm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ModPerm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DelPerm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FuncCategory[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
