// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fund prices request.
 * For additional view information see <A HREF="../../../../viewspecs/FundPrices.doc">FundPrices.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundPricesRequest extends IFastRequest implements Serializable
{

   /**
    * Fund to report on (blank for all) member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class to report on (blank for all) member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Report prices from date member variable.
    */
   private Date _FromDate = null;
            
   /**
    * Report prices to date (inclusive) member variable.
    */
   private Date _ToDate = null;
            
   /**
    * Previous Date Pressed member variable.
    */
   private Boolean _PrevDatePressed = new Boolean(false);
            
   /**
    * Next Date Pressed member variable.
    */
   private Boolean _NextDatePressed = new Boolean(false);
            
            
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
    * SearchType member variable.
    */
   private String _SearchType = "";
            
   /**
    * WKN member variable.
    */
   private String _WKN = "";
            
   /**
    * ISIN member variable.
    */
   private String _ISIN = "";
            
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * SalesRep Code member variable.
    */
   private String _SalesRepCode = "";
            
   /**
    * Ignore FundLoadGrp member variable.
    */
   private Boolean _IgnoreFundLoadGrp = new Boolean(false);
            
   /**
    * ExcludeClass member variable.
    */
   private String _ExcludeClass = "";
            
   /**
    * Flag if LastIDRate will be returned member variable.
    */
   private Boolean _GetLastIDRate = new Boolean(false);
            
   /**
    * GetTransType member variable.
    */
   private String _GetTransType = "";
            
   /**
    * GetNextAvailRate member variable.
    */
   private Boolean _GetNextAvailRate = new Boolean(false);
            

   /**
    * Constructs the FundPricesRequest object.
    * 
    */
   FundPricesRequest()
   {
      super ( 23 );
   }

   /**
    * Constructs the FundPricesRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FundPricesRequest( String hostEncoding )
   {
      super ( 23, hostEncoding );
   }

   /**
    * Sets the Fund to report on (blank for all) field for the request.
    * 
    * @param value  Value that the Fund to report on (blank for all) will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class to report on (blank for all) field for the request.
    * 
    * @param value  Value that the Class to report on (blank for all) will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the Report prices from date field for the request.
    * 
    * @param value  Value that the Report prices from date will be set to.
    */
   public final void setFromDate( Date value )
   {
      assertUnsent();
      _FromDate = value;
   }
	
   /**
    * Sets the Report prices to date (inclusive) field for the request.
    * 
    * @param value  Value that the Report prices to date (inclusive) will be set to.
    */
   public final void setToDate( Date value )
   {
      assertUnsent();
      _ToDate = value;
   }
	
   /**
    * Sets the Previous Date Pressed field for the request.
    * 
    * @param value  Value that the Previous Date Pressed will be set to.
    */
   public final void setPrevDatePressed( Boolean value )
   {
      assertUnsent();
      _PrevDatePressed = value;
   }
	
   /**
    * Sets the Next Date Pressed field for the request.
    * 
    * @param value  Value that the Next Date Pressed will be set to.
    */
   public final void setNextDatePressed( Boolean value )
   {
      assertUnsent();
      _NextDatePressed = value;
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
    * Sets the SearchType field for the request.
    * 
    * @param value  Value that the SearchType will be set to.
    */
   public final void setSearchType( String value )
   {
      assertUnsent();
      _SearchType = value;
   }
	
   /**
    * Sets the WKN field for the request.
    * 
    * @param value  Value that the WKN will be set to.
    */
   public final void setWKN( String value )
   {
      assertUnsent();
      _WKN = value;
   }
	
   /**
    * Sets the ISIN field for the request.
    * 
    * @param value  Value that the ISIN will be set to.
    */
   public final void setISIN( String value )
   {
      assertUnsent();
      _ISIN = value;
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
    * Sets the SalesRep Code field for the request.
    * 
    * @param value  Value that the SalesRep Code will be set to.
    */
   public final void setSalesRepCode( String value )
   {
      assertUnsent();
      _SalesRepCode = value;
   }
	
   /**
    * Sets the Ignore FundLoadGrp field for the request.
    * 
    * @param value  Value that the Ignore FundLoadGrp will be set to.
    */
   public final void setIgnoreFundLoadGrp( Boolean value )
   {
      assertUnsent();
      _IgnoreFundLoadGrp = value;
   }
	
   /**
    * Sets the ExcludeClass field for the request.
    * 
    * @param value  Value that the ExcludeClass will be set to.
    */
   public final void setExcludeClass( String value )
   {
      assertUnsent();
      _ExcludeClass = value;
   }
	
   /**
    * Sets the Flag if LastIDRate will be returned field for the request.
    * 
    * @param value  Value that the Flag if LastIDRate will be returned will be set to.
    */
   public final void setGetLastIDRate( Boolean value )
   {
      assertUnsent();
      _GetLastIDRate = value;
   }
	
   /**
    * Sets the GetTransType field for the request.
    * 
    * @param value  Value that the GetTransType will be set to.
    */
   public final void setGetTransType( String value )
   {
      assertUnsent();
      _GetTransType = value;
   }
	
   /**
    * Sets the GetNextAvailRate field for the request.
    * 
    * @param value  Value that the GetNextAvailRate will be set to.
    */
   public final void setGetNextAvailRate( Boolean value )
   {
      assertUnsent();
      _GetNextAvailRate = value;
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
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _FromDate );
      requestBuffer.appendField( _ToDate );
      requestBuffer.appendField( _PrevDatePressed );
      requestBuffer.appendField( _NextDatePressed );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _WKN );
      requestBuffer.appendField( _ISIN );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SalesRepCode );
      requestBuffer.appendField( _IgnoreFundLoadGrp );
      requestBuffer.appendField( _ExcludeClass );
      requestBuffer.appendField( _GetLastIDRate );
      requestBuffer.appendField( _GetTransType );
      requestBuffer.appendField( _GetNextAvailRate );
   }

}

