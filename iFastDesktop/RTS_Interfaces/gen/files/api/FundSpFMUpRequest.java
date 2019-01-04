// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fund Sponsor Fee Model Update request.
 * For additional view information see <A HREF="../../../../viewspecs/FundSpFMUp.doc">FundSpFMUp.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundSpFMUpRequest extends IFastRequest implements Serializable
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
   private String _CompanyID = "";
            
            
            
            
            
   /**
    * Run mode A, M, D member variable.
    */
   private String _RunMode = "";
            
   /**
    * Recid of existing record update member variable.
    */
   private Integer _FundSpFMRId = null;
            
   /**
    * Fund group member variable.
    */
   private String _FundGroup = "";
            
   /**
    * Fee model code member variable.
    */
   private String _FeeModelCode = "";
            
   /**
    * Fee model option member variable.
    */
   private String _FeeModelOption = "";
            
   /**
    * Start date of fund sponsor fee model member variable.
    */
   private Date _StartDate = null;
            
   /**
    * Stop date of fund sponsor fee model member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Version of the fund sponsor fee model record member variable.
    */
   private Integer _FundSpFmVer = null;
            

   /**
    * Constructs the FundSpFMUpRequest object.
    * 
    */
   FundSpFMUpRequest()
   {
      super ( 308 );
   }

   /**
    * Constructs the FundSpFMUpRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FundSpFMUpRequest( String hostEncoding )
   {
      super ( 308, hostEncoding );
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
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Run mode A, M, D field for the request.
    * 
    * @param value  Value that the Run mode A, M, D will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
   }
	
   /**
    * Sets the Recid of existing record update field for the request.
    * 
    * @param value  Value that the Recid of existing record update will be set to.
    */
   public final void setFundSpFMRId( Integer value )
   {
      assertUnsent();
      _FundSpFMRId = value;
   }
	
   /**
    * Sets the Fund group field for the request.
    * 
    * @param value  Value that the Fund group will be set to.
    */
   public final void setFundGroup( String value )
   {
      assertUnsent();
      _FundGroup = value;
   }
	
   /**
    * Sets the Fee model code field for the request.
    * 
    * @param value  Value that the Fee model code will be set to.
    */
   public final void setFeeModelCode( String value )
   {
      assertUnsent();
      _FeeModelCode = value;
   }
	
   /**
    * Sets the Fee model option field for the request.
    * 
    * @param value  Value that the Fee model option will be set to.
    */
   public final void setFeeModelOption( String value )
   {
      assertUnsent();
      _FeeModelOption = value;
   }
	
   /**
    * Sets the Start date of fund sponsor fee model field for the request.
    * 
    * @param value  Value that the Start date of fund sponsor fee model will be set to.
    */
   public final void setStartDate( Date value )
   {
      assertUnsent();
      _StartDate = value;
   }
	
   /**
    * Sets the Stop date of fund sponsor fee model field for the request.
    * 
    * @param value  Value that the Stop date of fund sponsor fee model will be set to.
    */
   public final void setStopDate( Date value )
   {
      assertUnsent();
      _StopDate = value;
   }
	
   /**
    * Sets the Version of the fund sponsor fee model record field for the request.
    * 
    * @param value  Value that the Version of the fund sponsor fee model record will be set to.
    */
   public final void setFundSpFmVer( Integer value )
   {
      assertUnsent();
      _FundSpFmVer = value;
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
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _FundSpFMRId );
      requestBuffer.appendField( _FundGroup );
      requestBuffer.appendField( _FeeModelCode );
      requestBuffer.appendField( _FeeModelOption );
      requestBuffer.appendField( _StartDate );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _FundSpFmVer );
   }

}

