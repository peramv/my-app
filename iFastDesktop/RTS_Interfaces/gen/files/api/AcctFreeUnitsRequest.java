// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account/fund free units request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctFreeUnits.doc">AcctFreeUnits.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctFreeUnitsRequest extends IFastRequest implements Serializable
{

            
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
    * Account number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * AllFunds member variable.
    */
   private Boolean _AllFunds = new Boolean(false);
            
   /**
    * Fund code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class of fund member variable.
    */
   private String _ClassCode = "";
            
            
            
            
   /**
    * Account Level DSC Fund member variable.
    */
   private Boolean _AcctLvlDSCFund = new Boolean(false);
            

   /**
    * Constructs the AcctFreeUnitsRequest object.
    * 
    */
   AcctFreeUnitsRequest()
   {
      super ( 19 );
   }

   /**
    * Constructs the AcctFreeUnitsRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctFreeUnitsRequest( String hostEncoding )
   {
      super ( 19, hostEncoding );
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
    * Sets the Account number field for the request.
    * 
    * @param value  Value that the Account number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the AllFunds field for the request.
    * 
    * @param value  Value that the AllFunds will be set to.
    */
   public final void setAllFunds( Boolean value )
   {
      assertUnsent();
      _AllFunds = value;
   }
	
   /**
    * Sets the Fund code field for the request.
    * 
    * @param value  Value that the Fund code will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class of fund field for the request.
    * 
    * @param value  Value that the Class of fund will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the Account Level DSC Fund field for the request.
    * 
    * @param value  Value that the Account Level DSC Fund will be set to.
    */
   public final void setAcctLvlDSCFund( Boolean value )
   {
      assertUnsent();
      _AcctLvlDSCFund = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _AllFunds );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _AcctLvlDSCFund );
   }

}

