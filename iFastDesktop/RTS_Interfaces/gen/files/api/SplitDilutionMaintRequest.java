// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Split Dilution Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/SplitDilutionMaint.doc">SplitDilutionMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class SplitDilutionMaintRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
   /**
    * Transaction ID member variable.
    */
   private String _TransID = "0";
            
   /**
    * Settle Network member variable.
    */
   private String _SettleNetwork = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Add, Modify, Delete member array.
    */
   private String[] _DilRunMode = new String[25];
            
   /**
    * Accountability for Backdated Trade member array.
    */
   private String[] _AccCode = new String[25];
            
   /**
    * Reason Code member array.
    */
   private String[] _RsnCode = new String[25];
            
   /**
    * Responsibility from date member array.
    */
   private Date[] _RespDate = new Date[25];
            
   /**
    * Percentage of responsibility member array.
    */
   private String[] _RspPrcnt = new String[25];
            
   /**
    * Version number of dilution record member array.
    */
   private Integer[] _DilVersion = new Integer[25];
            
   /**
    * Recid of dilution records member array.
    */
   private Integer[] _SplitAccCodeRID = new Integer[25];
            
   /**
    * Bill To Type (BROK,INTR,"") member array.
    */
   private String[] _BillToType = new String[25];
            
   /**
    * Bill To Entity (Broker or Intermediary cod) member array.
    */
   private String[] _BillToEntity = new String[25];
            
   /**
    * Bill To Associated Account member array.
    */
   private String[] _BillToAccount = new String[25];
            
   /**
    * Dilution Amount settle through FundServ member array.
    */
   private String[] _DilutionNSM = new String[25];
            
   /**
    * External System Dilution Payment via FundSERV member array.
    */
   private String[] _ExSysDilPymtNSM = new String[25];
            

   /**
    * Constructs the SplitDilutionMaintRequest object.
    * 
    */
   SplitDilutionMaintRequest()
   {
      super ( 357 );
   }

   /**
    * Constructs the SplitDilutionMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SplitDilutionMaintRequest( String hostEncoding )
   {
      super ( 357, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
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
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Transaction ID field for the request.
    * 
    * @param value  Value that the Transaction ID will be set to.
    */
   public final void setTransID( String value )
   {
      assertUnsent();
      _TransID = value;
   }
	
   /**
    * Sets the Settle Network field for the request.
    * 
    * @param value  Value that the Settle Network will be set to.
    */
   public final void setSettleNetwork( String value )
   {
      assertUnsent();
      _SettleNetwork = value;
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
    * Sets the Add, Modify, Delete field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Add, Modify, Delete will be set to.
    */
   public final void setDilRunMode( int index, String value )
   {
      assertUnsent();
      _DilRunMode[index] = value;
   }
	
   /**
    * Sets the Accountability for Backdated Trade field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Accountability for Backdated Trade will be set to.
    */
   public final void setAccCode( int index, String value )
   {
      assertUnsent();
      _AccCode[index] = value;
   }
	
   /**
    * Sets the Reason Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reason Code will be set to.
    */
   public final void setRsnCode( int index, String value )
   {
      assertUnsent();
      _RsnCode[index] = value;
   }
	
   /**
    * Sets the Responsibility from date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Responsibility from date will be set to.
    */
   public final void setRespDate( int index, Date value )
   {
      assertUnsent();
      _RespDate[index] = value;
   }
	
   /**
    * Sets the Percentage of responsibility field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Percentage of responsibility will be set to.
    */
   public final void setRspPrcnt( int index, String value )
   {
      assertUnsent();
      _RspPrcnt[index] = value;
   }
	
   /**
    * Sets the Version number of dilution record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Version number of dilution record will be set to.
    */
   public final void setDilVersion( int index, Integer value )
   {
      assertUnsent();
      _DilVersion[index] = value;
   }
	
   /**
    * Sets the Recid of dilution records field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Recid of dilution records will be set to.
    */
   public final void setSplitAccCodeRID( int index, Integer value )
   {
      assertUnsent();
      _SplitAccCodeRID[index] = value;
   }
	
   /**
    * Sets the Bill To Type (BROK,INTR,"") field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bill To Type (BROK,INTR,"") will be set to.
    */
   public final void setBillToType( int index, String value )
   {
      assertUnsent();
      _BillToType[index] = value;
   }
	
   /**
    * Sets the Bill To Entity (Broker or Intermediary cod) field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bill To Entity (Broker or Intermediary cod) will be set to.
    */
   public final void setBillToEntity( int index, String value )
   {
      assertUnsent();
      _BillToEntity[index] = value;
   }
	
   /**
    * Sets the Bill To Associated Account field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bill To Associated Account will be set to.
    */
   public final void setBillToAccount( int index, String value )
   {
      assertUnsent();
      _BillToAccount[index] = value;
   }
	
   /**
    * Sets the Dilution Amount settle through FundServ field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Dilution Amount settle through FundServ will be set to.
    */
   public final void setDilutionNSM( int index, String value )
   {
      assertUnsent();
      _DilutionNSM[index] = value;
   }
	
   /**
    * Sets the External System Dilution Payment via FundSERV field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the External System Dilution Payment via FundSERV will be set to.
    */
   public final void setExSysDilPymtNSM( int index, String value )
   {
      assertUnsent();
      _ExSysDilPymtNSM[index] = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _TransID );
      requestBuffer.appendField( _SettleNetwork );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _DilRunMode[x] );
         requestBuffer.appendField( _AccCode[x] );
         requestBuffer.appendField( _RsnCode[x] );
         requestBuffer.appendField( _RespDate[x] );
         requestBuffer.appendField( _RspPrcnt[x] );
         requestBuffer.appendField( _DilVersion[x] );
         requestBuffer.appendField( _SplitAccCodeRID[x] );
         requestBuffer.appendField( _BillToType[x] );
         requestBuffer.appendField( _BillToEntity[x] );
         requestBuffer.appendField( _BillToAccount[x] );
         requestBuffer.appendField( _DilutionNSM[x] );
         requestBuffer.appendField( _ExSysDilPymtNSM[x] );
      }
   }

}

