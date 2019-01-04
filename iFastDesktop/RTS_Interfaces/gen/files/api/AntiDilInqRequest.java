// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Anti Dilution Levy Inq request.
 * For additional view information see <A HREF="../../../../viewspecs/AntiDilInq.doc">AntiDilInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AntiDilInqRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionID = "";
            
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
    * Record Type member variable.
    */
   private String _RecordType = "";
            
   /**
    * Fee Code member variable.
    */
   private String _FeeCode = "";
            
   /**
    * Fund member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Duplicate Check member variable.
    */
   private Boolean _DuplicateCheck = new Boolean(false);
            
   /**
    * DailyFeeRid member variable.
    */
   private Integer _DailyFeeRid = null;
            

   /**
    * Constructs the AntiDilInqRequest object.
    * 
    */
   AntiDilInqRequest()
   {
      super ( 284 );
   }

   /**
    * Constructs the AntiDilInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AntiDilInqRequest( String hostEncoding )
   {
      super ( 284, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
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
    * Sets the Record Type field for the request.
    * 
    * @param value  Value that the Record Type will be set to.
    */
   public final void setRecordType( String value )
   {
      assertUnsent();
      _RecordType = value;
   }
	
   /**
    * Sets the Fee Code field for the request.
    * 
    * @param value  Value that the Fee Code will be set to.
    */
   public final void setFeeCode( String value )
   {
      assertUnsent();
      _FeeCode = value;
   }
	
   /**
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the Effective Date field for the request.
    * 
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the Stop Date field for the request.
    * 
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( Date value )
   {
      assertUnsent();
      _StopDate = value;
   }
	
   /**
    * Sets the Duplicate Check field for the request.
    * 
    * @param value  Value that the Duplicate Check will be set to.
    */
   public final void setDuplicateCheck( Boolean value )
   {
      assertUnsent();
      _DuplicateCheck = value;
   }
	
   /**
    * Sets the DailyFeeRid field for the request.
    * 
    * @param value  Value that the DailyFeeRid will be set to.
    */
   public final void setDailyFeeRid( Integer value )
   {
      assertUnsent();
      _DailyFeeRid = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _RecordType );
      requestBuffer.appendField( _FeeCode );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _DuplicateCheck );
      requestBuffer.appendField( _DailyFeeRid );
   }

}

