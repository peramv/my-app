#if !defined(CryptoDLL_H_E51gh47u36uue56u78o88717F_82AD_4F5C_B3F6_4CAD86481A56)
#define CryptoDLL_H_E51gh47u36uue56u78o88717F_82AD_4F5C_B3F6_4CAD86481A56
						 
#ifdef EXPORT
	#undef EXPORT
#endif

//PolarCryptoDLL.h
#define EXPORT extern "C" __declspec(dllexport)

//-------------------------
// Key property identifiers - constant for lPropID parameter in SetKeyProperty function 
//-------------------------
#define 	pcpAlgorithmKeylength			 1 
#define 	pcpAlgorithmPadding				 2 
#define 	pcpAlgorithmCiphermode			 3 
#define 	pcpAlgorithmID					 5 
#define 	pcpAlgorithmEncryptionscheme	 6 
#define 	pcpAlgorithmInitializationVector 7 

//-------------------------
//pcpPadding constant for lValue parameter where lPropID == pcpAlgorithmPadding in SetKeyProperty function 
//-------------------------
#define pcpZeroPadding	1
#define pcpPKCS5		2
#define pcpFIPS81		3
#define pcpRandom		4

//-------------------------
//constant for parameter pclKeyLength in GenerateKey, DeriveKey functions
//and for for lValue parameter where lPropID == pcpAlgorithmKeylength in SetKeyProperty function 
//-------------------------
#define pcl128bit	128
#define pcl192bit	192
#define pcl256bit	256
#define pcl512bit	512
#define pcl1024bit	1024
#define pcl2048bit	2048
#define pclDefault	0   

//-------------------------
//constant for parameter pctKeyTypes in GenerateKey, DeriveKey, ForceKey functions 
//and for for lValue parameter where lPropID == pcpAlgorithmID in SetKeyProperty function 
//-------------------------
#define pcaAES			1
#define pcaTwoFish		2
#define pcaRSAPrivate	3
#define pcaRSAPublic	4
						 
//-------------------------
//pcmCipherMode constant for lValue parameter where lPropID == pcpAlgorithmCiphermode in SetKeyProperty function 
//-------------------------
#define pcmECB		 1
#define pcmCBC		 2
							   
//-------------------------
//pcsEncryptionScheme constant for lValue parameter where lPropID == pcpAlgorithmEncryptionscheme in SetKeyProperty function (only for RSA)
//-------------------------
#define pcsOAEP					1
#define pcsPKCS1				2

//-------------------------
//pceExportKeyType constant for lExportType parameter in ExportKey function
//-------------------------
#define pceDefault	0
#define pcePublic	2
#define pcePrivate	3

//-------------------------
//constant for pcfEncodingFormat parameter in function  ReadDataFromFile, WriteDataToFile, ReadDataFromBuffer and WriteDataToBuffer functions
//-------------------------
#define pcfHex		1
#define pcfBase64	2
#define pcfBinary	3


//-----------------------------------------------------------------------------
//pchHashSize constant for parameter lHashLength in SetHashLength function
//-----------------------------------------------------------------------------
#define pch160	 160
#define pch256	 256
#define pch384	 384
#define pch512	 512

//-----------------------------------------------------------------------------
//pfbExistingFileBehavior constant for Set/GetExistingFileBehavior
//-----------------------------------------------------------------------------
#define pfbSkip			1
#define pfbOverwrite	2

//-------------------------
//pceErrorConstants - constant which every DLL function returns 
//-------------------------		
#define pceSuccess					  0	   
#define pceInternalError			307
#define pceInvalidParam				301
#define pceFileDoesNotExist			302
#define pceCannotOpenFile			303
#define pceOutputFileAlreadyExists	323
#define pceKeyBusy					308
#define pceInvalidKey				314
#define pceIllegalKeyType			314
#define pceInvalidHashObject		318
#define pceUnsupportedHashSize		318
#define pceUnsupportedProperty		304
#define pceInvalidImportFormat		309
#define pceBaseIllegalForRSAKey		310
#define pceUnsuportedKeyLength		311
#define pceReadOnlyProperty			306
#define pceDataTooLong				316
#define pceCantGeneratePublic		317
#define pceCannotCreateFile			319
#define pceEncodingError			320
#define pceDecodingError			321
#define pceWriteError				322
#define pceMethodNotImplemented		315
#define pceMethodCantSignHash		325

