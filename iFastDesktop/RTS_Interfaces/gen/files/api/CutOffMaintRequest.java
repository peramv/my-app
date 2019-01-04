// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Level Cut Off Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/CutOffMaint.doc">CutOffMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class CutOffMaintRequest extends IFastRequest implements Serializable
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
   private String _CompanyID = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Entity ID member variable.
    */
   private String _EntityID = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * FundGroup member array.
    */
   private String[] _FundGroup = new String[25];
            
   /**
    * Cut Off Time Type member array.
    */
   private String[] _CutOffTimeType = new String[25];
            
   /**
    * Cut Off Time member array.
    */
   private String[] _CutOffTime = new String[25];
            
   /**
    * AcctLevelCutOffTime recid member array.
    */
   private Integer[] _CutOffRid = new Integer[25];
            
   /**
    * AcctLevelCutOffTime version number member array.
    */
   private Integer[] _CutOffVersion = new Integer[25];
            
   /**
    * Level member array.
    */
   private String[] _Level = new String[25];
            
   /**
    * Cut Off Time Zone member array.
    */
   private String[] _CutOffTimeZone = new String[25];
            
   /**
    * Trade Lead Days member array.
    */
   private Integer[] _TradeLeadDays = new Integer[25];
            
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = new String[25];
            
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = new String[25];
            

   /**
    * Constructs the CutOffMaintRequest object.
    * 
    */
   CutOffMaintRequest()
   {
      super ( 349 );
   }

   /**
    * Constructs the CutOffMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   CutOffMaintRequest( String hostEncoding )
   {
      super ( 349, hostEncoding );
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
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
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
    * Sets the Entity ID field for the request.
    * 
    * @param value  Value that the Entity ID will be set to.
    */
   public final void setEntityID( String value )
   {
      assertUnsent();
      _EntityID = value;
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
    * Sets the FundGroup field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the FundGroup will be set to.
    */
   public final void setFundGroup( int index, String value )
   {
      assertUnsent();
      _FundGroup[index] = value;
   }
	
   /**
    * Sets the Cut Off Time Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Cut Off Time Type will be set to.
    */
   public final void setCutOffTimeType( int index, String value )
   {
      assertUnsent();
      _CutOffTimeType[index] = value;
   }
	
   /**
    * Sets the Cut Off Time field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Cut Off Time will be set to.
    */
   public final void setCutOffTime( int index, String value )
   {
      assertUnsent();
      _CutOffTime[index] = value;
   }
	
   /**
    * Sets the AcctLevelCutOffTime recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AcctLevelCutOffTime recid will be set to.
    */
   public final void setCutOffRid( int index, Integer value )
   {
      assertUnsent();
      _CutOffRid[index] = value;
   }
	
   /**
    * Sets the AcctLevelCutOffTime version number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AcctLevelCutOffTime version number will be set to.
    */
   public final void setCutOffVersion( int index, Integer value )
   {
      assertUnsent();
      _CutOffVersion[index] = value;
   }
	
   /**
    * Sets the Level field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Level will be set to.
    */
   public final void setLevel( int index, String value )
   {
      assertUnsent();
      _Level[index] = value;
   }
	
   /**
    * Sets the Cut Off Time Zone field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Cut Off Time Zone will be set to.
    */
   public final void setCutOffTimeZone( int index, String value )
   {
      assertUnsent();
      _CutOffTimeZone[index] = value;
   }
	
   /**
    * Sets the Trade Lead Days field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Trade Lead Days will be set to.
    */
   public final void setTradeLeadDays( int index, Integer value )
   {
      assertUnsent();
      _TradeLeadDays[index] = value;
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
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _EntityID );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _FundGroup[x] );
         requestBuffer.appendField( _CutOffTimeType[x] );
         requestBuffer.appendField( _CutOffTime[x] );
         requestBuffer.appendField( _CutOffRid[x] );
         requestBuffer.appendField( _CutOffVersion[x] );
         requestBuffer.appendField( _Level[x] );
         requestBuffer.appendField( _CutOffTimeZone[x] );
         requestBuffer.appendField( _TradeLeadDays[x] );
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _ClassCode[x] );
      }
   }

}

