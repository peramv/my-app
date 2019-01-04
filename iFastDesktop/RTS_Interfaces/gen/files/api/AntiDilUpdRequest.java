// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Anti Dilution Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/AntiDilUpd.doc">AntiDilUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class AntiDilUpdRequest extends IFastRequest implements Serializable
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
    * Company ID member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Record Type member array.
    */
   private String[] _RecordType = new String[25];
            
   /**
    * Fee Code member array.
    */
   private String[] _FeeCode = new String[25];
            
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = new String[25];
            
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = new String[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Fee Percent member array.
    */
   private String[] _FeePercent = new String[25];
            
   /**
    * Daily Fee Recid member array.
    */
   private Integer[] _DailyFeeRid = new Integer[25];
            
   /**
    * Version member array.
    */
   private Integer[] _Version = new Integer[25];
            
   /**
    * Fee Type member array.
    */
   private String[] _FeeType = new String[25];
            

   /**
    * Constructs the AntiDilUpdRequest object.
    * 
    */
   AntiDilUpdRequest()
   {
      super ( 285 );
   }

   /**
    * Constructs the AntiDilUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AntiDilUpdRequest( String hostEncoding )
   {
      super ( 285, hostEncoding );
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
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
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
    * Sets the Record Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Record Type will be set to.
    */
   public final void setRecordType( int index, String value )
   {
      assertUnsent();
      _RecordType[index] = value;
   }
	
   /**
    * Sets the Fee Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fee Code will be set to.
    */
   public final void setFeeCode( int index, String value )
   {
      assertUnsent();
      _FeeCode[index] = value;
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
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _EffectiveDate[index] = value;
   }
	
   /**
    * Sets the Stop Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the Fee Percent field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fee Percent will be set to.
    */
   public final void setFeePercent( int index, String value )
   {
      assertUnsent();
      _FeePercent[index] = value;
   }
	
   /**
    * Sets the Daily Fee Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Daily Fee Recid will be set to.
    */
   public final void setDailyFeeRid( int index, Integer value )
   {
      assertUnsent();
      _DailyFeeRid[index] = value;
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
    * Sets the Fee Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fee Type will be set to.
    */
   public final void setFeeType( int index, String value )
   {
      assertUnsent();
      _FeeType[index] = value;
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
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _RecordType[x] );
         requestBuffer.appendField( _FeeCode[x] );
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _ClassCode[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _FeePercent[x] );
         requestBuffer.appendField( _DailyFeeRid[x] );
         requestBuffer.appendField( _Version[x] );
         requestBuffer.appendField( _FeeType[x] );
      }
   }

}

