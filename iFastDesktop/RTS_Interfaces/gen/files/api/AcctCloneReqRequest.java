// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Clone Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctCloneReq.doc">AcctCloneReq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctCloneReqRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
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
   private String _SlsRep = "";
            
   /**
    * Account Designation member variable.
    */
   private String _AcctDesignation = "";
            
   /**
    * Tax Type member variable.
    */
   private String _TaxType = "";
            
   /**
    * EffectiveDate member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * CreateSlsRep member variable.
    */
   private String _CreateSlsRep = "";
            
   /**
    * Intermediary Code member variable.
    */
   private String _IntermedCode = "";
            
   /**
    * Intermediary Account Number member variable.
    */
   private String _IntermedAcctNum = "";
            
   /**
    * Nominee Account Number member variable.
    */
   private String _NomineeAcctNum = "";
            

   /**
    * Constructs the AcctCloneReqRequest object.
    * 
    */
   AcctCloneReqRequest()
   {
      super ( 377 );
   }

   /**
    * Constructs the AcctCloneReqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctCloneReqRequest( String hostEncoding )
   {
      super ( 377, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
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
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
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
   public final void setSlsRep( String value )
   {
      assertUnsent();
      _SlsRep = value;
   }
	
   /**
    * Sets the Account Designation field for the request.
    * 
    * @param value  Value that the Account Designation will be set to.
    */
   public final void setAcctDesignation( String value )
   {
      assertUnsent();
      _AcctDesignation = value;
   }
	
   /**
    * Sets the Tax Type field for the request.
    * 
    * @param value  Value that the Tax Type will be set to.
    */
   public final void setTaxType( String value )
   {
      assertUnsent();
      _TaxType = value;
   }
	
   /**
    * Sets the EffectiveDate field for the request.
    * 
    * @param value  Value that the EffectiveDate will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the CreateSlsRep field for the request.
    * 
    * @param value  Value that the CreateSlsRep will be set to.
    */
   public final void setCreateSlsRep( String value )
   {
      assertUnsent();
      _CreateSlsRep = value;
   }
	
   /**
    * Sets the Intermediary Code field for the request.
    * 
    * @param value  Value that the Intermediary Code will be set to.
    */
   public final void setIntermedCode( String value )
   {
      assertUnsent();
      _IntermedCode = value;
   }
	
   /**
    * Sets the Intermediary Account Number field for the request.
    * 
    * @param value  Value that the Intermediary Account Number will be set to.
    */
   public final void setIntermedAcctNum( String value )
   {
      assertUnsent();
      _IntermedAcctNum = value;
   }
	
   /**
    * Sets the Nominee Account Number field for the request.
    * 
    * @param value  Value that the Nominee Account Number will be set to.
    */
   public final void setNomineeAcctNum( String value )
   {
      assertUnsent();
      _NomineeAcctNum = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _Broker );
      requestBuffer.appendField( _Branch );
      requestBuffer.appendField( _SlsRep );
      requestBuffer.appendField( _AcctDesignation );
      requestBuffer.appendField( _TaxType );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _CreateSlsRep );
      requestBuffer.appendField( _IntermedCode );
      requestBuffer.appendField( _IntermedAcctNum );
      requestBuffer.appendField( _NomineeAcctNum );
   }

}

