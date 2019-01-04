// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Shr Fund Broker Default Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/ShrFundBrkMaint.doc">ShrFundBrkMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrFundBrkMaintRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
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
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[150];
            
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = new String[150];
            
   /**
    * Fund Broker Code member array.
    */
   private String[] _FundBroker = new String[150];
            
   /**
    * IsDefault member array.
    */
   private Boolean[] _IsDefault = new Boolean[150];
            
   /**
    * FundBrokerEligId member array.
    */
   private Integer[] _FundBrokerEligId = new Integer[150];
            
   /**
    * Fund Broker Elig Version member array.
    */
   private Integer[] _FundBrokerEligVer = new Integer[150];
            

   /**
    * Constructs the ShrFundBrkMaintRequest object.
    * 
    */
   ShrFundBrkMaintRequest()
   {
      super ( 328 );
   }

   /**
    * Constructs the ShrFundBrkMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShrFundBrkMaintRequest( String hostEncoding )
   {
      super ( 328, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
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
    * Sets the Shareholder Number field for the request.
    * 
    * @param value  Value that the Shareholder Number will be set to.
    */
   public final void setShrNum( String value )
   {
      assertUnsent();
      _ShrNum = value;
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
    * Sets the Fund Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setFundCode( int index, String value )
   {
      assertUnsent();
      _FundCode[index] = value;
   }
	
   /**
    * Sets the Fund Broker Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Code will be set to.
    */
   public final void setFundBroker( int index, String value )
   {
      assertUnsent();
      _FundBroker[index] = value;
   }
	
   /**
    * Sets the IsDefault field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the IsDefault will be set to.
    */
   public final void setIsDefault( int index, Boolean value )
   {
      assertUnsent();
      _IsDefault[index] = value;
   }
	
   /**
    * Sets the FundBrokerEligId field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the FundBrokerEligId will be set to.
    */
   public final void setFundBrokerEligId( int index, Integer value )
   {
      assertUnsent();
      _FundBrokerEligId[index] = value;
   }
	
   /**
    * Sets the Fund Broker Elig Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Elig Version will be set to.
    */
   public final void setFundBrokerEligVer( int index, Integer value )
   {
      assertUnsent();
      _FundBrokerEligVer[index] = value;
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
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _FundBroker[x] );
         requestBuffer.appendField( _IsDefault[x] );
         requestBuffer.appendField( _FundBrokerEligId[x] );
         requestBuffer.appendField( _FundBrokerEligVer[x] );
      }
   }

}

