// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Authorization Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctAuthMaint.doc">AcctAuthMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctAuthMaintRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Agency Code member array.
    */
   private String[] _AgencyCode = new String[25];
            
   /**
    * Branch Code member array.
    */
   private String[] _BranchCode = new String[25];
            
   /**
    * Agent Code member array.
    */
   private String[] _AgentCode = new String[25];
            
   /**
    * Fund Indicator member array.
    */
   private String[] _FundIndc = new String[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _Deff = new Date[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Acct-Auth Version member array.
    */
   private Integer[] _AcctAuthVer = new Integer[25];
            
   /**
    * Acct-Auth RID member array.
    */
   private Integer[] _AcctAuthRID = new Integer[25];
            

   /**
    * Constructs the AcctAuthMaintRequest object.
    * 
    */
   AcctAuthMaintRequest()
   {
      super ( 396 );
   }

   /**
    * Constructs the AcctAuthMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctAuthMaintRequest( String hostEncoding )
   {
      super ( 396, hostEncoding );
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
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Agency Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Agency Code will be set to.
    */
   public final void setAgencyCode( int index, String value )
   {
      assertUnsent();
      _AgencyCode[index] = value;
   }
	
   /**
    * Sets the Branch Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Branch Code will be set to.
    */
   public final void setBranchCode( int index, String value )
   {
      assertUnsent();
      _BranchCode[index] = value;
   }
	
   /**
    * Sets the Agent Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Agent Code will be set to.
    */
   public final void setAgentCode( int index, String value )
   {
      assertUnsent();
      _AgentCode[index] = value;
   }
	
   /**
    * Sets the Fund Indicator field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Indicator will be set to.
    */
   public final void setFundIndc( int index, String value )
   {
      assertUnsent();
      _FundIndc[index] = value;
   }
	
   /**
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setDeff( int index, Date value )
   {
      assertUnsent();
      _Deff[index] = value;
   }
	
   /**
    * Sets the Stop Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the Acct-Auth Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Acct-Auth Version will be set to.
    */
   public final void setAcctAuthVer( int index, Integer value )
   {
      assertUnsent();
      _AcctAuthVer[index] = value;
   }
	
   /**
    * Sets the Acct-Auth RID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Acct-Auth RID will be set to.
    */
   public final void setAcctAuthRID( int index, Integer value )
   {
      assertUnsent();
      _AcctAuthRID[index] = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _AgencyCode[x] );
         requestBuffer.appendField( _BranchCode[x] );
         requestBuffer.appendField( _AgentCode[x] );
         requestBuffer.appendField( _FundIndc[x] );
         requestBuffer.appendField( _Deff[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _AcctAuthVer[x] );
         requestBuffer.appendField( _AcctAuthRID[x] );
      }
   }

}

