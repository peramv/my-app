// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * PAC/SWP NextProcDate Inq request.
 * For additional view information see <A HREF="../../../../viewspecs/RedValidInq.doc">RedValidInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RedValidInqRequest extends IFastRequest implements Serializable
{

   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * PAC/SWP Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * January member variable.
    */
   private Boolean _January = new Boolean(false);
            
   /**
    * February member variable.
    */
   private Boolean _February = new Boolean(false);
            
   /**
    * March member variable.
    */
   private Boolean _March = new Boolean(false);
            
   /**
    * April member variable.
    */
   private Boolean _April = new Boolean(false);
            
   /**
    * May member variable.
    */
   private Boolean _May = new Boolean(false);
            
   /**
    * June member variable.
    */
   private Boolean _June = new Boolean(false);
            
   /**
    * July member variable.
    */
   private Boolean _July = new Boolean(false);
            
   /**
    * August member variable.
    */
   private Boolean _August = new Boolean(false);
            
   /**
    * September member variable.
    */
   private Boolean _September = new Boolean(false);
            
   /**
    * October member variable.
    */
   private Boolean _October = new Boolean(false);
            
   /**
    * November member variable.
    */
   private Boolean _November = new Boolean(false);
            
   /**
    * December member variable.
    */
   private Boolean _December = new Boolean(false);
            
   /**
    * Weekly/Bi-Weekly member variable.
    */
   private String _Frequency = "";
            
   /**
    * Day of week member variable.
    */
   private Integer _DayOfWeek = null;
            
   /**
    * End Of Month member variable.
    */
   private Boolean _EndOfMonth = new Boolean(false);
            
   /**
    * Last Process Date member variable.
    */
   private Date _LastProcDate = null;
            

   /**
    * Constructs the RedValidInqRequest object.
    * 
    */
   RedValidInqRequest()
   {
      super ( 213 );
   }

   /**
    * Constructs the RedValidInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   RedValidInqRequest( String hostEncoding )
   {
      super ( 213, hostEncoding );
   }

   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the UserId field for the request.
    * 
    * @param value  Value that the UserId will be set to.
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
    * Sets the CompanyId field for the request.
    * 
    * @param value  Value that the CompanyId will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Fund Code field for the request.
    * 
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class Code field for the request.
    * 
    * @param value  Value that the Class Code will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the PAC/SWP Effective Date field for the request.
    * 
    * @param value  Value that the PAC/SWP Effective Date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the January field for the request.
    * 
    * @param value  Value that the January will be set to.
    */
   public final void setJanuary( Boolean value )
   {
      assertUnsent();
      _January = value;
   }
	
   /**
    * Sets the February field for the request.
    * 
    * @param value  Value that the February will be set to.
    */
   public final void setFebruary( Boolean value )
   {
      assertUnsent();
      _February = value;
   }
	
   /**
    * Sets the March field for the request.
    * 
    * @param value  Value that the March will be set to.
    */
   public final void setMarch( Boolean value )
   {
      assertUnsent();
      _March = value;
   }
	
   /**
    * Sets the April field for the request.
    * 
    * @param value  Value that the April will be set to.
    */
   public final void setApril( Boolean value )
   {
      assertUnsent();
      _April = value;
   }
	
   /**
    * Sets the May field for the request.
    * 
    * @param value  Value that the May will be set to.
    */
   public final void setMay( Boolean value )
   {
      assertUnsent();
      _May = value;
   }
	
   /**
    * Sets the June field for the request.
    * 
    * @param value  Value that the June will be set to.
    */
   public final void setJune( Boolean value )
   {
      assertUnsent();
      _June = value;
   }
	
   /**
    * Sets the July field for the request.
    * 
    * @param value  Value that the July will be set to.
    */
   public final void setJuly( Boolean value )
   {
      assertUnsent();
      _July = value;
   }
	
   /**
    * Sets the August field for the request.
    * 
    * @param value  Value that the August will be set to.
    */
   public final void setAugust( Boolean value )
   {
      assertUnsent();
      _August = value;
   }
	
   /**
    * Sets the September field for the request.
    * 
    * @param value  Value that the September will be set to.
    */
   public final void setSeptember( Boolean value )
   {
      assertUnsent();
      _September = value;
   }
	
   /**
    * Sets the October field for the request.
    * 
    * @param value  Value that the October will be set to.
    */
   public final void setOctober( Boolean value )
   {
      assertUnsent();
      _October = value;
   }
	
   /**
    * Sets the November field for the request.
    * 
    * @param value  Value that the November will be set to.
    */
   public final void setNovember( Boolean value )
   {
      assertUnsent();
      _November = value;
   }
	
   /**
    * Sets the December field for the request.
    * 
    * @param value  Value that the December will be set to.
    */
   public final void setDecember( Boolean value )
   {
      assertUnsent();
      _December = value;
   }
	
   /**
    * Sets the Weekly/Bi-Weekly field for the request.
    * 
    * @param value  Value that the Weekly/Bi-Weekly will be set to.
    */
   public final void setFrequency( String value )
   {
      assertUnsent();
      _Frequency = value;
   }
	
   /**
    * Sets the Day of week field for the request.
    * 
    * @param value  Value that the Day of week will be set to.
    */
   public final void setDayOfWeek( Integer value )
   {
      assertUnsent();
      _DayOfWeek = value;
   }
	
   /**
    * Sets the End Of Month field for the request.
    * 
    * @param value  Value that the End Of Month will be set to.
    */
   public final void setEndOfMonth( Boolean value )
   {
      assertUnsent();
      _EndOfMonth = value;
   }
	
   /**
    * Sets the Last Process Date field for the request.
    * 
    * @param value  Value that the Last Process Date will be set to.
    */
   public final void setLastProcDate( Date value )
   {
      assertUnsent();
      _LastProcDate = value;
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
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _January );
      requestBuffer.appendField( _February );
      requestBuffer.appendField( _March );
      requestBuffer.appendField( _April );
      requestBuffer.appendField( _May );
      requestBuffer.appendField( _June );
      requestBuffer.appendField( _July );
      requestBuffer.appendField( _August );
      requestBuffer.appendField( _September );
      requestBuffer.appendField( _October );
      requestBuffer.appendField( _November );
      requestBuffer.appendField( _December );
      requestBuffer.appendField( _Frequency );
      requestBuffer.appendField( _DayOfWeek );
      requestBuffer.appendField( _EndOfMonth );
      requestBuffer.appendField( _LastProcDate );
   }

}

