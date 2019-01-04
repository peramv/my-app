// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Branch List Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/BranchList.doc">BranchList.doc</A>.
 * 
 * @author RTS Generated
 */
public class BranchListRequest extends IFastRequest implements Serializable
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
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch Code (blank for all under Broker) member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sorting of records member variable.
    */
   private String _SortBy = "";
            
            
            
            

   /**
    * Constructs the BranchListRequest object.
    * 
    */
   BranchListRequest()
   {
      super ( 91 );
   }

   /**
    * Constructs the BranchListRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   BranchListRequest( String hostEncoding )
   {
      super ( 91, hostEncoding );
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
    * Sets the Broker Code field for the request.
    * 
    * @param value  Value that the Broker Code will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Branch Code (blank for all under Broker) field for the request.
    * 
    * @param value  Value that the Branch Code (blank for all under Broker) will be set to.
    */
   public final void setBranchCode( String value )
   {
      assertUnsent();
      _BranchCode = value;
   }
	
   /**
    * Sets the Sorting of records field for the request.
    * 
    * @param value  Value that the Sorting of records will be set to.
    */
   public final void setSortBy( String value )
   {
      assertUnsent();
      _SortBy = value;
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
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SortBy );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
   }

}

