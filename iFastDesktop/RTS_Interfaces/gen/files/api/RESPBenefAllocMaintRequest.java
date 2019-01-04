// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * RESP Beneficiary Allocaion Maint and Validation request.
 * For additional view information see <A HREF="../../../../viewspecs/RESPBenefAllocMaint.doc">RESPBenefAllocMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPBenefAllocMaintRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
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
    * Transaction Id member variable.
    */
   private String _TransId = "0";
            
   /**
    * Call Type validation and update member variable.
    */
   private String _CallType = "";
            
   /**
    * Trade Type member variable.
    */
   private String _TradeType = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * EntityType member array.
    */
   private String[] _EntityType = new String[25];
            
   /**
    * EntityTypeSeq member array.
    */
   private Integer[] _EntityTypeSeq = new Integer[25];
            
   /**
    * RESPBenefId member array.
    */
   private String[] _RESPBenefId = new String[25];
            
   /**
    * RESPAllocAmt member array.
    */
   private String[] _RESPAllocAmt = new String[25];
            
   /**
    * RESPAllocPrcnt member array.
    */
   private String[] _RESPAllocPrcnt = new String[25];
            
   /**
    * RESPContrDetlVer member array.
    */
   private Integer[] _RESPContrDetlVer = new Integer[25];
            
   /**
    * Flag if user has changed allocations without cancelling grant member array.
    */
   private Boolean[] _CreateEscrow = new Boolean[25];
            

   /**
    * Constructs the RESPBenefAllocMaintRequest object.
    * 
    */
   RESPBenefAllocMaintRequest()
   {
      super ( 403 );
   }

   /**
    * Constructs the RESPBenefAllocMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   RESPBenefAllocMaintRequest( String hostEncoding )
   {
      super ( 403, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
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
    * Sets the Transaction Id field for the request.
    * 
    * @param value  Value that the Transaction Id will be set to.
    */
   public final void setTransId( String value )
   {
      assertUnsent();
      _TransId = value;
   }
	
   /**
    * Sets the Call Type validation and update field for the request.
    * 
    * @param value  Value that the Call Type validation and update will be set to.
    */
   public final void setCallType( String value )
   {
      assertUnsent();
      _CallType = value;
   }
	
   /**
    * Sets the Trade Type field for the request.
    * 
    * @param value  Value that the Trade Type will be set to.
    */
   public final void setTradeType( String value )
   {
      assertUnsent();
      _TradeType = value;
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
    * Sets the Amount field for the request.
    * 
    * @param value  Value that the Amount will be set to.
    */
   public final void setAmount( String value )
   {
      assertUnsent();
      _Amount = value;
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
    * Sets the EntityType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the EntityType will be set to.
    */
   public final void setEntityType( int index, String value )
   {
      assertUnsent();
      _EntityType[index] = value;
   }
	
   /**
    * Sets the EntityTypeSeq field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the EntityTypeSeq will be set to.
    */
   public final void setEntityTypeSeq( int index, Integer value )
   {
      assertUnsent();
      _EntityTypeSeq[index] = value;
   }
	
   /**
    * Sets the RESPBenefId field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESPBenefId will be set to.
    */
   public final void setRESPBenefId( int index, String value )
   {
      assertUnsent();
      _RESPBenefId[index] = value;
   }
	
   /**
    * Sets the RESPAllocAmt field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESPAllocAmt will be set to.
    */
   public final void setRESPAllocAmt( int index, String value )
   {
      assertUnsent();
      _RESPAllocAmt[index] = value;
   }
	
   /**
    * Sets the RESPAllocPrcnt field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESPAllocPrcnt will be set to.
    */
   public final void setRESPAllocPrcnt( int index, String value )
   {
      assertUnsent();
      _RESPAllocPrcnt[index] = value;
   }
	
   /**
    * Sets the RESPContrDetlVer field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RESPContrDetlVer will be set to.
    */
   public final void setRESPContrDetlVer( int index, Integer value )
   {
      assertUnsent();
      _RESPContrDetlVer[index] = value;
   }
	
   /**
    * Sets the Flag if user has changed allocations without cancelling grant field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Flag if user has changed allocations without cancelling grant will be set to.
    */
   public final void setCreateEscrow( int index, Boolean value )
   {
      assertUnsent();
      _CreateEscrow[index] = value;
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
      requestBuffer.appendField( _TransId );
      requestBuffer.appendField( _CallType );
      requestBuffer.appendField( _TradeType );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _EntityType[x] );
         requestBuffer.appendField( _EntityTypeSeq[x] );
         requestBuffer.appendField( _RESPBenefId[x] );
         requestBuffer.appendField( _RESPAllocAmt[x] );
         requestBuffer.appendField( _RESPAllocPrcnt[x] );
         requestBuffer.appendField( _RESPContrDetlVer[x] );
         requestBuffer.appendField( _CreateEscrow[x] );
      }
   }

}

