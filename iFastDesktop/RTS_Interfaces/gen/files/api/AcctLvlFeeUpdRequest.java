// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Level Fee Parms/Scale Update request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctLvlFeeUpd.doc">AcctLvlFeeUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctLvlFeeUpdRequest extends IFastRequest implements Serializable
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
    * Account Fee Parm Recid member variable.
    */
   private Integer _AcctFeeParmId = null;
            
   /**
    * Fee Definition member variable.
    */
   private Integer _FeeCode = null;
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * Fee Type (flat, prcnt, scale, tier) member variable.
    */
   private String _FeeType = "";
            
   /**
    * Fee / Rate member variable.
    */
   private String _Rate = "0";
            
   /**
    * Minimum Fee member variable.
    */
   private String _MinFee = "0";
            
   /**
    * Maximum Fee member variable.
    */
   private String _MaxFee = "0";
            
   /**
    * Fund member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class member variable.
    */
   private String _ClassCode = "";
            
   /**
    * From Fund member variable.
    */
   private String _FundFromCode = "";
            
   /**
    * From Class member variable.
    */
   private String _ClassFromCode = "";
            
   /**
    * Modify, Add, Delete member variable.
    */
   private String _RunMode = "";
            
   /**
    * Process Date member variable.
    */
   private Date _ProcessDate = null;
            
   /**
    * Modify Date member variable.
    */
   private Date _ModDate = null;
            
   /**
    * User Name member variable.
    */
   private String _UserName = "";
            
   /**
    * Modify User member variable.
    */
   private String _ModUser = "";
            
   /**
    * Commission Group member variable.
    */
   private String _CommGroup = "";
            
   /**
    * Based On member variable.
    */
   private String _BasedOn = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Scale Run Mode member array.
    */
   private String[] _ScaleRunMode = new String[25];
            
   /**
    * Scale Rate member array.
    */
   private String[] _ScaleRate = new String[25];
            
   /**
    * Upper Bound member array.
    */
   private String[] _UpperBound = new String[25];
            
   /**
    * Lower Bound member array.
    */
   private String[] _LowerBound = new String[25];
            
   /**
    * Level member array.
    */
   private Integer[] _Level = new Integer[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _ScaleEffectiveDate = new Date[25];
            
   /**
    * Scale Detl Recid member array.
    */
   private Integer[] _ScaleDetlRid = new Integer[25];
            

   /**
    * Constructs the AcctLvlFeeUpdRequest object.
    * 
    */
   AcctLvlFeeUpdRequest()
   {
      super ( 196 );
   }

   /**
    * Constructs the AcctLvlFeeUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctLvlFeeUpdRequest( String hostEncoding )
   {
      super ( 196, hostEncoding );
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
    * Sets the Account Fee Parm Recid field for the request.
    * 
    * @param value  Value that the Account Fee Parm Recid will be set to.
    */
   public final void setAcctFeeParmId( Integer value )
   {
      assertUnsent();
      _AcctFeeParmId = value;
   }
	
   /**
    * Sets the Fee Definition field for the request.
    * 
    * @param value  Value that the Fee Definition will be set to.
    */
   public final void setFeeCode( Integer value )
   {
      assertUnsent();
      _FeeCode = value;
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
    * Sets the Stop Date field for the request.
    * 
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( Date value )
   {
      assertUnsent();
      _StopDate = value;
   }
	
   /**
    * Sets the Fee Type (flat, prcnt, scale, tier) field for the request.
    * 
    * @param value  Value that the Fee Type (flat, prcnt, scale, tier) will be set to.
    */
   public final void setFeeType( String value )
   {
      assertUnsent();
      _FeeType = value;
   }
	
   /**
    * Sets the Fee / Rate field for the request.
    * 
    * @param value  Value that the Fee / Rate will be set to.
    */
   public final void setRate( String value )
   {
      assertUnsent();
      _Rate = value;
   }
	
   /**
    * Sets the Minimum Fee field for the request.
    * 
    * @param value  Value that the Minimum Fee will be set to.
    */
   public final void setMinFee( String value )
   {
      assertUnsent();
      _MinFee = value;
   }
	
   /**
    * Sets the Maximum Fee field for the request.
    * 
    * @param value  Value that the Maximum Fee will be set to.
    */
   public final void setMaxFee( String value )
   {
      assertUnsent();
      _MaxFee = value;
   }
	
   /**
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the From Fund field for the request.
    * 
    * @param value  Value that the From Fund will be set to.
    */
   public final void setFundFromCode( String value )
   {
      assertUnsent();
      _FundFromCode = value;
   }
	
   /**
    * Sets the From Class field for the request.
    * 
    * @param value  Value that the From Class will be set to.
    */
   public final void setClassFromCode( String value )
   {
      assertUnsent();
      _ClassFromCode = value;
   }
	
   /**
    * Sets the Modify, Add, Delete field for the request.
    * 
    * @param value  Value that the Modify, Add, Delete will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
   }
	
   /**
    * Sets the Process Date field for the request.
    * 
    * @param value  Value that the Process Date will be set to.
    */
   public final void setProcessDate( Date value )
   {
      assertUnsent();
      _ProcessDate = value;
   }
	
   /**
    * Sets the Modify Date field for the request.
    * 
    * @param value  Value that the Modify Date will be set to.
    */
   public final void setModDate( Date value )
   {
      assertUnsent();
      _ModDate = value;
   }
	
   /**
    * Sets the User Name field for the request.
    * 
    * @param value  Value that the User Name will be set to.
    */
   public final void setUserName( String value )
   {
      assertUnsent();
      _UserName = value;
   }
	
   /**
    * Sets the Modify User field for the request.
    * 
    * @param value  Value that the Modify User will be set to.
    */
   public final void setModUser( String value )
   {
      assertUnsent();
      _ModUser = value;
   }
	
   /**
    * Sets the Commission Group field for the request.
    * 
    * @param value  Value that the Commission Group will be set to.
    */
   public final void setCommGroup( String value )
   {
      assertUnsent();
      _CommGroup = value;
   }
	
   /**
    * Sets the Based On field for the request.
    * 
    * @param value  Value that the Based On will be set to.
    */
   public final void setBasedOn( String value )
   {
      assertUnsent();
      _BasedOn = value;
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
    * Sets the Scale Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Scale Run Mode will be set to.
    */
   public final void setScaleRunMode( int index, String value )
   {
      assertUnsent();
      _ScaleRunMode[index] = value;
   }
	
   /**
    * Sets the Scale Rate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Scale Rate will be set to.
    */
   public final void setScaleRate( int index, String value )
   {
      assertUnsent();
      _ScaleRate[index] = value;
   }
	
   /**
    * Sets the Upper Bound field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Upper Bound will be set to.
    */
   public final void setUpperBound( int index, String value )
   {
      assertUnsent();
      _UpperBound[index] = value;
   }
	
   /**
    * Sets the Lower Bound field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Lower Bound will be set to.
    */
   public final void setLowerBound( int index, String value )
   {
      assertUnsent();
      _LowerBound[index] = value;
   }
	
   /**
    * Sets the Level field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Level will be set to.
    */
   public final void setLevel( int index, Integer value )
   {
      assertUnsent();
      _Level[index] = value;
   }
	
   /**
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setScaleEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _ScaleEffectiveDate[index] = value;
   }
	
   /**
    * Sets the Scale Detl Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Scale Detl Recid will be set to.
    */
   public final void setScaleDetlRid( int index, Integer value )
   {
      assertUnsent();
      _ScaleDetlRid[index] = value;
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
      requestBuffer.appendField( _AcctFeeParmId );
      requestBuffer.appendField( _FeeCode );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _FeeType );
      requestBuffer.appendField( _Rate );
      requestBuffer.appendField( _MinFee );
      requestBuffer.appendField( _MaxFee );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _FundFromCode );
      requestBuffer.appendField( _ClassFromCode );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _ProcessDate );
      requestBuffer.appendField( _ModDate );
      requestBuffer.appendField( _UserName );
      requestBuffer.appendField( _ModUser );
      requestBuffer.appendField( _CommGroup );
      requestBuffer.appendField( _BasedOn );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _ScaleRunMode[x] );
         requestBuffer.appendField( _ScaleRate[x] );
         requestBuffer.appendField( _UpperBound[x] );
         requestBuffer.appendField( _LowerBound[x] );
         requestBuffer.appendField( _Level[x] );
         requestBuffer.appendField( _ScaleEffectiveDate[x] );
         requestBuffer.appendField( _ScaleDetlRid[x] );
      }
   }

}

