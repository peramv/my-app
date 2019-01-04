// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Entity Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/EntInfoUpd.doc">EntInfoUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntInfoUpdRequest extends IFastRequest implements Serializable
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
    * Update Entity Info of Account with same CIF member variable.
    */
   private Boolean _UpdSameCIFInfo = new Boolean(false);
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Entity ID member array.
    */
   private String[] _EntityId = new String[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Salutation member array.
    */
   private String[] _Salutation = new String[25];
            
   /**
    * Last Name member array.
    */
   private String[] _LastName = new String[25];
            
   /**
    * First Name member array.
    */
   private String[] _FirstName = new String[25];
            
   /**
    * Birth Last Name member array.
    */
   private String[] _BirthLastName = new String[25];
            
   /**
    * Birth First Name member array.
    */
   private String[] _BirthFirstName = new String[25];
            
   /**
    * Gender member array.
    */
   private String[] _Gender = new String[25];
            
   /**
    * Date of Birth member array.
    */
   private Date[] _DofBirth = new Date[25];
            
   /**
    * Social Insurance Number member array.
    */
   private String[] _SIN = new String[25];
            
   /**
    * Type of Occupation member array.
    */
   private String[] _OccupationCode = new String[25];
            
   /**
    * Language Used by the Entity member array.
    */
   private String[] _Lang = new String[25];
            
   /**
    * Home Phone Number member array.
    */
   private String[] _HomePhone = new String[25];
            
   /**
    * Home Fax Number member array.
    */
   private String[] _HomeFax = new String[25];
            
   /**
    * Business Phone Number member array.
    */
   private String[] _BusinessPhone = new String[25];
            
   /**
    * Business Phone Extension member array.
    */
   private String[] _BusinessExt = new String[25];
            
   /**
    * Business Fax Number member array.
    */
   private String[] _BusinessFax = new String[25];
            
   /**
    * Telex Number member array.
    */
   private String[] _Telex = new String[25];
            
   /**
    * Email Address member array.
    */
   private String[] _Email = new String[25];
            
   /**
    * Date of Death member array.
    */
   private Date[] _DofDeath = new Date[25];
            
   /**
    * Date of Notication of Death member array.
    */
   private Date[] _DofDeathNotice = new Date[25];
            
   /**
    * Entity-Identity Table Version Number member array.
    */
   private Integer[] _EntityIdentityVer = new Integer[25];
            
   /**
    * Entity-Identity Table RECID member array.
    */
   private Integer[] _EntityIdentityRid = new Integer[25];
            
   /**
    * Telephone Number Country Code member array.
    */
   private String[] _HomePhoneCntry = new String[25];
            
   /**
    * Telephone Number Area Code member array.
    */
   private String[] _HomePhoneArea = new String[25];
            
   /**
    * Bus. Telephone Number Country Code member array.
    */
   private String[] _BusinessPhoneCntry = new String[25];
            
   /**
    * Bus. Telephone Number Area Code member array.
    */
   private String[] _BusinessPhoneArea = new String[25];
            
   /**
    * Home Fax Number Country Code member array.
    */
   private String[] _HomeFaxCntry = new String[25];
            
   /**
    * Home Fax Number Area Code member array.
    */
   private String[] _HomeFaxArea = new String[25];
            
   /**
    * Bus. Fax Number Country Code member array.
    */
   private String[] _BusFaxCntry = new String[25];
            
   /**
    * Bus. Fax Number Area Code member array.
    */
   private String[] _BusFaxArea = new String[25];
            
   /**
    * Employee Flag member array.
    */
   private String[] _EmployeeFlag = new String[25];
            
   /**
    * Nationality member array.
    */
   private String[] _Nationality = new String[25];
            
   /**
    * Other Occupation member array.
    */
   private String[] _OtherOccupation = new String[25];
            
   /**
    * Spouse EntityID member array.
    */
   private Integer[] _SpouseEntityID = new Integer[25];
            
   /**
    * Place of Birth member array.
    */
   private String[] _PlaceOfBirth = new String[25];
            
   /**
    * Risk Level member array.
    */
   private String[] _RiskLevel = new String[25];
            
   /**
    * Effective Date of Tax Jurisdiction Info member array.
    */
   private Date[] _TaxJurisDeff = new Date[25];
            
   /**
    * Tax Jurisdiction of the Entity member array.
    */
   private String[] _TaxJuris = new String[25];
            
   /**
    * EUSD Tax Option member array.
    */
   private String[] _EUSDTaxOption = new String[25];
            
   /**
    * is Prim-Mstr.TaxJuris to be shadowed from Entity-Identity.TaxJuris? member array.
    */
   private Boolean[] _UpdShrTaxJuris = new Boolean[25];
            
   /**
    * Country Of Birth of the Accountholder member array.
    */
   private String[] _CountryOfBirth = new String[25];
            
   /**
    * Contact Name for institutional entity member array.
    */
   private String[] _ContactName = new String[25];
            
   /**
    * Email2 member array.
    */
   private String[] _Email2 = new String[25];
            
   /**
    * Second Phone Number member array.
    */
   private String[] _SecondPhnNum = new String[25];
            
   /**
    * Second Phone Number Extension member array.
    */
   private String[] _SecondPhnNumExt = new String[25];
            
   /**
    * FATCAFFI member array.
    */
   private String[] _FATCAFFI = new String[25];
            

   /**
    * Constructs the EntInfoUpdRequest object.
    * 
    */
   EntInfoUpdRequest()
   {
      super ( 78 );
   }

   /**
    * Constructs the EntInfoUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EntInfoUpdRequest( String hostEncoding )
   {
      super ( 78, hostEncoding );
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
    * Sets the Update Entity Info of Account with same CIF field for the request.
    * 
    * @param value  Value that the Update Entity Info of Account with same CIF will be set to.
    */
   public final void setUpdSameCIFInfo( Boolean value )
   {
      assertUnsent();
      _UpdSameCIFInfo = value;
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
    * Sets the Entity ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity ID will be set to.
    */
   public final void setEntityId( int index, String value )
   {
      assertUnsent();
      _EntityId[index] = value;
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
    * Sets the Salutation field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Salutation will be set to.
    */
   public final void setSalutation( int index, String value )
   {
      assertUnsent();
      _Salutation[index] = value;
   }
	
   /**
    * Sets the Last Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Last Name will be set to.
    */
   public final void setLastName( int index, String value )
   {
      assertUnsent();
      _LastName[index] = value;
   }
	
   /**
    * Sets the First Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the First Name will be set to.
    */
   public final void setFirstName( int index, String value )
   {
      assertUnsent();
      _FirstName[index] = value;
   }
	
   /**
    * Sets the Birth Last Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Birth Last Name will be set to.
    */
   public final void setBirthLastName( int index, String value )
   {
      assertUnsent();
      _BirthLastName[index] = value;
   }
	
   /**
    * Sets the Birth First Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Birth First Name will be set to.
    */
   public final void setBirthFirstName( int index, String value )
   {
      assertUnsent();
      _BirthFirstName[index] = value;
   }
	
   /**
    * Sets the Gender field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Gender will be set to.
    */
   public final void setGender( int index, String value )
   {
      assertUnsent();
      _Gender[index] = value;
   }
	
   /**
    * Sets the Date of Birth field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Date of Birth will be set to.
    */
   public final void setDofBirth( int index, Date value )
   {
      assertUnsent();
      _DofBirth[index] = value;
   }
	
   /**
    * Sets the Social Insurance Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Social Insurance Number will be set to.
    */
   public final void setSIN( int index, String value )
   {
      assertUnsent();
      _SIN[index] = value;
   }
	
   /**
    * Sets the Type of Occupation field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Type of Occupation will be set to.
    */
   public final void setOccupationCode( int index, String value )
   {
      assertUnsent();
      _OccupationCode[index] = value;
   }
	
   /**
    * Sets the Language Used by the Entity field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Language Used by the Entity will be set to.
    */
   public final void setLang( int index, String value )
   {
      assertUnsent();
      _Lang[index] = value;
   }
	
   /**
    * Sets the Home Phone Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Home Phone Number will be set to.
    */
   public final void setHomePhone( int index, String value )
   {
      assertUnsent();
      _HomePhone[index] = value;
   }
	
   /**
    * Sets the Home Fax Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Home Fax Number will be set to.
    */
   public final void setHomeFax( int index, String value )
   {
      assertUnsent();
      _HomeFax[index] = value;
   }
	
   /**
    * Sets the Business Phone Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Business Phone Number will be set to.
    */
   public final void setBusinessPhone( int index, String value )
   {
      assertUnsent();
      _BusinessPhone[index] = value;
   }
	
   /**
    * Sets the Business Phone Extension field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Business Phone Extension will be set to.
    */
   public final void setBusinessExt( int index, String value )
   {
      assertUnsent();
      _BusinessExt[index] = value;
   }
	
   /**
    * Sets the Business Fax Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Business Fax Number will be set to.
    */
   public final void setBusinessFax( int index, String value )
   {
      assertUnsent();
      _BusinessFax[index] = value;
   }
	
   /**
    * Sets the Telex Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Telex Number will be set to.
    */
   public final void setTelex( int index, String value )
   {
      assertUnsent();
      _Telex[index] = value;
   }
	
   /**
    * Sets the Email Address field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Email Address will be set to.
    */
   public final void setEmail( int index, String value )
   {
      assertUnsent();
      _Email[index] = value;
   }
	
   /**
    * Sets the Date of Death field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Date of Death will be set to.
    */
   public final void setDofDeath( int index, Date value )
   {
      assertUnsent();
      _DofDeath[index] = value;
   }
	
   /**
    * Sets the Date of Notication of Death field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Date of Notication of Death will be set to.
    */
   public final void setDofDeathNotice( int index, Date value )
   {
      assertUnsent();
      _DofDeathNotice[index] = value;
   }
	
   /**
    * Sets the Entity-Identity Table Version Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity-Identity Table Version Number will be set to.
    */
   public final void setEntityIdentityVer( int index, Integer value )
   {
      assertUnsent();
      _EntityIdentityVer[index] = value;
   }
	
   /**
    * Sets the Entity-Identity Table RECID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity-Identity Table RECID will be set to.
    */
   public final void setEntityIdentityRid( int index, Integer value )
   {
      assertUnsent();
      _EntityIdentityRid[index] = value;
   }
	
   /**
    * Sets the Telephone Number Country Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Telephone Number Country Code will be set to.
    */
   public final void setHomePhoneCntry( int index, String value )
   {
      assertUnsent();
      _HomePhoneCntry[index] = value;
   }
	
   /**
    * Sets the Telephone Number Area Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Telephone Number Area Code will be set to.
    */
   public final void setHomePhoneArea( int index, String value )
   {
      assertUnsent();
      _HomePhoneArea[index] = value;
   }
	
   /**
    * Sets the Bus. Telephone Number Country Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bus. Telephone Number Country Code will be set to.
    */
   public final void setBusinessPhoneCntry( int index, String value )
   {
      assertUnsent();
      _BusinessPhoneCntry[index] = value;
   }
	
   /**
    * Sets the Bus. Telephone Number Area Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bus. Telephone Number Area Code will be set to.
    */
   public final void setBusinessPhoneArea( int index, String value )
   {
      assertUnsent();
      _BusinessPhoneArea[index] = value;
   }
	
   /**
    * Sets the Home Fax Number Country Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Home Fax Number Country Code will be set to.
    */
   public final void setHomeFaxCntry( int index, String value )
   {
      assertUnsent();
      _HomeFaxCntry[index] = value;
   }
	
   /**
    * Sets the Home Fax Number Area Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Home Fax Number Area Code will be set to.
    */
   public final void setHomeFaxArea( int index, String value )
   {
      assertUnsent();
      _HomeFaxArea[index] = value;
   }
	
   /**
    * Sets the Bus. Fax Number Country Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bus. Fax Number Country Code will be set to.
    */
   public final void setBusFaxCntry( int index, String value )
   {
      assertUnsent();
      _BusFaxCntry[index] = value;
   }
	
   /**
    * Sets the Bus. Fax Number Area Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bus. Fax Number Area Code will be set to.
    */
   public final void setBusFaxArea( int index, String value )
   {
      assertUnsent();
      _BusFaxArea[index] = value;
   }
	
   /**
    * Sets the Employee Flag field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Employee Flag will be set to.
    */
   public final void setEmployeeFlag( int index, String value )
   {
      assertUnsent();
      _EmployeeFlag[index] = value;
   }
	
   /**
    * Sets the Nationality field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Nationality will be set to.
    */
   public final void setNationality( int index, String value )
   {
      assertUnsent();
      _Nationality[index] = value;
   }
	
   /**
    * Sets the Other Occupation field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Other Occupation will be set to.
    */
   public final void setOtherOccupation( int index, String value )
   {
      assertUnsent();
      _OtherOccupation[index] = value;
   }
	
   /**
    * Sets the Spouse EntityID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Spouse EntityID will be set to.
    */
   public final void setSpouseEntityID( int index, Integer value )
   {
      assertUnsent();
      _SpouseEntityID[index] = value;
   }
	
   /**
    * Sets the Place of Birth field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Place of Birth will be set to.
    */
   public final void setPlaceOfBirth( int index, String value )
   {
      assertUnsent();
      _PlaceOfBirth[index] = value;
   }
	
   /**
    * Sets the Risk Level field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Risk Level will be set to.
    */
   public final void setRiskLevel( int index, String value )
   {
      assertUnsent();
      _RiskLevel[index] = value;
   }
	
   /**
    * Sets the Effective Date of Tax Jurisdiction Info field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date of Tax Jurisdiction Info will be set to.
    */
   public final void setTaxJurisDeff( int index, Date value )
   {
      assertUnsent();
      _TaxJurisDeff[index] = value;
   }
	
   /**
    * Sets the Tax Jurisdiction of the Entity field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Tax Jurisdiction of the Entity will be set to.
    */
   public final void setTaxJuris( int index, String value )
   {
      assertUnsent();
      _TaxJuris[index] = value;
   }
	
   /**
    * Sets the EUSD Tax Option field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the EUSD Tax Option will be set to.
    */
   public final void setEUSDTaxOption( int index, String value )
   {
      assertUnsent();
      _EUSDTaxOption[index] = value;
   }
	
   /**
    * Sets the is Prim-Mstr.TaxJuris to be shadowed from Entity-Identity.TaxJuris? field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the is Prim-Mstr.TaxJuris to be shadowed from Entity-Identity.TaxJuris? will be set to.
    */
   public final void setUpdShrTaxJuris( int index, Boolean value )
   {
      assertUnsent();
      _UpdShrTaxJuris[index] = value;
   }
	
   /**
    * Sets the Country Of Birth of the Accountholder field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Country Of Birth of the Accountholder will be set to.
    */
   public final void setCountryOfBirth( int index, String value )
   {
      assertUnsent();
      _CountryOfBirth[index] = value;
   }
	
   /**
    * Sets the Contact Name for institutional entity field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Contact Name for institutional entity will be set to.
    */
   public final void setContactName( int index, String value )
   {
      assertUnsent();
      _ContactName[index] = value;
   }
	
   /**
    * Sets the Email2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Email2 will be set to.
    */
   public final void setEmail2( int index, String value )
   {
      assertUnsent();
      _Email2[index] = value;
   }
	
   /**
    * Sets the Second Phone Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Second Phone Number will be set to.
    */
   public final void setSecondPhnNum( int index, String value )
   {
      assertUnsent();
      _SecondPhnNum[index] = value;
   }
	
   /**
    * Sets the Second Phone Number Extension field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Second Phone Number Extension will be set to.
    */
   public final void setSecondPhnNumExt( int index, String value )
   {
      assertUnsent();
      _SecondPhnNumExt[index] = value;
   }
	
   /**
    * Sets the FATCAFFI field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the FATCAFFI will be set to.
    */
   public final void setFATCAFFI( int index, String value )
   {
      assertUnsent();
      _FATCAFFI[index] = value;
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
      requestBuffer.appendField( _UpdSameCIFInfo );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _EntityId[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _Salutation[x] );
         requestBuffer.appendField( _LastName[x] );
         requestBuffer.appendField( _FirstName[x] );
         requestBuffer.appendField( _BirthLastName[x] );
         requestBuffer.appendField( _BirthFirstName[x] );
         requestBuffer.appendField( _Gender[x] );
         requestBuffer.appendField( _DofBirth[x] );
         requestBuffer.appendField( _SIN[x] );
         requestBuffer.appendField( _OccupationCode[x] );
         requestBuffer.appendField( _Lang[x] );
         requestBuffer.appendField( _HomePhone[x] );
         requestBuffer.appendField( _HomeFax[x] );
         requestBuffer.appendField( _BusinessPhone[x] );
         requestBuffer.appendField( _BusinessExt[x] );
         requestBuffer.appendField( _BusinessFax[x] );
         requestBuffer.appendField( _Telex[x] );
         requestBuffer.appendField( _Email[x] );
         requestBuffer.appendField( _DofDeath[x] );
         requestBuffer.appendField( _DofDeathNotice[x] );
         requestBuffer.appendField( _EntityIdentityVer[x] );
         requestBuffer.appendField( _EntityIdentityRid[x] );
         requestBuffer.appendField( _HomePhoneCntry[x] );
         requestBuffer.appendField( _HomePhoneArea[x] );
         requestBuffer.appendField( _BusinessPhoneCntry[x] );
         requestBuffer.appendField( _BusinessPhoneArea[x] );
         requestBuffer.appendField( _HomeFaxCntry[x] );
         requestBuffer.appendField( _HomeFaxArea[x] );
         requestBuffer.appendField( _BusFaxCntry[x] );
         requestBuffer.appendField( _BusFaxArea[x] );
         requestBuffer.appendField( _EmployeeFlag[x] );
         requestBuffer.appendField( _Nationality[x] );
         requestBuffer.appendField( _OtherOccupation[x] );
         requestBuffer.appendField( _SpouseEntityID[x] );
         requestBuffer.appendField( _PlaceOfBirth[x] );
         requestBuffer.appendField( _RiskLevel[x] );
         requestBuffer.appendField( _TaxJurisDeff[x] );
         requestBuffer.appendField( _TaxJuris[x] );
         requestBuffer.appendField( _EUSDTaxOption[x] );
         requestBuffer.appendField( _UpdShrTaxJuris[x] );
         requestBuffer.appendField( _CountryOfBirth[x] );
         requestBuffer.appendField( _ContactName[x] );
         requestBuffer.appendField( _Email2[x] );
         requestBuffer.appendField( _SecondPhnNum[x] );
         requestBuffer.appendField( _SecondPhnNumExt[x] );
         requestBuffer.appendField( _FATCAFFI[x] );
      }
   }

}

