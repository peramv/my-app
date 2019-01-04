// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * System Level Fee Parms Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/SysLvlFeePamInq.doc">SysLvlFeePamInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SysLvlFeePamInqRequest extends IFastRequest implements Serializable
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
    * Search Type member variable.
    */
   private String _SearchType = "";
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Fund member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Commission Group member variable.
    */
   private String _CommGroup = "";
            
   /**
    * Fee Code member variable.
    */
   private Integer _FeeCode = null;
            
   /**
    * Shareholder Group member variable.
    */
   private String _ShGroup = "";
            
            
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales Rep Code member variable.
    */
   private String _SlsRepCode = "";
            
   /**
    * Family Code member variable.
    */
   private String _FamilyCode = "";
            
   /**
    * Fund From member variable.
    */
   private String _rxFundFromCode = "";
            
   /**
    * Class From member variable.
    */
   private String _rxClassFromCode = "";
            
   /**
    * Default Fee Code  Y/N member variable.
    */
   private Boolean _DefaultFeeCode = new Boolean(false);
            
   /**
    * Fee Model Code member variable.
    */
   private String _FeeModelCode = "";
            
   /**
    * As of date member variable.
    */
   private Date _AsOfDate = null;
            

   /**
    * Constructs the SysLvlFeePamInqRequest object.
    * 
    */
   SysLvlFeePamInqRequest()
   {
      super ( 230 );
   }

   /**
    * Constructs the SysLvlFeePamInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SysLvlFeePamInqRequest( String hostEncoding )
   {
      super ( 230, hostEncoding );
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
    * Sets the Search Type field for the request.
    * 
    * @param value  Value that the Search Type will be set to.
    */
   public final void setSearchType( String value )
   {
      assertUnsent();
      _SearchType = value;
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
    * Sets the Fee Code field for the request.
    * 
    * @param value  Value that the Fee Code will be set to.
    */
   public final void setFeeCode( Integer value )
   {
      assertUnsent();
      _FeeCode = value;
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
    * Sets the Fund From field for the request.
    * 
    * @param value  Value that the Fund From will be set to.
    */
   public final void setrxFundFromCode( String value )
   {
      assertUnsent();
      _rxFundFromCode = value;
   }
	
   /**
    * Sets the Class From field for the request.
    * 
    * @param value  Value that the Class From will be set to.
    */
   public final void setrxClassFromCode( String value )
   {
      assertUnsent();
      _rxClassFromCode = value;
   }
	
   /**
    * Sets the Default Fee Code  Y/N field for the request.
    * 
    * @param value  Value that the Default Fee Code  Y/N will be set to.
    */
   public final void setDefaultFeeCode( Boolean value )
   {
      assertUnsent();
      _DefaultFeeCode = value;
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
    * Sets the As of date field for the request.
    * 
    * @param value  Value that the As of date will be set to.
    */
   public final void setAsOfDate( Date value )
   {
      assertUnsent();
      _AsOfDate = value;
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
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _CommGroup );
      requestBuffer.appendField( _FeeCode );
      requestBuffer.appendField( _ShGroup );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SlsRepCode );
      requestBuffer.appendField( _FamilyCode );
      requestBuffer.appendField( _rxFundFromCode );
      requestBuffer.appendField( _rxClassFromCode );
      requestBuffer.appendField( _DefaultFeeCode );
      requestBuffer.appendField( _FeeModelCode );
      requestBuffer.appendField( _AsOfDate );
   }

}

