// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Interest Accrual Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/IntrstAccr.doc">IntrstAccr.doc</A>.
 * 
 * @author RTS Generated
 */
public class IntrstAccrRequest extends IFastRequest implements Serializable
{

   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Starting Date member variable.
    */
   private Date _StartDate = null;
            
   /**
    * Ending Date member variable.
    */
   private Date _EndDate = null;
            
   /**
    * Include Unsettled Trade member variable.
    */
   private Boolean _InclUnsettled = new Boolean(false);
            
   /**
    * Summary Only member variable.
    */
   private Boolean _Summary = new Boolean(false);
            
            
   /**
    * SessionID member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyID member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Descending Order member variable.
    */
   private Boolean _DescendingOrder = new Boolean(false);
            
   /**
    * Calculate Market Value member variable.
    */
   private Boolean _CalculateMktValue = new Boolean(false);
            
            

   /**
    * Constructs the IntrstAccrRequest object.
    * 
    */
   IntrstAccrRequest()
   {
      super ( 62 );
   }

   /**
    * Constructs the IntrstAccrRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   IntrstAccrRequest( String hostEncoding )
   {
      super ( 62, hostEncoding );
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
    * Sets the Starting Date field for the request.
    * 
    * @param value  Value that the Starting Date will be set to.
    */
   public final void setStartDate( Date value )
   {
      assertUnsent();
      _StartDate = value;
   }
	
   /**
    * Sets the Ending Date field for the request.
    * 
    * @param value  Value that the Ending Date will be set to.
    */
   public final void setEndDate( Date value )
   {
      assertUnsent();
      _EndDate = value;
   }
	
   /**
    * Sets the Include Unsettled Trade field for the request.
    * 
    * @param value  Value that the Include Unsettled Trade will be set to.
    */
   public final void setInclUnsettled( Boolean value )
   {
      assertUnsent();
      _InclUnsettled = value;
   }
	
   /**
    * Sets the Summary Only field for the request.
    * 
    * @param value  Value that the Summary Only will be set to.
    */
   public final void setSummary( Boolean value )
   {
      assertUnsent();
      _Summary = value;
   }
	
   /**
    * Sets the SessionID field for the request.
    * 
    * @param value  Value that the SessionID will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
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
    * Sets the CompanyID field for the request.
    * 
    * @param value  Value that the CompanyID will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Descending Order field for the request.
    * 
    * @param value  Value that the Descending Order will be set to.
    */
   public final void setDescendingOrder( Boolean value )
   {
      assertUnsent();
      _DescendingOrder = value;
   }
	
   /**
    * Sets the Calculate Market Value field for the request.
    * 
    * @param value  Value that the Calculate Market Value will be set to.
    */
   public final void setCalculateMktValue( Boolean value )
   {
      assertUnsent();
      _CalculateMktValue = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _StartDate );
      requestBuffer.appendField( _EndDate );
      requestBuffer.appendField( _InclUnsettled );
      requestBuffer.appendField( _Summary );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _DescendingOrder );
      requestBuffer.appendField( _CalculateMktValue );
      encodeOverrideRepeatsField( requestBuffer );
   }

}

