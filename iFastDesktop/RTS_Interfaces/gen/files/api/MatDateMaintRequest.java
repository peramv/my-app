// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * User-Defined Maturity Date Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/MatDateMaint.doc">MatDateMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class MatDateMaintRequest extends IFastRequest implements Serializable
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
   private String _CompanyID = "";
            
            
            
   /**
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * SegMatDates recid member variable.
    */
   private Integer _SegMatRid = null;
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Contract Type member variable.
    */
   private String _ContractType = "";
            
   /**
    * Contract Maturity Date member variable.
    */
   private Date _ContMaturityDate = null;
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Original Event Type member variable.
    */
   private String _OrigEventType = "";
            

   /**
    * Constructs the MatDateMaintRequest object.
    * 
    */
   MatDateMaintRequest()
   {
      super ( 341 );
   }

   /**
    * Constructs the MatDateMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   MatDateMaintRequest( String hostEncoding )
   {
      super ( 341, hostEncoding );
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
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Run Mode field for the request.
    * 
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
   }
	
   /**
    * Sets the SegMatDates recid field for the request.
    * 
    * @param value  Value that the SegMatDates recid will be set to.
    */
   public final void setSegMatRid( Integer value )
   {
      assertUnsent();
      _SegMatRid = value;
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
    * Sets the Contract Type field for the request.
    * 
    * @param value  Value that the Contract Type will be set to.
    */
   public final void setContractType( String value )
   {
      assertUnsent();
      _ContractType = value;
   }
	
   /**
    * Sets the Contract Maturity Date field for the request.
    * 
    * @param value  Value that the Contract Maturity Date will be set to.
    */
   public final void setContMaturityDate( Date value )
   {
      assertUnsent();
      _ContMaturityDate = value;
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
    * Sets the Stop Date field for the request.
    * 
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( Date value )
   {
      assertUnsent();
      _StopDate = value;
   }
	
   /**
    * Sets the Original Event Type field for the request.
    * 
    * @param value  Value that the Original Event Type will be set to.
    */
   public final void setOrigEventType( String value )
   {
      assertUnsent();
      _OrigEventType = value;
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
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _SegMatRid );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _ContractType );
      requestBuffer.appendField( _ContMaturityDate );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _OrigEventType );
   }

}

