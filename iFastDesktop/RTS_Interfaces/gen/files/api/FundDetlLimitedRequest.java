// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fund Detail  with Limited Access request.
 * For additional view information see <A HREF="../../../../viewspecs/FundDetlLimited.doc">FundDetlLimited.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundDetlLimitedRequest extends IFastRequest implements Serializable
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
    * BrokerCode member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales Rep Code member variable.
    */
   private String _SalesRepCode = "";
            
   /**
    * Return only Excluded List member variable.
    */
   private Boolean _ExcludeList = new Boolean(false);
            

   /**
    * Constructs the FundDetlLimitedRequest object.
    * 
    */
   FundDetlLimitedRequest()
   {
      super ( 275 );
   }

   /**
    * Constructs the FundDetlLimitedRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FundDetlLimitedRequest( String hostEncoding )
   {
      super ( 275, hostEncoding );
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
    * Sets the BrokerCode field for the request.
    * 
    * @param value  Value that the BrokerCode will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Branch Code field for the request.
    * 
    * @param value  Value that the Branch Code will be set to.
    */
   public final void setBranchCode( String value )
   {
      assertUnsent();
      _BranchCode = value;
   }
	
   /**
    * Sets the Sales Rep Code field for the request.
    * 
    * @param value  Value that the Sales Rep Code will be set to.
    */
   public final void setSalesRepCode( String value )
   {
      assertUnsent();
      _SalesRepCode = value;
   }
	
   /**
    * Sets the Return only Excluded List field for the request.
    * 
    * @param value  Value that the Return only Excluded List will be set to.
    */
   public final void setExcludeList( Boolean value )
   {
      assertUnsent();
      _ExcludeList = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SalesRepCode );
      requestBuffer.appendField( _ExcludeList );
   }

}

