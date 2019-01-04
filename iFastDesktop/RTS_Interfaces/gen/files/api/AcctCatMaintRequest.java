// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Categories Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctCatMaint.doc">AcctCatMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctCatMaintRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * AcctCategory Record ID member array.
    */
   private Integer[] _AcctCatRId = new Integer[25];
            
   /**
    * Category Type member array.
    */
   private String[] _CategoryType = new String[25];
            
   /**
    * Category Value member array.
    */
   private String[] _CatValue = new String[25];
            

   /**
    * Constructs the AcctCatMaintRequest object.
    * 
    */
   AcctCatMaintRequest()
   {
      super ( 246 );
   }

   /**
    * Constructs the AcctCatMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctCatMaintRequest( String hostEncoding )
   {
      super ( 246, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User Id field for the request.
    * 
    * @param value  Value that the User Id will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the Language Code field for the request.
    * 
    * @param value  Value that the Language Code will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company Id field for the request.
    * 
    * @param value  Value that the Company Id will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the RunMode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RunMode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the AcctCategory Record ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AcctCategory Record ID will be set to.
    */
   public final void setAcctCatRId( int index, Integer value )
   {
      assertUnsent();
      _AcctCatRId[index] = value;
   }
	
   /**
    * Sets the Category Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Category Type will be set to.
    */
   public final void setCategoryType( int index, String value )
   {
      assertUnsent();
      _CategoryType[index] = value;
   }
	
   /**
    * Sets the Category Value field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Category Value will be set to.
    */
   public final void setCatValue( int index, String value )
   {
      assertUnsent();
      _CatValue[index] = value;
   }
	
   /**
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _AcctCatRId[x] );
         requestBuffer.appendField( _CategoryType[x] );
         requestBuffer.appendField( _CatValue[x] );
      }
   }

}

