// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Market Index Related Funds Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/MktIndxRelFndsMaint.doc">MktIndxRelFndsMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class MktIndxRelFndsMaintRequest extends IFastRequest implements Serializable
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
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * MktIndexVer member variable.
    */
   private Integer _MktIndexVer = null;
            
   /**
    * Record Id of MktIndex member variable.
    */
   private Integer _MktIndexRid = null;
            
   /**
    * Index Code member variable.
    */
   private String _IndexCode = "";
            
   /**
    * Index Name member variable.
    */
   private String _IndexName = "";
            
   /**
    * Days Basis member variable.
    */
   private String _DaysBasis = "";
            
   /**
    * Input Data Type member variable.
    */
   private String _InputDataType = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode for repeating section member array.
    */
   private String[] _FundRunMode = new String[25];
            
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = new String[25];
            
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = new String[25];
            
   /**
    * Record Id of Fund Detl member array.
    */
   private Integer[] _FundDetlRid = new Integer[25];
            
   /**
    * Fund Detl Version member array.
    */
   private String[] _FundDetlVer = new String[25];
            

   /**
    * Constructs the MktIndxRelFndsMaintRequest object.
    * 
    */
   MktIndxRelFndsMaintRequest()
   {
      super ( 242 );
   }

   /**
    * Constructs the MktIndxRelFndsMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   MktIndxRelFndsMaintRequest( String hostEncoding )
   {
      super ( 242, hostEncoding );
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
    * Sets the Run Mode field for the request.
    * 
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
   }
	
   /**
    * Sets the MktIndexVer field for the request.
    * 
    * @param value  Value that the MktIndexVer will be set to.
    */
   public final void setMktIndexVer( Integer value )
   {
      assertUnsent();
      _MktIndexVer = value;
   }
	
   /**
    * Sets the Record Id of MktIndex field for the request.
    * 
    * @param value  Value that the Record Id of MktIndex will be set to.
    */
   public final void setMktIndexRid( Integer value )
   {
      assertUnsent();
      _MktIndexRid = value;
   }
	
   /**
    * Sets the Index Code field for the request.
    * 
    * @param value  Value that the Index Code will be set to.
    */
   public final void setIndexCode( String value )
   {
      assertUnsent();
      _IndexCode = value;
   }
	
   /**
    * Sets the Index Name field for the request.
    * 
    * @param value  Value that the Index Name will be set to.
    */
   public final void setIndexName( String value )
   {
      assertUnsent();
      _IndexName = value;
   }
	
   /**
    * Sets the Days Basis field for the request.
    * 
    * @param value  Value that the Days Basis will be set to.
    */
   public final void setDaysBasis( String value )
   {
      assertUnsent();
      _DaysBasis = value;
   }
	
   /**
    * Sets the Input Data Type field for the request.
    * 
    * @param value  Value that the Input Data Type will be set to.
    */
   public final void setInputDataType( String value )
   {
      assertUnsent();
      _InputDataType = value;
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
    * Sets the Run Mode for repeating section field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode for repeating section will be set to.
    */
   public final void setFundRunMode( int index, String value )
   {
      assertUnsent();
      _FundRunMode[index] = value;
   }
	
   /**
    * Sets the Fund Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setFundCode( int index, String value )
   {
      assertUnsent();
      _FundCode[index] = value;
   }
	
   /**
    * Sets the Class Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Class Code will be set to.
    */
   public final void setClassCode( int index, String value )
   {
      assertUnsent();
      _ClassCode[index] = value;
   }
	
   /**
    * Sets the Record Id of Fund Detl field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Record Id of Fund Detl will be set to.
    */
   public final void setFundDetlRid( int index, Integer value )
   {
      assertUnsent();
      _FundDetlRid[index] = value;
   }
	
   /**
    * Sets the Fund Detl Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Detl Version will be set to.
    */
   public final void setFundDetlVer( int index, String value )
   {
      assertUnsent();
      _FundDetlVer[index] = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _MktIndexVer );
      requestBuffer.appendField( _MktIndexRid );
      requestBuffer.appendField( _IndexCode );
      requestBuffer.appendField( _IndexName );
      requestBuffer.appendField( _DaysBasis );
      requestBuffer.appendField( _InputDataType );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _FundRunMode[x] );
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _ClassCode[x] );
         requestBuffer.appendField( _FundDetlRid[x] );
         requestBuffer.appendField( _FundDetlVer[x] );
      }
   }

}

