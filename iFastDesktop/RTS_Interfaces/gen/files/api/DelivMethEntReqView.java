
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Delivery Methods for Entities view.
 * For additional view information see <A HREF="../../../../viewspecs/DelivMethEntReq.doc">DelivMethEntReq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DelivMethEntReqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Document Type member array.
    */
   private String[] _DocumentType = null;
   
   /**
    * Address Code member array.
    */
   private String[] _AddrCode = null;
   
   /**
    * Suppress member array.
    */
   private Boolean[] _Suppress = null;
   
   /**
    * Delivery Option member array.
    */
   private String[] _DeliveryOption = null;
   
   /**
    * Date when record was created member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User id of the person who created record member array.
    */
   private String[] _UserName = null;
   
   /**
    * Date when record was modified member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * User who last modified record member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Del-Optn-ActEnt record id member array.
    */
   private Integer[] _DelOptnRecId = null;
   
   /**
    * Del-Optn-ActEnt version member array.
    */
   private Integer[] _DelOptnVersion = null;
   
   /**
    * Consent member array.
    */
   private Boolean[] _Consent = null;
   
   /**
    * Fund Group member array.
    */
   private String[] _FundGroup = null;
   
   /**
    * Mail member array.
    */
   private String[] _Mail = null;
   
   /**
    * Fax member array.
    */
   private String[] _Fax = null;
   
   /**
    * CD member array.
    */
   private String[] _CD = null;
   
   /**
    * E-Mail member array.
    */
   private String[] _Email = null;
   
   /**
    * E-Post member array.
    */
   private String[] _EPost = null;
   
   /**
    * Authorization member array.
    */
   private String[] _Authorize = null;
   
   /**
    * Hold member array.
    */
   private Boolean[] _Hold = null;
   

   /**
    * Constructs the DelivMethEntReqView object.
    * 
    */
   public DelivMethEntReqView()
   {
      super ( new DelivMethEntReqRequest() );
   }

   /**
    * Constructs the DelivMethEntReqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DelivMethEntReqView( String hostEncoding )
   {
      super ( new DelivMethEntReqRequest( hostEncoding ) );
   }

   /**
    * Gets the DelivMethEntReqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DelivMethEntReqRequest object.
    */
   public final DelivMethEntReqRequest getRequest()
   {
      return (DelivMethEntReqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRepeatCount()
   {
      return _RepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RepeatCount += receivedRecordCount;
   }

   /**
    * Gets the Document Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Document Type or null.
    */
   public final String getDocumentType( int index )
   {
      return _DocumentType[index];
   }
    
   /**
    * Gets the Document Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Document Type or the specified default value.
    */
   public final String getDocumentType( int index, String defaultValue )
   {
      return _DocumentType[index] == null ? defaultValue : _DocumentType[index];
   }
    
   /**
    * Gets the array of Document Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Document Type values.
    */
   public final String[] getDocumentTypeArray()
   {
      return _DocumentType;
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code or null.
    */
   public final String getAddrCode( int index )
   {
      return _AddrCode[index];
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code or the specified default value.
    */
   public final String getAddrCode( int index, String defaultValue )
   {
      return _AddrCode[index] == null ? defaultValue : _AddrCode[index];
   }
    
   /**
    * Gets the array of Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code values.
    */
   public final String[] getAddrCodeArray()
   {
      return _AddrCode;
   }
    
   /**
    * Gets the Suppress field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Suppress or null.
    */
   public final Boolean getSuppress( int index )
   {
      return _Suppress[index];
   }
    
   /**
    * Gets the Suppress field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suppress or the specified default value.
    */
   public final boolean getSuppress( int index, boolean defaultValue )
   {
      return _Suppress[index] == null ? defaultValue : _Suppress[index].booleanValue();
   }
    
   /**
    * Gets the array of Suppress fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Suppress values.
    */
   public final Boolean[] getSuppressArray()
   {
      return _Suppress;
   }
    
   /**
    * Gets the Delivery Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Delivery Option or null.
    */
   public final String getDeliveryOption( int index )
   {
      return _DeliveryOption[index];
   }
    
   /**
    * Gets the Delivery Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Delivery Option or the specified default value.
    */
   public final String getDeliveryOption( int index, String defaultValue )
   {
      return _DeliveryOption[index] == null ? defaultValue : _DeliveryOption[index];
   }
    
   /**
    * Gets the array of Delivery Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Delivery Option values.
    */
   public final String[] getDeliveryOptionArray()
   {
      return _DeliveryOption;
   }
    
   /**
    * Gets the Date when record was created field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date when record was created or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date when record was created field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date when record was created or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date when record was created fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date when record was created values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the User id of the person who created record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User id of the person who created record or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User id of the person who created record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User id of the person who created record or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User id of the person who created record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User id of the person who created record values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Date when record was modified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date when record was modified or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Date when record was modified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date when record was modified or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Date when record was modified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date when record was modified values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the User who last modified record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User who last modified record or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the User who last modified record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User who last modified record or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of User who last modified record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User who last modified record values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Del-Optn-ActEnt record id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Del-Optn-ActEnt record id or null.
    */
   public final Integer getDelOptnRecId( int index )
   {
      return _DelOptnRecId[index];
   }
    
   /**
    * Gets the Del-Optn-ActEnt record id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Del-Optn-ActEnt record id or the specified default value.
    */
   public final int getDelOptnRecId( int index, int defaultValue )
   {
      return _DelOptnRecId[index] == null ? defaultValue : _DelOptnRecId[index].intValue();
   }
    
   /**
    * Gets the array of Del-Optn-ActEnt record id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Del-Optn-ActEnt record id values.
    */
   public final Integer[] getDelOptnRecIdArray()
   {
      return _DelOptnRecId;
   }
    
   /**
    * Gets the Del-Optn-ActEnt version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Del-Optn-ActEnt version or null.
    */
   public final Integer getDelOptnVersion( int index )
   {
      return _DelOptnVersion[index];
   }
    
   /**
    * Gets the Del-Optn-ActEnt version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Del-Optn-ActEnt version or the specified default value.
    */
   public final int getDelOptnVersion( int index, int defaultValue )
   {
      return _DelOptnVersion[index] == null ? defaultValue : _DelOptnVersion[index].intValue();
   }
    
   /**
    * Gets the array of Del-Optn-ActEnt version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Del-Optn-ActEnt version values.
    */
   public final Integer[] getDelOptnVersionArray()
   {
      return _DelOptnVersion;
   }
    
   /**
    * Gets the Consent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Consent or null.
    */
   public final Boolean getConsent( int index )
   {
      return _Consent[index];
   }
    
   /**
    * Gets the Consent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Consent or the specified default value.
    */
   public final boolean getConsent( int index, boolean defaultValue )
   {
      return _Consent[index] == null ? defaultValue : _Consent[index].booleanValue();
   }
    
   /**
    * Gets the array of Consent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Consent values.
    */
   public final Boolean[] getConsentArray()
   {
      return _Consent;
   }
    
   /**
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group or null.
    */
   public final String getFundGroup( int index )
   {
      return _FundGroup[index];
   }
    
   /**
    * Gets the Fund Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group or the specified default value.
    */
   public final String getFundGroup( int index, String defaultValue )
   {
      return _FundGroup[index] == null ? defaultValue : _FundGroup[index];
   }
    
   /**
    * Gets the array of Fund Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group values.
    */
   public final String[] getFundGroupArray()
   {
      return _FundGroup;
   }
    
   /**
    * Gets the Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mail or null.
    */
   public final String getMail( int index )
   {
      return _Mail[index];
   }
    
   /**
    * Gets the Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mail or the specified default value.
    */
   public final String getMail( int index, String defaultValue )
   {
      return _Mail[index] == null ? defaultValue : _Mail[index];
   }
    
   /**
    * Gets the array of Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mail values.
    */
   public final String[] getMailArray()
   {
      return _Mail;
   }
    
   /**
    * Gets the Fax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fax or null.
    */
   public final String getFax( int index )
   {
      return _Fax[index];
   }
    
   /**
    * Gets the Fax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fax or the specified default value.
    */
   public final String getFax( int index, String defaultValue )
   {
      return _Fax[index] == null ? defaultValue : _Fax[index];
   }
    
   /**
    * Gets the array of Fax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fax values.
    */
   public final String[] getFaxArray()
   {
      return _Fax;
   }
    
   /**
    * Gets the CD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CD or null.
    */
   public final String getCD( int index )
   {
      return _CD[index];
   }
    
   /**
    * Gets the CD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CD or the specified default value.
    */
   public final String getCD( int index, String defaultValue )
   {
      return _CD[index] == null ? defaultValue : _CD[index];
   }
    
   /**
    * Gets the array of CD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CD values.
    */
   public final String[] getCDArray()
   {
      return _CD;
   }
    
   /**
    * Gets the E-Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the E-Mail or null.
    */
   public final String getEmail( int index )
   {
      return _Email[index];
   }
    
   /**
    * Gets the E-Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the E-Mail or the specified default value.
    */
   public final String getEmail( int index, String defaultValue )
   {
      return _Email[index] == null ? defaultValue : _Email[index];
   }
    
   /**
    * Gets the array of E-Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of E-Mail values.
    */
   public final String[] getEmailArray()
   {
      return _Email;
   }
    
   /**
    * Gets the E-Post field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the E-Post or null.
    */
   public final String getEPost( int index )
   {
      return _EPost[index];
   }
    
   /**
    * Gets the E-Post field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the E-Post or the specified default value.
    */
   public final String getEPost( int index, String defaultValue )
   {
      return _EPost[index] == null ? defaultValue : _EPost[index];
   }
    
   /**
    * Gets the array of E-Post fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of E-Post values.
    */
   public final String[] getEPostArray()
   {
      return _EPost;
   }
    
   /**
    * Gets the Authorization field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Authorization or null.
    */
   public final String getAuthorize( int index )
   {
      return _Authorize[index];
   }
    
   /**
    * Gets the Authorization field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Authorization or the specified default value.
    */
   public final String getAuthorize( int index, String defaultValue )
   {
      return _Authorize[index] == null ? defaultValue : _Authorize[index];
   }
    
   /**
    * Gets the array of Authorization fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Authorization values.
    */
   public final String[] getAuthorizeArray()
   {
      return _Authorize;
   }
    
   /**
    * Gets the Hold field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold or null.
    */
   public final Boolean getHold( int index )
   {
      return _Hold[index];
   }
    
   /**
    * Gets the Hold field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold or the specified default value.
    */
   public final boolean getHold( int index, boolean defaultValue )
   {
      return _Hold[index] == null ? defaultValue : _Hold[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold values.
    */
   public final Boolean[] getHoldArray()
   {
      return _Hold;
   }
    
   /**
    * Implements the abstract base method to decode
    * the host formatted response.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   protected void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      // single-record section
      decodeMoreAvailableField( responseBuffer );
      decodeNextKeyField( responseBuffer );
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _DocumentType = resizeArray( _DocumentType, _RepeatCount );
      _AddrCode = resizeArray( _AddrCode, _RepeatCount );
      _Suppress = resizeArray( _Suppress, _RepeatCount );
      _DeliveryOption = resizeArray( _DeliveryOption, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _DelOptnRecId = resizeArray( _DelOptnRecId, _RepeatCount );
      _DelOptnVersion = resizeArray( _DelOptnVersion, _RepeatCount );
      _Consent = resizeArray( _Consent, _RepeatCount );
      _FundGroup = resizeArray( _FundGroup, _RepeatCount );
      _Mail = resizeArray( _Mail, _RepeatCount );
      _Fax = resizeArray( _Fax, _RepeatCount );
      _CD = resizeArray( _CD, _RepeatCount );
      _Email = resizeArray( _Email, _RepeatCount );
      _EPost = resizeArray( _EPost, _RepeatCount );
      _Authorize = resizeArray( _Authorize, _RepeatCount );
      _Hold = resizeArray( _Hold, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _DocumentType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Suppress[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DeliveryOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DelOptnRecId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DelOptnVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Consent[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Mail[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Fax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Email[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EPost[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Authorize[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Hold[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
