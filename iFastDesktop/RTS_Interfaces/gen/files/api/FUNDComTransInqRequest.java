// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * FUNDCom Transaction Summary Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/FUNDComTransInq.doc">FUNDComTransInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FUNDComTransInqRequest extends IFastRequest implements Serializable
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
    * Return Next or Previous record member variable.
    */
   private Boolean _NextOrPrevious = new Boolean(false);
            
   /**
    * Sort Order member variable.
    */
   private String _SortOrder = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Starting Date member variable.
    */
   private Date _FromDate = null;
            
   /**
    * Ending Date member variable.
    */
   private Date _ToDate = null;
            
   /**
    * Search Fund Code member variable.
    */
   private String _SrchFundCode = "";
            
   /**
    * Baycom Number member variable.
    */
   private String _BaycomReq = "";
            

   /**
    * Constructs the FUNDComTransInqRequest object.
    * 
    */
   FUNDComTransInqRequest()
   {
      super ( 117 );
   }

   /**
    * Constructs the FUNDComTransInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FUNDComTransInqRequest( String hostEncoding )
   {
      super ( 117, hostEncoding );
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
    * Sets the Return Next or Previous record field for the request.
    * 
    * @param value  Value that the Return Next or Previous record will be set to.
    */
   public final void setNextOrPrevious( Boolean value )
   {
      assertUnsent();
      _NextOrPrevious = value;
   }
	
   /**
    * Sets the Sort Order field for the request.
    * 
    * @param value  Value that the Sort Order will be set to.
    */
   public final void setSortOrder( String value )
   {
      assertUnsent();
      _SortOrder = value;
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
    * Sets the Starting Date field for the request.
    * 
    * @param value  Value that the Starting Date will be set to.
    */
   public final void setFromDate( Date value )
   {
      assertUnsent();
      _FromDate = value;
   }
	
   /**
    * Sets the Ending Date field for the request.
    * 
    * @param value  Value that the Ending Date will be set to.
    */
   public final void setToDate( Date value )
   {
      assertUnsent();
      _ToDate = value;
   }
	
   /**
    * Sets the Search Fund Code field for the request.
    * 
    * @param value  Value that the Search Fund Code will be set to.
    */
   public final void setSrchFundCode( String value )
   {
      assertUnsent();
      _SrchFundCode = value;
   }
	
   /**
    * Sets the Baycom Number field for the request.
    * 
    * @param value  Value that the Baycom Number will be set to.
    */
   public final void setBaycomReq( String value )
   {
      assertUnsent();
      _BaycomReq = value;
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
      requestBuffer.appendField( _NextOrPrevious );
      requestBuffer.appendField( _SortOrder );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FromDate );
      requestBuffer.appendField( _ToDate );
      requestBuffer.appendField( _SrchFundCode );
      requestBuffer.appendField( _BaycomReq );
   }

}

