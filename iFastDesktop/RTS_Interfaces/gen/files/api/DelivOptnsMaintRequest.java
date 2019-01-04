// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Delivery Options for Entity Screen - Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/DelivOptnsMaint.doc">DelivOptnsMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class DelivOptnsMaintRequest extends IFastRequest implements Serializable
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
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Entity Type member array.
    */
   private String[] _EntityType = new String[25];
            
   /**
    * Sequence Number member array.
    */
   private Integer[] _EntityTypeSeq = new Integer[25];
            
   /**
    * Document Type member array.
    */
   private String[] _DocumentType = new String[25];
            
   /**
    * Address Code member array.
    */
   private String[] _AddrCode = new String[25];
            
   /**
    * Suppress Flag member array.
    */
   private Boolean[] _Suppress = new Boolean[25];
            
   /**
    * Delivery Optioin member array.
    */
   private String[] _DeliveryOption = new String[25];
            
   /**
    * Del-Optn-ActEnt record id member array.
    */
   private Integer[] _DelOptnRId = new Integer[25];
            
   /**
    * Del-Optn-ActEnt Version member array.
    */
   private Integer[] _DelOptnVersion = new Integer[25];
            
   /**
    * Consent member array.
    */
   private Boolean[] _Consent = new Boolean[25];
            
   /**
    * Fund Group member array.
    */
   private String[] _FundGroup = new String[25];
            
   /**
    * Mail member array.
    */
   private String[] _Mail = new String[25];
            
   /**
    * Fax member array.
    */
   private String[] _Fax = new String[25];
            
   /**
    * CD member array.
    */
   private String[] _CD = new String[25];
            
   /**
    * E-Mail member array.
    */
   private String[] _Email = new String[25];
            
   /**
    * E-Post member array.
    */
   private String[] _EPost = new String[25];
            
   /**
    * Authorization member array.
    */
   private String[] _Authorize = new String[25];
            
   /**
    * Hold member array.
    */
   private Boolean[] _Hold = new Boolean[25];
            

   /**
    * Constructs the DelivOptnsMaintRequest object.
    * 
    */
   DelivOptnsMaintRequest()
   {
      super ( 216 );
   }

   /**
    * Constructs the DelivOptnsMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   DelivOptnsMaintRequest( String hostEncoding )
   {
      super ( 216, hostEncoding );
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
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Entity Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity Type will be set to.
    */
   public final void setEntityType( int index, String value )
   {
      assertUnsent();
      _EntityType[index] = value;
   }
	
   /**
    * Sets the Sequence Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Sequence Number will be set to.
    */
   public final void setEntityTypeSeq( int index, Integer value )
   {
      assertUnsent();
      _EntityTypeSeq[index] = value;
   }
	
   /**
    * Sets the Document Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Document Type will be set to.
    */
   public final void setDocumentType( int index, String value )
   {
      assertUnsent();
      _DocumentType[index] = value;
   }
	
   /**
    * Sets the Address Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Code will be set to.
    */
   public final void setAddrCode( int index, String value )
   {
      assertUnsent();
      _AddrCode[index] = value;
   }
	
   /**
    * Sets the Suppress Flag field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Suppress Flag will be set to.
    */
   public final void setSuppress( int index, Boolean value )
   {
      assertUnsent();
      _Suppress[index] = value;
   }
	
   /**
    * Sets the Delivery Optioin field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Delivery Optioin will be set to.
    */
   public final void setDeliveryOption( int index, String value )
   {
      assertUnsent();
      _DeliveryOption[index] = value;
   }
	
   /**
    * Sets the Del-Optn-ActEnt record id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Del-Optn-ActEnt record id will be set to.
    */
   public final void setDelOptnRId( int index, Integer value )
   {
      assertUnsent();
      _DelOptnRId[index] = value;
   }
	
   /**
    * Sets the Del-Optn-ActEnt Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Del-Optn-ActEnt Version will be set to.
    */
   public final void setDelOptnVersion( int index, Integer value )
   {
      assertUnsent();
      _DelOptnVersion[index] = value;
   }
	
   /**
    * Sets the Consent field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Consent will be set to.
    */
   public final void setConsent( int index, Boolean value )
   {
      assertUnsent();
      _Consent[index] = value;
   }
	
   /**
    * Sets the Fund Group field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Group will be set to.
    */
   public final void setFundGroup( int index, String value )
   {
      assertUnsent();
      _FundGroup[index] = value;
   }
	
   /**
    * Sets the Mail field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Mail will be set to.
    */
   public final void setMail( int index, String value )
   {
      assertUnsent();
      _Mail[index] = value;
   }
	
   /**
    * Sets the Fax field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fax will be set to.
    */
   public final void setFax( int index, String value )
   {
      assertUnsent();
      _Fax[index] = value;
   }
	
   /**
    * Sets the CD field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the CD will be set to.
    */
   public final void setCD( int index, String value )
   {
      assertUnsent();
      _CD[index] = value;
   }
	
   /**
    * Sets the E-Mail field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the E-Mail will be set to.
    */
   public final void setEmail( int index, String value )
   {
      assertUnsent();
      _Email[index] = value;
   }
	
   /**
    * Sets the E-Post field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the E-Post will be set to.
    */
   public final void setEPost( int index, String value )
   {
      assertUnsent();
      _EPost[index] = value;
   }
	
   /**
    * Sets the Authorization field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Authorization will be set to.
    */
   public final void setAuthorize( int index, String value )
   {
      assertUnsent();
      _Authorize[index] = value;
   }
	
   /**
    * Sets the Hold field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Hold will be set to.
    */
   public final void setHold( int index, Boolean value )
   {
      assertUnsent();
      _Hold[index] = value;
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
      requestBuffer.appendField( _AccountNum );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _EntityType[x] );
         requestBuffer.appendField( _EntityTypeSeq[x] );
         requestBuffer.appendField( _DocumentType[x] );
         requestBuffer.appendField( _AddrCode[x] );
         requestBuffer.appendField( _Suppress[x] );
         requestBuffer.appendField( _DeliveryOption[x] );
         requestBuffer.appendField( _DelOptnRId[x] );
         requestBuffer.appendField( _DelOptnVersion[x] );
         requestBuffer.appendField( _Consent[x] );
         requestBuffer.appendField( _FundGroup[x] );
         requestBuffer.appendField( _Mail[x] );
         requestBuffer.appendField( _Fax[x] );
         requestBuffer.appendField( _CD[x] );
         requestBuffer.appendField( _Email[x] );
         requestBuffer.appendField( _EPost[x] );
         requestBuffer.appendField( _Authorize[x] );
         requestBuffer.appendField( _Hold[x] );
      }
   }

}

