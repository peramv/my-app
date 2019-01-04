
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Sales representative contact details view.
 * For additional view information see <A HREF="../../../../viewspecs/SalesRepContact.doc">SalesRepContact.doc</A>.
 * 
 * @author RTS Generated
 */
public class SalesRepContactView extends IFastView implements Serializable
{

   /**
    * BrokerName member variable.
    */
   private String _BrokerName = null;
   
   /**
    * Broker Salutation member variable.
    */
   private String _BrokerSalut = null;
   
   /**
    * Rep's branch's name member variable.
    */
   private String _BranchName = null;
   
   /**
    * SalesRepName member variable.
    */
   private String _SalesRepName = null;
   
   /**
    * SalesRep Salutation member variable.
    */
   private String _SalesRepSalut = null;
   
   /**
    * PhoneNumber member variable.
    */
   private String _PhoneNumber = null;
   
   /**
    * Fax Number member variable.
    */
   private String _FaxNumber = null;
   
   /**
    * AddrLine1 member variable.
    */
   private String _AddrLine1 = null;
   
   /**
    * AddrLine2 member variable.
    */
   private String _AddrLine2 = null;
   
   /**
    * AddrLine3 member variable.
    */
   private String _AddrLine3 = null;
   
   /**
    * AddrLine4 member variable.
    */
   private String _AddrLine4 = null;
   
   /**
    * AddrLine5 member variable.
    */
   private String _AddrLine5 = null;
   
   /**
    * AddrCntryCode member variable.
    */
   private String _AddrCntryCode = null;
   
   /**
    * VersionNum member variable.
    */
   private Integer _VersionNum = null;
   

   /**
    * Constructs the SalesRepContactView object.
    * 
    */
   public SalesRepContactView()
   {
      super ( new SalesRepContactRequest() );
   }

   /**
    * Constructs the SalesRepContactView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SalesRepContactView( String hostEncoding )
   {
      super ( new SalesRepContactRequest( hostEncoding ) );
   }

   /**
    * Gets the SalesRepContactRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SalesRepContactRequest object.
    */
   public final SalesRepContactRequest getRequest()
   {
      return (SalesRepContactRequest)getIFastRequest();
   }
        
   /**
    * Gets the BrokerName field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BrokerName or null.
    */
   public final String getBrokerName()
   {
      return _BrokerName;
   }
	
   /**
    * Gets the BrokerName field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BrokerName or the specified default value.
    */
   public final String getBrokerName( String defaultValue )
   {
      return _BrokerName == null ? defaultValue : _BrokerName;
   }
                  
   /**
    * Gets the Broker Salutation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker Salutation or null.
    */
   public final String getBrokerSalut()
   {
      return _BrokerSalut;
   }
	
   /**
    * Gets the Broker Salutation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Salutation or the specified default value.
    */
   public final String getBrokerSalut( String defaultValue )
   {
      return _BrokerSalut == null ? defaultValue : _BrokerSalut;
   }
                  
   /**
    * Gets the Rep's branch's name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Rep's branch's name or null.
    */
   public final String getBranchName()
   {
      return _BranchName;
   }
	
   /**
    * Gets the Rep's branch's name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rep's branch's name or the specified default value.
    */
   public final String getBranchName( String defaultValue )
   {
      return _BranchName == null ? defaultValue : _BranchName;
   }
                  
   /**
    * Gets the SalesRepName field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SalesRepName or null.
    */
   public final String getSalesRepName()
   {
      return _SalesRepName;
   }
	
   /**
    * Gets the SalesRepName field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SalesRepName or the specified default value.
    */
   public final String getSalesRepName( String defaultValue )
   {
      return _SalesRepName == null ? defaultValue : _SalesRepName;
   }
                  
   /**
    * Gets the SalesRep Salutation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SalesRep Salutation or null.
    */
   public final String getSalesRepSalut()
   {
      return _SalesRepSalut;
   }
	
   /**
    * Gets the SalesRep Salutation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SalesRep Salutation or the specified default value.
    */
   public final String getSalesRepSalut( String defaultValue )
   {
      return _SalesRepSalut == null ? defaultValue : _SalesRepSalut;
   }
                  
