// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * SplitComm Maint at Account Level request.
 * For additional view information see <A HREF="../../../../viewspecs/CommAcctLvlUpd.doc">CommAcctLvlUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class CommAcctLvlUpdRequest extends IFastRequest implements Serializable
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
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Comm Level member array.
    */
   private Integer[] _CommLevel = new Integer[25];
            
   /**
    * Gross or Net member array.
    */
   private Boolean[] _GrossNet = new Boolean[25];
            
   /**
    * Pay Type member array.
    */
   private String[] _PayType = new String[25];
            
   /**
    * Split Percentage member array.
    */
   private String[] _CommPercent = new String[25];
            
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
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
    * Split Comm Recid member array.
    */
   private Integer[] _SplCommRid = new Integer[25];
            
   /**
    * Active member array.
    */
   private Boolean[] _Active = new Boolean[25];
            

   /**
    * Constructs the CommAcctLvlUpdRequest object.
    * 
    */
   CommAcctLvlUpdRequest()
   {
      super ( 176 );
   }

   /**
    * Constructs the CommAcctLvlUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   CommAcctLvlUpdRequest( String hostEncoding )
   {
      super ( 176, hostEncoding );
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
    * Sets the Comm Level field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Comm Level will be set to.
    */
   public final void setCommLevel( int index, Integer value )
   {
      assertUnsent();
      _CommLevel[index] = value;
   }
	
   /**
    * Sets the Gross or Net field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Gross or Net will be set to.
    */
   public final void setGrossNet( int index, Boolean value )
   {
      assertUnsent();
      _GrossNet[index] = value;
   }
	
   /**
    * Sets the Pay Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay Type will be set to.
    */
   public final void setPayType( int index, String value )
   {
      assertUnsent();
      _PayType[index] = value;
   }
	
   /**
    * Sets the Split Percentage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Split Percentage will be set to.
    */
   public final void setCommPercent( int index, String value )
   {
      assertUnsent();
      _CommPercent[index] = value;
   }
	
   /**
    * Sets the EffectiveDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the EffectiveDate will be set to.
    */
   public final void setEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _EffectiveDate[index] = value;
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
    * Sets the Split Comm Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Split Comm Recid will be set to.
    */
   public final void setSplCommRid( int index, Integer value )
   {
      assertUnsent();
      _SplCommRid[index] = value;
   }
	
   /**
    * Sets the Active field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Active will be set to.
    */
   public final void setActive( int index, Boolean value )
   {
      assertUnsent();
      _Active[index] = value;
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
         requestBuffer.appendField( _CommLevel[x] );
         requestBuffer.appendField( _GrossNet[x] );
         requestBuffer.appendField( _PayType[x] );
         requestBuffer.appendField( _CommPercent[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _AgencyCode[x] );
         requestBuffer.appendField( _BranchCode[x] );
         requestBuffer.appendField( _AgentCode[x] );
         requestBuffer.appendField( _SplCommRid[x] );
         requestBuffer.appendField( _Active[x] );
      }
   }

}

