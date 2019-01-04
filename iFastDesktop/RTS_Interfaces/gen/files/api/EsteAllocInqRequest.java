// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Estate Allocations Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/EsteAllocInq.doc">EsteAllocInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class EsteAllocInqRequest extends IFastRequest implements Serializable
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
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * TransID member variable.
    */
   private String _TransID = "0";
            
   /**
    * Withdrawal amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * Amount Type member variable.
    */
   private String _AmountType = "";
            
   /**
    * Fund member variable.
    */
   private String _Fund = "";
            
   /**
    * Class member variable.
    */
   private String _Class = "";
            
   /**
    * Trade effective date member variable.
    */
   private Date _EffectiveDate = null;
            

   /**
    * Constructs the EsteAllocInqRequest object.
    * 
    */
   EsteAllocInqRequest()
   {
      super ( 441 );
   }

   /**
    * Constructs the EsteAllocInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EsteAllocInqRequest( String hostEncoding )
   {
      super ( 441, hostEncoding );
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
    * Sets the TransID field for the request.
    * 
    * @param value  Value that the TransID will be set to.
    */
   public final void setTransID( String value )
   {
      assertUnsent();
      _TransID = value;
   }
	
   /**
    * Sets the Withdrawal amount field for the request.
    * 
    * @param value  Value that the Withdrawal amount will be set to.
    */
   public final void setAmount( String value )
   {
      assertUnsent();
      _Amount = value;
   }
	
   /**
    * Sets the Amount Type field for the request.
    * 
    * @param value  Value that the Amount Type will be set to.
    */
   public final void setAmountType( String value )
   {
      assertUnsent();
      _AmountType = value;
   }
	
   /**
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFund( String value )
   {
      assertUnsent();
      _Fund = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClass( String value )
   {
      assertUnsent();
      _Class = value;
   }
	
   /**
    * Sets the Trade effective date field for the request.
    * 
    * @param value  Value that the Trade effective date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _TransID );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _Fund );
      requestBuffer.appendField( _Class );
      requestBuffer.appendField( _EffectiveDate );
   }

}

