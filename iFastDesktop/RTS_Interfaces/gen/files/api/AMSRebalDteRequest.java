// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * AMS Rebalancing Date request.
 * For additional view information see <A HREF="../../../../viewspecs/AMSRebalDte.doc">AMSRebalDte.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSRebalDteRequest extends IFastRequest implements Serializable
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
    * AMSCode member variable.
    */
   private String _AMSCode = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Rebalance Frequency Type member variable.
    */
   private String _RebalFreqType = "";
            
   /**
    * AMS Type member variable.
    */
   private String _AMSType = "";
            
   /**
    * DayofWeek member variable.
    */
   private Integer _DayofWeek = null;
            

   /**
    * Constructs the AMSRebalDteRequest object.
    * 
    */
   AMSRebalDteRequest()
   {
      super ( 260 );
   }

   /**
    * Constructs the AMSRebalDteRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AMSRebalDteRequest( String hostEncoding )
   {
      super ( 260, hostEncoding );
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
    * Sets the AMSCode field for the request.
    * 
    * @param value  Value that the AMSCode will be set to.
    */
   public final void setAMSCode( String value )
   {
      assertUnsent();
      _AMSCode = value;
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
    * Sets the Rebalance Frequency Type field for the request.
    * 
    * @param value  Value that the Rebalance Frequency Type will be set to.
    */
   public final void setRebalFreqType( String value )
   {
      assertUnsent();
      _RebalFreqType = value;
   }
	
   /**
    * Sets the AMS Type field for the request.
    * 
    * @param value  Value that the AMS Type will be set to.
    */
   public final void setAMSType( String value )
   {
      assertUnsent();
      _AMSType = value;
   }
	
   /**
    * Sets the DayofWeek field for the request.
    * 
    * @param value  Value that the DayofWeek will be set to.
    */
   public final void setDayofWeek( Integer value )
   {
      assertUnsent();
      _DayofWeek = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _AMSCode );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _RebalFreqType );
      requestBuffer.appendField( _AMSType );
      requestBuffer.appendField( _DayofWeek );
   }

}

