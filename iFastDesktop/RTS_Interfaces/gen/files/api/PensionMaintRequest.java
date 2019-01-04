// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Pension Information Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/PensionMaint.doc">PensionMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class PensionMaintRequest extends IFastRequest implements Serializable
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
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Minimum withdrawal age member variable.
    */
   private Integer _MinWithAge = null;
            
   /**
    * Pension Source Line 1 member variable.
    */
   private String _PenSourceLine1 = "";
            
   /**
    * Pension Source Line 2 member variable.
    */
   private String _PenSourceLine2 = "";
            
   /**
    * Pension Source Line 3 member variable.
    */
   private String _PenSourceLine3 = "";
            
   /**
    * Unisex Amount member variable.
    */
   private String _UniSexPer = "0";
            
   /**
    * Sex distinction Amount member variable.
    */
   private String _SexDistinctPer = "0";
            
   /**
    * Version of the LIPPenInfo record member variable.
    */
   private Integer _LIPPenInfoVer = null;
            
   /**
    * LIPPenInfo recid member variable.
    */
   private Integer _LIPPenInfoRid = null;
            
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
            
            

   /**
    * Constructs the PensionMaintRequest object.
    * 
    */
   PensionMaintRequest()
   {
      super ( 203 );
   }

   /**
    * Constructs the PensionMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   PensionMaintRequest( String hostEncoding )
   {
      super ( 203, hostEncoding );
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
    * Sets the Minimum withdrawal age field for the request.
    * 
    * @param value  Value that the Minimum withdrawal age will be set to.
    */
   public final void setMinWithAge( Integer value )
   {
      assertUnsent();
      _MinWithAge = value;
   }
	
   /**
    * Sets the Pension Source Line 1 field for the request.
    * 
    * @param value  Value that the Pension Source Line 1 will be set to.
    */
   public final void setPenSourceLine1( String value )
   {
      assertUnsent();
      _PenSourceLine1 = value;
   }
	
   /**
    * Sets the Pension Source Line 2 field for the request.
    * 
    * @param value  Value that the Pension Source Line 2 will be set to.
    */
   public final void setPenSourceLine2( String value )
   {
      assertUnsent();
      _PenSourceLine2 = value;
   }
	
   /**
    * Sets the Pension Source Line 3 field for the request.
    * 
    * @param value  Value that the Pension Source Line 3 will be set to.
    */
   public final void setPenSourceLine3( String value )
   {
      assertUnsent();
      _PenSourceLine3 = value;
   }
	
   /**
    * Sets the Unisex Amount field for the request.
    * 
    * @param value  Value that the Unisex Amount will be set to.
    */
   public final void setUniSexPer( String value )
   {
      assertUnsent();
      _UniSexPer = value;
   }
	
   /**
    * Sets the Sex distinction Amount field for the request.
    * 
    * @param value  Value that the Sex distinction Amount will be set to.
    */
   public final void setSexDistinctPer( String value )
   {
      assertUnsent();
      _SexDistinctPer = value;
   }
	
   /**
    * Sets the Version of the LIPPenInfo record field for the request.
    * 
    * @param value  Value that the Version of the LIPPenInfo record will be set to.
    */
   public final void setLIPPenInfoVer( Integer value )
   {
      assertUnsent();
      _LIPPenInfoVer = value;
   }
	
   /**
    * Sets the LIPPenInfo recid field for the request.
    * 
    * @param value  Value that the LIPPenInfo recid will be set to.
    */
   public final void setLIPPenInfoRid( Integer value )
   {
      assertUnsent();
      _LIPPenInfoRid = value;
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
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _MinWithAge );
      requestBuffer.appendField( _PenSourceLine1 );
      requestBuffer.appendField( _PenSourceLine2 );
      requestBuffer.appendField( _PenSourceLine3 );
      requestBuffer.appendField( _UniSexPer );
      requestBuffer.appendField( _SexDistinctPer );
      requestBuffer.appendField( _LIPPenInfoVer );
      requestBuffer.appendField( _LIPPenInfoRid );
      requestBuffer.appendField( _ShrNum );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
   }

}

