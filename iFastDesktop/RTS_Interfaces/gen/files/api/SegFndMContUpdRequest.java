// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Seg Fund Multiple Contract Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/SegFndMContUpd.doc">SegFndMContUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class SegFndMContUpdRequest extends IFastRequest implements Serializable
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
    * Language member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
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
    * Recid of Cot-Acct-Contract member array.
    */
   private Integer[] _CotAcctRId = new Integer[25];
            
   /**
    * Previous Effective Date member array.
    */
   private Date[] _PrevEffectiveDate = new Date[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Contract Type member array.
    */
   private String[] _ContractType = new String[25];
            
   /**
    * Contract Type ID member array.
    */
   private Integer[] _ContractTypeId = new Integer[25];
            
   /**
    * Policy Number member array.
    */
   private String[] _PolicyNum = new String[25];
            
   /**
    * Contract Term member array.
    */
   private Integer[] _ContractTerm = new Integer[25];
            
   /**
    * Anniversary Month member array.
    */
   private Integer[] _AnnivMonth = new Integer[25];
            
   /**
    * Anniversary Day member array.
    */
   private Integer[] _AnnivDay = new Integer[25];
            
   /**
    * Province member array.
    */
   private String[] _Province = new String[25];
            
   /**
    * Age Based On member array.
    */
   private String[] _AgeBasedOn = new String[25];
            
   /**
    * Status Code member array.
    */
   private String[] _StatusCode = new String[25];
            
   /**
    * Bail Maturity Date member array.
    */
   private Date[] _BailMaturityDate = new Date[25];
            
   /**
    * Contract Maturity Date member array.
    */
   private Date[] _ContMaturityDate = new Date[25];
            
   /**
    * Legal Maturity Date member array.
    */
   private Date[] _LegalMaturityDate = new Date[25];
            
   /**
    * Closing Decade  Start Date member array.
    */
   private Date[] _CDStartDate = new Date[25];
            
   /**
    * Identifies accts what kind of problems guarantee has member array.
    */
   private String[] _SuspectGuarType = new String[25];
            
   /**
    * Contract Version of Cot Account Contract member array.
    */
   private Integer[] _ContractVer = new Integer[25];
            
   /**
    * Default Mature Date Base on of Cot Account Contract member array.
    */
   private String[] _ContractMatBasedOn = new String[25];
            

   /**
    * Constructs the SegFndMContUpdRequest object.
    * 
    */
   SegFndMContUpdRequest()
   {
      super ( 161 );
   }

   /**
    * Constructs the SegFndMContUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SegFndMContUpdRequest( String hostEncoding )
   {
      super ( 161, hostEncoding );
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
    * Sets the Language field for the request.
    * 
    * @param value  Value that the Language will be set to.
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
    * Sets the Recid of Cot-Acct-Contract field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Recid of Cot-Acct-Contract will be set to.
    */
   public final void setCotAcctRId( int index, Integer value )
   {
      assertUnsent();
      _CotAcctRId[index] = value;
   }
	
   /**
    * Sets the Previous Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Previous Effective Date will be set to.
    */
   public final void setPrevEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _PrevEffectiveDate[index] = value;
   }
	
   /**
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
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
    * Sets the Contract Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Contract Type will be set to.
    */
   public final void setContractType( int index, String value )
   {
      assertUnsent();
      _ContractType[index] = value;
   }
	
   /**
    * Sets the Contract Type ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Contract Type ID will be set to.
    */
   public final void setContractTypeId( int index, Integer value )
   {
      assertUnsent();
      _ContractTypeId[index] = value;
   }
	
   /**
    * Sets the Policy Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Policy Number will be set to.
    */
   public final void setPolicyNum( int index, String value )
   {
      assertUnsent();
      _PolicyNum[index] = value;
   }
	
   /**
    * Sets the Contract Term field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Contract Term will be set to.
    */
   public final void setContractTerm( int index, Integer value )
   {
      assertUnsent();
      _ContractTerm[index] = value;
   }
	
   /**
    * Sets the Anniversary Month field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Anniversary Month will be set to.
    */
   public final void setAnnivMonth( int index, Integer value )
   {
      assertUnsent();
      _AnnivMonth[index] = value;
   }
	
   /**
    * Sets the Anniversary Day field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Anniversary Day will be set to.
    */
   public final void setAnnivDay( int index, Integer value )
   {
      assertUnsent();
      _AnnivDay[index] = value;
   }
	
   /**
    * Sets the Province field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Province will be set to.
    */
   public final void setProvince( int index, String value )
   {
      assertUnsent();
      _Province[index] = value;
   }
	
   /**
    * Sets the Age Based On field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Age Based On will be set to.
    */
   public final void setAgeBasedOn( int index, String value )
   {
      assertUnsent();
      _AgeBasedOn[index] = value;
   }
	
   /**
    * Sets the Status Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Status Code will be set to.
    */
   public final void setStatusCode( int index, String value )
   {
      assertUnsent();
      _StatusCode[index] = value;
   }
	
   /**
    * Sets the Bail Maturity Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bail Maturity Date will be set to.
    */
   public final void setBailMaturityDate( int index, Date value )
   {
      assertUnsent();
      _BailMaturityDate[index] = value;
   }
	
   /**
    * Sets the Contract Maturity Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Contract Maturity Date will be set to.
    */
   public final void setContMaturityDate( int index, Date value )
   {
      assertUnsent();
      _ContMaturityDate[index] = value;
   }
	
   /**
    * Sets the Legal Maturity Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Legal Maturity Date will be set to.
    */
   public final void setLegalMaturityDate( int index, Date value )
   {
      assertUnsent();
      _LegalMaturityDate[index] = value;
   }
	
   /**
    * Sets the Closing Decade  Start Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Closing Decade  Start Date will be set to.
    */
   public final void setCDStartDate( int index, Date value )
   {
      assertUnsent();
      _CDStartDate[index] = value;
   }
	
   /**
    * Sets the Identifies accts what kind of problems guarantee has field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Identifies accts what kind of problems guarantee has will be set to.
    */
   public final void setSuspectGuarType( int index, String value )
   {
      assertUnsent();
      _SuspectGuarType[index] = value;
   }
	
   /**
    * Sets the Contract Version of Cot Account Contract field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Contract Version of Cot Account Contract will be set to.
    */
   public final void setContractVer( int index, Integer value )
   {
      assertUnsent();
      _ContractVer[index] = value;
   }
	
   /**
    * Sets the Default Mature Date Base on of Cot Account Contract field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Default Mature Date Base on of Cot Account Contract will be set to.
    */
   public final void setContractMatBasedOn( int index, String value )
   {
      assertUnsent();
      _ContractMatBasedOn[index] = value;
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
      requestBuffer.appendField( _AccountNum );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _CotAcctRId[x] );
         requestBuffer.appendField( _PrevEffectiveDate[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _ContractType[x] );
         requestBuffer.appendField( _ContractTypeId[x] );
         requestBuffer.appendField( _PolicyNum[x] );
         requestBuffer.appendField( _ContractTerm[x] );
         requestBuffer.appendField( _AnnivMonth[x] );
         requestBuffer.appendField( _AnnivDay[x] );
         requestBuffer.appendField( _Province[x] );
         requestBuffer.appendField( _AgeBasedOn[x] );
         requestBuffer.appendField( _StatusCode[x] );
         requestBuffer.appendField( _BailMaturityDate[x] );
         requestBuffer.appendField( _ContMaturityDate[x] );
         requestBuffer.appendField( _LegalMaturityDate[x] );
         requestBuffer.appendField( _CDStartDate[x] );
         requestBuffer.appendField( _SuspectGuarType[x] );
         requestBuffer.appendField( _ContractVer[x] );
         requestBuffer.appendField( _ContractMatBasedOn[x] );
      }
   }

}

