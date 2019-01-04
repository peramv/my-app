// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Pay Entity Trade Payment Instruction Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/PETRPayINSInq.doc">PETRPayINSInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PETRPayINSInqRequest extends IFastRequest implements Serializable
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
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Broker member variable.
    */
   private String _Broker = "";
            
   /**
    * Branch member variable.
    */
   private String _Branch = "";
            
   /**
    * Sales Rep member variable.
    */
   private String _SalesRep = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _Deff = null;
            
   /**
    * Payment For member variable.
    */
   private String _PaymentFor = "";
            
   /**
    * Transaction Number member variable.
    */
   private Integer _TransNum = null;
            
            
            

   /**
    * Constructs the PETRPayINSInqRequest object.
    * 
    */
   PETRPayINSInqRequest()
   {
      super ( 374 );
   }

   /**
    * Constructs the PETRPayINSInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   PETRPayINSInqRequest( String hostEncoding )
   {
      super ( 374, hostEncoding );
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
    * Sets the Broker field for the request.
    * 
    * @param value  Value that the Broker will be set to.
    */
   public final void setBroker( String value )
   {
      assertUnsent();
      _Broker = value;
   }
	
   /**
    * Sets the Branch field for the request.
    * 
    * @param value  Value that the Branch will be set to.
    */
   public final void setBranch( String value )
   {
      assertUnsent();
      _Branch = value;
   }
	
   /**
    * Sets the Sales Rep field for the request.
    * 
    * @param value  Value that the Sales Rep will be set to.
    */
   public final void setSalesRep( String value )
   {
      assertUnsent();
      _SalesRep = value;
   }
	
   /**
    * Sets the Effective Date field for the request.
    * 
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setDeff( Date value )
   {
      assertUnsent();
      _Deff = value;
   }
	
   /**
    * Sets the Payment For field for the request.
    * 
    * @param value  Value that the Payment For will be set to.
    */
   public final void setPaymentFor( String value )
   {
      assertUnsent();
      _PaymentFor = value;
   }
	
   /**
    * Sets the Transaction Number field for the request.
    * 
    * @param value  Value that the Transaction Number will be set to.
    */
   public final void setTransNum( Integer value )
   {
      assertUnsent();
      _TransNum = value;
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
      requestBuffer.appendField( _Broker );
      requestBuffer.appendField( _Branch );
      requestBuffer.appendField( _SalesRep );
      requestBuffer.appendField( _Deff );
      requestBuffer.appendField( _PaymentFor );
      requestBuffer.appendField( _TransNum );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
   }

}

