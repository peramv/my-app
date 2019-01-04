// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Default Split Commissions request.
 * For additional view information see <A HREF="../../../../viewspecs/DefaultSpltComm.doc">DefaultSpltComm.doc</A>.
 * 
 * @author RTS Generated
 */
public class DefaultSpltCommRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Source Account Number member variable.
    */
   private String _Account = "0";
            
   /**
    * Target Account Number member variable.
    */
   private String _AccountTo = "0";
            
   /**
    * Source Fund member variable.
    */
   private String _Fund = "";
            
   /**
    * Target Fund member variable.
    */
   private String _FundTo = "";
            
   /**
    * Source Class member variable.
    */
   private String _Class = "";
            
   /**
    * Target Class member variable.
    */
   private String _ClassTo = "";
            
   /**
    * Percent or Dollar member variable.
    */
   private String _PUD = "";
            
   /**
    * Flat or Percent member variable.
    */
   private Boolean _FlatPrcnt = new Boolean(false);
            
   /**
    * Input Pay Type member variable.
    */
   private String _InPayType = "";
            
   /**
    * Amount member variable.
    */
   private String _IAmount = "0";
            
   /**
    * Input TransType member variable.
    */
   private String _InTransType = "";
            
   /**
    * Effective Date of Trade member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Input - Gross or Net member variable.
    */
   private Boolean _InGrossNet = new Boolean(false);
            
   /**
    * Input Broker Code member variable.
    */
   private String _InBrokerCode = "";
            
   /**
    * Input Branch Code member variable.
    */
   private String _InBranchCode = "";
            
   /**
    * Input Sales Rep Code member variable.
    */
   private String _InSlsRepCode = "";
            
   /**
    * Settle Currency member variable.
    */
   private String _SettleCurr = "";
            
   /**
    * Record Type - FROM-fund or TO-fund member variable.
    */
   private String _RecordType = "";
            
   /**
    * Exchange Rate member variable.
    */
   private String _ExchRate = "0";
            
   /**
    * Investment Term member variable.
    */
   private Integer _InvestTerm = null;
            

   /**
    * Constructs the DefaultSpltCommRequest object.
    * 
    */
   DefaultSpltCommRequest()
   {
      super ( 158 );
   }

   /**
    * Constructs the DefaultSpltCommRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   DefaultSpltCommRequest( String hostEncoding )
   {
      super ( 158, hostEncoding );
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
    * Sets the Source Account Number field for the request.
    * 
    * @param value  Value that the Source Account Number will be set to.
    */
   public final void setAccount( String value )
   {
      assertUnsent();
      _Account = value;
   }
	
   /**
    * Sets the Target Account Number field for the request.
    * 
    * @param value  Value that the Target Account Number will be set to.
    */
   public final void setAccountTo( String value )
   {
      assertUnsent();
      _AccountTo = value;
   }
	
   /**
    * Sets the Source Fund field for the request.
    * 
    * @param value  Value that the Source Fund will be set to.
    */
   public final void setFund( String value )
   {
      assertUnsent();
      _Fund = value;
   }
	
   /**
    * Sets the Target Fund field for the request.
    * 
    * @param value  Value that the Target Fund will be set to.
    */
   public final void setFundTo( String value )
   {
      assertUnsent();
      _FundTo = value;
   }
	
   /**
    * Sets the Source Class field for the request.
    * 
    * @param value  Value that the Source Class will be set to.
    */
   public final void setClass( String value )
   {
      assertUnsent();
      _Class = value;
   }
	
   /**
    * Sets the Target Class field for the request.
    * 
    * @param value  Value that the Target Class will be set to.
    */
   public final void setClassTo( String value )
   {
      assertUnsent();
      _ClassTo = value;
   }
	
   /**
    * Sets the Percent or Dollar field for the request.
    * 
    * @param value  Value that the Percent or Dollar will be set to.
    */
   public final void setPUD( String value )
   {
      assertUnsent();
      _PUD = value;
   }
	
   /**
    * Sets the Flat or Percent field for the request.
    * 
    * @param value  Value that the Flat or Percent will be set to.
    */
   public final void setFlatPrcnt( Boolean value )
   {
      assertUnsent();
      _FlatPrcnt = value;
   }
	
   /**
    * Sets the Input Pay Type field for the request.
    * 
    * @param value  Value that the Input Pay Type will be set to.
    */
   public final void setInPayType( String value )
   {
      assertUnsent();
      _InPayType = value;
   }
	
   /**
    * Sets the Amount field for the request.
    * 
    * @param value  Value that the Amount will be set to.
    */
   public final void setIAmount( String value )
   {
      assertUnsent();
      _IAmount = value;
   }
	
   /**
    * Sets the Input TransType field for the request.
    * 
    * @param value  Value that the Input TransType will be set to.
    */
   public final void setInTransType( String value )
   {
      assertUnsent();
      _InTransType = value;
   }
	
   /**
    * Sets the Effective Date of Trade field for the request.
    * 
    * @param value  Value that the Effective Date of Trade will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the Input - Gross or Net field for the request.
    * 
    * @param value  Value that the Input - Gross or Net will be set to.
    */
   public final void setInGrossNet( Boolean value )
   {
      assertUnsent();
      _InGrossNet = value;
   }
	
   /**
    * Sets the Input Broker Code field for the request.
    * 
    * @param value  Value that the Input Broker Code will be set to.
    */
   public final void setInBrokerCode( String value )
   {
      assertUnsent();
      _InBrokerCode = value;
   }
	
   /**
    * Sets the Input Branch Code field for the request.
    * 
    * @param value  Value that the Input Branch Code will be set to.
    */
   public final void setInBranchCode( String value )
   {
      assertUnsent();
      _InBranchCode = value;
   }
	
   /**
    * Sets the Input Sales Rep Code field for the request.
    * 
    * @param value  Value that the Input Sales Rep Code will be set to.
    */
   public final void setInSlsRepCode( String value )
   {
      assertUnsent();
      _InSlsRepCode = value;
   }
	
   /**
    * Sets the Settle Currency field for the request.
    * 
    * @param value  Value that the Settle Currency will be set to.
    */
   public final void setSettleCurr( String value )
   {
      assertUnsent();
      _SettleCurr = value;
   }
	
   /**
    * Sets the Record Type - FROM-fund or TO-fund field for the request.
    * 
    * @param value  Value that the Record Type - FROM-fund or TO-fund will be set to.
    */
   public final void setRecordType( String value )
   {
      assertUnsent();
      _RecordType = value;
   }
	
   /**
    * Sets the Exchange Rate field for the request.
    * 
    * @param value  Value that the Exchange Rate will be set to.
    */
   public final void setExchRate( String value )
   {
      assertUnsent();
      _ExchRate = value;
   }
	
   /**
    * Sets the Investment Term field for the request.
    * 
    * @param value  Value that the Investment Term will be set to.
    */
   public final void setInvestTerm( Integer value )
   {
      assertUnsent();
      _InvestTerm = value;
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
      requestBuffer.appendField( _Account );
      requestBuffer.appendField( _AccountTo );
      requestBuffer.appendField( _Fund );
      requestBuffer.appendField( _FundTo );
      requestBuffer.appendField( _Class );
      requestBuffer.appendField( _ClassTo );
      requestBuffer.appendField( _PUD );
      requestBuffer.appendField( _FlatPrcnt );
      requestBuffer.appendField( _InPayType );
      requestBuffer.appendField( _IAmount );
      requestBuffer.appendField( _InTransType );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _InGrossNet );
      requestBuffer.appendField( _InBrokerCode );
      requestBuffer.appendField( _InBranchCode );
      requestBuffer.appendField( _InSlsRepCode );
      requestBuffer.appendField( _SettleCurr );
      requestBuffer.appendField( _RecordType );
      requestBuffer.appendField( _ExchRate );
      requestBuffer.appendField( _InvestTerm );
   }

}