   /**
    * Gets the PhoneNumber field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PhoneNumber or null.
    */
   public final String getPhoneNumber()
   {
      return _PhoneNumber;
   }
	
   /**
    * Gets the PhoneNumber field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PhoneNumber or the specified default value.
    */
   public final String getPhoneNumber( String defaultValue )
   {
      return _PhoneNumber == null ? defaultValue : _PhoneNumber;
   }
                  
   /**
    * Gets the Fax Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fax Number or null.
    */
   public final String getFaxNumber()
   {
      return _FaxNumber;
   }
	
   /**
    * Gets the Fax Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fax Number or the specified default value.
    */
   public final String getFaxNumber( String defaultValue )
   {
      return _FaxNumber == null ? defaultValue : _FaxNumber;
   }
                  
   /**
    * Gets the AddrLine1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AddrLine1 or null.
    */
   public final String getAddrLine1()
   {
      return _AddrLine1;
   }
	
   /**
    * Gets the AddrLine1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrLine1 or the specified default value.
    */
   public final String getAddrLine1( String defaultValue )
   {
      return _AddrLine1 == null ? defaultValue : _AddrLine1;
   }
                  
   /**
    * Gets the AddrLine2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AddrLine2 or null.
    */
   public final String getAddrLine2()
   {
      return _AddrLine2;
   }
	
   /**
    * Gets the AddrLine2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrLine2 or the specified default value.
    */
   public final String getAddrLine2( String defaultValue )
   {
      return _AddrLine2 == null ? defaultValue : _AddrLine2;
   }
                  
   /**
    * Gets the AddrLine3 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AddrLine3 or null.
    */
   public final String getAddrLine3()
   {
      return _AddrLine3;
   }
	
   /**
    * Gets the AddrLine3 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrLine3 or the specified default value.
    */
   public final String getAddrLine3( String defaultValue )
   {
      return _AddrLine3 == null ? defaultValue : _AddrLine3;
   }
                  
   /**
    * Gets the AddrLine4 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AddrLine4 or null.
    */
   public final String getAddrLine4()
   {
      return _AddrLine4;
   }
	
   /**
    * Gets the AddrLine4 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrLine4 or the specified default value.
    */
   public final String getAddrLine4( String defaultValue )
   {
      return _AddrLine4 == null ? defaultValue : _AddrLine4;
   }
                  
   /**
    * Gets the AddrLine5 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AddrLine5 or null.
    */
   public final String getAddrLine5()
   {
      return _AddrLine5;
   }
	
   /**
    * Gets the AddrLine5 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrLine5 or the specified default value.
    */
   public final String getAddrLine5( String defaultValue )
   {
      return _AddrLine5 == null ? defaultValue : _AddrLine5;
   }
                  
   /**
    * Gets the AddrCntryCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AddrCntryCode or null.
    */
   public final String getAddrCntryCode()
   {
      return _AddrCntryCode;
   }
	
   /**
    * Gets the AddrCntryCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrCntryCode or the specified default value.
    */
   public final String getAddrCntryCode( String defaultValue )
   {
      return _AddrCntryCode == null ? defaultValue : _AddrCntryCode;
   }
                  
   /**
    * Gets the VersionNum field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the VersionNum or null.
    */
   public final Integer getVersionNum()
   {
      return _VersionNum;
   }
	
   /**
    * Gets the VersionNum field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the VersionNum or the specified default value.
    */
   public final int getVersionNum( int defaultValue )
   {
      return _VersionNum == null ? defaultValue : _VersionNum.intValue();
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
      _BrokerName = responseBuffer.decodeString(responseBuffer.getNextField());
      _BrokerSalut = responseBuffer.decodeString(responseBuffer.getNextField());
      _BranchName = responseBuffer.decodeString(responseBuffer.getNextField());
      _SalesRepName = responseBuffer.decodeString(responseBuffer.getNextField());
      _SalesRepSalut = responseBuffer.decodeString(responseBuffer.getNextField());
      _PhoneNumber = responseBuffer.decodeString(responseBuffer.getNextField());
      _FaxNumber = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine4 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine5 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrCntryCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _VersionNum = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  

   }

}
      
