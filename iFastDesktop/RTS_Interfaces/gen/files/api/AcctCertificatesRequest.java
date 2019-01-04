// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account/fund certificates request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctCertificates.doc">AcctCertificates.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctCertificatesRequest extends IFastRequest implements Serializable
{

   /**
    * Account number member variable.
    */
   private String _InAcctNum = "0";
            
   /**
    * Fund code member variable.
    */
   private String _InFund = "";
            
   /**
    * Certificate Number member variable.
    */
   private String _InCertNum = "";
            
   /**
    * Cross Reference Number member variable.
    */
   private String _InXrefNum = "";
            
            
   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
            
            

   /**
    * Constructs the AcctCertificatesRequest object.
    * 
    */
   AcctCertificatesRequest()
   {
      super ( 18 );
   }

   /**
    * Constructs the AcctCertificatesRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctCertificatesRequest( String hostEncoding )
   {
      super ( 18, hostEncoding );
   }

   /**
    * Sets the Account number field for the request.
    * 
    * @param value  Value that the Account number will be set to.
    */
   public final void setInAcctNum( String value )
   {
      assertUnsent();
      _InAcctNum = value;
   }
	
   /**
    * Sets the Fund code field for the request.
    * 
    * @param value  Value that the Fund code will be set to.
    */
   public final void setInFund( String value )
   {
      assertUnsent();
      _InFund = value;
   }
	
   /**
    * Sets the Certificate Number field for the request.
    * 
    * @param value  Value that the Certificate Number will be set to.
    */
   public final void setInCertNum( String value )
   {
      assertUnsent();
      _InCertNum = value;
   }
	
   /**
    * Sets the Cross Reference Number field for the request.
    * 
    * @param value  Value that the Cross Reference Number will be set to.
    */
   public final void setInXrefNum( String value )
   {
      assertUnsent();
      _InXrefNum = value;
   }
	
   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
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
    * Sets the LanguageCode field for the request.
    * 
    * @param value  Value that the LanguageCode will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the CompanyId field for the request.
    * 
    * @param value  Value that the CompanyId will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
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
      requestBuffer.appendField( _InAcctNum );
      requestBuffer.appendField( _InFund );
      requestBuffer.appendField( _InCertNum );
      requestBuffer.appendField( _InXrefNum );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
   }

}

