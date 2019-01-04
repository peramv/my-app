// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Assets by Account and by Fund request.
 * For additional view information see <A HREF="../../../../viewspecs/AssetsByAcctByFnd.doc">AssetsByAcctByFnd.doc</A>.
 * 
 * @author RTS Generated
 */
public class AssetsByAcctByFndRequest extends IFastRequest implements Serializable
{

            
   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * UserId member variable.
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
    * EntityId member variable.
    */
   private String _EntityId = "0";
            
   /**
    * View by Account or by Fund ? member variable.
    */
   private Boolean _ByAccount = new Boolean(false);
            
            
   /**
    * All Accounts member variable.
    */
   private Boolean _AllAccounts = new Boolean(false);
            
   /**
    * ReportingCurrency member variable.
    */
   private String _ReportingCurrency = "";
            

   /**
    * Constructs the AssetsByAcctByFndRequest object.
    * 
    */
   AssetsByAcctByFndRequest()
   {
      super ( 192 );
   }

   /**
    * Constructs the AssetsByAcctByFndRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AssetsByAcctByFndRequest( String hostEncoding )
   {
      super ( 192, hostEncoding );
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
    * Sets the UserId field for the request.
    * 
    * @param value  Value that the UserId will be set to.
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
    * Sets the EntityId field for the request.
    * 
    * @param value  Value that the EntityId will be set to.
    */
   public final void setEntityId( String value )
   {
      assertUnsent();
      _EntityId = value;
   }
	
   /**
    * Sets the View by Account or by Fund ? field for the request.
    * 
    * @param value  Value that the View by Account or by Fund ? will be set to.
    */
   public final void setByAccount( Boolean value )
   {
      assertUnsent();
      _ByAccount = value;
   }
	
   /**
    * Sets the All Accounts field for the request.
    * 
    * @param value  Value that the All Accounts will be set to.
    */
   public final void setAllAccounts( Boolean value )
   {
      assertUnsent();
      _AllAccounts = value;
   }
	
   /**
    * Sets the ReportingCurrency field for the request.
    * 
    * @param value  Value that the ReportingCurrency will be set to.
    */
   public final void setReportingCurrency( String value )
   {
      assertUnsent();
      _ReportingCurrency = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _EntityId );
      requestBuffer.appendField( _ByAccount );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _AllAccounts );
      requestBuffer.appendField( _ReportingCurrency );
   }

}

