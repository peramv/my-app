// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Hypothetical Foreign Content request.
 * For additional view information see <A HREF="../../../../viewspecs/HypoFxContlnq.doc">HypoFxContlnq.doc</A>.
 * 
 * @author RTS Generated
 */
public class HypoFxContlnqRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * From Fund member variable.
    */
   private String _FromFund = "";
            
   /**
    * From Class member variable.
    */
   private String _FromClass = "";
            
   /**
    * To Fund member variable.
    */
   private String _ToFund = "";
            
   /**
    * To Class member variable.
    */
   private String _ToClass = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * Amount Type member variable.
    */
   private String _AmountType = "";
            

   /**
    * Constructs the HypoFxContlnqRequest object.
    * 
    */
   HypoFxContlnqRequest()
   {
      super ( 294 );
   }

   /**
    * Constructs the HypoFxContlnqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   HypoFxContlnqRequest( String hostEncoding )
   {
      super ( 294, hostEncoding );
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
    * Sets the Transaction Type field for the request.
    * 
    * @param value  Value that the Transaction Type will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the From Fund field for the request.
    * 
    * @param value  Value that the From Fund will be set to.
    */
   public final void setFromFund( String value )
   {
      assertUnsent();
      _FromFund = value;
   }
	
   /**
    * Sets the From Class field for the request.
    * 
    * @param value  Value that the From Class will be set to.
    */
   public final void setFromClass( String value )
   {
      assertUnsent();
      _FromClass = value;
   }
	
   /**
    * Sets the To Fund field for the request.
    * 
    * @param value  Value that the To Fund will be set to.
    */
   public final void setToFund( String value )
   {
      assertUnsent();
      _ToFund = value;
   }
	
   /**
    * Sets the To Class field for the request.
    * 
    * @param value  Value that the To Class will be set to.
    */
   public final void setToClass( String value )
   {
      assertUnsent();
      _ToClass = value;
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
    * Sets the Amount field for the request.
    * 
    * @param value  Value that the Amount will be set to.
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _FromFund );
      requestBuffer.appendField( _FromClass );
      requestBuffer.appendField( _ToFund );
      requestBuffer.appendField( _ToClass );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _AmountType );
   }

}

