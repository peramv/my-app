// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Shareholder Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/ShareholderMaintenance.doc">ShareholderMaintenance.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShareholderMaintenanceRequest extends IFastRequest implements Serializable
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
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Shareholder Number Manual member variable.
    */
   private Boolean _ShrNumManual = new Boolean(false);
            
   /**
    * Account Designation member variable.
    */
   private String _AcctDesignation = "";
            
   /**
    * Tax Jurisdiction Code member variable.
    */
   private String _TaxJurisCode = "";
            
   /**
    * Residence Province Code member variable.
    */
   private String _ResProvCode = "";
            
   /**
    * Shareholder Group Code member variable.
    */
   private String _GroupCode = "";
            
   /**
    * Family Code member variable.
    */
   private String _FamilyCode = "";
            
   /**
    * Fund Relation Code member variable.
    */
   private String _FundRelnCode = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Shareholder Table Version Number member variable.
    */
   private Integer _PrimMstrVer = null;
            
   /**
    * Name2 used for address member variable.
    */
   private String _Name2 = "";
            
   /**
    * Consolidated EFT member variable.
    */
   private Boolean _ConsolEFT = new Boolean(false);
            
            
            
   /**
    * Shareholder Type member variable.
    */
   private String _ShType = "";
            
   /**
    * Confidential member variable.
    */
   private Boolean _Confidential = new Boolean(false);
            
   /**
    * Channel member variable.
    */
   private String _Channel = "";
            
   /**
    * Fee Model Code member variable.
    */
   private String _FeeModelCode = "";
            
   /**
    * Update Shareholder Info of Account with same CIF member variable.
    */
   private Boolean _UpdSameCIFInfo = new Boolean(false);
            

   /**
    * Constructs the ShareholderMaintenanceRequest object.
    * 
    */
   ShareholderMaintenanceRequest()
   {
      super ( 75 );
   }

   /**
    * Constructs the ShareholderMaintenanceRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShareholderMaintenanceRequest( String hostEncoding )
   {
      super ( 75, hostEncoding );
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
    * Sets the Shareholder Number Manual field for the request.
    * 
    * @param value  Value that the Shareholder Number Manual will be set to.
    */
   public final void setShrNumManual( Boolean value )
   {
      assertUnsent();
      _ShrNumManual = value;
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
    * Sets the Tax Jurisdiction Code field for the request.
    * 
    * @param value  Value that the Tax Jurisdiction Code will be set to.
    */
   public final void setTaxJurisCode( String value )
   {
      assertUnsent();
      _TaxJurisCode = value;
   }
	
   /**
    * Sets the Residence Province Code field for the request.
    * 
    * @param value  Value that the Residence Province Code will be set to.
    */
   public final void setResProvCode( String value )
   {
      assertUnsent();
      _ResProvCode = value;
   }
	
   /**
    * Sets the Shareholder Group Code field for the request.
    * 
    * @param value  Value that the Shareholder Group Code will be set to.
    */
   public final void setGroupCode( String value )
   {
      assertUnsent();
      _GroupCode = value;
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
    * Sets the Fund Relation Code field for the request.
    * 
    * @param value  Value that the Fund Relation Code will be set to.
    */
   public final void setFundRelnCode( String value )
   {
      assertUnsent();
      _FundRelnCode = value;
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
    * Sets the Shareholder Table Version Number field for the request.
    * 
    * @param value  Value that the Shareholder Table Version Number will be set to.
    */
   public final void setPrimMstrVer( Integer value )
   {
      assertUnsent();
      _PrimMstrVer = value;
   }
	
   /**
    * Sets the Name2 used for address field for the request.
    * 
    * @param value  Value that the Name2 used for address will be set to.
    */
   public final void setName2( String value )
   {
      assertUnsent();
      _Name2 = value;
   }
	
   /**
    * Sets the Consolidated EFT field for the request.
    * 
    * @param value  Value that the Consolidated EFT will be set to.
    */
   public final void setConsolEFT( Boolean value )
   {
      assertUnsent();
      _ConsolEFT = value;
   }
	
   /**
    * Sets the Shareholder Type field for the request.
    * 
    * @param value  Value that the Shareholder Type will be set to.
    */
   public final void setShType( String value )
   {
      assertUnsent();
      _ShType = value;
   }
	
   /**
    * Sets the Confidential field for the request.
    * 
    * @param value  Value that the Confidential will be set to.
    */
   public final void setConfidential( Boolean value )
   {
      assertUnsent();
      _Confidential = value;
   }
	
   /**
    * Sets the Channel field for the request.
    * 
    * @param value  Value that the Channel will be set to.
    */
   public final void setChannel( String value )
   {
      assertUnsent();
      _Channel = value;
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
    * Sets the Update Shareholder Info of Account with same CIF field for the request.
    * 
    * @param value  Value that the Update Shareholder Info of Account with same CIF will be set to.
    */
   public final void setUpdSameCIFInfo( Boolean value )
   {
      assertUnsent();
      _UpdSameCIFInfo = value;
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
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( _ShrNumManual );
      requestBuffer.appendField( _AcctDesignation );
      requestBuffer.appendField( _TaxJurisCode );
      requestBuffer.appendField( _ResProvCode );
      requestBuffer.appendField( _GroupCode );
      requestBuffer.appendField( _FamilyCode );
      requestBuffer.appendField( _FundRelnCode );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _PrimMstrVer );
      requestBuffer.appendField( _Name2 );
      requestBuffer.appendField( _ConsolEFT );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _ShType );
      requestBuffer.appendField( _Confidential );
      requestBuffer.appendField( _Channel );
      requestBuffer.appendField( _FeeModelCode );
      requestBuffer.appendField( _UpdSameCIFInfo );
   }

}

