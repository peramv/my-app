// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * EntityWhereUse Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/EntWhUseMaint.doc">EntWhUseMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntWhUseMaintRequest extends IFastRequest implements Serializable
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
   private String _CompanyID = "";
            
            
            
            
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Entity Identity member array.
    */
   private String[] _EntityId = new String[25];
            
   /**
    * Where Entity is Used member array.
    */
   private String[] _WhereUse = new String[25];
            
   /**
    * Key identitification of Entity member array.
    */
   private String[] _WhereUseKey = new String[25];
            
   /**
    * Relationship Code member array.
    */
   private String[] _RelationshipCode = new String[25];
            
   /**
    * EntityWhereUseRid member array.
    */
   private Integer[] _EntityWhereUseRid = new Integer[25];
            
   /**
    * EntityWhereUseVersion member array.
    */
   private Integer[] _EntityWhereUseVer = new Integer[25];
            
   /**
    * Effective date of entity usage member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Date the entity usage stops member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Holding Company Name member array.
    */
   private String[] _HoldingCoName = new String[25];
            
   /**
    * Company Usage member array.
    */
   private String[] _CoUsage = new String[25];
            
   /**
    * Aggregation Method member array.
    */
   private String[] _AggrMethod = new String[25];
            
   /**
    * Language Code member array.
    */
   private String[] _LangCode = new String[25];
            

   /**
    * Constructs the EntWhUseMaintRequest object.
    * 
    */
   EntWhUseMaintRequest()
   {
      super ( 331 );
   }

   /**
    * Constructs the EntWhUseMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EntWhUseMaintRequest( String hostEncoding )
   {
      super ( 331, hostEncoding );
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
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
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
    * Sets the Entity Identity field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity Identity will be set to.
    */
   public final void setEntityId( int index, String value )
   {
      assertUnsent();
      _EntityId[index] = value;
   }
	
   /**
    * Sets the Where Entity is Used field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Where Entity is Used will be set to.
    */
   public final void setWhereUse( int index, String value )
   {
      assertUnsent();
      _WhereUse[index] = value;
   }
	
   /**
    * Sets the Key identitification of Entity field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Key identitification of Entity will be set to.
    */
   public final void setWhereUseKey( int index, String value )
   {
      assertUnsent();
      _WhereUseKey[index] = value;
   }
	
   /**
    * Sets the Relationship Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Relationship Code will be set to.
    */
   public final void setRelationshipCode( int index, String value )
   {
      assertUnsent();
      _RelationshipCode[index] = value;
   }
	
   /**
    * Sets the EntityWhereUseRid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the EntityWhereUseRid will be set to.
    */
   public final void setEntityWhereUseRid( int index, Integer value )
   {
      assertUnsent();
      _EntityWhereUseRid[index] = value;
   }
	
   /**
    * Sets the EntityWhereUseVersion field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the EntityWhereUseVersion will be set to.
    */
   public final void setEntityWhereUseVer( int index, Integer value )
   {
      assertUnsent();
      _EntityWhereUseVer[index] = value;
   }
	
   /**
    * Sets the Effective date of entity usage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective date of entity usage will be set to.
    */
   public final void setEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _EffectiveDate[index] = value;
   }
	
   /**
    * Sets the Date the entity usage stops field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Date the entity usage stops will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the Holding Company Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Holding Company Name will be set to.
    */
   public final void setHoldingCoName( int index, String value )
   {
      assertUnsent();
      _HoldingCoName[index] = value;
   }
	
   /**
    * Sets the Company Usage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Company Usage will be set to.
    */
   public final void setCoUsage( int index, String value )
   {
      assertUnsent();
      _CoUsage[index] = value;
   }
	
   /**
    * Sets the Aggregation Method field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Aggregation Method will be set to.
    */
   public final void setAggrMethod( int index, String value )
   {
      assertUnsent();
      _AggrMethod[index] = value;
   }
	
   /**
    * Sets the Language Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Language Code will be set to.
    */
   public final void setLangCode( int index, String value )
   {
      assertUnsent();
      _LangCode[index] = value;
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
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _EntityId[x] );
         requestBuffer.appendField( _WhereUse[x] );
         requestBuffer.appendField( _WhereUseKey[x] );
         requestBuffer.appendField( _RelationshipCode[x] );
         requestBuffer.appendField( _EntityWhereUseRid[x] );
         requestBuffer.appendField( _EntityWhereUseVer[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _HoldingCoName[x] );
         requestBuffer.appendField( _CoUsage[x] );
         requestBuffer.appendField( _AggrMethod[x] );
         requestBuffer.appendField( _LangCode[x] );
      }
   }

}

