// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * AMS Rules  Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/AMSRulesMaint.doc">AMSRulesMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSRulesMaintRequest extends IFastRequest implements Serializable
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
    * AMSCode member variable.
    */
   private String _AMSCode = "";
            
   /**
    * EffectiveDate member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * AMSType member variable.
    */
   private String _AMSType = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Rule Type member array.
    */
   private String[] _RuleType = new String[25];
            
   /**
    * Over Ride Decimal member array.
    */
   private String[] _OverRideDec = new String[25];
            
   /**
    * Over Ride Log member array.
    */
   private Boolean[] _OverRideLog = new Boolean[25];
            
   /**
    * Over Ride Fund member array.
    */
   private Boolean[] _OverRideFund = new Boolean[25];
            
   /**
    * Tax Juris Declaration member array.
    */
   private String[] _TaxJurisDecl = new String[25];
            
   /**
    * Prov Res Declaration member array.
    */
   private String[] _ProvResDecl = new String[25];
            
   /**
    * Tax Type Declaration member array.
    */
   private String[] _TaxTypeDecl = new String[25];
            
   /**
    * Account Type Declaration member array.
    */
   private String[] _AcctTypeDecl = new String[25];
            
   /**
    * Acct DesignationDecl member array.
    */
   private String[] _AcctDesigDecl = new String[25];
            
   /**
    * Online EWI member array.
    */
   private String[] _OnlineEWI = new String[25];
            
   /**
    * Cycle EWI member array.
    */
   private String[] _CycleEWI = new String[25];
            
   /**
    * ESG EWI member array.
    */
   private String[] _ESGEWI = new String[25];
            
   /**
    * AMSRuleID member array.
    */
   private Integer[] _AMSRuleID = new Integer[25];
            

   /**
    * Constructs the AMSRulesMaintRequest object.
    * 
    */
   AMSRulesMaintRequest()
   {
      super ( 261 );
   }

   /**
    * Constructs the AMSRulesMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AMSRulesMaintRequest( String hostEncoding )
   {
      super ( 261, hostEncoding );
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
    * Sets the AMSType field for the request.
    * 
    * @param value  Value that the AMSType will be set to.
    */
   public final void setAMSType( String value )
   {
      assertUnsent();
      _AMSType = value;
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
    * Sets the Rule Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Rule Type will be set to.
    */
   public final void setRuleType( int index, String value )
   {
      assertUnsent();
      _RuleType[index] = value;
   }
	
   /**
    * Sets the Over Ride Decimal field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Over Ride Decimal will be set to.
    */
   public final void setOverRideDec( int index, String value )
   {
      assertUnsent();
      _OverRideDec[index] = value;
   }
	
   /**
    * Sets the Over Ride Log field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Over Ride Log will be set to.
    */
   public final void setOverRideLog( int index, Boolean value )
   {
      assertUnsent();
      _OverRideLog[index] = value;
   }
	
   /**
    * Sets the Over Ride Fund field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Over Ride Fund will be set to.
    */
   public final void setOverRideFund( int index, Boolean value )
   {
      assertUnsent();
      _OverRideFund[index] = value;
   }
	
   /**
    * Sets the Tax Juris Declaration field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Tax Juris Declaration will be set to.
    */
   public final void setTaxJurisDecl( int index, String value )
   {
      assertUnsent();
      _TaxJurisDecl[index] = value;
   }
	
   /**
    * Sets the Prov Res Declaration field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Prov Res Declaration will be set to.
    */
   public final void setProvResDecl( int index, String value )
   {
      assertUnsent();
      _ProvResDecl[index] = value;
   }
	
   /**
    * Sets the Tax Type Declaration field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Tax Type Declaration will be set to.
    */
   public final void setTaxTypeDecl( int index, String value )
   {
      assertUnsent();
      _TaxTypeDecl[index] = value;
   }
	
   /**
    * Sets the Account Type Declaration field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Account Type Declaration will be set to.
    */
   public final void setAcctTypeDecl( int index, String value )
   {
      assertUnsent();
      _AcctTypeDecl[index] = value;
   }
	
   /**
    * Sets the Acct DesignationDecl field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Acct DesignationDecl will be set to.
    */
   public final void setAcctDesigDecl( int index, String value )
   {
      assertUnsent();
      _AcctDesigDecl[index] = value;
   }
	
   /**
    * Sets the Online EWI field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Online EWI will be set to.
    */
   public final void setOnlineEWI( int index, String value )
   {
      assertUnsent();
      _OnlineEWI[index] = value;
   }
	
   /**
    * Sets the Cycle EWI field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Cycle EWI will be set to.
    */
   public final void setCycleEWI( int index, String value )
   {
      assertUnsent();
      _CycleEWI[index] = value;
   }
	
   /**
    * Sets the ESG EWI field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ESG EWI will be set to.
    */
   public final void setESGEWI( int index, String value )
   {
      assertUnsent();
      _ESGEWI[index] = value;
   }
	
   /**
    * Sets the AMSRuleID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AMSRuleID will be set to.
    */
   public final void setAMSRuleID( int index, Integer value )
   {
      assertUnsent();
      _AMSRuleID[index] = value;
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
      requestBuffer.appendField( _AMSCode );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _AMSType );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _RuleType[x] );
         requestBuffer.appendField( _OverRideDec[x] );
         requestBuffer.appendField( _OverRideLog[x] );
         requestBuffer.appendField( _OverRideFund[x] );
         requestBuffer.appendField( _TaxJurisDecl[x] );
         requestBuffer.appendField( _ProvResDecl[x] );
         requestBuffer.appendField( _TaxTypeDecl[x] );
         requestBuffer.appendField( _AcctTypeDecl[x] );
         requestBuffer.appendField( _AcctDesigDecl[x] );
         requestBuffer.appendField( _OnlineEWI[x] );
         requestBuffer.appendField( _CycleEWI[x] );
         requestBuffer.appendField( _ESGEWI[x] );
         requestBuffer.appendField( _AMSRuleID[x] );
      }
   }

}

