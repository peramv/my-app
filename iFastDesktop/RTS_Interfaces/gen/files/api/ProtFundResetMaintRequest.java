// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Protected Fund Reset Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/ProtFundResetMaint.doc">ProtFundResetMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class ProtFundResetMaintRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
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
    * Activity member variable.
    */
   private String _Actitvity = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = new String[25];
            
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = new String[25];
            
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = new String[25];
            
   /**
    * Reset Date member array.
    */
   private Date[] _ResetDate = new Date[25];
            
   /**
    * Reset Type member array.
    */
   private String[] _ResetType = new String[25];
            
   /**
    * Canellred Reset ID member array.
    */
   private Integer[] _CanResetId = new Integer[25];
            
   /**
    * Batch Effective Date member array.
    */
   private Date[] _BatchEffective = new Date[25];
            
   /**
    * Batch Name member array.
    */
   private String[] _BatchName = new String[25];
            
   /**
    * Trace member array.
    */
   private Integer[] _Trace = new Integer[25];
            
   /**
    * Version member array.
    */
   private Integer[] _Version = new Integer[25];
            
   /**
    * Protect Reset Recid member array.
    */
   private Integer[] _ProtectResetRid = new Integer[25];
            

   /**
    * Constructs the ProtFundResetMaintRequest object.
    * 
    */
   ProtFundResetMaintRequest()
   {
      super ( 244 );
   }

   /**
    * Constructs the ProtFundResetMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ProtFundResetMaintRequest( String hostEncoding )
   {
      super ( 244, hostEncoding );
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
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
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
    * Sets the Activity field for the request.
    * 
    * @param value  Value that the Activity will be set to.
    */
   public final void setActitvity( String value )
   {
      assertUnsent();
      _Actitvity = value;
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
    * Sets the Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Account Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( int index, String value )
   {
      assertUnsent();
      _AccountNum[index] = value;
   }
	
   /**
    * Sets the Fund Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setFundCode( int index, String value )
   {
      assertUnsent();
      _FundCode[index] = value;
   }
	
   /**
    * Sets the Class Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Class Code will be set to.
    */
   public final void setClassCode( int index, String value )
   {
      assertUnsent();
      _ClassCode[index] = value;
   }
	
   /**
    * Sets the Reset Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reset Date will be set to.
    */
   public final void setResetDate( int index, Date value )
   {
      assertUnsent();
      _ResetDate[index] = value;
   }
	
   /**
    * Sets the Reset Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reset Type will be set to.
    */
   public final void setResetType( int index, String value )
   {
      assertUnsent();
      _ResetType[index] = value;
   }
	
   /**
    * Sets the Canellred Reset ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Canellred Reset ID will be set to.
    */
   public final void setCanResetId( int index, Integer value )
   {
      assertUnsent();
      _CanResetId[index] = value;
   }
	
   /**
    * Sets the Batch Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Batch Effective Date will be set to.
    */
   public final void setBatchEffective( int index, Date value )
   {
      assertUnsent();
      _BatchEffective[index] = value;
   }
	
   /**
    * Sets the Batch Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Batch Name will be set to.
    */
   public final void setBatchName( int index, String value )
   {
      assertUnsent();
      _BatchName[index] = value;
   }
	
   /**
    * Sets the Trace field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Trace will be set to.
    */
   public final void setTrace( int index, Integer value )
   {
      assertUnsent();
      _Trace[index] = value;
   }
	
   /**
    * Sets the Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Version will be set to.
    */
   public final void setVersion( int index, Integer value )
   {
      assertUnsent();
      _Version[index] = value;
   }
	
   /**
    * Sets the Protect Reset Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Protect Reset Recid will be set to.
    */
   public final void setProtectResetRid( int index, Integer value )
   {
      assertUnsent();
      _ProtectResetRid[index] = value;
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
      requestBuffer.appendField( _Actitvity );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _AccountNum[x] );
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _ClassCode[x] );
         requestBuffer.appendField( _ResetDate[x] );
         requestBuffer.appendField( _ResetType[x] );
         requestBuffer.appendField( _CanResetId[x] );
         requestBuffer.appendField( _BatchEffective[x] );
         requestBuffer.appendField( _BatchName[x] );
         requestBuffer.appendField( _Trace[x] );
         requestBuffer.appendField( _Version[x] );
         requestBuffer.appendField( _ProtectResetRid[x] );
      }
   }

}

