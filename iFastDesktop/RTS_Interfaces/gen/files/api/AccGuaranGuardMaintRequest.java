// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Guarantee Guard Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/AccGuaranGuardMaint.doc">AccGuaranGuardMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccGuaranGuardMaintRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
   /**
    * RunMode A for Add and M for Modify member variable.
    */
   private String _RunMode = "";
            
   /**
    * iFast Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Current Guard Option member variable.
    */
   private String _GuardOptCurrent = "";
            
   /**
    * Future Guard Option member variable.
    */
   private String _GuardOptAfter = "";
            
   /**
    * Effective Until member variable.
    */
   private Date _DeffUntil = null;
            
   /**
    * SEG Guar Guard ID member variable.
    */
   private String _SegGuarGuardId = "0";
            

   /**
    * Constructs the AccGuaranGuardMaintRequest object.
    * 
    */
   AccGuaranGuardMaintRequest()
   {
      super ( 413 );
   }

   /**
    * Constructs the AccGuaranGuardMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AccGuaranGuardMaintRequest( String hostEncoding )
   {
      super ( 413, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
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
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the RunMode A for Add and M for Modify field for the request.
    * 
    * @param value  Value that the RunMode A for Add and M for Modify will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
   }
	
   /**
    * Sets the iFast Account Number field for the request.
    * 
    * @param value  Value that the iFast Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Current Guard Option field for the request.
    * 
    * @param value  Value that the Current Guard Option will be set to.
    */
   public final void setGuardOptCurrent( String value )
   {
      assertUnsent();
      _GuardOptCurrent = value;
   }
	
   /**
    * Sets the Future Guard Option field for the request.
    * 
    * @param value  Value that the Future Guard Option will be set to.
    */
   public final void setGuardOptAfter( String value )
   {
      assertUnsent();
      _GuardOptAfter = value;
   }
	
   /**
    * Sets the Effective Until field for the request.
    * 
    * @param value  Value that the Effective Until will be set to.
    */
   public final void setDeffUntil( Date value )
   {
      assertUnsent();
      _DeffUntil = value;
   }
	
   /**
    * Sets the SEG Guar Guard ID field for the request.
    * 
    * @param value  Value that the SEG Guar Guard ID will be set to.
    */
   public final void setSegGuarGuardId( String value )
   {
      assertUnsent();
      _SegGuarGuardId = value;
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
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _GuardOptCurrent );
      requestBuffer.appendField( _GuardOptAfter );
      requestBuffer.appendField( _DeffUntil );
      requestBuffer.appendField( _SegGuarGuardId );
   }

}

