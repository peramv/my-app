// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * QESI Financial and Non Financial Changes Validations request.
 * For additional view information see <A HREF="../../../../viewspecs/QESIFinanNonFinanVal.doc">QESIFinanNonFinanVal.doc</A>.
 * 
 * @author RTS Generated
 */
public class QESIFinanNonFinanValRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Transaction ID member variable.
    */
   private String _TransID = "0";
            
   /**
    * New TaxJurisdiction member variable.
    */
   private String _NewTaxJuris = "";
            
   /**
    * New Sibling member variable.
    */
   private Boolean _NewSibling = new Boolean(false);
            
   /**
    * Validation Type member variable.
    */
   private String _ValidateType = "";
            
   /**
    * Starting position for more data member variable.
    */
   private String _ReqNextKey = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RESP Beneficairy ID member array.
    */
   private String[] _RESPBenefID = new String[25];
            
   /**
    * New DOFB member array.
    */
   private Date[] _NewDOFB = new Date[25];
            

   /**
    * Constructs the QESIFinanNonFinanValRequest object.
    * 
    */
   QESIFinanNonFinanValRequest()
   {
      super ( 415 );
   }

   /**
    * Constructs the QESIFinanNonFinanValRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   QESIFinanNonFinanValRequest( String hostEncoding )
   {
      super ( 415, hostEncoding );
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
    * Sets the Transaction ID field for the request.
    * 
    * @param value  Value that the Transaction ID will be set to.
    */
   public final void setTransID( String value )
   {
      assertUnsent();
      _TransID = value;
   }
	
   /**
    * Sets the New TaxJurisdiction field for the request.
    * 
    * @param value  Value that the New TaxJurisdiction will be set to.
    */
   public final void setNewTaxJuris( String value )
   {
      assertUnsent();
      _NewTaxJuris = value;
   }
	
   /**
    * Sets the New Sibling field for the request.
    * 
    * @param value  Value that the New Sibling will be set to.
    */
   public final void setNewSibling( Boolean value )
   {
      assertUnsent();
      _NewSibling = value;
   }
	
   /**
    * Sets the Validation Type field for the request.
    * 
    * @param value  Value that the Validation Type will be set to.
    */
   public final void setValidateType( String value )
   {
      assertUnsent();
      _ValidateType = value;
   }
	
   /**
    * Sets the Starting position for more data field for the request.
    * 
    * @param value  Value that the Starting position for more data will be set to.
    */
   public final void setReqNextKey( String value )
   {
      assertUnsent();
      _ReqNextKey = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the RESP Beneficairy ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESP Beneficairy ID will be set to.
    */
   public final void setRESPBenefID( int index, String value )
   {
      assertUnsent();
      _RESPBenefID[index] = value;
   }
	
   /**
    * Sets the New DOFB field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the New DOFB will be set to.
    */
   public final void setNewDOFB( int index, Date value )
   {
      assertUnsent();
      _NewDOFB[index] = value;
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
      requestBuffer.appendField( _NewTaxJuris );
      requestBuffer.appendField( _NewSibling );
      requestBuffer.appendField( _ValidateType );
      requestBuffer.appendField( _ReqNextKey );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RESPBenefID[x] );
         requestBuffer.appendField( _NewDOFB[x] );
      }
   }

}

