// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Broker Who-To-Pay Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/WhoToPayMaint.doc">WhoToPayMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class WhoToPayMaintRequest extends IFastRequest implements Serializable
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
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Broker Code member array.
    */
   private String[] _BrokerCode = new String[25];
            
   /**
    * Payment For member array.
    */
   private String[] _PaymentFor = new String[25];
            
   /**
    * Pay Entity member array.
    */
   private String[] _PayEntity = new String[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _Deff = new Date[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Pay Entity ID member array.
    */
   private String[] _PayEntityID = new String[25];
            

   /**
    * Constructs the WhoToPayMaintRequest object.
    * 
    */
   WhoToPayMaintRequest()
   {
      super ( 259 );
   }

   /**
    * Constructs the WhoToPayMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   WhoToPayMaintRequest( String hostEncoding )
   {
      super ( 259, hostEncoding );
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
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the RunMode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RunMode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Broker Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Broker Code will be set to.
    */
   public final void setBrokerCode( int index, String value )
   {
      assertUnsent();
      _BrokerCode[index] = value;
   }
	
   /**
    * Sets the Payment For field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payment For will be set to.
    */
   public final void setPaymentFor( int index, String value )
   {
      assertUnsent();
      _PaymentFor[index] = value;
   }
	
   /**
    * Sets the Pay Entity field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay Entity will be set to.
    */
   public final void setPayEntity( int index, String value )
   {
      assertUnsent();
      _PayEntity[index] = value;
   }
	
   /**
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setDeff( int index, Date value )
   {
      assertUnsent();
      _Deff[index] = value;
   }
	
   /**
    * Sets the Stop Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the Pay Entity ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay Entity ID will be set to.
    */
   public final void setPayEntityID( int index, String value )
   {
      assertUnsent();
      _PayEntityID[index] = value;
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
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _BrokerCode[x] );
         requestBuffer.appendField( _PaymentFor[x] );
         requestBuffer.appendField( _PayEntity[x] );
         requestBuffer.appendField( _Deff[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _PayEntityID[x] );
      }
   }

}