//-------------------------
// pscShowCommand - constant for nShowCmd parameter in pcAddExecuteAfter function
// (also for nShowCmd member of ExecAfterItem struct).
//-------------------------		
#define pscHide				0
#define pscMaximize			3
#define pscMinimize			6
#define pscRestore			9
#define pscShow				5
#define pscShowDefault		10
#define pscShowMaximized	3
#define pscShowMinimized	2
#define pscShowMinNoActive	7
#define pscShowNA			8
#define pscShowNoActivate	4
#define pscShowNormal		1

//-----------------------------------------------------------------------------
// handle of data in Polar Crypto
#define HPCRYPTKEY		long
#define HPCRYPTHASH 	long
#define HPCRYPTDATA		long
#define HPCRYPTSFDPROPS long

//--------------------------------------------------------------------------------------------
//Event structure
struct TDllEvent
{
	LONG EventProcessMode;	//pcmEncrypting, pcmDecrypting, pcmHashing, pcmSigning, pcmVerifying or pcmGeneratingRndData
	LONG HandleOfObject;	//handle of Key, CryptoData or Hash
	LONG TypeOfHandle;		//pcoCryptoKey, pcoCryptoHash, pcoCrypto, pcoCryptoData
	LONG Data;				//pointer on data stored in event
	LONG AbortFlag;			//if diferent form FALSE user whant abort this proces when this event occure	
};	

// SfdProperties functions
struct ExecAfterItem 
{
	char* lpVerb;
	char* lpFile;
	char* lpParameters;
	char* lpDirectory;
	LONG nShowCmd;
	
	LONG lVerbLength;
	LONG lFileLength;
	LONG lParametersLength;
	LONG lDirectoryLength;
};

//-------------------------
//constant for memeber TypeOfHandle of TDllEvent struct 
//-------------------------			   
#define pcoCryptoKey 			1
#define pcoCryptoHash 			2
#define pcoCrypto 				3
#define pcoCryptoData			4
#define pcoSfdProperties		5

//-------------------------
//constant for memeber EventProcessMode of TDllEvent struct 
//-------------------------
#define pcmEncrypting			 1
#define pcmDecrypting			 2
#define pcmHashing				 3  
#define pcmSigning				 4 
#define pcmVerifying			 5
#define pcmGeneratingRndData	 6

//-----------------------------------------------------------------------------
//Event constant
#define EVENT_ID_PROCESSSTATUS		100
#define EVENT_ID_PROCESSSTARTED		101
#define EVENT_ID_PROCESSENDED		102
#define EVENT_ID_ERROR				1000

//-----------------------------------------------------------------------------
//Crypto function
EXPORT LONG CALLBACK pcGenerateKey( HPCRYPTKEY*  pKey, LONG pctKeyTypes, LONG pclKeyLength);
EXPORT LONG	CALLBACK pcDeriveKey(HPCRYPTKEY*  pKey, char* pszPassword, LONG pctKeyTypes, LONG pclKeyLength );
EXPORT LONG	CALLBACK pcForceKey(HPCRYPTKEY* pKey, char* pszPassword, LONG pctKeyTypes);
EXPORT LONG CALLBACK pcImportKey( HPCRYPTDATA hCryptoData, HPCRYPTKEY hEncriptionKey, HPCRYPTKEY*  pKey );
EXPORT LONG CALLBACK pcCreateCryptoData(HPCRYPTDATA *phCryptoData );
EXPORT LONG CALLBACK pcCreateSfdProperties(HPCRYPTSFDPROPS  *phSfdProperties);	
EXPORT LONG CALLBACK pcGenerateRandomData( LONG lLength, HPCRYPTDATA* phCryptoData );
EXPORT LONG CALLBACK pcCreateHash( HPCRYPTHASH *phHash  );
EXPORT LONG CALLBACK pcSetRandomGeneratorSeed( LONG lNewValue);		
EXPORT LONG CALLBACK pcGetRandomGeneratorSeed( void );	
					 
