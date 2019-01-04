//******************************************************************************
//
// ^FILE   : DSTCAWDSession.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Dec. 18, 2003
//
// ^CLASS    : DSTCAWDSession
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <core\bfsessn\bfcpsession.hpp>

#undef IFASTAWD_LINKAGE
#ifdef IFASTAWD_DLL
   #define IFASTAWD_LINKAGE CLASS_EXPORT
#else
   #define IFASTAWD_LINKAGE CLASS_IMPORT
#endif
class DSTCAWDDataConvert;
class DSTCWorkSession;
class BFAwdInterface;
class BFAwdData;

class IFASTAWD_LINKAGE DSTCAWDSession : public BFCPSession
{

public:
	DSTCAWDSession(BFCPSession* pParent);
	~DSTCAWDSession();

public:
   void setAwdField(const DString& dstrNameTag,const DString& dstrValue );	
   void getAwdField(const DString& dstrTag,DString& dstrValue );
   void associateDSTCWorkSession(DSTCWorkSession* pWorkSession, bool bCheck = false );	
   void setAwdField(const BFFieldId& idField,
                          const DString& strValue );
 
   void getAwdField( const BFFieldId& idField,
						   DString& dstrValue );
   string_vector getAwdBusinessAreaList( );
   void getBusinessAreaByCompanyId( const DString &dstrCompanyId, DString &dstrBusinessArea );
   string_vector getWorkTypeList(const DString& dstrBusinessArea);

   string_vector getAwdStatusList( const DString& dstrBussArea, const DString& dstrWkType );
   DString getCurrentWork();

   bool isAWDWorking();
   bool hasWorkObject();	  
   void setAWDBeginTime();
   void setAWDEndTime();
   SEVERITY CallInquiry();
   SEVERITY EndCall();
   SEVERITY CallInquiryEndCall();
   SEVERITY CallInquiryUpdate(const DString& eventType,  DString& event,bool bUpdateOrg);

   void init(DSTCWorkSession* pWorkSession );
   void setupWorkArea(const DString& dstrEvent);
   bool isCallStarted(); 
   SEVERITY cleanupAWDObject( );
   void storeCallerInfo(DSTCAWDSession *pSession);	
   bool isContainerEmpty();
   DString getCurrentStatus();
   SEVERITY retrieveObjectId();
   SEVERITY lookupAWDImageByObjectId(const DString& dstrObjId);
   SEVERITY addDirectCommentToAWD(const DString& comment, const BFDataGroupId& idDataGroup);
   void saveCurrentObject();
   SEVERITY cloneAwdObject();
   bool	canClone();
   bool isOrgWorkUpdated();
   SEVERITY validateDirectCommentToAWD(const DString& comment, const BFDataGroupId& idDataGroup);

private:
	DSTCWorkSession* getDSTCWorkSession()
	{
		return m_pWorkSession;	
	}

	BFAwdInterface* getAwdInterface(void);
	void cleanCallerInfo();

	DSTCAWDDataConvert* getAWDDataConvert();
	SEVERITY createAWDObject(const DString& event, DString& dstrEvent );
	void getOperatorExtension();
	void saveOperatorExtension();
	bool isBusinessAreaEmpty();
	bool isWorkTypeEmpty();
	bool isStatusEmpty();
   SEVERITY updateOriginalAwdObject();
	void retrieveBusinessWorkStatusFromIni(DString& dstrTable);
   SEVERITY repositionWork( BFAwdData* pAwdNewWork );
private: 	
   bool  m_bOrgUpdated;
   const BFAwdData* m_AwdWorkData;
   BFData m_AWDData;
   BFAwdData* m_pCaseData;
   BFAwdInterface*   m_pAwdInterface; 
   BFCPSession* m_pParent;
   DSTCWorkSession* m_pWorkSession;
   DSTCAWDDataConvert* m_pConvert;
   friend class DSTCAWDDataConvert;
   BFAwdData * m_pAwdOriginalWork;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastawd/DSTCAWDSession.hpp-arc  $
//
//   Rev 1.19   01 Feb 2008 09:03:06   kovacsro
//IN#1118094&1114586 - filtering the status list on the queue, bussArea and workType
//
//   Rev 1.18   Apr 17 2006 14:30:02   popescu
//Incident# 544677 - subsequent fix when objects are cloned
//
//   Rev 1.17   Mar 07 2006 15:44:20   popescu
//Incident# 544677 - subsequent fix when objects are cloned
//
//   Rev 1.16   Aug 24 2004 09:55:20   HERNANDO
//PTS 10033149 - Created validateAddDirectCommenttoAWD in order to handle Warning messages appropriately.
//
//   Rev 1.15   May 26 2004 15:37:36   HERNANDO
//PET1017 FN01 - Additional enhancement - Display error or warning message based on environment (ErrMsgRuleList #415).  Added DataGroupId to addCommentDirectlytoAWD.
//
//   Rev 1.14   May 08 2004 10:12:24   YINGBAOL
//PET1017:Fix locking issue for cloning and max comments for adding comments
//
//   Rev 1.13   Apr 30 2004 10:43:48   YINGBAOL
//Fix work type status for add comments
//
//   Rev 1.12   Apr 29 2004 16:43:28   YINGBAOL
//PET1017: more function added for support clone
//
//   Rev 1.11   Apr 26 2004 16:02:10   YINGBAOL
//PEt 1017: Add clone support
//
//   Rev 1.10   Apr 20 2004 14:16:56   YINGBAOL
//PET1017 Add comments directly to AWD object
//
//   Rev 1.9   Apr 20 2004 11:01:12   YINGBAOL
//PET1017 FN2 and FN3 retrieve AWD source image by object ID
//
//   Rev 1.8   Mar 24 2004 17:49:10   HERNANDO
//Update business area.
//
//   Rev 1.7   Mar 22 2004 17:43:02   YINGBAOL
//PTS10028360:change WorkType,Status
//
//   Rev 1.6   Mar 12 2004 10:29:50   YINGBAOL
//PTS10027730:fix worktype override logic 
//
//   Rev 1.5   Feb 23 2004 14:58:26   YINGBAOL
//PTS10027244:Strore caller information to new object.
//
//   Rev 1.4   Feb 23 2004 09:40:52   YINGBAOL
//PTS10027246: F11 buton clear AWD Container
//
//   Rev 1.3   Jan 22 2004 11:43:20   PURDYECH
//PET987 - Removed unnecessary #include if <ifastcbo/mfcancbo.hpp> and added PVCS logging section.
//
