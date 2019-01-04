// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Security Recon - System Level Update request.
 * For additional view information see <A HREF="../../../../viewspecs/SecReconUpd.doc">SecReconUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class SecReconUpdRequest extends IFastRequest implements Serializable
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
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * SettlLoc Version member array.
    */
   private Integer[] _SettlLocVersion = new Integer[25];
            
   /**
    * SetllLoc Code member array.
    */
   private String[] _SettlLocCode = new String[25];
            
   /**
    * SettlLoc Description member array.
    */
   private String[] _SettlLocDesc = new String[25];
            
   /**
    * Mgmt SettleAcct Number member array.
    */
   private String[] _MgmtSettlAcctNum = new String[25];
            
   /**
    * Status Type member array.
    */
   private Boolean[] _StatusType = new Boolean[25];
            
   /**
    * SettleLoc Recid member array.
    */
   private Integer[] _SettlLocRid = new Integer[25];
            
   /**
    * InternalSettlementAccount member array.
    */
   private String[] _InternalSettlementAccount = new String[25];
            

   /**
    * Constructs the SecReconUpdRequest object.
    * 
    */
   SecReconUpdRequest()
   {
      super ( 268 );
   }

   /**
    * Constructs the SecReconUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SecReconUpdRequest( String hostEncoding )
   {
      super ( 268, hostEncoding );
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
    * Sets the SettlLoc Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the SettlLoc Version will be set to.
    */
   public final void setSettlLocVersion( int index, Integer value )
   {
      assertUnsent();
      _SettlLocVersion[index] = value;
   }
	
   /**
    * Sets the SetllLoc Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the SetllLoc Code will be set to.
    */
   public final void setSettlLocCode( int index, String value )
   {
      assertUnsent();
      _SettlLocCode[index] = value;
   }
	
   /**
    * Sets the SettlLoc Description field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the SettlLoc Description will be set to.
    */
   public final void setSettlLocDesc( int index, String value )
   {
      assertUnsent();
      _SettlLocDesc[index] = value;
   }
	
   /**
    * Sets the Mgmt SettleAcct Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Mgmt SettleAcct Number will be set to.
    */
   public final void setMgmtSettlAcctNum( int index, String value )
   {
      assertUnsent();
      _MgmtSettlAcctNum[index] = value;
   }
	
   /**
    * Sets the Status Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Status Type will be set to.
    */
   public final void setStatusType( int index, Boolean value )
   {
      assertUnsent();
      _StatusType[index] = value;
   }
	
   /**
    * Sets the SettleLoc Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the SettleLoc Recid will be set to.
    */
   public final void setSettlLocRid( int index, Integer value )
   {
      assertUnsent();
      _SettlLocRid[index] = value;
   }
	
   /**
    * Sets the InternalSettlementAccount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the InternalSettlementAccount will be set to.
    */
   public final void setInternalSettlementAccount( int index, String value )
   {
      assertUnsent();
      _InternalSettlementAccount[index] = value;
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
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _SettlLocVersion[x] );
         requestBuffer.appendField( _SettlLocCode[x] );
         requestBuffer.appendField( _SettlLocDesc[x] );
         requestBuffer.appendField( _MgmtSettlAcctNum[x] );
         requestBuffer.appendField( _StatusType[x] );
         requestBuffer.appendField( _SettlLocRid[x] );
         requestBuffer.appendField( _InternalSettlementAccount[x] );
      }
   }

}