//	Key function		 
EXPORT LONG CALLBACK pcEncrypt(HPCRYPTKEY hKey ,HPCRYPTDATA hInCryptoData, HPCRYPTDATA* phCryptoData, LONG EndOfData);
EXPORT LONG CALLBACK pcDecrypt (HPCRYPTKEY hKey, HPCRYPTDATA hInCryptoData, HPCRYPTDATA* phCryptoData, LONG EndOfData);
EXPORT LONG CALLBACK pcEncryptFile( HPCRYPTKEY hKey, char* pszSrcFileName, char* pszDestFileName );
EXPORT LONG CALLBACK pcDecryptFile( HPCRYPTKEY hKey, char* pszSrcFileName,char* pszDestFileName );
EXPORT BOOL CALLBACK pcDestroyKey( HPCRYPTKEY hKey );
EXPORT BOOL CALLBACK pcSetKeyProperty( HPCRYPTKEY hKey, LONG lPropID, LONG lValue);
EXPORT LONG CALLBACK pcGetKeyProperty( HPCRYPTKEY hKey, LONG lPropID, LONG* plValue);
EXPORT LONG CALLBACK pcSignHash( HPCRYPTKEY hKey, HPCRYPTHASH hHash, HPCRYPTDATA*	phCryptoData );
EXPORT LONG CALLBACK pcSign( HPCRYPTKEY hKey, HPCRYPTDATA hInCryptoData, HPCRYPTDATA* phOutCryptoData );
EXPORT LONG CALLBACK pcVerifySignature( HPCRYPTKEY hKey, HPCRYPTHASH hHash, HPCRYPTDATA hInCryptoData );
EXPORT LONG CALLBACK pcCalculateKeyHash( HPCRYPTKEY hKey, HPCRYPTHASH* phHash );
EXPORT LONG CALLBACK pcExportKey( HPCRYPTKEY  hKey, LONG lExportType, HPCRYPTKEY  hEncryptionKey, HPCRYPTDATA*  phOutCryptoData );
// v2.5
EXPORT LONG CALLBACK pcCreateSelfDecrpytingFile( HPCRYPTKEY hKey, char* pszSrcFileName, char* pszDestFileName, HPCRYPTSFDPROPS hSfdProps, BOOL fOverwriteExisting, BOOL* pfResult);
					 
//Hash function		 
EXPORT LONG CALLBACK pcHashData( HPCRYPTHASH hHash, HPCRYPTDATA hCryptoData);
EXPORT LONG CALLBACK pcHashFile(HPCRYPTHASH hHash, char* pszFileName);
EXPORT LONG CALLBACK pcDestroyHash(HPCRYPTHASH hHash );
EXPORT LONG CALLBACK pcGetHashValue(HPCRYPTHASH hHash, HPCRYPTDATA* phCryptoData);
EXPORT LONG CALLBACK pcGetHashLength(HPCRYPTHASH hHash, LONG* plHashLength );
EXPORT LONG CALLBACK pcSetHashLength(HPCRYPTHASH hHash, LONG lHashLength);
					 
//CryptoData function
EXPORT LONG	 CALLBACK pcGetCryptoDataLength( HPCRYPTDATA hCryptoData, LONG* plCryptoDataLength );
EXPORT LONG  CALLBACK pcReadDataFromFile(HPCRYPTDATA hCryptoData, char* szFileName, LONG pcfEncodingFormat);
EXPORT LONG  CALLBACK pcWriteDataToFile(HPCRYPTDATA hCryptoData, char* szFileName, LONG pcfEncodingFormat);
EXPORT LONG  CALLBACK pcReadDataFromBuffer(HPCRYPTDATA hCryptoData, char* pszString, LONG lSize, LONG pcfEncodingFormat );
EXPORT LONG  CALLBACK pcWriteDataToBuffer(HPCRYPTDATA hCryptoData, char* pszString, LONG* plSize, LONG pcfEncodingFormat );
EXPORT LONG  CALLBACK pcCompare	(HPCRYPTDATA hCryptoDataFirs, HPCRYPTDATA hCryptoDataSecond, BOOL* pfOutResult );	 
EXPORT LONG  CALLBACK pcDestroyCryptoData( HPCRYPTDATA hCryptoData );
EXPORT LONG  CALLBACK pcSetStreaming( HPCRYPTDATA hCryptoData, BOOL fStreaming);
EXPORT LONG  CALLBACK pcGetStreaming(HPCRYPTDATA hCryptoData, BOOL* pfValue );	

