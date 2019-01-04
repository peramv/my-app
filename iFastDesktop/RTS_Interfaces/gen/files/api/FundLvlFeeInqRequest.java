// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fund Level Fee Parms Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/FundLvlFeeInq.doc">FundLvlFeeInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundLvlFeeInqRequest extends IFastRequest implements Serializable
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
    * Fee Definition member variable.
    */
   private Integer _FeeCode = null;
            
   /**
    * Fund member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
            
            
   /**
    * Commission Group member variable.
    */
   private String _CommGroup = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Family Code member variable.
    */
   private String _FamilyCode = "";
            
   /**
    * Fund Code 2 member variable.
    */
   private String _FundCode2 = "";
            
   /**
    * Class Code 2 member variable.
    */
   private String _ClassCode2 = "";
            
   /**
    * Stop Date member variable.
    */
   private Date _rxStopDate = null;
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales Rep Code member variable.
    */
   private String _SlsRepCode = "";
            
   /**
    * Shareholder Group member variable.
    */
   private String _ShGroup = "";
            
   /**
    * Validation Type member variable.
    */
   private String _ValidationType = "";
            
   /**
    * Fee Recid ID member variable.
    */
   private Integer _FeeRecID = null;
            
   /**
    * Fee  which can't co-exist with FeeCode member variable.
    */
   private Integer _ExclFeeCode = null;
            
   /**
    * Fee Model Code member variable.
    */
   private String _FeeModelCode = "";
            
   /**
    * Distribution Channel member variable.
    */
   private String _DistribChannel = "";
            

   /**
    * Constructs the FundLvlFeeInqRequest object.
    * 
    */
   FundLvlFeeInqRequest()
   {
      super ( 197 );
   }

   /**
    * Constructs the FundLvlFeeInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FundLvlFeeInqRequest( String hostEncoding )
   {
      super ( 197, hostEncoding );
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
    * Sets the Fee Definition field for the request.
    * 
    * @param value  Value that the Fee Definition will be set to.
    */
   public final void setFeeCode( Integer value )
   {
      assertUnsent();
      _FeeCode = value;
   }
	
   /**
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
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
    * Sets the Commission Group field for the request.
    * 
    * @param value  Value that the Commission Group will be set to.
    */
   public final void setCommGroup( String value )
   {
      assertUnsent();
      _CommGroup = value;
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
    * Sets the Family Code field for the request.
    * 
    * @param value  Value that the Family Code will be set to.
    */
   public final void setFamilyCode( String value )
   {
      assertUnsent();
      _FamilyCode = value;
   }
	
   /**
    * Sets the Fund Code 2 field for the request.
    * 
    * @param value  Value that the Fund Code 2 will be set to.
    */
   public final void setFundCode2( String value )
   {
      assertUnsent();
      _FundCode2 = value;
   }
	
   /**
    * Sets the Class Code 2 field for the request.
    * 
    * @param value  Value that the Class Code 2 will be set to.
    */
   public final void setClassCode2( String value )
   {
      assertUnsent();
      _ClassCode2 = value;
   }
	
   /**
    * Sets the Stop Date field for the request.
    * 
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setrxStopDate( Date value )
   {
      assertUnsent();
      _rxStopDate = value;
   }
	
   /**
    * Sets the Broker Code field for the request.
    * 
    * @param value  Value that the Broker Code will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Branch Code field for the request.
    * 
    * @param value  Value that the Branch Code will be set to.
    */
   public final void setBranchCode( String value )
   {
      assertUnsent();
      _BranchCode = value;
   }
	
   /**
    * Sets the Sales Rep Code field for the request.
    * 
    * @param value  Value that the Sales Rep Code will be set to.
    */
   public final void setSlsRepCode( String value )
   {
      assertUnsent();
      _SlsRepCode = value;
   }
	
   /**
    * Sets the Shareholder Group field for the request.
    * 
    * @param value  Value that the Shareholder Group will be set to.
    */
   public final void setShGroup( String value )
   {
      assertUnsent();
      _ShGroup = value;
   }
	
   /**
    * Sets the Validation Type field for the request.
    * 
    * @param value  Value that the Validation Type will be set to.
    */
   public final void setValidationType( String value )
   {
      assertUnsent();
      _ValidationType = value;
   }
	
   /**
    * Sets the Fee Recid ID field for the request.
    * 
    * @param value  Value that the Fee Recid ID will be set to.
    */
   public final void setFeeRecID( Integer value )
   {
      assertUnsent();
      _FeeRecID = value;
   }
	
   /**
    * Sets the Fee  which can't co-exist with FeeCode field for the request.
    * 
    * @param value  Value that the Fee  which can't co-exist with FeeCode will be set to.
    */
   public final void setExclFeeCode( Integer value )
   {
      assertUnsent();
      _ExclFeeCode = value;
   }
	
   /**
    * Sets the Fee Model Code field for the request.
    * 
    * @param value  Value that the Fee Model Code will be set to.
    */
   public final void setFeeModelCode( String value )
   {
      assertUnsent();
      _FeeModelCode = value;
   }
	
   /**
    * Sets the Distribution Channel field for the request.
    * 
    * @param value  Value that the Distribution Channel will be set to.
    */
   public final void setDistribChannel( String value )
   {
      assertUnsent();
      _DistribChannel = value;
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
      requestBuffer.appendField( _FeeCode );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _EffectiveDate );
      encodeNextKeyField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _CommGroup );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FamilyCode );
      requestBuffer.appendField( _FundCode2 );
      requestBuffer.appendField( _ClassCode2 );
      requestBuffer.appendField( _rxStopDate );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SlsRepCode );
      requestBuffer.appendField( _ShGroup );
      requestBuffer.appendField( _ValidationType );
      requestBuffer.appendField( _FeeRecID );
      requestBuffer.appendField( _ExclFeeCode );
      requestBuffer.appendField( _FeeModelCode );
      requestBuffer.appendField( _DistribChannel );
   }

}