//SfdProperties function
EXPORT LONG  CALLBACK pcSetAppName(HPCRYPTSFDPROPS hSfdProps, char* szAppName);
EXPORT LONG  CALLBACK pcGetAppName(HPCRYPTSFDPROPS hSfdProps, char* szAppName, long lBuffLength);	
EXPORT LONG  CALLBACK pcSetDefaultFolder(HPCRYPTSFDPROPS hSfdProps, char* szFolderName);                  
EXPORT LONG  CALLBACK pcGetDefaultFolder(HPCRYPTSFDPROPS hSfdProps, char* szFolderName, long lBuffLength);	
EXPORT LONG  CALLBACK pcSetLanguageDll(HPCRYPTSFDPROPS hSfdProps, char* szDllName);                  
EXPORT LONG  CALLBACK pcGetLanguageDll(HPCRYPTSFDPROPS hSfdProps, char* szDllName, long lBuffLength);	
EXPORT LONG  CALLBACK pcSetOutputFilename(HPCRYPTSFDPROPS hSfdProps, char* szFileName);                  
EXPORT LONG  CALLBACK pcGetOutputFilename(HPCRYPTSFDPROPS hSfdProps, char* szFileName, long lBuffLength);
EXPORT LONG  CALLBACK pcSetReadmeFile(HPCRYPTSFDPROPS hSfdProps, char* szFileName);                  
EXPORT LONG  CALLBACK pcGetReadmeFile(HPCRYPTSFDPROPS hSfdProps, char* szFileName, long lBuffLength);
EXPORT LONG  CALLBACK pcSetShowDialogs(HPCRYPTSFDPROPS hSfdProps, BOOL fShow);
EXPORT LONG  CALLBACK pcGetShowDialogs(HPCRYPTSFDPROPS hSfdProps, BOOL* pfShow);	
EXPORT LONG  CALLBACK pcSetIgnoreUserCmdLine(HPCRYPTSFDPROPS hSfdProps, BOOL fIgnore);
EXPORT LONG  CALLBACK pcGetIgnoreUserCmdLine(HPCRYPTSFDPROPS hSfdProps, BOOL* pfIgnore);	
EXPORT LONG  CALLBACK pcSetExistingFileBehavior(HPCRYPTSFDPROPS hSfdProps, LONG pceBehavior);
EXPORT LONG  CALLBACK pcGetExistingFileBehavior(HPCRYPTSFDPROPS hSfdProps, LONG* ppceBehavior);	
EXPORT LONG  CALLBACK pcGetExecuteAfterCount(HPCRYPTSFDPROPS hSfdProps, LONG* plCount);
EXPORT LONG  CALLBACK pcGetExecuteAfterItem(HPCRYPTSFDPROPS hSfdProps, LONG nIndex, ExecAfterItem* pItem);	
EXPORT LONG  CALLBACK pcAddExecuteAfter(HPCRYPTSFDPROPS hSfdProps, char* lpVerb, char* lpFile, char* lpParameters, char* lpDirectory, LONG nShowCmd);	




//-----------------------------------------------------------------------------
//callback function definitions
//-----------------------------------------------------------------------------
typedef void (CALLBACK *LPFNCRYPTOCALLBACKEVENT)(LONG lEventMessage, LONG lEventParam);

		   
//-------------------------------------------------------------------------
//Callback function  - event
//-------------------------------------------------------------------------
//dll function which set callback function:
EXPORT LONG CALLBACK pcSetCallbackEventFunction( LPFNCRYPTOCALLBACKEVENT pFn );

#endif // !defined(CryptoDLL_H_E51gh47u36uue56u78o88717F_82AD_4F5C_B3F6_4CAD86481A56)




